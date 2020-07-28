#if !defined(AFX_COLOREDIT_H__BDFA3BE0_7782_4FDC_B7CA_3F34230A0C5E__INCLUDED_)
#define AFX_COLOREDIT_H__BDFA3BE0_7782_4FDC_B7CA_3F34230A0C5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorEdit window

class CColorEdit : public CEdit
{
// Construction
public:
	CColorEdit();
	COLORREF m_bkEditCorlor;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetBkColor(COLORREF bkColor);
	virtual ~CColorEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorEdit)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLOREDIT_H__BDFA3BE0_7782_4FDC_B7CA_3F34230A0C5E__INCLUDED_)
