#ifndef _CONTROLTRACKER_H
#define _CONTROLTRACKER_H

class CControlRect;

class CControlTracker : public CRectTracker
{
public:
// Sets the cursor on all the controls
	BOOL SetCursor( UINT nHitTest, UINT message );
// Adds the Control to the Tracker
	void Add( CControlRect* pObject );
// Tells weather the specified control is selected or not
	BOOL IsSelected( CControlRect* pObject ) const;
// Selects the specified control. Returns TRUE if it was initially unselected else FALSE
	BOOL Select( CControlRect* pObject );
// DeSelects the specified control. Returns TRUE if it was initially selected else FALSE
	BOOL DeSelect( CControlRect* pObject );
// Toggles the state of the object, TRUE: control was selected, else FALSE
	BOOL Toggle( CControlRect* pObject );
// Draws all the controls
	void Draw( CDC* pDC ) const;
// Starts tracking the controls
	BOOL Track( const CPoint & point, UINT nFlags = 0, BOOL bTrackRubberBand = TRUE );
// DeSelects all the controls, returns the number of controls that were selected
	int DeSelectAll();
// Creates the Control Tracker Object
	void Create( CWnd* pParentWnd );

private:
// Corrects the z-orders of all the controls
	void CorrectZOrders( CWnd* pWndInsertAfter );
// Selects a control unconditionally
	void SelectUnConditional( CControlRect* pObject );	
// Gets Bounding rect for multiply selected objects
	CRect GetBoundsRect() const;
// Parent window
	CWnd* m_pwndParent;
// Array of all items
	CArray< CControlRect*, CControlRect* > m_arrRectanglesAll;
// Array of currently selected items
	CArray< CControlRect*, CControlRect* > m_arrRectanglesSelected;

public:
	CControlTracker();
	virtual ~CControlTracker();

};

#endif
