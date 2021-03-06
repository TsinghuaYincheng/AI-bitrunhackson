#pragma once
#include<vector>
using namespace std;
#include<ctime>

// CDialogPeople 对话框

class CDialogPeople : public CDialog
{
	DECLARE_DYNAMIC(CDialogPeople)

public:
	CDialogPeople(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogPeople();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_people };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit;
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	CImageList  m_ImageList;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLvnDeleteitemList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemdblclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton2();
};
