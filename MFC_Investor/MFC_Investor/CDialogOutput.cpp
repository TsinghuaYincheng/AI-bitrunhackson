// CDialogOutput.cpp: 实现文件
//

#include "stdafx.h"
#include "MFC_Investor.h"
#include "CDialogOutput.h"
#include "afxdialogex.h"


// CDialogOutput 对话框

IMPLEMENT_DYNAMIC(CDialogOutput, CDialogEx)

CDialogOutput::CDialogOutput(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_OUTPUT, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CDialogOutput::~CDialogOutput()
{
}

void CDialogOutput::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
}


BEGIN_MESSAGE_MAP(CDialogOutput, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogOutput::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialogOutput::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDialogOutput 消息处理程序


void CDialogOutput::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(L"付款成功", L"付款成功",0);
}


void CDialogOutput::OnBnClickedButton2()
{
	m_edit1.SetWindowTextW(L"");
	m_edit2.SetWindowTextW(L"");
	// TODO: 在此添加控件通知处理程序代码
}
