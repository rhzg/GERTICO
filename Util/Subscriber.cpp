/*********************************************************************************
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
**********************************************************************************
 
$Author: mul $
$Name $
$Log: Subscriber.cpp,v $
Revision 1.25  2009/08/17 09:58:30  mul
Use standard length type.

Revision 1.24  2008/09/12 08:31:52  mul
Remove unwanted variables.

Revision 1.23  2007/11/22 14:58:43  mul
Changes for vc8.

Revision 1.22  2007/11/13 10:20:22  mul
Remove unused variables.

Revision 1.21  2007/09/25 07:56:57  mul
Changes for ddm.

Revision 1.20  2007/09/05 15:17:31  mul
Changes for ieee1516.

Revision 1.19  2007/05/03 14:27:54  mul
Add parameter to exception constructor.

Revision 1.18  2007/02/02 13:22:58  mul
Fix some memory leaks.

Revision 1.17  2006/09/21 14:44:05  mul
Remove unused method.

Revision 1.16  2006/08/23 11:09:48  mul
Add print functions.

Revision 1.15  2006/08/22 08:46:47  mul
Change logic for phase 4 testcases.

Revision 1.14  2006/08/18 12:44:03  mul
Changes for phase 4 testcases.

Revision 1.13  2006/08/15 12:34:09  mul
Changes for phase 4 test.

Revision 1.12  2006/04/26 10:05:57  mul
phase II corrections

Revision 1.11  2006/04/24 06:33:35  mul
Add new method for subscribe.

Revision 1.10  2006/04/21 07:10:12  mul
Fix delete subscribed attribute logic.

Revision 1.9  2006/03/17 12:10:04  mul
Fix scope logic for data distribution.

Revision 1.8  2006/02/27 14:26:41  mul
Change handling of attribute/region pairs.

Revision 1.7  2005/09/19 07:53:34  mul
Fix a memory leak.

Revision 1.6  2005/03/15 14:38:11  mul
Fix multiple region logic. Fix save/restore logic.

Revision 1.5  2005/02/25 11:15:29  mul
Add logic to support unconditional attribute ownership divesture.

Revision 1.4  2004/08/20 08:15:50  mul
Fix print formats.

Revision 1.3  2004/08/19 09:31:14  mul
Changes for save/restore logic.

Revision 1.2  2004/07/16 10:22:40  mul
Add classes taken from another file.

Revision 1.1  2004/05/27 11:26:13  mul
Integrate subscriber management.

 
**
*******************************************************************************/

#include "Subscriber.h"

// Static strings for save/restore.
std::string GERTICO::Subscriber::activeStr("active");
std::string GERTICO::Subscriber::idStr("id");
std::string GERTICO::Subscriber::regionStr("region");
std::string GERTICO::Subscriber::regionsStr("regions");

std::string GERTICO::SubscribeAttributeDB::federateStr("federate");
std::string GERTICO::SubscribeAttributeDB::subscriberStr("subscriber");
std::string GERTICO::SubscribeAttributeDB::subscribersStr("subscribers");

std::string GERTICO::SubscribedClass::attributeStr("attribute");
std::string GERTICO::SubscribedClass::attributesStr("attributes");
std::string GERTICO::SubscribedClass::idStr("id");

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Subscriber::Subscriber(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Subscriber::~Subscriber(void)
{
  clear();
}

// ---------------------------------------------------------------------------
// Default region has key 0.
// ---------------------------------------------------------------------------
void GERTICO::Subscriber::addActiveRegion(const CORBA::Boolean &theActive)
{
  GERTICO::HandleBoolMap::iterator itRAM;
  bool active;

  // Type conversion.
  if (theActive)
  {
    active = true;
  }
  else
  {
    active = false;
  }

  // Get rid of old entry.
  itRAM = regionActiveMap.find(0);
  if (itRAM != regionActiveMap.end())
  {
    regionActiveMap.erase(itRAM);
  }

  regionActiveMap[0] = active;
}

// ---------------------------------------------------------------------------
// Default region has key 0.
// ---------------------------------------------------------------------------
void GERTICO::Subscriber::addActiveRegion(const CORBA::Boolean &theActive, GERTICO::HandleSet &theRegions)
{
  GERTICO::HandleBoolMap::iterator itRAM;
  GERTICO::HandleSet::iterator itRegions;
  bool active;

  // Type conversion.
  if (theActive)
  {
    active = true;
  }
  else
  {
    active = false;
  }

  for (itRegions = theRegions.begin(); itRegions != theRegions.end(); itRegions++)
  {
    unsigned long ul;
    ul = *itRegions;
    // Get rid of old entry.
    itRAM = regionActiveMap.find(*itRegions);
    if (itRAM != regionActiveMap.end())
    {
      regionActiveMap.erase(itRAM);
    }

    regionActiveMap[*itRegions] = active;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Subscriber::checkActiveSubscriber(void)
{
  GERTICO::HandleBoolMap::iterator itRAM;

  for (itRAM = regionActiveMap.begin(); itRAM != regionActiveMap.end(); itRAM++)
  {
    if (itRAM->second)
    {
      return true;
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Subscriber::checkSubscribedDefault(void)
{
  GERTICO::HandleBoolMap::iterator itRAM;

  itRAM = regionActiveMap.find(0);
  if (itRAM != regionActiveMap.end())
  {
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Subscriber::clear(void)
{
  regionActiveMap.clear();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Subscriber::delRegion(const GeRtiFactory::GeRtiHandle &theRegion)
{
  CORBA::WChar *wChar = L"";
  GERTICO::HandleBoolMap::iterator itRAM;

  itRAM = regionActiveMap.find(theRegion);
  if (itRAM != regionActiveMap.end())
  {
    regionActiveMap.erase(itRAM);
  }
  else
  {
#ifndef IEEE_1516
    throw GeRtiFactory::RegionNotKnown(wChar);
#endif
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Subscriber::getRegions(GERTICO::HandleBoolMap &theRegions)
{
  theRegions = regionActiveMap;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Subscriber::isRegionSubscribed(const GeRtiFactory::GeRtiHandle &theRegion)
{
  GERTICO::HandleBoolMap::iterator itRAM;

  itRAM = regionActiveMap.find(theRegion);
  if (itRAM != regionActiveMap.end())
  {
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Subscriber::isEmpty(void)
{
  size_t size = regionActiveMap.size();

  if (size == 0)
  {
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Subscriber::isSubscribed(void)
{
  GERTICO::HandleBoolMap::iterator itRAM;

  for (itRAM = regionActiveMap.begin(); itRAM != regionActiveMap.end(); itRAM++)
  {
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Subscriber::isSubscribedActive(void)
{
  GERTICO::HandleBoolMap::iterator itRAM;

  for (itRAM = regionActiveMap.begin(); itRAM != regionActiveMap.end(); itRAM++)
  {
    if (itRAM->second)
    {
      return true;
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Subscriber::print(void)
{
/*
  GERTICO::HandleBoolMap::iterator itRegionActiveMap;
  unsigned long ul;

  for (itRegionActiveMap = regionActiveMap.begin(); itRegionActiveMap != regionActiveMap.end(); itRegionActiveMap++)
  {
    ul = itRegionActiveMap->first;
    std::cout << "        Subscriber Region " << ul << std::endl;
  }
*/
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Subscriber::restore(DOMElement &theDOMElement)
{
  DOMNode* child;
  DOMNode* subChild;
  bool theActive;
  char *tmpArray;
  unsigned long tmpREGION;
  unsigned long tmpUL;

  // Clear any old data.
  clear();

  for (child = theDOMElement.getFirstChild(); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode(regionsStr.c_str())) == 0)
      {
        for (subChild = child->getFirstChild(); subChild != 0; subChild = subChild->getNextSibling())
        {
          if (subChild->getNodeType() == DOMNode::ELEMENT_NODE)
          {
            if (XMLString::compareString(subChild->getNodeName(),XMLString::transcode(regionStr.c_str())) == 0)
            {
              tmpArray = XMLString::transcode(((DOMElement*)subChild)->getAttribute(XMLString::transcode(idStr.c_str())));
              sscanf(tmpArray, "%lu", &tmpREGION);
              XMLString::release(&tmpArray);
              tmpArray = XMLString::transcode(((DOMElement*)subChild)->getAttribute(XMLString::transcode(activeStr.c_str())));
              sscanf(tmpArray, "%lu", &tmpUL);
              if (tmpUL)
              {
                theActive = true;
              }
              else
              {
                theActive = false;
              }
              regionActiveMap[tmpREGION] = theActive;
            }
          }
        }
      }
    }
  }
  XMLString::release(&tmpArray);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Subscriber::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel1;
  DOMElement* elemLevel2;
  GERTICO::HandleBoolMap::iterator itRAM;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[128];
  unsigned long ul;

  XMLString::transcode(regionsStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel1);

  for (itRAM = regionActiveMap.begin(); itRAM != regionActiveMap.end(); itRAM++)
  {
    XMLString::transcode(regionStr.c_str(), tempStr, 99);
    elemLevel2 = theDOMDocument.createElement(tempStr);
    elemLevel1->appendChild(elemLevel2);

    XMLString::transcode(activeStr.c_str(), tempStr, 99);
    if (itRAM->second)
    {
      strcpy(buf, "1");
    }
    else
    {
      strcpy(buf, "0");
    }
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);
     
    XMLString::transcode(idStr.c_str(), tempStr, 99);
    ul = itRAM->first;
    sprintf(buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::SubscribeAttributeDB::SubscribeAttributeDB(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::SubscribeAttributeDB::~SubscribeAttributeDB(void)
{
  clear();
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribeAttributeDB::addSubFederate(const GeRtiFactory::GeRtiHandle &theFederate, const CORBA::Boolean &theActive)
{
  Subscriber subscriber;
  SubscriberMap::iterator itFS;

  itFS = subscribedFederates.find(theFederate);
  if (itFS == subscribedFederates.end())
  {
    subscriber.addActiveRegion(theActive);
    subscribedFederates[theFederate] = subscriber;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribeAttributeDB::addSubFederate(const GeRtiFactory::GeRtiHandle &theFederate, const CORBA::Boolean &theActive, GERTICO::HandleSet &theRegions)
{
  Subscriber subscriber;
  Subscriber *subscriberPtr;
  SubscriberMap::iterator itFS;

  itFS = subscribedFederates.find(theFederate);
  if (itFS == subscribedFederates.end())
  {
    subscriber.addActiveRegion(theActive, theRegions);
    subscribedFederates[theFederate] = subscriber;
  }
  else
  {
    subscriberPtr = &itFS->second;
    subscriberPtr->addActiveRegion(theActive, theRegions);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SubscribeAttributeDB::checkActiveSubscriber(const GeRtiFactory::GeRtiHandle &theFederate)
{
  SubscriberMap::iterator itFS;

  for (itFS = subscribedFederates.begin(); itFS != subscribedFederates.end(); itFS++)
  {
    // Skip the current federate.
    if (itFS->first == theFederate)
    {
      continue;
    }

    // If any active subscriber, return true.
    if (itFS->second.checkActiveSubscriber() == true)
    {
      return true;
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SubscribeAttributeDB::checkFederateSubscribed(const GeRtiFactory::GeRtiHandle &theFederate)
{
  Subscriber *currSubscriber;
  SubscriberMap::iterator itFS;

  // Get the federate info.
  itFS = subscribedFederates.find(theFederate);
  if (itFS != subscribedFederates.end())
  {
    currSubscriber = &itFS->second;
    if (currSubscriber->isRegionSubscribed(0))
    {
      return true;
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SubscribeAttributeDB::checkFederateSubscribedRegion(const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::HandleSet &theRegions)
{
  GERTICO::HandleSet::iterator itRegions;
  Subscriber *currSubscriber;
  SubscriberMap::iterator itFS;

  // Get the federate info.
  itFS = subscribedFederates.find(theFederate);
  if (itFS != subscribedFederates.end())
  {
    currSubscriber = &itFS->second;
    for (itRegions = theRegions.begin(); itRegions != theRegions.end(); itRegions++)
    {
      if (currSubscriber->isRegionSubscribed(*itRegions))
      {
        return true;
      }
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribeAttributeDB::clear(void)
{
  subscribedFederates.clear();
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribeAttributeDB::delSubFederate(const GeRtiFactory::GeRtiHandle &theFederate)
{
  Subscriber *currSubscriber;
  SubscriberMap::iterator itFS;

  // Get the federate info.
  itFS = subscribedFederates.find(theFederate);
  if (itFS != subscribedFederates.end())
  {
    currSubscriber = &itFS->second;
    // Delete the region.
    currSubscriber->delRegion(0);
    if (currSubscriber->isEmpty())
    {
      // No more regions.
      subscribedFederates.erase(itFS);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribeAttributeDB::delSubFederateRegion(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theRegion)
{
  Subscriber *currSubscriber;
  SubscriberMap::iterator itFS;

  // Get the federate info.
  itFS = subscribedFederates.find(theFederate);
  if (itFS != subscribedFederates.end())
  {
    currSubscriber = &itFS->second;
    // Delete the region.
    currSubscriber->delRegion(theRegion);
    if (currSubscriber->isEmpty())
    {
      // No more regions.
      subscribedFederates.erase(itFS);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribeAttributeDB::getRegions(const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::HandleBoolMap &theRegions)
{
  Subscriber *currSubscriber;
  SubscriberMap::iterator itFS;

  // Clear any previous values.
  theRegions.clear();

  // Check the federate.
  itFS = subscribedFederates.find(theFederate);
  if (itFS != subscribedFederates.end())
  {
    currSubscriber = &itFS->second;
    currSubscriber->getRegions(theRegions);
  }
}

// ---------------------------------------------------------------------------
// Check all maps and sets - true only if all are empty.
// ---------------------------------------------------------------------------
bool GERTICO::SubscribeAttributeDB::isEmpty(void)
{
  size_t len;

  len = subscribedFederates.size();
  if (len)
  {
    return false;
  }

  return true;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SubscribeAttributeDB::isRegionSubscribed(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theRegion)
{
  Subscriber *currSubscriber;
  SubscriberMap::iterator itFS;

  itFS = subscribedFederates.find(theFederate);
  if (itFS != subscribedFederates.end())
  {
    currSubscriber = &itFS->second;
    if (currSubscriber->isRegionSubscribed(theRegion))
    {
      return true;
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SubscribeAttributeDB::isSubscribed(const GeRtiFactory::GeRtiHandle &theFederate)
{
  Subscriber *currSubscriber;
  SubscriberMap::iterator itFS;

  itFS = subscribedFederates.find(theFederate);
  if (itFS != subscribedFederates.end())
  {
    currSubscriber = &itFS->second;
    if (currSubscriber->isSubscribed())
    {
      return true;
    }
  }
  
  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SubscribeAttributeDB::isSubscribedActive(const GeRtiFactory::GeRtiHandle &theFederate)
{
  Subscriber *currSubscriber;
  SubscriberMap::iterator itFS;

  itFS = subscribedFederates.find(theFederate);
  if (itFS != subscribedFederates.end())
  {
    currSubscriber = &itFS->second;
    if (currSubscriber->isSubscribedActive())
    {
      return true;
    }
  }
  
  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribeAttributeDB::print(void)
{
/*
  Subscriber *currSubscriber;
  SubscriberMap::iterator itSubscriberMap;
  unsigned long ul;

  for (itSubscriberMap = subscribedFederates.begin(); itSubscriberMap != subscribedFederates.end(); itSubscriberMap++)
  {
    ul = itSubscriberMap->first;
    std::cout << "      SubscribeAttributeDB Federate " << ul << std::endl;
    currSubscriber = &itSubscriberMap->second;
    currSubscriber->print();
  }
*/
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribeAttributeDB::restore(DOMElement &theDOMElement)
{
  DOMNode* child;
  DOMNode* subChild;
  Subscriber subscriber;
  char *tmpChar;
  unsigned long tmpFED;

  clear();

  for (child = theDOMElement.getFirstChild(); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode(subscribersStr.c_str())) == 0)
      {
        for (subChild = child->getFirstChild(); subChild != 0; subChild = subChild->getNextSibling())
        {
          if (subChild->getNodeType() == DOMNode::ELEMENT_NODE)
          {
            if (XMLString::compareString(subChild->getNodeName(),XMLString::transcode(subscriberStr.c_str())) == 0)
            {
              tmpChar = XMLString::transcode(((DOMElement*)subChild)->getAttribute(XMLString::transcode(federateStr.c_str())));
              sscanf(tmpChar, "%lu", &tmpFED);
              subscriber.restore(*((DOMElement *)subChild));
              subscribedFederates[tmpFED] = subscriber;
            }
          }
        }
      }
    }
  }
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribeAttributeDB::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel1;
  DOMElement* elemLevel2;
  SubscriberMap::iterator itS;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[128];
  unsigned long ul;

  XMLString::transcode(subscribersStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel1);

  for (itS = subscribedFederates.begin(); itS != subscribedFederates.end(); itS++)
  {
    XMLString::transcode(subscriberStr.c_str(), tempStr, 99);
    elemLevel2 = theDOMDocument.createElement(tempStr);
    elemLevel1->appendChild(elemLevel2);

    XMLString::transcode(federateStr.c_str(), tempStr, 99);
    ul = itS->first;
    sprintf(buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);

    itS->second.save(theDOMDocument, *elemLevel2);
  }

  XMLString::transcode("publishers", tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel1);
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SubscribeAttributeDB::subscribedToAttribute(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theRegion, GERTICO::RegionMap &theRegionMap)
{
  GERTICO::HandleBoolMap regions;
  GERTICO::HandleBoolMap::iterator itRAM;
  Subscriber *currSubscriber;
  SubscriberMap::iterator itFS;

  itFS = subscribedFederates.find(theFederate);
  if (itFS != subscribedFederates.end())
  {
    currSubscriber = &itFS->second;
    currSubscriber->getRegions(regions);

    for (itRAM = regions.begin(); itRAM != regions.end(); itRAM++)
    {
      if (theRegion == 0)
      {
        // Have region overlap with default region.
        return true;
      }

      if (testIntersection(theRegion, itRAM->first, theRegionMap))
      {
        // Have region overlap.
        return true;
      }
    }
  }
  
  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SubscribeAttributeDB::testIntersection(const GeRtiFactory::GeRtiHandle &regionFirst, const GeRtiFactory::GeRtiHandle &regionSecond, GERTICO::RegionMap &theRegionMap)
{
  Region *currRegion;
  RegionMap::iterator itR;

  itR = theRegionMap.find(regionFirst);
  if (itR != theRegionMap.end())
  {
    currRegion = itR->second;
    return currRegion->gotIntersection(regionSecond);
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::SubscribedClass::SubscribedClass(const GeRtiFactory::GeRtiHandle &theObjectClass)
{
  myObjectClassId = theObjectClass;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::SubscribedClass::~SubscribedClass(void)
{
  clear();
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribedClass::addSubAttributes(const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::HandleSet &theAttributes, const CORBA::Boolean &theActive)
{
  GERTICO::HandleSet::iterator itAttributes;
  GERTICO::HandleSetMap::iterator itHS;
  SubscribeAttributeDB *currSubscribeAttributeDB;
  SubscribeAttributeDBMap::iterator itFOCA;

  // Process the given attributes.
  for (itAttributes = theAttributes.begin(); itAttributes != theAttributes.end(); itAttributes++)
  {
    itFOCA = subscribeAttributeDBMap.find(*itAttributes);
    if (itFOCA != subscribeAttributeDBMap.end())
    {
      currSubscribeAttributeDB = &itFOCA->second;
      currSubscribeAttributeDB->addSubFederate(theFederate, theActive);
    }
    else
    {
      currSubscribeAttributeDB = new SubscribeAttributeDB();
      currSubscribeAttributeDB->addSubFederate(theFederate, theActive);
      subscribeAttributeDBMap[*itAttributes] = *currSubscribeAttributeDB;
      delete currSubscribeAttributeDB;
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribedClass::addSubAttributesWithRegion(const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::HandleSetMap &theAttributeRegions, const CORBA::Boolean &theActive)
{
  GERTICO::HandleSetMap::iterator itAttributeRegions;
  SubscribeAttributeDBMap::iterator itFOCA;
  HandleSetMap::iterator itHS;

#ifndef IEEE_1516
  // Delete any old values.
  delFederateRegionSubscribed(theFederate, theAttributeRegions);
#endif

  // Process the given attributes.
  for (itAttributeRegions = theAttributeRegions.begin(); itAttributeRegions != theAttributeRegions.end(); itAttributeRegions++)
  {
    unsigned long ul;
    ul = itAttributeRegions->first;
    itFOCA = subscribeAttributeDBMap.find(itAttributeRegions->first);
    if (itFOCA != subscribeAttributeDBMap.end())
    {
      SubscribeAttributeDB *currSubscribeAttributeDBPtr;
      currSubscribeAttributeDBPtr = &itFOCA->second;
      currSubscribeAttributeDBPtr->addSubFederate(theFederate, theActive, itAttributeRegions->second);
    }
    else
    {
      SubscribeAttributeDB currSubscribeAttributeDB;
      currSubscribeAttributeDB.addSubFederate(theFederate, theActive, itAttributeRegions->second);
      subscribeAttributeDBMap[itAttributeRegions->first] = currSubscribeAttributeDB;
    }
  }
}

// ---------------------------------------------------------------------------
// Special logic to find publishers which do not have active subscribers.
// ---------------------------------------------------------------------------
bool GERTICO::SubscribedClass::checkActiveSubscribers(const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::HandleSet &theAttributes)
{
  GERTICO::HandleSet::iterator itHS;
  SubscribeAttributeDB *currSubscribeAttributeDB;
  SubscribeAttributeDBMap::iterator itFOCA;

  // Process the given attributes.
  for (itHS = theAttributes.begin(); itHS != theAttributes.end(); itHS++)
  {
    itFOCA = subscribeAttributeDBMap.find(*itHS);
    if (itFOCA != subscribeAttributeDBMap.end())
    {
      // Do not take passive subscriber.
      currSubscribeAttributeDB = &itFOCA->second;
      if (currSubscribeAttributeDB->checkActiveSubscriber(theFederate) == false)
      {
        continue;
      }

      // Have an active subscriber.
      return true;
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribedClass::clear(void)
{
  subscribeAttributeDBMap.clear();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribedClass::delFederateRegionSubscribed(const GeRtiFactory::GeRtiHandle &theFederate)
{
  GERTICO::SubscribeAttributeDB *currSubscribeAttributeDB;
  GERTICO::SubscribeAttributeDBMap::iterator itFOCA;

  // Check if any object class/region pair exists.
  for (itFOCA = subscribeAttributeDBMap.begin(); itFOCA != subscribeAttributeDBMap.end(); itFOCA++)
  {
    currSubscribeAttributeDB = &itFOCA->second;
    if (currSubscribeAttributeDB->checkFederateSubscribed(theFederate))
    {
      try
      {
        currSubscribeAttributeDB->delSubFederate(theFederate);
      }
      catch(GeRtiFactory::RegionNotKnown &)
      {
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribedClass::delFederateRegionSubscribed(const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::HandleSetMap &theAttributeRegions)
{
  GERTICO::HandleSet regions;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::HandleSet::iterator itTheRegion;
  GERTICO::HandleSetMap::iterator itAttributeRegions;
  GERTICO::SubscribeAttributeDB *currSubscribeAttributeDB;
  GERTICO::SubscribeAttributeDBMap::iterator itFOCA;

  // Get a set of region ids.
  for (itAttributeRegions = theAttributeRegions.begin(); itAttributeRegions != theAttributeRegions.end(); itAttributeRegions++)
  {
    for (itTheRegion = itAttributeRegions->second.begin(); itTheRegion != itAttributeRegions->second.end(); itTheRegion++)
    {
      itRegion = regions.find(*itTheRegion);
      if (itRegion == regions.end())
      {
        regions.insert(*itTheRegion);
      }
    }
  }

  // Check if any object class/region pair exists.
  for (itFOCA = subscribeAttributeDBMap.begin(); itFOCA != subscribeAttributeDBMap.end(); itFOCA++)
  {
    currSubscribeAttributeDB = &itFOCA->second;
    for (itRegion = regions.begin(); itRegion != regions.end(); itRegion++)
    {
      try
      {
        currSubscribeAttributeDB->delSubFederateRegion(theFederate, *itRegion);
      }
      catch(GeRtiFactory::RegionNotKnown &)
      {
        continue;
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribedClass::delSubObjectClass(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theRegion)
{
  SubscribeAttributeDB *currSubscribeAttributeDB;
  SubscribeAttributeDBMap::iterator itSubscribeAttributeDBMap;
  HandleSetMap::iterator itHS;

  // For all attributes, delete the region.
  for (itSubscribeAttributeDBMap = subscribeAttributeDBMap.begin(); itSubscribeAttributeDBMap != subscribeAttributeDBMap.end(); itSubscribeAttributeDBMap++)
  {
    currSubscribeAttributeDB = &itSubscribeAttributeDBMap->second;
    try
    {
      currSubscribeAttributeDB->delSubFederateRegion(theFederate, theRegion);
    }
    catch(...)
    {
      continue;
    }
  }

  for (itSubscribeAttributeDBMap = subscribeAttributeDBMap.begin(); itSubscribeAttributeDBMap != subscribeAttributeDBMap.end(); )
  {
    currSubscribeAttributeDB = &itSubscribeAttributeDBMap->second;
    if (currSubscribeAttributeDB->isEmpty())
    {
      // No values are set.
      subscribeAttributeDBMap.erase(itSubscribeAttributeDBMap);
      itSubscribeAttributeDBMap = subscribeAttributeDBMap.begin();
    }
    else
    {
      itSubscribeAttributeDBMap++;
    }
  }

  // Check if there is any information for the federate in the attribute map.
  // If any found, return, else erase.
  for (itSubscribeAttributeDBMap = subscribeAttributeDBMap.begin(); itSubscribeAttributeDBMap != subscribeAttributeDBMap.end(); itSubscribeAttributeDBMap++)
  {
    currSubscribeAttributeDB = &itSubscribeAttributeDBMap->second;
    if (currSubscribeAttributeDB->isSubscribed(theFederate))
    {
      return;
    }
  }
}

#ifdef IEEE_1516
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribedClass::delSubObjectClass(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theAttribute, const GERTICO::HandleSet &theRegions)
{
  SubscribeAttributeDB *currSubscribeAttributeDB;
  SubscribeAttributeDBMap::iterator itSubscribeAttributeDBMap;
  HandleSet::const_iterator itRegion;
  HandleSetMap::iterator itHS;

  // For all attributes, delete the regions.
  itSubscribeAttributeDBMap = subscribeAttributeDBMap.find(theAttribute);
  if (itSubscribeAttributeDBMap != subscribeAttributeDBMap.end())
  {
    currSubscribeAttributeDB = &itSubscribeAttributeDBMap->second;
    for (itRegion = theRegions.begin(); itRegion != theRegions.end(); itRegion++)
    {
      try
      {
        currSubscribeAttributeDB->delSubFederateRegion(theFederate, *itRegion);
      }
      catch(...)
      {
        continue;
      }
    }
    // Check if there is any information for the federate in the attribute map.
    // If any found, return, else erase.
    if (currSubscribeAttributeDB->isSubscribed(theFederate))
    {
      return;
    }
    if (currSubscribeAttributeDB->isEmpty())
    {
      // No values are set.
      subscribeAttributeDBMap.erase(itSubscribeAttributeDBMap);
    }
  }
}
#endif

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SubscribedClass::getRegions(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theAttribute, GERTICO::HandleBoolMap &theRegions)
{
  SubscribeAttributeDB *currSubscribeAttributeDB;
  SubscribeAttributeDBMap::iterator itFOCA;

  itFOCA = subscribeAttributeDBMap.find(theAttribute);
  if (itFOCA != subscribeAttributeDBMap.end())
  {
    currSubscribeAttributeDB = &itFOCA->second;
    currSubscribeAttributeDB->getRegions(theFederate, theRegions);
    if (theRegions.size())
    {
      return true;
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::SubscribedClass::getClassId(void)
{
  return myObjectClassId;
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribedClass::getDesiredAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet const &theEventAttributes, GERTICO::HandleSet &theDesiredAttributes)
{
  GERTICO::HandleSet::const_iterator itEvent;
  GERTICO::SubscribeAttributeDBMap::iterator itSubscribeAttributeDBMap;

  for (itEvent = theEventAttributes.begin(); itEvent != theEventAttributes.end(); itEvent++)
  {
    itSubscribeAttributeDBMap = subscribeAttributeDBMap.find(*itEvent);
    if (itSubscribeAttributeDBMap != subscribeAttributeDBMap.end())
    {
      theDesiredAttributes.insert(*itEvent);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SubscribedClass::isEmpty(void)
{
  size_t size;

  size = subscribeAttributeDBMap.size();
  if (size)
  {
    return false;
  }

  return true;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SubscribedClass::isRegionSubscribed(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theRegion)
{
  SubscribeAttributeDB *currSubscribeAttributeDB;
  SubscribeAttributeDBMap::iterator itFOCA;

  for (itFOCA = subscribeAttributeDBMap.begin(); itFOCA != subscribeAttributeDBMap.end(); itFOCA++)
  {
    currSubscribeAttributeDB = &itFOCA->second;
    if (currSubscribeAttributeDB->isRegionSubscribed(theFederate, theRegion))
    {
      return true;
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribedClass::print(void)
{
/*
  SubscribeAttributeDB *subscribeAttributeDB;
  SubscribeAttributeDBMap::iterator itSubscribeAttributeDBMap;
  unsigned long ul;

  for(itSubscribeAttributeDBMap = subscribeAttributeDBMap.begin(); itSubscribeAttributeDBMap != subscribeAttributeDBMap.end(); itSubscribeAttributeDBMap++)
  {
    ul = itSubscribeAttributeDBMap->first;
    std::cout << "    SubscribedClass Attribute " << ul << std::endl;
    subscribeAttributeDB = &itSubscribeAttributeDBMap->second;
    subscribeAttributeDB->print();
  }
*/
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribedClass::restore(DOMElement &theDOMElement)
{
  DOMNode* child;
  DOMNode* subChild;
  SubscribeAttributeDB subscribeAttributeDB;
  char *tmpChar;
  unsigned long tmpID;

  for (child = theDOMElement.getFirstChild(); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode(attributesStr.c_str())) == 0)
      {
        for(subChild = child->getFirstChild(); subChild != 0; subChild = subChild->getNextSibling())
        {
          if (subChild->getNodeType() == DOMNode::ELEMENT_NODE)
          {
            if (XMLString::compareString(subChild->getNodeName(),XMLString::transcode(attributeStr.c_str())) == 0)
            {
              tmpChar = XMLString::transcode(((DOMElement*)subChild)->getAttribute(XMLString::transcode(idStr.c_str())));
              sscanf(tmpChar, "%lu", &tmpID);
              subscribeAttributeDB.restore(*((DOMElement *)subChild));
              subscribeAttributeDBMap[tmpID] = subscribeAttributeDB;
            }
          }
        }
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribedClass::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel1;
  DOMElement* elemLevel2;
  DOMElement* elemLevel3;
  SubscribeAttributeDBMap::iterator itFOCA;
  GERTICO::HandleSet::iterator itH;
  HandleSetMap::iterator itHS;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[128];
  unsigned long ul;

  XMLString::transcode("class", tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel1);

  XMLString::transcode("objectClass", tempStr, 99);
  ul = myObjectClassId;
  sprintf(buf, "%lu", ul);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(attributesStr.c_str(), tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  elemLevel1->appendChild(elemLevel2);

  for (itFOCA = subscribeAttributeDBMap.begin(); itFOCA != subscribeAttributeDBMap.end(); itFOCA++)
  {
    XMLString::transcode(attributeStr.c_str(), tempStr, 99);
    elemLevel3 = theDOMDocument.createElement(tempStr);
    elemLevel2->appendChild(elemLevel3);

    XMLString::transcode(idStr.c_str(), tempStr, 99);
    ul = itFOCA->first;
    sprintf(buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel3->setAttribute(tempStr, tempStr1);

    itFOCA->second.save(theDOMDocument, *elemLevel3);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SubscribedClass::subscribedToAttribute(const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::HandleSet &theAttributes)
{
  SubscribeAttributeDB *currSubscribeAttributeDB;
  SubscribeAttributeDBMap::iterator itFOCA;
  GERTICO::HandleSet::iterator itGHS;

  for (itGHS = theAttributes.begin(); itGHS != theAttributes.end(); itGHS++)
  {
    itFOCA = subscribeAttributeDBMap.find(*itGHS);
    if (itFOCA != subscribeAttributeDBMap.end())
    {
      currSubscribeAttributeDB = &itFOCA->second;
      if (currSubscribeAttributeDB->isSubscribed(theFederate))
      {
        return true;
      }
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SubscribedClass::subscribedToAttribute(const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::HandleSetMap &theAttributeRegions, GERTICO::RegionMap &theRegionMap)
{
  GERTICO::HandleSet *regionsPtr;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::HandleSetMap::iterator itAttributeRegions;
  SubscribeAttributeDB *currSubscribeAttributeDB;
  SubscribeAttributeDBMap::iterator itFOCA;

  for (itAttributeRegions = theAttributeRegions.begin(); itAttributeRegions != theAttributeRegions.end(); itAttributeRegions++)
  {
    itFOCA = subscribeAttributeDBMap.find(itAttributeRegions->first);
    if (itFOCA != subscribeAttributeDBMap.end())
    {
      currSubscribeAttributeDB = &itFOCA->second;
      regionsPtr = &itAttributeRegions->second;
      for (itRegion = regionsPtr->begin(); itRegion != regionsPtr->end(); itRegion++)
      {
        if (currSubscribeAttributeDB->subscribedToAttribute(theFederate, *itRegion, theRegionMap))
        {
          return true;
        }
      }
    }
  }
 
  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SubscribedClass::subscribedToAttributeActive(const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::HandleSet &theAttributes)
{
  SubscribeAttributeDB *currSubscribeAttributeDB;
  SubscribeAttributeDBMap::iterator itFOCA;
  GERTICO::HandleSet::iterator itGHS;

  for (itGHS = theAttributes.begin(); itGHS != theAttributes.end(); itGHS++)
  {
    itFOCA = subscribeAttributeDBMap.find(*itGHS);
    if (itFOCA != subscribeAttributeDBMap.end())
    {
      currSubscribeAttributeDB = &itFOCA->second;
      if (currSubscribeAttributeDB->isSubscribedActive(theFederate))
      {
        return true;
      }
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::SubscribedClassHolder::SubscribedClassHolder(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::SubscribedClassHolder::~SubscribedClassHolder(void)
{
}

// ---------------------------------------------------------------------------
// Special logic to find publishers which do not have active subscribers.
// ---------------------------------------------------------------------------
bool GERTICO::SubscribedClassHolder::checkActiveObjectClassSubscribers(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClassId, GERTICO::HandleSet &theAttributes)
{
  SubscribedClass *subscribedClass;
  
  try
  {
    subscribedClass = getSubscribedClass(theClassId);
  }
  catch (GeRtiFactory::ObjectClassNotSubscribed &)
  {
    return false;
  }

  return subscribedClass->checkActiveSubscribers(theFederate, theAttributes);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribedClassHolder::clear(void)
{
  SubscribedClass *currSubscribedClass;
  SubscribedClassMap::iterator itSC;

  for (itSC = subObjectClassMap.begin(); itSC != subObjectClassMap.end(); itSC = subObjectClassMap.begin())
  {
    currSubscribedClass = itSC->second;
    subObjectClassMap.erase(itSC);
    delete currSubscribedClass;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribedClassHolder::getDesiredAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClassId, GERTICO::HandleSet const &theEventAttributes, GERTICO::HandleSet &theDesiredAttributes)
{
  GERTICO::SubscribedClass *subscribedClass;
  GERTICO::SubscribedClassMap::iterator itSubscribedClassMap;

  theDesiredAttributes.clear();

  itSubscribedClassMap = subObjectClassMap.find(theClassId);
  if (itSubscribedClassMap != subObjectClassMap.end())
  {
    subscribedClass = itSubscribedClassMap->second;
    subscribedClass->getDesiredAttributes(theFederate, theEventAttributes, theDesiredAttributes);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::SubscribedClass* GERTICO::SubscribedClassHolder::getSubscribedClass(GeRtiFactory::GeRtiHandle const &classId)
  throw (GeRtiFactory::ObjectClassNotSubscribed)
{
  CORBA::WChar *wChar = L"";
  GERTICO::SubscribedClassMap::iterator iClass;
  
  pm.acquire();
  iClass = subObjectClassMap.find(classId);
  if (iClass == subObjectClassMap.end())
  {
    pm.release();
    throw GeRtiFactory::ObjectClassNotSubscribed(wChar);
  }
  pm.release();

  return iClass->second;
}

// ---------------------------------------------------------------------------
// Check whether an object instance attribute is subscribed for any object in
// the given region.
// ---------------------------------------------------------------------------
bool GERTICO::SubscribedClassHolder::isRegionSubscribed(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theRegion)
{
  GERTICO::SubscribedClass *currSubscribedClass;
  GERTICO::SubscribedClassMap::iterator itSC;

  for (itSC = subObjectClassMap.begin(); itSC != subObjectClassMap.end(); itSC++)
  {
    currSubscribedClass = itSC->second;
    if (currSubscribedClass->isRegionSubscribed(theFederate, theRegion))
    {
      return true;
    }
  }

  return false;
}
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribedClassHolder::restoreSubscribedClasses(DOMElement &theDOMElement)
{
  DOMNode *child;
  SubscribedClass *currSubscribedClass;
  char *tmpChar;
  unsigned long tmpID;

  // Restore the subscribed classes,
  for (child = theDOMElement.getFirstChild(); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode("class")) == 0)
      {
        tmpChar = XMLString::transcode(((DOMElement *)child)->getAttribute(XMLString::transcode("objectClass")));
        sscanf(tmpChar, "%lu", &tmpID);
        currSubscribedClass = new SubscribedClass(tmpID);
        currSubscribedClass->restore(*((DOMElement *)child));
        subObjectClassMap[tmpID] = currSubscribedClass;
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribedClassHolder::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel1;
  GERTICO::SubscribedClassMap::iterator itS;
  XMLCh tempStr[100];

  XMLString::transcode(subscribedClassesStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel1);

  for (itS = subObjectClassMap.begin(); itS != subObjectClassMap.end(); itS++)
  {
    itS->second->save(theDOMDocument, *elemLevel1);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribedClassHolder::subscribeObjectClassAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet &theAttributes, CORBA::Boolean const &theActive)
{
  GERTICO::SubscribedClass *currSubscribedClass;

  // Check if object class already administered.
  try
  {
    currSubscribedClass = getSubscribedClass(theObjectClass);
    // Have an object class.
    currSubscribedClass->addSubAttributes(theFederate, theAttributes, theActive);
  }
  catch(GeRtiFactory::ObjectClassNotSubscribed &)
  {
    // Create an object class.
    currSubscribedClass = new GERTICO::SubscribedClass(theObjectClass);
    currSubscribedClass->addSubAttributes(theFederate, theAttributes, theActive);
    
    subObjectClassMap[theObjectClass] = currSubscribedClass;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribedClassHolder::subscribeObjectClassAttributesWithRegion(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSetMap &theAttributeRegions, const CORBA::Boolean &theActive)
{
  GERTICO::SubscribedClass *currSubscribedClass;

  // Check if object class already administered.
  try
  {
    currSubscribedClass = getSubscribedClass(theObjectClass);
    // Have an object class.
    currSubscribedClass->addSubAttributesWithRegion(theFederate, theAttributeRegions, theActive);
  }
  catch (GeRtiFactory::ObjectClassNotSubscribed &)
  {
    // Create an object class.
    currSubscribedClass = new GERTICO::SubscribedClass(theObjectClass);
    currSubscribedClass->addSubAttributesWithRegion(theFederate, theAttributeRegions, theActive);
    
    subObjectClassMap[theObjectClass] = currSubscribedClass;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribedClassHolder::unsubscribeObjectClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet const &theRegions)
{
  CORBA::WChar *wChar = L"";
  GERTICO::HandleSet::const_iterator itRegion;
  GERTICO::SubscribedClass *currSubscribedClass;
  GERTICO::SubscribedClassMap::iterator itSC;

  // Find the object class.
  itSC = subObjectClassMap.find(theObjectClass);
  if (itSC != subObjectClassMap.end())
  {
    currSubscribedClass = itSC->second;
    for (itRegion = theRegions.begin(); itRegion != theRegions.end(); itRegion++)
    {
      currSubscribedClass->delSubObjectClass(theFederate, *itRegion);
    }
    if (currSubscribedClass->isEmpty())
    {
      subObjectClassMap.erase(itSC);
    }
  }
#ifndef IEEE_1516
  else
  {
    throw GeRtiFactory::ObjectClassNotSubscribed(wChar);
  }
#endif
}

#ifdef IEEE_1516
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SubscribedClassHolder::unsubscribeObjectClassWithAttributeRegions(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, const GERTICO::HandleSetMap &theAttributeRegions)
{
  CORBA::WChar *wChar = L"";
  GERTICO::HandleSetMap::const_iterator itAttribute;
  GERTICO::SubscribedClass *currSubscribedClass;
  GERTICO::SubscribedClassMap::iterator itSC;

  // Find the object class.
  itSC = subObjectClassMap.find(theObjectClass);
  if (itSC != subObjectClassMap.end())
  {
    currSubscribedClass = itSC->second;
    for (itAttribute = theAttributeRegions.begin(); itAttribute != theAttributeRegions.end(); itAttribute++)
    {
      currSubscribedClass->delSubObjectClass(theFederate, itAttribute->first, itAttribute->second);
    }
    if (currSubscribedClass->isEmpty())
    {
      subObjectClassMap.erase(itSC);
    }
  }
}
#endif
