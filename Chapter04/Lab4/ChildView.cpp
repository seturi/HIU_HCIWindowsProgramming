// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "Lab4.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
	m_mypts.RemoveAll();
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	POSITION pos = m_mypts.GetHeadPosition();
	while (pos != NULL) 
	{
		CPoint m_pt = m_mypts.GetNext(pos);

		CFont font;
		font.CreatePointFont(300, CString("Arial"));
		dc.SelectObject(&font);

		CRect rect(m_pt.x - 100, m_pt.y - 50, m_pt.x + 100, m_pt.y + 50);
		dc.Rectangle(&rect);

		dc.SetTextColor(RGB(0, 0, 255));
		dc.SetBkColor(RGB(255, 255, 0));
		dc.DrawText(CString("Hello HCI"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_mypts.AddTail(point);
	Invalidate();
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);

	// Rectangle
	dc.SelectStockObject(BLACK_PEN);
	dc.SelectStockObject(NULL_BRUSH);
	CRect rect(point.x - 100, point.y - 100, point.x + 100, point.y + 100);
	dc.Rectangle(&rect);

	// Ellipse
	CPen pen1(PS_DOT, 1, RGB(255, 0, 0));
	dc.SelectObject(&pen1);
	dc.SelectStockObject(LTGRAY_BRUSH);
	dc.Ellipse(point.x - 100, point.y - 100, point.x + 100, point.y + 100);

	// Polygon
	CPen pen2(PS_SOLID, 1, RGB(0, 255, 0));
	CBrush br2(HS_DIAGCROSS, RGB(255, 0, 0));
	dc.SelectObject(&pen2);
	dc.SelectObject(&br2);
	POINT points[] = { {point.x, point.y - 100}, {point.x + 100, point.y}, {point.x, point.y + 100}, {point.x - 100, point.y} };
	dc.Polygon(points, 4);
}
