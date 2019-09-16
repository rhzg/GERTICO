/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** ManagementObjectModel1516.cpp
**
*******************************************************************************/

#include "ManagementObjectModel.h"

#include "Util/Mapper.h"

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomReportObjectPublicationHandles::MomReportObjectPublicationHandles(void)
{
  momClassId = 0;
  federate = 0;
  numberOfClasses = 0;
  objectClass = 0;
  attributeList = 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomReportObjectPublicationHandles::~MomReportObjectPublicationHandles(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomReportInteractionPublicationHandles::MomReportInteractionPublicationHandles(void)
{
  momClassId = 0;
  federate = 0;
  interactionClassList = 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomReportInteractionPublicationHandles::~MomReportInteractionPublicationHandles(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomReportObjectSubscriptionHandles::MomReportObjectSubscriptionHandles(void)
{
  momClassId = 0;
  federate = 0;
  numberOfClasses = 0;
  objectClass = 0;
  active = 0;
  attributeList = 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomReportObjectSubscriptionHandles::~MomReportObjectSubscriptionHandles(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomReportInteractionSubscriptionHandles::MomReportInteractionSubscriptionHandles(void)
{
  momClassId = 0;
  federate = 0;
  interactionClassList = 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomReportInteractionSubscriptionHandles::~MomReportInteractionSubscriptionHandles(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomReportObjectsHandles::MomReportObjectsHandles(void)
{
  momClassId = 0;
  federate = 0;
  objectCounts = 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomReportObjectsHandles::~MomReportObjectsHandles(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomReportUpdatesSentHandles::MomReportUpdatesSentHandles(void)
{
  momClassId = 0;
  federate = 0;
  transportationType = 0;
  updateCounts = 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomReportUpdatesSentHandles::~MomReportUpdatesSentHandles(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomReportReflectionsReceivedHandles::MomReportReflectionsReceivedHandles(void)
{
  momClassId = 0;
  federate = 0;
  transportationType = 0;
  reflectCounts = 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomReportReflectionsReceivedHandles::~MomReportReflectionsReceivedHandles(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomReportInteractionsHandles::MomReportInteractionsHandles(void)
{
  momClassId = 0;
  federate = 0;
  transportationType = 0;
  interactionCounts = 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomReportInteractionsHandles::~MomReportInteractionsHandles(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomReportObjectInformationHandles::MomReportObjectInformationHandles(void)
{
  momClassId = 0;
  federate = 0;
  objectInstance = 0;
  objectAttributeList = 0;
  registeredClass = 0;
  knownClass = 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomReportObjectInformationHandles::~MomReportObjectInformationHandles(void)
{
}

#ifdef IEEE_1516
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomExceptionHandles::MomExceptionHandles(void)
{
  momClassId = 0;
  federate = 0;
  exceptionService = 0;
  exceptionException = 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomExceptionHandles::~MomExceptionHandles(void)
{
}
#else
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomAlertHandles::MomAlertHandles(void)
{
  momClassId = 0;
  federate = 0;
  alertSeverity = 0;
  alertDescription = 0;
  alertID = 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomAlertHandles::~MomAlertHandles(void)
{
}
#endif

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomReportServiceInvocationHandles::MomReportServiceInvocationHandles(void)
{
  momClassId = 0;
  federate = 0;
  service = 0;
  initiator = 0;
  successIndicator = 0;
  suppliedArguments = 0;
  returnedArguments = 0;
  exceptionDescription = 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomReportServiceInvocationHandles::~MomReportServiceInvocationHandles(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomResignFederationExecutionHandles::MomResignFederationExecutionHandles(void)
{
  momClassId = 0;
  federate = 0;
  resignAction = 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomResignFederationExecutionHandles::~MomResignFederationExecutionHandles(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomFederationTimeHandles::MomFederationTimeHandles(void)
{
  momClassId = 0;
  federate = 0;
  federationTime = 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomFederationTimeHandles::~MomFederationTimeHandles(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomRequestPublications::MomRequestPublications(GeRtiFactory::GeRtiEvent &theGeRtiEvent, GERTICO::MomReportObjectPublicationHandles &theMomReportObjectPublicationHandles, GERTICO::MomReportInteractionPublicationHandles &theMomReportInteractionPublicationHandles, GERTICO::ObjectManagement &theObjectManagement, GERTICO::FederatesHolder &theFederatesHolder, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot) : federatesHolder(theFederatesHolder), interactionRoot(theInteractionRoot), objectManagement(theObjectManagement), momReportInteractionPublicationHandles(theMomReportInteractionPublicationHandles), momReportObjectPublicationHandles(theMomReportObjectPublicationHandles)
{
  eventHandler = theEventHandler;
  geRtiEvent = theGeRtiEvent;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomRequestPublications::~MomRequestPublications(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomRequestPublications::execute (void)
{
  CORBA::ULong i;
  CORBA::ULong indd;
  CORBA::ULong lenObjects;
  CORBA::ULong lengthi;
  CORBA::ULong pos;
  CORBA::ULong ulong;
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *currFederate = NULL;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::PushEvent pushEvent;
  bool gotFederate = false;
  bool reliableFlag;
  long l;
  size_t size;
  unsigned long ul;

  lengthi = geRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (geRtiEvent.data[i].id == momReportObjectPublicationHandles.federate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, geRtiEvent.data[i].value);
      federate = l;
      if (federate)
      {
        gotFederate = true;
      }
    }
  }

  if (gotFederate)
  {
    currFederate = federatesHolder.getFederate(federate);
    if (currFederate)
    {
      GERTICO::HandleSet attributes;
      GERTICO::HandleSet publishedInteractionClasses;
      GERTICO::HandleSet publishedClasses;
      GERTICO::HandleSet::iterator itAttribute;
      GERTICO::HandleSet::iterator itPublishedInteractionClass;
      GERTICO::HandleSet::iterator itPublishedObjectClass;
      GeRtiFactory::GeRtiEvent e;
      GeRtiFactory::GeRtiHandle privilegeToDeleteId;

      currFederate->getPublishedObjectClasses(publishedClasses);
      GERTICO::Mapper::mapULongSizet(lenObjects, publishedClasses.size());

      // Check number of object classes
      if (lenObjects == 0)
      {
        // Minimum: One empty object plus one interaction class.
        e.type = GeRtiFactory::interaction;
        e.source = 1;
        e.theSerialNumber = 0;
        GERTICO::Mapper::mapUserSuppliedTag(e.theTag, "MOM");
        e.obj = 0;
        e.reg = 0;
        e._cxx_class = momReportObjectPublicationHandles.momClassId;
        classDescr = interactionRoot.getClassDescr(momReportObjectPublicationHandles.momClassId);
        if (classDescr)
        {
          classDescr->getTransportation(ul);
          if (ul)
          {
            // 1 = best effort
            reliableFlag = false;
          }
          else
          {
            // 0 = reliable
            reliableFlag = true;
          }
          e.bestEffort = ul;
          classDescr->getOrdering(ul);
          e.tso = ul;
        }

        // NB.
        e.data.length(4);

        indd = 0;
        l = federate;
        GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportObjectPublicationHandles.federate, l);

        indd += 1;
        l = 0;
        GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportObjectPublicationHandles.numberOfClasses, l);

        indd += 1;
        l = 0;
        GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportObjectPublicationHandles.objectClass, l);

        indd += 1;
        l = 0;
        GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportObjectPublicationHandles.attributeList, l);

		    pushEvent.e(e);
        if (eventHandler)
        {
          eventHandler->addEvent(pushEvent, reliableFlag, 0);
        }
      }
      else
      {
        // Object classes plus one interaction class.
        privilegeToDeleteId = objectManagement.getPrivilegeToDeleteId();
        for (itPublishedObjectClass = publishedClasses.begin(); itPublishedObjectClass != publishedClasses.end(); itPublishedObjectClass++)
        {
          e.type = GeRtiFactory::interaction;
          e.source = 1;
          e.theSerialNumber = 0;
          GERTICO::Mapper::mapUserSuppliedTag(e.theTag, "MOM");
          e.obj = 0;
          e.reg = 0;
          e._cxx_class = momReportObjectPublicationHandles.momClassId;
          classDescr = interactionRoot.getClassDescr(momReportObjectPublicationHandles.momClassId);
          if (classDescr)
          {
            classDescr->getTransportation(ul);
            if (ul)
            {
              // 1 = best effort
              reliableFlag = false;
            }
            else
            {
              // 0 = reliable
              reliableFlag = true;
            }
            e.bestEffort = ul;
            classDescr->getOrdering(ul);
            e.tso = ul;
          }

          // NB.
          e.data.length(4);

          indd = 0;
          l = federate;
          GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportObjectPublicationHandles.federate, l);

          indd += 1;
          size = publishedClasses.size();
          GERTICO::Mapper::mapULongSizet(ulong, size);
          GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportObjectPublicationHandles.numberOfClasses, ulong);

          indd += 1;
          l = *itPublishedObjectClass;
          GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportObjectPublicationHandles.objectClass, l);

          indd += 1;
          currFederate->getPublishedAttributes(*itPublishedObjectClass, attributes);
          pos = 0;
          attributes.insert(privilegeToDeleteId);
          GERTICO::Mapper::mapHLAhandleList(e.data[indd], momReportObjectPublicationHandles.attributeList, attributes);

  		    pushEvent.e(e);
          if (eventHandler)
          {
            eventHandler->addEvent(pushEvent, reliableFlag, 0);
          }
        }
      }

      e.type = GeRtiFactory::interaction;
      e.source = 1;
      e.theSerialNumber = 0;
      GERTICO::Mapper::mapUserSuppliedTag(e.theTag, "MOM");
      e.obj = 0;
      e.reg = 0;
      e._cxx_class = momReportInteractionPublicationHandles.momClassId;
      classDescr = interactionRoot.getClassDescr(momReportInteractionPublicationHandles.momClassId);
      if (classDescr)
      {
        classDescr->getTransportation(ul);
        if (ul)
        {
          // 1 = best effort
          reliableFlag = false;
        }
        else
        {
          // 0 = reliable
          reliableFlag = true;
        }
        e.bestEffort = ul;
        classDescr->getOrdering(ul);
        e.tso = ul;
      }

      // NB.
      e.data.length(2);

      indd = 0;
      l = federate;
      GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportInteractionPublicationHandles.federate, l);

      indd += 1;
//      eventHandler.declarationManagementEC->interactionHolder->getPublishedInteractionClasses(federate, publishedInteractionClasses);
      GERTICO::Mapper::mapHLAhandleList(e.data[indd], momReportInteractionPublicationHandles.interactionClassList, publishedInteractionClasses);

	    pushEvent.e(e);
      if (eventHandler)
      {
        eventHandler->addEvent(pushEvent, reliableFlag, 0);
      }
    }
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomRequestSubscriptions::MomRequestSubscriptions(GeRtiFactory::GeRtiEvent &theGeRtiEvent, GERTICO::MomReportObjectSubscriptionHandles &theMomReportObjectSubscriptionHandles, GERTICO::MomReportInteractionSubscriptionHandles &theMomReportInteractionSubscriptionHandles, GERTICO::FederatesHolder &theFederatesHolder, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot) : federatesHolder(theFederatesHolder), interactionRoot(theInteractionRoot), momReportInteractionSubscriptionHandles(theMomReportInteractionSubscriptionHandles), momReportObjectSubscriptionHandles(theMomReportObjectSubscriptionHandles)
{
  eventHandler = theEventHandler;
  geRtiEvent = theGeRtiEvent;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomRequestSubscriptions::~MomRequestSubscriptions(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomRequestSubscriptions::execute (void)
{
  CORBA::ULong i;
  CORBA::ULong indd;
  CORBA::ULong lenObjects;
  CORBA::ULong lengthi;
  CORBA::ULong ulong;
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *currFederate = NULL;
  GeRtiFactory::GeRtiEvent e;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::PushEvent pushEvent;
  bool activeBool;
  bool gotFederate = false;
  bool reliableFlag;
  long l;
  size_t size;
  unsigned long ul;

  lengthi = geRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (geRtiEvent.data[i].id == momReportObjectSubscriptionHandles.federate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, geRtiEvent.data[i].value);
      federate = l;
      if (federate)
      {
        gotFederate = true;
      }
    }
  }

  if (gotFederate)
  {
    currFederate = federatesHolder.getFederate(federate);
    if (currFederate)
    {
      GERTICO::HandleBoolMap subscribedInteractionClasses;
      GERTICO::HandleBoolMap::iterator itSubscribedInteractionClass;
      GERTICO::HandleSet attributes;
      GERTICO::HandleSet subscribedObjectClasses;
      GERTICO::HandleSet::iterator itAttribute;
      GERTICO::HandleSet::iterator itSubscribedObjectClass;

      currFederate->getSubscribedObjectClasses(subscribedObjectClasses);
      GERTICO::Mapper::mapULongSizet(lenObjects, subscribedObjectClasses.size());

      // Check number of object classes
      if (lenObjects == 0)
      {
        e.type = GeRtiFactory::interaction;
        e.source = 1;
        e.theSerialNumber = 0;
        GERTICO::Mapper::mapUserSuppliedTag(e.theTag, "MOM");
        e.obj = 0;
        e.reg = 0;
        e._cxx_class = momReportObjectSubscriptionHandles.momClassId;
        classDescr = interactionRoot.getClassDescr(momReportObjectSubscriptionHandles.momClassId);
        if (classDescr)
        {
          classDescr->getTransportation(ul);
          if (ul)
          {
            // 1 = best effort
            reliableFlag = false;
          }
          else
          {
            // 0 = reliable
            reliableFlag = true;
          }
          e.bestEffort = ul;
          classDescr->getOrdering(ul);
          e.tso = ul;
        }

        // NB.
        e.data.length(5);

        indd = 0;
        l = federate;
        GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportObjectSubscriptionHandles.federate, l);

        indd += 1;
        l = 0;
        GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportObjectSubscriptionHandles.numberOfClasses, l);

        indd += 1;
        l = 0;
        GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportObjectSubscriptionHandles.objectClass, l);

        indd += 1;
        l = 0;
        GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportObjectSubscriptionHandles.attributeList, l);

        indd += 1;
        activeBool = true;
        GERTICO::Mapper::mapHLAboolean(e.data[indd], momReportObjectSubscriptionHandles.active, activeBool);

	      pushEvent.e(e);
        if (eventHandler)
        {
          eventHandler->addEvent(pushEvent, reliableFlag, 0);
        }
      }
      else
      {
        // Object classes plus one interaction class.
        for (itSubscribedObjectClass = subscribedObjectClasses.begin(); itSubscribedObjectClass != subscribedObjectClasses.end(); itSubscribedObjectClass++)
        {
          e.type = GeRtiFactory::interaction;
          e.source = 1;
          e.theSerialNumber = 0;
          GERTICO::Mapper::mapUserSuppliedTag(e.theTag, "MOM");
          e.obj = 0;
          e.reg = 0;
          e._cxx_class = momReportObjectSubscriptionHandles.momClassId;
          classDescr = interactionRoot.getClassDescr(momReportObjectSubscriptionHandles.momClassId);
          if (classDescr)
          {
            classDescr->getTransportation(ul);
            if (ul)
            {
              // 1 = best effort
              reliableFlag = false;
            }
            else
            {
              // 0 = reliable
              reliableFlag = true;
            }
            e.bestEffort = ul;
            classDescr->getOrdering(ul);
            e.tso = ul;
          }

          // NB.
          e.data.length(5);

          indd = 0;
          l = federate;
          GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportObjectSubscriptionHandles.federate, l);

          indd += 1;
          size = subscribedObjectClasses.size();
          GERTICO::Mapper::mapULongSizet(ulong, size);
          GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportObjectSubscriptionHandles.numberOfClasses, ulong);

          indd += 1;
          l = *itSubscribedObjectClass;
          GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportObjectSubscriptionHandles.objectClass,l);

          indd += 1;
          currFederate->getSubscribedAttributes(*itSubscribedObjectClass, attributes);
          GERTICO::Mapper::mapHLAhandleList(e.data[indd], momReportObjectSubscriptionHandles.attributeList, attributes);

          indd += 1;
          activeBool = true;
          GERTICO::Mapper::mapHLAboolean(e.data[indd], momReportObjectSubscriptionHandles.active, activeBool);

	        pushEvent.e(e);
          if (eventHandler)
          {
            eventHandler->addEvent(pushEvent, reliableFlag, 0);
          }
        }
      }

      e.type = GeRtiFactory::interaction;
      e.source = 1;
      e.theSerialNumber = 0;
      GERTICO::Mapper::mapUserSuppliedTag(e.theTag, "MOM");
      e.obj = 0;
      e.reg = 0;
      e._cxx_class = momReportInteractionSubscriptionHandles.momClassId;
      classDescr = interactionRoot.getClassDescr(momReportInteractionSubscriptionHandles.momClassId);
      if (classDescr)
      {
        classDescr->getTransportation(ul);
        if (ul)
        {
          // 1 = best effort
          reliableFlag = false;
        }
        else
        {
          // 0 = reliable
          reliableFlag = true;
        }
        e.bestEffort = ul;
        classDescr->getOrdering(ul);
        e.tso = ul;
      }

      // NB.
      e.data.length(2);

      indd = 0;
      l = federate;
      GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportInteractionSubscriptionHandles.federate, l);

      indd += 1;
//      eventHandler.declarationManagementEC->interactionHolder->getSubscribedInteractionClasses(federate, subscribedInteractionClasses);
      GERTICO::Mapper::mapHLAhandleListBool(e.data[indd], momReportInteractionSubscriptionHandles.interactionClassList, subscribedInteractionClasses);

      pushEvent.e(e);
      if (eventHandler)
      {
        eventHandler->addEvent(pushEvent, reliableFlag, 0);
      }
    }
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomRequestObjectsOwned::MomRequestObjectsOwned(GeRtiFactory::GeRtiEvent &theGeRtiEvent, GERTICO::MomReportObjectsHandles &theMomReportObjectsHandles, GERTICO::ObjectManagement &theObjectManagement, GERTICO::FederatesHolder &theFederatesHolder, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot) : federatesHolder(theFederatesHolder), interactionRoot(theInteractionRoot), objectManagement(theObjectManagement), momReportObjectsHandles(theMomReportObjectsHandles)
{
  eventHandler = theEventHandler;
  geRtiEvent = theGeRtiEvent;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomRequestObjectsOwned::~MomRequestObjectsOwned(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomRequestObjectsOwned::execute (void)
{
  CORBA::ULong i;
  CORBA::ULong indd;
  CORBA::ULong lengthi;
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *currFederate = NULL;
  GeRtiFactory::GeRtiEvent e;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::PushEvent pushEvent;
  bool gotFederate = false;
  bool reliableFlag;
  long l;
  unsigned long ul;

  lengthi = geRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (geRtiEvent.data[i].id == momReportObjectsHandles.federate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, geRtiEvent.data[i].value);
      federate = l;
      if (federate)
      {
        gotFederate = true;
      }
    }
  }

  if (gotFederate)
  {
    currFederate = federatesHolder.getFederate(federate);
    if (currFederate)
    {
      GERTICO::HandleSet objects;
      GERTICO::HandleSet::iterator itObject;
      GERTICO::HandleMap handleMap;
      GERTICO::HandleMap::iterator itObjectClass;
      GeRtiFactory::GeRtiHandle knownObjectClass;

      e.type = GeRtiFactory::interaction;
      e.source = 1;
      e.theSerialNumber = 0;
      GERTICO::Mapper::mapUserSuppliedTag(e.theTag, "MOM");
      e.obj = 0;
      e.reg = 0;
      e._cxx_class = momReportObjectsHandles.momClassId;
      classDescr = interactionRoot.getClassDescr(momReportObjectsHandles.momClassId);
      if (classDescr)
      {
        classDescr->getTransportation(ul);
        if (ul)
        {
          // 1 = best effort
          reliableFlag = false;
        }
        else
        {
          // 0 = reliable
          reliableFlag = true;
        }
        e.bestEffort = ul;
        classDescr->getOrdering(ul);
        e.tso = ul;
      }

      // NB.
      e.data.length(2);

      indd = 0;
      l = federate;
      GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportObjectsHandles.federate, l);

      indd += 1;
      objectManagement.getOwnedObjectIds(federate, objects);
      for (itObject = objects.begin(); itObject != objects.end(); itObject++)
      {
        knownObjectClass = currFederate->getObjectClass(*itObject);
        itObjectClass = handleMap.find(knownObjectClass);
        if (itObjectClass != handleMap.end())
        {
          itObjectClass->second++;
        }
        else
        {
          handleMap[knownObjectClass] = 1;
        }
      }
      GERTICO::Mapper::mapHLAobjectClassBasedCounts(e.data[indd], momReportObjectsHandles.objectCounts, handleMap);

      pushEvent.e(e);
      if (eventHandler)
      {
	      eventHandler->addEvent(pushEvent, reliableFlag, 0);
      }
    }
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomRequestObjectsUpdated::MomRequestObjectsUpdated(GeRtiFactory::GeRtiEvent &theGeRtiEvent, GERTICO::MomReportObjectsHandles &theMomReportObjectsHandles, GERTICO::ObjectManagement &theObjectManagement, GERTICO::FederatesHolder &theFederatesHolder, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot) : federatesHolder(theFederatesHolder), interactionRoot(theInteractionRoot), objectManagement(theObjectManagement), momReportObjectsHandles(theMomReportObjectsHandles)
{
  eventHandler = theEventHandler;
  geRtiEvent = theGeRtiEvent;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomRequestObjectsUpdated::~MomRequestObjectsUpdated(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomRequestObjectsUpdated::execute (void)
{
  CORBA::ULong i;
  CORBA::ULong indd;
  CORBA::ULong lengthi;
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *currFederate = NULL;
  GeRtiFactory::GeRtiEvent e;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::PushEvent pushEvent;
  bool gotFederate = false;
  bool reliableFlag;
  long l;
  unsigned long ul;

  lengthi = geRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (geRtiEvent.data[i].id == momReportObjectsHandles.federate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, geRtiEvent.data[i].value);
      federate = l;
      if (federate)
      {
        gotFederate = true;
      }
    }
  }

  if (gotFederate)
  {
    currFederate = federatesHolder.getFederate(federate);
    if (currFederate)
    {
      GERTICO::HandleSet attributes;
      GERTICO::HandleSet objects;
      GERTICO::HandleSet::iterator itAttribute;
      GERTICO::HandleSet::iterator itObject;
      GERTICO::HandleMap handleMap;
      GERTICO::HandleMap::iterator itObjectClass;
      GERTICO::RegisteredObject *registeredObject;
      GeRtiFactory::GeRtiHandle knownObjectClass;
      GeRtiFactory::GeRtiHandle privilegeToDeleteId;
      bool gotTurnedOn;

      e.type = GeRtiFactory::interaction;
      e.source = 1;
      e.theSerialNumber = 0;
      GERTICO::Mapper::mapUserSuppliedTag(e.theTag, "MOM");
      e.obj = 0;
      e.reg = 0;
      e._cxx_class = momReportObjectsHandles.momClassId;
      classDescr = interactionRoot.getClassDescr(momReportObjectsHandles.momClassId);
      if (classDescr)
      {
        classDescr->getTransportation(ul);
        if (ul)
        {
          // 1 = best effort
          reliableFlag = false;
        }
        else
        {
          // 0 = reliable
          reliableFlag = true;
        }
        e.bestEffort = ul;
        classDescr->getOrdering(ul);
        e.tso = ul;
      }

      // NB.
      e.data.length(2);

      indd = 0;
      l = federate;
      GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportObjectsHandles.federate, l);

      indd += 1;
      currFederate->getKnownObjects(objects);
      for (itObject = objects.begin(); itObject != objects.end(); itObject++)
      {
        knownObjectClass = currFederate->getObjectClass(*itObject);
        registeredObject = objectManagement.getObject(*itObject);
        privilegeToDeleteId = objectManagement.getPrivilegeToDeleteId();
        registeredObject->getOwnedAttributes(federate, privilegeToDeleteId, attributes, false);
        if (attributes.size() == 0)
        {
          continue;
        }
        gotTurnedOn = false;
        for (itAttribute = attributes.begin(); itAttribute != attributes.end(); itAttribute++)
        {
          if (currFederate->testTurnedOn(*itObject, *itAttribute))
          {
            gotTurnedOn = true;
            break;
          }
        }
//        if (gotTurnedOn == false)  // XX ???????????
//        {
//          continue;
//        }
        itObjectClass = handleMap.find(knownObjectClass);
        if (itObjectClass != handleMap.end())
        {
          itObjectClass->second++;
        }
        else
        {
          handleMap[knownObjectClass] = 1;
        }
      }
      GERTICO::Mapper::mapHLAobjectClassBasedCounts(e.data[indd], momReportObjectsHandles.objectCounts, handleMap);

      pushEvent.e(e);
      if (eventHandler)
      {
	      eventHandler->addEvent(pushEvent, reliableFlag, 0);
      }
    }
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomRequestObjectsReflected::MomRequestObjectsReflected(GeRtiFactory::GeRtiEvent &theGeRtiEvent, GERTICO::MomReportObjectsHandles &theMomReportObjectsHandles, GERTICO::FederatesHolder &theFederatesHolder, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot) : federatesHolder(theFederatesHolder), interactionRoot(theInteractionRoot), momReportObjectsHandles(theMomReportObjectsHandles)
{
  eventHandler = theEventHandler;
  geRtiEvent = theGeRtiEvent;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomRequestObjectsReflected::~MomRequestObjectsReflected(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomRequestObjectsReflected::execute (void)
{
  CORBA::ULong i;
  CORBA::ULong indd;
  CORBA::ULong lengthi;
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *currFederate = NULL;
  GeRtiFactory::GeRtiEvent e;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::PushEvent pushEvent;
  bool gotFederate = false;
  bool reliableFlag;
  long l;
  unsigned long ul;

  lengthi = geRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (geRtiEvent.data[i].id == momReportObjectsHandles.federate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, geRtiEvent.data[i].value);
      federate = l;
      if (federate)
      {
        gotFederate = true;
      }
    }
  }

  if (gotFederate)
  {
    currFederate = federatesHolder.getFederate(federate);
    if (currFederate)
    {
      GERTICO::HandleSet attributes;
      GERTICO::HandleSet objects;
      GERTICO::HandleSet::iterator itAttribute;
      GERTICO::HandleSet::iterator itObject;
      GERTICO::HandleMap handleMap;
      GERTICO::HandleMap::iterator itObjectClass;
      GeRtiFactory::GeRtiHandle knownObjectClass;

      e.type = GeRtiFactory::interaction;
      e.source = 1;
      e.theSerialNumber = 0;
      GERTICO::Mapper::mapUserSuppliedTag(e.theTag, "MOM");
      e.obj = 0;
      e.reg = 0;
      e._cxx_class = momReportObjectsHandles.momClassId;
      classDescr = interactionRoot.getClassDescr(momReportObjectsHandles.momClassId);
      if (classDescr)
      {
        classDescr->getTransportation(ul);
        if (ul)
        {
          // 1 = best effort
          reliableFlag = false;
        }
        else
        {
          // 0 = reliable
          reliableFlag = true;
        }
        e.bestEffort = ul;
        classDescr->getOrdering(ul);
        e.tso = ul;
      }

      // NB.
      e.data.length(2);

      indd = 0;
      l = federate;
      GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportObjectsHandles.federate, l);

      indd += 1;
      currFederate->getKnownObjects(objects);
      for (itObject = objects.begin(); itObject != objects.end(); itObject++)
      {
        knownObjectClass = currFederate->getObjectClass(*itObject);
        currFederate->getInScope(*itObject, attributes);
        if (attributes.size() == 0)
        {
          continue;
        }
        itObjectClass = handleMap.find(knownObjectClass);
        if (itObjectClass != handleMap.end())
        {
          itObjectClass->second++;
        }
        else
        {
          handleMap[knownObjectClass] = 1;
        }
      }
      GERTICO::Mapper::mapHLAobjectClassBasedCounts(e.data[indd], momReportObjectsHandles.objectCounts, handleMap);

      pushEvent.e(e);
      if (eventHandler)
      {
	      eventHandler->addEvent(pushEvent, reliableFlag, 0);
      }
    }
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomRequestUpdatesSent::MomRequestUpdatesSent(GeRtiFactory::GeRtiEvent &theGeRtiEvent, GERTICO::MomReportUpdatesSentHandles &theMomReportUpdatesSentHandles, GERTICO::FederatesHolder &theFederatesHolder, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot) : federatesHolder(theFederatesHolder), interactionRoot(theInteractionRoot), momReportUpdatesSentHandles(theMomReportUpdatesSentHandles)
{
  eventHandler = theEventHandler;
  geRtiEvent = theGeRtiEvent;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomRequestUpdatesSent::~MomRequestUpdatesSent(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomRequestUpdatesSent::execute (void)
{
  CORBA::ULong i;
  CORBA::ULong indd;
  CORBA::ULong lengthi;
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *currFederate = NULL;
  GeRtiFactory::GeRtiEvent e;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::PushEvent pushEvent;
  bool gotFederate = false;
  bool reliableFlag;
  long l;
  unsigned long ul;

  lengthi = geRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (geRtiEvent.data[i].id == momReportUpdatesSentHandles.federate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, geRtiEvent.data[i].value);
      federate = l;
      if (federate)
      {
        gotFederate = true;
      }
    }
  }

  if (gotFederate)
  {
    currFederate = federatesHolder.getFederate(federate);
    if (currFederate)
    {
      GERTICO::HandleSet attributes;
      GERTICO::HandleSet objects;
      GERTICO::HandleSet::iterator itAttribute;
      GERTICO::HandleSet::iterator itObject;
      GERTICO::HandleMap handleMap;
      GERTICO::HandleMap::iterator itObjectClass;
      std::wstring bestEffortWstr(L"Best Effort");
      std::wstring reliableWstr(L"Reliable");

      e.type = GeRtiFactory::interaction;
      e.source = 1;
      e.theSerialNumber = 0;
      GERTICO::Mapper::mapUserSuppliedTag(e.theTag, "MOM");
      e.obj = 0;
      e.reg = 0;
      e._cxx_class = momReportUpdatesSentHandles.momClassId;
      classDescr = interactionRoot.getClassDescr(momReportUpdatesSentHandles.momClassId);
      if (classDescr)
      {
        classDescr->getTransportation(ul);
        if (ul)
        {
          // 1 = best effort
          reliableFlag = false;
        }
        else
        {
          // 0 = reliable
          reliableFlag = true;
        }
        e.bestEffort = ul;
        classDescr->getOrdering(ul);
        e.tso = ul;
      }

      // NB.
      e.data.length(3);

      indd = 0;
      l = federate;
      GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportUpdatesSentHandles.federate, l);

      indd += 1;
      GERTICO::Mapper::mapHandleValueFromWstring(e.data[indd], momReportUpdatesSentHandles.transportationType, reliableWstr);

      indd += 1;
      if (eventHandler)
      {
        eventHandler->getUpdatesSentCounts(federate, handleMap, false);
      }
      GERTICO::Mapper::mapHLAobjectClassBasedCounts(e.data[indd], momReportUpdatesSentHandles.updateCounts, handleMap);

      // NB.
      pushEvent.e(e);
      if (eventHandler)
      {
        eventHandler->addEvent(pushEvent, reliableFlag, 0);
      }

      indd = 1;
      GERTICO::Mapper::mapHandleValueFromWstring(e.data[indd], momReportUpdatesSentHandles.transportationType, bestEffortWstr);

      indd += 1;
      if (eventHandler)
      {
        eventHandler->getUpdatesSentCounts(federate, handleMap, true);
      }
      GERTICO::Mapper::mapHLAobjectClassBasedCounts(e.data[indd], momReportUpdatesSentHandles.updateCounts, handleMap);

      // NB.
      pushEvent.e(e);
      if (eventHandler)
      {
        eventHandler->addEvent(pushEvent, reliableFlag, 0);
      }
    }
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomRequestReflectionsReceived::MomRequestReflectionsReceived(GeRtiFactory::GeRtiEvent &theGeRtiEvent, GERTICO::MomReportReflectionsReceivedHandles &theMomReportReflectionsReceivedHandles, GERTICO::FederatesHolder &theFederatesHolder, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot) : federatesHolder(theFederatesHolder), interactionRoot(theInteractionRoot), momReportReflectionsReceivedHandles(theMomReportReflectionsReceivedHandles)
{
  eventHandler = theEventHandler;
  geRtiEvent = theGeRtiEvent;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomRequestReflectionsReceived::~MomRequestReflectionsReceived(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomRequestReflectionsReceived::execute (void)
{
  CORBA::ULong i;
  CORBA::ULong len;
  CORBA::ULong lengthi;
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *currFederate = NULL;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::PushEvent pushEvent;
  bool gotFederate = false;
  bool reliableFlag;
  long l;
  unsigned long ul;

  lengthi = geRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (geRtiEvent.data[i].id == momReportReflectionsReceivedHandles.federate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, geRtiEvent.data[i].value);
      federate = l;
      if (federate)
      {
        gotFederate = true;
      }
    }
  }

  if (gotFederate)
  {
    currFederate = federatesHolder.getFederate(federate);
    if (currFederate)
    {
      GERTICO::HandleSet attributes;
      GERTICO::HandleSet objects;
      GERTICO::HandleSet::iterator itAttribute;
      GERTICO::HandleSet::iterator itObject;
      GERTICO::HandleMap::iterator itObjectClass;
      GeRtiFactory::GeRtiEvent eventsBestEffort;
      GeRtiFactory::GeRtiEvent eventsReliable;
      GeRtiFactory::Handles handles;
      GeRtiFactory::HandleValues_var data;

      eventsBestEffort.type = GeRtiFactory::interaction;
      eventsBestEffort.source = 1;
      eventsBestEffort.theSerialNumber = 0;
      GERTICO::Mapper::mapUserSuppliedTag(eventsBestEffort.theTag, "MOM");
      eventsBestEffort.obj = 0;
      eventsBestEffort.reg = 0;
      eventsBestEffort._cxx_class = momReportReflectionsReceivedHandles.momClassId;
      classDescr = interactionRoot.getClassDescr(momReportReflectionsReceivedHandles.momClassId);
      if (classDescr)
      {
        classDescr->getTransportation(ul);
        if (ul)
        {
          // 1 = best effort
          reliableFlag = false;
        }
        else
        {
          // 0 = reliable
          reliableFlag = true;
        }
        eventsBestEffort.bestEffort = ul;
        classDescr->getOrdering(ul);
        eventsBestEffort.tso = ul;
      }
      eventsReliable.type = GeRtiFactory::interaction;
      eventsReliable.source = 1;
      eventsReliable.theSerialNumber = 0;
      GERTICO::Mapper::mapUserSuppliedTag(eventsReliable.theTag, "MOM");
      eventsReliable.obj = 0;
      eventsReliable.reg = 0;
      eventsReliable._cxx_class = momReportReflectionsReceivedHandles.momClassId;
      classDescr = interactionRoot.getClassDescr(momReportReflectionsReceivedHandles.momClassId);
      if (classDescr)
      {
        classDescr->getTransportation(ul);
        if (ul)
        {
          // 1 = best effort
          reliableFlag = false;
        }
        else
        {
          // 0 = reliable
          reliableFlag = true;
        }
        eventsReliable.bestEffort = ul;
        classDescr->getOrdering(ul);
        eventsReliable.tso = ul;
      }

      // NB.
      eventsBestEffort.data.length(3);
      eventsReliable.data.length(3);
      handles.length(3);
      handles[0] = momReportReflectionsReceivedHandles.federate;
      handles[1] = momReportReflectionsReceivedHandles.transportationType;
      handles[2] = momReportReflectionsReceivedHandles.reflectCounts;

      if (currFederate->getMomData(momReportReflectionsReceivedHandles.momClassId, handles, data))
      {
        return GERTICO::done;
      }

      // Double values!
      len = data->length() / 2;
      for (i = 0; i < len; i++)
      {
        if (data[i].id == momReportReflectionsReceivedHandles.federate)
        {
          eventsBestEffort.data[i] = data[i];
          eventsReliable.data[i] = data[i + len];
        }
        if (data[i].id == momReportReflectionsReceivedHandles.transportationType)
        {
          eventsBestEffort.data[i] = data[i];
          eventsReliable.data[i] = data[i + len];
        }
        if (data[i].id == momReportReflectionsReceivedHandles.reflectCounts)
        {
          eventsBestEffort.data[i] = data[i];
          eventsReliable.data[i] = data[i + len];
        }
      }
      pushEvent.e(eventsBestEffort);
      if (eventHandler)
      {
        eventHandler->addEvent(pushEvent, reliableFlag, 0);
      }

      pushEvent.e(eventsReliable);
      if (eventHandler)
      {
        eventHandler->addEvent(pushEvent, reliableFlag, 0);
      }
    }
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomRequestInteractionsSent::MomRequestInteractionsSent(GeRtiFactory::GeRtiEvent &theGeRtiEvent, GERTICO::MomReportInteractionsHandles &theMomReportInteractionsHandles, GERTICO::FederatesHolder &theFederatesHolder, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot) : federatesHolder(theFederatesHolder), interactionRoot(theInteractionRoot), momReportInteractionsHandles(theMomReportInteractionsHandles)
{
  eventHandler = theEventHandler;
  geRtiEvent = theGeRtiEvent;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomRequestInteractionsSent::~MomRequestInteractionsSent(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomRequestInteractionsSent::execute (void)
{
  CORBA::ULong i;
  CORBA::ULong indd;
  CORBA::ULong lengthi;
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *currFederate = NULL;
  GeRtiFactory::GeRtiEvent e;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::PushEvent pushEvent;
  bool gotFederate = false;
  bool reliableFlag;
  long l;
  unsigned long ul;

  lengthi = geRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (geRtiEvent.data[i].id == momReportInteractionsHandles.federate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, geRtiEvent.data[i].value);
      federate = l;
      if (federate)
      {
        gotFederate = true;
      }
    }
  }

  if (gotFederate)
  {
    currFederate = federatesHolder.getFederate(federate);
    if (currFederate)
    {
      GERTICO::HandleSet attributes;
      GERTICO::HandleSet objects;
      GERTICO::HandleSet::iterator itAttribute;
      GERTICO::HandleSet::iterator itObject;
      GERTICO::HandleMap handleMap;
      GERTICO::HandleMap::iterator itObjectClass;
      std::wstring bestEffortWstr(L"Best Effort");
      std::wstring reliableWstr(L"Reliable");

      e.type = GeRtiFactory::interaction;
      e.source = 1;
      e.theSerialNumber = 0;
      GERTICO::Mapper::mapUserSuppliedTag(e.theTag, "MOM");
      e.obj = 0;
      e.reg = 0;
      e._cxx_class = momReportInteractionsHandles.momClassId;
      classDescr = interactionRoot.getClassDescr(momReportInteractionsHandles.momClassId);
      if (classDescr)
      {
        classDescr->getTransportation(ul);
        if (ul)
        {
          // 1 = best effort
          reliableFlag = false;
        }
        else
        {
          // 0 = reliable
          reliableFlag = true;
        }
        e.bestEffort = ul;
        classDescr->getOrdering(ul);
        e.tso = ul;
      }

      // NB.
      e.data.length(3);

      indd = 0;
      l = federate;
      GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportInteractionsHandles.federate, l);

      indd += 1;
      GERTICO::Mapper::mapHandleValueFromWstring(e.data[indd], momReportInteractionsHandles.transportationType, reliableWstr);

      indd += 1;
      if (eventHandler)
      {
        eventHandler->getInteractionsSentCount(federate, handleMap, false);
      }
      GERTICO::Mapper::mapHLAobjectClassBasedCounts(e.data[indd], momReportInteractionsHandles.interactionCounts, handleMap);

      // NB.
      pushEvent.e(e);
      if (eventHandler)
      {
        eventHandler->addEvent(pushEvent, reliableFlag, 0);
      }

      indd = 1;
      GERTICO::Mapper::mapHandleValueFromWstring(e.data[indd], momReportInteractionsHandles.transportationType, bestEffortWstr);

      indd += 1;
      if (eventHandler)
      {
        eventHandler->getInteractionsSentCount(federate, handleMap, true);
      }
      GERTICO::Mapper::mapHLAobjectClassBasedCounts(e.data[indd], momReportInteractionsHandles.interactionCounts, handleMap);

      // NB.
      pushEvent.e(e);
      if (eventHandler)
      {
        eventHandler->addEvent(pushEvent, reliableFlag, 0);
      }
    }
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomRequestInteractionsReceived::MomRequestInteractionsReceived(GeRtiFactory::GeRtiEvent &theGeRtiEvent, GERTICO::MomReportInteractionsHandles &theMomReportInteractionsHandles, GERTICO::FederatesHolder &theFederatesHolder, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot) : federatesHolder(theFederatesHolder), interactionRoot(theInteractionRoot), momReportInteractionsHandles(theMomReportInteractionsHandles)
{
  eventHandler = theEventHandler;
  geRtiEvent = theGeRtiEvent;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomRequestInteractionsReceived::~MomRequestInteractionsReceived(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomRequestInteractionsReceived::execute (void)
{
  CORBA::ULong i;
  CORBA::ULong len;
  CORBA::ULong lengthi;
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *currFederate = NULL;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::PushEvent pushEvent;
  bool gotFederate = false;
  bool reliableFlag;
  long l;
  unsigned long ul;

  lengthi = geRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (geRtiEvent.data[i].id == momReportInteractionsHandles.federate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, geRtiEvent.data[i].value);
      federate = l;
      if (federate)
      {
        gotFederate = true;
      }
    }
  }

  if (gotFederate)
  {
    currFederate = federatesHolder.getFederate(federate);
    if (currFederate)
    {
      GERTICO::HandleSet attributes;
      GERTICO::HandleSet objects;
      GERTICO::HandleSet::iterator itAttribute;
      GERTICO::HandleSet::iterator itObject;
      GERTICO::HandleMap::iterator itObjectClass;
      GeRtiFactory::GeRtiEvent eventsBestEffort;
      GeRtiFactory::GeRtiEvent eventsReliable;
      GeRtiFactory::Handles handles;
      GeRtiFactory::HandleValues_var data;

      eventsBestEffort.type = GeRtiFactory::interaction;
      eventsBestEffort.source = 1;
      eventsBestEffort.theSerialNumber = 0;
      GERTICO::Mapper::mapUserSuppliedTag(eventsBestEffort.theTag, "MOM");
      eventsBestEffort.obj = 0;
      eventsBestEffort.reg = 0;
      eventsBestEffort._cxx_class = momReportInteractionsHandles.momClassId;
      classDescr = interactionRoot.getClassDescr(momReportInteractionsHandles.momClassId);
      if (classDescr)
      {
        classDescr->getTransportation(ul);
        if (ul)
        {
          // 1 = best effort
          reliableFlag = false;
        }
        else
        {
          // 0 = reliable
          reliableFlag = true;
        }
        eventsBestEffort.bestEffort = ul;
        classDescr->getOrdering(ul);
        eventsBestEffort.tso = ul;
      }
      eventsReliable.type = GeRtiFactory::interaction;
      eventsReliable.source = 1;
      eventsReliable.theSerialNumber = 0;
      GERTICO::Mapper::mapUserSuppliedTag(eventsReliable.theTag, "MOM");
      eventsReliable.obj = 0;
      eventsReliable.reg = 0;
      eventsReliable._cxx_class = momReportInteractionsHandles.momClassId;
      classDescr = interactionRoot.getClassDescr(momReportInteractionsHandles.momClassId);
      if (classDescr)
      {
        classDescr->getTransportation(ul);
        if (ul)
        {
          // 1 = best effort
          reliableFlag = false;
        }
        else
        {
          // 0 = reliable
          reliableFlag = true;
        }
        eventsReliable.bestEffort = ul;
        classDescr->getOrdering(ul);
        eventsReliable.tso = ul;
      }

      // NB.
      eventsBestEffort.data.length(3);
      eventsReliable.data.length(3);
      handles.length(3);
      handles[0] = momReportInteractionsHandles.federate;
      handles[1] = momReportInteractionsHandles.transportationType;
      handles[2] = momReportInteractionsHandles.interactionCounts;

      if (currFederate->getMomData(momReportInteractionsHandles.momClassId, handles, data))
      {
        return GERTICO::done;
      }

      // Double values!
      len = data->length() / 2;
      for (i = 0; i < len; i++)
      {
        if (data[i].id == momReportInteractionsHandles.federate)
        {
          eventsBestEffort.data[i] = data[i];
          eventsReliable.data[i] = data[i + len];
        }
        if (data[i].id == momReportInteractionsHandles.transportationType)
        {
          eventsBestEffort.data[i] = data[i];
          eventsReliable.data[i] = data[i + len];
        }
        if (data[i].id == momReportInteractionsHandles.interactionCounts)
        {
          eventsBestEffort.data[i] = data[i];
          eventsReliable.data[i] = data[i + len];
        }
      }
      pushEvent.e(eventsBestEffort);
      if (eventHandler)
      {
        eventHandler->addEvent(pushEvent, reliableFlag, 0);
      }

      pushEvent.e(eventsReliable);
      if (eventHandler)
      {
        eventHandler->addEvent(pushEvent, reliableFlag, 0);
      }
    }
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomRequestObjectsInformation::MomRequestObjectsInformation(GeRtiFactory::GeRtiEvent &theGeRtiEvent, const GeRtiFactory::GeRtiHandle &theObjectHandle, GERTICO::MomReportObjectInformationHandles &theMomReportObjectInformationHandles, GERTICO::ObjectManagement &theObjectManagement, GERTICO::FederatesHolder &theFederatesHolder, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot) : federatesHolder(theFederatesHolder), interactionRoot(theInteractionRoot), momReportObjectInformationHandles(theMomReportObjectInformationHandles), objectManagement(theObjectManagement)
{
  eventHandler = theEventHandler;
  geRtiEvent = theGeRtiEvent;
  objectHandle = theObjectHandle;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomRequestObjectsInformation::~MomRequestObjectsInformation(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomRequestObjectsInformation::execute (void)
{
  CORBA::ULong i;
  CORBA::ULong indd;
  CORBA::ULong lengthi;
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *currFederate = NULL;
  GeRtiFactory::GeRtiEvent e;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::PushEvent pushEvent;
  bool gotFederate = false;
  bool reliableFlag;
  long l;
  long objectInstance;
  unsigned long ul;

  lengthi = geRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (geRtiEvent.data[i].id == momReportObjectInformationHandles.federate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, geRtiEvent.data[i].value);
      federate = l;
      if (federate)
      {
        gotFederate = true;
      }
    }

    if (geRtiEvent.data[i].id == objectHandle)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(objectInstance, geRtiEvent.data[i].value);
    }
  }

  if (gotFederate)
  {
    currFederate = federatesHolder.getFederate(federate);
    if (currFederate)
    {
      GERTICO::HandleSet attributes;
      GERTICO::HandleSet::iterator itAttribute;
      GERTICO::HandleMap handleMap;
      GERTICO::RegisteredObject *registeredObject;
      GeRtiFactory::GeRtiHandle knownObjectClass;
      GeRtiFactory::GeRtiHandle privilegeToDeleteId;
      GeRtiFactory::GeRtiHandle registeredClass;
      std::wstring objectName;

      e.type = GeRtiFactory::interaction;
      e.source = 1;
      e.theSerialNumber = 0;
      GERTICO::Mapper::mapUserSuppliedTag(e.theTag, "MOM");
      e.obj = 0;
      e.reg = 0;
      e._cxx_class = momReportObjectInformationHandles.momClassId;
      classDescr = interactionRoot.getClassDescr(momReportObjectInformationHandles.momClassId);
      if (classDescr)
      {
        classDescr->getTransportation(ul);
        if (ul)
        {
          // 1 = best effort
          reliableFlag = false;
        }
        else
        {
          // 0 = reliable
          reliableFlag = true;
        }
        e.bestEffort = ul;
        classDescr->getOrdering(ul);
        e.tso = ul;
      }

      // NB.
      e.data.length(5);

      indd = 0;
      l = federate;
      GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportObjectInformationHandles.federate, l);

      indd += 1;
      GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportObjectInformationHandles.objectInstance, objectInstance);

      indd += 1;
      privilegeToDeleteId = objectManagement.getPrivilegeToDeleteId();
      registeredObject = objectManagement.getObject(objectInstance);
      registeredObject->getOwnedAttributes(federate, privilegeToDeleteId, attributes, true);
      GERTICO::Mapper::mapHLAhandleList(e.data[indd], momReportObjectInformationHandles.objectAttributeList, attributes);

      indd += 1;
      l = 0;
      try
      {
        // Only if the federate knows the object!
        knownObjectClass = currFederate->getObjectClass(registeredObject->getId());
        registeredClass = registeredObject->getClassId();
        l = registeredClass;
      }
      catch(...)
      {
      }
      GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportObjectInformationHandles.registeredClass, l);

      indd += 1;
      l = 0;
      try
      {
        knownObjectClass = currFederate->getObjectClass(registeredObject->getId());
        l = knownObjectClass;
      }
      catch(...)
      {
      }
      GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], momReportObjectInformationHandles.knownClass, l);

      pushEvent.e(e);
      if (eventHandler)
      {
        eventHandler->addEvent(pushEvent, reliableFlag, 0);
      }
    }
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::DoMomRequest::DoMomRequest(GeRtiFactory::GeRtiEvent &theGeRtiEvent, const GeRtiFactory::GeRtiHandle &theServiceHandle, const GeRtiFactory::GeRtiHandle &theFederateParameter, GERTICO::FederatesHolder &theFederatesHolder) : federatesHolder(theFederatesHolder)
{
  geRtiEvent = theGeRtiEvent;
  federateParameter = theFederateParameter;
  serviceHandle = theServiceHandle;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::DoMomRequest::~DoMomRequest(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::DoMomRequest::execute (void)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::Federate *currFederate = NULL;
  GeRtiFactory::GeRtiHandle federate = 0;
  bool gotFederate = false;
  long l;

  lengthi = geRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (geRtiEvent.data[i].id == federateParameter)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, geRtiEvent.data[i].value);
      federate = l;
      if (federate)
      {
        gotFederate = true;
      }
    }
  }

  if (gotFederate)
  {
    currFederate = federatesHolder.getFederate(federate);
    if (currFederate)
    {
      currFederate->doMomRequest(serviceHandle, geRtiEvent.data);
    }
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RequestManagerFederatesJob::RequestManagerFederatesJob(GERTICO::FederatesHolder &theFederatesHolder, GERTICO::MomFederateMap &theMomFederateMap, const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theAttributes, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot) : federatesHolder(theFederatesHolder), interactionRoot(theInteractionRoot), momFederateMap(theMomFederateMap)
{
  CORBA::ULong ind = 0;
  CORBA::ULong length;
  GERTICO::HandleSet::iterator itAttribute;

  eventHandler = theEventHandler;
  whichClass = theClass;

  GERTICO::Mapper::mapULongSizet(length, theAttributes.size());
  handles.length(length);
  for (itAttribute = theAttributes.begin(); itAttribute != theAttributes.end(); itAttribute++)
  {
    handles[ind] = *itAttribute;
    ind += 1;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RequestManagerFederatesJob::~RequestManagerFederatesJob(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::RequestManagerFederatesJob::execute()
{
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *currFederate;
  GeRtiFactory::GeRtiEvent e;
  GeRtiFactory::GeRtiHandle federateObject = 0;
  GeRtiFactory::PushEvent pushEvent;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet::iterator itHS;
  GERTICO::MomFederateMap::iterator itMomFederateMap;
  bool reliableFlag;
  unsigned long ul;

  federatesHolder.getFederates(federates);

  for (itHS = federates.begin(); itHS != federates.end(); itHS++)
  {
    currFederate = federatesHolder.getFederate(*itHS);
    if (currFederate)
    {
      try
      {
        GeRtiFactory::HandleValues_var data;

        if (currFederate->getMomData(whichClass, handles, data))
        {
          return done;
        }
        itMomFederateMap = momFederateMap.find(*itHS);
        if (itMomFederateMap != momFederateMap.end())
        {
          itMomFederateMap->second->getMomFederateFederate(federateObject);
        }
        e.type = GeRtiFactory::obj;
        e.source = 1;
        e.theSerialNumber = 0;
        e.data = data;
        GERTICO::Mapper::mapUserSuppliedTag(e.theTag, "MOM");
        e.obj = federateObject;
        e.reg = 0;
        e._cxx_class = whichClass;
        classDescr = interactionRoot.getClassDescr(whichClass);
        if (classDescr)
        {
          classDescr->getTransportation(ul);
          if (ul)
          {
            // 1 = best effort
            reliableFlag = false;
          }
          else
          {
            // 0 = reliable
            reliableFlag = true;
          }
          e.bestEffort = ul;
          classDescr->getOrdering(ul);
          e.tso = ul;
        }
        pushEvent.e(e);
        if (eventHandler)
        {
          eventHandler->addEvent(pushEvent, reliableFlag, 0);
        }
      }
      catch(...)
      {
      }
    }
  }

  return done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RequestManagerFederateJob::RequestManagerFederateJob(GERTICO::FederatesHolder &theFederatesHolder, GERTICO::MomFederateMap &theMomFederateMap, const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theAttributes, const GeRtiFactory::GeRtiHandle &theManagerFederateFEDid, const std::wstring theFederationFile, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot) : federatesHolder(theFederatesHolder), interactionRoot(theInteractionRoot), momFederateMap(theMomFederateMap)
{
  CORBA::ULong ind = 0;
  CORBA::ULong length;
  GERTICO::HandleSet::iterator itAttribute;

  eventHandler = theEventHandler;
  federate = theFederate;
  federationFile = theFederationFile;
  managerFederateFEDid = theManagerFederateFEDid;
  whichClass = theClass;

  GERTICO::Mapper::mapULongSizet(length, theAttributes.size());
  handles.length(length);
  for (itAttribute = theAttributes.begin(); itAttribute != theAttributes.end(); itAttribute++)
  {
    handles[ind] = *itAttribute;
    ind += 1;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RequestManagerFederateJob::~RequestManagerFederateJob(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::RequestManagerFederateJob::execute()
{
  CORBA::ULong i;
  CORBA::ULong len;
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *currFederate;
  GeRtiFactory::GeRtiEvent e;
  GeRtiFactory::GeRtiHandle federateObject = 0;
  GeRtiFactory::PushEvent pushEvent;
  GERTICO::MomFederateMap::iterator itMomFederateMap;
  GeRtiFactory::HandleValues_var data;
  bool reliableFlag;
  unsigned long ul;

  currFederate = federatesHolder.getFederate(federate);
  if (currFederate == NULL)
  {
    return done;
  }

  try
  {
    if (currFederate->getMomData(whichClass, handles, data))
    {
      return done;
    }
    len = data->length();
    for (i = 0; i < len; i++)
    {
      if (data[i].id == managerFederateFEDid)
      {
        GERTICO::Mapper::mapHLAunicodeWstring(data[i], managerFederateFEDid, federationFile);
      }
    }
    itMomFederateMap = momFederateMap.find(federate);
    if (itMomFederateMap != momFederateMap.end())
    {
      itMomFederateMap->second->getMomFederateFederate(federateObject);
    }
    e.type = GeRtiFactory::obj;
    e.source = 1;
    e.theSerialNumber = 0;
    e.data = data;
    GERTICO::Mapper::mapUserSuppliedTag(e.theTag, "MOM");
    e.obj = federateObject;
    e.reg = 0;
    e._cxx_class = whichClass;
    classDescr = interactionRoot.getClassDescr(whichClass);
    if (classDescr)
    {
      classDescr->getTransportation(ul);
      if (ul)
      {
        // 1 = best effort
        reliableFlag = false;
      }
      else
      {
        // 0 = reliable
        reliableFlag = true;
      }
      e.bestEffort = ul;
      classDescr->getOrdering(ul);
      e.tso = ul;
    }
    pushEvent.e(e);
    if (eventHandler)
    {
      eventHandler->addEvent(pushEvent, reliableFlag, 0);
    }
  }
  catch (CORBA::UserException &userex)
  {
    ACE_PRINT_EXCEPTION (userex, "RequestManagerFederateJob");
    return done;
  }
  catch(...)
  {
  }

  return done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomFederate::MomFederate(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theFederateFederate)
{
  doNow = false;
  exceptionLogging = false;
  federate = theFederate;
  momFederateFederate = theFederateFederate;
  reportPeriod = 0;
  serviceReporting = false;
  wallClockLast = 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomFederate::~MomFederate(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::MomFederate::checkExceptionLogging(void)
{
  return exceptionLogging;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::MomFederate::checkReportPeriod(const GeRtiFactory::GeRtiHandle &theWallClockCounter)
{
  if (doNow)
  {
    wallClockLast = theWallClockCounter;
    doNow = false;
    return true;
  }

  if (reportPeriod)
  {
    if (theWallClockCounter > wallClockLast + reportPeriod)
    {
      wallClockLast = theWallClockCounter;
      return true;
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::MomFederate::getMomFederateFederate(GeRtiFactory::GeRtiHandle &theMomFederateFederate)
{
  theMomFederateFederate = momFederateFederate;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::MomFederate::setExceptionLogging(const bool &theExceptionLogging)
{
  exceptionLogging = theExceptionLogging;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::MomFederate::setServiceReporting(const bool &theServiceReporting)
{
  serviceReporting = theServiceReporting;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::MomFederate::setTiming(const GeRtiFactory::GeRtiHandle &theReportPeriod)
{
  if (theReportPeriod)
  {
    doNow = true;
  }
  reportPeriod = theReportPeriod;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::SendEventsJob::SendEventsJob(GeRtiFactory::PushEvent &theE, EventHandler *theEventHandler, bool const &theReliable) : e(theE), reliableFlag(theReliable)
{
  eventHandler = theEventHandler;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::SendEventsJob::~SendEventsJob(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::SendEventsJob::execute(void)
{
  if (eventHandler)
  {
    eventHandler->addEvent(e, reliableFlag, 0);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ManagementObjectModel::ManagementObjectModel(GERTICO::DeclarationManagementRTI &theDeclarationManagement, GERTICO::ObjectManagement &theObjectManagement, GERTICO::GeRtiOwnershipMasterI &theGeRtiOwnershipMasterI, GERTICO::SupportingServices &theSupportingServices, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot, GERTICO::ClassDescrHolder &theObjectRoot, GERTICO::FederatesHolder &theFederatesHolder, GERTICO::JobHolder &theFederationJobs, ACE_Semaphore &thePs) : ps(thePs), interactionRoot(theInteractionRoot), objectRoot(theObjectRoot), declarationManagement(theDeclarationManagement), federatesHolder(theFederatesHolder), federationJobs(theFederationJobs), objectManagement(theObjectManagement), ownershipMaster(theGeRtiOwnershipMasterI), supportingServices(theSupportingServices)
{
  CORBA::Boolean active = 1;
  GERTICO::HandleSet regions;
  counter = 10;
  bool foundClass = false;
  bool foundItem = false;
  wallClockCounter = 0;

  eventHandler = theEventHandler;
  // Default region.
  regions.insert(0);

  // Manager
  std::wstring ws;
  ws = L"HLAmanager";
  managerObject = supportingServices.findObjectClassHandle(ws);
  momClasses.insert(managerObject);

  // Manager.Federate
  ws = L"HLAmanager.HLAfederate";
  managerFederateObject = supportingServices.findObjectClassHandle(ws);

  ws = L"HLAfederateHandle";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateFederateHandle, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateFederateHandle);

  ws = L"HLAfederateType";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateFederateType, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateFederateType);

  ws = L"HLAfederateHost";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateFederateHost, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateFederateHost);

  ws = L"HLARTIversion";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateRTIversion, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateRTIversion);

  ws = L"HLAFDDID";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateFDDid, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateFDDid);

  ws = L"HLAtimeConstrained";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateTimeConstrained, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateTimeConstrained);

  ws = L"HLAtimeRegulating";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateTimeRegulating, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateTimeRegulating);

  ws = L"HLAasynchronousDelivery";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateAsynchronousDelivery, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateAsynchronousDelivery);

  ws = L"HLAfederateState";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateFederateState, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateFederateState);

  ws = L"HLAtimeManagerState";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateTimeManagerState, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateTimeManagerState);

  ws = L"HLAlogicalTime";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateLogicalTime, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateLogicalTime);

  ws = L"HLAlookahead";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateLookahead, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateLookahead);

  ws = L"HLAGALT";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateGALT, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateGALT);

  ws = L"HLALITS";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateLITS, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateLITS);

  ws = L"HLAROlength";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateROlength, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateROlength);

  ws = L"HLATSOlength";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateTSOlength, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateTSOlength);

  ws = L"HLAreflectionsReceived";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateReflectionsReceived, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateReflectionsReceived);

  ws = L"HLAupdatesSent";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateUpdatesSent, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateUpdatesSent);

  ws = L"HLAinteractionsReceived";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateInteractionsReceived, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateInteractionsReceived);

  ws = L"HLAinteractionsSent";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateInteractionsSent, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateInteractionsSent);

  ws = L"HLAobjectInstancesThatCanBeDeleted";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateObjectInstancesThatCanBeDeleted, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateObjectInstancesThatCanBeDeleted);

  ws = L"HLAobjectInstancesUpdated";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateObjectInstancesUpdated, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateObjectInstancesUpdated);

  ws = L"HLAobjectInstancesReflected";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateObjectInstancesReflected, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateObjectInstancesReflected);

  ws = L"HLAobjectInstancesDeleted";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateObjectInstancesDeleted, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateObjectInstancesDeleted);

  ws = L"HLAobjectInstancesRemoved";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateObjectInstancesRemoved, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateObjectInstancesRemoved);

  ws = L"HLAobjectInstancesRegistered";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateObjectInstancesRegistered, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateObjectInstancesRegistered);

  ws = L"HLAobjectInstancesDiscovered";
  supportingServices.getObjectClassItem(ws, managerFederateObject, managerFederateObjectInstancesDiscovered, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateObjectInstancesDiscovered);

  declarationManagement.publishObjectClass(1, managerFederateObject, managerFederateAttributes);

  // Manager.Federation
  ws = L"HLAmanager.HLAfederation";
  managerFederationClass = supportingServices.findObjectClassHandle(ws);
  momClasses.insert(managerFederationClass);

  ws = L"HLAfederationName";
  supportingServices.getObjectClassItem(ws, managerFederationClass, managerFederationFederationName, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederationAttributes.insert(managerFederationFederationName);

  ws = L"HLAfederatesInFederation";
  supportingServices.getObjectClassItem(ws, managerFederationClass, managerFederationFederatesInFederation, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederationAttributes.insert(managerFederationFederatesInFederation);

  ws = L"HLARTIversion";
  supportingServices.getObjectClassItem(ws, managerFederationClass, managerFederationRTIversion, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederationAttributes.insert(managerFederationRTIversion);

  ws = L"HLAFDDID";
  supportingServices.getObjectClassItem(ws, managerFederationClass, managerFederationFDDid, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederationAttributes.insert(managerFederationFDDid);

  ws = L"HLAlastSaveName";
  supportingServices.getObjectClassItem(ws, managerFederationClass, managerFederationLastSaveName, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederationAttributes.insert(managerFederationLastSaveName);

  ws = L"HLAlastSaveTime";
  supportingServices.getObjectClassItem(ws, managerFederationClass, managerFederationLastSaveTime, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederationAttributes.insert(managerFederationLastSaveTime);

  ws = L"HLAnextSaveName";
  supportingServices.getObjectClassItem(ws, managerFederationClass, managerFederationNextSaveName, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederationAttributes.insert(managerFederationNextSaveName);

  ws = L"HLAnextSaveTime";
  supportingServices.getObjectClassItem(ws, managerFederationClass, managerFederationNextSaveTime, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  managerFederationAttributes.insert(managerFederationNextSaveTime);

  declarationManagement.publishObjectClass(1, managerFederationClass, managerFederationAttributes);

  managerFederation = objectManagement.registerObjectInstance(1, managerFederationClass);

    // MOM Interactions
  ws = L"HLAmanager";
  managerInteractionRoot = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerInteractionRoot);

  ws = L"HLAmanager.HLAfederate";
  managerInteractionFederate = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerInteractionFederate);

  ws = L"HLAfederate";
  supportingServices.getParameterHandle(ws, managerInteractionFederate, managerInteractionFederateFederate, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);

  // Adjust
  // Manager.Federate.Adjust.SetTiming
  ws = L"HLAmanager.HLAfederate.HLAadjust.HLAsetTiming";
  managerFederateAdjustSetTiming = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateAdjustSetTiming);
  declarationManagement.subscribeInteractionClass(1, managerFederateAdjustSetTiming, active, regions);
  ws = L"HLAreportPeriod";
  supportingServices.getParameterHandle(ws, managerFederateAdjustSetTiming, managerFederateAdjustSetTimingReportPeriod, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);

  // Manager.Federate.Adjust.ModifyAttributeState
  ws = L"HLAmanager.HLAfederate.HLAadjust.HLAmodifyAttributeState";
  managerFederateAdjustModifyAttributeState = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateAdjustModifyAttributeState);
  declarationManagement.subscribeInteractionClass(1, managerFederateAdjustModifyAttributeState, active, regions);
  ws = L"HLAobjectInstance";
  supportingServices.getParameterHandle(ws, managerFederateAdjustModifyAttributeState, managerFederateAdjustModifyAttributeStateObjectInstance, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAattribute";
  supportingServices.getParameterHandle(ws, managerFederateAdjustModifyAttributeState, managerFederateAdjustModifyAttributeStateAttribute, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAattributeState";
  supportingServices.getParameterHandle(ws, managerFederateAdjustModifyAttributeState, managerFederateAdjustModifyAttributeStateAttributeState, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);

  // Manager.Federate.Adjust.SetServiceReporting
  ws = L"HLAmanager.HLAfederate.HLAadjust.HLAsetServiceReporting";
  managerFederateAdjustSetServiceReporting = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateAdjustSetServiceReporting);
  declarationManagement.subscribeInteractionClass(1, managerFederateAdjustSetServiceReporting, active, regions);
  ws = L"HLAreportingState";
  supportingServices.getParameterHandle(ws, managerFederateAdjustSetServiceReporting, managerFederateAdjustSetServiceReportingState, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);

  // Manager.Federate.Adjust.SetExceptionReporting
  ws = L"HLAmanager.HLAfederate.HLAadjust.HLAsetExceptionReporting";
  managerFederateAdjustSetExceptionReporting = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateAdjustSetExceptionReporting);
  declarationManagement.subscribeInteractionClass(1, managerFederateAdjustSetExceptionReporting, active, regions);
  ws = L"HLAreportingState";
  supportingServices.getParameterHandle(ws, managerFederateAdjustSetExceptionReporting, managerFederateAdjustSetExceptionReportingState, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);

  // Request
  ws = L"HLAmanager.HLAfederate.HLArequest.HLArequestPublications";
  managerFederateRequestPublications = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateRequestPublications);
  declarationManagement.subscribeInteractionClass(1, managerFederateRequestPublications, active, regions);

  ws = L"HLAmanager.HLAfederate.HLArequest.HLArequestSubscriptions";
  managerFederateRequestSubscriptions = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateRequestSubscriptions);
  declarationManagement.subscribeInteractionClass(1, managerFederateRequestSubscriptions, active, regions);

  ws = L"HLAmanager.HLAfederate.HLArequest.HLArequestObjectInstancesThatCanBeDeleted";
  managerFederateRequestObjectsInstancesThatCanBeDeleted = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateRequestObjectsInstancesThatCanBeDeleted);
  declarationManagement.subscribeInteractionClass(1, managerFederateRequestObjectsInstancesThatCanBeDeleted, active, regions);

  ws = L"HLAmanager.HLAfederate.HLArequest.HLArequestObjectInstancesUpdated";
  managerFederateRequestObjectsUpdated = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateRequestObjectsUpdated);
  declarationManagement.subscribeInteractionClass(1, managerFederateRequestObjectsUpdated, active, regions);

  ws = L"HLAmanager.HLAfederate.HLArequest.HLArequestObjectInstancesReflected";
  managerFederateRequestObjectsReflected = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateRequestObjectsReflected);
  declarationManagement.subscribeInteractionClass(1, managerFederateRequestObjectsReflected, active, regions);

  ws = L"HLAmanager.HLAfederate.HLArequest.HLArequestUpdatesSent";
  managerFederateRequestUpdatesSent = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateRequestUpdatesSent);
  declarationManagement.subscribeInteractionClass(1, managerFederateRequestUpdatesSent, active, regions);

  ws = L"HLAmanager.HLAfederate.HLArequest.HLArequestInteractionsSent";
  managerFederateRequestInteractionsSent = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateRequestInteractionsSent);
  declarationManagement.subscribeInteractionClass(1, managerFederateRequestInteractionsSent, active, regions);

  ws = L"HLAmanager.HLAfederate.HLArequest.HLArequestReflectionsReceived";
  managerFederateRequestReflectionsReceived = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateRequestReflectionsReceived);
  declarationManagement.subscribeInteractionClass(1, managerFederateRequestReflectionsReceived, active, regions);

  ws = L"HLAmanager.HLAfederate.HLArequest.HLArequestInteractionsReceived";
  managerFederateRequestInteractionsReceived = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateRequestInteractionsReceived);
  declarationManagement.subscribeInteractionClass(1, managerFederateRequestInteractionsReceived, active, regions);

  ws = L"HLAmanager.HLAfederate.HLArequest.HLArequestObjectInstanceInformation";
  managerFederateRequestObjectInformation = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateRequestObjectInformation);
  ws = L"HLAobjectInstance";
  supportingServices.getParameterHandle(ws, managerFederateRequestObjectInformation, managerFederateRequestObjectInformationObjectInstance, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  declarationManagement.subscribeInteractionClass(1, managerFederateRequestObjectInformation, active, regions);

  ws = L"HLAmanager.HLAfederate.HLArequest.HLArequestSynchronizationPoints";
  managerFederateRequestSynchronizationPoints = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateRequestSynchronizationPoints);
  declarationManagement.subscribeInteractionClass(1, managerFederateRequestSynchronizationPoints, active, regions);

  ws = L"HLAmanager.HLAfederate.HLArequest.HLArequestSynchronizationPointStatus";
  managerFederateRequestSynchronizationPointStatus = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateRequestSynchronizationPointStatus);
  declarationManagement.subscribeInteractionClass(1, managerFederateRequestSynchronizationPointStatus, active, regions);

  // Report
  // Manager.Federate.Report.ReportObjectPublication
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportObjectClassPublication";
  managerFederateReportObjectClassPublication = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateRequestInteractionsReceived);
  ws = L"HLAnumberOfClasses";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectClassPublication, managerFederateReportObjectPublicationNumberOfClasses, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAobjectClass";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectClassPublication, managerFederateReportObjectPublicationObjectClass, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAattributeList";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectClassPublication, managerFederateReportObjectPublicationAttributeList, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momReportObjectPublicationHandles.momClassId = managerFederateReportObjectClassPublication;
  momReportObjectPublicationHandles.federate = managerInteractionFederateFederate;
  momReportObjectPublicationHandles.numberOfClasses = managerFederateReportObjectPublicationNumberOfClasses;
  momReportObjectPublicationHandles.objectClass = managerFederateReportObjectPublicationObjectClass;
  momReportObjectPublicationHandles.attributeList = managerFederateReportObjectPublicationAttributeList;

  // Manager.Federate.Report.ReportInteractionPublication
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportInteractionPublication";
  managerFederateReportInteractionPublication = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAinteractionClassList";
  supportingServices.getParameterHandle(ws, managerFederateReportInteractionPublication, managerFederateReportInteractionPublicationInteractionClassList, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momReportInteractionPublicationHandles.momClassId = managerFederateReportInteractionPublication;
  momReportInteractionPublicationHandles.federate = managerInteractionFederateFederate;
  momReportInteractionPublicationHandles.interactionClassList = managerFederateReportInteractionPublicationInteractionClassList;

  // Manager.Federate.Report.ReportObjectSubscription
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportObjectClassSubscription";
  managerFederateReportObjectClassSubscription = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAnumberOfClasses";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectClassSubscription, managerFederateReportObjectSubscriptionNumberOfClasses, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAobjectClass";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectClassSubscription, managerFederateReportObjectSubscriptionObjectClass, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAattributeList";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectClassSubscription, managerFederateReportObjectSubscriptionAttributeList, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAactive";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectClassSubscription, managerFederateReportObjectSubscriptionActive, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momReportObjectSubscriptionHandles.momClassId = managerFederateReportObjectClassSubscription;
  momReportObjectSubscriptionHandles.federate = managerInteractionFederateFederate;
  momReportObjectSubscriptionHandles.numberOfClasses = managerFederateReportObjectSubscriptionNumberOfClasses;
  momReportObjectSubscriptionHandles.objectClass = managerFederateReportObjectSubscriptionObjectClass;
  momReportObjectSubscriptionHandles.attributeList = managerFederateReportObjectSubscriptionAttributeList;
  momReportObjectSubscriptionHandles.active = managerFederateReportObjectSubscriptionActive;

  // Manager.Federate.Report.ReportInteractionSubscription
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportInteractionSubscription";
  managerFederateReportInteractionSubscription = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAinteractionClassList";
  supportingServices.getParameterHandle(ws, managerFederateReportInteractionSubscription, managerFederateReportInteractionSubscriptionInteractionClassList, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momReportInteractionSubscriptionHandles.momClassId = managerFederateReportInteractionSubscription;
  momReportInteractionSubscriptionHandles.federate = managerInteractionFederateFederate;
  momReportInteractionSubscriptionHandles.interactionClassList = managerFederateReportInteractionSubscriptionInteractionClassList;

  // Manager.Federate.Report.ReportObjectsOwned
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportObjectInstancesThatCanBeDeleted";
  managerFederateReportObjectInstancesThatCanBeDeleted = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAobjectInstanceCounts";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectInstancesThatCanBeDeleted, managerFederateReportObjectsOwnedObjectCounts, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momReportObjectsOwnedHandles.momClassId = managerFederateReportObjectInstancesThatCanBeDeleted;
  momReportObjectsOwnedHandles.federate = managerInteractionFederateFederate;
  momReportObjectsOwnedHandles.objectCounts = managerFederateReportObjectsOwnedObjectCounts;

  // Manager.Federate.Report.ReportObjectsUpdated
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportObjectInstancesUpdated";
  managerFederateReportObjectInstancessUpdated = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAobjectInstanceCounts";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectInstancessUpdated, managerFederateReportObjectsUpdatedObjectCounts, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momReportObjectsUpdatedHandles.momClassId = managerFederateReportObjectInstancessUpdated;
  momReportObjectsUpdatedHandles.federate = managerInteractionFederateFederate;
  momReportObjectsUpdatedHandles.objectCounts = managerFederateReportObjectsUpdatedObjectCounts;

  // Manager.Federate.Report.ReportObjectsReflected
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportObjectInstancesReflected";
  managerFederateReportObjectInstancessReflected = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAobjectInstanceCounts";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectInstancessReflected, managerFederateReportObjectsReflectedObjectCounts, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momReportObjectsReflectedHandles.momClassId = managerFederateReportObjectInstancessReflected;
  momReportObjectsReflectedHandles.federate = managerInteractionFederateFederate;
  momReportObjectsReflectedHandles.objectCounts = managerFederateReportObjectsReflectedObjectCounts;

  // Manager.Federate.Report.ReportUpdatesSent
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportUpdatesSent";
  managerFederateReportUpdatesSent = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAtransportation";
  supportingServices.getParameterHandle(ws, managerFederateReportUpdatesSent, managerFederateReportUpdatesSentTransportationType, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAupdateCounts";
  supportingServices.getParameterHandle(ws, managerFederateReportUpdatesSent, managerFederateReportUpdatesSentUpdateCounts, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momReportUpdatesSentHandles.momClassId = managerFederateReportUpdatesSent;
  momReportUpdatesSentHandles.federate = managerInteractionFederateFederate;
  momReportUpdatesSentHandles.transportationType = managerFederateReportUpdatesSentTransportationType;
  momReportUpdatesSentHandles.updateCounts = managerFederateReportUpdatesSentUpdateCounts;

  // Manager.Federate.Report.ReportReflectionsReceived
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportReflectionsReceived";
  managerFederateReportReflectionsReceived = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAtransportation";
  supportingServices.getParameterHandle(ws, managerFederateReportReflectionsReceived, managerFederateReportReflectionsReceivedTransportationType, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAreflectCounts";
  supportingServices.getParameterHandle(ws, managerFederateReportReflectionsReceived, managerFederateReportReflectionsReceivedReflectCounts, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momReportReflectionsReceivedHandles.momClassId = managerFederateReportReflectionsReceived;
  momReportReflectionsReceivedHandles.federate = managerInteractionFederateFederate;
  momReportReflectionsReceivedHandles.transportationType = managerFederateReportReflectionsReceivedTransportationType;
  momReportReflectionsReceivedHandles.reflectCounts = managerFederateReportReflectionsReceivedReflectCounts;

  // Manager.Federate.Report.ReportInteractionsSent
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportInteractionsSent";
  managerFederateReportInteractionsSent = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAtransportation";
  supportingServices.getParameterHandle(ws, managerFederateReportInteractionsSent, managerFederateReportInteractionsSentTransportationType, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAinteractionCounts";
  supportingServices.getParameterHandle(ws, managerFederateReportInteractionsSent, managerFederateReportInteractionsSentInteractionCounts, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momReportInteractionsSentHandles.momClassId = managerFederateReportInteractionsSent;
  momReportInteractionsSentHandles.federate = managerInteractionFederateFederate;
  momReportInteractionsSentHandles.transportationType = managerFederateReportInteractionsSentTransportationType;
  momReportInteractionsSentHandles.interactionCounts = managerFederateReportInteractionsSentInteractionCounts;

  // Manager.Federate.Report.ReportInteractionsReceived
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportInteractionsReceived";
  managerFederateReportInteractionsReceived = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAtransportation";
  supportingServices.getParameterHandle(ws, managerFederateReportInteractionsReceived, managerFederateReportInteractionsReceivedTransportationType, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAinteractionCounts";
  supportingServices.getParameterHandle(ws, managerFederateReportInteractionsReceived, managerFederateReportInteractionsReceivedInteractionCounts, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momReportInteractionsReceivedHandles.momClassId = managerFederateReportInteractionsReceived;
  momReportInteractionsReceivedHandles.federate = managerInteractionFederateFederate;
  momReportInteractionsReceivedHandles.transportationType = managerFederateReportInteractionsReceivedTransportationType;
  momReportInteractionsReceivedHandles.interactionCounts = managerFederateReportInteractionsReceivedInteractionCounts;

  // Manager.Federate.Report.ReportObjectInformation
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportObjectInstanceInformation";
  managerFederateReportObjectInstanceInformation = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAobjectInstance";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectInstanceInformation, managerFederateReportObjectInformationObjectInstance, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAownedInstanceAttributeList";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectInstanceInformation, managerFederateReportObjectInformationOwnedAttributeList, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAregisteredClass";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectInstanceInformation, managerFederateReportObjectInformationRegisteredClass, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAknownClass";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectInstanceInformation, managerFederateReportObjectInformationKnownClass, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momReportObjectInformationHandles.momClassId = managerFederateReportObjectInstanceInformation;
  momReportObjectInformationHandles.federate = managerInteractionFederateFederate;
  momReportObjectInformationHandles.objectInstance = managerFederateReportObjectInformationObjectInstance;
  momReportObjectInformationHandles.objectAttributeList = managerFederateReportObjectInformationOwnedAttributeList;
  momReportObjectInformationHandles.registeredClass = managerFederateReportObjectInformationRegisteredClass;
  momReportObjectInformationHandles.knownClass = managerFederateReportObjectInformationKnownClass;

  // Manager.Federate.Report.Alert
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportException";
  managerFederateReportException = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAservice";
  supportingServices.getParameterHandle(ws, managerFederateReportException, managerFederateReportExceptionService, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAexception";
  supportingServices.getParameterHandle(ws, managerFederateReportException, managerFederateReportExceptionException, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momExceptionHandles.momClassId = managerFederateReportException;
  momExceptionHandles.federate = managerInteractionFederateFederate;
  momExceptionHandles.exceptionService = managerFederateReportExceptionService;
  momExceptionHandles.exceptionException = managerFederateReportExceptionException;

  // Manager.Federate.Report.ReportServiceInvocation
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportServiceInvocation";
  managerFederateReportServiceInvocation = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAservice";
  supportingServices.getParameterHandle(ws, managerFederateReportServiceInvocation, managerFederateReportServiceInvocationService, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAsuccessIndicator";
  supportingServices.getParameterHandle(ws, managerFederateReportServiceInvocation, managerFederateReportServiceInvocationSuccessIndicator, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAsuppliedArguments";
  supportingServices.getParameterHandle(ws, managerFederateReportServiceInvocation, managerFederateReportServiceInvocationSuppliedArguments, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAreturnedArguments";
  supportingServices.getParameterHandle(ws, managerFederateReportServiceInvocation, managerFederateReportServiceInvocationReturnedArguments, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAexception";
  supportingServices.getParameterHandle(ws, managerFederateReportServiceInvocation, managerFederateReportServiceInvocationException, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAserialNumber";
  supportingServices.getParameterHandle(ws, managerFederateReportServiceInvocation, managerFederateReportServiceInvocationSerialNumber, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momReportServiceInvocationHandles.momClassId = managerFederateReportServiceInvocation;
  momReportServiceInvocationHandles.federate = managerInteractionFederateFederate;
  momReportServiceInvocationHandles.service = managerFederateReportServiceInvocationService;
  momReportServiceInvocationHandles.initiator = managerFederateReportServiceInvocationInitiator;
  momReportServiceInvocationHandles.successIndicator = managerFederateReportServiceInvocationSuccessIndicator;
  momReportServiceInvocationHandles.suppliedArguments = managerFederateReportServiceInvocationSuppliedArguments;
  momReportServiceInvocationHandles.returnedArguments = managerFederateReportServiceInvocationReturnedArguments;
  momReportServiceInvocationHandles.exceptionDescription = managerFederateReportServiceInvocationException;
  momReportServiceInvocationHandles.serialNumber = managerFederateReportServiceInvocationSerialNumber;

  // Manager.Federate.Report.ReportMOMexception
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportMOMexception";
  managerFederateReportMOMexception = supportingServices.getInteractionClassHandle(ws);

  // Manager.Federate.Report.SynchronizationPoints
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportSynchronizationPoints";
  managerFederateReportSynchronizationPoints = supportingServices.getInteractionClassHandle(ws);

  // Manager.Federate.Report.SynchronizationPointStatus
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportSynchronizationPointStatus";
  managerFederateReportSynchronizationPointStatus = supportingServices.getInteractionClassHandle(ws);

  // Service
  ws = L"HLAmanager.HLAfederate.HLAservice.HLAresignFederationExecution";
  managerFederateServiceResignFederationExecution = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAresignAction";
  supportingServices.getParameterHandle(ws, managerFederateServiceResignFederationExecution, managerFederateServiceResignFederationExecutionResignAction, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momClasses.insert(managerFederateServiceResignFederationExecution);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceResignFederationExecution, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAsynchronizationPointAchieved";
  managerFederateServiceSynchronizationPointAchieved = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAlabel";
  supportingServices.getParameterHandle(ws, managerFederateServiceSynchronizationPointAchieved, managerFederateServiceSynchronizationPointAchievedLabel, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momClasses.insert(managerFederateServiceSynchronizationPointAchieved);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceSynchronizationPointAchieved, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAfederateSaveBegun";
  managerFederateServiceFederateSaveBegun = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateServiceFederateSaveBegun);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceFederateSaveBegun, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAfederateSaveComplete";
  managerFederateServiceFederateSaveComplete = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAsuccessIndicator";
  supportingServices.getParameterHandle(ws, managerFederateServiceFederateSaveComplete, managerFederateServiceFederateSaveCompleteSuccessIndicator, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momClasses.insert(managerFederateServiceFederateSaveComplete);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceFederateSaveComplete, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAfederateRestoreComplete";
  managerFederateServiceFederateRestoreComplete = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAsuccessIndicator";
  supportingServices.getParameterHandle(ws, managerFederateServiceFederateRestoreComplete, managerFederateServiceFederateRestoreCompleteSuccessIndicator, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momClasses.insert(managerFederateServiceFederateRestoreComplete);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceFederateRestoreComplete, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLApublishObjectClassAttributes";
  managerFederateServicePublishObjectClassAttributes = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAobjectClass";
  supportingServices.getParameterHandle(ws, managerFederateServicePublishObjectClassAttributes, managerFederateServicePublishObjectClassObjectClass, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAattributeList";
  supportingServices.getParameterHandle(ws, managerFederateServicePublishObjectClassAttributes, managerFederateServicePublishObjectClassAttributeList, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momClasses.insert(managerFederateServicePublishObjectClassAttributes);
  declarationManagement.subscribeInteractionClass(1, managerFederateServicePublishObjectClassAttributes, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAunpublishObjectClassAttributes";
  managerFederateServiceUnpublishObjectClassAttributes = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAobjectClass";
  supportingServices.getParameterHandle(ws, managerFederateServiceUnpublishObjectClassAttributes, managerFederateServiceUnpublishObjectClassObjectClass, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momClasses.insert(managerFederateServiceUnpublishObjectClassAttributes);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceUnpublishObjectClassAttributes, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLApublishInteractionClass";
  managerFederateServicePublishInteractionClass = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAinteractionClass";
  supportingServices.getParameterHandle(ws, managerFederateServicePublishInteractionClass, managerFederateServicePublishInteractionClassInteractionClass, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momClasses.insert(managerFederateServicePublishInteractionClass);
  declarationManagement.subscribeInteractionClass(1, managerFederateServicePublishInteractionClass, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAunpublishInteractionClass";
  managerFederateServiceUnpublishInteractionClass = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAinteractionClass";
  supportingServices.getParameterHandle(ws, managerFederateServiceUnpublishInteractionClass, managerFederateServiceUnpublishInteractionClassInteractionClass, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momClasses.insert(managerFederateServiceUnpublishInteractionClass);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceUnpublishInteractionClass, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAsubscribeObjectClassAttributes";
  managerFederateServiceSubscribeObjectClassAttributes = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAobjectClass";
  supportingServices.getParameterHandle(ws, managerFederateServiceSubscribeObjectClassAttributes, managerFederateServiceSubscribeObjectClassAttributesObjectClass, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAattributeList";
  supportingServices.getParameterHandle(ws, managerFederateServiceSubscribeObjectClassAttributes, managerFederateServiceSubscribeObjectClassAttributesAttributeList, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAactive";
  supportingServices.getParameterHandle(ws, managerFederateServiceSubscribeObjectClassAttributes, managerFederateServiceSubscribeObjectClassAttributesActive, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momClasses.insert(managerFederateServiceSubscribeObjectClassAttributes);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceSubscribeObjectClassAttributes, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAunsubscribeObjectClassAttributes";
  managerFederateServiceUnsubscribeObjectClassAttributes = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAobjectClass";
  supportingServices.getParameterHandle(ws, managerFederateServiceUnsubscribeObjectClassAttributes, managerFederateServiceUnsubscribeObjectClassObjectClass, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAattributeList";
  supportingServices.getParameterHandle(ws, managerFederateServiceUnsubscribeObjectClassAttributes, managerFederateServiceUnsubscribeObjectClassAttributeList, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momClasses.insert(managerFederateServiceUnsubscribeObjectClassAttributes);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceUnsubscribeObjectClassAttributes, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAsubscribeInteractionClass";
  managerFederateServiceSubscribeInteractionClass = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAinteractionClass";
  supportingServices.getParameterHandle(ws, managerFederateServiceSubscribeInteractionClass, managerFederateServiceSubscribeInteractionClassInteractionClass, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAactive";
  supportingServices.getParameterHandle(ws, managerFederateServiceSubscribeInteractionClass, managerFederateServiceSubscribeInteractionClassActive, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momClasses.insert(managerFederateServiceSubscribeInteractionClass);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceSubscribeInteractionClass, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAunsubscribeInteractionClass";
  managerFederateServiceUnsubscribeInteractionClass = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAinteractionClass";
  supportingServices.getParameterHandle(ws, managerFederateServiceUnsubscribeInteractionClass, managerFederateServiceUnsubscribeInteractionClassInteractionClass, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momClasses.insert(managerFederateServiceUnsubscribeInteractionClass);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceUnsubscribeInteractionClass, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAdeleteObjectInstance";
  managerFederateServiceDeleteObjectInstance = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAobjectInstance";
  supportingServices.getParameterHandle(ws, managerFederateServiceDeleteObjectInstance, managerFederateServiceDeleteObjectInstanceObjectInstance, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAtag";
  supportingServices.getParameterHandle(ws, managerFederateServiceDeleteObjectInstance, managerFederateServiceDeleteObjectInstanceTag, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAtimeStamp";
  supportingServices.getParameterHandle(ws, managerFederateServiceDeleteObjectInstance, managerFederateServiceDeleteObjectInstanceTimeStamp, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momClasses.insert(managerFederateServiceDeleteObjectInstance);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceDeleteObjectInstance, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAlocalDeleteObjectInstance";
  managerFederateServiceLocalDeleteObjectInstance = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAobjectInstance";
  supportingServices.getParameterHandle(ws, managerFederateServiceLocalDeleteObjectInstance, managerFederateServiceLocalDeleteObjectInstanceObjectInstance, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momClasses.insert(managerFederateServiceLocalDeleteObjectInstance);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceLocalDeleteObjectInstance, active, regions);

  // Manager Federate Service ChangeAttributeOrderTypeObjectInstance
  ws = L"HLAmanager.HLAfederate.HLAservice.HLAchangeAttributeTransportationType";
  managerFederateServiceChangeAttributeTransportationType = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateServiceChangeAttributeTransportationType);
  ws = L"HLAobjectInstance";
  supportingServices.getParameterHandle(ws, managerFederateServiceChangeAttributeTransportationType, managerFederateServiceChangeAttributeTransportationTypeObjectInstance, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAattributeList";
  supportingServices.getParameterHandle(ws, managerFederateServiceChangeAttributeTransportationType, managerFederateServiceChangeAttributeTransportationTypeAttributeList, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAtransportation";
  supportingServices.getParameterHandle(ws, managerFederateServiceChangeAttributeTransportationType, managerFederateServiceChangeAttributeTransportationTypeTransportationType, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceChangeAttributeTransportationType, active, regions);

  // Manager Federate Service ChangeAttributeOrderType
  ws = L"HLAmanager.HLAfederate.HLAservice.HLAchangeAttributeOrderType";
  managerFederateServiceChangeAttributeOrderType = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateServiceChangeAttributeOrderType);
  ws = L"HLAobjectInstance";
  supportingServices.getParameterHandle(ws, managerFederateServiceChangeAttributeOrderType, managerFederateServiceChangeAttributeOrderTypeObjectInstance, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAattributeList";
  supportingServices.getParameterHandle(ws, managerFederateServiceChangeAttributeOrderType, managerFederateServiceChangeAttributeOrderTypeAttributeList, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAsendOrder";
  supportingServices.getParameterHandle(ws, managerFederateServiceChangeAttributeOrderType, managerFederateServiceChangeAttributeOrderTypeOrderingType, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceChangeAttributeOrderType, active, regions);

  // Change interaction transportation type
  ws = L"HLAmanager.HLAfederate.HLAservice.HLAchangeInteractionTransportationType";
  managerFederateServiceChangeInteractionTransportationType = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAinteractionClass";
  supportingServices.getParameterHandle(ws, managerFederateServiceChangeInteractionTransportationType, managerFederateServiceChangeInteractionTransportationTypeInteractionClass, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAtransportation";
  supportingServices.getParameterHandle(ws, managerFederateServiceChangeInteractionTransportationType, managerFederateServiceChangeInteractionTransportationTypeTransportationType, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momClasses.insert(managerFederateServiceChangeInteractionTransportationType);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceChangeInteractionTransportationType, active, regions);

  // Change interaction order type
  ws = L"HLAmanager.HLAfederate.HLAservice.HLAchangeInteractionOrderType";
  managerFederateServiceChangeInteractionOrderType = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAinteractionClass";
  supportingServices.getParameterHandle(ws, managerFederateServiceChangeInteractionOrderType, managerFederateServiceChangeInteractionOrderTypeInteractionClass, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAsendOrder";
  supportingServices.getParameterHandle(ws, managerFederateServiceChangeInteractionOrderType, managerFederateServiceChangeInteractionOrderTypeOrderingType, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momClasses.insert(managerFederateServiceChangeInteractionOrderType);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceChangeInteractionOrderType, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAunconditionalAttributeOwnershipDivestiture";
  managerFederateServiceUnconditionalAttributeOwnershipDivestiture = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAobjectInstance";
  supportingServices.getParameterHandle(ws, managerFederateServiceUnconditionalAttributeOwnershipDivestiture, managerFederateServiceUnconditionalAttributeOwnershipDivestitureObjectInstance, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  ws = L"HLAattributeList";
  supportingServices.getParameterHandle(ws, managerFederateServiceUnconditionalAttributeOwnershipDivestiture, managerFederateServiceUnconditionalAttributeOwnershipDivestitureAttributeList, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momClasses.insert(managerFederateServiceUnconditionalAttributeOwnershipDivestiture);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceUnconditionalAttributeOwnershipDivestiture, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAenableTimeRegulation";
  managerFederateServiceEnableTimeRegulation = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAlookahead";
  supportingServices.getParameterHandle(ws, managerFederateServiceEnableTimeRegulation, managerFederateServiceEnableTimeRegulationLookahead, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momClasses.insert(managerFederateServiceEnableTimeRegulation);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceEnableTimeRegulation, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAdisableTimeRegulation";
  managerFederateServiceDisableTimeRegulation = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateServiceDisableTimeRegulation);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceDisableTimeRegulation, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAenableTimeConstrained";
  managerFederateServiceEnableTimeConstrained = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateServiceEnableTimeConstrained);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceEnableTimeConstrained, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAdisableTimeConstrained";
  managerFederateServiceDisableTimeConstrained = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateServiceDisableTimeConstrained);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceDisableTimeConstrained, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAenableAsynchronousDelivery";
  managerFederateServiceEnableAsynchronousDelivery = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateServiceEnableAsynchronousDelivery);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceEnableAsynchronousDelivery, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAdisableAsynchronousDelivery";
  managerFederateServiceDisableAsynchronousDelivery = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateServiceDisableAsynchronousDelivery);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceDisableAsynchronousDelivery, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAmodifyLookahead";
  managerFederateServiceModifyLookahead = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAlookahead";
  supportingServices.getParameterHandle(ws, managerFederateServiceModifyLookahead, managerFederateServiceModifyLookaheadLookahead, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momClasses.insert(managerFederateServiceModifyLookahead);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceModifyLookahead, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAtimeAdvanceRequest";
  managerFederateServiceTimeAdvanceRequest = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAtimeStamp";
  supportingServices.getParameterHandle(ws, managerFederateServiceTimeAdvanceRequest, managerFederateServiceTimeAdvanceRequestTimeStamp, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momClasses.insert(managerFederateServiceTimeAdvanceRequest);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceTimeAdvanceRequest, active, regions);
  momTimeAdvanceRequestHandles.momClassId = managerFederateServiceTimeAdvanceRequest;
  momTimeAdvanceRequestHandles.federate = managerInteractionFederateFederate;
  momTimeAdvanceRequestHandles.federationTime = managerFederateServiceTimeAdvanceRequestTimeStamp;

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAtimeAdvanceRequestAvailable";
  managerFederateServiceTimeAdvanceRequestAvailable = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAtimeStamp";
  supportingServices.getParameterHandle(ws, managerFederateServiceTimeAdvanceRequestAvailable, managerFederateServiceTimeAdvanceRequestAvailableTimeStamp, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momClasses.insert(managerFederateServiceTimeAdvanceRequestAvailable);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceTimeAdvanceRequestAvailable, active, regions);
  momTimeAdvanceRequestAvailableHandles.momClassId = managerFederateServiceTimeAdvanceRequestAvailable;
  momTimeAdvanceRequestAvailableHandles.federate = managerInteractionFederateFederate;
  momTimeAdvanceRequestAvailableHandles.federationTime = managerFederateServiceTimeAdvanceRequestAvailableTimeStamp;

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAnextMessageRequest";
  managerFederateServiceNextMessageRequest = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAtimeStamp";
  supportingServices.getParameterHandle(ws, managerFederateServiceNextMessageRequest, managerFederateServiceNextMessageRequestTimeStamp, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momClasses.insert(managerFederateServiceNextMessageRequest);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceNextMessageRequest, active, regions);
  momNextMessageRequestHandles.momClassId = managerFederateServiceNextMessageRequest;
  momNextMessageRequestHandles.federate = managerInteractionFederateFederate;
  momNextMessageRequestHandles.federationTime = managerFederateServiceNextMessageRequestTimeStamp;

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAnextMessageRequestAvailable";
  managerFederateServiceNextMessageRequestAvailable = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAtimeStamp";
  supportingServices.getParameterHandle(ws, managerFederateServiceNextMessageRequestAvailable, managerFederateServiceNextMessageRequestAvailableTimeStamp, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momClasses.insert(managerFederateServiceNextMessageRequestAvailable);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceNextMessageRequestAvailable, active, regions);
  momNextMessageRequestAvailableHandles.momClassId = managerFederateServiceNextMessageRequestAvailable;
  momNextMessageRequestAvailableHandles.federate = managerInteractionFederateFederate;
  momNextMessageRequestAvailableHandles.federationTime = managerFederateServiceNextMessageRequestAvailableTimeStamp;

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAflushQueueRequest";
  managerFederateServiceFlushQueueRequest = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAtimeStamp";
  supportingServices.getParameterHandle(ws, managerFederateServiceFlushQueueRequest, managerFederateServiceFlushQueueRequestTimeStamp, foundItem, foundClass);
  testFoundValues(ws, foundItem, foundClass);
  momClasses.insert(managerFederateServiceFlushQueueRequest);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceFlushQueueRequest, active, regions);
  momFlushQueueRequestHandles.momClassId = managerFederateServiceFlushQueueRequest;
  momFlushQueueRequestHandles.federate = managerInteractionFederateFederate;
  momFlushQueueRequestHandles.federationTime = managerFederateServiceFlushQueueRequestTimeStamp;

  ws = L"HLAmanager.HLAfederation.HLAadjust.HLAsetSwitches";
  managerFederationAdjustSetSwitches = supportingServices.getInteractionClassHandle(ws);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ManagementObjectModel::~ManagementObjectModel(void)
{
  GERTICO::MomFederate *momFederate;
  GERTICO::MomFederateMap::iterator itMomFederateMap;

  pm.acquire();
  for (itMomFederateMap = momFederateMap.begin(); itMomFederateMap != momFederateMap.end(); itMomFederateMap = momFederateMap.begin())
  {
    momFederate = itMomFederateMap->second;
    momFederateMap.erase(itMomFederateMap);
    delete momFederate;
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::adjustModifyAttributeState(GeRtiFactory::GeRtiEvent const &theGeRtiEvent)
{
  CORBA::ULong count = 4;
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GeRtiFactory::GeRtiHandle attribute;
  GeRtiFactory::GeRtiHandle federate;
  std::string attributeState;
  bool gotItem[4];
  long l;
  long objectInstance;

  for (i = 0; i < count; i++)
  {
    gotItem[i] = false;
  }

  lengthi = theGeRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theGeRtiEvent.data[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theGeRtiEvent.data[i].value);
      federate = l;
      gotItem[0] = true;
    }

    if (theGeRtiEvent.data[i].id == managerFederateAdjustModifyAttributeStateObjectInstance)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(objectInstance, theGeRtiEvent.data[i].value);
      gotItem[1] = true;
    }

    if (theGeRtiEvent.data[i].id == managerFederateAdjustModifyAttributeStateAttribute)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theGeRtiEvent.data[i].value);
      attribute = l,
      gotItem[2] = true;
    }
    if (theGeRtiEvent.data[i].id == managerFederateAdjustModifyAttributeStateAttributeState)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theGeRtiEvent.data[i].value);
      if (l)
      {
        attributeState = "HLAowned";
      }
      else
      {
        attributeState = "HLAunowned";
      }
      gotItem[3] = true;
    }
  }

  for (i = 0; i < count; i++)
  {
    if (gotItem[i] == false)
    {
      return;
    }
  }

  ownershipMaster.managerFederateAdjustModifyAttributeState(federate, objectInstance, attribute, attributeState);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::adjustSetServiceReporting(GeRtiFactory::GeRtiEvent &theGeRtiEvent)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomFederateMap::iterator itMomFederateMap;
  GeRtiFactory::GeRtiHandle federate = 0;
  bool reportingState = false;
  long l;

  lengthi = theGeRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theGeRtiEvent.data[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theGeRtiEvent.data[i].value);
      federate = l;
    }

    if (theGeRtiEvent.data[i].id == managerFederateAdjustSetServiceReportingState)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theGeRtiEvent.data[i].value);
      if (l)
      {
        reportingState = true;
      }
    }
  }

  pm.acquire();
  itMomFederateMap = momFederateMap.find(federate);
  if (itMomFederateMap != momFederateMap.end())
  {
    itMomFederateMap->second->setServiceReporting(reportingState);
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::adjustSetExceptionLogging(GeRtiFactory::GeRtiEvent &theGeRtiEvent)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomFederateMap::iterator itMomFederateMap;
  GeRtiFactory::GeRtiHandle federate = 0;
  std::string loggingStateStr;
  bool loggingState = false;
  long l;

  lengthi = theGeRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theGeRtiEvent.data[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theGeRtiEvent.data[i].value);
      federate = l;
    }

    if (theGeRtiEvent.data[i].id == managerFederateAdjustSetExceptionReportingState)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theGeRtiEvent.data[i].value);
      if (l)
      {
        loggingState = true;
      }
    }
  }

  pm.acquire();
  itMomFederateMap = momFederateMap.find(federate);
  if (itMomFederateMap != momFederateMap.end())
  {
    itMomFederateMap->second->setExceptionLogging(loggingState);
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::adjustSetTiming(GeRtiFactory::GeRtiEvent &theGeRtiEvent)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomFederateMap::iterator itMomFederateMap;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::GeRtiHandle setTiming = 0;
  long l;

  lengthi = theGeRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theGeRtiEvent.data[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theGeRtiEvent.data[i].value);
      federate = l;
    }

    if (theGeRtiEvent.data[i].id == managerFederateAdjustSetTimingReportPeriod)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theGeRtiEvent.data[i].value);
      setTiming = l;
    }
  }

  pm.acquire();
  itMomFederateMap = momFederateMap.find(federate);
  if (itMomFederateMap != momFederateMap.end())
  {
    itMomFederateMap->second->setTiming(setTiming);
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::changeAttributeOrderType(const GeRtiFactory::GeRtiEvent &theGeRtiEvent)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::RegisteredObject *registeredObject;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::GeRtiHandle orderingType;
  GeRtiFactory::Handles attributes;
  std::string alertDescription;
  std::string alertSeverity;
  bool gotError = false;
  long l;
  long objectInstance;

  lengthi = theGeRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theGeRtiEvent.data[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theGeRtiEvent.data[i].value);
      federate = l;
    }

    if (theGeRtiEvent.data[i].id == managerFederateServiceChangeAttributeOrderTypeObjectInstance)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(objectInstance, theGeRtiEvent.data[i].value);
    }

    if (theGeRtiEvent.data[i].id == managerFederateServiceChangeAttributeOrderTypeAttributeList)
    {
      GERTICO::Mapper::mapHLAAttributesFromOctetSequence(attributes, theGeRtiEvent.data[i].value);
    }

    if (theGeRtiEvent.data[i].id == managerFederateServiceChangeAttributeOrderTypeOrderingType)
    {
      GERTICO::Mapper::getOrderType(orderingType, theGeRtiEvent.data[i].value);
    }
  }

  registeredObject = objectManagement.getObject(objectInstance);
  if (registeredObject)
  {
    try
    {
      objectManagement.changeAttributeOrderType(federate, registeredObject->getId(), attributes, orderingType);
    }
    catch(GeRtiFactory::ObjectNotKnown &)
    {
      gotError = true;
      alertDescription = "ObjectNotKnown";
      alertSeverity = "RTI exception";
    }
    catch(GeRtiFactory::AttributeNotDefined &)
    {
      gotError = true;
      alertDescription = "AttributeNotDefined";
      alertSeverity = "RTI exception";
    }
    catch(GeRtiFactory::AttributeNotOwned &)
    {
      gotError = true;
      alertDescription = "AttributeNotOwned";
      alertSeverity = "RTI exception";
    }
    catch(GeRtiFactory::InvalidOrderingHandle &)
    {
      gotError = true;
      alertDescription = "InvalidOrderingHandle";
      alertSeverity = "RTI exception";
    }
    catch(GeRtiFactory::FederateNotExecutionMember &)
    {
      gotError = true;
      alertDescription = "FederateNotExecutionMember";
      alertSeverity = "RTI exception";
    }
    catch(GeRtiFactory::SaveInProgress &)
    {
      gotError = true;
      alertDescription = "SaveInProgress";
      alertSeverity = "RTI exception";
    }
    catch(GeRtiFactory::RestoreInProgress &)
    {
      gotError = true;
      alertDescription = "RestoreInProgress";
      alertSeverity = "RTI exception";
    }
    catch(GeRtiFactory::RTIinternalError &)
    {
      gotError = true;
      alertDescription = "RTIinternalError";
      alertSeverity = "RTI internal error";
    }
    catch(GeRtiFactory::ConcurrentAccessAttempted &)
    {
      gotError = true;
      alertDescription = "ConcurrentAccessAttempted";
      alertSeverity = "RTI exception";
    }
  }
  else
  {
    gotError = true;
    alertDescription = "ObjectNotKnown";
    alertSeverity = "RTI exception";
  }

  if (gotError)
  {
    GERTICO::MomFederateMap::iterator itMomFederateMap;
    bool exceptionLogging;

    pm.acquire();
    itMomFederateMap = momFederateMap.find(federate);
    if (itMomFederateMap != momFederateMap.end())
    {
      exceptionLogging = itMomFederateMap->second->checkExceptionLogging();
      if (exceptionLogging)
      {
        sendAlert(federate, alertSeverity, alertDescription);
      }
    }
    pm.release();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::changeAttributeTransportationType(const GeRtiFactory::GeRtiEvent &theEvent)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::RegisteredObject *registeredObject;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::GeRtiHandle transportationType;
  GeRtiFactory::Handles attributes;
  std::string alertDescription;
  std::string alertSeverity;
  bool gotError = false;
  long l;
  long objectInstance;

  lengthi = theEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theEvent.data[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theEvent.data[i].value);
      federate = l;
    }

    if (theEvent.data[i].id == managerFederateServiceChangeAttributeTransportationTypeObjectInstance)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(objectInstance, theEvent.data[i].value);
    }

    if (theEvent.data[i].id == managerFederateServiceChangeAttributeTransportationTypeAttributeList)
    {
      GERTICO::Mapper::mapHLAAttributesFromOctetSequence(attributes, theEvent.data[i].value);
    }

    if (theEvent.data[i].id == managerFederateServiceChangeAttributeTransportationTypeTransportationType)
    {
      GERTICO::Mapper::getTransportationType(transportationType, theEvent.data[i].value);
    }
  }

  registeredObject = objectManagement.getObject(objectInstance);
  if (registeredObject)
  {
    try
    {
      objectManagement.changeAttributeTransportationType(federate, registeredObject->getId(), attributes, transportationType);
    }
    catch(GeRtiFactory::ObjectNotKnown)
    {
      gotError = true;
      alertDescription = "ObjectNotKnown";
      alertSeverity = "RTI exception";
    }
    catch(GeRtiFactory::AttributeNotDefined)
    {
      gotError = true;
      alertDescription = "AttributeNotDefined";
      alertSeverity = "RTI exception";
    }
    catch(GeRtiFactory::AttributeNotOwned)
    {
      gotError = true;
      alertDescription = "AttributeNotOwned";
      alertSeverity = "RTI exception";
    }
    catch(GeRtiFactory::InvalidTransportationHandle)
    {
      gotError = true;
      alertDescription = "InvalidTransportationHandle";
      alertSeverity = "RTI exception";
    }
    catch(GeRtiFactory::FederateNotExecutionMember)
    {
      gotError = true;
      alertDescription = "FederateNotExecutionMember";
      alertSeverity = "RTI exception";
    }
    catch(GeRtiFactory::SaveInProgress)
    {
      gotError = true;
      alertDescription = "SaveInProgress";
      alertSeverity = "RTI exception";
    }
    catch(GeRtiFactory::RestoreInProgress)
    {
      gotError = true;
      alertDescription = "RestoreInProgress";
      alertSeverity = "RTI exception";
    }
    catch(GeRtiFactory::RTIinternalError)
    {
      gotError = true;
      alertDescription = "RTIinternalError";
      alertSeverity = "RTI internal error";
    }
    catch(GeRtiFactory::ConcurrentAccessAttempted)
    {
      gotError = true;
      alertDescription = "ConcurrentAccessAttempted";
      alertSeverity = "RTI exception";
    }
  }
  else
  {
    gotError = true;
    alertDescription = "ObjectNotKnown";
    alertSeverity = "RTI exception";
  }

  if (gotError)
  {
    GERTICO::MomFederateMap::iterator itMomFederateMap;
    bool exceptionLogging;

    pm.acquire();
    itMomFederateMap = momFederateMap.find(federate);
    if (itMomFederateMap != momFederateMap.end())
    {
      exceptionLogging = itMomFederateMap->second->checkExceptionLogging();
      if (exceptionLogging)
      {
        sendAlert(federate, alertSeverity, alertDescription);
      }
    }
    pm.release();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::changeInteractionOrderType(const GeRtiFactory::GeRtiEvent &theGeRtiEvent)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::GeRtiHandle interactionClass = 0;
  GeRtiFactory::GeRtiHandle orderingType;
  std::string alertDescription;
  std::string alertSeverity;
  bool gotError = false;
  long l;

  lengthi = theGeRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theGeRtiEvent.data[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theGeRtiEvent.data[i].value);
      federate = l;
    }

    if (theGeRtiEvent.data[i].id == managerFederateServiceChangeInteractionOrderTypeInteractionClass)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theGeRtiEvent.data[i].value);
      interactionClass = l;
    }

    if (theGeRtiEvent.data[i].id == managerFederateServiceChangeInteractionOrderTypeOrderingType)
    {
      GERTICO::Mapper::getOrderType(orderingType, theGeRtiEvent.data[i].value);
    }
  }

  try
  {
//    declarationManagement.changeInteractionOrderType(federate, interactionClass, orderingType);
  }
  catch(GeRtiFactory::InteractionClassNotDefined &)
  {
    gotError = true;
    alertDescription = "InteractionClassNotDefined";
    alertSeverity = "RTI exception";
  }
  catch(GeRtiFactory::InteractionClassNotPublished &)
  {
    gotError = true;
    alertDescription = "InteractionClassNotPublished";
    alertSeverity = "RTI exception";
  }
  catch(GeRtiFactory::InvalidOrderingHandle &)
  {
    gotError = true;
    alertDescription = "InvalidOrderingHandle";
    alertSeverity = "RTI exception";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    alertDescription = "FederateNotExecutionMember";
    alertSeverity = "RTI exception";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    alertDescription = "SaveInProgress";
    alertSeverity = "RTI exception";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    alertDescription = "RestoreInProgress";
    alertSeverity = "RTI exception";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    alertDescription = "RTIinternalError";
    alertSeverity = "RTI internal error";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    alertDescription = "ConcurrentAccessAttempted";
    alertSeverity = "RTI exception";
  }

  if (gotError)
  {
    GERTICO::MomFederateMap::iterator itMomFederateMap;
    bool exceptionLogging;

    pm.acquire();
    itMomFederateMap = momFederateMap.find(federate);
    if (itMomFederateMap != momFederateMap.end())
    {
      exceptionLogging = itMomFederateMap->second->checkExceptionLogging();
      if (exceptionLogging)
      {
        sendAlert(federate, alertSeverity, alertDescription);
      }
    }
    pm.release();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::changeInteractionTransportationType(const GeRtiFactory::GeRtiEvent &theGeRtiEvent)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::GeRtiHandle interactionClass = 0;
  GeRtiFactory::GeRtiHandle transportationType;
  std::string alertDescription;
  std::string alertSeverity;
  bool gotError = false;
  long l;

  lengthi = theGeRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theGeRtiEvent.data[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theGeRtiEvent.data[i].value);
      federate = l;
    }

    if (theGeRtiEvent.data[i].id == managerFederateServiceChangeInteractionTransportationTypeInteractionClass)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theGeRtiEvent.data[i].value);
      interactionClass = l;
    }

    if (theGeRtiEvent.data[i].id == managerFederateServiceChangeInteractionTransportationTypeTransportationType)
    {
      GERTICO::Mapper::getTransportationType(transportationType, theGeRtiEvent.data[i].value);
    }
  }

  try
  {
//    declarationManagement.changeInteractionTransportationType(federate, interactionClass, transportationType);
  }
  catch(GeRtiFactory::InteractionClassNotDefined &)
  {
    gotError = true;
    alertDescription = "InteractionClassNotDefined";
    alertSeverity = "RTI exception";
  }
  catch(GeRtiFactory::InteractionClassNotPublished &)
  {
    gotError = true;
    alertDescription = "InteractionClassNotPublished";
    alertSeverity = "RTI exception";
  }
  catch(GeRtiFactory::InvalidTransportationHandle &)
  {
    gotError = true;
    alertDescription = "InvalidTransportationHandle";
    alertSeverity = "RTI exception";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    alertDescription = "FederateNotExecutionMember";
    alertSeverity = "RTI exception";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    alertDescription = "SaveInProgress";
    alertSeverity = "RTI exception";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    alertDescription = "RestoreInProgress";
    alertSeverity = "RTI exception";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    alertDescription = "RTIinternalError";
    alertSeverity = "RTI internal error";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    alertDescription = "ConcurrentAccessAttempted";
    alertSeverity = "RTI exception";
  }

  if (gotError)
  {
    GERTICO::MomFederateMap::iterator itMomFederateMap;
    bool exceptionLogging;

    pm.acquire();
    itMomFederateMap = momFederateMap.find(federate);
    if (itMomFederateMap != momFederateMap.end())
    {
      exceptionLogging = itMomFederateMap->second->checkExceptionLogging();
      if (exceptionLogging)
      {
        sendAlert(federate, alertSeverity, alertDescription);
      }
    }
    pm.release();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::discoverManagerFederation(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass)
{
  GERTICO::Federate *federate;
  GERTICO::HandleSet atts;

  if (isMomClass(theClass) == false)
  {
    return;
  }

  federate = federatesHolder.getFederate(theFederate);
  if (federate)
  {
    federate->getSubscribedAttributes(theClass, atts);
    if (federate->knowObject(managerFederation) == false)
    {
      objectManagement.addDiscoverObject(theFederate, theClass, managerFederation, atts);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::doMomInteraction(GeRtiFactory::GeRtiEvent &theGeRtiEvent)
{
  GERTICO::ClassDescr *classDescr;
  GERTICO::HandleSet items;
  GeRtiFactory::GeRtiHandle federate = 0;
  std::string alertDescription;
  std::string alertSeverity;

  if (theGeRtiEvent.source == 1)
  {
    return;
  }
  if (theGeRtiEvent.type == GeRtiFactory::obj)
  {
    classDescr = objectRoot.getClassDescr(theGeRtiEvent._cxx_class);
    if (classDescr->isDerivedClass(managerObject) == false)
    {
      return;
    }
  }
  else
  {
    classDescr = interactionRoot.getClassDescr(theGeRtiEvent._cxx_class);
    if (classDescr->isDerivedClass(managerInteractionRoot) == false)
    {
      return;
    }
  }

  getFederate(federate, theGeRtiEvent);
  if (federate == 0)
  {
    alertSeverity = "RTI warning";
    alertDescription = "Federate id is missing";
//    sendAlert(federate, alertSeverity, alertDescription);
    return;
  }

  // Adjust
  if (classDescr->isDerivedClass(managerFederateAdjustSetTiming))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateAdjustSetTimingReportPeriod);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      adjustSetTiming(theGeRtiEvent);
    }
  }

  if (classDescr->isDerivedClass(managerFederateAdjustModifyAttributeState))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateAdjustModifyAttributeStateObjectInstance);
    items.insert(managerFederateAdjustModifyAttributeStateAttribute);
    items.insert(managerFederateAdjustModifyAttributeStateAttributeState);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      GeRtiFactory::GeRtiEvent unownedGeRtiEvent;
      bool setOwned = false;

      getSetServiceReportingParams(setOwned, theGeRtiEvent, unownedGeRtiEvent);
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateAdjustModifyAttributeState, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
      adjustModifyAttributeState(theGeRtiEvent);
      if (setOwned)
      {
        // May have to set unowned to another federate.
        doMomRequest = new GERTICO::DoMomRequest(unownedGeRtiEvent, managerFederateAdjustSetServiceReporting, managerInteractionFederateFederate, federatesHolder);
        federationJobs.add(doMomRequest);
      }
    }
  }

  if (classDescr->isDerivedClass(managerFederateAdjustSetServiceReporting))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateAdjustSetServiceReportingState);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateAdjustSetServiceReporting, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
      adjustSetServiceReporting(theGeRtiEvent);
    }
  }

  if (classDescr->isDerivedClass(managerFederateAdjustSetExceptionReporting))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateAdjustSetExceptionReportingState);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      adjustSetExceptionLogging(theGeRtiEvent);
    }
  }

  // Request
  if (classDescr->isDerivedClass(managerFederateRequestPublications))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::MomRequestPublications *momRequestPublications;
      momRequestPublications = new GERTICO::MomRequestPublications(theGeRtiEvent, momReportObjectPublicationHandles, momReportInteractionPublicationHandles, objectManagement, federatesHolder, eventHandler, interactionRoot);
      federationJobs.add(momRequestPublications);
    }
  }

  if (classDescr->isDerivedClass(managerFederateRequestSubscriptions))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::MomRequestSubscriptions *momRequestSubscriptions;
      momRequestSubscriptions = new GERTICO::MomRequestSubscriptions(theGeRtiEvent, momReportObjectSubscriptionHandles, momReportInteractionSubscriptionHandles, federatesHolder, eventHandler, interactionRoot);
      federationJobs.add(momRequestSubscriptions);
    }
  }

  if (classDescr->isDerivedClass(managerFederateRequestObjectsInstancesThatCanBeDeleted))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::MomRequestObjectsOwned *momRequestObjectsOwned;
      momRequestObjectsOwned = new GERTICO::MomRequestObjectsOwned(theGeRtiEvent, momReportObjectsOwnedHandles, objectManagement, federatesHolder, eventHandler, interactionRoot);
      federationJobs.add(momRequestObjectsOwned);
    }
  }

  if (classDescr->isDerivedClass(managerFederateRequestObjectsUpdated))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::MomRequestObjectsUpdated *momRequestObjectsUpdated;
      momRequestObjectsUpdated = new GERTICO::MomRequestObjectsUpdated(theGeRtiEvent, momReportObjectsUpdatedHandles, objectManagement, federatesHolder, eventHandler, interactionRoot);
      federationJobs.add(momRequestObjectsUpdated);
    }
  }

  if (classDescr->isDerivedClass(managerFederateRequestObjectsReflected))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::MomRequestObjectsReflected *momRequestObjectsReflected;
      momRequestObjectsReflected = new GERTICO::MomRequestObjectsReflected(theGeRtiEvent, momReportObjectsReflectedHandles, federatesHolder, eventHandler, interactionRoot);
      federationJobs.add(momRequestObjectsReflected);
    }
  }

  if (classDescr->isDerivedClass(managerFederateRequestUpdatesSent))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::MomRequestUpdatesSent *momRequestUpdatesSent;
      momRequestUpdatesSent = new GERTICO::MomRequestUpdatesSent(theGeRtiEvent, momReportUpdatesSentHandles, federatesHolder, eventHandler, interactionRoot);
      federationJobs.add(momRequestUpdatesSent);
    }
  }

  if (classDescr->isDerivedClass(managerFederateRequestReflectionsReceived))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::MomRequestReflectionsReceived *momRequestReflectionsReceived;
      momRequestReflectionsReceived = new GERTICO::MomRequestReflectionsReceived(theGeRtiEvent, momReportReflectionsReceivedHandles, federatesHolder, eventHandler, interactionRoot);
      federationJobs.add(momRequestReflectionsReceived);
    }
  }

  if (classDescr->isDerivedClass(managerFederateRequestInteractionsSent))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::MomRequestInteractionsSent *momRequestInteractionsSent;
      momRequestInteractionsSent = new GERTICO::MomRequestInteractionsSent(theGeRtiEvent, momReportInteractionsSentHandles, federatesHolder, eventHandler, interactionRoot);
      federationJobs.add(momRequestInteractionsSent);
    }
  }

  if (classDescr->isDerivedClass(managerFederateRequestInteractionsReceived))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::MomRequestInteractionsReceived *momRequestInteractionsReceived;
      momRequestInteractionsReceived = new GERTICO::MomRequestInteractionsReceived(theGeRtiEvent, momReportInteractionsReceivedHandles, federatesHolder, eventHandler, interactionRoot);
      federationJobs.add(momRequestInteractionsReceived);
    }
  }

  if (classDescr->isDerivedClass(managerFederateRequestObjectInformation))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateRequestObjectInformationObjectInstance);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::MomRequestObjectsInformation *momRequestObjectsInformation;
      momRequestObjectsInformation = new GERTICO::MomRequestObjectsInformation(theGeRtiEvent, managerFederateRequestObjectInformationObjectInstance, momReportObjectInformationHandles, objectManagement, federatesHolder, eventHandler, interactionRoot);
      federationJobs.add(momRequestObjectsInformation);
    }
  }

  // Service
  if (classDescr->isDerivedClass(managerFederateServiceResignFederationExecution))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceResignFederationExecutionResignAction);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceResignFederationExecution, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (classDescr->isDerivedClass(managerFederateServiceSynchronizationPointAchieved))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceSynchronizationPointAchievedLabel);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceSynchronizationPointAchieved, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (classDescr->isDerivedClass(managerFederateServiceFederateSaveBegun))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceFederateSaveBegun, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (classDescr->isDerivedClass(managerFederateServiceFederateSaveComplete))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceFederateSaveCompleteSuccessIndicator);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceFederateSaveComplete, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (classDescr->isDerivedClass(managerFederateServiceFederateRestoreComplete))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceFederateRestoreCompleteSuccessIndicator);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceFederateRestoreComplete, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (classDescr->isDerivedClass(managerFederateServicePublishObjectClassAttributes))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServicePublishObjectClassObjectClass);
    items.insert(managerFederateServicePublishObjectClassAttributeList);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServicePublishObjectClassAttributes, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (classDescr->isDerivedClass(managerFederateServiceUnpublishObjectClassAttributes))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceUnpublishObjectClassObjectClass);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceUnpublishObjectClassAttributes, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (classDescr->isDerivedClass(managerFederateServicePublishInteractionClass))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServicePublishInteractionClassInteractionClass);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServicePublishInteractionClass, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (classDescr->isDerivedClass(managerFederateServiceUnpublishInteractionClass))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceUnpublishInteractionClassInteractionClass);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceUnpublishInteractionClass, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (classDescr->isDerivedClass(managerFederateServiceSubscribeObjectClassAttributes))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceSubscribeObjectClassAttributesObjectClass);
    items.insert(managerFederateServiceSubscribeObjectClassAttributesAttributeList);
    items.insert(managerFederateServiceSubscribeObjectClassAttributesActive);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceSubscribeObjectClassAttributes, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (classDescr->isDerivedClass(managerFederateServiceUnsubscribeObjectClassAttributes))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceUnsubscribeObjectClassObjectClass);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceUnsubscribeObjectClassAttributes, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (classDescr->isDerivedClass(managerFederateServiceSubscribeInteractionClass))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceSubscribeInteractionClassInteractionClass);
    items.insert(managerFederateServiceSubscribeInteractionClassActive);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceSubscribeInteractionClass, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (classDescr->isDerivedClass(managerFederateServiceUnsubscribeInteractionClass))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceUnsubscribeInteractionClassInteractionClass);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceUnsubscribeInteractionClass, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (classDescr->isDerivedClass(managerFederateServiceDeleteObjectInstance))
  {
    GERTICO::DoMomRequest *doMomRequest;

    // A reverse checklist.
    items.clear();
    items.insert(managerFederateServiceDeleteObjectInstanceObjectInstance);
    items.insert(managerFederateServiceDeleteObjectInstanceTag);
    // managerFederateServiceDeleteObjectInstanceFederationTime is optional!

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceDeleteObjectInstance, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (classDescr->isDerivedClass(managerFederateServiceLocalDeleteObjectInstance))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceLocalDeleteObjectInstanceObjectInstance);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceLocalDeleteObjectInstance, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (theGeRtiEvent._cxx_class == managerFederateServiceChangeAttributeTransportationType)
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceChangeAttributeTransportationTypeObjectInstance);
    items.insert(managerFederateServiceChangeAttributeTransportationTypeAttributeList);
    items.insert(managerFederateServiceChangeAttributeTransportationTypeTransportationType);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceChangeAttributeTransportationType, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
//      changeAttributeTransportationType(theGeRtiEvent);
    }
  }

  if (theGeRtiEvent._cxx_class == managerFederateServiceChangeAttributeOrderType)
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceChangeAttributeOrderTypeObjectInstance);
    items.insert(managerFederateServiceChangeAttributeOrderTypeAttributeList);
    items.insert(managerFederateServiceChangeAttributeOrderTypeOrderingType);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceChangeAttributeOrderType, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
//      changeAttributeOrderType(theGeRtiEvent);
    }
  }

  if (theGeRtiEvent._cxx_class == managerFederateServiceChangeInteractionTransportationType)
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceChangeInteractionTransportationTypeInteractionClass);
    items.insert(managerFederateServiceChangeInteractionTransportationTypeTransportationType);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceChangeInteractionTransportationType, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
//      changeInteractionTransportationType(theGeRtiEvent);
    }
  }

  if (theGeRtiEvent._cxx_class == managerFederateServiceChangeInteractionOrderType)
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceChangeInteractionOrderTypeInteractionClass);
    items.insert(managerFederateServiceChangeInteractionOrderTypeOrderingType);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceChangeInteractionOrderType, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
//      changeInteractionOrderType(theGeRtiEvent);
    }
  }

  if (theGeRtiEvent._cxx_class == managerFederateServiceUnconditionalAttributeOwnershipDivestiture)
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceUnconditionalAttributeOwnershipDivestitureObjectInstance);
    items.insert(managerFederateServiceUnconditionalAttributeOwnershipDivestitureAttributeList);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      unconditionalAttributeOwnershipDivestiture(theGeRtiEvent);
    }
  }

  if (theGeRtiEvent._cxx_class == managerFederateServiceEnableTimeRegulation)
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceEnableTimeRegulationLookahead);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceEnableTimeRegulation, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (theGeRtiEvent._cxx_class == managerFederateServiceDisableTimeRegulation)
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceDisableTimeRegulation, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (theGeRtiEvent._cxx_class == managerFederateServiceEnableTimeConstrained)
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceEnableTimeConstrained, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (theGeRtiEvent._cxx_class == managerFederateServiceDisableTimeConstrained)
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceDisableTimeConstrained, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (theGeRtiEvent._cxx_class == managerFederateServiceEnableAsynchronousDelivery)
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceEnableAsynchronousDelivery, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (theGeRtiEvent._cxx_class == managerFederateServiceDisableAsynchronousDelivery)
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceDisableAsynchronousDelivery, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (theGeRtiEvent._cxx_class == managerFederateServiceModifyLookahead)
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceModifyLookaheadLookahead);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceModifyLookahead, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (theGeRtiEvent._cxx_class == managerFederateServiceTimeAdvanceRequest)
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceTimeAdvanceRequestTimeStamp);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceTimeAdvanceRequest, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (theGeRtiEvent._cxx_class == managerFederateServiceTimeAdvanceRequestAvailable)
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceTimeAdvanceRequestAvailableTimeStamp);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceTimeAdvanceRequestAvailable, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (theGeRtiEvent._cxx_class == managerFederateServiceNextMessageRequest)
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceNextMessageRequestTimeStamp);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceNextMessageRequest, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (theGeRtiEvent._cxx_class == managerFederateServiceNextMessageRequestAvailable)
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceNextMessageRequestAvailableTimeStamp);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceNextMessageRequestAvailable, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (theGeRtiEvent._cxx_class == managerFederateServiceFlushQueueRequest)
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceFlushQueueRequestTimeStamp);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceFlushQueueRequest, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
    else
    {
      alertSeverity = "RTI warning";
      alertDescription = "FederationTime is missing";
      sendAlert(federate, alertSeverity, alertDescription);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::getAttributes(GeRtiFactory::Handles &theAttributes, char *theBuff)
{
  int i;
  int ind = 0;
  int items;
  int j;
  unsigned long len = 0;
  unsigned long ul;

  for (i = 0, j = 0; ;)
  {
    items = sscanf(&theBuff[ind], "%lu%n ,%n", &ul, &i, &j);
    if (items == 0)
    {
      break;
    }
    theAttributes.length(len + 1);
    theAttributes[len] = ul;
    len += 1;
    if (j == 0)
    {
      break;
    }
    ind += j;
    j = 0;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::getFederate(GeRtiFactory::GeRtiHandle &theFederate, GeRtiFactory::GeRtiEvent &theGeRtiEvent)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  long l;

  lengthi = theGeRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theGeRtiEvent.data[i].id == managerFederateFederateHandle)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theGeRtiEvent.data[i].value);
      theFederate = l;
    }
    if (theGeRtiEvent.data[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theGeRtiEvent.data[i].value);
      theFederate = l;
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::getFederationName(std::wstring &theFederationName)
{
  theFederationName = federationName;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::getLastSaveName(std::wstring &theLastSaveName)
{
  theLastSaveName = lastSaveName;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::getSetServiceReportingParams(bool &theBool, GeRtiFactory::GeRtiEvent &theGeRtiEvent, GeRtiFactory::GeRtiEvent &theUnonwedGeRtiEvent)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong jLen;
  CORBA::ULong len;
  CORBA::ULong saveFederateIndex;
  CORBA::ULong saveStateIndex;
  GERTICO::AttributeStatus status;
  unsigned long attribute;
  unsigned long federate;
  char *cptr;
  std::wstring objectInstance;

  theBool = false;

  len = theGeRtiEvent.data.length();
  for (i = 0; i < len; i++)
  {
    if (theGeRtiEvent.data[i].id == managerInteractionFederateFederate)
    {
      saveFederateIndex = i;
      GERTICO::Mapper::mapOctetSequence(&cptr, theGeRtiEvent.data[i].value);
      sscanf(cptr, "%lu", &federate);
      delete[] cptr;
      continue;
    }
    if (theGeRtiEvent.data[i].id == managerFederateAdjustModifyAttributeStateObjectInstance)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theGeRtiEvent.data[i].value);
      GERTICO::Mapper::mapWstringFromChar(objectInstance, cptr);
      delete[] cptr;
      continue;
    }
    if (theGeRtiEvent.data[i].id == managerFederateAdjustModifyAttributeStateAttribute)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theGeRtiEvent.data[i].value);
      sscanf(cptr, "%lu", &attribute);
      delete[] cptr;
      continue;
    }
    if (theGeRtiEvent.data[i].id == managerFederateAdjustModifyAttributeStateAttributeState)
    {
      saveStateIndex = i;
      GERTICO::Mapper::mapOctetSequence(&cptr, theGeRtiEvent.data[i].value);
      GERTICO::Mapper::mapULongSizet(jLen, strlen(cptr));
      for (j = 0; j < jLen; j++)
      {
        cptr[j] = tolower(cptr[j]);
      }
      if (strcmp(cptr, "owned") == 0)
      {
        theBool = true;
        status = owned;
      }
      else
      {
        status = unowned;
      }
      delete[] cptr;
      continue;
    }
  }
  if (theBool)
  {
    CORBA::ULong privilegeToDeleteId;
    GERTICO::RegisteredObject *registeredObject;
    GeRtiFactory::GeRtiHandle unownedFederate = 0;
    std::wstring ws(L"unowned");

    theUnonwedGeRtiEvent = theGeRtiEvent;
    try
    {
      registeredObject = objectManagement.getObjectByName(objectInstance);
      privilegeToDeleteId = objectManagement.getPrivilegeToDeleteId();
      registeredObject->getOwner(unownedFederate, privilegeToDeleteId);
      GERTICO::Mapper::mapHLAinteger32BE(theGeRtiEvent.data[saveFederateIndex], managerInteractionFederateFederate, unownedFederate);
      GERTICO::Mapper::mapHLAunicodeWstring(theGeRtiEvent.data[saveStateIndex], managerFederateAdjustModifyAttributeStateAttributeState, ws);
    }
    catch(...)
    {
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::getMomManagerInteractionRoot(GeRtiFactory::GeRtiHandle &theMomManagerInteractionRoot)
{
  theMomManagerInteractionRoot = managerInteractionRoot;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::ManagementObjectModel::isMomClass(const GeRtiFactory::GeRtiHandle &theClass)
{
  GERTICO::HandleSet::iterator itMomClass;

  itMomClass = momClasses.find(theClass);
  if (itMomClass != momClasses.end())
  {
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::ManagementObjectModel::isMomFederateClass(const GeRtiFactory::GeRtiHandle &theClass)
{
  if (theClass == managerFederateObject)
  {
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::joinFederationExecutionMom(const GeRtiFactory::GeRtiHandle &theFederate)
{
  GERTICO::MomFederate *momFederate;
  GeRtiFactory::GeRtiHandle momFederateFederate;

  momFederateFederate = objectManagement.registerObjectInstance(1, managerFederateObject);
  momFederate = new GERTICO::MomFederate(theFederate, momFederateFederate);

  pm.acquire();
  momFederateMap[theFederate] = momFederate;
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::otherManagerFederateSubscribedAttributes(GERTICO::HandleSet &theAttributes)
{
  GERTICO::Federate *currFederate;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet fedAttributes;
  GERTICO::HandleSet::iterator itFederate;
  GERTICO::HandleSet::iterator itFedAttribute;
  GERTICO::HandleSet::iterator itTheAttribute;

  theAttributes.clear();
  federatesHolder.getFederates(federates);
  for (itFederate = federates.begin(); itFederate != federates.end(); itFederate++)
  {
    currFederate = federatesHolder.getFederate(*itFederate);
    currFederate->getSubscribedAttributes(managerFederateObject, fedAttributes);
    for (itFedAttribute = fedAttributes.begin(); itFedAttribute != fedAttributes.end(); itFedAttribute++)
    {
      itTheAttribute = theAttributes.find(*itFedAttribute);
      if (itTheAttribute == theAttributes.end())
      {
        theAttributes.insert(*itFedAttribute);
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::ManagementObjectModel::requestClassAttributeValueUpdate(const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theAttributes)
{
  if (theClass == managerFederateObject)
  {
    requestManagerFederates(theClass, theAttributes);
    return true;
  }
  if (theClass == managerFederationClass)
  {
    requestManagerFederationUpdate(theClass, theAttributes);
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::ManagementObjectModel::requestObjectAttributeValueUpdate(const GeRtiFactory::GeRtiHandle &theObject, GERTICO::HandleSet &theAttributes)
{
  GERTICO::MomFederateMap::iterator itMomFederateMap;
  GERTICO::RegisteredObject *registeredObject;
  GeRtiFactory::GeRtiHandle object;
  GeRtiFactory::GeRtiHandle whichClass;

  registeredObject = objectManagement.getObject(theObject);
  whichClass = registeredObject->getClassId();
  if (whichClass == managerFederateObject)
  {
    GERTICO::RequestManagerFederateJob *requestManagerFederateJob;

    pm.acquire();
    for (itMomFederateMap = momFederateMap.begin(); itMomFederateMap != momFederateMap.end(); itMomFederateMap++)
    {
      itMomFederateMap->second->getMomFederateFederate(object);
      if (object == theObject)
      {
        requestManagerFederateJob = new GERTICO::RequestManagerFederateJob(federatesHolder, momFederateMap, itMomFederateMap->first, whichClass, theAttributes, managerFederateFDDid, federationFile, eventHandler, interactionRoot);

        federationJobs.add(requestManagerFederateJob);
      }
    }
    pm.release();
    return true;
  }
  if (whichClass == managerFederationClass)
  {
    requestManagerFederationUpdate(whichClass, theAttributes);
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
// Set up a job to handle this request.
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::requestManagerFederates(const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theAttributes)
{
  GERTICO::RequestManagerFederatesJob *requestManagerFederatesJob;

  requestManagerFederatesJob = new GERTICO::RequestManagerFederatesJob(federatesHolder, momFederateMap, theClass, theAttributes, eventHandler, interactionRoot);

  federationJobs.add(requestManagerFederatesJob);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::requestManagerFederationUpdate(const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theAttributes)
{
  CORBA::ULong length;
  GERTICO::ClassDescr *classDescr;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet::iterator itAttribute;
  GERTICO::HandleSet::iterator itFederate;
  GeRtiFactory::GeRtiEvent e;
  GeRtiFactory::PushEvent pushEvent;
  bool reliableFlag;
  unsigned long ul;

  e.type = GeRtiFactory::obj;
  e.source = 0;
  e.theSerialNumber = 0;
  length = 8;
  e.data.length(length);
  length = 0;
  e.data.length(length);
  e.obj = managerFederation;
  e.reg = 0;
  e._cxx_class = theClass;
  classDescr = interactionRoot.getClassDescr(theClass);
  if (classDescr)
  {
    classDescr->getTransportation(ul);
    if (ul)
    {
      // 1 = best effort
      reliableFlag = false;
    }
    else
    {
      // 0 = reliable
      reliableFlag = true;
    }
    e.bestEffort = ul;
    classDescr->getOrdering(ul);
    e.tso = ul;
  }

  itAttribute = theAttributes.find(managerFederationFederationName);
  if (itAttribute != theAttributes.end())
  {
    e.data.length(length + 1);
    GERTICO::Mapper::mapHLAunicodeWstring(e.data[length], managerFederationFederationName, federationName);
    length += 1;
  }

  itAttribute = theAttributes.find(managerFederationFederatesInFederation);
  if (itAttribute != theAttributes.end())
  {
    e.data.length(length + 1);
    federatesHolder.getFederates(federates);
    GERTICO::Mapper::mapHLAhandleList(e.data[length], managerFederationFederatesInFederation, federates);
    length += 1;
  }

  itAttribute = theAttributes.find(managerFederationRTIversion);
  if (itAttribute != theAttributes.end())
  {
    std::wstring s;
    s = L"gertico_0_57";
    e.data.length(length + 1);
    GERTICO::Mapper::mapHLAunicodeWstring(e.data[length], managerFederationRTIversion, s.c_str());
    length += 1;
  }

  itAttribute = theAttributes.find(managerFederationFDDid);
  if (itAttribute != theAttributes.end())
  {
    e.data.length(length + 1);
    GERTICO::Mapper::mapHLAunicodeWstring(e.data[length], managerFederationFDDid, federationFile);
    length += 1;
  }

  itAttribute = theAttributes.find(managerFederationLastSaveName);
  if (itAttribute != theAttributes.end())
  {
    e.data.length(length + 1);
    GERTICO::Mapper::mapHLAunicodeWstring(e.data[length], managerFederationLastSaveName, lastSaveName);
    length += 1;
  }

  itAttribute = theAttributes.find(managerFederationLastSaveTime);
  if (itAttribute != theAttributes.end())
  {
    e.data.length(length + 1);
    GERTICO::Mapper::mapHLAlogicalTime(e.data[length], managerFederationLastSaveTime, lastSaveTime);
    length += 1;
  }

  itAttribute = theAttributes.find(managerFederationNextSaveName);
  if (itAttribute != theAttributes.end())
  {
    e.data.length(length + 1);
    GERTICO::Mapper::mapHLAunicodeWstring(e.data[length], managerFederationNextSaveName, nextSaveName);
    length += 1;
  }

  itAttribute = theAttributes.find(managerFederationNextSaveTime);
  if (itAttribute != theAttributes.end())
  {
    e.data.length(length + 1);
    GERTICO::Mapper::mapHLAlogicalTime(e.data[length], managerFederationNextSaveTime, nextSaveTime);
    length += 1;
  }

  pushEvent.e(e);
  if (eventHandler)
  {
    eventHandler->addEvent(pushEvent, reliableFlag, 0);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::resignFederationExecutionMom(const GeRtiFactory::GeRtiHandle &theFederate)
{
  GERTICO::MomFederateMap::iterator itMomFederateMap;
  GeRtiFactory::GeRtiHandle mom = 1;
  GeRtiFactory::GeRtiHandle federateObject;
  GeRtiFactory::UserSuppliedTag userSuppliedTag;

  pm.acquire();
  itMomFederateMap = momFederateMap.find(theFederate);
  if (itMomFederateMap != momFederateMap.end())
  {
    itMomFederateMap->second->getMomFederateFederate(federateObject);
    objectManagement.deleteObjectInstance(mom, federateObject, userSuppliedTag);
    momFederateMap.erase(itMomFederateMap);
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::reverseChecklist(GERTICO::HandleSet &theItems, GeRtiFactory::GeRtiEvent &theGeRtiEvent)
{
  CORBA::ULong i;
  CORBA::ULong len;
  GERTICO::HandleSet::iterator itItem;

  len = theGeRtiEvent.data.length();
  for (i = 0; i < len; i++)
  {
    itItem = theItems.find(theGeRtiEvent.data[i].id);
    if (itItem != theItems.end())
    {
      theItems.erase(itItem);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::sendAlert(const GeRtiFactory::GeRtiHandle &theFederate, const std::string &theAlertSeverity, const std::string &theAlertDescription)
{
  CORBA::ULong indd = 0;
  GERTICO::ClassDescr *classDescr;
  GERTICO::SendEventsJob *sendEventsJob;
  GeRtiFactory::GeRtiEvent e;
  GeRtiFactory::PushEvent pushEvent;
  bool reliableFlag;
  long l;
  unsigned long ul;

  e.type = GeRtiFactory::interaction;
  e.source = 1;
  e.theSerialNumber = 0;
  GERTICO::Mapper::mapUserSuppliedTag(e.theTag, "MOM");
  e.obj = 0;
  e.reg = 0;
  e._cxx_class = managerFederateReportException;
  classDescr = interactionRoot.getClassDescr(managerFederateReportException);
  if (classDescr)
  {
    classDescr->getTransportation(ul);
    if (ul)
    {
      // 1 = best effort
      reliableFlag = false;
    }
    else
    {
      // 0 = reliable
      reliableFlag = true;
    }
    e.bestEffort = ul;
    classDescr->getOrdering(ul);
    e.tso = ul;
  }

  e.data.length(3);

  indd = 0;
  l = theFederate;
  GERTICO::Mapper::mapHLAinteger32BE(e.data[indd], managerInteractionFederateFederate, l);

  indd = 1;
  GERTICO::Mapper::mapHandleValue(e.data[indd], managerFederateReportExceptionService, theAlertSeverity.c_str());

  indd = 2;
  GERTICO::Mapper::mapHandleValue(e.data[indd], managerFederateReportExceptionException, theAlertDescription.c_str());

  pushEvent.e(e);
  sendEventsJob = new GERTICO::SendEventsJob(pushEvent, eventHandler, reliableFlag);
  federationJobs.add(sendEventsJob);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::setFederationFile(const std::wstring &theFederationFile)
{
  federationFile = theFederationFile;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::setFederationName(const std::wstring &theFederationName)
{
  federationName = theFederationName;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::setNextSaveName(const std::wstring &theName)
{
  if (theName.size() == 0)
  {
    lastSaveName = nextSaveName;
    lastSaveTime = nextSaveTime;
  }
  nextSaveName = theName;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::setNextSaveTime(std::auto_ptr<GERTICO::GeRtiFedTime> &theTime)
{
  nextSaveTime = theTime;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::testFoundValues(std::wstring const &theMomName, bool const &theFoundItem, bool const &theFoundClass)
throw
(
  GeRtiFactory::ErrorReadingFED
)
{
  if (theFoundClass == false)
  {
    std::wstring noClass = L"MOM class not found: ";
    noClass.append(theMomName);
    throw GeRtiFactory::ErrorReadingFED(noClass.c_str());
  }
  if (theFoundItem == false)
  {
    std::wstring noItem = L"MOM attribute / parameter not found: ";
    noItem.append(theMomName);
    throw GeRtiFactory::ErrorReadingFED(noItem.c_str());
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::unconditionalAttributeOwnershipDivestiture(const GeRtiFactory::GeRtiEvent &theGeRtiEvent)
{

  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::RegisteredObject *registeredObject;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::Handles attributes;
  std::string alertDescription;
  std::string alertSeverity;
  bool gotError = false;
  long l;
  long objectInstance;

  lengthi = theGeRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theGeRtiEvent.data[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theGeRtiEvent.data[i].value);
      federate = l;
    }

    if (theGeRtiEvent.data[i].id == managerFederateServiceUnconditionalAttributeOwnershipDivestitureObjectInstance)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theGeRtiEvent.data[i].value);
      objectInstance = l;
    }

    if (theGeRtiEvent.data[i].id == managerFederateServiceUnconditionalAttributeOwnershipDivestitureAttributeList)
    {
      GERTICO::Mapper::mapHLAAttributesFromOctetSequence(attributes, theGeRtiEvent.data[i].value);
    }
  }

  registeredObject = objectManagement.getObject(objectInstance);
  if (registeredObject)
  {
    try
    {
      ownershipMaster.unconditionalAttributeOwnershipDivestiture(federate, registeredObject->getId(), attributes);
    }
    catch(GeRtiFactory::ObjectNotKnown &)
    {
      gotError = true;
      alertDescription = "ObjectNotKnown";
      alertSeverity = "RTI exception";
    }
    catch(GeRtiFactory::AttributeNotDefined &)
    {
      gotError = true;
      alertDescription = "AttributeNotDefined";
      alertSeverity = "RTI exception";
    }
    catch(GeRtiFactory::AttributeNotOwned &)
    {
      gotError = true;
      alertDescription = "AttributeNotOwned";
      alertSeverity = "RTI exception";
    }
    catch(GeRtiFactory::FederateNotExecutionMember &)
    {
      gotError = true;
      alertDescription = "FederateNotExecutionMember";
      alertSeverity = "RTI exception";
    }
    catch(GeRtiFactory::ConcurrentAccessAttempted &)
    {
      gotError = true;
      alertDescription = "ConcurrentAccessAttempted";
      alertSeverity = "RTI exception";
    }
    catch(GeRtiFactory::SaveInProgress &)
    {
      gotError = true;
      alertDescription = "SaveInProgress";
      alertSeverity = "RTI exception";
    }
    catch(GeRtiFactory::RestoreInProgress &)
    {
      gotError = true;
      alertDescription = "RestoreInProgress";
      alertSeverity = "RTI exception";
    }
    catch(GeRtiFactory::RTIinternalError &)
    {
      gotError = true;
      alertDescription = "RTIinternalError";
      alertSeverity = "RTI exception";
    }
  }
  else
  {
    gotError = true;
    alertDescription = "ObjectNotKnown";
    alertSeverity = "RTI exception";
  }

  if (gotError)
  {
    GERTICO::MomFederateMap::iterator itMomFederateMap;
    bool exceptionLogging;

    pm.acquire();
    itMomFederateMap = momFederateMap.find(federate);
    if (itMomFederateMap != momFederateMap.end())
    {
      exceptionLogging = itMomFederateMap->second->checkExceptionLogging();
      if (exceptionLogging)
      {
        sendAlert(federate, alertSeverity, alertDescription);
      }
    }
    pm.release();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::wallClockWorker(void)
{
  GERTICO::HandleSet attributes;
  GERTICO::MomFederateMap::iterator itMomFederateMap;
  GERTICO::RequestManagerFederateJob *requestManagerFederateJob;

  wallClockCounter += 1;

  pm.acquire();
  for (itMomFederateMap = momFederateMap.begin(); itMomFederateMap != momFederateMap.end(); itMomFederateMap++)
  {
    if (itMomFederateMap->second->checkReportPeriod(wallClockCounter))
    {
      otherManagerFederateSubscribedAttributes(attributes);

      requestManagerFederateJob = new GERTICO::RequestManagerFederateJob(federatesHolder, momFederateMap, itMomFederateMap->first, managerFederateObject, attributes, managerFederateFDDid, federationFile, eventHandler, interactionRoot);

      federationJobs.add(requestManagerFederateJob);

      ps.release();
    }
  }
  pm.release();
}
