@if "%1%"=="" goto local
%GERTICO%\bin\Naming_Service.exe -ORBEndpoint iiop://%1:3000  -d
@goto done
:local
%GERTICO%\bin\Naming_Service.exe -ORBEndpoint iiop://localhost:3000  -d
:done
