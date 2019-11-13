// CompanyDlg.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "CompanyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompanyDlg dialog


CCompanyDlg::CCompanyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCompanyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCompanyDlg)
	m_iDay = 0;
	m_iMonth = 0;
	m_strName = _T("");
	//}}AFX_DATA_INIT
}


void CCompanyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCompanyDlg)
	DDX_Control(pDX, IDC_TXT_NAME, m_edName);
	DDX_Control(pDX, IDC_TXT_MON, m_edMonth);
	DDX_Control(pDX, IDC_TXT_DAY, m_edDay);
	DDX_Text(pDX, IDC_TXT_DAY, m_iDay);
	DDV_MinMaxUInt(pDX, m_iDay, 1, 31);
	DDX_Text(pDX, IDC_TXT_MON, m_iMonth);
	DDV_MinMaxUInt(pDX, m_iMonth, 1, 12);
	DDX_Text(pDX, IDC_TXT_NAME, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCompanyDlg, CDialog)
	//{{AFX_MSG_MAP(CCompanyDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompanyDlg message handlers

BOOL CCompanyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
