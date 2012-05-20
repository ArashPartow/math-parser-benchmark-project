// MathExpr.h : main header file for the MATHEXPR application
//

#if !defined(AFX_MATHEXPR_H__F6BC4E36_85E1_4F38_A538_F42BA82DAE7B__INCLUDED_)
#define AFX_MATHEXPR_H__F6BC4E36_85E1_4F38_A538_F42BA82DAE7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMathExprApp:
// See MathExpr.cpp for the implementation of this class
//

class CMathExprApp : public CWinApp
{
public:
	CMathExprApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMathExprApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMathExprApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATHEXPR_H__F6BC4E36_85E1_4F38_A538_F42BA82DAE7B__INCLUDED_)
