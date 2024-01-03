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
//ע��:һ��Ҫ����stdcall
extern "C" __declspec(dllexport) void __stdcall StartHook(HANDLE hMainWnd, DWORD dwThreadId);
extern "C" __declspec(dllexport) void __stdcall StopHook();
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
typedef int(__stdcall*Tluaopen_customlib)(lua_State* L);
extern Tluaopen_customlib luaopen_star;
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
// ����DLL����е���������Ҫ���ã��������·�ʽ����
typedef int(__stdcall* funcProc)();
//////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
// �ͷ�ע�������DLL
void free3rdDll();

// ���ųɹ�������
void playSoundSuccess();

// ����ʧ�ܵ�����
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
	void showDlg();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CHookDllApp theApp;

extern std::list<HMODULE>g_3rdDllList;	// ���ص�����DLL�б�
