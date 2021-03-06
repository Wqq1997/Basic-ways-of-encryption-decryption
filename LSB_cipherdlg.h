#pragma once


#pragma   pack(push)  
#pragma   pack(1)  
// LSB_cipherdlg 对话框
//bmp文件头
struct BitmapFileHeader
{
	WORD	 bfType;            //位图类别，为‘BM' 
	DWORD	 bfSize;            //BMP图像文件大小，以字节为单位 
	WORD	 bfReserved;        //BMP图像文件保留字，为0 
	WORD	 bfReservedEx;      //BMP图像文件保留字，为0 
	DWORD	 bfOffBits;         //BMP图像数据的地址，相对于位图文件头 
};                              //的偏移量，以字节为单位 
#pragma     pack(pop)   


#pragma   pack(push)  
#pragma   pack(1)    


								//bmp信息头 
 struct BitmapInfoHeader
{
	DWORD	 biSize;            //本结构大小，应为28h字节 
	long	 biWidth;           //BMP图像的宽度，以像素为单位 
	long	 biHeight;          //BMP图像的高度，以像素为单位 
	WORD	 biPlanes;          //位图设备级别为1 
	WORD	 biBitPerPixel;     //每像素所需的位数，可以是1，4，8，24
	DWORD	 biCompression;     //压缩类型
	DWORD	 biDataSize;        //位图数据区域的大小，以字节为单位 
	long	 biHResolution;     //水平分辨率 
	long  	 biVResolution;     //垂直分辨率 
	DWORD	 biColors;          //实际使用颜色数 
	DWORD    biImprotantColors; //重要颜色数 
};
#pragma     pack(pop)   


#pragma   pack(push)  
#pragma   pack(1)    


 struct BitmapInfo
{
	BitmapInfoHeader	bmiHeader;           //位图信息头 
	RGBQUAD	    bmiColors[1];        //颜色表 
};
#pragma     pack(pop)   
  

//-------------------------------------------


class LSB_cipherdlg : public CDialogEx
{
	DECLARE_DYNAMIC(LSB_cipherdlg)

public:
	LSB_cipherdlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~LSB_cipherdlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LSB_cipherdlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BitmapFileHeader *  m_pBitmapFileHeader;   //指向文件头
	BitmapInfoHeader * m_pBitmapInfoHeader;   //指向信息头
	RGBQUAD * m_pRGB;                //指向调色板 
	BYTE * m_pData;               //
	unsigned int m_numberOfColors;       //颜色数 
	bool m_bmptest;              //bmp文件的正确性	
	BitmapInfo * m_pBitmapInfo;         //
	BYTE * pbmp;                  //指向数据区
	DWORD size;                   //调色板和数据区的总大小

	char m_fileName[256] = {0};            //文件名数组 
	unsigned int	getwidth();                 //获取图像宽度
	unsigned int	getheight();                //获取图像高度
	DWORD			getsize();                  //获得数据区大小
	unsigned int	getnumofcolors();           //获得颜色数
	void			loadfile(const char* dibFileName);   //载入文件
	void 			savefile(const char* filename);      //保存文件
	int             Code(const char* textFileName);        //LSB信息隐藏
	void            Decode(const char* dibFileName);       //LSB解码
	CString bmpfile="";
	char* bmpfilechar;
	CString txtfile="";
	char* txtfilechar;
	CString bmpsave="";
	char* bmpsavechar;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedfileopen1();

	

	afx_msg void OnBnClickedfileopen2();
	afx_msg void OnBnClickedfileopen3();
};
