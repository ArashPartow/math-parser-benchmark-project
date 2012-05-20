// DefineMacroDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MathExpr.h"
#include "DefineMacroDlg.h"
#include "Localization.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDefineMacroDlg dialog


CDefineMacroDlg::CDefineMacroDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDefineMacroDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDefineMacroDlg)
	m_symbol = _T("");
	m_function = _T("");
	m_desc = _T("");
	m_msg = _T("");
	//}}AFX_DATA_INIT
}


void CDefineMacroDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDefineMacroDlg)
	DDX_Text(pDX, IDC_SYMBOL, m_symbol);
	DDX_Text(pDX, IDC_FUNCTION, m_function);
	DDX_Text(pDX, IDC_DESCRIPTION, m_desc);
	DDX_Text(pDX, IDC_MSG, m_msg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDefineMacroDlg, CDialog)
	//{{AFX_MSG_MAP(CDefineMacroDlg)
	ON_BN_CLICKED(IDC_DEFINEMACRO, OnDefinemacro)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDefineMacroDlg message handlers

void CDefineMacroDlg::setParser(MTParser *pParser)
{
	m_pParser = pParser;
}

void CDefineMacroDlg::OnDefinemacro() 
{
	UpdateData(1);
	try
	{
		m_pParser->defineMacro(m_symbol.GetBuffer(0), m_function.GetBuffer(0), m_desc.GetBuffer(0));
		
		m_msg = RToS(IDS_MSG_NEWMACRODEFINED);	
	}
	catch( MTParserException &e )
	{		
		m_msg = getAllExceptionString(e).c_str();		
	}	

	UpdateData(0);
}
