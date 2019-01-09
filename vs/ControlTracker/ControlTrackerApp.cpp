// ControlTrackerApp.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ControlTrackerApp.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CControlTrackerApp

BEGIN_MESSAGE_MAP(CControlTrackerApp, CWinApp)
	//{{AFX_MSG_MAP(CControlTrackerApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControlTrackerApp construction

CControlTrackerApp::CControlTrackerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CControlTrackerApp object

CControlTrackerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CControlTrackerApp initialization

BOOL CControlTrackerApp::InitInstance()
{

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);
	
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CControlTrackerApp message handlers