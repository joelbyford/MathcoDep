// MathcoDepView.cpp : implementation of the CMathcoDepView class
//

#include "stdafx.h"
#include "MathcoDep.h"

#include "MathcoDepView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMathcoDepView

IMPLEMENT_DYNCREATE(CMathcoDepView, CFormView)

BEGIN_MESSAGE_MAP(CMathcoDepView, CFormView)
	//{{AFX_MSG_MAP(CMathcoDepView)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_BN_CLICKED(IDC_BTN_EDIT, OnBtnEdit)
	ON_BN_CLICKED(IDC_BTN_SCHED, OnBtnSched)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_WM_CLOSE()
	ON_COMMAND(ID_EDIT_INFO, OnEditInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMathcoDepView construction/destruction

CMathcoDepView::CMathcoDepView()
	: CFormView(CMathcoDepView::IDD)
{
	//{{AFX_DATA_INIT(CMathcoDepView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

}

CMathcoDepView::~CMathcoDepView()
{
}

void CMathcoDepView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMathcoDepView)
	DDX_Control(pDX, IDC_LIST1, m_lstMain);
	//}}AFX_DATA_MAP
}

BOOL CMathcoDepView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMathcoDepView diagnostics

#ifdef _DEBUG
void CMathcoDepView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMathcoDepView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMathcoDepDoc* CMathcoDepView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMathcoDepDoc)));
	return (CMathcoDepDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMathcoDepView message handlers
int CMathcoDepView::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	int iResult = CFormView::OnCreate(lpCreateStruct);

	if(iResult == 0)
		CWnd::ShowDoneButton(TRUE);

	return iResult;
}
void CMathcoDepView::OnSetFocus(CWnd* pOldWnd)
{
	CFormView::OnSetFocus(pOldWnd);
	//::SHSipPreference(m_hWnd, SIP_UP);
}

void CMathcoDepView::OnDestroy()
{
	//::SHSipPreference(m_hWnd, SIP_FORCEDOWN);
	CFormView::OnDestroy();
}

BOOL CMathcoDepView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CMathcoDepView::OnBtnAdd() 
{
	CMathcoDepDoc* pDoc = GetDocument();
	CDlgAsset* pDlgAsset = new CDlgAsset();

	CAsset* newObj;
	if (pDlgAsset->DoModal() == IDOK)
	{
		newObj = new CAsset;
		//General Values
		newObj->m_strName = pDlgAsset->m_strName;
		newObj->m_tmPurch = pDlgAsset->m_tmPurch;
		//GAAP Values
		newObj->m_fGBasis = pDlgAsset->m_fBasisG;
		newObj->m_fGReduction = pDlgAsset->m_f179G;
		newObj->m_fGResidual = pDlgAsset->m_fResidG;
		newObj->m_iGMethod = pDlgAsset->m_iMethodG;
		newObj->m_iGLife = pDlgAsset->m_iLifeG;

		//Tax Values
		newObj->m_fTBasis = pDlgAsset->m_fBasisT;
		newObj->m_fTReduction = pDlgAsset->m_f179T;
		newObj->m_iTMethod = pDlgAsset->m_iMethodT;
		newObj->m_iTLife = pDlgAsset->m_iLifeT;
		
		//Add the asset to the list
		pDoc->m_assetList.Add(newObj);
		pDoc->SetModifiedFlag();
		if (!BuildList())
			MessageBox(TEXT("Trouble building list"));
	}
	delete pDlgAsset;

	return;
	
}

void CMathcoDepView::OnBtnDel() 
{
	CMathcoDepDoc* pDoc = GetDocument();
	POSITION pos = m_lstMain.GetFirstSelectedItemPosition();

	if (pos == NULL)
		MessageBox(TEXT("Please select an item to delete"));
	else
	{
		int iResult = MessageBox(TEXT("Are you sure you wish to delete this asset?"), TEXT("Are you sure?"), MB_ICONQUESTION | MB_OKCANCEL);
		if (iResult == IDOK)
		{
			//get the one selected.
			int iIndex = m_lstMain.GetNextSelectedItem(pos);
			pDoc->m_assetList.RemoveAt(iIndex);
			pDoc->SetModifiedFlag();
			if (!BuildList())
				MessageBox(TEXT("Trouble building list"));

		}
	}
	
}

void CMathcoDepView::OnBtnEdit() 
{
	CMathcoDepDoc* pDoc = GetDocument();

	CDlgAsset* pDlgAsset = new CDlgAsset();


	POSITION pos = m_lstMain.GetFirstSelectedItemPosition();
	if (pos == NULL)
		MessageBox(TEXT("Please select an item to edit"));
	else
	{
		//get the one selected.
		int iIndex = m_lstMain.GetNextSelectedItem(pos);
		CAsset* newObj = pDoc->m_assetList.GetAt(iIndex);
		//populate the defaults
		//General Values
		pDlgAsset->m_strName = newObj->m_strName ;
		pDlgAsset->m_tmPurch = newObj->m_tmPurch;
		//GAAP Values
		pDlgAsset->m_fBasisG = newObj->m_fGBasis;
		pDlgAsset->m_f179G = newObj->m_fGReduction;
		pDlgAsset->m_fResidG = newObj->m_fGResidual;
		pDlgAsset->m_iMethodG = newObj->m_iGMethod;
		pDlgAsset->m_iLifeG = newObj->m_iGLife;
		//Tax Values
		pDlgAsset->m_fBasisT = newObj->m_fTBasis;
		pDlgAsset->m_f179T = newObj->m_fTReduction;
		pDlgAsset->m_iMethodT = newObj->m_iTMethod;
		pDlgAsset->m_iLifeT = newObj->m_iTLife;

		//show the dialog box then
		if (pDlgAsset->DoModal() == IDOK)
		{
			//General Values
			newObj->m_strName = pDlgAsset->m_strName;
			newObj->m_tmPurch = pDlgAsset->m_tmPurch;
			//GAAP Values
			newObj->m_fGBasis = pDlgAsset->m_fBasisG;
			newObj->m_fGReduction = pDlgAsset->m_f179G;
			newObj->m_fGResidual = pDlgAsset->m_fResidG;
			newObj->m_iGMethod = pDlgAsset->m_iMethodG;
			newObj->m_iGLife = pDlgAsset->m_iLifeG;
			//Tax Values
			newObj->m_fTBasis = pDlgAsset->m_fBasisT;
			newObj->m_fTReduction = pDlgAsset->m_f179T;
			newObj->m_iTMethod = pDlgAsset->m_iMethodT;
			newObj->m_iTLife = pDlgAsset->m_iLifeT;
			
			//Add the asset to the list
			pDoc->m_assetList.SetAt(iIndex, newObj);
			pDoc->SetModifiedFlag();
			if (!BuildList())
				MessageBox(TEXT("Trouble building list"));
		}
	}
	delete pDlgAsset;
	return;	
}

void CMathcoDepView::OnBtnSched() 
{
	CSchedDlg dlg = new CSchedDlg(this);
	CMathcoDepDoc* pDoc = GetDocument();
	dlg.m_pDoc = pDoc;

	
	dlg.m_iYear = pDoc->m_tmFYE.GetYear();
	dlg.m_tmCurrent = pDoc->m_tmFYE;

	dlg.DoModal();

	delete dlg;
	return;
	
}

BOOL CMathcoDepView::BuildList()
{
	CRect rect;	
	LVITEM lvI;
	CMathcoDepDoc* pDoc = GetDocument();
	int iNumAssets = pDoc->m_assetList.GetSize();
	int index;
	TCHAR szText[35], szText2[35];
	SYSTEMTIME tm;

	//delete all old data
	m_lstMain.DeleteAllItems();

	//delete old columns
	int iColCount = m_lstMain.GetHeaderCtrl()->GetItemCount();

	for (int i=0;i < iColCount;i++)
	{
		m_lstMain.DeleteColumn(0);
	}


	//Make list columns
	m_lstMain.GetClientRect(&rect);
	int nColInterval = rect.Width()/3;

	m_lstMain.InsertColumn(0, _T("Name"), LVCFMT_LEFT, nColInterval);
	m_lstMain.InsertColumn(1, _T("Purchased"), LVCFMT_LEFT, nColInterval);
	m_lstMain.InsertColumn(2, _T("GAAP Basis"), LVCFMT_LEFT, nColInterval);


	// Finally, add the actual items to the control.
	lvI.mask = LVIF_TEXT |  LVIF_STATE;
	lvI.state = 0;
	lvI.stateMask = 0;

	for(index=0;index<iNumAssets;index++)
	{
		//Insert a new item on the list
		lvI.iItem = index;
		lvI.iSubItem = 0;

		wsprintf(szText, TEXT("Error"));
		lvI.pszText = szText;
		lvI.cchTextMax = 80;

		if (m_lstMain.InsertItem(&lvI)== -1)
			return FALSE;
		
		//Add the data to the new item
		m_lstMain.SetItemText(index, 0, pDoc->m_assetList.GetAt(index)->m_strName);
		pDoc->m_assetList.GetAt(index)->m_tmPurch.GetAsSystemTime(tm);
		GetDateFormat(LOCALE_USER_DEFAULT, DATE_SHORTDATE, &tm, NULL, szText2, 35);
		m_lstMain.SetItemText(index, 1, szText2);
		wsprintf(szText, TEXT("%.2f"), pDoc->m_assetList.GetAt(index)->m_fGBasis);
		GetNumberFormat(LOCALE_USER_DEFAULT, 0, szText, NULL, szText2, 35);
		m_lstMain.SetItemText(index, 2, szText2);
	}
	return true;
}

void CMathcoDepView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	if(!BuildList())
		MessageBox(TEXT("Trouble Populating List Box"));
	
}

void CMathcoDepView::OnEditCopy() 
{
	CMathcoDepDoc* pDoc = GetDocument();
	CMathcoDepApp* pApp = (CMathcoDepApp*) AfxGetApp();

	POSITION pos = m_lstMain.GetFirstSelectedItemPosition();
	if (pos == NULL)
		MessageBox(TEXT("Please select an item to copy"));
	else
	{
		//clean out the old buffer
		if(pApp->m_copyBuf)
		{
			delete pApp->m_copyBuf;
			pApp->m_copyBuf = NULL;
		}

		//get the one selected.
		int iIndex = m_lstMain.GetNextSelectedItem(pos);
		pApp->m_copyBuf = new CAsset(*pDoc->m_assetList.GetAt(iIndex));
		
	}
	return;
}

void CMathcoDepView::OnEditPaste() 
{
	CMathcoDepDoc* pDoc = GetDocument();
	CMathcoDepApp* pApp = (CMathcoDepApp*) AfxGetApp();

	CAsset* newObj = new CAsset(*pApp->m_copyBuf);

	//Add the asset to the list
	pDoc->m_assetList.Add(newObj);
	pDoc->SetModifiedFlag();
	if (!BuildList())
		MessageBox(TEXT("Trouble building list"));

	return;	
}

void CMathcoDepView::OnEditCut() 
{
	CMathcoDepDoc* pDoc = GetDocument();
	CMathcoDepApp* pApp = (CMathcoDepApp*) AfxGetApp();

	POSITION pos = m_lstMain.GetFirstSelectedItemPosition();
	if (pos == NULL)
		MessageBox(TEXT("Please select an item to edit"));
	else
	{
		//clean out the old buffer
		if(pApp->m_copyBuf)
		{
			delete pApp->m_copyBuf;
			pApp->m_copyBuf = NULL;
		}

		//get the one selected.
		int iIndex = m_lstMain.GetNextSelectedItem(pos);
		pApp->m_copyBuf = new CAsset(*pDoc->m_assetList.GetAt(iIndex));

		//delete the selected item
		pDoc->m_assetList.RemoveAt(iIndex);
		pDoc->SetModifiedFlag();
		if (!BuildList())
			MessageBox(TEXT("Trouble building list"));
	}
	return;	
}

void CMathcoDepView::OnClose() 
{
	m_lstMain.DeleteAllItems();
	
	CFormView::OnClose();
}

void CMathcoDepView::OnEditInfo() 
{
	CMathcoDepDoc* pDoc = GetDocument();
	CCompanyDlg dlg = new CCompanyDlg(this);
	
	dlg.m_strName = pDoc->m_strCoName;
	dlg.m_iDay = pDoc->m_tmFYE.GetDay();
	dlg.m_iMonth = pDoc->m_tmFYE.GetMonth();

	if (dlg.DoModal() == IDOK)
	{
		CTime tmTemp(2002, dlg.m_iMonth, dlg.m_iDay,0,0,0);

		pDoc->m_tmFYE = tmTemp;
		pDoc->m_strCoName = dlg.m_strName;
		pDoc->SetModifiedFlag();
	}

	delete dlg;
	return;
	
}
