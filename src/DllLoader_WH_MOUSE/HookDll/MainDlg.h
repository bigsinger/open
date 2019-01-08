#pragma once
#include "AnchorCtrl.h"

// CMainDlg 对话框

class CMainDlg : public CDialog {
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainDlg();

	// 对话框数据
	enum { IDD = IDD_DIALOG_MAIN };

	UINT static TheadDetectPlug(LPVOID lParam);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedOk();

	// Lua脚本内容
	CString m_strScriptText;

private:
	CAnchorCtrl m_anchor;
};
