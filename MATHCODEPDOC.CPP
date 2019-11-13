// MathcoDepDoc.cpp : implementation of the CMathcoDepDoc class
//

#include "stdafx.h"
#include "MathcoDep.h"

#include "MathcoDepDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMathcoDepDoc

IMPLEMENT_SERIAL(CMathcoDepDoc, CDocument, VERSIONABLE_SCHEMA | 2)

BEGIN_MESSAGE_MAP(CMathcoDepDoc, CDocument)
	//{{AFX_MSG_MAP(CMathcoDepDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMathcoDepDoc construction/destruction

CMathcoDepDoc::CMathcoDepDoc()
{
	m_strCoName = TEXT("");
	m_tmFYE = CTime::GetCurrentTime();
}

CMathcoDepDoc::~CMathcoDepDoc()
{
}

BOOL CMathcoDepDoc::OnNewDocument()
{
	int iNumAssets = m_assetList.GetSize();
	int i = 0;

	if (!CDocument::OnNewDocument())
		return FALSE;

	//delete the asset array
	m_assetList.RemoveAll();

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMathcoDepDoc serialization

void CMathcoDepDoc::Serialize(CArchive& ar)
{
	m_assetList.Serialize(ar);

	if (ar.IsStoring())
	{
		
		ar << m_strCoName;
		ar << m_tmFYE;
	}
	else
	{
		ar >> m_strCoName;
		ar >> m_tmFYE;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMathcoDepDoc diagnostics

#ifdef _DEBUG
void CMathcoDepDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMathcoDepDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMathcoDepDoc commands
