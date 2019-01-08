// MainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HookDll.h"
#include "MainDlg.h"

#ifdef _DEBUG
#pragma comment(lib,"lua53D.lib")
#else
#pragma comment(lib,"lua53.lib")
#endif

// CMainDlg 对话框

IMPLEMENT_DYNAMIC(CMainDlg, CDialog)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
	, m_strScriptText(_T(""))
{
}

CMainDlg::~CMainDlg()
{
}

BOOL CMainDlg::PreTranslateMessage(MSG* pMsg) {
	// 屏蔽ESC关闭窗体
	if( pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE ) {
		return TRUE;
	} else {
		return __super::PreTranslateMessage(pMsg);
	}
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strScriptText);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDOK, &CMainDlg::OnBnClickedOk)
END_MESSAGE_MAP()


void runScriptText(lua_State* L, const CString&strScriptText) {
	if ( luaL_loadbuffer(L, strScriptText, strScriptText.GetLength(), strScriptText) || lua_pcall(L, 0, 0, 0) ){
		const char*szError = lua_tostring(L, -1);
		AfxMessageBox(szError);
	}

}


// CMainDlg 消息处理程序

BOOL CMainDlg::OnInitDialog() {
	__super::OnInitDialog();
	
	m_anchor.SetParent(this);
	m_anchor.Fix(IDC_EDIT1, CAnchorCtrl::LeftTopRightBottom);
	m_anchor.Fix(IDOK, CAnchorCtrl::TopRight);

	return TRUE;
}

void CMainDlg::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);
	m_anchor.Resize();
}

void CMainDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	//char szCode[]={"\0xB8\0x00\0x04\0x00\0x00\0x89\0x45\0xF8\0x90\0x90\0x90\0x90\0x90\0x90\0x90\0x90"};
	//memcpy( PBYTE(NULL)+0x0047278C,szCode,sizeof(szCode) );

	//char szCode[]={"\0xB8\0x40\0x01\0x00\0x00"};
	//memcpy( PBYTE(NULL)+0x00472787,szCode,sizeof(szCode) );
	//AfxMessageBox(_T("patched OK"));
	//AfxBeginThread(TheadDetectPlug,NULL);

	lua_State* L = luaL_newstate();
	if ( L ){
		luaL_openlibs(L);
		if ( luaopen_star != NULL ) {
			luaopen_star(L);
		}
		runScriptText(L, m_strScriptText);
		lua_close(L);
	}
}

void CMainDlg::OnOK()
{
}

void CMainDlg::OnCancel()
{
	AfxMessageBox("请退出注入器");
}

UINT CMainDlg::TheadDetectPlug(LPVOID lParam)
{
	//TRACE0("\n");

	return 0;
}