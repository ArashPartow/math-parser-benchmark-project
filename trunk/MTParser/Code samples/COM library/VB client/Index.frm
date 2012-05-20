VERSION 5.00
Begin VB.Form IndexDlg 
   Caption         =   "Operator, function and constant index"
   ClientHeight    =   7185
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   10545
   LinkTopic       =   "Form2"
   ScaleHeight     =   7185
   ScaleWidth      =   10545
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Ok 
      Caption         =   "Ok"
      Height          =   375
      Left            =   6600
      TabIndex        =   6
      Top             =   6600
      Width           =   1095
   End
   Begin VB.Frame Frame2 
      Caption         =   "Defined Constants"
      Height          =   1575
      Left            =   240
      TabIndex        =   4
      Top             =   4800
      Width           =   10095
      Begin VB.ListBox Constants 
         Height          =   1035
         Left            =   120
         Sorted          =   -1  'True
         TabIndex        =   5
         Top             =   360
         Width           =   9855
      End
   End
   Begin VB.Frame DefinedFuncs 
      Caption         =   "Defined Functions"
      Height          =   2775
      Left            =   240
      TabIndex        =   2
      Top             =   1920
      Width           =   10095
      Begin VB.ListBox Functions 
         Height          =   2010
         Left            =   120
         Sorted          =   -1  'True
         TabIndex        =   3
         Top             =   360
         Width           =   9855
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Defined Operators"
      Height          =   1695
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   10095
      Begin VB.ListBox Operators 
         Height          =   1035
         Left            =   120
         Sorted          =   -1  'True
         TabIndex        =   1
         Top             =   360
         Width           =   9855
      End
   End
End
Attribute VB_Name = "IndexDlg"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim m_parser As MTParser


Public Sub SetParser(parser As MTParser)
    Set m_parser = parser

End Sub

Private Sub form_load()

On Error Resume Next

    Dim loc As New MTParserLocalizer
        
    Dim str As String
    
    nbOps = m_parser.getNbDefinedOps
    Dim opInfo As sMTOperator
    
    For t = 0 To nbOps - 1
        
        opInfo = m_parser.getOp(t)
        opInfo = loc.getOpInfo(opInfo.ID)
        
        str = opInfo.symbol & Chr$(9) & opInfo.helpString & Chr$(9) & opInfo.Description
        Operators.AddItem str
    Next t
    
    nbFuncs = m_parser.getNbDefinedFuncs
    Dim funcInfo As sMTFunction
    Dim syntax As sMTSyntax
    syntax = m_parser.getSyntax()
    
    For t = 0 To nbFuncs - 1
        
        funcInfo = m_parser.getFunc(t)
        funcInfo = loc.getFuncInfo(funcInfo.ID, syntax)
        
        str = funcInfo.symbol & Chr$(9) & funcInfo.helpString & Chr$(9) & funcInfo.Description
        Functions.AddItem str
    Next t
   
    
    nbConsts = m_parser.getNbDefinedConsts
    Dim constInfo As sMTConstant
    
    For t = 0 To nbConsts - 1
        
        constInfo = m_parser.getConst(t)
        
        str = constInfo.Name & Chr$(9) & constInfo.Value
        Constants.AddItem str
    Next t
    


End Sub


Private Sub Ok_Click()

    Me.Hide
    
End Sub
