#pragma once


// CDialogPublic 对话框
#include<Windows.h>
class CDialogPublic : public CDialog
{
	DECLARE_DYNAMIC(CDialogPublic)

public:
	CDialogPublic(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogPublic();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGpublic };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_com;
	CEdit m_edit1;
	CEdit m_edit2;
	CEdit m_edit3;
	CEdit m_edit4;
	CEdit m_edit5;
	CEdit m_edit6;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	virtual BOOL OnInitDialog();
};
