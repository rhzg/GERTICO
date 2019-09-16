/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**                RTI Parameter Passing Memory Conventions
**
** C1  In parameter by value.
** C2  Out parameter by pointer value.
** C3  Function return by value.
** C4  In parameter by const pointer value.  Caller provides memory.
**     Caller may free memory or overwrite it upon completion of
**     the call.  Callee must copy during the call anything it
**     wishes to save beyond completion of the call.  Parameter
**     type must define const accessor methods.
** C5  Out parameter by pointer value.  Caller provides reference to object.
**     Callee constructs an instance on the heap (new) and returns.
**     The caller destroys the instance (delete) at its leisure.
** C6  Function return by pointer value.  Callee constructs an instance on
**     the heap (new) and returns a reference.  The caller destroys the
**     instance (delete) at its leisure.
********************************************************************************
**

$Author: mul $
$Name $
$Log: RTIambServices.cpp,v $
Revision 1.76  2010/05/17 07:55:42  mul
Add logical time interval.

Revision 1.75  2010/04/13 12:28:37  mul
Add delete receiver.

Revision 1.74  2009/08/17 10:09:09  mul
Minor changes.

Revision 1.73  2009/05/27 11:32:49  mul
Fix problems found in level four tests.

Revision 1.72  2009/05/07 12:21:28  mul
Minor changes.

Revision 1.71  2008/10/17 13:46:45  mul
Changed logic for order and transport types.

Revision 1.70  2007/09/05 15:46:45  mul
Changes for ieee1516.

Revision 1.69  2007/06/25 15:11:36  mul
Changes for ieee1516.

Revision 1.68  2007/06/08 12:05:34  mul
Changes for ieee1516.

Revision 1.67  2007/05/15 13:18:54  mul
Changes for combined 1.3 and 1516 logic.

Revision 1.66  2007/05/09 13:10:50  mul
Changes to make sender generic.

Revision 1.65  2007/05/03 14:43:40  mul
Add wchar parameter to exception constructor.

Revision 1.64  2007/03/29 09:09:37  mul
Add repeated attempts for corba minor error == 0.

Revision 1.63  2007/03/12 13:09:03  mul
Changed string to wstring.

Revision 1.62  2007/03/06 09:29:12  mul
Changes for ieee conversion.

Revision 1.61  2007/02/28 07:57:37  mul
Add namespace.

Revision 1.60  2006/12/18 10:10:58  mul
Test parameter values.

Revision 1.59  2006/12/15 08:46:04  mul
Check boolean flag values.

Revision 1.58  2006/11/28 15:39:37  mul
Minor error fix.

Revision 1.57  2006/10/23 14:43:34  mul
Fix region storage problem.

Revision 1.56  2006/10/18 13:38:46  mul
Fix memory leaks.

Revision 1.55  2006/09/28 07:11:18  mul
Minor changes.

Revision 1.54  2006/09/26 13:25:39  mul
Minor changes.

Revision 1.53  2006/09/21 14:48:18  mul
Fix sprintf formats.

Revision 1.52  2006/09/18 14:56:52  mul
Fix some program structure problems.

Revision 1.51  2006/09/13 09:14:21  mul
New gal.

Revision 1.50  2006/09/12 11:30:24  mul
Changes for phase 5 testcases.

Revision 1.49  2006/09/06 14:59:08  mul
Minor change.

Revision 1.48  2006/09/04 15:05:46  mul
Add hla logging.

Revision 1.46  2006/08/01 11:28:59  mul
Changes for mom.

Revision 1.45  2006/04/19 14:58:55  mul
Minor changes.

Revision 1.44  2005/12/20 09:11:15  mul
Suppress exceptions in tick.

Revision 1.43  2005/11/22 12:36:51  mul
Minor change.

Revision 1.42  2005/10/05 11:50:51  mul
Fixed exception handling.

Revision 1.41  2005/10/05 10:12:00  mul
Use defines rather than constants..

Revision 1.40  2005/09/27 12:01:10  mul
Remove catch for unknown location exception.

Revision 1.39  2005/09/19 08:12:39  mul
Changes to handle unknown location exceptions.

Revision 1.38  2005/09/08 11:54:33  mul
Print error message only after several attempts.

Revision 1.37  2005/09/07 12:34:30  mul
Change name scoping.

Revision 1.36  2005/08/03 13:02:35  mul
Add sleep.

Revision 1.35  2005/07/14 12:40:40  mul
Add concurrency handling in creat and destroy federation.

Revision 1.34  2005/05/03 15:07:09  mul
Add name scoping.

Revision 1.33  2005/02/07 10:33:26  mul
Changes due to test cases.

Revision 1.32  2004/12/14 13:42:26  mul
Add query min next event time logic.

Revision 1.31  2004/09/24 08:32:53  mul
Change name scoping.

Revision 1.30  2004/05/27 12:26:38  mul
Fix problems found in conformance test.

Revision 1.29  2004/04/19 15:06:03  mul
Exception handling for fed-file errors.

Revision 1.28  2004/03/17 14:21:03  mul
Add remaining services.

Revision 1.27  2003/09/23 14:33:00  mul
Extensions for DDM.

Revision 1.26  2003/08/07 12:03:55  mul
Fix synchronization point registration.

Revision 1.25  2003/07/28 12:43:38  mul
Fix exception handling.

Revision 1.24  2003/07/16 08:05:43  mul
Changes for RTI::FedTime.

Revision 1.23  2003/06/10 13:30:07  hzg
include

Revision 1.22  2003/05/28 06:36:44  mul
Fix Saved and Restored logic.

Revision 1.21  2003/05/21 11:59:25  hzg
Debug.h removed

Revision 1.20  2003/05/21 08:23:45  hzg
catch internal exception

Revision 1.19  2003/05/14 08:02:27  hzg
using of RTI private Ref

Revision 1.18  2003/05/06 12:57:46  hzg
tested for WindowsXP and SuSE7.2

Revision 1.17  2003/04/29 06:26:14  hzg
Portierung auf Windows

Revision 1.16  2003/04/10 13:00:08  mul
Sender as global pointer to avoid automatic CORBA calls in constructor.

Revision 1.15  2003/02/18 09:55:09  mul
Fix unsubscribe logic.

Revision 1.14  2003/02/10 14:59:04  ba
FedAm interface logged by Gal.

Revision 1.13  2003/02/10 11:26:21  hzg
Gal converter

Revision 1.12  2003/01/10 14:08:14  ba
Fehler in Parser behoben

Revision 1.11  2002/12/19 13:32:46  hzg
*** empty log message ***

Revision 1.10  2002/11/19 16:01:44  hzg
Static data model used in OMT_XML

Revision 1.9  2002/11/06 15:06:31  hzg
Ownership included

Revision 1.8  2002/10/21 13:09:48  mul
Changes in logic for delete CORBA objects.

Revision 1.7  2002/09/19 08:19:04  hzg
CORBA System Exception mapped to RTI Internal Error

Revision 1.6  2002/09/18 14:50:17  mul
Add/complete usage of exceptions.

Revision 1.5  2002/09/10 12:52:40  mul
Fix problems with file not found. Changes for linking fedtimeDouble.cpp.

Revision 1.4  2002/09/10 12:39:10  hzg
Fehlerbehandlung für joinFederation aus Sender.cpp in RTIamb verschoben

Revision 1.3  2002/07/23 14:50:35  hzg
Modifications and corrections for RTBenchmark
fine tuning of Makefile logic

Revision 1.2  2002/07/16 08:57:24  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen


**
*******************************************************************************/

//File RTIambServices.hh
#include <orbsvcs/CosNamingC.h>
#include "include/RTI_1.3/RTI.hh"
#include "Util/GeRtiTypes.h"
#include "Util/Mapper.h"
#include "LRC/Sender.h"
#include "LRC/HLASpec/RTI_RegionI.h"
#include "LRC/HLASpec/ReceiverI.h"
#include "Mapper13.h"

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

#define GalHLADebug 1

/********************************* Gal begin *********************************/   // inserted by Gal converter

// Version: 1.0   // inserted by Gal converter
// Date/Time: Fri Jan 10 11:09:07 2003   // inserted by Gal converter
//
// insert Gal file .init here
/********************************* Gal begin *********************************/   // inserted by Gal converter
// inserted by Gal converter
// Version: 1.1   // inserted by Gal converter
// Date/Time: Wed Jan 22 15:41:52 2003   // inserted by Gal converter
// inserted by Gal converter

// Redesign by GAL creator in 2006

#ifdef GalHLADebug   // inserted by Gal converter

#include "Gal/StdAfx.h"   // inserted by Gal converter
#include "Gal/repository_l.h"   // inserted by Gal converter
#include "Gal/event.h"   // inserted by Gal converter
//#include <strstream.h>   // inserted by Gal converter
   // inserted by Gal converter
//static char GalBuffer[256];   // inserted by Gal converter
//static class ostrstream GalOs(GalBuffer,256);   // inserted by Gal converter
   // inserted by Gal converter

#include "ut.h"

static class Repository_l *rpGal=(Repository::getSingleInstance())->getRepository_l("HLAServices.res","HLAServices");
   // inserted by Gal converter

static class Event *cAA_d0=rpGal->getRefEvent("cAA_d0");   // inserted by Gal converter
static class Event *cFE_s0=rpGal->getRefEvent("cFE_s0");   // inserted by Gal converter
static class Event *cFE_ta=rpGal->getRefEvent("cFE_ta");   // inserted by Gal converter
static class Event *cFE_ts=rpGal->getRefEvent("cFE_ts");   // inserted by Gal converter
static class Event *dFE_s0=rpGal->getRefEvent("dFE_s0");   // inserted by Gal converter
static class Event *dFE_ta=rpGal->getRefEvent("dFE_ta");   // inserted by Gal converter
static class Event *dFE_ts=rpGal->getRefEvent("dFE_ts");   // inserted by Gal converter
static class Event *jFE_s0=rpGal->getRefEvent("jFE_s0");   // inserted by Gal converter
static class Event *jFE_ta=rpGal->getRefEvent("jFE_ta");   // inserted by Gal converter
static class Event *jFE_ts=rpGal->getRefEvent("jFE_ts");   // inserted by Gal converter
static class Event *rFE_s0=rpGal->getRefEvent("rFE_s0");   // inserted by Gal converter
static class Event *rFE_ta=rpGal->getRefEvent("rFE_ta");   // inserted by Gal converter
static class Event *rFE_ts=rpGal->getRefEvent("rFE_ts");   // inserted by Gal converter
static class Event *rFSP_s0=rpGal->getRefEvent("rFSP_s0");   // inserted by Gal converter
static class Event *rFSP_s1=rpGal->getRefEvent("rFSP_s1");   // inserted by Gal converter
static class Event *rFSP_ta=rpGal->getRefEvent("rFSP_ta");   // inserted by Gal converter
static class Event *rFSP_ts=rpGal->getRefEvent("rFSP_ts");   // inserted by Gal converter
static class Event *sPA_s0=rpGal->getRefEvent("sPA_s0");   // inserted by Gal converter
static class Event *sPA_ta=rpGal->getRefEvent("sPA_ta");   // inserted by Gal converter
static class Event *sPA_ts=rpGal->getRefEvent("sPA_ts");   // inserted by Gal converter
static class Event *rFS_s0=rpGal->getRefEvent("rFS_s0");   // inserted by Gal converter
static class Event *rFS_s1=rpGal->getRefEvent("rFS_s1");   // inserted by Gal converter
static class Event *rFS_ta=rpGal->getRefEvent("rFS_ta");   // inserted by Gal converter
static class Event *rFS_ts=rpGal->getRefEvent("rFS_ts");   // inserted by Gal converter
static class Event *fSB_s0=rpGal->getRefEvent("fSB_s0");   // inserted by Gal converter
static class Event *fSB_ta=rpGal->getRefEvent("fSB_ta");   // inserted by Gal converter
static class Event *fSB_ts=rpGal->getRefEvent("fSB_ts");   // inserted by Gal converter
static class Event *fSC_s0=rpGal->getRefEvent("fSC_s0");   // inserted by Gal converter
static class Event *fSC_ta=rpGal->getRefEvent("fSC_ta");   // inserted by Gal converter
static class Event *fSC_ts=rpGal->getRefEvent("fSC_ts");   // inserted by Gal converter
static class Event *fSNC_s0=rpGal->getRefEvent("fSNC_s0");   // inserted by Gal converter
static class Event *fSNC_ta=rpGal->getRefEvent("fSNC_ta");   // inserted by Gal converter
static class Event *fSNC_ts=rpGal->getRefEvent("fSNC_ts");   // inserted by Gal converter
static class Event *rFR_s0=rpGal->getRefEvent("rFR_s0");   // inserted by Gal converter
static class Event *rFR_ta=rpGal->getRefEvent("rFR_ta");   // inserted by Gal converter
static class Event *rFR_ts=rpGal->getRefEvent("rFR_ts");   // inserted by Gal converter
static class Event *fRC_s0=rpGal->getRefEvent("fRC_s0");   // inserted by Gal converter
static class Event *fRC_ta=rpGal->getRefEvent("fRC_ta");   // inserted by Gal converter
static class Event *fRC_ts=rpGal->getRefEvent("fRC_ts");   // inserted by Gal converter
static class Event *fRNC_s0=rpGal->getRefEvent("fRNC_s0");   // inserted by Gal converter
static class Event *fRNC_ta=rpGal->getRefEvent("fRNC_ta");   // inserted by Gal converter
static class Event *fRNC_ts=rpGal->getRefEvent("fRNC_ts");   // inserted by Gal converter
static class Event *pOC_s0=rpGal->getRefEvent("pOC_s0");   // inserted by Gal converter
static class Event *pOC_ta=rpGal->getRefEvent("pOC_ta");   // inserted by Gal converter
static class Event *pOC_ts=rpGal->getRefEvent("pOC_ts");   // inserted by Gal converter
static class Event *uOC_s0=rpGal->getRefEvent("uOC_s0");   // inserted by Gal converter
static class Event *uOC_ta=rpGal->getRefEvent("uOC_ta");   // inserted by Gal converter
static class Event *uOC_ts=rpGal->getRefEvent("uOC_ts");   // inserted by Gal converter
static class Event *pIC_s0=rpGal->getRefEvent("pIC_s0");   // inserted by Gal converter
static class Event *pIC_ta=rpGal->getRefEvent("pIC_ta");   // inserted by Gal converter
static class Event *pIC_ts=rpGal->getRefEvent("pIC_ts");   // inserted by Gal converter
static class Event *sOCA_s0=rpGal->getRefEvent("sOCA_s0");   // inserted by Gal converter
static class Event *sOCA_ta=rpGal->getRefEvent("sOCA_ta");   // inserted by Gal converter
static class Event *sOCA_ts=rpGal->getRefEvent("sOCA_ts");   // inserted by Gal converter
static class Event *usOC_s0=rpGal->getRefEvent("usOC_s0");   // inserted by Gal converter
static class Event *usOC_ta=rpGal->getRefEvent("usOC_ta");   // inserted by Gal converter
static class Event *usOC_ts=rpGal->getRefEvent("usOC_ts");   // inserted by Gal converter
static class Event *sIC_s0=rpGal->getRefEvent("sIC_s0");   // inserted by Gal converter
static class Event *sIC_ts=rpGal->getRefEvent("sIC_ts");   // inserted by Gal converter
static class Event *sIC_ta=rpGal->getRefEvent("sIC_ta");   // inserted by Gal converter
static class Event *uIC_s0=rpGal->getRefEvent("uIC_s0");   // inserted by Gal converter
static class Event *uIC_ta=rpGal->getRefEvent("uIC_ta");   // inserted by Gal converter
static class Event *uIC_ts=rpGal->getRefEvent("uIC_ts");   // inserted by Gal converter
static class Event *usIC_s0=rpGal->getRefEvent("usIC_s0");   // inserted by Gal converter
static class Event *usIC_ta=rpGal->getRefEvent("usIC_ta");   // inserted by Gal converter
static class Event *usIC_ts=rpGal->getRefEvent("usIC_ts");   // inserted by Gal converter
static class Event *rOI_s0=rpGal->getRefEvent("rOI_s0");   // inserted by Gal converter
static class Event *rOI_s1=rpGal->getRefEvent("rOI_s1");   // inserted by Gal converter
static class Event *rOI_ta=rpGal->getRefEvent("rOI_ta");   // inserted by Gal converter
static class Event *rOI_ts=rpGal->getRefEvent("rOI_ts");   // inserted by Gal converter
static class Event *uAV_s0=rpGal->getRefEvent("uAV_s0");   // inserted by Gal converter
static class Event *uAV_s1=rpGal->getRefEvent("uAV_s1");   // inserted by Gal converter
static class Event *uAV_ta=rpGal->getRefEvent("uAV_ta");   // inserted by Gal converter
static class Event *uAV_ts=rpGal->getRefEvent("uAV_ts");   // inserted by Gal converter
static class Event *sI_s0=rpGal->getRefEvent("sI_s0");   // inserted by Gal converter
static class Event *sI_s1=rpGal->getRefEvent("sI_s1");   // inserted by Gal converter
static class Event *sI_ta=rpGal->getRefEvent("sI_ta");   // inserted by Gal converter
static class Event *sI_ts=rpGal->getRefEvent("sI_ts");   // inserted by Gal converter
static class Event *dOI_s0=rpGal->getRefEvent("dOI_s0");   // inserted by Gal converter
static class Event *dOI_s1=rpGal->getRefEvent("dOI_s1");   // inserted by Gal converter
static class Event *dOI_ta=rpGal->getRefEvent("dOI_ta");   // inserted by Gal converter
static class Event *dOI_ts=rpGal->getRefEvent("dOI_ts");   // inserted by Gal converter
static class Event *lDOI_s0=rpGal->getRefEvent("lDOI_s0");   // inserted by Gal converter
static class Event *lDOI_ta=rpGal->getRefEvent("lDOI_ta");   // inserted by Gal converter
static class Event *lDOI_ts=rpGal->getRefEvent("lDOI_ts");   // inserted by Gal converter
static class Event *cATT_s0=rpGal->getRefEvent("cATT_s0");   // inserted by Gal converter
static class Event *cATT_ta=rpGal->getRefEvent("cATT_ta");   // inserted by Gal converter
static class Event *cATT_ts=rpGal->getRefEvent("cATT_ts");   // inserted by Gal converter
static class Event *cITT_s0=rpGal->getRefEvent("cITT_s0");   // inserted by Gal converter
static class Event *cITT_ta=rpGal->getRefEvent("cITT_ta");   // inserted by Gal converter
static class Event *cITT_ts=rpGal->getRefEvent("cITT_ts");   // inserted by Gal converter
static class Event *rOAVU_s0=rpGal->getRefEvent("rOAVU_s0");   // inserted by Gal converter
static class Event *rOAVU_ta=rpGal->getRefEvent("rOAVU_ta");   // inserted by Gal converter
static class Event *rOAVU_ts=rpGal->getRefEvent("rOAVU_ts");   // inserted by Gal converter
static class Event *rCAVU_s0=rpGal->getRefEvent("rCAVU_s0");   // inserted by Gal converter
static class Event *rCAVU_ta=rpGal->getRefEvent("rCAVU_ta");   // inserted by Gal converter
static class Event *rCAVU_ts=rpGal->getRefEvent("rCAVU_ts");   // inserted by Gal converter
static class Event *uAOD_s0=rpGal->getRefEvent("uAOD_s0");   // inserted by Gal converter
static class Event *uAOD_ta=rpGal->getRefEvent("uAOD_ta");   // inserted by Gal converter
static class Event *uAOD_ts=rpGal->getRefEvent("uAOD_ts");   // inserted by Gal converter
static class Event *nAOD_s0=rpGal->getRefEvent("nAOD_s0");   // inserted by Gal converter
static class Event *nAOD_ta=rpGal->getRefEvent("nAOD_ta");   // inserted by Gal converter
static class Event *nAOD_ts=rpGal->getRefEvent("nAOD_ts");   // inserted by Gal converter
static class Event *aOA_s0=rpGal->getRefEvent("aOA_s0");   // inserted by Gal converter
static class Event *aOA_ta=rpGal->getRefEvent("aOA_ta");   // inserted by Gal converter
static class Event *aOA_ts=rpGal->getRefEvent("aOA_ts");   // inserted by Gal converter
static class Event *aOAIA_s0=rpGal->getRefEvent("aOAIA_s0");   // inserted by Gal converter
static class Event *aOAIA_ta=rpGal->getRefEvent("aOAIA_ta");   // inserted by Gal converter
static class Event *aOAIA_ts=rpGal->getRefEvent("aOAIA_ts");   // inserted by Gal converter
static class Event *aORR_s0=rpGal->getRefEvent("aORR_s0");   // inserted by Gal converter
static class Event *aORR_ta=rpGal->getRefEvent("aORR_ta");   // inserted by Gal converter
static class Event *aORR_ts=rpGal->getRefEvent("aORR_ts");   // inserted by Gal converter
static class Event *cNAOD_s0=rpGal->getRefEvent("cNAOD_s0");   // inserted by Gal converter
static class Event *cNAOD_ta=rpGal->getRefEvent("cNAOD_ta");   // inserted by Gal converter
static class Event *cNAOD_ts=rpGal->getRefEvent("cNAOD_ts");   // inserted by Gal converter
static class Event *cAOA_s0=rpGal->getRefEvent("cAOA_s0");   // inserted by Gal converter
static class Event *cAOA_ta=rpGal->getRefEvent("cAOA_ta");   // inserted by Gal converter
static class Event *cAOA_ts=rpGal->getRefEvent("cAOA_ts");   // inserted by Gal converter
static class Event *qAO_s0=rpGal->getRefEvent("qAO_s0");   // inserted by Gal converter
static class Event *qAO_ta=rpGal->getRefEvent("qAO_ta");   // inserted by Gal converter
static class Event *qAO_ts=rpGal->getRefEvent("qAO_ts");   // inserted by Gal converter
static class Event *iAOBF_s0=rpGal->getRefEvent("iAOBF_s0");   // inserted by Gal converter
static class Event *iAOBF_ta=rpGal->getRefEvent("iAOBF_ta");   // inserted by Gal converter
static class Event *iAOBF_ts=rpGal->getRefEvent("iAOBF_ts");   // inserted by Gal converter
static class Event *eTR_s0=rpGal->getRefEvent("eTR_s0");   // inserted by Gal converter
static class Event *eTR_ta=rpGal->getRefEvent("eTR_ta");   // inserted by Gal converter
static class Event *eTR_ts=rpGal->getRefEvent("eTR_ts");   // inserted by Gal converter
static class Event *dTR_s0=rpGal->getRefEvent("dTR_s0");   // inserted by Gal converter
static class Event *dTR_ta=rpGal->getRefEvent("dTR_ta");   // inserted by Gal converter
static class Event *dTR_ts=rpGal->getRefEvent("dTR_ts");   // inserted by Gal converter
static class Event *eTC_s0=rpGal->getRefEvent("eTC_s0");   // inserted by Gal converter
static class Event *eTC_ts=rpGal->getRefEvent("eTC_ts");   // inserted by Gal converter
static class Event *eTC_ta=rpGal->getRefEvent("eTC_ta");   // inserted by Gal converter
static class Event *dTC_s0=rpGal->getRefEvent("dTC_s0");   // inserted by Gal converter
static class Event *dTC_ta=rpGal->getRefEvent("dTC_ta");   // inserted by Gal converter
static class Event *dTC_ts=rpGal->getRefEvent("dTC_ts");   // inserted by Gal converter
static class Event *tAR_s0=rpGal->getRefEvent("tAR_s0");   // inserted by Gal converter
static class Event *tAR_ta=rpGal->getRefEvent("tAR_ta");   // inserted by Gal converter
static class Event *tAR_ts=rpGal->getRefEvent("tAR_ts");   // inserted by Gal converter
static class Event *tARA_s0=rpGal->getRefEvent("tARA_s0");   // inserted by Gal converter
static class Event *tARA_ta=rpGal->getRefEvent("tARA_ta");   // inserted by Gal converter
static class Event *tARA_ts=rpGal->getRefEvent("tARA_ts");   // inserted by Gal converter
static class Event *nER_s0=rpGal->getRefEvent("nER_s0");   // inserted by Gal converter
static class Event *nER_ta=rpGal->getRefEvent("nER_ta");   // inserted by Gal converter
static class Event *nER_ts=rpGal->getRefEvent("nER_ts");   // inserted by Gal converter
static class Event *nERA_s0=rpGal->getRefEvent("nERA_s0");   // inserted by Gal converter
static class Event *nERA_ta=rpGal->getRefEvent("nERA_ta");   // inserted by Gal converter
static class Event *nERA_ts=rpGal->getRefEvent("nERA_ts");   // inserted by Gal converter
static class Event *fQR_s0=rpGal->getRefEvent("fQR_s0");   // inserted by Gal converter
static class Event *fQR_ta=rpGal->getRefEvent("fQR_ta");   // inserted by Gal converter
static class Event *fQR_ts=rpGal->getRefEvent("fQR_ts");   // inserted by Gal converter
static class Event *eAD_s0=rpGal->getRefEvent("eAD_s0");   // inserted by Gal converter
static class Event *eAD_ta=rpGal->getRefEvent("eAD_ta");   // inserted by Gal converter
static class Event *eAD_ts=rpGal->getRefEvent("eAD_ts");   // inserted by Gal converter
static class Event *dAD_s0=rpGal->getRefEvent("dAD_s0");   // inserted by Gal converter
static class Event *dAD_ta=rpGal->getRefEvent("dAD_ta");   // inserted by Gal converter
static class Event *dAD_ts=rpGal->getRefEvent("dAD_ts");   // inserted by Gal converter
static class Event *qLBTS_s0=rpGal->getRefEvent("qLBTS_s0");   // inserted by Gal converter
static class Event *qLBTS_ta=rpGal->getRefEvent("qLBTS_ta");   // inserted by Gal converter
static class Event *qLBTS_ts=rpGal->getRefEvent("qLBTS_ts");   // inserted by Gal converter
static class Event *qFT_s0=rpGal->getRefEvent("qFT_s0");   // inserted by Gal converter
static class Event *qFT_ta=rpGal->getRefEvent("qFT_ta");   // inserted by Gal converter
static class Event *qFT_ts=rpGal->getRefEvent("qFT_ts");   // inserted by Gal converter
static class Event *qMNET_s0=rpGal->getRefEvent("qMNET_s0");   // inserted by Gal converter
static class Event *qMNET_ta=rpGal->getRefEvent("qMNET_ta");   // inserted by Gal converter
static class Event *qMNET_ts=rpGal->getRefEvent("qMNET_ts");   // inserted by Gal converter
static class Event *mL_s0=rpGal->getRefEvent("mL_s0");   // inserted by Gal converter
static class Event *mL_ta=rpGal->getRefEvent("mL_ta");   // inserted by Gal converter
static class Event *mL_ts=rpGal->getRefEvent("mL_ts");   // inserted by Gal converter
static class Event *qL_s0=rpGal->getRefEvent("qL_s0");   // inserted by Gal converter
static class Event *qL_ta=rpGal->getRefEvent("qL_ta");   // inserted by Gal converter
static class Event *qL_ts=rpGal->getRefEvent("qL_ts");   // inserted by Gal converter
static class Event *r_s0=rpGal->getRefEvent("r_s0");   // inserted by Gal converter
static class Event *r_ta=rpGal->getRefEvent("r_ta");   // inserted by Gal converter
static class Event *r_ts=rpGal->getRefEvent("r_ts");   // inserted by Gal converter
static class Event *cAOT_s0=rpGal->getRefEvent("cAOT_s0");   // inserted by Gal converter
static class Event *cAOT_ta=rpGal->getRefEvent("cAOT_ta");   // inserted by Gal converter
static class Event *cAOT_ts=rpGal->getRefEvent("cAOT_ts");   // inserted by Gal converter
static class Event *cIOT_s0=rpGal->getRefEvent("cIOT_s0");   // inserted by Gal converter
static class Event *cIOT_ta=rpGal->getRefEvent("cIOT_ta");   // inserted by Gal converter
static class Event *cIOT_ts=rpGal->getRefEvent("cIOT_ts");   // inserted by Gal converter
static class Event *cR_s0=rpGal->getRefEvent("cR_s0");   // inserted by Gal converter
static class Event *cR_ta=rpGal->getRefEvent("cR_ta");   // inserted by Gal converter
static class Event *cR_ts=rpGal->getRefEvent("cR_ts");   // inserted by Gal converter
static class Event *nARM_s0=rpGal->getRefEvent("nARM_s0");   // inserted by Gal converter
static class Event *nARM_ta=rpGal->getRefEvent("nARM_ta");   // inserted by Gal converter
static class Event *nARM_ts=rpGal->getRefEvent("nARM_ts");   // inserted by Gal converter
static class Event *dR_s0=rpGal->getRefEvent("dR_s0");   // inserted by Gal converter
static class Event *dR_ta=rpGal->getRefEvent("dR_ta");   // inserted by Gal converter
static class Event *dR_ts=rpGal->getRefEvent("dR_ts");   // inserted by Gal converter
static class Event *rOIWR_s0=rpGal->getRefEvent("rOIWR_s0");   // inserted by Gal converter
static class Event *rOIWR_s1=rpGal->getRefEvent("rOIWR_s1");   // inserted by Gal converter
static class Event *rOIWR_ta=rpGal->getRefEvent("rOIWR_ta");   // inserted by Gal converter
static class Event *rOIWR_ts=rpGal->getRefEvent("rOIWR_ts");   // inserted by Gal converter
static class Event *aRFU_s0=rpGal->getRefEvent("aRFU_s0");   // inserted by Gal converter
static class Event *aRFU_ta=rpGal->getRefEvent("aRFU_ta");   // inserted by Gal converter
static class Event *aRFU_ts=rpGal->getRefEvent("aRFU_ts");   // inserted by Gal converter
static class Event *uRFU_s0=rpGal->getRefEvent("uRFU_s0");   // inserted by Gal converter
static class Event *uRFU_ta=rpGal->getRefEvent("uRFU_ta");   // inserted by Gal converter
static class Event *uRFU_ts=rpGal->getRefEvent("uRFU_ts");   // inserted by Gal converter
static class Event *sOCAWR_s0=rpGal->getRefEvent("sOCAWR_s0");   // inserted by Gal converter
static class Event *sOCAWR_ta=rpGal->getRefEvent("sOCAWR_ta");   // inserted by Gal converter
static class Event *sOCAWR_ts=rpGal->getRefEvent("sOCAWR_ts");   // inserted by Gal converter
static class Event *uOCWR_s0=rpGal->getRefEvent("uOCWR_s0");   // inserted by Gal converter
static class Event *uOCWR_ta=rpGal->getRefEvent("uOCWR_ta");   // inserted by Gal converter
static class Event *uOCWR_ts=rpGal->getRefEvent("uOCWR_ts");   // inserted by Gal converter
static class Event *sICWR_s0=rpGal->getRefEvent("sICWR_s0");   // inserted by Gal converter
static class Event *sICWR_ta=rpGal->getRefEvent("sICWR_ta");   // inserted by Gal converter
static class Event *sICWR_ts=rpGal->getRefEvent("sICWR_ts");   // inserted by Gal converter
static class Event *uICWR_s0=rpGal->getRefEvent("uICWR_s0");   // inserted by Gal converter
static class Event *uICWR_ta=rpGal->getRefEvent("uICWR_ta");   // inserted by Gal converter
static class Event *uICWR_ts=rpGal->getRefEvent("uICWR_ts");   // inserted by Gal converter
static class Event *sIWR_s0=rpGal->getRefEvent("sIWR_s0");   // inserted by Gal converter
static class Event *sIWR_s1=rpGal->getRefEvent("sIWR_s1");   // inserted by Gal converter
static class Event *sIWR_ta=rpGal->getRefEvent("sIWR_ta");   // inserted by Gal converter
static class Event *sIWR_ts=rpGal->getRefEvent("sIWR_ts");   // inserted by Gal converter
static class Event *rCAVUWR_s0=rpGal->getRefEvent("rCAVUWR_s0");   // inserted by Gal converter
static class Event *rCAVUWR_ta=rpGal->getRefEvent("rCAVUWR_ta");   // inserted by Gal converter
static class Event *rCAVUWR_ts=rpGal->getRefEvent("rCAVUWR_ts");   // inserted by Gal converter
static class Event *gOCH_s0=rpGal->getRefEvent("gOCH_s0");   // inserted by Gal converter
static class Event *gOCH_ta=rpGal->getRefEvent("gOCH_ta");   // inserted by Gal converter
static class Event *gOCH_ts=rpGal->getRefEvent("gOCH_ts");   // inserted by Gal converter
static class Event *gOCN_s0=rpGal->getRefEvent("gOCN_s0");   // inserted by Gal converter
static class Event *gOCN_ta=rpGal->getRefEvent("gOCN_ta");   // inserted by Gal converter
static class Event *gOCN_ts=rpGal->getRefEvent("gOCN_ts");   // inserted by Gal converter
static class Event *gAH_s0=rpGal->getRefEvent("gAH_s0");   // inserted by Gal converter
static class Event *gAH_ta=rpGal->getRefEvent("gAH_ta");   // inserted by Gal converter
static class Event *gAH_ts=rpGal->getRefEvent("gAH_ts");   // inserted by Gal converter
static class Event *gAN_s0=rpGal->getRefEvent("gAN_s0");   // inserted by Gal converter
static class Event *gAN_ta=rpGal->getRefEvent("gAN_ta");   // inserted by Gal converter
static class Event *gAN_ts=rpGal->getRefEvent("gAN_ts");   // inserted by Gal converter
static class Event *gICH_s0=rpGal->getRefEvent("gICH_s0");   // inserted by Gal converter
static class Event *gICH_ta=rpGal->getRefEvent("gICH_ta");   // inserted by Gal converter
static class Event *gICH_ts=rpGal->getRefEvent("gICH_ts");   // inserted by Gal converter
static class Event *gICN_s0=rpGal->getRefEvent("gICN_s0");   // inserted by Gal converter
static class Event *gICN_ta=rpGal->getRefEvent("gICN_ta");   // inserted by Gal converter
static class Event *gICN_ts=rpGal->getRefEvent("gICN_ts");   // inserted by Gal converter
static class Event *gPH_s0=rpGal->getRefEvent("gPH_s0");   // inserted by Gal converter
static class Event *gPH_ta=rpGal->getRefEvent("gPH_ta");   // inserted by Gal converter
static class Event *gPH_ts=rpGal->getRefEvent("gPH_ts");   // inserted by Gal converter
static class Event *gPN_s0=rpGal->getRefEvent("gPN_s0");   // inserted by Gal converter
static class Event *gPN_ta=rpGal->getRefEvent("gPN_ta");   // inserted by Gal converter
static class Event *gPN_ts=rpGal->getRefEvent("gPN_ts");   // inserted by Gal converter
static class Event *gOIH_s0=rpGal->getRefEvent("gOIH_s0");   // inserted by Gal converter
static class Event *gOIH_ta=rpGal->getRefEvent("gOIH_ta");   // inserted by Gal converter
static class Event *gOIH_ts=rpGal->getRefEvent("gOIH_ts");   // inserted by Gal converter
static class Event *gOIN_s0=rpGal->getRefEvent("gOIN_s0");   // inserted by Gal converter
static class Event *gOIN_ta=rpGal->getRefEvent("gOIN_ta");   // inserted by Gal converter
static class Event *gOIN_ts=rpGal->getRefEvent("gOIN_ts");   // inserted by Gal converter
static class Event *gRSH_s0=rpGal->getRefEvent("gRSH_s0");   // inserted by Gal converter
static class Event *gRSH_ta=rpGal->getRefEvent("gRSH_ta");   // inserted by Gal converter
static class Event *gRSH_ts=rpGal->getRefEvent("gRSH_ts");   // inserted by Gal converter
static class Event *gRSN_s0=rpGal->getRefEvent("gRSN_s0");   // inserted by Gal converter
static class Event *gRSN_ta=rpGal->getRefEvent("gRSN_ta");   // inserted by Gal converter
static class Event *gRSN_ts=rpGal->getRefEvent("gRSN_ts");   // inserted by Gal converter
static class Event *gDH_s0=rpGal->getRefEvent("gDH_s0");   // inserted by Gal converter
static class Event *gDH_ta=rpGal->getRefEvent("gDH_ta");   // inserted by Gal converter
static class Event *gDH_ts=rpGal->getRefEvent("gDH_ts");   // inserted by Gal converter
static class Event *gDN_s0=rpGal->getRefEvent("gDN_s0");   // inserted by Gal converter
static class Event *gDN_ta=rpGal->getRefEvent("gDN_ta");   // inserted by Gal converter
static class Event *gDN_ts=rpGal->getRefEvent("gDN_ts");   // inserted by Gal converter
static class Event *gARSH_s0=rpGal->getRefEvent("gARSH_s0");   // inserted by Gal converter
static class Event *gARSH_ta=rpGal->getRefEvent("gARSH_ta");   // inserted by Gal converter
static class Event *gARSH_ts=rpGal->getRefEvent("gARSH_ts");   // inserted by Gal converter
static class Event *gOC_s0=rpGal->getRefEvent("gOC_s0");   // inserted by Gal converter
static class Event *gOC_ta=rpGal->getRefEvent("gOC_ta");   // inserted by Gal converter
static class Event *gOC_ts=rpGal->getRefEvent("gOC_ts");   // inserted by Gal converter
static class Event *gIRSH_s0=rpGal->getRefEvent("gIRSH_s0");   // inserted by Gal converter
static class Event *gIRSH_ta=rpGal->getRefEvent("gIRSH_ta");   // inserted by Gal converter
static class Event *gIRSH_ts=rpGal->getRefEvent("gIRSH_ts");   // inserted by Gal converter
static class Event *gTH_s0=rpGal->getRefEvent("gTH_s0");   // inserted by Gal converter
static class Event *gTH_ta=rpGal->getRefEvent("gTH_ta");   // inserted by Gal converter
static class Event *gTH_ts=rpGal->getRefEvent("gTH_ts");   // inserted by Gal converter
static class Event *gTN_s0=rpGal->getRefEvent("gTN_s0");   // inserted by Gal converter
static class Event *gTN_ta=rpGal->getRefEvent("gTN_ta");   // inserted by Gal converter
static class Event *gTN_ts=rpGal->getRefEvent("gTN_ts");   // inserted by Gal converter
static class Event *gOH_s0=rpGal->getRefEvent("gOH_s0");   // inserted by Gal converter
static class Event *gOH_ta=rpGal->getRefEvent("gOH_ta");   // inserted by Gal converter
static class Event *gOH_ts=rpGal->getRefEvent("gOH_ts");   // inserted by Gal converter
static class Event *gON_s0=rpGal->getRefEvent("gON_s0");   // inserted by Gal converter
static class Event *gON_ta=rpGal->getRefEvent("gON_ta");   // inserted by Gal converter
static class Event *gON_ts=rpGal->getRefEvent("gON_ts");   // inserted by Gal converter
static class Event *eCRAS_s0=rpGal->getRefEvent("eCRAS_s0");   // inserted by Gal converter
static class Event *eCRAS_ta=rpGal->getRefEvent("eCRAS_ta");   // inserted by Gal converter
static class Event *eCRAS_ts=rpGal->getRefEvent("eCRAS_ts");   // inserted by Gal converter
static class Event *dCRAS_s0=rpGal->getRefEvent("dCRAS_s0");   // inserted by Gal converter
static class Event *dCRAS_ta=rpGal->getRefEvent("dCRAS_ta");   // inserted by Gal converter
static class Event *dCRAS_ts=rpGal->getRefEvent("dCRAS_ts");   // inserted by Gal converter
static class Event *eARAS_s0=rpGal->getRefEvent("eARAS_s0");   // inserted by Gal converter
static class Event *eARAS_ta=rpGal->getRefEvent("eARAS_ta");   // inserted by Gal converter
static class Event *eARAS_ts=rpGal->getRefEvent("eARAS_ts");   // inserted by Gal converter
static class Event *dARAS_s0=rpGal->getRefEvent("dARAS_s0");   // inserted by Gal converter
static class Event *dARAS_ta=rpGal->getRefEvent("dARAS_ta");   // inserted by Gal converter
static class Event *dARAS_ts=rpGal->getRefEvent("dARAS_ts");   // inserted by Gal converter
static class Event *eASAS_s0=rpGal->getRefEvent("eASAS_s0");   // inserted by Gal converter
static class Event *eASAS_ta=rpGal->getRefEvent("eASAS_ta");   // inserted by Gal converter
static class Event *eASAS_ts=rpGal->getRefEvent("eASAS_ts");   // inserted by Gal converter
static class Event *dASAS_s0=rpGal->getRefEvent("dASAS_s0");   // inserted by Gal converter
static class Event *dASAS_ta=rpGal->getRefEvent("dASAS_ta");   // inserted by Gal converter
static class Event *dASAS_ts=rpGal->getRefEvent("dASAS_ts");   // inserted by Gal converter
static class Event *eIRAS_s0=rpGal->getRefEvent("eIRAS_s0");   // inserted by Gal converter
static class Event *eIRAS_ta=rpGal->getRefEvent("eIRAS_ta");   // inserted by Gal converter
static class Event *eIRAS_ts=rpGal->getRefEvent("eIRAS_ts");   // inserted by Gal converter
static class Event *dIRAS_s0=rpGal->getRefEvent("dIRAS_s0");   // inserted by Gal converter
static class Event *dIRAS_ta=rpGal->getRefEvent("dIRAS_ta");   // inserted by Gal converter
static class Event *dIRAS_ts=rpGal->getRefEvent("dIRAS_ts");   // inserted by Gal converter
static class Event *gRT_e=rpGal->getRefEvent("gRT_e");   // inserted by Gal converter
static class Event *gR_e=rpGal->getRefEvent("gR_e");   // inserted by Gal converter
static class Event *gR_ts=rpGal->getRefEvent("gR_ts");   // inserted by Gal converter
static class Event *t_e=rpGal->getRefEvent("t_e");   // inserted by Gal converter
static class Event *RTI_e=rpGal->getRefEvent("RTI_e");   // inserted by Gal converter
static class Event *RTI_ts=rpGal->getRefEvent("RTI_ts");   // inserted by Gal converter
static class Event *RTId_e=rpGal->getRefEvent("RTId_e");   // inserted by Gal converter
static class Event *RTId_l=rpGal->getRefEvent("RTId_l");   // inserted by Gal converter

static char galMsg[MAX_TXT];

#endif

/*********************************** Gal end *********************************/   // inserted by Gal converter


////////////////////////////////////
// Federation Management Services //
////////////////////////////////////

GERTICO::GeRtiFedTimeFactory *myLogicalTimeFactory;
GERTICO::GeRtiLogicalTimeIntervalFactory *myLogicalTimeIntervalFactory;

#define maxRetries 10
#define waitTime 2000 // micro seconds

struct RTIambPrivateRefs
{
  GERTICO::ReceiverI *receiverI;
  NAMESPACE::Sender *sender;
  RegionIMap regionIMap;
};

void mapRegionI(GeRtiFactory::Extents &out, const RegionI &in);
void mapRegionI(RegionI &out, const GeRtiFactory::Extents &in);

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void clear(RegionIMap &regionIMap)
{
  RegionI *regionI;
  RegionIMap::iterator itRI;


  for (itRI = regionIMap.begin(); itRI != regionIMap.end(); itRI = regionIMap.begin())
  {
    regionI = itRI->second;
    regionIMap.erase(itRI);
    delete regionI;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
RTI::Region *getRegionI(const GeRtiFactory::GeRtiHandle &theToken, RegionIMap &regionIMap)
{
  RTI::Region *ret = NULL;
  RegionI *r = NULL;
  RegionIMap::iterator itRI;

  itRI = regionIMap.find(theToken);
  if (itRI != regionIMap.end())
  {
    r = itRI->second;
    ret = r;
    return ret;
  }

  throw GeRtiFactory::RegionNotKnown(L"");
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle getRegionTokenI(RTI::Region *theRegion)
{
  RegionI *r = (RegionI *) theRegion;
  return r->id;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void mapRegionI(GeRtiFactory::Extents &out, const RegionI &in)
{
  CORBA::ULong i;
  CORBA::ULong ilength;
  CORBA::ULong j;
  CORBA::ULong jlength;
  DimensionIMap::const_iterator itD;
  ExtentIVector::const_iterator itE;
  size_t size;

  ilength = in.getNumberOfExtents();
  out.length(ilength);
  for (itE = in.extentIs.begin(), i = 0; itE != in.extentIs.end(); itE++, i++)
  {
    size = itE->dimensionIs.size();
    GERTICO::Mapper::mapULongSizet(jlength, size);
    out[i].length(jlength);
    for (itD = itE->dimensionIs.begin(), j = 0; itD != itE->dimensionIs.end(); itD++, j++)
    {
      out[i][j].dimension = itD->first;
      out[i][j].lower = itD->second.lowerBound;
      out[i][j].upper = itD->second.upperBound;
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void mapRegionI(RegionI &out, const GeRtiFactory::Extents &in)
{
  CORBA::ULong i;
  CORBA::ULong ilength;
  CORBA::ULong j;
  CORBA::ULong jlength;

  ilength = in.length();
  for (i = 0; i < ilength; i++)
  {
    jlength = in[i].length();
    for (j = 0; j < jlength; j++)
    {
      out.setRangeLowerBound(i, in[i][j].dimension, in[i][j].lower);
      out.setRangeUpperBound(i, in[i][j].dimension, in[i][j].upper);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void loadRegion(GeRtiFactory::GeRtiHandle theSpace, GeRtiFactory::GeRtiHandle theRegion, const GeRtiFactory::Extents &theExtents, RegionIMap &regionIMap)
{
  RegionI *regionI = NULL;

  regionI = new RegionI(theSpace, theRegion, theExtents.length());
  mapRegionI(*regionI, theExtents);
  regionIMap[theRegion] = regionI;
}

// 4.2
void RTI::RTIambassador::createFederationExecution (
  const char *executionName, // supplied C4
  const char *FED)           // supplied C4
throw (
  FederationExecutionAlreadyExists,
  CouldNotOpenFED,
  ErrorReadingFED,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cFE_s0)
                            {
                              sprintf(galMsg,"name=%s,designator=%s",executionName,FED);
                              E1mEnd(cFE_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  std::string s;
  std::wstring execName;
  std::wstring fed;
  std::wstring ws;

  GERTICO::Mapper::mapWstringFromChar(execName, executionName);
  GERTICO::Mapper::mapWstringFromChar(fed, FED);
  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
    try
    {
      privateRefs->sender->createFederationExecution(execName, fed);
      break;
    }
    catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      if (maxExceptions < maxRetries)
      {
        ACE_OS::sleep(1);
        continue;
      }
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
      throw ConcurrentAccessAttempted(s.c_str());
    }
    catch (GeRtiFactory::FederationExecutionAlreadyExists &ex)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cFE_ta,"FederationExecutionAlreadyExists");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
      throw FederationExecutionAlreadyExists(s.c_str());
    }
    catch (GeRtiFactory::CouldNotOpenFED &ex)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cFE_ta,"CouldNotOpenFED");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
      throw CouldNotOpenFED(s.c_str());
    }
    catch (GeRtiFactory::ErrorReadingFED &ex)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cFE_ta,"ErrorReadingFED");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
      throw ErrorReadingFED(s.c_str());
    }
    catch (GeRtiFactory::RTIinternalError &ex)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cFE_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
      throw RTIinternalError(s.c_str());
    }
    catch (CORBA::SystemException &sysex)
    {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
      ACE_PRINT_EXCEPTION (sysex, "System Exception in createFederationExecution ");

                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cFE_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      throw RTIinternalError ("CORBA::SystemException");
    }
    catch (...)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cFE_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      throw RTIinternalError ("unknown Exception");
    }
  }
}

// 4.3
void RTI::RTIambassador::destroyFederationExecution (
  const char *executionName) // supplied C4
throw (
  FederatesCurrentlyJoined,
  FederationExecutionDoesNotExist,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(dFE_s0)
                            {
                              sprintf(galMsg,"name=%s",executionName);
                              E1mEnd(dFE_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  std::string s;
  std::wstring execName;
  std::wstring ws;

  GERTICO::Mapper::mapWstringFromChar(execName, executionName);
  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
    try
    {
      privateRefs->sender->destroyFederationExecution(execName);
      break;
    }
    catch (GeRtiFactory::FederatesCurrentlyJoined &ex)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dFE_ta,"FederatesCurrentlyJoined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
      throw FederatesCurrentlyJoined(s.c_str());
    }
    catch (GeRtiFactory::FederationExecutionDoesNotExist &ex)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dFE_ta,"FederationExecutionDoesNotExist");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
      throw FederationExecutionDoesNotExist(s.c_str());
    }
    catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
      throw ConcurrentAccessAttempted(s.c_str());
    }
    catch (GeRtiFactory::RTIinternalError &ex)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dFE_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
      throw RTIinternalError(s.c_str());
    }
    catch (CosNaming::NamingContext::NotFound &)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dFE_ta,"FederationExecutionDoesNotExist");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      throw FederationExecutionDoesNotExist(executionName);
    }
    catch (CORBA::SystemException &sysex)
    {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dFE_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      throw FederationExecutionDoesNotExist ("CORBA::SystemException");
    }
    catch (...)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dFE_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      throw RTIinternalError ("unknown Exception");
    }
  }
}

// 4.4
RTI::FederateHandle                                               // returned C3
RTI::RTIambassador::joinFederationExecution (
  const char                   *yourName,                    // supplied C4
  const char                   *executionName,               // supplied C4
        FederateAmbassadorPtr   federateAmbassadorReference) // supplied C1
throw (
  FederateAlreadyExecutionMember,
  FederationExecutionDoesNotExist,
  CouldNotOpenFED,
  ErrorReadingFED,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(jFE_s0)
                            {
                              sprintf(galMsg,"type=%s,name=%s",yourName,executionName);
                              E1mEnd(jFE_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  std::string s;
  std::wstring yName;
  std::wstring execName;
  std::wstring ws;
  RTI::FederateHandle ret;

  myLogicalTimeFactory = new GERTICO::GeRtiFedTimeFactory();
  myLogicalTimeIntervalFactory = new GERTICO::GeRtiLogicalTimeIntervalFactory();
  privateRefs->receiverI->initiate(federateAmbassadorReference);
  GERTICO::Mapper::mapWstringFromChar(yName, yourName);
  GERTICO::Mapper::mapWstringFromChar(execName, executionName);
  try
  {
    ret = privateRefs->sender->joinFederationExecution(yName, execName, *myLogicalTimeFactory, *myLogicalTimeIntervalFactory);
  }
  catch (GeRtiFactory::FederateAlreadyExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(jFE_ta,"FederateAlreadyExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateAlreadyExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::FederationExecutionDoesNotExist &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(jFE_ta,"FederationExecutionDoesNotExist");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederationExecutionDoesNotExist(s.c_str());
  }
  catch (CosNaming::NamingContext::NotFound &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(jFE_ta,"FederationExecutionDoesNotExist");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw FederationExecutionDoesNotExist("CosNaming::NamingContext::NotFound");
  }
  catch (GeRtiFactory::CouldNotOpenFED &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(jFE_ta,"CouldNotOpenFED");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw CouldNotOpenFED(s.c_str());
  }
  catch (GeRtiFactory::ErrorReadingFED &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(jFE_ta,"ErrorReadingFED");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ErrorReadingFED(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(jFE_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(jFE_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (CosNaming::NamingContext::AlreadyBound &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(jFE_ts,"RTIinternalError. CosNaming::NamingContext::AlreadyBound");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CosNaming::NamingContext::AlreadyBound");
  }
  catch (CosNaming::NamingContext::CannotProceed &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(jFE_ts,"RTIinternalError. CosNaming::NamingContext::CannotProceed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CosNaming::NamingContext::CannotProceed");
  }
  catch (CosNaming::NamingContext::InvalidName &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(jFE_ta,"FederationExecutionDoesNotExist");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw FederationExecutionDoesNotExist ("CosNaming::NamingContext::InvalidName");
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(jFE_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(jFE_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw FederationExecutionDoesNotExist ("SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(jFE_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(jFE_s0)
                            {
                              sprintf(galMsg,"ret=%lu",ret);
                              E1mEnd(jFE_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 4.5
void RTI::RTIambassador::resignFederationExecution (
  ResignAction theAction) // supplied C1
throw (
  FederateOwnsAttributes,
  FederateNotExecutionMember,
  InvalidResignAction,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rFE_s0)
                            {
                              sprintf(galMsg,"action=%s",GERTICO::ut::convert(theAction));
                              E1mEnd(rFE_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::ResignAction ra = GeRtiFactory::noAction;
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  switch (theAction)
  {
    case RELEASE_ATTRIBUTES:
    {
      ra = GeRtiFactory::unconditionallyDivestAttributes;
      break;
    }
    case DELETE_OBJECTS:
    {
      ra = GeRtiFactory::deleteObjects;
      break;
    }
    case DELETE_OBJECTS_AND_RELEASE_ATTRIBUTES:
    {
      ra = GeRtiFactory::deleteObjectsThenDivest;
      break;
    }
    case NO_ACTION:
    {
      ra = GeRtiFactory::noAction;
      break;
    }
    default:
    {
      throw InvalidResignAction("unknownAction");
    }
  }

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->resignFederationExecution (ra);
      break;
  }
  catch (GeRtiFactory::FederateOwnsAttributes &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFE_ta,"FederateOwnsAttributes");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateOwnsAttributes(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFE_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::InvalidResignAction &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFE_ta,"InvalidResignAction");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidResignAction(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFE_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in resignFederationExecution ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFE_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFE_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 4.6
void RTI::RTIambassador::registerFederationSynchronizationPoint (
  const char *label,  // supplied C4
  const char *theTag) // supplied C4
throw (
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rFSP_s0)
                            {
                              sprintf(galMsg,"label=%s,tag=%s",label,theTag);
                              E1mEnd(rFSP_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::UserSuppliedTag tag;
  std::string s;
  std::wstring l;
  std::wstring ws;

  GERTICO::Mapper::mapWstringFromChar(l, label);
  GERTICO::Mapper::mapUserSuppliedTag(tag, theTag);
  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->registerFederationSynchronizationPoint(l, tag);
      break;
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFSP_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFSP_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFSP_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFSP_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in registerFederationSynchronizationPoint ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFSP_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFSP_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

void RTI::RTIambassador::registerFederationSynchronizationPoint (
  const char                *label,    // supplied C4
  const char                *theTag,   // supplied C4
  const FederateHandleSet&   syncSet)  // supplied C4
throw (
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rFSP_s1)
                            {
                              sprintf(galMsg,"label=%s,tag=%s",label,theTag);
                              E1mEnd(rFSP_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::UserSuppliedTag tag;
  GeRtiFactory::Handles designators;
  std::string s;
  std::wstring l;
  std::wstring ws;

  GERTICO::Mapper::mapWstringFromChar(l, label);
  GERTICO::Mapper::mapUserSuppliedTag(tag, theTag);
  GERTICO::Mapper13::mapFederateHandleSet(designators, syncSet);
  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->registerFederationSynchronizationPoint(l, tag, designators);
      break;
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFSP_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFSP_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFSP_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFSP_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in registerFederationSynchronizationPoint ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFSP_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFSP_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 4.9
void RTI::RTIambassador::synchronizationPointAchieved (
  const char *label) // supplied C4
throw (
  SynchronizationPointLabelWasNotAnnounced,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sPA_s0)
                            {
                              sprintf(galMsg,"label=%s",label);
                              E1mEnd(sPA_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  std::string s;
  std::wstring l;
  std::wstring ws;

  GERTICO::Mapper::mapWstringFromChar(l, label);
  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->synchronizationPointAchieved(l);
      break;
  }
  catch (GeRtiFactory::SynchronizationPointLabelWasNotAnnounced &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sPA_ta,"SynchronizationPointLabelWasNotAnnounced");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SynchronizationPointLabelWasNotAnnounced(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sPA_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sPA_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sPA_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sPA_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in synchronizationPointAchieved ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sPA_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sPA_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 4.11
void RTI::RTIambassador::requestFederationSave (
  const char     *label,   // supplied C4
  const FedTime&  theTime) // supplied C4
throw (
  FederationTimeAlreadyPassed,
  InvalidFederationTime,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());
  GERTICO::Mapper13::mapFedTime(*myLogicalTimeFactory, geRtiFedTime, theTime);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rFS_s0)
                            {
                              sprintf(galMsg,"label=%s,time=%s",label,GERTICO::ut::convertLogicalTime(*myLogicalTimeFactory, *geRtiFedTime));
                              E1mEnd(rFS_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  std::string s;
  std::wstring l;
  std::wstring ws;

  GERTICO::Mapper::mapWstringFromChar(l, label);
  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->requestFederationSave(l, *geRtiFedTime);
      break;
  }
  catch (GeRtiFactory::FederationTimeAlreadyPassed &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ta,"FederationTimeAlreadyPassed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederationTimeAlreadyPassed(s.c_str());
  }
  catch (GeRtiFactory::InvalidFederationTime &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidFederationTime(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in requestFederationSave ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

void RTI::RTIambassador::requestFederationSave (
  const char *label)     // supplied C4
  throw (
    FederateNotExecutionMember,
    ConcurrentAccessAttempted,
    SaveInProgress,
    RestoreInProgress,
    RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rFS_s1)
                            {
                              sprintf(galMsg,"label=%s",label);
                              E1mEnd(rFS_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter
  std::string s;
  std::wstring l;
  std::wstring ws;

  GERTICO::Mapper::mapWstringFromChar(l, label);
  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->requestFederationSave(l);
      break;
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in requestFederationSave ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 4.13
void RTI::RTIambassador::federateSaveBegun ()
throw (
  SaveNotInitiated,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(fSB_s0);
                           #endif   // inserted by Gal converter
  std::string s;
  std::wstring ws;

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->federateSaveBegun ();
      break;
  }
  catch (GeRtiFactory::SaveNotInitiated &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSB_ta,"SaveNotInitiated");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveNotInitiated(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSB_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSB_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSB_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in federateSaveBegun ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSB_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSB_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 4.14
void RTI::RTIambassador::federateSaveComplete ()
throw (
  SaveNotInitiated,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(fSC_s0);
                           #endif   // inserted by Gal converter
  std::string s;
  std::wstring ws;

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->federateSaveComplete (true);
    clear(privateRefs->regionIMap);
    break;
  }
  catch (GeRtiFactory::SaveNotInitiated &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSC_ta,"SaveNotInitiated");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveNotInitiated(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSC_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in federateSaveComplete ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

void RTI::RTIambassador::federateSaveNotComplete ()
throw (
  SaveNotInitiated,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(fSNC_s0);
                           #endif   // inserted by Gal converter
  std::string s;
  std::wstring ws;

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->federateSaveComplete (false);
      break;
  }
  catch (GeRtiFactory::SaveNotInitiated &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSNC_ta,"SaveNotInitiated");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveNotInitiated(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSNC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSNC_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSNC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in federateSaveNotComplete ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSNC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSNC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 4.16
void RTI::RTIambassador::requestFederationRestore (
  const char *label) // supplied C4
throw (
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rFR_s0)
                            {
                              sprintf(galMsg,"label=%s",label);
                              E1mEnd(rFR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  std::string s;
  std::wstring l;
  std::wstring ws;

  GERTICO::Mapper::mapWstringFromChar(l, label);
  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->requestFederationRestore(l);
      break;
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in requestFederationRestore ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 4.20
void RTI::RTIambassador::federateRestoreComplete ()
  throw (
    RestoreNotRequested,
    FederateNotExecutionMember,
    ConcurrentAccessAttempted,
    SaveInProgress,
    RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(fRC_s0);
                           #endif   // inserted by Gal converter
  std::string s;
  std::wstring ws;

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->federateRestoreComplete (true);
      break;
  }
  catch (GeRtiFactory::RestoreNotRequested &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fRC_ta,"RestoreNotRequested");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreNotRequested(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fRC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fRC_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fRC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in federateRestoreComplete ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fRC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fRC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

void RTI::RTIambassador::federateRestoreNotComplete ()
throw (
  RestoreNotRequested,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(fRNC_s0);
                           #endif   // inserted by Gal converter
  std::string s;
  std::wstring ws;

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->federateRestoreComplete (false);
      break;
  }
  catch (GeRtiFactory::RestoreNotRequested &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fRNC_ta,"RestoreNotRequested");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreNotRequested(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fRNC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fRNC_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fRNC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in federateRestoreNotComplete ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fRNC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fRNC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

/////////////////////////////////////
// Declaration Management Services //
/////////////////////////////////////

// 5.2
void RTI::RTIambassador::publishObjectClass (
        ObjectClassHandle   theClass,      // supplied C1
  const AttributeHandleSet& attributeList) // supplied C4
throw (
  ObjectClassNotDefined,
  AttributeNotDefined,
  OwnershipAcquisitionPending,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(pOC_s0)
                            {
                              sprintf(galMsg,"class=%lu",theClass);
                              GERTICO::ut::printAttributeHandleSet(galMsg,attributeList);
                              E1mEnd(pOC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  GeRtiFactory::Handles handles;
  std::string s;
  std::wstring ws;

  GERTICO::Mapper13::mapAttributeHandleSet(handles, attributeList);

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->publishObjectClass (theClass, handles);
      break;
  }
  catch (GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pOC_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pOC_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotDefined(s.c_str());
  }
  catch (GeRtiFactory::OwnershipAcquisitionPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pOC_ta,"OwnershipAcquisitionPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw OwnershipAcquisitionPending(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pOC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pOC_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pOC_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pOC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in publishObjectClass ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pOC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pOC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }

  if (privateRefs->sender->checkReportServiceInvocation())
  {
    CORBA::ULong i;
    CORBA::ULong len;
    CORBA::ULong pos;
    char buf[128];
    size_t size;

    momReportServiceInvocation.service = "publishObjectClass";
    momReportServiceInvocation.initiatorEnum = GERTICO::FederateEnum;
    momReportServiceInvocation.successIndicator = true;
    sprintf(buf,"%ld", theClass);
    momReportServiceInvocation.suppliedArgument1 = buf;
    pos = 0;
    len = handles.length();
    for (i = 0; i < len; i++)
    {
      if (pos)
      {
        sprintf(&buf[pos], ",%ld", handles[i]);
      }
      else
      {
        sprintf(&buf[pos], "%ld", handles[i]);
      }
      size = strlen(buf);
      GERTICO::Mapper::mapULongSizet(pos, size);
    }
    momReportServiceInvocation.suppliedArgument2 = buf;
//    momReportServiceInvocation.suppliedArgument3 =
//    momReportServiceInvocation.suppliedArgument4 =
//    momReportServiceInvocation.suppliedArgument5 =
//    momReportServiceInvocation.returnedArgument =
//    momReportServiceInvocation.exceptionDescription =
//    momReportServiceInvocation.exceptionId =
    privateRefs->sender->sendReportServiceInvocation(momReportServiceInvocation);
  }
}

// 5.3
void RTI::RTIambassador::unpublishObjectClass (
  ObjectClassHandle theClass) // supplied C1
throw (
  ObjectClassNotDefined,
  ObjectClassNotPublished,
  OwnershipAcquisitionPending,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uOC_s0)
                            {
                              sprintf(galMsg,"class=%lu",theClass);
                              E1mEnd(uOC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  std::string s;
  std::wstring ws;

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->unpublishObjectClass (theClass);
      break;
  }
  catch (GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOC_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::ObjectClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOC_ta,"ObjectClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectClassNotPublished(s.c_str());
  }
  catch (GeRtiFactory::OwnershipAcquisitionPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOC_ta,"OwnershipAcquisitionPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw OwnershipAcquisitionPending(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOC_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOC_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in unpublishObjectClass ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 5.4
void RTI::RTIambassador::publishInteractionClass (
  InteractionClassHandle theInteraction) // supplied C1
throw (
  InteractionClassNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(pIC_s0)
                            {
                              sprintf(galMsg,"class=%lu",theInteraction);
                              E1mEnd(pIC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  std::string s;
  std::wstring ws;

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->publishInteractionClass (theInteraction);
      break;
  }
  catch (GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pIC_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pIC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pIC_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pIC_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pIC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in publishInteractionClass ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pIC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pIC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 5.5
void RTI::RTIambassador::unpublishInteractionClass (
  InteractionClassHandle theInteraction) // supplied C1
throw (
  InteractionClassNotDefined,
  InteractionClassNotPublished,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uIC_s0)
                            {
                              sprintf(galMsg,"class=%lu",theInteraction);
                              E1mEnd(uIC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  std::string s;
  std::wstring ws;

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->unpublishInteractionClass (theInteraction);
      break;
  }
  catch (GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uIC_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::InteractionClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uIC_ta,"InteractionClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionClassNotPublished(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uIC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uIC_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uIC_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uIC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in unpublishInteractionClass ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uIC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uIC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 5.6
void RTI::RTIambassador::subscribeObjectClassAttributes (
        ObjectClassHandle   theClass,      // supplied C1
  const AttributeHandleSet& attributeList, // supplied C4
        Boolean        active)
throw (
  ObjectClassNotDefined,
  AttributeNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sOCA_s0)
                            {
                              sprintf(galMsg,"class=%lu,active=%s",theClass,GERTICO::ut::convert(active));
                              GERTICO::ut::printAttributeHandleSet(galMsg,attributeList);
                              E1mEnd(sOCA_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::Handles handles;
  std::string s;
  std::wstring ws;

  if (active != RTI_FALSE && active != RTI_TRUE)
  {
    throw RTIinternalError("Invalid active boolean value");
  }

  GERTICO::Mapper13::mapAttributeHandleSet(handles, attributeList);

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->subscribeObjectClassAttributes (theClass, handles, active);
      break;
  }
  catch (GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCA_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCA_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotDefined(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCA_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCA_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCA_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCA_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in subscribeObjectClassAttributes ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCA_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCA_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 5.7
void RTI::RTIambassador::unsubscribeObjectClass (
  ObjectClassHandle theClass) // supplied C1
throw (
  ObjectClassNotDefined,
  ObjectClassNotSubscribed,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(usOC_s0)
                            {
                              sprintf(galMsg,"class=%lu",theClass);
                              E1mEnd(usOC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  std::string s;
  std::wstring ws;

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->unsubscribeObjectClass (theClass);
      break;
  }
  catch (GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usOC_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::ObjectClassNotSubscribed &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usOC_ta,"ObjectClassNotSubscribed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectClassNotSubscribed(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usOC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usOC_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usOC_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usOC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in unsubscribeObjectClass ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usOC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usOC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 5.8
void RTI::RTIambassador::subscribeInteractionClass (
  InteractionClassHandle theClass, // supplied C1
  Boolean           active)
throw (
  InteractionClassNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  FederateLoggingServiceCalls,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sIC_s0)
                            {
                              sprintf(galMsg,"class=%lu,active=%s",theClass,GERTICO::ut::convert(active));
                              E1mEnd(sIC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  CORBA::Boolean boo = 0;
  std::string s;
  std::wstring ws;

  if (active != RTI_FALSE && active != RTI_TRUE)
  {
    throw RTIinternalError("Invalid active boolean value");
  }

  if (active == RTI_TRUE)
  {
    boo = 1;
  }

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->subscribeInteractionClass (theClass, boo);
      break;
  }
  catch (GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIC_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::FederateLoggingServiceCalls &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIC_ta,"FederateLoggingServiceCalls");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateLoggingServiceCalls(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIC_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIC_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < 3)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in subscribeInteractionClass ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 5.9
void RTI::RTIambassador::unsubscribeInteractionClass (
  InteractionClassHandle theClass) // supplied C1
throw (
  InteractionClassNotDefined,
  InteractionClassNotSubscribed,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(usIC_s0)
                            {
                              sprintf(galMsg,"class=%lu",theClass);
                              E1mEnd(usIC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  std::string s;
  std::wstring ws;

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->unsubscribeInteractionClass (theClass);
      break;
  }
  catch (GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usIC_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::InteractionClassNotSubscribed &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usIC_ta,"InteractionClassNotSubscribed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionClassNotSubscribed(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usIC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
    ACE_OS::sleep (ACE_Time_Value(0,waitTime));
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usIC_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usIC_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usIC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in unsubscribeInteractionClass ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usIC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usIC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

////////////////////////////////
// Object Management Services //
////////////////////////////////

// 6.2
RTI::ObjectHandle                          // returned C3
RTI::RTIambassador::registerObjectInstance (
        ObjectClassHandle  theClass,  // supplied C1
  const char              *theObject) // supplied C4
throw (
  ObjectClassNotDefined,
  ObjectClassNotPublished,
  ObjectAlreadyRegistered,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rOI_s0)
                            {
                              sprintf(galMsg,"class=%lu,object=%s",theClass,theObject);
                              E1mEnd(rOI_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::ObjectHandle ret;
  std::string s;
  std::wstring object;
  std::wstring ws;

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    GERTICO::Mapper::mapWstringFromChar(object, theObject);
    ret = privateRefs->sender->registerObjectInstance(theClass, object);
    break;
  }
  catch (GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::ObjectClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ta,"ObjectClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectClassNotPublished(s.c_str());
  }
  catch (GeRtiFactory::ObjectAlreadyRegistered &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ta,"ObjectAlreadyRegistered");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectAlreadyRegistered(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in registerObjectInstance ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rOI_s0)
                            {
                              sprintf(galMsg,"ret=%lu",ret);
                              E1mEnd(rOI_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

RTI::ObjectHandle                         // returned C3
RTI::RTIambassador::registerObjectInstance (
        ObjectClassHandle theClass)  // supplied C1
throw (
  ObjectClassNotDefined,
  ObjectClassNotPublished,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rOI_s1)
                            {
                              sprintf(galMsg,"class=%lu",theClass);
                              E1mEnd(rOI_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::ObjectHandle ret;
  std::string s;
  std::wstring ws;

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    ret = privateRefs->sender->registerObjectInstance (theClass);
    break;
  }
  catch (GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::ObjectClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ta,"ObjectClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectClassNotPublished(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in registerObjectInstance ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rOI_s1)
                            {
                              sprintf(galMsg,"ret=%lu",ret);
                              E1mEnd(rOI_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 6.4
RTI::EventRetractionHandle                          // returned C3
RTI::RTIambassador::updateAttributeValues (
        RTI::ObjectHandle            theObject,     // supplied C1
  const AttributeHandleValuePairSet& theAttributes, // supplied C4
  const FedTime&                     theTime,       // supplied C4
  const char                        *theTag)        // supplied C4
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeNotOwned,
  InvalidFederationTime,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());
  GERTICO::Mapper13::mapFedTime(*myLogicalTimeFactory, geRtiFedTime, theTime);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uAV_s0)
                            {
                              sprintf(galMsg,"object=%lu,time=%s,tag=%s",theObject,GERTICO::ut::convertLogicalTime(*myLogicalTimeFactory, *geRtiFedTime),theTag);
                              GERTICO::ut::printAttributeHandleValuePairSet(galMsg,theAttributes);
                              E1mEnd(uAV_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::HandleValues handleValues;
  GeRtiFactory::ERHandle erHandle;
  GeRtiFactory::UserSuppliedTag tag;
  RTI::EventRetractionHandle ret;
  std::string s;
  std::wstring ws;

  GERTICO::Mapper13::mapAttributeHandleValuePairSet(handleValues, theAttributes);
  GERTICO::Mapper::mapUserSuppliedTag(tag, theTag);

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    erHandle = privateRefs->sender->updateAttributeValues(theObject, handleValues, *geRtiFedTime, tag);
      break;
  }
  catch (GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTI::ObjectNotKnown(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTI::AttributeNotDefined(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotOwned &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"AttributeNotOwned");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTI::AttributeNotOwned(s.c_str());
  }
  catch (GeRtiFactory::InvalidFederationTime &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTI::InvalidFederationTime(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTI::FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTI::ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTI::SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTI::RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in updateAttributeValues ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }


  GERTICO::Mapper13::mapEventRetractionHandle(ret, erHandle);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uAV_s0)
                            {
                              sprintf(galMsg,"ret=%lu",ret);
                              E1mEnd(uAV_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

void RTI::RTIambassador::updateAttributeValues (
        RTI::ObjectHandle                 theObject,     // supplied C1
  const AttributeHandleValuePairSet &theAttributes, // supplied C4
  const char                        *theTag)        // supplied C4
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeNotOwned,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uAV_s1)
                            {
                              sprintf(galMsg,"object=%lu,tag=%s",theObject,theTag);
                              GERTICO::ut::printAttributeHandleValuePairSet(galMsg,theAttributes);
                              E1mEnd(uAV_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::HandleValues handleValues;
  GeRtiFactory::UserSuppliedTag tag;
  std::string s;
  std::wstring ws;

  GERTICO::Mapper13::mapAttributeHandleValuePairSet(handleValues, theAttributes);
  GERTICO::Mapper::mapUserSuppliedTag(tag, theTag);

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->updateAttributeValues (theObject, handleValues, tag);
      break;
  }
  catch (GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTI::ObjectNotKnown(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTI::AttributeNotDefined(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotOwned &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"AttributeNotOwned");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTI::AttributeNotOwned(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTI::FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTI::ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTI::SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTI::RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in updateAttributeValues ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 6.6
RTI::EventRetractionHandle                                // returned C3
RTI::RTIambassador::sendInteraction (
        InteractionClassHandle       theInteraction, // supplied C1
  const ParameterHandleValuePairSet& theParameters,  // supplied C4
  const FedTime&                     theTime,        // supplied C4
  const char                        *theTag)         // supplied C4
throw (
  InteractionClassNotDefined,
  InteractionClassNotPublished,
  InteractionParameterNotDefined,
  InvalidFederationTime,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());
  GERTICO::Mapper13::mapFedTime(*myLogicalTimeFactory, geRtiFedTime, theTime);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sI_s0)
                            {
                              sprintf(galMsg,"interaction=%lu,time=%s,tag=%s",theInteraction,GERTICO::ut::convertLogicalTime(*myLogicalTimeFactory, *geRtiFedTime),theTag);
                              GERTICO::ut::printParameterHandleValuePairSet(galMsg,theParameters);
                              E1mEnd(sI_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::HandleValues handleValues;
  GeRtiFactory::ERHandle erHandle;
  GeRtiFactory::UserSuppliedTag tag;
  RTI::EventRetractionHandle ret;
  std::string s;
  std::wstring ws;

  GERTICO::Mapper13::mapParameterHandleValuePairSet(handleValues, theParameters);
  GERTICO::Mapper::mapUserSuppliedTag(tag, theTag);

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    erHandle = privateRefs->sender->sendInteraction(theInteraction, handleValues, *geRtiFedTime, tag);
    GERTICO::Mapper13::mapEventRetractionHandle(ret, erHandle);
      break;
  }
  catch (GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::InteractionClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"InteractionClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionClassNotPublished(s.c_str());
  }
  catch (GeRtiFactory::InteractionParameterNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"InteractionParameterNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionParameterNotDefined(s.c_str());
  }
  catch (GeRtiFactory::InvalidFederationTime &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidFederationTime(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in sendInteraction ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sI_s0)
                            {
                              sprintf(galMsg,"ret=%lu",ret);
                              E1mEnd(sI_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

void RTI::RTIambassador::sendInteraction (
        InteractionClassHandle       theInteraction, // supplied C1
  const ParameterHandleValuePairSet& theParameters,  // supplied C4
  const char                        *theTag)         // supplied C4
throw (
  InteractionClassNotDefined,
  InteractionClassNotPublished,
  InteractionParameterNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sI_s1)
                            {
                              sprintf(galMsg,"interaction=%lu,tag=%s",theInteraction,theTag);
                              GERTICO::ut::printParameterHandleValuePairSet(galMsg,theParameters);
                              E1mEnd(sI_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::HandleValues handleValues;
  GeRtiFactory::UserSuppliedTag tag;
  std::string s;
  std::wstring ws;

  GERTICO::Mapper13::mapParameterHandleValuePairSet(handleValues, theParameters);
  GERTICO::Mapper::mapUserSuppliedTag(tag, theTag);

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->sendInteraction (theInteraction, handleValues, tag);
      break;
  }
  catch (GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTI::InteractionClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::InteractionClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"InteractionClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTI::InteractionClassNotPublished(s.c_str());
  }
  catch (GeRtiFactory::InteractionParameterNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"InteractionParameterNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTI::InteractionParameterNotDefined(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTI::FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTI::ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTI::SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTI::RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in sendInteraction ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 6.8
RTI::EventRetractionHandle                 // returned C3
RTI::RTIambassador::deleteObjectInstance (
        RTI::ObjectHandle    theObject,    // supplied C1
  const FedTime&        theTime,      // supplied C4
  const char           *theTag)       // supplied C4
throw (
  ObjectNotKnown,
  DeletePrivilegeNotHeld,
  InvalidFederationTime,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());
  GERTICO::Mapper13::mapFedTime(*myLogicalTimeFactory, geRtiFedTime, theTime);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(dOI_s0)
                            {
                              sprintf(galMsg,"object=%lu,time=%s,tag=%s",theObject,GERTICO::ut::convertLogicalTime(*myLogicalTimeFactory, *geRtiFedTime),theTag);
                              E1mEnd(dOI_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::ERHandle erHandle;
  GeRtiFactory::UserSuppliedTag tag;
  RTI::EventRetractionHandle ret;
  std::string s;
  std::wstring ws;

  GERTICO::Mapper::mapUserSuppliedTag(tag, theTag);

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    erHandle = privateRefs->sender->deleteObjectInstance(theObject, *geRtiFedTime, tag);
    GERTICO::Mapper13::mapEventRetractionHandle(ret, erHandle);
      break;
  }
  catch (GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectNotKnown(s.c_str());
  }
  catch (GeRtiFactory::DeletePrivilegeNotHeld &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ta,"DeletePrivilegeNotHeld");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw DeletePrivilegeNotHeld(s.c_str());
  }
  catch (GeRtiFactory::InvalidFederationTime &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidFederationTime(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in deleteObjectInstance ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(dOI_s0)
                            {
                              sprintf(galMsg,"ret=%lu",ret);
                              E1mEnd(dOI_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

void RTI::RTIambassador::deleteObjectInstance (
        RTI::ObjectHandle    theObject,    // supplied C1
  const char           *theTag)       // supplied C4
throw (
  ObjectNotKnown,
  DeletePrivilegeNotHeld,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(dOI_s1)
                            {
                              sprintf(galMsg,"object=%lu,tag=%s",theObject,theTag);
                              E1mEnd(dOI_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::UserSuppliedTag tag;
  std::string s;
  std::wstring ws;

  GERTICO::Mapper::mapUserSuppliedTag(tag, theTag);

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->deleteObjectInstance (theObject, tag);
      break;
  }
  catch (GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectNotKnown(s.c_str());
  }
  catch (GeRtiFactory::DeletePrivilegeNotHeld &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ta,"DeletePrivilegeNotHeld");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw DeletePrivilegeNotHeld(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in deleteObjectInstance ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E0(dOI_ts);   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 6.10
void RTI::RTIambassador::localDeleteObjectInstance (
  RTI::ObjectHandle    theObject)       // supplied C1
throw (
  ObjectNotKnown,
  FederateOwnsAttributes,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(lDOI_s0)
                            {
                              sprintf(galMsg,"object=%lu",theObject);
                              E1mEnd(lDOI_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  std::string s;
  std::wstring ws;

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->localDeleteObjectInstance (theObject);
      break;
  }
  catch (GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(lDOI_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectNotKnown(s.c_str());
  }
  catch (GeRtiFactory::FederateOwnsAttributes &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(lDOI_ta,"FederateOwnsAttributes");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateOwnsAttributes(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(lDOI_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(lDOI_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(lDOI_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(lDOI_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in localDeleteObjectInstance ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(lDOI_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(lDOI_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 6.11
void RTI::RTIambassador::changeAttributeTransportationType (
        RTI::ObjectHandle             theObject,     // supplied C1
  const AttributeHandleSet&      theAttributes, // supplied C4
        TransportationHandle     theType)       // supplied C1
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeNotOwned,
  InvalidTransportationHandle,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cATT_s0)
                            {
                              sprintf(galMsg,"object=%lu,type=%lu",theObject,theType);
                              GERTICO::ut::printAttributeHandleSet(galMsg,theAttributes);
                              E1mEnd(cATT_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::Handles handles;
  std::string s;
  std::wstring ws;

  if (theType != RTI_FALSE && theType != RTI_TRUE)
  {
    throw InvalidTransportationHandle("Invalid boolean value");
  }

  GERTICO::Mapper13::mapAttributeHandleSet(handles, theAttributes);

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->changeAttributeTransportationType (theObject, handles, theType);
      break;
  }
  catch (GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cATT_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectNotKnown(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cATT_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotDefined(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotOwned &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cATT_ta,"AttributeNotOwned");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotOwned(s.c_str());
  }
  catch (GeRtiFactory::InvalidTransportationHandle &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cATT_ta,"InvalidTransportationHandle");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidTransportationHandle(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cATT_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cATT_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cATT_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cATT_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in changeAttributeTransportationType ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cATT_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cATT_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 6.12
void RTI::RTIambassador::changeInteractionTransportationType (
  InteractionClassHandle theClass, // supplied C1
  TransportationHandle   theType)  // supplied C1
throw (
  InteractionClassNotDefined,
  InteractionClassNotPublished,
  InvalidTransportationHandle,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cITT_s0)
                            {
                              sprintf(galMsg,"class=%lu,type=%lu",theClass,theType);
                              E1mEnd(cITT_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  if (theType != RTI_FALSE && theType != RTI_TRUE)
  {
    throw InvalidTransportationHandle("Invalid boolean value");
  }

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->changeInteractionTransportationType (theClass, theType);
      break;
  }
  catch (GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cITT_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::InteractionClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cITT_ta,"InteractionClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionClassNotPublished(s.c_str());
  }
  catch (GeRtiFactory::InvalidTransportationHandle &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cITT_ta,"InvalidTransportationHandle");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidTransportationHandle(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cITT_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cITT_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cITT_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cITT_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in changeInteractionTransportationType ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cITT_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cITT_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 6.15
void RTI::RTIambassador::requestObjectAttributeValueUpdate (
        RTI::ObjectHandle        theObject,     // supplied C1
  const AttributeHandleSet& theAttributes) // supplied C4
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rOAVU_s0)
                            {
                              sprintf(galMsg,"object=%lu",theObject);
                              GERTICO::ut::printAttributeHandleSet(galMsg,theAttributes);
                              E1mEnd(rOAVU_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::Handles handles;
  GeRtiFactory::UserSuppliedTag tag;
  std::string s;
  std::wstring ws;

  GERTICO::Mapper13::mapAttributeHandleSet(handles, theAttributes);

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->requestObjectAttributeValueUpdate(theObject, handles, tag);
    break;
  }
  catch (GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOAVU_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectNotKnown(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOAVU_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotDefined(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOAVU_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOAVU_ta,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOAVU_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOAVU_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOAVU_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in requestObjectAttributeValueUpdate ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOAVU_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOAVU_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

void RTI::RTIambassador::requestClassAttributeValueUpdate (
        ObjectClassHandle   theClass,      // supplied C1
  const AttributeHandleSet& theAttributes) // supplied C4
throw (
  ObjectClassNotDefined,
  AttributeNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rCAVU_s0)
                            {
                              sprintf(galMsg,"class=%lu",theClass);
                              GERTICO::ut::printAttributeHandleSet(galMsg,theAttributes);
                              E1mEnd(rCAVU_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::Handles handles;
  GeRtiFactory::UserSuppliedTag tag;
  std::string s;
  std::wstring ws;

  GERTICO::Mapper13::mapAttributeHandleSet(handles, theAttributes);

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->requestClassAttributeValueUpdate(theClass, handles, tag);
    break;
  }
  catch (GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVU_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVU_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotDefined(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVU_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVU_ta,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVU_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVU_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVU_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in requestClassAttributeValueUpdate ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVU_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVU_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

///////////////////////////////////
// Ownership Management Services //
///////////////////////////////////

// 7.2
void RTI::RTIambassador::unconditionalAttributeOwnershipDivestiture (
        RTI::ObjectHandle                  theObject,     // supplied C1
  const AttributeHandleSet&           theAttributes) // supplied C4
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeNotOwned,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uAOD_s0)
                            {
                              sprintf(galMsg,"object=%lu",theObject);
                              GERTICO::ut::printAttributeHandleSet(galMsg,theAttributes);
                              E1mEnd(uAOD_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::Handles handles;
  std::string s;
  std::wstring ws;

  GERTICO::Mapper13::mapAttributeHandleSet(handles, theAttributes);
  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->unconditionalAttributeOwnershipDivestiture (theObject, handles);
      break;
  }
  catch (GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAOD_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectNotKnown(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAOD_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotDefined(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotOwned &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAOD_ta,"AttributeNotOwned");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotOwned(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAOD_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAOD_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAOD_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAOD_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in unconditionalAttributeOwnershipDivestiture ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAOD_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAOD_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 7.3
void RTI::RTIambassador::negotiatedAttributeOwnershipDivestiture (
        RTI::ObjectHandle                  theObject,     // supplied C1
  const AttributeHandleSet&           theAttributes, // supplied C4
  const char                         *theTag)        // supplied C4
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeNotOwned,
  AttributeAlreadyBeingDivested,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(nAOD_s0)
                            {
                              sprintf(galMsg,"object=%lu,tag=%s",theObject,theTag);
                              GERTICO::ut::printAttributeHandleSet(galMsg,theAttributes);
                              E1mEnd(nAOD_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::Handles handles;
  GeRtiFactory::UserSuppliedTag tag;
  std::string s;
  std::wstring ws;

  GERTICO::Mapper13::mapAttributeHandleSet(handles, theAttributes);
  GERTICO::Mapper::mapUserSuppliedTag(tag, theTag);

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->negotiatedAttributeOwnershipDivestiture (theObject, handles, tag);
      break;
  }
  catch (GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nAOD_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectNotKnown(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nAOD_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotDefined(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotOwned &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nAOD_ta,"AttributeNotOwned");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotOwned(s.c_str());
  }
  catch (GeRtiFactory::AttributeAlreadyBeingDivested &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nAOD_ta,"AttributeAlreadyBeingDivested");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeAlreadyBeingDivested(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nAOD_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nAOD_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nAOD_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nAOD_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in negotiatedAttributeOwnershipDivestiture ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nAOD_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nAOD_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 7.7
void RTI::RTIambassador::attributeOwnershipAcquisition (
        RTI::ObjectHandle        theObject,         // supplied C1
  const AttributeHandleSet& desiredAttributes, // supplied C4
  const char               *theTag)            // supplied C4
throw (
  ObjectNotKnown,
  ObjectClassNotPublished,
  AttributeNotDefined,
  AttributeNotPublished,
  FederateOwnsAttributes,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aOA_s0)
                            {
                              sprintf(galMsg,"object=%lu,tag=%s",theObject,theTag);
                              GERTICO::ut::printAttributeHandleSet(galMsg,desiredAttributes);
                              E1mEnd(aOA_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::Handles handles;
  GeRtiFactory::UserSuppliedTag tag;
  std::string s;
  std::wstring ws;

  GERTICO::Mapper13::mapAttributeHandleSet(handles, desiredAttributes);
  GERTICO::Mapper::mapUserSuppliedTag(tag, theTag);

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->attributeOwnershipAcquisition(theObject, handles, tag);
      break;
  }
  catch (GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOA_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectNotKnown(s.c_str());
  }
  catch (GeRtiFactory::ObjectClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOA_ta,"ObjectClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectClassNotPublished(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOA_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotDefined(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOA_ta,"AttributeNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotPublished(s.c_str());
  }
  catch (GeRtiFactory::FederateOwnsAttributes &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOA_ta,"FederateOwnsAttributes");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateOwnsAttributes(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOA_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOA_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOA_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOA_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in attributeOwnershipAcquisition ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOA_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOA_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 7.8
void RTI::RTIambassador::attributeOwnershipAcquisitionIfAvailable (
        RTI::ObjectHandle        theObject,         // supplied C1
  const AttributeHandleSet& desiredAttributes) // supplied C4
throw (
  ObjectNotKnown,
  ObjectClassNotPublished,
  AttributeNotDefined,
  AttributeNotPublished,
  FederateOwnsAttributes,
  AttributeAlreadyBeingAcquired,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aOAIA_s0)
                            {
                              sprintf(galMsg,"object=%lu",theObject);
                              GERTICO::ut::printAttributeHandleSet(galMsg,desiredAttributes);
                              E1mEnd(aOAIA_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::Handles handles;
  std::string s;
  std::wstring ws;

  GERTICO::Mapper13::mapAttributeHandleSet(handles, desiredAttributes);
  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->attributeOwnershipAcquisitionIfAvailable (theObject, handles);
      break;
  }
  catch (GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOAIA_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectNotKnown(s.c_str());
  }
  catch (GeRtiFactory::ObjectClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOAIA_ta,"ObjectClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectClassNotPublished(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOAIA_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotDefined(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOAIA_ta,"AttributeNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotPublished(s.c_str());
  }
  catch (GeRtiFactory::FederateOwnsAttributes &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOAIA_ta,"FederateOwnsAttributes");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateOwnsAttributes(s.c_str());
  }
  catch (GeRtiFactory::AttributeAlreadyBeingAcquired &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOAIA_ta,"AttributeAlreadyBeingAcquired");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeAlreadyBeingAcquired(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOAIA_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOAIA_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOAIA_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOAIA_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in attributeOwnershipAcquisitionIfAvailable ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOAIA_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOAIA_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 7.11
RTI::AttributeHandleSet*                        // returned C6
RTI::RTIambassador::attributeOwnershipReleaseResponse (
        RTI::ObjectHandle        theObject,     // supplied C1
  const AttributeHandleSet& theAttributes) // supplied C4
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeNotOwned,
  FederateWasNotAskedToReleaseAttribute,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aORR_s0)
                            {
                              sprintf(galMsg,"object=%lu",theObject);
                              GERTICO::ut::printAttributeHandleSet(galMsg,theAttributes);
                              E1mEnd(aORR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::AttributeHandleSet* ret;
  GeRtiFactory::Handles handles;
  GeRtiFactory::Handles* retHandles;
  GeRtiFactory::UserSuppliedTag tag;
  std::string s;
  std::wstring ws;

  GERTICO::Mapper13::mapAttributeHandleSet(handles, theAttributes);

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    retHandles = privateRefs->sender->confirmDivestiture (theObject, handles, tag);
    ret = RTI::AttributeHandleSetFactory::create (retHandles->length());
    GERTICO::Mapper13::mapAttributeHandleSet(*ret, *retHandles);
      break;
  }
  catch (GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aORR_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectNotKnown(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aORR_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotDefined(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotOwned &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aORR_ta,"AttributeNotOwned");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotOwned(s.c_str());
  }
  catch (GeRtiFactory::FederateWasNotAskedToReleaseAttribute &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aORR_ta,"FederateWasNotAskedToReleaseAttribute");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateWasNotAskedToReleaseAttribute(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aORR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aORR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aORR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aORR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in attributeOwnershipReleaseResponse ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aORR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aORR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aORR_s0)
                            {
                              sprintf(galMsg,"%s","ret");
                              GERTICO::ut::printAttributeHandleSet(galMsg,*ret);
                              E1mEnd(aORR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 7.12
void RTI::RTIambassador::cancelNegotiatedAttributeOwnershipDivestiture (
        RTI::ObjectHandle        theObject,     // supplied C1
  const AttributeHandleSet& theAttributes) // supplied C4
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeNotOwned,
  AttributeDivestitureWasNotRequested,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cNAOD_s0)
                            {
                              sprintf(galMsg,"object=%lu",theObject);
                              GERTICO::ut::printAttributeHandleSet(galMsg,theAttributes);
                              E1mEnd(cNAOD_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::Handles handles;
  std::string s;
  std::wstring ws;

  GERTICO::Mapper13::mapAttributeHandleSet(handles, theAttributes);
  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->cancelNegotiatedAttributeOwnershipDivestiture (theObject, handles);
      break;
  }
  catch (GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cNAOD_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectNotKnown(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cNAOD_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotDefined(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotOwned &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cNAOD_ta,"AttributeNotOwned");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotOwned(s.c_str());
  }
  catch (GeRtiFactory::AttributeDivestitureWasNotRequested &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cNAOD_ta,"AttributeDivestitureWasNotRequested");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeDivestitureWasNotRequested(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cNAOD_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cNAOD_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cNAOD_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cNAOD_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in cancelNegotiatedAttributeOwnershipDivestiture ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cNAOD_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cNAOD_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 7.13
void RTI::RTIambassador::cancelAttributeOwnershipAcquisition (
        RTI::ObjectHandle        theObject,     // supplied C1
  const AttributeHandleSet& theAttributes) // supplied C4
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeAlreadyOwned,
  AttributeAcquisitionWasNotRequested,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cAOA_s0)
                            {
                              sprintf(galMsg,"object=%lu",theObject);
                              GERTICO::ut::printAttributeHandleSet(galMsg,theAttributes);
                              E1mEnd(cAOA_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::Handles handles;
  std::string s;
  std::wstring ws;

  GERTICO::Mapper13::mapAttributeHandleSet(handles, theAttributes);

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->cancelAttributeOwnershipAcquisition (theObject, handles);
      break;
  }
  catch (GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOA_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectNotKnown(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOA_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotDefined(s.c_str());
  }
  catch (GeRtiFactory::AttributeAlreadyOwned &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOA_ta,"AttributeAlreadyOwned");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeAlreadyOwned(s.c_str());
  }
  catch (GeRtiFactory::AttributeAcquisitionWasNotRequested &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOA_ta,"AttributeAcquisitionWasNotRequested");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeAcquisitionWasNotRequested(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOA_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOA_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOA_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOA_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in cancelAttributeOwnershipAcquisition ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOA_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOA_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 7.15
void RTI::RTIambassador::queryAttributeOwnership (
  RTI::ObjectHandle    theObject,    // supplied C1
  AttributeHandle theAttribute) // supplied C1
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(qAO_s0)
                            {
                              sprintf(galMsg,"object=%lu,attribute=%lu",theObject,theAttribute);
                              E1mEnd(qAO_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->queryAttributeOwnership (theObject, theAttribute);
      break;
  }
  catch (GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qAO_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectNotKnown(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qAO_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotDefined(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qAO_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qAO_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qAO_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qAO_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in queryAttributeOwnership ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qAO_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qAO_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 7.17
RTI::Boolean                          // returned C3
RTI::RTIambassador::isAttributeOwnedByFederate (
  RTI::ObjectHandle    theObject,     // supplied C1
  AttributeHandle theAttribute)  // supplied C1
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(iAOBF_s0)
                            {
                              sprintf(galMsg,"object=%lu,attribute=%lu",theObject,theAttribute);
                              E1mEnd(iAOBF_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::Boolean ret;
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    if (privateRefs->sender->isAttributeOwnedByFederate (theObject, theAttribute))
      ret = RTI::RTI_TRUE;
    else
      ret = RTI::RTI_FALSE;
      break;
  }
  catch (GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(iAOBF_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectNotKnown(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(iAOBF_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotDefined(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(iAOBF_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(iAOBF_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(iAOBF_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(iAOBF_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in isAttributeOwnedByFederate ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(iAOBF_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(iAOBF_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(iAOBF_s0)
                            {
                              sprintf(galMsg,"ret=%s",GERTICO::ut::convert(ret));
                              E1mEnd(iAOBF_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

//////////////////////////////
// Time Management Services //
//////////////////////////////

// 8.2
void RTI::RTIambassador::enableTimeRegulation (
  const FedTime& theFederateTime,  // supplied C4
  const FedTime& theLookahead)     // supplied C4
throw (
  TimeRegulationAlreadyEnabled,
  EnableTimeRegulationPending,
  TimeAdvanceAlreadyInProgress,
  InvalidFederationTime,
  InvalidLookahead,
  ConcurrentAccessAttempted,
  FederateNotExecutionMember,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());
  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> geRtiLookahead(myLogicalTimeIntervalFactory->makeZero());
  GERTICO::Mapper13::mapFedTime(*myLogicalTimeFactory, geRtiFedTime, theFederateTime);
  GERTICO::Mapper13::mapLogicalTimeInterval(*myLogicalTimeIntervalFactory, *geRtiLookahead, theLookahead);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(eTR_s0)
                            {
                              char buff[512];

                              sprintf(galMsg,"time=%s,lookAhead=",GERTICO::ut::convertLogicalTime(*myLogicalTimeFactory, *geRtiFedTime));
                              geRtiLookahead->getPrintableString(buff);
                              strcat(galMsg, buff);
                              E1mEnd(eTR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  std::string s;
  std::wstring ws;

  try
  {
    privateRefs->sender->enableTimeRegulation(*geRtiFedTime, *geRtiLookahead);
  }
  catch (GeRtiFactory::TimeRegulationAlreadyEnabled &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTR_ta,"TimeRegulationAlreadyEnabled");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw TimeRegulationAlreadyEnabled(s.c_str());
  }
  catch (GeRtiFactory::EnableTimeRegulationPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTR_ta,"EnableTimeRegulationPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw EnableTimeRegulationPending(s.c_str());
  }
  catch (GeRtiFactory::TimeAdvanceAlreadyInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTR_ta,"TimeAdvanceAlreadyInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw TimeAdvanceAlreadyInProgress(s.c_str());
  }
  catch (GeRtiFactory::InvalidFederationTime &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTR_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidFederationTime(s.c_str());
  }
  catch (GeRtiFactory::InvalidLookahead &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTR_ta,"InvalidLookahead");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidLookahead(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
ACE_PRINT_EXCEPTION (sysex, "System Exception in enableTimeRegulation ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
}

// 8.4
void RTI::RTIambassador::disableTimeRegulation ()
throw (
  TimeRegulationWasNotEnabled,
  ConcurrentAccessAttempted,
  FederateNotExecutionMember,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(dTR_s0);
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->disableTimeRegulation ();
      break;
  }
  catch (GeRtiFactory::TimeRegulationWasNotEnabled &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTR_ta,"TimeRegulationWasNotEnabled");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw TimeRegulationWasNotEnabled(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in disableTimeRegulation ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 8.5
void RTI::RTIambassador::enableTimeConstrained ()
throw (
  TimeConstrainedAlreadyEnabled,
  EnableTimeConstrainedPending,
  TimeAdvanceAlreadyInProgress,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(eTC_s0);
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->enableTimeConstrained ();
      break;
  }
  catch (GeRtiFactory::TimeConstrainedAlreadyEnabled &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTC_ta,"TimeConstrainedAlreadyEnabled");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw TimeConstrainedAlreadyEnabled(s.c_str());
  }
  catch (GeRtiFactory::EnableTimeConstrainedPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTC_ta,"EnableTimeConstrainedPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw EnableTimeConstrainedPending(s.c_str());
  }
  catch (GeRtiFactory::TimeAdvanceAlreadyInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTC_ta,"TimeAdvanceAlreadyInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw TimeAdvanceAlreadyInProgress(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTC_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTC_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in enableTimeConstrained ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 8.7
void RTI::RTIambassador::disableTimeConstrained ()
throw (
  TimeConstrainedWasNotEnabled,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(dTC_s0);
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->disableTimeConstrained ();
      break;
  }
  catch (GeRtiFactory::TimeConstrainedWasNotEnabled &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTC_ta,"TimeConstrainedWasNotEnabled");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw TimeConstrainedWasNotEnabled(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTC_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTC_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in disableTimeConstrained ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 8.8
void RTI::RTIambassador::timeAdvanceRequest (
 const  FedTime& theTime) // supplied C4
throw (
  InvalidFederationTime,
  FederationTimeAlreadyPassed,
  TimeAdvanceAlreadyInProgress,
  EnableTimeRegulationPending,
  EnableTimeConstrainedPending,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());
  GERTICO::Mapper13::mapFedTime(*myLogicalTimeFactory, geRtiFedTime, theTime);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(tAR_s0)
                            {
                              sprintf(galMsg,"time=%s",GERTICO::ut::convertLogicalTime(*myLogicalTimeFactory, *geRtiFedTime));
                              E1mEnd(tAR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->timeAdvanceRequest(*geRtiFedTime);
      break;
  }
  catch (GeRtiFactory::InvalidFederationTime &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tAR_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidFederationTime(s.c_str());
  }
  catch (GeRtiFactory::FederationTimeAlreadyPassed &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tAR_ta,"FederationTimeAlreadyPassed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederationTimeAlreadyPassed(s.c_str());
  }
  catch (GeRtiFactory::TimeAdvanceAlreadyInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tAR_ta,"TimeAdvanceAlreadyInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw TimeAdvanceAlreadyInProgress(s.c_str());
  }
  catch (GeRtiFactory::EnableTimeRegulationPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tAR_ta,"EnableTimeRegulationPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw EnableTimeRegulationPending(s.c_str());
  }
  catch (GeRtiFactory::EnableTimeConstrainedPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tAR_ta,"EnableTimeConstrainedPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw EnableTimeConstrainedPending(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tAR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tAR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tAR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tAR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in timeAdvanceRequest ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tAR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tAR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 8.9
void RTI::RTIambassador::timeAdvanceRequestAvailable (
const FedTime& theTime) // supplied C4
  throw (
    InvalidFederationTime,
    FederationTimeAlreadyPassed,
    TimeAdvanceAlreadyInProgress,
    EnableTimeRegulationPending,
    EnableTimeConstrainedPending,
    FederateNotExecutionMember,
    ConcurrentAccessAttempted,
    SaveInProgress,
    RestoreInProgress,
    RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());
  GERTICO::Mapper13::mapFedTime(*myLogicalTimeFactory, geRtiFedTime, theTime);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(tARA_s0)
                            {
                              sprintf(galMsg,"time=%s",GERTICO::ut::convertLogicalTime(*myLogicalTimeFactory, *geRtiFedTime));
                              E1mEnd(tARA_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->timeAdvanceRequestAvailable(*geRtiFedTime);
      break;
  }
  catch (GeRtiFactory::InvalidFederationTime &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tARA_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidFederationTime(s.c_str());
  }
  catch (GeRtiFactory::FederationTimeAlreadyPassed &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tARA_ta,"FederationTimeAlreadyPassed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederationTimeAlreadyPassed(s.c_str());
  }
  catch (GeRtiFactory::TimeAdvanceAlreadyInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tARA_ta,"TimeAdvanceAlreadyInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw TimeAdvanceAlreadyInProgress(s.c_str());
  }
  catch (GeRtiFactory::EnableTimeRegulationPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tARA_ta,"EnableTimeRegulationPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw EnableTimeRegulationPending(s.c_str());
  }
  catch (GeRtiFactory::EnableTimeConstrainedPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tARA_ta,"EnableTimeConstrainedPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw EnableTimeConstrainedPending(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tARA_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tARA_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tARA_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tARA_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in timeAdvanceRequestAvailable ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tARA_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tARA_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 8.10
void RTI::RTIambassador::nextEventRequest (
  const FedTime& theTime) // supplied C4
throw (
  InvalidFederationTime,
  FederationTimeAlreadyPassed,
  TimeAdvanceAlreadyInProgress,
  EnableTimeRegulationPending,
  EnableTimeConstrainedPending,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());
  GERTICO::Mapper13::mapFedTime(*myLogicalTimeFactory, geRtiFedTime, theTime);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(nER_s0)
                            {
                              sprintf(galMsg,"time=%s",GERTICO::ut::convertLogicalTime(*myLogicalTimeFactory, *geRtiFedTime));
                              E1mEnd(nER_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->nextEventRequest(*geRtiFedTime);
      break;
  }
  catch (GeRtiFactory::InvalidFederationTime &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nER_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidFederationTime(s.c_str());
  }
  catch (GeRtiFactory::FederationTimeAlreadyPassed &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nER_ta,"FederationTimeAlreadyPassed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederationTimeAlreadyPassed(s.c_str());
  }
  catch (GeRtiFactory::TimeAdvanceAlreadyInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nER_ta,"TimeAdvanceAlreadyInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw TimeAdvanceAlreadyInProgress(s.c_str());
  }
  catch (GeRtiFactory::EnableTimeRegulationPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nER_ta,"EnableTimeRegulationPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw EnableTimeRegulationPending(s.c_str());
  }
  catch (GeRtiFactory::EnableTimeConstrainedPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nER_ta,"EnableTimeConstrainedPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw EnableTimeConstrainedPending(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nER_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nER_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nER_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nER_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in nextEventRequest ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nER_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nER_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 8.11
void RTI::RTIambassador::nextEventRequestAvailable (
  const FedTime& theTime) // supplied C4
throw (
  InvalidFederationTime,
  FederationTimeAlreadyPassed,
  TimeAdvanceAlreadyInProgress,
  EnableTimeRegulationPending,
  EnableTimeConstrainedPending,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());
  GERTICO::Mapper13::mapFedTime(*myLogicalTimeFactory, geRtiFedTime, theTime);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(nERA_s0)
                            {
                              sprintf(galMsg,"time=%s",GERTICO::ut::convertLogicalTime(*myLogicalTimeFactory, *geRtiFedTime));
                              E1mEnd(nERA_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->nextEventRequestAvailable(*geRtiFedTime);
      break;
  }
  catch (GeRtiFactory::InvalidFederationTime &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nERA_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidFederationTime(s.c_str());
  }
  catch (GeRtiFactory::FederationTimeAlreadyPassed &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nERA_ta,"FederationTimeAlreadyPassed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederationTimeAlreadyPassed(s.c_str());
  }
  catch (GeRtiFactory::TimeAdvanceAlreadyInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nERA_ta,"TimeAdvanceAlreadyInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw TimeAdvanceAlreadyInProgress(s.c_str());
  }
  catch (GeRtiFactory::EnableTimeRegulationPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nERA_ta,"EnableTimeRegulationPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw EnableTimeRegulationPending(s.c_str());
  }
  catch (GeRtiFactory::EnableTimeConstrainedPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nERA_ta,"EnableTimeConstrainedPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw EnableTimeConstrainedPending(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nERA_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nERA_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nERA_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nERA_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in nextEventRequestAvailable ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nERA_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nERA_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 8.12
void RTI::RTIambassador::flushQueueRequest (
  const FedTime& theTime) // supplied C4
throw (
  InvalidFederationTime,
  FederationTimeAlreadyPassed,
  TimeAdvanceAlreadyInProgress,
  EnableTimeRegulationPending,
  EnableTimeConstrainedPending,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());
  GERTICO::Mapper13::mapFedTime(*myLogicalTimeFactory, geRtiFedTime, theTime);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(fQR_s0)
                            {
                              sprintf(galMsg,"time=%s",GERTICO::ut::convertLogicalTime(*myLogicalTimeFactory, *geRtiFedTime));
                              E1mEnd(fQR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->flushQueueRequest(*geRtiFedTime);
      break;
  }
  catch (GeRtiFactory::InvalidFederationTime &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fQR_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidFederationTime(s.c_str());
  }
  catch (GeRtiFactory::FederationTimeAlreadyPassed &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fQR_ta,"FederationTimeAlreadyPassed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederationTimeAlreadyPassed(s.c_str());
  }
  catch (GeRtiFactory::TimeAdvanceAlreadyInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fQR_ta,"TimeAdvanceAlreadyInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw TimeAdvanceAlreadyInProgress(s.c_str());
  }
  catch (GeRtiFactory::EnableTimeRegulationPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fQR_ta,"EnableTimeRegulationPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw EnableTimeRegulationPending(s.c_str());
  }
  catch (GeRtiFactory::EnableTimeConstrainedPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fQR_ta,"EnableTimeConstrainedPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw EnableTimeConstrainedPending(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fQR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fQR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fQR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fQR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in flushQueueRequest ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fQR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fQR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 8.14
void RTI::RTIambassador::enableAsynchronousDelivery()
  throw (
    AsynchronousDeliveryAlreadyEnabled,
    FederateNotExecutionMember,
    ConcurrentAccessAttempted,
    SaveInProgress,
    RestoreInProgress,
    RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E0(eAD_s0);   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->enableAsynchronousDelivery ();
      break;
  }
  catch (GeRtiFactory::AsynchronousDeliveryAlreadyEnabled &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eAD_ta,"AsynchronousDeliveryAlreadyEnabled");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AsynchronousDeliveryAlreadyEnabled(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eAD_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eAD_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eAD_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eAD_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in enableAsynchronousDelivery ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eAD_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eAD_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 8.15
void RTI::RTIambassador::disableAsynchronousDelivery()
  throw (
    AsynchronousDeliveryAlreadyDisabled,
    FederateNotExecutionMember,
    ConcurrentAccessAttempted,
    SaveInProgress,
    RestoreInProgress,
    RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(dAD_s0);
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->disableAsynchronousDelivery ();
      break;
  }
  catch (GeRtiFactory::AsynchronousDeliveryAlreadyDisabled &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dAD_ta,"AsynchronousDeliveryAlreadyDisabled");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AsynchronousDeliveryAlreadyDisabled(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dAD_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dAD_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dAD_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dAD_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in disableAsynchronousDelivery ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dAD_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dAD_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 8.16
void RTI::RTIambassador::queryLBTS (
  FedTime& theTime) // returned C5
throw (
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());

  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->queryLBTS(*geRtiFedTime);
    GERTICO::Mapper13::mapFedTime(theTime, geRtiFedTime);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(qLBTS_s0)
                            {
                              sprintf(galMsg,"time=%s",GERTICO::ut::convertLogicalTime(*myLogicalTimeFactory, *geRtiFedTime));
                              E1mEnd(qLBTS_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
    break;
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qLBTS_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qLBTS_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qLBTS_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qLBTS_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in queryLBTS ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qLBTS_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qLBTS_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 8.17
void RTI::RTIambassador::queryFederateTime (
  FedTime& theTime) // returned C5
throw (
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());

  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->queryFederateTime(*geRtiFedTime);
    GERTICO::Mapper13::mapFedTime(theTime, geRtiFedTime);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(qFT_s0)
                            {
                              sprintf(galMsg,"time=%s",GERTICO::ut::convertLogicalTime(*myLogicalTimeFactory, *geRtiFedTime));
                              E1mEnd(qFT_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
    break;
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qFT_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qFT_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qFT_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qFT_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in queryFederateTime ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qFT_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qFT_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 8.18
void RTI::RTIambassador::queryMinNextEventTime (
  FedTime& theTime) // returned C5
throw (
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());

  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->queryMinNextEventTime(*geRtiFedTime);
    GERTICO::Mapper13::mapFedTime(theTime, geRtiFedTime);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(qMNET_s0)
                            {
                              sprintf(galMsg,"time=%s",GERTICO::ut::convertLogicalTime(*myLogicalTimeFactory, *geRtiFedTime));
                              E1mEnd(qMNET_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
    break;
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qMNET_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qMNET_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qMNET_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qMNET_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in queryMinNextEventTime ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qMNET_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qMNET_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 8.19
void RTI::RTIambassador::modifyLookahead (
  const FedTime& theLookahead) // supplied C4
throw (
  InvalidLookahead,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> geRtiFedTime(myLogicalTimeIntervalFactory->makeZero());
  GERTICO::Mapper13::mapLogicalTimeInterval(*myLogicalTimeIntervalFactory, *geRtiFedTime, theLookahead);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(mL_s0)
                            {
                              char buff[512];

                              geRtiFedTime->getPrintableString(buff);
                              sprintf(galMsg,"lookahead=%s", buff);
                              E1mEnd(mL_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->modifyLookahead(*geRtiFedTime);
      break;
  }
  catch (GeRtiFactory::InvalidLookahead &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(mL_ta,"InvalidLookahead");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidLookahead(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(mL_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(mL_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(mL_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(mL_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in modifyLookahead ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(mL_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(mL_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 8.20
void RTI::RTIambassador::queryLookahead (
   FedTime& theTime) // returned C5
throw (
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> geRtiFedTime(myLogicalTimeIntervalFactory->makeZero());
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->queryLookahead(*geRtiFedTime);
    GERTICO::Mapper13::mapLogicalTimeInterval(*myLogicalTimeIntervalFactory, theTime, *geRtiFedTime);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(qL_s0)
                            {
                              char buff[512];

                              geRtiFedTime->getPrintableString(buff);
                              sprintf(galMsg,"time=%s", buff);
                              E1mEnd(qL_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
    break;
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qL_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qL_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qL_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qL_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in queryLookahead ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qL_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qL_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 8.21
void RTI::RTIambassador::retract (
  RTI::EventRetractionHandle theHandle) // supplied C1
throw (
  InvalidRetractionHandle,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(r_s0)
                            {
                              sprintf(galMsg,"sendingFederate=%lu",theHandle.sendingFederate);
                              E1mEnd(r_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::ERHandle erHandle;
  std::string s;
  std::wstring ws;

  GERTICO::Mapper13::mapEventRetractionHandle(erHandle, theHandle);

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->retract (erHandle);
      break;
  }
  catch (GeRtiFactory::InvalidRetractionHandle &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(r_ta,"InvalidRetractionHandle");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidRetractionHandle(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(r_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(r_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(r_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(r_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in retract ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(r_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(r_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 8.23
void RTI::RTIambassador::changeAttributeOrderType (
        RTI::ObjectHandle        theObject,     // supplied C1
  const AttributeHandleSet& theAttributes, // supplied C4
        OrderingHandle      theType)       // supplied C1
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeNotOwned,
  InvalidOrderingHandle,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cAOT_s0)
                            {
                              sprintf(galMsg,"object=%lu,type=%lu",theObject,theType);
                              GERTICO::ut::printAttributeHandleSet(galMsg,theAttributes);
                              E1mEnd(cAOT_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::Handles handles;
  std::string s;
  std::wstring ws;

  if (theType != RTI_FALSE && theType != RTI_TRUE)
  {
    throw InvalidOrderingHandle("Invalid boolean value");
  }

  GERTICO::Mapper13::mapAttributeHandleSet(handles, theAttributes);

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->changeAttributeOrderType (theObject, handles, theType);
      break;
  }
  catch (GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOT_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectNotKnown(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOT_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotDefined(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotOwned &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOT_ta,"AttributeNotOwned");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotOwned(s.c_str());
  }
  catch (GeRtiFactory::InvalidOrderingHandle &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOT_ta,"InvalidOrderingHandle");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidOrderingHandle(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOT_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOT_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOT_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOT_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in changeAttributeOrderType ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOT_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOT_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 8.24
void RTI::RTIambassador::changeInteractionOrderType (
  InteractionClassHandle theClass, // supplied C1
  OrderingHandle         theType)  // supplied C1
throw (
  InteractionClassNotDefined,
  InteractionClassNotPublished,
  InvalidOrderingHandle,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cIOT_s0)
                            {
                              sprintf(galMsg,"class=%lu,type=%lu",theClass,theType);
                              E1mEnd(cIOT_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  if (theType != RTI_FALSE && theType != RTI_TRUE)
  {
    throw InvalidOrderingHandle("Invalid boolean value");
  }

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->changeInteractionOrderType (theClass, theType);
      break;
  }
  catch (GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cIOT_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::InteractionClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cIOT_ta,"InteractionClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionClassNotPublished(s.c_str());
  }
  catch (GeRtiFactory::InvalidOrderingHandle &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cIOT_ta,"InvalidOrderingHandle");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidOrderingHandle(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cIOT_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cIOT_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cIOT_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cIOT_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in changeInteractionOrderType ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cIOT_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cIOT_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

//////////////////////////////////
// Data Distribution Management //
//////////////////////////////////

// 9.2
RTI::Region*                           // returned C6
RTI::RTIambassador::createRegion (
  SpaceHandle theSpace,           // supplied C1
  ULong       numberOfExtents)    // supplied C1
throw (
  SpaceNotDefined,
  InvalidExtents,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cR_s0)
                            {
                              sprintf(galMsg,"space=%ld,extents=%lu",theSpace,numberOfExtents);
                              E1mEnd(cR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GERTICO::HandleSet dimensions;
  GeRtiFactory::GeRtiHandle region;
  RTI::Region *ret = NULL;
  RegionI *regionI = NULL;
  std::string s;
  std::wstring ws;

  if (numberOfExtents == 0)
  {
    throw InvalidExtents("Number of extents is zero");
  }

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    region = privateRefs->sender->createRegion(theSpace, numberOfExtents, dimensions);
    regionI = new RegionI(theSpace, region, numberOfExtents);
    privateRefs->regionIMap[region] = regionI;
    ret = regionI;
    break;
  }
  catch (GeRtiFactory::SpaceNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cR_ta,"SpaceNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SpaceNotDefined(s.c_str());
  }
  catch (GeRtiFactory::InvalidExtents &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cR_ta,"InvalidExtents");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidExtents(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in createRegion ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cR_s0)
                            {
                              sprintf(galMsg,"ret=%s",GERTICO::ut::convert(ret));
                              E1mEnd(cR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 9.3
void RTI::RTIambassador::notifyAboutRegionModification (
  Region &theRegion)  // supplied C4
throw (
  RegionNotKnown,
  InvalidExtents,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(nARM_s0)
                            {
                              sprintf(galMsg,"region=%s",GERTICO::ut::convert(&theRegion));
                              E1mEnd(nARM_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  GeRtiFactory::Extents myExtents;
  RegionI *regionI = (RegionI *) &theRegion;

  mapRegionI(myExtents, *regionI);

  GeRtiFactory::GeRtiHandle id = regionI->id;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->notifyAboutRegionModification(id, myExtents);
    break;
  }
  catch (GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nARM_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RegionNotKnown(s.c_str());
  }
  catch (GeRtiFactory::InvalidExtents &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nARM_ta,"InvalidExtents");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidExtents(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nARM_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nARM_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nARM_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nARM_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in notifyAboutRegionModification ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nARM_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nARM_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 9.4
void RTI::RTIambassador::deleteRegion (
  RTI::Region *theRegion) // supplied C1
throw (
  RegionNotKnown,
  RegionInUse,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(dR_s0)
                            {
                              sprintf(galMsg,"region=%s",GERTICO::ut::convert(theRegion));
                              E1mEnd(dR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RegionI *regionI = (RegionI *) theRegion;
  GeRtiFactory::GeRtiHandle regionId = regionI->id;
  RegionIMap::iterator itRI;

  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    itRI = privateRefs->regionIMap.find(regionId);
    if (itRI != privateRefs->regionIMap.end())
    {
      // Do NOT delete second!
      privateRefs->regionIMap.erase(itRI);
    }

    privateRefs->sender->deleteRegion(regionId);
    break;
  }
  catch (GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dR_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RegionNotKnown(s.c_str());
  }
  catch (GeRtiFactory::RegionInUse &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dR_ta,"RegionInUse");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RegionInUse(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in deleteRegion ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 9.5
RTI::ObjectHandle                                  // returned C3
RTI::RTIambassador::registerObjectInstanceWithRegion (
        ObjectClassHandle theClass,           // supplied C1
  const char             *theObject,          // supplied C4
        AttributeHandle   theAttributes[],    // supplied C4
        Region           *theRegions[],       // supplied C4
        ULong             theNumberOfHandles) // supplied C1
throw (
  ObjectClassNotDefined,
  ObjectClassNotPublished,
  AttributeNotDefined,
  AttributeNotPublished,
  RegionNotKnown,
  InvalidRegionContext,
  ObjectAlreadyRegistered,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rOIWR_s0)
                            {
                              sprintf(galMsg,"class=%lu,object=%s,numberOfHandles=%lu",theClass,theObject,theNumberOfHandles);
                              E1mEnd(rOIWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  CORBA::ULong i;
  GERTICO::HandleSetMap attRegMap;
  GERTICO::HandleSetMap::iterator itAttRegMap;
  RegionI *regionI;
  RTI::ObjectHandle ret = 0;
  std::string s;
  std::wstring object;
  std::wstring ws;

  for (i = 0; i < theNumberOfHandles; i++)
  {
    itAttRegMap = attRegMap.find(theAttributes[i]);
    if (itAttRegMap != attRegMap.end())
    {
      GERTICO::HandleSet *regionsPtr;

      regionsPtr = &itAttRegMap->second;
      regionI = (RegionI *) theRegions[i];
      regionsPtr->insert(regionI->id);
    }
    else
    {
      GERTICO::HandleSet regions;

      regionI = (RegionI *) theRegions[i];
      regions.insert(regionI->id);
      attRegMap[theAttributes[i]] = regions;
    }
  }

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    GERTICO::Mapper::mapWstringFromChar(object, theObject);
    ret = privateRefs->sender->registerObjectInstanceWithRegion(theClass, object, attRegMap);
    break;
  }
  catch (GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::ObjectClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"ObjectClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectClassNotPublished(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotDefined(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"AttributeNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotPublished(s.c_str());
  }
  catch (GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RegionNotKnown(s.c_str());
  }
  catch (GeRtiFactory::InvalidRegionContext &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"InvalidRegionContext");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidRegionContext(s.c_str());
  }
  catch (GeRtiFactory::ObjectAlreadyRegistered &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"ObjectAlreadyRegistered");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectAlreadyRegistered(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in registerObjectInstanceWithRegion ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rOIWR_s0)
                            {
                              sprintf(galMsg,"ret=%lu",ret);
                              E1mEnd(rOIWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

RTI::ObjectHandle                              // returned C3
RTI::RTIambassador::registerObjectInstanceWithRegion (
  ObjectClassHandle theClass,             // supplied C1
  AttributeHandle   theAttributes[],      // supplied C4
  Region           *theRegions[],         // supplied C4
  ULong             theNumberOfHandles)   // supplied C1
throw (
  ObjectClassNotDefined,
  ObjectClassNotPublished,
  AttributeNotDefined,
  AttributeNotPublished,
  RegionNotKnown,
  InvalidRegionContext,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rOIWR_s1)
                            {
                              sprintf(galMsg,"class=%lu,numberOfHandles=%lu",theClass,theNumberOfHandles);
                              E1mEnd(rOIWR_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter
  CORBA::ULong i;
  GERTICO::HandleSetMap attRegMap;
  GERTICO::HandleSetMap::iterator itAttRegMap;
  RegionI *regionI;
  RTI::ObjectHandle ret = 0;
  std::string s;
  std::wstring ws;

  for (i = 0; i < theNumberOfHandles; i++)
  {
    itAttRegMap = attRegMap.find(theAttributes[i]);
    if (itAttRegMap != attRegMap.end())
    {
      GERTICO::HandleSet *regionsPtr;

      regionsPtr = &itAttRegMap->second;
      regionI = (RegionI *) theRegions[i];
      regionsPtr->insert(regionI->id);
    }
    else
    {
      GERTICO::HandleSet regions;

      regionI = (RegionI *) theRegions[i];
      regions.insert(regionI->id);
      attRegMap[theAttributes[i]] = regions;
    }
  }

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    ret = privateRefs->sender->registerObjectInstanceWithRegion(theClass, attRegMap);
    break;
  }
  catch (GeRtiFactory::ObjectClassNotDefined &ex)
  {
                             #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
  throw ObjectClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::ObjectClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"ObjectClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectClassNotPublished(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotDefined(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"AttributeNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotPublished(s.c_str());
  }
  catch (GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RegionNotKnown(s.c_str());
  }
  catch (GeRtiFactory::InvalidRegionContext &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"InvalidRegionContext");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidRegionContext(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in registerObjectInstanceWithRegion ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rOIWR_s1)
                            {
                              sprintf(galMsg,"ret=%lu",ret);
                              E1mEnd(rOIWR_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 9.6
void RTI::RTIambassador::associateRegionForUpdates (
        Region             &theRegion,     // supplied C4
        RTI::ObjectHandle        theObject,     // supplied C1
  const AttributeHandleSet &theAttributes) // supplied C4
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  InvalidRegionContext,
  RegionNotKnown,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aRFU_s0)
                            {
                              sprintf(galMsg,"region=%s,object=%lu",GERTICO::ut::convert(&theRegion),theObject);
                              E1mEnd(aRFU_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GERTICO::HandleSetMap attRegHandles;
  GERTICO::HandleSet regions;
  RTI::ULong i;
  RTI::ULong size;
  RegionI *regionI = (RegionI *) &theRegion;
  GeRtiFactory::GeRtiHandle regionId = regionI->id;
  std::string s;
  std::wstring ws;

  regions.insert(regionId);
  size = theAttributes.size ();
  for (i = 0; i < size; i++)
  {
    attRegHandles[theAttributes.getHandle(i)] = regions;
  }

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->associateRegionForUpdates(theObject, attRegHandles);
    break;
  }
  catch (GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aRFU_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectNotKnown(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aRFU_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotDefined(s.c_str());
  }
  catch (GeRtiFactory::InvalidRegionContext &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aRFU_ta,"InvalidRegionContext");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidRegionContext(s.c_str());
  }
  catch (GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aRFU_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RegionNotKnown(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aRFU_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aRFU_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aRFU_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aRFU_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in associateRegionForUpdates ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aRFU_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aRFU_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 9.7
void RTI::RTIambassador::unassociateRegionForUpdates (
  Region       &theRegion,     // supplied C4
  RTI::ObjectHandle  theObject)     // supplied C1
throw (
  ObjectNotKnown,
  InvalidRegionContext,
  RegionNotKnown,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uRFU_s0)
                            {
                              sprintf(galMsg,"region=%s,object=%lu",GERTICO::ut::convert(&theRegion),theObject);
                              E1mEnd(uRFU_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RegionI *regionI = (RegionI *) &theRegion;
  GeRtiFactory::GeRtiHandle regionId = regionI->id;
  std::string s;
  std::wstring ws;

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->unassociateRegionForUpdates (regionId, theObject);
      break;
  }
  catch (GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uRFU_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectNotKnown(s.c_str());
  }
  catch (GeRtiFactory::InvalidRegionContext &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uRFU_ta,"InvalidRegionContext");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidRegionContext(s.c_str());
  }
  catch (GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uRFU_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RegionNotKnown(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uRFU_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uRFU_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uRFU_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uRFU_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in unassociateRegionForUpdates ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uRFU_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uRFU_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 9.8
void RTI::RTIambassador::subscribeObjectClassAttributesWithRegion (
        ObjectClassHandle   theClass,      // supplied C1
        Region             &theRegion,     // supplied C4
  const AttributeHandleSet &attributeList, // supplied C4
        Boolean        active)
throw (
  ObjectClassNotDefined,
  AttributeNotDefined,
  RegionNotKnown,
  InvalidRegionContext,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sOCAWR_s0)
                            {
                              sprintf(galMsg,"class=%lu,region=%s",theClass,GERTICO::ut::convert(&theRegion));
                              sprintf(&galMsg[strlen(galMsg)],",active=%s",GERTICO::ut::convert(active));
                              GERTICO::ut::printAttributeHandleSet(galMsg,attributeList);
                              E1mEnd(sOCAWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GERTICO::HandleSetMap attRegHandles;
  GERTICO::HandleSet regions;
  RegionI *regionI = (RegionI *) &theRegion;
  RTI::ULong i;
  RTI::ULong size;
  GeRtiFactory::GeRtiHandle regionId = regionI->id;
  bool boo = false;
  std::string s;
  std::wstring ws;

  regions.insert(regionId);
  size = attributeList.size ();
  for (i = 0; i < size; i++)
  {
    attRegHandles[attributeList.getHandle(i)] = regions;
  }

  if (active)
  {
    boo = true;
  }

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->subscribeObjectClassAttributesWithRegion(theClass, attRegHandles, boo);
    break;
  }
  catch (GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCAWR_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCAWR_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotDefined(s.c_str());
  }
  catch (GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCAWR_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RegionNotKnown(s.c_str());
  }
  catch (GeRtiFactory::InvalidRegionContext &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCAWR_ta,"InvalidRegionContext");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidRegionContext(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCAWR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCAWR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCAWR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCAWR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in subscribeObjectClassAttributesWithRegion ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCAWR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCAWR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 9.9
void RTI::RTIambassador::unsubscribeObjectClassWithRegion (
  ObjectClassHandle theClass,          // supplied C1
  Region           &theRegion)         // supplied C4
throw (
  ObjectClassNotDefined,
  RegionNotKnown,
  ObjectClassNotSubscribed,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uOCWR_s0)
                            {
                              sprintf(galMsg,"class=%lu,region=%s",theClass,GERTICO::ut::convert(&theRegion));
                              E1mEnd(uOCWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RegionI *regionI = (RegionI *) &theRegion;
  GeRtiFactory::GeRtiHandle regionId = regionI->id;
  std::string s;
  std::wstring ws;

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->unsubscribeObjectClassWithRegion (theClass, regionId);
      break;
  }
  catch (GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOCWR_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOCWR_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RegionNotKnown(s.c_str());
  }
  catch (GeRtiFactory::ObjectClassNotSubscribed &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOCWR_ta,"ObjectClassNotSubscribed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectClassNotSubscribed(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOCWR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOCWR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOCWR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOCWR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in unsubscribeObjectClassWithRegion ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOCWR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOCWR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 9.10
void RTI::RTIambassador::subscribeInteractionClassWithRegion (
  InteractionClassHandle theClass,        // supplied C1
  Region                &theRegion,       // supplied C4
  Boolean           active)
throw (
  InteractionClassNotDefined,
  RegionNotKnown,
  InvalidRegionContext,
  FederateLoggingServiceCalls,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sICWR_s0)
                            {
                              sprintf(galMsg,"class=%lu,region=%s",theClass,GERTICO::ut::convert(&theRegion));
                              sprintf(&galMsg[strlen(galMsg)],",active=%s",GERTICO::ut::convert(active));
                              E1mEnd(sICWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  bool boo = false;
  GERTICO::HandleSet regions;
  RegionI *regionI = (RegionI *) &theRegion;
  GeRtiFactory::GeRtiHandle regionId = regionI->id;
  std::string s;
  std::wstring ws;

  regions.insert(regionId);

  if (active == RTI_TRUE)
  {
    boo = true;
  }

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->subscribeInteractionClassWithRegion(theClass, regions, boo);
    break;
  }
  catch (GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sICWR_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sICWR_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RegionNotKnown(s.c_str());
  }
  catch (GeRtiFactory::InvalidRegionContext &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sICWR_ta,"InvalidRegionContext");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidRegionContext(s.c_str());
  }
  catch (GeRtiFactory::FederateLoggingServiceCalls &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sICWR_ta,"FederateLoggingServiceCalls");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateLoggingServiceCalls(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sICWR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sICWR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sICWR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sICWR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in subscribeInteractionClassWithRegion ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sICWR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sICWR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 9.11
void RTI::RTIambassador::unsubscribeInteractionClassWithRegion (
  InteractionClassHandle theClass,  // supplied C1
  Region                &theRegion) // supplied C4
throw (
  InteractionClassNotDefined,
  InteractionClassNotSubscribed,
  RegionNotKnown,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uICWR_s0)
                            {
                              sprintf(galMsg,"class=%lu,region=%s",theClass,GERTICO::ut::convert(&theRegion));
                              E1mEnd(uICWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RegionI *regionI = (RegionI *) &theRegion;
  GERTICO::HandleSet regions;
  GeRtiFactory::GeRtiHandle regionId = regionI->id;
  std::string s;
  std::wstring ws;

  regions.insert(regionId);

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->unsubscribeInteractionClassWithRegion(theClass, regions);
    break;
  }
  catch (GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uICWR_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::InteractionClassNotSubscribed &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uICWR_ta,"InteractionClassNotSubscribed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionClassNotSubscribed(s.c_str());
  }
  catch (GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uICWR_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RegionNotKnown(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uICWR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uICWR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uICWR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uICWR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in unsubscribeInteractionClassWithRegion ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uICWR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uICWR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 9.12
RTI::EventRetractionHandle                                // returned C3
RTI::RTIambassador::sendInteractionWithRegion (
        InteractionClassHandle       theInteraction, // supplied C1
  const ParameterHandleValuePairSet &theParameters,  // supplied C4
  const FedTime&                     theTime,        // supplied C4
  const char                        *theTag,         // supplied C4
  const Region                      &theRegion)      // supplied C4
throw (
  InteractionClassNotDefined,
  InteractionClassNotPublished,
  InteractionParameterNotDefined,
  InvalidFederationTime,
  RegionNotKnown,
  InvalidRegionContext,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());
  GERTICO::Mapper13::mapFedTime(*myLogicalTimeFactory, geRtiFedTime, theTime);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sIWR_s0)
                            {
                              sprintf(galMsg,"interaction=%lu,time=%s,tag=%s",theInteraction,GERTICO::ut::convertLogicalTime(*myLogicalTimeFactory, *geRtiFedTime),theTag);
                              sprintf(&galMsg[strlen(galMsg)],",region=%s",GERTICO::ut::convert(&theRegion));
                              GERTICO::ut::printParameterHandleValuePairSet(galMsg,theParameters);
                              E1mEnd(sIWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GERTICO::HandleSet regions;
  GeRtiFactory::HandleValues handleValues;
  GeRtiFactory::ERHandle erHandle;
  GeRtiFactory::UserSuppliedTag tag;
  RTI::EventRetractionHandle ret;
  RegionI *regionI = (RegionI *) &theRegion;
  GeRtiFactory::GeRtiHandle regionId = regionI->id;
  std::string s;
  std::wstring ws;

  GERTICO::Mapper13::mapParameterHandleValuePairSet(handleValues, theParameters);
  GERTICO::Mapper::mapUserSuppliedTag(tag, theTag);
  regions.insert(regionId);

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    erHandle = privateRefs->sender->sendInteractionWithRegion(theInteraction, handleValues, *geRtiFedTime, tag, regions);
    GERTICO::Mapper13::mapEventRetractionHandle(ret, erHandle);
    break;
  }
  catch (GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::InteractionClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"InteractionClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionClassNotPublished(s.c_str());
  }
  catch (GeRtiFactory::InteractionParameterNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"InteractionParameterNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionParameterNotDefined(s.c_str());
  }
  catch (GeRtiFactory::InvalidFederationTime &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidFederationTime(s.c_str());
  }
  catch (GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RegionNotKnown(s.c_str());
  }
  catch (GeRtiFactory::InvalidRegionContext &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"InvalidRegionContext");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidRegionContext(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in sendInteractionWithRegion ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sIWR_s0)
                            {
                              sprintf(galMsg,"ret=%lu",ret);
                              E1mEnd(sIWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

void RTI::RTIambassador::sendInteractionWithRegion (
        InteractionClassHandle       theInteraction, // supplied C1
  const ParameterHandleValuePairSet &theParameters,  // supplied C4
  const char                        *theTag,         // supplied C4
  const Region                      &theRegion)      // supplied C4
throw (
  InteractionClassNotDefined,
  InteractionClassNotPublished,
  InteractionParameterNotDefined,
  RegionNotKnown,
  InvalidRegionContext,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sIWR_s1)
                            {
                              sprintf(galMsg,"interaction=%lu,tag=%s",theInteraction,theTag);
                              sprintf(&galMsg[strlen(galMsg)],",region=%s",GERTICO::ut::convert(&theRegion));
                              GERTICO::ut::printParameterHandleValuePairSet(galMsg,theParameters);
                              E1mEnd(sIWR_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GERTICO::HandleSet regions;
  GeRtiFactory::HandleValues handleValues;
  GeRtiFactory::UserSuppliedTag tag;
  RegionI *regionI = (RegionI *) &theRegion;
  GeRtiFactory::GeRtiHandle regionId = regionI->id;
  std::string s;
  std::wstring ws;

  GERTICO::Mapper13::mapParameterHandleValuePairSet(handleValues, theParameters);
  GERTICO::Mapper::mapUserSuppliedTag(tag, theTag);
  regions.insert(regionId);

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->sendInteractionWithRegion(theInteraction, handleValues, tag, regions);
    break;
  }
  catch (GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::InteractionClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"InteractionClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionClassNotPublished(s.c_str());
  }
  catch (GeRtiFactory::InteractionParameterNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"InteractionParameterNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionParameterNotDefined(s.c_str());
  }
  catch (GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RegionNotKnown(s.c_str());
  }
  catch (GeRtiFactory::InvalidRegionContext &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"InvalidRegionContext");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InvalidRegionContext(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in sendInteractionWithRegion ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 9.13
void RTI::RTIambassador::requestClassAttributeValueUpdateWithRegion (
        ObjectClassHandle   theClass,      // supplied C1
  const AttributeHandleSet &theAttributes, // supplied C4
  const Region             &theRegion)     // supplied C4
throw (
  ObjectClassNotDefined,
  AttributeNotDefined,
  RegionNotKnown,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rCAVUWR_s0)
                            {
                              sprintf(galMsg,"class=%lu,region=%s",theClass,GERTICO::ut::convert(&theRegion));
                              E1mEnd(rCAVUWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GERTICO::HandleSetMap attRegHandles;
  GeRtiFactory::UserSuppliedTag tag;
  RegionI *regionI = (RegionI *) &theRegion;
  GeRtiFactory::GeRtiHandle regionId = regionI->id;
  GERTICO::HandleSet regions;
  RTI::ULong i;
  RTI::ULong size;
  std::string s;
  std::wstring ws;

  regions.insert(regionId);

  size = theAttributes.size ();
  for (i = 0; i < size; i++)
  {
    attRegHandles[theAttributes.getHandle(i)] = regions;
  }

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->requestClassAttributeValueUpdateWithRegion(theClass, attRegHandles, tag);
    break;
  }
  catch (GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVUWR_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVUWR_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotDefined(s.c_str());
  }
  catch (GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVUWR_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RegionNotKnown(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVUWR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVUWR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVUWR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVUWR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in requestClassAttributeValueUpdateWithRegion ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVUWR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVUWR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

//////////////////////////
// RTI Support Services //
//////////////////////////

// 10.2
RTI::ObjectClassHandle      // returned C3
RTI::RTIambassador::getObjectClassHandle (
  const char *theName) // supplied C4
throw (
  NameNotFound,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gOCH_s0)
                            {
                              sprintf(galMsg,"name=%s",theName);
                              E1mEnd(gOCH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::ObjectClassHandle ret;
  std::string s;
  std::wstring name;
  std::wstring ws;

  GERTICO::Mapper::mapWstringFromChar(name, theName);
  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    ret = privateRefs->sender->getObjectClassHandle(name);
      break;
  }
  catch (GeRtiFactory::NameNotFound &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOCH_ta,"NameNotFound");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw NameNotFound(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOCH_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOCH_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in getObjectClassHandle ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOCH_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOCH_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gOCH_s0)
                            {
                              sprintf(galMsg,"ret=%lu",ret);
                              E1mEnd(gOCH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.3
char *                         // returned C6
RTI::RTIambassador::getObjectClassName (
  ObjectClassHandle theHandle) // supplied C1
throw (
  ObjectClassNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gOCN_s0)
                            {
                              sprintf(galMsg,"handle=%lu",theHandle);
                              E1mEnd(gOCN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  char *ret;
  std::string s;
  std::wstring ws;

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    ws = privateRefs->sender->getObjectClassName(theHandle);
    GERTICO::Mapper::mapStringFromWstring(s, ws);
    ret = strdup(s.c_str());
      break;
  }
  catch (GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOCN_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOCN_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOCN_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in getObjectClassName ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOCN_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOCN_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gOCN_s0)
                            {
                              sprintf(galMsg,"ret=%s",ret);
                              E1mEnd(gOCN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.4
RTI::AttributeHandle                       // returned C3
RTI::RTIambassador::getAttributeHandle (
  const char             *theName,    // supplied C4
        ObjectClassHandle whichClass) // supplied C1
throw (
  ObjectClassNotDefined,
  NameNotFound,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gAH_s0)
                            {
                              sprintf(galMsg,"name=%s,class=%lu",theName,whichClass);
                              E1mEnd(gAH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::AttributeHandle ret;
  std::wstring name;
  std::string s;
  std::wstring ws;

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  GERTICO::Mapper::mapWstringFromChar(name, theName);
  try
  {
    ret = privateRefs->sender->getAttributeHandle(name, whichClass);
      break;
  }
  catch (GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gAH_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::NameNotFound &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gAH_ta,"NameNotFound");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw NameNotFound(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gAH_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gAH_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in getAttributeHandle ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gAH_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gAH_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gAH_s0)
                            {
                              sprintf(galMsg,"ret=%lu",ret);
                              E1mEnd(gAH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.5
char *                          // returned C6
RTI::RTIambassador::getAttributeName (
  AttributeHandle   theHandle,  // supplied C1
  ObjectClassHandle whichClass) // supplied C1
throw (
  ObjectClassNotDefined,
  AttributeNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gAN_s0)
                            {
                              sprintf(galMsg,"handle=%lu,class=%lu",theHandle,whichClass);
                              E1mEnd(gAN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  char *ret;
  std::string s;
  std::wstring ws;

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    ws = privateRefs->sender->getAttributeName (theHandle, whichClass);
    GERTICO::Mapper::mapStringFromWstring(s, ws);
    ret = strdup(s.c_str());
      break;
  }
  catch (GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gAN_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gAN_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotDefined(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gAN_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gAN_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in getAttributeName ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gAN_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gAN_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gAN_s0)
                            {
                              sprintf(galMsg,"ret=%s",ret);
                              E1mEnd(gAN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.6
RTI::InteractionClassHandle      // returned C3
RTI::RTIambassador::getInteractionClassHandle (
  const char *theName)      // supplied C4
throw (
  NameNotFound,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gICH_s0)
                            {
                              sprintf(galMsg,"name=%s",theName);
                              E1mEnd(gICH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::InteractionClassHandle ret;
  std::wstring name;
  std::string s;
  std::wstring ws;

  GERTICO::Mapper::mapWstringFromChar(name, theName);
  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    ret = privateRefs->sender->getInteractionClassHandle(name);
      break;
  }
  catch (GeRtiFactory::NameNotFound &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gICH_ta,"NameNotFound");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw NameNotFound(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gICH_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gICH_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in getInteractionClassHandle ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gICH_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gICH_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gICH_s0)
                            {
                              sprintf(galMsg,"ret=%lu",ret);
                              E1mEnd(gICH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.7
char *                              // returned C6
RTI::RTIambassador::getInteractionClassName (
  InteractionClassHandle theHandle) // supplied C1
throw (
  InteractionClassNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gICN_s0)
                            {
                              sprintf(galMsg,"handle=%lu",theHandle);
                              E1mEnd(gICN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  char *ret;
  std::string s;
  std::wstring ws;

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    ws = privateRefs->sender->getInteractionClassName (theHandle);
    GERTICO::Mapper::mapStringFromWstring(s, ws);
    ret = strdup(s.c_str());
      break;
  }
  catch (GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gICN_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gICN_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gICN_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in getInteractionClassName ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gICN_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gICN_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gICN_s0)
                            {
                              sprintf(galMsg,"ret=%s",ret);
                              E1mEnd(gICN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.8
RTI::ParameterHandle                            // returned C3
RTI::RTIambassador::getParameterHandle (
  const char *theName,                     // supplied C4
        InteractionClassHandle whichClass) // supplied C1
throw (
  InteractionClassNotDefined,
  NameNotFound,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gPH_s0)
                            {
                              sprintf(galMsg,"name=%s,class=%lu",theName,whichClass);
                              E1mEnd(gPH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::ParameterHandle ret;
  std::wstring name;
  std::string s;
  std::wstring ws;

  GERTICO::Mapper::mapWstringFromChar(name, theName);
  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    ret = privateRefs->sender->getParameterHandle(name, whichClass);
      break;
  }
  catch (GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gPH_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::NameNotFound &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gPH_ta,"NameNotFound");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw NameNotFound(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gPH_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gPH_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in getParameterHandle ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gPH_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gPH_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gPH_s0)
                            {
                              sprintf(galMsg,"ret=%lu",ret);
                              E1mEnd(gPH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.9
char *                               // returned C6
RTI::RTIambassador::getParameterName (
  ParameterHandle        theHandle,  // supplied C1
  InteractionClassHandle whichClass) // supplied C1
throw (
  InteractionClassNotDefined,
  InteractionParameterNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gPN_s0)
                            {
                              sprintf(galMsg,"class=%lu",whichClass);
                              E1mEnd(gPN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  char *ret;
  std::string s;
  std::wstring ws;

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    ws = privateRefs->sender->getParameterName (theHandle, whichClass);
    GERTICO::Mapper::mapStringFromWstring(s, ws);
    ret = strdup(s.c_str());
      break;
  }
  catch (GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gPN_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::InteractionParameterNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gPN_ta,"InteractionParameterNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionParameterNotDefined(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gPN_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gPN_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in getParameterName ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gPN_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gPN_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gPN_s0)
                            {
                              sprintf(galMsg,"ret=%s",ret);
                              E1mEnd(gPN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.10
RTI::ObjectHandle                 // returned C3
RTI::RTIambassador::getObjectInstanceHandle (
  const char *theName)       // supplied C4
throw (
    ObjectNotKnown,
    FederateNotExecutionMember,
    ConcurrentAccessAttempted,
    RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gOIH_s0)
                            {
                              sprintf(galMsg,"name=%s",theName);
                              E1mEnd(gOIH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::ObjectHandle ret;
  std::wstring name;
  std::string s;
  std::wstring ws;

  GERTICO::Mapper::mapWstringFromChar(name, theName);
  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    ret = privateRefs->sender->getObjectInstanceHandle(name);
      break;
  }
  catch (GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOIH_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectNotKnown(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOIH_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOIH_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in getObjectInstanceHandle ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOIH_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOIH_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gOIH_s0)
                            {
                              sprintf(galMsg,"ret=%lu",ret);
                              E1mEnd(gOIH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.11
char *                     // returned C6
RTI::RTIambassador::getObjectInstanceName (
  RTI::ObjectHandle theHandle)  // supplied C1
throw (
  ObjectNotKnown,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gOIN_s0)
                            {
                              sprintf(galMsg,"handle=%lu",theHandle);
                              E1mEnd(gOIN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  char *ret;
  std::string s;
  std::wstring ws;

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    ws = privateRefs->sender->getObjectInstanceName(theHandle);
    GERTICO::Mapper::mapStringFromWstring(s, ws);
    ret = strdup(s.c_str());
      break;
  }
  catch (GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOIN_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectNotKnown(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOIN_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOIN_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in getObjectInstanceName ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOIN_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOIN_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gOIN_s0)
                            {
                              sprintf(galMsg,"ret=%s",ret);
                              E1mEnd(gOIN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.12
RTI::SpaceHandle                // returned C3
RTI::RTIambassador::getRoutingSpaceHandle (
  const char *theName)     // supplied C4
throw (
  NameNotFound,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gRSH_s0)
                            {
                              sprintf(galMsg,"name=%s",theName);
                              E1mEnd(gRSH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::SpaceHandle ret = 0;
  std::wstring name;
  std::string s;
  std::wstring ws;

  GERTICO::Mapper::mapWstringFromChar(name, theName);
  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    ret = privateRefs->sender->getRoutingSpaceHandle(name);
      break;
  }
  catch (GeRtiFactory::NameNotFound &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gRSH_ta,"NameNotFound");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw NameNotFound(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gRSH_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gRSH_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in getRoutingSpaceHandle ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gRSH_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gRSH_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gRSH_s0)
                            {
                              sprintf(galMsg,"ret=%ld",ret);
                              E1mEnd(gRSH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.13
char *                         // returned C6
RTI::RTIambassador::getRoutingSpaceName (
   //
   // This const was removed for the RTI 1.3 NG to work around a limitation of
   // the Sun 4.2 C++ compiler regarding template instantiation.  The const
   // is unnecessary.
   //
   /* const */ SpaceHandle theHandle) // supplied C4
throw (
  SpaceNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gRSN_s0)
                            {
                              sprintf(galMsg,"handle=%ld",theHandle);
                              E1mEnd(gRSN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  char *ret = NULL;
  std::string s;
  std::wstring ws;

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    ws = privateRefs->sender->getRoutingSpaceName(theHandle);
    GERTICO::Mapper::mapStringFromWstring(s, ws);
    ret = strdup(s.c_str());
      break;
  }
  catch (GeRtiFactory::SpaceNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gRSN_ta,"SpaceNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SpaceNotDefined(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gRSN_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gRSN_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in getRoutingSpaceName ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gRSN_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gRSN_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gRSN_s0)
                            {
                              sprintf(galMsg,"ret=%s",ret);
                              E1mEnd(gRSN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.14
RTI::DimensionHandle                   // returned C3
RTI::RTIambassador::getDimensionHandle (
  const char         *theName,    // supplied C4
        SpaceHandle   whichSpace) // supplied C1
throw (
  SpaceNotDefined,
  NameNotFound,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gDH_s0)
                            {
                              sprintf(galMsg,"name=%s,space=%ld",theName,whichSpace);
                              E1mEnd(gDH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::DimensionHandle ret = 0;
  std::wstring name;
  std::string s;
  std::wstring ws;

  GERTICO::Mapper::mapWstringFromChar(name, theName);
  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    ret = privateRefs->sender->getDimensionHandle(name, whichSpace);
      break;
  }
  catch (GeRtiFactory::SpaceNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gDH_ta,"SpaceNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SpaceNotDefined(s.c_str());
  }
  catch (GeRtiFactory::NameNotFound &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gDH_ta,"NameNotFound");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw NameNotFound(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gDH_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gDH_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in getDimensionHandle ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gDH_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gDH_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gDH_s0)
                            {
                              sprintf(galMsg,"ret=%lu",ret);
                              E1mEnd(gDH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.15
char *                        // returned C6
RTI::RTIambassador::getDimensionName (
  DimensionHandle theHandle,  // supplied C1
  SpaceHandle     whichSpace) // supplied C1
throw (
  SpaceNotDefined,
  DimensionNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gDN_s0)
                            {
                              sprintf(galMsg,"handle=%lu,space=%ld",theHandle,whichSpace);
                              E1mEnd(gDN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  char *ret = NULL;
  std::string s;
  std::wstring ws;

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    ws = privateRefs->sender->getDimensionName(theHandle, whichSpace);
    GERTICO::Mapper::mapStringFromWstring(s, ws);
    ret = strdup(s.c_str());
      break;
  }
  catch (GeRtiFactory::SpaceNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gDN_ta,"SpaceNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SpaceNotDefined(s.c_str());
  }
  catch (GeRtiFactory::DimensionNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gDN_ta,"DimensionNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw DimensionNotDefined(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gDN_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gDN_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in getDimensionName ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gDN_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gDN_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gDN_s0)
                            {
                              sprintf(galMsg,"ret=%s",ret);
                              E1mEnd(gDN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.16
RTI::SpaceHandle                      // returned C3
RTI::RTIambassador::getAttributeRoutingSpaceHandle (
  AttributeHandle   theHandle,   // supplied C1
  ObjectClassHandle whichClass)  // supplied C1
throw (
  ObjectClassNotDefined,
  AttributeNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gARSH_s0)
                            {
                              sprintf(galMsg,"handle=%lu,class=%lu",theHandle,whichClass);
                              E1mEnd(gARSH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::SpaceHandle ret = 0;
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    ret = privateRefs->sender->getAttributeRoutingSpaceHandle (theHandle, whichClass);
      break;
  }
  catch (GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gARSH_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gARSH_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw AttributeNotDefined(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gARSH_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gARSH_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in getAttributeRoutingSpaceHandle ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gARSH_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gARSH_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gARSH_s0)
                            {
                              sprintf(galMsg,"ret=%ld",ret);
                              E1mEnd(gARSH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.17
RTI::ObjectClassHandle            // returned C3
RTI::RTIambassador::getObjectClass (
  RTI::ObjectHandle theObject)    // supplied C1
throw (
  ObjectNotKnown,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gOC_s0)
                            {
                              sprintf(galMsg,"object=%lu",theObject);
                              E1mEnd(gOC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::ObjectClassHandle ret = 0;
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    ret = privateRefs->sender->getObjectClass (theObject);
      break;
  }
  catch (GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOC_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ObjectNotKnown(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in getObjectClass ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gOC_s0)
                            {
                              sprintf(galMsg,"ret=%lu",ret);
                              E1mEnd(gOC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.18
RTI::SpaceHandle                             // returned C3
RTI::RTIambassador::getInteractionRoutingSpaceHandle (
  InteractionClassHandle   theHandle)   // supplied C1
throw (
  InteractionClassNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gIRSH_s0)
                            {
                              sprintf(galMsg,"handle=%lu",theHandle);
                              E1mEnd(gIRSH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::SpaceHandle ret = 0;
  std::string s;
  std::wstring ws;

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    ret = privateRefs->sender->getInteractionRoutingSpaceHandle (theHandle);
      break;
  }
  catch (GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gIRSH_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw InteractionClassNotDefined(s.c_str());
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gIRSH_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gIRSH_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in getInteractionRoutingSpaceHandle ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gIRSH_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gIRSH_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gIRSH_s0)
                            {
                              sprintf(galMsg,"ret=%ld",ret);
                              E1mEnd(gIRSH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.19
RTI::TransportationHandle      // returned C3
RTI::RTIambassador::getTransportationHandle (
  const char *theName)    // supplied C4
throw (
  NameNotFound,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
  RTI::TransportationHandle transportationHandle = 0;
  bool nameFound = false;
  std::string name = theName;

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gTH_s0)
                            {
                              sprintf(galMsg,"name=%s",theName);
                              E1mEnd(gTH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  if (privateRefs->sender->isJoined() == false)
  {
    throw FederateNotExecutionMember("");
  }

  GERTICO::Mapper::nameToLower(name);
  if (name == "reliable")
  {
    nameFound = true;
    transportationHandle = 0;
  }

  if (name == "best_effort")
  {
    nameFound = true;
    transportationHandle = 1;
  }

  if (nameFound == false)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gTH_ta,"NameNotFound");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw NameNotFound("getTransportationHandle");
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gTH_s0)
                            {
                              unsigned long ul;

                              ul = transportationHandle;
                              sprintf(galMsg,"transportationHandle=%lu",ul);
                              E1mEnd(gTH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  return transportationHandle;
}

// 10.20
char *                            // returned C6
RTI::RTIambassador::getTransportationName (
  TransportationHandle theHandle) // supplied C1
throw (
  InvalidTransportationHandle,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gTN_s0)
                            {
                              sprintf(galMsg,"handle=%lu",theHandle);
                              E1mEnd(gTN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  char *ret = NULL;

  if (privateRefs->sender->isJoined() == false)
  {
    throw FederateNotExecutionMember("");
  }

  if (theHandle == 0)
  {
    ret = strdup("reliable");
  }
  if (theHandle == 1)
  {
    ret = strdup("best_effort");
  }

  if (ret == NULL)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gTN_ta,"InvalidTransportationHandle");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw InvalidTransportationHandle("getTransportationName");
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gTN_s0)
                            {
                              sprintf(galMsg,"ret=%s",ret);
                              E1mEnd(gTN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.21
RTI::OrderingHandle         // returned C3
RTI::RTIambassador::getOrderingHandle (
  const char *theName) // supplied C4
throw (
  NameNotFound,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
  RTI::OrderingHandle ret = 0;
  bool nameFound = false;
  std::string name = theName;

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gOH_s0)
                            {
                              sprintf(galMsg,"name=%s",theName);
                              E1mEnd(gOH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  if (privateRefs->sender->isJoined() == false)
  {
    throw FederateNotExecutionMember("");
  }

  GERTICO::Mapper::nameToLower(name);
  if (name == "receive")
  {
    nameFound = true;
    ret = 0;
  }

  if (name == "timestamp")
  {
    nameFound = true;
    ret = 1;
  }


  if (nameFound == false)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOH_ta,"NameNotFound");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw NameNotFound("getOrderingHandle");
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gOH_s0)
                            {
                              unsigned long ul;

                              ul = ret;
                              sprintf(galMsg,"ret=%lu",ul);
                              E1mEnd(gOH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.22
char *                      // returned C6
RTI::RTIambassador::getOrderingName (
  OrderingHandle theHandle) // supplied C1
throw (
  InvalidOrderingHandle,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gON_s0)
                            {
                              sprintf(galMsg,"handle=%lu",theHandle);
                              E1mEnd(gON_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  char *ret = NULL;

  if (privateRefs->sender->isJoined() == false)
  {
    throw FederateNotExecutionMember("");
  }

  if (theHandle == 0)
  {
    ret = strdup("receive");
  }
  if (theHandle == 1)
  {
    ret = strdup("timestamp");
  }

  if (ret == NULL)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gON_ta,"InvalidOrderingHandle");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw InvalidOrderingHandle("getOrderingName");
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gON_s0)
                            {
                              sprintf(galMsg,"ret=%s",ret);
                              E1mEnd(gON_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.23
void RTI::RTIambassador::enableClassRelevanceAdvisorySwitch()
throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(eCRAS_s0);
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->enableClassRelevanceAdvisorySwitch ();
      break;
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in enableClassRelevanceAdvisorySwitch ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 10.24
void RTI::RTIambassador::disableClassRelevanceAdvisorySwitch()
throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(dCRAS_s0);
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->disableClassRelevanceAdvisorySwitch ();
      break;
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in disableClassRelevanceAdvisorySwitch ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 10.25
void RTI::RTIambassador::enableAttributeRelevanceAdvisorySwitch()
throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(eARAS_s0);
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->enableAttributeRelevanceAdvisorySwitch ();
      break;
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eARAS_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eARAS_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eARAS_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eARAS_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in enableAttributeRelevanceAdvisorySwitch ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eARAS_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eARAS_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 10.26
void RTI::RTIambassador::disableAttributeRelevanceAdvisorySwitch()
throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(dARAS_s0);
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->disableAttributeRelevanceAdvisorySwitch ();
      break;
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dARAS_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dARAS_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dARAS_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dARAS_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in disableAttributeRelevanceAdvisorySwitch ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dARAS_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dARAS_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 10.27
void RTI::RTIambassador::enableAttributeScopeAdvisorySwitch()
throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(eASAS_s0);
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->enableAttributeScopeAdvisorySwitch ();
      break;
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eASAS_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eASAS_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eASAS_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eASAS_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in enableAttributeScopeAdvisorySwitch ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eASAS_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eASAS_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 10.28
void RTI::RTIambassador::disableAttributeScopeAdvisorySwitch()
throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(dASAS_s0);
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->disableAttributeScopeAdvisorySwitch ();
      break;
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dASAS_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dARAS_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dARAS_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dASAS_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in disableAttributeScopeAdvisorySwitch ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dARAS_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dARAS_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 10.29
void RTI::RTIambassador::enableInteractionRelevanceAdvisorySwitch()
throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(eIRAS_s0);
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->enableInteractionRelevanceAdvisorySwitch ();
      break;
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eIRAS_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eIRAS_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eIRAS_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eIRAS_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in enableInteractionRelevanceAdvisorySwitch ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eIRAS_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eIRAS_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

// 10.30
void RTI::RTIambassador::disableInteractionRelevanceAdvisorySwitch()
throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(dIRAS_s0);
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::string s;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    privateRefs->sender->disableInteractionRelevanceAdvisorySwitch ();
      break;
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dIRAS_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dIRAS_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw SaveInProgress(s.c_str());
  }
  catch (GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dIRAS_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RestoreInProgress(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dIRAS_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTIinternalError(s.c_str());
  }
  catch (CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
ACE_PRINT_EXCEPTION (sysex, "System Exception in disableInteractionRelevanceAdvisorySwitch ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dIRAS_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("CORBA::SystemException");
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dIRAS_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTIinternalError ("unknown Exception");
  }
  }
}

//
RTI::Boolean // returned C3
RTI::RTIambassador::tick ()
throw (
  SpecifiedSaveLabelDoesNotExist,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E0(t_e);   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  CORBA::Boolean b;
  RTI::Boolean ret = RTI_FALSE;

  try
  {
    b = privateRefs->sender->tick ();
  }
  catch (...)
  {
  }

  if (b == 1)
  {
    ret = RTI_TRUE;
  }

  return ret;
}

RTI::Boolean             // returned C3
RTI::RTIambassador::tick (
  TickTime minimum, // supplied C1
  TickTime maximum) // supplied C1
throw (
  SpecifiedSaveLabelDoesNotExist,
  ConcurrentAccessAttempted,
  RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E0(t_e);   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  CORBA::Boolean b = 0;
  RTI::Boolean ret = RTI_FALSE;

  try
  {
    b = privateRefs->sender->tick (minimum, maximum);
  }
  catch (...)
  {
  }

  if (b == 1)
  {
    ret = RTI_TRUE;
  }

  return ret;
}

RTI::RTIambassador::RTIambassador()
throw (
  RTI::MemoryExhausted,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E0(RTI_e);   // inserted by Gal converter
                           #endif   // inserted by Gal converter

  try
  {
    privateRefs = new RTIambPrivateRefs();
    privateRefs->receiverI = new GERTICO::ReceiverI();
    privateRefs->sender = new NAMESPACE::Sender(privateRefs->receiverI);
  }
  catch (...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(RTI_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError("init failed");
  }

}

RTI::RTIambassador::~RTIambassador()
throw (RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E0(RTI_e);   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  clear(privateRefs->regionIMap);
  delete privateRefs->sender;
  delete privateRefs->receiverI;
  delete privateRefs;
}

RTI::RegionToken
RTI::RTIambassador::getRegionToken(
  Region *theRegion)
throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RegionNotKnown,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(gRT_e);
                           #endif   // inserted by Gal converter
  RTI::RegionToken ret = 0;
  std::string s;
  std::wstring ws;

  try
  {
    ret = getRegionTokenI(theRegion);
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw ConcurrentAccessAttempted(s.c_str());
  }
  catch (GeRtiFactory::RegionNotKnown &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RegionNotKnown(s.c_str());
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTI::RTIinternalError(s.c_str());
  }

  return ret;
}

RTI::Region *
RTI::RTIambassador::getRegion(
  RegionToken theToken)
throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RegionNotKnown,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(gR_e);
                           #endif   // inserted by Gal converter
  GeRtiFactory::Extents extents;
  GeRtiFactory::GeRtiHandle space;
  RTI::Region *ret = NULL;
  std::string s;
  std::wstring ws;

  try
  {
    ret = getRegionI(theToken, privateRefs->regionIMap);
  }
  catch (GeRtiFactory::FederateNotExecutionMember &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw FederateNotExecutionMember(s.c_str());
  }
  catch (GeRtiFactory::RegionNotKnown &)
  {
    try
    {
      privateRefs->sender->getExtents(theToken, space, extents);
      loadRegion(space, theToken, extents, privateRefs->regionIMap);
      ret = getRegionI(theToken, privateRefs->regionIMap);
    }
    catch (GeRtiFactory::FederateNotExecutionMember &ex)
    {
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
      throw FederateNotExecutionMember(s.c_str());
    }
    catch (GeRtiFactory::RTIinternalError &ex)
    {
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      GERTICO::Mapper::mapStringFromWstring(s, ws);
      throw RTI::RTIinternalError(s.c_str());
    }
  }
  catch (GeRtiFactory::RTIinternalError &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    GERTICO::Mapper::mapStringFromWstring(s, ws);
    throw RTI::RTIinternalError(s.c_str());
  }

  return ret;
}
