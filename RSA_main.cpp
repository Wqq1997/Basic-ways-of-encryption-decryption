// RSA_main.cpp: 实现文件
//

#include "stdafx.h"
#include "加解密.h"
#include "RSA_main.h"
#include "afxdialogex.h"
#include "RSA_show.h"


// RSA_main 对话框

IMPLEMENT_DYNAMIC(RSA_main, CDialogEx)

RSA_main::RSA_main(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RSA_main, pParent)
{
}

RSA_main::~RSA_main()
{
}

void RSA_main::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_p, ps);
	DDX_Text(pDX, IDC_q, qs);
	DDX_Text(pDX, IDC_RSA_cleartext, m);

}


BEGIN_MESSAGE_MAP(RSA_main, CDialogEx)
	ON_BN_CLICKED(IDOK, &RSA_main::OnBnClickedOk)
END_MESSAGE_MAP()


// RSA_main 消息处理程序


void RSA_main::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	RSA_show dlg;
	
	flag = 0;
	p = ps;
	q = qs;
	n = p * q;
	fn = (p - 1) * (q - 1);
	intest = (primetest(p) && primetest(q) && (p != q));

	if (intest == 1)
	{
		produce_key();
		dlg.n2 = n;
		dlg.e2 = e;
		dlg.d2 = d ;
		encrypt(m);
		dlg.ciphertextB = c;
		decrypt(c);
		dlg.cleartextB = m;
		dlg.DoModal();
	}
	else AfxMessageBox(_T("输入错误！"));

	CDialogEx::OnOK();
}


//素数检测
bool RSA_main::primetest(int m)
{
	if (m <= 1)
		return false;
	else if (m == 2)
		return true;
	else
	{
		for (int i = 2; i <= sqrt(double(m)); i++)
		{
			if ((m % i) == 0)
			{
				return false;
				break;
			}
		}
		return true;
	}
}

//排序
void RSA_main::order(int &a, int &b)
{
	int big = (a > b ? a : b);
	int Small = (a < b ? a : b);
	a = big;
	b = Small;
}

//求解最大公约数
int RSA_main::gcd(int a, int b)
{
	order(a, b); //将输入的a,b排序
	int r;
	if (b == 0)
		return a;
	else
	{
		while (true)     //辗转相除法
		{
			r = a % b;
			a = b;
			b = r;
			if (b == 0)
			{
				return a;
				break;
			}
		}
	}
}

//扩展欧几里得算法
int RSA_main::extend_euclid(int m, int bin)
{
	order(m, bin);
	int a[3], b[3], t[3];
	a[0] = 1, a[1] = 0, a[2] = m;
	b[0] = 0, b[1] = 1, b[2] = bin;
	if (b[2] == 0)
	{
		return a[2] = gcd(m, bin);
	}
	if (b[2] == 1)
	{
		return b[2] = gcd(m, bin);
	}
	while (true)
	{
		if (b[2] == 1)
		{
			return b[1];
			break;
		}
		int q = a[2] / b[2];
		for (int i = 0; i<3; i++)
		{
			t[i] = a[i] - q * b[i];
			a[i] = b[i];
			b[i] = t[i];
		}
	}
}

//整形转化为二进制数组
void RSA_main::int_to_binarr(int i, int binarr[32])
{
	int n = 0;
	while (i > 0)
	{
		binarr[n] = i % 2;
		n++;
		i /= 2;
	}
}

//快速模幂算法
int RSA_main::modular_multiplication(int a, int b, int n)
{
	int f = 1;
	int bin[32];
	int_to_binarr(b, bin);    //转换为二进制数组
	for (int i = 31; i >= 0; i--)
	{
		f = (f * f) % n;
		if (bin[i] == 1)
		{
			f = (f * a) % n;
		}
	}
	return f;
}


//密钥生成
void RSA_main::produce_key()
{
	if (intest == 1)
		e = 2;
	while ((gcd(fn, e) != 1))
		e++;
	d = (extend_euclid(fn, e) + fn) % fn;  //扩展欧几里得算法求逆元
	flag = 1;
}

void RSA_main::encrypt(int m)
{
	if (flag == 0)
		produce_key();
	c = modular_multiplication(m, e, n);
}

void RSA_main::decrypt(int c)
{
	if (flag == 0)
		produce_key();
	m = modular_multiplication(c, d, n);
}

