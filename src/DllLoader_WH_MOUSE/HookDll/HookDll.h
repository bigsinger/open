// HookDll.h : main header file for the HookDll DLL
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



//////////////////////////////////////////////////////////////////////////
// 三方DLL如果有导出函数需要调用，按照如下方式定义
typedef int(__stdcall* funcProc)();
//////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
// 释放注入的三方DLL
void free3rdDll();

// 播放成功的声音
void playSoundSuccess();

// 播放失败的声音
void playSoundFailed();
/////////////////////////////////////////////////////////////////////////////


// CHookDllApp
// See HookDll.cpp for the implementation of this class
//

class CHookDllApp : public CWinApp {
private:
	CString m_strThisDir;
	CString m_strHostDir;

public:
	CHookDllApp();
	CMainDlg*m_pdlgMain;

private:
	void loadLuaStarDll();
	void loadDll();
	void showDlg(BOOL isShowDlg);

	// 是否在当前自己工具的空间
	bool isInMyselfSpace();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CHookDllApp theApp;

extern std::list<HMODULE>g_3rdDllList;		// 加载的三方DLL列表
extern std::list<funcProc>g_3rdProcList;	// 加载的三方DLL的导出函数列表
