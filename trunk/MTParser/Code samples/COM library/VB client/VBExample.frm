VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "MTParserCOM: VB client demo"
   ClientHeight    =   3690
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   6390
   LinkTopic       =   "Form1"
   ScaleHeight     =   3690
   ScaleWidth      =   6390
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton DefineMacro 
      Caption         =   "Define Macro"
      Height          =   375
      Left            =   4920
      TabIndex        =   15
      Top             =   3120
      Width           =   1335
   End
   Begin VB.CommandButton Index 
      Caption         =   "Index"
      Height          =   375
      Left            =   4920
      TabIndex        =   8
      Top             =   2640
      Width           =   1335
   End
   Begin VB.TextBox VarZ 
      Height          =   285
      Left            =   840
      TabIndex        =   7
      Text            =   "0"
      Top             =   1560
      Width           =   975
   End
   Begin VB.TextBox VarY 
      Height          =   285
      Left            =   840
      TabIndex        =   6
      Text            =   "0"
      Top             =   1200
      Width           =   975
   End
   Begin VB.TextBox VarX 
      Height          =   285
      Left            =   840
      TabIndex        =   5
      Text            =   "0"
      Top             =   840
      Width           =   975
   End
   Begin VB.TextBox Result 
      Enabled         =   0   'False
      Height          =   375
      Left            =   3840
      Locked          =   -1  'True
      TabIndex        =   4
      Text            =   "0"
      Top             =   1440
      Width           =   2055
   End
   Begin VB.TextBox Msg 
      Appearance      =   0  'Flat
      BackColor       =   &H80000004&
      BorderStyle     =   0  'None
      Enabled         =   0   'False
      Height          =   855
      Left            =   120
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      TabIndex        =   3
      Top             =   2520
      Width           =   4335
   End
   Begin VB.CommandButton Benchmark 
      Caption         =   "Benchmark"
      Height          =   615
      Left            =   2040
      TabIndex        =   2
      Top             =   1560
      Width           =   1455
   End
   Begin VB.TextBox Expr 
      Height          =   375
      Left            =   240
      TabIndex        =   1
      Text            =   "pi*min(x+y+sin(z)/2^3-40.9988*2, avg(y,x*10,3,5))"
      Top             =   240
      Width           =   5895
   End
   Begin VB.CommandButton Evaluate 
      Caption         =   "Evaluate"
      Default         =   -1  'True
      Height          =   615
      Left            =   2040
      TabIndex        =   0
      Top             =   840
      Width           =   1455
   End
   Begin VB.Frame Frame1 
      Caption         =   "Result"
      Height          =   975
      Left            =   3720
      TabIndex        =   10
      Top             =   1080
      Width           =   2415
   End
   Begin VB.Frame Frame2 
      Height          =   2415
      Left            =   120
      TabIndex        =   11
      Top             =   0
      Width           =   6135
      Begin VB.Label Label1 
         Caption         =   "X ="
         Height          =   375
         Left            =   120
         TabIndex        =   14
         Top             =   960
         Width           =   495
      End
      Begin VB.Label Label2 
         Caption         =   "Y ="
         Height          =   375
         Left            =   120
         TabIndex        =   13
         Top             =   1320
         Width           =   495
      End
      Begin VB.Label Label3 
         Caption         =   "Z ="
         Height          =   375
         Left            =   120
         TabIndex        =   12
         Top             =   1680
         Width           =   495
      End
   End
   Begin VB.Label Label4 
      Caption         =   "Result:"
      Height          =   255
      Left            =   3960
      TabIndex        =   9
      Top             =   1200
      Width           =   1095
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private Declare Function GetTickCount Lib "kernel32" () As Long

Dim m_parser As New MTParser
Dim m_varx As New MTDouble
Dim m_vary As New MTDouble
Dim m_varz As New MTDouble



Private Sub form_load()



    MacroDefinition.SetParser m_parser
  
    
    ' Define the variables and keep the keys to speed up value assignations
    m_varx.Create "x", 0
    m_vary.Create "y", 0
    m_varz.Create "z", 0
    
    m_parser.defineVar m_varx
    m_parser.defineVar m_vary
    m_parser.defineVar m_varz
      
    ' Define a shared double variable for test purpose
    Dim v As New MTDouble
    
    v.Create "v", 1
    m_parser.defineVar v
    Dim r As Double
    r = m_parser.Evaluate("v")
    v.Value = 10        ' Change the variable's value
    r = m_parser.Evaluate("v")
    
     
    ' Create another parser and copy the existing parser configuration
    Dim p2 As New MTParser
    p2.Copy m_parser
    
    r = p2.Evaluate("v")    ' the shared variable has been copied
    
    ' Changing the shared variable's value impact all parsers using this variable
    v.Value = 3
    r = p2.Evaluate("v")
    r = m_parser.Evaluate("v")
    
    
    
    
    
    ' Define a constant
    m_parser.defineConst "pi", 3.14159
    
    ' When the localizer COM object is available, use the
    ' following code to load all plug-ins in a directory...
    'Dim loc As New MTParserLocalizer
    'loc.setLocale "fr"
    'loc.registerAllLibraries App.Path, "*.xml"
    
    
    'm_parser.loadAllPlugins App.Path, "*.xml"
    
    Exit Sub

load_error:

    MsgBox "Error: " & getLastExcepText(m_parser)
       
End Sub

Private Function getLastExcepText(parser As MTParser) As String

    Dim Msg As String
    Dim e As New MTExcepData
    Dim localizer As New MTParserLocalizer
    Dim desc As String
    
    Do
        parser.getLastExcep e
        
        If e.getID() <> "ok" Then
            desc = getLocalizedExcepText(e, localizer)
            If desc = "" Then
                ' Take the default description
                desc = e.getDescription()
            End If
            Msg = Msg + desc
            Msg = Msg + vbCrLf
        End If
    Loop Until e.getID() = "ok"
    
    getLastExcepText = Msg
End Function

' Get the localized exception text.  Return an empty string if not available
Private Function getLocalizedExcepText(data As MTExcepData, localizer As MTParserLocalizer) As String
    On Error GoTo unavailableDesc
    
    getLocalizedExcepText = localizer.getExcep(data)
    Exit Function
unavailableDesc:
    getLocalizedExcepText = ""
    
End Function


Private Sub Benchmark_Click()
    
On Error GoTo benchmark_error

    
    Dim benchParser As New MTParser
    benchParser.Copy m_parser
                
    Dim x As New MTDoubleVector
    Dim y As New MTDoubleVector
    Dim z As New MTDoubleVector

    x.Create ("x")
    y.Create ("y")
    z.Create ("z")

    benchParser.undefineAllVars
    benchParser.defineVar x
    benchParser.defineVar y
    benchParser.defineVar z

    ' Compile the expression only once
    benchParser.compile Expr.Text
                
    ' Generate random variable values...
    Dim nbEvals As Long
    nbEvals = 800000

    Dim xval() As Double
    Dim yval() As Double
    Dim zval() As Double
    ReDim xval(nbEvals) As Double
    ReDim yval(nbEvals) As Double
    ReDim zval(nbEvals) As Double
    
    Dim t As Long
    xval(0) = Val(VarX)
    yval(0) = Val(VarY)
    zval(0) = Val(VarZ)
    For t = 1 To nbEvals
        xval(t) = xval(0)
        yval(t) = yval(t - 1) + 1
        zval(t) = zval(0)
    Next t
    
    ' Set values...
    x.setValueVectorVB6 xval
    y.setValueVectorVB6 yval
    z.setValueVectorVB6 zval
    
    ' this will contain all the results after evaluations
    Dim results() As Double
    ReDim results(nbEvals) As Double
   
    
    Dim beginTime As Long, endTime As Long
    
    beginTime = GetTickCount    ' start the timer
    
    benchParser.evaluateCompiledBatchVB6 nbEvals, results
    
    endTime = GetTickCount  ' stop the timer
    Dim elapsedTime As Integer
    elapsedTime = endTime - beginTime
    
    Dim nbEvalSec As Long
    Dim timePerEval As Double
    timePerEval = elapsedTime / nbEvals
    nbEvalSec = nbEvals / elapsedTime * 1000
    
    Msg = "Nb. Evaluations: " & nbEvals
    Msg = Msg + Chr$(13) + Chr$(10)
    Msg = Msg + "Elapsed time (ms): " & (elapsedTime)
    Msg = Msg + Chr$(13) + Chr$(10)
    Msg = Msg + "Time per evaluation (ms): " & timePerEval
    Msg = Msg + Chr$(13) + Chr$(10)
    
    Msg = Msg + "Nb. Eval per sec: " & nbEvalSec
    
    Exit Sub
    
benchmark_error:

    Msg = "Error: " & getLastExcepText(m_parser)
    
    
    

End Sub

Private Sub Evaluate_Click()

On Error GoTo evaluate_error
    
    ' Update the variable' values
    m_varx.Value = Val(VarX)
    m_vary.Value = Val(VarY)
    m_varz.Value = Val(VarZ)
    
    ' Evaluate the expression with the current variable' values
    Result = m_parser.Evaluate(Expr)
    
    ' Print the used variables
    Dim nbUsedVars As Integer
    nbUsedVars = m_parser.getNbUsedVars
    
    Dim str As String
    Msg = "Used variables: "
           
    Dim t As Integer
    
    For t = 0 To nbUsedVars - 1
        
        Msg = Msg + m_parser.getUsedVar(t)
        If t <> nbUsedVars - 1 Then Msg = Msg & ", "
    Next t
    
    
    Exit Sub
    
evaluate_error:

    Msg = "Syntax error: " & getLastExcepText(m_parser)
   
End Sub

Private Sub Index_Click()

    Call IndexDlg.SetParser(m_parser)
    Call IndexDlg.Show(1, Form1)

End Sub

Private Sub DefineMacro_Click()
    MacroDefinition.Show 1, Form1
End Sub

