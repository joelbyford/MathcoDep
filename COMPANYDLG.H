#if !defined(AFX_COMPANYDLG_H__2A9B4B21_85E1_46DC_B2D6_F828EC60C7BF__INCLUDED_)
#define AFX_COMPANYDLG_H__2A9B4B21_85E1_46DC_B2D6_F828EC60C7BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CompanyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCompanyDlg dialog

class CCompanyDlg : public CDialog
{
// Construction
public:
	CCompanyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCompanyDlg)
	enum { IDD = IDD_COMPANY };
	CEdit	m_edName;
	CEdit	m_edMonth;
	CEdit	m_edDay;
	UINT	m_iDay;
	UINT	m_iMonth;
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompanyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCompanyDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPANYDLG_H__2A9B4B21_85E1_46DC_B2D6_F828EC60C7BF__INCLUDED_)
