// ETH0416S_panel.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ETH0416S_panel.h"
#include "MotionPanel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CETH0416S_panelApp

BEGIN_MESSAGE_MAP(CETH0416S_panelApp, CWinApp)
	//{{AFX_MSG_MAP(CETH0416S_panelApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CETH0416S_panelApp construction

CETH0416S_panelApp::CETH0416S_panelApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CETH0416S_panelApp object

CETH0416S_panelApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CETH0416S_panelApp initialization

//CETH0416S_panelDlg dlg;

BOOL CETH0416S_panelApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	
	CMotionPanel MotionPanel;
	m_pMainWnd = &MotionPanel/*dlg*/;
	int nResponse = /*dlg*/MotionPanel.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
