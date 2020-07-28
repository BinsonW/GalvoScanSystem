// DlgIPSetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ETH0416S_panel.h"
#include "DlgIPSetting.h"
#include "afxdialogex.h"


// CDlgIPSetting �Ի���

IMPLEMENT_DYNAMIC(CDlgIPSetting, CDialogEx)

CDlgIPSetting::CDlgIPSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgIPSetting::IDD, pParent)
	, m_strMacAddr(_T(""))
{

}

CDlgIPSetting::~CDlgIPSetting()
{
}

BOOL CDlgIPSetting::OnInitDialog() 
{

	CDialogEx::OnInitDialog();

	m_ctrlMacAddr.EnableMask(_T("AA AA AA AA AA AA"), _T("__-__-__-__-__-__"),_T(' '));
	m_ctrlMacAddr.SetValidChars(_T("01234567890ABCDEFabcdef"));
	//m_strMacAddr = _T("00-78-13-81-12-87");// ����������
	//m_ctrlMacAddr.SetWindowText(_T("00-78-13-81-12-87"));// ��������
	m_ctrlMacAddr.SetWindowText(m_strMacAddr2);// ��������

	m_ipAddress.SetAddress(ipByte[0],ipByte[1],ipByte[2],ipByte[3]);

	return TRUE;
}

void CDlgIPSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipAddress);
	DDX_Control(pDX, IDC_MFCMASKEDEDIT1, m_ctrlMacAddr);
	DDX_Text(pDX, IDC_MFCMASKEDEDIT1, m_strMacAddr);
}


BEGIN_MESSAGE_MAP(CDlgIPSetting, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgIPSetting::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgIPSetting::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgIPSetting ��Ϣ�������


void CDlgIPSetting::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData();

	m_ipAddress.GetAddress(ipByte[0],ipByte[1],ipByte[2],ipByte[3]);
	m_ctrlMacAddr.DisableMask();// ��ȡ�ı�֮ǰ��Ҫdisable������õ����ַ��������м��-
	m_ctrlMacAddr.GetWindowText(m_strMacAddr2.GetBuffer(),30);
	CDialogEx::OnOK();
}


void CDlgIPSetting::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
