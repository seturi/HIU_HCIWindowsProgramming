// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "Simple.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_mystrs.SetSize(3);
	m_index = -1;
}

CChildView::~CChildView()
{
	m_mystrs.RemoveAll();
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
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
	dc.TextOutW(100, 100, CString("안녕하세요"));
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//AfxMessageBox(CString("left mouse clicked!"));
	CString str;
	str.Format(CString("left click: (%d, %d) \n"), point.x, point.y);
	AfxMessageBox(str);
	if (m_index < 2)
		m_mystrs[++m_index] = str;
	else
		m_mystrs.Add(str);

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//AfxMessageBox(CString("right mouse clicked!"));
	CString str;
	int n;
	if (m_index < 2)
		n = m_index + 1;
	else
		n = m_mystrs.GetSize();
		str.Format(CString("왼쪽 클릭 횟수: %d \n\n"), n);

	for (int i = 0; i < n; i++)
	{
		CString str1;
		str1.Format(CString("%d 회: "), i + 1);
		str1 += m_mystrs[i];
		
		str += str1;
	}
	AfxMessageBox(str);

	CWnd::OnRButtonDown(nFlags, point);
}