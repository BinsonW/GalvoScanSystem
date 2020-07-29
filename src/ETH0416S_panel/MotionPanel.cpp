// MotionPanel.cpp : implementation file
//

//#include "poco-net.cpp"
#include "stdafx.h"
#include <windows.h> 
#include "ETH0416S_panel.h"
#include "MotionPanel.h"
#include "ETH0416SAPI.h"
#include "DialogParameters.h"
#include "DlgIPSetting.h"
#include "DialogTargetIP.h"

#include "DialogDebug.h"

#include "SkinH.h"
#include "math.h"

#include "drawpath.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CMotionPanel dialog


CMotionPanel::CMotionPanel(CWnd* pParent /*=NULL*/)
	: CDialog(CMotionPanel::IDD, pParent)
	, iXCnt(1)
	, iYCnt(1)
	, iZCnt(1)
	, iXDelay(0)
	, iYDelay(0)
	, iZDelay(0)
	, m_str8AxisStr(_T(""))
	, m_iLinkCnt(0)
	, m_iScanSpeedpps(1000000)
{
	//{{AFX_DATA_INIT(CMotionPanel)
	m_iStepZA = 100;
	m_iContinueMovAxisSelect = 0;
	m_iGoHomeMovAxisSelect = 0;
	m_strMesg = _T("");
	m_iStepOrContinue = 1;
	m_bXGoHomePositive = FALSE;
	m_bXGoHomeBackEZ = FALSE;
	m_bYGoHomePositive = FALSE;
	m_bZGoHomePositive = FALSE;

	m_bXCloseloop = FALSE;
	m_bYCloseloop = FALSE;
	m_bZCloseloop = FALSE;

	m_bXENCODE_DEV = FALSE;
	m_bYENCODE_DEV = FALSE;
	m_bZENCODE_DEV = FALSE;

	m_bAGoHomePositive = FALSE;
	m_bDisplayCnt = TRUE;
	m_fAccTime = 0.3f;
	m_fAccTimeY = 0.0f;
	m_fAccTimeZ = 0.0f;
	m_iPPM_X = 0;
	m_iPPM_Y = 0;
	m_iPPM_Z = 0;
	m_iCPMM_X=0;
	m_iCPMM_Y=0;
	m_iCPMM_Z=0;

	m_fStartSpeedX = 0.0f;
	m_fSpeedX = 0.0f;
	m_fStartSpeedY = 0.0f;
	m_fSpeedY = 0.0f;
	m_fStartSpeedZ = 0.0f;
	m_fSpeedZ = 0.0f;
	m_fHomeSpeedX = 0.0f;
	m_fHomeSpeedY = 0.0f;
	m_fHomeSpeedZ = 0.0f;
	m_bHomeX = FALSE;
	m_bHomeY = FALSE;
	m_bHomeZ = FALSE;
	m_fGoHomeOffset = 0.0f;
	m_fStepXY = 0.0f;
	m_fDistX = 0.0f;
	m_fDistY = 0.0f;
	m_fDistZ = 0.0f;
	m_bDistX = FALSE;
	m_bDistY = FALSE;
	m_bDistZ = FALSE;

	m_iTarPositionX=0; // 指定位置
	m_iTarPositionY=0xFFFFFFFF;
	m_iTarPositionZ=0xFFFFFFFF;
	m_iTarPositionA=0xFFFFFFFF;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	blinked=0;
	timerCnt=0;
	Golv_Mouse_SW = 0;
}

//	DDX_Radio(pDX, IDC_RADIO_X, m_iContinueMovAxisSelect);

void CMotionPanel::DoDataExchange(CDataExchange* pDX)
{ 
	//DDX_Radio(pDX, IDC_RADIO_X2, m_iGoHomeMovAxisSelect);
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMotionPanel)
	// 	DDX_Check(pDX, IDC_CHECK1, m_bXGoHomePositive);
	// 	DDX_Check(pDX, IDC_CHECK2, m_bYGoHomePositive);
	// 	DDX_Check(pDX, IDC_CHECK3, m_bZGoHomePositive);
	// 	DDX_Check(pDX, IDC_CHECK4, m_bAGoHomePositive);



	DDX_Text(pDX, IDC_EDIT_STEP_XY, m_fStepXY);




	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_8AXIS_STR, m_str8AxisStr);
	DDX_Text(pDX, IDC_LINK_CNT, m_iLinkCnt);
	DDX_Control(pDX, IDC_CMD_IDLE, m_cmdExe_flag);
	DDX_Control(pDX, IDC_FIFO_EXE, m_FifoExeSW);
	DDX_Control(pDX, IDC_TRANSFER_TCP, m_TcpDataTrans);
	DDX_Text(pDX, IDC_EDIT1, m_iScanSpeedpps);
}


BEGIN_MESSAGE_MAP(CMotionPanel, CDialog)
	//{{AFX_MSG_MAP(CMotionPanel)
	ON_BN_CLICKED(IDC_BT_X_STEP_P, OnBtXStepP)
	ON_BN_CLICKED(IDC_RADIO_X2, OnRadioX2)
	ON_BN_CLICKED(IDC_RADIO_Y2, OnRadioY2)
	ON_BN_CLICKED(IDC_RADIO_Z2, OnRadioZ2)
	ON_BN_CLICKED(IDC_RADIO_A2, OnRadioA2)
	ON_BN_CLICKED(IDC_RADIO_X, OnRadioX)
	ON_BN_CLICKED(IDC_RADIO_Y, OnRadioY)
	ON_BN_CLICKED(IDC_RADIO_Z, OnRadioZ)
	ON_BN_CLICKED(IDC_RADIO_A, OnRadioA)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_BT_X_STEP_M, OnBtXStepM)
	ON_BN_CLICKED(IDC_BT_Y_STEP_P, OnBtYStepP)
	ON_BN_CLICKED(IDC_BT_Y_STEP_M, OnBtYStepM)
	ON_BN_CLICKED(IDC_CONTINUE_P, OnContinueP)
	ON_BN_CLICKED(IDC_CONTINUE_M, OnContinueM)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_RESET_X, OnResetX)
	ON_BN_CLICKED(IDC_RESET_Y, OnResetY)
	ON_BN_CLICKED(IDC_RESET_Z, OnResetZ)
	ON_BN_CLICKED(IDC_RESET_A, OnResetA)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BT_Z_STEP_P, OnBtZStepP)
	ON_BN_CLICKED(IDC_BT_Z_STEP_M, OnBtZStepM)
	ON_BN_CLICKED(IDC_BT_A_STEP_M, OnBtAStepM)
	ON_BN_CLICKED(IDC_BT_A_STEP_P, OnBtAStepP)
	ON_BN_CLICKED(IDC_SAVEPARAM, OnSaveparam)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_quit, Onquit)
	ON_BN_CLICKED(IDC_START_DIST, OnStartDist)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BT_TESTPOCO, &CMotionPanel::OnBnClickedBtTestpoco)
	ON_BN_CLICKED(IDC_BT_TESTIO, &CMotionPanel::OnBnClickedBtTestio)
	ON_BN_CLICKED(IDC_START_LINE4, &CMotionPanel::OnBnClickedStartLine4)
	ON_BN_CLICKED(IDC_START_ARC, &CMotionPanel::OnBnClickedStartArc)
	ON_BN_CLICKED(IDC_BT_TESTIO2, &CMotionPanel::OnBnClickedBtTestio2)
	ON_BN_CLICKED(IDC_START_ARC2, &CMotionPanel::OnBnClickedStartArc2)
	ON_BN_CLICKED(IDC_BT_TESTIO3, &CMotionPanel::OnBnClickedBtTestio3)
	ON_BN_CLICKED(IDC_BT_TESTIO4, &CMotionPanel::OnBnClickedBtTestio4)
	ON_BN_CLICKED(IDC_CLEAR_FIFO, &CMotionPanel::OnBnClickedClearFifo)
	ON_BN_CLICKED(IDC_STOP_FIFO, &CMotionPanel::OnBnClickedStopFifo)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, &CMotionPanel::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_START_ARC3, &CMotionPanel::OnBnClickedStartArc3)
	ON_BN_CLICKED(IDC_BT_TESTIO5, &CMotionPanel::OnBnClickedBtTestio5)
	ON_BN_CLICKED(IDC_BT_TESTIO6, &CMotionPanel::OnBnClickedBtTestio6)
	ON_BN_CLICKED(IDC_BT_MOUSE_FO, &CMotionPanel::OnBnClickedBtMouseFo)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON2, &CMotionPanel::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMotionPanel::OnBnClickedButton3)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMotionPanel message handlers

FifoCmd cmdArr2[200000];
unsigned short curX=32768,curY=32768;// 振镜XY，当前位置在中间即32768
// 运动控制函数，控制振镜移动到指定的点
//FifoCmd *pBuffer, 缓冲区指针
//int *pk, 缓冲区当前指令个数
//POINT startPt, 当前点坐标----起始点(振镜单位p),xy取值0-65535
//POINT endPt ， 结束点(振镜单位p),xy取值0-65535
//int SpeedMov ，速度 p/s
int ScanMoveTo(FifoCmd* pBuffer, int* pk, POINT startPt, POINT endPt, int SpeedMov)
{// 因为振镜质量有不同，所以MoveTo也要插补
	int i, k = *pk;
	double Sdist;// 总长度
	double sinAngel, cosAngel; // 夹角  正弦，余弦
	int stepS, stepCnt, stepDelay, stepLeft;
	Sdist = (startPt.x - endPt.x) * (startPt.x - endPt.x) + (startPt.y - endPt.y) * (startPt.y - endPt.y);
	Sdist = sqrt(Sdist);

	sinAngel = (endPt.y - startPt.y) / Sdist;
	cosAngel = (endPt.x - startPt.x) / Sdist;

	int SdistInt;
	SdistInt = Sdist;
	// 每次步距预设50
	stepS = 50;// 每步走的振镜单位
	stepCnt = SdistInt / 50;
	stepLeft = SdistInt % 50;
	if (stepCnt == 0)
	{
		stepDelay = (SdistInt * 1000000) / SpeedMov;// 单位us

		// 点的数据给入
		pBuffer[k++].cmd = 0x60000000 + endPt.x;//pos // 
		pBuffer[k++].cmd = 0x64000000 + endPt.y;//pos // 

		if (stepDelay > 65530)
		{
			stepDelay = stepDelay / 100;

			pBuffer[k++].cmd = 0x12010000 + stepDelay;//延时，ms
		}
		else
			pBuffer[k++].cmd = 0x12000000 + stepDelay;//延时，us
	}
	else
	{
		double tempdouble;
		tempdouble = SdistInt;
		tempdouble = (tempdouble * 1000000) / SpeedMov;// 总共走的时间, 这里SdistInt会越界超过32位的数据
		stepDelay = tempdouble / (stepCnt);// 每步走的时间

		for (i = 0; i < stepCnt; i++)
		{
			if ((stepLeft == 0) && (i == (stepCnt - 1)))// 即最后一个准确的点
			{
				pBuffer[k++].cmd = 0x60000000 + endPt.x;//pos // 
				pBuffer[k++].cmd = 0x64000000 + endPt.y;//pos // 
			}
			else
			{
				pBuffer[k++].cmd = 0x60000000 + startPt.x + i * cosAngel * stepS;//pos // 
				pBuffer[k++].cmd = 0x64000000 + startPt.y + i * sinAngel * stepS;//pos // 
			}

			if (stepDelay > 65530)
			{
				stepDelay = stepDelay / 100;
				pBuffer[k++].cmd = 0x12010000 + stepDelay;//延时，ms
			}
			else
				pBuffer[k++].cmd = 0x12000000 + stepDelay;//延时，us
		}
		if (stepLeft)
		{
			pBuffer[k++].cmd = 0x60000000 + endPt.x;//pos // 
			pBuffer[k++].cmd = 0x64000000 + endPt.y;//pos // 

			if (stepDelay > 65530)
			{
				stepDelay = stepDelay / 100;
				pBuffer[k++].cmd = 0x12010000 + stepDelay;//延时，ms
			}
			else
				pBuffer[k++].cmd = 0x12000000 + stepDelay;//延时，us
		}
	}

	*pk = k;
	return 0;
}

void CMotionPanel::OnBtXStepP() 
{	
	int k=0;
	if(Cen_DllFifoBusy_A()) return;

	memset(cmdArr2,0,sizeof(FifoCmd)*200000);

	unsigned short realMovP;// 实际移动的数量，16位，对应振镜的范围0~65535
	realMovP=m_iPPM_X*m_fStepXY;
	curX=m_iPositionX-realMovP;
	cmdArr2[k++].cmd = 0x60000000+curX;//0x60指令

	Cen_pushDllFifo_A(cmdArr2,k);
}

void CMotionPanel::OnRadioX2() 
{
	// TODO: Add your control notification handler code here
  m_iGoHomeMovAxisSelect	=0;
}

void CMotionPanel::OnRadioY2() 
{
	// TODO: Add your control notification handler code here
	
	m_iGoHomeMovAxisSelect	=1;
}

void CMotionPanel::OnRadioZ2() 
{
	// TODO: Add your control notification handler code here
	
	m_iGoHomeMovAxisSelect	=2;	
}

void CMotionPanel::OnRadioA2() 
{
	// TODO: Add your control notification handler code here
	
	m_iGoHomeMovAxisSelect	=3;	
}

void CMotionPanel::OnRadioX() 
{
	// TODO: Add your control notification handler code here
   m_iContinueMovAxisSelect = 0;	
}

void CMotionPanel::OnRadioY() 
{
	// TODO: Add your control notification handler code here
	m_iContinueMovAxisSelect=1;
}

void CMotionPanel::OnRadioZ() 
{
	// TODO: Add your control notification handler code here
	m_iContinueMovAxisSelect=2;
}

void CMotionPanel::OnRadioA() 
{
	// TODO: Add your control notification handler code here
	m_iContinueMovAxisSelect=3;
} 
int iGoHomeStatus=0; // 回原点的状态机，=0 表示没有做这个动作或者已经完成

unsigned int iCurrentHomeDIN=0x55005462; // 当前限位设置的命令值， 零位到了以后，方便恢复

int iGoHomeStatusX=0,iGoHomeStatusY=0,iGoHomeStatusZ=0;  // 1表示向零点运动中，2表示到零点偏移运动中


int CMD_EXET=4;// 单位ms

void CMotionPanel::OnGohomeP()  // 正向回零
{

}
// 
// void CMotionPanel::OnGohomeM() // 负向回零
// {
// 	// TODO: Add your control notification handler code here
// 	
// }

BOOL bStartPmovX=FALSE; // 现在【开始】是多次运动了，靠这个变量标注
BOOL bStartPmovY=FALSE; // 现在【开始】是多次运动了，靠这个变量标注
BOOL bStartPmovZ=FALSE; // 现在【开始】是多次运动了，靠这个变量标注

int PmovXcnt=0;
int PmovYcnt=0;
int PmovZcnt=0;
int PmovXDelay=0;
int PmovYDelay=0;
int PmovZDelay=0;

BOOL bXmoving=FALSE;
BOOL bYmoving=FALSE;
BOOL bZmoving=FALSE;



void CMotionPanel::OnStop() 
{
	bStartPmovX=0; // 停止运行，复位
	PmovXDelay=0;
	bXmoving=0;

	bStartPmovY=0; // 停止运行，复位
	PmovYDelay=0;
	bYmoving=0;

	bStartPmovZ=0; // 停止运行，复位
	PmovZDelay=0;
	bZmoving=0;

	UpdateData();

	return ;
}
//CColorEdit *XEditArray[16];

//#define GREEN_COLOR RGB(48,127,70)
#define GREEN_COLOR RGB(70,185,102)
#define RED_COLOR RGB(197,48,48)

#define GRAIL_COLOR RGB(195,195,195)

//FifoCmd CreCmds[200000];
//void CreateCmd(float *deltaPos,int speedV)
//{// 4ms一级fifo
//	//deltaPos[]
//}


BOOL CMotionPanel::OnInitDialog() 
{
	//SkinH_Attach();//界面风格
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	iCardCnt=0;


	// 获取ini文件名
	char buf[MAX_PATH];
	GetModuleFileName(NULL, buf, MAX_PATH);
	CString FileName(buf);
	FileName = FileName.Left( FileName.ReverseFind('\\') + 1 ) + "config.ini";
	m_strINIPath= FileName;

	LoadParam(m_strINIPath);

	CString strIP,strIP2;
	CDialogTargetIP  DialogTargetIP;
	DialogTargetIP.dwAddress = dwAddress;
	DialogTargetIP.dwAddress2 = dwAddress2;

	if(DialogTargetIP.DoModal()==IDOK)
	{
		dwAddress=DialogTargetIP.dwAddress;
		dwAddress2=DialogTargetIP.dwAddress2;
		strIP.Format("%d.%d.%d.%d",(0xFF000000&dwAddress)>>24,(0xFF0000&dwAddress)>>16,(0xFF00&dwAddress)>>8,0xFF&dwAddress);
		strIP2.Format("%d.%d.%d.%d",(0xFF000000&dwAddress2)>>24,(0xFF0000&dwAddress2)>>16,(0xFF00&dwAddress2)>>8,0xFF&dwAddress2);

		OnSaveparam();
	}
	else
	{
		CDialog::OnCancel();
		return false;
	}

	blinked = 1;
	 m_strCurrIP = strIP;//"169.254.54.202";//"192.168.1.55"; // "169.254.54.202"单独给孙那边一个客户的
	 m_strCurrIP2= strIP2;//"169.254.54.202";//"192.168.1.55"; // "169.254.54.202"单独给孙那边一个客户的
	iConnCardSn=ETH0416S_EthCardInitIP(m_strCurrIP.GetBuffer());// 返回唯一编号
//	iConnCardSn=ETH0416S_EthCardInitIP("192.168.1.55");// 返回唯一编号
	if(iConnCardSn==-1)
	{

		AfxMessageBox("连接第1个控制器失败！请检查网线或供电！");

		ETH0416S_CloseAll();
		//CDialog::OnCancel();
		//return false;

		blinked = 0;
	}
	iCardCnt++;

	if(dwAddress2!=0)
	{
		iConnCardSn=ETH0416S_EthCardInitIP(m_strCurrIP2.GetBuffer());// 返回唯一编号
		if(iConnCardSn==-1)
		{

			AfxMessageBox("连接第2个控制器失败！请检查网线或供电！");

			//ETH0416S_CloseAll();
			//CDialog::OnCancel();
			//return false;
		}else 
			iCardCnt++; // 连接成功， 
	}


	ETH0416S_SetCurrentCard(iConnCardSn);


	
	CDialog::OnInitDialog();



	//XEditArray[0]= &m_ctrlEditDIN1;
	//XEditArray[1]= &m_ctrlEditDIN2;
	//XEditArray[2]= &m_ctrlEditDIN3;
	//XEditArray[3]= &m_ctrlEditDIN4;
	//XEditArray[4]= &m_ctrlEditDIN5;
	//XEditArray[5]= &m_ctrlEditDIN6;
	//XEditArray[6]= &m_ctrlEditDIN7;
	//XEditArray[7]= &m_ctrlEditDIN8;
	//XEditArray[8]= &m_ctrlEditDIN9;
	//XEditArray[9]= &m_ctrlEditDIN10;
	//XEditArray[10]= &m_ctrlEditDIN11;
	//XEditArray[11]= &m_ctrlEditDIN12;
	//XEditArray[12]= &m_ctrlEditDIN13;
	//XEditArray[13]= &m_ctrlEditDIN14;
	//XEditArray[14]= &m_ctrlEditDIN15;
	//XEditArray[15]= &m_ctrlEditDIN16;

	//for(int ii=0;ii<16;ii++)
	//{ 
	//	XEditArray[ii]->SetBkColor(GREEN_COLOR);
	//}

	m_cmdExe_flag.SetBkColor(GRAIL_COLOR);
	m_FifoExeSW.SetBkColor(GRAIL_COLOR);

	char curIP[50];
	memset(curIP,0,50);
	ETH0416S_GetCardIP(iConnCardSn,curIP);

	SetWindowText(curIP);//"Eth0416已连接"
		
	SetTimer(1,100,NULL);
	
	InitializeCriticalSection(&m_criSecEvent);



	CString tempStr;
	int tempPosX,tempPosY,tempPosZ,tempPosA;


	gifPicTcp.Create(NULL,WS_CHILD | WS_VISIBLE |SS_ENHMETAFILE,CRect(275,210,100,100),this,1234);
	gifPicFifo.Create(NULL,WS_CHILD | WS_VISIBLE |SS_ENHMETAFILE,CRect(530,220,100,100),this,1235);

	;// gif 图片对象

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CMotionPanel::OnBtXStepM() 
{
	int k=0;
	if(Cen_DllFifoBusy_A()) return;

	memset(cmdArr2,0,sizeof(FifoCmd)*200000);

	//startA.x=m_iPositionX;
	//startA.y=m_iPositionY;
	//
	
	unsigned short realMovP;// 实际移动的数量，16位，对应振镜的范围0~65535
	realMovP=m_iPPM_X*m_fStepXY;
	curX =realMovP+m_iPositionX;

	cmdArr2[k++].cmd = 0x60000000+curX;//0x60指令

	Cen_pushDllFifo_A(cmdArr2,k);
}

void CMotionPanel::OnBtYStepP() 
{
	int k=0;
	if(Cen_DllFifoBusy_A()) return;

	memset(cmdArr2,0,sizeof(FifoCmd)*200000);

	unsigned short realMovP;// 实际移动的数量，16位，对应振镜的范围0~65535
	realMovP=m_iPPM_Y*m_fStepXY;
	curY=m_iPositionY-realMovP;
	cmdArr2[k++].cmd = 0x64000000+curY;//0x60指令

	Cen_pushDllFifo_A(cmdArr2,k);
}

void CMotionPanel::OnBtYStepM() 
{
	int k=0;
	if(Cen_DllFifoBusy_A()) return;

	memset(cmdArr2,0,sizeof(FifoCmd)*200000);

	unsigned short realMovP;// 实际移动的数量，16位，对应振镜的范围0~65535
	realMovP=m_iPPM_Y*m_fStepXY;
	curY =m_iPositionY+realMovP;
	cmdArr2[k++].cmd = 0x64000000+curY;//0x60指令

	Cen_pushDllFifo_A(cmdArr2,k);
}

void CMotionPanel::OnContinueP() 
{
 }

void CMotionPanel::OnContinueM() 
{

}

void CMotionPanel::OnLButtonUp(UINT nFlags, CPoint point) 
{

	CDialog::OnLButtonUp(nFlags, point);
}

void CMotionPanel::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CDialog::OnLButtonDown(nFlags, point);
}

BOOL bContinueMoving=FALSE;


BOOL CMotionPanel::PreTranslateMessage(MSG* pMsg)  // 连续运动必须在这里处理消息
{
	int m_iStartSpeed,m_iSpeed;
	if ((pMsg->message == WM_LBUTTONDOWN)&&(m_iStepOrContinue==1))
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

			default:
				;
		}
	
	}

	if(pMsg->message   ==   WM_KEYDOWN)   
	{   
		//if(pMsg->wParam =='p')//这里90是表示想用z键代替CTRL+C键
		{
			if((GetAsyncKeyState(VK_MENU)<0 )&&(GetAsyncKeyState(VK_CONTROL)<0 )&&(GetAsyncKeyState(VK_SHIFT)<0 )&&(GetAsyncKeyState('P')<0))   //   注意VK_MENU是ALT键的虚拟码   
			{
				//   该键是按下状态 
			//	AfxMessageBox("该键是按下状态");
				CDialogParameters DialogParameters;

				DialogParameters.m_fAccTime    =m_fAccTime    ;
				DialogParameters.m_fAccTimeY   =m_fAccTimeY   ;
				DialogParameters.m_fAccTimeZ   =m_fAccTimeZ   ;
				DialogParameters.m_iPPM_X      =m_iPPM_X      ;
				DialogParameters.m_iPPM_Y      =m_iPPM_Y      ;
				DialogParameters.m_iPPM_Z      =m_iPPM_Z      ;
				DialogParameters.m_iCPMM_X      =m_iCPMM_X      ;
				DialogParameters.m_iCPMM_Y      =m_iCPMM_Y      ;
				DialogParameters.m_iCPMM_Z      =m_iCPMM_Z      ;
				DialogParameters.m_fStartSpeedX=m_fStartSpeedX;
				DialogParameters.m_fSpeedX     =m_fSpeedX     ;
				DialogParameters.m_fStartSpeedY=m_fStartSpeedY;
				DialogParameters.m_fSpeedY     =m_fSpeedY     ;
				DialogParameters.m_fStartSpeedZ=m_fStartSpeedZ;
				DialogParameters.m_fSpeedZ     =m_fSpeedZ     ;
				DialogParameters.m_fHomeSpeedX =m_fHomeSpeedX ;
				DialogParameters.m_fHomeSpeedY =m_fHomeSpeedY ;
				DialogParameters.m_fHomeSpeedZ =m_fHomeSpeedZ ;



				DialogParameters.m_bXCloseloop =m_bXCloseloop ;
				DialogParameters.m_bYCloseloop =m_bYCloseloop ;
				DialogParameters.m_bZCloseloop =m_bZCloseloop ;

				DialogParameters.m_bXENCODE_DEV =m_bXENCODE_DEV ;
				DialogParameters.m_bYENCODE_DEV =m_bYENCODE_DEV ;
				DialogParameters.m_bZENCODE_DEV =m_bZENCODE_DEV ;

				DialogParameters.m_bXGoHomeBackEZ =m_bXGoHomeBackEZ ;


				DialogParameters.m_bXGoHomePositive =m_bXGoHomePositive ;
				DialogParameters.m_bYGoHomePositive =m_bYGoHomePositive ;
				DialogParameters.m_bZGoHomePositive =m_bZGoHomePositive ;
				DialogParameters.m_bAGoHomePositive =m_bAGoHomePositive ;
				DialogParameters.m_bDisplayCnt =m_bDisplayCnt ;

				DialogParameters.m_iCaliTimeMS =m_iCaliTimeMS ;
				DialogParameters.m_iAfterHomeOffset =m_iAfterHomeOffset ;

				DialogParameters.m_fSoftLimitPosValue = m_fSoftLimitPosValue ;
				DialogParameters.m_fSoftLimitNegaValue =m_fSoftLimitNegaValue ;
				

				if(DialogParameters.DoModal()==IDOK)
				{	
					m_fAccTime    =DialogParameters.m_fAccTime    ;
					m_fAccTimeY   =DialogParameters.m_fAccTimeY   ;
					m_fAccTimeZ   =DialogParameters.m_fAccTimeZ   ;
					m_iPPM_X      =DialogParameters.m_iPPM_X      ;
					m_iPPM_Y      =DialogParameters.m_iPPM_Y      ;
					m_iPPM_Z      =DialogParameters.m_iPPM_Z      ;
					m_iCPMM_X      =DialogParameters.m_iCPMM_X      ;
					m_iCPMM_Y      =DialogParameters.m_iCPMM_Y      ;
					m_iCPMM_Z      =DialogParameters.m_iCPMM_Z      ;
					m_fStartSpeedX=DialogParameters.m_fStartSpeedX;
					m_fSpeedX     =DialogParameters.m_fSpeedX     ;
					m_fStartSpeedY=DialogParameters.m_fStartSpeedY;
					m_fSpeedY     =DialogParameters.m_fSpeedY     ;
					m_fStartSpeedZ=DialogParameters.m_fStartSpeedZ;
					m_fSpeedZ     =DialogParameters.m_fSpeedZ     ;
					m_fHomeSpeedX =DialogParameters.m_fHomeSpeedX ;
					m_fHomeSpeedY =DialogParameters.m_fHomeSpeedY ;
					m_fHomeSpeedZ =DialogParameters.m_fHomeSpeedZ ;


					m_bXCloseloop =DialogParameters.m_bXCloseloop ;
					m_bYCloseloop =DialogParameters.m_bYCloseloop ;
					m_bZCloseloop =DialogParameters.m_bZCloseloop ;
					m_bXENCODE_DEV =DialogParameters.m_bXENCODE_DEV;
					m_bYENCODE_DEV =DialogParameters.m_bYENCODE_DEV;
					m_bZENCODE_DEV =DialogParameters.m_bZENCODE_DEV;

					m_bXGoHomeBackEZ =DialogParameters.m_bXGoHomeBackEZ ;
					m_bXGoHomePositive =DialogParameters.m_bXGoHomePositive ;
					m_bYGoHomePositive =DialogParameters.m_bYGoHomePositive ;
					m_bZGoHomePositive =DialogParameters.m_bZGoHomePositive ;
					m_bAGoHomePositive =DialogParameters.m_bAGoHomePositive ;
					m_bDisplayCnt =DialogParameters.m_bDisplayCnt ;

					m_iCaliTimeMS =DialogParameters.m_iCaliTimeMS ;
					m_iAfterHomeOffset =DialogParameters.m_iAfterHomeOffset ;

					m_fSoftLimitPosValue = DialogParameters.m_fSoftLimitPosValue ;
					m_fSoftLimitNegaValue = DialogParameters.m_fSoftLimitNegaValue ;

					// 第二个参数，0表示 急停
					//ETH0416S_SetSoftLimit(0,0,m_fSoftLimitPosValue*m_iPPM_X,m_fSoftLimitNegaValue*m_iPPM_X);
					//ETH0416S_SetSoftLimit(1,0,m_fSoftLimitPosValue*m_iPPM_Y,m_fSoftLimitNegaValue*m_iPPM_Y);

					// 20170806，如果脉冲当量是500，就不对了，不能设置 1um对应的脉冲数，还是要用1mm对应的脉冲数
					// 20170806，所以第3个参数，不要除以1000，下位机都要改
					//ETH0416S_SetCloseLoop(0,m_bXCloseloop+(m_bXENCODE_DEV<<4),m_iPPM_X,m_iCPMM_X/1000); // pPum=4, cPum=1
					//ETH0416S_SetCloseLoop(1,m_bYCloseloop+(m_bYENCODE_DEV<<4),m_iPPM_Y,m_iCPMM_Y/1000);
					//ETH0416S_SetCloseLoop(2,m_bZCloseloop+(m_bZENCODE_DEV<<4),m_iPPM_Z,m_iCPMM_Z/1000);
					//ETH0416S_SetCloseLoopTime(m_iCaliTimeMS);
					OnSaveparam();
					UpdateData(FALSE);
					
				}
				return TRUE;
			}
			if(((GetAsyncKeyState(VK_MENU)<0 )&&(GetAsyncKeyState(VK_CONTROL)<0 )&&(GetAsyncKeyState(VK_SHIFT)<0 )&&(GetAsyncKeyState('I')<0)))//   注意VK_MENU是ALT键的虚拟码   
			{
				CDlgIPSetting DlgIPSetting;
	/*		DWORD dwIP; 
			void SetAddress(BYTE& nField0, BYTE& 
				nField1, BYTE nField2, BYTE nField3);
			void SetAddress(DWORD 
				dwAddress);*/

			//CIPAddressCtrl m_ipAddress; // IP设置对话框对应的变量 ip地址
			//CMFCMaskedEdit m_ctrlMacAddr; // IP设置对话框对应的变量控件，mac地址
			//CString m_strMacAddr;// // IP设置对话框对应的变量，mac地址

			//m_ipAddress.GetAddress(dwIP);

				DlgIPSetting.ipByte[0]=192;
				DlgIPSetting.ipByte[1]=168;
				DlgIPSetting.ipByte[2]=1;
				DlgIPSetting.ipByte[3]=56;
				DlgIPSetting.m_strMacAddr2= _T("00-11-22-44-12-87");//将要显示的
				
				if(DlgIPSetting.DoModal()==IDOK)
				{
					int macByte[6];
					char macTran[6];
					//AfxMessageBox(DlgIPSetting.m_strMacAddr2);
					sscanf(DlgIPSetting.m_strMacAddr2,"%d-%d-%d-%d-%d-%d",&(macByte[0]),&(macByte[1]),&(macByte[2]),&(macByte[3]),&(macByte[4]),&(macByte[5]));
					for(int i=0;i<6;i++)
						macTran[i]=macByte[i];
					ETH0416S_SetIP((char *)(DlgIPSetting.ipByte),(char *)macTran);


					
					AfxMessageBox("设置完成！");//tempStringUI
				}
				return TRUE; // 这个return很重要，要然会异常
			}
			
		}
	} 

	
	return CDialog::PreTranslateMessage(pMsg);
}

void CMotionPanel::OnResetX() 
{
//	EnterCriticalSection(&(m_criSecEvent));
	Cen_resetCount_B(0,0); // 计数
	Cen_resetCount_B(0,1); // 编码器
	//m_iPositionX=0;
	////UpdateData(FALSE);
	//CString tempStr;

	m_iTarPositionX=0;
	CString tempStr;
	{tempStr.Format("%.4f",(double)0/(double)m_iPPM_X);GetDlgItem(IDC_TAR_POSITION_X)->SetWindowText(tempStr);}

	//{tempStr.Format("%.2f",(double)m_iPositionX/(double)m_iPPM_X);GetDlgItem(IDC_POSITION_X)->SetWindowText(tempStr);}
	//LeaveCriticalSection(&(m_criSecEvent));		
}

void CMotionPanel::OnResetY() 
{
//	EnterCriticalSection(&(m_criSecEvent));
	Cen_resetCount_B(1,0);
	Cen_resetCount_B(1,1);

	m_iTarPositionY=0;
	CString tempStr;
	{tempStr.Format("%.4f",(double)0/(double)m_iPPM_Y);GetDlgItem(IDC_TAR_POSITION_Y)->SetWindowText(tempStr);}

	//m_iPositionY=0;
	//CString tempStr;
	//{tempStr.Format("%.2f",(double)m_iPositionY/(double)m_iPPM_Y);GetDlgItem(IDC_POSITION_Y)->SetWindowText(tempStr);}
	//LeaveCriticalSection(&(m_criSecEvent));	
}

void CMotionPanel::OnResetZ() 
{
	//	EnterCriticalSection(&(m_criSecEvent));
	Cen_resetCount_B(2,0);
	Cen_resetCount_B(2,1);
	//m_iPositionZ=0;
	//CString tempStr;


	m_iTarPositionZ=0;
	CString tempStr;
	{tempStr.Format("%.4f",(double)0/(double)m_iPPM_Z);GetDlgItem(IDC_TAR_POSITION_Z)->SetWindowText(tempStr);}


	//{tempStr.Format("%.2f",(double)m_iPositionZ/(double)m_iPPM_Z);GetDlgItem(IDC_POSITION_Z)->SetWindowText(tempStr);}
	//LeaveCriticalSection(&(m_criSecEvent));	
}

void CMotionPanel::OnResetA() 
{
	Cen_resetCount_B(3,0);
	Cen_resetCount_B(3,1);
	m_iPositionA=0;
	CString tempStr;
//	{tempStr.Format("%.2f",(double)m_iPositionA/(double)m_iPPM_A);GetDlgItem(IDC_POSITION_A)->SetWindowText(tempStr);}
}
BOOL bFirstStart=TRUE; // 解决偶尔界面没有更新显示当前位置的问题

//
//short ppmm[8]={300,300,400,300,300,300,400,300};// 脉冲当量，后8轴

short ppmm[8]={10,10,10,10,10,10,10,10};// 脉冲当量，后8轴

void CMotionPanel::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CString tempStr, tempStr2;
	int tempPosX, tempPosY, tempPosZ, tempPosA;
	unsigned int buffercmd[2];

	int m_iStartSpeed, m_iSpeed;
	int m_iStepXY;

	// 下面这段功能是 频繁测试 建立TCP连接与 关闭TCP连接
#if 0

	if (nIDEvent == 1)
	{
		if (timerCnt > 25)//2.5s进一次，切换
		{
			if (blinked)
			{
				ETH0416S_CloseAll();
				blinked = 0;
			}
			else
			{
				// 重新建立连接
				iConnCardSn = ETH0416S_EthCardInitIP(m_strCurrIP.GetBuffer());// 返回唯一编号
				//	iConnCardSn=ETH0416S_EthCardInitIP("192.168.1.55");// 返回唯一编号
				if (iConnCardSn != -1)
				{
					blinked = 1;
					ETH0416S_SetCurrentCard(iConnCardSn);
					m_iLinkCnt++;
					UpdateData(FALSE);
				}
				else
				{
					TRACE("TCP连接出错！");
				}
			}
			timerCnt = 0;
		}
		else
		{
			timerCnt++;
		}
	}

#endif

	if (nIDEvent == 1 && blinked && drawpathsw == false)
	{
		//UpdateData(TRUE);

		EnterCriticalSection(&(m_criSecEvent));



		//////////////////////////////////更新状态
		CString tempstr2;


		char FifoStatus[13];
		Cen_FifoCtrl_B(3, FifoStatus);// 3,取得状态

		char fifoStat, exeState;
		unsigned int fifoIdleCnt = 0, fifoCmdCnt = 0;// fifo 空闲空间个数，fifo内部指令个数
		fifoStat = FifoStatus[0];
		memcpy((char*)&fifoCmdCnt, (char*)(&(FifoStatus[1])), 4);
		memcpy((char*)&fifoIdleCnt, (char*)(&(FifoStatus[5])), 4);

		m_FifoExeSW.SetBkColor(fifoStat ? GREEN_COLOR : GRAIL_COLOR);// FIFO指令执行开关
		tempstr2.Format("控制器内FIFO 命令个数：%d， 剩余空间：%d", fifoCmdCnt, fifoIdleCnt);

		exeState = Cen_checkDone_C();
		m_cmdExe_flag.SetBkColor(exeState ? GRAIL_COLOR : RED_COLOR);// 运行完成的标志

		if (fifoStat)
		{
			if (!(gifPicFifo.IsPlaying()))
			{
				if (gifPicFifo.Load("2.gif"))
					gifPicFifo.Draw();
			}
		}
		else
		{
			if ((gifPicFifo.IsPlaying()))
			{
				gifPicFifo.UnLoad();
				//Invalidate();//重绘
			}
		}

		if (tempstr2 != m_str8AxisStr)
		{
			m_str8AxisStr = tempstr2;
			GetDlgItem(IDC_8AXIS_STR)->SetWindowText(m_str8AxisStr);
		}

		int tcp_transFlag = Cen_DllFifoBusy_A();
		//m_TcpDataTrans.SetBkColor(tcp_transFlag?GREEN_COLOR:GRAIL_COLOR);// TCP 是否在传输数据

		if (tcp_transFlag)
		{
			if (!(gifPicTcp.IsPlaying()))
			{
				if (gifPicTcp.Load("2.gif"))
					gifPicTcp.Draw();
			}
		}
		else
		{
			if ((gifPicTcp.IsPlaying()))
			{
				gifPicTcp.UnLoad();
				//Invalidate();//重绘
			}
		}


		Cen_readCount_C(0, m_bDisplayCnt, &tempPosX);// 振镜当前位置， 第2个参数改成0就是计数值
		Cen_readCount_C(1, m_bDisplayCnt, &tempPosY);


		if ((tempPosX != m_iPositionX) || bFirstStart)  // m_iStepXY = m_fStepXY * m_iPPM_X;
		{
			tempStr.Format("%.4f", (double)tempPosX / (double)(m_bDisplayCnt ? m_iCPMM_X : m_iPPM_X)); GetDlgItem(IDC_POSITION_X)->SetWindowText(tempStr); m_iPositionX = tempPosX;
		}

		if ((tempPosY != m_iPositionY) || bFirstStart)
		{
			tempStr.Format("%.4f", (double)tempPosY / (double)(m_bDisplayCnt ? m_iCPMM_Y : m_iPPM_Y)); GetDlgItem(IDC_POSITION_Y)->SetWindowText(tempStr); m_iPositionY = tempPosY;
		}

		//if(bFirstStart) bFirstStart=FALSE;


		LeaveCriticalSection(&(m_criSecEvent));

		int xCheckDone, yCheckDone, zCheckDone, aCheckDone;

		//if(xCheckDone|| yCheckDone || zCheckDone ||  aCheckDone )
		//{
		//	tempStr="轴运动中.....";
		//}
		//else if((!bStartPmovX)&&(!bStartPmovY)&&(!bStartPmovZ))
		//{
		//	tempStr="轴停止!";
		//	if(bContinueMoving) bContinueMoving=FALSE;

		//	GetDlgItem( IDC_START_DIST )->EnableWindow(TRUE);
		//}
		//else
		//	tempStr="轴停止!";

	//if(fifoStat )
	//{
	//	tempStr="轴运动中.....";
	//}else tempStr="轴停止!";








//}
		if (nIDEvent == 1 && blinked && drawpathsw == true) {
			EnterCriticalSection(&(m_criSecEvent));


			// 这里有个坐标转换： 【opencv窗口 坐标】 转换 到 【振镜坐标】
			//  opencv窗口，左上角是（0,0）,600x600,中心点是（300，300）
			//  振镜：                   65535x65535，中心是（32768，32768）
			//  我们这里示例做个简单的60倍放大软件坐标

			memset(cmdArr2, 0, sizeof(FifoCmd) * 200000);

			POINT A;
			int k = 0;
			A.x = m_iPositionX;// 振镜当前坐标
			A.y = m_iPositionY;

			//每70次移动,push到下位机
			for (auto p = pxy.begin(); p != pxy.end(); p++) {


				auto x = p->x * 60;
				auto y = p->y * 60; // 转换后的 振镜目标坐标

				ScanMoveTo(cmdArr2, &k, A, POINT{ x,y }, m_iScanSpeedpps); // 关激光状态从当前点到 鼠标对于点

				if (69 == k) {
					Cen_pushDllFifo_A(cmdArr2, k);
					memset(cmdArr2, 0, sizeof(FifoCmd) * 200000);
					k = 0;
				}
				else {
					k++;
				}
			}
			for (auto p = pxy.end(); p != pxy.begin(); p--) {


				auto x = p->x * 60;
				auto y = p->y * 60; // 转换后的 振镜目标坐标

				ScanMoveTo(cmdArr2, &k, A, POINT{ x,y }, m_iScanSpeedpps); // 关激光状态从当前点到 鼠标对于点

				if (69 == k) {
					Cen_pushDllFifo_A(cmdArr2, k);
					memset(cmdArr2, 0, sizeof(FifoCmd) * 200000);
					k = 0;
				}
				else {
					k++;
				}
			}
			LeaveCriticalSection(&(m_criSecEvent));
		}
		if (nIDEvent == 2)
		{

		}
		CDialog::OnTimer(nIDEvent);
	}
}

void CMotionPanel::WriteParam( CString strFile )
{
}
void CMotionPanel::LoadParam( CString strFile )
{
	CString str;
	char btBuf[ 512 ];
	int iRet;
	

	dwAddress = GetPrivateProfileInt( _T( "Eth6608" ), _T( "dwAddress" ), 0, m_strINIPath );// IP 地址
	dwAddress2 = GetPrivateProfileInt( _T( "Eth6608" ), _T( "dwAddress2" ), 0, m_strINIPath );// IP 地址

//	m_iStepOrContinue = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_iStepOrContinue" ), 0, m_strINIPath );

	
	m_bDistX = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_bDistX" ), 0, m_strINIPath );
	m_bDistY = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_bDistY" ), 0, m_strINIPath );
	m_bDistZ = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_bDistZ" ), 0, m_strINIPath );


	ZeroMemory( btBuf, 512 );
	iRet = GetPrivateProfileString( _T( "Eth6608" ), _T( "m_fStepXY" ), _T( "1" ), btBuf, 256, m_strINIPath );	
	m_fStepXY = atof( btBuf );

	ZeroMemory( btBuf, 512 );
	iRet = GetPrivateProfileString( _T( "Eth6608" ), _T( "m_fDistX" ), _T( "1" ), btBuf, 256, m_strINIPath );	
	m_fDistX = atof( btBuf );
	ZeroMemory( btBuf, 512 );
	iRet = GetPrivateProfileString( _T( "Eth6608" ), _T( "m_fDistY" ), _T( "1" ), btBuf, 256, m_strINIPath );	
	m_fDistY = atof( btBuf );
	ZeroMemory( btBuf, 512 );
	iRet = GetPrivateProfileString( _T( "Eth6608" ), _T( "m_fDistZ" ), _T( "1" ), btBuf, 256, m_strINIPath );	
	m_fDistZ = atof( btBuf );

	ZeroMemory( btBuf, 512 );
	iRet = GetPrivateProfileString( _T( "Eth6608" ), _T( "m_fGoHomeOffset" ), _T( "-1" ), btBuf, 256, m_strINIPath );	
	m_fGoHomeOffset = atof( btBuf );
	
	ZeroMemory( btBuf, 512 );
	iRet = GetPrivateProfileString( _T( "Eth6608" ), _T( "m_fSoftLimitPosValue" ), _T( "2000" ), btBuf, 256, m_strINIPath );	
	m_fSoftLimitPosValue = atof( btBuf );
	ZeroMemory( btBuf, 512 );
	iRet = GetPrivateProfileString( _T( "Eth6608" ), _T( "m_fSoftLimitNegaValue" ), _T( "-2000" ), btBuf, 256, m_strINIPath );	
	m_fSoftLimitNegaValue = atof( btBuf );

	m_bHomeX = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_bHomeX" ), 0, m_strINIPath );
	m_bHomeY = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_bHomeY" ), 0, m_strINIPath );
	m_bHomeZ = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_bHomeZ" ), 0, m_strINIPath );


	m_bXGoHomeBackEZ = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_bXGoHomeBackEZ" ), 0, m_strINIPath );
	m_bXGoHomePositive = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_bXGoHomePositive" ), 0, m_strINIPath );
	m_bYGoHomePositive = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_bYGoHomePositive" ), 0, m_strINIPath );
	m_bZGoHomePositive = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_bZGoHomePositive" ), 0, m_strINIPath );


	m_bXCloseloop = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_bXCloseloop" ), 0, m_strINIPath );
	m_bYCloseloop = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_bYCloseloop" ), 0, m_strINIPath );
	m_bZCloseloop = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_bZCloseloop" ), 0, m_strINIPath );
	
	m_bXENCODE_DEV = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_bXENCODE_DEV" ), 0, m_strINIPath );
	m_bYENCODE_DEV = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_bYENCODE_DEV" ), 0, m_strINIPath );
	m_bZENCODE_DEV = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_bZENCODE_DEV" ), 0, m_strINIPath );




	ZeroMemory( btBuf, 512 );
	iRet = GetPrivateProfileString( _T( "Eth6608" ), _T( "m_fStartSpeedX" ), _T( "0.1" ), btBuf, 256, m_strINIPath );	
	m_fStartSpeedX = atof( btBuf );
	ZeroMemory( btBuf, 512 );
	iRet = GetPrivateProfileString( _T( "Eth6608" ), _T( "m_fStartSpeedY" ), _T( "0.1" ), btBuf, 256, m_strINIPath );	
	m_fStartSpeedY = atof( btBuf );
	ZeroMemory( btBuf, 512 );
	iRet = GetPrivateProfileString( _T( "Eth6608" ), _T( "m_fStartSpeedZ" ), _T( "0.1" ), btBuf, 256, m_strINIPath );	
	m_fStartSpeedZ = atof( btBuf );

	ZeroMemory( btBuf, 512 );
	iRet = GetPrivateProfileString( _T( "Eth6608" ), _T( "m_fSpeedX" ), _T( "2" ), btBuf, 256, m_strINIPath );	
	m_fSpeedX = atof( btBuf );
	ZeroMemory( btBuf, 512 );
	iRet = GetPrivateProfileString( _T( "Eth6608" ), _T( "m_fSpeedY" ), _T( "2" ), btBuf, 256, m_strINIPath );	
	m_fSpeedY = atof( btBuf );
	ZeroMemory( btBuf, 512 );
	iRet = GetPrivateProfileString( _T( "Eth6608" ), _T( "m_fSpeedZ" ), _T( "2" ), btBuf, 256, m_strINIPath );	
	m_fSpeedZ = atof( btBuf );

	
	ZeroMemory( btBuf, 512 );
	iRet = GetPrivateProfileString( _T( "Eth6608" ), _T( "m_fHomeSpeedX" ), _T( "1" ), btBuf, 256, m_strINIPath );	
	m_fHomeSpeedX = atof( btBuf );
	ZeroMemory( btBuf, 512 );
	iRet = GetPrivateProfileString( _T( "Eth6608" ), _T( "m_fHomeSpeedY" ), _T( "1" ), btBuf, 256, m_strINIPath );	
	m_fHomeSpeedY = atof( btBuf );
	ZeroMemory( btBuf, 512 );
	iRet = GetPrivateProfileString( _T( "Eth6608" ), _T( "m_fHomeSpeedZ" ), _T( "1" ), btBuf, 256, m_strINIPath );	
	m_fHomeSpeedZ = atof( btBuf );
	
	
	ZeroMemory( btBuf, 512 );
	iRet = GetPrivateProfileString( _T( "Eth6608" ), _T( "m_fAccTime" ), _T( "0.3" ), btBuf, 256, m_strINIPath );	
	m_fAccTime = atof( btBuf );
	ZeroMemory( btBuf, 512 );
	iRet = GetPrivateProfileString( _T( "Eth6608" ), _T( "m_fAccTimeY" ), _T( "0.3" ), btBuf, 256, m_strINIPath );	
	m_fAccTimeY = atof( btBuf );
	ZeroMemory( btBuf, 512 );
	iRet = GetPrivateProfileString( _T( "Eth6608" ), _T( "m_fAccTimeZ" ), _T( "0.3" ), btBuf, 256, m_strINIPath );	
	m_fAccTimeZ = atof( btBuf );


	m_iPPM_X = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_iPPM_X" ), 1000, m_strINIPath );
	m_iPPM_Y = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_iPPM_Y" ), 1000, m_strINIPath );
	m_iPPM_Z = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_iPPM_Z" ), 1000, m_strINIPath );


	m_iCPMM_X = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_iCPMM_X" ), 1000, m_strINIPath );
	m_iCPMM_Y = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_iCPMM_Y" ), 1000, m_strINIPath );
	m_iCPMM_Z = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_iCPMM_Z" ), 1000, m_strINIPath );

	m_bDisplayCnt = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_bDisplayCnt" ), 0, m_strINIPath );
	m_iCaliTimeMS = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_iCaliTimeMS" ), 5000, m_strINIPath );
	m_iAfterHomeOffset = GetPrivateProfileInt( _T( "Eth6608" ), _T( "m_iAfterHomeOffset" ), 0, m_strINIPath );
}
void CMotionPanel::OnBtZStepP() 
{
	// TODO: Add your control notification handler code here
//	UpdateData();
//	ETH0416S_set_profile(2,m_iStartSpeed,m_iSpeed,m_fAccTime);
//	ETH0416S_pmove(2, m_iStepZA);

}

void CMotionPanel::OnBtZStepM() 
{
//	// TODO: Add your control notification handler code here
//	UpdateData();
//	ETH0416S_set_profile(2,m_iStartSpeed,m_iSpeed,m_fAccTime);
//	ETH0416S_pmove(2, -1*m_iStepZA);	

}

void CMotionPanel::OnBtAStepM() 
{
	// TODO: Add your control notification handler code here
//	UpdateData();
//	ETH0416S_set_profile(3,m_iStartSpeed,m_iSpeed,m_fAccTime);
//	ETH0416S_pmove(3, m_iStepZA);
}

void CMotionPanel::OnBtAStepP() 
{
	// TODO: Add your control notification handler code here
//	UpdateData();
//	ETH0416S_set_profile(3,m_iStartSpeed,m_iSpeed,m_fAccTime);
//	ETH0416S_pmove(3, -1*m_iStepZA);
}

void CMotionPanel::OnSaveparam() 
{
	
	//if(!UpdateData()) return;
	CString strValue;
// 	strValue.Format( _T( "%d" ), m_iStepOrContinue );
// 	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_iStepOrContinue" ), strValue, m_strINIPath );
	strValue.Format( _T( "%d" ), dwAddress );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "dwAddress" ), strValue, m_strINIPath );

	strValue.Format( _T( "%d" ), dwAddress2 );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "dwAddress2" ), strValue, m_strINIPath );

	strValue.Format( _T( "%d" ), m_bDistX );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_bDistX" ), strValue, m_strINIPath );
	strValue.Format( _T( "%d" ), m_bDistY );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_bDistY" ), strValue, m_strINIPath );
	strValue.Format( _T( "%d" ), m_bDistZ );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_bDistZ" ), strValue, m_strINIPath );



	strValue.Format( _T( "%f" ), m_fStepXY );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_fStepXY" ), strValue, m_strINIPath );

	strValue.Format( _T( "%f" ), m_fDistX );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_fDistX" ), strValue, m_strINIPath );
	strValue.Format( _T( "%f" ), m_fDistY );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_fDistY" ), strValue, m_strINIPath );
	strValue.Format( _T( "%f" ), m_fDistZ );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_fDistZ" ), strValue, m_strINIPath );
	
	strValue.Format( _T( "%f" ), m_fGoHomeOffset );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_fGoHomeOffset" ), strValue, m_strINIPath );
	
	strValue.Format( _T( "%d" ), m_bHomeX );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_bHomeX" ), strValue, m_strINIPath );
	strValue.Format( _T( "%d" ), m_bHomeY );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_bHomeY" ), strValue, m_strINIPath );
	strValue.Format( _T( "%d" ), m_bHomeZ );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_bHomeZ" ), strValue, m_strINIPath );

	strValue.Format( _T( "%d" ), m_bXGoHomeBackEZ );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_bXGoHomeBackEZ" ), strValue, m_strINIPath );



	strValue.Format( _T( "%d" ), m_bXGoHomePositive );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_bXGoHomePositive" ), strValue, m_strINIPath );
	strValue.Format( _T( "%d" ), m_bYGoHomePositive );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_bYGoHomePositive" ), strValue, m_strINIPath );
	strValue.Format( _T( "%d" ), m_bZGoHomePositive );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_bZGoHomePositive" ), strValue, m_strINIPath );

	strValue.Format( _T( "%d" ), m_bXCloseloop );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_bXCloseloop" ), strValue, m_strINIPath );
	strValue.Format( _T( "%d" ), m_bYCloseloop );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_bYCloseloop" ), strValue, m_strINIPath );
	strValue.Format( _T( "%d" ), m_bZCloseloop );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_bZCloseloop" ), strValue, m_strINIPath );

	strValue.Format( _T( "%d" ), m_bXENCODE_DEV );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_bXENCODE_DEV" ), strValue, m_strINIPath );
	strValue.Format( _T( "%d" ), m_bYENCODE_DEV );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_bYENCODE_DEV" ), strValue, m_strINIPath );
	strValue.Format( _T( "%d" ), m_bZENCODE_DEV );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_bZENCODE_DEV" ), strValue, m_strINIPath );

	
	strValue.Format( _T( "%f" ), m_fStartSpeedX );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_fStartSpeedX" ), strValue, m_strINIPath );
	strValue.Format( _T( "%f" ), m_fStartSpeedY );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_fStartSpeedY" ), strValue, m_strINIPath );
	strValue.Format( _T( "%f" ), m_fStartSpeedZ );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_fStartSpeedZ" ), strValue, m_strINIPath );
	
	strValue.Format( _T( "%f" ), m_fSpeedX );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_fSpeedX" ), strValue, m_strINIPath );
	strValue.Format( _T( "%f" ), m_fSpeedY );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_fSpeedY" ), strValue, m_strINIPath );
	strValue.Format( _T( "%f" ), m_fSpeedZ );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_fSpeedZ" ), strValue, m_strINIPath );
	
	strValue.Format( _T( "%f" ), m_fHomeSpeedX );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_fHomeSpeedX" ), strValue, m_strINIPath );
	strValue.Format( _T( "%f" ), m_fHomeSpeedY );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_fHomeSpeedY" ), strValue, m_strINIPath );
	strValue.Format( _T( "%f" ), m_fHomeSpeedZ );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_fHomeSpeedZ" ), strValue, m_strINIPath );

	strValue.Format( _T( "%f" ), m_fAccTime );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_fAccTime" ), strValue, m_strINIPath );
	strValue.Format( _T( "%f" ), m_fAccTimeY );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_fAccTimeY" ), strValue, m_strINIPath );
	strValue.Format( _T( "%f" ), m_fAccTimeZ );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_fAccTimeZ" ), strValue, m_strINIPath );


	strValue.Format( _T( "%f" ), m_fSoftLimitPosValue );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_fSoftLimitPosValue" ), strValue, m_strINIPath );
	strValue.Format( _T( "%f" ), m_fSoftLimitNegaValue );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_fSoftLimitNegaValue" ), strValue, m_strINIPath );

	strValue.Format( _T( "%d" ), m_iPPM_X );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_iPPM_X" ), strValue, m_strINIPath );
	strValue.Format( _T( "%d" ), m_iPPM_Y );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_iPPM_Y" ), strValue, m_strINIPath );
	strValue.Format( _T( "%d" ), m_iPPM_Z );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_iPPM_Z" ), strValue, m_strINIPath );

	strValue.Format( _T( "%d" ), m_iCPMM_X );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_iCPMM_X" ), strValue, m_strINIPath );
	strValue.Format( _T( "%d" ), m_iCPMM_Y );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_iCPMM_Y" ), strValue, m_strINIPath );
	strValue.Format( _T( "%d" ), m_iCPMM_Z );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_iCPMM_Z" ), strValue, m_strINIPath );

	strValue.Format( _T( "%d" ), m_bDisplayCnt?1:0 );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_bDisplayCnt" ), strValue, m_strINIPath );

	strValue.Format( _T( "%d" ), m_iCaliTimeMS );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_iCaliTimeMS" ), strValue, m_strINIPath );
	strValue.Format( _T( "%d" ), m_iAfterHomeOffset );
	WritePrivateProfileString( _T( "Eth6608" ), _T( "m_iAfterHomeOffset" ), strValue, m_strINIPath );
}

void CMotionPanel::OnRadioStep() 
{
	// TODO: Add your control notification handler code here
	m_iStepOrContinue=0;
}

void CMotionPanel::OnRadioContinue() 
{
	// TODO: Add your control notification handler code here
	m_iStepOrContinue=1;
}

void CMotionPanel::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default


	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMotionPanel::Onquit() 
{
	// TODO: Add your control notification handler code here
	OnStop();

	ETH0416S_CloseAll();

	if(!UpdateData()) return ;
	OnSaveparam();
	CDialog::OnCancel();	
}



void CMotionPanel::OnStartDist() 
{
	
	if(!UpdateData()) return ;
	int m_iStartSpeed,m_iSpeed;
	int m_iStepXY;
	int deltaSx;
	int AccStepNum,AccVdeta;
	CString tempStr;
	int i;

	PmovXcnt = iXCnt;
	PmovYcnt = iYCnt;
	PmovZcnt = iZCnt;

	PmovXDelay = iXDelay*10;// 100ms 的单位
	PmovYDelay = iYDelay*10;
	PmovZDelay = iZDelay*10;


	if(Cen_DllFifoBusy_A()) return;

	int pos[4];
	pos[0]=m_bDistX?m_fDistX * m_iPPM_X:0;
	pos[1]=m_bDistY?m_fDistY * m_iPPM_Y:0;
	pos[2]=m_bDistZ?m_fDistZ * m_iPPM_Z:0;
	pos[3]=0;
//	Cen_line4Fifo_A(pos,m_fStartSpeedX* m_iPPM_X,m_fSpeedX * m_iPPM_X,m_fAccTime*1000,CMD_EXET);
	
	OnSaveparam();
}

	
void CMotionPanel::OnBnClickedBtTestpoco()
{
	if(Cen_writeOutbit_B(3,0)==-1) AfxMessageBox("连接断开!");

// 下面这个代码是测试可以使用的！ 不需要使用reactor模型，所以不使用poco
	//SocketReactor reactor;
	//reactor.setTimeout(Poco::Timespan(10, 0));
	//SocketAddress sa("192.168.1.55", 3298);// 服务器的IP地址和端口号

	//// 连接成功自动生成流套接字，不成功则首先进入FailConnector的onError，  
	//// 连接如果中途中断进入ClientServiceHandler的onShutdown
	///*SocketConnector<ClientServiceHandler> */FailConnector connector(sa, reactor); 
	//std::string data(ClientServiceHandler::data());
	//// 起一个客户端
	//ClientServiceHandler::setOnce(true);
	//ClientServiceHandler::resetData();
	//reactor.run();

}


void CMotionPanel::OnBnClickedBtTestio()
{
	if(Cen_writeOutbit_B(3,1)==-1) AfxMessageBox("连接断开!");
}


void CMotionPanel::OnBnClickedStartLine4()
{
	

}




void CMotionPanel::OnBnClickedStartArc()
{
	int sizeCMD,k=0;
	char FifoStatus[13];

	if(Cen_DllFifoBusy_A()) return;

	memset(cmdArr2,0,sizeof(FifoCmd)*200000);
	for(int i = 0; i < 10000; i++)//65530
	{
		cmdArr2[k++].cmd=0x60000000+i;//pos // 
		cmdArr2[k++].cmd=0x64000000+i;//pos // 
		//cmdArr2[k++].cmd=0x12010000+10;//延时，ms
		cmdArr2[k++].cmd=0x12000000+10;//延时，us
	}

	Cen_pushDllFifo_A(cmdArr2,k);
	return ;
}

char yvalue=1;
void CMotionPanel::OnBnClickedBtTestio2()
{

}


void CMotionPanel::OnBnClickedStartArc2()
{
	if(iCardCnt>1)
	{
		char curIP[50];
		if(iConnCardSn==1) iConnCardSn=0;else iConnCardSn=1;
		ETH0416S_SetCurrentCard(iConnCardSn);
		memset(curIP,0,50);
		ETH0416S_GetCardIP(iConnCardSn,curIP);
		SetWindowText(curIP);
	}
}


void CMotionPanel::OnBnClickedBtTestio3()
{
	int k=0;

	unsigned int cycle;
	int  m_iClockLow=15;
	int  m_iSyncLow=15;
	char  m_iUsing10ns=1;
	unsigned int g_PWMhighLevelns=50;// 高电平持续时间, 脉宽设置

	int pwm_HIGH=1;

	if(Cen_DllFifoBusy_A()) return;

	memset(cmdArr2,0,sizeof(FifoCmd)*200000);

#define g_power_num 85  // 85% 功率
	unsigned char Power=(g_power_num*255)/100;// g_power_num  能量百分比的值
	// 光纤激光器的初始化
	cmdArr2[k++].cmd =  0xa2000000+(m_iSyncLow<<8)+(m_iClockLow<<4)+(m_iClockLow)/*0xa2000fff*//*0xa2000200*/;//0xa2000f55//0xa2000a11--clk周期120ns(8.3M),0xa2000a00--clk周期80ns



	// (激光的能量)  //31 =1 ,32=0	
	//启动激光器,包括设置指定的功率和PWM频率，MO,PA=1，出光了
	//D0-D7设置激光器能量			D0 ~D7	 (DOUT11-DOUT18)
	// 0.3*255=76.5  (0100 1100)
	cmdArr2[k++].cmd = 0x32000000 + 7;//MO=0;
	cmdArr2[k++].cmd = 0x32000000 + 9;//PA=0
	cmdArr2[k++].cmd = 0x31000000+6;//DOUT7接的ES，必须=1，=0表示要求停止出光
	cmdArr2[k++].cmd = 0x32000000+18;//DOUT19--latch信号 = 0
	cmdArr2[k++].cmd = ((Power&0x01)?0x31000000:0x32000000)+10;//D0; 
	cmdArr2[k++].cmd = ((Power&0x02)?0x31000000:0x32000000)+11;//D1; 
	cmdArr2[k++].cmd = ((Power&0x04)?0x31000000:0x32000000)+12;//D2; 
	cmdArr2[k++].cmd = ((Power&0x08)?0x31000000:0x32000000)+13;//D3; 
	cmdArr2[k++].cmd = ((Power&0x10)?0x31000000:0x32000000)+14;//D4; 
	cmdArr2[k++].cmd = ((Power&0x20)?0x31000000:0x32000000)+15;//D5; 
	cmdArr2[k++].cmd = ((Power&0x40)?0x31000000:0x32000000)+16;//D6; 
	cmdArr2[k++].cmd = ((Power&0x80)?0x31000000:0x32000000)+17;//D7; 

	cmdArr2[k++].cmd = 0x12000002; //2us	

	cmdArr2[k++].cmd = 0x31000000+18;//DOUT19--latch信号 = 1    给1个脉冲
	cmdArr2[k++].cmd = 0x12000003; //5us	
	cmdArr2[k++].cmd = 0x32000000+18;//DOUT19--latch信号 = 0
	cmdArr2[k++].cmd = 0x12000003; //5us
	cmdArr2[k++].cmd = 0x31000000+18;//DOUT19--latch信号 = 1    给1个脉冲
	cmdArr2[k++].cmd = 0x12000003; //5us	
	cmdArr2[k++].cmd = 0x32000000+18;//DOUT19--latch信号 = 0
	cmdArr2[k++].cmd = 0x12000003; //5us
	cmdArr2[k++].cmd = 0x31000000+18;//DOUT19--latch信号 = 1    给1个脉冲
	cmdArr2[k++].cmd = 0x12000003; //5us	
	cmdArr2[k++].cmd = 0x32000000+18;//DOUT19--latch信号 = 0
	cmdArr2[k++].cmd = 0x12000003; //5us

#define g_freq_num 30
	cycle = 100000/g_freq_num; // 10ns 为单位
	//PWM开了后，延时50ms 后MO 高  延时3ms 后 PA 高 
	pwm_HIGH = (m_iUsing10ns?(g_PWMhighLevelns/10):(g_PWMhighLevelns/100));

	// 如果是YAG或者CO2激光器，就用占空比来决定激光器功率大小
	{// 全部要重新计算了，  
		// 实际测量高电平持续时间（脉宽）最少要5us，5us 代表1%， 使用的频率周期即为500us=2KHz
		cycle = 100000/2; // 50000个 10ns=500us
		pwm_HIGH = (cycle/100)*g_power_num; // 高电平持续时间需要计算出来，根据占空比
	}


	if(pwm_HIGH<1) pwm_HIGH=1;

	//到这一步，m_iUsing10ns=1， pwm_HIGH，cycle单位都是10ns，如果m_iUsing10ns>65535,就要重新换上一下
	if(pwm_HIGH>65535)
	{
		pwm_HIGH=pwm_HIGH/10;
		cycle=cycle/10;
		m_iUsing10ns=0; // 单位即为100ns单位
	}

	cmdArr2[k++].cmd = 0x41000000+pwm_HIGH;//m_iUsing10ns?pwm_HIGH:(pwm_HIGH/10); // pwm_HIGH;//

	//cmdArr2[k++].cmd = 0x41000032;  // 高电平持续时间
	cmdArr2[k++].cmd = 0x42000000; 
	cmdArr2[k++].cmd = 0x43000000; 
	cmdArr2[k++].cmd = 0x44000000+cycle;//(m_iUsing10ns?cycle:cycle/10);//50us---5000	  //周期  频率周期设置
	cmdArr2[k++].cmd = 0x45000064; 
	cmdArr2[k++].cmd = m_iUsing10ns?0x40800001:0x40000001;//0x40000001
	cmdArr2[k++].cmd = 0x31000000 + 7;//MO;
	cmdArr2[k++].cmd = 0x1201000a; //之前是5ms，现在改成10ms


		//// 开激光
		//cmdArr2[k++].cmd = 0x31000000 + 9;//PA=1
		//cmdArr2[k++].cmd = 0x31000000 + 3;// DB37.20 =1

#define m_iOpenLaserDelay 50 // us 单位

	// 开激光延时
	if(m_iOpenLaserDelay) cmdArr2[k++].cmd = 0x12000000+m_iOpenLaserDelay; //us为单位


	Cen_pushDllFifo_A(cmdArr2,k);


}

// 直线，圆弧命令结构体， 下位机只做3轴直线插补，上位机必须写3轴直线插补数据
typedef struct _LineArcCmd  // 圆弧也给3个轴坐标
{// 28字节       // !!!!!!!          轴编号  必须从小到大！！！
	short aixsID;//第一个轴编号： b[0-3] ， 比如给0 （ax），  4（bx）
				 //第二个轴编号： b[4-7] ， 比如给1 （ay），  5（by）
				 //第三个轴编号： b[8-11],  比如给2 （az），  6（bz） 
	char yuliu; // 预留
	char mod; // 只用低8位，高24位预留，
	         // mod=0 ，二轴xy直线插补，
	         // mod=1 ，三轴xyz直线插补，
	         // mod=2，3，  2=顺时针圆弧插补，3=逆时针圆弧插补
	float axisEndPos0;//[3]; // 直线，圆弧，终点坐标 xyz  ,mm 单位，绝对坐标
	float axisEndPos1;
	float axisEndPos2;
	float axisCenPos0;//[2]; // 圆弧中心坐标 xy ,mm 单位, 绝对坐标
	float axisCenPos1;
	float nominal_speed; // 标称（工作速度）速度, mm/min  (毫米/分钟)
}LineArcCmd;

#define AXIS_IDS 0x210//0x654//0x210  // // x,y,z 直线

#define SWITCH_ON 1
#define SWITCH_OFF 0
void CMotionPanel::OnBnClickedBtTestio4()
{

	char FifoStatus[13];
	Cen_FifoCtrl_B(1,FifoStatus);

	char fifoStat;
	unsigned int fifoIdleCnt=0,fifoCmdCnt=0;// fifo 空闲空间个数，fifo内部指令个数
	fifoStat=FifoStatus[0];
	memcpy((char*)&fifoCmdCnt,(char *)(&(FifoStatus[1])),4);
	memcpy((char*)&fifoIdleCnt,(char *)(&(FifoStatus[5])),4);


}


void CMotionPanel::OnBnClickedClearFifo()
{
	char FifoStatus[13];
	Cen_FifoCtrl_B(2,FifoStatus);
}


void CMotionPanel::OnBnClickedStopFifo()
{
	char FifoStatus[13];


//	ETH0416S_set_profile(0,100,10000,0.2);

	Cen_FifoCtrl_B(0,FifoStatus);
}


void CMotionPanel::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Onquit();
	CDialog::OnClose();
}


void CMotionPanel::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	Onquit();
	CDialog::OnCancel();
}


void CMotionPanel::OnBnClickedStartArc3()
{
	int sizeCMD,k=0;
	char FifoStatus[13];

	if(Cen_DllFifoBusy_A()) return;

	memset(cmdArr2,0,sizeof(FifoCmd)*200000);
//	for(int i = 0; i < 50; i++)
	{

		cmdArr2[k++].cmd = 0x48000000;//PWM关指令

	}
	Cen_pushDllFifo_A(cmdArr2,k);
	return ;
}


void CMotionPanel::OnBnClickedBtTestio5()
{// 画矩形
	int sizeCMD,k=0;
	char FifoStatus[13];

	UpdateData();

	if(Cen_DllFifoBusy_A()) return;

	memset(cmdArr2,0,sizeof(FifoCmd)*200000);

	if(m_iScanSpeedpps<100) m_iScanSpeedpps=1000;

	POINT startA,endB,endC,endD,endE;

	startA.x=m_iPositionX;
	startA.y=m_iPositionY;

	endB.x=42768;endB.y=42768;


	//1. *********关激光状态从当前点到第1个点
	cmdArr2[k++].cmd = 0x32000000 + 9;//PA=0// 关激光,之前要做初始化
	ScanMoveTo(cmdArr2,&k,startA,endB,m_iScanSpeedpps); // 关激光状态从当前点到第1个点

	//1. *********开激光状态 画第1条线
	cmdArr2[k++].cmd = 0x31000000 + 9;//PA=1// 开激光,之前要做初始化
	cmdArr2[k++].cmd = 0x12000000 + 200;// 开激光延时 us，200us开激光延时配套1000000速度是可以的
	endC.x=22768;endC.y=42768;
	ScanMoveTo(cmdArr2,&k,endB,endC,m_iScanSpeedpps);// 从第1个点画到第2个点

	//2. *********开激光状态 画第2条线
	endD.x=22768;endD.y=22768;
	ScanMoveTo(cmdArr2,&k,endC,endD,m_iScanSpeedpps);// 从第2个点画到第3个点

	//3. *********开激光状态 画第3条线
	endE.x=42768;endE.y=22768;
	ScanMoveTo(cmdArr2,&k,endD,endE,m_iScanSpeedpps);// 从第3个点画到第4个点


	//4. *********开激光状态 画第4条线
	ScanMoveTo(cmdArr2,&k,endE,endB,m_iScanSpeedpps);// 从第4个点画到第1个点

	//5.关激光
	cmdArr2[k++].cmd = 0x32000000 + 9;//PA=0
	cmdArr2[k++].cmd = 0x12000000 + 200;// 关激光延时 us，200us开激光延时配套1000000速度是可以的

	Cen_pushDllFifo_A(cmdArr2,k);
	return ;
}



void CMotionPanel::OnBnClickedBtTestio6()
{
		int sizeCMD,k=0;
	char FifoStatus[13];

	if(Cen_DllFifoBusy_A()) return;

	memset(cmdArr2,0,sizeof(FifoCmd)*200000);

	// 关激光
	cmdArr2[k++].cmd = 0x31000000 + 9;//PA=0
	cmdArr2[k++].cmd = 0x31000000 + 3;// DB37.20 =1
	

	Cen_pushDllFifo_A(cmdArr2,k);
	return ;
}


void CMotionPanel::OnBnClickedBtMouseFo()
{
	Golv_Mouse_SW = !Golv_Mouse_SW; // 开的情况下 会在定时器里面刷新 实时坐标

}


void CMotionPanel::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (Golv_Mouse_SW)
	{
		CString strMousePos;
		strMousePos.Format("%d,%d",point.x,point.y);
		GetDlgItem(IDC_MSG_MOUSE)->SetWindowText(strMousePos);


		// 这里有个坐标转换： 【软件窗口 坐标】 转换 到 【振镜坐标】
		//  软件窗口，左上角是（0,0）,800x600,中心点是（400，300）
		//  振镜：                   65535x65535，中心是（32768，32768）
		//  我们这里示例做个简单的60倍放大软件坐标

		int sizeCMD, k = 0;
		char FifoStatus[13];
		memset(cmdArr2, 0, sizeof(FifoCmd) * 200000);

		if (m_iScanSpeedpps < 100) m_iScanSpeedpps = 1000;//振镜移动速度

		POINT startA, endB;

		startA.x = m_iPositionX;// 振镜当前坐标
		startA.y = m_iPositionY;

		endB.x = point.x*60; endB.y = point.y*60; // 转换后的 振镜目标坐标


		cmdArr2[k++].cmd = 0x32000000 + 9;//PA=0// 关激光,之前要做初始化
		ScanMoveTo(cmdArr2, &k, startA, endB, m_iScanSpeedpps); // 关激光状态从当前点到 鼠标对于点

		if(blinked)
			Cen_pushDllFifo_A(cmdArr2, k);

	}
	CDialog::OnMouseMove(nFlags, point);
}


void CMotionPanel::OnBnClickedButton2()
{
	drawpathsw = true;
	drawpath(pxy);
}


void CMotionPanel::OnBnClickedButton3()
{
	drawpathsw = false;
	pxy.clear();
}
