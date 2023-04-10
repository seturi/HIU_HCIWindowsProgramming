
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "Lab5.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_start = m_end = CPoint(0, 0);
	m_bDraw = false;
	m_bRight = false;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
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
	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_bDraw = true;
	m_start = m_end = point;
	SetCapture();
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);

	ReleaseCapture();
	m_bDraw = false;
	m_end = point;
	dc.Ellipse(m_start.x, m_start.y, m_end.x, m_end.y);
	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bDraw && !m_bRight) 
	{
		CClientDC dc(this);
		//dc.SelectStockObject(NULL_BRUSH);
		dc.SetROP2(R2_NOTXORPEN);
		dc.Ellipse(m_start.x, m_start.y, m_end.x, m_end.y); // 그 전에 있던 start - end 타원 지우기
		
		m_end = point; // 마우스 움직인 위치까지 새로운 타원 그리기
		dc.Ellipse(m_start.x, m_start.y, m_end.x, m_end.y);
	}
	else if (m_bDraw && m_bRight)
	{
		CRgn rgn;
		rgn.CreateEllipticRgn(m_start.x, m_start.y, m_end.x, m_end.y);
		if (rgn.PtInRegion(point))
			// 사용자 정의 커서로 변경한다.
			::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR1));
		else
			// 표준 커서 중 하나로 변경한다.
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
	}
	CWnd::OnMouseMove(nFlags, point);
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	m_bRight = true;
	m_bDraw = true;
	CBrush br(HS_CROSS, RGB(0, 255, 0));
	dc.SelectObject(&br);
	dc.Ellipse(point.x - 200, point.y - 100, point.x + 200, point.y + 100);
	m_start = CPoint(point.x - 200, point.y - 100);
	m_end = CPoint(point.x + 200, point.y + 100);
	
	
	CRect rect(point.x - 200, point.y - 100, point.x + 200, point.y + 100);
	ClientToScreen(&rect);
	ClipCursor(&rect);
	CWnd::OnRButtonDown(nFlags, point);
}

void CChildView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	ClipCursor(NULL);
	CWnd::OnRButtonDblClk(nFlags, point);
}

void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_bRight = false;
	m_bDraw = false;
	CWnd::OnRButtonUp(nFlags, point);
}