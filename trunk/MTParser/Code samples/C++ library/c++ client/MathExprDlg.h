// MathExprDlg.h : header file
//

#if !defined(AFX_MATHEXPRDLG_H__A71C510C_42B2_4A9C_8015_074901D2229D__INCLUDED_)
#define AFX_MATHEXPRDLG_H__A71C510C_42B2_4A9C_8015_074901D2229D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../../MTParserLib/MTParser.h"
#include "Benchmarker.h"
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// CMathExprDlg dialog


class CMathExprDlg : public CDialog
{
// Construction
public:
	CMathExprDlg(CWnd* pParent = NULL);	// standard constructor	
	int m_varXID, m_varYID, m_varZID;
	CString m_lang;
	class MTParser *m_pParser;

	
	void printException(const MTParserException &e);	
	void setMsg(const CString &msg, const MTCHAR * icon);

	// Evaluation benchmark 
	class EvaluateBenchmark : public Benchmarker
	{
	public:

		void setParser( MTParser *pParser ){ m_pParser = pParser; }

		virtual void doWork(){ double res = m_pParser->evaluate(); }

	private:

		MTParser *m_pParser;

	};

	// Compilation benchmark 
	class CompileBenchmark : public Benchmarker
	{
	public:

		void setParser( MTParser *pParser, MTSTRING &expr ){ m_pParser = pParser; m_expr = expr;}

		virtual void doWork(){ m_pParser->compile(m_expr.c_str()); }

	private:

		MTParser *m_pParser;
		MTSTRING m_expr;

	};

// Dialog Data
	//{{AFX_DATA(CMathExprDlg)
	enum { IDD = IDD_MATHEXPR_DIALOG };
	CButton	m_benchBtn;
	CButton	m_evaluateBtn;
	CString	m_expr;
	CString	m_msg;
	double	m_varx;
	double	m_vary;
	double	m_varz;
	double	m_result;
	int		m_benchType;
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
public:
	afx_msg void OnFileExit();
	afx_msg void OnLanguagesEnglish();
	afx_msg void OnLanguagesFrench();
	CStatic m_msgIcon;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATHEXPRDLG_H__A71C510C_42B2_4A9C_8015_074901D2229D__INCLUDED_)
