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

// SrvrItem.cpp: CMFCInvestorServerItem 类的实现
//

#include "stdafx.h"
#include "MFC_Investor.h"

#include "MFC_InvestorDoc.h"
#include "SrvrItem.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCInvestorServerItem 实现

IMPLEMENT_DYNAMIC(CMFCInvestorServerItem, COleServerItem)

CMFCInvestorServerItem::CMFCInvestorServerItem(CMFCInvestorDoc* pContainerDoc)
	: COleServerItem(pContainerDoc, TRUE)
{
	// TODO: 在此添加一次性构造代码
	//  (如将附加剪贴板格式添加到项的数据源中)
}

CMFCInvestorServerItem::~CMFCInvestorServerItem()
{
	// TODO: 在此处添加清理代码
}

void CMFCInvestorServerItem::Serialize(CArchive& ar)
{
	// 如果将该项复制到剪贴板中，则框架将调用 CMFCInvestorServerItem::Serialize。
	//  这可以
	//  通过 OLE 回调 OnGetClipboardData 来自动执行。
	//  对于嵌入项，默认最好直接委托给文档的 Serialize 函数。
	//  如果支持链接，则只需序列化
	//  文档的一部分。

	if (!IsLinkedItem())
	{
		CMFCInvestorDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (pDoc)
			pDoc->Serialize(ar);
	}
}

BOOL CMFCInvestorServerItem::OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize)
{
	// 大多数与此类似的应用程序只处理绘制内容
	//  项目的方面。如果希望支持其他方面，如
	//  DVASPECT_THUMBNAIL (通过重写 OnDrawEx)，则此
	//  应修改 OnGetExtent 的实现以处理
	//  其他方面。

	if (dwDrawAspect != DVASPECT_CONTENT)
		return COleServerItem::OnGetExtent(dwDrawAspect, rSize);

	// 调用 CMFCInvestorServerItem::OnGetExtent 以便获取整个项的
	//  HIMETRIC 单元表示的范围。  此处的默认实现
	//  只返回单元的硬编码数字。

	// TODO: 替换此任意大小

	rSize = CSize(3000, 3000);   // 3000 x 3000 HIMETRIC 单元

	return TRUE;
}

BOOL CMFCInvestorServerItem::OnDraw(CDC* pDC, CSize& rSize)
{
	if (!pDC)
		return FALSE;

	// 如果使用 rSize，则将此移除
	UNREFERENCED_PARAMETER(rSize);

	// TODO: 设置映射模式和范围
	//  (此范围通常与从 OnGetExtent 返回的大小相同)
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowOrg(0,0);
	pDC->SetWindowExt(3000, 3000);

	// TODO:  在此处添加绘制代码。  也可以填充 HIMETRIC 范围。
	//  所有绘制都将在图元文件设备上下文(pDC)中进行。

	// TODO: 同时绘制嵌入的 CMFCInvestorInPlaceFrame 对象。

	// 以下代码将在任意位置绘制第一个项。

	// TODO: 完成真正的绘制代码后，将移除此代码

	CMFCInvestorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return FALSE;

	POSITION pos = pDoc->GetStartPosition();
	CMFCInvestorInPlaceFrame* pItem = DYNAMIC_DOWNCAST(CMFCInvestorInPlaceFrame, pDoc->GetNextClientItem(pos));
	if (pItem != nullptr)
		pItem->Draw(pDC, CRect(10, 10, 1010, 1010));
	return TRUE;
}


// CMFCInvestorServerItem 诊断

#ifdef _DEBUG
void CMFCInvestorServerItem::AssertValid() const
{
	COleServerItem::AssertValid();
}

void CMFCInvestorServerItem::Dump(CDumpContext& dc) const
{
	COleServerItem::Dump(dc);
}
#endif

