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

// CntrItem.cpp: CMFCprojectorInPlaceFrame 类的实现
//

#include "stdafx.h"
#include "MFC_projector.h"

#include "MFC_projectorDoc.h"
#include "MFC_projectorView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCprojectorInPlaceFrame 实现

IMPLEMENT_SERIAL(CMFCprojectorInPlaceFrame, COleClientItem, 0)

CMFCprojectorInPlaceFrame::CMFCprojectorInPlaceFrame(CMFCprojectorDoc* pContainer)
	: COleClientItem(pContainer)
{
	// TODO: 在此添加一次性构造代码
}

CMFCprojectorInPlaceFrame::~CMFCprojectorInPlaceFrame()
{
	// TODO: 在此处添加清理代码
}

void CMFCprojectorInPlaceFrame::OnChange(OLE_NOTIFICATION nCode, DWORD dwParam)
{
	ASSERT_VALID(this);

	COleClientItem::OnChange(nCode, dwParam);

	// 在编辑某项时(就地编辑或完全打开进行编辑)，
	//  该项将就其自身状态的更改
	//  或其内容的可视外观状态的更改发送 OnChange 通知。

	// TODO: 通过调用 UpdateAllViews 使该项无效
	//  (包括适合您的应用程序的提示)

	GetDocument()->UpdateAllViews(nullptr);
		// 现在只更新所有视图/无提示
}

BOOL CMFCprojectorInPlaceFrame::OnChangeItemPosition(const CRect& rectPos)
{
	ASSERT_VALID(this);

	// 就地激活期间，CMFCprojectorInPlaceFrame::OnChangeItemPosition
	//  以更改就地窗口的位置。
	//  这通常是由于服务器
	//  文档中的数据更改而导致范围改变或是
	//  就地调整大小所引起的。
	//
	// 此处的默认设置调用基类，该基类将调用
	//  COleClientItem::SetItemRects 以移动项
	//  移动到新的位置。

	if (!COleClientItem::OnChangeItemPosition(rectPos))
		return FALSE;

	// TODO: 更新该项的矩形/范围可能存在的任何缓存

	return TRUE;
}

BOOL CMFCprojectorInPlaceFrame::OnShowControlBars(CFrameWnd* pFrameWnd, BOOL bShow)
{
	CMDIFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CMDIFrameWndEx, pFrameWnd);

	if (pMainFrame != nullptr)
	{
		ASSERT_VALID(pMainFrame);
		return pMainFrame->OnShowPanes(bShow);
	}

	return FALSE;
}


void CMFCprojectorInPlaceFrame::OnActivate()
{
}

void CMFCprojectorInPlaceFrame::OnDeactivateUI(BOOL bUndoable)
{
	COleClientItem::OnDeactivateUI(bUndoable);

	DWORD dwMisc = 0;
	m_lpObject->GetMiscStatus(GetDrawAspect(), &dwMisc);
	if (dwMisc & OLEMISC_INSIDEOUT)
		DoVerb(OLEIVERB_HIDE, nullptr);
}

void CMFCprojectorInPlaceFrame::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	// 首先调用基类以读取 COleClientItem 数据。
	// 因为这样会设置从 [!output CONTAINER_ITEM_CLASS]::GetDocument 返回的 m_pDocument 指针，
	//  CMFCprojectorInPlaceFrame::GetDocument，最好调用
	//  基类 Serialize。
	COleClientItem::Serialize(ar);

	// 现在存储/检索特定于 CMFCprojectorInPlaceFrame 的数据
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

BOOL CMFCprojectorInPlaceFrame::CanActivate()
{
	// 当服务器本身处于就地编辑模式时，就地编辑无效且不受支持。
	//  因此，在这种情况下禁用就地
	//  激活。
	CMFCprojectorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return FALSE;
	ASSERT_KINDOF(COleServerDoc, pDoc);
	if (!pDoc->IsKindOf(RUNTIME_CLASS(COleServerDoc)))
	{
		return FALSE;
	}
	if (pDoc->IsInPlaceActive())
		return FALSE;

	// 否则，依赖默认行为
	return COleClientItem::CanActivate();
}


// CMFCprojectorInPlaceFrame 诊断

#ifdef _DEBUG
void CMFCprojectorInPlaceFrame::AssertValid() const
{
	COleClientItem::AssertValid();
}

void CMFCprojectorInPlaceFrame::Dump(CDumpContext& dc) const
{
	COleClientItem::Dump(dc);
}
#endif

