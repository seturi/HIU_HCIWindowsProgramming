// CRectView.cpp: 구현 파일
//

#include "pch.h"
#include "SDI.h"
#include "CRectView.h"
#include "SDIDoc.h"


// CRectView

IMPLEMENT_DYNCREATE(CRectView, CView)

CRectView::CRectView()
{

}

CRectView::~CRectView()
{
}

BEGIN_MESSAGE_MAP(CRectView, CView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CRectView 그리기

void CRectView::OnDraw(CDC* pDC)
{
	CSDIDoc* pDoc = (CSDIDoc*)GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
	pDC->SelectStockObject(LTGRAY_BRUSH);
	for (int i = 0; i < pDoc->m_rects.GetSize(); i++) {
		pDC->Rectangle(pDoc->m_rects[i]);
	}
}


// CRectView 진단

#ifdef _DEBUG
void CRectView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CRectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CRectView 메시지 처리기


void CRectView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CSDIDoc* pDoc = (CSDIDoc*)GetDocument();
	CRect rect(point.x - 20, point.y - 20, point.x + 20, point.y + 20);
	pDoc->m_rects.Add(rect);
	pDoc->UpdateAllViews(NULL);
	pDoc->SetModifiedFlag();
}
