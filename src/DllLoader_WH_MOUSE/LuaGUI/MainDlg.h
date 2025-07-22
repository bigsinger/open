#pragma once
#include "AnchorCtrl.h"

// CMainDlg �Ի���

class CMainDlg : public CDialog {
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainDlg();

	// �Ի�������
	enum { IDD = IDD_DIALOG_MAIN };


protected:
	BOOL RegisterHotKey(WORD wVirtualKeyCode, WORD wModifiers, int nHotId);	//ע���ȼ�
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedOk();
	afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);

	// Lua�ű�����
	CString m_strScriptText;

private:
	CAnchorCtrl m_anchor;
};
