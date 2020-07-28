#pragma once
#include "afxcmn.h"
#include "afxmaskededit.h"


// CDlgIPSetting 对话框

class CDlgIPSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgIPSetting)

public:
	CDlgIPSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgIPSetting();

	BYTE ipByte[4];
// 对话框数据
	enum { IDD = IDD_DLG_IP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CIPAddressCtrl m_ipAddress;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CMFCMaskedEdit m_ctrlMacAddr;
	CString m_strMacAddr;
	CString m_strMacAddr2;
	afx_msg void OnBnClickedCancel();
};
