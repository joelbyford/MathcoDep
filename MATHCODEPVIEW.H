// MathcoDepView.h : interface of the CMathcoDepView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATHCODEPVIEW_H__C4FB36D3_F949_4D92_8F0C_7BD25585CEAB__INCLUDED_)
#define AFX_MATHCODEPVIEW_H__C4FB36D3_F949_4D92_8F0C_7BD25585CEAB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "DlgAsset.h"
#include "SchedDlg.h"
#include "CompanyDlg.h"
#include "MathcoDepDoc.h"

class CMathcoDepView : public CFormView
{
protected: // create from serialization only
	CMathcoDepView();
	DECLARE_DYNCREATE(CMathcoDepView)

public:
	//{{AFX_DATA(CMathcoDepView)
	enum { IDD = IDD_MATHCODEP_FORM };
	CListCtrl	m_lstMain;
	//}}AFX_DATA

// Attributes
public:
	CMathcoDepDoc* GetDocument();
private:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMathcoDepView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMathcoDepView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMathcoDepView)
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnSetFocus( CWnd* pOldWnd );
	afx_msg void OnDestroy();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDel();
	afx_msg void OnBtnEdit();
	afx_msg void OnBtnSched();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditCut();
	afx_msg void OnClose();
	afx_msg void OnEditInfo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL BuildList(void);
};

#ifndef _DEBUG  // debug version in MathcoDepView.cpp
inline CMathcoDepDoc* CMathcoDepView::GetDocument()
   { return (CMathcoDepDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATHCODEPVIEW_H__C4FB36D3_F949_4D92_8F0C_7BD25585CEAB__INCLUDED_)
