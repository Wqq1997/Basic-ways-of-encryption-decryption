// RSA_show.cpp: 实现文件
//

#include "stdafx.h"
#include "加解密.h"
#include "RSA_show.h"
#include "afxdialogex.h"


// RSA_show 对话框

IMPLEMENT_DYNAMIC(RSA_show, CDialogEx)

RSA_show::RSA_show(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RSA_show, pParent)
{

}

RSA_show::~RSA_show()
{
}

void RSA_show::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_E, e2);
	DDX_Text(pDX, IDC_N1, n2);
	DDX_Text(pDX, IDC_N2, n2);
	DDX_Text(pDX, IDC_D, d2);

	DDX_Text(pDX, IDC_RSA_ciphertextB, ciphertextB);
	DDX_Text(pDX, IDC_RSA_cleartextB, cleartextB);

}


BEGIN_MESSAGE_MAP(RSA_show, CDialogEx)
	ON_EN_CHANGE(IDC_RSA_cleartextB, &RSA_show::OnEnChangeRsacleartextb)
END_MESSAGE_MAP()


// RSA_show 消息处理程序


void RSA_show::OnEnChangeRsacleartextb()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
