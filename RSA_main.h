#pragma once


// RSA_main 对话框

class RSA_main : public CDialogEx
{
	DECLARE_DYNAMIC(RSA_main)

public:
	RSA_main(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~RSA_main();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RSA_main };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int ps=3;
	int qs=11;
	int q;
	int p;

	int n;
	int e;
	int d;

	int m=0;
	int c;
	int fn;

	bool intest;
	bool flag;

	bool primetest(int m);        //素数检测
	int gcd(int a, int b);        //求解最大公约数
	int extend_euclid(int m, int bin); //扩展欧几里得算法
	int modular_multiplication(int a, int b, int n);   //快速模幂算法
	void int_to_binarr(int i, int binarr[32]);  //十进制数组转换为二进制数组
	void order(int &a, int &b);   //排序
	void produce_key();         //生成密钥  
	void encrypt(int m);        //加密
	void decrypt(int c);        //解密

};
