#pragma once


// CDialogTargetIP 对话框

class CDialogTargetIP : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogTargetIP)

public:
	CDialogTargetIP(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogTargetIP();


	DWORD dwAddress ;
	DWORD dwAddress2 ;
	CIPAddressCtrl m_ipAddress;
	CIPAddressCtrl m_ipAddress2;
// 对话框数据
	enum { IDD = IDD_TARGET_IP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnStnClicked65535();
};
