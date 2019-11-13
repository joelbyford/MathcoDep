// MathcoDepDoc.h : interface of the CMathcoDepDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATHCODEPDOC_H__DFAE1F3D_8C41_4D13_8EDC_F7EBE6667F41__INCLUDED_)
#define AFX_MATHCODEPDOC_H__DFAE1F3D_8C41_4D13_8EDC_F7EBE6667F41__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxtempl.h>
#include "Asset.h"

typedef CTypedPtrArray <CObArray, CAsset*> CAssetArray;

class CMathcoDepDoc : public CDocument
{
protected: // create from serialization only
	CMathcoDepDoc();
	DECLARE_SERIAL(CMathcoDepDoc)

// Attributes
public:
	CAssetArray m_assetList;
	CTime m_tmFYE;
	CString m_strCoName;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMathcoDepDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMathcoDepDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMathcoDepDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATHCODEPDOC_H__DFAE1F3D_8C41_4D13_8EDC_F7EBE6667F41__INCLUDED_)
