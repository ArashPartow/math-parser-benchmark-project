// MathExprDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MathExpr.h"
#include "MathExprDlg.h"
#include "IndexDlg.h"
#include "DefineMacroDlg.h"

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
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMathExprDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMathExprDlg)
	DDX_Text(pDX, IDC_EXPR, m_expr);
	DDX_Text(pDX, IDC_MSG, m_msg);
	DDX_Text(pDX, IDC_VARX, m_varx);
	DDX_Text(pDX, IDC_VARY, m_vary);
	DDX_Text(pDX, IDC_VARZ, m_varz);
	DDX_Text(pDX, IDC_RESULT, m_result);
	//}}AFX_DATA_MAP
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
	
	
	m_expr = _T("pi*min(x+y+sin(z)/2^3-40.9988*2, avg(y,x*10,3,5))");	

	CoInitialize(NULL);	
	
	m_pParser.CreateInstance(__uuidof(MTParser));

	IMTParserPtr parser2;
	parser2.CreateInstance(__uuidof(MTParser));	

	IMTDoublePtr v;
	v.CreateInstance(__uuidof(MTDouble));
	v->create(_T("v"), 1);
	v->Putvalue(10);

	m_varX.CreateInstance(__uuidof(MTDouble));
	m_varX->create(_T("x"), 1);

	m_varY.CreateInstance(__uuidof(MTDouble));
	m_varY->create(_T("y"), 0);

	m_varZ.CreateInstance(__uuidof(MTDouble));
	m_varZ->create(_T("z"), 0);
	
	try
	{
		defineVar(m_pParser, m_varX);
		defineVar(m_pParser, m_varY);
		defineVar(m_pParser, m_varZ);		
		
		double r = m_pParser->evaluate(_T("x"));
		

		// constant definitions
		m_pParser->defineConst(_T("pi"), 3.14159265359);		
		m_pParser->defineConst(_T("e"), 2.7182818284590452354);	
		
		// load the Date plugin
		//m_pParser->loadPlugin(_T("{4C639DCD-2043-42DC-9132-4B5C730855D6}"));			
		
		// copy an existing parser configuration
		parser2->copy(m_pParser);
	}
	catch( _com_error )
	{
		MessageBox(getLastExcepText(), _T("Definition error"), MB_OK|MB_ICONSTOP);
		EndDialog(IDCANCEL);
		return TRUE;
	}	
	

	UpdateData(0);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMathExprDlg::defineVar(IMTParserPtr &parser, IMTDoublePtr &var)
{
	IMTVariable *pVar;		
	var.QueryInterface(__uuidof(IMTVariable), &pVar);		// explicitly converts from MTDouble to MTVariable	
	parser->defineVar(pVar);
	pVar->Release();
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

CString CMathExprDlg::getLastExcepText()
{
	CString msg;
	IMTExcepDataPtr e;	
	e.CreateInstance(__uuidof(MTExcepData));
	
	while(1)
	{
		m_pParser->getLastExcep(e);
		BSTR id = e->getID();
		int cmp = lstrcmp(id, _T("ok"));
		SysFreeString(id);

		if( cmp != 0 )
		{
			BSTR desc = e->getDescription();
			msg += desc;			
			msg += _T("\r\n");

			SysFreeString(desc);
		}
		else
		{
			break;
		}		
	}
	
    
    return msg;
}

void CMathExprDlg::OnEvaluate() 
{
	UpdateData(1);	
	m_msg = _T("");

	try
	{		
		m_varX->put_value(m_varx);
		m_varY->put_value(m_vary);
		m_varZ->put_value(m_varz);
		m_result = m_pParser->evaluate(m_expr.GetBuffer(0));
		
		int nbUsedVars = m_pParser->getNbUsedVars();

		if( nbUsedVars > 0 )
		{
			m_msg = _T("Used variables: ");
			for( int t=0; t<nbUsedVars; t++ )
			{

				BSTR symbol = m_pParser->getUsedVar(t);

				m_msg += (wchar_t*)symbol;
				SysFreeString(symbol);

				if( t != nbUsedVars-1 )
				{
					m_msg += _T(", ");
				}
					
			}

		}
		else
		{
			m_msg = _T("No variable used");			
		}
		
	}
	catch( _com_error  )
	{
		m_msg = getLastExcepText();		
	}

	UpdateData(0);	
}

void CMathExprDlg::OnBenchmark() 
{
	UpdateData(1);	
	m_msg = _T("Processing...");
	UpdateData(0);	
	UpdateWindow();


	try	
	{	
		m_pParser->compile(m_expr.GetBuffer(0));

		DWORD begin = GetTickCount();
		
		int loops = 1000000;
		int t;

		for( t=0; t<loops; t++ )
		{
			m_varX->put_value(m_varx);
			m_varY->put_value(m_vary);
			m_varZ->put_value(m_varz);
		
			m_result = m_pParser->evaluateCompiled();	
			
		}

		DWORD end = GetTickCount();
		double each = (end-begin)/(double)loops;	
		int nbEvalPerSec = (int)(1000/each);

		CString msg;
		msg.Format(_T("Number of evaluations = %d\r\nElapsed time(ms) = %d\r\nTime per evaluation(ms) = %f\r\nEvaluations per second = %d"), loops, end-begin, each, nbEvalPerSec);
		m_msg = msg;
		
	}
	catch( _com_error  )
	{
		m_msg = getLastExcepText();
	}

	UpdateData(0);	
	
	
}


void CMathExprDlg::OnIndex() 
{

	
	IndexDlg index;	

	int nbOps = m_pParser->getNbDefinedOps();
	int nbFuncs = m_pParser->getNbDefinedFuncs();
	int nbConsts = m_pParser->getNbDefinedConsts();
	
	CString msg;
	int t;

	for( t=0; t<nbOps; t++ )
	{
		
		sMTOperator op = m_pParser->getOp(t);

		msg += op.symbol;		
		msg += (wchar_t)9;	// tab
		msg += op.helpString;
		msg += _T(",  ");
		msg+= op.description;
		msg += _T("\r\n");	

		
		SysFreeString(op.symbol);
		SysFreeString(op.helpString);
		SysFreeString(op.description);
	}

	index.m_ops = msg;

	msg = _T("");

	for(  t=0; t<nbFuncs; t++ )
	{
		sMTFunction func = m_pParser->getFunc(t);
		
		msg += func.symbol;		
		msg += (wchar_t)9;	// tab
		msg += func.helpString;
		msg += _T(",  ");
		msg += func.description;
		msg += _T("\r\n");

		SysFreeString(func.symbol);
		SysFreeString(func.helpString);
		SysFreeString(func.description);
	}

	index.m_funcs = msg;

	msg = _T("");
	
	CString constValStr;

	for(  t=0; t<nbConsts; t++ )
	{
		sMTConstant c = m_pParser->getConst(t);	

		constValStr.Format(_T("%f"), c.value);

		msg += c.name;		
		msg += (wchar_t)9;	// tab
		msg += constValStr;
		msg += _T("\r\n");

		SysFreeString(c.name);		
	}

	index.m_consts = msg;

	index.DoModal();	
	
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
