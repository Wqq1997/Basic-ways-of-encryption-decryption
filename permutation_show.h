#pragma once


// permutation_show 对话框

class permutation_show : public CDialogEx
{
	DECLARE_DYNAMIC(permutation_show)

public:
	permutation_show(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~permutation_show();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_permutation_show };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString ciphertextB;
	CString cleartextB;
	afx_msg void OnBnClickedOk();
};
