
// 加解密View.cpp: C加解密View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "加解密.h"
#endif

#include "加解密Doc.h"
#include "加解密View.h"
#include "CMainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C加解密View

IMPLEMENT_DYNCREATE(C加解密View, CView)

BEGIN_MESSAGE_MAP(C加解密View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &C加解密View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_Menu, &C加解密View::OnMenu)
END_MESSAGE_MAP()

// C加解密View 构造/析构

C加解密View::C加解密View()
{
	// TODO: 在此处添加构造代码

}

C加解密View::~C加解密View()
{
}

BOOL C加解密View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// C加解密View 绘图

void C加解密View::OnDraw(CDC* /*pDC*/)
{
	C加解密Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// C加解密View 打印


void C加解密View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL C加解密View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void C加解密View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void C加解密View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void C加解密View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void C加解密View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// C加解密View 诊断

#ifdef _DEBUG
void C加解密View::AssertValid() const
{
	CView::AssertValid();
}

void C加解密View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C加解密Doc* C加解密View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C加解密Doc)));
	return (C加解密Doc*)m_pDocument;
}
#endif //_DEBUG


// C加解密View 消息处理程序


void C加解密View::OnMenu()
{
	// TODO: 在此添加命令处理程序代码
	CMainDlg MyDlg;
	MyDlg.DoModal();
}
