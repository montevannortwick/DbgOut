// DbgOut.h : main header file for the DBGOUT application
//

#if !defined(AFX_DBGOUT_H__B8054248_ACFC_11D1_961F_204C4F4F5020__INCLUDED_)
#define AFX_DBGOUT_H__B8054248_ACFC_11D1_961F_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDbgOutApp:
// See DbgOut.cpp for the implementation of this class
//

class CDbgOutApp : public CWinApp
{
public:
	CDbgOutApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDbgOutApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDbgOutApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    HANDLE m_monoInstance;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBGOUT_H__B8054248_ACFC_11D1_961F_204C4F4F5020__INCLUDED_)
