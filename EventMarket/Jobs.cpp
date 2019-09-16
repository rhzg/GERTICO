/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
** Jobs.cpp
**
*******************************************************************************/

#include "Jobs.h"
#include "Util/Mapper.h"

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::AnnounceObjectJob::AnnounceObjectJob(const GeRtiFactory::GeRtiHandle &theClass, const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObject, GERTICO::FederatesHolder &theFederatesHolder, const std::wstring &theName, GERTICO::HandleSet &theAttributes) : federatesHolder(theFederatesHolder), attributes(theAttributes)
{
  classId = theClass;
  fedId = theFederate;
  objectId = theObject;
  objectName = theName;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::AnnounceObjectJob::~AnnounceObjectJob()
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::AnnounceObjectJob::execute ()
{
  GERTICO::Federate *currFederate;

  // Get fed ambassador for this fed.
  currFederate = federatesHolder.getFederate(fedId);
  if (currFederate == NULL)
  {
    return done;
  }

  try
  {
    currFederate->announceObjectInstance(objectId, classId, objectName, attributes);
  }
  catch (CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION (sysex, "announceObjectInstance");
    return done;
  }
  catch(...)
  {
    return done;
  }

  return done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::BeginFederationRestoreJob::BeginFederationRestoreJob(GERTICO::FederatesHolder &theFederatesHolder, const GeRtiFactory::GeRtiHandle &theFederate, const std::wstring &theLabel, const bool &theSuccess, bool &theRestoreStatus) : federatesHolder(theFederatesHolder), restoreStatus (theRestoreStatus)
{
  fed = theFederate;
  label = theLabel;
  success = theSuccess;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::BeginFederationRestoreJob::~BeginFederationRestoreJob (void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::BeginFederationRestoreJob::execute (void)
{
  GERTICO::Federate *currFederate;
  GERTICO::HandleSet::iterator itFederate;

  // How to implement????
  // success = checkRestorationStateInformation (label);

  currFederate = federatesHolder.getFederate(fed);
  if (currFederate)
  {
    try
    {
      currFederate->confirmFederationRestorationRequest (label, success);
    }
    catch(...)
    {
    }
  }
  else
  {
    restoreStatus = false;
    return GERTICO::done;
  }

  if (success)
  {
    GERTICO::HandleSet allFederates;
    GERTICO::HandleSet newFederates;
    GERTICO::HandleSet oldFederates;

    federatesHolder.getNewFederates(newFederates, oldFederates, allFederates);
    while(newFederates.size() != 0)
    {
      for (itFederate = newFederates.begin (); itFederate != newFederates.end (); itFederate++)
      {
        currFederate = federatesHolder.getFederate(*itFederate);
        if (currFederate == NULL)
        {
          continue;
        }
        try
        {
          currFederate->federationRestoreBegun();
          currFederate->initiateFederateRestore(label, currFederate->getId());
        }
        catch(...)
        {
        }
      }
      oldFederates = allFederates;
      federatesHolder.getNewFederates(newFederates, oldFederates, allFederates);
    }
  }
  else
  {
    restoreStatus = false;
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::DiscoverObjectJob::DiscoverObjectJob(const GeRtiFactory::GeRtiHandle &theClass, const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObject, GERTICO::FederatesHolder &theFederatesHolder, const std::wstring &theName) : federatesHolder(theFederatesHolder)
{
  classId = theClass;
  fedId = theFederate;
  objectId = theObject;
  objectName = theName;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::DiscoverObjectJob::~DiscoverObjectJob()
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::DiscoverObjectJob::execute ()
{
  GERTICO::Federate *currFederate;

  // Get fed ambassador for this fed.
  currFederate = federatesHolder.getFederate(fedId);
  if (currFederate == NULL)
  {
    return done;
  }

  try
  {
    currFederate->discoverObjectInstance(objectId, classId, objectName);
  }
  catch (CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION (sysex, "discoverObjectInstance");
    return done;
  }
  catch(...)
  {
    return done;
  }

  return done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FederationRestoredJob::FederationRestoredJob(GERTICO::FederatesHolder &theFederatesHolder, bool &theStatus, const bool &theSuccess, const GeRtiFactory::RestoreFailureReason &theFailureReason, bool &theConcurrencyFlag) : federatesHolder(theFederatesHolder), concurrencyFlag(theConcurrencyFlag), status(theStatus)
{
  success = theSuccess;
  failureReason = theFailureReason;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FederationRestoredJob::~FederationRestoredJob (void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::FederationRestoredJob::execute (void)
{
  Federate *currFederate;
  GERTICO::HandleSet allFederates;
  GERTICO::HandleSet newFederates;
  GERTICO::HandleSet oldFederates;
  GERTICO::HandleSet::iterator itFederate;

  concurrencyFlag = true;
  federatesHolder.getNewFederates(newFederates, oldFederates, allFederates);
  while(newFederates.size() != 0)
  {
    for (itFederate = newFederates.begin(); itFederate != newFederates.end(); itFederate++)
    {
      currFederate = federatesHolder.getFederate(*itFederate);
      if (currFederate == NULL)
      {
        continue;
      }
      try
      {
        currFederate->federationRestored(success, failureReason);
      }
      catch(...)
      {
      }
    }
    oldFederates = allFederates;
    federatesHolder.getNewFederates(newFederates, oldFederates, allFederates);
  }
  concurrencyFlag = false;
  status = false;

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FederationSavedJob::FederationSavedJob(GERTICO::FederatesHolder &theFederatesHolder, bool &theStatus, const bool &theSuccess, const GeRtiFactory::SaveFailureReason &theFailureReason, bool &theConcurrencyFlag) : federatesHolder(theFederatesHolder), concurrencyFlag(theConcurrencyFlag), status(theStatus)
{
  success = theSuccess;
  failureReason = theFailureReason;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FederationSavedJob::~FederationSavedJob (void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::FederationSavedJob::execute (void)
{
  Federate *currFederate;
  GERTICO::HandleSet allFederates;
  GERTICO::HandleSet newFederates;
  GERTICO::HandleSet oldFederates;
  GERTICO::HandleSet::iterator itFederate;

  concurrencyFlag = true;
  federatesHolder.getNewFederates(newFederates, oldFederates, allFederates);
  while(newFederates.size() != 0)
  {
    for (itFederate = newFederates.begin(); itFederate != newFederates.end(); itFederate++)
    {
      currFederate = federatesHolder.getFederate(*itFederate);
      if (currFederate == NULL)
      {
        continue;
      }
      try
      {
        currFederate->federationSaved(success, failureReason);
      }
      catch (...)
      {
      }
    }
    oldFederates = allFederates;
    federatesHolder.getNewFederates(newFederates, oldFederates, allFederates);
  }
  concurrencyFlag = false;
  status = false;

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::IntoScopeJob::IntoScopeJob(const unsigned long &theFed, const unsigned long &theObj, GERTICO::HandleSet &p_item, GERTICO::FederatesHolder &theFederatesHolder) : federatesHolder(theFederatesHolder)
{
  GERTICO::Federate *currFederate;
  GERTICO::HandleSet::iterator it;

  objectId = theObj;
  fedId = theFed;

  for (it = p_item.begin (); it != p_item.end (); it++)
  {
    items.insert (*it);
  }

  // Get fed ambassador for this fed.
  currFederate = federatesHolder.getFederate(fedId);
  if (currFederate)
  {
    try
    {
      currFederate->attributesInScope(objectId, items);
    }
    catch (...)
    {
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::IntoScopeJob::~IntoScopeJob ()
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::IntoScopeJob::execute ()
{
  GERTICO::Federate *currFederate;

  // Get fed ambassador for this fed.
  currFederate = federatesHolder.getFederate(fedId);
  if (currFederate)
  {
    try
    {
      currFederate->attributesInScopeRemote(objectId, items);
    }
    catch (...)
    {
      return done;
    }
  }

  return done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::OutOfScopeJob::OutOfScopeJob(const unsigned long &theFed, const unsigned long &theObj, const GERTICO::HandleSet &p_item, GERTICO::FederatesHolder &theFederatesHolder, const bool &theSendFlag) : federatesHolder(theFederatesHolder), sendFlag(theSendFlag)
{
  GERTICO::Federate *currFederate;
  GERTICO::HandleSet::const_iterator it;

  objectId = theObj;
  fedId = theFed;

  for (it = p_item.begin (); it != p_item.end (); it++)
  {
    items.insert (*it);
  }

  // Get fed ambassador for this fed.
  currFederate = federatesHolder.getFederate(fedId);
  if (currFederate)
  {
    try
    {
      currFederate->attributesOutOfScope(objectId, items);
    }
    catch (...)
    {
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::OutOfScopeJob::~OutOfScopeJob ()
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::OutOfScopeJob::execute ()
{
  GERTICO::Federate *currFederate;

  // Get fed ambassador for this fed.
  currFederate = federatesHolder.getFederate(fedId);
  if (currFederate)
  {
    try
    {
      currFederate->attributesOutOfScopeRemote(objectId, items, sendFlag);
    }
    catch (...)
    {
      return done;
    }
  }

  return done;
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ProvideUpdateJob::ProvideUpdateJob(const GeRtiFactory::GeRtiHandle &theObject, GERTICO::HandleSet &theAttributes, const GeRtiFactory::UserSuppliedTag &theTag, const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::FederatesHolder &theFederatesHolder) : federatesHolder(theFederatesHolder)
{
  CORBA::ULong length;
  GERTICO::HandleSet::iterator it;
  unsigned long i = 0;
  size_t size;

  objectId = theObject;
  fedId = theFederate;
  size = theAttributes.size();
  GERTICO::Mapper::mapULongSizet(length, size);
  att.length(length);
  for (it = theAttributes.begin(); it != theAttributes.end(); it++)
  {
    att[i++] = *it;
  }
  tag = theTag;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ProvideUpdateJob::~ProvideUpdateJob (void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::ProvideUpdateJob::execute(void)
{
  GERTICO::Federate *currFederate;

  // Get fed ambassador for this fed.
  currFederate = federatesHolder.getFederate(fedId);
  if (currFederate == NULL)
  {
    return done;
  }

  try
  {
    currFederate->provideAttributeValueUpdate(objectId, att, tag);
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "provideAttributeValueUpdate");
  }
  catch(...)
  {
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RemoveObject::RemoveObject (const GeRtiFactory::GeRtiHandle &v_objectId, const GeRtiFactory::GeRtiHandle &v_fedId, GERTICO::FederatesHolder &theFederatesHolder, const GeRtiFactory::UserSuppliedTag &t) : federatesHolder(theFederatesHolder), tag (t)
{
  objectId = v_objectId;
  fedId = v_fedId;
  withTime = false;
}

GERTICO::RemoveObject::RemoveObject (const GeRtiFactory::GeRtiHandle &v_objectId, const GeRtiFactory::GeRtiHandle &v_fedId, GERTICO::FederatesHolder &theFederatesHolder, const GeRtiFactory::Time &theTime, const GeRtiFactory::UserSuppliedTag &t, const GeRtiFactory::ERHandle &theERHandle) : federatesHolder(theFederatesHolder), tag (t)
{
  objectId = v_objectId;
  fedId = v_fedId;
  myTime = theTime;
  myERHandle = theERHandle;
  withTime = true;
}

GERTICO::RemoveObject::~RemoveObject (void)
{
}

GERTICO::JobStatus GERTICO::RemoveObject::execute (void)
{
  GERTICO::Federate *currFederate;

  // Get fed ambassador for this fed.
  currFederate = federatesHolder.getFederate(fedId);;
  if (currFederate == NULL)
  {
    return done;
  }

  try
  {
    if (withTime)
    {
      currFederate->removeObjectInstanceWithTime (objectId, tag, myTime, myERHandle);
    }
    else
    {
      currFederate->removeObjectInstance (objectId, tag);
    }
  }
  catch (CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION (sysex, "removeObjectInstance");
  }
  catch (...)
  {
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ReserveObjectInstanceNameJob::ReserveObjectInstanceNameJob(GERTICO::FederatesHolder &theFederatesHolder, const GeRtiFactory::GeRtiHandle &theFed, std::wstring const &theObjectInstanceName) : federatesHolder(theFederatesHolder)
{
  fed = theFed;
  objectName = theObjectInstanceName;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ReserveObjectInstanceNameJob::~ReserveObjectInstanceNameJob(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::ReserveObjectInstanceNameJob::execute()
{
  GERTICO::Federate *currFederate;

  currFederate = federatesHolder.getFederate(fed);
  if (currFederate)
  {
    try
    {
      currFederate->objectInstanceNameReservationSucceeded(objectName);
    }
    catch(CORBA::SystemException &sysex)
    {
      ACE_PRINT_EXCEPTION(sysex, "requestRetraction");
    }
    catch(...)
    {
      return done;
    }
  }

  return done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::TurnOffForObjectInstance::TurnOffForObjectInstance(CORBA::ULong const &theFederate, CORBA::ULong const &theObject, GERTICO::HandleSetMap const &theAttributeSubscribers, GERTICO::FederatesHolder &theFederatesHolder) : federatesHolder(theFederatesHolder)
{
  GERTICO::Federate *currFederate;
  GERTICO::HandleSet::iterator it;

  objectId = theObject;
  fedId = theFederate;

  attributeSubscribers = theAttributeSubscribers;

  // Get fed ambassador for this fed.
  currFederate = federatesHolder.getFederate(fedId);
  if (currFederate)
  {
    // Local call.
    currFederate->turnUpdatesOffForObjectInstance(objectId, theAttributeSubscribers);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::TurnOffForObjectInstance::~TurnOffForObjectInstance ()
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::TurnOffForObjectInstance::execute ()
{
  GERTICO::Federate *currFederate;

  // Get fed ambassador for this fed.
  currFederate = federatesHolder.getFederate(fedId);
  if (currFederate)
  {
    try
    {
      // Remote call.
      currFederate->turnUpdatesOffForObjectInstanceRemote(objectId, attributeSubscribers);
    }
    catch(CORBA::SystemException &sysex)
    {
      ACE_PRINT_EXCEPTION(sysex, "turnUpdatesOffForObjectInstance");
    }
    catch(...)
    {
      return done;
    }
  }

  return done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::TurnOnForObjectInstance::TurnOnForObjectInstance(CORBA::ULong const &theFederate, CORBA::ULong const &theObject, GERTICO::HandleSetMap const &theAttributeSubscribers, GERTICO::FederatesHolder &theFederatesHolder) : federatesHolder(theFederatesHolder)
{
  GERTICO::Federate *currFederate;
  GERTICO::HandleSet::const_iterator it;

  objectId = theObject;
  fedId = theFederate;

  attributeSubscribers = theAttributeSubscribers;

  // Get fed ambassador for this fed.
  currFederate = federatesHolder.getFederate(fedId);
  if (currFederate)
  {
    currFederate->turnUpdatesOnForObjectInstance(objectId, attributeSubscribers);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::TurnOnForObjectInstance::~TurnOnForObjectInstance ()
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::TurnOnForObjectInstance::execute ()
{
  GERTICO::Federate *currFederate;

  // Get fed ambassador for this fed.
  currFederate = federatesHolder.getFederate(fedId);
  if (currFederate)
  {
    try
    {
      currFederate->turnUpdatesOnForObjectInstanceRemote(objectId, attributeSubscribers);
    }
    catch(CORBA::SystemException &sysex)
    {
      ACE_PRINT_EXCEPTION(sysex, "turnUpdatesOnForObjectInstance");
    }
    catch(...)
    {
      return done;
    }
  }

  return done;
}
