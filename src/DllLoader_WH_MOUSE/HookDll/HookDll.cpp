// HookDll.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "HookDll.h"
#include <Shlwapi.h>
#include "Constant.h"

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
HANDLE		hMapFile;
int			nSize;
//////////////////////////////////////////////////////////////////////////


// CHookDllApp

BEGIN_MESSAGE_MAP(CHookDllApp, CWinApp)
END_MESSAGE_MAP()





// CHookDllApp construction

CHookDllApp::CHookDllApp() {
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CHookDllApp object

CHookDllApp theApp;

Tluaopen_customlib luaopen_star = NULL;


BOOL CHookDllApp::InitInstance() {
	CWinApp::InitInstance();

	showDlg(TRUE);
	loadLuaStarDll();

	return TRUE;
}

int CHookDllApp::ExitInstance() {
	if (m_pdlgMain) {
		delete m_pdlgMain;
		m_pdlgMain = NULL;
	}
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