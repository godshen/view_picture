// SeePiCScrollView.cpp : implementation of the CSeePiCView class
//

#include "stdafx.h"
#include "SeePic.h"

#include "SeePicDoc.h"
#include "SeePiCView.h"
#include "Mainfrm.h"
#include "io.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeePiCView

IMPLEMENT_DYNCREATE(CSeePiCView, CScrollView)

BEGIN_MESSAGE_MAP(CSeePiCView, CScrollView)
//{{AFX_MSG_MAP(CSeePiCView)
ON_WM_SIZE()
ON_COMMAND(ID_ZOOMOUT, OnZoomout)
ON_COMMAND(ID_ZOOMIN, OnZoomin)
ON_COMMAND(ID_ZOOMFULL, OnZoomfull)
ON_COMMAND(ID_BEFORE, OnBefore)
ON_COMMAND(ID_AFTER, OnAfter)
//}}AFX_MSG_MAP
// Standard printing commands
ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSeePiCView construction/destruction

CSeePiCView::CSeePiCView()
{
	// TODO: add construction code here
	
	m_pImageObject = NULL;
	
	m_bCropBoxShowing = FALSE;
	CRect Rect( 10, 10, 200, 100 );
	m_pTracker = new CRectTracker( &Rect, CRectTracker::solidLine | CRectTracker::resizeOutside );
	sizezoom=1.0;
}


CSeePiCView::~CSeePiCView()
{
	if(m_pImageObject!=NULL)
		delete m_pImageObject;
	
}

BOOL CSeePiCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSeePiCView drawing

void CSeePiCView::OnDraw(CDC* pDC)
{
	CSeePicDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if( pDoc->m_bImageLoaded )
	{		
		CString PathName = pDoc->GetPathName ();
		
		if( m_pImageObject == NULL )
		{
			AfxMessageBox( "Could not create picture class!" );
			return;
		}					
		CSize SizeTotal;
		SizeTotal.cx = m_pImageObject->GetWidth();
		SizeTotal.cy = m_pImageObject->GetHeight();
		SetScrollSizes (MM_TEXT, SizeTotal);
		
		//	CMainFrame *pFrame = (CMainFrame *) AfxGetMainWnd();
		//
		//	pFrame->m_nWidth = m_pImageObject->GetWidth(); 
		//	pFrame->m_nHeight = m_pImageObject->GetHeight(); 
		//	pFrame->SetWindowPos( NULL, 0, 0, 2500, 2500, SWP_NOZORDER | SWP_NOMOVE );
		//		OnPrepareDC (pDC);
		//m_pImageObject->Reverse();
		
		m_pImageObject->Draw( pDC );
		
		if( m_pTracker != NULL && m_bCropBoxShowing )
			m_pTracker->Draw( pDC );
	}
	
}

/////////////////////////////////////////////////////////////////////////////
// CSeePiCView printing

BOOL CSeePiCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSeePiCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSeePiCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSeePiCView diagnostics

#ifdef _DEBUG
void CSeePiCView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSeePiCView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CSeePicDoc* CSeePiCView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSeePicDoc)));
	return (CSeePicDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSeePiCView message handlers

void CSeePiCView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
	CSeePicDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	BeginWaitCursor ();
	if(m_pImageObject!=NULL)
		delete m_pImageObject;
	m_pImageObject = new CImageObject(	pDoc->FileStr.GetBuffer( 3 ), GetDC() );
	EndWaitCursor ();
	if( GetFocus() == this ) m_pImageObject->SetPalette(  GetDC() );
	o_height=m_pImageObject->GetHeight();
	o_wide=m_pImageObject->GetWidth();
}

void CSeePiCView::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

void CSeePiCView::OnZoomout() 
{
	// TODO: Add your command handler code here
	sizezoom=sizezoom*1.5;
	m_pImageObject->Load(GetDocument()->GetPathName());
	int newwidth = m_pImageObject->GetWidth()*sizezoom;
	int newheight= m_pImageObject->GetHeight()*sizezoom;
	m_pImageObject->Stretch(newwidth,newheight);
	Invalidate();
}

void CSeePiCView::OnZoomin() 
{
	// TODO: Add your command handler code here
		sizezoom=sizezoom/1.5;
	int newwidth = m_pImageObject->GetWidth()/1.5;
	int newheight= m_pImageObject->GetHeight()/1.5;
	if((newwidth<=2)||(newheight<=2))
		return;
	
	m_pImageObject->Stretch(newwidth,newheight);
	Invalidate();
}

void CSeePiCView::OnZoomfull() 
{
	// TODO: Add your command handler code here
	m_pImageObject->Stretch(o_wide,o_height);
	Invalidate();
}
#include <direct.h>
CString Search(CString curstr,bool b_after);

void CSeePiCView::OnBefore() 
{
	// TODO: Add your command handler code here
	CString str=Search(GetDocument()->GetPathName(),false);
	if(str=="")
		return;
	AfxGetApp()->OpenDocumentFile(str);
}

void CSeePiCView::OnAfter() 
{
	
	CString str=Search(GetDocument()->GetPathName(),true);
	if(str=="")
		return;
	AfxGetApp()->OpenDocumentFile(str);
}

char buffer[1000];

CString Search(CString curstr,bool b_after)
{
	long handle;
	if(curstr.IsEmpty())
		return "";
	if(_getcwd( buffer, 1000)==NULL)
	{
		AfxMessageBox("û�е�ǰ·��,���һ��ͼ���ļ�!");
		return "";
	}
	
	CString m_sbefore="";
	CString m_sPartname;
	int len = curstr.GetLength();
	int i;
	for(i = len-1;curstr[i] != '\\';i--)
		m_sPartname.Insert(0,curstr[i]);
	i++;
	while(i--<0)
		buffer[i]=curstr[i];
	if (_chdir(buffer) != 0)
		return "";
	
	bool b_notfinde=false;
	struct _finddata_t filestruct;
	//��ʾ���ҵ���·����� 
	// ��ʼ���ҹ���, �ҵ���ǰĿ¼�µĵ�һ��ʵ��(�ļ�����Ŀ¼)�� 
	// �壪���ʾ�����κε��ļ�����Ŀ¼, filestructΪ���ҽ�� 
	//handle = _findfirst("*.bmp", &filestruct);
	// ���handleΪ��1, ��ʾ��ǰĿ¼Ϊ��, ��������Ҷ�����
	
	// ����ҵ��ĵ�һ��ʵ���Ƿ���һ��Ŀ¼(filestruct.nameΪ������) 
	handle = _findfirst("*", &filestruct);
	do{
		if((handle ==-1)) 
			break; 
		if( ::GetFileAttributes(filestruct.name) & FILE_ATTRIBUTE_DIRECTORY )
		{
			continue ;
		}
		CString Filename=filestruct.name;
		{
			CString tailstr;
			tailstr = Filename.Mid(Filename.GetLength()-3);
			tailstr.MakeUpper();
			Filename.MakeUpper();
			m_sPartname.MakeUpper();
			//BMP Files(*.BMP)|*.BMP|GIF Files(*.GIF)|*.GIF|PCX Files(*.PCX)|*.PCX|Targa Files(*.TGA)|*.TGA|Jpeg Files(*.JPG)|*.JPG|Tif Files(*.TIF)|*.TIF||";
			if((tailstr=="BMP")||(tailstr=="BMP")||(tailstr=="GIF")||(tailstr=="PCX")\
				||(tailstr=="TGA")||(tailstr=="TIF")||(tailstr=="JPG"))
			{
				//
				if(b_after)
				{
					if(b_notfinde==false)
					{
						if(m_sPartname==Filename)
							b_notfinde=true;
					}
					else
					{
						_findclose(handle);
						return Filename;
					}
				}
				else
				{
					if(m_sPartname==Filename)
					{
						_findclose(handle);
						if(m_sbefore=="")
						{
							AfxMessageBox("�Ѿ������һ��ͼ���ļ�!");
						}
						return m_sbefore;
					}
					b_notfinde=true;
					m_sbefore = Filename;
					
				}
				
				
			}
			
			
			
		}
		
		
	} while(_findnext(handle, &filestruct)==0);
	_findclose(handle);
	if(b_after)
	{
		AfxMessageBox("�Ѿ��������һ��ͼ���ļ�!");

	}
	else
	{
		AfxMessageBox("�Ѿ������һ��ͼ���ļ�!");
	}
	return "";
} 

char szFilter[] = "BMP Files(*.BMP)|*.BMP|GIF Files(*.GIF)|*.GIF|PCX Files(*.PCX)|*.PCX|Targa Files(*.TGA)|*.TGA|Jpeg Files(*.JPG)|*.JPG|Tif Files(*.TIF)|*.TIF||";
