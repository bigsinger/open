#ifndef _CONTROLRECT_H
#define _CONTROLRECT_H

class CTracker;

class CControlRect : public CRectTracker , public CWnd
{
	friend class CControlTracker;

public:

// Controls enumerated in WindowType
	enum WindowType
	{
		enmScrollBar,
		enmStatic,
		enmButton,
		enmEdit,
		enmListBox,
		enmComboBox
	};

// Can use enumerated type to create control
	BOOL Create( WindowType wndType, 
				 LPCTSTR lpszWindowName , 
				 CWnd* pParentWnd, 
				 DWORD dwStyle = WS_DISABLED, 
				 const CRect& Rect = CRect(0,0,0,0), 
				 UINT nID = 0 );	

// Can also use class name to create control
	BOOL Create( LPCTSTR lpszClassName, 
				 LPCTSTR lpszWindowName , 
				 CWnd* pParentWnd, 
				 DWORD dwStyle = WS_DISABLED, 
				 const CRect& Rect = CRect(0,0,0,0), 
				 UINT nID = 0 );	

// Tracks movement rectangle for control
	void Track( CWnd* pWnd, CPoint point, BOOL bAllowInvert = FALSE, CWnd* pWndClipTo = NULL );

// Sets bounding rectangle for control
	void SetRect( int x1, int y1, int x2, int y2 );
	void SetRect( const CRect & rect );

private:
// TRUE if selected
	BOOL m_bSelected;
// virtual function called to get handle masks
	UINT GetHandleMask() const;
// Sets default attributes for CRectTracker
	void Initialize();

public:	
// Gets class name from enum WindowType
	static LPCTSTR GetWindowClassName( WindowType wndType );
// Contructors
	CControlRect( int x1, int y1, int x2, int y2 );
	CControlRect();

};

#endif 
