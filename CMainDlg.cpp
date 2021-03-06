// CMainDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "加解密.h"
#include "CMainDlg.h"
#include "afxdialogex.h"
#include "C_Caesar_Main.h"
#include "permutation_main.h"
#include "des_main.h"
#include "RSA_main.h"
#include "MD5_main.h"
#include "LSB_main.h"

// CMainDlg 对话框

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_maindlg, pParent)
{

}

CMainDlg::~CMainDlg()
{
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_BN_CLICKED(IDC_Caesar, &CMainDlg::OnBnClickedCaesar)
	ON_BN_CLICKED(IDC_Permutation, &CMainDlg::OnBnClickedPermutation)
	ON_BN_CLICKED(IDC_des, &CMainDlg::OnBnClickeddes)
	ON_BN_CLICKED(IDC_RSA, &CMainDlg::OnBnClickedRsa)
	ON_BN_CLICKED(IDC_MD5, &CMainDlg::OnBnClickedMd5)
	ON_BN_CLICKED(IDC_LSB, &CMainDlg::OnBnClickedLsb)
END_MESSAGE_MAP()


// CMainDlg 消息处理程序


void CMainDlg::OnBnClickedCaesar()
{
	// TODO: 在此添加控件通知处理程序代码
	C_Caesar_Main MyDlg;
	MyDlg.DoModal();
}


void CMainDlg::OnBnClickedPermutation()
{
	// TODO: 在此添加控件通知处理程序代码
	permutation_main dlg;
	dlg.DoModal();
}


void CMainDlg::OnBnClickeddes()
{
	// TODO: 在此添加控件通知处理程序代码
	des_main dlg;
	dlg.DoModal();
}


void CMainDlg::OnBnClickedRsa()
{
	// TODO: 在此添加控件通知处理程序代码
	RSA_main dlg;
	dlg.DoModal();
}


void CMainDlg::OnBnClickedMd5()
{
	// TODO: 在此添加控件通知处理程序代码
	MD5_main dlg;
	dlg.DoModal();

}


void CMainDlg::OnBnClickedLsb()
{
	// TODO: 在此添加控件通知处理程序代码
	LSB_main dlg;
	dlg.DoModal();

}
