/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
** ManagementObjectModel.cpp
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
#ifdef IEEE_1516
  suppliedArguments = 0;
  returnedArguments = 0;
  exceptionDescription = 0;
#else
  suppliedArgument1 = 0;
  suppliedArgument2 = 0;
  suppliedArgument3 = 0;
  suppliedArgument4 = 0;
  suppliedArgument5 = 0;
  returnedArgument = 0;
  exceptionDescription = 0;
  exceptionID = 0;
#endif
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
GERTICO::JobStatus GERTICO::MomRequestPublications::execute(void)
{
  CORBA::ULong i;
  CORBA::ULong indd;
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  size_t pos;
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *currFederate = NULL;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::PushEvent pushEvent;
  bool gotFederate = false;
  bool reliableFlag;
  char buff[512];
  long l;
  size_t lenObjects;
  unsigned long ul;

  lengthi = geRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = geRtiEvent.data[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = geRtiEvent.data[i].value[j];
    }
    buff[lengthj] = '\0';

    if (geRtiEvent.data[i].id == momReportObjectPublicationHandles.federate)
    {
      sscanf(buff, "%ld", &l);
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
      lenObjects = publishedClasses.size();

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
        sprintf(buff, "%ld", l);
        GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectPublicationHandles.federate, buff);
        buff[0] = '\0';

        indd += 1;
        strcpy(buff, "0");
        GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectPublicationHandles.numberOfClasses, buff);
        buff[0] = '\0';

        indd += 1;
        GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectPublicationHandles.objectClass, buff);
        buff[0] = '\0';

        indd += 1;
        GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectPublicationHandles.attributeList, buff);
        buff[0] = '\0';

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
            e.bestEffort = ul;
            classDescr->getOrdering(ul);
            e.tso = ul;
          }

          // NB.
          e.data.length(4);

          indd = 0;
          l = federate;
          sprintf(buff, "%ld", l);
          GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectPublicationHandles.federate, buff);
          buff[0] = '\0';

          indd += 1;
          sprintf(buff, "%d", publishedClasses.size());
          GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectPublicationHandles.numberOfClasses, buff);
          buff[0] = '\0';

          indd += 1;
          l = *itPublishedObjectClass;
          sprintf(buff, "%ld", l);
          GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectPublicationHandles.objectClass, buff);
          buff[0] = '\0';

          indd += 1;
          currFederate->getPublishedAttributes(*itPublishedObjectClass, attributes);
          pos = 0;
          attributes.insert(privilegeToDeleteId);
          for (itAttribute = attributes.begin(); itAttribute != attributes.end(); itAttribute++)
          {
            l = *itAttribute;
            if (pos)
            {
              sprintf(&buff[pos], ",%ld", l);
            }
            else
            {
              sprintf(&buff[pos], "%ld", l);
            }
            pos = strlen(buff);
          }
          GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectPublicationHandles.attributeList, buff);
          buff[0] = '\0';

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
        e.bestEffort = ul;
        classDescr->getOrdering(ul);
        e.tso = ul;
      }

      // NB.
      e.data.length(2);

      indd = 0;
      l = federate;
      sprintf(buff, "%ld", l);
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportInteractionPublicationHandles.federate, buff);
      buff[0] = '\0';

      indd += 1;
//      eventHandler.declarationManagementEC->interactionHolder->getPublishedInteractionClasses(federate, publishedInteractionClasses);
      pos = 0;
      for (itPublishedInteractionClass = publishedInteractionClasses.begin(); itPublishedInteractionClass != publishedInteractionClasses.end(); itPublishedInteractionClass++)
      {
        l = *itPublishedInteractionClass;
        if (pos)
        {
          sprintf(&buff[pos], ",%ld", l);
        }
        else
        {
          sprintf(&buff[pos], "%ld", l);
        }
        pos = strlen(buff);
      }
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportInteractionPublicationHandles.interactionClassList, buff);
      buff[0] = '\0';

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
GERTICO::JobStatus GERTICO::MomRequestSubscriptions::execute(void)
{
  CORBA::ULong i;
  CORBA::ULong indd;
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *currFederate = NULL;
  GeRtiFactory::GeRtiEvent e;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::PushEvent pushEvent;
  bool gotFederate = false;
  bool reliableFlag;
  char buff[512];
  long l;
  size_t lenObjects;
  size_t pos;
  unsigned long ul;

  lengthi = geRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = geRtiEvent.data[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = geRtiEvent.data[i].value[j];
    }
    buff[lengthj] = '\0';

    if (geRtiEvent.data[i].id == momReportObjectSubscriptionHandles.federate)
    {
      sscanf(buff, "%ld", &l);
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
      lenObjects = subscribedObjectClasses.size();

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
        sprintf(buff, "%ld", l);
        GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectSubscriptionHandles.federate, buff);

        indd += 1;
        strcpy(buff, "0");
        GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectSubscriptionHandles.numberOfClasses, buff);

        indd += 1;
        buff[0] = '\0';
        GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectSubscriptionHandles.objectClass, buff);

        indd += 1;
        buff[0] = '\0';
        GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectSubscriptionHandles.attributeList, buff);

        indd += 1;
        buff[0] = '\0';
        GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectSubscriptionHandles.active, buff);

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
            e.bestEffort = ul;
            classDescr->getOrdering(ul);
            e.tso = ul;
          }

          // NB.
          e.data.length(5);

          indd = 0;
          l = federate;
          sprintf(buff, "%ld", l);
          GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectSubscriptionHandles.federate, buff);

          indd += 1;
          sprintf(buff, "%d", subscribedObjectClasses.size());
          GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectSubscriptionHandles.numberOfClasses, buff);

          indd += 1;
          l = *itSubscribedObjectClass;
          sprintf(buff, "%ld", l);
          GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectSubscriptionHandles.objectClass, buff);

          indd += 1;
          currFederate->getSubscribedAttributes(*itSubscribedObjectClass, attributes);
          pos = 0;
          buff[0] = '\0';
          for (itAttribute = attributes.begin(); itAttribute != attributes.end(); itAttribute++)
          {
            l = *itAttribute;
            if (pos)
            {
              sprintf(&buff[pos], ",%ld", l);
            }
            else
            {
              sprintf(&buff[pos], "%ld", l);
            }
            pos = strlen(buff);
          }
          GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectSubscriptionHandles.attributeList, buff);

          indd += 1;
          strcpy(buff, "True");
          GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectSubscriptionHandles.active, buff);

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
        e.bestEffort = ul;
        classDescr->getOrdering(ul);
        e.tso = ul;
      }

      // NB.
      e.data.length(2);

      indd = 0;
      l = federate;
      sprintf(buff, "%ld", l);
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportInteractionSubscriptionHandles.federate, buff);

      indd += 1;
//      eventHandler.declarationManagementEC->interactionHolder->getSubscribedInteractionClasses(federate, subscribedInteractionClasses);
      pos = 0;
      buff[0] = '\0';
      for (itSubscribedInteractionClass = subscribedInteractionClasses.begin(); itSubscribedInteractionClass != subscribedInteractionClasses.end(); itSubscribedInteractionClass++)
      {
        char tmpBuff[16];
        if (itSubscribedInteractionClass->second)
        {
          strcpy(tmpBuff, "active");
        }
        else
        {
          strcpy(tmpBuff, "passive");
        }
        l = itSubscribedInteractionClass->first;
        if (pos)
        {
          sprintf(&buff[pos], ",%ld/%s", l, tmpBuff);
        }
        else
        {
          sprintf(&buff[pos], "%ld/%s", l, tmpBuff);
        }
        pos = strlen(buff);
      }
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportInteractionSubscriptionHandles.interactionClassList, buff);

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
GERTICO::JobStatus GERTICO::MomRequestObjectsOwned::execute(void)
{
  CORBA::ULong i;
  CORBA::ULong indd;
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  size_t pos;
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *currFederate = NULL;
  GeRtiFactory::GeRtiEvent e;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::PushEvent pushEvent;
  bool gotFederate = false;
  bool reliableFlag;
  char buff[512];
  long l;
  long l1;
  unsigned long ul;

  lengthi = geRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = geRtiEvent.data[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = geRtiEvent.data[i].value[j];
    }
    buff[lengthj] = '\0';

    if (geRtiEvent.data[i].id == momReportObjectsHandles.federate)
    {
      sscanf(buff, "%ld", &l);
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
      sprintf(buff, "%ld", l);
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectsHandles.federate, buff);

      indd += 1;
      buff[0] = '\0';
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
      pos = 0;
      for (itObjectClass = handleMap.begin(); itObjectClass != handleMap.end(); itObjectClass++)
      {
        l = itObjectClass->first;
        l1 = itObjectClass->second;
        if (pos)
        {
          sprintf(&buff[pos], ",%ld/%ld", l, l1);
        }
        else
        {
          sprintf(&buff[pos], "%ld/%ld", l, l1);
        }
        pos = strlen(buff);
      }
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectsHandles.objectCounts, buff);

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
GERTICO::JobStatus GERTICO::MomRequestObjectsUpdated::execute(void)
{
  CORBA::ULong i;
  CORBA::ULong indd;
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *currFederate = NULL;
  GeRtiFactory::GeRtiEvent e;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::PushEvent pushEvent;
  bool gotFederate = false;
  bool reliableFlag;
  char buff[512];
  long l;
  long l1;
  size_t pos;
  unsigned long ul;

  lengthi = geRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = geRtiEvent.data[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = geRtiEvent.data[i].value[j];
    }
    buff[lengthj] = '\0';

    if (geRtiEvent.data[i].id == momReportObjectsHandles.federate)
    {
      sscanf(buff, "%ld", &l);
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
      sprintf(buff, "%ld", l);
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectsHandles.federate, buff);

      indd += 1;
      buff[0] = '\0';
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
      pos = 0;
      for (itObjectClass = handleMap.begin(); itObjectClass != handleMap.end(); itObjectClass++)
      {
        l = itObjectClass->first;
        l1 = itObjectClass->second;
        if (pos)
        {
          sprintf(&buff[pos], ",%ld/%ld", l, l1);
        }
        else
        {
          sprintf(&buff[pos], "%ld/%ld", l, l1);
        }
        pos = strlen(buff);
      }
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectsHandles.objectCounts, buff);

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
GERTICO::JobStatus GERTICO::MomRequestObjectsReflected::execute(void)
{
  CORBA::ULong i;
  CORBA::ULong indd;
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *currFederate = NULL;
  GeRtiFactory::GeRtiEvent e;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::PushEvent pushEvent;
  bool gotFederate = false;
  bool reliableFlag;
  char buff[512];
  long l;
  long l1;
  size_t pos;
  unsigned long ul;

  lengthi = geRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = geRtiEvent.data[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = geRtiEvent.data[i].value[j];
    }
    buff[lengthj] = '\0';

    if (geRtiEvent.data[i].id == momReportObjectsHandles.federate)
    {
      sscanf(buff, "%ld", &l);
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
      sprintf(buff, "%ld", l);
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectsHandles.federate, buff);

      indd += 1;
      buff[0] = '\0';
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
      pos = 0;
      for (itObjectClass = handleMap.begin(); itObjectClass != handleMap.end(); itObjectClass++)
      {
        l = itObjectClass->first;
        l1 = itObjectClass->second;
        if (pos)
        {
          sprintf(&buff[pos], ",%ld/%ld", l, l1);
        }
        else
        {
          sprintf(&buff[pos], "%ld/%ld", l, l1);
        }
        pos = strlen(buff);
      }
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectsHandles.objectCounts, buff);

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
GERTICO::JobStatus GERTICO::MomRequestUpdatesSent::execute(void)
{
  CORBA::ULong i;
  CORBA::ULong indd;
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *currFederate = NULL;
  GeRtiFactory::GeRtiEvent e;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::PushEvent pushEvent;
  bool gotFederate = false;
  bool reliableFlag;
  char buff[512];
  long l;
  unsigned long ul;

  lengthi = geRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = geRtiEvent.data[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = geRtiEvent.data[i].value[j];
    }
    buff[lengthj] = '\0';

    if (geRtiEvent.data[i].id == momReportUpdatesSentHandles.federate)
    {
      sscanf(buff, "%ld", &l);
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
      sprintf(buff, "%ld", l);
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportUpdatesSentHandles.federate, buff);

      indd += 1;
      strcpy(buff, "Reliable");
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportUpdatesSentHandles.transportationType, buff);

      indd += 1;
      buff[0] = '\0';
      if (eventHandler)
      {
        eventHandler->getUpdatesSentCounts(federate, buff, false);
      }
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportUpdatesSentHandles.updateCounts, buff);

      pushEvent.e(e);
      if (eventHandler)
      {
	      eventHandler->addEvent(pushEvent, reliableFlag, 0);
      }

      indd = 1;
      strcpy(buff, "Best Effort");
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportUpdatesSentHandles.transportationType, buff);

      indd += 1;
      buff[0] = '\0';
      if (eventHandler)
      {
        eventHandler->getUpdatesSentCounts(federate, buff, true);
      }
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportUpdatesSentHandles.updateCounts, buff);

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
GERTICO::JobStatus GERTICO::MomRequestReflectionsReceived::execute(void)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong len;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *currFederate = NULL;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::PushEvent pushEvent;
  bool gotFederate = false;
  bool reliableFlag;
  char buff[512];
  long l;
  unsigned long ul;

  lengthi = geRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = geRtiEvent.data[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = geRtiEvent.data[i].value[j];
    }
    buff[lengthj] = '\0';

    if (geRtiEvent.data[i].id == momReportReflectionsReceivedHandles.federate)
    {
      sscanf(buff, "%ld", &l);
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

      currFederate->getMomData(momReportReflectionsReceivedHandles.momClassId, handles, data);

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
GERTICO::JobStatus GERTICO::MomRequestInteractionsSent::execute(void)
{
  CORBA::ULong i;
  CORBA::ULong indd;
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *currFederate = NULL;
  GeRtiFactory::GeRtiEvent e;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::PushEvent pushEvent;
  bool gotFederate = false;
  bool reliableFlag;
  char buff[512];
  long l;
  unsigned long ul;

  lengthi = geRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = geRtiEvent.data[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = geRtiEvent.data[i].value[j];
    }
    buff[lengthj] = '\0';

    if (geRtiEvent.data[i].id == momReportInteractionsHandles.federate)
    {
      sscanf(buff, "%ld", &l);
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
      sprintf(buff, "%ld", l);
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportInteractionsHandles.federate, buff);

      indd += 1;
      strcpy(buff, "Reliable");
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportInteractionsHandles.transportationType, buff);

      indd += 1;
      buff[0] = '\0';
      if (eventHandler)
      {
        eventHandler->getInteractionsSentCount(federate, buff, false);
      }
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportInteractionsHandles.interactionCounts, buff);

      pushEvent.e(e);
      if (eventHandler)
      {
        eventHandler->addEvent(pushEvent, reliableFlag, 0);
      }

      indd = 1;
      strcpy(buff, "Best Effort");
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportInteractionsHandles.transportationType, buff);

      indd += 1;
      buff[0] = '\0';
      if (eventHandler)
      {
        eventHandler->getInteractionsSentCount(federate, buff, true);
      }
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportInteractionsHandles.interactionCounts, buff);

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
GERTICO::JobStatus GERTICO::MomRequestInteractionsReceived::execute(void)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong len;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *currFederate = NULL;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::PushEvent pushEvent;
  bool gotFederate = false;
  bool reliableFlag;
  char buff[512];
  long l;
  unsigned long ul;

  lengthi = geRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = geRtiEvent.data[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = geRtiEvent.data[i].value[j];
    }
    buff[lengthj] = '\0';

    if (geRtiEvent.data[i].id == momReportInteractionsHandles.federate)
    {
      sscanf(buff, "%ld", &l);
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

      currFederate->getMomData(momReportInteractionsHandles.momClassId, handles, data);

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
GERTICO::JobStatus GERTICO::MomRequestObjectsInformation::execute(void)
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
  char buff[512];
  char *cptr;
  long l;
  std::string s;
  std::wstring objectInstanceStr;
  size_t pos;
  unsigned long ul;

  lengthi = geRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (geRtiEvent.data[i].id == momReportObjectInformationHandles.federate)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, geRtiEvent.data[i].value);
      sscanf(cptr, "%ld", &l);
      federate = l;
      delete[] cptr;
      if (federate)
      {
        gotFederate = true;
      }
    }

    if (geRtiEvent.data[i].id == objectHandle)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, geRtiEvent.data[i].value);
      GERTICO::Mapper::mapWstringFromChar(objectInstanceStr, cptr);
      delete[] cptr;
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
        }        e.bestEffort = ul;
        classDescr->getOrdering(ul);
        e.tso = ul;
      }

      // NB.
      e.data.length(5);

      indd = 0;
      l = federate;
      sprintf(buff, "%ld", l);
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectInformationHandles.federate, buff);

      indd += 1;
      buff[0] = '\0';
      registeredObject = objectManagement.getObjectByName(objectInstanceStr.c_str());
//      registeredObject = objectManagement.getObject(object);
      registeredObject->getName(objectName);
      GERTICO::Mapper::mapStringFromWstring(s, objectName);
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectInformationHandles.objectInstance, s.c_str());

      indd += 1;
      buff[0] = '\0';
      privilegeToDeleteId = objectManagement.getPrivilegeToDeleteId();
      registeredObject->getOwnedAttributes(federate, privilegeToDeleteId, attributes, true);
      pos = 0;
      for (itAttribute = attributes.begin(); itAttribute != attributes.end(); itAttribute++)
      {
        l = *itAttribute;
        if (pos)
        {
          sprintf(&buff[pos], ",%ld", l);
        }
        else
        {
          sprintf(&buff[pos], "%ld", l);
        }
        pos = strlen(buff);
      }
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectInformationHandles.objectAttributeList, buff);

      indd += 1;
      buff[0] = '\0';
      try
      {
        // Only if the federate knows the object!
        knownObjectClass = currFederate->getObjectClass(registeredObject->getId());
        registeredClass = registeredObject->getClassId();
        l = registeredClass;
        sprintf(buff, "%ld", l);
      }
      catch(...)
      {
      }
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectInformationHandles.registeredClass, buff);

      indd += 1;
      buff[0] = '\0';
      try
      {
        knownObjectClass = currFederate->getObjectClass(registeredObject->getId());
        l = knownObjectClass;
        sprintf(buff, "%ld", l);
      }
      catch(...)
      {
      }
      GERTICO::Mapper::mapHandleValue(e.data[indd], momReportObjectInformationHandles.knownClass, buff);

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
GERTICO::JobStatus GERTICO::DoMomRequest::execute(void)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::Federate *currFederate = NULL;
  GeRtiFactory::GeRtiHandle federate = 0;
  bool gotFederate = false;
  char *cptr;
  long l;

  lengthi = geRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (geRtiEvent.data[i].id == federateParameter)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, geRtiEvent.data[i].value);
      sscanf(cptr, "%ld", &l);
      federate = l;
      delete[] cptr;
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
  CORBA::ULong ind = 0;
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

        currFederate->getMomData(whichClass, handles, data);
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
  CORBA::ULong ind;
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

  ind = 0;
  try
  {
    currFederate->getMomData(whichClass, handles, data);
    len = data->length();
    for (i = 0; i < len; i++)
    {
      if (data[i].id == managerFederateFEDid)
      {
        std::string s;
        GERTICO::Mapper::mapStringFromWstring(s, federationFile);
        GERTICO::Mapper::mapHandleValue(data[i], managerFederateFEDid, s.c_str());
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
  catch(CORBA::UserException &userex)
  {
    ACE_PRINT_EXCEPTION(userex, "RequestManagerFederateJob");
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
  eventHandler = theEventHandler;
  bool foundClass = false;
  bool foundItem = false;
  wallClockCounter = 0;

  // Default region.
  regions.insert(0);

  // Manager
#ifdef IEEE_1516
  std::wstring ws;
  ws = L"HLAmanager";
  managerObject = supportingServices.findObjectClassHandle(ws);
  momClasses.insert(managerObject);

  // Manager.Federate
  ws = L"HLAmanager.HLAfederate";
  managerFederateObjectClass = supportingServices.findObjectClassHandle(ws);

  ws = L"HLAfederateHandle";
  supportingServices.getObjectClassItem(ws, managerFederateObjectClass, managerFederateFederateHandle, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateFederateHandle);

  ws = L"HLAfederateType";
  supportingServices.getObjectClassItem(ws, managerFederateObjectClass, managerFederateFederateType, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateFederateType);

  ws = L"HLAfederateHost";
  supportingServices.getObjectClassItem(ws, managerFederateObjectClass, managerFederateFederateHost, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateFederateHost);

  ws = L"HLARTIversion";
  supportingServices.getObjectClassItem(ws, managerFederateObjectClass, managerFederateRTIversion, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateRTIversion);

  ws = L"HLAFDDID";
  supportingServices.getObjectClassItem(ws, managerFederateObjectClass, managerFederateFEDid, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateFEDid);

  ws = L"HLAtimeConstrained";
  supportingServices.getObjectClassItem(ws, managerFederateObjectClass, managerFederateTimeConstrained, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateTimeConstrained);

  ws = L"HLAtimeRegulating";
  supportingServices.getObjectClassItem(ws, managerFederateObjectClass, managerFederateTimeRegulating, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateTimeRegulating);

  ws = L"HLAasynchronousDelivery";
  supportingServices.getObjectClassItem(ws, managerFederateObjectClass, managerFederateAsynchronousDelivery, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateAsynchronousDelivery);

  ws = L"HLAfederateState";
  supportingServices.getObjectClassItem(ws, managerFederateObjectClass, managerFederateFederateState, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateFederateState);

  ws = L"HLAtimeManagerState";
  supportingServices.getObjectClassItem(ws, managerFederateObjectClass, managerFederateTimeManagerState, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateTimeManagerState);

  ws = L"HLAlogicalTime";
  supportingServices.getObjectClassItem(ws, managerFederateObjectClass, managerFederateFederateTime, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateFederateTime);

  ws = L"HLAlookahead";
  supportingServices.getObjectClassItem(ws, managerFederateObjectClass, managerFederateLookahead, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateLookahead);

  ws = L"HLAGALT";
  supportingServices.getObjectClassItem(ws, managerFederateObjectClass, managerFederateLBTS, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateLBTS);

  ws = L"HLALITS";
  supportingServices.getObjectClassItem(ws, managerFederateObjectClass, managerFederateMinNextEventTime, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateMinNextEventTime);

  ws = L"HLAROlength";
  supportingServices.getObjectClassItem(ws, managerFederateObjectClass, managerFederateROlength, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateROlength);

  ws = L"HLATSOlength";
  supportingServices.getObjectClassItem(ws, managerFederateObjectClass, managerFederateTSOlength, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateTSOlength);

  ws = L"HLAreflectionsReceived";
  supportingServices.getObjectClassItem(ws, managerFederateObjectClass, managerFederateReflectionsReceived, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateReflectionsReceived);

  ws = L"HLAupdatesSent";
  supportingServices.getObjectClassItem(ws, managerFederateObjectClass, managerFederateUpdatesSent, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateUpdatesSent);

  ws = L"HLAinteractionsReceived";
  supportingServices.getObjectClassItem(ws, managerFederateObjectClass, managerFederateInteractionsReceived, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateInteractionsReceived);

  ws = L"HLAinteractionsSent";
  supportingServices.getObjectClassItem(ws, managerFederateObjectClass, managerFederateInteractionsSent, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateInteractionsSent);

  ws = L"HLAobjectInstancesThatCanBeDeleted";
  supportingServices.getObjectClassItem(ws, managerFederateObjectClass, managerFederateObjectsOwned, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateObjectsOwned);

  ws = L"HLAobjectInstancesUpdated";
  supportingServices.getObjectClassItem(ws, managerFederateObjectClass, managerFederateObjectsUpdated, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateObjectsUpdated);

  ws = L"HLAobjectInstancesReflected";
  supportingServices.getObjectClassItem(ws, managerFederateObjectClass, managerFederateObjectsReflected, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateObjectsReflected);

  declarationManagement.publishObjectClass(1, managerFederateObjectClass, managerFederateAttributes);

  // Manager.Federation
  ws = L"HLAmanager.HLAfederation";
  managerFederationClass = supportingServices.findObjectClassHandle(ws);
  momClasses.insert(managerFederationClass);

  ws = L"HLAfederationName";
  supportingServices.getObjectClassItem(ws, managerFederationClass, managerFederationFederationName, foundItem, foundClass);
  managerFederationAttributes.insert(managerFederationFederationName);

  ws = L"HLAfederatesInFederation";
  supportingServices.getObjectClassItem(ws, managerFederationClass, managerFederationFederatesInFederation, foundItem, foundClass);
  managerFederationAttributes.insert(managerFederationFederatesInFederation);

  ws = L"HLARTIversion";
  supportingServices.getObjectClassItem(ws, managerFederationClass, managerFederationRTIversion, foundItem, foundClass);
  managerFederationAttributes.insert(managerFederationRTIversion);

  ws = L"HLAFDDID";
  supportingServices.getObjectClassItem(ws, managerFederationClass, managerFederationFEDid, foundItem, foundClass);
  managerFederationAttributes.insert(managerFederationFEDid);

  ws = L"HLAlastSaveName";
  supportingServices.getObjectClassItem(ws, managerFederationClass, managerFederationLastSaveName, foundItem, foundClass);
  managerFederationAttributes.insert(managerFederationLastSaveName);

  ws = L"HLAlastSaveTime";
  supportingServices.getObjectClassItem(ws, managerFederationClass, managerFederationLastSaveTime, foundItem, foundClass);
  managerFederationAttributes.insert(managerFederationLastSaveTime);

  ws = L"HLAnextSaveName";
  supportingServices.getObjectClassItem(ws, managerFederationClass, managerFederationNextSaveName, foundItem, foundClass);
  managerFederationAttributes.insert(managerFederationNextSaveName);

  ws = L"HLAnextSaveTime";
  supportingServices.getObjectClassItem(ws, managerFederationClass, managerFederationNextSaveTime, foundItem, foundClass);
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

  // Adjust
  // Manager.Federate.Adjust.SetTiming
  ws = L"HLAmanager.HLAfederate.HLAadjust.HLAsetTiming";
  managerFederateAdjustSetTiming = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateAdjustSetTiming);
  declarationManagement.subscribeInteractionClass(1, managerFederateAdjustSetTiming, active, regions);
  ws = L"HLAreportPeriod";
  supportingServices.getParameterHandle(ws, managerFederateAdjustSetTiming, managerFederateAdjustSetTimingReportPeriod, foundItem, foundClass);

  // Manager.Federate.Adjust.ModifyAttributeState
  ws = L"HLAmanager.HLAfederate.HLAadjust.HLAmodifyAttributeState";
  managerFederateAdjustModifyAttributeState = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateAdjustModifyAttributeState);
  declarationManagement.subscribeInteractionClass(1, managerFederateAdjustModifyAttributeState, active, regions);
  ws = L"HLAobjectInstance";
  supportingServices.getParameterHandle(ws, managerFederateAdjustModifyAttributeState, managerFederateAdjustModifyAttributeStateObjectInstance, foundItem, foundClass);
  ws = L"HLAattribute";
  supportingServices.getParameterHandle(ws, managerFederateAdjustModifyAttributeState, managerFederateAdjustModifyAttributeStateAttribute, foundItem, foundClass);
  ws = L"HLAattributeState";
  supportingServices.getParameterHandle(ws, managerFederateAdjustModifyAttributeState, managerFederateAdjustModifyAttributeStateAttributeState, foundItem, foundClass);

  // Manager.Federate.Adjust.SetServiceReporting
  ws = L"HLAmanager.HLAfederate.HLAadjust.HLAsetServiceReporting";
  managerFederateAdjustSetServiceReporting = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateAdjustSetServiceReporting);
  declarationManagement.subscribeInteractionClass(1, managerFederateAdjustSetServiceReporting, active, regions);
  ws = L"HLAreportingState";
  supportingServices.getParameterHandle(ws, managerFederateAdjustSetServiceReporting, managerFederateAdjustSetServiceReportingState, foundItem, foundClass);

  // Manager.Federate.Adjust.SetExceptionReporting
  ws = L"HLAmanager.HLAfederate.HLAadjust.HLAsetExceptionReporting";
  managerFederateAdjustSetExceptionReporting = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateAdjustSetExceptionReporting);
  declarationManagement.subscribeInteractionClass(1, managerFederateAdjustSetExceptionReporting, active, regions);
  ws = L"HLAreportingState";
  supportingServices.getParameterHandle(ws, managerFederateAdjustSetExceptionReporting, managerFederateAdjustSetExceptionReportingState, foundItem, foundClass);

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
  ws = L"HLAobjectClass";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectClassPublication, managerFederateReportObjectPublicationObjectClass, foundItem, foundClass);
  ws = L"HLAattributeList";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectClassPublication, managerFederateReportObjectPublicationAttributeList, foundItem, foundClass);
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
  momReportInteractionPublicationHandles.momClassId = managerFederateReportInteractionPublication;
  momReportInteractionPublicationHandles.federate = managerInteractionFederateFederate;
  momReportInteractionPublicationHandles.interactionClassList = managerFederateReportInteractionPublicationInteractionClassList;

  // Manager.Federate.Report.ReportObjectSubscription
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportObjectClassSubscription";
  managerFederateReportObjectClassSubscription = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAnumberOfClasses";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectClassSubscription, managerFederateReportObjectSubscriptionNumberOfClasses, foundItem, foundClass);
  ws = L"HLAobjectClass";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectClassSubscription, managerFederateReportObjectSubscriptionObjectClass, foundItem, foundClass);
  ws = L"HLAattributeList";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectClassSubscription, managerFederateReportObjectSubscriptionAttributeList, foundItem, foundClass);
  ws = L"HLAactive";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectClassSubscription, managerFederateReportObjectSubscriptionActive, foundItem, foundClass);
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
  momReportInteractionSubscriptionHandles.momClassId = managerFederateReportInteractionSubscription;
  momReportInteractionSubscriptionHandles.federate = managerInteractionFederateFederate;
  momReportInteractionSubscriptionHandles.interactionClassList = managerFederateReportInteractionSubscriptionInteractionClassList;

  // Manager.Federate.Report.ReportObjectsOwned
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportObjectInstancesThatCanBeDeleted";
  managerFederateReportObjectInstancesThatCanBeDeleted = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAobjectInstanceCounts";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectInstancesThatCanBeDeleted, managerFederateReportObjectsOwnedObjectCounts, foundItem, foundClass);
  momReportObjectsOwnedHandles.momClassId = managerFederateReportObjectInstancesThatCanBeDeleted;
  momReportObjectsOwnedHandles.federate = managerInteractionFederateFederate;
  momReportObjectsOwnedHandles.objectCounts = managerFederateReportObjectsOwnedObjectCounts;

  // Manager.Federate.Report.ReportObjectsUpdated
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportObjectInstancesUpdated";
  managerFederateReportObjectInstancessUpdated = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAobjectInstanceCounts";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectInstancessUpdated, managerFederateReportObjectsUpdatedObjectCounts, foundItem, foundClass);
  momReportObjectsUpdatedHandles.momClassId = managerFederateReportObjectInstancessUpdated;
  momReportObjectsUpdatedHandles.federate = managerInteractionFederateFederate;
  momReportObjectsUpdatedHandles.objectCounts = managerFederateReportObjectsUpdatedObjectCounts;

  // Manager.Federate.Report.ReportObjectsReflected
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportObjectInstancesReflected";
  managerFederateReportObjectInstancessReflected = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAobjectInstanceCounts";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectInstancessReflected, managerFederateReportObjectsReflectedObjectCounts, foundItem, foundClass);
  momReportObjectsReflectedHandles.momClassId = managerFederateReportObjectInstancessReflected;
  momReportObjectsReflectedHandles.federate = managerInteractionFederateFederate;
  momReportObjectsReflectedHandles.objectCounts = managerFederateReportObjectsReflectedObjectCounts;

  // Manager.Federate.Report.ReportUpdatesSent
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportUpdatesSent";
  managerFederateReportUpdatesSent = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAtransportation";
  supportingServices.getParameterHandle(ws, managerFederateReportUpdatesSent, managerFederateReportUpdatesSentTransportationType, foundItem, foundClass);
  ws = L"HLAupdateCounts";
  supportingServices.getParameterHandle(ws, managerFederateReportUpdatesSent, managerFederateReportUpdatesSentUpdateCounts, foundItem, foundClass);
  momReportUpdatesSentHandles.momClassId = managerFederateReportUpdatesSent;
  momReportUpdatesSentHandles.federate = managerInteractionFederateFederate;
  momReportUpdatesSentHandles.transportationType = managerFederateReportUpdatesSentTransportationType;
  momReportUpdatesSentHandles.updateCounts = managerFederateReportUpdatesSentUpdateCounts;

  // Manager.Federate.Report.ReportReflectionsReceived
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportReflectionsReceived";
  managerFederateReportReflectionsReceived = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAtransportation";
  supportingServices.getParameterHandle(ws, managerFederateReportReflectionsReceived, managerFederateReportReflectionsReceivedTransportationType, foundItem, foundClass);
  ws = L"HLAreflectCounts";
  supportingServices.getParameterHandle(ws, managerFederateReportReflectionsReceived, managerFederateReportReflectionsReceivedReflectCounts, foundItem, foundClass);
  momReportReflectionsReceivedHandles.momClassId = managerFederateReportReflectionsReceived;
  momReportReflectionsReceivedHandles.federate = managerInteractionFederateFederate;
  momReportReflectionsReceivedHandles.transportationType = managerFederateReportReflectionsReceivedTransportationType;
  momReportReflectionsReceivedHandles.reflectCounts = managerFederateReportReflectionsReceivedReflectCounts;

  // Manager.Federate.Report.ReportInteractionsSent
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportInteractionsSent";
  managerFederateReportInteractionsSent = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAtransportation";
  supportingServices.getParameterHandle(ws, managerFederateReportInteractionsSent, managerFederateReportInteractionsSentTransportationType, foundItem, foundClass);
  ws = L"HLAinteractionCounts";
  supportingServices.getParameterHandle(ws, managerFederateReportInteractionsSent, managerFederateReportInteractionsSentInteractionCounts, foundItem, foundClass);
  momReportInteractionsSentHandles.momClassId = managerFederateReportInteractionsSent;
  momReportInteractionsSentHandles.federate = managerInteractionFederateFederate;
  momReportInteractionsSentHandles.transportationType = managerFederateReportInteractionsSentTransportationType;
  momReportInteractionsSentHandles.interactionCounts = managerFederateReportInteractionsSentInteractionCounts;

  // Manager.Federate.Report.ReportInteractionsReceived
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportInteractionsReceived";
  managerFederateReportInteractionsReceived = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAtransportation";
  supportingServices.getParameterHandle(ws, managerFederateReportInteractionsReceived, managerFederateReportInteractionsReceivedTransportationType, foundItem, foundClass);
  ws = L"HLAinteractionCounts";
  supportingServices.getParameterHandle(ws, managerFederateReportInteractionsReceived, managerFederateReportInteractionsReceivedInteractionCounts, foundItem, foundClass);
  momReportInteractionsReceivedHandles.momClassId = managerFederateReportInteractionsReceived;
  momReportInteractionsReceivedHandles.federate = managerInteractionFederateFederate;
  momReportInteractionsReceivedHandles.transportationType = managerFederateReportInteractionsReceivedTransportationType;
  momReportInteractionsReceivedHandles.interactionCounts = managerFederateReportInteractionsReceivedInteractionCounts;

  // Manager.Federate.Report.ReportObjectInformation
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportObjectInstanceInformation";
  managerFederateReportObjectInstanceInformation = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAobjectInstance";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectInstanceInformation, managerFederateReportObjectInformationObjectInstance, foundItem, foundClass);
  ws = L"HLAownedInstanceAttributeList";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectInstanceInformation, managerFederateReportObjectInformationOwnedAttributeList, foundItem, foundClass);
  ws = L"HLAregisteredClass";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectInstanceInformation, managerFederateReportObjectInformationRegisteredClass, foundItem, foundClass);
  ws = L"HLAknownClass";
  supportingServices.getParameterHandle(ws, managerFederateReportObjectInstanceInformation, managerFederateReportObjectInformationKnownClass, foundItem, foundClass);
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
  supportingServices.getParameterHandle(ws, managerFederateReportException, managerFederateReportAlertAlertSeverity, foundItem, foundClass);
  ws = L"HLAexception";
  supportingServices.getParameterHandle(ws, managerFederateReportException, managerFederateReportAlertAlertDescription, foundItem, foundClass);
  momAlertHandles.momClassId = managerFederateReportException;
  momAlertHandles.federate = managerInteractionFederateFederate;
  momAlertHandles.alertSeverity = managerFederateReportAlertAlertSeverity;
  momAlertHandles.alertDescription = managerFederateReportAlertAlertDescription;

  // Manager.Federate.Report.ReportServiceInvocation
  ws = L"HLAmanager.HLAfederate.HLAreport.HLAreportServiceInvocation";
  managerFederateReportServiceInvocation = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAservice";
  supportingServices.getParameterHandle(ws, managerFederateReportServiceInvocation, managerFederateReportServiceInvocationService, foundItem, foundClass);
  ws = L"HLAsuccessIndicator";
  supportingServices.getParameterHandle(ws, managerFederateReportServiceInvocation, managerFederateReportServiceInvocationSuccessIndicator, foundItem, foundClass);
  ws = L"HLAsuppliedArguments";
  supportingServices.getParameterHandle(ws, managerFederateReportServiceInvocation, managerFederateReportServiceInvocationSuppliedArguments, foundItem, foundClass);
  ws = L"HLAreturnedArguments";
  supportingServices.getParameterHandle(ws, managerFederateReportServiceInvocation, managerFederateReportServiceInvocationReturnedArguments, foundItem, foundClass);
  ws = L"HLAexception";
  supportingServices.getParameterHandle(ws, managerFederateReportServiceInvocation, managerFederateReportServiceInvocationExceptionDescription, foundItem, foundClass);
  ws = L"HLAserialNumber";
  supportingServices.getParameterHandle(ws, managerFederateReportServiceInvocation, managerFederateReportServiceInvocationSerialNumber, foundItem, foundClass);
  momReportServiceInvocationHandles.momClassId = managerFederateReportServiceInvocation;
  momReportServiceInvocationHandles.federate = managerInteractionFederateFederate;
  momReportServiceInvocationHandles.service = managerFederateReportServiceInvocationService;
  momReportServiceInvocationHandles.initiator = managerFederateReportServiceInvocationInitiator;
  momReportServiceInvocationHandles.successIndicator = managerFederateReportServiceInvocationSuccessIndicator;
  momReportServiceInvocationHandles.suppliedArguments = managerFederateReportServiceInvocationSuppliedArguments;
  momReportServiceInvocationHandles.returnedArguments = managerFederateReportServiceInvocationReturnedArguments;
  momReportServiceInvocationHandles.exceptionDescription = managerFederateReportServiceInvocationExceptionDescription;
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
  momClasses.insert(managerFederateServiceResignFederationExecution);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceResignFederationExecution, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAsynchronizationPointAchieved";
  managerFederateServiceSynchronizationPointAchieved = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAlabel";
  supportingServices.getParameterHandle(ws, managerFederateServiceSynchronizationPointAchieved, managerFederateServiceSynchronizationPointAchievedLabel, foundItem, foundClass);
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
  momClasses.insert(managerFederateServiceFederateSaveComplete);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceFederateSaveComplete, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAfederateRestoreComplete";
  managerFederateServiceFederateRestoreComplete = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAsuccessIndicator";
  supportingServices.getParameterHandle(ws, managerFederateServiceFederateRestoreComplete, managerFederateServiceFederateRestoreCompleteSuccessIndicator, foundItem, foundClass);
  momClasses.insert(managerFederateServiceFederateRestoreComplete);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceFederateRestoreComplete, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLApublishObjectClassAttributes";
  managerFederateServicePublishObjectClassAttributes = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAobjectClass";
  supportingServices.getParameterHandle(ws, managerFederateServicePublishObjectClassAttributes, managerFederateServicePublishObjectClassObjectClass, foundItem, foundClass);
  ws = L"HLAattributeList";
  supportingServices.getParameterHandle(ws, managerFederateServicePublishObjectClassAttributes, managerFederateServicePublishObjectClassAttributeList, foundItem, foundClass);
  momClasses.insert(managerFederateServicePublishObjectClassAttributes);
  declarationManagement.subscribeInteractionClass(1, managerFederateServicePublishObjectClassAttributes, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAunpublishObjectClassAttributes";
  managerFederateServiceUnpublishObjectClassAttributes = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAobjectClass";
  supportingServices.getParameterHandle(ws, managerFederateServiceUnpublishObjectClassAttributes, managerFederateServiceUnpublishObjectClassObjectClass, foundItem, foundClass);
  momClasses.insert(managerFederateServiceUnpublishObjectClassAttributes);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceUnpublishObjectClassAttributes, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLApublishInteractionClass";
  managerFederateServicePublishInteractionClass = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAinteractionClass";
  supportingServices.getParameterHandle(ws, managerFederateServicePublishInteractionClass, managerFederateServicePublishInteractionClassInteractionClass, foundItem, foundClass);
  momClasses.insert(managerFederateServicePublishInteractionClass);
  declarationManagement.subscribeInteractionClass(1, managerFederateServicePublishInteractionClass, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAunpublishInteractionClass";
  managerFederateServiceUnpublishInteractionClass = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAinteractionClass";
  supportingServices.getParameterHandle(ws, managerFederateServiceUnpublishInteractionClass, managerFederateServiceUnpublishInteractionClassInteractionClass, foundItem, foundClass);
  momClasses.insert(managerFederateServiceUnpublishInteractionClass);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceUnpublishInteractionClass, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAsubscribeObjectClassAttributes";
  managerFederateServiceSubscribeObjectClassAttributes = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAobjectClass";
  supportingServices.getParameterHandle(ws, managerFederateServiceSubscribeObjectClassAttributes, managerFederateServiceSubscribeObjectClassAttributesObjectClass, foundItem, foundClass);
  ws = L"HLAattributeList";
  supportingServices.getParameterHandle(ws, managerFederateServiceSubscribeObjectClassAttributes, managerFederateServiceSubscribeObjectClassAttributesAttributeList, foundItem, foundClass);
  ws = L"HLAactive";
  supportingServices.getParameterHandle(ws, managerFederateServiceSubscribeObjectClassAttributes, managerFederateServiceSubscribeObjectClassAttributesActive, foundItem, foundClass);
  momClasses.insert(managerFederateServiceSubscribeObjectClassAttributes);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceSubscribeObjectClassAttributes, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAunsubscribeObjectClassAttributes";
  managerFederateServiceUnsubscribeObjectClass = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAobjectClass";
  supportingServices.getParameterHandle(ws, managerFederateServiceUnsubscribeObjectClass, managerFederateServiceUnsubscribeObjectClassObjectClass, foundItem, foundClass);
  momClasses.insert(managerFederateServiceUnsubscribeObjectClass);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceUnsubscribeObjectClass, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAsubscribeInteractionClass";
  managerFederateServiceSubscribeInteractionClass = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAinteractionClass";
  supportingServices.getParameterHandle(ws, managerFederateServiceSubscribeInteractionClass, managerFederateServiceSubscribeInteractionClassInteractionClass, foundItem, foundClass);
  ws = L"HLAactive";
  supportingServices.getParameterHandle(ws, managerFederateServiceSubscribeInteractionClass, managerFederateServiceSubscribeInteractionClassActive, foundItem, foundClass);
  momClasses.insert(managerFederateServiceSubscribeInteractionClass);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceSubscribeInteractionClass, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAunsubscribeInteractionClass";
  managerFederateServiceUnsubscribeInteractionClass = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAinteractionClass";
  supportingServices.getParameterHandle(ws, managerFederateServiceUnsubscribeInteractionClass, managerFederateServiceUnsubscribeInteractionClassInteractionClass, foundItem, foundClass);
  momClasses.insert(managerFederateServiceUnsubscribeInteractionClass);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceUnsubscribeInteractionClass, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAdeleteObjectInstance";
  managerFederateServiceDeleteObjectInstance = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAobjectInstance";
  supportingServices.getParameterHandle(ws, managerFederateServiceDeleteObjectInstance, managerFederateServiceDeleteObjectInstanceObjectInstance, foundItem, foundClass);
  ws = L"HLAtag";
  supportingServices.getParameterHandle(ws, managerFederateServiceDeleteObjectInstance, managerFederateServiceDeleteObjectInstanceTag, foundItem, foundClass);
  ws = L"HLAtimeStamp";
  supportingServices.getParameterHandle(ws, managerFederateServiceDeleteObjectInstance, managerFederateServiceDeleteObjectInstanceFederationTime, foundItem, foundClass);
  momClasses.insert(managerFederateServiceDeleteObjectInstance);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceDeleteObjectInstance, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAlocalDeleteObjectInstance";
  managerFederateServiceLocalDeleteObjectInstance = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAobjectInstance";
  supportingServices.getParameterHandle(ws, managerFederateServiceLocalDeleteObjectInstance, managerFederateServiceLocalDeleteObjectInstanceObjectInstance, foundItem, foundClass);
  momClasses.insert(managerFederateServiceLocalDeleteObjectInstance);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceLocalDeleteObjectInstance, active, regions);

  // Manager Federate Service ChangeAttributeOrderTypeObjectInstance
  ws = L"HLAmanager.HLAfederate.HLAservice.HLAchangeAttributeTransportationType";
  managerFederateServiceChangeAttributeTransportationType = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateServiceChangeAttributeTransportationType);
  ws = L"HLAobjectInstance";
  supportingServices.getParameterHandle(ws, managerFederateServiceChangeAttributeTransportationType, managerFederateServiceChangeAttributeTransportationTypeObjectInstance, foundItem, foundClass);
  ws = L"HLAattributeList";
  supportingServices.getParameterHandle(ws, managerFederateServiceChangeAttributeTransportationType, managerFederateServiceChangeAttributeTransportationTypeAttributeList, foundItem, foundClass);
  ws = L"HLAtransportation";
  supportingServices.getParameterHandle(ws, managerFederateServiceChangeAttributeTransportationType, managerFederateServiceChangeAttributeTransportationTypeTransportationType, foundItem, foundClass);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceChangeAttributeTransportationType, active, regions);

  // Manager Federate Service ChangeAttributeOrderType
  ws = L"HLAmanager.HLAfederate.HLAservice.HLAchangeAttributeOrderType";
  managerFederateServiceChangeAttributeOrderType = supportingServices.getInteractionClassHandle(ws);
  momClasses.insert(managerFederateServiceChangeAttributeOrderType);
  ws = L"HLAobjectInstance";
  supportingServices.getParameterHandle(ws, managerFederateServiceChangeAttributeOrderType, managerFederateServiceChangeAttributeOrderTypeObjectInstance, foundItem, foundClass);
  ws = L"HLAattributeList";
  supportingServices.getParameterHandle(ws, managerFederateServiceChangeAttributeOrderType, managerFederateServiceChangeAttributeOrderTypeAttributeList, foundItem, foundClass);
  ws = L"HLAsendOrder";
  supportingServices.getParameterHandle(ws, managerFederateServiceChangeAttributeOrderType, managerFederateServiceChangeAttributeOrderTypeOrderingType, foundItem, foundClass);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceChangeAttributeOrderType, active, regions);

  // Change interaction transportation type
  ws = L"HLAmanager.HLAfederate.HLAservice.HLAchangeInteractionTransportationType";
  managerFederateServiceChangeInteractionTransportationType = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAinteractionClass";
  supportingServices.getParameterHandle(ws, managerFederateServiceChangeInteractionTransportationType, managerFederateServiceChangeInteractionTransportationTypeInteractionClass, foundItem, foundClass);
  ws = L"HLAtransportation";
  supportingServices.getParameterHandle(ws, managerFederateServiceChangeInteractionTransportationType, managerFederateServiceChangeInteractionTransportationTypeTransportationType, foundItem, foundClass);
  momClasses.insert(managerFederateServiceChangeInteractionTransportationType);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceChangeInteractionTransportationType, active, regions);

  // Change interaction order type
  ws = L"HLAmanager.HLAfederate.HLAservice.HLAchangeInteractionOrderType";
  managerFederateServiceChangeInteractionOrderType = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAinteractionClass";
  supportingServices.getParameterHandle(ws, managerFederateServiceChangeInteractionOrderType, managerFederateServiceChangeInteractionOrderTypeInteractionClass, foundItem, foundClass);
  ws = L"HLAsendOrder";
  supportingServices.getParameterHandle(ws, managerFederateServiceChangeInteractionOrderType, managerFederateServiceChangeInteractionOrderTypeOrderingType, foundItem, foundClass);
  momClasses.insert(managerFederateServiceChangeInteractionOrderType);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceChangeInteractionOrderType, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAunconditionalAttributeOwnershipDivestiture";
  managerFederateServiceUnconditionalAttributeOwnershipDivestiture = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAobjectInstance";
  supportingServices.getParameterHandle(ws, managerFederateServiceUnconditionalAttributeOwnershipDivestiture, managerFederateServiceUnconditionalAttributeOwnershipDivestitureObjectInstance, foundItem, foundClass);
  ws = L"HLAattributeList";
  supportingServices.getParameterHandle(ws, managerFederateServiceUnconditionalAttributeOwnershipDivestiture, managerFederateServiceUnconditionalAttributeOwnershipDivestitureAttributeList, foundItem, foundClass);
  momClasses.insert(managerFederateServiceUnconditionalAttributeOwnershipDivestiture);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceUnconditionalAttributeOwnershipDivestiture, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAenableTimeRegulation";
  managerFederateServiceEnableTimeRegulation = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAlookahead";
  supportingServices.getParameterHandle(ws, managerFederateServiceEnableTimeRegulation, managerFederateServiceEnableTimeRegulationLookahead, foundItem, foundClass);
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
  momClasses.insert(managerFederateServiceModifyLookahead);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceModifyLookahead, active, regions);

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAtimeAdvanceRequest";
  managerFederateServiceTimeAdvanceRequest = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAtimeStamp";
  supportingServices.getParameterHandle(ws, managerFederateServiceTimeAdvanceRequest, managerFederateServiceTimeAdvanceRequestFederationTime, foundItem, foundClass);
  momClasses.insert(managerFederateServiceTimeAdvanceRequest);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceTimeAdvanceRequest, active, regions);
  momTimeAdvanceRequestHandles.momClassId = managerFederateServiceTimeAdvanceRequest;
  momTimeAdvanceRequestHandles.federate = managerInteractionFederateFederate;
  momTimeAdvanceRequestHandles.federationTime = managerFederateServiceTimeAdvanceRequestFederationTime;

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAtimeAdvanceRequestAvailable";
  managerFederateServiceTimeAdvanceRequestAvailable = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAtimeStamp";
  supportingServices.getParameterHandle(ws, managerFederateServiceTimeAdvanceRequestAvailable, managerFederateServiceTimeAdvanceRequestAvailableFederationTime, foundItem, foundClass);
  momClasses.insert(managerFederateServiceTimeAdvanceRequestAvailable);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceTimeAdvanceRequestAvailable, active, regions);
  momTimeAdvanceRequestAvailableHandles.momClassId = managerFederateServiceTimeAdvanceRequestAvailable;
  momTimeAdvanceRequestAvailableHandles.federate = managerInteractionFederateFederate;
  momTimeAdvanceRequestAvailableHandles.federationTime = managerFederateServiceTimeAdvanceRequestAvailableFederationTime;

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAnextMessageRequest";
  managerFederateServiceNextMessageRequest = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAtimeStamp";
  supportingServices.getParameterHandle(ws, managerFederateServiceNextMessageRequest, managerFederateServiceNextMessageRequestFederationTime, foundItem, foundClass);
  momClasses.insert(managerFederateServiceNextMessageRequest);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceNextMessageRequest, active, regions);
  momNextMessageRequestHandles.momClassId = managerFederateServiceNextMessageRequest;
  momNextMessageRequestHandles.federate = managerInteractionFederateFederate;
  momNextMessageRequestHandles.federationTime = managerFederateServiceNextMessageRequestFederationTime;

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAnextMessageRequestAvailable";
  managerFederateServiceNextMessageRequestAvailable = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAtimeStamp";
  supportingServices.getParameterHandle(ws, managerFederateServiceNextMessageRequestAvailable, managerFederateServiceNextMessageRequestAvailableFederationTime, foundItem, foundClass);
  momClasses.insert(managerFederateServiceNextMessageRequestAvailable);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceNextMessageRequestAvailable, active, regions);
  momNextMessageRequestAvailableHandles.momClassId = managerFederateServiceNextMessageRequestAvailable;
  momNextMessageRequestAvailableHandles.federate = managerInteractionFederateFederate;
  momNextMessageRequestAvailableHandles.federationTime = managerFederateServiceNextMessageRequestAvailableFederationTime;

  ws = L"HLAmanager.HLAfederate.HLAservice.HLAflushQueueRequest";
  managerFederateServiceFlushQueueRequest = supportingServices.getInteractionClassHandle(ws);
  ws = L"HLAtimeStamp";
  supportingServices.getParameterHandle(ws, managerFederateServiceFlushQueueRequest, managerFederateServiceFlushQueueRequestFederationTime, foundItem, foundClass);
  momClasses.insert(managerFederateServiceFlushQueueRequest);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceFlushQueueRequest, active, regions);
  momFlushQueueRequestHandles.momClassId = managerFederateServiceFlushQueueRequest;
  momFlushQueueRequestHandles.federate = managerInteractionFederateFederate;
  momFlushQueueRequestHandles.federationTime = managerFederateServiceFlushQueueRequestFederationTime;

  ws = L"HLAmanager.HLAfederation.HLAadjust.HLAsetSwitches";
  managerFederationAdjustSetSwitches = supportingServices.getInteractionClassHandle(ws);
#else
  managerObject = supportingServices.findObjectClassHandle(L"manager");
  momClasses.insert(managerObject);

  // Manager.Federate
  managerFederateObjectClass = supportingServices.findObjectClassHandle(L"manager.federate");

  supportingServices.getObjectClassItem(L"federatehandle", managerFederateObjectClass, managerFederateFederateHandle, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateFederateHandle);

  supportingServices.getObjectClassItem(L"FederateType", managerFederateObjectClass, managerFederateFederateType, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateFederateType);

  supportingServices.getObjectClassItem(L"FederateHost", managerFederateObjectClass, managerFederateFederateHost, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateFederateHost);

  supportingServices.getObjectClassItem(L"RTIversion", managerFederateObjectClass, managerFederateRTIversion, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateRTIversion);

  supportingServices.getObjectClassItem(L"FEDid", managerFederateObjectClass, managerFederateFEDid, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateFEDid);

  supportingServices.getObjectClassItem(L"TimeConstrained", managerFederateObjectClass, managerFederateTimeConstrained, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateTimeConstrained);

  supportingServices.getObjectClassItem(L"TimeRegulating", managerFederateObjectClass, managerFederateTimeRegulating, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateTimeRegulating);

  supportingServices.getObjectClassItem(L"AsynchronousDelivery", managerFederateObjectClass, managerFederateAsynchronousDelivery, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateAsynchronousDelivery);

  supportingServices.getObjectClassItem(L"FederateState", managerFederateObjectClass, managerFederateFederateState, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateFederateState);

  supportingServices.getObjectClassItem(L"TimeManagerState", managerFederateObjectClass, managerFederateTimeManagerState, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateTimeManagerState);

  supportingServices.getObjectClassItem(L"FederateTime", managerFederateObjectClass, managerFederateFederateTime, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateFederateTime);

  supportingServices.getObjectClassItem(L"Lookahead", managerFederateObjectClass, managerFederateLookahead, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateLookahead);

  supportingServices.getObjectClassItem(L"LBTS", managerFederateObjectClass, managerFederateLBTS, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateLBTS);

  supportingServices.getObjectClassItem(L"MinNextEventTime", managerFederateObjectClass, managerFederateMinNextEventTime, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateMinNextEventTime);

  supportingServices.getObjectClassItem(L"ROlength", managerFederateObjectClass, managerFederateROlength, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateROlength);

  supportingServices.getObjectClassItem(L"TSOlength", managerFederateObjectClass, managerFederateTSOlength, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateTSOlength);

  supportingServices.getObjectClassItem(L"ReflectionsReceived", managerFederateObjectClass, managerFederateReflectionsReceived, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateReflectionsReceived);

  supportingServices.getObjectClassItem(L"UpdatesSent", managerFederateObjectClass, managerFederateUpdatesSent, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateUpdatesSent);

  supportingServices.getObjectClassItem(L"InteractionsReceived", managerFederateObjectClass, managerFederateInteractionsReceived, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateInteractionsReceived);

  supportingServices.getObjectClassItem(L"InteractionsSent", managerFederateObjectClass, managerFederateInteractionsSent, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateInteractionsSent);

  supportingServices.getObjectClassItem(L"ObjectsOwned", managerFederateObjectClass, managerFederateObjectsOwned, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateObjectsOwned);

  supportingServices.getObjectClassItem(L"ObjectsUpdated", managerFederateObjectClass, managerFederateObjectsUpdated, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateObjectsUpdated);

  supportingServices.getObjectClassItem(L"ObjectsReflected", managerFederateObjectClass, managerFederateObjectsReflected, foundItem, foundClass);
  managerFederateAttributes.insert(managerFederateObjectsReflected);

  declarationManagement.publishObjectClass(1, managerFederateObjectClass, managerFederateAttributes);

  // Manager.Federation
  managerFederationClass = supportingServices.findObjectClassHandle(L"manager.federation");
  momClasses.insert(managerFederationClass);

  supportingServices.getObjectClassItem(L"FederationName", managerFederationClass, managerFederationFederationName, foundItem, foundClass);
  managerFederationAttributes.insert(managerFederationFederationName);

  supportingServices.getObjectClassItem(L"FederatesInFederation", managerFederationClass, managerFederationFederatesInFederation, foundItem, foundClass);
  managerFederationAttributes.insert(managerFederationFederatesInFederation);

  supportingServices.getObjectClassItem(L"RTIversion", managerFederationClass, managerFederationRTIversion, foundItem, foundClass);
  managerFederationAttributes.insert(managerFederationRTIversion);

  supportingServices.getObjectClassItem(L"FEDid", managerFederationClass, managerFederationFEDid, foundItem, foundClass);
  managerFederationAttributes.insert(managerFederationFEDid);

  supportingServices.getObjectClassItem(L"LastSaveName", managerFederationClass, managerFederationLastSaveName, foundItem, foundClass);
  managerFederationAttributes.insert(managerFederationLastSaveName);

  supportingServices.getObjectClassItem(L"LastSaveTime", managerFederationClass, managerFederationLastSaveTime, foundItem, foundClass);
  managerFederationAttributes.insert(managerFederationLastSaveTime);

  supportingServices.getObjectClassItem(L"NextSaveName", managerFederationClass, managerFederationNextSaveName, foundItem, foundClass);
  managerFederationAttributes.insert(managerFederationNextSaveName);

  supportingServices.getObjectClassItem(L"NextSaveTime", managerFederationClass, managerFederationNextSaveTime, foundItem, foundClass);
  managerFederationAttributes.insert(managerFederationNextSaveTime);

  declarationManagement.publishObjectClass(1, managerFederationClass, managerFederationAttributes);

  managerFederation = objectManagement.registerObjectInstance(1, managerFederationClass);

    // MOM Interactions
  managerInteractionRoot = supportingServices.getInteractionClassHandle(L"Manager");
  momClasses.insert(managerInteractionRoot);

  managerInteractionFederate = supportingServices.getInteractionClassHandle(L"Manager.Federate");
  momClasses.insert(managerInteractionFederate);

  supportingServices.getParameterHandle(L"federate", managerInteractionFederate, managerInteractionFederateFederate, foundItem, foundClass);

  // Adjust
  // Manager.Federate.Adjust.SetTiming
  managerFederateAdjustSetTiming = supportingServices.getInteractionClassHandle(L"Manager.Federate.Adjust.SetTiming");
  momClasses.insert(managerFederateAdjustSetTiming);
  declarationManagement.subscribeInteractionClass(1, managerFederateAdjustSetTiming, active, regions);
  supportingServices.getParameterHandle(L"ReportPeriod", managerFederateAdjustSetTiming, managerFederateAdjustSetTimingReportPeriod, foundItem, foundClass);

  // Manager.Federate.Adjust.ModifyAttributeState
  managerFederateAdjustModifyAttributeState = supportingServices.getInteractionClassHandle(L"Manager.Federate.Adjust.ModifyAttributeState");
  momClasses.insert(managerFederateAdjustModifyAttributeState);
  declarationManagement.subscribeInteractionClass(1, managerFederateAdjustModifyAttributeState, active, regions);
  supportingServices.getParameterHandle(L"objectinstance", managerFederateAdjustModifyAttributeState, managerFederateAdjustModifyAttributeStateObjectInstance, foundItem, foundClass);
  supportingServices.getParameterHandle(L"attribute", managerFederateAdjustModifyAttributeState, managerFederateAdjustModifyAttributeStateAttribute, foundItem, foundClass);
  supportingServices.getParameterHandle(L"attributestate", managerFederateAdjustModifyAttributeState, managerFederateAdjustModifyAttributeStateAttributeState, foundItem, foundClass);

  // Manager.Federate.Adjust.SetServiceReporting
  managerFederateAdjustSetServiceReporting = supportingServices.getInteractionClassHandle(L"Manager.Federate.Adjust.SetServiceReporting");
  momClasses.insert(managerFederateAdjustSetServiceReporting);
  declarationManagement.subscribeInteractionClass(1, managerFederateAdjustSetServiceReporting, active, regions);
  supportingServices.getParameterHandle(L"ReportingState", managerFederateAdjustSetServiceReporting, managerFederateAdjustSetServiceReportingState, foundItem, foundClass);

  // Manager.Federate.Adjust.SetExceptionLogging
  managerFederateAdjustSetExceptionLogging = supportingServices.getInteractionClassHandle(L"Manager.Federate.Adjust.SetExceptionLogging");
  momClasses.insert(managerFederateAdjustSetExceptionLogging);
  declarationManagement.subscribeInteractionClass(1, managerFederateAdjustSetExceptionLogging, active, regions);
  supportingServices.getParameterHandle(L"LoggingState", managerFederateAdjustSetExceptionLogging, managerFederateAdjustSetExceptionLoggingState, foundItem, foundClass);

  // Request
  managerFederateRequestPublications = supportingServices.getInteractionClassHandle(L"Manager.Federate.Request.RequestPublications");
  momClasses.insert(managerFederateRequestPublications);
  declarationManagement.subscribeInteractionClass(1, managerFederateRequestPublications, active, regions);

  managerFederateRequestSubscriptions = supportingServices.getInteractionClassHandle(L"Manager.Federate.Request.RequestSubscriptions");
  momClasses.insert(managerFederateRequestSubscriptions);
  declarationManagement.subscribeInteractionClass(1, managerFederateRequestSubscriptions, active, regions);

  managerFederateRequestObjectsOwned = supportingServices.getInteractionClassHandle(L"Manager.Federate.Request.RequestObjectsOwned");
  momClasses.insert(managerFederateRequestObjectsOwned);
  declarationManagement.subscribeInteractionClass(1, managerFederateRequestObjectsOwned, active, regions);

  managerFederateRequestObjectsUpdated = supportingServices.getInteractionClassHandle(L"Manager.Federate.Request.RequestObjectsUpdated");
  momClasses.insert(managerFederateRequestObjectsUpdated);
  declarationManagement.subscribeInteractionClass(1, managerFederateRequestObjectsUpdated, active, regions);

  managerFederateRequestObjectsReflected = supportingServices.getInteractionClassHandle(L"Manager.Federate.Request.RequestObjectsReflected");
  momClasses.insert(managerFederateRequestObjectsReflected);
  declarationManagement.subscribeInteractionClass(1, managerFederateRequestObjectsReflected, active, regions);

  managerFederateRequestUpdatesSent = supportingServices.getInteractionClassHandle(L"Manager.Federate.Request.RequestUpdatesSent");
  momClasses.insert(managerFederateRequestUpdatesSent);
  declarationManagement.subscribeInteractionClass(1, managerFederateRequestUpdatesSent, active, regions);

  managerFederateRequestInteractionsSent = supportingServices.getInteractionClassHandle(L"Manager.Federate.Request.RequestInteractionsSent");
  momClasses.insert(managerFederateRequestInteractionsSent);
  declarationManagement.subscribeInteractionClass(1, managerFederateRequestInteractionsSent, active, regions);

  managerFederateRequestReflectionsReceived = supportingServices.getInteractionClassHandle(L"Manager.Federate.Request.RequestReflectionsReceived");
  momClasses.insert(managerFederateRequestReflectionsReceived);
  declarationManagement.subscribeInteractionClass(1, managerFederateRequestReflectionsReceived, active, regions);

  managerFederateRequestInteractionsReceived = supportingServices.getInteractionClassHandle(L"Manager.Federate.Request.RequestInteractionsReceived");
  momClasses.insert(managerFederateRequestInteractionsReceived);
  declarationManagement.subscribeInteractionClass(1, managerFederateRequestInteractionsReceived, active, regions);

  managerFederateRequestObjectInformation = supportingServices.getInteractionClassHandle(L"Manager.Federate.Request.RequestObjectInformation");
  momClasses.insert(managerFederateRequestObjectInformation);
  supportingServices.getParameterHandle(L"ObjectInstance", managerFederateRequestObjectInformation, managerFederateRequestObjectInformationObjectInstance, foundItem, foundClass);
  declarationManagement.subscribeInteractionClass(1, managerFederateRequestObjectInformation, active, regions);

  // Report
  // Manager.Federate.Report.ReportObjectPublication
  managerFederateReportObjectPublication = supportingServices.getInteractionClassHandle(L"Manager.Federate.Report.ReportObjectPublication");
  momClasses.insert(managerFederateRequestInteractionsReceived);
  supportingServices.getParameterHandle(L"NumberOfClasses", managerFederateReportObjectPublication, managerFederateReportObjectPublicationNumberOfClasses, foundItem, foundClass);
  supportingServices.getParameterHandle(L"ObjectClass", managerFederateReportObjectPublication, managerFederateReportObjectPublicationObjectClass, foundItem, foundClass);
  supportingServices.getParameterHandle(L"AttributeList", managerFederateReportObjectPublication, managerFederateReportObjectPublicationAttributeList, foundItem, foundClass);
  momReportObjectPublicationHandles.momClassId = managerFederateReportObjectPublication;
  momReportObjectPublicationHandles.federate = managerInteractionFederateFederate;
  momReportObjectPublicationHandles.numberOfClasses = managerFederateReportObjectPublicationNumberOfClasses;
  momReportObjectPublicationHandles.objectClass = managerFederateReportObjectPublicationObjectClass;
  momReportObjectPublicationHandles.attributeList = managerFederateReportObjectPublicationAttributeList;

  // Manager.Federate.Report.ReportInteractionPublication
  managerFederateReportInteractionPublication = supportingServices.getInteractionClassHandle(L"Manager.Federate.Report.ReportInteractionPublication");
  supportingServices.getParameterHandle(L"InteractionClassList", managerFederateReportInteractionPublication, managerFederateReportInteractionPublicationInteractionClassList, foundItem, foundClass);
  momReportInteractionPublicationHandles.momClassId = managerFederateReportInteractionPublication;
  momReportInteractionPublicationHandles.federate = managerInteractionFederateFederate;
  momReportInteractionPublicationHandles.interactionClassList = managerFederateReportInteractionPublicationInteractionClassList;

  // Manager.Federate.Report.ReportObjectSubscription
  managerFederateReportObjectSubscription = supportingServices.getInteractionClassHandle(L"Manager.Federate.Report.ReportObjectSubscription");
  supportingServices.getParameterHandle(L"NumberOfClasses", managerFederateReportObjectSubscription, managerFederateReportObjectSubscriptionNumberOfClasses, foundItem, foundClass);
  supportingServices.getParameterHandle(L"ObjectClass", managerFederateReportObjectSubscription, managerFederateReportObjectSubscriptionObjectClass, foundItem, foundClass);
  supportingServices.getParameterHandle(L"AttributeList", managerFederateReportObjectSubscription, managerFederateReportObjectSubscriptionAttributeList, foundItem, foundClass);
  supportingServices.getParameterHandle(L"Active", managerFederateReportObjectSubscription, managerFederateReportObjectSubscriptionActive, foundItem, foundClass);
  momReportObjectSubscriptionHandles.momClassId = managerFederateReportObjectSubscription;
  momReportObjectSubscriptionHandles.federate = managerInteractionFederateFederate;
  momReportObjectSubscriptionHandles.numberOfClasses = managerFederateReportObjectSubscriptionNumberOfClasses;
  momReportObjectSubscriptionHandles.objectClass = managerFederateReportObjectSubscriptionObjectClass;
  momReportObjectSubscriptionHandles.attributeList = managerFederateReportObjectSubscriptionAttributeList;
  momReportObjectSubscriptionHandles.active = managerFederateReportObjectSubscriptionActive;

  // Manager.Federate.Report.ReportInteractionSubscription
  managerFederateReportInteractionSubscription = supportingServices.getInteractionClassHandle(L"Manager.Federate.Report.ReportInteractionSubscription");
  supportingServices.getParameterHandle(L"InteractionClassList", managerFederateReportInteractionSubscription, managerFederateReportInteractionSubscriptionInteractionClassList, foundItem, foundClass);
  momReportInteractionSubscriptionHandles.momClassId = managerFederateReportInteractionSubscription;
  momReportInteractionSubscriptionHandles.federate = managerInteractionFederateFederate;
  momReportInteractionSubscriptionHandles.interactionClassList = managerFederateReportInteractionSubscriptionInteractionClassList;

  // Manager.Federate.Report.ReportObjectsOwned
  managerFederateReportObjectsOwned = supportingServices.getInteractionClassHandle(L"Manager.Federate.Report.ReportObjectsOwned");
  supportingServices.getParameterHandle(L"ObjectCounts", managerFederateReportObjectsOwned, managerFederateReportObjectsOwnedObjectCounts, foundItem, foundClass);
  momReportObjectsOwnedHandles.momClassId = managerFederateReportObjectsOwned;
  momReportObjectsOwnedHandles.federate = managerInteractionFederateFederate;
  momReportObjectsOwnedHandles.objectCounts = managerFederateReportObjectsOwnedObjectCounts;

  // Manager.Federate.Report.ReportObjectsUpdated
  managerFederateReportObjectsUpdated = supportingServices.getInteractionClassHandle(L"Manager.Federate.Report.ReportObjectsUpdated");
  supportingServices.getParameterHandle(L"ObjectCounts", managerFederateReportObjectsUpdated, managerFederateReportObjectsUpdatedObjectCounts, foundItem, foundClass);
  momReportObjectsUpdatedHandles.momClassId = managerFederateReportObjectsUpdated;
  momReportObjectsUpdatedHandles.federate = managerInteractionFederateFederate;
  momReportObjectsUpdatedHandles.objectCounts = managerFederateReportObjectsUpdatedObjectCounts;

  // Manager.Federate.Report.ReportObjectsReflected
  managerFederateReportObjectsReflected = supportingServices.getInteractionClassHandle(L"Manager.Federate.Report.ReportObjectsReflected");
  supportingServices.getParameterHandle(L"ObjectCounts", managerFederateReportObjectsReflected, managerFederateReportObjectsReflectedObjectCounts, foundItem, foundClass);
  momReportObjectsReflectedHandles.momClassId = managerFederateReportObjectsReflected;
  momReportObjectsReflectedHandles.federate = managerInteractionFederateFederate;
  momReportObjectsReflectedHandles.objectCounts = managerFederateReportObjectsReflectedObjectCounts;

  // Manager.Federate.Report.ReportUpdatesSent
  managerFederateReportUpdatesSent = supportingServices.getInteractionClassHandle(L"Manager.Federate.Report.ReportUpdatesSent");
  supportingServices.getParameterHandle(L"TransportationType", managerFederateReportUpdatesSent, managerFederateReportUpdatesSentTransportationType, foundItem, foundClass);
  supportingServices.getParameterHandle(L"UpdateCounts", managerFederateReportUpdatesSent, managerFederateReportUpdatesSentUpdateCounts, foundItem, foundClass);
  momReportUpdatesSentHandles.momClassId = managerFederateReportUpdatesSent;
  momReportUpdatesSentHandles.federate = managerInteractionFederateFederate;
  momReportUpdatesSentHandles.transportationType = managerFederateReportUpdatesSentTransportationType;
  momReportUpdatesSentHandles.updateCounts = managerFederateReportUpdatesSentUpdateCounts;

  // Manager.Federate.Report.ReportReflectionsReceived
  managerFederateReportReflectionsReceived = supportingServices.getInteractionClassHandle(L"Manager.Federate.Report.ReportReflectionsReceived");
  supportingServices.getParameterHandle(L"TransportationType", managerFederateReportReflectionsReceived, managerFederateReportReflectionsReceivedTransportationType, foundItem, foundClass);
  supportingServices.getParameterHandle(L"ReflectCounts", managerFederateReportReflectionsReceived, managerFederateReportReflectionsReceivedReflectCounts, foundItem, foundClass);
  momReportReflectionsReceivedHandles.momClassId = managerFederateReportReflectionsReceived;
  momReportReflectionsReceivedHandles.federate = managerInteractionFederateFederate;
  momReportReflectionsReceivedHandles.transportationType = managerFederateReportReflectionsReceivedTransportationType;
  momReportReflectionsReceivedHandles.reflectCounts = managerFederateReportReflectionsReceivedReflectCounts;

  // Manager.Federate.Report.ReportInteractionsSent
  managerFederateReportInteractionsSent = supportingServices.getInteractionClassHandle(L"Manager.Federate.Report.ReportInteractionsSent");
  supportingServices.getParameterHandle(L"TransportationType", managerFederateReportInteractionsSent, managerFederateReportInteractionsSentTransportationType, foundItem, foundClass);
  supportingServices.getParameterHandle(L"InteractionCounts", managerFederateReportInteractionsSent, managerFederateReportInteractionsSentInteractionCounts, foundItem, foundClass);
  momReportInteractionsSentHandles.momClassId = managerFederateReportInteractionsSent;
  momReportInteractionsSentHandles.federate = managerInteractionFederateFederate;
  momReportInteractionsSentHandles.transportationType = managerFederateReportInteractionsSentTransportationType;
  momReportInteractionsSentHandles.interactionCounts = managerFederateReportInteractionsSentInteractionCounts;

  // Manager.Federate.Report.ReportInteractionsReceived
  managerFederateReportInteractionsReceived = supportingServices.getInteractionClassHandle(L"Manager.Federate.Report.ReportInteractionsReceived");
  supportingServices.getParameterHandle(L"TransportationType", managerFederateReportInteractionsReceived, managerFederateReportInteractionsReceivedTransportationType, foundItem, foundClass);
  supportingServices.getParameterHandle(L"InteractionCounts", managerFederateReportInteractionsReceived, managerFederateReportInteractionsReceivedInteractionCounts, foundItem, foundClass);
  momReportInteractionsReceivedHandles.momClassId = managerFederateReportInteractionsReceived;
  momReportInteractionsReceivedHandles.federate = managerInteractionFederateFederate;
  momReportInteractionsReceivedHandles.transportationType = managerFederateReportInteractionsReceivedTransportationType;
  momReportInteractionsReceivedHandles.interactionCounts = managerFederateReportInteractionsReceivedInteractionCounts;

  // Manager.Federate.Report.ReportObjectInformation
  managerFederateReportObjectInformation = supportingServices.getInteractionClassHandle(L"Manager.Federate.Report.ReportObjectInformation");
  supportingServices.getParameterHandle(L"ObjectInstance", managerFederateReportObjectInformation, managerFederateReportObjectInformationObjectInstance, foundItem, foundClass);
  supportingServices.getParameterHandle(L"OwnedAttributeList", managerFederateReportObjectInformation, managerFederateReportObjectInformationOwnedAttributeList, foundItem, foundClass);
  supportingServices.getParameterHandle(L"RegisteredClass", managerFederateReportObjectInformation, managerFederateReportObjectInformationRegisteredClass, foundItem, foundClass);
  supportingServices.getParameterHandle(L"KnownClass", managerFederateReportObjectInformation, managerFederateReportObjectInformationKnownClass, foundItem, foundClass);
  momReportObjectInformationHandles.momClassId = managerFederateReportObjectInformation;
  momReportObjectInformationHandles.federate = managerInteractionFederateFederate;
  momReportObjectInformationHandles.objectInstance = managerFederateReportObjectInformationObjectInstance;
  momReportObjectInformationHandles.objectAttributeList = managerFederateReportObjectInformationOwnedAttributeList;
  momReportObjectInformationHandles.registeredClass = managerFederateReportObjectInformationRegisteredClass;
  momReportObjectInformationHandles.knownClass = managerFederateReportObjectInformationKnownClass;

  // Manager.Federate.Report.Alert
  managerFederateReportAlert = supportingServices.getInteractionClassHandle(L"Manager.Federate.Report.Alert");
  supportingServices.getParameterHandle(L"AlertSeverity", managerFederateReportAlert, managerFederateReportAlertAlertSeverity, foundItem, foundClass);
  supportingServices.getParameterHandle(L"AlertDescription", managerFederateReportAlert, managerFederateReportAlertAlertDescription, foundItem, foundClass);
  supportingServices.getParameterHandle(L"AlertID", managerFederateReportAlert, managerFederateReportAlertAlertID, foundItem, foundClass);
  momAlertHandles.momClassId = managerFederateReportAlert;
  momAlertHandles.federate = managerInteractionFederateFederate;
  momAlertHandles.alertSeverity = managerFederateReportAlertAlertSeverity;
  momAlertHandles.alertDescription = managerFederateReportAlertAlertDescription;
  momAlertHandles.alertID = managerFederateReportAlertAlertID;

  // Manager.Federate.Report.ReportServiceInvocation
  managerFederateReportServiceInvocation = supportingServices.getInteractionClassHandle(L"Manager.Federate.Report.ReportServiceInvocation");
  supportingServices.getParameterHandle(L"Service", managerFederateReportServiceInvocation, managerFederateReportServiceInvocationService, foundItem, foundClass);
  supportingServices.getParameterHandle(L"Initiator", managerFederateReportServiceInvocation, managerFederateReportServiceInvocationInitiator, foundItem, foundClass);
  supportingServices.getParameterHandle(L"SuccessIndicator", managerFederateReportServiceInvocation, managerFederateReportServiceInvocationSuccessIndicator, foundItem, foundClass);
  supportingServices.getParameterHandle(L"SuppliedArgument1", managerFederateReportServiceInvocation, managerFederateReportServiceInvocationSuppliedArgument1, foundItem, foundClass);
  supportingServices.getParameterHandle(L"SuppliedArgument2", managerFederateReportServiceInvocation, managerFederateReportServiceInvocationSuppliedArgument2, foundItem, foundClass);
  supportingServices.getParameterHandle(L"SuppliedArgument3", managerFederateReportServiceInvocation, managerFederateReportServiceInvocationSuppliedArgument3, foundItem, foundClass);
  supportingServices.getParameterHandle(L"SuppliedArgument4", managerFederateReportServiceInvocation, managerFederateReportServiceInvocationSuppliedArgument4, foundItem, foundClass);
  supportingServices.getParameterHandle(L"SuppliedArgument5", managerFederateReportServiceInvocation, managerFederateReportServiceInvocationSuppliedArgument5, foundItem, foundClass);
  supportingServices.getParameterHandle(L"ReturnedArgument", managerFederateReportServiceInvocation, managerFederateReportServiceInvocationReturnedArgument, foundItem, foundClass);
  supportingServices.getParameterHandle(L"ExceptionDescription", managerFederateReportServiceInvocation, managerFederateReportServiceInvocationExceptionDescription, foundItem, foundClass);
  supportingServices.getParameterHandle(L"ExceptionID", managerFederateReportServiceInvocation, managerFederateReportServiceInvocationExceptionID, foundItem, foundClass);
  momReportServiceInvocationHandles.momClassId = managerFederateReportServiceInvocation;
  momReportServiceInvocationHandles.federate = managerInteractionFederateFederate;
  momReportServiceInvocationHandles.service = managerFederateReportServiceInvocationService;
  momReportServiceInvocationHandles.initiator = managerFederateReportServiceInvocationInitiator;
  momReportServiceInvocationHandles.successIndicator = managerFederateReportServiceInvocationSuccessIndicator;
  momReportServiceInvocationHandles.suppliedArgument1 = managerFederateReportServiceInvocationSuppliedArgument1;
  momReportServiceInvocationHandles.suppliedArgument2 = managerFederateReportServiceInvocationSuppliedArgument2;
  momReportServiceInvocationHandles.suppliedArgument3 = managerFederateReportServiceInvocationSuppliedArgument3;
  momReportServiceInvocationHandles.suppliedArgument4 = managerFederateReportServiceInvocationSuppliedArgument4;
  momReportServiceInvocationHandles.suppliedArgument5 = managerFederateReportServiceInvocationSuppliedArgument5;
  momReportServiceInvocationHandles.returnedArgument = managerFederateReportServiceInvocationReturnedArgument;
  momReportServiceInvocationHandles.exceptionDescription = managerFederateReportServiceInvocationExceptionDescription;
  momReportServiceInvocationHandles.exceptionID = managerFederateReportServiceInvocationExceptionID;

  // Service
  managerFederateServiceResignFederationExecution = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.ResignFederationExecution");
  supportingServices.getParameterHandle(L"ResignAction", managerFederateServiceResignFederationExecution, managerFederateServiceResignFederationExecutionResignAction, foundItem, foundClass);
  momClasses.insert(managerFederateServiceResignFederationExecution);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceResignFederationExecution, active, regions);

  managerFederateServiceSynchronizationPointAchieved = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.SynchronizationPointAchieved");
  supportingServices.getParameterHandle(L"Label", managerFederateServiceSynchronizationPointAchieved, managerFederateServiceSynchronizationPointAchievedLabel, foundItem, foundClass);
  momClasses.insert(managerFederateServiceSynchronizationPointAchieved);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceSynchronizationPointAchieved, active, regions);

  managerFederateServiceFederateSaveBegun = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.FederateSaveBegun");
  momClasses.insert(managerFederateServiceFederateSaveBegun);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceFederateSaveBegun, active, regions);

  managerFederateServiceFederateSaveComplete = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.FederateSaveComplete");
  supportingServices.getParameterHandle(L"SuccessIndicator", managerFederateServiceFederateSaveComplete, managerFederateServiceFederateSaveCompleteSuccessIndicator, foundItem, foundClass);
  momClasses.insert(managerFederateServiceFederateSaveComplete);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceFederateSaveComplete, active, regions);

  managerFederateServiceFederateRestoreComplete = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.FederateRestoreComplete");
  supportingServices.getParameterHandle(L"SuccessIndicator", managerFederateServiceFederateRestoreComplete, managerFederateServiceFederateRestoreCompleteSuccessIndicator, foundItem, foundClass);
  momClasses.insert(managerFederateServiceFederateRestoreComplete);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceFederateRestoreComplete, active, regions);

  managerFederateServicePublishObjectClass = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.PublishObjectClass");
  supportingServices.getParameterHandle(L"ObjectClass", managerFederateServicePublishObjectClass, managerFederateServicePublishObjectClassObjectClass, foundItem, foundClass);
  supportingServices.getParameterHandle(L"AttributeList", managerFederateServicePublishObjectClass, managerFederateServicePublishObjectClassAttributeList, foundItem, foundClass);
  momClasses.insert(managerFederateServicePublishObjectClass);
  declarationManagement.subscribeInteractionClass(1, managerFederateServicePublishObjectClass, active, regions);

  managerFederateServiceUnpublishObjectClass = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.UnpublishObjectClass");
  supportingServices.getParameterHandle(L"ObjectClass", managerFederateServiceUnpublishObjectClass, managerFederateServiceUnpublishObjectClassObjectClass, foundItem, foundClass);
  momClasses.insert(managerFederateServiceUnpublishObjectClass);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceUnpublishObjectClass, active, regions);

  managerFederateServicePublishInteractionClass = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.PublishInteractionClass");
  supportingServices.getParameterHandle(L"InteractionClass", managerFederateServicePublishInteractionClass, managerFederateServicePublishInteractionClassInteractionClass, foundItem, foundClass);
  momClasses.insert(managerFederateServicePublishInteractionClass);
  declarationManagement.subscribeInteractionClass(1, managerFederateServicePublishInteractionClass, active, regions);

  managerFederateServiceUnpublishInteractionClass = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.UnpublishInteractionClass");
  supportingServices.getParameterHandle(L"InteractionClass", managerFederateServiceUnpublishInteractionClass, managerFederateServiceUnpublishInteractionClassInteractionClass, foundItem, foundClass);
  momClasses.insert(managerFederateServiceUnpublishInteractionClass);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceUnpublishInteractionClass, active, regions);

  managerFederateServiceSubscribeObjectClassAttributes = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.SubscribeObjectClassAttributes");
  supportingServices.getParameterHandle(L"ObjectClass", managerFederateServiceSubscribeObjectClassAttributes, managerFederateServiceSubscribeObjectClassAttributesObjectClass, foundItem, foundClass);
  supportingServices.getParameterHandle(L"AttributeList", managerFederateServiceSubscribeObjectClassAttributes, managerFederateServiceSubscribeObjectClassAttributesAttributeList, foundItem, foundClass);
  supportingServices.getParameterHandle(L"Active", managerFederateServiceSubscribeObjectClassAttributes, managerFederateServiceSubscribeObjectClassAttributesActive, foundItem, foundClass);
  momClasses.insert(managerFederateServiceSubscribeObjectClassAttributes);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceSubscribeObjectClassAttributes, active, regions);

  managerFederateServiceUnsubscribeObjectClass = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.UnsubscribeObjectClass");
  supportingServices.getParameterHandle(L"ObjectClass", managerFederateServiceUnsubscribeObjectClass, managerFederateServiceUnsubscribeObjectClassObjectClass, foundItem, foundClass);
  momClasses.insert(managerFederateServiceUnsubscribeObjectClass);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceUnsubscribeObjectClass, active, regions);

  managerFederateServiceSubscribeInteractionClass = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.SubscribeInteractionClass");
  supportingServices.getParameterHandle(L"InteractionClass", managerFederateServiceSubscribeInteractionClass, managerFederateServiceSubscribeInteractionClassInteractionClass, foundItem, foundClass);
  supportingServices.getParameterHandle(L"Active", managerFederateServiceSubscribeInteractionClass, managerFederateServiceSubscribeInteractionClassActive, foundItem, foundClass);
  momClasses.insert(managerFederateServiceSubscribeInteractionClass);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceSubscribeInteractionClass, active, regions);

  managerFederateServiceUnsubscribeInteractionClass = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.UnsubscribeInteractionClass");
  supportingServices.getParameterHandle(L"InteractionClass", managerFederateServiceUnsubscribeInteractionClass, managerFederateServiceUnsubscribeInteractionClassInteractionClass, foundItem, foundClass);
  momClasses.insert(managerFederateServiceUnsubscribeInteractionClass);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceUnsubscribeInteractionClass, active, regions);

  managerFederateServiceDeleteObjectInstance = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.DeleteObjectInstance");
  supportingServices.getParameterHandle(L"ObjectInstance", managerFederateServiceDeleteObjectInstance, managerFederateServiceDeleteObjectInstanceObjectInstance, foundItem, foundClass);
  supportingServices.getParameterHandle(L"Tag", managerFederateServiceDeleteObjectInstance, managerFederateServiceDeleteObjectInstanceTag, foundItem, foundClass);
  supportingServices.getParameterHandle(L"FederationTime", managerFederateServiceDeleteObjectInstance, managerFederateServiceDeleteObjectInstanceFederationTime, foundItem, foundClass);
  momClasses.insert(managerFederateServiceDeleteObjectInstance);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceDeleteObjectInstance, active, regions);

  managerFederateServiceLocalDeleteObjectInstance = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.LocalDeleteObjectInstance");
  supportingServices.getParameterHandle(L"ObjectInstance", managerFederateServiceLocalDeleteObjectInstance, managerFederateServiceLocalDeleteObjectInstanceObjectInstance, foundItem, foundClass);
  momClasses.insert(managerFederateServiceLocalDeleteObjectInstance);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceLocalDeleteObjectInstance, active, regions);

  // Manager Federate Service ChangeAttributeOrderTypeObjectInstance
  managerFederateServiceChangeAttributeTransportationType = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.ChangeAttributeTransportationType");
  momClasses.insert(managerFederateServiceChangeAttributeTransportationType);

  supportingServices.getParameterHandle(L"objectinstance", managerFederateServiceChangeAttributeTransportationType, managerFederateServiceChangeAttributeTransportationTypeObjectInstance, foundItem, foundClass);
  supportingServices.getParameterHandle(L"attributelist", managerFederateServiceChangeAttributeTransportationType, managerFederateServiceChangeAttributeTransportationTypeAttributeList, foundItem, foundClass);
  supportingServices.getParameterHandle(L"transportationtype", managerFederateServiceChangeAttributeTransportationType, managerFederateServiceChangeAttributeTransportationTypeTransportationType, foundItem, foundClass);

  declarationManagement.subscribeInteractionClass(1, managerFederateServiceChangeAttributeTransportationType, active, regions);

  // Manager Federate Service ChangeAttributeOrderType
  managerFederateServiceChangeAttributeOrderType = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.ChangeAttributeOrderType");
  momClasses.insert(managerFederateServiceChangeAttributeOrderType);

  supportingServices.getParameterHandle(L"objectinstance", managerFederateServiceChangeAttributeOrderType, managerFederateServiceChangeAttributeOrderTypeObjectInstance, foundItem, foundClass);
  supportingServices.getParameterHandle(L"attributelist", managerFederateServiceChangeAttributeOrderType, managerFederateServiceChangeAttributeOrderTypeAttributeList, foundItem, foundClass);
  supportingServices.getParameterHandle(L"orderingtype", managerFederateServiceChangeAttributeOrderType, managerFederateServiceChangeAttributeOrderTypeOrderingType, foundItem, foundClass);

  declarationManagement.subscribeInteractionClass(1, managerFederateServiceChangeAttributeOrderType, active, regions);

  // Change interaction transportation type
  managerFederateServiceChangeInteractionTransportationType = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.ChangeInteractionTransportationType");
  supportingServices.getParameterHandle(L"InteractionClass", managerFederateServiceChangeInteractionTransportationType, managerFederateServiceChangeInteractionTransportationTypeInteractionClass, foundItem, foundClass);
  supportingServices.getParameterHandle(L"TransportationType", managerFederateServiceChangeInteractionTransportationType, managerFederateServiceChangeInteractionTransportationTypeTransportationType, foundItem, foundClass);
  momClasses.insert(managerFederateServiceChangeInteractionTransportationType);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceChangeInteractionTransportationType, active, regions);

  // Change interaction order type
  managerFederateServiceChangeInteractionOrderType = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.ChangeInteractionOrderType");
  supportingServices.getParameterHandle(L"InteractionClass", managerFederateServiceChangeInteractionOrderType, managerFederateServiceChangeInteractionOrderTypeInteractionClass, foundItem, foundClass);
  supportingServices.getParameterHandle(L"OrderingType", managerFederateServiceChangeInteractionOrderType, managerFederateServiceChangeInteractionOrderTypeOrderingType, foundItem, foundClass);
  momClasses.insert(managerFederateServiceChangeInteractionOrderType);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceChangeInteractionOrderType, active, regions);

  managerFederateServiceUnconditionalAttributeOwnershipDivestiture = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.UnconditionalAttributeOwnershipDivestiture");
  supportingServices.getParameterHandle(L"ObjectInstance", managerFederateServiceUnconditionalAttributeOwnershipDivestiture, managerFederateServiceUnconditionalAttributeOwnershipDivestitureObjectInstance, foundItem, foundClass);
  supportingServices.getParameterHandle(L"AttributeList", managerFederateServiceUnconditionalAttributeOwnershipDivestiture, managerFederateServiceUnconditionalAttributeOwnershipDivestitureAttributeList, foundItem, foundClass);
  momClasses.insert(managerFederateServiceUnconditionalAttributeOwnershipDivestiture);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceUnconditionalAttributeOwnershipDivestiture, active, regions);

  managerFederateServiceEnableTimeRegulation = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.EnableTimeRegulation");
  supportingServices.getParameterHandle(L"FederationTime", managerFederateServiceEnableTimeRegulation, managerFederateServiceEnableTimeRegulationFederationTime, foundItem, foundClass);
  supportingServices.getParameterHandle(L"Lookahead", managerFederateServiceEnableTimeRegulation, managerFederateServiceEnableTimeRegulationLookahead, foundItem, foundClass);
  momClasses.insert(managerFederateServiceEnableTimeRegulation);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceEnableTimeRegulation, active, regions);

  managerFederateServiceDisableTimeRegulation = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.DisableTimeRegulation");
  momClasses.insert(managerFederateServiceDisableTimeRegulation);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceDisableTimeRegulation, active, regions);

  managerFederateServiceEnableTimeConstrained = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.EnableTimeConstrained");
  momClasses.insert(managerFederateServiceEnableTimeConstrained);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceEnableTimeConstrained, active, regions);

  managerFederateServiceDisableTimeConstrained = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.DisableTimeConstrained");
  momClasses.insert(managerFederateServiceDisableTimeConstrained);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceDisableTimeConstrained, active, regions);

  managerFederateServiceEnableAsynchronousDelivery = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.EnableAsynchronousDelivery");
  momClasses.insert(managerFederateServiceEnableAsynchronousDelivery);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceEnableAsynchronousDelivery, active, regions);

  managerFederateServiceDisableAsynchronousDelivery = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.DisableAsynchronousDelivery");
  momClasses.insert(managerFederateServiceDisableAsynchronousDelivery);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceDisableAsynchronousDelivery, active, regions);

  managerFederateServiceModifyLookahead = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.ModifyLookahead");
  supportingServices.getParameterHandle(L"Lookahead", managerFederateServiceModifyLookahead, managerFederateServiceModifyLookaheadLookahead, foundItem, foundClass);
  momClasses.insert(managerFederateServiceModifyLookahead);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceModifyLookahead, active, regions);

  managerFederateServiceTimeAdvanceRequest = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.TimeAdvanceRequest");
  supportingServices.getParameterHandle(L"FederationTime", managerFederateServiceTimeAdvanceRequest, managerFederateServiceTimeAdvanceRequestFederationTime, foundItem, foundClass);
  momClasses.insert(managerFederateServiceTimeAdvanceRequest);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceTimeAdvanceRequest, active, regions);
  momTimeAdvanceRequestHandles.momClassId = managerFederateServiceTimeAdvanceRequest;
  momTimeAdvanceRequestHandles.federate = managerInteractionFederateFederate;
  momTimeAdvanceRequestHandles.federationTime = managerFederateServiceTimeAdvanceRequestFederationTime;

  managerFederateServiceTimeAdvanceRequestAvailable = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.TimeAdvanceRequestAvailable");
  supportingServices.getParameterHandle(L"FederationTime", managerFederateServiceTimeAdvanceRequestAvailable, managerFederateServiceTimeAdvanceRequestAvailableFederationTime, foundItem, foundClass);
  momClasses.insert(managerFederateServiceTimeAdvanceRequestAvailable);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceTimeAdvanceRequestAvailable, active, regions);
  momTimeAdvanceRequestAvailableHandles.momClassId = managerFederateServiceTimeAdvanceRequestAvailable;
  momTimeAdvanceRequestAvailableHandles.federate = managerInteractionFederateFederate;
  momTimeAdvanceRequestAvailableHandles.federationTime = managerFederateServiceTimeAdvanceRequestAvailableFederationTime;

  managerFederateServiceNextEventRequest = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.NextEventRequest");
  supportingServices.getParameterHandle(L"FederationTime", managerFederateServiceNextEventRequest, managerFederateServiceNextEventRequestFederationTime, foundItem, foundClass);
  momClasses.insert(managerFederateServiceNextEventRequest);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceNextEventRequest, active, regions);
  momNextEventRequestHandles.momClassId = managerFederateServiceNextEventRequest;
  momNextEventRequestHandles.federate = managerInteractionFederateFederate;
  momNextEventRequestHandles.federationTime = managerFederateServiceNextEventRequestFederationTime;

  managerFederateServiceNextEventRequestAvailable = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.NextEventRequestAvailable");
  supportingServices.getParameterHandle(L"FederationTime", managerFederateServiceNextEventRequestAvailable, managerFederateServiceNextEventRequestAvailableFederationTime, foundItem, foundClass);
  momClasses.insert(managerFederateServiceNextEventRequestAvailable);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceNextEventRequestAvailable, active, regions);
  momNextEventRequestAvailableHandles.momClassId = managerFederateServiceNextEventRequestAvailable;
  momNextEventRequestAvailableHandles.federate = managerInteractionFederateFederate;
  momNextEventRequestAvailableHandles.federationTime = managerFederateServiceNextEventRequestAvailableFederationTime;

  managerFederateServiceFlushQueueRequest = supportingServices.getInteractionClassHandle(L"Manager.Federate.Service.FlushQueueRequest");
  supportingServices.getParameterHandle(L"FederationTime", managerFederateServiceFlushQueueRequest, managerFederateServiceFlushQueueRequestFederationTime, foundItem, foundClass);
  momClasses.insert(managerFederateServiceFlushQueueRequest);
  declarationManagement.subscribeInteractionClass(1, managerFederateServiceFlushQueueRequest, active, regions);
  momFlushQueueRequestHandles.momClassId = managerFederateServiceFlushQueueRequest;
  momFlushQueueRequestHandles.federate = managerInteractionFederateFederate;
  momFlushQueueRequestHandles.federationTime = managerFederateServiceFlushQueueRequestFederationTime;
#endif
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ManagementObjectModel::~ManagementObjectModel(void)
{
  GERTICO::MomFederate *momFederate;
  GERTICO::MomFederateMap::iterator itMomFederateMap;

  for (itMomFederateMap = momFederateMap.begin(); itMomFederateMap != momFederateMap.end(); itMomFederateMap = momFederateMap.begin())
  {
    momFederate = itMomFederateMap->second;
    momFederateMap.erase(itMomFederateMap);
    delete momFederate;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::adjustModifyAttributeState(GeRtiFactory::GeRtiEvent const &theGeRtiEvent)
{
  CORBA::ULong count = 4;
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::RegisteredObject *registeredObject;
  GeRtiFactory::GeRtiHandle attribute;
  GeRtiFactory::GeRtiHandle federate;
  GeRtiFactory::GeRtiHandle objectId = 0;
  std::string attributeState;
  std::wstring object;
  char buff[256];
  char tmp[256];
  bool gotItem[4];
  int fields;
  long l;

  for (i = 0; i < count; i++)
  {
    gotItem[i] = false;
  }

  lengthi = theGeRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theGeRtiEvent.data[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theGeRtiEvent.data[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theGeRtiEvent.data[i].id == managerInteractionFederateFederate)
    {
      l = 0;
      fields = sscanf(buff, "%ld", &l);
      if (fields == 1)
      {
        federate = l;
        gotItem[0] = true;
      }
    }

    if (theGeRtiEvent.data[i].id == managerFederateAdjustModifyAttributeStateObjectInstance)
    {
      GERTICO::Mapper::mapWstringFromChar(object, buff);
      gotItem[1] = true;
    }

    if (theGeRtiEvent.data[i].id == managerFederateAdjustModifyAttributeStateAttribute)
    {
      l = 0;
      fields = sscanf(buff, "%ld", &l);
      if (fields == 1)
      {
        attribute = l;
        gotItem[2] = true;
      }
    }
    if (theGeRtiEvent.data[i].id == managerFederateAdjustModifyAttributeStateAttributeState)
    {
      fields = sscanf(buff, "%s", tmp);
      attributeState = tmp;
      if (fields == 1)
      {
        gotItem[3] = true;
      }
    }
  }

  for (i = 0; i < count; i++)
  {
    if (gotItem[i] == false)
    {
      return;
    }
  }

  registeredObject = objectManagement.getObjectByName(object);
  if (registeredObject)
  {
    objectId = registeredObject->getId();
  }

  ownershipMaster.managerFederateAdjustModifyAttributeState(federate, objectId, attribute, attributeState);
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
  std::string loggingStateStr;
  bool reportingState = false;
  char *cptr;
  long l;

  lengthi = theGeRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theGeRtiEvent.data[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theGeRtiEvent.data[i].value);
      sscanf(cptr, "%ld", &l);
      federate = l;
      delete[] cptr;
    }

    if (theGeRtiEvent.data[i].id == managerFederateAdjustSetServiceReportingState)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theGeRtiEvent.data[i].value);
      loggingStateStr = cptr;
      delete[] cptr;
#ifdef IEEE_1516
      if (strcmp(loggingStateStr.c_str(), "HLAtrue") == 0)
#else
      GERTICO::Mapper::nameToLower(loggingStateStr);
      if (strcmp(loggingStateStr.c_str(), "true") == 0)
#endif
      {
        reportingState = true;
      }
    }
  }

  itMomFederateMap = momFederateMap.find(federate);
  if (itMomFederateMap != momFederateMap.end())
  {
    itMomFederateMap->second->setServiceReporting(reportingState);
  }
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
  char *cptr;
  long l;

  lengthi = theGeRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theGeRtiEvent.data[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theGeRtiEvent.data[i].value);
      sscanf(cptr, "%ld", &l);
      federate = l;
      delete[] cptr;
    }

#ifdef IEEE_1516
    if (theGeRtiEvent.data[i].id == managerFederateAdjustSetExceptionReportingState)
#else
    if (theGeRtiEvent.data[i].id == managerFederateAdjustSetExceptionLoggingState)
#endif
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theGeRtiEvent.data[i].value);
      loggingStateStr = cptr;
      delete[] cptr;
#ifdef IEEE_1516
      if (strcmp(loggingStateStr.c_str(), "HLAtrue") == 0)
#else
      GERTICO::Mapper::nameToLower(loggingStateStr);
      if (strcmp(loggingStateStr.c_str(), "true") == 0)
#endif
      {
        loggingState = true;
      }
    }
  }

  itMomFederateMap = momFederateMap.find(federate);
  if (itMomFederateMap != momFederateMap.end())
  {
    itMomFederateMap->second->setExceptionLogging(loggingState);
  }
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
  char *cptr;
  long l;

  lengthi = theGeRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theGeRtiEvent.data[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theGeRtiEvent.data[i].value);
      sscanf(cptr, "%ld", &l);
      federate = l;
      delete[] cptr;
    }

    if (theGeRtiEvent.data[i].id == managerFederateAdjustSetTimingReportPeriod)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theGeRtiEvent.data[i].value);
      sscanf(cptr, "%ld", &l);
      setTiming = l;
      delete[] cptr;
    }
  }

  itMomFederateMap = momFederateMap.find(federate);
  if (itMomFederateMap != momFederateMap.end())
  {
    itMomFederateMap->second->setTiming(setTiming);
  }
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
  std::wstring objectInstance;
  bool gotError = false;
  char *cptr;
  long l;

  lengthi = theGeRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theGeRtiEvent.data[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theGeRtiEvent.data[i].value);
      sscanf(cptr, "%ld", &l);
      federate = l;
      delete[] cptr;
    }

    if (theGeRtiEvent.data[i].id == managerFederateServiceChangeAttributeOrderTypeObjectInstance)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theGeRtiEvent.data[i].value);
      GERTICO::Mapper::mapWstringFromChar(objectInstance, cptr);
      delete[] cptr;
    }

    if (theGeRtiEvent.data[i].id == managerFederateServiceChangeAttributeOrderTypeAttributeList)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theGeRtiEvent.data[i].value);
      getAttributes(attributes, cptr);
      delete[] cptr;
    }

    if (theGeRtiEvent.data[i].id == managerFederateServiceChangeAttributeOrderTypeOrderingType)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theGeRtiEvent.data[i].value);
      GERTICO::Mapper::getOrderType(orderingType, cptr);
      delete[] cptr;
    }
  }

  registeredObject = objectManagement.getObjectByName(objectInstance);
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

    itMomFederateMap = momFederateMap.find(federate);
    if (itMomFederateMap != momFederateMap.end())
    {
      exceptionLogging = itMomFederateMap->second->checkExceptionLogging();
      if (exceptionLogging)
      {
        sendAlert(federate, alertSeverity, alertDescription);
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModel::changeAttributeTransportationType(const GeRtiFactory::GeRtiEvent &theEvent)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::RegisteredObject *registeredObject;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::GeRtiHandle transportationType;
  GeRtiFactory::Handles attributes;
  std::string alertDescription;
  std::string alertSeverity;
  std::wstring objectInstance;
  bool gotError = false;
  char buff[256];
  long l;

  lengthi = theEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theEvent.data[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theEvent.data[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theEvent.data[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%ld", &l);
      federate = l;
    }

    if (theEvent.data[i].id == managerFederateServiceChangeAttributeTransportationTypeObjectInstance)
    {
      GERTICO::Mapper::mapWstringFromChar(objectInstance, buff);
    }

    if (theEvent.data[i].id == managerFederateServiceChangeAttributeTransportationTypeAttributeList)
    {
      getAttributes(attributes, buff);
    }

    if (theEvent.data[i].id == managerFederateServiceChangeAttributeTransportationTypeTransportationType)
    {
      GERTICO::Mapper::getTransportationType(transportationType, buff);
    }
  }

  registeredObject = objectManagement.getObjectByName(objectInstance);
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

    itMomFederateMap = momFederateMap.find(federate);
    if (itMomFederateMap != momFederateMap.end())
    {
      exceptionLogging = itMomFederateMap->second->checkExceptionLogging();
      if (exceptionLogging)
      {
        sendAlert(federate, alertSeverity, alertDescription);
      }
    }
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
  char *cptr;
  long l;

  lengthi = theGeRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theGeRtiEvent.data[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theGeRtiEvent.data[i].value);
      sscanf(cptr, "%ld", &l);
      federate = l;
      delete[] cptr;
    }

    if (theGeRtiEvent.data[i].id == managerFederateServiceChangeInteractionOrderTypeInteractionClass)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theGeRtiEvent.data[i].value);
      sscanf(cptr, "%ld", &l);
      interactionClass = l;
      delete[] cptr;
    }

    if (theGeRtiEvent.data[i].id == managerFederateServiceChangeInteractionOrderTypeOrderingType)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theGeRtiEvent.data[i].value);
      GERTICO::Mapper::getOrderType(orderingType, cptr);
      delete[] cptr;
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

    itMomFederateMap = momFederateMap.find(federate);
    if (itMomFederateMap != momFederateMap.end())
    {
      exceptionLogging = itMomFederateMap->second->checkExceptionLogging();
      if (exceptionLogging)
      {
        sendAlert(federate, alertSeverity, alertDescription);
      }
    }
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
  char *cptr;
  long l;

  lengthi = theGeRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theGeRtiEvent.data[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theGeRtiEvent.data[i].value);
      sscanf(cptr, "%ld", &l);
      federate = l;
      delete[] cptr;
    }

    if (theGeRtiEvent.data[i].id == managerFederateServiceChangeInteractionTransportationTypeInteractionClass)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theGeRtiEvent.data[i].value);
      sscanf(cptr, "%ld", &l);
      interactionClass = l;
      delete[] cptr;
    }

    if (theGeRtiEvent.data[i].id == managerFederateServiceChangeInteractionTransportationTypeTransportationType)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theGeRtiEvent.data[i].value);
      GERTICO::Mapper::getTransportationType(transportationType, cptr);
      delete[] cptr;
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

    itMomFederateMap = momFederateMap.find(federate);
    if (itMomFederateMap != momFederateMap.end())
    {
      exceptionLogging = itMomFederateMap->second->checkExceptionLogging();
      if (exceptionLogging)
      {
        sendAlert(federate, alertSeverity, alertDescription);
      }
    }
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
    unsigned long ul = theGeRtiEvent._cxx_class;
    classDescr = interactionRoot.getClassDescr(theGeRtiEvent._cxx_class);
    if (classDescr == NULL)
    {
      std::cout << "class = NULL " << ul << std::endl;
    }
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
      if (setOwned)
      {
        // May have to set unowned to another federate.
        doMomRequest = new GERTICO::DoMomRequest(unownedGeRtiEvent, managerFederateAdjustModifyAttributeState, managerInteractionFederateFederate, federatesHolder);
        federationJobs.add(doMomRequest);
        adjustModifyAttributeState(unownedGeRtiEvent);
      }
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateAdjustModifyAttributeState, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
      adjustModifyAttributeState(theGeRtiEvent);
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

#ifdef IEEE_1516
  if (classDescr->isDerivedClass(managerFederateAdjustSetExceptionReporting))
#else
  if (classDescr->isDerivedClass(managerFederateAdjustSetExceptionLogging))
#endif
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
#ifdef IEEE_1516
    items.insert(managerFederateAdjustSetExceptionReportingState);
#else
    items.insert(managerFederateAdjustSetExceptionLoggingState);
#endif

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

#ifdef IEEE_1516
  if (classDescr->isDerivedClass(managerFederateRequestObjectsInstancesThatCanBeDeleted))
#else
  if (classDescr->isDerivedClass(managerFederateRequestObjectsOwned))
#endif
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

#ifdef IEEE_1516
  if (classDescr->isDerivedClass(managerFederateServicePublishObjectClassAttributes))
#else
  if (classDescr->isDerivedClass(managerFederateServicePublishObjectClass))
#endif
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
#ifdef IEEE_1516
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServicePublishObjectClassAttributes, managerInteractionFederateFederate, federatesHolder);
#else
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServicePublishObjectClass, managerInteractionFederateFederate, federatesHolder);
#endif
      federationJobs.add(doMomRequest);
    }
  }

#ifdef IEEE_1516
  if (classDescr->isDerivedClass(managerFederateServiceUnpublishObjectClassAttributes))
#else
  if (classDescr->isDerivedClass(managerFederateServiceUnpublishObjectClass))
#endif
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceUnpublishObjectClassObjectClass);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
#ifdef IEEE_1516
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceUnpublishObjectClassAttributes, managerInteractionFederateFederate, federatesHolder);
#else
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceUnpublishObjectClass, managerInteractionFederateFederate, federatesHolder);
#endif
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

  if (classDescr->isDerivedClass(managerFederateServiceUnsubscribeObjectClass))
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceUnsubscribeObjectClassObjectClass);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceUnsubscribeObjectClass, managerInteractionFederateFederate, federatesHolder);
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
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceUnconditionalAttributeOwnershipDivestiture, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

  if (theGeRtiEvent._cxx_class == managerFederateServiceEnableTimeRegulation)
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
#ifndef IEEE_1516
    items.insert(managerFederateServiceEnableTimeRegulationFederationTime);
#endif
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
    items.insert(managerFederateServiceTimeAdvanceRequestFederationTime);

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
    items.insert(managerFederateServiceTimeAdvanceRequestAvailableFederationTime);

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceTimeAdvanceRequestAvailable, managerInteractionFederateFederate, federatesHolder);
      federationJobs.add(doMomRequest);
    }
  }

#ifdef IEEE_1516
  if (theGeRtiEvent._cxx_class == managerFederateServiceNextMessageRequest)
#else
  if (theGeRtiEvent._cxx_class == managerFederateServiceNextEventRequest)
#endif
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
#ifdef IEEE_1516
    items.insert(managerFederateServiceNextMessageRequestFederationTime);
#else
    items.insert(managerFederateServiceNextEventRequestFederationTime);
#endif

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
#ifdef IEEE_1516
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceNextMessageRequest, managerInteractionFederateFederate, federatesHolder);
#else
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceNextEventRequest, managerInteractionFederateFederate, federatesHolder);
#endif
      federationJobs.add(doMomRequest);
    }
  }

#ifdef IEEE_1516
  if (theGeRtiEvent._cxx_class == managerFederateServiceNextMessageRequestAvailable)
#else
  if (theGeRtiEvent._cxx_class == managerFederateServiceNextEventRequestAvailable)
#endif
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
#ifdef IEEE_1516
    items.insert(managerFederateServiceNextMessageRequestAvailableFederationTime);
#else
    items.insert(managerFederateServiceNextEventRequestAvailableFederationTime);
#endif

    reverseChecklist(items, theGeRtiEvent);
    if (items.size() == 0)
    {
      GERTICO::DoMomRequest *doMomRequest;
#ifdef IEEE_1516
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceNextMessageRequestAvailable, managerInteractionFederateFederate, federatesHolder);
#else
      doMomRequest = new GERTICO::DoMomRequest(theGeRtiEvent, managerFederateServiceNextEventRequestAvailable, managerInteractionFederateFederate, federatesHolder);
#endif
      federationJobs.add(doMomRequest);
    }
  }

  if (theGeRtiEvent._cxx_class == managerFederateServiceFlushQueueRequest)
  {
    // A reverse checklist.
    items.clear();
    items.insert(managerInteractionFederateFederate);
    items.insert(managerFederateServiceFlushQueueRequestFederationTime);

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
  char *cptr;
  long l;

  lengthi = theGeRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theGeRtiEvent.data[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theGeRtiEvent.data[i].value);
      sscanf(cptr, "%ld", &l);
      theFederate = l;
      delete[] cptr;
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

    theUnonwedGeRtiEvent = theGeRtiEvent;
    try
    {
      char buff[128];
      long l;

      registeredObject = objectManagement.getObjectByName(objectInstance);
      privilegeToDeleteId = objectManagement.getPrivilegeToDeleteId();
      registeredObject->getOwner(unownedFederate, privilegeToDeleteId);
      l = unownedFederate;
      sprintf(buff, "%ld", l);
      GERTICO::Mapper::mapHandleValue(theUnonwedGeRtiEvent.data[saveFederateIndex], managerInteractionFederateFederate, buff);
      strcpy(buff,"unowned");
      GERTICO::Mapper::mapHandleValue(theUnonwedGeRtiEvent.data[saveStateIndex], managerFederateAdjustModifyAttributeStateAttributeState, buff);
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
  if (theClass == managerFederateObjectClass)
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

  momFederateFederate = objectManagement.registerObjectInstance(1, managerFederateObjectClass);
  momFederate = new GERTICO::MomFederate(theFederate, momFederateFederate);

  momFederateMap[theFederate] = momFederate;
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
    currFederate->getSubscribedAttributes(managerFederateObjectClass, fedAttributes);
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
  if (theClass == managerFederateObjectClass)
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
  if (whichClass == managerFederateObjectClass)
  {
    GERTICO::RequestManagerFederateJob *requestManagerFederateJob;

    for (itMomFederateMap = momFederateMap.begin(); itMomFederateMap != momFederateMap.end(); itMomFederateMap++)
    {
      itMomFederateMap->second->getMomFederateFederate(object);
      if (object == theObject)
      {
        requestManagerFederateJob = new GERTICO::RequestManagerFederateJob(federatesHolder, momFederateMap, itMomFederateMap->first, whichClass, theAttributes, managerFederateFEDid, federationFile, eventHandler, interactionRoot);

        federationJobs.add(requestManagerFederateJob);
      }
    }
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
  std::string s;
  unsigned long ul;

  length = 1;
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

  itAttribute = theAttributes.find(managerFederationFederationName);
  if (itAttribute != theAttributes.end())
  {
    e.data.length(length + 1);
    GERTICO::Mapper::mapStringFromWstring(s, federationName);
    GERTICO::Mapper::mapHandleValue(e.data[length], managerFederationFederationName, s.c_str());
    length += 1;
  }

  itAttribute = theAttributes.find(managerFederationFederatesInFederation);
  if (itAttribute != theAttributes.end())
  {
    bool b = false;
    char buff[16];

    s = "";
    e.data.length(length + 1);
    federatesHolder.getFederates(federates);
    for (itFederate = federates.begin(); itFederate != federates.end(); itFederate++)
    {
      if (b)
      {
        s.append(",");
      }
      b = true;
      sprintf(buff, "%d", *itFederate);
      s.append(buff);
    }
    GERTICO::Mapper::mapHandleValue(e.data[length], managerFederationFederatesInFederation, s.c_str());
    length += 1;
  }

  itAttribute = theAttributes.find(managerFederationRTIversion);
  if (itAttribute != theAttributes.end())
  {
    s = "gertico_0_54";
    e.data.length(length + 1);
    GERTICO::Mapper::mapHandleValue(e.data[length], managerFederationRTIversion, s.c_str());
    length += 1;
  }

  itAttribute = theAttributes.find(managerFederationFEDid);
  if (itAttribute != theAttributes.end())
  {
    e.data.length(length + 1);
    GERTICO::Mapper::mapStringFromWstring(s, federationFile);
    GERTICO::Mapper::mapHandleValue(e.data[length], managerFederationFEDid, s.c_str());
    length += 1;
  }

  itAttribute = theAttributes.find(managerFederationLastSaveName);
  if (itAttribute != theAttributes.end())
  {
    e.data.length(length + 1);
    GERTICO::Mapper::mapStringFromWstring(s, lastSaveName);
    GERTICO::Mapper::mapHandleValue(e.data[length], managerFederationLastSaveName, s.c_str());
    length += 1;
  }

  itAttribute = theAttributes.find(managerFederationLastSaveTime);
  if (itAttribute != theAttributes.end())
  {
    e.data.length(length + 1);
    GERTICO::Mapper::mapHandleValue(e.data[length], managerFederationLastSaveTime, lastSaveTime.c_str());
    length += 1;
  }

  itAttribute = theAttributes.find(managerFederationNextSaveName);
  if (itAttribute != theAttributes.end())
  {
    e.data.length(length + 1);
    GERTICO::Mapper::mapStringFromWstring(s, nextSaveName);
    GERTICO::Mapper::mapHandleValue(e.data[length], managerFederationNextSaveName, s.c_str());
    length += 1;
  }

  itAttribute = theAttributes.find(managerFederationNextSaveTime);
  if (itAttribute != theAttributes.end())
  {
    e.data.length(length + 1);
    GERTICO::Mapper::mapHandleValue(e.data[length], managerFederationNextSaveTime, nextSaveTime.c_str());
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

  itMomFederateMap = momFederateMap.find(theFederate);
  if (itMomFederateMap != momFederateMap.end())
  {
    itMomFederateMap->second->getMomFederateFederate(federateObject);
    objectManagement.deleteObjectInstance(mom, federateObject, userSuppliedTag);
    momFederateMap.erase(itMomFederateMap);
  }
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
  char buff[128];
  long l;
  unsigned long ul;

  e.type = GeRtiFactory::interaction;
  e.source = 1;
  e.theSerialNumber = 0;
  GERTICO::Mapper::mapUserSuppliedTag(e.theTag, "MOM");
  e.obj = 0;
  e.reg = 0;
#ifdef IEEE_1516
  e._cxx_class = managerFederateReportException;
#else
  e._cxx_class = managerFederateReportAlert;
#endif
  classDescr = interactionRoot.getClassDescr(e._cxx_class);
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

  e.data.length(4);

  indd = 0;
  l = theFederate;
  sprintf(buff, "%ld", l);
  GERTICO::Mapper::mapHandleValue(e.data[indd], managerInteractionFederateFederate, buff);

  indd = 1;
  GERTICO::Mapper::mapHandleValue(e.data[indd], managerFederateReportAlertAlertSeverity, theAlertSeverity.c_str());

  indd = 2;
  GERTICO::Mapper::mapHandleValue(e.data[indd], managerFederateReportAlertAlertDescription, theAlertDescription.c_str());

  indd = 3;
  sprintf(buff, "%ld", counter++);
  GERTICO::Mapper::mapHandleValue(e.data[indd], managerFederateReportAlertAlertID, buff);

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
void GERTICO::ManagementObjectModel::setNextSaveTime(const std::string &theTime)
{
  nextSaveTime = theTime;
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
  std::wstring objectInstance;
  bool gotError = false;
  char *cptr;
  long l;

  lengthi = theGeRtiEvent.data.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theGeRtiEvent.data[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theGeRtiEvent.data[i].value);
      sscanf(cptr, "%ld", &l);
      federate = l;
      delete[] cptr;
    }

    if (theGeRtiEvent.data[i].id == managerFederateServiceUnconditionalAttributeOwnershipDivestitureObjectInstance)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theGeRtiEvent.data[i].value);
      GERTICO::Mapper::mapWstringFromChar(objectInstance, cptr);
      delete[] cptr;
    }

    if (theGeRtiEvent.data[i].id == managerFederateServiceUnconditionalAttributeOwnershipDivestitureAttributeList)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theGeRtiEvent.data[i].value);
      getAttributes(attributes, cptr);
      delete[] cptr;
    }
  }

  registeredObject = objectManagement.getObjectByName(objectInstance);
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

    itMomFederateMap = momFederateMap.find(federate);
    if (itMomFederateMap != momFederateMap.end())
    {
      exceptionLogging = itMomFederateMap->second->checkExceptionLogging();
      if (exceptionLogging)
      {
        sendAlert(federate, alertSeverity, alertDescription);
      }
    }
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

  for (itMomFederateMap = momFederateMap.begin(); itMomFederateMap != momFederateMap.end(); itMomFederateMap++)
  {
    if (itMomFederateMap->second->checkReportPeriod(wallClockCounter))
    {
      otherManagerFederateSubscribedAttributes(attributes);

      requestManagerFederateJob = new GERTICO::RequestManagerFederateJob(federatesHolder, momFederateMap, itMomFederateMap->first, managerFederateObjectClass, attributes, managerFederateFEDid, federationFile, eventHandler, interactionRoot);

      federationJobs.add(requestManagerFederateJob);

      ps.release();
    }
  }
}
