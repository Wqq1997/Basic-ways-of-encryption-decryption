#pragma once


// des_show 对话框

class des_show : public CDialogEx
{
	DECLARE_DYNAMIC(des_show)

public:
	des_show(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~des_show();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_des_show };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString ciphertextB="";
	CString cleartextB="";
};
