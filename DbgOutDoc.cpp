// DbgOutDoc.cpp : implementation of the CDbgOutDoc class
//

#include "stdafx.h"
#include "DbgOut.h"

#include "DbgOutDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDbgOutDoc

IMPLEMENT_DYNCREATE(CDbgOutDoc, CDocument)

BEGIN_MESSAGE_MAP(CDbgOutDoc, CDocument)
	//{{AFX_MSG_MAP(CDbgOutDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDbgOutDoc construction/destruction

CDbgOutDoc::CDbgOutDoc()
{
	// TODO: add one-time construction code here

}

CDbgOutDoc::~CDbgOutDoc()
{
}

BOOL CDbgOutDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDbgOutDoc serialization

void CDbgOutDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CDbgOutDoc diagnostics

#ifdef _DEBUG
void CDbgOutDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDbgOutDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDbgOutDoc commands

BOOL CDbgOutDoc::SaveModified() 
{
	return TRUE;  // never save something if it's not asking by the user
//	return CDocument::SaveModified();
}
