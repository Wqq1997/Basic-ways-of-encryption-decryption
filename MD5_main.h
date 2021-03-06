#pragma once
typedef unsigned char uchar;
typedef unsigned int uint;

// MD5_main 对话框

class MD5_main : public CDialogEx
{
	DECLARE_DYNAMIC(MD5_main)

public:
	MD5_main(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MD5_main();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MD5_main };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	uint state[4];   //连接变量
	uchar digest[16]; //消息摘要结果  
	uchar buffer[64]; //每次处理的分组  
	uint count[2];   // 比特计数器，64位  
	void md5_init();
	void transform(const uchar block[64]);
	void uchar_to_uint(uint output[], const uchar input[], uint len);
	//字符型数组转换为整形数组
	void uint_to_uchar(uchar output[], const uint input[], uint len);
	//整形数组转换为字符型数组
	bool finalized;
	static inline uint rotate_left(uint x, int n);
	static inline uint F(uint x, uint y, uint z); //4个基本运算 
	static inline uint G(uint x, uint y, uint z);
	static inline uint H(uint x, uint y, uint z);
	static inline uint I(uint x, uint y, uint z);
	static inline void FF(uint &a, uint b, uint c, uint d, uint x, uint s, uint ac);  //4个函数
	static inline void GG(uint &a, uint b, uint c, uint d, uint x, uint s, uint ac);
	static inline void HH(uint &a, uint b, uint c, uint d, uint x, uint s, uint ac);
	static inline void II(uint &a, uint b, uint c, uint d, uint x, uint s, uint ac);

	void func(const uchar *buf, uint length);  //处理数据分组
	void func(const char *buf, uint length);
	void finalize();
	CString hexdigest();  //计算消息摘要的16进制表示

	CString cleartext;
};
