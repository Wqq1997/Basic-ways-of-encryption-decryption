#pragma once


// C_Caesar_Main 对话框

 class C_Caesar_Main : public CDialogEx
{
	DECLARE_DYNAMIC(C_Caesar_Main)

public:
	C_Caesar_Main(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~C_Caesar_Main();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Caesar_Main };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedluru();
	//凯撒
	int key=0;
	CString cleartext;
	CString ciphertext;
	void Set_alphabet();
	int searchnum(char);
	char alphabet[26];
	void Encrypt();
	void Decrypt();
	char* chartemp;
	char* chartemp1;
	//
	
	
 };
