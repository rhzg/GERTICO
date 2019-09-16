/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: SyncPointHandler.cpp,v $
Revision 1.31  2009/10/20 12:21:29  mul
Changed some logging events.

Revision 1.30  2009/06/12 12:55:02  mul
Use thread mutex.

Revision 1.29  2009/06/04 06:38:11  mul
Changes for level four test case.

Revision 1.28  2008/11/26 09:38:14  mul
Changed some logging.

Revision 1.27  2008/10/17 09:21:02  mul
Minor change in logging.

Revision 1.26  2007/09/06 09:14:42  mul
Changes for ieee1516.

Revision 1.25  2007/06/26 08:35:49  mul
Changes for ieee1516.

Revision 1.24  2007/05/03 15:05:03  mul
Change gal logging events.

Revision 1.23  2007/03/12 13:26:07  mul
Changed string to wstring.

Revision 1.22  2007/02/02 13:37:25  mul
Minor changes.

Revision 1.21  2006/11/28 15:51:12  mul
Use federates holder.

Revision 1.20  2006/08/30 11:50:07  mul
Add federates holder.

Revision 1.19  2005/10/05 10:00:36  mul
Change logic for CORBA exceptions.

Revision 1.18  2005/09/19 08:05:10  mul
Change callback handling.

Revision 1.17  2005/09/09 11:55:02  mul
Files from EventMarket directory.

Revision 1.9  2005/08/22 14:21:10  mul
Fix blocking mutex.

Revision 1.8  2005/08/03 13:37:46  mul
Add concurrent access logic.

Revision 1.7  2005/07/04 13:44:18  mul
Fix mutex handling for sync points.

Revision 1.6  2005/02/21 08:26:40  mul
Correct exception type.

Revision 1.5  2004/12/14 11:28:44  mul
Minor changes for verification test.

Revision 1.4  2004/09/24 07:44:55  mul
Minor changes.

Revision 1.3  2004/07/19 13:56:13  mul
removed unused variable.

Revision 1.2  2004/07/16 13:13:47  mul
Changes due to verfication test.

Revision 1.1  2004/05/27 11:58:04  mul
Changes due to subscriber integration.


**
*******************************************************************************/

#include <vector>
#include "SyncPointHandler.h"

// insert Gal file .init here
/********************************* Gal begin *********************************/   // inserted by Gal converter
   // inserted by Gal converter
// Version: 1.1   // inserted by Gal converter
// Date/Time: Mon May 12 17:02:38 2003   // inserted by Gal converter
   // inserted by Gal converter
#ifdef GalDebug   // inserted by Gal converter
#include "Gal/StdAfx.h"   // inserted by Gal converter
#include "Gal/repository_l.h"   // inserted by Gal converter
#include "Gal/event.h"   // inserted by Gal converter
//#include <strstream.h>   // inserted by Gal converter
   // inserted by Gal converter
//static char GalBuffer[256];   // inserted by Gal converter
//static class ostrstream GalOs(GalBuffer,256);   // inserted by Gal converter
   // inserted by Gal converter
static class Repository_l *FM=(Repository::getSingleInstance())->getRepository_l("GeRtiFM.res","GeRtiFM");

static class Event *GeRti_FM_feds_i=FM->getRefEvent("GeRti_FM_feds_i");
static class Event *GeRti_FM_d=FM->getRefEvent("GeRti_FM_d");
static class Event *GeRti_FM_e=FM->getRefEvent("GeRti_FM_e");
static class Event *GeRti_FM_w=FM->getRefEvent("GeRti_FM_w");
static class Event *GeRti_FM_sync_i=FM->getRefEvent("GeRti_FM_sync_i");
   // inserted by Gal converter
#endif   // inserted by Gal converter
   // inserted by Gal converter
/*********************************** Gal end *********************************/   // inserted by Gal converter

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::SyncPointFederate::SyncPointFederate (const GeRtiFactory::GeRtiHandle &theFed)
{
  fed = theFed;
  syncPointAchieved = false;
  syncPointAnnounced = false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::SyncPointFederate::~SyncPointFederate (void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::SyncPointFederate::getFed (void)
{
  return fed;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SyncPointFederate::getSyncPointAchieved (void)
{
  return syncPointAchieved;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SyncPointFederate::setSyncPointAchieved (void)
{
  syncPointAchieved = true;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SyncPointFederate::getSyncPointAnnounced (void)
{
  return syncPointAnnounced;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SyncPointFederate::setSyncPointAnnounced (void)
{
  syncPointAnnounced = true;
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::SyncPoint::SyncPoint(const std::wstring &theLabel, const GeRtiFactory::UserSuppliedTag &theTag, const GeRtiFactory::GeRtiHandle &theFederate) : tag(theTag), label (theLabel)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "SyncPoint::SyncPoint", "Enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
//  GERTICO::cSyncPointRegisterer *newSyncPointRegisterer;
  confirmed = false;
  designated = false;
  distributingFederationSynchronized = false;
  synchronized  = false;
//  newSyncPointRegisterer = new GERTICO::cSyncPointRegisterer (theFed);
//  registerers[theFed] = newSyncPointRegisterer;
  originalRegisterer = theFederate;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "SyncPoint::SyncPoint", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::SyncPoint::~SyncPoint ()
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "SyncPoint::~SyncPoint", "Enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  GERTICO::SyncPointFederate *currSyncPointFederate;
  GERTICO::cSyncPointFederateMap::iterator itSPF;

  for (itSPF = syncPointfederates.begin (); itSPF != syncPointfederates.end (); itSPF = syncPointfederates.begin ())
  {
    currSyncPointFederate = itSPF->second;
    delete currSyncPointFederate;
    syncPointfederates.erase (itSPF);
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "SyncPoint::~SyncPoint", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void  GERTICO::SyncPoint::addSyncPointFederate (const GeRtiFactory::GeRtiHandle &theFed)
{
  GERTICO::SyncPointFederate *newSyncPointFederate;

  // Do not change the designated list of federates.
  if (designated)
  {
    return;
  }

  // The game is over: no new players!
  if (synchronized)
  {
    return;
  }

  newSyncPointFederate = new GERTICO::SyncPointFederate (theFed);

  syncPointfederates[theFed] = newSyncPointFederate;
}

// ---------------------------------------------------------------------------
// If a list of federates was given to registerSynchronizationPoint.
// ---------------------------------------------------------------------------
bool GERTICO::SyncPoint::isDesignated (void)
{
  return designated;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SyncPoint::isDistributingFederationSynchronized(void)
{
  return distributingFederationSynchronized;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SyncPoint::isSynchronized (void)
{
  return synchronized;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SyncPoint::processSyncPointAchieved (GERTICO::FederatesHolder &theFederatesHolder, ACE_Thread_Mutex &pm)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "SyncPoint::processSyncPointAchieved", "Enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  GERTICO::Federate *currFederate;
  cSyncPointFederateMap::iterator itSPF;
  GERTICO::SyncPointFederate *currSyncPointFederate;

  // Check if all federates have achieved the check point.
  for (itSPF = syncPointfederates.begin (); itSPF != syncPointfederates.end (); itSPF++)
  {
    currSyncPointFederate = itSPF->second;
    if (currSyncPointFederate->getSyncPointAchieved () == false)
    {
                           {   // inserted by Gal converter
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "SyncPoint::not sync point achieved", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      return;
                           }   // inserted by Gal converter
    }
  }

  // Send federationSynchronized to all associated federates.
  distributingFederationSynchronized = true;
  for (itSPF = syncPointfederates.begin (); itSPF != syncPointfederates.end (); itSPF = syncPointfederates.begin ())
  {
    currSyncPointFederate = itSPF->second;
    syncPointfederates.erase (itSPF);
    currFederate = theFederatesHolder.getFederate(currSyncPointFederate->getFed());
    delete currSyncPointFederate;
    if (currFederate)
    {
      pm.release ();
      try
      {
        currFederate->federationSynchronized(label);
      }
      catch (CORBA::SystemException &sysex)
      {
        ACE_PRINT_EXCEPTION (sysex, "federationSynchronized");
      }
      pm.acquire ();
    }
  }
  synchronized = true;

                           {   // inserted by Gal converter
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "SyncPoint::processSyncPointAchieved", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  return;
                           }   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SyncPoint::processSyncPointRegistration (GERTICO::FederatesHolder &theFederatesHolder, ACE_Thread_Mutex &pm)
{
  GERTICO::Federate *currFederate;
  GERTICO::HandleSet hs;
  GERTICO::HandleSet::iterator itHS;
  GERTICO::SyncPointFederate *currSyncPointFederate;
  cSyncPointFederateMap::iterator itSPF;

  if (confirmed == false)
  {
    confirmed = true;
    try
    {
      pm.acquire ();
      currFederate = theFederatesHolder.getFederate(originalRegisterer);
      if (currFederate)
      {
        GeRtiFactory::SynchronizationPointFailureReason synchronizationPointFailureReason;
        pm.release ();

        // Value has no meaning!
        synchronizationPointFailureReason = GeRtiFactory::rtiDetectedFailureDuringSynchronization;

        currFederate->confirmSynchronizationPointRegistration(label, 1, synchronizationPointFailureReason);
        syncPointConfirmed = true;
        pm.acquire ();
      }
      pm.release ();
    }
    catch (CORBA::SystemException &sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "confirmSynchronizationPointRegistration");
    }
  }

  // Get a secure list of federate ids.
  pm.acquire ();
  for (itSPF = syncPointfederates.begin (); itSPF != syncPointfederates.end (); itSPF++)
  {
    hs.insert(itSPF->first);
  }
  pm.release ();

  // Work through the list of federate ids.
  pm.acquire ();
  for (itHS = hs.begin(); itHS != hs.end(); itHS++)
  {
    itSPF = syncPointfederates.find(*itHS);
    if (itSPF != syncPointfederates.end())
    {
      currSyncPointFederate = itSPF->second;
      if (currSyncPointFederate->getSyncPointAnnounced() == false)
      {
        currFederate = theFederatesHolder.getFederate(currSyncPointFederate->getFed());
        if (currFederate)
        {
          pm.release();
          try
          {
            currFederate->announceSynchronizationPoint(label, tag);
            currSyncPointFederate->setSyncPointAnnounced();
          }
          catch(CORBA::SystemException &sysex)
          {
            ACE_PRINT_EXCEPTION (sysex, "announceSynchronizationPoint");
          }
          catch (...)
          {
          }
          pm.acquire();
        }
      }
    }
  }
  pm.release ();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SyncPoint::resignFederate (const GeRtiFactory::GeRtiHandle &id)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "SyncPoint::resignFederate", "Enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  GERTICO::SyncPointFederate *currSyncPointFederate;

  cSyncPointFederateMap::iterator itSPF;

  itSPF = syncPointfederates.find (id);
  if (itSPF != syncPointfederates.end ())
  {
    currSyncPointFederate = itSPF->second;
    delete currSyncPointFederate;
    syncPointfederates.erase (itSPF);
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "SyncPoint::resignFederate", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SyncPoint::setDesignated (void)
{
  designated = true;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SyncPoint::synchronizationPointAchieved(const GeRtiFactory::GeRtiHandle &theFederate)
{
  GERTICO::SyncPointFederate *currSyncPointFederate;
  GERTICO::cSyncPointFederateMap::iterator itSPF;

  itSPF = syncPointfederates.find(theFederate);
  if (itSPF != syncPointfederates.end ())
  {
    currSyncPointFederate = itSPF->second;
    currSyncPointFederate->setSyncPointAchieved ();
  }
  else
  {
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::SyncPointHandler::SyncPointHandler(GERTICO::FederatesHolder &theFederatesHolder) : federatesHolder(theFederatesHolder)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "SyncPointHandler::SyncPointHandler", "Enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "SyncPointHandler::SyncPointHandler", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::SyncPointHandler::~SyncPointHandler ()
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "SyncPointHandler::~SyncPointHandler", "Enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  GERTICO::SyncPoint *currSyncPoint;
  SyncPointMap::iterator itSP;

  pm.acquire ();
  for (itSP = syncPoints.begin (); itSP != syncPoints.end (); itSP = syncPoints.begin ())
  {
    currSyncPoint = itSP->second;
    delete currSyncPoint;
    syncPoints.erase (itSP);
  }
  pm.release ();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "SyncPointHandler::~SyncPointHandler", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SyncPointHandler::addFederate (const GeRtiFactory::GeRtiHandle &theFed)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "SyncPointHandler::addFederate", "Enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  GERTICO::SyncPoint *currSyncPoint;
  GERTICO::SyncPointMap::iterator itSP;

  pm.acquire ();
  for (itSP = syncPoints.begin (); itSP != syncPoints.end (); itSP++)
  {
    currSyncPoint = itSP->second;
    currSyncPoint->addSyncPointFederate (theFed);
  }
  pm.release ();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "SyncPointHandler::addFederate", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}


// ---------------------------------------------------------------------------
// Clean up any references to this federate.
// ---------------------------------------------------------------------------
void GERTICO::SyncPointHandler::resignFed (const GeRtiFactory::GeRtiHandle &v_fed)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "SyncPointHandler::resignFed", "Enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  GERTICO::SyncPoint *currSyncPoint;
  SyncPointMap::iterator itSP;

  pm.acquire ();

  // For all synchronization points.
  for (itSP = syncPoints.begin (); itSP != syncPoints.end (); itSP++)
  {
    currSyncPoint = itSP->second;

    currSyncPoint->resignFederate (v_fed);
  }

  pm.release ();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "SyncPointHandler::resignFed", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
int GERTICO::SyncPointHandler::process ()
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "SyncPointHandler::process", "Enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  processSynchronizationPointRegistration ();

  processSynchronizationPointAchieved ();

  processSynchronizationPointFailures ();

                           {   // inserted by Gal converter
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "SyncPointHandler::process", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  return 0;
                           }   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// Mark current id as "synchronization point achieved" and check if all
// the others have reached the synchronization point. If yes, send
// federationSynchronized to all the federates associated with this
// synchronization point.
// ---------------------------------------------------------------------------
void GERTICO::SyncPointHandler::processSynchronizationPointAchieved ()
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "SyncPointHandler::processSynchronizationPointAchieved", "Enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  GERTICO::SyncPoint *currSyncPoint;
  std::vector <std::wstring> delSyncPoints;
  std::vector <std::wstring>::iterator itDO;

  pm.acquire ();
  SyncPointMap::iterator itSP;

  for (itSP = syncPoints.begin (); itSP != syncPoints.end (); itSP++)
  {
    currSyncPoint = itSP->second;
    currSyncPoint->processSyncPointAchieved(federatesHolder, pm);
    if (currSyncPoint->isSynchronized ())
    {
      delSyncPoints.push_back (currSyncPoint->label);
    }
  }
  for (itDO = delSyncPoints.begin (); itDO != delSyncPoints.end (); itDO = delSyncPoints.begin ())
  {
    syncPoints.erase (*itDO);
    delSyncPoints.erase (itDO);
  }
  pm.release ();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "SyncPointHandler::processSynchronizationPointAchieved", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SyncPointHandler::processSynchronizationPointFailures (void)
{
  GERTICO::Federate *currFederate;
  GERTICO::SyncFailedMap::iterator itSF;

  pm.acquire ();
  for (itSF = failures.begin (); itSF != failures.end (); itSF = failures.begin ())
  {
    currFederate = federatesHolder.getFederate(itSF->first);
    if (currFederate)
    {
      GERTICO::SyncPointData *syncPointData;
      syncPointData = &itSF->second;
      currFederate->confirmSynchronizationPointRegistration(syncPointData->label, 0, syncPointData->reason);
    }
    failures.erase (itSF);
  }
  pm.release ();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SyncPointHandler::processSynchronizationPointRegistration ()
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "SyncPointHandler::processSynchronizationPointRegistration", "Enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  GERTICO::SyncPoint *currSyncPoint;

  pm.acquire ();
  SyncPointMap::iterator itSP;

  for (itSP = syncPoints.begin (); itSP != syncPoints.end (); itSP++)
  {
    pm.release ();
    currSyncPoint = itSP->second;
    currSyncPoint->processSyncPointRegistration(federatesHolder, pm);
    pm.acquire ();
  }
  pm.release ();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "SyncPointHandler::processSynchronizationPointRegistration", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SyncPointHandler::registerSynchronizationPoint(const std::wstring &label, const GeRtiFactory::UserSuppliedTag &tag, const GeRtiFactory::Handles &designators, const GeRtiFactory::GeRtiHandle &fed)
{
  CORBA::ULong i;
  CORBA::ULong len;
  CORBA::WChar *wChar = L"";
  GERTICO::Federate *currFederate;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet::iterator itFederate;
  GERTICO::SyncPoint *newSyncPoint;
  GERTICO::SyncPointData syncPointData;
  GERTICO::SyncPointMap::iterator itSP;

  pm.acquire ();

  // check if sync Point is already in use
  itSP = syncPoints.find (label);
  if (itSP == syncPoints.end())
  {
    len = designators.length ();
    if (len > 0)
    {
      for (i = 0; i < len; i++)
      {
        currFederate = federatesHolder.getFederate(designators[i]);
        if (currFederate == NULL)
        {
          syncPointData.label = label;
          syncPointData.reason = GeRtiFactory::synchronizationSetMemberNotJoined;
          failures[fed] = syncPointData;
          pm.release ();
          return;
        }
      }
      newSyncPoint = new GERTICO::SyncPoint (label, tag, fed);
      syncPoints[label] = newSyncPoint;
      for (i = 0; i < len; i++)
      {
        newSyncPoint->addSyncPointFederate (designators[i]);
      }

      newSyncPoint->setDesignated ();
    }
    else
    {
      newSyncPoint = new GERTICO::SyncPoint (label, tag, fed);
      syncPoints[label] = newSyncPoint;
      federatesHolder.getFederates(federates);
      for (itFederate = federates.begin (); itFederate != federates.end (); itFederate++)
      {
        currFederate = federatesHolder.getFederate(*itFederate);
        newSyncPoint->addSyncPointFederate (currFederate->getId ());
      }
    }
  }
  else
  {
    GERTICO::SyncPoint *currSyncPoint;

    currSyncPoint = itSP->second;
    if (currSyncPoint->isDistributingFederationSynchronized())
    {
      pm.release ();
      throw GeRtiFactory::ConcurrentAccessAttempted(wChar);
    }

    syncPointData.label = label;
    syncPointData.reason = GeRtiFactory::synchronizationPointLabelNotUnique;
    failures[fed] = syncPointData;
  }

  pm.release ();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SyncPointHandler::synchronizationPointAchieved(const std::wstring &label, const GeRtiFactory::GeRtiHandle &id)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_sync_i, "SyncPointHandler::synchronizationPointAchieved", "Enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"";
  GERTICO::SyncPointMap::iterator itSP;
  GERTICO::SyncPoint *currSyncPoint;

  pm.acquire ();
  itSP = syncPoints.find (label);
  if (itSP != syncPoints.end ())
  {
    currSyncPoint = itSP->second;
    if (currSyncPoint->synchronizationPointAchieved (id))
    {
      pm.release ();
      throw GeRtiFactory::SynchronizationPointLabelWasNotAnnounced(wChar);
    }
  }
  else
  {
    pm.release ();
    throw GeRtiFactory::SynchronizationPointLabelWasNotAnnounced(wChar);
  }
  pm.release ();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_sync_i, "SyncPointHandler::synchronizationPointAchieved", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}
