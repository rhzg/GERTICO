/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** GeRtiFactoryI.cpp
**
*******************************************************************************/

#include <vector>
#include "ace/Thread_Manager.h"
#include "GeRtiFactoryECI.h"
#include "Util/GeRtiOrb.h"
#include "Util/Mapper.h"
#include "Util/NextHandle.h"

/********************************* Gal begin *********************************/   // inserted by Gal converter
#ifdef GalDebug   // inserted by Gal converter
#include "Gal/StdAfx.h"   // inserted by Gal converter
#include "Gal/repository_l.h"   // inserted by Gal converter
#include "Gal/event.h"   // inserted by Gal converter
static class Repository_l *FM=(Repository::getSingleInstance())->getRepository_l("GeRtiFM.res","GeRtiFM");

static class Event *GeRti_FM_feds_i=FM->getRefEvent("GeRti_FM_feds_i");
static class Event *GeRti_FM_d=FM->getRefEvent("GeRti_FM_d");
static class Event *GeRti_FM_e=FM->getRefEvent("GeRti_FM_e");
static class Event *GeRti_FM_w=FM->getRefEvent("GeRti_FM_w");
#endif   // inserted by Gal converter
/*********************************** Gal end *********************************/   // inserted by Gal converter

#define MAX_TXT 1024
static char galMsg[MAX_TXT];

ACE_Semaphore *psCleanHub = NULL;
bool cleanRunningHub = false;
static unsigned int GERTICO_POA_counter = 0;

ACE_Thread_Mutex GeRtiFactory_TheEventHubFederationFactoryEC_i::spm;
FederationManagementECMap GeRtiFactory_TheEventHubFederationFactoryEC_i::federationManagementECs;
std::vector <GERTICO::FederationManagementEC *>deleteFedManVector;

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void *clean_up_hub(void *arg)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "clean_up_hub", "Enter");
                           #endif   // inserted by Gal converter
  while(1)
  {
    if (psCleanHub->acquire() == -1)
    {
      // Do not have the semaphore: error.
      ACE_OS::sleep(1);
                           {   // inserted by Gal converter
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_e, "clean_up_hub", "semaphore problem");
                           #endif   // inserted by Gal converter
      return NULL;
                           }   // inserted by Gal converter
    }

    GeRtiFactory_TheEventHubFederationFactoryEC_i::spm.acquire();
    GeRtiFactory_TheEventHubFederationFactoryEC_i::spm.release();
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "clean_up_hub", "Leave");
                           #endif   // inserted by Gal converter
  return NULL;
}

// ---------------------------------------------------------------------------
// A thread to process work on a regular one second granularity wall clock
// time. eg. thread to watch for time management inactivity or mom management.
// ---------------------------------------------------------------------------
void *wallClockWorker_hub(void *arg)
{
  GERTICO::FederationManagementEC *federationManagementEC = (GERTICO::FederationManagementEC *) arg;

  while (federationManagementEC->notDone)
  {
    federationManagementEC->wallClockWorker();

    // Granularity of one second.
    ACE_OS::sleep(1);
  }

  return NULL;
}

// ---------------------------------------------------------------------------
// Implementation skeleton constructor
// ---------------------------------------------------------------------------
GeRtiFactory_TheEventHubFederationFactoryEC_i::GeRtiFactory_TheEventHubFederationFactoryEC_i(std::wstring const &theHubName, GERTICO::GeRtiOrb &theGeRtiOrb, GERTICOconf const &theGERTICOconf, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory) : geRtiFedTimeFactory(theGeRtiFedTimeFactory), geRtiLogicalTimeIntervalFactory(theGeRtiLogicalTimeIntervalFactory), myGeRtiOrb(theGeRtiOrb), conf(theGERTICOconf)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "GeRtiFactory_Factory_i", "Enter");
                           #endif   // inserted by Gal converter
  createInProgress = false;
  myEventHub = theHubName;
  if (cleanRunningHub == false)
  {
    psCleanHub = new ACE_Semaphore(0);
    ACE_Thread_Manager::instance()->spawn(ACE_reinterpret_cast(ACE_THR_FUNC, &clean_up_hub), NULL);
    cleanRunningHub = true;
  }

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "GeRtiFactory_Factory_i", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// Implementation skeleton destructor
// ---------------------------------------------------------------------------
GeRtiFactory_TheEventHubFederationFactoryEC_i::~GeRtiFactory_TheEventHubFederationFactoryEC_i(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "~GeRtiFactory_Factory_i", "Enter");
                           #endif   // inserted by Gal converter
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "~GeRtiFactory_Factory_i", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_TheEventHubFederationFactoryEC_i::createFederationExecution(CORBA::WChar const *fedName,
    GeRtiFactory::GeRtiHandle momInteractionRoot,
    GeRtiFactory::GeRtiHandle momObjectRoot,
    GeRtiFactory::GeRtiHandle interactionRoot,
    GeRtiFactory::GeRtiHandle objectRoot,
    GeRtiFactory::GeRtiHandle privilegeToDeleteId,
    GeRtiFactory::EventHubFederation_out theEventHubFederation,
    GeRtiFactory::EventChannel_out theEventChannelReference)
throw
(
  GeRtiFactory::FederationExecutionAlreadyExists,
  GeRtiFactory::RTIinternalError,
  CORBA::SystemException
)
{
  std::string fedNameString;
  std::wstring fedNameWstring;
  GERTICO::Mapper::mapWstringFromWchar(fedNameWstring, fedName);
  GERTICO::Mapper::mapStringFromWstring(fedNameString, fedNameWstring);
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_feds_i)
                            {
                              sprintf(galMsg,"federateName=%ls", fedName);
                              E2(GeRti_FM_feds_i, "createFederationExecution", galMsg);
                            }
                           #endif   // inserted by Gal converter
  FederationManagementECMap::iterator i;
  GERTICO::FederationManagementEC *currFederationManagementEC;
  char name[1024];
  size_t size;
  CORBA::WChar *wChar = L"createFederationExecution";

  name[0] = '\0';
  sscanf(fedNameString.c_str(), "%s", name);
  if (name[0] == '\0')
  {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_w)
                            {
                              sprintf(galMsg,"federationNameMissing");
                              E2(GeRti_FM_w, "createFederationExecution", galMsg);
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::RTIinternalError(L"createFederationExecution: federation name missing");
  }

  spm.acquire();
  if (createInProgress == true)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_w)
                            {
                             E2(GeRti_FM_w, "createFederationExecution", "ConcurrentAccessAttempted");
                            }
                           #endif   // inserted by Gal converter
    spm.release();
    throw GeRtiFactory::ConcurrentAccessAttempted(L"createFederationExecution");
  }
  createInProgress = true;
  spm.release();

  try
  {
    // Allocate new federation and read fed file.
    std::wstring ff;
//    GERTICO::Mapper::mapWstringFromWchar(ff, fedFile);
    spm.acquire();
    size = federationManagementECs.size();
    i = federationManagementECs.find(fedNameWstring);
    if (i != federationManagementECs.end())
    {
      currFederationManagementEC = i->second;
      if (currFederationManagementEC->isActive())
      {
        createInProgress = false;
        spm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_w)
                            {
                             sprintf(galMsg,"FederationExecutionAlreadyExists:federateName=%ls,fedFile=%ls", fedNameWstring.c_str(), ff.c_str());
                             E2(GeRti_FM_w, "createFederationExecution", galMsg);
                            }
                           #endif   // inserted by Gal converter
        throw GeRtiFactory::FederationExecutionAlreadyExists(wChar);
      }
      // Allow old federation to be removed.
      ACE_OS::sleep(1);
    }
    spm.release();

    GERTICO::FederationManagementEC *fedNew = new GERTICO::FederationManagementEC(myEventHub, myGeRtiOrb, myGeRtiOrb.poaRootReceiver, myGeRtiOrb.poaRootSenderBestEffort, myGeRtiOrb.poaRootSenderReliable, fedNameWstring, ff, idHandler, conf, geRtiFedTimeFactory, geRtiLogicalTimeIntervalFactory, privilegeToDeleteId);
    theEventHubFederation = fedNew->_this();
    theEventChannelReference = GeRtiFactory::EventChannel::_duplicate(fedNew->eventChannel->eventChannelVar);

    // Into the vector.
    spm.acquire();
    federationManagementECs[fedNameWstring] = fedNew;
    spm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "allocFederation", "Leave");
                           #endif   // inserted by Gal converter
    doEventHubCreateFederation(fedName);
  }
  catch(...)
  {
    spm.acquire();
    createInProgress = false;
    spm.release();
    throw;
  }

  spm.acquire();
  createInProgress = false;
  spm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_feds_i, "createFederationExecution", "done");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_TheEventHubFederationFactoryEC_i::destroyFederationExecution(CORBA::WChar const *fedName)
{
  CORBA::WChar *wChar = L"destroyFederationExecution";
  std::string fedNameString;
  std::wstring fedNameWstring;
  std::wstring ws;

  GERTICO::Mapper::mapWstringFromWchar(fedNameWstring, fedName);
  GERTICO::Mapper::mapStringFromWstring(fedNameString, fedNameWstring);

  GERTICO::FederationManagementEC *federationManagementEC;
  size_t size;

  spm.acquire();
  size = federationManagementECs.size();
  FederationManagementECMap::iterator it = federationManagementECs.find(fedNameWstring);

  if (it != federationManagementECs.end())
  {
    federationManagementEC = it->second;

    if (federationManagementEC->isActive() == false)
    {
      spm.release();
      GERTICO::Mapper::mapWstringFromChar(ws, fedNameString.c_str());
      throw GeRtiFactory::FederationExecutionDoesNotExist(ws.c_str());
    }

    if (federationManagementEC->areFederatesJoined() == false)
    {
      // No federates are joined, schedule delete job.
      federationManagementEC->deactivate();

      federationManagementECs.erase(it);
      size = federationManagementECs.size();

      spm.release();
      deleteFedManVector.push_back(federationManagementEC);
      psCleanHub->release();
      return;
    }
    else
    {
      // Federates currently joined.
      spm.release();
      throw GeRtiFactory::FederatesCurrentlyJoined(wChar);
    }
  }
  else
  {
    spm.release();
    GERTICO::Mapper::mapWstringFromChar(ws, fedNameString.c_str());
    throw GeRtiFactory::FederationExecutionDoesNotExist(ws.c_str());
  }
  spm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_TheEventHubFederationFactoryEC_i::doEventHubCreateFederation(CORBA::WChar const *fedNameWstring)
{
//  TODO
  int i = 1;
  int j = 2;

  i += j;
  /*
  CORBA::ULong momInteractionRoot;
  CORBA::ULong momObjectRoot;
  CORBA::ULong interactionRoot;
  CORBA::ULong objectRoot;
  CORBA::ULong privilegeToDeleteId;
  CORBA::WChar *wChar = L"doEventHubCreateFederation: my event hub not found";
  EventHubMap::iterator itEventHub;
  FederationManagementMap::iterator itFederationManagementMap;

  itFederationManagementMap = fedMan.find(fedNameWstring);
  if (itFederationManagementMap != fedMan.end())
  {
    itFederationManagementMap->second->getEventHubCreateData(momInteractionRoot, momObjectRoot, interactionRoot, objectRoot, privilegeToDeleteId);
  }

  itEventHub = eventHubs.find(myEventHub);
  if (itEventHub != eventHubs.end())
  {
    itEventHub->second->createFederationExecution(fedNameWstring, momInteractionRoot, momObjectRoot, interactionRoot, objectRoot, privilegeToDeleteId);
  }
  else
  {
    throw GeRtiFactory::FederationExecutionAlreadyExists(wChar);
  }
  */
}
