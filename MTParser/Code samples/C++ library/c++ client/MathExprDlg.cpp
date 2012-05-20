// MathExprDlg.cpp : implementation file
//

//#include <vld.h>		// memory leak detector
#include "stdafx.h"
#include "MathExpr.h"
#include "MathExprDlg.h"

#include "../../../MTParserLib/MTTools.h"
#include "../../../MTParserLib/MTParserLocalizer.h"
#include "IndexDlg.h"
#include "DefineMacroDlg.h"
#include "Localization.h"
#include ".\mathexprdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



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

/////////////////////////////////////////////////////////////////////////////
// CMathExprDlg dialog

CMathExprDlg::CMathExprDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMathExprDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMathExprDlg)
	m_expr = _T("");
	m_msg = _T("");
	m_varx = 0.0;
	m_vary = 0.0;
	m_varz = 0.0;
	m_result = 0.0;
	m_benchType = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_lang = _T("en");
}

void CMathExprDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMathExprDlg)
	DDX_Control(pDX, IDC_BENCHMARK, m_benchBtn);
	DDX_Control(pDX, IDC_EVALUATE, m_evaluateBtn);
	DDX_Text(pDX, IDC_EXPR, m_expr);
	DDX_Text(pDX, IDC_MSG, m_msg);
	DDX_Text(pDX, IDC_VARX, m_varx);
	DDX_Text(pDX, IDC_VARY, m_vary);
	DDX_Text(pDX, IDC_VARZ, m_varz);
	DDX_Text(pDX, IDC_RESULT, m_result);
	DDX_Radio(pDX, IDC_BENCHEVAL, m_benchType);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_MSGICON, m_msgIcon);
}

BEGIN_MESSAGE_MAP(CMathExprDlg, CDialog)
	//{{AFX_MSG_MAP(CMathExprDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EVALUATE, OnEvaluate)	
	ON_BN_CLICKED(IDC_INDEX, OnIndex)
	ON_BN_CLICKED(IDC_BENCHMARK, OnBenchmark)
	ON_BN_CLICKED(IDC_DEFINEMACRO, OnDefinemacro)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_COMMAND(ID_LANGUAGES_ENGLISH, OnLanguagesEnglish)
	ON_COMMAND(ID_LANGUAGES_FRENCH, OnLanguagesFrench)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMathExprDlg message handlers

BOOL CMathExprDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon	
	
	m_expr = RToS(IDS_DEFFORMULA);			
	MTSyntax syntax = m_pParser->getSyntax();

	if( m_lang == _T("en") )
	{
		GetMenu()->CheckMenuItem(ID_LANGUAGES_FRENCH, MF_BYCOMMAND|MF_UNCHECKED);
		GetMenu()->CheckMenuItem(ID_LANGUAGES_ENGLISH, MF_BYCOMMAND|MF_CHECKED);

		syntax.argumentSeparator = ',';
		syntax.decimalPoint = '.';
	}
	else
	{
		GetMenu()->CheckMenuItem(ID_LANGUAGES_FRENCH, MF_BYCOMMAND|MF_CHECKED);
		GetMenu()->CheckMenuItem(ID_LANGUAGES_ENGLISH, MF_BYCOMMAND|MF_UNCHECKED);		

		syntax.argumentSeparator = ';';
		syntax.decimalPoint = ',';
		
	}		
	
	// Initialize the parser... 
	try
	{	
		m_pParser->setSyntax(syntax);

		m_pParser->undefineAllVars();
		// variable definitions
		m_pParser->defineVar(_T("x"), &m_varx);
		m_pParser->defineVar(_T("y"), &m_vary);
		m_pParser->defineVar(_T("z"), &m_varz);	
		
	}
	catch( MTParserException &e )
	{		
		MessageBox(getAllExceptionString(e).c_str(), RToS(IDS_MSG_INITERROR), MB_OK|MB_ICONSTOP);
		return false;
	}		

	// Set the locale to english and load the xml information file...
	try
	{
		MTParserLocalizer::getInstance()->setLocale(m_lang.GetBuffer(0));		
	}
	catch( MTParserException &e )
	{
		MessageBox(getAllExceptionString(e).c_str(), RToS(IDS_TITLE_INDEXUNAVAILABLE), MB_OK|MB_ICONSTOP);		
	}
	
	UpdateData(0);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CMathExprDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMathExprDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMathExprDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMathExprDlg::OnOK() 
{
	//CDialog::OnOK();
}

void CMathExprDlg::OnEvaluate() 
{
	UpdateData(1);	
	m_msg = _T("");

	try
	{
		m_result = m_pParser->evaluate(m_expr.GetBuffer(0));			
		
		unsigned int nbUsedVars = m_pParser->getNbUsedVars();
		if( nbUsedVars > 0 )
		{

			m_msg = RToS(IDS_USEDVARIABLES) + _T(": ");
			for( unsigned int t=0; t<nbUsedVars; t++ )
			{
				m_msg += m_pParser->getUsedVar(t).c_str();
				if( t != nbUsedVars-1 )
				{
					m_msg += _T(", ");
				}					
			}

			setMsg(m_msg, IDI_INFORMATION);
		}
		else
		{			
			setMsg(RToS(IDS_NOVARIABLEUSED), IDI_INFORMATION);
		}
		
		if( m_pParser->isConstant() )
		{
			m_msg += _T("\r\n");
			m_msg += RToS(IDS_CONSTEXPR);

			setMsg(m_msg, IDI_INFORMATION);
		}

		if( !m_pParser->isFinite() )
		{
			m_msg += _T("\r\n");
			m_msg += RToS(IDS_INVALIDRESULT);
			m_result = 0;
			setMsg(m_msg, IDI_INFORMATION);
		}
	}
	catch( MTParserException &e )
	{
		printException(e);
	}

	UpdateData(0);	
}

void CMathExprDlg::OnBenchmark() 
{
	UpdateData(1);	
	setMsg(RToS(IDS_BENCHPROCESSING), NULL);
	UpdateData(0);	
	UpdateWindow();	

	try
	{	
		
		MTSTRING expr = m_expr.GetBuffer(0);
		m_pParser->compile(m_expr.GetBuffer(0));

		unsigned int loops;
		unsigned int elapsed;	
		bool isValid;
		CString msg;

		if( m_benchType == 0 )		
		{
			// evaluation benchmark
			EvaluateBenchmark bench;
			bench.setParser( m_pParser );
			isValid = bench.bench(500, loops, elapsed);
			msg = RToS(IDS_TITLE_EVALBENCHRESULT) + _T(":\r\n\r\n");
			msg += RToS(IDS_TIMEPEREVAL) + _T(" = %f\r\n");
			msg += RToS(IDS_EVALPERSEC) + _T(" = %d");			
		}
		else
		{
			// compilation benchmark
			CompileBenchmark bench;
			bench.setParser( m_pParser, expr );
			isValid = bench.bench(50, loops, elapsed);

			msg = RToS(IDS_TITLE_COMPILBENCHRESULT) + _T(":\r\n\r\n");
			msg += RToS(IDS_TIMEPERCOMP) + _T(" = %f\r\n");
			msg += RToS(IDS_COMPPERSEC) + _T(" = %d");					
		}
	
		if( isValid )
		{
			double each = (elapsed)/(double)loops;
			int nbEvalPerSec = 1000*loops/elapsed;							
			m_msg.Format(msg, each, nbEvalPerSec);	
			setMsg(m_msg, IDI_INFORMATION);
		}
		else
		{
			CString msg = RToS(IDS_MSG_BENCHERROR);			
			setMsg(msg, IDI_ERROR);
		}
		
	}
	catch( MTParserException &e )
	{
		printException(e);
	}

	UpdateData(0);	
	
	
}


void CMathExprDlg::OnIndex() 
{
	IndexDlg index(m_pParser);		
	index.DoModal();	
}

void CMathExprDlg::printException(const MTParserException &e)
{	
	setMsg(getAllExceptionString(e).c_str(), IDI_ERROR);
}


BOOL CMathExprDlg::DestroyWindow() 
{

	return CDialog::DestroyWindow();
}

void CMathExprDlg::OnDefinemacro() 
{
	CDefineMacroDlg dlg;
	dlg.setParser(m_pParser);
	dlg.DoModal();
}

void CMathExprDlg::OnFileExit()
{
	EndDialog(IDOK);
	
}

void CMathExprDlg::OnLanguagesEnglish()
{
	if( m_lang != _T("en") )
	{
		m_lang = _T("en");
		EndDialog(IDSWITCHLANG);
	}
}

void CMathExprDlg::OnLanguagesFrench()
{
	if( m_lang != _T("fr") )
	{
		m_lang = _T("fr");
		EndDialog(IDSWITCHLANG);
	}
}

void CMathExprDlg::setMsg(const CString &msg, const MTCHAR* icon)
{
	m_msg = msg;	
	HICON hIcon = LoadIcon(NULL, icon);
	m_msgIcon.SetIcon(hIcon);	
	UpdateData(0);
}
