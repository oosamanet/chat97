# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=MapClient - Win32 Debug
!MESSAGE 構成が指定されていません。ﾃﾞﾌｫﾙﾄの MapClient - Win32 Debug を設定します。
!ENDIF 

!IF "$(CFG)" != "MapClient - Win32 Release" && "$(CFG)" !=\
 "MapClient - Win32 Debug"
!MESSAGE 指定された ﾋﾞﾙﾄﾞ ﾓｰﾄﾞ "$(CFG)" は正しくありません。
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛ 'CFG' を定義することによって
!MESSAGE NMAKE 実行時にﾋﾞﾙﾄﾞ ﾓｰﾄﾞを指定できます。例えば:
!MESSAGE 
!MESSAGE NMAKE /f "MapClient.mak" CFG="MapClient - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "MapClient - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "MapClient - Win32 Debug" ("Win32 (x86) Application" 用)
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
# PROP Target_Last_Scanned "MapClient - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "MapClient - Win32 Release"

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

ALL : "$(OUTDIR)\chat97.exe"

CLEAN : 
	-@erase "$(INTDIR)\Chatsock.obj"
	-@erase "$(INTDIR)\ConnectDlg.obj"
	-@erase "$(INTDIR)\HelpDlg.obj"
	-@erase "$(INTDIR)\MapClient.obj"
	-@erase "$(INTDIR)\MapClient.pch"
	-@erase "$(INTDIR)\MapClient.res"
	-@erase "$(INTDIR)\Member.obj"
	-@erase "$(INTDIR)\panel.obj"
	-@erase "$(INTDIR)\RoomName.obj"
	-@erase "$(INTDIR)\Send.obj"
	-@erase "$(INTDIR)\SendMes.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\user.obj"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(OUTDIR)\chat97.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/MapClient.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
RSC_PROJ=/l 0x411 /fo"$(INTDIR)/MapClient.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MapClient.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib /nologo /subsystem:windows /machine:I386 /out:"Release/chat97.exe"
LINK32_FLAGS=winmm.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/chat97.pdb" /machine:I386 /out:"$(OUTDIR)/chat97.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Chatsock.obj" \
	"$(INTDIR)\ConnectDlg.obj" \
	"$(INTDIR)\HelpDlg.obj" \
	"$(INTDIR)\MapClient.obj" \
	"$(INTDIR)\MapClient.res" \
	"$(INTDIR)\Member.obj" \
	"$(INTDIR)\panel.obj" \
	"$(INTDIR)\RoomName.obj" \
	"$(INTDIR)\Send.obj" \
	"$(INTDIR)\SendMes.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\user.obj" \
	"$(INTDIR)\util.obj"

"$(OUTDIR)\chat97.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MapClient - Win32 Debug"

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

ALL : "$(OUTDIR)\chat97.exe"

CLEAN : 
	-@erase "$(INTDIR)\Chatsock.obj"
	-@erase "$(INTDIR)\ConnectDlg.obj"
	-@erase "$(INTDIR)\HelpDlg.obj"
	-@erase "$(INTDIR)\MapClient.obj"
	-@erase "$(INTDIR)\MapClient.pch"
	-@erase "$(INTDIR)\MapClient.res"
	-@erase "$(INTDIR)\Member.obj"
	-@erase "$(INTDIR)\panel.obj"
	-@erase "$(INTDIR)\RoomName.obj"
	-@erase "$(INTDIR)\Send.obj"
	-@erase "$(INTDIR)\SendMes.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\user.obj"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\chat97.exe"
	-@erase "$(OUTDIR)\chat97.ilk"
	-@erase "$(OUTDIR)\chat97.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/MapClient.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
RSC_PROJ=/l 0x411 /fo"$(INTDIR)/MapClient.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MapClient.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/chat97.exe"
LINK32_FLAGS=winmm.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/chat97.pdb" /debug /machine:I386 /out:"$(OUTDIR)/chat97.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Chatsock.obj" \
	"$(INTDIR)\ConnectDlg.obj" \
	"$(INTDIR)\HelpDlg.obj" \
	"$(INTDIR)\MapClient.obj" \
	"$(INTDIR)\MapClient.res" \
	"$(INTDIR)\Member.obj" \
	"$(INTDIR)\panel.obj" \
	"$(INTDIR)\RoomName.obj" \
	"$(INTDIR)\Send.obj" \
	"$(INTDIR)\SendMes.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\user.obj" \
	"$(INTDIR)\util.obj"

"$(OUTDIR)\chat97.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "MapClient - Win32 Release"
# Name "MapClient - Win32 Debug"

!IF  "$(CFG)" == "MapClient - Win32 Release"

!ELSEIF  "$(CFG)" == "MapClient - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\MapClient.cpp
DEP_CPP_MAPCL=\
	".\Chatsock.h"\
	".\MapClient.h"\
	".\Member.h"\
	".\Panel.h"\
	".\Send.h"\
	".\StdAfx.h"\
	".\user.h"\
	".\util.h"\
	

"$(INTDIR)\MapClient.obj" : $(SOURCE) $(DEP_CPP_MAPCL) "$(INTDIR)"\
 "$(INTDIR)\MapClient.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "MapClient - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS"\
 /Fp"$(INTDIR)/MapClient.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MapClient.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "MapClient - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/MapClient.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MapClient.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MapClient.rc
DEP_RSC_MAPCLI=\
	".\res\icon3.ico"\
	".\res\login.wav"\
	".\res\mailchat.ico"\
	".\res\MapClient.ico"\
	".\res\MapClient.rc2"\
	

"$(INTDIR)\MapClient.res" : $(SOURCE) $(DEP_RSC_MAPCLI) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\panel.cpp
DEP_CPP_PANEL=\
	".\Chatsock.h"\
	".\ConnectDlg.h"\
	".\HelpDlg.h"\
	".\MapClient.h"\
	".\Member.h"\
	".\Panel.h"\
	".\RoomName.h"\
	".\Send.h"\
	".\SendMes.h"\
	".\StdAfx.h"\
	".\user.h"\
	".\util.h"\
	

"$(INTDIR)\panel.obj" : $(SOURCE) $(DEP_CPP_PANEL) "$(INTDIR)"\
 "$(INTDIR)\MapClient.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Chatsock.cpp
DEP_CPP_CHATS=\
	".\Chatsock.h"\
	".\MapClient.h"\
	".\Member.h"\
	".\Panel.h"\
	".\Send.h"\
	".\StdAfx.h"\
	".\user.h"\
	".\util.h"\
	

"$(INTDIR)\Chatsock.obj" : $(SOURCE) $(DEP_CPP_CHATS) "$(INTDIR)"\
 "$(INTDIR)\MapClient.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ConnectDlg.cpp
DEP_CPP_CONNE=\
	".\Chatsock.h"\
	".\ConnectDlg.h"\
	".\MapClient.h"\
	".\Member.h"\
	".\Send.h"\
	".\StdAfx.h"\
	".\user.h"\
	".\util.h"\
	

"$(INTDIR)\ConnectDlg.obj" : $(SOURCE) $(DEP_CPP_CONNE) "$(INTDIR)"\
 "$(INTDIR)\MapClient.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Send.cpp
DEP_CPP_SEND_=\
	".\Chatsock.h"\
	".\MapClient.h"\
	".\Member.h"\
	".\Panel.h"\
	".\Send.h"\
	".\StdAfx.h"\
	".\user.h"\
	".\util.h"\
	

"$(INTDIR)\Send.obj" : $(SOURCE) $(DEP_CPP_SEND_) "$(INTDIR)"\
 "$(INTDIR)\MapClient.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\util.cpp
DEP_CPP_UTIL_=\
	".\Chatsock.h"\
	".\MapClient.h"\
	".\Member.h"\
	".\Send.h"\
	".\StdAfx.h"\
	".\user.h"\
	".\util.h"\
	

"$(INTDIR)\util.obj" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)"\
 "$(INTDIR)\MapClient.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\user.cpp
DEP_CPP_USER_=\
	".\Chatsock.h"\
	".\MapClient.h"\
	".\Member.h"\
	".\Send.h"\
	".\StdAfx.h"\
	".\user.h"\
	".\util.h"\
	

"$(INTDIR)\user.obj" : $(SOURCE) $(DEP_CPP_USER_) "$(INTDIR)"\
 "$(INTDIR)\MapClient.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SendMes.cpp
DEP_CPP_SENDM=\
	".\Chatsock.h"\
	".\MapClient.h"\
	".\Member.h"\
	".\Send.h"\
	".\SendMes.h"\
	".\StdAfx.h"\
	".\user.h"\
	".\util.h"\
	

"$(INTDIR)\SendMes.obj" : $(SOURCE) $(DEP_CPP_SENDM) "$(INTDIR)"\
 "$(INTDIR)\MapClient.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\RoomName.cpp
DEP_CPP_ROOMN=\
	".\Chatsock.h"\
	".\MapClient.h"\
	".\Member.h"\
	".\RoomName.h"\
	".\Send.h"\
	".\StdAfx.h"\
	".\user.h"\
	".\util.h"\
	

"$(INTDIR)\RoomName.obj" : $(SOURCE) $(DEP_CPP_ROOMN) "$(INTDIR)"\
 "$(INTDIR)\MapClient.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\HelpDlg.cpp
DEP_CPP_HELPD=\
	".\Chatsock.h"\
	".\HelpDlg.h"\
	".\MapClient.h"\
	".\Member.h"\
	".\Send.h"\
	".\StdAfx.h"\
	".\user.h"\
	".\util.h"\
	

"$(INTDIR)\HelpDlg.obj" : $(SOURCE) $(DEP_CPP_HELPD) "$(INTDIR)"\
 "$(INTDIR)\MapClient.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Member.cpp
DEP_CPP_MEMBE=\
	".\Chatsock.h"\
	".\MapClient.h"\
	".\Member.h"\
	".\Panel.h"\
	".\Send.h"\
	".\StdAfx.h"\
	".\user.h"\
	".\util.h"\
	

"$(INTDIR)\Member.obj" : $(SOURCE) $(DEP_CPP_MEMBE) "$(INTDIR)"\
 "$(INTDIR)\MapClient.pch"


# End Source File
# End Target
# End Project
################################################################################
