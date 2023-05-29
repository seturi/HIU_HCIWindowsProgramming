
// Lab9View.cpp: CLab9View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Lab9.h"
#endif

#include "Lab9Doc.h"
#include "Lab9View.h"
#include "CMyDialog.h"
#include "CMyMDLESS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLab9View

IMPLEMENT_DYNCREATE(CLab9View, CView)

BEGIN_MESSAGE_MAP(CLab9View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_COLOR_TEXTCOLOR, &CLab9View::OnColorTextcolor)
	ON_COMMAND(ID_COLOR_TEXTBGCOLOR, &CLab9View::OnColorTextbgcolor)
	ON_COMMAND(ID_FONT_SELECT, &CLab9View::OnFontSelect)
END_MESSAGE_MAP()

// CLab9View 생성/소멸

CLab9View::CLab9View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_str = CString("");
	m_font = 0;
	m_pDlg = NULL;
	m_textcolor = RGB(0, 0, 0);
	m_bgcolor = RGB(255, 255, 255);
	m_bf = false;
}

CLab9View::~CLab9View()
{
}

BOOL CLab9View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CLab9View 그리기

void CLab9View::OnDraw(CDC* pDC)
{
	CLab9Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CFont font;
	CString fontname;

	if (m_bf)
	{
		font.CreateFontIndirectW(&m_lf);
	}
	else // false면 기존방법 
	{
		if (m_font == 0) fontname = _T("굴림");
		else if (m_font == 1) fontname = _T("궁서");
		else if (m_font == 2) fontname = _T("바탕");
		font.CreatePointFont(400, fontname);
	}

	pDC->SetTextColor(m_textcolor);
	pDC->SetBkColor(m_bgcolor);
	pDC->SelectObject(&font);
	pDC->TextOut(10, 10, m_str);
}


// CLab9View 인쇄

BOOL CLab9View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CLab9View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CLab9View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CLab9View 진단

#ifdef _DEBUG
void CLab9View::AssertValid() const
{
	CView::AssertValid();
}

void CLab9View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLab9Doc* CLab9View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLab9Doc)));
	return (CLab9Doc*)m_pDocument;
}
#endif //_DEBUG


// CLab9View 메시지 처리기


void CLab9View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CMyDialog dlg;	// 지역변수로 정의
	m_bf = false;

	dlg.m_str = m_str;
	dlg.m_font = m_font; // 초기값 전달
	int res = dlg.DoModal();

	if (res == IDOK)
	{
		m_str = dlg.m_str;
		m_font = dlg.m_font;
		Invalidate();
	}
	else if (res == IDC_CLEAR)
	{
		m_str = CString("");
		m_font = 0;
		Invalidate();
	}
	if (m_pDlg != NULL)
	{
		m_pDlg->m_str = m_str;
		m_pDlg->m_font = m_font;
		// 비모드형 대화상자 변수값 --> 컨트롤로 전달해서 화면출력
		m_pDlg->UpdateData(FALSE);
	}
}


void CLab9View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_pDlg != NULL)
	{
		m_pDlg->SetFocus();
	}
	else
	{
		m_bf = false;
		m_pDlg = new CMyMDLESS();
		m_pDlg->m_pView = this;
		m_pDlg->m_str = m_str;
		m_pDlg->m_font = m_font;
		m_pDlg->Create(IDD_DIALOG2);
		m_pDlg->ShowWindow(SW_SHOW);
	}
}


void CLab9View::OnColorTextcolor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorDialog dlg(m_textcolor);
	if (dlg.DoModal() == IDOK)
	{
		m_textcolor = dlg.GetColor();
		Invalidate();
	}
}


void CLab9View::OnColorTextbgcolor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorDialog dlg(m_bgcolor, CC_FULLOPEN);
	if (dlg.DoModal() == IDOK)
	{
		m_bgcolor = dlg.GetColor();
		Invalidate();
	}
}


void CLab9View::OnFontSelect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFontDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		dlg.GetCurrentFont(&m_lf);
		m_textcolor = dlg.GetColor();
		m_bf = true;
		Invalidate();
	}
}
