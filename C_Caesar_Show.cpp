// C_Caesar_Show.cpp: 实现文件
//

#include "stdafx.h"
#include "加解密.h"
#include "C_Caesar_Show.h"
#include "afxdialogex.h"
#include "Resource.h"

// C_Caesar_Show 对话框

IMPLEMENT_DYNAMIC(C_Caesar_Show, CDialogEx)

C_Caesar_Show::C_Caesar_Show(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Caesar_show, pParent)
{

}

C_Caesar_Show::~C_Caesar_Show()
{
}

void C_Caesar_Show::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ciphertextB, ciphertextB);
	DDX_Text(pDX, IDC_cleartextB, cleartextB);

}


BEGIN_MESSAGE_MAP(C_Caesar_Show, CDialogEx)
END_MESSAGE_MAP()


// C_Caesar_Show 消息处理程序


