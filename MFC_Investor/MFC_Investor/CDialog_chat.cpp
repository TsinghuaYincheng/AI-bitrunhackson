// CDialog_chat.cpp: 实现文件
//

#include "stdafx.h"
#include "MFC_Investor.h"
#include "CDialog_chat.h"
#include "afxdialogex.h"


// CDialog_chat 对话框

IMPLEMENT_DYNAMIC(CDialog_chat, CDialog)

CDialog_chat::CDialog_chat(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_chat, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif
	AfxInitRichEdit(); //richedit的初始化
}

CDialog_chat::~CDialog_chat()
{
}

void CDialog_chat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_LIST2, m_list2);
	DDX_Control(pDX, IDC_RICHEDIT21, m_edit1);
	DDX_Control(pDX, IDC_RICHEDIT22, m_edit2);
}


BEGIN_MESSAGE_MAP(CDialog_chat, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog_chat::OnBnClickedButton1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CDialog_chat::OnNMClickList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CDialog_chat::OnNMClickList2)
END_MESSAGE_MAP()


// CDialog_chat 消息处理程序


void CDialog_chat::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	// TODO: 在此添加控件通知处理程序代码
	m_edit1.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	CString str;
	m_edit1.SetSel(-1, -1);
	CString sendstr;
	m_edit2.GetWindowText(sendstr);
	sendstr = L"投资人尹成说: " + sendstr;
	m_edit2.SetWindowText(L"");
	m_edit1.ReplaceSel(sendstr + L"\r\n");


}


BOOL CDialog_chat::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// TODO:  在此添加额外的初始化
	this->SetWindowTextW(L"投资人群聊");
	HICON myIcon[8];
	for (int i = 0; i < 8; i++)
		myIcon[i] = AfxGetApp()->LoadIcon(IDR_MAINFRAME);//这里使用LoadIcon获得HICON  其中IDR_MAINFRAME为系统默认图标
	m_ImageList1.Create(32, 32, ILC_COLOR32, 4, 4);
	for (int i = 0; i<8; i++)
		m_ImageList1.Add(myIcon[i]);
	m_list1.SetImageList(&m_ImageList1, LVSIL_NORMAL);
	for (int i = 0; i < 1; i++)
	{
		LVITEM lvitem;
		lvitem.mask = LVIF_IMAGE | LVIF_TEXT;
		lvitem.iItem = i;
		lvitem.pszText = L"VNT";
		lvitem.iImage = i;
		lvitem.iSubItem = 0;
		m_list1.InsertItem(&lvitem);



		// ((CListCtrl *) lParam)->InsertItem(i,m_strTitle, i);
	}
	for (int i = 0; i < 1; i++)
	{
		LVITEM lvitem;
		lvitem.mask = LVIF_IMAGE | LVIF_TEXT;
		lvitem.iItem = i;
		lvitem.pszText = L"Nervos";
		lvitem.iImage = i;
		lvitem.iSubItem = 0;
		m_list1.InsertItem(&lvitem);



		// ((CListCtrl *) lParam)->InsertItem(i,m_strTitle, i);
	}
	for (int i = 0; i < 1; i++)
	{
		LVITEM lvitem;
		lvitem.mask = LVIF_IMAGE | LVIF_TEXT;
		lvitem.iItem = i;
		lvitem.pszText = L"NKN";
		lvitem.iImage = i;
		lvitem.iSubItem = 0;
		m_list1.InsertItem(&lvitem);



		// ((CListCtrl *) lParam)->InsertItem(i,m_strTitle, i);
	}
	
	{
		m_list2.DeleteAllItems();
		HICON myIcon[8];
		for (int i = 0; i < 8; i++)
			myIcon[i] = AfxGetApp()->LoadIcon(IDR_MAINFRAME);//这里使用LoadIcon获得HICON  其中IDR_MAINFRAME为系统默认图标
		m_ImageList2.Create(32, 32, ILC_COLOR32, 4, 4);
		for (int i = 0; i<8; i++)
			m_ImageList2.Add(myIcon[i]);
		m_list2.SetImageList(&m_ImageList2, LVSIL_NORMAL);
		for (int i = 0; i < 1; i++)
		{
			LVITEM lvitem;
			lvitem.mask = LVIF_IMAGE | LVIF_TEXT;
			lvitem.iItem = i;
			lvitem.pszText = L"投资人尹成";
			lvitem.iImage = i;
			lvitem.iSubItem = 0;
			m_list2.InsertItem(&lvitem);



			// ((CListCtrl *) lParam)->InsertItem(i,m_strTitle, i);
		}
		for (int i = 0; i < 1; i++)
		{
			LVITEM lvitem;
			lvitem.mask = LVIF_IMAGE | LVIF_TEXT;
			lvitem.iItem = i;
			lvitem.pszText = L"投资人朱胡美";
			lvitem.iImage = i;
			lvitem.iSubItem = 0;
			m_list2.InsertItem(&lvitem);



			// ((CListCtrl *) lParam)->InsertItem(i,m_strTitle, i);
		}
	}
	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialog_chat::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	int nId;
	//首先得到点击的位置
	POSITION pos = m_list1.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(L"请至少选择一项", L"提示", MB_ICONEXCLAMATION);
		return;
	}
	//得到行号，通过POSITION转化
	nId = (int)m_list1.GetNextSelectedItem(pos);
	str.Format(L"%d", nId);
	//MessageBox(L"您选中第" + str + L"行");
	//得到列中的内容（0表示第一列，同理1,2,3...表示第二，三，四...列）
	str = m_list1.GetItemText(nId, 0);
	//MessageBox(str);
	if (str==L"MKN")
	{

		{
			m_list2.DeleteAllItems();
			HICON myIcon[8];
			for (int i = 0; i < 8; i++)
				myIcon[i] = AfxGetApp()->LoadIcon(IDR_MAINFRAME);//这里使用LoadIcon获得HICON  其中IDR_MAINFRAME为系统默认图标
			m_ImageList2.Create(32, 32, ILC_COLOR32, 4, 4);
			for (int i = 0; i<8; i++)
				m_ImageList2.Add(myIcon[i]);
			m_list2.SetImageList(&m_ImageList2, LVSIL_NORMAL);
			for (int i = 0; i < 1; i++)
			{
				LVITEM lvitem;
				lvitem.mask = LVIF_IMAGE | LVIF_TEXT;
				lvitem.iItem = i;
				lvitem.pszText = L"投资人尹成";
				lvitem.iImage = i;
				lvitem.iSubItem = 0;
				m_list2.InsertItem(&lvitem);



				// ((CListCtrl *) lParam)->InsertItem(i,m_strTitle, i);
			}
			for (int i = 0; i < 1; i++)
			{
				LVITEM lvitem;
				lvitem.mask = LVIF_IMAGE | LVIF_TEXT;
				lvitem.iItem = i;
				lvitem.pszText = L"投资人朱胡美";
				lvitem.iImage = i;
				lvitem.iSubItem = 0;
				m_list2.InsertItem(&lvitem);



				// ((CListCtrl *) lParam)->InsertItem(i,m_strTitle, i);
			}
		}
	}
	else if (str == "Nervos")
	{
		{
			m_list2.DeleteAllItems();
			HICON myIcon[8];
			for (int i = 0; i < 8; i++)
				myIcon[i] = AfxGetApp()->LoadIcon(IDR_MAINFRAME);//这里使用LoadIcon获得HICON  其中IDR_MAINFRAME为系统默认图标
			m_ImageList2.Create(32, 32, ILC_COLOR32, 4, 4);
			for (int i = 0; i<8; i++)
				m_ImageList2.Add(myIcon[i]);
			m_list2.SetImageList(&m_ImageList2, LVSIL_NORMAL);
			for (int i = 0; i < 1; i++)
			{
				LVITEM lvitem;
				lvitem.mask = LVIF_IMAGE | LVIF_TEXT;
				lvitem.iItem = i;
				lvitem.pszText = L"投资人尹成";
				lvitem.iImage = i;
				lvitem.iSubItem = 0;
				m_list2.InsertItem(&lvitem);



				// ((CListCtrl *) lParam)->InsertItem(i,m_strTitle, i);
			}
			for (int i = 0; i < 1; i++)
			{
				LVITEM lvitem;
				lvitem.mask = LVIF_IMAGE | LVIF_TEXT;
				lvitem.iItem = i;
				lvitem.pszText = L"投资人张小虎";
				lvitem.iImage = i;
				lvitem.iSubItem = 0;
				m_list2.InsertItem(&lvitem);



				// ((CListCtrl *) lParam)->InsertItem(i,m_strTitle, i);
			}
			for (int i = 0; i < 1; i++)
			{
				LVITEM lvitem;
				lvitem.mask = LVIF_IMAGE | LVIF_TEXT;
				lvitem.iItem = i;
				lvitem.pszText = L"投资人王晓梅";
				lvitem.iImage = i;
				lvitem.iSubItem = 0;
				m_list2.InsertItem(&lvitem);



				// ((CListCtrl *) lParam)->InsertItem(i,m_strTitle, i);
			}
			for (int i = 0; i < 1; i++)
			{
				LVITEM lvitem;
				lvitem.mask = LVIF_IMAGE | LVIF_TEXT;
				lvitem.iItem = i;
				lvitem.pszText = L"投资人王晓虎";
				lvitem.iImage = i;
				lvitem.iSubItem = 0;
				m_list2.InsertItem(&lvitem);



				// ((CListCtrl *) lParam)->InsertItem(i,m_strTitle, i);
			}
		}
	}
	else {
		{
			m_list2.DeleteAllItems();
			HICON myIcon[8];
			for (int i = 0; i < 8; i++)
				myIcon[i] = AfxGetApp()->LoadIcon(IDR_MAINFRAME);//这里使用LoadIcon获得HICON  其中IDR_MAINFRAME为系统默认图标
			m_ImageList2.Create(32, 32, ILC_COLOR32, 4, 4);
			for (int i = 0; i<8; i++)
				m_ImageList2.Add(myIcon[i]);
			m_list2.SetImageList(&m_ImageList2, LVSIL_NORMAL);
			for (int i = 0; i < 1; i++)
			{
				LVITEM lvitem;
				lvitem.mask = LVIF_IMAGE | LVIF_TEXT;
				lvitem.iItem = i;
				lvitem.pszText = L"投资人尹成";
				lvitem.iImage = i;
				lvitem.iSubItem = 0;
				m_list2.InsertItem(&lvitem);



				// ((CListCtrl *) lParam)->InsertItem(i,m_strTitle, i);
			}
			for (int i = 0; i < 1; i++)
			{
				LVITEM lvitem;
				lvitem.mask = LVIF_IMAGE | LVIF_TEXT;
				lvitem.iItem = i;
				lvitem.pszText = L"投资人张虎";
				lvitem.iImage = i;
				lvitem.iSubItem = 0;
				m_list2.InsertItem(&lvitem);



				// ((CListCtrl *) lParam)->InsertItem(i,m_strTitle, i);
			}
			for (int i = 0; i < 1; i++)
			{
				LVITEM lvitem;
				lvitem.mask = LVIF_IMAGE | LVIF_TEXT;
				lvitem.iItem = i;
				lvitem.pszText = L"投资人王涛";
				lvitem.iImage = i;
				lvitem.iSubItem = 0;
				m_list2.InsertItem(&lvitem);



				// ((CListCtrl *) lParam)->InsertItem(i,m_strTitle, i);
			}
		}

	}



	*pResult = 0;
}


void CDialog_chat::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
