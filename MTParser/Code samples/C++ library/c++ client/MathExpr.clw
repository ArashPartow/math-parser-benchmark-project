; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDefineMacroDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MathExpr.h"

ClassCount=5
Class1=CMathExprApp
Class2=CMathExprDlg
Class3=CAboutDlg

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_MATHEXPR_DIALOG
Resource4=IDD_INDEXDLG
Resource5=IDD_ABOUTBOX (French (France))
Class4=IndexDlg
Resource6=IDD_MATHEXPR_DIALOG (French (France))
Class5=CDefineMacroDlg
Resource7=IDD_DEFINEMACRO

[CLS:CMathExprApp]
Type=0
HeaderFile=MathExpr.h
ImplementationFile=MathExpr.cpp
Filter=N

[CLS:CMathExprDlg]
Type=0
HeaderFile=MathExprDlg.h
ImplementationFile=MathExprDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CMathExprDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=MathExprDlg.h
ImplementationFile=MathExprDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_MATHEXPR_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CMathExprDlg

[DLG:IDD_MATHEXPR_DIALOG (French (France))]
Type=1
Class=CMathExprDlg
ControlCount=18
Control1=IDC_EXPR,edit,1350631552
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_VARX,edit,1350631552
Control8=IDC_VARY,edit,1350631552
Control9=IDC_VARZ,edit,1350631552
Control10=IDC_EVALUATE,button,1342242817
Control11=IDC_MSG,edit,1342248964
Control12=IDC_STATIC,button,1342177287
Control13=IDC_RESULT,edit,1350633600
Control14=IDC_INDEX,button,1342242816
Control15=IDC_BENCHMARK,button,1342242816
Control16=IDC_DEFINEMACRO,button,1342242816
Control17=IDC_BENCHEVAL,button,1342308361
Control18=IDC_BENCHCOMP,button,1342177289

[DLG:IDD_ABOUTBOX (French (France))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_INDEXDLG]
Type=1
Class=IndexDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_DEFINEDOPS,SysListView32,1350666261
Control6=IDC_DEFINEDFUNCS,SysListView32,1350666261
Control7=IDC_DEFINEDCONSTS,SysListView32,1350666261

[CLS:IndexDlg]
Type=0
HeaderFile=IndexDlg.h
ImplementationFile=IndexDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_DEFINEDFUNCS

[DLG:IDD_DEFINEMACRO]
Type=1
Class=CDefineMacroDlg
ControlCount=9
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_SYMBOL,edit,1350631552
Control6=IDC_FUNCTION,edit,1350631552
Control7=IDC_DESCRIPTION,edit,1350631552
Control8=IDC_DEFINEMACRO,button,1342242816
Control9=IDC_MSG,edit,1342248964

[CLS:CDefineMacroDlg]
Type=0
HeaderFile=DefineMacroDlg.h
ImplementationFile=DefineMacroDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CDefineMacroDlg
VirtualFilter=dWC

