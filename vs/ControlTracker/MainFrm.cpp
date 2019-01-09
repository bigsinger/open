// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "resource.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_ACTIVATE()
	ON_WM_SETCURSOR()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::OnPaint()
{
	CPaintDC dc( this ); 

// Fill background with white color
	CRect Rect;
	GetClientRect( &Rect );	
	CBrush FillBrush( RGB(255,255,255) );
	dc.FillRect( &Rect, &FillBrush );

// Allow tracker to draw its handles
	m_ControlTracker.Draw( &dc );
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect Rect;
	GetClientRect( &Rect );
	
	m_ControlTracker.Create( this );

// Create Controls
//////////////////////////////////////////////////////////////////////////////////////////////////////

	r1.Create( CControlRect::enmStatic, "Static Text Control",  this , SS_CENTERIMAGE    | SS_BITMAP,  CRect( 10,10,70,70 ) );
	r2.Create( CControlRect::enmListBox, "List Box Control",  this , WS_DISABLED  , CRect( 10,10,100,100 ) );
	r3.Create( CControlRect::enmEdit, "Button Control",  this ,  WS_DISABLED  ,  CRect( 160,110,300,250 ) );
	r4.Create( CControlRect::enmScrollBar, "ScrollBar",  this , WS_DISABLED  , CRect( 201,271,250,350 ) );
	r5.Create( CControlRect::enmButton, "Any Button",  this , WS_DISABLED  , CRect( 10,10,150,150 ) );

	r2.SendMessage( LB_ADDSTRING, 0, (LPARAM)"1- Static" );
	r2.SendMessage( LB_ADDSTRING, 0, (LPARAM)"2- ListBox" );
	r2.SendMessage( LB_ADDSTRING, 0, (LPARAM)"3- Button" );	
		
	m_ControlTracker.Add( &r1 );
	m_ControlTracker.Add( &r2 );
	m_ControlTracker.Add( &r3 );
	m_ControlTracker.Add( &r4 );
	m_ControlTracker.Add( &r5 );	
	
	r1.SendMessage( STM_SETIMAGE , IMAGE_BITMAP, (LPARAM) ::LoadBitmap( AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP) ) );
	
//////////////////////////////////////////////////////////////////////////////////////////////////////

	return 0;
}

void CMainFrame::OnLButtonDown(UINT nFlags, CPoint point) 
{	
	m_ControlTracker.Track( point , nFlags , true );

	CFrameWnd::OnLButtonDown(nFlags, point);
}

BOOL CMainFrame::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{	
	if( m_ControlTracker.SetCursor( nHitTest, message ) )
		return TRUE;
	
	return CFrameWnd::OnSetCursor(pWnd, nHitTest, message);
}