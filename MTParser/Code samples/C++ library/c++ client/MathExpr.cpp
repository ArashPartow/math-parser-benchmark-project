// MathExpr.cpp : Defines the class behaviors for the application.
//
//#include <vld.h>		// memory leak detector
#include "stdafx.h"
#include "MathExpr.h"
#include "MathExprDlg.h"
#include "../../../MTParserLib/MTParser.h"
#include "../../../MTParserLib/MTParserTestCases.h"
#include "../../../MTParserLib/MTParserLocalizer.h"
#include "../../../MTParserLib/MTTools.h"
#include "Localization.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DATEPLUGINFILE		_T("MTDatePlugin.dll")			// date plug-in file
#define NUMALGOPLUGINFILE	_T("MTNumAlgoPlugin.dll")		// num algo plug-in file
#define MTPARSERINFOFILE	_T("MTParserInfoFile.dll")		// info file manager file
#define MTPLUGINTLB			_T("_MTParserPlugin.tlb")		// plug-in tlb file

/////////////////////////////////////////////////////////////////////////////
// CMathExprApp

BEGIN_MESSAGE_MAP(CMathExprApp, CWinApp)
	//{{AFX_MSG_MAP(CMathExprApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMathExprApp construction

CMathExprApp::CMathExprApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMathExprApp object

CMathExprApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMathExprApp initialization

BOOL CMathExprApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CMathExprDlg *pDlg = NULL;
	MTParser parser;	

	if( !create(&parser) )
	{
		return FALSE;
	}
	
	int nResponse;
	CString lang = _T("en");

	do
	{// load the satellite...
		loadSat(lang);

		pDlg = new CMathExprDlg();
		pDlg->m_lang = lang;
		pDlg->m_pParser = &parser;
		m_pMainWnd = NULL; 	

		// launch the dialog
		nResponse = pDlg->DoModal();		
		lang = pDlg->m_lang;
		delete pDlg;
	}
	while( nResponse == IDSWITCHLANG);
	
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

bool CMathExprApp::create(class MTParser *pParser)
{
	
	CoInitialize(NULL);		

	// Initialize the parser... 
	try	
	{			
		// constant definitions
		pParser->defineConst(_T("pi"), 3.14159265359);
		pParser->defineConst(_T("e"), 2.7182818284590452354);	
		
	}
	catch( MTParserException &e )
	{		
		MessageBox(NULL, getAllExceptionString(e).c_str(), RToS(IDS_MSG_INITERROR), MB_OK|MB_ICONSTOP);
		return false;
	}	

	// Register external files...
	
	if( !MTTools::registerCOMObject(MTPARSERINFOFILE) )
	{
		MessageBox(NULL, _T("Unable to register the info file COM object.  Localized information will be unavailable."), RToS(IDS_MSG_INITERROR), MB_OK|MB_ICONWARNING);
	}

	if( !MTTools::registerTypeLib(MTPLUGINTLB) )
	{
		MessageBox(NULL, _T("Unable to register the plug-in tlb file.  Plug-ins may be unavailable."), RToS(IDS_MSG_INITERROR), MB_OK|MB_ICONWARNING);
	}

	if( !MTTools::registerCOMObject(DATEPLUGINFILE) )
	{
		MessageBox(NULL, _T("Unable to register date plug-in file."), RToS(IDS_MSG_INITERROR), MB_OK|MB_ICONWARNING);
	}

	if( !MTTools::registerCOMObject(NUMALGOPLUGINFILE) )
	{
		MessageBox(NULL, _T("Unable to register the numerical algorithm plug-in file."), RToS(IDS_MSG_INITERROR), MB_OK|MB_ICONWARNING);
	}	
	

	// load plug-ins...
	try
	{		
		MTSTRING directory = _T("./");
		MTSTRING pluginFileSearchPattern = _T("*.xml");
		pParser->loadAllPlugins(directory.c_str(), pluginFileSearchPattern.c_str());				
	}
	catch( MTParserException &e )
	{
		MessageBox(NULL, getAllExceptionString(e).c_str(), RToS(IDS_TITLE_NUMALGOPLUGIN), MB_OK|MB_ICONINFORMATION);
	}
	
	// load info files...
	try
	{		
		MTParserLocalizer::getInstance()->registerAllLibraries(_T("./"), _T("*.xml"));		
	}
	catch( MTParserException &e )
	{
		MessageBox(NULL, getAllExceptionString(e).c_str(), RToS(IDS_TITLE_INDEXUNAVAILABLE), MB_OK|MB_ICONSTOP);		
	}
	
	
	
	// Modification safety net! Unit tests.		
	
	MTParserTestSuite tc;	
	if( !tc.doTests() )
	{
		MessageBox(NULL, _T("Unit tests failed!"), _T(""), MB_OK);
	}

	return true;
}

void CMathExprApp::loadSat(const CString &lang)
{
	HINSTANCE hIns = NULL;
	
	if( lang == _T("en") )
	{		
		// the english resource is embedded with the application
		hIns = AfxGetInstanceHandle();
		
	}
	else
	{
		hIns = LoadLibrary(_T("MathExprFr.dll"));
		if( hIns == NULL )
		{
			MessageBox(NULL, _T("Unable to load the french resources.  Make sure the MathExprFr.dll file exists."), _T("Missing file"), MB_OK|MB_ICONSTOP);
			hIns = AfxGetInstanceHandle();
		}

	}

	AfxSetResourceHandle(hIns);

}