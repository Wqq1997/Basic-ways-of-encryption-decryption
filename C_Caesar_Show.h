#pragma once


// C_Caesar_Show 对话框

class C_Caesar_Show : public CDialogEx
{
	DECLARE_DYNAMIC(C_Caesar_Show)

public:
	C_Caesar_Show(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~C_Caesar_Show();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Caesar_show };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString ciphertextB;
	CString cleartextB;
};
