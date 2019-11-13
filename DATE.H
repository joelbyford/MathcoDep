// Date.h: interface for the CDate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATE_H__1F771AD2_2950_4F3A_B3D3_6506AC778BC2__INCLUDED_)
#define AFX_DATE_H__1F771AD2_2950_4F3A_B3D3_6506AC778BC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDate
{
public:
	void SetToday(void);
	void SetDay(int nDay);
	void SetDay(CString strDay);
	void SetMonth(int nMonth);
	void SetYear(int nYear);
	int GetDay(void);
	int GetMonth(void);
	int GetYear(void);
	void AddMonth(int nMonth);

	CDate();
	CDate(int nYear, int nMonth, int nDay);
	CDate(CDate& dtDate);
	virtual ~CDate();

private:
	void NoWeekend(void);
	int DaysInMonth(int iMonth);

	int m_nYear;
	int m_nDay;
	int m_nMonth;
};

#endif // !defined(AFX_DATE_H__1F771AD2_2950_4F3A_B3D3_6506AC778BC2__INCLUDED_)
