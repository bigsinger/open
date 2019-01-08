// HookTestDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "../HookDll/ShareMemType.h"

typedef void(__stdcall*TStartHook)(HANDLE hMainWnd, DWORD dwThreadId);
typedef void(__stdcall*TStopHook)();

// CHookLoadDlg 对话框
class CHookLoadDlg : public CDialog {
private:
	BOOL	m_bIsDrag;
	BOOL	m_bMouseDown;
	CRect	m_rcFinder;
	HICON	m_hIconOrig;
	HICON	m_hIconEmpty;
	HWND	m_hWndLastFocus;

	CString m_strStartPath;
	CString m_strConfigFile;

private:
	DWORD		m_dwThreadId;

	TStartHook	StartHook = NULL;
	TStopHook	StopHook = NULL;
private:
	void HiliTheWindow(CPoint point);

	// 构造
public:
	CHookLoadDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_HOOKTEST_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonHook();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	CStatic m_stcFinder;
	CString m_szClassName;
	int m_nHandle;

	// 进程名
	CString m_strProcessName;
	CString m_strLastProcessName;
	afx_msg void OnBnClickedButtonUnhook();
};
