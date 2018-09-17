// HookDll.h : main header file for the HookDll DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "ShareMemType.h"
#include "MainDlg.h"
#include "HookClass.h"
//#include "../../export/comdef/CommonMacro.h"


extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}



//注意:一定要加上stdcall
extern "C" __declspec(dllexport) void __stdcall StartHook(HANDLE hMainWnd,DWORD dwThreadId);
extern "C" __declspec(dllexport) void __stdcall StopHook();


//////////////////////////////////////////////////////////////////////////
typedef int (__stdcall*Tluaopen_customlib)(lua_State* L);
extern Tluaopen_customlib luaopen_star;



// CHookDllApp
// See HookDll.cpp for the implementation of this class
//

class CHookDllApp : public CWinApp
{
private:
	CString m_strThisDir;
	CString m_strHostDir;

public:
	CHookClass	Hook;
	CHookClass	Hook2;
	CHookClass	m_hkCreateProcess;
	CHookDllApp();
	CMainDlg*m_pdlgMain;

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CHookDllApp theApp;
