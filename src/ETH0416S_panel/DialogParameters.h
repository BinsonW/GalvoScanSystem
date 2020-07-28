#if !defined(AFX_DIALOGPARAMETERS_H__10A5D6DB_0285_499C_838B_9F7293EE7910__INCLUDED_)
#define AFX_DIALOGPARAMETERS_H__10A5D6DB_0285_499C_838B_9F7293EE7910__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogParameters.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogParameters dialog

class CDialogParameters : public CDialog
{
// Construction
public:
	CDialogParameters(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogParameters)
	enum { IDD = IDD_DIALOG_PARAMETERS };
	float	m_fAccTime;
	float	m_fAccTimeY;
	float	m_fAccTimeZ;
	int		m_iPPM_X;
	int		m_iPPM_Y;
	int		m_iPPM_Z;
	int		m_iCPMM_X;
	int		m_iCPMM_Y;
	int		m_iCPMM_Z;
	float	m_fStartSpeedX;
	float	m_fSpeedX;
	float	m_fStartSpeedY;
	float	m_fSpeedY;
	float	m_fStartSpeedZ;
	float	m_fSpeedZ;
	float	m_fHomeSpeedX;
	float	m_fHomeSpeedY;
	float	m_fHomeSpeedZ;
	BOOL	m_bXGoHomeBackEZ;
	BOOL	m_bXGoHomePositive;
	BOOL	m_bYGoHomePositive;
	BOOL	m_bZGoHomePositive;
	BOOL	m_bAGoHomePositive;

	BOOL	m_bXCloseloop;
	BOOL	m_bYCloseloop;
	BOOL	m_bZCloseloop;
	BOOL	m_bXENCODE_DEV;
	BOOL	m_bYENCODE_DEV;
	BOOL	m_bZENCODE_DEV;

	BOOL	m_bDisplayCnt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogParameters)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogParameters)
	afx_msg void OnSaveparam();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedDisplayCnt();
	afx_msg void OnEnChangecpumYz();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck12();
	afx_msg void OnBnClickedCheck13();
	afx_msg void OnBnClickedCheck14();
	UINT m_iCaliTimeMS;
	int m_iAfterHomeOffset;
	afx_msg void OnBnClickedParseRtl();
	afx_msg void OnBnClickedParseRtl2();
	float m_fSoftLimitPosValue;
	float m_fSoftLimitNegaValue;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGPARAMETERS_H__10A5D6DB_0285_499C_838B_9F7293EE7910__INCLUDED_)
