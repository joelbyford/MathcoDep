#if !defined(AFX_DLGASSET_H__CE9ECFA8_502F_4786_9689_33C63B4B9A25__INCLUDED_)
#define AFX_DLGASSET_H__CE9ECFA8_502F_4786_9689_33C63B4B9A25__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgAsset.h : header file
//

#define NUMFMT(FVALUE, EDCTL)\
	{\
	CString MACString;\
	TCHAR MACszTemp[35];\
	MACString.Format(TEXT("%f"), FVALUE);\
	GetNumberFormat(LOCALE_USER_DEFAULT, 0, MACString.LockBuffer(), NULL, MACszTemp, 35);\
	EDCTL.SetWindowText(MACszTemp);\
	}
/////////////////////////////////////////////////////////////////////////////
// CDlgAsset dialog

class CDlgAsset : public CDialog
{
// Construction
public:
	CDlgAsset(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAsset)
	enum { IDD = IDD_ASSET };
	CDateTimeCtrl	m_dtctlPurch;
	CEdit	m_edBasisT;
	CEdit	m_edName;
	CEdit	m_edResidG;
	CEdit	m_edLifeG;
	CEdit	m_edBasisG;
	CEdit	m_ed179T;
	CEdit	m_ed179G;
	CComboBox	m_cmbLifeT;
	CComboBox	m_cmbMethodT;
	CComboBox	m_cmbMethodG;
	CTime	m_tmPurch;
	CString	m_str179G;
	CString	m_strBasisG;
	UINT	m_iLifeG;
	CString	m_strResidG;
	CString	m_strName;
	CString	m_str179T;
	CString	m_strBasisT;
	//}}AFX_DATA

	int cleanInt(TCHAR szInput[]);
	double cleanFloat(TCHAR szInput[]);

	double m_f179G;
	double m_f179T;
	double m_fBasisG;
	double m_fBasisT;
	double m_fResidG;
	int m_iMethodG;
	int m_iMethodT;
	int m_iLifeT;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAsset)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAsset)
	afx_msg void OnKillfocusTxtGbasis();
	afx_msg void OnKillfocusTxtGlife();
	afx_msg void OnKillfocusTxtG179();
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusTxtGresid();
	afx_msg void OnKillfocusTxtT179();
	afx_msg void OnKillfocusTxtTbasis();
	afx_msg void OnSelendokCmbGmeth();
	afx_msg void OnSelendokCmbTlife();
	afx_msg void OnSelendokCmbTmeth();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGASSET_H__CE9ECFA8_502F_4786_9689_33C63B4B9A25__INCLUDED_)
