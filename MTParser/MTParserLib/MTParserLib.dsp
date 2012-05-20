# Microsoft Developer Studio Project File - Name="MTParserLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=MTParserLib - Win32 Debug Unicode
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MTParserLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MTParserLib.mak" CFG="MTParserLib - Win32 Debug Unicode"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MTParserLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "MTParserLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "MTParserLib - Win32 Release Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE "MTParserLib - Win32 Debug Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MTParserLib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /Ob2 /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /YX /FD /c
# SUBTRACT CPP /WX
# ADD BASE RSC /l 0xc0c /d "NDEBUG"
# ADD RSC /l 0xc0c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/MTParser.lib"

!ELSEIF  "$(CFG)" == "MTParserLib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# SUBTRACT CPP /WX
# ADD BASE RSC /l 0xc0c /d "_DEBUG"
# ADD RSC /l 0xc0c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/MTParserd.lib"

!ELSEIF  "$(CFG)" == "MTParserLib - Win32 Release Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MTParserLib___Win32_Release_Unicode"
# PROP BASE Intermediate_Dir "MTParserLib___Win32_Release_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_Unicode"
# PROP Intermediate_Dir "Release_Unicode"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /Ob2 /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /YX /FD /c
# SUBTRACT BASE CPP /WX
# ADD CPP /nologo /MD /W3 /GX /O2 /Ob2 /D "UNICODE" /D "_UNICODE" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /YX /FD /c
# SUBTRACT CPP /WX
# ADD BASE RSC /l 0xc0c /d "NDEBUG"
# ADD RSC /l 0xc0c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"lib/MTParser.lib"
# ADD LIB32 /nologo /out:"lib/MTParserU.lib"

!ELSEIF  "$(CFG)" == "MTParserLib - Win32 Debug Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MTParserLib___Win32_Debug_Unicode"
# PROP BASE Intermediate_Dir "MTParserLib___Win32_Debug_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_Unicode"
# PROP Intermediate_Dir "Debug_Unicode"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# SUBTRACT BASE CPP /WX
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "UNICODE" /D "_UNICODE" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# SUBTRACT CPP /WX
# ADD BASE RSC /l 0xc0c /d "_DEBUG"
# ADD RSC /l 0xc0c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"lib/MTParserd.lib"
# ADD LIB32 /nologo /out:"lib/MTParserUd.lib"

!ENDIF 

# Begin Target

# Name "MTParserLib - Win32 Release"
# Name "MTParserLib - Win32 Debug"
# Name "MTParserLib - Win32 Release Unicode"
# Name "MTParserLib - Win32 Debug Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\MTParser.cpp
# End Source File
# Begin Source File

SOURCE=.\MTParserCompiler.cpp
# End Source File
# Begin Source File

SOURCE=.\MTParserExcepStrEng.cpp
# End Source File
# Begin Source File

SOURCE=.\MTParserLocalizer.cpp
# End Source File
# Begin Source File

SOURCE=.\MTParserMacroFunc.cpp
# End Source File
# Begin Source File

SOURCE=.\MTParserRegistrar.cpp
# End Source File
# Begin Source File

SOURCE=.\MTParserTestCases.cpp
# End Source File
# Begin Source File

SOURCE=.\MTSearchFile.cpp
# End Source File
# Begin Source File

SOURCE=.\MTTools.cpp
# End Source File
# Begin Source File

SOURCE=.\MTUnicodeANSIDefs.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\MTException.h
# End Source File
# Begin Source File

SOURCE=.\MTGlobalString.h
# End Source File
# Begin Source File

SOURCE=.\MTParser.h
# End Source File
# Begin Source File

SOURCE=.\MTParserCompiler.h
# End Source File
# Begin Source File

SOURCE=.\MTParserDefFuncs.h
# End Source File
# Begin Source File

SOURCE=.\MTParserDefOps.h
# End Source File
# Begin Source File

SOURCE=.\MTParserExcepStrEng.h
# End Source File
# Begin Source File

SOURCE=.\MTParserException.h
# End Source File
# Begin Source File

SOURCE=.\MTParserLocalizer.h
# End Source File
# Begin Source File

SOURCE=.\MTParserMacroFunc.h
# End Source File
# Begin Source File

SOURCE=.\MTParserPrivate.h
# End Source File
# Begin Source File

SOURCE=.\MTParserPublic.h
# End Source File
# Begin Source File

SOURCE=.\MTParserRegistrar.h
# End Source File
# Begin Source File

SOURCE=.\MTParserTestCases.h
# End Source File
# Begin Source File

SOURCE=.\MTSearchFile.h
# End Source File
# Begin Source File

SOURCE=.\MTTools.h
# End Source File
# Begin Source File

SOURCE=.\MTUnicodeANSIDefs.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Mainpage.txt
# End Source File
# End Target
# End Project
