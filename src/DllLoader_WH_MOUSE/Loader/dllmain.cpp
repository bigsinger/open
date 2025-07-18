// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <stdio.h>
#include "..\HookLoader\Resource.h"


BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
    switch (dwReason) {
    case DLL_PROCESS_ATTACH:
        g_thisModule = hModule;
        Install();
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        Uninstall();
        break;
    }
    return TRUE;
}

//////////////////////////////////////////////////////////////////////////
HHOOK hhk = NULL;
//////////////////////////////////////////////////////////////////////////
LRESULT MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    return CallNextHookEx(hhk, nCode, wParam, lParam);
}

DLL_EXPORT_API HHOOK __stdcall StartHook(HANDLE hMainWnd, DWORD dwThreadId) {
    // 注意：这里不能判断hhk是否为NULL，否则连续注入会失败。
    hhk = SetWindowsHookEx(WH_MOUSE, (HOOKPROC)MouseProc, g_thisModule, dwThreadId);
    TRACEW(L"StartHook hook：%p", hhk);
    return hhk;
}
DLL_EXPORT_API void __stdcall StopHook(HHOOK hook) {
    TRACEW(L"StopHook hook：%p", hook);
    if (hook) {
        UnhookWindowsHookEx(hook);
        hhk = NULL;
    }
}
//////////////////////////////////////////////////////////////////////////


std::string ts2s(const TCHAR* tstr) {
#ifdef UNICODE
	int len = WideCharToMultiByte(CP_UTF8, 0, tstr, -1, nullptr, 0, nullptr, nullptr);
	if (len <= 0) return "";
	std::string result(len - 1, '\0'); // -1 去掉 '\0'
	WideCharToMultiByte(CP_UTF8, 0, tstr, -1, &result[0], len, nullptr, nullptr);
	return result;
#else
	return std::string(tstr);
#endif
}

void TRACEW(const wchar_t* pFormat, ...) {
	wchar_t buffer[1024] = {};
	va_list args;
	va_start(args, pFormat);
	vswprintf_s(buffer, pFormat, args);
	OutputDebugStringW(buffer);
}

//////////////////////////////////////////////////////////////////////////
// 释放注入的三方DLL
void free3rdDll() {
    if (g_isAutoFree) {
        for (auto it = g_3rdDllList.begin(); it != g_3rdDllList.end(); it++) {
            BOOL ret = ::FreeLibrary(*it);
            TRACEW(L"FreeLibrary: %p ret: %d last error: %d", *it, ret, GetLastError());
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
//////////////////////////////////////////////////////////////////////////

void Install() {
	TCHAR szBuff[MAX_PATH * 2] = { 0 };
	GetModuleFileName(g_thisModule, szBuff, sizeof(szBuff));
	_tcsrchr(szBuff, '\\')[1] = 0;
	m_strThisDir = szBuff;

	GetModuleFileName(NULL, szBuff, sizeof(szBuff));
	_tcsrchr(szBuff, '\\')[1] = 0;
	m_strHostDir = szBuff;

	if (!isInMyselfSpace()) {
		TRACEW(L"成功注入到目标进程!");

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
				TRACEW(L"lua.dll load failed");
			}
		} else {
			TRACEW(L"lua.dll not found");
		}
#endif

		BOOL isLoadLuaStar = FALSE;
		BOOL isCreateDlg = FALSE;
		BOOL isShowDlg = FALSE;
		std::wstring mConfigFilePath = m_strThisDir + _T("hookloader.ini");
		if (GetFileAttributes(mConfigFilePath.c_str()) != -1) {
			isLoadLuaStar = GetPrivateProfileInt(_T("dll"), _T("lua"), FALSE, mConfigFilePath.c_str());
			isCreateDlg = GetPrivateProfileInt(_T("dll"), _T("dlg"), FALSE, mConfigFilePath.c_str());
			isShowDlg = GetPrivateProfileInt(_T("dll"), _T("dlgshow"), FALSE, mConfigFilePath.c_str());
			g_isAutoFree = GetPrivateProfileInt(_T("dll"), _T("autofree"), FALSE, mConfigFilePath.c_str());
		}

		loadDll();	// 加载配置的三方DLL

		// TODO 这里后面配置为三方DLL列表里加载
		//if (isLoadLuaStar) { loadLuaStarDll(); }
		//if (isCreateDlg) { showDlg(isShowDlg); }

		// 播放成功的声音
		playSoundSuccess();
	}
}

void Uninstall() {
	StopHook(hhk);

	// 释放注入的三方DLL
	free3rdDll();
	playSoundSuccess();
}


void loadDll() {
	TCHAR szBuff[MAX_PATH] = { 0 };
	TCHAR szDllName[MAX_PATH] = { 0 };
	TCHAR szProcName[MAX_PATH] = { 0 };
	std::wstring strDllName;
	std::string strProcName;
	std::wstring mConfigFilePath = m_strThisDir + _T("hookloader.ini");
	// 加载配置的dll
	std::wstring strSection;
	std::wstring strKeyName;
#ifdef _WIN64
	strKeyName = _T("name64");
#else
	strKeyName = _T("name32");
#endif // _WIN64

	int nDllCount = GetPrivateProfileInt(_T("dll"), _T("count"), 0, mConfigFilePath.c_str());
	for (auto i = 0; i < nDllCount; i++) {
		_stprintf_s(szBuff, sizeof(szBuff), _T("%d"), i + 1);
		strSection.assign(szBuff);

		::GetPrivateProfileString(strSection.c_str(), strKeyName.c_str(), NULL, szDllName, sizeof(szDllName), mConfigFilePath.c_str());
		::GetPrivateProfileString(strSection.c_str(), _T("proc"), NULL, szProcName, sizeof(szProcName), mConfigFilePath.c_str());
		strDllName = szDllName;
		strProcName = ts2s(szProcName);
		if (!strDllName.empty() && strDllName.find(':') == std::string::npos) {
			// 相对路径
			strDllName = m_strThisDir + strDllName;
			if (strDllName.find('.') == std::string::npos) { strDllName += _T(".dll"); }
		}

		if (!strDllName.empty()) {
			if (GetFileAttributes(strDllName.c_str()) != -1) {
				HMODULE hModule = ::LoadLibrary(strDllName.c_str());
				if (hModule) {
					g_3rdDllList.push_back(hModule);

					// 如果有配置导出函数则调用
					if (!strProcName.empty()) {
						funcProc proc = (funcProc)GetProcAddress(hModule, strProcName.c_str());
						if (proc) {
							proc();
							g_3rdProcList.push_back(proc);
						} else {
							TRACEW(L"not found: %s", szProcName);
						}
					}

#pragma region 自动卸载或退出
					HWND hWndLoader = FindWindow(_T("#32770"), _T("HookLoader"));
					BOOL isAutoExit = GetPrivateProfileInt(_T("dll"), _T("autoexit"), TRUE, mConfigFilePath.c_str());
					BOOL isAutoUninstall = GetPrivateProfileInt(_T("dll"), _T("autouninstall"), TRUE, mConfigFilePath.c_str());
					if (isAutoExit) {
						::PostMessage(hWndLoader, WM_COMMAND, IDCANCEL, 0);
					} else if (isAutoUninstall) {
						::PostMessage(hWndLoader, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_UNHOOK, BN_CLICKED), 0);
					}
#pragma endregion
				} else {
					TRACEW(L"load failed: %s", strDllName.c_str());
				}
			} else {
				TRACEW(L"not found: %s", strDllName.c_str());
			}
		}

	}
}

// 是否在当前自己工具的空间
bool isInMyselfSpace() {
	return m_strHostDir.compare(m_strThisDir) == 0;
}