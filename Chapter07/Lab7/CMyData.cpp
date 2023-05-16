#include "pch.h"
#include "CMyData.h"

IMPLEMENT_SERIAL(CMyData, CObject, 1);
CMyData::CMyData()
{
	m_str = CString("");
	m_bItalic = m_bUnderline = FALSE;
	m_start = CPoint(0, 0);
}
CMyData::CMyData(CString& st, BOOL it, BOOL under, CPoint& pt)
{
	m_str = st;
	m_bItalic = it;
	m_bUnderline = under;
	m_start = pt;
}
CMyData::CMyData(const CMyData& t) 
{
	m_str = t.m_str;
	m_bItalic = t.m_bItalic;
	m_bUnderline = t.m_bUnderline;
	m_start = t.m_start;
}
CMyData::~CMyData()
{

}
void CMyData::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
		ar << m_str << m_bItalic << m_bUnderline << m_start;
	else
		ar >> m_str >> m_bItalic >> m_bUnderline >> m_start;
}

void CMyData::initialize() 
{
	m_str = CString("");
	m_bItalic = m_bUnderline = FALSE;
	m_start = CPoint(0, 0);
}
CMyData& CMyData::operator=(const CMyData& t)
{
	m_str = t.m_str;
	m_bItalic = t.m_bItalic;
	m_bUnderline = t.m_bUnderline;
	m_start = t.m_start;
	return *this;
}