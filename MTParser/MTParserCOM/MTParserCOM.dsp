# Microsoft Developer Studio Project File - Name="MTParserCOM" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MTParserCOM - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MTParserCOM.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MTParserCOM.mak" CFG="MTParserCOM - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MTParserCOM - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MTParserCOM - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MTParserCOM - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "UNICODE" /D "_UNICODE" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc0c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc0c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Performing registration
OutDir=.\Debug
TargetPath=.\Debug\MTParserCOM.dll
InputPath=.\Debug\MTParserCOM.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "MTParserCOM - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MTParserCOM___Win32_Release"
# PROP BASE Intermediate_Dir "MTParserCOM___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MD /W3 /GX /O2 /Ob2 /D "_MBCS" /D "_USRDLL" /D "UNICODE" /D "_UNICODE" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /FD /c
# ADD BASE RSC /l 0xc0c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc0c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /debug
# Begin Custom Build - Performing registration
OutDir=.\Release
TargetPath=.\Release\MTParserCOM.dll
InputPath=.\Release\MTParserCOM.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "MTParserCOM - Win32 Debug"
# Name "MTParserCOM - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\MTDate.cpp

!IF  "$(CFG)" == "MTParserCOM - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MTParserCOM - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MTDouble.cpp

!IF  "$(CFG)" == "MTParserCOM - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MTParserCOM - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MTParser.cpp

!IF  "$(CFG)" == "MTParserCOM - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MTParserCOM - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MTParserCOM.cpp

!IF  "$(CFG)" == "MTParserCOM - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MTParserCOM - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MTParserCOM.def
# End Source File
# Begin Source File

SOURCE=.\MTParserCOM.idl
# ADD MTL /tlb ".\MTParserCOM.tlb" /h "MTParserCOM.h" /iid "MTParserCOM_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\MTParserCOM.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\MTDate.h
# End Source File
# Begin Source File

SOURCE=.\MTDouble.h
# End Source File
# Begin Source File

SOURCE=.\MTParser.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\MTDate.rgs
# End Source File
# Begin Source File

SOURCE=.\MTDemoSplash.bmp
# End Source File
# Begin Source File

SOURCE=.\MTDouble.rgs
# End Source File
# Begin Source File

SOURCE=.\MTParser.rgs
# End Source File
# End Group
# Begin Source File

SOURCE=.\History.txt
# End Source File
# End Target
# End Project
