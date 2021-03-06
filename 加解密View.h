
// 加解密View.h: C加解密View 类的接口
//

#pragma once


class C加解密View : public CView
{
protected: // 仅从序列化创建
	C加解密View();
	DECLARE_DYNCREATE(C加解密View)

// 特性
public:
	C加解密Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~C加解密View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenu();
};

#ifndef _DEBUG  // 加解密View.cpp 中的调试版本
inline C加解密Doc* C加解密View::GetDocument() const
   { return reinterpret_cast<C加解密Doc*>(m_pDocument); }
#endif

