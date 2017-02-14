# Microsoft Developer Studio Project File - Name="MapClient" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MapClient - Win32 Release
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "mapclient.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "mapclient.mak" CFG="MapClient - Win32 Release"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "MapClient - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "MapClient - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/CHAT97", CAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MapClient - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib /nologo /subsystem:windows /machine:I386 /out:".\Release\chat97.exe"

!ELSEIF  "$(CFG)" == "MapClient - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386 /out:".\Debug\chat97.exe"

!ENDIF 

# Begin Target

# Name "MapClient - Win32 Release"
# Name "MapClient - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\addserver.cpp
# End Source File
# Begin Source File

SOURCE=.\bossstring.cpp
# End Source File
# Begin Source File

SOURCE=.\Chatsock.cpp
# End Source File
# Begin Source File

SOURCE=.\ConnectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\editserver.cpp
# End Source File
# Begin Source File

SOURCE=.\HelpDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MapClient.cpp
# End Source File
# Begin Source File

SOURCE=.\MapClient.rc
# End Source File
# Begin Source File

SOURCE=.\Member.cpp
# End Source File
# Begin Source File

SOURCE=.\panel.cpp
# End Source File
# Begin Source File

SOURCE=.\RichEditCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=.\RoomName.cpp
# End Source File
# Begin Source File

SOURCE=.\Send.cpp
# End Source File
# Begin Source File

SOURCE=.\SendMes.cpp
# End Source File
# Begin Source File

SOURCE=.\sethandle.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\user.cpp
# End Source File
# Begin Source File

SOURCE=.\util.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\addserver.h
# End Source File
# Begin Source File

SOURCE=.\bossstring.h
# End Source File
# Begin Source File

SOURCE=.\Chatsock.h
# End Source File
# Begin Source File

SOURCE=.\ConnectDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditServer.h
# End Source File
# Begin Source File

SOURCE=.\HelpDlg.h
# End Source File
# Begin Source File

SOURCE=.\MapClient.h
# End Source File
# Begin Source File

SOURCE=.\Member.h
# End Source File
# Begin Source File

SOURCE=.\Panel.h
# End Source File
# Begin Source File

SOURCE=.\RichEditCtrlEx.h
# End Source File
# Begin Source File

SOURCE=.\RoomName.h
# End Source File
# Begin Source File

SOURCE=.\Send.h
# End Source File
# Begin Source File

SOURCE=.\SendMes.h
# End Source File
# Begin Source File

SOURCE=.\sethandle.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\user.h
# End Source File
# Begin Source File

SOURCE=.\util.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\__97.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chat97.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\RES\linkhand.cur
# End Source File
# Begin Source File

SOURCE=.\res\listicon.bmp
# End Source File
# Begin Source File

SOURCE=.\res\login.wav
# End Source File
# Begin Source File

SOURCE=.\res\mailchat.ico
# End Source File
# Begin Source File

SOURCE=.\res\MapClient.ico
# End Source File
# Begin Source File

SOURCE=.\res\MapClient.rc2
# End Source File
# End Group
# End Target
# End Project
