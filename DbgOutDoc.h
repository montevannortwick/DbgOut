// DbgOutDoc.h : interface of the CDbgOutDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBGOUTDOC_H__B805424E_ACFC_11D1_961F_204C4F4F5020__INCLUDED_)
#define AFX_DBGOUTDOC_H__B805424E_ACFC_11D1_961F_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CDbgOutDoc : public CDocument
{
protected: // create from serialization only
	CDbgOutDoc();
	DECLARE_DYNCREATE(CDbgOutDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDbgOutDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	protected:
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDbgOutDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDbgOutDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBGOUTDOC_H__B805424E_ACFC_11D1_961F_204C4F4F5020__INCLUDED_)
