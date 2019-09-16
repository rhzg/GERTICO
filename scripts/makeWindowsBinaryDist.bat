set DEST=gertico_0_33

mkdir %DEST%
IF ERRORLEVEL 1 goto mderror
xcopy %GERTICO%\GERTICOconf.xml %DEST%
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\Readme.txt %DEST%
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\gertico_manual.txt %DEST%
IF ERRORLEVEL 1 goto cperror

mkdir %DEST%\Gal
IF ERRORLEVEL 1 goto mderror
xcopy %GERTICO%\Gal\StdAfx.h %DEST%\Gal
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\Gal\adm.h %DEST%\Gal
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\Gal\appender.h %DEST%\Gal
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\Gal\event.h %DEST%\Gal
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\Gal\format.h %DEST%\Gal
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\Gal\global.h %DEST%\Gal
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\Gal\in.h %DEST%\Gal
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\Gal\layout.h %DEST%\Gal
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\Gal\logger.h %DEST%\Gal
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\Gal\lst.h %DEST%\Gal
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\Gal\out.h %DEST%\Gal
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\Gal\param.h %DEST%\Gal
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\Gal\repository.h %DEST%\Gal
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\Gal\repository_l.h %DEST%\Gal
IF ERRORLEVEL 1 goto cperror

mkdir %DEST%\GalRes
IF ERRORLEVEL 1 goto mderror
xcopy %GERTICO%\GalRes %DEST%\GalRes /e
IF ERRORLEVEL 1 goto xcperror

mkdir %DEST%\bin
IF ERRORLEVEL 1 goto mderror
rem xcopy %GERTICO%\bin\MomManager.exe %DEST%\bin
xcopy %GERTICO%\bin\gerti.exe %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\bin\gertiD.exe %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\FedTime\Release\fedtime.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\FedTime\DeBug\fedtimeD.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\FedTime\Release\fedtime.lib %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\FedTime\DeBug\fedtimeD.lib %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\Gal\Release\Gal.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\Gal\DeBug\GalD.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\Gal\Release\Gal.lib %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\Gal\DeBug\GalD.lib %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\LRC\Release\LRC.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\LRC\DeBug\LRCd.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\LRC\Release\LRC.lib %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\LRC\DeBug\LRCd.lib %DEST%\bin
IF ERRORLEVEL 1 goto cperror

xcopy %ACE_ROOT%\TAO\orbsvcs\Naming_Service\Naming_Service.exe %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\TAO\utils\nslist\nslist.exe %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\bin\ace.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\bin\aced.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\ace\ace.lib %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\ace\aced.lib %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\bin\TAO.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\bin\TAOd.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\bin\TAO_CosNaming.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\bin\TAO_CosNamingd.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\bin\TAO_IORInterceptor.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\bin\TAO_IORInterceptord.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\bin\TAO_IORTable.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\bin\TAO_IORTabled.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\bin\TAO_Messaging.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\bin\TAO_Messagingd.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\bin\TAO_ObjRefTemplate.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\bin\TAO_ObjRefTemplated.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\bin\TAO_PortableServer.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\bin\TAO_PortableServerd.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\bin\TAO_Svc_Utils.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\bin\TAO_Svc_Utilsd.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\bin\TAO_Valuetype.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\bin\TAO_Valuetyped.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %XERCESCROOT%\Build\Win32\VC6\Release\xerces-c_2_6.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %XERCESCROOT%\Build\Win32\VC6\Debug\xerces-c_2_6D.dll %DEST%\bin
IF ERRORLEVEL 1 goto cperror

xcopy %GERTICO%\OMT_XML\Samples\HelloWorld.fed %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\OMT_XML\Samples\Schwarm.fed %DEST%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\OMT_XML\Samples\HLA.dtd %DEST%\bin
IF ERRORLEVEL 1 goto cperror

mkdir %DEST%\doc
IF ERRORLEVEL 1 goto mderror
xcopy %GERTICO%\doc\GERTICO.doc %DEST%\doc
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\doc\MessageService.doc %DEST%\doc
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\doc\NameService.doc %DEST%\doc
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\doc\OMT_XML.doc %DEST%\doc
IF ERRORLEVEL 1 goto cperror

mkdir %DEST%\include
IF ERRORLEVEL 1 goto mderror
xcopy %GERTICO%\include %DEST%\include /e
IF ERRORLEVEL 1 goto xcperror

rem mkdir %DEST%\lib
rem IF ERRORLEVEL 1 goto mderror
rem xcopy %GERTICO%\lib %DEST%\lib /e
rem IF ERRORLEVEL 1 goto xcperror

mkdir %DEST%\scripts
IF ERRORLEVEL 1 goto mderror
xcopy %GERTICO%\scripts\startNS.bat %DEST%\scripts
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\scripts\NSlist.bat %DEST%\scripts
IF ERRORLEVEL 1 goto cperror

mkdir %DEST%\samples
IF ERRORLEVEL 1 goto mderror
xcopy %GERTICO%\samples\Samples.dsw %DEST%\samples

mkdir %DEST%\samples\BossFish
IF ERRORLEVEL 1 goto mderror
mkdir %DEST%\samples\Common
IF ERRORLEVEL 1 goto mderror
mkdir %DEST%\samples\SchwarmMonitorConsole
IF ERRORLEVEL 1 goto mderror
mkdir %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto mderror
mkdir %DEST%\samples\SchwarmMonitor\res
IF ERRORLEVEL 1 goto mderror
mkdir %DEST%\samples\SchwarmRandom
IF ERRORLEVEL 1 goto mderror
mkdir %DEST%\samples\helloWorld
IF ERRORLEVEL 1 goto mderror
mkdir %DEST%\samples\FedTimeInteger
IF ERRORLEVEL 1 goto mderror
mkdir %DEST%\samples\FedTimeDouble
IF ERRORLEVEL 1 goto mderror

xcopy %GERTICO%\samples\BossFish\BossFish.cpp %DEST%\samples\BossFish
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\BossFish\SchwarmAmbassador.cpp %DEST%\samples\BossFish
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\BossFish\SchwarmAmbassador.h %DEST%\samples\BossFish
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\BossFish\BossFish.dsp %DEST%\samples\BossFish
IF ERRORLEVEL 1 goto cperror

xcopy %GERTICO%\samples\Common\Federate.cpp %DEST%\samples\Common
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\Common\Federate.h %DEST%\samples\Common
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\Common\Fish.cpp %DEST%\samples\Common
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\Common\Fish.h %DEST%\samples\Common
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\Common\Common.dsp %DEST%\samples\Common
IF ERRORLEVEL 1 goto cperror

xcopy %GERTICO%\samples\SchwarmMonitorConsole\SchwarmMonitorConsole.dsp %DEST%\samples\SchwarmMonitorConsole
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitorConsole\SchwarmAmbassador.cpp %DEST%\samples\SchwarmMonitorConsole
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitorConsole\SchwarmAmbassador.h %DEST%\samples\SchwarmMonitorConsole
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitorConsole\SchwarmMonitor.cpp %DEST%\samples\SchwarmMonitorConsole
IF ERRORLEVEL 1 goto cperror

xcopy %GERTICO%\samples\SchwarmRandom\SchwarmRandom.dsp %DEST%\samples\SchwarmRandom
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmRandom\Schwarm.cpp %DEST%\samples\SchwarmRandom
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmRandom\SchwarmAmbassador.cpp %DEST%\samples\SchwarmRandom
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmRandom\SchwarmAmbassador.h %DEST%\samples\SchwarmRandom
IF ERRORLEVEL 1 goto cperror

xcopy %GERTICO%\samples\helloWorld\Country.cpp %DEST%\samples\helloWorld
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\helloWorld\Country.hh %DEST%\samples\helloWorld
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\helloWorld\HelloWorld.cpp %DEST%\samples\helloWorld
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\helloWorld\HwFederateAmbassador.cpp %DEST%\samples\helloWorld
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\helloWorld\HwFederateAmbassador.hh %DEST%\samples\helloWorld
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\helloWorld\helloWorld.dsp %DEST%\samples\helloWorld
IF ERRORLEVEL 1 goto cperror

xcopy %GERTICO%\samples\FedTimeInteger\IntegerTime.h %DEST%\samples\FedTimeInteger
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\FedTimeInteger\IntegerTime.cpp %DEST%\samples\FedTimeInteger
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\FedTimeInteger\FedTimeInteger.dsp %DEST%\samples\FedTimeInteger
IF ERRORLEVEL 1 goto cperror

xcopy %GERTICO%\samples\FedTimeDouble\FedTimeDouble.h %DEST%\samples\FedTimeDouble
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\FedTimeDouble\FedTimeDouble.cpp %DEST%\samples\FedTimeDouble
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\FedTimeDouble\FedTimeDouble.dsp %DEST%\samples\FedTimeDouble
IF ERRORLEVEL 1 goto cperror

xcopy %GERTICO%\samples\SchwarmMonitor\scribble.dsp %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\SchwarmAmbassador.cpp %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\stdafx.h %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\stdafx.cpp %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\scribvw.h %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\scribvw.cpp %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\scribdoc.h %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\scribdoc.cpp %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\scribble.reg %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\scribble.rc %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\scribble.mak %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\scribble.h %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\scribble.dsw %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\scribble.cpp %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\scribble.clw %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\resource.h %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\resource.fd %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\readme.txt %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\pendlg.h %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\pendlg.cpp %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\mainfrm.h %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\mainfrm.cpp %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\childfrm.h %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\childfrm.cpp %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\Scribble.aps %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\SchwarmAmbassador.h %DEST%\samples\SchwarmMonitor
IF ERRORLEVEL 1 goto cperror
xcopy %GERTICO%\samples\SchwarmMonitor\res %DEST%\samples\SchwarmMonitor\res
IF ERRORLEVEL 1 goto xcperror
goto end
:cperror
echo xcopy did not work
pause
goto end
:xcperror
echo xcopy did not work
pause
goto end
:mderror
echo mkdir did not work
pause
goto end
:end
