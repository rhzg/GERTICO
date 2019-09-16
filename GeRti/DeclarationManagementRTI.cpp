/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** DeclarationManagementRTI.cpp
**
*******************************************************************************/

#include "DeclarationManagementRTI.h"
#include "EventMarket/Jobs.h"
#include "Util/Mapper.h"
#include <iostream>
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::DeclarationManagementRTI::DeclarationManagementRTI(GERTICO::ObjectManagement &theObjectManagement, GERTICO::GeRtiOwnershipMasterI &theGeRtiOwnershipMasterI, GERTICO::RunTimeObjectDB &theRunTimeObjectDB, GERTICO::ClassDescrHolder &theInteractionRoot, GERTICO::FederatesHolder &theFederatesHolder, GERTICO::JobHolder &theFederationJobs, ACE_Thread_Mutex &thePm) : pm(thePm), interactionRoot(theInteractionRoot), federatesHolder(theFederatesHolder), federationJobs(theFederationJobs), objectManagement(theObjectManagement), ownershipMaster(theGeRtiOwnershipMasterI), runTimeObjectDB(theRunTimeObjectDB)
{
  // Get privilege to delete id.
  privilegeToDeleteId = runTimeObjectDB.getPrivilegeToDeleteId();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::DeclarationManagementRTI::~DeclarationManagementRTI(void)
{
}

// ---------------------------------------------------------------------------
// For all objects below this object class level.
// Find any objects which may generate events and
// send a discover object to this federate.
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementRTI::addDiscoverObjects(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClassId, GERTICO::HandleSet const &theAttributeList)
{
  GERTICO::Federate *myFed;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet objects;
  GERTICO::HandleSet::iterator itFederate;
  GERTICO::HandleSet::iterator ito;
  GERTICO::RegisteredObject *currObject;

  std::wstring oName;

  // Get the federate attributes for this fed.
  myFed = federatesHolder.getFederate(theFederate);
  if (myFed == NULL)
  {
    return;
  }

  // Get all objects for this class.
  runTimeObjectDB.getObjectIdsForClass(theClassId, objects);
  for (ito = objects.begin (); ito != objects.end (); ito++)
  {
    // Already know the object.
    if (myFed->knowObject (*ito))
    {
      continue;
    }

    // Get the object
    currObject = runTimeObjectDB.getObject (*ito);
    if (currObject)
    {
      currObject->getName (oName);
    }

    // Do not discover unowned objects testcase 6113
    if (objectManagement.checkUnowned(*currObject, theAttributeList))
    {
      continue;
    }

    // Test if the federate has a subscription at a lower level.
    // If yes, do not do discover!!
    // see testcase 6223
    if (testFederateLowerSubscription(*myFed, currObject->getClassId(), theClassId))
    {
      continue;
    }

    if (addFederateDiscoverObject(theFederate, *myFed, 1, theClassId, *ito, oName))
    {
      continue;
    }

    // Fed does not know object, check if any attributes are published by another federate.
    federatesHolder.getFederates(federates);
    for (itFederate = federates.begin(); itFederate != federates.end(); itFederate++)
    {
      // Do not take this federate.
      if (*itFederate == theFederate)
      {
        continue;
      }

      if (addFederateDiscoverObject(theFederate, *myFed, *itFederate, theClassId, *ito, oName))
      {
        break;
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::DeclarationManagementRTI::addFederateDiscoverObject(const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::Federate &theMyFederate, const GeRtiFactory::GeRtiHandle &theOtherFederate, const GeRtiFactory::GeRtiHandle &theClassId, const GeRtiFactory::GeRtiHandle &theObject, const std::wstring &theObjectName)
{
  GERTICO::DiscoverObjectJob *newDiscoverObject;
  GERTICO::HandleSet attributes;

  // Use only if some attribute(s) found.
  runTimeObjectDB.getOwnedObjectAttributes(theObject, theOtherFederate, attributes, false);
  if (attributes.size() == 1)
  {
    GERTICO::HandleSet::iterator itHS;
    bool gotPrivilegeToDeleteId = false;

    for (itHS = attributes.begin (); itHS != attributes.end (); itHS++)
    {
      if (runTimeObjectDB.isPrivilegeToDeleteId(*itHS))
      {
        gotPrivilegeToDeleteId = true;
      }
    }
    if (gotPrivilegeToDeleteId)
    {
      return false;
    }
  }
  if (attributes.size())
  {
    // NB. use the class id known to the subscriber!
    newDiscoverObject = new GERTICO::DiscoverObjectJob(theClassId, theFederate, theObject, federatesHolder, theObjectName);
    federationJobs.add(newDiscoverObject);
    theMyFederate.addKnownObject(theObject, theClassId, attributes);

    // Next object.
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementRTI::delFedInteractions (const GeRtiFactory::GeRtiHandle &theFederate, HandleSet &pubObjects, HandleSetMap &subObjectsMap)
{
  GERTICO::HandleSet *currHandleSet;
  GERTICO::HandleSet::iterator itHS;
  HandleSetMap currHandleSetMap;
  HandleSetMap::iterator itFI;

  // For each object class delete federate information.
  for (itHS = pubObjects.begin (); itHS != pubObjects.end (); itHS++)
  {
    try
    {
      unpublishObjectClass (theFederate, *itHS);
    }
    catch(...)
    {
      continue;
    }
  }

  // Get list of subscriber object classes per federate.
  for (itFI = subObjectsMap.begin (); itFI != subObjectsMap.end (); itFI++)
  {
    currHandleSet = &itFI->second;
    for (itHS = currHandleSet->begin (); itHS != currHandleSet->end (); itHS++)
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
//
// ---------------------------------------------------------------------------
GERTICO::ClassDescr *GERTICO::DeclarationManagementRTI::getInteractionClassDescr (const GeRtiFactory::GeRtiHandle &theClass)
{
  GERTICO::ClassDescr *ret;

  ret = interactionRoot.getClassDescr(theClass);

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementRTI::getInteractionRoutingSpaceHandle (const GeRtiFactory::GeRtiHandle &theClass, GeRtiFactory::GeRtiHandle &theSpace, bool &theClassFound)
{
  interactionRoot.getRoutingSpaceHandle(theClass, theSpace, theClassFound);
}

// ---------------------------------------------------------------------------
// For the given object class check if there are any active subscribers
// in given or in base classes.
// ---------------------------------------------------------------------------
/*
void GERTICO::DeclarationManagementRTI::objectClassPubStartRegistration(GERTICO::Federate &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSet &theAttributes)
{
  GERTICO::ClassDescr *currClassDescr;
//  StJob *newStJob;
  bool started;

  started = theFederate.getStarted(theObjectClass);

  // Get current class from object class tree.
  currClassDescr = runTimeObjectDB.getObjectClassDescr(theObjectClass);

  // Take class and any parents of class.
  while (currClassDescr)
  {
    try
    {
      if (runTimeObjectDB.checkActiveObjectClassSubscribers(theFederate.getId(), currClassDescr->getId(), theAttributes))
      {
        // Turn the fed on and leave.
        if (theFederate.getStarted(theObjectClass) == false)
        {
//          newStJob = new StJob(theFederate.getId(), theObjectClass, true, federatesHolder);
//          federationJobs.add(newStJob);
        }
        return;
      }
    }
    catch(GeRtiFactory::ObjectClassNotPublished &)
    {
    }

    // Try subscribers at a higher level.
    currClassDescr = currClassDescr->parent;
  }

  // No active subscriber found.
  // Turn off publisher.
  if (started == true)
  {
//    newStJob = new StJob(theFederate.getId(), theObjectClass, false, federatesHolder);
//    federationJobs.add(newStJob);
  }
}
*/

// ---------------------------------------------------------------------------
// Recursive function to get publishers in all derived classes and start
// registration for object classes.
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementRTI::objectClassSubStartRegistration(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theAttributes, const GeRtiFactory::GeRtiHandle &theObjectClass)
{
  GERTICO::ClassDescrMap::iterator itCD;
  GERTICO::ClassDescr *currClassDescr;
  GERTICO::ClassDescr *theClassDescr;
  GERTICO::HandleSet::iterator itHS;
  GERTICO::HandleSet publishers;
  PublishedClass *currPublishedClass;
//  StJob *newStJob;
//  unsigned long cla;
//  unsigned long fed;

  // Check this level, if found
  currPublishedClass = runTimeObjectDB.getPublishedClass(theObjectClass);
  if (currPublishedClass)
  {
//    currPublishedClass->startRegistration(theFederate, theAttributes, publishers, federatesHolder);
//    for (itHS = publishers.begin(); itHS != publishers.end(); itHS++)
//    {
//      fed = *itHS;
//      cla = currPublishedClass->getId();
//      newStJob = new StJob(*itHS, currPublishedClass->getId(), true, federatesHolder);
//      federationJobs.add(newStJob);
//    }
  }

  // Check children of class.
  theClassDescr = runTimeObjectDB.getObjectClassDescr(theObjectClass);
  for (itCD = theClassDescr->classDescrs.begin(); itCD != theClassDescr->classDescrs.end(); itCD++)
  {
    currClassDescr = itCD->second;
    objectClassSubStartRegistration(theFederate, theAttributes, currClassDescr->getId());
  }
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementRTI::publishObjectClass (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSet &theAttributes)
{
  GERTICO::Federate *currFederate;
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet objects;
  GERTICO::HandleSet unpubAttributes;
  GERTICO::HandleSet::iterator itAttribute;
  GERTICO::HandleSet::iterator itTheAttribute;
  GERTICO::HandleSet::iterator itObject;
  GeRtiFactory::GeRtiHandle privilegeToDeleteId;

  privilegeToDeleteId = runTimeObjectDB.getPrivilegeToDeleteId();

  // Get any old published attributes.
  try
  {
    runTimeObjectDB.getPublishedAttributes(theFederate, theObjectClass, attributes);
  }
  catch(...)
  {
  }

//#ifndef IEEE_1516
  // Check if any become unpublished.
  for (itAttribute = attributes.begin(); itAttribute != attributes.end(); itAttribute++)
  {
    if (*itAttribute == privilegeToDeleteId)
    {
      continue;
    }

    itTheAttribute = theAttributes.find(*itAttribute);
    if (itTheAttribute == theAttributes.end())
    {
      unpubAttributes.insert(*itAttribute);
    }
  }

  // Check if another federate wants ownership.
  if (theFederate != 1)
  {
    if (unpubAttributes.size())
    {
      ownershipMaster.processUnpublishOwnershipCandidate(theFederate, theObjectClass, unpubAttributes);
    }
  }
//#endif

  pm.acquire ();
  try
  {
    runTimeObjectDB.publishObjectClass (theFederate, theObjectClass, theAttributes);

    // Add to federate.
    currFederate = federatesHolder.getFederate(theFederate);
    if (currFederate)
    {
      currFederate->publishObjectClass (theObjectClass, theAttributes);
      currFederate->setAlive();

      // Require logic to start registration for object class.
//      objectClassPubStartRegistration(*currFederate, theObjectClass, theAttributes);
    }
  }
  catch (...)
  {
    pm.release ();
    throw;
  }

  pm.release ();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementRTI::restore (DOMElement &theDOMElement)
{
  GERTICO::ClassDescr *classDescr;
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
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode ("interaction")) == 0)
      {
        tmpChar = XMLString::transcode (((DOMElement*)child)->getAttribute (XMLString::transcode ("id")));
        sscanf (tmpChar, "%lu", &tmpUL);
        classDescr = interactionRoot.getClassDescr(tmpUL);
        if (classDescr)
        {
          classDescr->getOrdering(ordering);
          classDescr->getTransportation(transportation);
        }
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
void GERTICO::DeclarationManagementRTI::save (DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
//  interactionHolder.save(theDOMDocument, theDOMElement);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementRTI::subscribeInteractionClass (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theInteraction, const CORBA::Boolean &theActive, const GERTICO::HandleSet &theRegions)
{
  CORBA::WChar *wChar = L"";
  GERTICO::ClassDescr *classDescr;
  GERTICO::HandleSet::const_iterator itHandleSet;
  GERTICO::Region *region;
  unsigned long interactionSpace = 0;
  unsigned long regionSpace = 0;

#ifdef IEEE_1516
  // Atomic test.
//  interactionHolder.testRegionDimensions(theInteraction, theRegions);
#endif

  // Get class information.
  classDescr = interactionRoot.getClassDescr(theInteraction);
  if (classDescr == NULL)
  {
    throw GeRtiFactory::InteractionClassNotDefined(wChar);
  }

  if (theActive != 0 && theActive != 1)
  {
    throw GeRtiFactory::RTIinternalError(L"invalid active boolean");
  }

  pm.acquire ();
  // Check region space and fed file space.
  for (itHandleSet = theRegions.begin(); itHandleSet != theRegions.end(); itHandleSet++)
  {
    if (*itHandleSet)
    {
      region = runTimeObjectDB.getRegion(*itHandleSet);
      if (region)
      {
        regionSpace = region->getSpace();
      }
      classDescr->getInteractionSpaceHandle(interactionSpace);
      if (regionSpace != interactionSpace)
      {
        pm.release ();
        throw GeRtiFactory::InvalidRegionContext(wChar);
      }
    }
  }
  pm.release ();

  // Check if interactions already administered.
//  interactionHolder.subscribeInteractionClass(theFederate, theInteraction, theActive, theRegions);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementRTI::subscribeObjectClassAttributes(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSet &theAttributes, const CORBA::Boolean &theActive)
{
  CORBA::WChar *wChar = L"";
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *currFederate;
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet feds;
  GERTICO::HandleSet objects;
  GERTICO::HandleSet::iterator itAttribute;
  GERTICO::HandleSet::iterator itFed;
  GERTICO::HandleSet::iterator ita;
  GERTICO::HandleSet::iterator ito;

  classDescr = runTimeObjectDB.getObjectClassDescr(theObjectClass);
  if (classDescr == NULL)
  {
    throw GeRtiFactory::ObjectClassNotDefined(wChar);
  }

  if (theActive != 0 && theActive != 1)
  {
    throw GeRtiFactory::RTIinternalError(L"invalid active boolean");
  }

  pm.acquire ();

  try
  {
    runTimeObjectDB.subscribeObjectClassAttributes(theFederate, theObjectClass, theAttributes, theActive);
  }
  catch (...)
  {
    pm.release ();
    throw;
  }

  // Find federate attribute entry.
  currFederate = federatesHolder.getFederate(theFederate);
  if (currFederate == NULL)
  {
    pm.release ();
    return;
  }

  // Add to federate.
  currFederate->addSubscribeObjectClass(theObjectClass, theAttributes, theActive);
  currFederate->setAlive();

//  if (theActive)
//  {
//    // Logic to start registration for object class.
//    objectClassSubStartRegistration (theFederate, theAttributes, theObjectClass);
//  }
currFederate->print();
  // Discover any objects on this or lower levels.
  addDiscoverObjects(theFederate, theObjectClass, theAttributes);
currFederate->print();

  // Do any scope messages.
  objectManagement.doScope(theFederate, theObjectClass, theAttributes);
currFederate->print();

  if (theActive)
  {
    runTimeObjectDB.getObjectIdsForClass (theObjectClass, objects);

    // Turn on publishers who are not publishing.
    for (ito = objects.begin (); ito != objects.end (); ito++)
    {
      federatesHolder.getFederates(feds);
      for (itFed = feds.begin (); itFed != feds.end (); itFed++)
      {
        runTimeObjectDB.getOwnedObjectAttributes (*ito, *itFed, attributes, false);
        currFederate = federatesHolder.getFederate(*itFed);
        for (itAttribute = theAttributes.begin(); itAttribute != theAttributes.end(); itAttribute++)
        {
          ita = attributes.find (*itAttribute);
          if (ita != attributes.end ())
          {
            pm.release ();
            objectManagement.doTurnOnForObjectInstance(*ito, currFederate->getId (), attributes, true);
            pm.acquire ();
            break;
          }
        }
      }
    }
  }

  objectManagement.doTurnOffForObjectClass(theFederate, theObjectClass);

  // Logic to stop registration for object class.
//  objectClassSubStopRegistration (theFederate, theObjectClass);

  pm.release ();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::DeclarationManagementRTI::testFederateLowerSubscription(GERTICO::Federate &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, const GeRtiFactory::GeRtiHandle &theSubscribedClass)
{
  GERTICO::ClassDescr *classDescr;

  for (classDescr = runTimeObjectDB.getObjectClassDescr(theObjectClass); classDescr->getId() != theSubscribedClass; classDescr = classDescr->parent)
  {
    if (theFederate.isSubscribedToObjectClass(classDescr->getId()))
    {
      return true;
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementRTI::unpublishObjectClass (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass)
{
  CORBA::WChar *wChar = L"";
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *currFederate;
  GERTICO::HandleSet unpubAttributes;

  classDescr = runTimeObjectDB.getObjectClassDescr(theObjectClass);
  if (classDescr == NULL)
  {
    throw GeRtiFactory::ObjectClassNotDefined(wChar);
  }

  // Get any old published attributes.
  try
  {
    runTimeObjectDB.getPublishedAttributes(theFederate, theObjectClass, unpubAttributes);
  }
  catch(...)
  {
  }

  // Check if another federate wants ownership.
  if (theFederate != 1)
  {
    if (unpubAttributes.size())
    {
      ownershipMaster.processUnpublishOwnershipCandidate(theFederate, theObjectClass, unpubAttributes);
    }
  }

  runTimeObjectDB.unpublishObjectClass(theFederate, theObjectClass);

  // Delete from federate.
  currFederate = federatesHolder.getFederate(theFederate);
  if (currFederate)
  {
    currFederate->delObjectClassRegionPub (theObjectClass);
    currFederate->setAlive();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementRTI::unpublishObjectClassAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet const &attributeSet)
{
  // XXX
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementRTI::unsubscribeInteractionClass (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theInteraction, const GERTICO::HandleSet &theRegions)
{
  CORBA::WChar *wChar = L"";
  GERTICO::ClassDescr *classDescr;
  GERTICO::HandleMap publishers;
  GERTICO::HandleSet::const_iterator itHandleSet;

  classDescr = interactionRoot.getClassDescr(theInteraction);
  if (classDescr == NULL)
  {
    throw GeRtiFactory::InteractionClassNotDefined(wChar);
  }

  pm.acquire ();
  try
  {
    for (itHandleSet = theRegions.begin(); itHandleSet != theRegions.end(); itHandleSet++)
    {
//      interactionHolder.unsubscribeInteractionClass(theFederate, theInteraction, *itHandleSet);
    }
  }
  catch(GeRtiFactory::RegionNotKnown &)
  {
    pm.release();
    // Testcase 9-7-13.
    throw GeRtiFactory::InteractionClassNotSubscribed(wChar);
  }
  catch(...)
  {
    pm.release ();
    throw;
  }
  pm.release ();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementRTI::unsubscribeObjectClass (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, const GERTICO::HandleSet &theAttributes)
{
  CORBA::WChar *wChar = L"";
  GERTICO::ClassDescr *classDescr;

  classDescr = runTimeObjectDB.getObjectClassDescr(theObjectClass);
  if (classDescr == NULL)
  {
    throw GeRtiFactory::ObjectClassNotDefined(L"unsubscribeObjectClass");
  }

  pm.acquire ();
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

  pm.release ();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementRTI::unsubscribeObjectClassPrivate (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, const GeRtiFactory::GeRtiHandle &theRegion)
{
  GERTICO::Federate *currFederate;
  GERTICO::HandleSet regions;

  // Delete from federate.
  currFederate = federatesHolder.getFederate(theFederate);
  if (currFederate)
  {
    currFederate->delObjectClassSub(theObjectClass);
    currFederate->setAlive();
  }

  regions.insert(theRegion);
  runTimeObjectDB.unsubscribeObjectClass(theFederate, theObjectClass, regions);

  objectManagement.doScopeSubscribe(theFederate, theObjectClass, false);

  objectManagement.doTurnOffForObjectClass(theFederate, theObjectClass);
  // Logic to stop registration for object class.
//  objectClassSubStopRegistration(theFederate, theObjectClass);
}
