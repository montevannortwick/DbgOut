// MainFrame.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRAME_H__B805424C_ACFC_11D1_961F_204C4F4F5020__INCLUDED_)
#define AFX_MAINFRAME_H__B805424C_ACFC_11D1_961F_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  
    // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
    
    BOOL m_topMost;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnAlwaysOnTop();
	afx_msg void OnUpdateAlwaysOnTop(CCmdUI* pCmdUI);
	afx_msg void OnShowTRACE();
	afx_msg void OnUpdateShowTRACE(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void WriteLine (LPCTSTR pText);
	void WriteText (LPCTSTR pText);

    static unsigned __stdcall _ThreadProcedureForOutputDebugString (void *pThis);
    static BOOL m_showTRACE;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRAME_H__B805424C_ACFC_11D1_961F_204C4F4F5020__INCLUDED_)
