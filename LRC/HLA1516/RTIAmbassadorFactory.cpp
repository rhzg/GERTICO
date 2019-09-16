/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**
** MODULE
** FederateAmbassador - implementation for RTI 1.3 NG V3 CORBA
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: RTIAmbassadorFactory.cpp,v $
Revision 1.1  2007/09/05 15:43:41  mul
Changes for ieee1516.

Revision 1.1  2007/06/26 08:25:28  mul
New files for ieee1516.

 
**
*******************************************************************************/

#include "RTI/RTIambassadorFactory.h"
#include "LRC/HLA1516/RTIambServices.h"

#ifdef _WIN32
BOOL WINAPI DllMain( HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{ 
   WORD wVersionRequested;
   WSADATA wsaData;
   int err;

   wVersionRequested = MAKEWORD( 2, 2 );
   switch (ul_reason_for_call)
   {
   case DLL_PROCESS_ATTACH:
      err = WSAStartup( wVersionRequested, &wsaData );
      if ( err != 0 ) 
      {
         std::string message;
         message = "Initialization of Windows sockets failed: ";
         switch (err)
         {
            case WSASYSNOTREADY:
               message += "The underlying network subsystem is not ready for network communication.";
               break;
            case WSAVERNOTSUPPORTED:
               message += "The Windows Sockets version 2.2";
               message += "is not provided by this particular Windows Sockets implementation.";
               break;
            case WSAEINPROGRESS:
               message += "A blocking Windows Sockets 1.1 operation is in progress.";
               break;
            case WSAEPROCLIM:
               message += "A limit on the number of tasks supported by the Windows Sockets implementation has been reached.";
               break;
            case WSAEFAULT:
               message += "The lpWSAData parameter is not a valid pointer.";
               break;
            default: 
               message += "Unknown error.";
               break;
         }
         /* Tell the user that we could not find a usable */
         /* WinSock DLL.                                  */
         MessageBox(
            NULL, 
            message.c_str(),
            "DIS Socket Fatal Error",
            MB_SETFOREGROUND | MB_ICONERROR |  MB_OK );
         return false;
      }
     break;
   case DLL_THREAD_ATTACH:
      break;
   case DLL_THREAD_DETACH:
      break;
   case DLL_PROCESS_DETACH:
          WSACleanup ();
      break;
   }
   return true;
}
#endif

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
RTI::RTIambassadorFactory::RTIambassadorFactory(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
RTI::RTIambassadorFactory::~RTIambassadorFactory(void)
throw()
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::auto_ptr<RTI::RTIambassador> RTI::RTIambassadorFactory::createRTIambassador(std::vector<std::wstring> & args)
  throw (BadInitializationParameter,
         RTIinternalError)
{
  std::auto_ptr<RTI::RTIambassador> ret(new GERTICO::RTIambServices());

  return ret;
}
