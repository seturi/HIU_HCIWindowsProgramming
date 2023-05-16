
// Lab7Doc.cpp: CLab7Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Lab7.h"
#endif

#include "Lab7Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLab7Doc

IMPLEMENT_DYNCREATE(CLab7Doc, CDocument)

BEGIN_MESSAGE_MAP(CLab7Doc, CDocument)
	ON_COMMAND(ID_STYLE_ITALIC, &CLab7Doc::OnStyleItalic)
	ON_COMMAND(ID_STYLE_UNDERLINE, &CLab7Doc::OnStyleUnderline)
	ON_UPDATE_COMMAND_UI(ID_STYLE_ITALIC, &CLab7Doc::OnUpdateStyleItalic)
	ON_UPDATE_COMMAND_UI(ID_STYLE_UNDERLINE, &CLab7Doc::OnUpdateStyleUnderline)
END_MESSAGE_MAP()


// CLab7Doc 생성/소멸

CLab7Doc::CLab7Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CLab7Doc::~CLab7Doc()
{
}

BOOL CLab7Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.
	m_data.initialize();
	m_mylist.RemoveAll();
	return TRUE;
}




// CLab7Doc serialization

void CLab7Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		m_data.Serialize(ar);
		//m_mylist.Serialize(ar);
		int num = m_mylist.GetCount();
		ar << num;
		POSITION pos = m_mylist.GetHeadPosition();
		for (int i = 0; i < num; i++) {
			CMyData temp = m_mylist.GetNext(pos);
			temp.Serialize(ar);
		}
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		m_data.Serialize(ar);
		//m_mylist.Serialize(ar);
		int num;
		ar >> num;
		for (int i = 0; i < num; i++) {
			CMyData temp;
			temp.Serialize(ar);
			m_mylist.AddTail(temp);
		}
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CLab7Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CLab7Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CLab7Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CLab7Doc 진단

#ifdef _DEBUG
void CLab7Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLab7Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLab7Doc 명령


void CLab7Doc::OnStyleItalic()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_data.m_bItalic = !m_data.m_bItalic;
	SetModifiedFlag();
	UpdateAllViews(NULL);
}


void CLab7Doc::OnStyleUnderline()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_data.m_bUnderline = !m_data.m_bUnderline;
	SetModifiedFlag();
	UpdateAllViews(NULL);
}


void CLab7Doc::OnUpdateStyleItalic(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_data.m_bItalic == TRUE);
}


void CLab7Doc::OnUpdateStyleUnderline(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_data.m_bUnderline == TRUE);
}
