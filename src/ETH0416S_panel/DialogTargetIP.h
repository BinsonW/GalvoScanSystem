#pragma once


// CDialogTargetIP �Ի���

class CDialogTargetIP : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogTargetIP)

public:
	CDialogTargetIP(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogTargetIP();


	DWORD dwAddress ;
	DWORD dwAddress2 ;
	CIPAddressCtrl m_ipAddress;
	CIPAddressCtrl m_ipAddress2;
// �Ի�������
	enum { IDD = IDD_TARGET_IP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnStnClicked65535();
};
