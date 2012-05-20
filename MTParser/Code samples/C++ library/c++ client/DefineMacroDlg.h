#if !defined(AFX_DEFINEMACRODLG_H__CC709227_DFC1_42B8_B437_CCCAA5C06986__INCLUDED_)
#define AFX_DEFINEMACRODLG_H__CC709227_DFC1_42B8_B437_CCCAA5C06986__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DefineMacroDlg.h : header file
//

#include "../../../MTParserLib/MTParser.h"

/////////////////////////////////////////////////////////////////////////////
// CDefineMacroDlg dialog

class CDefineMacroDlg : public CDialog
{
// Construction
public:
	CDefineMacroDlg(CWnd* pParent = NULL);   // standard constructor

	void setParser(MTParser *pParser);

	MTParser *m_pParser;

// Dialog Data
	//{{AFX_DATA(CDefineMacroDlg)
	enum { IDD = IDD_DEFINEMACRO };
	CString	m_symbol;
	CString	m_function;
	CString	m_desc;
	CString	m_msg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDefineMacroDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDefineMacroDlg)
	afx_msg void OnDefinemacro();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEFINEMACRODLG_H__CC709227_DFC1_42B8_B437_CCCAA5C06986__INCLUDED_)
