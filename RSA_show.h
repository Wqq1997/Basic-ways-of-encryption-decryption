#pragma once


// RSA_show 对话框

class RSA_show : public CDialogEx
{
	DECLARE_DYNAMIC(RSA_show)

public:
	RSA_show(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~RSA_show();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RSA_show };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeRsacleartextb();
	int n2;
	int e2;
	int d2;
	int ciphertextB;
	int cleartextB;
};
