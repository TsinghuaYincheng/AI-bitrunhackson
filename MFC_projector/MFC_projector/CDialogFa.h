#pragma once


// CDialogFa 对话框

class CDialogFa : public CDialog
{
	DECLARE_DYNAMIC(CDialogFa)

public:
	CDialogFa(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogFa();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_fa };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit1;
	CEdit m_edit2;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
//	virtual BOOL OnInitDialog();
	virtual BOOL OnInitDialog();
};
