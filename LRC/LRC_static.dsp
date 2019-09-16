# Microsoft Developer Studio Project File - Name="LRC_static" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=LRC_static - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "LRC_static.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "LRC_static.mak" CFG="LRC_static - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "LRC_static - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "LRC_static - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LRC_static - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "LRC_static - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD CPP /nologo /MTd /w /W0 /Gm /GX /ZI /Od /I ".." /I "../Util" /I "../idl" /I "../OMT_XML" /I "../Gal" /I "../Ownership" /I "../EventMarket" /I "../GeRtiTime" /I "../MOM" /I "HLASpec/RTI-1.3NGv3-include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_WIN32_" /D "BUILDING_RTI" /D "RTI_USES_STD_FSTREAM" /D "BUILDING_FEDTIME" /FR /YX /FD /GZ  /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "LRC_static - Win32 Release"
# Name "LRC_static - Win32 Debug"
# Begin Group "HLAspec"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\HLASpec\AnSynPtHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\AnSynPtHandler.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\CoFedRestorationReqJob.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\CoFedRestorationReqJob.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\CoSynPtHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\CoSynPtHandler.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\DebugHLASpec.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\DiscoverHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\DiscoverHandler.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\EventHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\EventHandler.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\FederationNotRestoredJob.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\FederationNotRestoredJob.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\FederationNotSavedJob.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\FederationNotSavedJob.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\FederationRestoreBegunJob.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\FederationRestoreBegunJob.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\FederationRestoredJob.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\FederationRestoredJob.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\FederationSavedJob.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\FederationSavedJob.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\FedSyncHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\FedSyncHandler.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\fedtimeDouble.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\HlaOwnershipClientMapper.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\HlaOwnershipClientMapper.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\InitFederateRestoreJob.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\InitFederateRestoreJob.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\InitFederateSaveJob.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\InitFederateSaveJob.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\InterPubOnHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\InterPubOnHandler.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\Mapper.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\Mapper.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\ObjPubOnHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\ObjPubOnHandler.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\ProvideHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\ProvideHandler.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\ReceiverI.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\ReceiverI.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\RemoveHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\RemoveHandler.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\RemoveWithTimeHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\RemoveWithTimeHandler.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\RTI_AHSet.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\RTI_AHSet.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\RTI_AHSetFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\RTI_AHVPSet.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\RTI_AHVPSet.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\RTI_AHVPSetFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\RTI_Exception.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\RTI_Exceptions.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\RTI_HSet.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\RTI_HSet.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\RTI_HSetFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\RTI_HVPSet.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\RTI_HVPSet.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\RTI_PHVPSet.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\RTI_PHVPSet.h
# End Source File
# Begin Source File

SOURCE=.\HLASpec\RTI_PHVPSetFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\RTIambServices.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\StartRegHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\HLASpec\StartRegHandler.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\config.h
# End Source File
# Begin Source File

SOURCE=.\Debug.h
# End Source File
# Begin Source File

SOURCE=.\EventMarket.cpp
# End Source File
# Begin Source File

SOURCE=.\EventMarket.h
# End Source File
# Begin Source File

SOURCE=.\GeRtiAmbassadorI.cpp
# End Source File
# Begin Source File

SOURCE=.\GeRtiAmbassadorI.h
# End Source File
# Begin Source File

SOURCE=.\GeRtiEventMarketI.cpp
# End Source File
# Begin Source File

SOURCE=.\GeRtiEventMarketI.h
# End Source File
# Begin Source File

SOURCE=.\LrcListener.cpp
# End Source File
# Begin Source File

SOURCE=.\LrcListener.h
# End Source File
# Begin Source File

SOURCE=.\LrcOwnershipClient.cpp
# End Source File
# Begin Source File

SOURCE=.\LrcOwnershipClient.h
# End Source File
# Begin Source File

SOURCE=.\LrcOwnershipClientMapper.h
# End Source File
# Begin Source File

SOURCE=.\Receiver.h
# End Source File
# Begin Source File

SOURCE=.\Sender.cpp
# End Source File
# Begin Source File

SOURCE=.\Sender.h
# End Source File
# Begin Source File

SOURCE=.\TimeClient.cpp
# End Source File
# Begin Source File

SOURCE=.\TimeClient.h
# End Source File
# End Target
# End Project
