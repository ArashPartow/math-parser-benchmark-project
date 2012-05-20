// MathExprDlg.h : header file
//

#if !defined(AFX_MATHEXPRDLG_H__A71C510C_42B2_4A9C_8015_074901D2229D__INCLUDED_)
#define AFX_MATHEXPRDLG_H__A71C510C_42B2_4A9C_8015_074901D2229D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#import "../../../MTParserCOM/MTParserCOM.tlb" no_namespace

/////////////////////////////////////////////////////////////////////////////
// CMathExprDlg dialog


class CMathExprDlg : public CDialog
{
// Construction
public:
	CMathExprDlg(CWnd* pParent = NULL);	// standard constructor

	IMTParserPtr m_pParser;
	int m_varXID, m_varYID, m_varZID;

	IMTDoublePtr m_varX, m_varY, m_varZ;

	// Get the last exception text
	CString getLastExcepText();
	void defineVar(IMTParserPtr &parser, IMTDoublePtr &var);

// Dialog Data
	//{{AFX_DATA(CMathExprDlg)
	enum { IDD = IDD_MATHEXPR_DIALOG };
	CString	m_expr;
	CString	m_msg;
	double	m_varx;
	double	m_vary;
	double	m_varz;
	double	m_result;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMathExprDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMathExprDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnEvaluate();
	afx_msg void OnQuit();
	afx_msg void OnIndex();
	afx_msg void OnBenchmark();
	afx_msg void OnDefinemacro();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATHEXPRDLG_H__A71C510C_42B2_4A9C_8015_074901D2229D__INCLUDED_)
