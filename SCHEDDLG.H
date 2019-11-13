#if !defined(AFX_SCHEDDLG_H__D34B1153_61A0_4AAA_8FCD_892176C753CF__INCLUDED_)
#define AFX_SCHEDDLG_H__D34B1153_61A0_4AAA_8FCD_892176C753CF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "MathcoDepDoc.h"
// SchedDlg.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CSchedDlg dialog

class CSchedDlg : public CDialog
{
// Construction
public:
	CSchedDlg(CWnd* pParent = NULL);	// standard constructor
	BOOL BuildSchedule(void);
	CTime m_tmCurrent;
	int m_iYear;
	CMathcoDepDoc* m_pDoc;

// Dialog Data
	//{{AFX_DATA(CSchedDlg)
	enum { IDD = IDD_SCHEDULE };
	CListCtrl	m_lstSched;
	CStatic	m_staticFYE;
	CSpinButtonCtrl	m_spinYear;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSchedDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSchedDlg)
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHEDDLG_H__D34B1153_61A0_4AAA_8FCD_892176C753CF__INCLUDED_)
