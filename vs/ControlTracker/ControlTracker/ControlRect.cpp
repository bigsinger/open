#include "stdafx.h"
#include "ControlRect.h"

CControlRect::CControlRect( int x1, int y1, int x2, int y2 ) : 
				CRectTracker( & CRect( x1, y1, x2, y2 ), CRectTracker::resizeOutside | CRectTracker::solidLine  )
{
	Initialize();
}

CControlRect::CControlRect()
{
	Initialize();	
}

UINT CControlRect::GetHandleMask() const
{
	return ( 255 );
}

void CControlRect::Initialize()
{
	m_bSelected = FALSE;
	m_nHandleSize = 5;
	m_nStyle = CRectTracker::resizeOutside | CRectTracker::solidLine;
}

void CControlRect::SetRect( int x1, int y1, int x2, int y2 )
{ 
	m_rect.SetRect( x1, y1, x2, y2 ); 
	MoveWindow( & m_rect );
}

void CControlRect::SetRect( const CRect & rect )
{
	m_rect.SetRect( rect.left , rect.top , rect.right , rect.bottom ); 
	MoveWindow( & m_rect );
}

BOOL CControlRect::Create( LPCTSTR lpszClassName, LPCTSTR lpszWindowName , CWnd* pParentWnd, DWORD dwStyle, const CRect& Rect , UINT nID )
{
	if( Rect.IsRectEmpty() )
		return CWnd::Create( lpszClassName, lpszWindowName , WS_CHILD | dwStyle | WS_VISIBLE, m_rect, pParentWnd, nID );
	else
	{
		m_rect.CopyRect( & Rect );
		return CWnd::Create( lpszClassName, lpszWindowName , WS_CHILD | dwStyle | WS_VISIBLE, m_rect, pParentWnd, nID );
	}	
}


BOOL CControlRect::Create( WindowType wndType, LPCTSTR lpszWindowName , CWnd* pParentWnd, DWORD dwStyle, const CRect& Rect , UINT nID )
{
	if( Rect.IsRectEmpty() )
		return CWnd::Create( GetWindowClassName( wndType ), lpszWindowName , WS_CHILD | dwStyle | WS_VISIBLE, m_rect, pParentWnd, nID );
	else
	{
		m_rect.CopyRect( & Rect );
		return CWnd::Create( GetWindowClassName( wndType ), lpszWindowName , WS_CHILD | dwStyle | WS_VISIBLE, m_rect, pParentWnd, nID );
	}	
}

LPCTSTR CControlRect::GetWindowClassName( WindowType wndType )
{
	switch( wndType )
	{
		case enmScrollBar:
			return "SCROLLBAR";
		break;

		case enmStatic:
			return "STATIC";
		break;

		case enmButton:
			return "BUTTON";
		break;
	
		case enmEdit:
			return "EDIT";
		break;

		case enmListBox:
			return "LISTBOX";
		break;
	
		case enmComboBox:
			return "COMBOBOX";
		break;
		
		default:
			return "";
	}
}

void CControlRect::Track( CWnd* pWnd, CPoint point, BOOL bAllowInvert, CWnd* pWndClipTo )
{
	CRectTracker::Track( pWnd, point, bAllowInvert, pWndClipTo );
				
	MoveWindow( & m_rect );
}
