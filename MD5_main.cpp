// MD5_main.cpp: 实现文件
//

#include "stdafx.h"
#include "加解密.h"
#include "MD5_main.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "MD5_show.h"

typedef unsigned char uchar;
typedef unsigned int uint;


// MD5_main 对话框

IMPLEMENT_DYNAMIC(MD5_main, CDialogEx)

MD5_main::MD5_main(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MD5_main, pParent)
{

}

MD5_main::~MD5_main()
{
}

void MD5_main::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MD5_cleartext, cleartext);

}


BEGIN_MESSAGE_MAP(MD5_main, CDialogEx)
	ON_BN_CLICKED(IDOK, &MD5_main::OnBnClickedOk)
END_MESSAGE_MAP()


// MD5_main 消息处理程序


void MD5_main::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	MD5_show dlg;
	
	char* cleartemp = cleartext.GetBuffer(cleartext.GetLength());
	cleartext.ReleaseBuffer();

	//构造函数
	md5_init();  //初始化
	func(cleartemp, cleartext.GetLength());  //前部分分组变换
	finalize();  //最后部分分组的变换

	dlg.ciphertextB = hexdigest();

	dlg.DoModal();
	CDialogEx::OnOK();
}


inline  uint MD5_main::rotate_left(uint x, int n)
{
	return (x << n) | (x >> (32 - n));
}

//一轮运算中的几个基本运算
inline  uint MD5_main::F(uint x, uint y, uint z)
{
	return x & y | ~x&z;
}

inline  uint MD5_main::G(uint x, uint y, uint z)
{
	return x & z | y & ~z;
}

inline  uint MD5_main::H(uint x, uint y, uint z)
{
	return x ^ y^z;
}

inline  uint MD5_main::I(uint x, uint y, uint z)
{
	return y ^ (x | ~z);
}


inline void MD5_main::FF(uint &a, uint b, uint c, uint d, uint x, uint s, uint ac)
{
	a = rotate_left(a + F(b, c, d) + x + ac, s) + b;
}

inline void MD5_main::GG(uint &a, uint b, uint c, uint d, uint x, uint s, uint ac)
{
	a = rotate_left(a + G(b, c, d) + x + ac, s) + b;
}

inline void MD5_main::HH(uint &a, uint b, uint c, uint d, uint x, uint s, uint ac)
{
	a = rotate_left(a + H(b, c, d) + x + ac, s) + b;
}

inline void MD5_main::II(uint &a, uint b, uint c, uint d, uint x, uint s, uint ac)
{
	a = rotate_left(a + I(b, c, d) + x + ac, s) + b;
}


//////////////////////////////  

void MD5_main::md5_init()
{
	finalized = false;
	count[0] = 0;  //计数器置0
	count[1] = 0;
	state[0] = 0x67452301;
	state[1] = 0xefcdab89;
	state[2] = 0x98badcfe;
	state[3] = 0x10325476;
}

//整形数组转化为字符型数组  
void MD5_main::uint_to_uchar(uchar output[], const uint input[], uint len)
{
	for (uint i = 0, j = 0; j < len; i++, j += 4) {
		output[j] = input[i] & 0xff;
		output[j + 1] = (input[i] >> 8) & 0xff;
		output[j + 2] = (input[i] >> 16) & 0xff;
		output[j + 3] = (input[i] >> 24) & 0xff;
	}
}

//字符型数组转化为整形数组
void MD5_main::uchar_to_uint(uint output[], const uchar input[], uint len)
{
	for (unsigned int i = 0, j = 0; j < len; i++, j += 4)
		output[i] = ((uint)input[j]) | (((uint)input[j + 1]) << 8) |
		(((uint)input[j + 2]) << 16) | (((uint)input[j + 3]) << 24);
}

//4轮（64）步运算 
void MD5_main::transform(const uchar block[64])
{
	uint a = state[0], b = state[1], c = state[2], d = state[3], x[16];
	uchar_to_uint(x, block, 64);

	//1-16 第一轮
	FF(a, b, c, d, x[0], 7, 0xd76aa478);
	FF(d, a, b, c, x[1], 12, 0xe8c7b756);
	FF(c, d, a, b, x[2], 17, 0x242070db);
	FF(b, c, d, a, x[3], 22, 0xc1bdceee);
	FF(a, b, c, d, x[4], 7, 0xf57c0faf);
	FF(d, a, b, c, x[5], 12, 0x4787c62a);
	FF(c, d, a, b, x[6], 17, 0xa8304613);
	FF(b, c, d, a, x[7], 22, 0xfd469501);
	FF(a, b, c, d, x[8], 7, 0x698098d8);
	FF(d, a, b, c, x[9], 12, 0x8b44f7af);
	FF(c, d, a, b, x[10], 17, 0xffff5bb1);
	FF(b, c, d, a, x[11], 22, 0x895cd7be);
	FF(a, b, c, d, x[12], 7, 0x6b901122);
	FF(d, a, b, c, x[13], 12, 0xfd987193);
	FF(c, d, a, b, x[14], 17, 0xa679438e);
	FF(b, c, d, a, x[15], 22, 0x49b40821);
	//17-32 第二轮
	GG(a, b, c, d, x[1], 5, 0xf61e2562);
	GG(d, a, b, c, x[6], 9, 0xc040b340);
	GG(c, d, a, b, x[11], 14, 0x265e5a51);
	GG(b, c, d, a, x[0], 20, 0xe9b6c7aa);
	GG(a, b, c, d, x[5], 5, 0xd62f105d);
	GG(d, a, b, c, x[10], 9, 0x2441453);
	GG(c, d, a, b, x[15], 14, 0xd8a1e681);
	GG(b, c, d, a, x[4], 20, 0xe7d3fbc8);
	GG(a, b, c, d, x[9], 5, 0x21e1cde6);
	GG(d, a, b, c, x[14], 9, 0xc33707d6);
	GG(c, d, a, b, x[3], 14, 0xf4d50d87);
	GG(b, c, d, a, x[8], 20, 0x455a14ed);
	GG(a, b, c, d, x[13], 5, 0xa9e3e905);
	GG(d, a, b, c, x[2], 9, 0xfcefa3f8);
	GG(c, d, a, b, x[7], 14, 0x676f02d9);
	GG(b, c, d, a, x[12], 20, 0x8d2a4c8a);

	//33-48 第三轮
	HH(a, b, c, d, x[5], 4, 0xfffa3942);
	HH(d, a, b, c, x[8], 11, 0x8771f681);
	HH(c, d, a, b, x[11], 16, 0x6d9d6122);
	HH(b, c, d, a, x[14], 23, 0xfde5380c);
	HH(a, b, c, d, x[1], 4, 0xa4beea44);
	HH(d, a, b, c, x[4], 11, 0x4bdecfa9);
	HH(c, d, a, b, x[7], 16, 0xf6bb4b60);
	HH(b, c, d, a, x[10], 23, 0xbebfbc70);
	HH(a, b, c, d, x[13], 4, 0x289b7ec6);
	HH(d, a, b, c, x[0], 11, 0xeaa127fa);
	HH(c, d, a, b, x[3], 16, 0xd4ef3085);
	HH(b, c, d, a, x[6], 23, 0x4881d05);
	HH(a, b, c, d, x[9], 4, 0xd9d4d039);
	HH(d, a, b, c, x[12], 11, 0xe6db99e5);
	HH(c, d, a, b, x[15], 16, 0x1fa27cf8);
	HH(b, c, d, a, x[2], 23, 0xc4ac5665);

	//49-64 第四轮
	II(a, b, c, d, x[0], 6, 0xf4292244);
	II(d, a, b, c, x[7], 10, 0x432aff97);
	II(c, d, a, b, x[14], 15, 0xab9423a7);
	II(b, c, d, a, x[5], 21, 0xfc93a039);
	II(a, b, c, d, x[12], 6, 0x655b59c3);
	II(d, a, b, c, x[3], 10, 0x8f0ccc92);
	II(c, d, a, b, x[10], 15, 0xffeff47d);
	II(b, c, d, a, x[1], 21, 0x85845dd1);
	II(a, b, c, d, x[8], 6, 0x6fa87e4f);
	II(d, a, b, c, x[15], 10, 0xfe2ce6e0);
	II(c, d, a, b, x[6], 15, 0xa3014314);
	II(b, c, d, a, x[13], 21, 0x4e0811a1);
	II(a, b, c, d, x[4], 6, 0xf7537e82);
	II(d, a, b, c, x[11], 10, 0xbd3af235);
	II(c, d, a, b, x[2], 15, 0x2ad7d2bb);
	II(b, c, d, a, x[9], 21, 0xeb86d391);

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
	memset(x, 0, sizeof x);
}



// 数据block的处理程序，length不必等于64字节（512位）
//将输入数据前半部分填充至buffer[64]补满，填充完整后全部数据批量进行多次变换
void MD5_main::func(const uchar input[], uint length)
{
	uint index = count[0] / 8 % 64;
	if ((count[0] += (length << 3)) < (length << 3))
		count[1]++;
	count[1] += (length >> 29);    //更新已处理数据计数器
	uint firstpart = 64 - index;   // 确定填充数目
	uint i;
	if (length >= firstpart)
	{
		memcpy(&buffer[index], input, firstpart);  //输入数据最前部分填充满buffer
		transform(buffer);
		for (i = firstpart; i + 64 <= length; i += 64)
			transform(&input[i]);        //多次变换，每次变换64字节
		index = 0;
	}
	else
		i = 0;
	memcpy(&buffer[index], &input[i], length - i);   //不足部分填充至buffer
}



void MD5_main::func(const char input[], uint length)
{
	func((const unsigned char*)input, length);
}

//
void MD5_main::finalize()
{
	static unsigned char append[64] =
	{ 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	if (!finalized)
	{
		unsigned char size_bits[8];
		uint_to_uchar(size_bits, count, 8);  //长度转化为字符  
		uint index = count[0] / 8 % 64;
		uint append_len = (index < 56) ? (56 - index) : (120 - index);  //计算填充数目
		func(append, append_len);  //填充至buffer
		func(size_bits, 8);      //填充至buffer进行变换
								 // 最终的链接变量即为消息摘要 
		uint_to_uchar(digest, state, 16);
		//摘要计算完成后，buffer,count置0
		memset(buffer, 0, sizeof buffer);
		memset(count, 0, sizeof count);
		finalized = true;
	}

}

//16计算消息摘要的16进制表示
CString MD5_main::hexdigest()
{
	if (!finalized)
		return "";
	char hex[33];
	for (int i = 0; i<16; i++)
		sprintf(hex + i * 2, "%02x", digest[i]);
	hex[32] = 0;
	return CString(hex);
}

