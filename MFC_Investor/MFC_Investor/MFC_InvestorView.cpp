// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// MFC_InvestorView.cpp: CMFCInvestorView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFC_Investor.h"
#endif

#include "MFC_InvestorDoc.h"
#include "CntrItem.h"
#include "resource.h"
#include "MFC_InvestorView.h"
#include"CClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCInvestorView

IMPLEMENT_DYNCREATE(CMFCInvestorView, CHtmlView)

BEGIN_MESSAGE_MAP(CMFCInvestorView, CHtmlView)
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_OLE_INSERT_NEW, &CMFCInvestorView::OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, &CMFCInvestorView::OnCancelEditCntr)
	ON_COMMAND(ID_FILE_PRINT, &CMFCInvestorView::OnFilePrint)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, &CMFCInvestorView::OnCancelEditSrvr)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CHtmlView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCInvestorView::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &OnFilePrintPreviewUIUpdate)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON2, &CMFCInvestorView::OnButton2)
	ON_COMMAND(ID_BUTTON3, &CMFCInvestorView::OnButton3)
	ON_COMMAND(ID_BUTTON4, &CMFCInvestorView::OnButton4)
	ON_COMMAND(ID_BUTTON5, &CMFCInvestorView::OnButton5)
	ON_COMMAND(ID_BUTTON6, &CMFCInvestorView::OnButton6)
	ON_COMMAND(ID_BUTTON7, &CMFCInvestorView::OnButton7)
	ON_COMMAND(ID_BUTTON8, &CMFCInvestorView::OnButton8)
	ON_COMMAND(ID_BUTTON9, &CMFCInvestorView::OnButton9)
	ON_COMMAND(ID_BUTTON10, &CMFCInvestorView::OnButton10)
	ON_COMMAND(ID_BUTTON11, &CMFCInvestorView::OnButton11)
	ON_COMMAND(ID_BUTTON12, &CMFCInvestorView::OnButton12)
	ON_COMMAND(ID_BUTTON13, &CMFCInvestorView::OnButton13)
	ON_COMMAND(ID_BUTTON14, &CMFCInvestorView::OnButton14)
END_MESSAGE_MAP()

// CMFCInvestorView 构造/析构

CMFCInvestorView::CMFCInvestorView()
{
	EnableActiveAccessibility();
	m_pSelection = nullptr;
	// TODO: 在此处添加构造代码

}

CMFCInvestorView::~CMFCInvestorView()
{
}

BOOL CMFCInvestorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CHtmlView::PreCreateWindow(cs);
}

void CMFCInvestorView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();
	wchar_t pBuf[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, pBuf);
	CString mypath = pBuf;
	mypath += "\\2.swf";
	//MessageBox(mypath, mypath, 0);
	Navigate2(mypath, 0, 0, 0, 0, 0);
	//Navigate2(_T("http://www.msdn.microsoft.com/visualc/"),0,0,0,0);

	// TODO: 写入最终选择模式代码之后移除此代码
	m_pSelection = nullptr;    // 初始化所选内容
	OnPipeConnect();

}


// CMFCInvestorView 打印

void CMFCInvestorView::OnFilePrintPreviewUIUpdate(CCmdUI* pCmdUI)
{
	if (!pCmdUI)
		return;

	if (m_pSelection != nullptr)
	{
		DWORD dwStatus = 0;
		//if (SUCCEEDED(m_pSelection->QueryCommand(OLECMDID_PRINTPREVIEW, &dwStatus)) &&
		//	dwStatus & OLECMDF_ENABLED)
		{
				pCmdUI->Enable(TRUE);
				return;
		}
	}
	pCmdUI->Enable(FALSE);
}

void CMFCInvestorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}


void CMFCInvestorView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: 在此处添加自定义打印代码
	if(pInfo->m_bDocObject)
		COleDocObjectItem::OnPrint(this, pInfo, TRUE);
	else
		CView::OnPrint(pDC, pInfo);
}

void CMFCInvestorView::OnDestroy()
{
	// 析构时停用此项；这在
	// 使用拆分器视图时非常重要 
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != nullptr && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == nullptr);
   }
   CHtmlView::OnDestroy();
}



// OLE 客户端支持和命令

BOOL CMFCInvestorView::IsSelected(const CObject* pDocItem) const
{
	//下面的实现是足够的，如果所选内容包括
	// CMFCInvestorInPlaceFrame 对象，则以下实现就足够了。若要处理其他选择机制，
	//  则应替换此处的实现

	// TODO: 实现对所选 OLE 客户端项进行测试的函数

	return pDocItem == m_pSelection;
}

void CMFCInvestorView::OnInsertObject()
{
	// 调用标准的“插入对象”对话框以获得有关
	//  对于新的 CMFCInvestorInPlaceFrame 对象
	COleInsertDialog dlg;
	if (dlg.DoModal(COleInsertDialog::DocObjectsOnly) != IDOK)
		return;

	BeginWaitCursor();

	CMFCInvestorInPlaceFrame* pItem = nullptr;
	TRY
	{
		// 创建与此文档相连接的新项
		CMFCInvestorDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CMFCInvestorInPlaceFrame(pDoc);
		ASSERT_VALID(pItem);

		// 通过对话框数据初始化该项
		if (!dlg.CreateItem(pItem))
			AfxThrowMemoryException();  // 任何异常都将导致该结果
		ASSERT_VALID(pItem);

		pItem->DoVerb(OLEIVERB_SHOW, this);

		ASSERT_VALID(pItem);
		// 作为任意用户界面设计，这会将所选内容
		//  设置为插入的最后一项

		// TODO: 重新实现所选内容，使其适合于您的应用程序
		m_pSelection = pItem;   // 将所选内容设置为插入的最后一项
		pDoc->UpdateAllViews(nullptr);
	}
	CATCH(CException, e)
	{
		if (pItem != nullptr)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();
		}
		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH

	EndWaitCursor();
}

// 以下命令处理程序提供了标准键盘
//  用户界面以取消就地编辑会话。  此处，
//  容器(而不是服务器)将导致停用
void CMFCInvestorView::OnCancelEditCntr()
{
	// 关闭此视图中的任何就地活动项。
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != nullptr)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == nullptr);
}

// 在就地编辑一个对象时，容器需要对 OnSetFocus 和 OnSize 
//  进行特殊处理
void CMFCInvestorView::OnSetFocus(CWnd* pOldWnd)
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != nullptr &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// 如果该项处于同一视图中，则需要将焦点设置到该项
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != nullptr)
		{
			pWnd->SetFocus();   // 不要调用基类
			return;
		}
	}

	CHtmlView::OnSetFocus(pOldWnd);
}

void CMFCInvestorView::OnSize(UINT nType, int cx, int cy)
{
	CHtmlView::OnSize(nType, cx, cy);
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != nullptr)
		pActiveItem->SetItemRects();
}

void CMFCInvestorView::OnFilePrint()
{
	//默认情况下，要求活动文档使用 IOleCommandTarget 打印自身。
	//如果不需要此行为，
	//请移除对 COleDocObjectItem::DoDefaultPrinting 调用。
	//如果由于某种原因调用失败，则将尝试使用 IPrint 接口打印
	//该文档对象。
	CPrintInfo printInfo;
	ASSERT(printInfo.m_pPD != nullptr);
	if (S_OK == COleDocObjectItem::DoDefaultPrinting(this, &printInfo))
		return;

	CView::OnFilePrint();

}


void CMFCInvestorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCInvestorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// OLE 服务器支持

// 以下命令处理程序提供了标准键盘
//  用户界面以取消就地编辑会话。  此处，
//  服务器(而不是容器)将导致停用
void CMFCInvestorView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}


// CMFCInvestorView 诊断

#ifdef _DEBUG
void CMFCInvestorView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CMFCInvestorView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CMFCInvestorDoc* CMFCInvestorView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCInvestorDoc)));
	return (CMFCInvestorDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCInvestorView 消息处理程序


void CMFCInvestorView::OnButton2()
{
	// TODO: 在此添加命令处理程序代码
	INT_PTR nRes;
	CDialogPrivateKey   tipDlg;           // 构造对话框类CTipDlg的实例   
	nRes = tipDlg.DoModal();
}


void CMFCInvestorView::OnButton3()
{
	// TODO: 在此添加命令处理程序代码
	INT_PTR nRes;
	CDialogPassword  tipDlg;           // 构造对话框类CTipDlg的实例   
	nRes = tipDlg.DoModal();
}


void CMFCInvestorView::OnButton4()
{
	// TODO: 在此添加命令处理程序代码
	INT_PTR nRes;
	CDialogPeople   tipDlg;           // 构造对话框类CTipDlg的实例   
	nRes = tipDlg.DoModal();
}


void CMFCInvestorView::OnButton5()
{
	// TODO: 在此添加命令处理程序代码
	INT_PTR nRes;
	CDialogpasswordTools   tipDlg;           // 构造对话框类CTipDlg的实例   
	nRes = tipDlg.DoModal();
}


void CMFCInvestorView::OnButton6()
{
	// TODO: 在此添加命令处理程序代码
	INT_PTR nRes;
	CDialogOutput tipDlg;           // 构造对话框类CTipDlg的实例   
	nRes = tipDlg.DoModal();
}


void CMFCInvestorView::OnButton7()
{
	// TODO: 在此添加命令处理程序代码
	INT_PTR nRes;
	CDialogInput   tipDlg;           // 构造对话框类CTipDlg的实例   
	nRes = tipDlg.DoModal();
}


void CMFCInvestorView::OnButton8()
{
	// TODO: 在此添加命令处理程序代码
	INT_PTR nRes;
	CDialog_projects  tipDlg;           // 构造对话框类CTipDlg的实例   
	nRes = tipDlg.DoModal();
}


void CMFCInvestorView::OnButton9()
{
	// TODO: 在此添加命令处理程序代码
	INT_PTR nRes;
	CDialog_chat   tipDlg;           // 构造对话框类CTipDlg的实例   
	nRes = tipDlg.DoModal();
}


void CMFCInvestorView::OnButton10()
{
	// TODO: 在此添加命令处理程序代码
	INT_PTR nRes;
	CDialogEAA  tipDlg;           // 构造对话框类CTipDlg的实例   
	nRes = tipDlg.DoModal();
}


void CMFCInvestorView::OnButton11()
{
	// TODO: 在此添加命令处理程序代码
	INT_PTR nRes;
	CDialogViewCost   tipDlg;           // 构造对话框类CTipDlg的实例   
	nRes = tipDlg.DoModal();
}


void CMFCInvestorView::OnButton12()
{
	// TODO: 在此添加命令处理程序代码
	INT_PTR nRes;
	CDialogdispute   tipDlg;           // 构造对话框类CTipDlg的实例   
	nRes = tipDlg.DoModal();
}


void CMFCInvestorView::OnButton13()
{
	// TODO: 在此添加命令处理程序代码
	INT_PTR nRes;
	CDialogShareholders  tipDlg;           // 构造对话框类CTipDlg的实例   
	nRes = tipDlg.DoModal();
}


void CMFCInvestorView::OnButton14()
{
	// TODO: 在此添加命令处理程序代码
	INT_PTR nRes;
	CDialogViewAllMoney   tipDlg;           // 构造对话框类CTipDlg的实例   
	nRes = tipDlg.DoModal();
}
