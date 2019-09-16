/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** EventHandler.cpp
**
*******************************************************************************/

#include "EventHandler.h"
#include "Util/ConvertTime.h"
#include "Util/Mapper.h"
#include "Mapper13.h"

// Static strings for save/restore.
std::string GERTICO::EventHandler::classStr("class");
std::string GERTICO::EventHandler::eventStr("event");
std::string GERTICO::EventHandler::eventHandlerStr("eventHandler");
std::string GERTICO::EventHandler::idStr("id");
std::string GERTICO::EventHandler::objectStr("object");
std::string GERTICO::EventHandler::regionStr("region");
std::string GERTICO::EventHandler::removeObjectsWithTimeStr("removeObjectsWithTime");
std::string GERTICO::EventHandler::retractHandleStr("retractHandle");
std::string GERTICO::EventHandler::retractHandlesStr("retractHandles");
std::string GERTICO::EventHandler::sendingFederateStr("sendingFederate");
std::string GERTICO::EventHandler::tagStr("tag");
std::string GERTICO::EventHandler::theSerialNumberStr("theSerialNumber");
std::string GERTICO::EventHandler::timeStr("time");
std::string GERTICO::EventHandler::timestampStr("timestamp");
std::string GERTICO::EventHandler::tsoEventsStr("tsoEvents");
std::string GERTICO::EventHandler::typeStr("type");
std::string GERTICO::EventHandler::userTagStr("userTag");
std::string GERTICO::EventHandler::valueStr("value");
std::string GERTICO::EventHandler::valuePairStr("valuePair");
std::string GERTICO::EventHandler::valuePairsStr("valuePairs");

/********************************* Gal begin *********************************/
#ifdef GalDebug   // inserted by Gal converter
#define GalHLADebug 1

#include "Gal/StdAfx.h"
#include "Gal/repository_l.h"
#include "Gal/event.h"

#include "ut.h"

static class Repository_l *FM=(Repository::getSingleInstance())->getRepository_l("GeRtiFM.res","GeRtiFM");

static class Event *GeRti_FM_d=FM->getRefEvent("GeRti_FM_d");
static class Event *GeRti_FM_e=FM->getRefEvent("GeRti_FM_e");
static class Event *GeRti_FM_feds_i=FM->getRefEvent("GeRti_FM_feds_i");
static class Event *GeRti_FM_i=FM->getRefEvent("GeRti_FM_i");
static class Event *GeRti_FM_save_restore_i=FM->getRefEvent("GeRti_FM_save_restore_i");
static class Event *GeRti_FM_sync_i=FM->getRefEvent("GeRti_FM_sync_i");
static class Event *GeRti_FM_w=FM->getRefEvent("GeRti_FM_w");

static class Repository_l *OM=(Repository::getSingleInstance())->getRepository_l("GeRtiOM.res","GeRtiOM");

static class Event *GeRti_OM_d=OM->getRefEvent("GeRti_OM_d");
static class Event *GeRti_OM_e=OM->getRefEvent("GeRti_OM_e");
static class Event *GeRti_OM_i=OM->getRefEvent("GeRti_OM_i");
static class Event *GeRti_OM_w=OM->getRefEvent("GeRti_OM_w");

static class Repository_l *TM=(Repository::getSingleInstance())->getRepository_l("GeRtiTM.res","GeRtiTM");

static class Event *GeRti_TM_d=TM->getRefEvent("GeRti_TM_d");
static class Event *GeRti_TM_e=TM->getRefEvent("GeRti_TM_e");
static class Event *GeRti_TM_i=TM->getRefEvent("GeRti_TM_i");
static class Event *GeRti_TM_w=TM->getRefEvent("GeRti_TM_w");
static class Event *GeRti_TM_mu_d=TM->getRefEvent("GeRti_TM_mu_d");

#include "Gal/StdAfx.h"   // inserted by Gal converter
#include "Gal/repository_l.h"   // inserted by Gal converter
#include "Gal/event.h"   // inserted by Gal converter

static class Repository_l *rpGalH=(Repository::getSingleInstance())->getRepository_l("HLAServices.res","HLAServices");
static class Event *pIFS_i0=rpGalH->getRefEvent("pIFS_i0");
static class Event *pIFS_ts=rpGalH->getRefEvent("pIFS_ts");
static class Event *pFS_i1=rpGalH->getRefEvent("pFS_i1");
static class Event *pFS_ts=rpGalH->getRefEvent("pFS_ts");
static class Event *pCFRR_i0=rpGalH->getRefEvent("pCFRR_i0");
static class Event *pCFRR_i1=rpGalH->getRefEvent("pCFRR_i1");
static class Event *pCFRR_ts=rpGalH->getRefEvent("pCFRR_ts");
static class Event *pFRB_i0=rpGalH->getRefEvent("pFRB_i0");
static class Event *pFRB_ts=rpGalH->getRefEvent("pFRB_ts");
static class Event *pIFR_i0=rpGalH->getRefEvent("pIFR_i0");
static class Event *pIFR_ts=rpGalH->getRefEvent("pIFR_ts");
static class Event *pFR_i0=rpGalH->getRefEvent("pFR_i0");
static class Event *pTO_i0=rpGalH->getRefEvent("pTO_i0");
static class Event *pERO_i0=rpGalH->getRefEvent("pERO_i0");
static class Event *pERO_ta=rpGalH->getRefEvent("pERO_ta");
static class Event *pERO_ts=rpGalH->getRefEvent("pERO_ts");
static class Event *pETO_i0=rpGalH->getRefEvent("pETO_i0");
static class Event *pETO_ta=rpGalH->getRefEvent("pETO_ta");
static class Event *pETO_ts=rpGalH->getRefEvent("pETO_ts");
static class Event *pERI_i0=rpGalH->getRefEvent("pERI_i0");
static class Event *pERI_ta=rpGalH->getRefEvent("pERI_ta");
static class Event *pERI_ts=rpGalH->getRefEvent("pERI_ts");
static class Event *pRWT_i0=rpGalH->getRefEvent("pRWT_i0");
static class Event *pRWT_ta=rpGalH->getRefEvent("pRWT_ta");
static class Event *pRWT_ts=rpGalH->getRefEvent("pRWT_ts");
static class Event *pTRE_i0=rpGalH->getRefEvent("pTRE_i0");
static class Event *pTRE_ta=rpGalH->getRefEvent("pTRE_ta");
static class Event *pTRE_ts=rpGalH->getRefEvent("pTRE_ts");
static class Event *pTCE_i0=rpGalH->getRefEvent("pTCE_i0");
static class Event *pTCE_ta=rpGalH->getRefEvent("pTCE_ta");
static class Event *pTCE_ts=rpGalH->getRefEvent("pTCE_ts");
static class Event *pT_i0=rpGalH->getRefEvent("pT_i0");
static class Event *pT_ta=rpGalH->getRefEvent("pT_ta");
static class Event *pT_ts=rpGalH->getRefEvent("pT_ts");
static class Event *rAOA_i0=rpGalH->getRefEvent("rAOA_i0");
static class Event *pETI_i0=rpGalH->getRefEvent("pETI_i0");
static class Event *pETI_ta=rpGalH->getRefEvent("pETI_ta");
static class Event *pETI_ts=rpGalH->getRefEvent("pETI_ts");
static class Event *pR_i0=rpGalH->getRefEvent("pR_i0");
static class Event *pR_ta=rpGalH->getRefEvent("pR_ta");
static class Event *pR_ts=rpGalH->getRefEvent("pR_ts");
static class Event *pRF_i0=rpGalH->getRefEvent("pRF_i0");

static char galMsg[MAX_TXT];

#endif

char cBuff[1024];

/*********************************** Gal end *********************************/   // inserted by Gal converter

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Remove::Remove (const unsigned long &v_objectId, const GeRtiFactory::UserSuppliedTag &v_tag)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "Remove::Remove", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  objectId = v_objectId;
  myTag = new GeRtiFactory::UserSuppliedTag (v_tag);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "Remove::Remove", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Remove::~Remove (void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "Remove::~Remove", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  delete myTag;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "Remove::~Remove", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RemoveWithTime::RemoveWithTime (const GeRtiFactory::GeRtiHandle &v_objectId, const GeRtiFactory::UserSuppliedTag &v_tag, GERTICO::GeRtiFedTime &theTime, const RTI::EventRetractionHandle &theERHandle, GERTICO::GeRtiFedTimeFactory &theFedTimeFactory) : fedTimeFactory(theFedTimeFactory)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "RemoveWithTime::RemoveWithTime", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  myTime = NULL;

  objectId = v_objectId;
  myTag = v_tag;
  myTime = fedTimeFactory.makeZero();
  *myTime = theTime;
  retractionHandle = theERHandle;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "RemoveWithTime::RemoveWithTime", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RemoveWithTime::~RemoveWithTime (void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "RemoveWithTime::~RemoveWithTime", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  if (myTime)
  {
    delete myTime;
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "RemoveWithTime::~RemoveWithTime", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::EventHolder::EventHolder(const GeRtiFactory::GeRtiEvent &theEvent, GERTICO::GeRtiFedTimeFactory &theFedTimeFactory)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHolder::EventHolder", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  type = theEvent.type;
  timestamp.reset(theFedTimeFactory.makeZero());
  GERTICO::ConvertTime::mapGeRtiFedTimeAutoPtr(theFedTimeFactory, timestamp, theEvent.timestamp);
  ahvps = NULL;
  phvps = NULL;
  tag = NULL;
  if (type == GeRtiFactory::interaction)
  {
    phvps = RTI::ParameterSetFactory::create(theEvent.data.length());
    Mapper13::mapParameterHandleValuePairSet(*phvps, theEvent.data);
    Mapper13::mapUserSuppliedTag(&tag, theEvent.theTag);
    objectId = theEvent.obj;
    classId = theEvent._cxx_class;
    region = theEvent.reg;
    retractionHandle.theSerialNumber = theEvent.theSerialNumber;
    retractionHandle.sendingFederate = theEvent.source;
    if (theEvent.bestEffort)
    {
      bestEffort = true;
    }
    else
    {
      bestEffort = false;
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHolder::EventHolder", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::EventHolder::EventHolder(const GeRtiFactory::GeRtiEvent &theEvent, const int &theGrouping, const bool theBestEffort, GERTICO::GeRtiFedTimeFactory &theFedTimeFactory)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "RemoveWithTime::~RemoveWithTime", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  type = theEvent.type;
  timestamp.reset(theFedTimeFactory.makeZero());
  GERTICO::ConvertTime::mapGeRtiFedTimeAutoPtr(theFedTimeFactory, timestamp, theEvent.timestamp);
  ahvps = NULL;
  phvps = NULL;
  tag = NULL;
  if (type != GeRtiFactory::interaction)
  {
    ahvps = RTI::AttributeSetFactory::create(theEvent.data.length());
    Mapper13::mapAttributeHandleValuePairSet(*ahvps, theEvent.data, theGrouping, theBestEffort);
    Mapper13::mapUserSuppliedTag(&tag, theEvent.theTag);
    objectId = theEvent.obj;
    classId = theEvent._cxx_class;
    region = theEvent.reg;
    retractionHandle.theSerialNumber = theEvent.theSerialNumber;
    retractionHandle.sendingFederate = theEvent.source;
    if (theBestEffort)
    {
      bestEffort = true;
    }
    else
    {
      bestEffort = false;
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHolder::EventHolder", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::EventHolder::~EventHolder (void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHolder::~EventHolder", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  if (tag)
  {
    delete []tag;
  }
  if (ahvps)
  {
    delete ahvps;
  }
  if (phvps)
  {
    delete phvps;
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHolder::~EventHolder", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
unsigned long GERTICO::EventHolder::getLength(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHolder::getLength", "enterLeave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  if (type == GeRtiFactory::interaction)
  {
    return phvps->size();
  }

  return ahvps->size();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::EventHandler::EventHandler(bool &theAsynchronousDelivery) : asynchronousDelivery (theAsynchronousDelivery)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::EventHandler", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  timeManagementLRC = NULL;
  init();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::EventHandler", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::init(void)
{
  pm.acquire();
  ehRequest = EHNone;

  // Save / Restore
  federateState = Running;
  gotAnnounceFederateSave = false;
  gotConfirmFederationRestorationRequest = false;
  gotInitiateFederateSave = false;

  confirmRestoreSuccess = true;
  gotTimeConstrainedEnabled = false;
  gotTimeConstrainedEnabledFlag = false;
  gotTimeRegulationEnabled = false;
  gotTimeRegulationEnabledFlag = false;
  interactionsReceived = 0;
  reflectionsReceived = 0;
  restoreLabel = L"";
  saveLabel = L"";
  stateRestore = false;
  stateSave = false;
  gotSaveTime = false;

  // Time
  available = false;
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::EventHandler::~EventHandler (void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::~EventHandler", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  clear();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::~EventHandler", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::addConfirmFederationRestorationRequest(const std::wstring &theLabel, const bool &myReason)
{
  restoreLabel = theLabel;
  if (myReason)
  {
    confirmRestoreSuccess = true;
  }
  else
  {
    confirmRestoreSuccess = false;
  }

  gotConfirmFederationRestorationRequest = true;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::addERHandle (const RTI::EventRetractionHandle &theEventRetractionHandle, const GERTICO::GeRtiFedTime &theFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::addERHandle", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  GERTICO::HandleErMap::iterator itHEM;
  std::auto_ptr<GERTICO::GeRtiFedTime> tmpFedTime(timeManagementLRC->geRtiFedTimeFactory.makeZero());

  *tmpFedTime = theFedTime;
  itHEM = handleErMap.find (theEventRetractionHandle.sendingFederate);
  if (itHEM != handleErMap.end ())
  {
    // Got an entry for the federate.
    GERTICO::ERHandleTimeMap *currERHandleTimeMap;
    currERHandleTimeMap = &itHEM->second;
    (*currERHandleTimeMap)[theEventRetractionHandle.theSerialNumber] = tmpFedTime.release();
  }
  else
  {
    // Create an entry for the federate.
    GERTICO::ERHandleTimeMap newERHandleTimeMap;
    newERHandleTimeMap[theEventRetractionHandle.theSerialNumber] = tmpFedTime.release();
    handleErMap[theEventRetractionHandle.sendingFederate] = newERHandleTimeMap;
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::addERHandle", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::addEventHolder(GeRtiFactory::GeRtiEvent const &theEvent, unsigned int &numberRO, unsigned int &numberTSO)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::addEventHolder", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  EventHolder *newEventHolderRoBestEffort = NULL;
  EventHolder *newEventHolderRoReliable = NULL;
  EventHolder *newEventHolderTsoBestEffort = NULL;
  EventHolder *newEventHolderTsoReliable = NULL;

  numberRO = 0;
  numberTSO = 0;

  pm.acquire();

  // Only when the application has received the enabled call.
  if (gotTimeConstrainedEnabled == true && gotTimeConstrainedEnabledFlag == false)
  {
    if (theEvent.type == GeRtiFactory::interaction)
    {
      if (theEvent.timestamp.length())
      {
        // Events TSO based on timestamp and preferred type.
        if (theEvent.bestEffort)
        {
          newEventHolderTsoBestEffort = new EventHolder(theEvent, timeManagementLRC->geRtiFedTimeFactory);
        }
        else
        {
          newEventHolderTsoReliable = new EventHolder(theEvent, timeManagementLRC->geRtiFedTimeFactory);
        }
        // NB. zero length is allowed
      }
      else
      {
        // Events are RO.
        if (theEvent.bestEffort)
        {
          newEventHolderRoBestEffort = new EventHolder(theEvent, timeManagementLRC->geRtiFedTimeFactory);
        }
        else
        {
          newEventHolderRoReliable = new EventHolder(theEvent, timeManagementLRC->geRtiFedTimeFactory);
        }
        // NB. zero length is allowed
      }
    }
    else
    {
      if (theEvent.timestamp.length())
      {
        // Events are RO and/or TSO based on preferred type.
        newEventHolderRoBestEffort = new EventHolder (theEvent, 0, true, timeManagementLRC->geRtiFedTimeFactory);
        if (newEventHolderRoBestEffort->getLength() == 0)
        {
          delete newEventHolderRoBestEffort;
          newEventHolderRoBestEffort = NULL;
        }
        newEventHolderRoReliable = new EventHolder (theEvent, 0, false, timeManagementLRC->geRtiFedTimeFactory);
        if (newEventHolderRoReliable->getLength() == 0)
        {
          delete newEventHolderRoReliable;
          newEventHolderRoReliable = NULL;
        }
        newEventHolderTsoBestEffort = new EventHolder (theEvent, 1, true, timeManagementLRC->geRtiFedTimeFactory);
        if (newEventHolderTsoBestEffort->getLength() == 0)
        {
          delete newEventHolderTsoBestEffort;
          newEventHolderTsoBestEffort = NULL;
        }
        newEventHolderTsoReliable = new EventHolder (theEvent, 1, false, timeManagementLRC->geRtiFedTimeFactory);
        if (newEventHolderTsoReliable->getLength() == 0)
        {
          delete newEventHolderTsoReliable;
          newEventHolderTsoReliable = NULL;
        }
      }
      else
      {
        // Events are RO.
        newEventHolderRoBestEffort = new EventHolder (theEvent, 2, true, timeManagementLRC->geRtiFedTimeFactory);
        newEventHolderRoReliable = new EventHolder (theEvent, 2, false, timeManagementLRC->geRtiFedTimeFactory);
        // NB. zero length is allowed
      }
    }
  }
  else
  {
    if (theEvent.type == GeRtiFactory::interaction)
    {
      // Events are RO.
      if (theEvent.bestEffort)
      {
        newEventHolderRoBestEffort = new EventHolder (theEvent, timeManagementLRC->geRtiFedTimeFactory);
      }
      else
      {
        newEventHolderRoReliable = new EventHolder (theEvent, timeManagementLRC->geRtiFedTimeFactory);
      }
      // NB. zero length is allowed
    }
    else
    {
      // All events are made RO.
      newEventHolderRoBestEffort = new EventHolder (theEvent, 2, true, timeManagementLRC->geRtiFedTimeFactory);
      newEventHolderRoReliable = new EventHolder (theEvent, 2, false, timeManagementLRC->geRtiFedTimeFactory);
    }
  }
  if (newEventHolderTsoBestEffort)
  {
    // Got a TSO event.
    if (*newEventHolderTsoBestEffort->timestamp < *myRegulationTime)
    {
      newEventHolderTsoBestEffort->timestamp.release();
      newEventHolderRoBestEffort = newEventHolderTsoBestEffort;
      newEventHolderTsoBestEffort = NULL;
    }
  }

  if (newEventHolderTsoBestEffort)
  {
    if (*newEventHolderTsoBestEffort->timestamp < *timeManagementLRC->myLogicalTime)
    {
      char b[128];
      timeManagementLRC->myLogicalTime->getPrintableString(b);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::addEventHolder_logicalTime", b);   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      newEventHolderTsoBestEffort->timestamp->getPrintableString(b);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::addEventHolder_timestamp", b);   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      delete newEventHolderTsoBestEffort;
      newEventHolderTsoBestEffort = NULL;
    }
    if (newEventHolderTsoBestEffort)
    {
      EventHolderMap::iterator itEHM;
      std::vector <EventHolder *> *currEventHolderVector;
      std::vector <EventHolder *> newEventHolder;

      itEHM = eventsTimedMap.find(newEventHolderTsoBestEffort->timestamp.get());
      if (itEHM != eventsTimedMap.end())
      {
        currEventHolderVector = &itEHM->second;
        currEventHolderVector->push_back(newEventHolderTsoBestEffort);
      }
      else
      {
        GERTICO::GeRtiFedTime *tempTime;
        newEventHolder.push_back(newEventHolderTsoBestEffort);
        tempTime = timeManagementLRC->geRtiFedTimeFactory.makeZero();
        *tempTime = *newEventHolderTsoBestEffort->timestamp;
        eventsTimedMap[tempTime] = newEventHolder;
      }
      numberTSO += 1;
      addERHandle (newEventHolderTsoBestEffort->retractionHandle, *newEventHolderTsoBestEffort->timestamp);
    }
  }
  if (newEventHolderTsoReliable)
  {
    if (*newEventHolderTsoReliable->timestamp < *myRegulationTime)
    {
      newEventHolderTsoReliable->timestamp.release();
      newEventHolderRoReliable = newEventHolderTsoReliable;
      newEventHolderTsoReliable = NULL;
    }
  }

  if (newEventHolderTsoReliable)
  {
    // Got a TSO event.
    if (*newEventHolderTsoReliable->timestamp < *timeManagementLRC->myLogicalTime)
    {
      char b[128];
      timeManagementLRC->myLogicalTime->getPrintableString(b);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::addEventHolder_logicalTime", b);   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      newEventHolderTsoReliable->timestamp->getPrintableString(b);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::addEventHolder_timestamp", b);   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      delete newEventHolderTsoReliable;
      newEventHolderTsoReliable = NULL;
    }
    if (newEventHolderTsoReliable)
    {
      EventHolderMap::iterator itEHM;
      std::vector <EventHolder *> *currEventHolderVector;
      std::vector <EventHolder *> newEventHolder;

      itEHM = eventsTimedMap.find(newEventHolderTsoReliable->timestamp.get());
      if (itEHM != eventsTimedMap.end())
      {
        currEventHolderVector = &itEHM->second;
        currEventHolderVector->push_back(newEventHolderTsoReliable);
      }
      else
      {
        GERTICO::GeRtiFedTime *tempTime;
        newEventHolder.push_back(newEventHolderTsoReliable);
        tempTime = timeManagementLRC->geRtiFedTimeFactory.makeZero();
        *tempTime = *newEventHolderTsoReliable->timestamp;
        eventsTimedMap[tempTime] = newEventHolder;
      }
      numberTSO += 1;
      addERHandle (newEventHolderTsoReliable->retractionHandle, *newEventHolderTsoReliable->timestamp);
    }
  }
  if (newEventHolderRoBestEffort)
  {
    // Got an RO event.
    events.push_back (newEventHolderRoBestEffort);
    numberRO += 1;
  }
  if (newEventHolderRoReliable)
  {
    // Got an RO event.
    events.push_back (newEventHolderRoReliable);
    numberRO += 1;
  }

  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::addEventHolder", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::addFlushERHandle (const RTI::EventRetractionHandle &theEventRetractionHandle, const GERTICO::GeRtiFedTime *theFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::addFlushERHandle", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  timeErMultimap.insert (std::pair<const GERTICO::GeRtiFedTime *, RTI::EventRetractionHandle>(theFedTime, theEventRetractionHandle));
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::addFlushERHandle", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::addHandleMap(const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleMap &theHandleMap)
{
  GERTICO::HandleMap::iterator itHandleMap;

  itHandleMap = theHandleMap.find(theClass);
  if (itHandleMap != theHandleMap.end())
  {
    itHandleMap->second += 1;
  }
  else
  {
    GeRtiFactory::GeRtiHandle count = 1;

    theHandleMap[theClass] = count;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::addInitiateFederateSave(std::wstring const &theLabel)
{
  gotAnnounceFederateSave = true;
  gotSaveTime = false;
  timeManagementLRC->gotAnnounceFederateSaveWithTime = false;
  saveLabel = theLabel;
  federateState = SavePending;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::addInitiateFederateSaveWithTime(const std::wstring &theLabel, const GERTICO::GeRtiFedTime &theTime)
{
  char buff[256];
  *timeManagementLRC->myTimeSave = theTime;
  timeManagementLRC->myTimeSave->getPrintableString(buff);
  gotAnnounceFederateSave = false;
  gotSaveTime = true;
  timeManagementLRC->gotAnnounceFederateSaveWithTime = true;
  saveLabel = theLabel;
  federateState = SavePending;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::addRemove (const unsigned long &theObject, const GeRtiFactory::UserSuppliedTag &tag)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::addRemove", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  Remove *newRemove = new Remove (theObject, tag);

  pm.acquire();
  removeObjects.push_back (newRemove);
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::addRemove", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::addRemoveWithTime (const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::UserSuppliedTag &tag, std::auto_ptr<GERTICO::GeRtiFedTime> &theTime, const GeRtiFactory::ERHandle &theERHandle)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::addRemoveWithTime", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter

  if (gotTimeConstrainedEnabled)
  {
    RTI::EventRetractionHandle erh;
    erh.theSerialNumber = theERHandle.theSerialNumber;
    erh.sendingFederate = theERHandle.sendingFederate;
    RemoveWithTime *newRemoveWithTime = new RemoveWithTime (theObject, tag, *theTime, erh, timeManagementLRC->geRtiFedTimeFactory);
    pm.acquire();
    removeObjectsWithTime.insert (std::pair<const GERTICO::GeRtiFedTime *, RemoveWithTime *>(newRemoveWithTime->myTime, newRemoveWithTime));

    addERHandle (erh, *theTime);
    pm.release();
  }
  else
  {
    try
    {
      // get object only for test if known
      runTimeObjectDB->getObject(theObject);
      addRemove(theObject, tag);
    }
    catch (GeRtiFactory::ObjectNotKnown&)
    {
      // object is not known - no delete required
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::addRemoveWithTime", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::addRequestRetraction (const GeRtiFactory::ERHandle & theHandle)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::addRequestRetraction", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  GERTICO::HandleSet handleSet;
  GERTICO::HandleSet *currHandleSet;
  GERTICO::HandleSetMap::iterator itHSM;

  itHSM = retractRequests.find (theHandle.sendingFederate);
  if (itHSM != retractRequests.end ())
  {
    currHandleSet = &itHSM->second;
    currHandleSet->insert (theHandle.theSerialNumber);
  }
  else
  {
    handleSet.insert (theHandle.theSerialNumber);
    retractRequests[theHandle.sendingFederate] = handleSet;
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::addRequestRetraction", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::addRetractionHandle(const GeRtiFactory::ERHandle &theERHandle, const GERTICO::GeRtiFedTime &theFedTime)
{
  ERHandleTimeMap::iterator itERHTM;
  TimeERHandleMap::iterator itTERHM;

  itERHTM = eRHandleTimeMap.find(theERHandle.theSerialNumber);
  if (itERHTM == eRHandleTimeMap.end())
  {
    std::auto_ptr<GERTICO::GeRtiFedTime> fedTime(timeManagementLRC->geRtiFedTimeFactory.makeZero());
    *fedTime = theFedTime;
    itTERHM = timeERHandleMap.find(fedTime.get());
    if (itTERHM != timeERHandleMap.end())
    {
      GERTICO::HandleSet *handleSetPtr;
      handleSetPtr = &itTERHM->second;
      handleSetPtr->insert(theERHandle.theSerialNumber);
    }
    else
    {
      GERTICO::HandleSet handleSet;
      handleSet.insert(theERHandle.theSerialNumber);
      timeERHandleMap[fedTime.get()] = handleSet;
    }
    eRHandleTimeMap[theERHandle.theSerialNumber] = fedTime.release();
  }
  else
  {
    // XXX Gal error message: duplicate retraction handle
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::addTimeAdvanceGrant(GERTICO::GeRtiFedTime const &theFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::addTimeAdvanceGrant", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  timeManagementLRC->addTimeAdvanceGrant(theFedTime);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::addTimeAdvanceGrant", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::addTimeAdvanceGrantGalt(GERTICO::GeRtiFedTime const &theFedTime, GERTICO::GeRtiFedTime const &theGaltFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::addTimeAdvanceGrantGalt", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  timeManagementLRC->addTimeAdvanceGrantGalt(theFedTime, theGaltFedTime);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::addTimeAdvanceGrantGalt", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::addTimeAdvanceGrantIntermediate(GERTICO::GeRtiFedTime const &theFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::addTimeAdvanceGrantIntermediate", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  timeManagementLRC->addTimeAdvanceGrantIntermediate(theFedTime);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::addTimeAdvanceGrantIntermediate", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::checkRetractionHandle(const GeRtiFactory::ERHandle &theERHandle)
{
  ERHandleTimeMap::iterator itERHTM;

  itERHTM = eRHandleTimeMap.find(theERHandle.theSerialNumber);
  if (itERHTM != eRHandleTimeMap.end())
  {
    return;
  }
  else
  {
    throw GeRtiFactory::InvalidRetractionHandle(L"checkRetractionHandle");
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::deleteRetractionHandle(const GeRtiFactory::ERHandle &theERHandle)
{
  ERHandleTimeMap::iterator itERHTM;
  GERTICO::GeRtiFedTime *fedTime;

  itERHTM = eRHandleTimeMap.find(theERHandle.theSerialNumber);
  if (itERHTM != eRHandleTimeMap.end())
  {
    fedTime = itERHTM->second;
    eRHandleTimeMap.erase(itERHTM);
    delete fedTime;
    return;
  }
  else
  {
    throw GeRtiFactory::InvalidRetractionHandle(L"checkRetractionHandle");
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::clear (void)
{
  EventHolder *currEventHolder;
  EventHolderMap::iterator itEHM;
  GERTICO::ERHandleTimeMap *currERHandleTimeMap;
  GERTICO::ERHandleTimeMap::iterator itERHTM;
  GERTICO::HandleErMap::iterator itHEM;
  GERTICO::HandleSetMap::iterator itHSM;
  GERTICO::HandleSetSetMap::iterator itRCA;
  GERTICO::TimeERHandleMap::iterator itTERHM;
  GERTICO::TimeErMultimap::iterator itTEM;
  Remove *currRemove;
  RemoveWithTime *currRemoveWithTime;
  RemoveWithTimeMultimap::iterator itRWT;
  GERTICO::GeRtiFedTime *fedTime;
  std::vector <EventHolder *> *currEventHolderVector;
  std::vector <EventHolder *>::iterator itEH;
  std::vector <Remove *>::iterator itR;

  pm.acquire();
  gotAnnounceFederateSave = false;
  for (itEH = events.begin(); itEH != events.end(); itEH = events.begin())
  {
    currEventHolder = *itEH;
    events.erase (itEH);
    delete currEventHolder;
  }

  for (itEHM = eventsTimedMap.begin(); itEHM != eventsTimedMap.end(); itEHM = eventsTimedMap.begin())
  {
    currEventHolderVector = &itEHM->second;
    for (itEH = currEventHolderVector->begin(); itEH != currEventHolderVector->end(); itEH = currEventHolderVector->begin())
    {
      currEventHolder = *itEH;
      currEventHolderVector->erase(itEH);
      delete currEventHolder;
    }
    eventsTimedMap.erase(itEHM);
  }

  for (itRWT = removeObjectsWithTime.begin (); itRWT !=  removeObjectsWithTime.end (); itRWT = removeObjectsWithTime.begin ())
  {
    currRemoveWithTime = itRWT->second;
    removeObjectsWithTime.erase (itRWT);
    delete currRemoveWithTime;
  }

  for (itR = removeObjects.begin (); itR !=  removeObjects.end (); itR = removeObjects.begin ())
  {
    currRemove = *itR;
    removeObjects.erase (itR);
    delete currRemove;
  }

  for (itTERHM = timeERHandleMap.begin(); itTERHM != timeERHandleMap.end(); itTERHM = timeERHandleMap.begin())
  {
    timeERHandleMap.erase(itTERHM);
  }

  for (itERHTM = eRHandleTimeMap.begin(); itERHTM != eRHandleTimeMap.end(); itERHTM = eRHandleTimeMap.begin())
  {
    fedTime = itERHTM->second;
    eRHandleTimeMap.erase(itERHTM);
    delete fedTime;
  }

  for (itHEM = handleErMap.begin(); itHEM != handleErMap.end(); itHEM = handleErMap.begin())
  {
    currERHandleTimeMap = &itHEM->second;
    for (itERHTM = currERHandleTimeMap->begin(); itERHTM != currERHandleTimeMap->end(); itERHTM = currERHandleTimeMap->begin())
    {
      fedTime = itERHTM->second;
      currERHandleTimeMap->erase(itERHTM);
      delete fedTime;
    }
    handleErMap.erase(itHEM);
  }

  for (itRCA = regionClassAttMap.begin(); itRCA != regionClassAttMap.end(); itRCA = regionClassAttMap.begin())
  {
    for (itHSM = itRCA->second.begin(); itHSM != itRCA->second.end(); itHSM = itRCA->second.begin())
    {
      itRCA->second.erase(itHSM);
    }

    regionClassAttMap.erase(itRCA);
  }

  for (itTEM = timeErMultimap.begin (); itTEM !=  timeErMultimap.end (); itTEM = timeErMultimap.begin ())
  {
    timeErMultimap.erase(itTEM);
  }

  interactionsReceivedBestEffort.clear();
  interactionsReceivedReliable.clear();
  reflectionsReceivedBestEffort.clear();
  reflectionsReceivedReliable.clear();
  retractRequests.clear();

  federateState = Running;

  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::delERHandle (const RTI::EventRetractionHandle &theEventRetractionHandle)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::delERHandle", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  GERTICO::ERHandleTimeMap *currERHandleTimeMap;
  GERTICO::ERHandleTimeMap::iterator itErH;
  GERTICO::HandleErMap::iterator itHEM;
  GERTICO::GeRtiFedTime *tmpFedTime;

  itHEM = handleErMap.find (theEventRetractionHandle.sendingFederate);
  if (itHEM != handleErMap.end ())
  {
    currERHandleTimeMap = &itHEM->second;
    itErH = currERHandleTimeMap->find (theEventRetractionHandle.theSerialNumber);
    if (itErH != currERHandleTimeMap->end ())
    {
      tmpFedTime = itErH->second;
      if (*tmpFedTime <= *timeManagementLRC->myTimeTag)
      {
        // Events are consumed according to time management and cannot be retracted.
        currERHandleTimeMap->erase (itErH);
        delete tmpFedTime;
      }
      else
      {
        // Events are in the future and may be retracted.
        // Save the time stamp until a TAG with a time stamp greater than or equal to
        // the event time consumes the event.
        addFlushERHandle (theEventRetractionHandle, tmpFedTime);
      }
    }
    if (currERHandleTimeMap->size() == 0)
    {
      handleErMap.erase(itHEM);
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::delERHandle", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// Delete all timestamps that are less than or equal to TAG timestamp.
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::delFlushERHandle (void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::delFlushERHandle", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  GERTICO::ERHandleTimeMap *currERHandleTimeMap;
  GERTICO::ERHandleTimeMap::iterator itErH;
  GERTICO::HandleErMap::iterator itHEM;
  GERTICO::TimeErMultimap::iterator itTEM;
  GERTICO::GeRtiFedTime *tmpFedTime;

  for (itTEM = timeErMultimap.begin (); itTEM !=  timeErMultimap.end (); itTEM = timeErMultimap.begin ())
  {
    if (*itTEM->first <= *timeManagementLRC->myTimeTag)
    {
      // Have a timestamp that is passed.
      itHEM = handleErMap.find (itTEM->second.sendingFederate);
      if (itHEM != handleErMap.end ())
      {
        // Found the sending federate.
        currERHandleTimeMap = &itHEM->second;
        itErH = currERHandleTimeMap->find (itTEM->second.theSerialNumber);
        if (itErH != currERHandleTimeMap->end ())
        {
          // Erase the event.
          tmpFedTime = itErH->second;
          currERHandleTimeMap->erase (itErH);
          delete tmpFedTime;
        }
      }
      // Erase the ERHandle.
      timeErMultimap.erase (itTEM);
    }
    else
    {
      // Remaining timestamps are greater.
      break;
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::delFlushERHandle", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::federateSaveBegun(void)
{
  federateState = Saving;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::getFederateState(GERTICO::FederateState &theFederateState)
{
  theFederateState = federateState;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
long GERTICO::EventHandler::getInteractionsReceived (void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "EventHandler::getInteractionsReceived", "enterLeave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  return interactionsReceived;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::getInteractionsReceivedBestEffort(GERTICO::HandleMap &theInteractions)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "EventHandler::getInteractionsReceivedBestEffort", "enterLeave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  theInteractions = interactionsReceivedBestEffort;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::getInteractionsReceivedReliable(GERTICO::HandleMap &theInteractions)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "EventHandler::getInteractionsReceivedReliable", "enterLeave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  theInteractions = interactionsReceivedReliable;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::GeRtiFedTime *GERTICO::EventHandler::getLITS (void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::getLITS", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  EventHolderMap::iterator it;

  it = eventsTimedMap.begin();
  if (it !=  eventsTimedMap.end())
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::getLITS", "leave_1");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    return it->first;
  }

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::getLITS", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  return NULL;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
CORBA::ULong GERTICO::EventHandler::getROlength(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "EventHandler::getROlength", "enterLeave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  CORBA::ULong length;
  size_t size;

  size = events.size();
  GERTICO::Mapper::mapULongSizet(length, size);
  return length;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
long GERTICO::EventHandler::getReflectionsReceived (void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "EventHandler::getReflectionsReceived", "enterLeave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  return reflectionsReceived;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::getReflectionsReceivedBestEffort(GERTICO::HandleMap &theReflections)
{
  theReflections = reflectionsReceivedBestEffort;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::getReflectionsReceivedReliable(GERTICO::HandleMap &theReflections)
{
  theReflections = reflectionsReceivedReliable;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler::getRestoreInProgress(void)
{
  if (federateState == Restoring || federateState == RestorePending)
  {
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler::getSaveInProgress(void)
{
  if (federateState == Saving)
  {
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
long GERTICO::EventHandler::getTSOlength (void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "EventHandler::getTSOlength", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  EventHolderMap::iterator itEHM;
  long l = 0;
  std::vector <EventHolder *> *currEventHolderVector;
  std::vector <EventHolder *>::iterator itEH;

  for (itEHM = eventsTimedMap.begin(); itEHM != eventsTimedMap.end(); itEHM++)
  {
    currEventHolderVector = &itEHM->second;
    for (itEH = currEventHolderVector->begin(); itEH != currEventHolderVector->end(); itEH++)
    {
      l += 1;
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "EventHandler::getTSOlength", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  return l;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::restore(DOMElement &theDOMElement)
{
  DOMNode* child;
  char *tmpChar;

  clear ();

//std::cout << "GERTICO::EventHandler::restore not completely programmed" << std::endl;
/*
  for (child = theDOMElement.getFirstChild(); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode (eventHandlerStr.c_str ())) == 0)
      {
      }
    }
  }
*/
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel0;
  DOMElement* elemLevel1;
  DOMElement* elemLevel2;
  EventHolder *currEventHolder;
  EventHolderMap::iterator itEHM;
  GeRtiFactory::Time tmpTime;
  RemoveWithTime *currRemoveWithTime;
  RemoveWithTimeMultimap::iterator itRWTM;
  RTI::EventRetractionHandle *currEventRetractionHandle;
  TimeErMultimap::iterator itTEM;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[10000];
  char *tempBuf;
  std::vector <EventHolder *> *currEventHolderVector;
  std::vector <EventHolder *>::iterator itEH;
  unsigned int ui;
  unsigned long i;
  unsigned long j;
  unsigned long length;
  unsigned long ul;
  unsigned long valueLength;

  // Event Handler save values.
  XMLString::transcode(eventHandlerStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  // Transform remove object with time to XML.
  XMLString::transcode(removeObjectsWithTimeStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  for (itRWTM = removeObjectsWithTime.begin(); itRWTM != removeObjectsWithTime.end(); itRWTM++)
  {
    currRemoveWithTime = itRWTM->second;

    // Object.
    XMLString::transcode(objectStr.c_str(), tempStr, 99);
    elemLevel1 = theDOMDocument.createElement(tempStr);
    elemLevel0->appendChild(elemLevel1);

    // Retraction handle.
    XMLString::transcode(retractHandleStr.c_str(), tempStr, 99);
    elemLevel2 = theDOMDocument.createElement(tempStr);
    elemLevel1->appendChild(elemLevel2);
    XMLString::transcode(theSerialNumberStr.c_str(), tempStr, 99);
    sprintf(buf, "%lu", currRemoveWithTime->retractionHandle.theSerialNumber);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);
    XMLString::transcode(sendingFederateStr.c_str(), tempStr, 99);
    sprintf(buf, "%lu", currRemoveWithTime->retractionHandle.sendingFederate);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);

    // Tag.
    XMLString::transcode(userTagStr.c_str(), tempStr, 99);
    length = currRemoveWithTime->myTag.length();
    for (i = 0; i < length; i++)
    {
      ui = currRemoveWithTime->myTag[i];
      sprintf(&buf[2 * i], "%02x", ui);
    }
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel1->setAttribute(tempStr, tempStr1);

    // Time.
    XMLString::transcode(timeStr.c_str(), tempStr, 99);
    GERTICO::ConvertTime::mapIt(tmpTime, *currRemoveWithTime->myTime);
    length = tmpTime.length();
    for (i = 0; i < length; i++)
    {
      sprintf(&buf[2 * i], "%02x", tmpTime[i]);
    }
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel1->setAttribute(tempStr, tempStr1);

    // Id.
    XMLString::transcode(idStr.c_str(), tempStr, 99);
    ul = currRemoveWithTime->objectId;
    sprintf(buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel1->setAttribute(tempStr, tempStr1);
  }

  // Transform events with time to XML.
  XMLString::transcode(tsoEventsStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  for (itEHM = eventsTimedMap.begin(); itEHM != eventsTimedMap.end(); itEHM++)
  {
    currEventHolderVector = &itEHM->second;

    for (itEH = currEventHolderVector->begin(); itEH != currEventHolderVector->end(); itEH++)
    {
      currEventHolder = *itEH;

      // Event.
      XMLString::transcode(eventStr.c_str(), tempStr, 99);
      elemLevel1 = theDOMDocument.createElement(tempStr);
      elemLevel0->appendChild(elemLevel1);

      // Type.
      XMLString::transcode(typeStr.c_str(), tempStr, 99);
      switch(currEventHolder->type)
      {
        case GeRtiFactory::interaction:
        {
          strcpy(buf, "interaction");
          break;
        }
        case GeRtiFactory::obj:
        {
          strcpy(buf, "object");
          break;
        }
      }
      XMLString::transcode(buf, tempStr1, 99);
      elemLevel1->setAttribute(tempStr, tempStr1);

      // Value pairs.
      XMLString::transcode(valuePairsStr.c_str(), tempStr, 99);
      elemLevel1 = theDOMDocument.createElement(tempStr);
      elemLevel0->appendChild(elemLevel1);

      switch(currEventHolder->type)
      {
        case GeRtiFactory::interaction:
        {
          length = currEventHolder->phvps->size();
          for (i = 0; i < length; i++)
          {
            // Value pair.
            XMLString::transcode(valuePairStr.c_str(), tempStr, 99);
            elemLevel2 = theDOMDocument.createElement(tempStr);
            elemLevel1->appendChild(elemLevel2);

            XMLString::transcode(idStr.c_str(), tempStr, 99);
            sprintf(buf, "%lu", currEventHolder->phvps->getHandle(i));
            XMLString::transcode(buf, tempStr1, 99);
            elemLevel2->setAttribute(tempStr, tempStr1);

            XMLString::transcode(valueStr.c_str(), tempStr, 99);
            valueLength = currEventHolder->phvps->getValueLength(i);
            tempBuf = new char[valueLength];
            currEventHolder->phvps->getValue(i, tempBuf, valueLength);
            for (j = 0; j < valueLength; j++)
            {
              sprintf(&buf[2 * j], "%02x", tempBuf[j]);
            }
            delete[] tempBuf;
            elemLevel2->setAttribute(tempStr, tempStr1);
          }
          break;
        }
        case GeRtiFactory::obj:
        {
          length = currEventHolder->ahvps->size();
          for (i = 0; i < length; i++)
          {
            // Value pair.
            XMLString::transcode(valuePairStr.c_str(), tempStr, 99);
            elemLevel2 = theDOMDocument.createElement(tempStr);
            elemLevel1->appendChild(elemLevel2);

            XMLString::transcode(idStr.c_str(), tempStr, 99);
            sprintf(buf, "%lu", currEventHolder->ahvps->getHandle(i));
            XMLString::transcode(buf, tempStr1, 99);
            elemLevel2->setAttribute(tempStr, tempStr1);

            XMLString::transcode(valueStr.c_str(), tempStr, 99);
            valueLength = currEventHolder->ahvps->getValueLength(i);
            tempBuf = new char[valueLength];
            currEventHolder->ahvps->getValue(i, tempBuf, valueLength);
            for (j = 0; j < valueLength; j++)
            {
              sprintf(&buf[2 * j], "%02x", tempBuf[j]);
            }
            delete[] tempBuf;
            elemLevel2->setAttribute(tempStr, tempStr1);
          }
          break;
        }
      }


      // Tag.
      XMLString::transcode(tagStr.c_str(), tempStr, 99);
      XMLString::transcode(currEventHolder->tag, tempStr1, 99);
      elemLevel1->setAttribute(tempStr, tempStr1);

      // Timestamp.
      XMLString::transcode(timestampStr.c_str(), tempStr, 99);
      GERTICO::ConvertTime::mapIt (tmpTime, *currEventHolder->timestamp);
      length = tmpTime.length();
      for (i = 0; i < length; i++)
      {
        sprintf(&buf[2 * i], "%02x", tmpTime[i]);
      }
      XMLString::transcode(buf, tempStr1, 99);
      elemLevel1->setAttribute(tempStr, tempStr1);

      // Retraction handle.
      XMLString::transcode(retractHandleStr.c_str(), tempStr, 99);
      elemLevel2 = theDOMDocument.createElement(tempStr);
      elemLevel1->appendChild(elemLevel2);
      XMLString::transcode(theSerialNumberStr.c_str(), tempStr, 99);
      sprintf(buf, "%lu", currEventHolder->retractionHandle.theSerialNumber);
      XMLString::transcode(buf, tempStr1, 99);
      elemLevel2->setAttribute(tempStr, tempStr1);
      XMLString::transcode(sendingFederateStr.c_str(), tempStr, 99);
      sprintf(buf, "%lu", currEventHolder->retractionHandle.sendingFederate);
      XMLString::transcode(buf, tempStr1, 99);
      elemLevel2->setAttribute(tempStr, tempStr1);

      // Object id.
      XMLString::transcode(objectStr.c_str(), tempStr, 99);
      sprintf(buf, "%lu", currEventHolder->objectId);
      XMLString::transcode(buf, tempStr1, 99);
      elemLevel1->setAttribute(tempStr, tempStr1);

      // Class id.
      XMLString::transcode(classStr.c_str(), tempStr, 99);
      sprintf(buf, "%lu", currEventHolder->classId);
      XMLString::transcode(buf, tempStr1, 99);
      elemLevel1->setAttribute(tempStr, tempStr1);

      // Region id.
      XMLString::transcode(regionStr.c_str(), tempStr, 99);
      sprintf(buf, "%lu", currEventHolder->region);
      XMLString::transcode(buf, tempStr1, 99);
      elemLevel1->setAttribute(tempStr, tempStr1);
    }
  }

  // Transform retract handles to XML.
  XMLString::transcode(retractHandlesStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  for (itTEM = timeErMultimap.begin(); itTEM != timeErMultimap.end(); itTEM++)
  {
    currEventRetractionHandle = &itTEM->second;

    // Retraction handle.
    XMLString::transcode(retractHandleStr.c_str(), tempStr, 99);
    elemLevel1 = theDOMDocument.createElement(tempStr);
    elemLevel0->appendChild(elemLevel1);
    XMLString::transcode(theSerialNumberStr.c_str(), tempStr, 99);
    sprintf(buf, "%lu", currEventRetractionHandle->theSerialNumber);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel1->setAttribute(tempStr, tempStr1);
    XMLString::transcode(sendingFederateStr.c_str(), tempStr, 99);
    sprintf(buf, "%lu", currEventRetractionHandle->sendingFederate);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel1->setAttribute(tempStr, tempStr1);

    // Time.
    XMLString::transcode(timeStr.c_str(), tempStr, 99);
    GERTICO::ConvertTime::mapIt(tmpTime, *itTEM->first);
    length = tmpTime.length();
    for (i = 0; i < length; i++)
    {
      sprintf(&buf[2 * i], "%02x", tmpTime[i]);
    }
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel1->setAttribute(tempStr, tempStr1);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::setDisableTimeConstrainedd (void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::setDisableTimeConstrainedd", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  gotTimeConstrainedEnabled = false;
  gotTimeConstrainedEnabledFlag = false;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::setDisableTimeConstrainedd", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::setDisableTimeRegulation (void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::setDisableTimeRegulation", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  gotTimeRegulationEnabled = false;
  gotTimeRegulationEnabledFlag = false;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::setDisableTimeRegulation", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::setRunTimeObjectDB (GERTICO::RunTimeObjectDB *theRunTimeObjectDB)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "EventHandler::setRunTimeObjectDB", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  runTimeObjectDB = theRunTimeObjectDB;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "EventHandler::setRunTimeObjectDB", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::setFederate(const GeRtiFactory::GeRtiHandle &theFederate)
{
  federateId = theFederate;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::setFederateAmbassador(RTI::FederateAmbassador *theFederateAmbassador)
{
  clear();
  init();
  receiver = theFederateAmbassador;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::setFlushQueueRequest(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::setFlushQueueRequest", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  ehRequest = EHFlush;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::setFlushQueueRequest", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::setTimeConstrainedEnabled (const GERTICO::GeRtiFedTime &theTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::setTimeConstrainedEnabled", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  *myConstrainedTime = theTime;
  gotTimeConstrainedEnabled = true;
  gotTimeConstrainedEnabledFlag = true;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::setTimeConstrainedEnabled", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::setTimeRegulationEnabled (const GERTICO::GeRtiFedTime &theTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::setTimeRegulationEnabled", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  *myRegulationTime = theTime;
  gotTimeRegulationEnabled = true;
  gotTimeRegulationEnabledFlag = true;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::setTimeRegulationEnabled", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::setTimeService(GERTICO::TimeManagementLRC *theTimeManagementLRC)
{
  timeManagementLRC = theTimeManagementLRC;
  myConstrainedTime.reset(timeManagementLRC->geRtiFedTimeFactory.makeZero());
  myRegulationTime.reset(timeManagementLRC->geRtiFedTimeFactory.makeZero());
  timeManagementLRC->myTimeSave.reset(timeManagementLRC->geRtiFedTimeFactory.makeZero());
  timeManagementLRC->myTimeSave->setPositiveInfinity();
}

// ---------------------------------------------------------------------------
// Process receive ordered messages
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler::processEventRo(const bool &enableRegulation)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::processEventRo", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  EventHolder *currEventHolder;
  std::vector <EventHolder *>::iterator it;
  bool ret = false;

  if (enableRegulation == false)
  {
    if (gotTimeConstrainedEnabled)
    {
      if (asynchronousDelivery == false)
      {
        // Only in time advancing state.
        if (ehRequest == EHNone)
        {
                           {   // inserted by Gal converter
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::processEventRo", "leave_1");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
          return ret;
                           }   // inserted by Gal converter
        }
      }
    }
  }

  pm.acquire();
  // RO messages.
  it = events.begin();
  if (it != events.end())
  {
    currEventHolder = *it;

    events.erase(it);

    switch(currEventHolder->type)
    {
      case GeRtiFactory::interaction:
      {
        if (processEventRoInteraction(*currEventHolder))
        {
          ret = true;
        }
        break;
      }
      case GeRtiFactory::obj:
      {
        if (processEventRoObject(*currEventHolder))
        {
          ret = true;
        }
        break;
      }
      default:
      {
        break;
      }
    }
    delete currEventHolder;
  }

  // Timed events lose their timestamps.
  if (gotTimeConstrainedEnabled == false)
  {
    processEventTso(false);
  }
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::processEventRo", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  return ret;
}

// ---------------------------------------------------------------------------
// Process receive ordered interaction messages
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler::processEventRoInteraction (EventHolder &currEventHolder)
{
  bool ret = false;

  ret = true;
  try
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(pERI_i0)
                            {
                              sprintf(galMsg,"interaction=%lu,tag=%s",currEventHolder.classId,currEventHolder.tag);
                              ut::printParameterHandleValuePairSet(galMsg,*(currEventHolder.phvps));
                              E1mEnd(pERI_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
    receiver->receiveInteraction(currEventHolder.classId, *(currEventHolder.phvps), currEventHolder.tag);
    interactionsReceived += 1;
    if (currEventHolder.bestEffort)
    {
      addHandleMap(currEventHolder.classId, interactionsReceivedBestEffort);
    }
    else
    {
      addHandleMap(currEventHolder.classId, interactionsReceivedReliable);
    }
  }
  catch (RTI::InteractionClassNotKnown)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pERI_ta,"InteractionClassNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch (RTI::InteractionParameterNotKnown)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pERI_ta,"InteractionParameterNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch (RTI::FederateInternalError)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pERI_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::getSubscribedAttributes (EventHolder &theEventHolder, RTI::AttributeHandleValuePairSet **theAhvps)
{
  HandleSet hs;
  HandleSet *phs = NULL;
  HandleSet::iterator itHS;
  HandleSetMap::iterator itHSM;
  HandleSetMap *classAttributes = NULL;
  HandleSetSetMap::iterator itRCA;
  GeRtiFactory::GeRtiHandle classId;
  RegisteredObject *objPtr;
  RTI::ULong i;
  RTI::ULong id;
  RTI::ULong j;
  RTI::ULong lengthj;
  char *buff;
  unsigned int size;

  *theAhvps = NULL;
  size = theEventHolder.ahvps->size();
  if (size == 0)
  {
    return;
  }

  // Find the known class.
  try
  {
    objPtr = runTimeObjectDB->getObject(theEventHolder.objectId);
    classId = objPtr->getClassId();
  }
  catch(...)
  {
    return;
  }

  // Process the attributes.
  for (i = 0; i < size; i++)
  {
    id = theEventHolder.ahvps->getHandle (i);

    // Search the regions.
    for (itRCA = regionClassAttMap.begin(); itRCA != regionClassAttMap.end (); itRCA++)
    {
      classAttributes = &itRCA->second;

      itHSM = classAttributes->find(classId);
      if (itHSM != classAttributes->end ())
      {
        phs = &itHSM->second;
        itHS = phs->find (id);
        if (itHS != phs->end ())
        {
          // Index NOT attribute!
         hs.insert (i);
        }
      }
    }
  }

  size = hs.size ();
  if (size == 0)
  {
    return;
  }

  *theAhvps = RTI::AttributeSetFactory::create(hs.size ());

  for (itHS = hs.begin (), j = 0; itHS != hs.end (); itHS++)
  {
    // Copy the attribute value.
    lengthj = theEventHolder.ahvps->getValueLength (*itHS);
    buff = new char[lengthj];
    theEventHolder.ahvps->getValue (*itHS, buff, lengthj);
    (*theAhvps)->add (theEventHolder.ahvps->getHandle (*itHS), buff, lengthj);
    delete[] buff;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::queryMinNextEventTime(GERTICO::GeRtiFedTime &theTime)
{
  EventHolderMap::iterator itEHM;

  itEHM = eventsTimedMap.begin();
  if (itEHM != eventsTimedMap.end())
  {
    theTime = *itEHM->first;
  }
  else
  {
    std::auto_ptr<GERTICO::GeRtiFedTime> t(timeManagementLRC->geRtiFedTimeFactory.makeZero());
    t->setPositiveInfinity();
    theTime = *t;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::processConfirmFederationRestorationRequest(std::wstring const &theLabel, bool const &myReason)
{
  restoreLabel = theLabel;
  if (myReason)
  {
    confirmRestoreSuccess = true;
  }
  else
  {
    confirmRestoreSuccess = false;
  }

  gotConfirmFederationRestorationRequest = true;

  pm.acquire();
  if (gotConfirmFederationRestorationRequest)
  {
    std::string rl;
    GERTICO::Mapper::mapStringFromWstring(rl, restoreLabel);
    try
    {
      if (confirmRestoreSuccess)
      {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(pCFRR_i0)
                            {
                              sprintf(galMsg,"label=%s",restoreLabel.c_str ());
                              E1mEnd(pCFRR_i0,galMsg);
                            }
                          #endif   // inserted by Gal converter
        receiver->requestFederationRestoreSucceeded(rl.c_str());
        stateRestore = true;
      }
      else
      {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(pCFRR_i1)
                            {
                              sprintf(galMsg,"label=%s",restoreLabel.c_str ());
                              E1mEnd(pCFRR_i1,galMsg);
                            }
                           #endif   // inserted by Gal converter
        receiver->requestFederationRestoreFailed(rl.c_str (), "failed");
        stateRestore = false;
      }
    }
    catch (...)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pCFRR_ts, "FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }

    gotConfirmFederationRestorationRequest = false;
  }
  pm.release();
}

// ---------------------------------------------------------------------------
// Process receive ordered object messages
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler::processEventRoObject (EventHolder &currEventHolder)
{
  RTI::AttributeHandleValuePairSet *ahvps = NULL;
  bool ret = false;

  try
  {
    // Deliver reflect only if object known
    runTimeObjectDB->getObject(currEventHolder.objectId);
  }
  catch (GeRtiFactory::ObjectNotKnown&)
  {
    ret = true;
    return ret;
  }

  getSubscribedAttributes (currEventHolder, &ahvps);

  if (ahvps == NULL)
  {
    ret = true;
    return ret;
  }

  ret = true;
  try
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(pERO_i0)
                            {
                              sprintf(galMsg,"object=%lu,tag=%s",currEventHolder.objectId,currEventHolder.tag);
                              ut::printAttributeHandleValuePairSet(galMsg, *(ahvps));
                              E1mEnd(pERO_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                            std::cout << "reflectAttributeValues before" << std::endl;
    receiver->reflectAttributeValues(currEventHolder.objectId, *(ahvps), currEventHolder.tag);
                            std::cout << "reflectAttributeValuesafter " << std::endl;
    reflectionsReceived += 1;
    if (currEventHolder.bestEffort)
    {
      addHandleMap(currEventHolder.classId, reflectionsReceivedBestEffort);
    }
    else
    {
      addHandleMap(currEventHolder.classId, reflectionsReceivedReliable);
    }
  }
  catch (RTI::ObjectNotKnown)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pERO_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch (RTI::AttributeNotKnown)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pERO_ta,"AttributeNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch (RTI::FederateOwnsAttributes)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pERO_ta,"FederateOwnsAttributes");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch (RTI::FederateInternalError)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pERO_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  delete ahvps;
  return ret;
}

// ---------------------------------------------------------------------------
// Process time stamp ordered messages
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler::processEventTso(bool const &enableRegulation)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::processEventTso", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  EventHolder *currEventHolder;
  EventHolderMap::iterator itEHM;
  std::vector <EventHolder *> *currEventHolderVector;
  std::vector <EventHolder *>::iterator itEH;
  bool ret = false;

  // Condition for delivery of events.
  if (enableRegulation == false)
  {
    if (gotTimeConstrainedEnabled)
    {
      if (timeManagementLRC->gotTimeAdvanceGrant == false)
      {
        if (ehRequest == EHTar)
        {
          if (timeManagementLRC->gotTimeAdvanceGrantIntermediate == false)
          {
            return ret;
          }
        }
        else
        {
          return ret;
        }
      }
    }
  }

  // TSO messages.
  for (itEHM = eventsTimedMap.begin(); itEHM != eventsTimedMap.end(); itEHM = eventsTimedMap.begin())
  {
    if (gotTimeConstrainedEnabled)
    {
      // A flush queue request means process all events.
      if (ehRequest != EHFlush)
      {
          if (gotAnnounceFederateSave)
          {
            // Limit on the events processed is save time.
            if (*itEHM->first > *timeManagementLRC->myTimeSave)
            {
              return ret;
            }
          }

        // Limit on the events processed is grant time.
        if (timeManagementLRC->gotTimeAdvanceGrant || enableRegulation)
        {
          if (*itEHM->first > *timeManagementLRC->myTimeTag)
          {
            return ret;
          }
        }
        else
        {
          if (ehRequest == EHTar)
          {
            if (*itEHM->first > *timeManagementLRC->myTimeTarGalt)
            {
              return ret;
            }
          }
          else
          {
            return ret;
          }
        }
      }
    }

    currEventHolderVector = &itEHM->second;

    for (itEH = currEventHolderVector->begin(); itEH != currEventHolderVector->end(); itEH = currEventHolderVector->begin())
    {
      currEventHolder = *itEH;
      currEventHolderVector->erase(itEH);

      delERHandle(currEventHolder->retractionHandle);
      switch (currEventHolder->type)
      {
        case GeRtiFactory::interaction:
        {
          if (gotTimeConstrainedEnabled)
          {
            if (processEventTsoInteraction(*currEventHolder))
            {
              ret = true;
            }
          }
          else
          {
            if (processEventRoInteraction(*currEventHolder))
            {
              ret = true;
            }
          }
          break;
        }
        case GeRtiFactory::obj:
        {
          if (gotTimeConstrainedEnabled)
          {
            if (processEventTsoObject(*currEventHolder))
            {
              ret = true;
            }
          }
          else
          {
            if (processEventRoObject(*currEventHolder))
            {
              ret = true;
            }
          }
          break;
        }
        default:
        {
          break;
        }
      }
      delete currEventHolder;
    }
    eventsTimedMap.erase(itEHM);
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler::processEventTso", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  return ret;
}

// ---------------------------------------------------------------------------
// Process time stamp ordered interaction messages
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler::processEventTsoInteraction (EventHolder &currEventHolder)
{
  bool ret = false;

  ret = true;
  try
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(pETI_i0)
                            {
                              sprintf(galMsg,"interaction=%lu,time=%s,tag=%s sendingFederate=%lu",
                                currEventHolder.classId,ut::convertLogicalTime(timeManagementLRC->geRtiFedTimeFactory, *currEventHolder.timestamp),currEventHolder.tag,currEventHolder.retractionHandle);
                              ut::printParameterHandleValuePairSet(galMsg,*(currEventHolder.phvps));
                              E1mEnd(pETI_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
    RTI::FedTime *fedTime = RTI::FedTimeFactory::makeZero();
    Mapper13::mapFedTime(*fedTime, *(currEventHolder.timestamp));
    receiver->receiveInteraction (currEventHolder.classId, *(currEventHolder.phvps), *fedTime, currEventHolder.tag, currEventHolder.retractionHandle);
    if (fedTime)
    {
      delete fedTime;
    }
    interactionsReceived += 1;
    if (currEventHolder.bestEffort)
    {
      addHandleMap(currEventHolder.classId, interactionsReceivedBestEffort);
    }
    else
    {
      addHandleMap(currEventHolder.classId, interactionsReceivedReliable);
    }
  }
  catch (RTI::InteractionClassNotKnown)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pETI_ta,"InteractionClassNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch (RTI::InteractionParameterNotKnown)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pETI_ta,"InteractionParameterNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch (RTI::InvalidFederationTime)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pETI_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch (RTI::FederateInternalError)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pETI_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  return ret;
}

// ---------------------------------------------------------------------------
// Process time stamp ordered object messages
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler::processEventTsoObject(EventHolder &currEventHolder)
{
  RTI::AttributeHandleValuePairSet *ahvps = NULL;
  bool ret = false;

  ret = true;
  try
  {
    // Deliver reflect only if object known
    runTimeObjectDB->getObject(currEventHolder.objectId);
  }
  catch (GeRtiFactory::ObjectNotKnown&)
  {
    return ret;
  }

  getSubscribedAttributes (currEventHolder, &ahvps);

  if (ahvps == NULL)
  {
                           {   // inserted by Gal converter
    return ret;
                           }   // inserted by Gal converter
  }

  try
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(pETO_i0)
                            {
                              sprintf(galMsg,"object=%lu,time=%s,tag=%s sendingFederate=%lu",
                                currEventHolder.objectId,ut::convertLogicalTime(timeManagementLRC->geRtiFedTimeFactory, *currEventHolder.timestamp),currEventHolder.tag, currEventHolder.retractionHandle);
                              ut::printAttributeHandleValuePairSet(galMsg,*(currEventHolder.ahvps));
                              E1mEnd(pETO_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
    RTI::FedTime *fedTime = RTI::FedTimeFactory::makeZero();
    Mapper13::mapFedTime(*fedTime, *(currEventHolder.timestamp));
    receiver->reflectAttributeValues(currEventHolder.objectId, *(currEventHolder.ahvps), *fedTime, currEventHolder.tag, currEventHolder.retractionHandle);
    if (fedTime)
    {
      delete fedTime;
    }
    reflectionsReceived += 1;
    if (currEventHolder.bestEffort)
    {
      addHandleMap(currEventHolder.classId, reflectionsReceivedBestEffort);
    }
    else
    {
      addHandleMap(currEventHolder.classId, reflectionsReceivedReliable);
    }
  }
  catch (RTI::ObjectNotKnown)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pETO_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch (RTI::AttributeNotKnown)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pETO_ta,"AttributeNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch (RTI::FederateOwnsAttributes)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pETO_ta,"FederateOwnsAttributes");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch (RTI::InvalidFederationTime)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pETO_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch (RTI::FederateInternalError)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pETO_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  delete ahvps;
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::processFederationRestoreBegun (void)
{
  federateState = RestorePending;

  pm.acquire();
    try
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E0(pFRB_i0);   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      receiver->federationRestoreBegun ();
    }
    catch (...)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pFRB_i0,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }

  pm.release();
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::processFederationSaved(bool const &theSuccess, GeRtiFactory::SaveFailureReason const &theFailureReason)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "EventHandler::processFederationSaved", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  federateState = Running;

  pm.acquire();
    try
    {
      if (theSuccess)
      {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pFS_i1,"Saved");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
        receiver->federationSaved ();
      }
      else
      {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pFS_i1,"Not Saved");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
        receiver->federationNotSaved ();
      }
    }
    catch (...)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pFS_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
    gotAnnounceFederateSave = false;
    stateSave = false;
    timeManagementLRC->myTimeSave->setPositiveInfinity();

  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::processInitiateFederateRestore(std::wstring const &theLabel, GeRtiFactory::GeRtiHandle const &theFederate)
{
  restoreLabel = theLabel;
  federate = theFederate;
  federateState = Restoring;

  pm.acquire();
    std::string rl;
    GERTICO::Mapper::mapStringFromWstring(rl, restoreLabel);
    try
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(pIFR_i0)
                            {
                              sprintf(galMsg,"label=%s,handle=%lu",restoreLabel.c_str (), federate);
                              E1mEnd(pIFR_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
      receiver->initiateFederateRestore(rl.c_str (), federate);
    }
    catch (...)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pIFR_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }

  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::processFederationRestored(bool const &theSuccess, GeRtiFactory::RestoreFailureReason const &theFailureReason)
{
  pm.acquire();
    try
    {
      if (theSuccess)
      {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pFR_i0,"Succeeded");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
        receiver->federationRestored();
      }
      else
      {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pFR_i0,"Failed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
        receiver->federationNotRestored();
      }
    }
    catch(...)
    {
    }

    stateRestore = false;

  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler::processInitiateFederateSave (void)
{
  CORBA::Boolean fedTimeBoolean = 0;
  CORBA::WChar *l;
  GeRtiFactory::Time fedTime;
  std::auto_ptr<GERTICO::GeRtiFedTime> galt(timeManagementLRC->geRtiFedTimeFactory.makeZero());
  bool ret = false;

  federateState = SavePending;

  pm.acquire();
  if (gotAnnounceFederateSave || timeManagementLRC->gotAnnounceFederateSaveWithTime)
  {
    if (gotTimeConstrainedEnabled)
    {
      if (gotSaveTime)
      {
        if (*timeManagementLRC->myTimeSave > *timeManagementLRC->myTimeRequested)
        {
          pm.release();
          return ret;
        }
        if (timeManagementLRC)
        {
          timeManagementLRC->queryGALT(*galt);
        }
        if (*timeManagementLRC->myTimeSave >= *galt)
        {
          pm.release();
          return ret;
        }
      }
    }

    // Test case 4623 - initiateFederateSave only in advancing state
    if (gotTimeConstrainedEnabled)
    {
      if (ehRequest == EHNone)
      {
        pm.release();
        return ret;
      }
    }

    try
    {
      if (gotSaveTime)
      {
        fedTimeBoolean = 1;
      }
      GERTICO::ConvertTime::mapIt(fedTime, *timeManagementLRC->myTimeSave);
      GERTICO::Mapper::mapWcharFromWstring(&l, saveLabel);
      geRtiAmVar->requestFederateSaveStart(l, fedTime, fedTimeBoolean);
    }
    catch(GeRtiFactory::StartNotAllowed &)
    {
      CORBA::wstring_free(l);
      pm.release();
      return ret;
    }
    catch(...)
    {
      CORBA::wstring_free(l);
      pm.release();
      return ret;
    }

    gotAnnounceFederateSave = false;

    try
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(pIFS_i0)
                            {
                              sprintf(galMsg,"label=%s",saveLabel.c_str ());
                              E1mEnd(pIFS_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
      std::string s;
      GERTICO::Mapper::mapStringFromWstring(s, saveLabel);
      receiver->initiateFederateSave(s.c_str ());
      ret = true;
      stateSave = true;
      federateState = Saving;
    }
    catch (...)
    {
//Test for ut.cpp on Linux 9.1
//pm.release();
//throw;
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pIFS_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
  }
  pm.release();
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler::processRemove (void)
{
  GERTICO::Remove *currRemove;
  char *cptr = NULL;
  size_t size;
  std::vector <Remove *>::iterator it;
  bool ret = false;

  if (gotTimeConstrainedEnabled)
  {
    if (asynchronousDelivery == false)
    {
      // Only in time advancing state.
      if (ehRequest == EHNone)
      {
        return ret;
      }
    }
  }

  // Quick way to see if there is any work to do.
  size = removeObjects.size ();
  if (size == 0)
  {
                           {   // inserted by Gal converter
    return ret;
                           }   // inserted by Gal converter
  }

  pm.acquire();
  ret = true;
  // Get begin () until all processed.
  it = removeObjects.begin();
  if (it !=  removeObjects.end())
  {
    currRemove = *it;
    removeObjects.erase (it);

    Mapper13::mapUserSuppliedTag(&cptr, *currRemove->myTag);
    try
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(pR_i0)
                            {
                              sprintf(galMsg,"object=%lu,tag=%s",currRemove->objectId, cptr);
                              E1mEnd(pR_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
      receiver->removeObjectInstance (currRemove->objectId, cptr);
    }
    catch (RTI::ObjectNotKnown)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pR_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
    catch (RTI::FederateInternalError)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pR_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }

    try
    {
      runTimeObjectDB->removeObjectInstance(currRemove->objectId);
    }
    catch (GeRtiFactory::ObjectClassNotPublished)
    {
    }

    if (cptr)
    {
      delete []cptr;
    }
    delete currRemove;
  }
  pm.release();
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler::processRemoveWithTime(bool const &enableRegulation)
{
  RemoveWithTime *currRemoveWithTime;
  RemoveWithTimeMultimap::iterator it;
  char *cptr;
  size_t size;
  bool ret = false;

  if (enableRegulation == false)
  {
    if (gotTimeConstrainedEnabled)
    {
      if (timeManagementLRC->gotTimeAdvanceGrant == false)
      {
        return ret;
      }
    }
  }

  // Quick way to see if there is any work to do.
  size = removeObjectsWithTime.size ();
  if (size == 0)
  {
                           {   // inserted by Gal converter
    return ret;
                           }   // inserted by Gal converter
  }

  // Get begin () until all processed.
  it = removeObjectsWithTime.begin();
  if (it !=  removeObjectsWithTime.end())
  {
    currRemoveWithTime = it->second;

    if (gotTimeConstrainedEnabled)
    {
      // A flush queue request means process all events.
      if (ehRequest != EHFlush)
      {
        // Limit on the events processed.
          if (gotAnnounceFederateSave)
          {
            if (*currRemoveWithTime->myTime > *timeManagementLRC->myTimeSave)
            {
              return ret;
            }
          }

        if (*currRemoveWithTime->myTime > *timeManagementLRC->myTimeTag)
        {
          return ret;
        }
      }
    }

    removeObjectsWithTime.erase (it);

//    pm.acquire();
    delERHandle (currRemoveWithTime->retractionHandle);
//    pm.release();

    try
    {
      Mapper13::mapUserSuppliedTag(&cptr, currRemoveWithTime->myTag);

      ret = true;
      if (gotTimeConstrainedEnabled)
      {
        std::auto_ptr<GERTICO::GeRtiFedTime> geRtifedTime(timeManagementLRC->geRtiFedTimeFactory.makeZero());
        *geRtifedTime = *currRemoveWithTime->myTime;

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(pRWT_i0)
                            {
                              sprintf(galMsg,"object=%lu,time=%s,tag=%s sendingFederate=%lu",currRemoveWithTime->objectId,ut::convertLogicalTime(timeManagementLRC->geRtiFedTimeFactory, *geRtifedTime),
                                cptr, currRemoveWithTime->retractionHandle);
                              E1mEnd(pRWT_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter

        try
        {
          // get object only for test if known
          RTI::FedTime *fedTime = RTI::FedTimeFactory::makeZero();
          runTimeObjectDB->getObject(currRemoveWithTime->objectId);
          Mapper13::mapFedTime(*fedTime, geRtifedTime);
          receiver->removeObjectInstance(currRemoveWithTime->objectId, *fedTime, cptr, currRemoveWithTime->retractionHandle);
          if (fedTime)
          {
            delete fedTime;
          }
        }
        catch (GeRtiFactory::ObjectNotKnown&)
        {
          // object is not known - no delete required
        }

        runTimeObjectDB->removeObjectInstance(currRemoveWithTime->objectId);
      }
      else
      {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(pRWT_i0)
                            {
                              sprintf(galMsg,"object=%lu,tag=%s",currRemoveWithTime->objectId, cptr);
                              E1mEnd(pRWT_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
        try
        {
          // get object only for test if known
          runTimeObjectDB->getObject(currRemoveWithTime->objectId);
          receiver->removeObjectInstance(currRemoveWithTime->objectId, cptr);
        }
        catch (GeRtiFactory::ObjectNotKnown&)
        {
          // object is not known - no delete required
        }
        runTimeObjectDB->removeObjectInstance(currRemoveWithTime->objectId);
      }
      delete []cptr;
    }
    catch (RTI::ObjectNotKnown)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pRWT_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
    catch (RTI::InvalidFederationTime)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pRWT_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
    catch (RTI::FederateInternalError)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pRWT_ta,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }

    delete currRemoveWithTime;
  }
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::processRequestRetraction(GeRtiFactory::ERHandle const &theHandle)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::processRequestRetraction", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  GERTICO::HandleSet *currHandleSet;
  GERTICO::HandleSet::iterator itHS;
  GERTICO::HandleSetMap::iterator itHSM;
  RTI::EventRetractionHandle eventRetractionHandle;

  pm.acquire();
  // For all federate / retractions.
  for (itHSM = retractRequests.begin (); itHSM != retractRequests.end (); itHSM = retractRequests.begin ())
  {
    // Retractions for a federate.
    currHandleSet = &itHSM->second;
    eventRetractionHandle.sendingFederate = itHSM->first;
    // For each serial number.
    for (itHS = currHandleSet->begin (); itHS != currHandleSet->end (); itHS = currHandleSet->begin ())
    {
      eventRetractionHandle.theSerialNumber = *itHS;
      processRetraction (eventRetractionHandle);
      currHandleSet->erase (itHS);
    }
    retractRequests.erase (itHSM);
  }
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::processRequestRetraction", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::processRetraction (const RTI::EventRetractionHandle &theEventRetractionHandle)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::processRetraction", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  GERTICO::ERHandleTimeMap *currERHandleTimeMap;
  GERTICO::ERHandleTimeMap::iterator itERH;
  GERTICO::HandleErMap::iterator itHEM;

  // Get event retraction handle map for this federate.
  itHEM = handleErMap.find (theEventRetractionHandle.sendingFederate);
  if (itHEM != handleErMap.end ())
  {
    currERHandleTimeMap = &itHEM->second;
    // Find event retraction handle.
    itERH = currERHandleTimeMap->find (theEventRetractionHandle.theSerialNumber);
    if (itERH != currERHandleTimeMap->end ())
    {
      if (processRetractionFlushed (itERH->second, theEventRetractionHandle) == false)
      {
        processRetractionDelete (itERH->second, theEventRetractionHandle);
      }
      currERHandleTimeMap->erase (itERH);
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::processRetraction", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::processRetractionDelete (GERTICO::GeRtiFedTime *theFedTime, const RTI::EventRetractionHandle &theEventRetractionHandle)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::processRetractionDelete", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  GERTICO::EventHolder *currEventHolder;
  GERTICO::EventHolderMap::iterator itEHM;
  GERTICO::RemoveWithTime *currRemoveWithTime;
  GERTICO::RemoveWithTimeMultimap::iterator itRWTM;
  std::vector <EventHolder *> *currEventHolderVector;
  std::vector <EventHolder *>::iterator itEH;

  // Check in TSO events.
  for (itEHM = eventsTimedMap.begin(); itEHM != eventsTimedMap.end(); )
  {
    if (*itEHM->first > *theFedTime)
    {
      // Exceed the possible time in the sorted-by-time map.
      break;
    }
    currEventHolderVector = &itEHM->second;
    for (itEH = currEventHolderVector->begin(); itEH != currEventHolderVector->end(); itEH++)
    {
      currEventHolder = *itEH;
      if (currEventHolder->retractionHandle.sendingFederate == theEventRetractionHandle.sendingFederate)
      {
        if (currEventHolder->retractionHandle.sendingFederate == theEventRetractionHandle.sendingFederate)
        {
          // Got the event.
          currEventHolderVector->erase(itEH);
          delete currEventHolder;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::processRetractionDelete", "leave_1");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
          break;
        }
      }
    }
    if (currEventHolderVector->size() == 0)
    {
      eventsTimedMap.erase(itEHM);
      itEHM = eventsTimedMap.begin();
    }
    else
    {
      itEHM++;
    }
  }

  // Check in TSO removes.
  for (itRWTM = removeObjectsWithTime.begin (); itRWTM != removeObjectsWithTime.end (); itRWTM++)
  {
    if (*itRWTM->first > *theFedTime)
    {
      // Exceed the possible time in the sorted-by-time multimap.
      break;
    }
    currRemoveWithTime = itRWTM->second;
    if (currRemoveWithTime->retractionHandle.sendingFederate == theEventRetractionHandle.sendingFederate)
    {
      if (currRemoveWithTime->retractionHandle.sendingFederate == theEventRetractionHandle.sendingFederate)
      {
        // Got the event.
        removeObjectsWithTime.erase (itRWTM);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::processRetractionDelete", "leave_2");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
        return;
      }
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::processRetractionDelete", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler::processRetractionFlushed (GERTICO::GeRtiFedTime *theFedTime, const RTI::EventRetractionHandle &theEventRetractionHandle)
{
  GERTICO::TimeErMultimap::iterator itTEM;
  RTI::EventRetractionHandle *currEventRetractionHandle;

  // Search whether event was delivered to the federate ambassador.
  for (itTEM = timeErMultimap.begin (); itTEM != timeErMultimap.end (); itTEM++)
  {
    // Check timestamps.
    if (*itTEM->first > *theFedTime)
    {
      // Did not find in the sorted-by-time multimap.
      break;
    }

    // Got a possible entry.
    currEventRetractionHandle = &itTEM->second;
    if (currEventRetractionHandle->sendingFederate == theEventRetractionHandle.sendingFederate)
    {
      // Got the federate.
      if (currEventRetractionHandle->theSerialNumber == theEventRetractionHandle.theSerialNumber)
      {
        // Got the serial number.
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(pRF_i0)
                            {
                              sprintf(galMsg,"sendingFederate=%lu",theEventRetractionHandle);
                              E1mEnd(pRF_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
        receiver->requestRetraction (theEventRetractionHandle);
        timeErMultimap.erase (itTEM);
                           {   // inserted by Gal converter
        return true;
                           }   // inserted by Gal converter
      }
    }
  }

                           {   // inserted by Gal converter
  return false;
                           }   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler::processTimedEvent(void)
{
  bool ret = false;
  bool workOutstanding = false;

  if (stateRestore || stateSave)
  {
    return ret;
  }

  if (gotAnnounceFederateSave)
  {
    if (*timeManagementLRC->myTimeTag >= *timeManagementLRC->myTimeSave)
    {
      return ret;
    }
  }

  // NB. The save status is important.
  if (eventsTimedMap.size())
  {
    pm.acquire();
    if (processEventTso(false))
    {
      pm.release();
      return true;
    }
    pm.release();
    workOutstanding = true;
  }

  if (removeObjects.size())
  {
    if (processRemove())
    {
      ret = true;
      return ret;
    }
    workOutstanding = true;
  }

  // NB. The save status is important.
  if (removeObjectsWithTime.size())
  {
    pm.acquire();
    if (processRemoveWithTime(false))
    {
      ret = true;
      pm.release();
      return ret;
    }
    pm.release();
    workOutstanding = true;
  }

  if (timeManagementLRC->gotAnnounceFederateSaveWithTime)
  {
    if (processInitiateFederateSave())
    {
      ret = true;
      return ret;
    }
    workOutstanding = true;
  }

  pm.acquire();
  if (timeManagementLRC->gotTimeAdvanceGrant)
  {
    ret = true;
    ehRequest = EHNone;
    timeManagementLRC->gotTimeAdvanceGrant = false;
    delFlushERHandle();
    removeRetractionHandle(*timeManagementLRC->myTimeTag);
    try
    {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(pT_i0)
                            {
                              char buf[512];

                              timeManagementLRC->myTimeTag->getPrintableString(buf);
                              sprintf(galMsg, "time=%s", buf);
                              E1mEnd(pT_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
      RTI::FedTime *fedTime = RTI::FedTimeFactory::makeZero();
      Mapper13::mapFedTime(*fedTime, *timeManagementLRC->myTimeTag);
      timeManagementLRC->timeAdvanceGrant();
      receiver->timeAdvanceGrant(*fedTime);
    }
    catch(RTI::InvalidFederationTime)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pT_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
    catch(RTI::TimeAdvanceWasNotInProgress)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pT_ta,"TimeAdvanceWasNotInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
    catch(RTI::FederationTimeAlreadyPassed)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pT_ta,"FederationTimeAlreadyPassed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
    catch(RTI::FederateInternalError)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pT_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
  }
  pm.release();
  if (workOutstanding == false)
  {
    // Nothing to do.
    // Stop the time event job.
    ret = true;
  }
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::processTimeConEnabled(GERTICO::GeRtiFedTime const &theFedTime)
{
  *myConstrainedTime = theFedTime;
  gotTimeConstrainedEnabledFlag = true;

  pm.acquire();
  if (gotTimeConstrainedEnabledFlag)
  {
    std::auto_ptr<GERTICO::GeRtiFedTime> geRtifedTime(timeManagementLRC->geRtiFedTimeFactory.makeZero());

    *geRtifedTime = *myConstrainedTime;
    try
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(pTCE_i0)
                            {
                              sprintf(galMsg,"time=%s",ut::convertLogicalTime(timeManagementLRC->geRtiFedTimeFactory, *geRtifedTime));
                              E1mEnd(pTCE_i0,galMsg);
                            }
                          #endif   // inserted by Gal converter
      RTI::FedTime *fedTime = RTI::FedTimeFactory::makeZero();
      Mapper13::mapFedTime(*fedTime, geRtifedTime);
      receiver->timeConstrainedEnabled (*fedTime);
      timeManagementLRC->timeConstrainedEnabled(*myConstrainedTime);
      gotTimeConstrainedEnabled = true;
      if (fedTime)
      {
        delete fedTime;
      }
    }
    catch (RTI::InvalidFederationTime)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pTCE_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
    catch (RTI::EnableTimeConstrainedWasNotPending)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pTCE_ta,"EnableTimeConstrainedWasNotPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
    catch (RTI::FederateInternalError)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pTCE_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
    gotTimeConstrainedEnabledFlag = false;
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
int GERTICO::EventHandler::processTimeRegEnabled(GERTICO::GeRtiFedTime const &theFedTime)
{
  int ret = 0;

  *myRegulationTime = theFedTime;
  gotTimeRegulationEnabledFlag = true;

  if (gotTimeRegulationEnabledFlag)
  {
    try
    {
      // If already constrained, deliver
      if (gotTimeConstrainedEnabled)
      {
        if (processEventRo(true))
        {
          return 2;
        }
        pm.acquire();
        *timeManagementLRC->myTimeTag = *myRegulationTime;
        if (processEventTso(true))
        {
          pm.release();
          return 2;
        }
        pm.release();
      }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(pTRE_i0)
                            {
                              sprintf(galMsg,"time=%s",ut::convertLogicalTime(timeManagementLRC->geRtiFedTimeFactory, *timeManagementLRC->myLogicalTime));
                              E1mEnd(pTRE_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
      ret = 1;
      RTI::FedTime *fedTime = RTI::FedTimeFactory::makeZero();
      Mapper13::mapFedTime(*fedTime, *myRegulationTime);
      receiver->timeRegulationEnabled(*fedTime);
      if (fedTime)
      {
        delete fedTime;
      }
      timeManagementLRC->timeRegulationEnabled(*myRegulationTime);
    }
    catch (RTI::InvalidFederationTime)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pTRE_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
    catch (RTI::EnableTimeRegulationWasNotPending)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pTRE_ta,"EnableTimeRegulationWasNotPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
    catch (RTI::FederateInternalError)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pTRE_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }

    gotTimeRegulationEnabledFlag = false;
  }
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::removeRetractionHandle(const GERTICO::GeRtiFedTime &theFedTime)
{
  ERHandleTimeMap::iterator itERHTM;
  GERTICO::HandleSet *handleSetPtr;
  GERTICO::HandleSet::iterator itHS;
  GERTICO::GeRtiFedTime *fedTime;
  TimeERHandleMap::iterator itTERHM;

  for (itTERHM = timeERHandleMap.begin(); itTERHM != timeERHandleMap.end(); itTERHM = timeERHandleMap.begin())
  {
    fedTime = itTERHM->first;
    if (*fedTime > theFedTime)
    {
      break;
    }

    handleSetPtr = &itTERHM->second;
    for (itHS = handleSetPtr->begin(); itHS != handleSetPtr->end(); itHS++)
    {
      itERHTM = eRHandleTimeMap.find(*itHS);
      if (itERHTM != eRHandleTimeMap.end())
      {
        fedTime = itERHTM->second;
        eRHandleTimeMap.erase(itERHTM);
        delete fedTime;
      }
    }
    timeERHandleMap.erase(itTERHM);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::setGeRtiAmVar(const GeRtiFactory::GeRtiAmbassador_var &theGeRtiAmVar)
{
  geRtiAmVar = GeRtiFactory::GeRtiAmbassador::_duplicate(theGeRtiAmVar);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::setNextEventRequest(bool const &avail)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::setNextEventRequest", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  available = avail;

  ehRequest = EHNer;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::setNextEventRequest", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::setTimeAdvanceRequest(const bool &avail)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::setTimeAdvanceRequest", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  available = avail;

  ehRequest = EHTar;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::setTimeAdvanceRequest", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::GeRtiFedTime *GERTICO::EventHandler::smallestAvailableTSO (void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::smallestAvailableTSO", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  GERTICO::GeRtiFedTime *tso = NULL;
  EventHolderMap::iterator it;

  pm.acquire();
  it = eventsTimedMap.begin ();
  if (it !=  eventsTimedMap.end ())
  {
    tso = timeManagementLRC->geRtiFedTimeFactory.makeZero();
    *tso = *it->first;
  }
  pm.release();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler::smallestAvailableTSO", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  return tso;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::subscribeObjectClassAttributes (const GeRtiFactory::GeRtiHandle &theClass, const GeRtiFactory::GeRtiHandle &theRegion, const GERTICO::HandleSet &theAttributes)
{
  size_t size;
  GERTICO::HandleSet attributes;
  GERTICO::HandleSetMap classAttributes;
  GERTICO::HandleSetMap::iterator itHSM;
  GERTICO::HandleSetSetMap::iterator itRCA;

  // Find or create the region key.
  itRCA = regionClassAttMap.find (theRegion);
  if (itRCA != regionClassAttMap.end ())
  {
    // Delete any class information.
    itHSM = itRCA->second.find (theClass);
    if (itHSM != itRCA->second.end ())
    {
      itRCA->second.erase (itHSM);
    }
  }
  else
  {
    regionClassAttMap[theRegion] = classAttributes;
  }

  // Check the length.
  size = theAttributes.size();

  // Unsubscribe.
  if (size == 0)
  {
    return;
  }

  // Copy the attributes.
  attributes = theAttributes;

  // Fill class information.
  itRCA = regionClassAttMap.find (theRegion);
  if (itRCA != regionClassAttMap.end ())
  {
    itRCA->second[theClass] = attributes;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::unsubscribeObjectClassWithRegion(const GeRtiFactory::GeRtiHandle &theClass, const GeRtiFactory::GeRtiHandle &theRegion)
{
  HandleSetMap::iterator itHSM;
  HandleSetSetMap::iterator itRCA;

  // Delete the region key.
  itRCA = regionClassAttMap.find(theRegion);
  if (itRCA != regionClassAttMap.end())
  {
    // Delete any class information.
    itHSM = itRCA->second.find(theClass);
    if (itHSM != itRCA->second.end())
    {
      itRCA->second.erase(itHSM);
    }
  }
}
