// DbgOutView.cpp : implementation of the CDbgOutView class
//

#include "stdafx.h"
#include "Resource.h"
#include "DbgOut.h"

#include "DbgOutDoc.h"
#include "DbgOutView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDbgOutView

IMPLEMENT_DYNCREATE(CDbgOutView, CEditView)

BEGIN_MESSAGE_MAP(CDbgOutView, CEditView)
	//{{AFX_MSG_MAP(CDbgOutView)
	ON_COMMAND(ID_WORDWRAP, OnWordWrap)
	ON_UPDATE_COMMAND_UI(ID_WORDWRAP, OnUpdateWordWrap)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDbgOutView construction/destruction

CDbgOutView::CDbgOutView() :
    m_wordWrap(FALSE)
{
}

CDbgOutView::~CDbgOutView()
{
}

BOOL CDbgOutView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
    if (m_wordWrap)
        cs.style &= ~(ES_AUTOHSCROLL | WS_HSCROLL);	// Enable word-wrapping
    else
    		cs.style |= ES_AUTOHSCROLL | WS_HSCROLL;




  return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CDbgOutView drawing

void CDbgOutView::OnDraw(CDC* /*pDC*/)
{
	CDbgOutDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDbgOutView printing

BOOL CDbgOutView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CDbgOutView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CDbgOutView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CDbgOutView diagnostics

#ifdef _DEBUG
void CDbgOutView::AssertValid() const
{
	CEditView::AssertValid();
}

void CDbgOutView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CDbgOutDoc* CDbgOutView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDbgOutDoc)));
	return (CDbgOutDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDbgOutView message handlers

void CDbgOutView::OnWordWrap() 
{
	// preserve original control's state.
	CFont* pFont = GetFont();
	int nLen = GetBufferLength();
	TCHAR* pSaveText = new TCHAR[GetBufferLength()+1];
	GetWindowText(pSaveText, nLen+1);

	// create new edit control with appropriate style and size.
	DWORD dwStyle = dwStyleDefault & ~(ES_AUTOHSCROLL | WS_HSCROLL | WS_VISIBLE);
	if (m_wordWrap)
		dwStyle |= ES_AUTOHSCROLL | WS_HSCROLL;

	CWnd* pParent = GetParent();
	CRect rect;
	GetWindowRect(rect);
	pParent->ScreenToClient(rect);
	CWnd* pFocus = GetFocus();

	UINT nID = GetDlgCtrlID();

	HWND hWnd = ::CreateWindowEx (WS_EX_CLIENTEDGE, 
                                  _T("edit"), NULL, 
                                  dwStyle,
		                          rect.left, 
                                  rect.top, 
                                  rect.right-rect.left, 
                                  rect.bottom-rect.top,
		                          pParent->m_hWnd, 
                                  (HMENU)nID, 
                                  AfxGetInstanceHandle(), 
                                  NULL);

	if (hWnd == NULL)
	{
		delete[] pSaveText;
		return;
	}

	// set the window text to nothing to make sure following set doesn't fail
	SetWindowText(NULL);

	// restore visual state
	::SetWindowText(hWnd, pSaveText);
	delete[] pSaveText;
	if (pFont != NULL)
	{
		ASSERT(pFont->m_hObject != NULL);
		::SendMessage(hWnd, WM_SETFONT, (WPARAM)pFont->m_hObject, 0);
	}

	// detach old window, attach new
	SetDlgCtrlID(nID+1);
	HWND hWndOld = Detach();
	::SetWindowLong(hWndOld, GWL_WNDPROC, (LONG)*GetSuperWndProcAddr());
	ASSERT(m_hWnd == NULL);
	SubclassWindow(hWnd);

/*    ASSERT(m_hWnd == hWnd);
	GetParentFrame()->SendMessage(WM_RECALCPARENT);*/
    
    GetClientRect(&rect);
	SetWindowPos(NULL, 0, 0, 0, 0,
		         SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER | SWP_SHOWWINDOW);
	SetWindowPos(NULL, 0, 0, 0, 0,
		         SWP_NOMOVE|SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER | SWP_DRAWFRAME);
	SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	UpdateWindow();

	// destroy old
	::SetWindowPos(hWndOld, NULL, 0, 0, 0, 0,
		           SWP_HIDEWINDOW|SWP_NOREDRAW|SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE|
		           SWP_NOZORDER);
	::DestroyWindow(hWndOld);

	// restore rest of state...
	GetEditCtrl().LimitText(nMaxSize);
	if (pFocus == this)
		SetFocus();

	// notify container that doc changed
//	GetDocument()->UpdateAllItems(NULL);

    m_wordWrap = ! m_wordWrap;
}

void CDbgOutView::OnUpdateWordWrap(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck ( ! ((GetStyle() & ES_AUTOHSCROLL)));
}

void CDbgOutView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
  CEdit& cntrlEdit = GetEditCtrl();
  cntrlEdit.SetLimitText(100 * 1000 * 1024); // 100M
	
}
