#pragma once
#include "afxcmn.h"
#include "afxmaskededit.h"


// CDlgIPSetting �Ի���

class CDlgIPSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgIPSetting)

public:
	CDlgIPSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgIPSetting();

	BYTE ipByte[4];
// �Ի�������
	enum { IDD = IDD_DLG_IP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
