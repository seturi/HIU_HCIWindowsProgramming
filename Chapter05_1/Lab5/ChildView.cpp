
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
	m_xPos = m_yPos = 50;
	m_bFill = false;
	m_bitmap.LoadBitmapW(IDB_BITMAP1);
	m_mystr = CString("");
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_SIZE()
	ON_WM_CHAR()
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
	CFont font;
	font.CreatePointFont(300, CString("돋움체"));
	dc.SelectObject(&font);
	CRect rect(0, 0, m_xMax, m_yMax);
	dc.SetTextColor(RGB(255, 0, 0));
	dc.SetBkColor(RGB(0, 255, 0));
	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(m_mystr, &rect, DT_CENTER);
	
	SetCaretPos(CPoint(m_xPos, m_yPos)); // 캐럿의 위치를 설정한다.
	ShowCaret(); // 캐럿을 화면에 보인다.
}



void CChildView::OnSetFocus(CWnd* pOldWnd)
{
	m_bFill = !m_bFill;

	if(!m_bFill)
		CreateSolidCaret(20, 20); // 캐럿을 생성한다.
	else
		CreateCaret(&m_bitmap);
	SetCaretPos(CPoint(m_xPos, m_yPos)); // 캐럿의 위치를 설정한다.
	ShowCaret(); // 캐럿을 화면에 보인다.
}


void CChildView::OnKillFocus(CWnd* pNewWnd)
{
	HideCaret(); // 캐럿을 숨긴다.
	::DestroyCaret(); // 캐럿을 파괴한다.

}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar) {
	case VK_LEFT:
		m_xPos -= 20;
		break;
	case VK_RIGHT:
		m_xPos += 20;
		break;
	case VK_UP:
		m_yPos -= 20;
		break;
	case VK_DOWN:
		m_yPos += 20;
		break;
	case VK_SPACE:
		m_bFill = !m_bFill;
	}
	// 0 <= m_xPos <= m_xMax-20
	m_xPos = min(max(0, m_xPos), m_xMax - 20);
	// 0 <= m_yPos <= m_yMax-20
	m_yPos = min(max(0, m_yPos), m_yMax - 20);
	Invalidate();

}


void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_xMax = cx;
	m_yMax = cy;
}


void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// [Backspace] 키 입력 시 맨 마지막 글자를 삭제한다.
	if (nChar == _T('\b')) {
		if (m_mystr.GetLength() > 0)
			m_mystr.Delete(m_mystr.GetLength() - 1);
	}
	// 그 밖의 경우에는 동적 배열에 글자를 추가한다.
	else {
		m_mystr.AppendChar(nChar);
	}

	// 화면을 갱신한다.
	Invalidate();
}
