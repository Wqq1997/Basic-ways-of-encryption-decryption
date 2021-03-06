#pragma once


// permutation_main 对话框

class permutation_main : public CDialogEx
{
	DECLARE_DYNAMIC(permutation_main)

public:
	permutation_main(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~permutation_main();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_permutation_main };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	CString key;
	CString key_s;
	char* key_temp;
	char* key_s_temp;
	char* clear;			//一维数组明文temp

	CString cleartext;		//cstring明文 用于传递参数
	char cleararray[100][100];	//二维明文 用于实现算法
	CString clearone;			//一维明文 用于二维转一维

	CString ciphertext;	//cstring用于传递参数
	char cipherarray1[100][100];//二维密文 用于实现算法
	char cipherarray2[100][100];
	CString cipherone;//用于二维转一维


	int len;
	int row;
	void Set_clear();
	void Encrypt();
	void Decrypt();
	void Set_key();
	void Sort_key();

	afx_msg void OnBnClickedOk();

};
