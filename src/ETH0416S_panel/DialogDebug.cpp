// DialogDebug.cpp : 实现文件
//

#include "stdafx.h"
#include "ETH0416S_panel.h"
#include "DialogDebug.h"
#include "afxdialogex.h"

#include "ETH0416SAPI.h"

// CDialogDebug 对话框

IMPLEMENT_DYNAMIC(CDialogDebug, CDialogEx)

CDialogDebug::CDialogDebug(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogDebug::IDD, pParent)
{

}

CDialogDebug::~CDialogDebug()
{
}

void CDialogDebug::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogDebug, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CDialogDebug::OnBnClickedCancel)
	ON_WM_TIMER()
//	ON_BN_CLICKED(IDOKs, &CDialogDebug::OnBnClickedOks)
ON_BN_CLICKED(IDC_BT_Y1, &CDialogDebug::OnBnClickedBtY1)
ON_BN_CLICKED(IDC_BT_Y2, &CDialogDebug::OnBnClickedBtY2)
ON_BN_CLICKED(IDC_BT_Y3, &CDialogDebug::OnBnClickedBtY3)
ON_BN_CLICKED(IDC_BT_Y4, &CDialogDebug::OnBnClickedBtY4)
ON_BN_CLICKED(IDC_BT_Y5, &CDialogDebug::OnBnClickedBtY5)
ON_BN_CLICKED(IDC_BT_Y6, &CDialogDebug::OnBnClickedBtY6)
ON_BN_CLICKED(IDC_BT_Y7, &CDialogDebug::OnBnClickedBtY7)
ON_BN_CLICKED(IDC_BT_Y8, &CDialogDebug::OnBnClickedBtY8)
ON_BN_CLICKED(IDC_BT_Y9, &CDialogDebug::OnBnClickedBtY9)
ON_BN_CLICKED(IDC_BT_Y10, &CDialogDebug::OnBnClickedBtY10)
ON_BN_CLICKED(IDC_BT_Y11, &CDialogDebug::OnBnClickedBtY11)
ON_BN_CLICKED(IDC_BT_Y12, &CDialogDebug::OnBnClickedBtY12)
ON_BN_CLICKED(IDC_BT_Y13, &CDialogDebug::OnBnClickedBtY13)
ON_BN_CLICKED(IDC_BT_Y14, &CDialogDebug::OnBnClickedBtY14)
ON_BN_CLICKED(IDC_BT_Y15, &CDialogDebug::OnBnClickedBtY15)
ON_BN_CLICKED(IDC_BT_Y16, &CDialogDebug::OnBnClickedBtY16)
ON_BN_CLICKED(IDC_BT_ALL1, &CDialogDebug::OnBnClickedBtAll1)
ON_BN_CLICKED(IDC_BT_ALL0, &CDialogDebug::OnBnClickedBtAll0)
ON_BN_CLICKED(IDC_BT_Y_STEP_P, &CDialogDebug::OnBnClickedBtYStepP)
ON_BN_CLICKED(IDC_RESET_A, &CDialogDebug::OnBnClickedResetA)
ON_BN_CLICKED(IDC_RESET_X, &CDialogDebug::OnBnClickedResetX)
ON_BN_CLICKED(IDC_RESET_Y, &CDialogDebug::OnBnClickedResetY)
ON_BN_CLICKED(IDC_RESET_Z, &CDialogDebug::OnBnClickedResetZ)
ON_BN_CLICKED(IDC_BT_X_STEP_M, &CDialogDebug::OnBnClickedBtXStepM)
ON_BN_CLICKED(IDC_BT_Y_STEP_M, &CDialogDebug::OnBnClickedBtYStepM)
END_MESSAGE_MAP()

CColorEdit *XEditArray[16];

CxShadeButton *OutputYArray[16];
#define GREEN_COLOR RGB(48,127,70)
#define RED_COLOR RGB(197,48,48)
// CDialogDebug 消息处理程序
BOOL CDialogDebug::OnInitDialog()
{
	CDialog::OnInitDialog();
	XEditArray[0]= &m_ctrlEditDIN1;
	XEditArray[1]= &m_ctrlEditDIN2;
	XEditArray[2]= &m_ctrlEditDIN3;
	XEditArray[3]= &m_ctrlEditDIN4;
	XEditArray[4]= &m_ctrlEditDIN5;
	XEditArray[5]= &m_ctrlEditDIN6;
	XEditArray[6]= &m_ctrlEditDIN7;
	XEditArray[7]= &m_ctrlEditDIN8;
	XEditArray[8]= &m_ctrlEditDIN9;
	XEditArray[9]= &m_ctrlEditDIN10;
	XEditArray[10]= &m_ctrlEditDIN11;
	XEditArray[11]= &m_ctrlEditDIN12;
	XEditArray[12]= &m_ctrlEditDIN13;
	XEditArray[13]= &m_ctrlEditDIN14;
	XEditArray[14]= &m_ctrlEditDIN15;
	XEditArray[15]= &m_ctrlEditDIN16;

	for(int ii=0;ii<16;ii++)
	{ 
		XEditArray[ii]->SetBkColor(GREEN_COLOR);
	}


	m_ctrlY1Edit.SetTextColor(RGB(255,255,255));
	m_ctrlY1Edit.SetShade(SHS_SOFTBUMP/*SHS_HARDBUMP*/,0,255,255,GREEN_COLOR);
	m_ctrlY1Edit.SetFont(_T("宋体"),18,500);
	m_ctrlY2Edit.SetTextColor(RGB(255,255,255));
	m_ctrlY2Edit.SetShade(SHS_SOFTBUMP/*SHS_HARDBUMP*/,0,255,255,GREEN_COLOR);
	m_ctrlY2Edit.SetFont(_T("宋体"),18,500);
	m_ctrlY3Edit.SetTextColor(RGB(255,255,255));
	m_ctrlY3Edit.SetShade(SHS_SOFTBUMP/*SHS_HARDBUMP*/,0,255,255,GREEN_COLOR);
	m_ctrlY3Edit.SetFont(_T("宋体"),18,500);
	m_ctrlY4Edit.SetTextColor(RGB(255,255,255));
	m_ctrlY4Edit.SetShade(SHS_SOFTBUMP/*SHS_HARDBUMP*/,0,255,255,GREEN_COLOR);
	m_ctrlY4Edit.SetFont(_T("宋体"),18,500);
	m_ctrlY5Edit.SetTextColor(RGB(255,255,255));
	m_ctrlY5Edit.SetShade(SHS_SOFTBUMP/*SHS_HARDBUMP*/,0,255,255,GREEN_COLOR);
	m_ctrlY5Edit.SetFont(_T("宋体"),18,500);
	m_ctrlY6Edit.SetTextColor(RGB(255,255,255));
	m_ctrlY6Edit.SetShade(SHS_SOFTBUMP/*SHS_HARDBUMP*/,0,255,255,GREEN_COLOR);
	m_ctrlY6Edit.SetFont(_T("宋体"),18,500);

	m_ctrlY7Edit.SetTextColor(RGB(255,255,255));
	m_ctrlY7Edit.SetShade(SHS_SOFTBUMP/*SHS_HARDBUMP*/,0,255,255,GREEN_COLOR);
	m_ctrlY7Edit.SetFont(_T("宋体"),18,500);
	m_ctrlY8Edit.SetTextColor(RGB(255,255,255));
	m_ctrlY8Edit.SetShade(SHS_SOFTBUMP/*SHS_HARDBUMP*/,0,255,255,GREEN_COLOR);
	m_ctrlY8Edit.SetFont(_T("宋体"),18,500);
	m_ctrlY9Edit.SetTextColor(RGB(255,255,255));
	m_ctrlY9Edit.SetShade(SHS_SOFTBUMP/*SHS_HARDBUMP*/,0,255,255,GREEN_COLOR);
	m_ctrlY9Edit.SetFont(_T("宋体"),18,500);
	m_ctrlY10Edit.SetTextColor(RGB(255,255,255));
	m_ctrlY10Edit.SetShade(SHS_SOFTBUMP/*SHS_HARDBUMP*/,0,255,255,GREEN_COLOR);
	m_ctrlY10Edit.SetFont(_T("宋体"),18,500);
	m_ctrlY11Edit.SetTextColor(RGB(255,255,255));
	m_ctrlY11Edit.SetShade(SHS_SOFTBUMP/*SHS_HARDBUMP*/,0,255,255,GREEN_COLOR);
	m_ctrlY11Edit.SetFont(_T("宋体"),18,500);
	m_ctrlY12Edit.SetTextColor(RGB(255,255,255));
	m_ctrlY12Edit.SetShade(SHS_SOFTBUMP/*SHS_HARDBUMP*/,0,255,255,GREEN_COLOR);
	m_ctrlY12Edit.SetFont(_T("宋体"),18,500);
	m_ctrlY13Edit.SetTextColor(RGB(255,255,255));
	m_ctrlY13Edit.SetShade(SHS_SOFTBUMP/*SHS_HARDBUMP*/,0,255,255,GREEN_COLOR);
	m_ctrlY13Edit.SetFont(_T("宋体"),18,500);
	m_ctrlY14Edit.SetTextColor(RGB(255,255,255));
	m_ctrlY14Edit.SetShade(SHS_SOFTBUMP/*SHS_HARDBUMP*/,0,255,255,GREEN_COLOR);
	m_ctrlY14Edit.SetFont(_T("宋体"),18,500);
	m_ctrlY15Edit.SetTextColor(RGB(255,255,255));
	m_ctrlY15Edit.SetShade(SHS_SOFTBUMP/*SHS_HARDBUMP*/,0,255,255,GREEN_COLOR);
	m_ctrlY15Edit.SetFont(_T("宋体"),18,500);
	m_ctrlY16Edit.SetTextColor(RGB(255,255,255));
	m_ctrlY16Edit.SetShade(SHS_SOFTBUMP/*SHS_HARDBUMP*/,0,255,255,GREEN_COLOR);
	m_ctrlY16Edit.SetFont(_T("宋体"),18,500);

	OutputYArray[0]= &m_ctrlY1Edit;
	OutputYArray[1]= &m_ctrlY2Edit;
	OutputYArray[2]= &m_ctrlY3Edit;
	OutputYArray[3]= &m_ctrlY4Edit;
	OutputYArray[4]= &m_ctrlY5Edit;
	OutputYArray[5]= &m_ctrlY6Edit;
	OutputYArray[6]= &m_ctrlY7Edit;
	OutputYArray[7]= &m_ctrlY8Edit;
	OutputYArray[8]= &m_ctrlY9Edit;
	OutputYArray[9]= &m_ctrlY10Edit;
	OutputYArray[10]= &m_ctrlY11Edit;
	OutputYArray[11]= &m_ctrlY12Edit;
	OutputYArray[12]= &m_ctrlY13Edit;
	OutputYArray[13]= &m_ctrlY14Edit;
	OutputYArray[14]= &m_ctrlY15Edit;
	OutputYArray[15]= &m_ctrlY16Edit;
	SetTimer(1,100,NULL);

	OnBnClickedBtAll0();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogDebug::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CDialogDebug::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//  DINstate的[15：0]位， 对应 DIN16 ~ DIN1 
	// 输入状态修改
	int iRet;unsigned int DINvalue;



	int tempPosX,tempPosY,tempPosZ,tempPosA;
	CString tempStr;
	Cen_readCount_C(0,0,&tempPosX);// 内部位置计数值， 第2个参数改成1就是编码器计数值
	Cen_readCount_C(1,0,&tempPosY);
	Cen_readCount_C(2,0,&tempPosZ);
	Cen_readCount_C(3,0,&tempPosA); 

	if((tempPosX!=m_iPositionX))  // m_iStepXY = m_fStepXY * m_iPPM_X;
	{tempStr.Format("%d",tempPosX/*/(double)(m_bDisplayCnt?m_iCPMM_X:m_iPPM_X)*/);GetDlgItem(IDC_POSITION_X)->SetWindowText(tempStr);m_iPositionX=tempPosX;}

	if((tempPosY!=m_iPositionY) ) 
	{tempStr.Format("%d",tempPosY/*/(double)(m_bDisplayCnt?m_iCPMM_Y:m_iPPM_Y)*/);GetDlgItem(IDC_POSITION_Y)->SetWindowText(tempStr);m_iPositionY=tempPosY;}

	if((tempPosZ!=m_iPositionZ) ) 
	{tempStr.Format("%d",tempPosZ/*/(double)(m_bDisplayCnt?m_iCPMM_Z:m_iPPM_Z)*/);GetDlgItem(IDC_POSITION_Z)->SetWindowText(tempStr);m_iPositionZ=tempPosZ;}

	if((tempPosA!=m_iPositionA) ) 
	{tempStr.Format("%d",tempPosA/*/(double)(m_bDisplayCnt?m_iCPMM_Z:m_iPPM_Z)*/);GetDlgItem(IDC_POSITION_A)->SetWindowText(tempStr);m_iPositionA=tempPosA;}

	Cen_readCount_C(0,1,&tempPosX);// 内部位置计数值， 第2个参数改成1就是编码器计数值
	Cen_readCount_C(1,1,&tempPosY);
	Cen_readCount_C(2,1,&tempPosZ);
	Cen_readCount_C(3,1,&tempPosA); 

	if((tempPosX!=m_iEnPositionX))  // m_iStepXY = m_fStepXY * m_iPPM_X;
	{tempStr.Format("%d",tempPosX/*/(double)(m_bDisplayCnt?m_iCPMM_X:m_iPPM_X)*/);GetDlgItem(IDC_POSITION_X2)->SetWindowText(tempStr);m_iEnPositionX=tempPosX;}

	if((tempPosY!=m_iEnPositionY) ) 
	{tempStr.Format("%d",tempPosY/*/(double)(m_bDisplayCnt?m_iCPMM_Y:m_iPPM_Y)*/);GetDlgItem(IDC_POSITION_Y2)->SetWindowText(tempStr);m_iEnPositionY=tempPosY;}

	if((tempPosZ!=m_iEnPositionZ) ) 
	{tempStr.Format("%d",tempPosZ/*/(double)(m_bDisplayCnt?m_iCPMM_Z:m_iPPM_Z)*/);
	GetDlgItem(IDC_POSITION_Z2)->SetWindowText(tempStr);
	m_iEnPositionZ=tempPosZ;}

	if((tempPosA!=m_iEnPositionA) ) 
	{tempStr.Format("%d",tempPosA/*/(double)(m_bDisplayCnt?m_iCPMM_Z:m_iPPM_Z)*/);GetDlgItem(IDC_POSITION_A2)->SetWindowText(tempStr);m_iEnPositionA=tempPosA;}


	CDialogEx::OnTimer(nIDEvent);
}

BOOL CDialogDebug::PreTranslateMessage(MSG* pMsg)  // 连续运动必须在这里处理消息
{
	int m_iStartSpeed,m_iSpeed;
	if ((pMsg->message == WM_LBUTTONDOWN))//&&(m_iStepOrContinue==1)
	{
		UINT nCtrlID = ((CWnd *)WindowFromPoint(pMsg->pt))->GetDlgCtrlID();
		switch (nCtrlID)
		{
		case IDC_BT_X_STEP_P:


			break;
		case IDC_BT_X_STEP_M:// 负向运动

			break;
		case IDC_BT_Y_STEP_P:// 正向运动
	
			break;
		case IDC_BT_Y_STEP_M:
		
			break;
		case IDC_BT_Z_STEP_P:
			
			break;
		case IDC_BT_Z_STEP_M:
		
			break;
		case IDC_BT_A_STEP_P:
		
			break;
		case IDC_BT_A_STEP_M:
		
			break;
		default:
			;
		}
	}

	int m_iStepXY;
	if ((pMsg->message == WM_LBUTTONUP))
	{ 
		UINT nCtrlID = ((CWnd *)WindowFromPoint(pMsg->pt))->GetDlgCtrlID();
		switch (nCtrlID)
		{
		case IDC_BT_X_STEP_P:

			break;
		case IDC_BT_X_STEP_M:
			break;
		case IDC_BT_Y_STEP_P:
			break;
		case IDC_BT_Y_STEP_M:
			break;
		case IDC_BT_Z_STEP_P:
			break;
		case IDC_BT_Z_STEP_M:
			break;
		case IDC_BT_A_STEP_P:
			break;
		case IDC_BT_A_STEP_M:
			
			break;
		default:
			;
		}
	}



	return CDialog::PreTranslateMessage(pMsg);
}
//
//void CDialogDebug::OnBnClickedOks()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}
#define GREEN_COLOR RGB(48,127,70)
#define RED_COLOR RGB(197,48,48)
char Yvalue[16]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

void CDialogDebug::UpdateUIOUTputValue(int num)
{
	Yvalue[num]=Yvalue[num]?0:1;
	OutputYArray[num]->SetTextColor(RGB(255,255,255));
	OutputYArray[num]->SetShade(SHS_SOFTBUMP/*SHS_HARDBUMP*/,0,255,255,Yvalue[num]?GREEN_COLOR:RED_COLOR);
	OutputYArray[num]->SetFont(_T("宋体"),18,500);
	CString tempStr;tempStr.Format(_T("%d"),Yvalue[num]);
	OutputYArray[num]->SetWindowText(tempStr);
	OutputYArray[num]->Invalidate();
	Cen_writeOutbit_B(num+1,Yvalue[num]);
}
void CDialogDebug::OnBnClickedBtY1()
{
	UpdateUIOUTputValue(0);
}


void CDialogDebug::OnBnClickedBtY2()
{
	UpdateUIOUTputValue(1);
}


void CDialogDebug::OnBnClickedBtY3()
{
	UpdateUIOUTputValue(2);
}


void CDialogDebug::OnBnClickedBtY4()
{
	UpdateUIOUTputValue(3);
}


void CDialogDebug::OnBnClickedBtY5()
{
	UpdateUIOUTputValue(4);
}


void CDialogDebug::OnBnClickedBtY6()
{
	UpdateUIOUTputValue(5);
}


void CDialogDebug::OnBnClickedBtY7()
{
	UpdateUIOUTputValue(6);
}


void CDialogDebug::OnBnClickedBtY8()
{
	UpdateUIOUTputValue(7);
}


void CDialogDebug::OnBnClickedBtY9()
{
	UpdateUIOUTputValue(8);
}


void CDialogDebug::OnBnClickedBtY10()
{
	UpdateUIOUTputValue(9);
}


void CDialogDebug::OnBnClickedBtY11()
{
	UpdateUIOUTputValue(10);
}


void CDialogDebug::OnBnClickedBtY12()
{
	UpdateUIOUTputValue(11);
}


void CDialogDebug::OnBnClickedBtY13()
{
	UpdateUIOUTputValue(12);
}


void CDialogDebug::OnBnClickedBtY14()
{
	UpdateUIOUTputValue(13);
}


void CDialogDebug::OnBnClickedBtY15()
{
	UpdateUIOUTputValue(14);
}


void CDialogDebug::OnBnClickedBtY16()
{
	UpdateUIOUTputValue(15);
}

#define BACKGROUND_COLOR RGB(180,200,234)
void CDialogDebug::OnBnClickedBtAll1()
{
	for(int num=0;num<16;num++)
	{
		Yvalue[num]=1;

		OutputYArray[num]->SetTextColor(BACKGROUND_COLOR);
		OutputYArray[num]->SetShade(SHS_SOFTBUMP/*SHS_HARDBUMP*/,0,255,255,Yvalue[num]?GREEN_COLOR:RED_COLOR);
		OutputYArray[num]->SetFont(_T("宋体"),18,500);
		CString tempStr;tempStr.Format(_T("%d"),Yvalue[num]);
		OutputYArray[num]->SetWindowText(tempStr);
		OutputYArray[num]->Invalidate();
		Cen_writeOutbit_B(num+1,Yvalue[num]);
	}
}


void CDialogDebug::OnBnClickedBtAll0()
{
	for(int num=0;num<16;num++)
	{
		Yvalue[num]=0;

		OutputYArray[num]->SetTextColor(RGB(255,255,255));
		OutputYArray[num]->SetShade(SHS_SOFTBUMP/*SHS_HARDBUMP*/,0,255,255,Yvalue[num]?GREEN_COLOR:RED_COLOR);
		OutputYArray[num]->SetFont(_T("宋体"),18,500);
		CString tempStr;tempStr.Format(_T("%d"),Yvalue[num]);
		OutputYArray[num]->SetWindowText(tempStr);
		OutputYArray[num]->Invalidate();
		Cen_writeOutbit_B(num+1,Yvalue[num]);
	}
}


void CDialogDebug::OnBnClickedBtYStepP()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDialogDebug::OnBnClickedResetA()
{
	Cen_resetCount_B(3,0); // 计数
	Cen_resetCount_B(3,1); // 编码器
}


void CDialogDebug::OnBnClickedResetX()
{

	Cen_resetCount_B(0,0); // 计数
	Cen_resetCount_B(0,1); // 编码器

}


void CDialogDebug::OnBnClickedResetY()
{
	

	Cen_resetCount_B(1,0); // 计数
	Cen_resetCount_B(1,1); // 编码器
}


void CDialogDebug::OnBnClickedResetZ()
{

	Cen_resetCount_B(2,0); // 计数
	Cen_resetCount_B(2,1); // 编码器
}


void CDialogDebug::OnBnClickedBtXStepM()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDialogDebug::OnBnClickedBtYStepM()
{
	// TODO: 在此添加控件通知处理程序代码
}
