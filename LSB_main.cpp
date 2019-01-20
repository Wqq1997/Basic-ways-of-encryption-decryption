// LSB_main.cpp: 实现文件
//

#include "stdafx.h"
#include "加解密.h"
#include "LSB_main.h"
#include "afxdialogex.h"
#include "LSB_cipherdlg.h"
#include "LSB_cleardlg.h"


// LSB_main 对话框

IMPLEMENT_DYNAMIC(LSB_main, CDialogEx)

LSB_main::LSB_main(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LSB_main, pParent)
{

}

LSB_main::~LSB_main()
{
}

void LSB_main::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LSB_main, CDialogEx)
	ON_BN_CLICKED(IDC_LSB_cipher, &LSB_main::OnBnClickedLsbcipher)
	ON_BN_CLICKED(IDC_LSB_clear, &LSB_main::OnBnClickedLsbclear)
END_MESSAGE_MAP()


// LSB_main 消息处理程序


void LSB_main::OnBnClickedLsbcipher()
{
	// TODO: 在此添加控件通知处理程序代码
	LSB_cipherdlg dlg;
	dlg.DoModal();
}


void LSB_main::OnBnClickedLsbclear()
{
	// TODO: 在此添加控件通知处理程序代码
	LSB_cleardlg dlg;
	dlg.DoModal();

}
