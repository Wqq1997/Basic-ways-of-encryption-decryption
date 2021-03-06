// C_Caesar_Main.cpp: 实现文件
//

#include "stdafx.h"
#include "加解密.h"
#include "C_Caesar_Main.h"
#include "afxdialogex.h"
#include "C_Caesar_Show.h"
#include "Resource.h"

// C_Caesar_Main 对话框

IMPLEMENT_DYNAMIC(C_Caesar_Main, CDialogEx)

C_Caesar_Main::C_Caesar_Main(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Caesar_Main, pParent)
{

}

C_Caesar_Main::~C_Caesar_Main()
{
}

void C_Caesar_Main::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_key, key);
	DDX_Text(pDX, IDC_Cleartext, cleartext);

}


BEGIN_MESSAGE_MAP(C_Caesar_Main, CDialogEx)
	ON_BN_CLICKED(IDC_luru, &C_Caesar_Main::OnBnClickedluru)
END_MESSAGE_MAP()


// C_Caesar_Main 消息处理程序




void C_Caesar_Main::Set_alphabet()
{
	// TODO: 在此处添加实现代码.
	for (int i = 0, c = 'A'; i<26; i++, c++)
	{
		alphabet[i] = c;
	}
}


int C_Caesar_Main::searchnum(char a)
{
	// TODO: 在此处添加实现代码.
	for (int i = 0; i<26; i++)
	{
		if (a == alphabet[i])
			return i;
	}
}


void C_Caesar_Main::Encrypt()//加密
{
	// TODO: 在此处添加实现代码.
	chartemp = cleartext.GetBuffer(cleartext.GetLength());
	cleartext.ReleaseBuffer();

	Set_alphabet();
	int i;
	for (i = 0; chartemp[i] != '\0'; i++)
	{
		int m = searchnum(chartemp[i]);
		int n = (m + key) % 26;
		if (n<0) n = n+26;
		char c = alphabet[n];
		chartemp[i] = c;//密文
	}
	chartemp[i] = '\0';
	CString ctemp(chartemp);
	ciphertext = ctemp;
}


void C_Caesar_Main::Decrypt()//解密
{
	// TODO: 在此处添加实现代码.
	chartemp1 = ciphertext.GetBuffer(ciphertext.GetLength());
	ciphertext.ReleaseBuffer();

	Set_alphabet();
	int i;
	for (i = 0; chartemp1[i] != '\0'; i++)
	{
		int m = searchnum(chartemp1[i]);
		int n = (m - key) % 26;
		if (n<0) n = n+26;
		char c = alphabet[n];
		chartemp1[i] = c;
	}
	chartemp1[i] = '\0';
	CString ctemp1(chartemp1);
	cleartext = ctemp1;

}
void C_Caesar_Main::OnBnClickedluru()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	C_Caesar_Show dlg;

	Encrypt();
	dlg.ciphertextB = ciphertext;
	Decrypt();
	dlg.cleartextB = cleartext;	//传递数据
	dlg.DoModal();
	
	CDialogEx::OnOK();
}
