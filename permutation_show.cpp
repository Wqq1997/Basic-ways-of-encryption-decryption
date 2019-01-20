// permutation_show.cpp: 实现文件
//

#include "stdafx.h"
#include "加解密.h"
#include "permutation_show.h"
#include "afxdialogex.h"


// permutation_show 对话框

IMPLEMENT_DYNAMIC(permutation_show, CDialogEx)

permutation_show::permutation_show(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_permutation_show, pParent)
{

}

permutation_show::~permutation_show()
{
}

void permutation_show::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_permutation_cleartextB, cleartextB);
	DDX_Text(pDX, IDC_permutation_ciphertextB, ciphertextB);
}


BEGIN_MESSAGE_MAP(permutation_show, CDialogEx)
	ON_BN_CLICKED(IDOK, &permutation_show::OnBnClickedOk)
END_MESSAGE_MAP()


// permutation_show 消息处理程序


void permutation_show::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
