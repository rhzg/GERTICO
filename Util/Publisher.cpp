/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** RegisteredObject.cpp
**
*******************************************************************************/

#include "Util/Publisher.h"

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::PublishedClass::PublishedClass(GeRtiFactory::GeRtiHandle const &theClassId)
{
  myId = theClassId;
  sharingStatus = Neither;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::PublishedClass::~PublishedClass(void)
{
  GERTICO::FedPubAttributeMap::iterator itAM;

  for (itAM = fedPubAttributeMap.begin(); itAM != fedPubAttributeMap.end(); itAM = fedPubAttributeMap.begin())
  {
    fedPubAttributeMap.erase(itAM);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublishedClass::addObject(GeRtiFactory::GeRtiHandle const &theObject)
{
  HandleSet::iterator itH;

  itH = objects.find(theObject);
  if (itH == objects.end())
  {
    objects.insert(theObject);
  }
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublishedClass::addPubAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theAttributes)
{
  CORBA::ULong ul;
  GERTICO::PubAttributeDB *currPubAttributeDB;
  GERTICO::FedPubAttributeMap::iterator itAM;
  GERTICO::HandleSet attributesOld;
  GERTICO::HandleSet::iterator itA;
  GERTICO::HandleSet::iterator itHSi;
  GERTICO::HandleSet::iterator itHSo;

  itAM = fedPubAttributeMap.find(theFederate);
  if (itAM != fedPubAttributeMap.end())
  {
    currPubAttributeDB = &itAM->second;
  }
  else
  {
    currPubAttributeDB = new GERTICO::PubAttributeDB();
    fedPubAttributeMap[theFederate] = *currPubAttributeDB;
    delete currPubAttributeDB;
    currPubAttributeDB = NULL;
    itAM = fedPubAttributeMap.find(theFederate);
    if (itAM != fedPubAttributeMap.end())
    {
      currPubAttributeDB = &itAM->second;
    }
  }

  // Get the set of old published attributes.
  getFederatePubAttributes(theFederate, attributesOld);
  // Check if any attributes have been dropped.
  for (itHSo = attributesOld.begin(); itHSo != attributesOld.end(); itHSo++)
  {
    ul = *itHSo;
    itHSi = theAttributes.find(ul);
    if (itHSi == theAttributes.end())
    {
      itA = currPubAttributeDB->attributeSet.find(ul);
      if (itA != currPubAttributeDB->attributeSet.end())
      {
        currPubAttributeDB->attributeSet.erase(itA);
      }
    }
  }

  // Process the given attributes.
  for (itHSi = theAttributes.begin(); itHSi != theAttributes.end(); itHSi++)
  {
    currPubAttributeDB->attributeSet.insert(*itHSi);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublishedClass::checkPublishing(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::Handles const &theAttributes, GeRtiFactory::GeRtiHandle const &thePrivilegeToDeleteId)
{
  CORBA::ULong i;
  CORBA::ULong len;
  GERTICO::HandleSet::iterator itHS;
  PubAttributeDB *pubAttributeDB;
  FedPubAttributeMap::iterator itFPAM;

  itFPAM = fedPubAttributeMap.find(theFederate);
  if (itFPAM != fedPubAttributeMap.end())
  {
    pubAttributeDB = &itFPAM->second;
    len = theAttributes.length();
    for (i = 0; i < len; i++)
    {
      if (theAttributes[i] == thePrivilegeToDeleteId)
      {
        continue;
      }
      itHS = pubAttributeDB->attributeSet.find(theAttributes[i]);
      if (itHS == pubAttributeDB->attributeSet.end())
      {
        throw GeRtiFactory::AttributeNotPublished(L"checkPublishing");
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublishedClass::delObject(GeRtiFactory::GeRtiHandle const &theObject)
{
  HandleSet::iterator itH;

  itH = objects.find(theObject);
  if (itH != objects.end())
  {
    objects.erase(itH);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublishedClass::delPubAttributes(GeRtiFactory::GeRtiHandle const &theFederate)
{
  GERTICO::FedPubAttributeMap::iterator itAM;

  itAM = fedPubAttributeMap.find(theFederate);
  if (itAM != fedPubAttributeMap.end())
  {
    fedPubAttributeMap.erase(itAM);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublishedClass::delPubAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::Handles const &theAttributes)
{
  CORBA::ULong i;
  CORBA::ULong len;
  GERTICO::FedPubAttributeMap::iterator itAM;
  GERTICO::HandleSet::iterator itAttribute;
  GERTICO::PubAttributeDB *pubAttributeDB;

  itAM = fedPubAttributeMap.find(theFederate);
  if (itAM != fedPubAttributeMap.end())
  {
    pubAttributeDB = &itAM->second;
    len = theAttributes.length();
    for (i = 0; i < len; i++)
    {
      itAttribute = pubAttributeDB->attributeSet.find(theAttributes[i]);
      if (itAttribute != pubAttributeDB->attributeSet.end())
      {
        pubAttributeDB->attributeSet.erase(itAttribute);
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::PublishedClass::getId(void)
{
  return myId;
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublishedClass::getPublishInfo(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theAttributes)
{
  GERTICO::PubAttributeDB *currPubAttributeDB;
  GERTICO::FedPubAttributeMap::iterator itA;
  GERTICO::HandleSet::iterator itHS;
  unsigned long ul;

  itA = fedPubAttributeMap.find(theFederate);
  if (itA != fedPubAttributeMap.end())
  {
    currPubAttributeDB = &itA->second;
  }  
  else
  {
    throw GeRtiFactory::ObjectClassNotPublished(L"getPublishInfo");
  }

  for (itHS = currPubAttributeDB->attributeSet.begin(); itHS != currPubAttributeDB->attributeSet.end(); itHS++)
  {
    ul = *itHS;
    theAttributes.insert(*itHS);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublishedClass::getFederatePubAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &thePubAttributes)
{
  GERTICO::PubAttributeDB *currPubAttributeDB;
  GERTICO::FedPubAttributeMap::iterator itAM;

  itAM = fedPubAttributeMap.find(theFederate);
  if (itAM != fedPubAttributeMap.end())
  {
    currPubAttributeDB = &itAM->second;
    thePubAttributes = currPubAttributeDB->attributeSet;
  }
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublishedClass::getObjectIds(GERTICO::HandleSet &theObjects)
{
  HandleSet::iterator itH;

  for (itH = objects.begin(); itH != objects.end(); itH++)
  {
    theObjects.insert(*itH);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::PublishedClass::getStarted(GeRtiFactory::GeRtiHandle const &theFederate)
{
  GERTICO::FedPubAttributeMap::iterator itPOCF;
  bool ret = false;

  itPOCF = fedPubAttributeMap.find(theFederate);
  if (itPOCF != fedPubAttributeMap.end ())
  {
    ret = itPOCF->second.getStarted();
  }

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void  GERTICO::PublishedClass::print()
{
/*
  HandleSet::iterator iObject;
  for (iObject = objects.begin(); iObject != objects.end(); iObject++)
  {
    std::cout << "Object " << *iObject << std::endl;
  }  
*/
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublishedClass::restore(DOMElement &theDOMElement)
{
  DOMNode* child;

  for (child = theDOMElement.getFirstChild(); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode("objects")) == 0)
      {
        restoreObjects(*((DOMElement *)child));
      }
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode("federates")) == 0)
      {
        restoreFederates(*((DOMElement *)child));
      }
    }
  }
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublishedClass::restoreAttributes(DOMElement &theDOMElement, PubAttributeDB &thePubAttributeDB)
{
  DOMNode* child;
  DOMNode* subChild;
  char *tmpChar;
  unsigned long tmpID;

  for (child = theDOMElement.getFirstChild(); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode("attributes")) == 0)
      {
        for (subChild = child->getFirstChild(); subChild != 0; subChild = subChild->getNextSibling())
        {
          if (subChild->getNodeType() == DOMNode::ELEMENT_NODE)
          {
            tmpChar = XMLString::transcode(((DOMElement*)subChild)->getAttribute(XMLString::transcode("id")));
            sscanf(tmpChar, "%lu", &tmpID);
            thePubAttributeDB.attributeSet.insert(tmpID);
          }
        }
      }
    }
  }
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublishedClass::restoreFederates(DOMElement &theDOMElement)
{
  DOMNode* child;
  char *tmpChar;
  unsigned long tmpID;

  for (child = theDOMElement.getFirstChild(); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode("federate")) == 0)
      {
        PubAttributeDB pubAttributeDB;
        tmpChar = XMLString::transcode(((DOMElement*)child)->getAttribute(XMLString::transcode("id")));
        sscanf(tmpChar, "%lu", &tmpID);

        restoreAttributes(*((DOMElement *)child), pubAttributeDB);
        fedPubAttributeMap[tmpID] = pubAttributeDB;
      }
    }
  }
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublishedClass::restoreObjects(DOMElement &theDOMElement)
{
  DOMNode* child;
  char *tmpChar;
  unsigned long tmpUL;

  // Clear old values.
  objects.clear();

  for (child = theDOMElement.getFirstChild(); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode("object")) == 0)
      {
        tmpChar = XMLString::transcode(((DOMElement*)child)->getAttribute(XMLString::transcode("id")));
        sscanf(tmpChar, "%lu", &tmpUL);
        addObject(tmpUL);
      }
    }
  }
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublishedClass::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  GERTICO::PubAttributeDB *currPubAttributeDB;
  GERTICO::FedPubAttributeMap::iterator itAM;
  GERTICO::HandleSet::iterator itA;
  DOMElement* elemLevel1;
  DOMElement* elemLevel2;
  DOMElement* elemLevel3;
  DOMElement* elemLevel4;
  DOMElement* elemLevel5;
  HandleSet::iterator itO;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[128];
  unsigned long ul;

  XMLString::transcode("publishedClass", tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel1);

  XMLString::transcode("id", tempStr, 99);
  ul = myId;
  sprintf(buf, "%lu", ul);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode("objects", tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  elemLevel1->appendChild(elemLevel2);

  for (itO = objects.begin(); itO != objects.end(); itO++)
  {
    XMLString::transcode("object", tempStr, 99);
    elemLevel3 = theDOMDocument.createElement(tempStr);
    elemLevel2->appendChild(elemLevel3);

    XMLString::transcode("id", tempStr, 99);
    ul = *itO;
    sprintf(buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel3->setAttribute(tempStr, tempStr1);
  }

  XMLString::transcode("federates", tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  elemLevel1->appendChild(elemLevel2);

  for (itAM = fedPubAttributeMap.begin(); itAM != fedPubAttributeMap.end(); itAM++)
  {
    currPubAttributeDB = &itAM->second;
    XMLString::transcode("federate", tempStr, 99);
    elemLevel3 = theDOMDocument.createElement(tempStr);
    elemLevel2->appendChild(elemLevel3);

    XMLString::transcode("id", tempStr, 99);
    ul = itAM->first;
    sprintf(buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel3->setAttribute(tempStr, tempStr1);

    XMLString::transcode("attributes", tempStr, 99);
    elemLevel4 = theDOMDocument.createElement(tempStr);
    elemLevel3->appendChild(elemLevel4);

    for (itA = currPubAttributeDB->attributeSet.begin(); itA != currPubAttributeDB->attributeSet.end(); itA++)
    {
      XMLString::transcode("attribute", tempStr, 99);
      elemLevel5 = theDOMDocument.createElement(tempStr);
      elemLevel4->appendChild(elemLevel5);

      XMLString::transcode("id", tempStr, 99);
      ul = *itA;
      sprintf(buf, "%lu", ul);
      XMLString::transcode(buf, tempStr1, 99);
      elemLevel5->setAttribute(tempStr, tempStr1);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublishedClass::setStarted(GeRtiFactory::GeRtiHandle const &theFederate, bool const &theStarted)
{
  GERTICO::FedPubAttributeMap::iterator itPOCF;

  itPOCF = fedPubAttributeMap.find(theFederate);
  if (itPOCF != fedPubAttributeMap.end ())
  {
    itPOCF->second.setStarted (theStarted);
  }
}

// ---------------------------------------------------------------------------
// Create a set of publishers who have to start registration.
// ---------------------------------------------------------------------------
void GERTICO::PublishedClass::startRegistration(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theAttributes, GERTICO::HandleSet &thePublishers, GERTICO::HandleSet &theFederates)
{
  GERTICO::HandleSet::iterator itA;
  GERTICO::HandleSet::iterator itAttribute;
  GERTICO::HandleSet::iterator itGHS;
  GERTICO::PubAttributeDB *currPubAttributeDB;
  GERTICO::FedPubAttributeMap::iterator itAM;

  // Clear out any previous publishers.
  thePublishers.clear();

  for (itAM = fedPubAttributeMap.begin(); itAM != fedPubAttributeMap.end(); itAM++)
  {
    // Do not take the current federate.
    if (itAM->first == theFederate)
    {
      continue;
    }

    currPubAttributeDB = &itAM->second;

    if (getStarted(itAM->first))
    {
      continue;
    }

    // Check if the publisher publishes any of the attributes.
    for (itAttribute = theAttributes.begin(); itAttribute != theAttributes.end(); itAttribute++)
    {
      itA = currPubAttributeDB->attributeSet.find(*itAttribute);
      if (itA != currPubAttributeDB->attributeSet.end())
      {
        itGHS = thePublishers.find(itAM->first);
        if (itGHS == thePublishers.end())
        {
          // Insert only once.
          thePublishers.insert(itAM->first);
          setStarted(itAM->first, true);
          break;
        }
      }
    }
  }  
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::PublisherHolder::PublisherHolder(void)
{
  // Strings for save/restore.
  idStr = "id";
  publishedClassesStr = "publishedClasses";
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::PublisherHolder::~PublisherHolder(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublisherHolder::checkPublishing(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &theAttributes, GeRtiFactory::GeRtiHandle const &thePrivilegeToDeleteId)
{
  GERTICO::PublishedClass *publishedClass;
  GERTICO::PublishedClassMap::iterator itPCM;

  itPCM = publishedClassMap.find(theClass);
  if (itPCM != publishedClassMap.end())
  {
    publishedClass = itPCM->second;
    publishedClass->checkPublishing(theFederate, theAttributes, thePrivilegeToDeleteId);
  }
  else
  {
    throw GeRtiFactory::ObjectClassNotPublished(L"checkPublishing");
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublisherHolder::clear(void)
{
  GERTICO::PublishedClass *currPublishedClass;
  PublishedClassMap::iterator itPC;

  // Clear old values.
  for (itPC = publishedClassMap.begin(); itPC != publishedClassMap.end(); itPC = publishedClassMap.begin())
  {
    currPublishedClass = itPC->second;
    publishedClassMap.erase(itPC);
    delete currPublishedClass;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublisherHolder::getPublishedAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSet &theAttributeSet, GeRtiFactory::GeRtiHandle const &thePrivilegeToDeleteId)
{
  GERTICO::PublishedClass *currPublishedClass;
  GERTICO::PublishedClassMap::iterator itC;

  // clear out any old values.
  theAttributeSet.clear();

  // Get published attributes,
  itC = publishedClassMap.find(theClass);
  if (itC != publishedClassMap.end())
  {
    currPublishedClass = itC->second;
    currPublishedClass->getPublishInfo(theFederate, theAttributeSet);
  }

  // Add privilege to delete.
  theAttributeSet.insert(thePrivilegeToDeleteId);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::PublishedClass* GERTICO::PublisherHolder::getPublishedClass(GeRtiFactory::GeRtiHandle const &classId) throw (GeRtiFactory::ObjectClassNotPublished)
{
  GERTICO::PublishedClassMap::iterator iClass = publishedClassMap.find(classId);
  if (iClass == publishedClassMap.end())
  {
    return NULL;
  }
  return iClass->second;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublisherHolder::getPublishFederates(GERTICO::HandleSet &theFederates)
{
  GERTICO::HandleSetMap::iterator itFedPubObjectClassMap;

  pm.acquire();
  for (itFedPubObjectClassMap = fedPubObjectClassMap.begin(); itFedPubObjectClassMap != fedPubObjectClassMap.end(); itFedPubObjectClassMap++)
  {
    theFederates.insert(itFedPubObjectClassMap->first);
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublisherHolder::getPublishedObjectClasses(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &thePublishedClasses)
{
  GERTICO::HandleSetMap::iterator itPOCF;

  itPOCF = fedPubObjectClassMap.find(theFederate);
  if (itPOCF != fedPubObjectClassMap.end())
  {
    thePublishedClasses = itPOCF->second;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::PublisherHolder::getStarted(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass)
{
  GERTICO::PublishedClass *publishedClassPtr;
  GERTICO::PublishedClassMap::iterator itPCM;
  bool ret = false;

  try
  {
    itPCM = publishedClassMap.find(theClass);
    if (itPCM != publishedClassMap.end())
    {
      publishedClassPtr = itPCM->second;
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
GERTICO::PublishedClass* GERTICO::PublisherHolder::createClass(GeRtiFactory::GeRtiHandle classId)
{
  GERTICO::PublishedClass* newClass;
  GERTICO::PublishedClassMap::iterator iClass =  publishedClassMap.find(classId);
  if (iClass == publishedClassMap.end())
  {
    newClass = new GERTICO::PublishedClass(classId);
    publishedClassMap[classId] = newClass;
  }
  else
  {
    newClass = iClass->second;
  }
  return newClass;
}

// ---------------------------------------------------------------------------
// Use for publish and unpublish.
// ---------------------------------------------------------------------------
void GERTICO::PublisherHolder::publishObjectClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet &theAttributes)
{
  GERTICO::HandleSet::iterator itClasses;
  GERTICO::HandleSetMap::iterator itFedPubObjectClassMap;
  GERTICO::PublishedClass *currPublishedClass;

  // Check if object class already administered.
  currPublishedClass = getPublishedClass (theObjectClass);
  if (currPublishedClass == NULL)
  {
    // Create an object class.
    currPublishedClass = createClass(theObjectClass);
    currPublishedClass->sharingStatus = Publish;
  }

  // Have an object class.
  currPublishedClass->addPubAttributes (theFederate, theAttributes);

  itFedPubObjectClassMap = fedPubObjectClassMap.find(theFederate);
  if (itFedPubObjectClassMap != fedPubObjectClassMap.end())
  {
    itClasses = itFedPubObjectClassMap->second.find(theObjectClass);
    if (itClasses == itFedPubObjectClassMap->second.end())
    {
      itFedPubObjectClassMap->second.insert(theObjectClass);
    }
  }
  else
  {
    GERTICO::HandleSet classes;

    classes.insert(theObjectClass);
    fedPubObjectClassMap[theFederate] = classes;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublisherHolder::restorePublishedClasses(DOMElement &theDOMElement)
{
  DOMNode *child;
  GERTICO::PublishedClass *currPublishedClass;
  char *tmpChar;
  unsigned long tmpID;

  // Restore the published classes,
  for (child = theDOMElement.getFirstChild(); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode("publishedClass")) == 0)
      {
        tmpChar = XMLString::transcode(((DOMElement *)child)->getAttribute(XMLString::transcode(idStr.c_str())));
        sscanf(tmpChar, "%lu", &tmpID);
        currPublishedClass = new GERTICO::PublishedClass(tmpID);
        currPublishedClass->restore(*((DOMElement *)child));
        publishedClassMap[tmpID] = currPublishedClass;
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublisherHolder::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel1;
  GERTICO::PublishedClassMap::iterator itP;
  XMLCh tempStr[100];

  // Published classes.
  XMLString::transcode(publishedClassesStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel1);

  for (itP = publishedClassMap.begin(); itP != publishedClassMap.end(); itP++)
  {
    itP->second->save(theDOMDocument, *elemLevel1);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublisherHolder::setStarted(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, bool const &theStarted)
{
  GERTICO::PublishedClass *publishedClassPtr;
  GERTICO::PublishedClassMap::iterator itPCM;

  try
  {
    itPCM = publishedClassMap.find(theClass);
    if (itPCM != publishedClassMap.end())
    {
      publishedClassPtr = itPCM->second;
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
void GERTICO::PublisherHolder::unpublishObjectClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass)
{
  GERTICO::HandleSet::iterator itClasses;
  GERTICO::HandleSetMap::iterator itFedPubObjectClassMap;
  GERTICO::PublishedClass *currPublishedClass;

  // Check if object class already administered.
  currPublishedClass = getPublishedClass(theObjectClass);
  if (currPublishedClass == NULL)
  {
#ifdef IEEE_1516
    return;
#else
    throw GeRtiFactory::ObjectClassNotPublished(L"unpublishObjectClass");
#endif
  }

  // Have an object class.
  currPublishedClass->delPubAttributes(theFederate);

  itFedPubObjectClassMap = fedPubObjectClassMap.find(theFederate);
  if (itFedPubObjectClassMap != fedPubObjectClassMap.end())
  {
    itClasses = itFedPubObjectClassMap->second.find(theObjectClass);
    if (itClasses != itFedPubObjectClassMap->second.end())
    {
      itFedPubObjectClassMap->second.erase(itClasses);
    }
  }
}
