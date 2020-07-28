#pragma once

#include "coloredit.h"
#include "xShadeButton.h"

// CDialogDebug 对话框

class CDialogDebug : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogDebug)

public:
	CDialogDebug(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogDebug();
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

	int CMD_EXET;// 单位ms

	int	m_iPositionX;
	int	m_iPositionY;
	int	m_iPositionZ;
	int	m_iPositionA;
	int	m_iEnPositionX;
	int	m_iEnPositionY;
	int	m_iEnPositionZ;
	int	m_iEnPositionA;
// 对话框数据
	enum { IDD = IDD_DIALOG_DEBUG };

	CColorEdit	m_ctrlEditHOMEA;
	CColorEdit	m_ctrlEditHOMEZ;
	CColorEdit	m_ctrlEditHOMEY;
	CColorEdit	m_ctrlEditHOMEX;
	CColorEdit	m_ctrlEditDINAM;
	CColorEdit	m_ctrlEditDINZM;
	CColorEdit	m_ctrlEditDINYM;
	CColorEdit	m_ctrlEditDINXM;
	CColorEdit	m_ctrlEditDINAP;
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


	CxShadeButton m_ctrlY1Edit;
	CxShadeButton m_ctrlY2Edit;
	CxShadeButton m_ctrlY3Edit;
	CxShadeButton m_ctrlY4Edit;
	CxShadeButton m_ctrlY5Edit;
	CxShadeButton m_ctrlY6Edit;
	CxShadeButton m_ctrlY7Edit;
	CxShadeButton m_ctrlY8Edit;
	CxShadeButton m_ctrlY9Edit;
	CxShadeButton m_ctrlY10Edit;
	CxShadeButton m_ctrlY11Edit;
	CxShadeButton m_ctrlY12Edit;
	CxShadeButton m_ctrlY13Edit;
	CxShadeButton m_ctrlY14Edit;
	CxShadeButton m_ctrlY15Edit;
	CxShadeButton m_ctrlY16Edit;

	void UpdateUIOUTputValue(int num);
protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnBnClickedOks();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtY1();
	afx_msg void OnBnClickedBtY2();
	afx_msg void OnBnClickedBtY3();
	afx_msg void OnBnClickedBtY4();
	afx_msg void OnBnClickedBtY5();
	afx_msg void OnBnClickedBtY6();
	afx_msg void OnBnClickedBtY7();
	afx_msg void OnBnClickedBtY8();
	afx_msg void OnBnClickedBtY9();
	afx_msg void OnBnClickedBtY10();
	afx_msg void OnBnClickedBtY11();
	afx_msg void OnBnClickedBtY12();
	afx_msg void OnBnClickedBtY13();
	afx_msg void OnBnClickedBtY14();
	afx_msg void OnBnClickedBtY15();
	afx_msg void OnBnClickedBtY16();
	afx_msg void OnBnClickedBtAll1();
	afx_msg void OnBnClickedBtAll0();
	afx_msg void OnBnClickedBtYStepP();
	afx_msg void OnBnClickedResetA();
	afx_msg void OnBnClickedResetX();
	afx_msg void OnBnClickedResetY();
	afx_msg void OnBnClickedResetZ();
	afx_msg void OnBnClickedBtXStepM();
	afx_msg void OnBnClickedBtYStepM();
};
