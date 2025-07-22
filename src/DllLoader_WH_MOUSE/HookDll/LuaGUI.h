// LuaGUI.h : main header file for the LuaGUI DLL
//

#pragma once

#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"
#include "MainDlg.h"


extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}



//////////////////////////////////////////////////////////////////////////
//注意:一定要加上stdcall
extern "C" __declspec(dllexport) HHOOK __stdcall StartHook(HANDLE hMainWnd, DWORD dwThreadId);
extern "C" __declspec(dllexport) void __stdcall StopHook(HHOOK hook);
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
typedef int(__stdcall*Tluaopen_customlib)(lua_State* L);
extern Tluaopen_customlib luaopen_star;
//////////////////////////////////////////////////////////////////////////




// CLuaGUIApp
// See LuaGUI.cpp for the implementation of this class
//

class CLuaGUIApp : public CWinApp {
private:
	CString m_strThisDir;
	CString m_strHostDir;

public:
	CLuaGUIApp();
	CMainDlg*m_pdlgMain;

private:
	void loadLuaStarDll();
	void showDlg(BOOL isShowDlg);


public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CLuaGUIApp theApp;
