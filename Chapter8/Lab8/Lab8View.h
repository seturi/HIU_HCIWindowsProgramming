
// Lab8View.h: CLab8View 클래스의 인터페이스
//

#pragma once


class CLab8View : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CLab8View() noexcept;
	DECLARE_DYNCREATE(CLab8View)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_LAB8_FORM };
#endif

// 특성입니다.
public:
	CLab8Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CLab8View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	CButton m_checkbox;
	CButton m_3state;
	CButton m_radio1;
	CButton m_radio2;
	afx_msg void OnBnClickedButtonPush();
	CStatic m_meta;
	afx_msg void OnStnDblclickMtfile();
	CEdit m_edit1;
	CEdit m_readonly;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnMaxtextEdit1();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
	CListBox m_left;
	CListBox m_right;
	afx_msg void OnBnClickedButtonToright();
	afx_msg void OnBnClickedButtonToleft();
	CEdit m_addstr;
	afx_msg void OnLbnDblclkListLeft();
	afx_msg void OnLbnDblclkListRight();
	CScrollBar m_red;
	CScrollBar m_green;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CEdit m_red_value;
	virtual void OnDraw(CDC* /*pDC*/);
};

#ifndef _DEBUG  // Lab8View.cpp의 디버그 버전
inline CLab8Doc* CLab8View::GetDocument() const
   { return reinterpret_cast<CLab8Doc*>(m_pDocument); }
#endif

