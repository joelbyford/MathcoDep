// SchedDlg.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "SchedDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSchedDlg dialog


CSchedDlg::CSchedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSchedDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSchedDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSchedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSchedDlg)
	DDX_Control(pDX, IDC_LIST1, m_lstSched);
	DDX_Control(pDX, IDC_FYE, m_staticFYE);
	DDX_Control(pDX, IDC_SPIN1, m_spinYear);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSchedDlg, CDialog)
	//{{AFX_MSG_MAP(CSchedDlg)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSchedDlg message handlers

void CSchedDlg::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMUPDOWN* pNMUpDown = (NMUPDOWN*)pNMHDR;
	SYSTEMTIME tm;
	TCHAR szText[35];
	
	m_iYear = pNMUpDown->iPos;
	m_tmCurrent = CTime(m_iYear, m_tmCurrent.GetMonth(), m_tmCurrent.GetDay(), 0, 0, 0);
	
	m_tmCurrent.GetAsSystemTime(tm);
	GetDateFormat(LOCALE_USER_DEFAULT, 0, &tm, TEXT("MMM d yyyy"), szText, 35);
	m_staticFYE.SetWindowText(szText);


	*pResult = 0;
}

BOOL CSchedDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SYSTEMTIME tm;
	TCHAR szText[35];

	m_spinYear.SetRange(1969, 2175);
	m_spinYear.SetPos(m_iYear); 
	
	m_tmCurrent.GetAsSystemTime(tm);
	GetDateFormat(LOCALE_USER_DEFAULT, 0, &tm, TEXT("MMM d yyyy"), szText, 35);
	m_staticFYE.SetWindowText(szText);

	//populate the schedule for the first time
	if(!BuildSchedule())
		MessageBox(TEXT("Error Building Schedule"));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSchedDlg::BuildSchedule()
{
	CRect rect;	
	CString strTemp;

	//Delete all columns
	int nColumnCount = m_lstSched.GetHeaderCtrl()->GetItemCount();

	for (int i=0;i < nColumnCount;i++)
	{
		m_lstSched.DeleteColumn(0);
	}
	
	//Make list columns (show only the first 4 and scroll for the rest)
	m_lstSched.GetClientRect(&rect);
	int nColInterval = (rect.Width())/4;
	m_lstSched.InsertColumn(0, _T("Asset"), LVCFMT_LEFT, nColInterval);
	m_lstSched.InsertColumn(1, _T("Basis"), LVCFMT_LEFT, nColInterval);
	m_lstSched.InsertColumn(2, _T("Expense"), LVCFMT_LEFT, nColInterval);
	m_lstSched.InsertColumn(3, _T("A/D."), LVCFMT_LEFT, nColInterval);
	m_lstSched.InsertColumn(4, _T("Life"), LVCFMT_LEFT, nColInterval);
	m_lstSched.InsertColumn(5, _T("Method"), LVCFMT_LEFT, nColInterval);
	
	int iAssetCount = m_pDoc->m_assetList.GetSize();

	for (int index = 0; index < iAssetCount; index++)
	{
		//Add an item to the list
		if (m_lstSched.InsertItem(index, m_pDoc->m_assetList[index]->m_strName) == -1)
			return FALSE;

		////////////////////
		//Calculation
		////////////////////
		m_pDoc->m_assetList[index]->Calculate();
		short iYear = m_pDoc->m_assetList[index]->m_tmPurch.GetYear() - m_iYear;
		
		//minimum year check
		if (iYear < 0)
			iYear = 0;

		//maximum year check
		if (iYear > m_pDoc->m_assetList[index]->m_iGLife)
			iYear = m_pDoc->m_assetList[index]->m_iGLife;


		////////////////////
		//Display
		////////////////////
		//Asset Name Column
		m_lstSched.SetItemText(index, 0, m_pDoc->m_assetList[index]->m_strName);
		//Asset Basis Column
		strTemp.Format(TEXT("%.2f"), m_pDoc->m_assetList[index]->m_fGBasis);
		m_lstSched.SetItemText(index, 1, strTemp);
		//Current Expense Column
		strTemp.Format(TEXT("%.2f"), m_pDoc->m_assetList[index]->m_pGExpArray[iYear]);
		m_lstSched.SetItemText(index, 2, strTemp);
		//A/D Column
		strTemp.Format(TEXT("%.2f"), m_pDoc->m_assetList[index]->m_pGADArray[iYear]);
		m_lstSched.SetItemText(index, 3, strTemp);
		//Life Column
		strTemp.Format(TEXT("%i"), m_pDoc->m_assetList[index]->m_iGLife);
		m_lstSched.SetItemText(index, 4, strTemp);
		//Method Column



	}
	return TRUE;
}

void CSchedDlg::OnClose() 
{
	CDialog::OnClose();
}
