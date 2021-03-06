#pragma once

// LSB_cleardlg 对话框

class LSB_cleardlg : public CDialogEx
{
	DECLARE_DYNAMIC(LSB_cleardlg)

public:
	LSB_cleardlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~LSB_cleardlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LSB_cleardlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BitmapFileHeader * m_pBitmapFileHeader;   //指向文件头
	BitmapInfoHeader * m_pBitmapInfoHeader;   //指向信息头
	RGBQUAD * m_pRGB;                //指向调色板 
	BYTE * m_pData;               //
	unsigned int m_numberOfColors;       //颜色数 
	bool m_bmptest;              //bmp文件的正确性	
	BitmapInfo * m_pBitmapInfo;         //
	BYTE * pbmp;                  //指向数据区
	DWORD size;                   //调色板和数据区的总大小

	char m_fileName[256] = { 0 };            //文件名数组 
	unsigned int	getwidth();                 //获取图像宽度
	unsigned int	getheight();                //获取图像高度
	DWORD			getsize();                  //获得数据区大小
	unsigned int	getnumofcolors();           //获得颜色数
	void			loadfile(const char* dibFileName);   //载入文件
	void 			savefile(const char* filename);      //保存文件
	int             Code(const char* textFileName);        //LSB信息隐藏
	void            Decode(const char* dibFileName);       //LSB解码
	CString bmpfile = "";
	char* bmpfilechar;
	CString txtfile="";
	char* txtfilechar;
	CString bmpsave="";
	char* bmpsavechar;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedfileoutput1();
	afx_msg void OnBnClickedfileoutput2();
};
