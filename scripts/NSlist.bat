@if "%1%"=="" goto local
%GERTICO%\bin\nslist.exe -ORBInitRef NameService=corbaloc:iiop:%1:3000/NameService
@goto done
:local
%GERTICO%\bin\nslist.exe -ORBInitRef NameService=corbaloc:iiop:localhost:3000/NameService
:done
