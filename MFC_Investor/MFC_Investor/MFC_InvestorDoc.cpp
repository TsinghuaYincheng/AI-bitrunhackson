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

// MFC_InvestorDoc.cpp: CMFCInvestorDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFC_Investor.h"
#endif

#include "MFC_InvestorDoc.h"
#include "CntrItem.h"
#include "SrvrItem.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCInvestorDoc

IMPLEMENT_DYNCREATE(CMFCInvestorDoc, COleServerDocEx)

BEGIN_MESSAGE_MAP(CMFCInvestorDoc, COleServerDocEx)
	// 启用默认的 OLE 容器实现
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, &COleServerDocEx::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, &COleServerDocEx::OnUpdatePasteLinkMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, &COleServerDocEx::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, &COleServerDocEx::OnEditConvert)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, &COleServerDocEx::OnUpdateEditLinksMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_VERB_POPUP, &CMFCInvestorDoc::OnUpdateObjectVerbPopup)
	ON_COMMAND(ID_OLE_EDIT_LINKS, &COleServerDocEx::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, &COleServerDocEx::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_FILE_SEND_MAIL, &CMFCInvestorDoc::OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, &CMFCInvestorDoc::OnUpdateFileSendMail)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMFCInvestorDoc, COleServerDocEx)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_IMFC_Investor 的支持来支持类型安全绑定
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {7d9f62fc-ba2d-4095-82ef-f3adbbc323fb}
static const IID IID_IMFC_Investor =
{0x7d9f62fc,0xba2d,0x4095,{0x82,0xef,0xf3,0xad,0xbb,0xc3,0x23,0xfb}};

BEGIN_INTERFACE_MAP(CMFCInvestorDoc, COleServerDocEx)
	INTERFACE_PART(CMFCInvestorDoc, IID_IMFC_Investor, Dispatch)
END_INTERFACE_MAP()


// CMFCInvestorDoc 构造/析构

CMFCInvestorDoc::CMFCInvestorDoc()
{
	// 使用 OLE 复合文件
	EnableCompoundFile();

	// TODO: 在此添加一次性构造代码

	EnableAutomation();

	AfxOleLockApp();
}

CMFCInvestorDoc::~CMFCInvestorDoc()
{
	AfxOleUnlockApp();
}

BOOL CMFCInvestorDoc::OnNewDocument()
{
	if (!COleServerDocEx::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}


// CMFCInvestorDoc 服务器实现

COleServerItem* CMFCInvestorDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem 由框架调用以获取与该文档关联的 COleServerItem。
	//  只在必要时才调用它。

	CMFCInvestorServerItem* pItem = new CMFCInvestorServerItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}


// CMFCInvestorDoc 活动文档服务器实现

CDocObjectServer *CMFCInvestorDoc::GetDocObjectServer(LPOLEDOCUMENTSITE pDocSite)
{
	return new CDocObjectServer(this, pDocSite);
}




// CMFCInvestorDoc 序列化

void CMFCInvestorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}

	// 调用基类 COleServerDocEx 会启用序列化
	//  容器文档的 COleClientItem 对象的序列化。
	COleServerDocEx::Serialize(ar);
	// 激活第一个
	if (!ar.IsStoring())
	{
		POSITION posItem = GetStartPosition();
		if (posItem != nullptr)
		{
			CDocItem* pItem = GetNextItem(posItem);
			POSITION posView = GetFirstViewPosition();
			COleDocObjectItem *pDocObjectItem = DYNAMIC_DOWNCAST(COleDocObjectItem, pItem);
			if (posView != nullptr && pDocObjectItem != nullptr)
			{
				CView* pView = GetNextView(posView);
				pDocObjectItem->DoVerb(OLEIVERB_SHOW, pView);
			}
		}
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMFCInvestorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMFCInvestorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMFCInvestorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCInvestorDoc 诊断

#ifdef _DEBUG
void CMFCInvestorDoc::AssertValid() const
{
	COleServerDocEx::AssertValid();
}

void CMFCInvestorDoc::Dump(CDumpContext& dc) const
{
	COleServerDocEx::Dump(dc);
}
#endif //_DEBUG


// CMFCInvestorDoc 命令
