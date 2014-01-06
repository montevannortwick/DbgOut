// MainFrame.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "DbgOutApp.h"
#include "DbgOut.h"
#include "DbgOutApp.h"

extern CDbgOutApp g_application;

#include "MainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_COPYDATA()
	ON_COMMAND(ID_ALWAYSONTOP, OnAlwaysOnTop)
	ON_UPDATE_COMMAND_UI(ID_ALWAYSONTOP, OnUpdateAlwaysOnTop)
	ON_COMMAND(ID_SHOWTRACE, OnShowTRACE)
	ON_UPDATE_COMMAND_UI(ID_SHOWTRACE, OnUpdateShowTRACE)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

BOOL CMainFrame::m_showTRACE = FALSE;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame() :
    m_topMost (FALSE)
{
    unsigned addr;
    HANDLE h;
    if ((h = (HANDLE)::_beginthreadex (NULL, 0,
                                       _ThreadProcedureForOutputDebugString,
                                       LPVOID(this),
                                       0,
                                       &addr)) == NULL)
    {
        return;
    }

    ::CloseHandle (h);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    SetWindowText (g_dbgOut);

    if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

    if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.style &= ~FWS_ADDTOTITLE;

    if ( ! CFrameWnd::PreCreateWindow(cs))
        return FALSE;

    // One-time initialization: register new class
    // with same info, but different name and style.
    // Get data for AfxControlBar    
    WNDCLASS wc;
    VERIFY(::GetClassInfo(AfxGetInstanceHandle(), cs.lpszClass, &wc));
    // Change name and style
    wc.lpszClassName = g_dbgOutwindowClassName;    
    wc.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    VERIFY(AfxRegisterClass(&wc));

    cs.lpszClass = g_dbgOutwindowClassName;
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCopyData(CWnd* /*pWnd*/, COPYDATASTRUCT* pCopyDataStruct) 
{
    if (pCopyDataStruct->lpData == NULL)
        return TRUE;

    TCHAR affi [1025];
    if (pCopyDataStruct->dwData == 0xFEFF)
    {
        // UNICODE
        wsprintf (affi, "%S", (LPCTSTR)pCopyDataStruct->lpData);
    }
    else
    {
        // not UNICODE
        wsprintf (affi, "%s", (LPCTSTR)pCopyDataStruct->lpData);
    }

    WriteText (affi);

	return TRUE;
}


void CMainFrame::WriteText(LPCTSTR pText)
{
    char affi [1025];
    int nSize = sizeof(affi);
    strncpy (affi +1, pText, nSize-1);  // we keep some space to do p-1
    //char * pResult = strncpy (affi +1, pText, nSize-1);  // we keep some space to do p-1
    //strncpy_s (affi +1, sizeof(affi) -1, pText, sizeof(affi) -1);  // we keep some space to do p-1
    //strncpy_s (affi +1, sizeof(affi), pText, strlen(pText)+1);  // we keep some space to do p-1 (added by Monte 3-16-9)
    affi[1024] = '\0';
    affi[0] = '\0';

    char *p;
    char *pAffi = affi;
    pAffi++;
    if ((p = strchr(pAffi, '\n')) == NULL)
    {
        WriteLine (pAffi);
    }
    else
    {
        while (p)
        {
            if (*(p-1) == '\r')
                *(p-1) = '\0';
            else
                *p = '\0';
            WriteLine (pAffi);
            WriteLine ("\r\n");
            pAffi = ++p;
            if ((p = strchr(pAffi, '\n')) == NULL)
                WriteLine (pAffi);
        }
    }

}

void CMainFrame::WriteLine(LPCTSTR pText)
{
    if (*pText == '\0')
        return;

    CEditView *pEditView = (CEditView*)GetActiveView();
    CEdit &edit = pEditView->GetEditCtrl();

    int n = pEditView->GetBufferLength();
    edit.SetSel (n, n);
    edit.ReplaceSel (pText);
}

void CMainFrame::OnAlwaysOnTop() 
{
    if (m_topMost)
    {
        SetWindowPos (&wndNoTopMost, 0, 0, 0, 0,
                      SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
        m_topMost = FALSE;

    }
    else
    {
        SetWindowPos (&wndTopMost, 0, 0, 0, 0,
                      SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
        m_topMost = TRUE;
    }
}

void CMainFrame::OnUpdateAlwaysOnTop(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck (m_topMost);
}


// Based on code from DBMon 
// Copyright (c) 1990  Microsoft Corporation
// Abstract:  
//    A simple program to print strings passed to OutputDebugString when 
//    the app printing the strings is not being debugged.  
// Author:  
//    Kent Forschmiedt (kentf) 30-Sep-1994
unsigned __stdcall CMainFrame::_ThreadProcedureForOutputDebugString (void * /*pThis*/)
{
    HANDLE  hAckEvent;
    HANDLE  hReadyEvent;
    HANDLE  hSharedFile;
    LPVOID  pSharedMem;
    LPSTR   pString;
    DWORD   ret;
    DWORD   lastPid;
    LPDWORD pThisPid;

    hAckEvent = ::CreateEvent(NULL, FALSE, FALSE, "DBWIN_BUFFER_READY");
    if ( ! hAckEvent) 
    {
        ::MessageBox (NULL,
                      "Unable to create synchronization object", 
                      "_ThreadProcedureForOutputDebugString", 
                      MB_OK | MB_TOPMOST);
        exit(1);
    }

    hReadyEvent = ::CreateEvent(NULL, FALSE, FALSE, "DBWIN_DATA_READY");
    if ( ! hReadyEvent) 
    {
        ::MessageBox (NULL,
                      "Unable to create synchronization object", 
                      "_ThreadProcedureForOutputDebugString", 
                      MB_OK | MB_TOPMOST);
        exit(1);
    }

    hSharedFile = ::CreateFileMapping ((HANDLE)-1,
                                       NULL,
                                       PAGE_READWRITE,
                                       0,
                                       4096,
                                       "DBWIN_BUFFER");

    if ( ! hSharedFile) 
    {
        ::MessageBox (NULL,
                      "Unable to create file mapping object", 
                      "_ThreadProcedureForOutputDebugString", 
                      MB_OK | MB_TOPMOST);
        exit(1);
    }

    pSharedMem = ::MapViewOfFile (hSharedFile,
                                  FILE_MAP_READ,
                                  0,
                                  0,
                                  512);

    if ( ! pSharedMem) 
    {
        ::MessageBox (NULL,
                      "Unable to map shared memory", 
                      "_ThreadProcedureForOutputDebugString", 
                      MB_OK | MB_TOPMOST);
        exit(1);
    }

    pString = (LPSTR)pSharedMem + sizeof(DWORD);
    pThisPid = (DWORD*)pSharedMem;

    lastPid = 0xffffffff;

    SetEvent(hAckEvent);

    for (;;) 
    {
        ret = ::WaitForSingleObject(hReadyEvent, INFINITE);

        if (ret != WAIT_OBJECT_0) 
        {
            ::MessageBox (NULL,
                          "Wait failed", 
                          "_ThreadProcedureForOutputDebugString", 
                          MB_OK | MB_TOPMOST);
            exit(1);

        } 
        else 
        {
            if (lastPid != *pThisPid) 
                lastPid = *pThisPid;

            if (m_showTRACE)
                DbgOut ("\t pid %3u : %s", lastPid, pString);
            SetEvent (hAckEvent);

        }

    }

    return 0;
}

void CMainFrame::OnShowTRACE() 
{
    m_showTRACE = ! m_showTRACE;
}

void CMainFrame::OnUpdateShowTRACE(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck (m_showTRACE);
}
