// ColorEdit.cpp : implementation file
//

#include "stdafx.h"
#include "ColorEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorEdit

CColorEdit::CColorEdit()
{
	m_bkEditCorlor = RGB(255,0,0);
}

CColorEdit::~CColorEdit()
{
}


BEGIN_MESSAGE_MAP(CColorEdit, CEdit)
	//{{AFX_MSG_MAP(CColorEdit)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorEdit message handlers

void CColorEdit::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rectClient;
	GetClientRect(&rectClient);
	BYTE RED,GREEN,BLUE;
	RED = GetRValue(m_bkEditCorlor);
	GREEN = GetRValue(m_bkEditCorlor);
	BLUE = GetRValue(m_bkEditCorlor);
	dc.FillSolidRect(rectClient,m_bkEditCorlor);
	dc.Rectangle(&rectClient);//,RGB(255,0,0),m_bkEditCorlor);
	rectClient.left-=1;
	rectClient.top-=1;
	rectClient.right-=1;
	rectClient.bottom-=1;
	dc.FillSolidRect(rectClient,m_bkEditCorlor);
}

void CColorEdit::SetBkColor(COLORREF bkColor)
{
	if(bkColor!=m_bkEditCorlor)
	{
		m_bkEditCorlor = bkColor;
		Invalidate();
	}
}
void CColorEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
    //TRACE("* %08X: down\n", ::GetTickCount());

	//Pass this message to the ToolTip control
	//RelayEvent(WM_LBUTTONDOWN,(WPARAM)nFlags,MAKELPARAM(LOWORD(point.x),LOWORD(point.y)));

    //If we are tracking this button, cancel it
  //  if (m_tracking) {
  //      TRACKMOUSEEVENT t = {
  //          sizeof(TRACKMOUSEEVENT),
  //          TME_CANCEL | TME_LEAVE,
  //          m_hWnd, 0
		//};
  //      if (::_TrackMouseEvent(&t)) {
  //          m_tracking = false;
  //      }
  //  }
 AfxMessageBox(_T("1111"));
    //Default-process the message
	CEdit::OnLButtonDown(nFlags, point);
    //m_button_down = true;
}