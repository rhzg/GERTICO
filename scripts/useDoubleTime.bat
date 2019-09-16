
IF EXIST %GERTICO%\samples\FedTimeDouble\Release\fedtime.dll (
copy %GERTICO%\samples\FedTimeDouble\Release\fedtime.dll %GERTICO%\bin\fedtime.dll ) ELSE (
goto nofile
)
IF EXIST %GERTICO%\samples\FedTimeDouble\Release\fedtime.lib (
copy %GERTICO%\samples\FedTimeDouble\Release\fedtime.lib %GERTICO%\bin\fedtime.lib ) ELSE (
goto nofile
)
IF EXIST %GERTICO%\samples\FedTimeDouble\Debug\fedtimeD.dll (
copy %GERTICO%\samples\FedTimeDouble\Debug\fedtimeD.dll %GERTICO%\bin\fedtimeD.dll ) ELSE (
goto nofile
)
IF EXIST %GERTICO%\samples\FedTimeDouble\Debug\fedtimeD.lib (
copy %GERTICO%\samples\FedTimeDouble\Debug\fedtimeD.lib %GERTICO%\bin\fedtimeD.lib ) ELSE (
goto nofile
)
copy %GERTICO%\samples\FedTimeDouble\FedTimeDouble.h %GERTICO%\include\fedtime.hh
goto end
:nofile
echo file does not exist
pause
goto end
:end
