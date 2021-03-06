#pragma once


// CMainDlg 对话框

class CMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMainDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_maindlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCaesar();
	afx_msg void OnBnClickedPermutation();
	afx_msg void OnBnClickeddes();
	afx_msg void OnBnClickedRsa();
	afx_msg void OnBnClickedMd5();
	afx_msg void OnBnClickedLsb();
};
