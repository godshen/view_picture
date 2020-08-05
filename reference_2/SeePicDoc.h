// SeePicDoc.h : interface of the CSeePicDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEEPICDOC_H__434EB03C_ACBF_43B9_B873_C0EB8BD036AA__INCLUDED_)
#define AFX_SEEPICDOC_H__434EB03C_ACBF_43B9_B873_C0EB8BD036AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "imageobject.h"

class CSeePicDoc : public CDocument
{
protected: // create from serialization only
	CSeePicDoc();
	DECLARE_DYNCREATE(CSeePicDoc)
 CString FileStr;
	CString DirStr;
// Attributes
public:

	BOOL m_bImageLoaded;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeePicDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSeePicDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSeePicDoc)
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEEPICDOC_H__434EB03C_ACBF_43B9_B873_C0EB8BD036AA__INCLUDED_)
