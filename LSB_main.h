#pragma once

// LSB_main 对话框
class LSB_main : public CDialogEx
{
	DECLARE_DYNAMIC(LSB_main)

public:
	LSB_main(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~LSB_main();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LSB_main };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLsbcipher();
	afx_msg void OnBnClickedLsbclear();
};
