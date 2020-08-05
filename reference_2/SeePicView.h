// SeePiCScrollView.h : interface of the CSeePiCView class
//
/////////////////////////////////////////////////////////////////////////////
#include "ImageObject.h"
#if !defined(AFX_SEEPICScrollView_H__FB7B80BD_6BC2_4E1E_B6B3_748F2D4CA469__INCLUDED_)
#define AFX_SEEPICScrollView_H__FB7B80BD_6BC2_4E1E_B6B3_748F2D4CA469__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSeePiCView : public CScrollView
{
protected: // create from serialization only
	CSeePiCView();
	DECLARE_DYNCREATE(CSeePiCView)

// Attributes
public:
	CSeePicDoc* GetDocument();
public:

	BOOL m_bCropBoxShowing;
	CRectTracker *m_pTracker;
	double sizezoom;
	CImageObject *m_pImageObject;
	CImageObject *m_pOrImageobject;
    int o_height,o_wide;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeePiCView)
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
	virtual ~CSeePiCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSeePiCView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnZoomout();
	afx_msg void OnZoomin();
	afx_msg void OnZoomfull();
	afx_msg void OnBefore();
	afx_msg void OnAfter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SeePiCScrollView.cpp
inline CSeePicDoc* CSeePiCView::GetDocument()
   { return (CSeePicDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEEPICScrollView_H__FB7B80BD_6BC2_4E1E_B6B3_748F2D4CA469__INCLUDED_)
