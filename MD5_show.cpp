// MD5_show.cpp: 实现文件
//

#include "stdafx.h"
#include "加解密.h"
#include "MD5_show.h"
#include "afxdialogex.h"
#include "Resource.h"

// MD5_show 对话框

IMPLEMENT_DYNAMIC(MD5_show, CDialogEx)

MD5_show::MD5_show(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MD5_show, pParent)
{

}

MD5_show::~MD5_show()
{
}

void MD5_show::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MD5_ciphertext, ciphertextB);

}


BEGIN_MESSAGE_MAP(MD5_show, CDialogEx)
END_MESSAGE_MAP()


// MD5_show 消息处理程序
