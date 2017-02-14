# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Chat97Server - Win32 Debug
!MESSAGE 構成が指定されていません。ﾃﾞﾌｫﾙﾄの Chat97Server - Win32 Debug を設定します。
!ENDIF 

!IF "$(CFG)" != "Chat97Server - Win32 Release" && "$(CFG)" !=\
 "Chat97Server - Win32 Debug"
!MESSAGE 指定された ﾋﾞﾙﾄﾞ ﾓｰﾄﾞ "$(CFG)" は正しくありません。
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛ 'CFG' を定義することによって
!MESSAGE NMAKE 実行時にﾋﾞﾙﾄﾞ ﾓｰﾄﾞを指定できます。例えば:
!MESSAGE 
!MESSAGE NMAKE /f "Chat97Server.mak" CFG="Chat97Server - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "Chat97Server - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "Chat97Server - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE 
!ERROR 無効な構成が指定されています。
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "Chat97Server - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Chat97Server - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\Chat97Server.exe"

CLEAN : 
	-@erase "$(INTDIR)\Chat97Server.obj"
	-@erase "$(INTDIR)\Chat97Server.pch"
	-@erase "$(INTDIR)\Chat97Server.res"
	-@erase "$(INTDIR)\Chat97ServerDlg.obj"
	-@erase "$(INTDIR)\Chatsock.obj"
	-@erase "$(INTDIR)\Sendmes.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Chat97Server.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/Chat97Server.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
RSC_PROJ=/l 0x411 /fo"$(INTDIR)/Chat97Server.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Chat97Server.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Chat97Server.pdb" /machine:I386\
 /out:"$(OUTDIR)/Chat97Server.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Chat97Server.obj" \
	"$(INTDIR)\Chat97Server.res" \
	"$(INTDIR)\Chat97ServerDlg.obj" \
	"$(INTDIR)\Chatsock.obj" \
	"$(INTDIR)\Sendmes.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Chat97Server.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Chat97Server - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\Chat97Server.exe"

CLEAN : 
	-@erase "$(INTDIR)\Chat97Server.obj"
	-@erase "$(INTDIR)\Chat97Server.pch"
	-@erase "$(INTDIR)\Chat97Server.res"
	-@erase "$(INTDIR)\Chat97ServerDlg.obj"
	-@erase "$(INTDIR)\Chatsock.obj"
	-@erase "$(INTDIR)\Sendmes.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Chat97Server.exe"
	-@erase "$(OUTDIR)\Chat97Server.ilk"
	-@erase "$(OUTDIR)\Chat97Server.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/Chat97Server.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
RSC_PROJ=/l 0x411 /fo"$(INTDIR)/Chat97Server.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Chat97Server.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Chat97Server.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Chat97Server.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Chat97Server.obj" \
	"$(INTDIR)\Chat97Server.res" \
	"$(INTDIR)\Chat97ServerDlg.obj" \
	"$(INTDIR)\Chatsock.obj" \
	"$(INTDIR)\Sendmes.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Chat97Server.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "Chat97Server - Win32 Release"
# Name "Chat97Server - Win32 Debug"

!IF  "$(CFG)" == "Chat97Server - Win32 Release"

!ELSEIF  "$(CFG)" == "Chat97Server - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Chat97Server.cpp
DEP_CPP_CHAT9=\
	".\Chat97Server.h"\
	".\Chat97ServerDlg.h"\
	".\chatsock.h"\
	".\sendmes.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Chat97Server.obj" : $(SOURCE) $(DEP_CPP_CHAT9) "$(INTDIR)"\
 "$(INTDIR)\Chat97Server.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Chat97ServerDlg.cpp
DEP_CPP_CHAT97=\
	".\Chat97Server.h"\
	".\Chat97ServerDlg.h"\
	".\chatsock.h"\
	".\sendmes.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Chat97ServerDlg.obj" : $(SOURCE) $(DEP_CPP_CHAT97) "$(INTDIR)"\
 "$(INTDIR)\Chat97Server.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Chat97Server - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS"\
 /Fp"$(INTDIR)/Chat97Server.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Chat97Server.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Chat97Server - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/Chat97Server.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Chat97Server.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Chat97Server.rc
DEP_RSC_CHAT97S=\
	".\res\Chat97Server.rc2"\
	".\res\ico00001.ico"\
	".\res\icon1.ico"\
	".\res\icon10.ico"\
	".\res\icon2.ico"\
	".\res\icon3.ico"\
	".\res\icon4.ico"\
	".\res\icon5.ico"\
	".\res\icon6.ico"\
	".\res\icon7.ico"\
	".\res\icon8.ico"\
	".\res\icon9.ico"\
	

"$(INTDIR)\Chat97Server.res" : $(SOURCE) $(DEP_RSC_CHAT97S) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Chatsock.cpp
DEP_CPP_CHATS=\
	".\Chat97Server.h"\
	".\Chat97ServerDlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Chatsock.obj" : $(SOURCE) $(DEP_CPP_CHATS) "$(INTDIR)"\
 "$(INTDIR)\Chat97Server.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Sendmes.cpp
DEP_CPP_SENDM=\
	".\Chat97Server.h"\
	".\chatsock.h"\
	".\sendmes.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Sendmes.obj" : $(SOURCE) $(DEP_CPP_SENDM) "$(INTDIR)"\
 "$(INTDIR)\Chat97Server.pch"


# End Source File
# End Target
# End Project
################################################################################
