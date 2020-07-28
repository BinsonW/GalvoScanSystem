// DialogTargetIP.cpp : 实现文件
//

#include "stdafx.h"
#include "ETH0416S_panel.h"
#include "DialogTargetIP.h"
#include "afxdialogex.h"


// CDialogTargetIP 对话框

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


// CDialogTargetIP 消息处理程序


void CDialogTargetIP::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO:  在此添加额外的初始化
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
