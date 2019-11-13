// DlgAsset.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "DlgAsset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAsset dialog


CDlgAsset::CDlgAsset(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAsset::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAsset)
	m_tmPurch = 0;
	m_str179G = _T("");
	m_strBasisG = _T("");
	m_iLifeG = 0;
	m_strResidG = _T("");
	m_strName = _T("");
	m_str179T = _T("");
	m_strBasisT = _T("");
	//}}AFX_DATA_INIT
	m_f179G = 0;
	m_f179T = 0;
	m_fBasisG = 0;
	m_fBasisT = 0;
	m_fResidG = 0;

	m_iMethodG = 0;
	m_iMethodT = 0;
	m_iLifeT = 0;

}


void CDlgAsset::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAsset)
	DDX_Control(pDX, IDC_DATE_PURCH, m_dtctlPurch);
	DDX_Control(pDX, IDC_TXT_TBASIS, m_edBasisT);
	DDX_Control(pDX, IDC_TXT_NAME, m_edName);
	DDX_Control(pDX, IDC_TXT_GRESID, m_edResidG);
	DDX_Control(pDX, IDC_TXT_GLIFE, m_edLifeG);
	DDX_Control(pDX, IDC_TXT_GBASIS, m_edBasisG);
	DDX_Control(pDX, IDC_TXT_T179, m_ed179T);
	DDX_Control(pDX, IDC_TXT_G179, m_ed179G);
	DDX_Control(pDX, IDC_CMB_TLIFE, m_cmbLifeT);
	DDX_Control(pDX, IDC_CMB_TMETH, m_cmbMethodT);
	DDX_Control(pDX, IDC_CMB_GMETH, m_cmbMethodG);
	DDX_DateTimeCtrl(pDX, IDC_DATE_PURCH, m_tmPurch);
	DDX_Text(pDX, IDC_TXT_G179, m_str179G);
	DDX_Text(pDX, IDC_TXT_GBASIS, m_strBasisG);
	DDX_Text(pDX, IDC_TXT_GLIFE, m_iLifeG);
	DDX_Text(pDX, IDC_TXT_GRESID, m_strResidG);
	DDX_Text(pDX, IDC_TXT_NAME, m_strName);
	DDX_Text(pDX, IDC_TXT_T179, m_str179T);
	DDX_Text(pDX, IDC_TXT_TBASIS, m_strBasisT);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAsset, CDialog)
	//{{AFX_MSG_MAP(CDlgAsset)
	ON_EN_KILLFOCUS(IDC_TXT_GBASIS, OnKillfocusTxtGbasis)
	ON_EN_KILLFOCUS(IDC_TXT_GLIFE, OnKillfocusTxtGlife)
	ON_EN_KILLFOCUS(IDC_TXT_G179, OnKillfocusTxtG179)
	ON_EN_KILLFOCUS(IDC_TXT_GRESID, OnKillfocusTxtGresid)
	ON_EN_KILLFOCUS(IDC_TXT_T179, OnKillfocusTxtT179)
	ON_EN_KILLFOCUS(IDC_TXT_TBASIS, OnKillfocusTxtTbasis)
	ON_CBN_SELENDOK(IDC_CMB_GMETH, OnSelendokCmbGmeth)
	ON_CBN_SELENDOK(IDC_CMB_TLIFE, OnSelendokCmbTlife)
	ON_CBN_SELENDOK(IDC_CMB_TMETH, OnSelendokCmbTmeth)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//-----------------
// cleanFloat()
// ----------------
// Remove non-numeric values from a string (such as letters and special characters)
// and return the cleaned string. 
double CDlgAsset::cleanFloat(TCHAR szInput[])
{
	int i, iStrSize;
	TCHAR szTemp[2];
	TCHAR szDecimal[2];
	TCHAR szValidChars[] = TEXT("1234567890");
	TCHAR szOutput[35];
	TCHAR *szTrash;

	//find out what the decimal figure is for this locale
	GetLocaleInfo(GetUserDefaultLCID(), LOCALE_SDECIMAL, szDecimal, 2);

	//initialize the output buffer
	wcscpy(szOutput, TEXT(""));
	
	iStrSize = wcslen(szInput);
	for (i=0;i<iStrSize;i++)
	{
		if (wcschr(szValidChars, szInput[i]))
		{
			wsprintf(szTemp, TEXT("%c"), szInput[i]);
			wcscat(szOutput, szTemp);
		}
		else if(wcschr(szDecimal, szInput[i]))
		{
			wsprintf(szTemp, TEXT("."), szInput[i]);
			wcscat(szOutput, szTemp);
		}

	}
	
	return wcstod(szOutput,  &szTrash);
}

//-----------------
// cleanInt()
// ----------------
// Remove non-numeric values from a string (such as letters and special characters)
// and return the cleaned string. 
int CDlgAsset::cleanInt(TCHAR szInput[])
{
	int i, iStrSize;
	TCHAR szTemp[2];
	TCHAR szValidChars[] = TEXT("1234567890");
	TCHAR szOutput[35];
	TCHAR *szTrash;

	//initialize the output buffer
	wcscpy(szOutput, TEXT(""));
	
	iStrSize = wcslen(szInput);
	for (i=0;i<iStrSize;i++)
	{
		if (wcschr(szValidChars, szInput[i]))
		{
			wsprintf(szTemp, TEXT("%c"), szInput[i]);
			wcscat(szOutput, szTemp);
		}
	}

	return wcstol(szOutput,  &szTrash, 10);
}



/////////////////////////////////////////////////////////////////////////////
// CDlgAsset message handlers
BOOL CDlgAsset::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString strTemp;
	
	if (m_tmPurch == 0)
	{
		m_tmPurch = CTime::GetCurrentTime();
		m_dtctlPurch.SetTime(&m_tmPurch);
	}

	//populate tax life list box
	strTemp.LoadString(IDS_THREE);
	m_cmbLifeT.AddString(strTemp);
	strTemp.LoadString(IDS_FIVE);
	m_cmbLifeT.AddString(strTemp);
	strTemp.LoadString(IDS_SEVEN);
	m_cmbLifeT.AddString(strTemp);
	strTemp.LoadString(IDS_TEN);
	m_cmbLifeT.AddString(strTemp);
	strTemp.LoadString(IDS_FIFTEEN);
	m_cmbLifeT.AddString(strTemp);
	strTemp.LoadString(IDS_TWENTY);
	m_cmbLifeT.AddString(strTemp);
	m_cmbLifeT.SetCurSel(m_iLifeT);
	
	//populate GAAP Methods
	strTemp.LoadString(IDS_SL);
	m_cmbMethodG.AddString(strTemp);
	strTemp.LoadString(IDS_DDB);
	m_cmbMethodG.AddString(strTemp);
	strTemp.LoadString(IDS_15DB);
	m_cmbMethodG.AddString(strTemp);
	strTemp.LoadString(IDS_SYD);
	m_cmbMethodG.AddString(strTemp);
	strTemp.LoadString(IDS_MACRSHY);
	m_cmbMethodG.AddString(strTemp);
	strTemp.LoadString(IDS_MACRSMQ);
	m_cmbMethodG.AddString(strTemp);
	m_cmbMethodG.SetCurSel(m_iMethodG);

	//Populate Tax Methods
	strTemp.LoadString(IDS_MACRSHY);
	m_cmbMethodT.AddString(strTemp);
	strTemp.LoadString(IDS_MACRSMQ);
	m_cmbMethodT.AddString(strTemp);
	strTemp.LoadString(IDS_SL);
	m_cmbMethodT.AddString(strTemp);
	m_cmbMethodT.SetCurSel(m_iMethodT);

	//if there is a name, then format the stuff
	if (!m_strName.IsEmpty())
	{
		NUMFMT(m_fBasisG, m_edBasisG);
		NUMFMT(m_fBasisT, m_edBasisT);
		NUMFMT(m_fResidG, m_edResidG);
		NUMFMT(m_f179G, m_ed179G);
		NUMFMT(m_f179T, m_ed179T);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAsset::OnKillfocusTxtGbasis() 
{
	CString tmpString;

	//Save the float value to memory
	m_edBasisG.GetWindowText(tmpString);
	m_fBasisG = cleanFloat(tmpString.LockBuffer());
	tmpString.ReleaseBuffer();

	NUMFMT(m_fBasisG, m_edBasisG);


	//Set the tax edit box to the same value if empty.
	m_edBasisT.GetWindowText(tmpString);

	if(tmpString.IsEmpty())
	{
		m_edBasisG.GetWindowText(tmpString);
		m_edBasisT.SetWindowText(tmpString);
		m_fBasisT = m_fBasisG;

	}	

	
}

void CDlgAsset::OnKillfocusTxtGlife() 
{
	//Set the tax edit box to the same value if empty.
	CString tmpString;
	
	m_edLifeG.GetWindowText(tmpString);
	m_iLifeG = cleanInt(tmpString.LockBuffer());
	
	if(m_iLifeG <= 3)
	{
		m_cmbLifeT.SetCurSel(0);
		m_iLifeT = 0;
	}
	else if(m_iLifeG <= 5)
	{
		m_cmbLifeT.SetCurSel(1);
		m_iLifeT = 1;
	}
	else if(m_iLifeG <= 7)
	{
		m_cmbLifeT.SetCurSel(2);
		m_iLifeT = 2;
	}
	else if(m_iLifeG <= 10)
	{
		m_cmbLifeT.SetCurSel(3);
		m_iLifeT = 3;
	}
	else
	{
		m_cmbLifeT.SetCurSel(4);
		m_iLifeT = 4;
	}

}		

void CDlgAsset::OnKillfocusTxtG179() 
{
	//Set the tax edit box to the same value if empty.
	CString tmpString;


	//save the float value to memory
	m_ed179G.GetWindowText(tmpString);
	m_f179G = cleanFloat(tmpString.LockBuffer());
	tmpString.ReleaseBuffer();

	NUMFMT(m_f179G, m_ed179G);

	m_ed179T.GetWindowText(tmpString);

	if(tmpString.IsEmpty())
	{
		m_ed179G.GetWindowText(tmpString);
		m_ed179T.SetWindowText(tmpString);
		m_f179T = m_f179G;
	}

	
}


void CDlgAsset::OnKillfocusTxtGresid() 
{
	CString tmpString;

	//save the float value to memory
	m_edResidG.GetWindowText(tmpString);
	m_fResidG = cleanFloat(tmpString.LockBuffer());
	tmpString.ReleaseBuffer();

	NUMFMT(m_fResidG, m_edResidG);

}

void CDlgAsset::OnKillfocusTxtT179() 
{
	CString tmpString;

	//save the float value to memory
	m_ed179T.GetWindowText(tmpString);
	m_f179T = cleanFloat(tmpString.LockBuffer());
	tmpString.ReleaseBuffer();

	NUMFMT(m_f179T, m_ed179T);
}

void CDlgAsset::OnKillfocusTxtTbasis() 
{
	CString tmpString;

	//save the float value to memory
	m_edBasisT.GetWindowText(tmpString);
	m_fBasisT = cleanFloat(tmpString.LockBuffer());
	tmpString.ReleaseBuffer();

	NUMFMT(m_fBasisT, m_edBasisT);

}



void CDlgAsset::OnSelendokCmbGmeth() 
{
	m_iMethodG = m_cmbMethodG.GetCurSel();
}

void CDlgAsset::OnSelendokCmbTlife() 
{
	m_iLifeT = m_cmbLifeT.GetCurSel();
}

void CDlgAsset::OnSelendokCmbTmeth() 
{
	m_iMethodT = m_cmbMethodT.GetCurSel();
}
