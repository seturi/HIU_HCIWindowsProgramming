
// Lab9View.h: CLab9View 클래스의 인터페이스
//

#pragma once
class CMyMDLESS;

class CLab9View : public CView
{
protected: // serialization에서만 만들어집니다.
	CLab9View() noexcept;
	DECLARE_DYNCREATE(CLab9View)

// 특성입니다.
public:
	CLab9Doc* GetDocument() const;

// 작업입니다.
public:
	CString m_str;
	int m_font;
	CMyMDLESS* m_pDlg; // 비모드형 대화상자 주소
	
	COLORREF m_textcolor, m_bgcolor;
	LOGFONT m_lf;
	bool m_bf;

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CLab9View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnColorTextcolor();
	afx_msg void OnColorTextbgcolor();
	afx_msg void OnFontSelect();
};

#ifndef _DEBUG  // Lab9View.cpp의 디버그 버전
inline CLab9Doc* CLab9View::GetDocument() const
   { return reinterpret_cast<CLab9Doc*>(m_pDocument); }
#endif

