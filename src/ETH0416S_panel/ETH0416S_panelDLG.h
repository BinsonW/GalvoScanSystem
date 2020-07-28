// ETH0416S_panelDlg.h : header file
//

#if !defined(AFX_ETH0416S_panelDLG_H__70765B79_EA1E_4AE5_9946_CF6C698F4887__INCLUDED_)
#define AFX_ETH0416S_panelDLG_H__70765B79_EA1E_4AE5_9946_CF6C698F4887__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ETH0416SAPI.h"
#include "MotionPanel.h "

/////////////////////////////////////////////////////////////////////////////
// CETH0416S_panelDlg dialog

class CETH0416S_panelDlg : public CDialog
{
// Construction
public:

	CETH0416S_panelDlg(CWnd* pParent = NULL);	// standard constructor

	CWinThread* m_pWorkThread;
	CMotionPanel MotionPanel;

// Dialog Data
	//{{AFX_DATA(CETH0416S_panelDlg)
	enum { IDD = IDD_ETH0416S_panel_DIALOG };
	CIPAddressCtrl	m_ipAddress;
	UINT	m_iDA1Value;
	UINT	m_iDA2Value;
	UINT	m_iDA3Value;
	UINT	m_iDA4Value;
	UINT	m_iDOnum;
	UINT	m_iDOValue;
	UINT	m_iPulseAmount;
	UINT	m_iPulseCycle;
	UINT	m_iPulseOutputDONUM;
	UINT	m_iDA5Value;
	UINT	m_iDA6Value;
	UINT	m_iPWMfreq;
	UINT	m_iPWMhighLevel;
	BOOL	m_iUsing10ns;
	UINT	m_iDA7Value;
	double	m_dTestDouble;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CETH0416S_panelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CETH0416S_panelDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnButtonDaset();
	afx_msg void OnButtonDoset();
	afx_msg void OnButtonDinget();
	afx_msg void OnButtonLimitget();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnButtonPulseout();
	afx_msg void OnButtonPwmout();
	afx_msg void OnButtonPwmlcose();
	afx_msg void OnButtonGetstatus();
	afx_msg void OnButtonStop();
	afx_msg void OnButtontestGetin();
	afx_msg void OnButtonRed();
	afx_msg void OnButtonSetIp();
	afx_msg void OnButton2();
	afx_msg void OnButtonDaDelay();
	afx_msg void OnSetAllDa0();
	afx_msg void OnSetAllDa45535();
	afx_msg void OnButtonDosetAll0();
	afx_msg void OnButtonDosetAll1();
	afx_msg void OnButtonKaoji();
	afx_msg void OnButtonDaDelay2();
	afx_msg void OnButtonDaDelay3();
	afx_msg void OnButtonBMP();
	afx_msg void OnButtonNewMotionTest();
	afx_msg void OnBtMotionPanel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ETH0416S_panelDLG_H__70765B79_EA1E_4AE5_9946_CF6C698F4887__INCLUDED_)
