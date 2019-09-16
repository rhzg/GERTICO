/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** FederationManagementEC.cpp
**
*******************************************************************************/

#include "FederationManagementEC.h"

#include <ace/OS.h>

#include "Util/GERTICOconf.h"
#include "Util/ConvertTime.h"
#include "Util/XercesInclude.h"
#include "Util/HLAparseErrorHandler.h"
#include "Util/Mapper.h"
#include "Util/PrintFilter.h"
#include "Util/PrintErrorHandler.h"

/********************************* Gal begin ************************************/

#ifdef GalDebug

#include "Gal/StdAfx.h"
#include "Gal/repository_l.h"
#include "Gal/event.h"

static class Repository_l *FM=(Repository::getSingleInstance())->getRepository_l("GeRtiFM.res","GeRtiFM");

static class Event *GeRti_FM_d=FM->getRefEvent("GeRti_FM_d");
static class Event *GeRti_FM_e=FM->getRefEvent("GeRti_FM_e");
static class Event *GeRti_FM_feds_i=FM->getRefEvent("GeRti_FM_feds_i");
static class Event *GeRti_FM_i=FM->getRefEvent("GeRti_FM_i");
static class Event *GeRti_FM_save_restore_i=FM->getRefEvent("GeRti_FM_save_restore_i");
static class Event *GeRti_FM_sync_i=FM->getRefEvent("GeRti_FM_sync_i");
static class Event *GeRti_FM_w=FM->getRefEvent("GeRti_FM_w");

#define MAX_TXT 2048

#endif

/********************************* Gal end ************************************/

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void *fed_worker_hub(void *arg)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "fed_worker_hub", "Enter");
                           #endif   // inserted by Gal converter
  GERTICO::EventHandler *eventHandler = (GERTICO::EventHandler *) arg;

  while(eventHandler->notDone)
  {
    eventHandler->process();
  }

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "fed_worker_hub", "Leave");
                           #endif   // inserted by Gal converter
  return NULL;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void *localEC_worker(void *arg)
{
                           #ifdef GalDebug
                             E2(GeRti_FM_d, "localEC_worker", "enter");
                           #endif
  GERTICO::EventHandler *eventHandler = (GERTICO::EventHandler *) arg;

  while(eventHandler->notDone)
  {
    eventHandler->processLocalEvents();
  }

                           #ifdef GalDebug
                             E2(GeRti_FM_d, "localEC_worker", "leave");
                           #endif
  return (void *) 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::TransmissionECArg::TransmissionECArg(void)
{
  barrier = NULL;
  eventHandler = NULL;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::TransmissionECArg::~TransmissionECArg(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void *transmissionEC_worker(void *arg)
{
                           #ifdef GalDebug
                             E2(GeRti_FM_d, "transmissionEC_worker", "enter");
                           #endif
  GERTICO::TransmissionECArg *myArg = (GERTICO::TransmissionECArg *)arg;

  myArg->barrier->wait();
  for (;myArg->eventHandler->notDone;)
  {
    try
    {
      myArg->eventHandler->processPeerEvents();
    }
   catch(...)
   {
   }
  }

                           #ifdef GalDebug
                             E2(GeRti_FM_d, "transmissionEC_worker", "leave");
                           #endif
  return (void *) 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FederationManagementEC::FederationManagementEC(std::wstring const &theEventHub, GERTICO::GeRtiOrb &theGeRtiOrb, PortableServer::POA_ptr thePOAReceiver, PortableServer::POA_ptr thePoaBestEffort, PortableServer::POA_ptr thePoaSender, std::wstring const &theFederationName, std::wstring const &theFedFile, GERTICO::NextHandle &theIdHandler, GERTICOconf const &theGERTICOconf, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory, GeRtiFactory::GeRtiHandle const &thePrivilegeToDeleteId) : geRtiFedTimeFactory(theGeRtiFedTimeFactory), geRtiLogicalTimeIntervalFactory(theGeRtiLogicalTimeIntervalFactory), myGeRtiOrb(theGeRtiOrb), privilegeToDeleteId(thePrivilegeToDeleteId), gerticoConf(theGERTICOconf)
{
  // Various varibles
  CosNaming::Name bindName;
  std::string hubName;
  std::string hubsName;
  std::string name;

  barrier = NULL;
  eventChannel = NULL;
  eventHandler = NULL;
  geRti_TimeManagement_i = NULL;
  ps = NULL;
  timeClient = NULL;

  active = true;
  notDone = true;

  myEventHub = theEventHub;
  federationName = theFederationName;

  myPOAReceiver = PortableServer::POA::_duplicate(thePOAReceiver);
  myPOAbestEffort = PortableServer::POA::_duplicate(thePoaBestEffort);
  myPoaSender = PortableServer::POA::_duplicate(thePoaSender);
  ps = new ACE_Semaphore(1);

  federationState = "federationState";

  timeClient = new TimeClient(&geRtiFedTimeFactory, &geRtiLogicalTimeIntervalFactory);

  // Event channel
  eventHandler = new GERTICO::EventHandler(*ps, gerticoConf, geRtiFedTimeFactory, geRtiLogicalTimeIntervalFactory, privilegeToDeleteId, myEventHub);
  eventHandler->timeServiceFac = new GERTICO::TimeServiceFacI(*timeClient);
  eventHandler->timeService = eventHandler->timeServiceFac->createTimeService();
  geRti_TimeManagement_i = new GeRti_TimeManagement_i(thePOAReceiver, *eventHandler->timeService, &geRtiFedTimeFactory, &geRtiLogicalTimeIntervalFactory);
  timeManagementVar = geRti_TimeManagement_i->_this();

  timeClient->eventHandler = eventHandler;

  eventChannel = new GeRtiFactory_EventChannel_i(theGeRtiOrb, myPOAReceiver, myPOAbestEffort, eventHandler);
  eventChannel->eventChannelVar = eventChannel->_this();


  tid0 = ACE_Thread_Manager::instance()->spawn(ACE_reinterpret_cast(ACE_THR_FUNC, &fed_worker_hub), eventHandler);
  tid1 = ACE_Thread_Manager::instance()->spawn(ACE_reinterpret_cast(ACE_THR_FUNC, &localEC_worker), eventHandler);

//  if (theGERTICOconf.dataLength > 1)
//  {
    barrier = new ACE_Barrier(2);
    transmissionArg.barrier = barrier;
    transmissionArg.eventHandler = eventHandler;
    tid2 = ACE_Thread_Manager::instance()->spawn(ACE_reinterpret_cast(ACE_THR_FUNC, &transmissionEC_worker), &transmissionArg);
    barrier->wait();
//  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FederationManagementEC::~FederationManagementEC(void)
{
  // Reverse order of creation!
  if (barrier)
  {
    delete barrier;
  }

  if (eventChannel)
  {
    delete eventChannel;
  }

  if (eventHandler)
  {
    delete eventHandler;
  }

  if (timeClient)
  {
    delete timeClient;
  }

  if (ps)
  {
    delete ps;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::FederationManagementEC::areFederatesJoined(void)
{
  size_t size;

  size = federates.size();

  if (size > 0)
  {
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagementEC::clear(void)
{
  eventHandler->clearFederates();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagementEC::deactivate(void)
{
  active = false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagementEC::getEventChannelAdmins(GeRtiFactory::EventChannel_out eventChannelOut, GeRtiFactory::TimeManagement_out theTimeManagement)
{
  eventChannelOut = GeRtiFactory::EventChannel::_duplicate(eventChannel->eventChannelVar);
  theTimeManagement = GeRtiFactory::TimeManagement::_duplicate(timeManagementVar);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagementEC::makeEventHubChannels(GeRtiFactory::HubEventChannelDataSeq const &theHubEventChannelDataSeq)
{
  eventHandler->makeEventHubChannels(myGeRtiOrb, myPOAReceiver, myEventHub, theHubEventChannelDataSeq);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::FederationManagementEC::isActive(void)
{
  return active;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::FederationManagementEC::noFederatesJoined(void)
{
  bool ret = false;

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::FederationManagementEC::parseEnv(char *out, char *in)
{
  bool gotClosing = false;
  bool gotEnv = false;
  bool ret = false;
  char *b;
  char env[128];
  size_t i;
  size_t j;
  size_t k;
  size_t l;
  size_t len;

  len = strlen(in);

  for (i = 0, l = 0; i < len; i++, l++)
  {
    if (in[i] == '$' && in[i + 1] == '(')
    {
      gotClosing = false;
      for (j = i + 2, k = 0; j < len; j++, k++)
      {
        if (in[j] == ')')
        {
          gotClosing = true;
          gotEnv = true;
          env[k] = '\0';
          b = getenv(env);
          if (b)
          {
            strcpy(&out[l], b);
            l += strlen(b) - 1;
            i = j;
          }
          else
          {
            std::cout << "Missing environment variable " << env << std::endl;
            ret = true;
            strncpy(&out[l], &in[i], j - i + 1);
            out[l + j - i + 1] = '\0';
            l += j - i;
            i = j;
          }
          break;
        }
        env[k] = in[j];
      }
      if (gotClosing == false)
      {
        std::cout << "Missing closing bracket" << std::endl;
        ret = true;
      }
    }
    if (gotEnv)
    {
      gotEnv = false;
      continue;
    }
    out[l] = in[i];
  }
  out[l] = '\0';

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagementEC::processLive(void)
{
  double diffTime;
  double doubleCurrentTime;

  // Delete any federates which have previously resigned.
//  federatesHolder->pruneResignedFederates();

  // Get current time.
  ACE_Time_Value currentTime = ACE_OS::gettimeofday();

  doubleCurrentTime = currentTime.sec() + currentTime.usec() / 1000000.0;

  diffTime = doubleCurrentTime - doublePreviousTime;

  if (diffTime < 1.0)
  {
    return;
  }

  doublePreviousTime = doubleCurrentTime;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagementEC::resignFed(const GeRtiFactory::GeRtiHandle &theFederate, const std::wstring &theFedType)
{
  // NEED MORE LOGIC! XXXXX
  timeClient->saveInProgress = false;
  timeClient->saveRequested = false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagementEC::setAlive(GeRtiFactory::GeRtiHandle const &theandle)
{
  /*
  GERTICO::Federate *federate;

  federate = federatesHolder->getFederate(theandle);
  if (federate != NULL)
  {
    federate->setAlive();
  }
  */
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagementEC::wallClockWorker(void)
{
  processLive();
}
