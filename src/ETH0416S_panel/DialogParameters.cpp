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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}


void CDialogParameters::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDialogParameters::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������


	CDialog::OnOK();
}


void CDialogParameters::OnBnClickedDisplayCnt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDialogParameters::OnEnChangecpumYz()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CDialogParameters::OnBnClickedCheck3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDialogParameters::OnBnClickedCheck12()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDialogParameters::OnBnClickedCheck13()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDialogParameters::OnBnClickedCheck14()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

float *pArrTargets; // mmΪ��λ
float *pArrMeasures;// um Ϊ��λ��ƫ��ֵ
float *pArrMeasures2;// um Ϊ��λ��ƫ��ֵ, ��2���õ�
unsigned int *pArrDeviaData;// �·���У�����ݴ洢��

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
		strFilePath = rtlSelFileDialog.GetPathName();//����·��
		strFileName = rtlSelFileDialog.GetFileName();
		//CString strFileExtName = rtlSelFileDialog.GetFileExt();//�ļ���չ��

		if( !f.Open(strFilePath, CFile::modeRead ) )
		{
			AfxMessageBox("Can't Open File: "+strFilePath);
			return ;
		}
		CArchive arLoad(&f, CArchive::load);
		while(1) // ��ʼ���ļ���һ���ж���,�ҵ���������
		{
			if(!(arLoad.ReadString(strReadBuf))) break;

			if ( strReadBuf.Find("Target-count", 0) != -1)
			{ sscanf(strReadBuf, "Target-count:%d", &iTargetCount);break;}

		}
		if(iTargetCount) // ����0
		{
			pArrTargets=new float[iTargetCount]; 
			memset(pArrTargets,0,iTargetCount*sizeof(float));
			while(1)
			{
				if(!(arLoad.ReadString(strReadBuf))) break;

				if ( strReadBuf.Find("Targets", 0) != -1)
				{
					// ��ʼ��ȡ����ֵ��mm
					{
						ParseOK =1;strAllTarget="";strSCanFort="";
						for(i=1;i<=((iTargetCount/5)+1);i++)
						{// ���������ô���У�������Ϊ��ν���ʧ��
							if(!(arLoad.ReadString(strReadBuf))) {ParseOK =0;break;}// ��ʧ��
							strAllTarget+=strReadBuf;
						}
						if(ParseOK) // ���н���strAllTarget
						{
							for(i=0;i<iTargetCount;i++)
							{// ��ʼ������ �����õ���iTargetCount��
								memset(tempCharBuf,0,200);
								//�Կո�Ϊ����,���һ����������ֱ����CString��������Ȼ�䳤��������
								strAllTarget.TrimLeft(" ");
								sscanf(strAllTarget,"%[^ ]",tempCharBuf);
								strOneString = tempCharBuf;// ��������תһ��
								strAllTarget= strAllTarget.Right((strAllTarget.GetLength())-(strOneString.GetLength())-1);
								sscanf(strOneString,"%f",&(pArrTargets[i]));
							}
						}
					}
					// ���涼�������ˣ���ȻҪ�˳���
					break;
				}
			}
		}
		// ����Ŀ��λ�óɹ�
		if(ParseOK)// �������OK�����·���դ�߲�����Ϣ������λ��
		{// ��ʼ��������ֵ
			//�ȶ�ȡ����ֵ������Run-count:4
			while(1) // ��ʼ���ļ���һ���ж���,�ҵ���������
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

					// ��ʼ����ֵ��mm
					{
						bReadMeasureSucc=1;strAllTarget="";strSCanFort="";
						for(i=0;i<iRunCount;i++) // 1,3 ȡƽ��ֵ��2,4ȡƽ��ֵ
						{// ���������ô���У�������Ϊ��ν���ʧ��
							for(j=0;j<iTargetCount;j++)
							{
								if(!(arLoad.ReadString(strReadBuf))) {bReadMeasureSucc =0;break;}// ��ʧ��
								//ֱ�����������ۼӲ�����
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
							pArrMeasures[j] /= iRunCount;//  2;////iRunCount; // ȡƽ��ֵ  
						}
					}
					// ���涼�������ˣ���ȻҪ�˳���
					break;
				}
			}
		}
		if(bReadMeasureSucc) // ��ʾȫ���ɹ�,��ʾ����
		{
			CString temp2;
			temDisplay.Format("Read file success!\r\nTarget-count:%d,run-count:%d\r\n\r\n",iTargetCount,iRunCount);
			for(j=0;j<iTargetCount;j++)
			{
				temp2 = temDisplay; // ����תһ�£�����release�汾�����쳣
				temDisplay.Format("%s %3.d   %9.4f(mm)   %6.1f(um)\r\n",temp2,j+1,pArrTargets[j],pArrMeasures[j]);
				if(((j+1)%3)==0) temDisplay+="\r\n";
				//temp2.Format("j=:%d",j);
				//AfxMessageBox(temp2);
			}
			if(::MessageBox(NULL, temDisplay, "�ļ���ȡ��ʾ", MB_OKCANCEL|MB_ICONINFORMATION)== IDOK)
			{

			}
		}
		else
			AfxMessageBox("�ļ���ȡʧ�ܣ������ļ����ݣ�");

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

	rtlSelFileDialog.m_ofn.lpstrTitle = "�򿪵�һ��У���ļ�";
	if( rtlSelFileDialog.DoModal ()==IDOK )
	{
		strFilePath = rtlSelFileDialog.GetPathName();//����·��
		strFileName = rtlSelFileDialog.GetFileName();
		//CString strFileExtName = rtlSelFileDialog.GetFileExt();//�ļ���չ��

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
		while(1) // ��ʼ���ļ���һ���ж���,�ҵ���������
		{
			if(!(arLoad.ReadString(strReadBuf))) break;

			if ( strReadBuf.Find("Target-count", 0) != -1)
			{ sscanf(strReadBuf, "Target-count:%d", &iTargetCount);break;}

		}
		if(iTargetCount) // ����0
		{
			pArrTargets=new float[iTargetCount]; 
			memset(pArrTargets,0,iTargetCount*sizeof(float));
			while(1)
			{
				if(!(arLoad.ReadString(strReadBuf))) break;

				if ( strReadBuf.Find("Targets", 0) != -1)
				{
					// ��ʼ��ȡ����ֵ��mm
					{
						ParseOK =1;strAllTarget="";strSCanFort="";
						for(i=1;i<=((iTargetCount/5)+1);i++)
						{// ���������ô���У�������Ϊ��ν���ʧ��
							if(!(arLoad.ReadString(strReadBuf))) {ParseOK =0;break;}// ��ʧ��
							strAllTarget+=strReadBuf;
						}
						if(ParseOK) // ���н���strAllTarget
						{
							for(i=0;i<iTargetCount;i++)
							{// ��ʼ������ �����õ���iTargetCount��
								memset(tempCharBuf,0,200);
								//�Կո�Ϊ����,���һ����������ֱ����CString��������Ȼ�䳤��������
								strAllTarget.TrimLeft(" ");
								sscanf(strAllTarget,"%[^ ]",tempCharBuf);
								strOneString = tempCharBuf;// ��������תһ��
								strAllTarget= strAllTarget.Right((strAllTarget.GetLength())-(strOneString.GetLength())-1);
								sscanf(strOneString,"%f",&(pArrTargets[i]));
							}
						}
					}
					// ���涼�������ˣ���ȻҪ�˳���
					break;
				}
			}
		}
		// ����Ŀ��λ�óɹ�
		if(ParseOK)// �������OK�����·���դ�߲�����Ϣ������λ��
		{// ��ʼ��������ֵ
			//�ȶ�ȡ����ֵ������Run-count:4
			while(1) // ��ʼ���ļ���һ���ж���,�ҵ���������
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

						// ��ʼ����ֵ��mm
						{
							bReadMeasureSucc=1;strAllTarget="";strSCanFort="";
							for(i=0;i<iRunCount;i++) // 1,3 ȡƽ��ֵ��2,4ȡƽ��ֵ
							{// ���������ô���У�������Ϊ��ν���ʧ��
								for(j=0;j<iTargetCount;j++)
								{
									if(!(arLoad.ReadString(strReadBuf))) {bReadMeasureSucc =0;break;}// ��ʧ��
									//ֱ�����������ۼӲ�����
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
								pArrMeasures[j] /= iRunCount;//  2;////iRunCount; // ȡƽ��ֵ  
							}
						}
						// ���涼�������ˣ���ȻҪ�˳���
						break;
					}
				}
		}
		if(bReadMeasureSucc) // ��ʾȫ���ɹ�,��ʾ����
		{
			CString temp2;
			temDisplay.Format("Read file success!\r\nTarget-count:%d,run-count:%d\r\n\r\n",iTargetCount,iRunCount);
			for(j=0;j<iTargetCount;j++)
			{
				temp2 = temDisplay; // ����תһ�£�����release�汾�����쳣
				temDisplay.Format("%s %3.d   %9.4f(mm)   %6.1f(um)----",temp2,j+1,pArrTargets[j],pArrMeasures[j]);
				if(((j+1)%3)==0) temDisplay+="\r\n";
				//temp2.Format("j=:%d",j);
				//AfxMessageBox(temp2);
			}
			if(::MessageBox(NULL, temDisplay, "�ļ���ȡ��ʾ", MB_OKCANCEL|MB_ICONINFORMATION)== IDOK)
			{;
				//pArrDeviaData =new U32[iTargetCount];  
				//// ������λ��
				//for(i=0;i<iTargetCount;i++)
				//{// ׼������
				//	pArrDeviaData[i]=(pArrTargets[i])*10;   // ���������mm-> 10mm
				//	pArrDeviaData[i]=pArrDeviaData[i] << 16;// ����Ĭ����С��6553mm�ģ����������ֱ��ȥ����
				//	pArrDeviaData[i] += (((int)((pArrMeasures[i])*10))&(0xffff));//   um -> 10um
				//}
				//ETH0416S_SetDeviatData(pArrDeviaData,iTargetCount);
			}
		}
		else
			AfxMessageBox("�ļ���ȡʧ�ܣ������ļ����ݣ�");

		arLoad.Close();
	}

	f.Close();











	CFileDialog rtlSelFileDialog2 (TRUE, NULL, NULL,
		OFN_EXPLORER | OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, NULL);

	rtlSelFileDialog2.m_ofn.lpstrTitle = "�򿪵�һ��У���ļ�";


	bReadMeasureSucc=0;
	rtlSelFileDialog2.m_ofn.lpstrTitle = "�򿪵ڶ���У���ļ�";
	if( rtlSelFileDialog2.DoModal ()==IDOK )
	{
		strFilePath = rtlSelFileDialog2.GetPathName();//����·��
		strFileName = rtlSelFileDialog2.GetFileName();
		//CString strFileExtName = rtlSelFileDialog.GetFileExt();//�ļ���չ��

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
		while(1) // ��ʼ���ļ���һ���ж���,�ҵ���������
		{
			if(!(arLoad.ReadString(strReadBuf))) break;

			if ( strReadBuf.Find("Target-count", 0) != -1)
			{ sscanf(strReadBuf, "Target-count:%d", &iTargetCount);break;}

		}
		
		// ������һ��Ŀ��λ�óɹ�
		if(ParseOK)// �������OK�����·���դ�߲�����Ϣ������λ��
		{// ��ʼ��������ֵ
			//�ȶ�ȡ����ֵ������Run-count:4
			while(1) // ��ʼ���ļ���һ���ж���,�ҵ���������
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

						// ��ʼ����ֵ��mm
						{
							bReadMeasureSucc=1;strAllTarget="";strSCanFort="";
							for(i=0;i<iRunCount;i++) // 1,3 ȡƽ��ֵ��2,4ȡƽ��ֵ
							{// ���������ô���У�������Ϊ��ν���ʧ��
								for(j=0;j<iTargetCount;j++)
								{
									if(!(arLoad.ReadString(strReadBuf))) {bReadMeasureSucc =0;break;}// ��ʧ��
									//ֱ�����������ۼӲ�����
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
								pArrMeasures2[j] /= iRunCount;//  2;////iRunCount; // ȡƽ��ֵ  
							}
						}
						// ���涼�������ˣ���ȻҪ�˳���
						break;
					}
				}
		}
		if(bReadMeasureSucc) // ��ʾȫ���ɹ�,��ʾ����
		{
			CString temp2;
			temDisplay.Format("Read file success!\r\nTarget-count:%d,run-count:%d\r\n\r\n",iTargetCount,iRunCount);
			for(j=0;j<iTargetCount;j++)
			{
				temp2 = temDisplay; // ����תһ�£�����release�汾�����쳣
				pArrMeasures[j] += pArrMeasures2[j];
				temDisplay.Format("%s %3.d   %9.4f(mm)   %6.1f(um)",temp2,j+1,pArrTargets[j],pArrMeasures[j]);
				if(((j+1)%3)==0) temDisplay+="\r\n";
				//temp2.Format("j=:%d",j);
				//AfxMessageBox(temp2);
			}
			if(::MessageBox(NULL, temDisplay, "�ļ���ȡ��ʾ", MB_OKCANCEL|MB_ICONINFORMATION)== IDOK)
			{;
			pArrDeviaData =new U32[iTargetCount];  
			// ������λ��
			for(i=0;i<iTargetCount;i++)
			{// ׼������
				pArrDeviaData[i]=(pArrTargets[i])*10;   // ���������mm-> 10mm
				pArrDeviaData[i]=pArrDeviaData[i] << 16;// ����Ĭ����С��6553mm�ģ����������ֱ��ȥ����
				pArrDeviaData[i] += (((int)((pArrMeasures[i])*10))&(0xffff));//   um -> 10um
			}
			//ETH0416S_SetDeviatData(pArrDeviaData,iTargetCount);
			}
		}
		else
			AfxMessageBox("�ļ���ȡʧ�ܣ������ļ����ݣ�");

		arLoad.Close();
	}

	f.Close();




	delete pArrTargets;
	delete pArrMeasures;
	delete pArrMeasures2;
	delete pArrDeviaData;
}
