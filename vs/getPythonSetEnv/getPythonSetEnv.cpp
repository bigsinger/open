// getPythonSetEnv.cpp : 定义控制台应用程序的入口点。
//

/*
HKEY_CLASSES_ROOT\Python.CompiledFile\DefaultIcon

HKEY_CLASSES_ROOT\Python.CompiledFile\shell\open\command


HKEY_CLASSES_ROOT\Python.File\DefaultIcon

HKEY_CLASSES_ROOT\Python.File\shell\open\command


HKEY_CLASSES_ROOT\Python.NoConFile\DefaultIcon

HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Python.CompiledFile\DefaultIcon


HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Python.CompiledFile\shell\open\command

HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Python.File\DefaultIcon

HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Python.File\shell\Edit with IDLE\command

HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Python.File\shell\open\command

HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Python.NoConFile\DefaultIcon



HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\Python.exe

HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Installer\Folders

HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\App Paths\Python.exe

HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Python\PythonCore\2.7\InstallPath
HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\Session Manager\Environment  Path
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Environment


*/

#include "stdafx.h"
#include <atlstr.h>


CString GetStartPath()
{
	TCHAR szTemp[MAX_PATH];
	GetModuleFileName(NULL, szTemp, sizeof(szTemp) / sizeof(TCHAR));
	_tcsrchr(szTemp, '\\')[1] = 0;
	return szTemp;
}


CString GetRegKeyStr(HKEY key, LPCTSTR subkey)
{
	CString strResult;
	HKEY hkey;
	LONG retval = RegOpenKeyEx(key, subkey, 0, KEY_QUERY_VALUE, &hkey);

	if (retval == ERROR_SUCCESS) {
		long datasize = MAX_PATH;
		TCHAR data[MAX_PATH] = {0};
		RegQueryValue(hkey, NULL, data, &datasize);
		strResult = data;
		RegCloseKey(hkey);
	}

	return strResult;
}

//获取文件路径的父目录，返回的路径最后带斜杠
CString GetParentPath(const CString&strFilePath)
{
	CString strPath;
	strPath = strFilePath;
	strPath.Replace('/','\\');

	if ( strPath.Right(1)=="\\" ) {
		strPath = strPath.Left(strPath.GetLength()-1);
	}

	int nPos = strPath.ReverseFind('\\');
	if ( nPos!=-1 ) {
		strPath = strPath.Left(nPos+1);
	}

	return strPath;
}

bool SetPathEnvironment(const CString&strEnv)
{
	bool bSuccess = false;
	HKEY hKey;

	LONG lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment"), 0, KEY_ALL_ACCESS, &hKey );
	if ( lRet == ERROR_SUCCESS ) {
		lRet = RegSetValueEx(hKey, _T("Path"), 0, REG_EXPAND_SZ, (const BYTE *)(LPCTSTR)strEnv, (strEnv.GetLength() + 1) * sizeof(TCHAR) );
		DWORD dwResult = 0;
		SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE , 0,LPARAM(_T("Environment")), SMTO_ABORTIFHUNG, 5000, &dwResult);
		bSuccess = (lRet == ERROR_SUCCESS);
		lRet = RegCloseKey(hKey);
	}else{
		//
	}

	return bSuccess;
}

void SetPythonToEnv(const CString&strPythonPath)
{
	CString strEnv;
	CString strScriptsPath = strPythonPath + _T("Scripts");
	strEnv = getenv("PATH");
	if ( strEnv.Find(strPythonPath)==-1 ) {
		strEnv = strPythonPath + ";" + strEnv;
	}
	if ( strEnv.Find(strScriptsPath)==-1 ) {
		strEnv = strScriptsPath + ";" + strEnv;
	}

	_tprintf(_T("%s\n\n"), strEnv);
	SetPathEnvironment(strEnv);

	strEnv = getenv("PATH");
	_tprintf(_T("%s\n\n"), strEnv);
}


int _tmain(int argc, _TCHAR* argv[])
{
	CString strPath = GetRegKeyStr(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\App Paths\\Python.exe"));
	CString strPyInstallPath;
	if ( GetFileAttributes(strPath)!=-1 ) {
		strPyInstallPath = GetParentPath(strPath);
	}

	if ( argc >= 2 ) {
		CString strParams;
		strParams += CString(argv[1]) + _T(" ");				//py脚本文件
		strParams += strPyInstallPath + _T(" ");	//py安装路径，末尾带斜杠
		for ( int i = 2; i < argc; ++i ) {
			strParams += CString(argv[i])  + _T(" ");
		}
		ShellExecute(NULL, _T("open"), strPath, strParams, NULL, SW_SHOWNORMAL);
	}else{
		SetPythonToEnv(strPath);
		system("pause");
	}

	return 0;
}

