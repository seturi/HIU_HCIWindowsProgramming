#pragma once
#include <afx.h>
class CMyData :
    public CObject
{
    DECLARE_SERIAL(CMyData)
public:
    CMyData();
    CMyData(CString& st, BOOL it, BOOL under, CPoint& pt);
    CMyData(const CMyData& t);
    ~CMyData();
    void Serialize(CArchive& ar);
    void initialize();
    CMyData& operator=(const CMyData& t);

public:
    CString m_str;
    BOOL m_bItalic, m_bUnderline;
    CPoint m_start;
};

