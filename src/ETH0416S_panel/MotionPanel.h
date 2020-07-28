#if !defined(AFX_MOTIONPANEL_H__3872529D_64BA_4CA1_AA13_954D5472403D__INCLUDED_)
#define AFX_MOTIONPANEL_H__3872529D_64BA_4CA1_AA13_954D5472403D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MotionPanel.h : header file
//

#include "coloredit.h"

#include "PictureEx.h"
#include <opencv2/core/core.hpp>
#include <vector>
/////////////////////////////////////////////////////////////////////////////
// CMotionPanel dialog

class CMotionPanel : public CDialog
{
// Construction
public:
	char Golv_Mouse_SW;// 振镜 跟踪 鼠标的 开关状态，  默认关闭
	CMotionPanel(CWnd* pParent = NULL);   // standard constructor
	CString m_strINIPath;
	void LoadParam( CString strFile );
	void WriteParam( CString strFile );
	

	CPictureEx gifPicTcp; // gif 图片对象
	CPictureEx gifPicFifo;// gif 图片对象

	CRITICAL_SECTION	m_criSecEvent;    //

	int iCardCnt;// 有几个板卡连接上了
	int iConnCardSn;// 当前连接的控制卡 标号

	DWORD dwAddress ;// 目标IP地址
	DWORD dwAddress2 ;// 目标IP地址2
	int	m_iPositionX;
	int	m_iPositionY;
	int	m_iPositionZ;
	int	m_iPositionA;
	CString m_strCurrIP;
		CString m_strCurrIP2;

		unsigned char blinked; // 没有连上
		unsigned int timerCnt;// 100ms 计数器+1，   10=1s，100=10s

	double	m_iTarPositionX; // 指定位置
	int	m_iTarPositionY;
	int	m_iTarPositionZ;
	int	m_iTarPositionA;
// Dialog Data
	//{{AFX_DATA(CMotionPanel)
	enum { IDD = IDD_DIALOG1 };
	CButton	m_ctrlGoHome;
	CColorEdit	m_ctrlEditHOMEZ;
	CColorEdit	m_ctrlEditHOMEY;
	CColorEdit	m_ctrlEditHOMEX;
	CColorEdit	m_ctrlEditDINZM;
	CColorEdit	m_ctrlEditDINYM;
	CColorEdit	m_ctrlEditDINXM;
	CColorEdit	m_ctrlEditDINZP;
	CColorEdit	m_ctrlEditDINYP;
	CColorEdit	m_ctrlEditDINXP;
	CColorEdit	m_ctrlEditDIN9;
	CColorEdit	m_ctrlEditDIN8;
	CColorEdit	m_ctrlEditDIN7;
	CColorEdit	m_ctrlEditDIN6;
	CColorEdit	m_ctrlEditDIN5;
	CColorEdit	m_ctrlEditDIN4;
	CColorEdit	m_ctrlEditDIN3;
	CColorEdit	m_ctrlEditDIN2;
	CColorEdit	m_ctrlEditDIN16;
	CColorEdit	m_ctrlEditDIN15;
	CColorEdit	m_ctrlEditDIN14;
	CColorEdit	m_ctrlEditDIN13;
	CColorEdit	m_ctrlEditDIN12;
	CColorEdit	m_ctrlEditDIN11;
	CColorEdit	m_ctrlEditDIN10;
	CColorEdit	m_ctrlEditDIN1;
	int		m_iStepZA;
	int		m_iContinueMovAxisSelect;
	int		m_iGoHomeMovAxisSelect;
	CString	m_strMesg;
	int		m_iStepOrContinue;
	BOOL	m_bXGoHomeBackEZ;
	BOOL	m_bXGoHomePositive;
	BOOL	m_bYGoHomePositive;
	BOOL	m_bZGoHomePositive;

	BOOL	m_bXCloseloop;
	BOOL	m_bYCloseloop;
	BOOL	m_bZCloseloop;


	BOOL	m_bXENCODE_DEV;
	BOOL	m_bYENCODE_DEV;
	BOOL	m_bZENCODE_DEV;

	BOOL	m_bAGoHomePositive;
	BOOL	m_bDisplayCnt;
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
	BOOL	m_bHomeX;
	BOOL	m_bHomeY;
	BOOL	m_bHomeZ;
	float	m_fGoHomeOffset;
	float	m_fStepXY;
	float	m_fDistX;
	float	m_fDistY;
	float	m_fDistZ;
	BOOL	m_bDistX;
	BOOL	m_bDistY;
	BOOL	m_bDistZ;

	unsigned int iXCnt;
	unsigned int iYCnt;
	unsigned int iZCnt;
	unsigned int iXDelay;
	unsigned int iYDelay;
	unsigned int iZDelay;

	UINT m_iCaliTimeMS;
	int m_iAfterHomeOffset;

	float m_fSoftLimitPosValue ;
	float m_fSoftLimitNegaValue ;
	
	bool drawpathsw = false;
	std::vector<cv::Point> pxy;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMotionPanel)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CMotionPanel)
	afx_msg void OnBtXStepP();
	afx_msg void OnRadioX2();
	afx_msg void OnRadioY2();
	afx_msg void OnRadioZ2();
	afx_msg void OnRadioA2();
	afx_msg void OnRadioX();
	afx_msg void OnRadioY();
	afx_msg void OnRadioZ();
	afx_msg void OnRadioA();
	afx_msg void OnGohomeP();
	afx_msg void OnStop();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtXStepM();
	afx_msg void OnBtYStepP();
	afx_msg void OnBtYStepM();
	afx_msg void OnContinueP();
	afx_msg void OnContinueM();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnResetX();
	afx_msg void OnResetY();
	afx_msg void OnResetZ();
	afx_msg void OnResetA();
	afx_msg void OnTimer(UINT_PTR  nIDEvent);
	afx_msg void OnBtZStepP();
	afx_msg void OnBtZStepM();
	afx_msg void OnBtAStepM();
	afx_msg void OnBtAStepP();
	afx_msg void OnSaveparam();
	afx_msg void OnRadioStep();
	afx_msg void OnRadioContinue();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void Onquit();
	afx_msg void OnStartDist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtTestpoco();
	afx_msg void OnBnClickedBtTestio();
	afx_msg void OnBnClickedStartLine4();
	afx_msg void OnBnClickedStartArc();
	afx_msg void OnBnClickedBtTestio2();
	afx_msg void OnBnClickedStartArc2();
	afx_msg void OnBnClickedBtTestio3();
	afx_msg void OnBnClickedBtTestio4();
	CString m_str8AxisStr;
	afx_msg void OnBnClickedClearFifo();
	afx_msg void OnBnClickedStopFifo();
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();
	UINT m_iLinkCnt;
	CColorEdit m_cmdExe_flag;
	CColorEdit m_FifoExeSW;
	CColorEdit m_TcpDataTrans;
	afx_msg void OnBnClickedStartArc3();
	afx_msg void OnBnClickedBtTestio5();
	afx_msg void OnBnClickedBtTestio6();
	UINT m_iScanSpeedpps;
	afx_msg void OnBnClickedBtMouseFo();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOTIONPANEL_H__3872529D_64BA_4CA1_AA13_954D5472403D__INCLUDED_)
