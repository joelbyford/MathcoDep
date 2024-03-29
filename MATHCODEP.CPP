// MathcoDep.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MathcoDep.h"

#include "MainFrm.h"

#include "MathcoDepDoc.h"
#include "MathcoDepView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMathcoDepApp

BEGIN_MESSAGE_MAP(CMathcoDepApp, CWinApp)
	//{{AFX_MSG_MAP(CMathcoDepApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMathcoDepApp construction

CMathcoDepApp::CMathcoDepApp()
	: CWinApp()
{
	m_copyBuf = NULL;
}

CMathcoDepApp::~CMathcoDepApp()
{
	if (m_copyBuf)
		delete m_copyBuf;
}
/////////////////////////////////////////////////////////////////////////////
// The one and only CMathcoDepApp object

CMathcoDepApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMathcoDepApp initialization

BOOL CMathcoDepApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Mathco\\Dep"));


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CCeDocListDocTemplate* pDocTemplate;
	pDocTemplate = new CCeDocListDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMathcoDepDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CMathcoDepView),
		CString(_T("Asset Files|*.mcd| |")));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	BOOL bResult = ProcessShellCommand(cmdInfo);
	if (!bResult)
	{
		pDocTemplate->ShowDocList();	
	
		// if there is no file in the doclist, we will create a new one.
		CCeDocList* pDL = pDocTemplate->m_pWndDocList;	
		if (pDL->GetItemCount() == 0) 
		{
			pDL->OnClose();
			OnFileNew();
		}
	}

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();		// Added for WCE apps
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CMathcoDepApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CMathcoDepApp commands
// Added for WCE apps

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CenterWindow();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
