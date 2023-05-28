// B911037 김순욱
// Lab8View.cpp: CLab8View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Lab8.h"
#endif

#include "Lab8Doc.h"
#include "Lab8View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLab8View

IMPLEMENT_DYNCREATE(CLab8View, CFormView)

BEGIN_MESSAGE_MAP(CLab8View, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_BUTTON_PUSH, &CLab8View::OnBnClickedButtonPush)
	ON_STN_DBLCLK(IDC_MTFILE, &CLab8View::OnStnDblclickMtfile)
	ON_EN_CHANGE(IDC_EDIT1, &CLab8View::OnEnChangeEdit1)
	ON_EN_MAXTEXT(IDC_EDIT1, &CLab8View::OnEnMaxtextEdit1)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CLab8View::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CLab8View::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_ToRight, &CLab8View::OnBnClickedButtonToright)
	ON_BN_CLICKED(IDC_BUTTON_ToLeft, &CLab8View::OnBnClickedButtonToleft)
	ON_LBN_DBLCLK(IDC_LIST_LEFT, &CLab8View::OnLbnDblclkListLeft)
	ON_LBN_DBLCLK(IDC_LIST_RIGHT, &CLab8View::OnLbnDblclkListRight)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()

// CLab8View 생성/소멸

CLab8View::CLab8View() noexcept
	: CFormView(IDD_LAB8_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CLab8View::~CLab8View()
{
}

void CLab8View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK, m_checkbox);
	DDX_Control(pDX, IDC_3STATE, m_3state);
	DDX_Control(pDX, IDC_RADIO1, m_radio1);
	DDX_Control(pDX, IDC_RADIO2, m_radio2);
	DDX_Control(pDX, IDC_MTFILE, m_meta);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT3, m_readonly);
	DDX_Control(pDX, IDC_LIST_LEFT, m_left);
	DDX_Control(pDX, IDC_LIST_RIGHT, m_right);
	DDX_Control(pDX, IDC_EDIT_ADD, m_addstr);
	DDX_Control(pDX, IDC_SCROLLBAR_RED, m_red);
	DDX_Control(pDX, IDC_SCROLLBAR_GREEN, m_green);
	DDX_Control(pDX, IDC_EDIT_RED, m_red_value);
}

BOOL CLab8View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CLab8View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	// 컨트롤 초기화
	m_checkbox.SetCheck(1);
	m_3state.SetCheck(2);
	m_radio1.SetCheck(0);
	m_radio2.SetCheck(1);

	m_meta.SetEnhMetaFile(GetEnhMetaFileW(CString("test.emf")));
	m_edit1.SetLimitText(15);

	m_left.AddString(CString("사과"));
	m_left.AddString(CString("딸기"));
	m_left.AddString(CString("파인애플"));
	m_left.AddString(CString("복숭아"));
	
	m_red.SetScrollRange(0, 255);
	m_green.SetScrollRange(0, 255);
	m_red.SetScrollPos(150);
	m_green.SetScrollPos(150);
	CString str("150");
	m_red_value.SetWindowTextW(str);
}


// CLab8View 인쇄

BOOL CLab8View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CLab8View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CLab8View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CLab8View::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}


// CLab8View 진단

#ifdef _DEBUG
void CLab8View::AssertValid() const
{
	CFormView::AssertValid();
}

void CLab8View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CLab8Doc* CLab8View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLab8Doc)));
	return (CLab8Doc*)m_pDocument;
}
#endif //_DEBUG


// CLab8View 메시지 처리기


void CLab8View::OnBnClickedButtonPush()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int state_checkbox = m_checkbox.GetCheck();
	int state_3state = m_3state.GetCheck();
	int state_radio1 = m_radio1.GetCheck();
	int state_radio2 = m_radio2.GetCheck();
	CString str;
	str.Format(_T("버튼 상태: %d, %d, %d, %d"),
		state_checkbox, state_3state, state_radio1, state_radio2);
	MessageBox(str, _T("Button1 예제"), MB_ICONINFORMATION);
}


void CLab8View::OnStnDblclickMtfile()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	MessageBox(CString("meta file double clicked"));
}


void CLab8View::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	m_edit1.GetWindowTextW(str);
	m_readonly.SetWindowTextW(str);
}


void CLab8View::OnEnMaxtextEdit1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	MessageBox(CString("15자 이상 불가합니다"));
}


void CLab8View::OnBnClickedButtonAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	m_addstr.GetWindowTextW(str);
	m_left.AddString(str);
	m_addstr.SetWindowTextW(CString(""));
}


void CLab8View::OnBnClickedButtonDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nIndex = m_left.GetCurSel();
	if (nIndex != LB_ERR) {
		CString str;
		m_left.DeleteString(nIndex);
		AfxGetMainWnd()->SetWindowText(_T("왼쪽에서 삭제됨..."));
	}
	
}


void CLab8View::OnBnClickedButtonToright()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nIndex = m_left.GetCurSel();
	if (nIndex != LB_ERR) {
		CString str;
		m_left.GetText(nIndex, str);
		m_left.DeleteString(nIndex);
		m_left.SetCurSel(nIndex); // 삭제된 다음 위치의 항목이 자동 선택됨
		m_right.AddString(str);
		AfxGetMainWnd()->SetWindowText(_T("왼쪽에서 오른쪽으로..."));
	}
}


void CLab8View::OnBnClickedButtonToleft()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nIndex = m_right.GetCurSel();
	if (nIndex != LB_ERR) {
		CString str;
		m_right.GetText(nIndex, str);
		m_right.DeleteString(nIndex);
		m_right.SetCurSel(nIndex); // 삭제된 다음 위치의 항목이 자동 선택됨
		m_left.AddString(str);
		AfxGetMainWnd()->SetWindowText(_T("오른쪽에서 왼쪽으로..."));
	}
}


void CLab8View::OnLbnDblclkListLeft()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nIndex = m_left.GetCurSel();
	if (nIndex != LB_ERR) {
		CString str;
		m_left.GetText(nIndex, str);
		m_left.DeleteString(nIndex);
		m_left.SetCurSel(nIndex); // 삭제된 다음 위치의 항목이 자동 선택됨
		m_right.AddString(str);
		AfxGetMainWnd()->SetWindowText(_T("왼쪽에서 오른쪽으로..."));
	}
}


void CLab8View::OnLbnDblclkListRight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nIndex = m_right.GetCurSel();
	if (nIndex != LB_ERR) {
		CString str;
		m_right.GetText(nIndex, str);
		m_right.DeleteString(nIndex);
		m_right.SetCurSel(nIndex); // 삭제된 다음 위치의 항목이 자동 선택됨
		m_left.AddString(str);
		AfxGetMainWnd()->SetWindowText(_T("오른쪽에서 왼쪽으로..."));
	}
}


void CLab8View::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString str;
	int pos;
	int delta = 0;
	if (pScrollBar != NULL) { // 스크롤바 컨트롤에서 발생한 메시지이면...
		if (pScrollBar->GetSafeHwnd() == m_red.GetSafeHwnd()) {
			switch (nSBCode) {
				case SB_THUMBTRACK:
					pScrollBar->SetScrollPos(nPos);
					str.Format(CString("%d"), nPos);
					m_red_value.SetWindowTextW(str);
					break;
				case SB_LINELEFT:
					delta = -4;
					break;
				case SB_LINERIGHT:
					delta = 4;
					break;
				case SB_PAGELEFT:
					delta = -20;
					break;
				case SB_PAGERIGHT:
					delta = 20;
					break;
			}
			if (delta != 0)
			{
				pos = pScrollBar->GetScrollPos();
				pScrollBar->SetScrollPos(pos + delta);
				str.Format(CString("%d"), pos);
				m_red_value.SetWindowTextW(str);
			}
			Invalidate();
		}
	}
	else // 윈도우 스크롤바에서 발생한 메시지이면...
		CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CLab8View::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int pos;
	int delta = 0;
	if (pScrollBar != NULL) { // 스크롤바 컨트롤에서 발생한 메시지이면...
		if (pScrollBar->GetSafeHwnd() == m_green.GetSafeHwnd()) {
			switch (nSBCode) {
			case SB_THUMBTRACK:
				pScrollBar->SetScrollPos(nPos);
				break;
			case SB_LINEUP:
				delta = -4;
				break;
			case SB_LINEDOWN:
				delta = 4;
				break;
			case SB_PAGEUP:
				delta = -20;
				break;
			case SB_PAGEDOWN:
				delta = 20;
				break;
			}
			if (delta != 0) {
				pos = pScrollBar->GetScrollPos();
				pScrollBar->SetScrollPos(pos + delta);
			}
			Invalidate();
		}
	}
	else // 윈도우 스크롤바에서 발생한 메시지이면...
		CFormView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CLab8View::OnDraw(CDC* pDC)
{
	int r = m_red.GetScrollPos();
	int g = m_green.GetScrollPos();

	CBrush br(RGB(r, g, 150));
	pDC->SelectObject(&br);
	pDC->SelectClipPath(NULL_PEN);
	CRect rect;
	GetClientRect(&rect);
	pDC->Rectangle(rect);
}