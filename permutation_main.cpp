// permutation_main.cpp: 实现文件
//

#include "stdafx.h"
#include "加解密.h"
#include "permutation_main.h"
#include "afxdialogex.h"
#include "permutation_show.h"

// permutation_main 对话框

IMPLEMENT_DYNAMIC(permutation_main, CDialogEx)

permutation_main::permutation_main(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_permutation_main, pParent)
{
	/*char* key_temp = NULL;	
	char* key_s_temp = NULL;
	char* clear = NULL;
*/

}

permutation_main::~permutation_main()
{
	
	//if(key_temp != NULL) delete key_temp;
	//if(key_s_temp != NULL) delete key_s_temp;
	//if(clear != NULL) delete clear;

}

void permutation_main::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_permutation_cleartext, cleartext);
	DDX_Text(pDX, IDC_permutation_key, key);

}


BEGIN_MESSAGE_MAP(permutation_main, CDialogEx)
	ON_BN_CLICKED(IDOK, &permutation_main::OnBnClickedOk)
END_MESSAGE_MAP()


// permutation_main 消息处理程序


void permutation_main::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	permutation_show dlg;
	
	Set_key();
	Set_clear();
	Sort_key();
	
	Encrypt();
	dlg.ciphertextB = cipherone;

	Decrypt();
	dlg.cleartextB = clearone;
	
	dlg.DoModal();
	CDialogEx::OnOK();


}


void permutation_main::Set_clear()//设置明文
{
	// TODO: 在此处添加实现代码.
	clear = cleartext.GetBuffer(cleartext.GetLength());
	cleartext.ReleaseBuffer();//将cstring cleartext转成char* clear
	
	
	for (int k = 0, i = 0, j = 0; clear[k] != '\0'; k++)
	{
		if (clear[k] != ' ')
		{
			cleararray[i][j] = clear[k]; //将输入的一维数组转化为二维数组cleararray
			row = i + 1;                 //矩阵的行数
			j++;
			if (j >= len)              //key的长度决定矩阵列数
			{
				j = 0; i++;
			}
		}
	}


}



void permutation_main::Set_key()
{
	// TODO: 在此处添加实现代码.
	len = strlen(key);
}



void permutation_main::Sort_key()
{
	// TODO: 在此处添加实现代码.
	key_temp = key.GetBuffer(key.GetLength());
	key_s_temp = key_s.GetBuffer(key.GetLength());
	key.ReleaseBuffer();
	key_s.ReleaseBuffer();
	
	strcpy_s(key_s_temp, strlen(key_temp)+1 ,key_temp);
	
	for (int i = 0; i<len; i++)
	{
		for (int j = 0; j<len - i - 1; j++)
		{
			if (key_s_temp[j] > key_s_temp[j + 1])
			{
				char temp = key_s_temp[j];
				key_s_temp[j] = key_s_temp[j + 1];
				key_s_temp[j + 1] = temp;
			}
		}
	}
}

void permutation_main::Encrypt()//加密
{
	// TODO: 在此处添加实现代码.
	//Sort_key();
	for (int i = 0; i<len; i++)
	{
		for (int j = 0; j<len; j++)
		{
			if (key_temp[i] == key_s_temp[j])
			{
				for (int k = 0; k<row; k++)
				{
					cipherarray1[k][j] = cleararray[k][i];
				}
			}
		}
	}

	for (int i = 0; i<len; i++)
	{
		for (int j = 0; j<len; j++)
		{
			if (key_temp[i] == key_s_temp[j])
			{
				for (int k = 0; k<row; k++)
				{
					cipherarray2[k][j] = cipherarray1[k][i];
				}
			}
		}
	}

	for (int i = 0; i<len; i++)
	{
		for (int j = 0; j<row; j++)
			cipherone += cipherarray2[j][i];
	}
	

}


void permutation_main::Decrypt()//解密
{
	// TODO: 在此处添加实现代码.
	//Sort_key();
	for (int i = 0; i<len; i++)
	{
		for (int j = 0; j<len; j++)
		{
			if (key_temp[i] == key_s_temp[j])
			{
				for (int k = 0; k<row; k++)
				{
					cipherarray1[k][j] = cipherarray2[k][i];
				}
			}
		}
	}

	for (int i = 0; i<len; i++)
	{
		for (int j = 0; j<len; j++)
		{
			if (key_temp[i] == key_s_temp[j])
			{
				for (int k = 0; k<row; k++)
				{
					cleararray[k][j] = cipherarray1[k][i];
				}
			}
		}
	}

	for (int i = 0; i<row; i++)//将二维转为一维
	{
		for (int j = 0; j<len; j++)
			clearone += cleararray[i][j];
	}
	

}


