// IndexDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MathExpr.h"
#include "IndexDlg.h"
#include "../../../MTParserLib/MTParser.h"
#include "../../../MTParserLib/MTParserLocalizer.h"
#include "../../../MTParserLib/MTTools.h"
#include ".\indexdlg.h"
#include "Localization.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// IndexDlg dialog


IndexDlg::IndexDlg(class MTParser *pParser, CWnd* pParent /*=NULL*/)
	: CDialog(IndexDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(IndexDlg)
	//}}AFX_DATA_INIT

	m_pParser = pParser;
}


void IndexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(IndexDlg)
	DDX_Control(pDX, IDC_DEFINEDCONSTS, m_consts);
	DDX_Control(pDX, IDC_DEFINEDFUNCS, m_funcs);
	DDX_Control(pDX, IDC_DEFINEDOPS, m_ops);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(IndexDlg, CDialog)
	//{{AFX_MSG_MAP(IndexDlg)
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_DBLCLK, IDC_DEFINEDOPS, OnNMDblclkDefinedops)
	ON_NOTIFY(NM_DBLCLK, IDC_DEFINEDFUNCS, OnNMDblclkDefinedfuncs)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// IndexDlg message handlers

BOOL IndexDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	MTParserLocalizer *pLocalizer = MTParserLocalizer::getInstance();

	unsigned int nbOps = m_pParser->getNbDefinedOps();
	unsigned int nbFuncs = m_pParser->getNbDefinedFuncs();
	unsigned int nbConsts = m_pParser->getNbDefinedConsts();

	m_ops.InsertColumn(0, RToS(IDS_COLNAME_SYMBOL), LVCFMT_LEFT, 100);
	m_ops.InsertColumn(1, RToS(IDS_COLNAME_USAGE), LVCFMT_LEFT, 180);
	m_ops.InsertColumn(2, RToS(IDS_COLNAME_DESCRIPTION), LVCFMT_LEFT, 320);

	m_funcs.InsertColumn(0, RToS(IDS_COLNAME_SYMBOL), LVCFMT_LEFT, 100);
	m_funcs.InsertColumn(1, RToS(IDS_COLNAME_USAGE), LVCFMT_LEFT, 180);
	m_funcs.InsertColumn(2, RToS(IDS_COLNAME_DESCRIPTION), LVCFMT_LEFT, 320);

	m_consts.InsertColumn(0, RToS(IDS_COLNAME_SYMBOL), LVCFMT_LEFT, 120);
	m_consts.InsertColumn(1, RToS(IDS_COLNAME_DESCRIPTION), LVCFMT_LEFT, 200);	

	unsigned int t;
	MTSTRING proto;

	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	MTParserLocalizerI::SOpInfo opInfo;
	
	for( t=0; t<nbOps; t++ )
	{
		lvItem.iItem = t;
		try
		{
			opInfo = pLocalizer->getOpInfo(m_pParser->getOp(t)->getID());
			proto = pLocalizer->formatOpPrototype(opInfo);
		}
		catch( MTParserException )
		{
			// no information available... so put the default information
			opInfo.symbol = m_pParser->getOp(t)->getSymbol();
			proto = m_pParser->getOp(t)->getHelpString();
			opInfo.desc = m_pParser->getOp(t)->getDescription();
		}

		lvItem.iSubItem = 0;
		lvItem.pszText = (MTCHAR*)opInfo.symbol.c_str();
		lvItem.iItem =  m_ops.InsertItem(&lvItem);
		m_ops.SetItemData(lvItem.iItem, t);
		
		lvItem.iSubItem = 1;		
		lvItem.pszText = (MTCHAR*)proto.c_str();
		m_ops.SetItem(&lvItem);

		lvItem.iSubItem = 2;
		lvItem.pszText = (MTCHAR*)opInfo.desc.c_str();
		m_ops.SetItem(&lvItem);			
	}

	MTParserLocalizerI::SFuncInfo funcInfo;
	MTSyntax syntax = m_pParser->getSyntax();
	for( t=0; t<nbFuncs; t++ )
	{
		lvItem.iItem = t;
		try
		{
			funcInfo = pLocalizer->getFuncInfo(m_pParser->getFunc(t)->getID());
			proto = pLocalizer->formatFuncPrototype(funcInfo, syntax);
		}
		catch( MTParserException )
		{
			// no information available... so put the default information
			funcInfo.symbol = m_pParser->getFunc(t)->getSymbol();
			proto = m_pParser->getFunc(t)->getHelpString();
			funcInfo.desc = m_pParser->getFunc(t)->getDescription();
		}

		lvItem.iSubItem = 0;
		lvItem.pszText = (MTCHAR*)funcInfo.symbol.c_str();
		lvItem.iItem =  m_funcs.InsertItem(&lvItem);
		m_funcs.SetItemData(lvItem.iItem, t);
		
		lvItem.iSubItem = 1;
		
		lvItem.pszText = (MTCHAR*)proto.c_str();
		m_funcs.SetItem(&lvItem);

		lvItem.iSubItem = 2;
		lvItem.pszText = (MTCHAR*)funcInfo.desc.c_str();
		m_funcs.SetItem(&lvItem);			
	}	
	
	
	MTParserLocalizerI::SConstInfo constInfo;

	MTSTRING constName;
	MTDOUBLE constVal;
	for( t=0; t<nbConsts; t++ )
	{
		lvItem.iItem = t;
		m_pParser->getConst(t, constName, constVal);
		try
		{
			constInfo = pLocalizer->getConstInfo(constName.c_str());
		}
		catch( MTParserException )
		{
			// no information available... so put the default information
			constInfo.symbol = constName;
			constInfo.desc = MTTools::doubleToS(constVal, syntax.decimalPoint);
		}
		
		lvItem.iSubItem = 0;
		lvItem.pszText = (MTCHAR*)constInfo.symbol.c_str();
		lvItem.iItem =  m_consts.InsertItem(&lvItem);
		
		lvItem.iSubItem = 1;
		lvItem.pszText = (MTCHAR*)constInfo.desc.c_str();
		m_consts.SetItem(&lvItem);
				
	}	

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void IndexDlg::OnNMDblclkDefinedops(NMHDR *pNMHDR, LRESULT *pResult)
{
	
}

void IndexDlg::OnNMDblclkDefinedfuncs(NMHDR *pNMHDR, LRESULT *pResult)
{
	int sel = m_funcs.GetSelectionMark();

	if( sel != -1 )
	{
		int funcId = m_funcs.GetItemData(sel);	// the real funcId

		CString msg;
		MTSTRING proto;
		MTParserLocalizerI::SFuncInfo funcInfo;
		try
		{
			funcInfo = MTParserLocalizer::getInstance()->getFuncInfo(m_pParser->getFunc(funcId)->getID());
			proto = MTParserLocalizer::formatFuncPrototype(funcInfo, m_pParser->getSyntax());
		}
		catch( MTParserException )
		{
			// no information available... so put the default information
			funcInfo.symbol = m_pParser->getFunc(funcId)->getSymbol();
			proto = m_pParser->getFunc(funcId)->getHelpString();
			funcInfo.desc = m_pParser->getFunc(funcId)->getDescription();			
		}

		msg = RToS(IDS_COLNAME_DESCRIPTION) + _T("\n\r\t");		
		msg += funcInfo.desc.c_str();

		
		msg += _T("\n\r") + RToS(IDS_COLNAME_PROTOTYPE) + _T("\r\t");		
		msg += proto.c_str();
		
		if( funcInfo.argDescs.size() > 0 )
		{
			msg += _T("\n\r") + RToS(IDS_COLNAME_PARAMETERS);

			for( unsigned int t=0; t<funcInfo.args.size(); t++ )
			{
				if( funcInfo.argDescs[t] != _T("") )
				{
					msg += _T("\r\t");
					msg += funcInfo.args[t].c_str();
					msg += _T("\t");
					msg += funcInfo.argDescs[t].c_str();					
				}
			}
		}

		MessageBox(msg, funcInfo.symbol.c_str());
	}
	
	
	*pResult = 0;
}
