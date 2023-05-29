// CMyMDLESS.cpp: 구현 파일
//

#include "pch.h"
#include "Lab9.h"
#include "CMyMDLESS.h"
#include "afxdialogex.h"
#include "Lab9Doc.h"
#include "Lab9View.h"

// CMyMDLESS 대화 상자

IMPLEMENT_DYNAMIC(CMyMDLESS, CDialogEx)

CMyMDLESS::CMyMDLESS(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, m_str(_T(""))
	, m_font(0)
	, m_pView(NULL)
{

}

CMyMDLESS::~CMyMDLESS()
{
}

void CMyMDLESS::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STR, m_str);
	DDV_MaxChars(pDX, m_str, 20);
	DDX_CBIndex(pDX, IDC_FONT, m_font);
}


BEGIN_MESSAGE_MAP(CMyMDLESS, CDialogEx)
	ON_BN_CLICKED(IDAPPLY, &CMyMDLESS::OnBnClickedApply)
END_MESSAGE_MAP()


// CMyMDLESS 메시지 처리기


void CMyMDLESS::OnBnClickedApply()
{
	UpdateData(TRUE);
	m_pView->m_str = m_str;
	m_pView->m_font = m_font;
	// 뷰클래스 화면에 출력
	m_pView->Invalidate();
}


void CMyMDLESS::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	DestroyWindow();
}


void CMyMDLESS::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	m_pView->m_pDlg = NULL;
	delete this;
}
