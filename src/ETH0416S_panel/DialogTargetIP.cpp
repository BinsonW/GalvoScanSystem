// DialogTargetIP.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ETH0416S_panel.h"
#include "DialogTargetIP.h"
#include "afxdialogex.h"


// CDialogTargetIP �Ի���

IMPLEMENT_DYNAMIC(CDialogTargetIP, CDialogEx)

CDialogTargetIP::CDialogTargetIP(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogTargetIP::IDD, pParent)
{

}

CDialogTargetIP::~CDialogTargetIP()
{
}

void CDialogTargetIP::DoDataExchange(CDataExchange* pDX)
{

	DDX_Control(pDX, IDC_TARGET_IP, m_ipAddress);
	DDX_Control(pDX, IDC_TARGET_IP2, m_ipAddress2);
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogTargetIP, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogTargetIP::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogTargetIP ��Ϣ�������


void CDialogTargetIP::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	m_ipAddress.GetAddress(dwAddress);
	m_ipAddress2.GetAddress(dwAddress2);

	CDialogEx::OnOK();
}


BOOL CDialogTargetIP::OnInitDialog()
{

	CDialogEx::OnInitDialog();

	m_ipAddress.SetAddress(dwAddress);
	m_ipAddress2.SetAddress(dwAddress2);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
