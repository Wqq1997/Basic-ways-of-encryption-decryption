// des_show.cpp: 实现文件
//

#include "stdafx.h"
#include "加解密.h"
#include "des_show.h"
#include "afxdialogex.h"
#include "Resource.h"

// des_show 对话框

IMPLEMENT_DYNAMIC(des_show, CDialogEx)

des_show::des_show(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_des_show, pParent)
{
}

des_show::~des_show()
{
}

void des_show::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_des_cleartextB, cleartextB);
	DDX_Text(pDX, IDC_des_ciphertextB, ciphertextB);
}


BEGIN_MESSAGE_MAP(des_show, CDialogEx)
END_MESSAGE_MAP()


// des_show 消息处理程序
