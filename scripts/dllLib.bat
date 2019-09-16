xcopy %ACE_ROOT%\lib\ACEd.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\ACEd.lib %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\ACE.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\ACE.lib %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_AnyTypeCoded.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_AnyTypeCoded.lib %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_AnyTypeCode.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_AnyTypeCode.lib %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_CodecFactoryd.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_CodecFactory.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_Codesetd.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_Codeset.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_CosNamingd.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_CosNamingd.lib %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_CosNaming.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_CosNaming.lib %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_CosNaming_Servd.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_CosNaming_Serv.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_CosNaming_Skeld.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_CosNaming_Skel.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAOd.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAOd.lib %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_ImR_Clientd.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_ImR_Client.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_IORInterceptord.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_IORInterceptor.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_IORTabled.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_IORTable.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO.lib %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_Messagingd.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_Messaging.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_ObjRefTemplated.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_ObjRefTemplate.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_PId.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_PI.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_PortableServerd.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_PortableServerd.lib %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_PortableServer.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_PortableServer.lib %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_Svc_Utilsd.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_Svc_Utils.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_Valuetyped.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %ACE_ROOT%\lib\TAO_Valuetype.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %XERCESCROOT%\Build\Win32\VC7.1\Debug\xerces-c_2_8D.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %XERCESCROOT%\Build\Win32\VC7.1\Release\xerces-c_2_8.dll %GERTICO%\bin
IF ERRORLEVEL 1 goto cperror
xcopy %XERCESCROOT%\Build\Win32\VC7.1\Debug\xerces-c_2D.lib
IF ERRORLEVEL 1 goto cperror
xcopy %XERCESCROOT%\Build\Win32\VC7.1\Release\xerces-c_2.lib
IF ERRORLEVEL 1 goto cperror
goto end
:cperror
echo xcopy did not work
pause
:end
