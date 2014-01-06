// dbgoutdll.h : main header file for the dbgoutdll DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CdbgoutdllApp
// See dbgoutdll.cpp for the implementation of this class
//

class CdbgoutdllApp : public CWinApp
{
public:
	CdbgoutdllApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};


extern "C" void PASCAL EXPORT DbgOutStr(char *);