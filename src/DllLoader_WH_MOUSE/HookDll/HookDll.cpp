// HookDll.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "HookDll.h"
#include <Shlwapi.h>
#include "Constant.h"
#include "..\HookLoader\Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//


//////////////////////////////////////////////////////////////////////////
HHOOK		hhk = NULL;
HANDLE		hMapFile;
int			nSize;
//////////////////////////////////////////////////////////////////////////
// 注入DLL的相关配置
// 是否自动释放
BOOL 	g_isAutoFree = FALSE;
//////////////////////////////////////////////////////////////////////////


// CHookDllApp

BEGIN_MESSAGE_MAP(CHookDllApp, CWinApp)
END_MESSAGE_MAP()



//////////////////////////////////////////////////////////////////////////
LRESULT MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
	return CallNextHookEx(hhk, nCode, wParam, lParam);
}

__declspec(dllexport) HHOOK __stdcall StartHook(HANDLE hMainWnd, DWORD dwThreadId) {
	// 注意：这里不能判断hhk是否为NULL，否则连续注入会失败。
	hhk = SetWindowsHookEx(WH_MOUSE, (HOOKPROC)MouseProc, AfxGetInstanceHandle(), dwThreadId);
	TRACE("StartHook hook：%p", hhk);
	return hhk;
}
__declspec(dllexport) void __stdcall StopHook(HHOOK hook) {
	TRACE("StopHook hook：%p", hook);
	if (hook) {
		UnhookWindowsHookEx(hook);
		hhk = NULL;
	}
}
//////////////////////////////////////////////////////////////////////////
// 释放注入的三方DLL
void free3rdDll() {
	if (g_isAutoFree) {
		for (auto it = g_3rdDllList.begin(); it != g_3rdDllList.end(); it++) {
			BOOL ret = ::FreeLibrary(*it);
			TRACE("FreeLibrary: %p ret: %d last error: %d", *it, ret, GetLastError());
		}
		g_3rdDllList.clear();
		g_3rdProcList.clear();
	}
}

// 播放成功的声音
void playSoundSuccess() {
	::Beep(523, 400);	// do
#if _DEBUG	
#endif
}


// 播放失败的声音
void playSoundFailed() {
	::Beep(659, 400);	// mi
#if _DEBUG	
#endif
}

// CHookDllApp construction

CHookDllApp::CHookDllApp() {
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CHookDllApp object

CHookDllApp theApp;
std::list<HMODULE>g_3rdDllList;		// 加载的三方DLL列表
std::list<funcProc>g_3rdProcList;	// 加载的三方DLL的导出函数列表
Tluaopen_customlib luaopen_star = NULL;


BOOL CHookDllApp::InitInstance() {
	CWinApp::InitInstance();

	//////////////////////////////////////////////////////////////////////////
	TCHAR szBuff[MAX_PATH * 2] = { 0 };
	GetModuleFileName(this->m_hInstance, szBuff, sizeof(szBuff));
	StrRChr(szBuff, NULL, '\\')[1] = 0;
	m_strThisDir = szBuff;

	GetModuleFileName(NULL, szBuff, sizeof(szBuff));
	StrRChr(szBuff, NULL, '\\')[1] = 0;
	m_strHostDir = szBuff;

	if (!isInMyselfSpace()) {
		TRACE("成功注入到目标进程!");

#if 0
		// 可以做一些HOOK
		Hook.Create(recv, NewRecv);
		Hook.Change();
		Hook2.Create(WSARecv, NewWSARecv);
		Hook2.Change();
		m_hkCreateProcess.Create(CreateProcess, newCreateProcess);
		m_hkCreateProcess.Change();
#endif

#if 0
		// 加载Lua的库
		CString strLuaDllFilePath = m_strThisDir + "lua.dll";
		if (GetFileAttributes(strLuaDllFilePath) != -1) {
			HMODULE hModule = ::LoadLibrary(strLuaDllFilePath);
			if (hModule == NULL) {
				AfxMessageBox("lua.dll load failed");
			}
		} else {
			AfxMessageBox("lua.dll not found");
		}
#endif

		BOOL isLoadLuaStar = FALSE;
		BOOL isCreateDlg = FALSE;
		BOOL isShowDlg = FALSE;
		CString mConfigFilePath = m_strThisDir + _T("hookloader.ini");
		if (GetFileAttributes(mConfigFilePath) != -1) {
			isLoadLuaStar = GetPrivateProfileInt(_T("dll"), _T("lua"), FALSE, mConfigFilePath);
			isCreateDlg = GetPrivateProfileInt(_T("dll"), _T("dlg"), FALSE, mConfigFilePath);
			isShowDlg = GetPrivateProfileInt(_T("dll"), _T("dlgshow"), FALSE, mConfigFilePath);
			g_isAutoFree = GetPrivateProfileInt(_T("dll"), _T("autofree"), FALSE, mConfigFilePath);
		}

		loadDll();	// 加载配置的三方DLL

		if (isLoadLuaStar) { loadLuaStarDll(); }
		if (isCreateDlg) { showDlg(isShowDlg); }

		// 播放成功的声音
		playSoundSuccess();
	}
	//////////////////////////////////////////////////////////////////////////

	return TRUE;
}

int CHookDllApp::ExitInstance() {
	StopHook(hhk);

	if (m_pdlgMain) {
		delete m_pdlgMain;
		m_pdlgMain = NULL;
	}

	// 释放注入的三方DLL
	free3rdDll();
	playSoundSuccess();

	return CWinApp::ExitInstance();
}

void CHookDllApp::showDlg(BOOL isShowDlg) {
	m_pdlgMain = new CMainDlg;
	m_pdlgMain->Create(CMainDlg::IDD, AfxGetMainWnd());
	m_pdlgMain->ShowWindow(isShowDlg ? SW_SHOW : SW_HIDE);
}

void CHookDllApp::loadLuaStarDll() {
	CString strDllFileName = STAR_LUA_LIB_NAME;
	CString strLuaDllFilePath = m_strThisDir + STAR_LUA_LIB_NAME;
	if (GetFileAttributes(strLuaDllFilePath) != -1) {
		HMODULE hModule = ::LoadLibrary(strLuaDllFilePath);
		if (hModule == NULL) {
			AfxMessageBox(strDllFileName + " load failed");
		} else {
			CString strFunctionName = "luaopen_star";
			luaopen_star = (Tluaopen_customlib)GetProcAddress(hModule, strFunctionName);
			if (luaopen_star == NULL) {
				AfxMessageBox(strFunctionName + " not found");
			}
		}
	} else {
		AfxMessageBox(strDllFileName + " not found");
	}
}

void CHookDllApp::loadDll() {
	TCHAR szDllName[MAX_PATH * 2] = { 0 };
	TCHAR szProcName[MAX_PATH * 2] = { 0 };
	CString strDllName;
	CStringA strProcName;
	CString mConfigFilePath = m_strThisDir + _T("hookloader.ini");
	// 加载配置的dll
	CString strSection;
	CString strKeyName;
#ifdef _WIN64
	strKeyName = _T("name64");
#else
	strKeyName = _T("name32");
#endif // _WIN64

	int nDllCount = GetPrivateProfileInt(_T("dll"), _T("count"), 0, mConfigFilePath);
	for (auto i = 0; i < nDllCount; i++) {
		strSection.Format(_T("%d"), i + 1);
		::GetPrivateProfileString(strSection, strKeyName, NULL, szDllName, sizeof(szDllName), mConfigFilePath);
		::GetPrivateProfileString(strSection, _T("proc"), NULL, szProcName, sizeof(szProcName), mConfigFilePath);
		strDllName = szDllName;
		strProcName = szProcName;
		if (!strDllName.IsEmpty() && strDllName.Find(':') == -1) {
			// 相对路径
			strDllName = m_strThisDir + strDllName;
			if (strDllName.Find('.') == -1) { strDllName += _T(".dll"); }
		}

		if (!strDllName.IsEmpty()) {
			if (GetFileAttributes(strDllName) != -1) {
				HMODULE hModule = ::LoadLibrary(strDllName);
				if (hModule ) {
					g_3rdDllList.push_back(hModule);

					// 如果有配置导出函数则调用
					if (!strProcName.IsEmpty()) {
						funcProc proc = (funcProc)GetProcAddress(hModule, strProcName);
						if (proc) {
							proc();
							g_3rdProcList.push_back(proc);
						} else {
							AfxMessageBox(strProcName + " not found");
						}
					}

#pragma region 自动卸载或退出
					HWND hWndLoader = FindWindow(_T("#32770"), _T("HookLoader"));
					BOOL isAutoExit = GetPrivateProfileInt(_T("dll"), _T("autoexit"), TRUE, mConfigFilePath);
					BOOL isAutoUninstall = GetPrivateProfileInt(_T("dll"), _T("autouninstall"), TRUE, mConfigFilePath);
					if (isAutoExit) {
						::PostMessage(hWndLoader, WM_COMMAND, IDCANCEL,0);
					} else if (isAutoUninstall) {
						::PostMessage(hWndLoader, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_UNHOOK, BN_CLICKED), 0);
					}
#pragma endregion
				} else {
					AfxMessageBox(strDllName + " load failed");
				}
			} else {
				AfxMessageBox(strDllName + " not found");
			}
		}

	}
}

// 是否在当前自己工具的空间
bool CHookDllApp::isInMyselfSpace() {
	return m_strHostDir.CompareNoCase(m_strThisDir) == 0;
}