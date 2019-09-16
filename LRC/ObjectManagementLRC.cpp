/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** ObjectManagementLRC.cpp
**
*******************************************************************************/

#include "ObjectManagementLRC.h"
#include "Util/Mapper.h"

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjectManagementLRC::ObjectManagementLRC(GeRtiFactory::GeRtiAmbassador_var &theGeRtiAmbassador_var, GeRtiFactory::GeRtiHandle &theFederate, GERTICO::RegisteredObjectsHolder &theRegisteredObjectsHolder, GERTICO::RunTimeObjectDB &theRunTimeObjectDB, GERTICO::SupportingServicesLRC &theSupportingServicesLRC) : registeredObjectsHolder(theRegisteredObjectsHolder), runTimeObjectDB(theRunTimeObjectDB), supportingServicesLRC(theSupportingServicesLRC)
{
  GeRtiAmbVar = GeRtiFactory::GeRtiAmbassador::_duplicate(theGeRtiAmbassador_var);
  federate = theFederate;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjectManagementLRC::~ObjectManagementLRC(void)
{
  pm.acquire();
  classObjectsSet.clear();
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagementLRC::addClassObjectsSet(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theObject)
{
  GERTICO::HandleSetMap::iterator itHSM;

  pm.acquire();
  itHSM = classObjectsSet.find(theClass);
  if (itHSM != classObjectsSet.end())
  {
    itHSM->second.insert(theObject);
  }
  else
  {
    GERTICO::HandleSet objectSet;
    objectSet.insert(theObject);
    classObjectsSet[theClass] = objectSet;
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagementLRC::changeAttributeOrderType(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes, GeRtiFactory::GeRtiHandle const &theType)
{
  GERTICO::RegisteredObject *registeredObject;

  registeredObject = registeredObjectsHolder.getObject(theObject);
  registeredObject->changeAttributeOrderType(theAttributes, theType);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagementLRC::changeAttributeTransportationType(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes, GeRtiFactory::GeRtiHandle const &theType)
{
  GERTICO::RegisteredObject *registeredObject;

  registeredObject = registeredObjectsHolder.getObject(theObject);
  registeredObject->changeAttributeTransportationType(theAttributes, theType);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagementLRC::changeInteractionOrderType(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theType)
{
  GERTICO::HandleMap::iterator itHandleMap;

  itHandleMap = interactionOrderTypeMap.find(theClass);
  if (itHandleMap != interactionOrderTypeMap.end())
  {
    itHandleMap->second = theType;
  }
  else
  {
    interactionOrderTypeMap[theClass] = theType;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagementLRC::changeInteractionTransportationType(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theType)
{
  GERTICO::HandleMap::iterator itHandleMap;

  itHandleMap = interactionTransportationTypeMap.find(theClass);
  if (itHandleMap != interactionTransportationTypeMap.end())
  {
    itHandleMap->second = theType;
  }
  else
  {
    interactionTransportationTypeMap[theClass] = theType;
  }
}

// ---------------------------------------------------------------------------
// Check the first three characters (lower case) of the name whether they are
// "hla" 
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagementLRC::checkHLA(std::wstring const &theName)
{
  CORBA::WChar *wChar = L"";
  std::wstring buf(theName);

#ifdef IEEE_1516
  if (buf[0] == 'H' && buf[1] == 'L' && buf[2] == 'A')
  {
    throw GeRtiFactory::RTIinternalError(wChar);
  }
#else
  GERTICO::Mapper::nameToLower(buf);
  if (buf[0] == 'h' && buf[1] == 'l' && buf[2] == 'a')
  {
    throw GeRtiFactory::ObjectAlreadyRegistered(wChar);
  }
#endif
}

// ---------------------------------------------------------------------------
// Delete local administration information.
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagementLRC::deleteObject(GeRtiFactory::GeRtiHandle const &theObject)
{
  GERTICO::RegisteredObject *currObject;
  GeRtiFactory::GeRtiHandle classId;

  currObject = registeredObjectsHolder.getObject(theObject);
  classId = currObject->getClassId();

  deleteClassObjectsSet(classId, theObject);

  runTimeObjectDB.deleteObjectInstance(theObject, federate);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagementLRC::deleteClassObjectsSet(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theObject)
{
  GERTICO::HandleSet *objectSet;
  GERTICO::HandleSet::iterator itO;
  GERTICO::HandleSetMap::iterator itHSM;

  pm.acquire();
  itHSM = classObjectsSet.find(theClass);
  if (itHSM != classObjectsSet.end())
  {
    objectSet = &itHSM->second;
    itO = objectSet->find(theObject);
    if (itO != objectSet->end())
    {
      objectSet->erase(itO);
    }
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagementLRC::deleteObjectInstance(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Time &theTime, GeRtiFactory::UserSuppliedTag const &theTag, GeRtiFactory::GeRtiHandle const &theSerialNumber)
{
  // Do not remove object from run time object db now!
  GeRtiAmbVar->deleteObjectInstanceWithTime(theObject, theTime, theTag, theSerialNumber);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagementLRC::deleteObjectInstance(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::UserSuppliedTag const &theTag)
{
  deleteObject(theObject);

  GeRtiAmbVar->deleteObjectInstance(theObject, theTag);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagementLRC::discoverObjectInstance(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theClass, std::wstring const &theObjectName)
{
  GERTICO::AttributeDatumMap attributeDatumMap;
  GERTICO::HandleSet attributeSet;
  GERTICO::RegisteredObject *objectPtr;

  // Get full set of attributes.
  supportingServicesLRC.getObjectClassAttributeDataMap(theClass, attributeDatumMap);

  // Create and register the object.
  objectPtr = new GERTICO::RegisteredObject(0, theClass, theObject, theObjectName, attributeSet, attributeDatumMap);
  registeredObjectsHolder.addObject(theObject, objectPtr, theObjectName);
//  registeredObjectsHolder.discoverObject(theObject, theClass, theObjectName);

  addClassObjectsSet(theClass, theObject);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::ObjectManagementLRC::getObjectClass(GeRtiFactory::GeRtiHandle const &theObject)
{
  GERTICO::RegisteredObject *currObject;

  currObject = registeredObjectsHolder.getObject(theObject);
  return currObject->getClassId();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RegisteredObject *GERTICO::ObjectManagementLRC::getObject(GeRtiFactory::GeRtiHandle const &theObject)
{
  GERTICO::RegisteredObject *ret;

  ret = registeredObjectsHolder.getObject(theObject);

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RegisteredObject *GERTICO::ObjectManagementLRC::getObjectByName(std::wstring const &theObjectName)
{
  GERTICO::RegisteredObject *ret;

  ret = registeredObjectsHolder.getObjectByName(theObjectName);

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagementLRC::getObjectsForClass(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSet &theObjects)
{
  GERTICO::HandleSetMap::iterator itHSM;

  pm.acquire();
  itHSM = classObjectsSet.find(theClass);
  if (itHSM != classObjectsSet.end())
  {
    theObjects = itHSM->second;
  }
  pm.release();
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagementLRC::loadObjectAttInfoMap(const GeRtiFactory::GeRtiHandle &theObjectId, const std::wstring &theObjectName, const GeRtiFactory::GeRtiHandle &theClass, AttInfoMap &theAttInfoMap)
{
  ObjectMap::iterator itO;
  GERTICO::RegisteredObject *registeredObject;

  // Get rid of any previous entry.
  registeredObjectsHolder.delObject(theObjectId);

  registeredObject = new GERTICO::RegisteredObject (theClass, theObjectId, theObjectName);
  registeredObject->loadAttInfoMap (theAttInfoMap);
  registeredObjectsHolder.addObject(theObjectId, registeredObject, theObjectName);
}

    
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagementLRC::localDeleteObjectInstance(GeRtiFactory::GeRtiHandle theObject, GeRtiFactory::GeRtiHandle theFederate)
{
  GeRtiFactory::GeRtiHandle myClass;
  GERTICO::PublishedClass *publishedClass;

  GeRtiAmbVar->localDeleteObjectInstance(theObject);

  // remove object with all registered attributes
  try
  {
    GERTICO::RegisteredObject* obj = registeredObjectsHolder.getObject(theObject);
    // remove object 
    myClass = obj->getClassId();
    registeredObjectsHolder.delObject(theObject);
    publishedClass = runTimeObjectDB.getPublishedClass(myClass);
    if (publishedClass)
    {
      publishedClass->delObject(theObject);
    }
  }
  catch(GeRtiFactory::ObjectNotKnown &)
  {
  }

  deleteClassObjectsSet(myClass, theObject);
}

// ---------------------------------------------------------------------------
// register a object with a default set of attributes - local administration.
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagementLRC::registerObject(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theClass, std::wstring const &theObjectName)
{
  CORBA::WChar *wChar = L"";
  GERTICO::AttributeDatumMap attributeDatumMap;
  GERTICO::HandleSet attributeSet;
  GERTICO::PublishedClass *currPublishedClass;
  GERTICO::RegisteredObject *objectPtr;

  // Names are unique, duplicates are not allowed.
  objectPtr = registeredObjectsHolder.getObjectByName(theObjectName);
  if (objectPtr)
  {
    throw GeRtiFactory::ObjectAlreadyRegistered(wChar);
  }

  // Get set of attributes that are published.
  runTimeObjectDB.getPublishedAttributes(theFederate, theClass, attributeSet);

  // Get full set of attributes.
  supportingServicesLRC.getObjectClassAttributeDataMap(theClass, attributeDatumMap);

  // Create and register the object.
  objectPtr = new GERTICO::RegisteredObject(theFederate, theClass, theObject, theObjectName, attributeSet, attributeDatumMap);
  registeredObjectsHolder.addObject(theObject, objectPtr, theObjectName);
  currPublishedClass = runTimeObjectDB.getPublishedClass(theClass);
  if (currPublishedClass)
  {
    currPublishedClass->addObject(theObject);
  }
  else
  {
    throw GeRtiFactory::ObjectClassNotPublished(L"registerObject");
  }

  addClassObjectsSet(theClass, theObject);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::ObjectManagementLRC::registerObjectInstance(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, std::wstring const &theObjectName)
{
  CORBA::WChar *objName;
  GeRtiFactory::GeRtiHandle theObject = 0;
  std::wstring objectName(theObjectName);

  checkHLA(objectName);
  GERTICO::Mapper::mapWcharFromWstring(&objName, objectName);
  theObject = GeRtiAmbVar->registerObjectInstanceWithName(theClass, objName);
  CORBA::wstring_free(objName);

  registerObject(theFederate, theObject, theClass, objectName);

  return theObject;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::ObjectManagementLRC::registerObjectInstance(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass)
{
  GeRtiFactory::GeRtiHandle theObject = 0;
  char name[64];
  std::wstring s;

  theObject = GeRtiAmbVar->registerObjectInstance(theClass);

  sprintf(name, "HLA%lu", theObject);
  GERTICO::Mapper::mapWstringFromChar(s, name);
  registerObject(theFederate, theObject, theClass, s);

  return theObject;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::ObjectManagementLRC::registerObjectInstanceWithRegion(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, std::wstring const &theObjectName, GERTICO::HandleSetMap &theAttRegMap)
{
  CORBA::WChar *objName;
  GeRtiFactory::AttributeRegionsSeq attributeRegionsSeq;
  GeRtiFactory::GeRtiHandle theObject = 0;
  std::wstring objectName(theObjectName);

  checkHLA(objectName);

  GERTICO::Mapper::mapWcharFromWstring(&objName, objectName);
  GERTICO::Mapper::mapAttributeRegionsSeqFromHandleSetMap(attributeRegionsSeq, theAttRegMap);
  theObject = GeRtiAmbVar->registerObjectInstanceWithNameWithRegions(theClass, attributeRegionsSeq, objName);
  CORBA::wstring_free(objName);
  registerObject(theFederate, theObject, theClass, objectName);

  return theObject;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::ObjectManagementLRC::registerObjectInstanceWithRegion(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSetMap &theAttRegMap)
{
  GeRtiFactory::AttributeRegionsSeq attributeRegionsSeq;
  GeRtiFactory::GeRtiHandle theObject = 0;
  char name[64];
  std::wstring s;

  GERTICO::Mapper::mapAttributeRegionsSeqFromHandleSetMap(attributeRegionsSeq, theAttRegMap);
  theObject = GeRtiAmbVar->registerObjectInstanceWithRegions(theClass, attributeRegionsSeq);
  sprintf(name, "HLA%lu", theObject);
  GERTICO::Mapper::mapWstringFromChar(s, name);
  registerObject(theFederate, theObject, theClass, s);

  return theObject;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagementLRC::requestClassAttributeValueUpdate(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &theAttributes, GeRtiFactory::UserSuppliedTag const &theTag)
{
  GeRtiAmbVar->requestClassAttributeValueUpdate(theClass, theAttributes, theTag);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagementLRC::requestObjectAttributeValueUpdate(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes, GeRtiFactory::UserSuppliedTag const &theTag)
{
  GeRtiAmbVar->requestObjectAttributeValueUpdate(theObject, theAttributes, theTag);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagementLRC::reserveObjectInstanceName(std::wstring const &theObjectInstanceName)
{
  CORBA::WChar *objName;

  checkHLA(theObjectInstanceName);
  GERTICO::Mapper::mapWcharFromWstring(&objName, theObjectInstanceName);
  GeRtiAmbVar->reserveObjectInstanceName(objName);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagementLRC::reset(void)
{
  turnOnUpdatesDB.clear();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagementLRC::setAttributeData(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::HandleValues &theAttributes)
{
  CORBA::ULong i;
  CORBA::ULong length;
  GERTICO::AttributeInfo *attributeInfo;
  GERTICO::HandleSetMap::iterator itHandleSetMap;
  GERTICO::HandleSetSetMap::iterator itHandleSetSetMap;
  GERTICO::RegisteredObject *registeredObject;

  registeredObject = getObject(theObject);
  length = theAttributes.length();

  itHandleSetSetMap = turnOnUpdatesDB.find(theObject);
  if (itHandleSetSetMap != turnOnUpdatesDB.end())
  {
    for (i = 0; i < length; i++)
    {
      itHandleSetMap = itHandleSetSetMap->second.find(theAttributes[i].id);
      if (itHandleSetMap != itHandleSetSetMap->second.end())
      {
        attributeInfo = registeredObject->getAttribute(theAttributes[i].id);
        theAttributes[i].timestampOrder = attributeInfo->getOrderType();
        theAttributes[i].bestEffort = attributeInfo->getTransportationType();
        GERTICO::Mapper::mapHandleSet(theAttributes[i].theSubscribers, itHandleSetMap->second);
      }
    }
  }
}
/*
  len = theAttributes.length();
  for (i = 0; i < len; i++)
  {
    if (federateDB.ownership->isAttributeOwnedByFederate(theObject, theAttributes[i].id) == false)
    {
      throw GeRtiFactory::AttributeNotOwned(wChar);
    }
  }

*/

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagementLRC::turnUpdatesOffForObjectInstance(GeRtiFactory::GeRtiHandle const &theObject, GERTICO::HandleSetMap const &theAttributeSubscribers, GeRtiFactory::Handles &theUserAttributes)
{
  CORBA::ULong ind = 0;
  CORBA::ULong length;
  GERTICO::HandleSet::const_iterator itSubscriberIn;
  GERTICO::HandleSet::iterator itSubscriberDB;
  GERTICO::HandleSetMap::const_iterator itAttributeIn;
  GERTICO::HandleSetMap::iterator itAttributeDB;
  GERTICO::HandleSetSetMap::iterator itObjectDB;
  size_t size;

  size = theAttributeSubscribers.size();
  GERTICO::Mapper::mapULongSizet(length, size);
  theUserAttributes.length(length);
  theUserAttributes.length(0);

  // Find the object.
  itObjectDB = turnOnUpdatesDB.find(theObject);
  if (itObjectDB != turnOnUpdatesDB.end())
  {
    GERTICO::HandleSetMap *attributeSubscriberMapDB;
    attributeSubscriberMapDB = &itObjectDB->second;
    // Loop over incoming <attributes, subscribers> map.
    for (itAttributeIn = theAttributeSubscribers.begin(); itAttributeIn != theAttributeSubscribers.end(); itAttributeIn++)
    {
      // Get attribute from database.
      itAttributeDB = attributeSubscriberMapDB->find(itAttributeIn->first);
      if (itAttributeDB != attributeSubscriberMapDB->end())
      {
        GERTICO::HandleSet *subscriberSetDB;
        subscriberSetDB = &itAttributeDB->second;
        // Loop over incoming <subscriber> set.
        for (itSubscriberIn = itAttributeIn->second.begin(); itSubscriberIn != itAttributeIn->second.end(); itSubscriberIn++)
        {
          itSubscriberDB = subscriberSetDB->find(*itSubscriberIn);
          if (itSubscriberDB != subscriberSetDB->end())
          {
            subscriberSetDB->erase(itSubscriberDB);
          }
        }
        if (subscriberSetDB->size() == 0)
        {
          // No subscribers left, delete attribute..
          theUserAttributes.length(ind + 1);
          theUserAttributes[ind] = itAttributeIn->first;
          ind = ind++;
        }
      }
    }
    if (attributeSubscriberMapDB->size() == 0)
    {
      turnOnUpdatesDB.erase(itObjectDB);
    }
  }
  else
  {
    // No object found.
    return;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagementLRC::turnUpdatesOnForObjectInstance(GeRtiFactory::GeRtiHandle const &theObject, GERTICO::HandleSetMap const &theAttributeSubscribers, GeRtiFactory::Handles &theUserAttributes)
{
  CORBA::ULong ind = 0;
  CORBA::ULong length;
  GERTICO::HandleSet::const_iterator itSubscriberIn;
  GERTICO::HandleSet::iterator itSubscriberDB;
  GERTICO::HandleSetMap::const_iterator itAttributeIn;
  GERTICO::HandleSetMap::iterator itAttributeDB;
  GERTICO::HandleSetSetMap::iterator itObjectDB;
  size_t size;

  size = theAttributeSubscribers.size();
  GERTICO::Mapper::mapULongSizet(length, size);
  theUserAttributes.length(length);
  theUserAttributes.length(0);

  // Make sure that an object is available.
  itObjectDB = turnOnUpdatesDB.find(theObject);
  if (itObjectDB == turnOnUpdatesDB.end())
  {
    GERTICO::HandleSetMap attributesDB;

    turnOnUpdatesDB[theObject] = attributesDB;
  }

  // Get the object.
  itObjectDB = turnOnUpdatesDB.find(theObject);
  if (itObjectDB != turnOnUpdatesDB.end())
  {
    GERTICO::HandleSetMap *attributeSubscriberMapDB;
    attributeSubscriberMapDB = &itObjectDB->second;
    // Loop over incoming <attributes, subscribers> map.
    for (itAttributeIn = theAttributeSubscribers.begin(); itAttributeIn != theAttributeSubscribers.end(); itAttributeIn++)
    {
      // Make sure that an attribute is available.
      itAttributeDB = attributeSubscriberMapDB->find(itAttributeIn->first);
      if (itAttributeDB == attributeSubscriberMapDB->end())
      {
        GERTICO::HandleSet subscribersDB;

        (*attributeSubscriberMapDB)[itAttributeIn->first] = subscribersDB;
        // The user will also need to know this attribute once: not for repeated calls with additional subscribers.
        theUserAttributes.length(ind + 1);
        theUserAttributes[ind] = itAttributeIn->first;
        ind += 1;
      }

      // Get attribute from database.
      itAttributeDB = attributeSubscriberMapDB->find(itAttributeIn->first);
      if (itAttributeDB != attributeSubscriberMapDB->end())
      {
        GERTICO::HandleSet *subscriberSetDB;
        subscriberSetDB = &itAttributeDB->second;
        // Loop over incoming <subscriber> set.
        for (itSubscriberIn = itAttributeIn->second.begin(); itSubscriberIn != itAttributeIn->second.end(); itSubscriberIn++)
        {
          itSubscriberDB = subscriberSetDB->find(*itSubscriberIn);
          if (itSubscriberDB == subscriberSetDB->end())
          {
            // Add subscriber to the database.
            subscriberSetDB->insert(*itSubscriberIn);
          }
        }
      }
    }
  }
}
