#pragma once


// MD5_show 对话框

class MD5_show : public CDialogEx
{
	DECLARE_DYNAMIC(MD5_show)

public:
	MD5_show(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MD5_show();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MD5_show };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString ciphertextB;
};
