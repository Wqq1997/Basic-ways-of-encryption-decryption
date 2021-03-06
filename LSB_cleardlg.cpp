// LSB_cleardlg.cpp: 实现文件
//


#include <stdlib.h>
#include "stdafx.h"
#include "LSB_cipherdlg.h"
#include "LSB_cleardlg.h"

#include "afxdialogex.h"
#include "LSB_main.h"
#include "Resource.h"
#include "加解密.h"


// LSB_cleardlg 对话框

IMPLEMENT_DYNAMIC(LSB_cleardlg, CDialogEx)

LSB_cleardlg::LSB_cleardlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LSB_cleardlg, pParent)
{
	size = 0;
	pbmp = NULL;
	m_pBitmapFileHeader = new BitmapFileHeader;//文件头
	m_pBitmapInfoHeader = new BitmapInfoHeader;//信息头
	m_pBitmapInfo = (BitmapInfo*)m_pBitmapInfoHeader;
	bmpfile = _T("");
	txtfile = _T("");
}

LSB_cleardlg::~LSB_cleardlg()
{
	delete m_pBitmapFileHeader;
	delete m_pBitmapInfoHeader;
	if (pbmp)
	{
		delete pbmp;
	}
}

void LSB_cleardlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_bmp2, bmpfile);
	DDX_Text(pDX, IDC_txt2, txtfile);

}


BEGIN_MESSAGE_MAP(LSB_cleardlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &LSB_cleardlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_fileoutput1, &LSB_cleardlg::OnBnClickedfileoutput1)
	ON_BN_CLICKED(IDC_fileoutput2, &LSB_cleardlg::OnBnClickedfileoutput2)
END_MESSAGE_MAP()


// LSB_cleardlg 消息处理程序

//读取图像信息
void LSB_cleardlg::loadfile(const char* bmpFileName)
{

	strcpy_s(m_fileName, bmpFileName);
	CFile myfile;

	if (!myfile.Open(m_fileName, CFile::typeBinary | CFile::modeRead))
	{
		MessageBox(_T("文件不存在！"));
		return;
	}


	myfile.Read((char*)m_pBitmapFileHeader, sizeof(BitmapFileHeader));//读入文件头

	myfile.Read((char*)m_pBitmapInfoHeader, sizeof(BitmapInfoHeader)); //读入信息头

	if (m_pBitmapFileHeader->bfType == 0x4d42) //BM，BMP文件标识符
	{
		//读入图像信息
		size = m_pBitmapFileHeader->bfSize - sizeof(BitmapFileHeader) - sizeof(BitmapInfoHeader);
		pbmp = new BYTE[size];
		myfile.Read((char*)pbmp, size);
		myfile.Close();
		m_pRGB = (RGBQUAD*)(pbmp);
		m_numberOfColors = getnumofcolors();
		if (m_pBitmapInfoHeader->biColors != 0) { m_pBitmapInfoHeader->biColors = m_numberOfColors; }
		DWORD colorTableSize = m_numberOfColors * sizeof(RGBQUAD);
		m_pData = pbmp + colorTableSize;
		if (m_pRGB == (RGBQUAD*)m_pData)//没有调色板
		{
			m_pRGB = NULL;
		}
		m_pBitmapInfoHeader->biDataSize = getsize();
		m_bmptest = true;
		MessageBox(_T("载入成功！"));
	}
	else
	{
		m_bmptest = false;
		MessageBox(_T("载入失败！"));
	}


}

//获得图像宽度
unsigned int LSB_cleardlg::getwidth()
{
	return (unsigned int)m_pBitmapInfoHeader->biWidth;
}
//获得图像高度
unsigned int LSB_cleardlg::getheight()
{
	return (unsigned int)m_pBitmapInfoHeader->biHeight;
}

//获得得数据区大小
DWORD LSB_cleardlg::getsize()
{
	if (m_pBitmapInfoHeader->biDataSize != 0)
	{
		return m_pBitmapInfoHeader->biDataSize;
	}
	else
	{
		DWORD height = (DWORD)getheight();
		DWORD width = (DWORD)getwidth();
		return height * width;
	}
}

//获得颜色数
unsigned int LSB_cleardlg::getnumofcolors()
{
	int numberOfColors;

	if ((m_pBitmapInfoHeader->biColors == 0) && (m_pBitmapInfoHeader->biBitPerPixel < 9))
	{
		switch (m_pBitmapInfoHeader->biBitPerPixel)
		{
		case 1:
			numberOfColors = 2; break;
		case 4:
			numberOfColors = 16; break;
		case 8:
			numberOfColors = 256;
		}
	}
	else
	{
		numberOfColors = (int)m_pBitmapInfoHeader->biColors;
	}
	return numberOfColors;
}


//保存文件
void LSB_cleardlg::savefile(const char* filename)
{
	strcpy_s(m_fileName, filename);
	CFile myfile(m_fileName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);

	/*if (!myfile.Open(m_fileName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
	{
	MessageBox(_T("文件不存在！请先创建。"));
	return;
	}
	else
	myfile.Open(m_fileName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);*/


	myfile.Write((char*)m_pBitmapFileHeader, sizeof(BitmapFileHeader));
	myfile.Write((char*)m_pBitmapInfoHeader, sizeof(BitmapInfoHeader));
	myfile.Write((char*)pbmp, size);

	MessageBox("文件保存成功");
	myfile.Close();
}

//基于LSB的信息隐藏

int  LSB_cleardlg::Code(const char* textFileName)
{
	CFile txtfile;
	txtfile.Open(textFileName, CFile::typeBinary | CFile::modeRead);
	txtfile.Seek(0, txtfile.end);
	DWORD txtfile_len = txtfile.GetPosition();
	//判断位图是否够存储隐藏的信息
	DWORD colorTableSize = m_numberOfColors * sizeof(RGBQUAD);
	if ((size - colorTableSize)<txtfile_len * 8)
	{
		return 0; //不够隐藏
	}
	BYTE* pTextFile = new BYTE[txtfile_len + 1];
	txtfile.Seek(0, txtfile.begin);
	txtfile.Read((char*)pTextFile, txtfile_len);
	txtfile.Close();

	BYTE txtdata;
	for (int i = 0, k = 0; i< txtfile_len; ++i)
	{
		for (int j = 0; j<8; ++j)
		{
			txtdata = pTextFile[i] >> j;
			txtdata = txtdata & 0x01;
			if (txtdata == 0)
			{
				pbmp[k + 32] = pbmp[k + 32] & 0xfe;
			}
			else
			{
				pbmp[k + 32] = pbmp[k + 32] | 0x01;
			}
			++k;
		}
	}
	MessageBox("信息隐藏成功");

	//将文本长度写入前4个字节
	DWORD length;
	for (int i = 0; i<32; ++i)
	{
		length = txtfile_len >> i;
		length = length & 0x00000001;
		if (length == 0)
		{
			pbmp[i] = pbmp[i] & 0x1e;
		}
		else
		{
			pbmp[i] = pbmp[i] | 0x01;
		}
	}

	return 1;
}


//LSB解码
void  LSB_cleardlg::Decode(const char* textFileName)
{
	DWORD length = 0x00000000;
	BYTE bit;
	//获取bmp文件中txt文件长度
	for (int i = 0; i<32; ++i)
	{
		bit = pbmp[i] & 0x01;
		if (bit == 0)
		{
			length = length & 0x7fffffff;
		}
		else
		{
			length = length | 0x80000000;
		}
		if (i<31)	length = length >> 1;
	}

	BYTE* pTextFile = new BYTE[length];
	BYTE textData;
	for (int i = 0, k = 0; i<length * 8; ++i)
	{
		if (i && i % 8 == 0) { ++k; }
		textData = pbmp[i + 32] & 0x01;
		if (textData == 0)
		{
			pTextFile[k] = pTextFile[k] & 0x7f;
		}
		else
		{
			pTextFile[k] = pTextFile[k] | 0x80;
		}
		if (i % 8 != 7) pTextFile[k] = pTextFile[k] >> 1;
	}
	MessageBox("解码成功");

	CFile textFile;
	textFile.Open(textFileName, CFile::typeBinary | CFile::modeReadWrite| CFile::modeCreate);
	textFile.Write((char*)pTextFile, length);
	textFile.Close();
	delete pTextFile;
}

void LSB_cleardlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (bmpfile.GetLength()==0||txtfile.GetLength()==0) {
		MessageBox("文件名不完整请重新输入！");
		return;
	}
	bmpfilechar = bmpfile.GetBuffer(bmpfile.GetLength());
	bmpfile.ReleaseBuffer();
	loadfile(bmpfilechar);

	txtfilechar = txtfile.GetBuffer(bmpfile.GetLength());
	txtfile.ReleaseBuffer();
	Decode(txtfilechar);

	ShellExecute(NULL, "open", txtfile, NULL, NULL, SW_SHOW);
	CDialogEx::OnOK();
}


void LSB_cleardlg::OnBnClickedfileoutput1()
{
	CFileDialog dlg(TRUE, "", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "(*.bmp)|*.bmp||");
	if (dlg.DoModal() == IDOK)
	{
		CString fileName = dlg.GetPathName();
		SetDlgItemText(IDC_bmp2, fileName);
	}
}


void LSB_cleardlg::OnBnClickedfileoutput2()
{
	CFileDialog dlg(TRUE, "", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "(*.txt)|*.txt||");
	if (dlg.DoModal() == IDOK)
	{
		CString fileName = dlg.GetPathName();
		SetDlgItemText(IDC_txt2, fileName);
	}
}


