#pragma once


// CDialog_chat 对话框

class CDialog_chat : public CDialog
{
	DECLARE_DYNAMIC(CDialog_chat)

public:
	CDialog_chat(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialog_chat();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_chat };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list1;
	CListCtrl m_list2;
	CRichEditCtrl m_edit1;
	CRichEditCtrl m_edit2;
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	CImageList   m_ImageList1;
	CImageList   m_ImageList2;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
};
