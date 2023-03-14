#include <afxwin.h>

// Ŭ���� �����
class CHelloApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};
class CMainFrame : public CFrameWnd
{
public:
	CMainFrame();
protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};

// ���� ���α׷� ��ü
CHelloApp theApp;

// Ŭ���� ���Ǻ�
BOOL CHelloApp::InitInstance()
{
	m_pMainWnd = new CMainFrame;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}
CMainFrame::CMainFrame()
{
	Create(NULL, _T("HelloMFC Application"));
}
void CMainFrame::OnPaint()
{
	CPaintDC dc(this);
	dc.TextOut(100, 100, _T("Hello, MFC"), 10);
}
void CMainFrame::OnLButtonDown(UINT nFlags, CPoint point)
{
	MessageBox(_T("���콺�� Ŭ���߽��ϴ�. "), _T("���콺 �޽���"));
}

// �޽�����
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()