VERSION 5.00
Begin VB.Form MacroDefinition 
   Caption         =   "Macro Definition"
   ClientHeight    =   3360
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   8385
   LinkTopic       =   "Form2"
   ScaleHeight     =   3360
   ScaleWidth      =   8385
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame1 
      Caption         =   "Macro"
      Height          =   2775
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   7935
      Begin VB.TextBox MacroFunction 
         Height          =   375
         Left            =   2280
         TabIndex        =   8
         Top             =   720
         Width           =   5295
      End
      Begin VB.CommandButton DefineMacro 
         Caption         =   "Define"
         Height          =   375
         Left            =   6000
         TabIndex        =   7
         Top             =   2160
         Width           =   1455
      End
      Begin VB.TextBox MacroDescription 
         Height          =   375
         Left            =   360
         TabIndex        =   6
         Top             =   1560
         Width           =   7215
      End
      Begin VB.TextBox MacroSymbol 
         Height          =   375
         Left            =   360
         TabIndex        =   4
         Top             =   720
         Width           =   1455
      End
      Begin VB.Label Label4 
         Caption         =   "Macro's description"
         Height          =   255
         Left            =   360
         TabIndex        =   5
         Top             =   1320
         Width           =   1935
      End
      Begin VB.Label Label3 
         Caption         =   "Macro's function"
         Height          =   255
         Left            =   2280
         TabIndex        =   3
         Top             =   480
         Width           =   2055
      End
      Begin VB.Label Label2 
         Alignment       =   2  'Center
         Caption         =   "="
         Height          =   495
         Left            =   1920
         TabIndex        =   2
         Top             =   720
         Width           =   255
      End
      Begin VB.Label Label1 
         Caption         =   "Macro' symbol"
         Height          =   255
         Left            =   360
         TabIndex        =   1
         Top             =   480
         Width           =   1215
      End
   End
End
Attribute VB_Name = "MacroDefinition"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim m_parser As MTParser


Private Sub DefineMacro_Click()
    On Error GoTo define_error
    
    m_parser.DefineMacro MacroSymbol, MacroFunction, MacroDescription
    
    MsgBox "New macro defined: " & MacroSymbol
    Exit Sub
define_error:
    MsgBox "Error defining the macro: " & Err.Description
    
End Sub

Public Sub SetParser(parser As MTParser)
    Set m_parser = parser
End Sub

