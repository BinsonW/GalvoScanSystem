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

	m_iTarPositionX=0; // ָ��λ��
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
unsigned short curX=32768,curY=32768;// ��XY����ǰλ�����м伴32768
// �˶����ƺ������������ƶ���ָ���ĵ�
//FifoCmd *pBuffer, ������ָ��
//int *pk, ��������ǰָ�����
//POINT startPt, ��ǰ������----��ʼ��(�񾵵�λp),xyȡֵ0-65535
//POINT endPt �� ������(�񾵵�λp),xyȡֵ0-65535
//int SpeedMov ���ٶ� p/s
int ScanMoveTo(FifoCmd* pBuffer, int* pk, POINT startPt, POINT endPt, int SpeedMov)
{// ��Ϊ�������в�ͬ������MoveToҲҪ�岹
	int i, k = *pk;
	double Sdist;// �ܳ���
	double sinAngel, cosAngel; // �н�  ���ң�����
	int stepS, stepCnt, stepDelay, stepLeft;
	Sdist = (startPt.x - endPt.x) * (startPt.x - endPt.x) + (startPt.y - endPt.y) * (startPt.y - endPt.y);
	Sdist = sqrt(Sdist);

	sinAngel = (endPt.y - startPt.y) / Sdist;
	cosAngel = (endPt.x - startPt.x) / Sdist;

	int SdistInt;
	SdistInt = Sdist;
	// ÿ�β���Ԥ��50
	stepS = 50;// ÿ���ߵ��񾵵�λ
	stepCnt = SdistInt / 50;
	stepLeft = SdistInt % 50;
	if (stepCnt == 0)
	{
		stepDelay = (SdistInt * 1000000) / SpeedMov;// ��λus

		// ������ݸ���
		pBuffer[k++].cmd = 0x60000000 + endPt.x;//pos // 
		pBuffer[k++].cmd = 0x64000000 + endPt.y;//pos // 

		if (stepDelay > 65530)
		{
			stepDelay = stepDelay / 100;

			pBuffer[k++].cmd = 0x12010000 + stepDelay;//��ʱ��ms
		}
		else
			pBuffer[k++].cmd = 0x12000000 + stepDelay;//��ʱ��us
	}
	else
	{
		double tempdouble;
		tempdouble = SdistInt;
		tempdouble = (tempdouble * 1000000) / SpeedMov;// �ܹ��ߵ�ʱ��, ����SdistInt��Խ�糬��32λ������
		stepDelay = tempdouble / (stepCnt);// ÿ���ߵ�ʱ��

		for (i = 0; i < stepCnt; i++)
		{
			if ((stepLeft == 0) && (i == (stepCnt - 1)))// �����һ��׼ȷ�ĵ�
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
				pBuffer[k++].cmd = 0x12010000 + stepDelay;//��ʱ��ms
			}
			else
				pBuffer[k++].cmd = 0x12000000 + stepDelay;//��ʱ��us
		}
		if (stepLeft)
		{
			pBuffer[k++].cmd = 0x60000000 + endPt.x;//pos // 
			pBuffer[k++].cmd = 0x64000000 + endPt.y;//pos // 

			if (stepDelay > 65530)
			{
				stepDelay = stepDelay / 100;
				pBuffer[k++].cmd = 0x12010000 + stepDelay;//��ʱ��ms
			}
			else
				pBuffer[k++].cmd = 0x12000000 + stepDelay;//��ʱ��us
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

	unsigned short realMovP;// ʵ���ƶ���������16λ����Ӧ�񾵵ķ�Χ0~65535
	realMovP=m_iPPM_X*m_fStepXY;
	curX=m_iPositionX-realMovP;
	cmdArr2[k++].cmd = 0x60000000+curX;//0x60ָ��

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
int iGoHomeStatus=0; // ��ԭ���״̬����=0 ��ʾû����������������Ѿ����

unsigned int iCurrentHomeDIN=0x55005462; // ��ǰ��λ���õ�����ֵ�� ��λ�����Ժ󣬷���ָ�

int iGoHomeStatusX=0,iGoHomeStatusY=0,iGoHomeStatusZ=0;  // 1��ʾ������˶��У�2��ʾ�����ƫ���˶���


int CMD_EXET=4;// ��λms

void CMotionPanel::OnGohomeP()  // �������
{

}
// 
// void CMotionPanel::OnGohomeM() // �������
// {
// 	// TODO: Add your control notification handler code here
// 	
// }

BOOL bStartPmovX=FALSE; // ���ڡ���ʼ���Ƕ���˶��ˣ������������ע
BOOL bStartPmovY=FALSE; // ���ڡ���ʼ���Ƕ���˶��ˣ������������ע
BOOL bStartPmovZ=FALSE; // ���ڡ���ʼ���Ƕ���˶��ˣ������������ע

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
	bStartPmovX=0; // ֹͣ���У���λ
	PmovXDelay=0;
	bXmoving=0;

	bStartPmovY=0; // ֹͣ���У���λ
	PmovYDelay=0;
	bYmoving=0;

	bStartPmovZ=0; // ֹͣ���У���λ
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
//{// 4msһ��fifo
//	//deltaPos[]
//}


BOOL CMotionPanel::OnInitDialog() 
{
	//SkinH_Attach();//������
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	iCardCnt=0;


	// ��ȡini�ļ���
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
	 m_strCurrIP = strIP;//"169.254.54.202";//"192.168.1.55"; // "169.254.54.202"���������Ǳ�һ���ͻ���
	 m_strCurrIP2= strIP2;//"169.254.54.202";//"192.168.1.55"; // "169.254.54.202"���������Ǳ�һ���ͻ���
	iConnCardSn=ETH0416S_EthCardInitIP(m_strCurrIP.GetBuffer());// ����Ψһ���
//	iConnCardSn=ETH0416S_EthCardInitIP("192.168.1.55");// ����Ψһ���
	if(iConnCardSn==-1)
	{

		AfxMessageBox("���ӵ�1��������ʧ�ܣ��������߻򹩵磡");

		ETH0416S_CloseAll();
		//CDialog::OnCancel();
		//return false;

		blinked = 0;
	}
	iCardCnt++;

	if(dwAddress2!=0)
	{
		iConnCardSn=ETH0416S_EthCardInitIP(m_strCurrIP2.GetBuffer());// ����Ψһ���
		if(iConnCardSn==-1)
		{

			AfxMessageBox("���ӵ�2��������ʧ�ܣ��������߻򹩵磡");

			//ETH0416S_CloseAll();
			//CDialog::OnCancel();
			//return false;
		}else 
			iCardCnt++; // ���ӳɹ��� 
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

	SetWindowText(curIP);//"Eth0416������"
		
	SetTimer(1,100,NULL);
	
	InitializeCriticalSection(&m_criSecEvent);



	CString tempStr;
	int tempPosX,tempPosY,tempPosZ,tempPosA;


	gifPicTcp.Create(NULL,WS_CHILD | WS_VISIBLE |SS_ENHMETAFILE,CRect(275,210,100,100),this,1234);
	gifPicFifo.Create(NULL,WS_CHILD | WS_VISIBLE |SS_ENHMETAFILE,CRect(530,220,100,100),this,1235);

	;// gif ͼƬ����

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
	
	unsigned short realMovP;// ʵ���ƶ���������16λ����Ӧ�񾵵ķ�Χ0~65535
	realMovP=m_iPPM_X*m_fStepXY;
	curX =realMovP+m_iPositionX;

	cmdArr2[k++].cmd = 0x60000000+curX;//0x60ָ��

	Cen_pushDllFifo_A(cmdArr2,k);
}

void CMotionPanel::OnBtYStepP() 
{
	int k=0;
	if(Cen_DllFifoBusy_A()) return;

	memset(cmdArr2,0,sizeof(FifoCmd)*200000);

	unsigned short realMovP;// ʵ���ƶ���������16λ����Ӧ�񾵵ķ�Χ0~65535
	realMovP=m_iPPM_Y*m_fStepXY;
	curY=m_iPositionY-realMovP;
	cmdArr2[k++].cmd = 0x64000000+curY;//0x60ָ��

	Cen_pushDllFifo_A(cmdArr2,k);
}

void CMotionPanel::OnBtYStepM() 
{
	int k=0;
	if(Cen_DllFifoBusy_A()) return;

	memset(cmdArr2,0,sizeof(FifoCmd)*200000);

	unsigned short realMovP;// ʵ���ƶ���������16λ����Ӧ�񾵵ķ�Χ0~65535
	realMovP=m_iPPM_Y*m_fStepXY;
	curY =m_iPositionY+realMovP;
	cmdArr2[k++].cmd = 0x64000000+curY;//0x60ָ��

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


BOOL CMotionPanel::PreTranslateMessage(MSG* pMsg)  // �����˶����������ﴦ����Ϣ
{
	int m_iStartSpeed,m_iSpeed;
	if ((pMsg->message == WM_LBUTTONDOWN)&&(m_iStepOrContinue==1))
    {
        UINT nCtrlID = ((CWnd *)WindowFromPoint(pMsg->pt))->GetDlgCtrlID();
        switch (nCtrlID)
        {
        case IDC_BT_X_STEP_P:


			break;
        case IDC_BT_X_STEP_M:// �����˶�

			break;
        case IDC_BT_Y_STEP_P:// �����˶�

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
		//if(pMsg->wParam =='p')//����90�Ǳ�ʾ����z������CTRL+C��
		{
			if((GetAsyncKeyState(VK_MENU)<0 )&&(GetAsyncKeyState(VK_CONTROL)<0 )&&(GetAsyncKeyState(VK_SHIFT)<0 )&&(GetAsyncKeyState('P')<0))   //   ע��VK_MENU��ALT����������   
			{
				//   �ü��ǰ���״̬ 
			//	AfxMessageBox("�ü��ǰ���״̬");
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

					// �ڶ���������0��ʾ ��ͣ
					//ETH0416S_SetSoftLimit(0,0,m_fSoftLimitPosValue*m_iPPM_X,m_fSoftLimitNegaValue*m_iPPM_X);
					//ETH0416S_SetSoftLimit(1,0,m_fSoftLimitPosValue*m_iPPM_Y,m_fSoftLimitNegaValue*m_iPPM_Y);

					// 20170806��������嵱����500���Ͳ����ˣ��������� 1um��Ӧ��������������Ҫ��1mm��Ӧ��������
					// 20170806�����Ե�3����������Ҫ����1000����λ����Ҫ��
					//ETH0416S_SetCloseLoop(0,m_bXCloseloop+(m_bXENCODE_DEV<<4),m_iPPM_X,m_iCPMM_X/1000); // pPum=4, cPum=1
					//ETH0416S_SetCloseLoop(1,m_bYCloseloop+(m_bYENCODE_DEV<<4),m_iPPM_Y,m_iCPMM_Y/1000);
					//ETH0416S_SetCloseLoop(2,m_bZCloseloop+(m_bZENCODE_DEV<<4),m_iPPM_Z,m_iCPMM_Z/1000);
					//ETH0416S_SetCloseLoopTime(m_iCaliTimeMS);
					OnSaveparam();
					UpdateData(FALSE);
					
				}
				return TRUE;
			}
			if(((GetAsyncKeyState(VK_MENU)<0 )&&(GetAsyncKeyState(VK_CONTROL)<0 )&&(GetAsyncKeyState(VK_SHIFT)<0 )&&(GetAsyncKeyState('I')<0)))//   ע��VK_MENU��ALT����������   
			{
				CDlgIPSetting DlgIPSetting;
	/*		DWORD dwIP; 
			void SetAddress(BYTE& nField0, BYTE& 
				nField1, BYTE nField2, BYTE nField3);
			void SetAddress(DWORD 
				dwAddress);*/

			//CIPAddressCtrl m_ipAddress; // IP���öԻ����Ӧ�ı��� ip��ַ
			//CMFCMaskedEdit m_ctrlMacAddr; // IP���öԻ����Ӧ�ı����ؼ���mac��ַ
			//CString m_strMacAddr;// // IP���öԻ����Ӧ�ı�����mac��ַ

			//m_ipAddress.GetAddress(dwIP);

				DlgIPSetting.ipByte[0]=192;
				DlgIPSetting.ipByte[1]=168;
				DlgIPSetting.ipByte[2]=1;
				DlgIPSetting.ipByte[3]=56;
				DlgIPSetting.m_strMacAddr2= _T("00-11-22-44-12-87");//��Ҫ��ʾ��
				
				if(DlgIPSetting.DoModal()==IDOK)
				{
					int macByte[6];
					char macTran[6];
					//AfxMessageBox(DlgIPSetting.m_strMacAddr2);
					sscanf(DlgIPSetting.m_strMacAddr2,"%d-%d-%d-%d-%d-%d",&(macByte[0]),&(macByte[1]),&(macByte[2]),&(macByte[3]),&(macByte[4]),&(macByte[5]));
					for(int i=0;i<6;i++)
						macTran[i]=macByte[i];
					ETH0416S_SetIP((char *)(DlgIPSetting.ipByte),(char *)macTran);


					
					AfxMessageBox("������ɣ�");//tempStringUI
				}
				return TRUE; // ���return����Ҫ��ҪȻ���쳣
			}
			
		}
	} 

	
	return CDialog::PreTranslateMessage(pMsg);
}

void CMotionPanel::OnResetX() 
{
//	EnterCriticalSection(&(m_criSecEvent));
	Cen_resetCount_B(0,0); // ����
	Cen_resetCount_B(0,1); // ������
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
BOOL bFirstStart=TRUE; // ���ż������û�и�����ʾ��ǰλ�õ�����

//
//short ppmm[8]={300,300,400,300,300,300,400,300};// ���嵱������8��

short ppmm[8]={10,10,10,10,10,10,10,10};// ���嵱������8��

void CMotionPanel::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CString tempStr, tempStr2;
	int tempPosX, tempPosY, tempPosZ, tempPosA;
	unsigned int buffercmd[2];

	int m_iStartSpeed, m_iSpeed;
	int m_iStepXY;

	// ������ι����� Ƶ������ ����TCP������ �ر�TCP����
#if 0

	if (nIDEvent == 1)
	{
		if (timerCnt > 25)//2.5s��һ�Σ��л�
		{
			if (blinked)
			{
				ETH0416S_CloseAll();
				blinked = 0;
			}
			else
			{
				// ���½�������
				iConnCardSn = ETH0416S_EthCardInitIP(m_strCurrIP.GetBuffer());// ����Ψһ���
				//	iConnCardSn=ETH0416S_EthCardInitIP("192.168.1.55");// ����Ψһ���
				if (iConnCardSn != -1)
				{
					blinked = 1;
					ETH0416S_SetCurrentCard(iConnCardSn);
					m_iLinkCnt++;
					UpdateData(FALSE);
				}
				else
				{
					TRACE("TCP���ӳ���");
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



		//////////////////////////////////����״̬
		CString tempstr2;


		char FifoStatus[13];
		Cen_FifoCtrl_B(3, FifoStatus);// 3,ȡ��״̬

		char fifoStat, exeState;
		unsigned int fifoIdleCnt = 0, fifoCmdCnt = 0;// fifo ���пռ������fifo�ڲ�ָ�����
		fifoStat = FifoStatus[0];
		memcpy((char*)&fifoCmdCnt, (char*)(&(FifoStatus[1])), 4);
		memcpy((char*)&fifoIdleCnt, (char*)(&(FifoStatus[5])), 4);

		m_FifoExeSW.SetBkColor(fifoStat ? GREEN_COLOR : GRAIL_COLOR);// FIFOָ��ִ�п���
		tempstr2.Format("��������FIFO ���������%d�� ʣ��ռ䣺%d", fifoCmdCnt, fifoIdleCnt);

		exeState = Cen_checkDone_C();
		m_cmdExe_flag.SetBkColor(exeState ? GRAIL_COLOR : RED_COLOR);// ������ɵı�־

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
				//Invalidate();//�ػ�
			}
		}

		if (tempstr2 != m_str8AxisStr)
		{
			m_str8AxisStr = tempstr2;
			GetDlgItem(IDC_8AXIS_STR)->SetWindowText(m_str8AxisStr);
		}

		int tcp_transFlag = Cen_DllFifoBusy_A();
		//m_TcpDataTrans.SetBkColor(tcp_transFlag?GREEN_COLOR:GRAIL_COLOR);// TCP �Ƿ��ڴ�������

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
				//Invalidate();//�ػ�
			}
		}


		Cen_readCount_C(0, m_bDisplayCnt, &tempPosX);// �񾵵�ǰλ�ã� ��2�������ĳ�0���Ǽ���ֵ
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
		//	tempStr="���˶���.....";
		//}
		//else if((!bStartPmovX)&&(!bStartPmovY)&&(!bStartPmovZ))
		//{
		//	tempStr="��ֹͣ!";
		//	if(bContinueMoving) bContinueMoving=FALSE;

		//	GetDlgItem( IDC_START_DIST )->EnableWindow(TRUE);
		//}
		//else
		//	tempStr="��ֹͣ!";

	//if(fifoStat )
	//{
	//	tempStr="���˶���.....";
	//}else tempStr="��ֹͣ!";








//}
		if (nIDEvent == 1 && blinked && drawpathsw == true) {
			EnterCriticalSection(&(m_criSecEvent));


			// �����и�����ת���� ��opencv���� ���꡿ ת�� �� �������꡿
			//  opencv���ڣ����Ͻ��ǣ�0,0��,600x600,���ĵ��ǣ�300��300��
			//  �񾵣�                   65535x65535�������ǣ�32768��32768��
			//  ��������ʾ�������򵥵�60���Ŵ��������

			memset(cmdArr2, 0, sizeof(FifoCmd) * 200000);

			POINT A;
			int k = 0;
			A.x = m_iPositionX;// �񾵵�ǰ����
			A.y = m_iPositionY;

			//ÿ70���ƶ�,push����λ��
			for (auto p = pxy.begin(); p != pxy.end(); p++) {


				auto x = p->x * 60;
				auto y = p->y * 60; // ת����� ��Ŀ������

				ScanMoveTo(cmdArr2, &k, A, POINT{ x,y }, m_iScanSpeedpps); // �ؼ���״̬�ӵ�ǰ�㵽 �����ڵ�

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
				auto y = p->y * 60; // ת����� ��Ŀ������

				ScanMoveTo(cmdArr2, &k, A, POINT{ x,y }, m_iScanSpeedpps); // �ؼ���״̬�ӵ�ǰ�㵽 �����ڵ�

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
	

	dwAddress = GetPrivateProfileInt( _T( "Eth6608" ), _T( "dwAddress" ), 0, m_strINIPath );// IP ��ַ
	dwAddress2 = GetPrivateProfileInt( _T( "Eth6608" ), _T( "dwAddress2" ), 0, m_strINIPath );// IP ��ַ

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

	PmovXDelay = iXDelay*10;// 100ms �ĵ�λ
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
	if(Cen_writeOutbit_B(3,0)==-1) AfxMessageBox("���ӶϿ�!");

// ������������ǲ��Կ���ʹ�õģ� ����Ҫʹ��reactorģ�ͣ����Բ�ʹ��poco
	//SocketReactor reactor;
	//reactor.setTimeout(Poco::Timespan(10, 0));
	//SocketAddress sa("192.168.1.55", 3298);// ��������IP��ַ�Ͷ˿ں�

	//// ���ӳɹ��Զ��������׽��֣����ɹ������Ƚ���FailConnector��onError��  
	//// ���������;�жϽ���ClientServiceHandler��onShutdown
	///*SocketConnector<ClientServiceHandler> */FailConnector connector(sa, reactor); 
	//std::string data(ClientServiceHandler::data());
	//// ��һ���ͻ���
	//ClientServiceHandler::setOnce(true);
	//ClientServiceHandler::resetData();
	//reactor.run();

}


void CMotionPanel::OnBnClickedBtTestio()
{
	if(Cen_writeOutbit_B(3,1)==-1) AfxMessageBox("���ӶϿ�!");
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
		//cmdArr2[k++].cmd=0x12010000+10;//��ʱ��ms
		cmdArr2[k++].cmd=0x12000000+10;//��ʱ��us
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
	unsigned int g_PWMhighLevelns=50;// �ߵ�ƽ����ʱ��, ��������

	int pwm_HIGH=1;

	if(Cen_DllFifoBusy_A()) return;

	memset(cmdArr2,0,sizeof(FifoCmd)*200000);

#define g_power_num 85  // 85% ����
	unsigned char Power=(g_power_num*255)/100;// g_power_num  �����ٷֱȵ�ֵ
	// ���˼������ĳ�ʼ��
	cmdArr2[k++].cmd =  0xa2000000+(m_iSyncLow<<8)+(m_iClockLow<<4)+(m_iClockLow)/*0xa2000fff*//*0xa2000200*/;//0xa2000f55//0xa2000a11--clk����120ns(8.3M),0xa2000a00--clk����80ns



	// (���������)  //31 =1 ,32=0	
	//����������,��������ָ���Ĺ��ʺ�PWMƵ�ʣ�MO,PA=1��������
	//D0-D7���ü���������			D0 ~D7	 (DOUT11-DOUT18)
	// 0.3*255=76.5  (0100 1100)
	cmdArr2[k++].cmd = 0x32000000 + 7;//MO=0;
	cmdArr2[k++].cmd = 0x32000000 + 9;//PA=0
	cmdArr2[k++].cmd = 0x31000000+6;//DOUT7�ӵ�ES������=1��=0��ʾҪ��ֹͣ����
	cmdArr2[k++].cmd = 0x32000000+18;//DOUT19--latch�ź� = 0
	cmdArr2[k++].cmd = ((Power&0x01)?0x31000000:0x32000000)+10;//D0; 
	cmdArr2[k++].cmd = ((Power&0x02)?0x31000000:0x32000000)+11;//D1; 
	cmdArr2[k++].cmd = ((Power&0x04)?0x31000000:0x32000000)+12;//D2; 
	cmdArr2[k++].cmd = ((Power&0x08)?0x31000000:0x32000000)+13;//D3; 
	cmdArr2[k++].cmd = ((Power&0x10)?0x31000000:0x32000000)+14;//D4; 
	cmdArr2[k++].cmd = ((Power&0x20)?0x31000000:0x32000000)+15;//D5; 
	cmdArr2[k++].cmd = ((Power&0x40)?0x31000000:0x32000000)+16;//D6; 
	cmdArr2[k++].cmd = ((Power&0x80)?0x31000000:0x32000000)+17;//D7; 

	cmdArr2[k++].cmd = 0x12000002; //2us	

	cmdArr2[k++].cmd = 0x31000000+18;//DOUT19--latch�ź� = 1    ��1������
	cmdArr2[k++].cmd = 0x12000003; //5us	
	cmdArr2[k++].cmd = 0x32000000+18;//DOUT19--latch�ź� = 0
	cmdArr2[k++].cmd = 0x12000003; //5us
	cmdArr2[k++].cmd = 0x31000000+18;//DOUT19--latch�ź� = 1    ��1������
	cmdArr2[k++].cmd = 0x12000003; //5us	
	cmdArr2[k++].cmd = 0x32000000+18;//DOUT19--latch�ź� = 0
	cmdArr2[k++].cmd = 0x12000003; //5us
	cmdArr2[k++].cmd = 0x31000000+18;//DOUT19--latch�ź� = 1    ��1������
	cmdArr2[k++].cmd = 0x12000003; //5us	
	cmdArr2[k++].cmd = 0x32000000+18;//DOUT19--latch�ź� = 0
	cmdArr2[k++].cmd = 0x12000003; //5us

#define g_freq_num 30
	cycle = 100000/g_freq_num; // 10ns Ϊ��λ
	//PWM���˺���ʱ50ms ��MO ��  ��ʱ3ms �� PA �� 
	pwm_HIGH = (m_iUsing10ns?(g_PWMhighLevelns/10):(g_PWMhighLevelns/100));

	// �����YAG����CO2������������ռ�ձ����������������ʴ�С
	{// ȫ��Ҫ���¼����ˣ�  
		// ʵ�ʲ����ߵ�ƽ����ʱ�䣨��������Ҫ5us��5us ����1%�� ʹ�õ�Ƶ�����ڼ�Ϊ500us=2KHz
		cycle = 100000/2; // 50000�� 10ns=500us
		pwm_HIGH = (cycle/100)*g_power_num; // �ߵ�ƽ����ʱ����Ҫ�������������ռ�ձ�
	}


	if(pwm_HIGH<1) pwm_HIGH=1;

	//����һ����m_iUsing10ns=1�� pwm_HIGH��cycle��λ����10ns�����m_iUsing10ns>65535,��Ҫ���»���һ��
	if(pwm_HIGH>65535)
	{
		pwm_HIGH=pwm_HIGH/10;
		cycle=cycle/10;
		m_iUsing10ns=0; // ��λ��Ϊ100ns��λ
	}

	cmdArr2[k++].cmd = 0x41000000+pwm_HIGH;//m_iUsing10ns?pwm_HIGH:(pwm_HIGH/10); // pwm_HIGH;//

	//cmdArr2[k++].cmd = 0x41000032;  // �ߵ�ƽ����ʱ��
	cmdArr2[k++].cmd = 0x42000000; 
	cmdArr2[k++].cmd = 0x43000000; 
	cmdArr2[k++].cmd = 0x44000000+cycle;//(m_iUsing10ns?cycle:cycle/10);//50us---5000	  //����  Ƶ����������
	cmdArr2[k++].cmd = 0x45000064; 
	cmdArr2[k++].cmd = m_iUsing10ns?0x40800001:0x40000001;//0x40000001
	cmdArr2[k++].cmd = 0x31000000 + 7;//MO;
	cmdArr2[k++].cmd = 0x1201000a; //֮ǰ��5ms�����ڸĳ�10ms


		//// ������
		//cmdArr2[k++].cmd = 0x31000000 + 9;//PA=1
		//cmdArr2[k++].cmd = 0x31000000 + 3;// DB37.20 =1

#define m_iOpenLaserDelay 50 // us ��λ

	// ��������ʱ
	if(m_iOpenLaserDelay) cmdArr2[k++].cmd = 0x12000000+m_iOpenLaserDelay; //usΪ��λ


	Cen_pushDllFifo_A(cmdArr2,k);


}

// ֱ�ߣ�Բ������ṹ�壬 ��λ��ֻ��3��ֱ�߲岹����λ������д3��ֱ�߲岹����
typedef struct _LineArcCmd  // Բ��Ҳ��3��������
{// 28�ֽ�       // !!!!!!!          ����  �����С���󣡣���
	short aixsID;//��һ�����ţ� b[0-3] �� �����0 ��ax����  4��bx��
				 //�ڶ������ţ� b[4-7] �� �����1 ��ay����  5��by��
				 //���������ţ� b[8-11],  �����2 ��az����  6��bz�� 
	char yuliu; // Ԥ��
	char mod; // ֻ�õ�8λ����24λԤ����
	         // mod=0 ������xyֱ�߲岹��
	         // mod=1 ������xyzֱ�߲岹��
	         // mod=2��3��  2=˳ʱ��Բ���岹��3=��ʱ��Բ���岹
	float axisEndPos0;//[3]; // ֱ�ߣ�Բ�����յ����� xyz  ,mm ��λ����������
	float axisEndPos1;
	float axisEndPos2;
	float axisCenPos0;//[2]; // Բ���������� xy ,mm ��λ, ��������
	float axisCenPos1;
	float nominal_speed; // ��ƣ������ٶȣ��ٶ�, mm/min  (����/����)
}LineArcCmd;

#define AXIS_IDS 0x210//0x654//0x210  // // x,y,z ֱ��

#define SWITCH_ON 1
#define SWITCH_OFF 0
void CMotionPanel::OnBnClickedBtTestio4()
{

	char FifoStatus[13];
	Cen_FifoCtrl_B(1,FifoStatus);

	char fifoStat;
	unsigned int fifoIdleCnt=0,fifoCmdCnt=0;// fifo ���пռ������fifo�ڲ�ָ�����
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	Onquit();
	CDialog::OnClose();
}


void CMotionPanel::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

		cmdArr2[k++].cmd = 0x48000000;//PWM��ָ��

	}
	Cen_pushDllFifo_A(cmdArr2,k);
	return ;
}


void CMotionPanel::OnBnClickedBtTestio5()
{// ������
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


	//1. *********�ؼ���״̬�ӵ�ǰ�㵽��1����
	cmdArr2[k++].cmd = 0x32000000 + 9;//PA=0// �ؼ���,֮ǰҪ����ʼ��
	ScanMoveTo(cmdArr2,&k,startA,endB,m_iScanSpeedpps); // �ؼ���״̬�ӵ�ǰ�㵽��1����

	//1. *********������״̬ ����1����
	cmdArr2[k++].cmd = 0x31000000 + 9;//PA=1// ������,֮ǰҪ����ʼ��
	cmdArr2[k++].cmd = 0x12000000 + 200;// ��������ʱ us��200us��������ʱ����1000000�ٶ��ǿ��Ե�
	endC.x=22768;endC.y=42768;
	ScanMoveTo(cmdArr2,&k,endB,endC,m_iScanSpeedpps);// �ӵ�1���㻭����2����

	//2. *********������״̬ ����2����
	endD.x=22768;endD.y=22768;
	ScanMoveTo(cmdArr2,&k,endC,endD,m_iScanSpeedpps);// �ӵ�2���㻭����3����

	//3. *********������״̬ ����3����
	endE.x=42768;endE.y=22768;
	ScanMoveTo(cmdArr2,&k,endD,endE,m_iScanSpeedpps);// �ӵ�3���㻭����4����


	//4. *********������״̬ ����4����
	ScanMoveTo(cmdArr2,&k,endE,endB,m_iScanSpeedpps);// �ӵ�4���㻭����1����

	//5.�ؼ���
	cmdArr2[k++].cmd = 0x32000000 + 9;//PA=0
	cmdArr2[k++].cmd = 0x12000000 + 200;// �ؼ�����ʱ us��200us��������ʱ����1000000�ٶ��ǿ��Ե�

	Cen_pushDllFifo_A(cmdArr2,k);
	return ;
}



void CMotionPanel::OnBnClickedBtTestio6()
{
		int sizeCMD,k=0;
	char FifoStatus[13];

	if(Cen_DllFifoBusy_A()) return;

	memset(cmdArr2,0,sizeof(FifoCmd)*200000);

	// �ؼ���
	cmdArr2[k++].cmd = 0x31000000 + 9;//PA=0
	cmdArr2[k++].cmd = 0x31000000 + 3;// DB37.20 =1
	

	Cen_pushDllFifo_A(cmdArr2,k);
	return ;
}


void CMotionPanel::OnBnClickedBtMouseFo()
{
	Golv_Mouse_SW = !Golv_Mouse_SW; // ��������� ���ڶ�ʱ������ˢ�� ʵʱ����

}


void CMotionPanel::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (Golv_Mouse_SW)
	{
		CString strMousePos;
		strMousePos.Format("%d,%d",point.x,point.y);
		GetDlgItem(IDC_MSG_MOUSE)->SetWindowText(strMousePos);


		// �����и�����ת���� ��������� ���꡿ ת�� �� �������꡿
		//  ������ڣ����Ͻ��ǣ�0,0��,800x600,���ĵ��ǣ�400��300��
		//  �񾵣�                   65535x65535�������ǣ�32768��32768��
		//  ��������ʾ�������򵥵�60���Ŵ��������

		int sizeCMD, k = 0;
		char FifoStatus[13];
		memset(cmdArr2, 0, sizeof(FifoCmd) * 200000);

		if (m_iScanSpeedpps < 100) m_iScanSpeedpps = 1000;//���ƶ��ٶ�

		POINT startA, endB;

		startA.x = m_iPositionX;// �񾵵�ǰ����
		startA.y = m_iPositionY;

		endB.x = point.x*60; endB.y = point.y*60; // ת����� ��Ŀ������


		cmdArr2[k++].cmd = 0x32000000 + 9;//PA=0// �ؼ���,֮ǰҪ����ʼ��
		ScanMoveTo(cmdArr2, &k, startA, endB, m_iScanSpeedpps); // �ؼ���״̬�ӵ�ǰ�㵽 �����ڵ�

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
