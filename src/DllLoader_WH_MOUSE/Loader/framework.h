#pragma once

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
#include <tchar.h>
#include <WinUser.h>
#include <list>
#include <string>


#define DLL_EXPORT_API __declspec(dllexport)


//////////////////////////////////////////////////////////////////////////
// 三方DLL如果有导出函数需要调用，按照如下方式定义
typedef int(__cdecl* funcProc)();
//////////////////////////////////////////////////////////////////////////



extern "C" DLL_EXPORT_API HHOOK __stdcall StartHook(HANDLE hMainWnd, DWORD dwThreadId);
extern "C" DLL_EXPORT_API void __stdcall StopHook(HHOOK hook);

inline HINSTANCE g_thisModule = NULL;		// 当前模块句柄

//////////////////////////////////////////////////////////////////////////
// 注入DLL的相关配置
//////////////////////////////////////////////////////////////////////////
inline BOOL g_isAutoFree = FALSE;			// 是否自动释放
inline std::list<HMODULE>g_3rdDllList;		// 加载的三方DLL列表
inline std::list<funcProc>g_3rdProcList;	// 加载的三方DLL的导出函数列表

inline std::wstring m_strThisDir;
inline std::wstring m_strHostDir;
/////////////////////////////////////////////////////////////////////////////


void Install();
void Uninstall();


/////////////////////////////////////////////////////////////////////////////
std::string ts2s(const TCHAR* tstr);
void TRACEW(const wchar_t* pFormat, ...);

void loadDll();

// 是否在当前自己工具的空间
bool isInMyselfSpace();

// 释放注入的三方DLL
void free3rdDll();

// 播放成功的声音
void playSoundSuccess();

// 播放失败的声音
void playSoundFailed();
/////////////////////////////////////////////////////////////////////////////
