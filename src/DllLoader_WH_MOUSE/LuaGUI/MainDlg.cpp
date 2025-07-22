// MainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LuaGUI.h"
#include "MainDlg.h"
#include "Constant.h"

#ifdef _DEBUG
#pragma comment(lib,"lua53D.lib")
#else
#pragma comment(lib,"lua53.lib")
#endif


// 热键ID
const int HOTKEY_EVENT_ID_COMMAND = 1010;


// CMainDlg 对话框

IMPLEMENT_DYNAMIC(CMainDlg, CDialog)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
	, m_strScriptText(_T("")) {
}

CMainDlg::~CMainDlg() {
}

BOOL CMainDlg::PreTranslateMessage(MSG* pMsg) {
	// 屏蔽ESC关闭窗体
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) {
		return TRUE;
	} else {
		return __super::PreTranslateMessage(pMsg);
	}
}

void CMainDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strScriptText);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
	ON_BN_CLICKED(IDOK, &CMainDlg::OnBnClickedOk)
	ON_WM_SIZE()
END_MESSAGE_MAP()


void runScriptText(lua_State* L, const CString&strScriptText) {
	CStringA strScriptTextA; strScriptTextA = strScriptText;
	if (luaL_loadbuffer(L, strScriptTextA, strScriptTextA.GetLength(), strScriptTextA) || lua_pcall(L, 0, 0, 0)) {
		const char*szError = lua_tostring(L, -1);
		CString strText; strText = szError;
		AfxMessageBox(strText);
	}

}


// CMainDlg 消息处理程序

BOOL CMainDlg::OnInitDialog() {
	__super::OnInitDialog();

	m_anchor.SetParent(this);
	m_anchor.Fix(IDC_EDIT1, CAnchorCtrl::LeftTopRightBottom);
	m_anchor.Fix(IDOK, CAnchorCtrl::TopRight);

	// 注册热键
	UINT uHotKey = MAKELONG('C', HOTKEYF_ALT);
	RegisterHotKey(LOWORD(uHotKey), HIWORD(uHotKey), HOTKEY_EVENT_ID_COMMAND);

	return TRUE;
}

void CMainDlg::OnSize(UINT nType, int cx, int cy) {
	__super::OnSize(nType, cx, cy);
	m_anchor.Resize();
}

void CMainDlg::OnBnClickedOk() {
	UpdateData(TRUE);

	lua_State* L = luaL_newstate();
	if (L) {
		luaL_openlibs(L);
		if (luaopen_star != NULL) {
			luaopen_star(L);
		}
		runScriptText(L, m_strScriptText);
		lua_close(L);
	}
}

void CMainDlg::OnOK() {
}

void CMainDlg::OnCancel() {
	AfxMessageBox(L"请退出注入器");
}

//注册热键
BOOL CMainDlg::RegisterHotKey(WORD wVirtualKeyCode, WORD wModifiers, int nHotId) {
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
		AfxMessageBox(L"热键冲突，请检查是否有其它程序注册了此热键!");
	}

	return bSuccess;
}

//热键消息响应函数
LRESULT CMainDlg::OnHotKey(WPARAM wParam, LPARAM lParam) {
	if (wParam == HOTKEY_EVENT_ID_COMMAND) {
		TRACEW(L"[LuaGUI]OnHotKey");
	}
	return 0;
}