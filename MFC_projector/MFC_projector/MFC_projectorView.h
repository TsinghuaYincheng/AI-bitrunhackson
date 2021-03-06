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

// MFC_projectorView.h: CMFCprojectorView 类的接口
//

#pragma once
#include"CDialogICO.h"
#include<Windows.h>
#include"CDialogViewMoney.h"
#include"CDialogPublic.h"
#include"CDialogViewMoneyView.h"
#include"CDialog_Output.h"
#include"CDialog_input.h"
#include"CDialogViewCost.h"
#include"CMoneyDialog.h"
#include"CDialogFa.h"
#include"CDialigLiao.h"

class CMFCprojectorInPlaceFrame;

class CMFCprojectorView : public CHtmlView
{
protected: // 仅从序列化创建
	CMFCprojectorView();
	DECLARE_DYNCREATE(CMFCprojectorView)

// 特性
public:
	CMFCprojectorDoc* GetDocument() const;
	// m_pSelection 将所选内容保存在当前 CMFCprojectorInPlaceFrame 中。
	// 对于许多应用程序，这种成员变量不足以
	//  表示某个选择，例如在不属于
	//  CMFCprojectorInPlaceFrame 的对象中选定的一个或多个对象。提供这种选择
	//  机制的目的只是帮助入门

	// TODO: 用适合应用程序的选择机制替换此选择机制
	CMFCprojectorInPlaceFrame* m_pSelection;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL IsSelected(const CObject* pDocItem) const;// 容器支持

// 实现
public:
	virtual ~CMFCprojectorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInsertObject();
	afx_msg void OnCancelEditCntr();
	afx_msg void OnFilePrint();
	afx_msg void OnCancelEditSrvr();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnFilePrintPreviewUIUpdate(CCmdUI* pCmdUI);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnButton10();
	afx_msg void OnButton11();
	afx_msg void OnButton9();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton16();
	afx_msg void OnButton17();
	virtual void OnNavigateComplete2(LPCTSTR strURL);
};

#ifndef _DEBUG  // MFC_projectorView.cpp 中的调试版本
inline CMFCprojectorDoc* CMFCprojectorView::GetDocument() const
   { return reinterpret_cast<CMFCprojectorDoc*>(m_pDocument); }
#endif

