
IF EXIST %GERTICO%\samples\FedTimeInteger\Release\fedtime.dll (
copy %GERTICO%\samples\FedTimeInteger\Release\fedtime.dll %GERTICO%\bin\fedtime.dll ) ELSE (
goto nofile
)
IF EXIST %GERTICO%\samples\FedTimeInteger\Release\fedtime.lib (
copy %GERTICO%\samples\FedTimeInteger\Release\fedtime.lib %GERTICO%\bin\fedtime.lib ) ELSE (
goto nofile
)
IF EXIST %GERTICO%\samples\FedTimeInteger\Debug\fedtimeD.dll (
copy %GERTICO%\samples\FedTimeInteger\Debug\fedtimeD.dll %GERTICO%\bin\fedtimeD.dll ) ELSE (
goto nofile
)
IF EXIST %GERTICO%\samples\FedTimeInteger\Debug\fedtimeD.lib (
copy %GERTICO%\samples\FedTimeInteger\Debug\fedtimeD.lib %GERTICO%\bin\fedtimeD.lib ) ELSE (
goto nofile
)
copy %GERTICO%\samples\FedTimeInteger\IntegerTime.h %GERTICO%\include\fedtime.hh
goto end
:nofile
echo file does not exist
pause
goto end
:end
