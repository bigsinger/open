// HookTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HookLoader.h"
#include "HookLoaderDlg.h"
#include <Tlhelp32.h>
#include <Shlwapi.h>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#ifdef _WIN64
#define  LuaGUI_NAME	_T("Loader_x64.dll")
#else
#define  LuaGUI_NAME	_T("Loader_Win32.dll")
#endif // _WIN64


// 热键ID
const int HOTKEY_EVENT_ID_HOOK = 1001;
const int HOTKEY_EVENT_ID_UNHOOK = 1002;
const int HOTKEY_EVENT_ID_HIDE = 1003;
HHOOK m_hook = NULL;


// CHookLoadDlg 对话框
CHookLoadDlg::CHookLoadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHookLoadDlg::IDD, pParent) {
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


	TCHAR szBuff[MAX_PATH * 2] = { 0 };
	GetModuleFileName(NULL, szBuff, sizeof(szBuff));
	StrRChr(szBuff, NULL, '\\')[1] = 0;
	m_strStartPath = szBuff;
	m_strConfigFile = m_strStartPath + _T("HookLoader.ini");

	HMODULE hModule = LoadLibrary(m_strStartPath + LuaGUI_NAME);
	if (hModule) {
		StartHook = (TStartHook)GetProcAddress(hModule, "StartHook");
		StopHook = (TStopHook)GetProcAddress(hModule, "StopHook");
	} else {
		AfxMessageBox(_T("加载Hook.dll失败"));
	}

	m_bIsDrag = FALSE;
	m_bMouseDown = FALSE;
	m_hIconOrig = NULL;
	m_hIconEmpty = NULL;
	m_hWndLastFocus = NULL;
}

void CHookLoadDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FINDER, m_stcFinder);
	DDX_Text(pDX, IDC_EDIT_CLASS_NAME, m_szClassName);
	DDX_Text(pDX, IDC_EDIT_HANDLE, m_hwndTarget);
	DDX_Text(pDX, IDC_EDIT_PROCESSNAME, m_strProcessName);
}

BEGIN_MESSAGE_MAP(CHookLoadDlg, CDialog)
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON_HOOK, &CHookLoadDlg::OnBnClickedButtonHook)
	ON_BN_CLICKED(IDC_BUTTON_UNHOOK, &CHookLoadDlg::OnBnClickedButtonUnhook)
END_MESSAGE_MAP()


// CHookLoadDlg 消息处理程序

BOOL CHookLoadDlg::OnInitDialog() {
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);		// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	/************************************************************************/
	m_hIconOrig = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ORIG));
	m_hIconEmpty = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_EMPTY));
	m_stcFinder.GetWindowRect(&m_rcFinder);
	ScreenToClient(&m_rcFinder);
	/************************************************************************/

	TCHAR szBuff[MAX_PATH] = {};
	GetPrivateProfileString("main", "pname", "notepad.exe", szBuff, sizeof(szBuff), m_strConfigFile);
	m_strProcessName = szBuff;
	m_strLastProcessName = m_strProcessName;
	UpdateData(FALSE);

	// 注册热键
	UINT uHotKey = MAKELONG('H', HOTKEYF_ALT);
	RegisterHotKey(LOWORD(uHotKey), HIWORD(uHotKey), HOTKEY_EVENT_ID_HOOK);
	
	uHotKey = MAKELONG('U', HOTKEYF_ALT);
	RegisterHotKey(LOWORD(uHotKey), HIWORD(uHotKey), HOTKEY_EVENT_ID_UNHOOK);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

//////////////////////////////////////////////////////////////////////////

HANDLE GetProcessHandle(DWORD dwPid, BOOL bAllAccess/* = FALSE*/) {
	HANDLE hProcess = NULL;
	DWORD dwDesiredAccess = PROCESS_QUERY_INFORMATION | PROCESS_VM_READ;
	if (bAllAccess) { dwDesiredAccess = PROCESS_ALL_ACCESS; }

	hProcess = OpenProcess(dwDesiredAccess, 0, dwPid);
	if (hProcess == NULL) {
		return NULL;
	}
	return hProcess;
}

typedef BOOL(WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
BOOL IsWow64Process(HANDLE hProcess) {
	BOOL bIsWow64 = FALSE;

	LPFN_ISWOW64PROCESS fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(_T("kernel32")), "IsWow64Process");

	if (fnIsWow64Process != NULL) {
		if (!fnIsWow64Process(hProcess, &bIsWow64)) {
			return FALSE;
		}
	}
	return bIsWow64;
}

//////////////////////////////////////////////////////////////////////////


//由进程ID获取相应的主线程ID
DWORD GetThreadIdFromPID(DWORD dwProcessId) {
	HANDLE ThreadHandle;
	THREADENTRY32 ThreadStruct;

	ThreadHandle = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, dwProcessId);
	ThreadStruct.dwSize = sizeof(ThreadStruct);
	if (Thread32First(ThreadHandle, &ThreadStruct)) {
		do {
			if (ThreadStruct.th32OwnerProcessID == dwProcessId) {
				CloseHandle(ThreadHandle);
				return ThreadStruct.th32ThreadID;
			}
		} while (Thread32Next(ThreadHandle, &ThreadStruct));
	}
	CloseHandle(ThreadHandle);
	return 0;
}

// 获取进程名为xx的pid
int getPIdFromName(LPCTSTR szProcessName, vector<DWORD>&vtpids, int nLimit) {
	if (szProcessName == NULL) {
		return 0;
	}

	string strProcessName = szProcessName;
	transform(strProcessName.begin(), strProcessName.end(), strProcessName.begin(), _totlower);

	PROCESSENTRY32	ProcessEntry32;
	HANDLE			hSnap = INVALID_HANDLE_VALUE;

	ProcessEntry32.dwSize = sizeof(PROCESSENTRY32);

	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap == INVALID_HANDLE_VALUE) {
		return 0;
	}

	int ret = Process32First(hSnap, &ProcessEntry32);
	while (ret) {
		_tcslwr_s(ProcessEntry32.szExeFile);
		if (_tcsstr(ProcessEntry32.szExeFile, strProcessName.c_str())) {
			vtpids.push_back(ProcessEntry32.th32ProcessID);
			if ((int)vtpids.size() >= nLimit) {
				break;
			}
		}
		ret = Process32Next(hSnap, &ProcessEntry32);
	}

	CloseHandle(hSnap);

	return (int)vtpids.size();
}

//查找一个进程名对应的pid
DWORD getPIdFromName(const char *szProcessName) {
	DWORD dwProcessId = 0;
	vector<DWORD>vtpids;

	getPIdFromName(szProcessName, vtpids, 1);
	if (vtpids.empty() == false) {
		dwProcessId = vtpids[0];
	}

	return dwProcessId;
}

CString getProcessName(DWORD dwProcessId) {
	CString strName;
	PROCESSENTRY32	ProcessEntry32;
	HANDLE			hSnap;
	int				ret;

	ProcessEntry32.dwSize = sizeof(PROCESSENTRY32);

	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE) {
		ret = Process32First(hSnap, &ProcessEntry32);
		while (ret) {
			if (ProcessEntry32.th32ProcessID == dwProcessId) {
				strName = ProcessEntry32.szExeFile;
				break;
			}
			ret = Process32Next(hSnap, &ProcessEntry32);
		}

		CloseHandle(hSnap);
	}

	return strName;
}

//注册热键
BOOL CHookLoadDlg::RegisterHotKey(WORD wVirtualKeyCode, WORD wModifiers, int nHotId) {
	BOOL bSuccess = TRUE;

	if ((wModifiers & HOTKEYF_ALT) && !(wModifiers & HOTKEYF_SHIFT)) {
		//Shift->ALt
		wModifiers &= ~HOTKEYF_ALT;
		wModifiers |= MOD_ALT;
	} else if (!(wModifiers & HOTKEYF_ALT) && (wModifiers & HOTKEYF_SHIFT)) {
		//Alt->Shift
		wModifiers &= ~HOTKEYF_SHIFT;
		wModifiers |= MOD_SHIFT;
	}
	if (::RegisterHotKey(m_hWnd, nHotId, wModifiers, wVirtualKeyCode) == FALSE) {
		bSuccess = FALSE;
		AfxMessageBox("热键冲突，请检查是否有其它程序注册了此热键!");
	}

	return bSuccess;
}

//热键消息响应函数
LRESULT CHookLoadDlg::OnHotKey(WPARAM wParam, LPARAM lParam) {
	if (wParam == HOTKEY_EVENT_ID_HOOK) {
		Hook();
	} else if (wParam == HOTKEY_EVENT_ID_UNHOOK) {
		UnHook();
	}
	return 0;
}

void CHookLoadDlg::OnLButtonDown(UINT nFlags, CPoint point) {
	if (m_rcFinder.PtInRect(point)) {
		m_bMouseDown = TRUE;
		SetCapture();
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CHookLoadDlg::OnLButtonUp(UINT nFlags, CPoint point) {
	if (m_bIsDrag) {
		ReleaseCapture();
		m_bIsDrag = FALSE;
		m_stcFinder.SetIcon(m_hIconOrig);
		if (m_hWndLastFocus) {
			::InvalidateRect(NULL, NULL, TRUE);
			m_hWndLastFocus = NULL;
		}
	}
	m_bMouseDown = FALSE;

	CDialog::OnLButtonUp(nFlags, point);
}

void CHookLoadDlg::OnMouseMove(UINT nFlags, CPoint point) {
	if (m_bMouseDown) {
		::SetCursor(LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_DRAG)));
		m_stcFinder.SetIcon(m_hIconEmpty);
		m_bIsDrag = TRUE;

		//get the window
		CPoint ptCursor(point);
		ClientToScreen(&ptCursor);
		HiliTheWindow(ptCursor);
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CHookLoadDlg::HiliTheWindow(CPoint point) {
	HWND hWnd = ::WindowFromPoint(point);
	if (!hWnd) return;
	DWORD dwProcessId = 0;
	GetWindowThreadProcessId(hWnd, &dwProcessId);
	if (dwProcessId == GetCurrentProcessId())
		return;

	GetClassName(hWnd, m_szClassName.GetBuffer(128), 128);
	m_szClassName.ReleaseBuffer();
	m_hwndTarget = (intptr_t)hWnd;
	m_strProcessName = getProcessName(dwProcessId);

	UpdateData(FALSE);

	HDC hdc = ::GetWindowDC(hWnd);
	if (hdc) {
		if (m_hWndLastFocus && m_hWndLastFocus != hWnd)
			::InvalidateRect(m_hWndLastFocus, NULL, TRUE); //::RedrawWindow(m_hWndLastFocus,NULL,NULL,RDW_FRAME|RDW_ERASE|RDW_UPDATENOW);
		m_hWndLastFocus = hWnd;

		CRect rcWnd;
		::GetWindowRect(hWnd, rcWnd);
		::MapWindowPoints(NULL, hWnd, (LPPOINT)&rcWnd, 2);
		rcWnd.OffsetRect(-rcWnd.left, -rcWnd.top);
		//TRACE2("left %d,top %d,\n",rcWnd.left,rcWnd.top);

		::SelectObject(hdc, ::GetStockObject(NULL_BRUSH));
		HPEN hPen = ::CreatePen(PS_SOLID, 3, RGB(0, 0, 0));

		HPEN hPenOld = (HPEN)::SelectObject(hdc, hPen);
		::Rectangle(hdc, rcWnd.left, rcWnd.top, rcWnd.Width(), rcWnd.Height());

		::SelectObject(hdc, hPenOld);
		::DeleteObject(hPenOld);
		::ReleaseDC(hWnd, hdc);
	}
}

void CHookLoadDlg::OnBnClickedButtonHook() {
	Hook();
}

void CHookLoadDlg::OnBnClickedButtonUnhook() {
	TRACEW(L"OnUnhook - 用户点击或收到自动卸载的消息");
	UnHook();
}

void CHookLoadDlg::OnOK() {
	if (StopHook) { StopHook(m_hook); }
	__super::OnOK();
}
void CHookLoadDlg::OnCancel() {
	TRACEW(L"OnCancel - 用户点击或收到自动退出的消息");
	if (StopHook) { StopHook(m_hook); }
	__super::OnCancel();
}

void CHookLoadDlg::Hook() {
	DWORD dwProcessId = 0;

	UpdateData();

	if (m_strLastProcessName.CompareNoCase(m_strProcessName) != 0) {
		WritePrivateProfileString("main", "pname", m_strProcessName, m_strConfigFile);
	}


	if (m_hwndTarget) {
		GetWindowThreadProcessId((HWND)((PBYTE)NULL + m_hwndTarget), &dwProcessId);
	} else {
		// 通过进程名找
		dwProcessId = getPIdFromName(m_strProcessName);
	}

	m_dwThreadId = GetThreadIdFromPID(dwProcessId);

	if (m_dwThreadId == 0) {
		AfxMessageBox(_T("没有选定目标,将使用全局HOOK"));
		return;
	}

	TRACE("开始HOOK……");
	m_hook = StartHook((HWND)((PBYTE)NULL + m_hwndTarget), m_dwThreadId);
}

void CHookLoadDlg::UnHook() 	{
	if (StopHook) { StopHook(m_hook); }
}