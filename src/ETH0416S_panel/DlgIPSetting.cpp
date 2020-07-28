// DlgIPSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "ETH0416S_panel.h"
#include "DlgIPSetting.h"
#include "afxdialogex.h"


// CDlgIPSetting 对话框

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
	//m_strMacAddr = _T("00-78-13-81-12-87");// 不能这样用
	//m_ctrlMacAddr.SetWindowText(_T("00-78-13-81-12-87"));// 这样可以
	m_ctrlMacAddr.SetWindowText(m_strMacAddr2);// 这样可以

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


// CDlgIPSetting 消息处理程序


void CDlgIPSetting::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData();

	m_ipAddress.GetAddress(ipByte[0],ipByte[1],ipByte[2],ipByte[3]);
	m_ctrlMacAddr.DisableMask();// 获取文本之前需要disable，否则得到的字符串少了中间的-
	m_ctrlMacAddr.GetWindowText(m_strMacAddr2.GetBuffer(),30);
	CDialogEx::OnOK();
}


void CDlgIPSetting::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
