/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** DeclarationManagementEC.cpp
**
*******************************************************************************/

#include "DeclarationManagementEC.h"
#include "EventMarket/Jobs.h"
#include "Util/Mapper.h"
#include <iostream>

/********************************** Gal begin ***************************************/

#ifdef GalDebug

#include "Gal/StdAfx.h"
#include "Gal/repository.h"
#include "Gal/event.h"

static class Repository_l *DM=(Repository::getSingleInstance())->getRepository_l("GeRtiDM.res","GeRtiDM");

static class Event *GeRti_DM_d=DM->getRefEvent("GeRti_DM_d");
static class Event *GeRti_DM_e=DM->getRefEvent("GeRti_DM_e");
static class Event *GeRti_DM_i=DM->getRefEvent("GeRti_DM_i");
static class Event *GeRti_DM_w=DM->getRefEvent("GeRti_DM_w");

#endif

/********************************** Gal end ***************************************/

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::DeclarationManagementEC::DeclarationManagementEC(GeRtiFactory::GeRtiHandle const &thePrivilegeToDeleteId, GERTICO::InteractionMap &theInteractionMap, GERTICO::FedEventSenderMap &theFedEventSenderMap, GERTICO::SupportingServicesEC &theSupportingServicesEC, ACE_Thread_Mutex &theFedPm) : pmFed(theFedPm), fedEventSenderMap(theFedEventSenderMap), interactionMap(theInteractionMap), supportingServicesEC(theSupportingServicesEC)
{
  // Get privilege to delete id.
  privilegeToDeleteId = thePrivilegeToDeleteId;

  // Interaction class
  interactionHolder = new GERTICO::InteractionHolder(interactionMap, regionsHolder, supportingServicesEC);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::DeclarationManagementEC::~DeclarationManagementEC(void)
{
  if (interactionHolder)
  {
    delete interactionHolder;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::addSubscribeObjectClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet &theAttSet, CORBA::Boolean const &theActive)
{
  GERTICO::RegionAttributes regionAttributes;
  GERTICO::ClassRegionsHolderMap *classRegionsHolderMapPtr;
  GERTICO::ClassRegionsHolderMap::iterator itCRH;
  GERTICO::FedClassRegionsHolderMap::iterator itSubscribedClassMap;
  GERTICO::FedRegionsHolder *currRegionsHolder;
  GERTICO::FedRegionsHolder newRegionsHolder;
  GERTICO::HandleSet::iterator itAttSet;
  GERTICO::HandleSet::iterator itRegionsIn;
  GERTICO::RegionAttributesMap::iterator itRA;

  itSubscribedClassMap = fedSubscribedClassMap.find(theFederate);
  if (itSubscribedClassMap == fedSubscribedClassMap.end())
  {
    GERTICO::ClassRegionsHolderMap classRegionsHolderMap;
    fedSubscribedClassMap[theFederate] = classRegionsHolderMap;
  }

#ifndef IEEE_1516
  itSubscribedClassMap = fedSubscribedClassMap.find(theFederate);
  if (itSubscribedClassMap == fedSubscribedClassMap.end())
  {
    classRegionsHolderMapPtr = &itSubscribedClassMap->second;
    itCRH = classRegionsHolderMapPtr->find(theObjectClass);
    if (itCRH != classRegionsHolderMapPtr->end())
    {
      // Replace all values -> delete old values first.
      for (itAttSet = theAttSet.begin(); itAttSet != theAttSet.end(); itAttSet++)
      {
        try
        {
          delObjectClassSub(theFederate, theObjectClass);
        }
        catch(...)
        {
        }
      }
    }
  }
#endif

  itSubscribedClassMap = fedSubscribedClassMap.find(theFederate);
  if (itSubscribedClassMap != fedSubscribedClassMap.end())
  {
    classRegionsHolderMapPtr = &itSubscribedClassMap->second;
    itCRH = classRegionsHolderMapPtr->find(theObjectClass);
    if (itCRH == classRegionsHolderMapPtr->end())
    {
      // Add empty value entry if necessary.
     (*classRegionsHolderMapPtr)[theObjectClass] = newRegionsHolder;
    }

    // Position on entry.
    itCRH = classRegionsHolderMapPtr->find(theObjectClass);
    if (itCRH != classRegionsHolderMapPtr->end())
    {
      currRegionsHolder = &itCRH->second;
      itRA = currRegionsHolder->regionAttributesMap.find(0);
      if (itRA != currRegionsHolder->regionAttributesMap.end())
      {
        currRegionsHolder->regionAttributesMap.erase(itRA);
      }
    }
    else
    {
      throw GeRtiFactory::RTIinternalError(L"Federate::addSubscribeObjectClass: map inconsistent");
    }
  }

  // Fill new atrributes.
  regionAttributes.attributes.clear();
  for (itAttSet = theAttSet.begin(); itAttSet != theAttSet.end(); itAttSet++)
  {
    regionAttributes.attributes.insert(*itAttSet);
  }
  regionAttributes.myActive = theActive;

  currRegionsHolder->regionAttributesMap[0] = regionAttributes;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::clear(void)
{
//  regionsHolder.clear();
  publisherObjectClassHolder.clear();
  subscribedClassHolder.clear();
  fedSubscribedClassMap.clear();
  interactionHolder->clear();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::delFedInteractions(GeRtiFactory::GeRtiHandle const &theFederate, HandleSet &pubInteractions, HandleSet &pubObjects, HandleSetMap &subInteractionMap, HandleSetMap &subObjectsMap)
{
  GERTICO::HandleSet *currHandleSet;
  GERTICO::HandleSet::iterator itHS;
  HandleSetMap currHandleSetMap;
  HandleSetMap::iterator itFI;

  // For each interaction delete federate information.
  for (itHS = pubInteractions.begin(); itHS != pubInteractions.end(); itHS++)
  {
    unpublishInteractionClass(theFederate, *itHS);
  }

  // For each interaction delete federate information.
  for (itFI = subInteractionMap.begin(); itFI != subInteractionMap.end(); itFI++)
  {
    currHandleSet = &itFI->second;
    for (itHS = currHandleSet->begin(); itHS != currHandleSet->end(); itHS++)
    {
//      interactionHolder.unsubscribeInteractionClass(theFederate, itFI->first, *itHS);
    }
//    eventHandler->unsubscribeInteractionClassWithRegions(theFederate, itFI->first, itFI->second);
  }

  // For each object class delete federate information.
  for (itHS = pubObjects.begin(); itHS != pubObjects.end(); itHS++)
  {
    try
    {
      unpublishObjectClass(theFederate, *itHS);
    }
    catch(...)
    {
      continue;
    }
  }

  // Get list of subscriber object classes per federate.
  for (itFI = subObjectsMap.begin(); itFI != subObjectsMap.end(); itFI++)
  {
    currHandleSet = &itFI->second;
    for (itHS = currHandleSet->begin(); itHS != currHandleSet->end(); itHS++)
    {
      try
      {
        unsubscribeObjectClassPrivate(theFederate, itFI->first, *itHS);
      }
      catch(...)
      {
        continue;
      }
    }
  }
}

// ---------------------------------------------------------------------------
// NB. default region is 0, thus general logic applies for any specific
// region value.
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::delObjectClassSub(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass)
{
  CORBA::WChar *wChar = L"delObjectClassSub";
  GERTICO::ClassRegionsHolderMap *classRegionsHolderMapPtr;
  GERTICO::ClassRegionsHolderMap::iterator itCRH;
  GERTICO::RegionAttributesMap::iterator itRA;
  GERTICO::FedRegionsHolder *currRegionsHolder;
  GERTICO::FedClassRegionsHolderMap::iterator itSubscribedClassMap;

  itSubscribedClassMap = fedSubscribedClassMap.find(theFederate);
  if (itSubscribedClassMap != fedSubscribedClassMap.end())
  {
    classRegionsHolderMapPtr = &itSubscribedClassMap->second;
    itCRH = classRegionsHolderMapPtr->find(theObjectClass);
    if (itCRH != classRegionsHolderMapPtr->end())
    {
      currRegionsHolder = &itCRH->second;
      // Erase old attribute values for this object class and region.
      itRA = currRegionsHolder->regionAttributesMap.find(0);
      if (itRA != currRegionsHolder->regionAttributesMap.end())
      {
        currRegionsHolder->regionAttributesMap.erase(itRA);
      }
      else
      {
        throw GeRtiFactory::ObjectClassNotSubscribed(wChar);
      }

      if (currRegionsHolder->regionAttributesMap.size() == 0)
      {
        classRegionsHolderMapPtr->erase(itCRH);
      }
    }
    else
    {
      throw GeRtiFactory::ObjectClassNotSubscribed(wChar);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::getDesiredAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClassId, GERTICO::HandleSet const &theEventAttributes, GERTICO::HandleSet &theDesiredAttributes)
{
  subscribedClassHolder.getDesiredAttributes(theFederate, theClassId, theEventAttributes, theDesiredAttributes);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::getFederatesForInteraction(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet &theFederates)
{
  interactionHolder->getFederatesForInteraction(theFederate, theInteraction, theFederates);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::getFederateRegions(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theRegions)
{
  RegionMap::iterator itRegion;

  theRegions.clear();
  for (itRegion = regionsHolder.regionMap.begin(); itRegion != regionsHolder.regionMap.end(); itRegion++)
  {
    theRegions.insert(itRegion->first);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::getPublishedAttributesPrivate(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSet &theAttributeSet)
{
  publisherObjectClassHolder.getPublishedAttributes(theFederate, theClass, theAttributeSet, privilegeToDeleteId);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::PublishedClass* GERTICO::DeclarationManagementEC::getPublishedClass(GeRtiFactory::GeRtiHandle const &classId)
  throw (GeRtiFactory::ObjectClassNotPublished)
{
  return publisherObjectClassHolder.getPublishedClass(classId);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Region *GERTICO::DeclarationManagementEC::getRegion(GeRtiFactory::GeRtiHandle const &regionId)
{
  Region *currRegion = NULL;

  currRegion = regionsHolder.getRegion(regionId);

  return currRegion;
}

// ---------------------------------------------------------------------------
// For the given object class check if there are any active subscribers
// in given or in base classes.
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::objectClassPubStartRegistration(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet &theAttributes)
{
  GERTICO::FedEventSenderMap::iterator itFedEventSenderMap;
  GeRtiFactory::GeRtiHandle currObjectClass;
  bool started;

  started = getStarted(theFederate, theObjectClass);

  // Take class and any parents of class.
  for (currObjectClass = theObjectClass; currObjectClass != 0; currObjectClass = supportingServicesEC.getObjectParent(currObjectClass))
  {
    try
    {
      if (subscribedClassHolder.checkActiveObjectClassSubscribers(theFederate, currObjectClass, theAttributes))
      {
        // Turn the fed on and leave.
        if (getStarted(theFederate, theObjectClass) == false)
        {
          GeRtiFactory::GertiDmEvent gertiDmEvent;

          // Start registration.
          gertiDmEvent.service = 10;
          gertiDmEvent.sourceId = theFederate;
          gertiDmEvent.theHandle = theObjectClass;
//          pmFed.acquire();
          itFedEventSenderMap = fedEventSenderMap.find(theFederate);
          if (itFedEventSenderMap != fedEventSenderMap.end())
          {
            itFedEventSenderMap->second->addDmEvent(gertiDmEvent);
          }
//          pmFed.release();
          setStarted(theFederate, theObjectClass, true);
//          itPublishInteractionFlagsMap->second.setTurnedOn(true);
//          newStJob = new StJob(theFederate.getId(), theObjectClass, true, federatesHolder);
//          federationJobs.add(newStJob);
        }
        return;
      }
    }
    catch(GeRtiFactory::ObjectClassNotPublished &)
    {
    }
  }

  // No active subscriber found.
  // Turn off publisher.
  if (started == true)
  {
//    newStJob = new StJob(theFederate.getId(), theObjectClass, false, federatesHolder);
//    federationJobs.add(newStJob);
  }
}

// ---------------------------------------------------------------------------
// Recursive function to get publishers in all derived classes and start
// registration for object classes.
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::objectClassSubStartRegistration(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theAttributes, GeRtiFactory::GeRtiHandle const &theObjectClass)
{
  GERTICO::HandleSet::iterator itChild;
  GERTICO::HandleSet children;

  objectClassSubStartRegistrationFind(theFederate, theAttributes, theObjectClass);

  // Check children of class.
  supportingServicesEC.getObjectClassChildren(theObjectClass, children);
  for (itChild = children.begin(); itChild != children.end(); itChild++)
  {
    objectClassSubStartRegistrationFind(theFederate, theAttributes, *itChild);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::objectClassSubStartRegistrationFind(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theAttributes, GeRtiFactory::GeRtiHandle const &theObjectClass)
{
  GERTICO::ClassDescrMap::iterator itCD;
  GERTICO::FedEventSenderMap::iterator itFedEventSenderMap;
  GERTICO::HandleSet children;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet::iterator itChild;
  GERTICO::HandleSet::iterator itHS;
  GERTICO::HandleSet publishers;
  PublishedClass *currPublishedClass;
  GeRtiFactory::GertiDmEvent gertiDmEvent;
  GeRtiFactory::GeRtiHandle cla;
  GeRtiFactory::GeRtiHandle fed;

  publisherObjectClassHolder.getPublishFederates(federates);

  // Check this level, if found
  currPublishedClass = getPublishedClass(theObjectClass);
  if (currPublishedClass)
  {
    currPublishedClass->startRegistration(theFederate, theAttributes, publishers, federates);
    for (itHS = publishers.begin(); itHS != publishers.end(); itHS++)
    {
      fed = *itHS;
      cla = currPublishedClass->getId();

      // Start registration.
      gertiDmEvent.service = 10;
      gertiDmEvent.sourceId = fed;
      gertiDmEvent.theHandle = theObjectClass;
//      pmFed.acquire();
      itFedEventSenderMap = fedEventSenderMap.find(fed);
      if (itFedEventSenderMap != fedEventSenderMap.end())
      {
        itFedEventSenderMap->second->addDmEvent(gertiDmEvent);
      }
//      pmFed.release();
      setStarted(fed, theObjectClass, true);
    }
  }
}

// ---------------------------------------------------------------------------
// NB. The search may be very slow for very large object class trees.
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::objectClassSubStopRegistration(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass)
{
  GERTICO::FedClassRegionsHolderMap::iterator itFedClassRegionsHolderMap;
  GERTICO::FedEventSenderMap::iterator itFedEventSenderMap;
  GERTICO::HandleSet publishFederates;
  GERTICO::HandleSet publishedAttributes;
  GERTICO::HandleSet publishedObjectClasses;
  GERTICO::HandleSet publishedRegions;
  GERTICO::HandleSet subscribedFederates;
  GERTICO::HandleSet subscribedRegions;
  GERTICO::HandleSet::iterator itPublisherFederate;
  GERTICO::HandleSet::iterator itSubscriberFederate;
  GERTICO::HandleSet::iterator itPublishedAttribute;
  GERTICO::HandleSet::iterator itPublishedObjectClass;
  GERTICO::HandleSet::iterator itPublishedRegion;
  GERTICO::HandleSet::iterator itSubscribedRegion;
  GERTICO::Region *subscribedRegion;
  GeRtiFactory::GeRtiHandle objectClass;
  GeRtiFactory::GeRtiHandle subscribedClass;
  bool gotSubscriber;

  publisherObjectClassHolder.getPublishFederates(publishFederates);
  for (itFedClassRegionsHolderMap = fedSubscribedClassMap.begin(); itFedClassRegionsHolderMap != fedSubscribedClassMap.end(); itFedClassRegionsHolderMap++)
  {
    subscribedFederates.insert(itFedClassRegionsHolderMap->first);
  }

  // Check any publishers.
  for (itPublisherFederate = publishFederates.begin(); itPublisherFederate != publishFederates.end(); itPublisherFederate++)
  {
    if (*itPublisherFederate == theFederate)
    {
      continue;
    }

    getFederateRegions(*itPublisherFederate, publishedRegions);

    publisherObjectClassHolder.getPublishedObjectClasses(*itPublisherFederate, publishedObjectClasses);
    for (itPublishedObjectClass = publishedObjectClasses.begin(); itPublishedObjectClass != publishedObjectClasses.end(); itPublishedObjectClass++)
    {
      // Class already stopped.
      if (getStarted(*itPublisherFederate, *itPublishedObjectClass) == false)
      {
        continue;
      }

      // Only useful if publisher is a derived class of subscriber
      if (supportingServicesEC.isDerivedObjectClass(*itPublishedObjectClass, theObjectClass) == false)
      {
        continue;
      }

      getPublishedAttributesPrivate(*itPublisherFederate, *itPublishedObjectClass, publishedAttributes);
      gotSubscriber = false;
      for (itPublishedAttribute = publishedAttributes.begin(); itPublishedAttribute != publishedAttributes.end(); itPublishedAttribute++)
      {
        for (itSubscriberFederate = subscribedFederates.begin(); itSubscriberFederate != subscribedFederates.end(); itSubscriberFederate++)
        {
          if (*itSubscriberFederate == *itPublisherFederate)
          {
            continue;
          }

          for (subscribedClass = *itPublishedObjectClass; subscribedClass != 0; subscribedClass = supportingServicesEC.getObjectParent(subscribedClass))
          {
            getSubscribedAttributeRegions(*itSubscriberFederate, subscribedClass, *itPublishedAttribute, subscribedRegions, true);
            for (itSubscribedRegion = subscribedRegions.begin(); itSubscribedRegion != subscribedRegions.end(); itSubscribedRegion++)
            {
              if (*itSubscribedRegion == 0)
              {
                gotSubscriber = true;
                break;
              }
              else
              {
                subscribedRegion = getRegion(*itSubscribedRegion);
                if (subscribedRegion)
                {
                  for (itPublishedRegion = publishedRegions.begin(); itPublishedRegion != publishedRegions.end(); itPublishedRegion++)
                  {
                    if (subscribedRegion->gotIntersection(*itPublishedRegion))
                    {
                      gotSubscriber = true;
                      break;
                    }
                  }
                }
              }
            }
            if (gotSubscriber)
            {
              // for class loop
              break;
            }
          }
          if (gotSubscriber)
          {
            // for subscriber loop
            break;
          }
        }
        if (gotSubscriber)
        {
          // for attribute loop
          break;
        }
      }
      if (gotSubscriber == false)
      {
        GeRtiFactory::GertiDmEvent gertiDmEvent;
        
        // for other object loop
        objectClass = *itPublishedObjectClass;
        // StOP registration.
        gertiDmEvent.service = 11;
        gertiDmEvent.sourceId = *itPublisherFederate;
        gertiDmEvent.theHandle = *itPublishedObjectClass;
//        pmFed.acquire();
        itFedEventSenderMap = fedEventSenderMap.find(*itPublisherFederate);
        if (itFedEventSenderMap != fedEventSenderMap.end())
        {
          itFedEventSenderMap->second->addDmEvent(gertiDmEvent);
        }
//        pmFed.release();
        setStarted(*itPublisherFederate, theObjectClass, false);
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::publishInteractionClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction)
{
  interactionHolder->publishInteractionClass(theFederate, theInteraction, fedEventSenderMap);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::publishObjectClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet &theAttributes)
{
  GERTICO::HandleSet attributes;

  // Get any old published attributes.
  try
  {
    getPublishedAttributesPrivate(theFederate, theObjectClass, attributes);
  }
  catch(...)
  {
  }

  pm.acquire();
  try
  {
    publisherObjectClassHolder.publishObjectClass(theFederate, theObjectClass, theAttributes);

      // Require logic to start registration for object class.
    objectClassPubStartRegistration(theFederate, theObjectClass, theAttributes);
  }
  catch(...)
  {
    pm.release();
    throw;
  }

  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::resignFederationExecution(GeRtiFactory::GeRtiHandle const &theFederate)
{
  GERTICO::FedClassRegionsHolderMap::iterator itSubscribedClassMap;

  itSubscribedClassMap = fedSubscribedClassMap.find(theFederate);
  if (itSubscribedClassMap != fedSubscribedClassMap.end())
  {
    fedSubscribedClassMap.erase(itSubscribedClassMap);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::restore(DOMElement &theDOMElement)
{
//  GERTICO::ClassDescr *classDescr;
  DOMNode *child;
  char *tmpChar;
  std::string tmpString;
  unsigned long ordering = 0;
  unsigned long transportation = 0;
  unsigned long tmpUL;

  // Delete old values.
//  interactionHolder.clear();

  // Restore the intersections,
  child = theDOMElement.getFirstChild();
  while (child != 0)
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode("interaction")) == 0)
      {
        tmpChar = XMLString::transcode(((DOMElement*)child)->getAttribute(XMLString::transcode("id")));
        sscanf(tmpChar, "%lu", &tmpUL);
//        classDescr = interactionRoot.getClassDescr(tmpUL);
//        if (classDescr)
//        {
//          classDescr->getOrdering(ordering);
//          classDescr->getTransportation(transportation);
//        }
//        interactionHolder.restore(*((DOMElement*) child), tmpUL, ordering, transportation);
      }
    }
    // Repeat for all federate types.
    child = child->getNextSibling();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
//  interactionHolder.save(theDOMDocument, theDOMElement);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::setStarted(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, bool const &theStarted)
{
  publisherObjectClassHolder.setStarted(theFederate, theClass, theStarted);
  GERTICO::PublishedClass *publishedClassPtr;

  try
  {
    publishedClassPtr = publisherObjectClassHolder.getPublishedClass(theClass);
    if (publishedClassPtr)
    {
      publishedClassPtr->setStarted(theFederate, theStarted);
    }
  }
  catch(...)
  {
    return;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::DeclarationManagementEC::getStarted(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass)
{
  GERTICO::PublishedClass *publishedClassPtr;
  bool ret = false;

  try
  {
    publishedClassPtr = publisherObjectClassHolder.getPublishedClass(theClass);
    if (publishedClassPtr)
    {
      ret = publishedClassPtr->getStarted(theFederate);
    }
  }
  catch(...)
  {
    return ret;
  }

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::getSubscribedAttributeRegions(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theAttribute, GERTICO::HandleSet &theRegions, bool const &onlyActiveSubscriptions)
{
  GERTICO::ClassRegionsHolderMap *classRegionsHolderMapPtr;
  GERTICO::ClassRegionsHolderMap::iterator itCRHM;
  HandleSet::iterator itAttribute;
  HandleSet::iterator itRegion;
  GERTICO::FedRegionsHolder *regionsHolder;
  GERTICO::FedClassRegionsHolderMap::iterator itSubscribedClassMap;
  GERTICO::RegionAttributes *regionAttributes;
  GERTICO::RegionAttributesMap::iterator itRAM;

  theRegions.clear();

  itSubscribedClassMap = fedSubscribedClassMap.find(theFederate);
  if (itSubscribedClassMap != fedSubscribedClassMap.end())
  {
    classRegionsHolderMapPtr = &itSubscribedClassMap->second;
    itCRHM = classRegionsHolderMapPtr->find(theClass);
    if (itCRHM != classRegionsHolderMapPtr->end())
    {
      regionsHolder = &itCRHM->second;

      for (itRAM = regionsHolder->regionAttributesMap.begin(); itRAM != regionsHolder->regionAttributesMap.end(); itRAM++)
      {
        regionAttributes = &itRAM->second;
        if (onlyActiveSubscriptions)
        {
          if (regionAttributes->myActive == false)
          {
            continue;
          }
        }
        itAttribute = regionAttributes->attributes.find(theAttribute);
        if (itAttribute != regionAttributes->attributes.end())
        {
          itRegion = theRegions.find(itRAM->first);
          if (itRegion == theRegions.end())
          {
            theRegions.insert(itRAM->first);
          }
        }
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::subscribeInteractionClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, CORBA::Boolean const &theActive, GERTICO::HandleSet const &theRegions)
{
  CORBA::WChar *wChar = L"";
  GERTICO::HandleSet::const_iterator itHandleSet;
//  GERTICO::Region *region;
  unsigned long interactionSpace = 0;
  unsigned long regionSpace = 0;

#ifdef IEEE_1516
  // Atomic test.
//  interactionHolder.testRegionDimensions(theInteraction, theRegions);
#endif

  if (theActive != 0 && theActive != 1)
  {
    throw GeRtiFactory::RTIinternalError(L"invalid active boolean");
  }

  interactionHolder->subscribeInteractionClass(theFederate, theInteraction, theActive, theRegions, fedEventSenderMap);
//  interactionHolder->subscribeInteractionClassWithRegions(theFederate, theInteraction, theRegions);







  /*
  pm.acquire();
  // Check region space and fed file space.
  for (itHandleSet = theRegions.begin(); itHandleSet != theRegions.end(); itHandleSet++)
  {
    if (*itHandleSet)
    {
      region = getRegion(*itHandleSet);
      if (region)
      {
        regionSpace = region->getSpace();
      }
      classDescr->getInteractionSpaceHandle(interactionSpace);
      if (regionSpace != interactionSpace)
      {
        pm.release();
        throw GeRtiFactory::InvalidRegionContext(wChar);
      }
    }
  }
  pm.release();
  */

  // Check if interactions already administered.
//  interactionHolder.subscribeInteractionClass(theFederate, theInteraction, theActive, theRegions);
//  eventHandler->subscribeInteractionClassWithRegions(theFederate, theInteraction, theRegions);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::subscribeObjectClassAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet &theAttributes, CORBA::Boolean const &theActive)
{
  if (theActive != 0 && theActive != 1)
  {
    throw GeRtiFactory::RTIinternalError(L"invalid active boolean");
  }

  pm.acquire();

  try
  {
    subscribeObjectClassAttributesPrivate(theFederate, theObjectClass, theAttributes, theActive);
  }
  catch(...)
  {
    pm.release();
    throw;
  }

  // Add to federate.
  addSubscribeObjectClass(theFederate, theObjectClass, theAttributes, theActive);

  if (theActive)
  {
    // Logic to start registration for object class.
    objectClassSubStartRegistration(theFederate, theAttributes, theObjectClass);
  }

  // Logic to stop registration for object class.
  objectClassSubStopRegistration(theFederate, theObjectClass);

  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::subscribeObjectClassAttributesPrivate(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet &theAttributes, CORBA::Boolean const &theActive)
{
  subscribedClassHolder.subscribeObjectClassAttributes(theFederate, theObjectClass, theAttributes, theActive);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::unpublishInteractionClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction)
{
//  interactionHolder.unpublishInteractionClass(theFederate, theInteraction);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::unpublishObjectClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass)
{
  CORBA::WChar *wChar = L"";
  GERTICO::HandleSet unpubAttributes;

  // Get any old published attributes.
  try
  {
    getPublishedAttributesPrivate(theFederate, theObjectClass, unpubAttributes);
  }
  catch(...)
  {
  }

  publisherObjectClassHolder.unpublishObjectClass(theFederate, theObjectClass);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::unpublishObjectClassAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet const &attributeSet)
{
  // XXX
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::unsubscribeInteractionClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet const &theRegions)
{
  CORBA::WChar *wChar = L"";
  GERTICO::HandleMap publishers;
  GERTICO::HandleSet::const_iterator itHandleSet;

  pm.acquire();
  try
  {
    for (itHandleSet = theRegions.begin(); itHandleSet != theRegions.end(); itHandleSet++)
    {
//      interactionHolder.unsubscribeInteractionClass(theFederate, theInteraction, *itHandleSet);
    }
//    eventHandler->unsubscribeInteractionClassWithRegions(theFederate, theInteraction, theRegions);
  }
  catch(GeRtiFactory::RegionNotKnown &)
  {
    pm.release();
    // Testcase 9-7-13.
    throw GeRtiFactory::InteractionClassNotSubscribed(wChar);
  }
  catch(...)
  {
    pm.release();
    throw;
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::unsubscribeObjectClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet const &theAttributes)
{
  CORBA::WChar *wChar = L"unsubscribeObjectClass";

  pm.acquire();
  try
  {
    unsubscribeObjectClassPrivate(theFederate, theObjectClass, 0);
  }
  catch(GeRtiFactory::RegionNotKnown &)
  {
    pm.release();
    //Testcase 9-6-19
    throw GeRtiFactory::ObjectClassNotSubscribed(wChar);
  }
#ifndef IEEE_1516
  catch(GeRtiFactory::ObjectClassNotSubscribed &)
  {
    pm.release();
    throw;
  }
#endif
  catch(...)
  {
    pm.release();
    return;
  }

  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementEC::unsubscribeObjectClassPrivate(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GeRtiFactory::GeRtiHandle const &theRegion)
{
  GERTICO::HandleSet regions;

  // Delete from federate.
  delObjectClassSub(theFederate, theObjectClass);

  regions.insert(theRegion);
  subscribedClassHolder.unsubscribeObjectClass(theFederate, theObjectClass, regions);

  // Logic to stop registration for object class.
  objectClassSubStopRegistration(theFederate, theObjectClass);
}
