#if !defined(AFX_INDEXDLG_H__D12C8C60_76D3_46D8_9C1F_0F2E6CB92867__INCLUDED_)
#define AFX_INDEXDLG_H__D12C8C60_76D3_46D8_9C1F_0F2E6CB92867__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IndexDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// IndexDlg dialog

class IndexDlg : public CDialog
{
// Construction
public:
	IndexDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(IndexDlg)
	enum { IDD = IDD_INDEXDLG };
	CString	m_consts;
	CString	m_funcs;
	CString	m_ops;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(IndexDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(IndexDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INDEXDLG_H__D12C8C60_76D3_46D8_9C1F_0F2E6CB92867__INCLUDED_)
