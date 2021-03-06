// des_main.cpp: 实现文件
//

#include "stdafx.h"
#include "加解密.h"
#include "des_main.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "des_show.h"

// des_main 对话框

IMPLEMENT_DYNAMIC(des_main, CDialogEx)

des_main::des_main(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_des_main, pParent)
{
	memset(clear, 0, sizeof(char) * 17);
	memset(cipher, 0, sizeof(char) * 8);
}

des_main::~des_main()
{
	delete []clear;
}

void des_main::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_des_key, key_s);
	DDX_Text(pDX, IDC_des_cleartext, cleartext);
}


BEGIN_MESSAGE_MAP(des_main, CDialogEx)
	ON_BN_CLICKED(IDOK, &des_main::OnBnClickedOk)
END_MESSAGE_MAP()


// des_main 消息处理程序

//ip置换表
const int des_main::ip_table[64] = {
	58,50,42,34,26,18,10,2,
	60,52,44,36,28,20,12,4,
	62,54,46,38,30,22,14,6,
	64,56,48,40,32,24,16,8,
	57,49,41,33,25,17,9,1,
	59,51,43,35,27,19,11,3,
	61,53,45,37,29,21,13,5,
	63,55,47,39,31,23,15,7
};
//PC-1置换表
const int des_main::PC1_0_table[28] = {
	57,49,41,33,25,17,9,
	1,58,50,42,34,26,18,
	10,2,59,51,43,35,27,
	19,11,3,60,52,44,36
};

const int des_main::PC1_1_table[28] = {
	63,55,47,39,31,23,15,
	7,62,54,46,38,30,22,
	14,6,61,53,45,37,29,
	21,13,5,28,20,12,4
};

const int des_main::LS_table[16] = {
	1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};

const int des_main::PC2_table[48] = {
	14,17,11,24,1,5,
	3,28,15,6,21,10,
	23,19,12,4,26,8,
	16,7,27,20,13,2,
	41,52,31,37,47,55,
	30,40,51,45,33,48,
	44,49,39,56,34,53,
	46,42,50,36,29,32
};

const int des_main::e_table[48] = {
	32,1,2,3,4,5,
	4,5,6,7,8,9,
	8,9,10,11,12,13,
	12,13,14,15,16,17,
	16,17,18,19,20,21,
	20,21,22,23,24,25,
	24,25,26,27,28,29,
	28,29,30,31,32,1
};

const int des_main::sbox_table[8][64] = {
	{
		14, 4, 13, 1, 1, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
		0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
		4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
		15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13
	},

  {
	  15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
	  3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
	  0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
	  13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9
  },

  {
	  10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
	  13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
	  13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
	  1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12
  },

  {
	  7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
	  13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
	  10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
	  3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14
  },

  {
	  2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
	  14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
	  4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
	  11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3
  },

  {
	  12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
	  10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
	  9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
	  4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13
  },

   {
	   4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
	   13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
	   1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
	   6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12
   },

   {
	   13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 13, 14, 5, 0, 12, 7,
	   1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
	   7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
	   2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
   }
};

const int des_main::p_table[32] = {
	16,7,20,21,
	29,12,28,17,
	1,15,23,26,
	5,18,31,10,
	2,8,24,14,
	32,27,3,9,
	19,13,30,6,
	22,11,4,25
};
const int des_main::ipr_table[64] = {
	40,8,48,16,56,24,64,32,
	39,7,47,15,55,23,63,31,
	38,6,46,14,54,22,62,30,
	37,5,45,13,53,21,61,29,
	36,4,44,12,52,20,60,28,
	35,3,43,11,51,19,59,27,
	34,2,42,10,50,18,58,26,
	33,1,41,9,49,17,57,25
};
const unsigned char des_main::bitmask[8] = { 128,64,32,16,8,4,2,1 };

void des_main::Char2Bit(char* chararr, bool* bitarr, int length)
{
	// TODO: 在此处添加实现代码.
	for (int i = 0; i <length; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			bitarr[i * 8 + 7 - j] = (chararr[i] >> j) & 1;
		}
	}
}


void des_main::Bit2Char(bool* bitarr,unsigned char* chararr)
{
	// TODO: 在此处添加实现代码.
	char temp;
	for (int i = 0; i < 8; i++)
	{
		temp = 0;
		for (int j = 0; j < 8; j++)
		{
			if (bitarr[i * 8 + j])
			{
				temp |= bitmask[j];
			}
		}
		chararr[i] = temp;
	}
}


void des_main::SetMsg(char* msgin, int length)
{
	// TODO: 在此处添加实现代码.
	if (length > 8)
		return;
	for (int i = 0; i < length; i++)
	{
		msg[i] = msgin[i];
	}
	Char2Bit(msg, bitmsg, 8);
}


void des_main::SetKey(char* keyin, int length)
{
	// TODO: 在此处添加实现代码.
	if (length>8)
	{
		return;
	}
	for (int i = 0; i < length; i++)
	{
		key[i] = keyin[i];
	}
	Char2Bit(key, bitkey, 8);
}


void des_main::IP(bool str[64])
{
	// TODO: 在此处添加实现代码.
	for (int i = 0; i < 32; i++)
	{
		lmsgi[i] = str[ip_table[i] - 1];
		rmsgi[i] = str[ip_table[i + 32] - 1];
	}
}


void des_main::IPR(bool str[64])
{
	// TODO: 在此处添加实现代码.
	bool temp[64];
	for (int i = 0; i < 32; i++)//左右两部分组合
	{
		temp[i] = rmsgi[i];
		temp[32 + i] = lmsgi[i];
	}
	for (int i = 0; i < 64; i++)
	{
		str[i] = temp[ipr_table[i] - 1];
	}
}


void des_main::LS(bool* keypart, int n)
{
	// TODO: 在此处添加实现代码.

	bool temp;
	for (int i = 0; i < n; i++)
	{
		temp = keypart[0];
		for (int i = 0; i < 27; i++)
		{
			keypart[i] = keypart[i + 1];
		}
		keypart[27] = temp;
	}
}

void des_main::ProduceSubKey()
{
	// TODO: 在此处添加实现代码.
	bool ctemp[28], dtemp[28]; //存放每轮左右各28位数据
	bool keytemp[56];        //存放移位并组合后56位数据
	for (int i = 0; i < 28; i++)//密钥置换PC-1
	{
		ctemp[i] = bitkey[PC1_0_table[i] - 1];
		dtemp[i] = bitkey[PC1_1_table[i] - 1];
	}

	for (int i = 0; i < 16; i++)
	{
		LS(ctemp, LS_table[i]); //两部分分别进行循环移位
		LS(dtemp, LS_table[i]);
		for (int j = 0; j <28; j++)
		{
			keytemp[j] = ctemp[j];
			keytemp[28 + j] = dtemp[j];
		}
		for (int j = 0; j < 48; j++) //密钥置换PC-2
		{
			subkeys[i][j] = keytemp[PC2_table[j] - 1];
		}
	}
}


void des_main::funce(bool bitin[32], bool bitout[48])
{
	// TODO: 在此处添加实现代码.
	for (int i = 0; i < 48; i++)
	{
		bitout[i] = bitin[e_table[i] - 1];
	}
}


void des_main::XOR(bool a[], bool b[], bool c[], int length)
{
	// TODO: 在此处添加实现代码.
	for (int i = 0; i < length; i++)
	{
		if (a[i] == b[i])
			c[i] = 0;
		else
			c[i] = 1;
	}
}


void des_main::SBox(bool in[48], bool out[32])
{
	// TODO: 在此处添加实现代码.
	bool _in[6], _out[4];
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			_in[j] = in[i * 6 + j];
		}
		subSBox(_in, _out, i);
		for (int jj = 0; jj < 4; jj++)
		{
			out[i * 4 + jj] = _out[jj];
		}
	}
}


void des_main::subSBox(bool in[6], bool out[4], int box)
{
	// TODO: 在此处添加实现代码.
	int raw, col;
	raw = in[0] * 2 + in[5];// 行
	col = in[1] * 2 * 2 * 2 + in[2] * 2 * 2 + in[3] * 2 + in[4];//列
	int result = sbox_table[box][raw * 16 + col];
	for (int i = 3; i >= 0; i--)
	{
		out[i] = (result >> (3 - i)) & 1;
	}
}


void des_main::funcp(bool bitin[32], bool bitout[32])
{
	// TODO: 在此处添加实现代码.
	for (int i = 0; i < 32; i++)
	{
		bitout[i] = bitin[p_table[i] - 1];
	}
}


void des_main::funcf(bool in[32], int i, bool out[32])
{
	// TODO: 在此处添加实现代码.
	bool temp1[48];
	funce(in, temp1);//扩展运算e
	bool temp2[48];
	XOR(temp1, (bool *)subkeys[i], temp2, 48);
	bool temp3[48]; //S盒运算
	SBox(temp2, temp3);
	funcp(temp3, out); //置换运算p
}


void des_main::Encrypt()
{
	// TODO: 在此处添加实现代码.
	msg = cleartext.GetBuffer(cleartext.GetLength());
	cleartext.ReleaseBuffer();

	bool temp1[32], temp2[32];
	IP(bitmsg); //初始置换ip
	for (int i = 0; i < 16; i++)
	{
		if (i % 2 == 0)
		{
			CopyArray(rmsgi, lmsgi1, 32);//L1=R0			
			funcf(rmsgi, i, temp1);//f(R0,k0)			
			XOR(lmsgi, temp1, temp2, 32);//L0+f(R0,k0)
			CopyArray(temp2, rmsgi1, 32); //R1=L0+f(R0,k0)
		}
		else
		{

			CopyArray(rmsgi1, lmsgi, 32);//L2=R1			
			funcf(rmsgi1, i, temp1); //f(R1,k1)
			XOR(lmsgi1, temp1, temp2, 32);//L1+f(R1,k1)
			CopyArray(temp2, rmsgi, 32);//R2=L1+f(R1,k1)
		}
	}
	IPR(bitcipher); //逆初始置换ip
	Bit2Char(bitcipher, cipher);

	for (int i = 0; i<8; i++)
		sprintf(buf + i * 2, "%02x", cipher[i]);
	buf[16] = 0;

	CString ctemp1(buf);
	ciphertext = ctemp1;


}


void des_main::CopyArray(bool a[], bool b[], int size)
{
	// TODO: 在此处添加实现代码.
	for (int i = 0; i < size; i++)
	{
		b[i] = a[i];
	}
}


void des_main::Decrypt()
{
	// TODO: 在此处添加实现代码.
	bool temp1[32], temp2[32];
	IP(bitcipher);//初始置换ip
	for (int i = 0; i < 16; i++)
	{
		if (i % 2 == 0)
		{
			CopyArray(rmsgi, lmsgi1, 32); //L1=R0    
			funcf(rmsgi, 15 - i, temp1);//f(R0,k15)
			XOR(lmsgi, temp1, temp2, 32);//L0+f(R0,k15)
			CopyArray(temp2, rmsgi1, 32);//R1=L0+f(R0,k15)
		}
		else
		{
			CopyArray(rmsgi1, lmsgi, 32); //L2=R1    
										  //解密时子密钥顺序与加密相反
			funcf(rmsgi1, 15 - i, temp1); //f(R1,k14)     
			XOR(lmsgi1, temp1, temp2, 32);//L1+f(R1,k14)     
			CopyArray(temp2, rmsgi, 32);//R2=L1+f(R1,k14)
		}
	}
	IPR(bitclear);//逆初始置换ip
	Bit2Char(bitclear, clear);

	CString ctemp1(clear);
	cleartext = ctemp1;
}


void des_main::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	des_show dlg;
	if (key_s.GetLength() != 8|| cleartext.GetLength() != 8)
	{
		MessageBox("输入不规范请重新输入");
		return;
	}

	key = key_s.GetBuffer(key_s.GetLength());
	key_s.ReleaseBuffer();//将输入的key_s转为char* key

	msg = cleartext.GetBuffer(cleartext.GetLength());
	cleartext.ReleaseBuffer();//将输入的cleartext转为char* msg

	SetMsg(msg, 8);
	SetKey(key, 8);
	ProduceSubKey();

	Encrypt(); //加密
	dlg.ciphertextB = ciphertext;				//输出密文
	Decrypt();								//对加密结果解密
	dlg.cleartextB = cleartext;				//输出解密后的明文

	dlg.DoModal();
	CDialogEx::OnOK();
}
