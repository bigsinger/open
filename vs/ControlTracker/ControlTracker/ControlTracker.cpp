#include "stdafx.h"
#include "ControlTracker.h"
#include "ControlRect.h"

CControlTracker::CControlTracker() : m_pwndParent( NULL )
{

}

CControlTracker::~CControlTracker()
{

}

void CControlTracker::Create( CWnd* pWnd )
{
	ASSERT( m_pwndParent == NULL );
	m_pwndParent = pWnd;
}
void CControlTracker::Add( CControlRect* pObject )
{
	m_arrRectanglesAll.Add( pObject );

	CorrectZOrders( pObject );
}

void CControlTracker::CorrectZOrders( CWnd* pWndInsertAfter )
{	
	for( int i=0; i < m_arrRectanglesAll.GetSize(); i++ )	
	{
		m_arrRectanglesAll.GetAt( i )->SetWindowPos( pWndInsertAfter , 0,0,0,0, SWP_NOMOVE   | SWP_NOSIZE   | SWP_SHOWWINDOW   );
	}
}

BOOL CControlTracker::IsSelected( CControlRect* pObject ) const
{
	for( int i=0; i < m_arrRectanglesSelected.GetSize(); i++ )
	{
		if( m_arrRectanglesSelected[i] == pObject )
		{
			return TRUE;
		}
	}

	return FALSE;
}

void CControlTracker::SelectUnConditional( CControlRect* pObject )
{
	m_arrRectanglesSelected.Add( pObject );
	pObject->m_bSelected = TRUE;
}

BOOL CControlTracker::Select( CControlRect* pObject )
{
	if( ! IsSelected( pObject ) )
	{
		SelectUnConditional( pObject );
		
		return TRUE;
	}

	return FALSE;
}

BOOL CControlTracker::Toggle( CControlRect* pObject )
{
	if( IsSelected( pObject ) )
	{
		DeSelect( pObject );
		return TRUE;
	}
	else
	{
		Select( pObject );
		return FALSE;
	}
	
}

BOOL CControlTracker::DeSelect( CControlRect* pObject )
{
	CArray< CControlRect*, CControlRect* > TempArray;

	if( IsSelected( pObject ) )
	{
		for( int i=0; i < m_arrRectanglesSelected.GetSize(); i++ )
		{
			if( m_arrRectanglesSelected[i] == pObject )
			{ 				
				pObject->m_bSelected = FALSE;
			}
			else
			{
				TempArray.Add( m_arrRectanglesSelected[i] );
			}

		}

		m_arrRectanglesSelected.RemoveAll();
		
		for( int i=0; i < TempArray.GetSize(); i++ )
		{
			m_arrRectanglesSelected.Add( TempArray[i] );
		}
		
		return ( ! pObject->m_bSelected );
	}

	return FALSE;
}

int CControlTracker::DeSelectAll()
{
	int UpperBound = m_arrRectanglesSelected.GetSize();

	for( int i=0; i < m_arrRectanglesAll.GetSize(); i++ )
	{
		m_arrRectanglesAll[i]->m_bSelected = FALSE;
	}

	m_arrRectanglesSelected.RemoveAll();

	return UpperBound;
}

BOOL CControlTracker::Track( const CPoint & point, UINT nFlags , BOOL bTrackRubberBand )
{
	ASSERT( m_pwndParent != NULL );

	int InitialCount = 0;
	CRect InitialBoundRect;
	int pX, pY;

	for( int i=0; i < m_arrRectanglesAll.GetSize(); i++ )
	{				
		int nHit = m_arrRectanglesAll[i]->HitTest( point );

		if( nHit != CRectTracker::hitNothing  )
		{
			// See if the control key was down
			if( ( nFlags & MK_CONTROL ) != 0 )
			{
				Toggle( m_arrRectanglesAll[i] );
				m_pwndParent->Invalidate();
				return TRUE;						
			}						

			// See if the shift key was down
			if( ( nFlags & MK_SHIFT ) != 0 )
			{
				Select( m_arrRectanglesAll[i] );
				m_pwndParent->Invalidate();
				return TRUE;
			}

			if( ! IsSelected( m_arrRectanglesAll[i] ) ) 
				InitialCount = DeSelectAll();
			
			Select( m_arrRectanglesAll[i] );

			if( nHit == CRectTracker::hitMiddle )
			{
				InitialBoundRect = GetBoundsRect();

				m_rect.CopyRect( & InitialBoundRect );
				
				CRectTracker::Track( m_pwndParent, point );

				pX = InitialBoundRect.left - m_rect.left;
				pY = InitialBoundRect.top - m_rect.top;

				// Offset each selected control
				for( int j = 0; j < m_arrRectanglesSelected.GetSize(); j++ )
				{
					m_arrRectanglesSelected[j]->SetRect( m_arrRectanglesSelected[j]->m_rect.left - pX, 
														 m_arrRectanglesSelected[j]->m_rect.top - pY,
														 m_arrRectanglesSelected[j]->m_rect.right - pX,
														 m_arrRectanglesSelected[j]->m_rect.bottom - pY );
				}


			}
			else
			{
				m_arrRectanglesAll[i]->Track( m_pwndParent, point );				
			}


			m_pwndParent->Invalidate();

			return TRUE;
		}

	}	

// Exit if the shift key or the control key was down
	if( ( ( nFlags & MK_SHIFT ) != 0 ) || ( ( nFlags & MK_CONTROL ) != 0 ) )
	{
		return FALSE;
	}

// Deselect all the controls
	DeSelectAll();

	if( bTrackRubberBand == FALSE )
	{
		m_pwndParent->Invalidate( WM_PAINT );
		return FALSE;
	}

// Start the selection rect
	TrackRubberBand( m_pwndParent, point );
	m_rect.NormalizeRect();

	CRect temp;

	// Now select objects according to the resized rectangle
	for( int i=0; i < m_arrRectanglesAll.GetSize(); i++ )
	{
		temp.IntersectRect( & m_rect, & m_arrRectanglesAll[i]->m_rect );
		
		if( m_arrRectanglesAll[i]->m_rect.EqualRect( & temp ) )
			Select( m_arrRectanglesAll[i] );

	}
	
	m_pwndParent->Invalidate();
	
	return FALSE;
}

CRect CControlTracker::GetBoundsRect() const
{
	int Left(0), Right(0), Top(0), Bottom(0);
	int pLeft(0), pRight(0), pTop(0), pBottom(0);

	pLeft = m_arrRectanglesSelected[0]->m_rect.left;
	pTop = m_arrRectanglesSelected[0]->m_rect.top;
	pRight = m_arrRectanglesSelected[0]->m_rect.right;
	pBottom = m_arrRectanglesSelected[0]->m_rect.bottom;

	
	for( int i = 1; i < m_arrRectanglesSelected.GetSize(); i++ )
	{
		Left = m_arrRectanglesSelected[ i ]->m_rect.left;			
		Top = m_arrRectanglesSelected[ i ]->m_rect.top;
		Right = m_arrRectanglesSelected[ i ]->m_rect.right;
		Bottom = m_arrRectanglesSelected[ i ]->m_rect.bottom;

		if( Left < pLeft )
			pLeft = Left;

		if( Top < pTop )
			pTop = Top;

		if( Bottom > pBottom )
			pBottom = Bottom;

		if( Right > pRight )
			pRight = Right;

	}

	return CRect( pLeft, pTop, pRight, pBottom );
}

void CControlTracker::Draw( CDC* pDC ) const
{
// Loop can iterate through all elements of the selected array
	for( int i=0; i < m_arrRectanglesAll.GetSize(); i++ )
	{		
		if( m_arrRectanglesAll[i]->m_bSelected )
		{
			m_arrRectanglesAll[i]->Draw( pDC );
		}
		else
		{

		}

	}	
}

BOOL CControlTracker::SetCursor( UINT nHitTest, UINT message )
{
	ASSERT( m_pwndParent != NULL );

	for( int i=0; i < m_arrRectanglesAll.GetSize(); i++ )
	{		
		if( m_arrRectanglesAll[i]->SetCursor( m_pwndParent, nHitTest ) )
			return TRUE;
	}	

	return FALSE;
}