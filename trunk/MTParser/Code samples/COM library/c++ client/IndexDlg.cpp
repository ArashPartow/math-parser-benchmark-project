// IndexDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MathExpr.h"
#include "IndexDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// IndexDlg dialog


IndexDlg::IndexDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IndexDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(IndexDlg)
	m_consts = _T("");
	m_funcs = _T("");
	m_ops = _T("");
	//}}AFX_DATA_INIT
}


void IndexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(IndexDlg)
	DDX_Text(pDX, IDC_DEFINEDCONSTS, m_consts);
	DDX_Text(pDX, IDC_DEFINEDFUNCS, m_funcs);
	DDX_Text(pDX, IDC_DEFINEDOPS, m_ops);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(IndexDlg, CDialog)
	//{{AFX_MSG_MAP(IndexDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// IndexDlg message handlers
