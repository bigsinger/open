// HookTestDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

typedef void(__stdcall*TStartHook)(HANDLE hMainWnd, DWORD dwThreadId);
typedef void(__stdcall*TStopHook)();

// CHookLoadDlg �Ի���
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
	DWORD		m_dwThreadId = 0;

	TStartHook	StartHook = NULL;
	TStopHook	StopHook = NULL;
private:
	void HiliTheWindow(CPoint point);
	BOOL RegisterHotKey(WORD wVirtualKeyCode, WORD wModifiers, int nHotId);	//ע���ȼ�
	void Hook();
	void UnHook();

	// ����
public:
	CHookLoadDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HOOKTEST_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonHook();
	afx_msg void OnBnClickedButtonUnhook();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	CStatic m_stcFinder;
	CString m_szClassName;
	int m_nHandle = 0;

	// ������
	CString m_strProcessName;
	CString m_strLastProcessName;
};
