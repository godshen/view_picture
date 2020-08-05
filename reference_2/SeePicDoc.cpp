// SeePicDoc.cpp : implementation of the CSeePicDoc class
//

#include "stdafx.h"
#include "SeePic.h"

#include "SeePicDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeePicDoc

IMPLEMENT_DYNCREATE(CSeePicDoc, CDocument)

BEGIN_MESSAGE_MAP(CSeePicDoc, CDocument)
	//{{AFX_MSG_MAP(CSeePicDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSeePicDoc construction/destruction

CSeePicDoc::CSeePicDoc()
{
	// TODO: add one-time construction code here
	m_bImageLoaded = FALSE;
}

CSeePicDoc::~CSeePicDoc()
{
}

BOOL CSeePicDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSeePicDoc serialization

void CSeePicDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSeePicDoc diagnostics

#ifdef _DEBUG
void CSeePicDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSeePicDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSeePicDoc commands

BOOL CSeePicDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
		m_bImageLoaded = TRUE;
	// TODO: Add your specialized creation code here
	FileStr= lpszPathName;
	
	return TRUE;
}

//char szFilter[] = "BMP Files(*.BMP)|*.BMP|GIF Files(*.GIF)|*.GIF|PCX Files(*.PCX)|*.PCX|Targa Files(*.TGA)|*.TGA|Jpeg Files(*.JPG)|*.JPG|Tif Files(*.TIF)|*.TIF||";

void CSeePicDoc::OnFileOpen() 
{
	static int nIndex = 1;

	CFileDialog FileDlg( TRUE, NULL, NULL, OFN_HIDEREADONLY, "Suport Files(*.BMP;*.GIF;*.PCX;*.TGA;*.JPG;*.TIF)|*.BMP;*.GIF;*.PCX;*.TGA;*.JPG;*.TIF|BMP Files(*.BMP)|*.BMP|GIF Files(*.GIF)|*.GIF|PCX Files(*.PCX)|*.PCX|Targa Files(*.TGA)|*.TGA|Jpeg Files(*.JPG)|*.JPG|Tif Files(*.TIF)|*.TIF||" );
	FileDlg.m_ofn.nFilterIndex = (DWORD) nIndex;

	if( FileDlg.DoModal() == IDOK ){
		CString PathName = FileDlg.GetPathName();
		PathName.MakeUpper();
		AfxGetApp()->OpenDocumentFile( PathName );
		UpdateAllViews(NULL);
		nIndex = (int) FileDlg.m_ofn.nFilterIndex;
	}

	
}

