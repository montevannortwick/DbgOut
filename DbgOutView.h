// DbgOutView.h : interface of the CDbgOutView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBGOUTVIEW_H__B8054250_ACFC_11D1_961F_204C4F4F5020__INCLUDED_)
#define AFX_DBGOUTVIEW_H__B8054250_ACFC_11D1_961F_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDbgOutView : public CEditView
{
protected: // create from serialization only
	CDbgOutView();
	DECLARE_DYNCREATE(CDbgOutView)

// Attributes
public:
	CDbgOutDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDbgOutView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDbgOutView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    BOOL m_wordWrap;

// Generated message map functions
protected:
	//{{AFX_MSG(CDbgOutView)
	afx_msg void OnWordWrap();
	afx_msg void OnUpdateWordWrap(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DbgOutView.cpp
inline CDbgOutDoc* CDbgOutView::GetDocument()
   { return (CDbgOutDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBGOUTVIEW_H__B8054250_ACFC_11D1_961F_204C4F4F5020__INCLUDED_)
