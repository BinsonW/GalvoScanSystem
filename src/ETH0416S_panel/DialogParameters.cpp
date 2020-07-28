// DialogParameters.cpp : implementation file
//

#include "stdafx.h"
#include "ETH0416S_panel.h"
#include "DialogParameters.h"

#include "ETH0416SAPI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogParameters dialog


CDialogParameters::CDialogParameters(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogParameters::IDD, pParent)
	, m_iCaliTimeMS(50),m_iAfterHomeOffset(0)
	, m_fSoftLimitPosValue(0)
	, m_fSoftLimitNegaValue(0)
{
	//{{AFX_DATA_INIT(CDialogParameters)
	//}}AFX_DATA_INIT
}


void CDialogParameters::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogParameters)
	DDX_Text(pDX, IDC_ACCTIME, m_fAccTime);
	DDV_MinMaxFloat(pDX, m_fAccTime, 0.001f, 100.f);
	DDX_Text(pDX, IDC_ACCTIME2, m_fAccTimeY);
	DDX_Text(pDX, IDC_PPM_X, m_iPPM_X);
	DDX_Text(pDX, IDC_PPM_Y, m_iPPM_Y);
	DDX_Text(pDX, IDC_cPum_X, m_iCPMM_X);
	DDX_Text(pDX, IDC_cPum_Y, m_iCPMM_Y);
	DDX_Text(pDX, IDC_START_SPEED, m_fStartSpeedX);
	DDX_Text(pDX, IDC_SPEED, m_fSpeedX);
	DDX_Text(pDX, IDC_START_SPEED2, m_fStartSpeedY);
	DDX_Text(pDX, IDC_SPEED2, m_fSpeedY);
	DDX_Text(pDX, IDC_SPEED4, m_fHomeSpeedX);
	DDX_Text(pDX, IDC_SPEED5, m_fHomeSpeedY);



	//}}AFX_DATA_MAP
	DDV_MinMaxUInt(pDX, m_iCaliTimeMS, 50, 50000);
}


BEGIN_MESSAGE_MAP(CDialogParameters, CDialog)
	//{{AFX_MSG_MAP(CDialogParameters)
	ON_BN_CLICKED(IDC_SAVEPARAM, OnSaveparam)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDCANCEL, &CDialogParameters::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CDialogParameters::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK3, &CDialogParameters::OnBnClickedCheck3)
//	ON_BN_CLICKED(IDC_CHECK14, &CDialogParameters::OnBnClickedCheck14)
ON_BN_CLICKED(ID_PARSE_RTL, &CDialogParameters::OnBnClickedParseRtl)
ON_BN_CLICKED(ID_PARSE_RTL2, &CDialogParameters::OnBnClickedParseRtl2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogParameters message handlers

void CDialogParameters::OnSaveparam() 
{
	// TODO: Add your control notification handler code here
	
}

void CDialogParameters::OnOK() 
{
	// TODO: Add extra validation here
	
	if(!UpdateData()) return;
	CDialog::OnOK();
}


void CDialogParameters::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


void CDialogParameters::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDialogParameters::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码


	CDialog::OnOK();
}


void CDialogParameters::OnBnClickedDisplayCnt()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDialogParameters::OnEnChangecpumYz()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDialogParameters::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDialogParameters::OnBnClickedCheck12()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDialogParameters::OnBnClickedCheck13()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDialogParameters::OnBnClickedCheck14()
{
	// TODO: 在此添加控件通知处理程序代码
}

float *pArrTargets; // mm为单位
float *pArrMeasures;// um 为单位的偏差值
float *pArrMeasures2;// um 为单位的偏差值, 第2次用的
unsigned int *pArrDeviaData;// 下发的校正数据存储区

char tempCharBuf[200];
void CDialogParameters::OnBnClickedParseRtl()
{
	CFile f;
	CString strFilePath,strFileName;
	CString strReadBuf,temDisplay,strAllTarget,strSCanFort,strOneString;
	char szFilters[]="Renishaw Files (*.rtl)|*.rtl|";
	unsigned int iTargetCount=0,iRunCount=0;
	int iRet;
	char ParseOK=0,bReadMeasureSucc=0;
	int i,j;
	//CList<DxfVertex,DxfVertex&> arrAllPoint;

	CFileDialog rtlSelFileDialog (TRUE, NULL, NULL,
		OFN_EXPLORER | OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, NULL);

	if( rtlSelFileDialog.DoModal ()==IDOK )
	{
		strFilePath = rtlSelFileDialog.GetPathName();//完整路径
		strFileName = rtlSelFileDialog.GetFileName();
		//CString strFileExtName = rtlSelFileDialog.GetFileExt();//文件扩展名

		if( !f.Open(strFilePath, CFile::modeRead ) )
		{
			AfxMessageBox("Can't Open File: "+strFilePath);
			return ;
		}
		CArchive arLoad(&f, CArchive::load);
		while(1) // 开始读文件（一行行读）,找到测量步数
		{
			if(!(arLoad.ReadString(strReadBuf))) break;

			if ( strReadBuf.Find("Target-count", 0) != -1)
			{ sscanf(strReadBuf, "Target-count:%d", &iTargetCount);break;}

		}
		if(iTargetCount) // 大于0
		{
			pArrTargets=new float[iTargetCount]; 
			memset(pArrTargets,0,iTargetCount*sizeof(float));
			while(1)
			{
				if(!(arLoad.ReadString(strReadBuf))) break;

				if ( strReadBuf.Find("Targets", 0) != -1)
				{
					// 开始读取步距值，mm
					{
						ParseOK =1;strAllTarget="";strSCanFort="";
						for(i=1;i<=((iTargetCount/5)+1);i++)
						{// 必须读到这么多行，否则认为这次解析失败
							if(!(arLoad.ReadString(strReadBuf))) {ParseOK =0;break;}// 读失败
							strAllTarget+=strReadBuf;
						}
						if(ParseOK) // 集中解析strAllTarget
						{
							for(i=0;i<iTargetCount;i++)
							{// 开始解析， 解析得到了iTargetCount个
								memset(tempCharBuf,0,200);
								//以空格为结束,最后一个参数不能直接用CString变量，不然其长度有问题
								strAllTarget.TrimLeft(" ");
								sscanf(strAllTarget,"%[^ ]",tempCharBuf);
								strOneString = tempCharBuf;// 必须这样转一下
								strAllTarget= strAllTarget.Right((strAllTarget.GetLength())-(strOneString.GetLength())-1);
								sscanf(strOneString,"%f",&(pArrTargets[i]));
							}
						}
					}
					// 上面都解析完了，当然要退出了
					break;
				}
			}
		}
		// 解析目标位置成功
		if(ParseOK)// 上面解析OK，才下发光栅尺补偿信息，到下位机
		{// 开始解析测量值
			//先读取测量值个数：Run-count:4
			while(1) // 开始读文件（一行行读）,找到测量步数
			{
				if(!(arLoad.ReadString(strReadBuf))) break;

				if ( strReadBuf.Find("Run-count", 0) != -1)
				{ sscanf(strReadBuf, "Run-count:%d", &iRunCount);break;}

			}


			if(iRunCount)
			while(1)
			{
				if(!(arLoad.ReadString(strReadBuf))) {break;}

				if ( strReadBuf.Find("Run Target Data", 0) != -1)
				{
					int iRunIndex,iTargetDataIndex;
					float fTargetDEVIA;
					pArrMeasures=new float[iTargetCount]; 
					memset(pArrMeasures,0,iTargetCount*sizeof(float));

					// 开始测量值，mm
					{
						bReadMeasureSucc=1;strAllTarget="";strSCanFort="";
						for(i=0;i<iRunCount;i++) // 1,3 取平均值，2,4取平均值
						{// 必须读到这么多行，否则认为这次解析失败
							for(j=0;j<iTargetCount;j++)
							{
								if(!(arLoad.ReadString(strReadBuf))) {bReadMeasureSucc =0;break;}// 读失败
								//直接做处理，做累加操作。
								//if((i==0)||(i==2))
								{
									sscanf(strReadBuf, "%d  %d  %f", &iRunIndex,&iTargetDataIndex,&fTargetDEVIA);
									pArrMeasures[iTargetDataIndex-1]+=fTargetDEVIA;
								}
							}
						}
					}

					if(bReadMeasureSucc)
					{
						for(j=0;j<iTargetCount;j++)
						{
							pArrMeasures[j] /= iRunCount;//  2;////iRunCount; // 取平均值  
						}
					}
					// 上面都解析完了，当然要退出了
					break;
				}
			}
		}
		if(bReadMeasureSucc) // 表示全部成功,显示出来
		{
			CString temp2;
			temDisplay.Format("Read file success!\r\nTarget-count:%d,run-count:%d\r\n\r\n",iTargetCount,iRunCount);
			for(j=0;j<iTargetCount;j++)
			{
				temp2 = temDisplay; // 必须转一下，否则release版本工作异常
				temDisplay.Format("%s %3.d   %9.4f(mm)   %6.1f(um)\r\n",temp2,j+1,pArrTargets[j],pArrMeasures[j]);
				if(((j+1)%3)==0) temDisplay+="\r\n";
				//temp2.Format("j=:%d",j);
				//AfxMessageBox(temp2);
			}
			if(::MessageBox(NULL, temDisplay, "文件读取提示", MB_OKCANCEL|MB_ICONINFORMATION)== IDOK)
			{

			}
		}
		else
			AfxMessageBox("文件读取失败！请检查文件数据！");

		delete pArrTargets;
		delete pArrMeasures;
		delete pArrDeviaData;
		arLoad.Close();
	}

	f.Close();
}


void CDialogParameters::OnBnClickedParseRtl2()
{
	CFile f;
	CString strFilePath,strFileName;
	CString strReadBuf,temDisplay,strAllTarget,strSCanFort,strOneString;
	char szFilters[]="Renishaw Files (*.rtl)|*.rtl|";
	unsigned int iTargetCount=0,iRunCount=0;
	int iRet;
	char ParseOK=0,bReadMeasureSucc=0;
	int i,j;
	//CList<DxfVertex,DxfVertex&> arrAllPoint;

	CFileDialog rtlSelFileDialog (TRUE, NULL, NULL,
		OFN_EXPLORER | OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, NULL);

	rtlSelFileDialog.m_ofn.lpstrTitle = "打开第一个校正文件";
	if( rtlSelFileDialog.DoModal ()==IDOK )
	{
		strFilePath = rtlSelFileDialog.GetPathName();//完整路径
		strFileName = rtlSelFileDialog.GetFileName();
		//CString strFileExtName = rtlSelFileDialog.GetFileExt();//文件扩展名

		if( !f.Open(strFilePath, CFile::modeRead ) )
		{
			AfxMessageBox("Can't Open File: "+strFilePath);

			delete pArrTargets;
			delete pArrMeasures;
			delete pArrMeasures2;
			delete pArrDeviaData;
			return ;
		}
		CArchive arLoad(&f, CArchive::load);
		while(1) // 开始读文件（一行行读）,找到测量步数
		{
			if(!(arLoad.ReadString(strReadBuf))) break;

			if ( strReadBuf.Find("Target-count", 0) != -1)
			{ sscanf(strReadBuf, "Target-count:%d", &iTargetCount);break;}

		}
		if(iTargetCount) // 大于0
		{
			pArrTargets=new float[iTargetCount]; 
			memset(pArrTargets,0,iTargetCount*sizeof(float));
			while(1)
			{
				if(!(arLoad.ReadString(strReadBuf))) break;

				if ( strReadBuf.Find("Targets", 0) != -1)
				{
					// 开始读取步距值，mm
					{
						ParseOK =1;strAllTarget="";strSCanFort="";
						for(i=1;i<=((iTargetCount/5)+1);i++)
						{// 必须读到这么多行，否则认为这次解析失败
							if(!(arLoad.ReadString(strReadBuf))) {ParseOK =0;break;}// 读失败
							strAllTarget+=strReadBuf;
						}
						if(ParseOK) // 集中解析strAllTarget
						{
							for(i=0;i<iTargetCount;i++)
							{// 开始解析， 解析得到了iTargetCount个
								memset(tempCharBuf,0,200);
								//以空格为结束,最后一个参数不能直接用CString变量，不然其长度有问题
								strAllTarget.TrimLeft(" ");
								sscanf(strAllTarget,"%[^ ]",tempCharBuf);
								strOneString = tempCharBuf;// 必须这样转一下
								strAllTarget= strAllTarget.Right((strAllTarget.GetLength())-(strOneString.GetLength())-1);
								sscanf(strOneString,"%f",&(pArrTargets[i]));
							}
						}
					}
					// 上面都解析完了，当然要退出了
					break;
				}
			}
		}
		// 解析目标位置成功
		if(ParseOK)// 上面解析OK，才下发光栅尺补偿信息，到下位机
		{// 开始解析测量值
			//先读取测量值个数：Run-count:4
			while(1) // 开始读文件（一行行读）,找到测量步数
			{
				if(!(arLoad.ReadString(strReadBuf))) break;

				if ( strReadBuf.Find("Run-count", 0) != -1)
				{ sscanf(strReadBuf, "Run-count:%d", &iRunCount);break;}

			}


			if(iRunCount)
				while(1)
				{
					if(!(arLoad.ReadString(strReadBuf))) {break;}

					if ( strReadBuf.Find("Run Target Data", 0) != -1)
					{
						int iRunIndex,iTargetDataIndex;
						float fTargetDEVIA;
						pArrMeasures=new float[iTargetCount]; 
						memset(pArrMeasures,0,iTargetCount*sizeof(float));

						// 开始测量值，mm
						{
							bReadMeasureSucc=1;strAllTarget="";strSCanFort="";
							for(i=0;i<iRunCount;i++) // 1,3 取平均值，2,4取平均值
							{// 必须读到这么多行，否则认为这次解析失败
								for(j=0;j<iTargetCount;j++)
								{
									if(!(arLoad.ReadString(strReadBuf))) {bReadMeasureSucc =0;break;}// 读失败
									//直接做处理，做累加操作。
									//if((i==0)||(i==2))
									{
										sscanf(strReadBuf, "%d  %d  %f", &iRunIndex,&iTargetDataIndex,&fTargetDEVIA);
										pArrMeasures[iTargetDataIndex-1]+=fTargetDEVIA;
									}
								}
							}
						}

						if(bReadMeasureSucc)
						{
							for(j=0;j<iTargetCount;j++)
							{
								pArrMeasures[j] /= iRunCount;//  2;////iRunCount; // 取平均值  
							}
						}
						// 上面都解析完了，当然要退出了
						break;
					}
				}
		}
		if(bReadMeasureSucc) // 表示全部成功,显示出来
		{
			CString temp2;
			temDisplay.Format("Read file success!\r\nTarget-count:%d,run-count:%d\r\n\r\n",iTargetCount,iRunCount);
			for(j=0;j<iTargetCount;j++)
			{
				temp2 = temDisplay; // 必须转一下，否则release版本工作异常
				temDisplay.Format("%s %3.d   %9.4f(mm)   %6.1f(um)----",temp2,j+1,pArrTargets[j],pArrMeasures[j]);
				if(((j+1)%3)==0) temDisplay+="\r\n";
				//temp2.Format("j=:%d",j);
				//AfxMessageBox(temp2);
			}
			if(::MessageBox(NULL, temDisplay, "文件读取提示", MB_OKCANCEL|MB_ICONINFORMATION)== IDOK)
			{;
				//pArrDeviaData =new U32[iTargetCount];  
				//// 发到下位机
				//for(i=0;i<iTargetCount;i++)
				//{// 准备数据
				//	pArrDeviaData[i]=(pArrTargets[i])*10;   // 变成整数，mm-> 10mm
				//	pArrDeviaData[i]=pArrDeviaData[i] << 16;// 距离默认是小于6553mm的，大于这个数直接去掉了
				//	pArrDeviaData[i] += (((int)((pArrMeasures[i])*10))&(0xffff));//   um -> 10um
				//}
				//ETH0416S_SetDeviatData(pArrDeviaData,iTargetCount);
			}
		}
		else
			AfxMessageBox("文件读取失败！请检查文件数据！");

		arLoad.Close();
	}

	f.Close();











	CFileDialog rtlSelFileDialog2 (TRUE, NULL, NULL,
		OFN_EXPLORER | OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, NULL);

	rtlSelFileDialog2.m_ofn.lpstrTitle = "打开第一个校正文件";


	bReadMeasureSucc=0;
	rtlSelFileDialog2.m_ofn.lpstrTitle = "打开第二个校正文件";
	if( rtlSelFileDialog2.DoModal ()==IDOK )
	{
		strFilePath = rtlSelFileDialog2.GetPathName();//完整路径
		strFileName = rtlSelFileDialog2.GetFileName();
		//CString strFileExtName = rtlSelFileDialog.GetFileExt();//文件扩展名

		if( !f.Open(strFilePath, CFile::modeRead ) )
		{
			AfxMessageBox("Can't Open File: "+strFilePath);

			delete pArrTargets;
			delete pArrMeasures;
			delete pArrMeasures2;
			delete pArrDeviaData;

			return ;
		}
		CArchive arLoad(&f, CArchive::load);
		while(1) // 开始读文件（一行行读）,找到测量步数
		{
			if(!(arLoad.ReadString(strReadBuf))) break;

			if ( strReadBuf.Find("Target-count", 0) != -1)
			{ sscanf(strReadBuf, "Target-count:%d", &iTargetCount);break;}

		}
		
		// 解析第一个目标位置成功
		if(ParseOK)// 上面解析OK，才下发光栅尺补偿信息，到下位机
		{// 开始解析测量值
			//先读取测量值个数：Run-count:4
			while(1) // 开始读文件（一行行读）,找到测量步数
			{
				if(!(arLoad.ReadString(strReadBuf))) break;

				if ( strReadBuf.Find("Run-count", 0) != -1)
				{ sscanf(strReadBuf, "Run-count:%d", &iRunCount);break;}

			}

			if(iRunCount)
				while(1)
				{
					if(!(arLoad.ReadString(strReadBuf))) {break;}

					if ( strReadBuf.Find("Run Target Data", 0) != -1)
					{
						int iRunIndex,iTargetDataIndex;
						float fTargetDEVIA;
						pArrMeasures2=new float[iTargetCount]; 
						memset(pArrMeasures2,0,iTargetCount*sizeof(float));

						// 开始测量值，mm
						{
							bReadMeasureSucc=1;strAllTarget="";strSCanFort="";
							for(i=0;i<iRunCount;i++) // 1,3 取平均值，2,4取平均值
							{// 必须读到这么多行，否则认为这次解析失败
								for(j=0;j<iTargetCount;j++)
								{
									if(!(arLoad.ReadString(strReadBuf))) {bReadMeasureSucc =0;break;}// 读失败
									//直接做处理，做累加操作。
									//if((i==0)||(i==2))
									{
										sscanf(strReadBuf, "%d  %d  %f", &iRunIndex,&iTargetDataIndex,&fTargetDEVIA);
										pArrMeasures2[iTargetDataIndex-1]+=fTargetDEVIA;
									}
								}
							}
						}

						if(bReadMeasureSucc)
						{
							for(j=0;j<iTargetCount;j++)
							{
								pArrMeasures2[j] /= iRunCount;//  2;////iRunCount; // 取平均值  
							}
						}
						// 上面都解析完了，当然要退出了
						break;
					}
				}
		}
		if(bReadMeasureSucc) // 表示全部成功,显示出来
		{
			CString temp2;
			temDisplay.Format("Read file success!\r\nTarget-count:%d,run-count:%d\r\n\r\n",iTargetCount,iRunCount);
			for(j=0;j<iTargetCount;j++)
			{
				temp2 = temDisplay; // 必须转一下，否则release版本工作异常
				pArrMeasures[j] += pArrMeasures2[j];
				temDisplay.Format("%s %3.d   %9.4f(mm)   %6.1f(um)",temp2,j+1,pArrTargets[j],pArrMeasures[j]);
				if(((j+1)%3)==0) temDisplay+="\r\n";
				//temp2.Format("j=:%d",j);
				//AfxMessageBox(temp2);
			}
			if(::MessageBox(NULL, temDisplay, "文件读取提示", MB_OKCANCEL|MB_ICONINFORMATION)== IDOK)
			{;
			pArrDeviaData =new U32[iTargetCount];  
			// 发到下位机
			for(i=0;i<iTargetCount;i++)
			{// 准备数据
				pArrDeviaData[i]=(pArrTargets[i])*10;   // 变成整数，mm-> 10mm
				pArrDeviaData[i]=pArrDeviaData[i] << 16;// 距离默认是小于6553mm的，大于这个数直接去掉了
				pArrDeviaData[i] += (((int)((pArrMeasures[i])*10))&(0xffff));//   um -> 10um
			}
			//ETH0416S_SetDeviatData(pArrDeviaData,iTargetCount);
			}
		}
		else
			AfxMessageBox("文件读取失败！请检查文件数据！");

		arLoad.Close();
	}

	f.Close();




	delete pArrTargets;
	delete pArrMeasures;
	delete pArrMeasures2;
	delete pArrDeviaData;
}
