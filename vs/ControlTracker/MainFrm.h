// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__68172A58_08B0_11D5_8DF0_0080AD8358A1__INCLUDED_)
#define AFX_MAINFRM_H__68172A58_08B0_11D5_8DF0_0080AD8358A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ControlTracker/ControlRect.h"
#include "ControlTracker/ControlTracker.h"

class CControlTracker;

class CMainFrame : public CFrameWnd
{
	CControlTracker m_ControlTracker;		

	CControlRect r1, r2, r3, r4, r5;

public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);	
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__68172A58_08B0_11D5_8DF0_0080AD8358A1__INCLUDED_)
