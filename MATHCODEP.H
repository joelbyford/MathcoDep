// MathcoDep.h : main header file for the MATHCODEP application
//

#if !defined(AFX_MATHCODEP_H__E80C5FE7_27F8_45A9_8C26_A3FD899E87C9__INCLUDED_)
#define AFX_MATHCODEP_H__E80C5FE7_27F8_45A9_8C26_A3FD899E87C9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "asset.h"
/////////////////////////////////////////////////////////////////////////////
// CMathcoDepApp:
// See MathcoDep.cpp for the implementation of this class
//

class CMathcoDepApp : public CWinApp
{
public:
	CMathcoDepApp();
	virtual ~CMathcoDepApp();

	//storage variable for cut/copy/paste
	CAsset* m_copyBuf;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMathcoDepApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMathcoDepApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATHCODEP_H__E80C5FE7_27F8_45A9_8C26_A3FD899E87C9__INCLUDED_)
