// ETH0416S_panel.h : main header file for the ETH0416S_panel application
//

#if !defined(AFX_ETH0416S_panel_H__4456AD7E_FDBE_4DE2_97BA_011102324022__INCLUDED_)
#define AFX_ETH0416S_panel_H__4456AD7E_FDBE_4DE2_97BA_011102324022__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CETH0416S_panelApp:
// See ETH0416S_panel.cpp for the implementation of this class
//

class CETH0416S_panelApp : public CWinApp
{
public:
	CETH0416S_panelApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CETH0416S_panelApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CETH0416S_panelApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ETH0416S_panel_H__4456AD7E_FDBE_4DE2_97BA_011102324022__INCLUDED_)
