#pragma once


// des_main 对话框

class des_main : public CDialogEx
{
	DECLARE_DYNAMIC(des_main)

public:
	des_main(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~des_main();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_des_main };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString cleartext;//8字节明文
	char* msg;
	bool bitmsg[64] = {0};  //64位明文

	CString key_s;  //8字节密钥
	char*key;
	bool bitkey[64];    //64位密钥
	bool subkeys[16][48]; //子密钥

	bool lmsgi[32], rmsgi[32];//第i个左、右部分数据
	bool lmsgi1[32], rmsgi1[32];//第i+1个左、右部分数据

	CString ciphertext;//传递的输出密文
	char* ciphertemp;
	char buf[17];
	unsigned char* cipher = new unsigned char[8];//8字节密文
	bool bitcipher[64];		//64位密文
	unsigned char* clear =new unsigned  char[17];//解密得到的明文
	bool bitclear[64];     //解密得到64位明文
	



	const static int ip_table[64]; //初始值换ip 
	const static int ipr_table[64];  //逆初始置换表ip-1
	const static int PC1_0_table[28]; //密钥置换PC-1
	const static int PC1_1_table[28];
	const static int PC2_table[48];   //密钥置换PC-2 
	const static int LS_table[16];  //循环左移规则表

	const static int e_table[48]; //e运算表 
	const static int sbox_table[8][64]; //S盒表
	const static int p_table[32]; //p置换运算表
	const static unsigned char bitmask[8];

	void IP(bool str[64]);     //初始置换 
	void IPR(bool str[64]);  //初始逆置换 
	void funcf(bool in[32], int i, bool out[32]); //子密钥控制下的f变换
	void LS(bool* keypart, int n); //循环左移
	void funce(bool a[32], bool b[48]); //扩展运算e
	void XOR(bool a[], bool b[], bool c[], int length);//模二加（异或）运算
	void SBox(bool in[48], bool out[32]);
	void subSBox(bool in[6], bool out[4], int box);
	void funcp(bool bitin[32], bool bitout[32]);   //置换P

	 //二进制和字符数组之间的转换
	void Bit2Char(bool* bitarr, unsigned char* chararr);
	void Char2Bit(char* chararr, bool* bitarr, int length);
	void CopyArray(bool a[], bool b[], int size);

	void SetMsg(char* _msg, int _length);//设置明文
	void SetKey(char* _msg, int _length);//设置密钥
	void ProduceSubKey();
	void Encrypt();   //加密函数
	void Decrypt();  //解密函数
	//void Outputclear(); //输出明文（解密结果）
	//void Outputcipher();//输出密文（加密结果）	

	afx_msg void OnBnClickedOk();
//	void CStringToHex(char *in, char *out);
};
