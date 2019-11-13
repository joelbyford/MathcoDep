// Date.cpp: implementation of the CDate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MathcoFile.h"
#include "Date.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDate::CDate()
{
	//Initialize to today
	SetToday();
}

CDate::CDate(CDate& dtDate)
{
	m_nYear = dtDate.GetYear();
	m_nDay = dtDate.GetDay();
	m_nMonth = dtDate.GetMonth();
}


CDate::CDate(int nYear, int nMonth, int nDay)
{
	m_nYear = nYear;
	m_nMonth = nMonth;
	m_nDay = nDay;
}

CDate::~CDate()
{

}

void CDate::AddMonth(int nMonth)
{
	int iTemp;
	iTemp = m_nMonth + nMonth;

	if (iTemp > 12)
	{
		m_nMonth = iTemp - 12;
		m_nYear++;
	}
	else
	{
		m_nMonth = iTemp;
	}
	
	return;
}

void CDate::SetDay(CString strDay)
{
	CString x;
	if (strDay.CompareNoCase(TEXT("LAST")) == 0)
	{
		m_nDay = DaysInMonth(m_nMonth);
	}
	else if (strDay.CompareNoCase(TEXT("END")) == 0)
	{
		m_nDay = DaysInMonth(m_nMonth);
	}
	else if (strDay.CompareNoCase(TEXT("15")) == 0)
	{
		m_nDay = 15;
	}
	else if (strDay.CompareNoCase(TEXT("MIDDLE")) == 0)
	{
		m_nDay = (int) ((double)DaysInMonth(m_nMonth) / (double)2);
	}
	else
	{
		m_nDay = 1;
	}

	NoWeekend();

	return;

}
void CDate::SetDay(int nDay)
{
	m_nDay = nDay;
	NoWeekend();

	return;
}

void CDate::SetMonth(int nMonth)
{
	m_nMonth = nMonth;
	return;
}

void CDate::SetYear(int nYear)
{
	m_nYear = nYear;
	return;
}

int CDate::GetDay()
{
	return m_nDay;
}

int CDate::GetMonth()
{
	return m_nMonth;
}

int CDate::GetYear()
{
	return m_nYear;
}


int CDate::DaysInMonth(int iMonth)
{
	int iDays = 0;

	switch(iMonth)
	{
	case 1:
		iDays = 31;
		break;
	case 2:
		iDays = 28;
		break;
	case 3:
		iDays = 31;
		break;
	case 4:
		iDays = 30;
		break;
	case 5:
		iDays = 31;
		break;
	case 6:
		iDays = 30;
		break;
	case 7:
		iDays = 31;
		break;
	case 8:
		iDays = 31;
		break;
	case 9:
		iDays = 30;
		break;
	case 10:
		iDays = 31;
		break;
	case 11:
		iDays = 30;
		break;
	case 12:
		iDays = 31;
		break;
	default:
		iDays = 0;
		break;
	}
	return iDays;
}


void CDate::SetToday()
{
	SYSTEMTIME systime;
	//Get the current date
	GetSystemTime(&systime);

	m_nMonth = systime.wMonth;
	m_nYear = systime.wYear;
	m_nDay = systime.wDay;
	return;
}

void CDate::NoWeekend()
{
	CTime tmRaw(m_nYear, m_nMonth, m_nDay,0,0,0);

	switch(tmRaw.GetDayOfWeek())
	{
	case 1://sunday
		m_nDay++;
		break;
	case 7://saturday
		m_nDay += 2;
		break;
	}
	return;
}
