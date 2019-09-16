/*********************************************************************************
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** Interaction.cpp
**
*******************************************************************************/

#include "Interaction.h"
#include "Util/Mapper.h"

std::string GERTICO::Interaction::federateStr("federate");
std::string GERTICO::Interaction::publisherStr("publisher");
std::string GERTICO::Interaction::publishersStr("publishers");
std::string GERTICO::Interaction::subscriberStr("subscriber");
std::string GERTICO::Interaction::subscribersStr("subscribers");

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
GERTICO::PublishInteractionFlags::PublishInteractionFlags(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::PublishInteractionFlags::~PublishInteractionFlags(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublishInteractionFlags::getSubscribers(GERTICO::HandleSet &theSubscribers)
{
  GERTICO::HandleBoolMap::iterator itTurnedOn;

  // Make sure the list is clean.
  theSubscribers.clear();

  // Take all subscribers
  for (itTurnedOn = turnedOn.begin(); itTurnedOn != turnedOn.end(); itTurnedOn++)
  {
    theSubscribers.insert(itTurnedOn->first);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::PublishInteractionFlags::getTurnedOn(GeRtiFactory::GeRtiHandle const &theFederateSubscriber)
{
  GERTICO::HandleBoolMap::iterator itTurnedOn;
  bool ret = false;

  itTurnedOn = turnedOn.find(theFederateSubscriber);
  if (itTurnedOn != turnedOn.end())
  {
    ret = itTurnedOn->second;
  }

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublishInteractionFlags::print(void)
{
  GERTICO::HandleBoolMap::iterator itHandleBoolMap;

  for (itHandleBoolMap = turnedOn.begin(); itHandleBoolMap != turnedOn.end(); itHandleBoolMap++)
  {
//    std::cout << "Subscriber federate= " << itHandleBoolMap->first << " turned on= " << itHandleBoolMap->second << std::endl;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublishInteractionFlags::setTurnedOn(GeRtiFactory::GeRtiHandle const &theFederateSubscriber, bool const &theTurnedOn)
{
  GERTICO::HandleBoolMap::iterator itTurnedOn;

  itTurnedOn = turnedOn.find(theFederateSubscriber);
  if (itTurnedOn != turnedOn.end())
  {
    itTurnedOn->second = theTurnedOn;
  }
  else
  {
    turnedOn[theFederateSubscriber] = theTurnedOn;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Interaction::Interaction(GeRtiFactory::GeRtiHandle const &theInteraction)
{
  myInteractionId = theInteraction;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Interaction::~Interaction(void)
{
  fedInteractionSubscribers.clear();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Interaction::addSubInteraction(GeRtiFactory::GeRtiHandle const &theFederate, CORBA::Boolean const &theActive, GeRtiFactory::GeRtiHandle const &theRegion)
{
  GERTICO::HandleSet regions;
  Subscriber *currSubscriber;
  SubscriberMap::iterator itFIS;

  regions.insert(theRegion);
  itFIS = fedInteractionSubscribers.find(theFederate);
  if (itFIS != fedInteractionSubscribers.end())
  {
    currSubscriber = &itFIS->second;

    currSubscriber->addActiveRegion(theActive, regions);
  }
  else
  {
    Subscriber fedInteractionSubscribed;
    fedInteractionSubscribed.addActiveRegion(theActive, regions);

    fedInteractionSubscribers[theFederate] = fedInteractionSubscribed;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Interaction::checkActiveSubscribers(GeRtiFactory::GeRtiHandle const &theFederate)
{
  Subscriber *currSubscriber;
  SubscriberMap::iterator itFIS;

  for (itFIS = fedInteractionSubscribers.begin();
       itFIS != fedInteractionSubscribers.end();
       itFIS++)
  {
    // Do not take this fed.
    if (itFIS->first == theFederate)
    {
      continue;
    }

    // Do not take passive subscriber.
    currSubscriber = &itFIS->second;
    if (currSubscriber->checkActiveSubscriber() == false)
    {
      continue;
    }

    // Have an active subscriber.
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Interaction::checkSubscriber(GeRtiFactory::GeRtiHandle const &theFederate)
{
  Subscriber *currSubscriber;
  SubscriberMap::iterator itFIS;

  itFIS = fedInteractionSubscribers.find(theFederate);
  if (itFIS != fedInteractionSubscribers.end())
  {
    currSubscriber = &itFIS->second;
    if (currSubscriber->checkSubscribedDefault())
    {
      // Have a subscriber.
      return true;
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Interaction::getFederateRegions(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleBoolMap &theRegions)
{
  Subscriber *currSubscriber;
  SubscriberMap::iterator itSubscriber;

  itSubscriber = fedInteractionSubscribers.find(theFederate);
  if (itSubscriber != fedInteractionSubscribers.end())
  {
    currSubscriber = &itSubscriber->second;
    currSubscriber->getRegions(theRegions);
  }
}

// ---------------------------------------------------------------------------
// Only remove the subscribed interaction for the region.
// ---------------------------------------------------------------------------
void GERTICO::Interaction::delSubInteraction(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion)
{
  Subscriber *currSubscriber;
  SubscriberMap::iterator itFIS;

  itFIS = fedInteractionSubscribers.find(theFederate);
  if (itFIS != fedInteractionSubscribers.end())
  {
    currSubscriber = &itFIS->second;
    currSubscriber->delRegion(theRegion);
    if (currSubscriber->isEmpty())
    {
      // No values are set.
      fedInteractionSubscribers.erase(itFIS);
    }
  }
  else
  {
#ifndef IEEE_1516
    CORBA::WChar *wChar = L"delSubInteraction";

    throw GeRtiFactory::InteractionClassNotSubscribed(wChar);
#endif
  }

  return;
}

// ---------------------------------------------------------------------------
// Create a set of publishers who are actively publishing.
// ---------------------------------------------------------------------------
void GERTICO::Interaction::delSubscribedRegions(GeRtiFactory::GeRtiHandle const &theFederate)
{
  GERTICO::HandleBoolMap regions;
  GERTICO::HandleBoolMap::iterator itHBM;
  Subscriber *subscriber;
  SubscriberMap::iterator itSM;

  itSM = fedInteractionSubscribers.find(theFederate);
  if (itSM != fedInteractionSubscribers.end())
  {
    subscriber = &itSM->second;
    subscriber->getRegions(regions);
    for (itHBM = regions.begin(); itHBM != regions.end(); itHBM++)
    {
      subscriber->delRegion(itHBM->first);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Interaction::getActiveSubscribers(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theSubscribers)
{
  Subscriber *currSubscriber;
  SubscriberMap::iterator itFIS;

  for (itFIS = fedInteractionSubscribers.begin();
       itFIS != fedInteractionSubscribers.end();
       itFIS++)
  {
    // Do not take this fed.
    if (itFIS->first == theFederate)
    {
      continue;
    }

    // Do not take passive subscriber.
    currSubscriber = &itFIS->second;
    if (currSubscriber->checkActiveSubscriber() == false)
    {
      continue;
    }

    // Have an active subscriber.
    theSubscribers.insert(itFIS->first);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Interaction::getPassiveSubscribers(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theSubscribers)
{
  Subscriber *currSubscriber;
  SubscriberMap::iterator itFIS;

  for (itFIS = fedInteractionSubscribers.begin();
       itFIS != fedInteractionSubscribers.end();
       itFIS++)
  {
    // Do not take this fed.
    if (itFIS->first == theFederate)
    {
      continue;
    }

    // Do not take active subscriber.
    currSubscriber = &itFIS->second;
    if (currSubscriber->checkActiveSubscriber())
    {
      continue;
    }

    // Have an active subscriber.
    theSubscribers.insert(itFIS->first);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::Interaction::getId(void)
{
  return myInteractionId;
}

// ---------------------------------------------------------------------------
// Check all maps and sets - true only if all are empty.
// ---------------------------------------------------------------------------
bool GERTICO::Interaction::isEmpty(void)
{
  size_t len;

  len = fedInteractionSubscribers.size();
  if (len)
  {
    return false;
  }

  return true;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Interaction::isRegionSubscribed(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion)
{
  Subscriber *subscriber;
  SubscriberMap::iterator itSM;

  itSM = fedInteractionSubscribers.find(theFederate);
  if (itSM != fedInteractionSubscribers.end())
  {
    subscriber = &itSM->second;
    return subscriber->isRegionSubscribed(theRegion);
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
/*
void GERTICO::Interaction::print(void)
{
  Subscriber *currSubscriber;
  SubscriberMap::iterator itFIS;
  HandleBoolMap::iterator itHS;

  for (itFIS = fedInteractionSubscribers.begin(); itFIS != fedInteractionSubscribers.end(); itFIS++)
  {
    currSubscriber = itFIS->second;
    currSubscriber->print();
  }
}
*/

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Interaction::restore(DOMElement &theDOMElement, GERTICO::HandleBoolMap &theFedInteractionRelevanceAdvisorySwitchMap)
{
  DOMNode *child;
  DOMNode *childSub;
  GERTICO::Subscriber subscriber;
  char *tmpChar;
  unsigned long tmpFED;

  // Restore the intersections,
  child = theDOMElement.getFirstChild();
  while (child != 0)
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode(subscribersStr.c_str())) == 0)
      {
        // Restore the subscribers,
        childSub = child->getFirstChild();
        while (childSub != 0)
        {
          if (childSub->getNodeType() == DOMNode::ELEMENT_NODE)
          {
            if (XMLString::compareString(childSub->getNodeName(),XMLString::transcode(subscriberStr.c_str())) == 0)
            {
              tmpChar = XMLString::transcode(((DOMElement*)childSub)->getAttribute(XMLString::transcode(federateStr.c_str())));
              sscanf(tmpChar, "%lu", &tmpFED);
              subscriber.restore(*((DOMElement*) childSub));
              fedInteractionSubscribers[tmpFED] = subscriber;
            }
          }
          // Repeat for subscriber.
          childSub = childSub->getNextSibling();
        }
      }
    }

    // Repeat for all children.
    child = child->getNextSibling();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Interaction::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel2;
  DOMElement* elemLevel3;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  GERTICO::HandleSet::iterator itPM;
  SubscriberMap::iterator itSM;
  char buf[128];

  XMLString::transcode(subscribersStr.c_str(), tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel2);

  for (itSM = fedInteractionSubscribers.begin(); itSM != fedInteractionSubscribers.end(); itSM++)
  {
    XMLString::transcode(subscriberStr.c_str(), tempStr, 99);
    elemLevel3 = theDOMDocument.createElement(tempStr);
    elemLevel2->appendChild(elemLevel3);

    XMLString::transcode(federateStr.c_str(), tempStr, 99);
    sprintf(buf, "%lu", itSM->first);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel3->setAttribute(tempStr, tempStr1);

    itSM->second.save(theDOMDocument, *elemLevel3);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::InteractionHolder::InteractionHolder(GERTICO::InteractionMap &theInteractionMap, GERTICO::RegionsHolder &theRegionsHolder, GERTICO::SupportingServicesEC &theSupportingServicesEC) : interactionMap(theInteractionMap), regionsHolder(theRegionsHolder), supportingServicesEC(theSupportingServicesEC)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::InteractionHolder::~InteractionHolder(void)
{
  GERTICO::Interaction *currInteraction;
  GERTICO::InteractionMap::iterator itIM;

  for (itIM = interactionMap.begin(); itIM != interactionMap.end(); itIM = interactionMap.begin())
  {
    currInteraction = itIM->second;
    interactionMap.erase(itIM);
    delete currInteraction;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::addInteractionClassRegionPub(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction)
{
  GERTICO::FedPublishInteractionFlagsMap::iterator itFedPublishInteractionFlagsMap;
  GERTICO::PublishInteractionFlags publishInteractionFlags;
  GERTICO::PublishInteractionFlagsMap::iterator itPIF;

  pm.acquire();
  itFedPublishInteractionFlagsMap = fedPublishInteractionFlagsMap.find(theFederate);
  if (itFedPublishInteractionFlagsMap == fedPublishInteractionFlagsMap.end())
  {
    GERTICO::PublishInteractionFlagsMap dummy;

    fedPublishInteractionFlagsMap[theFederate] = dummy;
  }

  itFedPublishInteractionFlagsMap = fedPublishInteractionFlagsMap.find(theFederate);
  if (itFedPublishInteractionFlagsMap != fedPublishInteractionFlagsMap.end())
  {
    itPIF = itFedPublishInteractionFlagsMap->second.find(theInteraction);
    if (itPIF == itFedPublishInteractionFlagsMap->second.end())
    {
      itFedPublishInteractionFlagsMap->second[theInteraction] = publishInteractionFlags;
    }
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::addInteractionClassRegionSub(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet const &theRegions, bool const &theActive)
{
  GERTICO::HandleSet::const_iterator itRegion;
  GERTICO::FedSubInteractionFlagsMap::iterator itFedSubInteractionFlagsMap;
  SubInteractionFlagMap *currSubInteractionFlagMap;
  SubInteractionFlagMap::iterator itSI;
  SubInteractionFlagsMap::iterator itSIF;

  itFedSubInteractionFlagsMap = fedSubInteractionFlagsMap.find(theFederate);
  if (itFedSubInteractionFlagsMap == fedSubInteractionFlagsMap.end())
  {
    GERTICO::SubInteractionFlagsMap dummy;

    fedSubInteractionFlagsMap[theFederate] = dummy;
  }

  itFedSubInteractionFlagsMap = fedSubInteractionFlagsMap.find(theFederate);
  if (itFedSubInteractionFlagsMap != fedSubInteractionFlagsMap.end())
  {
    itSIF = itFedSubInteractionFlagsMap->second.find(theInteraction);
    if (itSIF != itFedSubInteractionFlagsMap->second.end())
    {
      // Have the class.
      currSubInteractionFlagMap = &itSIF->second;
      for (itRegion = theRegions.begin(); itRegion != theRegions.end(); itRegion++)
      {
        itSI = currSubInteractionFlagMap->find(*itRegion);
        if (itSI == currSubInteractionFlagMap->end())
        {
          // Add the region.
          (*currSubInteractionFlagMap)[*itRegion] = theActive;
        }
      }
    }
    else
    {
      // Do not have class or region:
      // Add the region
      SubInteractionFlagMap newSubInteractionFlagMap;
      for (itRegion = theRegions.begin(); itRegion != theRegions.end(); itRegion++)
      {
        newSubInteractionFlagMap[*itRegion] = theActive;
      }
      // Add the intersection.
      itFedSubInteractionFlagsMap->second[theInteraction] = newSubInteractionFlagMap;
    }
  }
}

// ---------------------------------------------------------------------------
// NB: caller must secure the mutex lock.
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::addTurnOffForInteraction(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::FedEventSenderMap &theFedEventSenderMap)
{
  GERTICO::FedEventSenderMap::iterator itFedEventSenderMap;
  GERTICO::FedPublishInteractionFlagsMap::iterator itFedPublishInteractionFlagsMap;
  GERTICO::PublishInteractionFlagsMap::iterator itPublishInteractionFlagsMap;

  pm.acquire();
  itFedPublishInteractionFlagsMap = fedPublishInteractionFlagsMap.find(theFederate);
  if (itFedPublishInteractionFlagsMap != fedPublishInteractionFlagsMap.end())
  {
    itPublishInteractionFlagsMap = itFedPublishInteractionFlagsMap->second.find(theInteraction);
    if (itPublishInteractionFlagsMap != itFedPublishInteractionFlagsMap->second.end())
    {
      if (itPublishInteractionFlagsMap->second.getTurnedOn(theFederate))
      {
        GeRtiFactory::GertiDmEvent gertiDmEvent;

        // Subscribe interaction class.
        gertiDmEvent.service = 13;
        gertiDmEvent.sourceId = theFederate;
        gertiDmEvent.theHandle = theInteraction;
        itFedEventSenderMap = theFedEventSenderMap.find(theFederate);
        if (itFedEventSenderMap != theFedEventSenderMap.end())
        {
          itFedEventSenderMap->second->addDmEvent(gertiDmEvent);
        }
        itPublishInteractionFlagsMap->second.setTurnedOn(theFederate, false);
      }
    }
  }
  pm.release();
}

// ---------------------------------------------------------------------------
// NB: caller must secure the mutex lock.
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::addTurnOnForInteraction(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet &theActiveSubscribers, GERTICO::HandleSet &thePassiveSubscribers)
{
  GERTICO::HandleSet::iterator itHandleSet;
  GERTICO::FedPublishInteractionFlagsMap::iterator itFedPublishInteractionFlagsMap;
  GERTICO::PublishInteractionFlagsMap::iterator itPublishInteractionFlagsMap;

  pm.acquire();
  itFedPublishInteractionFlagsMap = fedPublishInteractionFlagsMap.find(theFederate);
  if (itFedPublishInteractionFlagsMap != fedPublishInteractionFlagsMap.end())
  {
    itPublishInteractionFlagsMap = itFedPublishInteractionFlagsMap->second.find(theInteraction);
    if (itPublishInteractionFlagsMap != itFedPublishInteractionFlagsMap->second.end())
    {
      for (itHandleSet = theActiveSubscribers.begin(); itHandleSet != theActiveSubscribers.end(); itHandleSet++)
      {
        if (itPublishInteractionFlagsMap->second.getTurnedOn(*itHandleSet) == false)
        {
          itPublishInteractionFlagsMap->second.setTurnedOn(*itHandleSet, true);
        }
      }
      for (itHandleSet = thePassiveSubscribers.begin(); itHandleSet != thePassiveSubscribers.end(); itHandleSet++)
      {
        if (itPublishInteractionFlagsMap->second.getTurnedOn(*itHandleSet) == false)
        {
          itPublishInteractionFlagsMap->second.setTurnedOn(*itHandleSet, true);
        }
      }
    }
  }
  pm.release();
}

// ---------------------------------------------------------------------------
// For the given federate and interaction class, check for active subscribers.
// ---------------------------------------------------------------------------
bool GERTICO::InteractionHolder::checkActiveSubscribers(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction)
{
  GeRtiFactory::GeRtiHandle currInteraction;

  currInteraction = theInteraction;

  // Go to parents of class.
  while (currInteraction)
  {
    if (checkClassActiveSubscribers(theFederate, currInteraction))
    {
      return true;
    }

    // Get current class from interaction tree.
    currInteraction = supportingServicesEC.getInteractionParent(currInteraction);
  }

  return false;
}

// ---------------------------------------------------------------------------
// For the given federate and interaction class, check for active subscribers.
// ---------------------------------------------------------------------------
bool GERTICO::InteractionHolder::checkClassActiveSubscribers(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction)
{
  Interaction *currInteraction;
  InteractionMap::iterator itI;

  itI = interactionMap.find(theInteraction);
  if (itI != interactionMap.end())
  {
    currInteraction = itI->second;
    if (currInteraction->checkActiveSubscribers(theFederate))
    {
      return true;
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::InteractionHolder::checkSubscriber(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction)
{
  Interaction *currInteraction;
  InteractionMap::iterator itI;

  itI = interactionMap.find(theInteraction);
  if (itI != interactionMap.end())
  {
    currInteraction = itI->second;
    if (currInteraction->checkSubscriber(theFederate))
    {
      return true;
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::clear(void)
{
  GERTICO::Interaction *currInteraction;
  GERTICO::InteractionMap::iterator itI;

  pm.acquire();
  fedPublishInteractionFlagsMap.clear();
  fedSubInteractionFlagsMap.clear();
  for (itI = interactionMap.begin(); itI != interactionMap.end(); itI = interactionMap.begin())
  {
    currInteraction = itI->second;
    interactionMap.erase(itI);
    delete currInteraction;
  }
  fedInteractionRegions.clear();
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::delInteractionClassRegionSub(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GeRtiFactory::GeRtiHandle const &theRegion)
{
  GERTICO::FedSubInteractionFlagsMap::iterator itFedSubInteractionFlagsMap;
  GERTICO::SubInteractionFlagMap *currSubInteractionFlagMap;
  GERTICO::SubInteractionFlagMap::iterator itSI;
  GERTICO::SubInteractionFlagsMap::iterator itSIF;

  itFedSubInteractionFlagsMap = fedSubInteractionFlagsMap.find(theFederate);
  if (itFedSubInteractionFlagsMap != fedSubInteractionFlagsMap.end())
  {
    itSIF = itFedSubInteractionFlagsMap->second.find(theInteraction);
    if (itSIF != itFedSubInteractionFlagsMap->second.end())
    {
      // Have the class.
      currSubInteractionFlagMap = &itSIF->second;
      itSI = currSubInteractionFlagMap->find(theRegion);
      if (itSI != currSubInteractionFlagMap->end())
      {
        // Delete the region.
        currSubInteractionFlagMap->erase(itSI);
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::delInteractionClassRegionSubs(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction)
{
  GERTICO::FedSubInteractionFlagsMap::iterator itFedSubInteractionFlagsMap;
  SubInteractionFlagMap *currSubInteractionFlagMap;
  SubInteractionFlagMap::iterator itSI;
  SubInteractionFlagsMap::iterator itSIF;

  itFedSubInteractionFlagsMap = fedSubInteractionFlagsMap.find(theFederate);
  if (itFedSubInteractionFlagsMap != fedSubInteractionFlagsMap.end())
  {
    itSIF = itFedSubInteractionFlagsMap->second.find(theInteraction);
    if (itSIF != itFedSubInteractionFlagsMap->second.end())
    {
      // Have the class.
      currSubInteractionFlagMap = &itSIF->second;
      // Delete the regions.
      currSubInteractionFlagMap->clear();
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::getActiveSubscribers(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet &theSubscribers)
{
  Interaction *currInteraction;
  InteractionMap::iterator itI;

  itI = interactionMap.find(theInteraction);
  if (itI != interactionMap.end())
  {
    currInteraction = itI->second;
    currInteraction->getActiveSubscribers(theFederate, theSubscribers);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::getPassiveSubscribers(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet &theSubscribers)
{
  Interaction *currInteraction;
  InteractionMap::iterator itI;

  itI = interactionMap.find(theInteraction);
  if (itI != interactionMap.end())
  {
    currInteraction = itI->second;
    currInteraction->getPassiveSubscribers(theFederate, theSubscribers);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::getFederatesForInteraction(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet &theFederates)
{
  CORBA::ULong i;
  CORBA::ULong length;
  GERTICO::FedSubInteractionFlagsMap::iterator itFedSubInteractionFlagsMap;
  GERTICO::SubInteractionFlagsMap::iterator itSubInteractionFlagsMap;
  GeRtiFactory::Handles parents;

  supportingServicesEC.getInteractionParents(theInteraction, parents);
  length = parents.length();
  for (itFedSubInteractionFlagsMap = fedSubInteractionFlagsMap.begin(); itFedSubInteractionFlagsMap != fedSubInteractionFlagsMap.end(); itFedSubInteractionFlagsMap++)
  {
    if (itFedSubInteractionFlagsMap->first == theFederate)
    {
      continue;
    }
    itSubInteractionFlagsMap = itFedSubInteractionFlagsMap->second.find(theInteraction);
    if (itSubInteractionFlagsMap != itFedSubInteractionFlagsMap->second.end())
    {
      theFederates.insert(itFedSubInteractionFlagsMap->first);
      continue;
    }
    for (i = 0; i < length; i++)
    {
      itSubInteractionFlagsMap = itFedSubInteractionFlagsMap->second.find(parents[i]);
      if (itSubInteractionFlagsMap != itFedSubInteractionFlagsMap->second.end())
      {
        theFederates.insert(itFedSubInteractionFlagsMap->first);
        break;
      }
    }
  }
  /*
  GERTICO::FedPublishInteractionFlagsMap::iterator itFedPublishInteractionFlagsMap;
  GERTICO::PublishInteractionFlagsMap::iterator itPublishInteractionFlagsMap;

  pm.acquire();
  itFedPublishInteractionFlagsMap = fedPublishInteractionFlagsMap.find(theFederate);
  if (itFedPublishInteractionFlagsMap != fedPublishInteractionFlagsMap.end())
  {
    itPublishInteractionFlagsMap = itFedPublishInteractionFlagsMap->second.find(theInteraction);
    if (itPublishInteractionFlagsMap != itFedPublishInteractionFlagsMap->second.end())
    {
      itPublishInteractionFlagsMap->second.getSubscribers(theFederates);
    }
  }
  pm.release();
  */
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::getFederateRegions(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleBoolMap &theRegions)
{
  GERTICO::Interaction *currInteraction;
  GERTICO::InteractionMap::iterator itInteraction;

  // Check if interactions already administered.
  itInteraction = interactionMap.find(theInteraction);
  if (itInteraction != interactionMap.end())
  {
    // Have an interaction.
    currInteraction = itInteraction->second;
    currInteraction->getFederateRegions(theFederate, theRegions);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::getPublishedInteractionClasses(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &thePublishedInteractionClasses)
{
  GERTICO::FedPublishInteractionFlagsMap::iterator itFedPublishInteractionFlagsMap;
  GERTICO::PublishInteractionFlagsMap::iterator itPIF;

  pm.acquire();
  thePublishedInteractionClasses.clear();
  itFedPublishInteractionFlagsMap = fedPublishInteractionFlagsMap.find(theFederate);
  if (itFedPublishInteractionFlagsMap != fedPublishInteractionFlagsMap.end())
  {
    for (itPIF = itFedPublishInteractionFlagsMap->second.begin(); itPIF != itFedPublishInteractionFlagsMap->second.end(); itPIF++)
    {
      thePublishedInteractionClasses.insert(itPIF->first);
    }
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::getSubscribedInteractionClasses(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleBoolMap &theSubscribedInteractionClasses)
{
  GERTICO::FedSubInteractionFlagsMap::iterator itFedSubInteractionFlagsMap;
  GERTICO::SubInteractionFlagMap *subInteractionFlagMapPtr;
  GERTICO::SubInteractionFlagMap::iterator itSubInteractionFlagMap;
  GERTICO::SubInteractionFlagsMap::iterator itSIF;
  bool boolFlag;

  itFedSubInteractionFlagsMap = fedSubInteractionFlagsMap.find(theFederate);
  if (itFedSubInteractionFlagsMap != fedSubInteractionFlagsMap.end())
  {
    for (itSIF = itFedSubInteractionFlagsMap->second.begin(); itSIF != itFedSubInteractionFlagsMap->second.end(); itSIF++)
    {
      subInteractionFlagMapPtr = &itSIF->second;
      boolFlag = false;
      for (itSubInteractionFlagMap = subInteractionFlagMapPtr->begin(); itSubInteractionFlagMap != subInteractionFlagMapPtr->end(); itSubInteractionFlagMap++)
      {
        if (itSubInteractionFlagMap->second)
        {
          boolFlag = true;
          break;
        }
      }
      theSubscribedInteractionClasses[itSIF->first] = boolFlag;
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::interactionClassSubTurnOff(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSetMap &thePublishers)
{
  GeRtiFactory::GeRtiHandle currInteraction;
  GERTICO::FedPublishInteractionFlagsMap::iterator itFedPublishInteractionFlagsMap;
  GERTICO::HandleSetMap::iterator itThePublisher;
  GERTICO::PublishInteractionFlagsMap::iterator itPIF;
  Interaction *subInteraction;
  InteractionMap::iterator itI;
  bool subscriberFound;

  pm.acquire();
  thePublishers.clear();
  for (itFedPublishInteractionFlagsMap = fedPublishInteractionFlagsMap.begin(); itFedPublishInteractionFlagsMap != fedPublishInteractionFlagsMap.end(); itFedPublishInteractionFlagsMap++)
  {
    if (itFedPublishInteractionFlagsMap->first == theFederate)
    {
      continue;
    }

    for (itPIF = itFedPublishInteractionFlagsMap->second.begin(); itPIF != itFedPublishInteractionFlagsMap->second.end(); itPIF++)
    {
      subscriberFound = false;

      currInteraction = itPIF->first;
      for ( ; currInteraction != 0; currInteraction = supportingServicesEC.getInteractionParent(currInteraction))
      {
        // Check this level, if found
        itI = interactionMap.find(currInteraction);
        if (itI != interactionMap.end())
        {
          subInteraction = itI->second;
          if (subInteraction->checkActiveSubscribers(itFedPublishInteractionFlagsMap->first))
          {
            subscriberFound = true;
            break;
          }
        }
      }
      if (subscriberFound == false)
      {
        itPIF->second.setTurnedOn(theFederate, false);
        itThePublisher = thePublishers.find(itFedPublishInteractionFlagsMap->first);
        if (itThePublisher != thePublishers.end())
        {
          GERTICO::HandleSet *interactionClasses;
          interactionClasses = &itThePublisher->second;
          interactionClasses->insert(itPIF->first);
        }
        else
        {
          GERTICO::HandleSet interactionClasses;
          interactionClasses.insert(itPIF->first);
          thePublishers[itFedPublishInteractionFlagsMap->first] = interactionClasses;
        }
      }
    }
  }
  pm.release();
}

// ---------------------------------------------------------------------------
// For the given interaction class, turn off any publishers in derived classes
// if there are no subscribers in the given or in base classes.
// NB. If any publisher at the given or derived class is required, no
//     publisher will be turned off.
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::interactionSubTurnOff(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSetMap &thePublishers)
{
  GERTICO::HandleSet children;
  GERTICO::HandleSet::iterator itChild;

  interactionSubTurnOffFind(theFederate, theInteraction, thePublishers);

  // Get children.
  supportingServicesEC.getInteractionChildren(theInteraction, children);

  // Call function.
  for (itChild = children.begin(); itChild != children.end(); itChild++)
  {
    interactionSubTurnOffFind(theFederate, *itChild, thePublishers);
  }
}

// ---------------------------------------------------------------------------
// Function to get publishers in all derived classes.
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::interactionSubTurnOffFind(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSetMap &thePublishers)
{
  GERTICO::FedPublishInteractionFlagsMap::iterator itFedPublishInteractionFlagsMap;
  GERTICO::HandleMap::iterator itFHH;
  GERTICO::HandleSetMap::iterator itThePublisher;
  InteractionMap::iterator itI;
  GERTICO::PublishInteractionFlagsMap::iterator itPublishInteractionFlagsMap;

  pm.acquire();
  // Check this level, if found
  for (itFedPublishInteractionFlagsMap = fedPublishInteractionFlagsMap.begin(); itFedPublishInteractionFlagsMap != fedPublishInteractionFlagsMap.end(); itFedPublishInteractionFlagsMap++)
  {
    if (itFedPublishInteractionFlagsMap->first == theFederate)
    {
      continue;
    }
    itPublishInteractionFlagsMap = itFedPublishInteractionFlagsMap->second.find(theInteraction);
    if (itPublishInteractionFlagsMap == itFedPublishInteractionFlagsMap->second.end())
    {
      continue;
    }
    if (itPublishInteractionFlagsMap->second.getTurnedOn(theFederate))
    {
      if (checkActiveSubscribers(itFHH->first, theInteraction))
      {
        continue;
      }
      itPublishInteractionFlagsMap->second.setTurnedOn(theFederate, false);
      itThePublisher = thePublishers.find(itFHH->first);
      if (itThePublisher != thePublishers.end())
      {
        GERTICO::HandleSet *interactionClasses;
        interactionClasses = &itThePublisher->second;
        interactionClasses->insert(itFHH->second);
      }
      else
      {
        GERTICO::HandleSet interactionClasses;
        interactionClasses.insert(itFHH->second);
        thePublishers[itFHH->first] = interactionClasses;
      }
    }
  }
  pm.release();
}

// ---------------------------------------------------------------------------
// For the given interaction class check if there are any publishers in the
// given or in derived classes.
// NB. More than one turnOn may result from derived classes.
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::interactionSubTurnOn(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSetMap &thePublishers)
{
  GERTICO::HandleSet children;
  GERTICO::HandleSet::iterator itChild;

  interactionSubTurnOnFind(theFederate, theInteraction, thePublishers);

  // Get children.
  supportingServicesEC.getInteractionChildren(theInteraction, children);

  // Call function.
  for (itChild = children.begin(); itChild != children.end(); itChild++)
  {
    interactionSubTurnOnFind(theFederate, *itChild, thePublishers);
  }
}

// ---------------------------------------------------------------------------
// Recursive function to get publishers in all derived classes.
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::interactionSubTurnOnFind(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSetMap &thePublishers)
{
  GERTICO::FedPublishInteractionFlagsMap::iterator itFedPublishInteractionFlagsMap;
  GERTICO::HandleSet::iterator itHS;
  GERTICO::HandleSet publishers;
  GERTICO::HandleSetMap::iterator itHSM;
  GERTICO::InteractionMap::iterator itI;
  GERTICO::PublishInteractionFlagsMap::iterator itPublishInteractionFlagsMap;

  pm.acquire();
  // Check this level, if found
  for (itFedPublishInteractionFlagsMap = fedPublishInteractionFlagsMap.begin(); itFedPublishInteractionFlagsMap != fedPublishInteractionFlagsMap.end(); itFedPublishInteractionFlagsMap++)
  {
    if (itFedPublishInteractionFlagsMap->first == theFederate)
    {
      continue;
    }
    itPublishInteractionFlagsMap = itFedPublishInteractionFlagsMap->second.find(theInteraction);
    if (itPublishInteractionFlagsMap == itFedPublishInteractionFlagsMap->second.end())
    {
      continue;
    }

    onPublishers(theFederate, theInteraction, publishers);
    for (itHS = publishers.begin(); itHS != publishers.end(); itHS++)
    {
      // Export list of feds and known interaction ids.
      itHSM = thePublishers.find(*itHS);
      if (itHSM != thePublishers.end())
      {
        GERTICO::HandleSet *handleSetPtr;
        handleSetPtr = &itHSM->second;
        handleSetPtr->insert(itPublishInteractionFlagsMap->first);
      }
      else
      {
        GERTICO::HandleSet handleSet;
        handleSet.insert(itPublishInteractionFlagsMap->first);
        thePublishers[*itHS] = handleSet;
      }
    }
  }
  pm.acquire();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::turnOnPublisher(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::FedEventSenderMap &theFedEventSenderMap)
{
  GERTICO::FedEventSenderMap::iterator itFedEventSenderMap;
  GERTICO::FedPublishInteractionFlagsMap::iterator itFedPublishInteractionFlagsMap;
  GERTICO::PublishInteractionFlagsMap::iterator itPublishInteractionFlagsMap;

  pm.acquire();
  itFedPublishInteractionFlagsMap = fedPublishInteractionFlagsMap.find(theFederate);
  if (itFedPublishInteractionFlagsMap != fedPublishInteractionFlagsMap.end())
  {
    itPublishInteractionFlagsMap = itFedPublishInteractionFlagsMap->second.find(theInteraction);
    if (itPublishInteractionFlagsMap != itFedPublishInteractionFlagsMap->second.end())
    {
      if (itPublishInteractionFlagsMap->second.getTurnedOn(theFederate) == false)
      {
        GeRtiFactory::GertiDmEvent gertiDmEvent;

        // Subscribe interaction class.
        gertiDmEvent.service = 12;
        gertiDmEvent.sourceId = theFederate;
        gertiDmEvent.theHandle = theInteraction;

        itFedEventSenderMap = theFedEventSenderMap.find(theFederate);
        if (itFedEventSenderMap != theFedEventSenderMap.end())
        {
          itFedEventSenderMap->second->addDmEvent(gertiDmEvent);
        }
        itPublishInteractionFlagsMap->second.setTurnedOn(theFederate, true);
      }
    }
  }
  pm.release();
}

// ---------------------------------------------------------------------------
// Create a set of publishers who are not yet publishing.
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::onPublishers(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet &thePublishers)
{
  GERTICO::FedPublishInteractionFlagsMap::iterator itFedPublishInteractionFlagsMap;
  GERTICO::PublishInteractionFlagsMap::iterator itPublishInteractionFlagsMap;

  pm.acquire();
  // Clear out any previous publishers.
  thePublishers.clear();

  for (itFedPublishInteractionFlagsMap = fedPublishInteractionFlagsMap.begin(); itFedPublishInteractionFlagsMap != fedPublishInteractionFlagsMap.end(); itFedPublishInteractionFlagsMap++)
  {
    if (itFedPublishInteractionFlagsMap->first == theFederate)
    {
      continue;
    }
    itPublishInteractionFlagsMap = itFedPublishInteractionFlagsMap->second.find(theInteraction);
    if (itPublishInteractionFlagsMap == itFedPublishInteractionFlagsMap->second.end())
    {
      continue;
    }
    if (itPublishInteractionFlagsMap->second.getTurnedOn(theFederate))
    {
      continue;
    }

    // Have an non-publishing publisher.
    thePublishers.insert(itFedPublishInteractionFlagsMap->first);
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::print(void)
{
  GERTICO::FedPublishInteractionFlagsMap::iterator itFedPublishInteractionFlagsMap;
  GERTICO::FedSubInteractionFlagsMap::iterator itFedSubInteractionFlagsMap;
  GERTICO::PublishInteractionFlagsMap::iterator itPublishInteractionFlagsMap;
  GERTICO::SubInteractionFlagMap::iterator itSubInteractionFlagMap;
  GERTICO::SubInteractionFlagsMap::iterator itSubInteractionFlagsMap;

  for (itFedPublishInteractionFlagsMap = fedPublishInteractionFlagsMap.begin(); itFedPublishInteractionFlagsMap != fedPublishInteractionFlagsMap.end(); itFedPublishInteractionFlagsMap++)
  {
    for (itPublishInteractionFlagsMap = itFedPublishInteractionFlagsMap->second.begin(); itPublishInteractionFlagsMap != itFedPublishInteractionFlagsMap->second.end(); itPublishInteractionFlagsMap++)
    {
      itPublishInteractionFlagsMap->second.print();
    }
  }

  for (itFedSubInteractionFlagsMap = fedSubInteractionFlagsMap.begin(); itFedSubInteractionFlagsMap != fedSubInteractionFlagsMap.end(); itFedSubInteractionFlagsMap++)
  {
    for (itSubInteractionFlagsMap = itFedSubInteractionFlagsMap->second.begin(); itSubInteractionFlagsMap != itFedSubInteractionFlagsMap->second.end(); itSubInteractionFlagsMap++)
    {
      for (itSubInteractionFlagMap = itSubInteractionFlagsMap->second.begin(); itSubInteractionFlagMap != itSubInteractionFlagsMap->second.end(); itSubInteractionFlagMap++)
      {
      }
    }
  }
  /*
  typedef std::map <GeRtiFactory::GeRtiHandle, bool> SubInteractionFlagMap;
  typedef std::map <GeRtiFactory::GeRtiHandle, PublishInteractionFlags> PublishInteractionFlagsMap;
  typedef std::map <GeRtiFactory::GeRtiHandle, SubInteractionFlagMap> SubInteractionFlagsMap;
  */
    // Key: <federate id < interaction class id, PublishInteractionFlags >>
    // GERTICO::FedPublishInteractionFlagsMap fedPublishInteractionFlagsMap;
    // Key: <federate id <interaction class id < region id, bool >>>
    // GERTICO::FedSubInteractionFlagsMap fedSubInteractionFlagsMap;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::publishInteractionClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::FedEventSenderMap &theFedEventSenderMap)
{
  CORBA::WChar *wChar = L"";
  GERTICO::HandleSet activeSubscribers;
  GERTICO::HandleSet passiveSubscribers;
  InteractionMap::iterator itI;
  bool gotMomClass = false;


  print();
  if (supportingServicesEC.isDerivedInteractionClass(theInteraction, momManagerInteractionRoot))
  {
    gotMomClass = true;
  }

  // Add to federate.
  addInteractionClassRegionPub(theFederate, theInteraction);

  // Turn on fed if there are any active subscribers.
  if (gotMomClass || checkActiveSubscribers(theFederate, theInteraction))
  {
    // Turn the fed on.
    addTurnOnForInteraction(theFederate, theInteraction, activeSubscribers, passiveSubscribers);
    turnOnPublisher(theFederate, theInteraction, theFedEventSenderMap);
  }
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::restore(DOMElement &theDOMElement, unsigned long const &theInteraction, unsigned long const &theOrdering, unsigned long const &theTransportation)
{
  /*
  Interaction *currInteraction;

  currInteraction = new Interaction(theInteraction, theOrdering, theTransportation);
  currInteraction->restore(theDOMElement, federatesHolder);
  interactionMap[theInteraction] = currInteraction;
  */
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel0;
  DOMElement* elemLevel1;
  InteractionMap::iterator itIM;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[128];
  unsigned long ul;

  XMLString::transcode("interactions", tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);
  for (itIM = interactionMap.begin(); itIM != interactionMap.end(); itIM++)
  {
    XMLString::transcode("interaction", tempStr, 99);
    elemLevel1 = theDOMDocument.createElement(tempStr);
    elemLevel0->appendChild(elemLevel1);

    XMLString::transcode("id", tempStr, 99);
    ul = itIM->first;
    sprintf(buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel1->setAttribute(tempStr, tempStr1);

    itIM->second->save(theDOMDocument, *elemLevel1);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::setMomManagerInteractionRoot(GeRtiFactory::GeRtiHandle const &theMomManagerInteractionRoot)
{
  momManagerInteractionRoot = theMomManagerInteractionRoot;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::subscribeInteractionClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, CORBA::Boolean const &theActive, GERTICO::HandleSet const &theRegions, GERTICO::FedEventSenderMap &theFedEventSenderMap)
{
  CORBA::WChar *wChar = L"";
  GERTICO::HandleSet activeSubscribers;
  GERTICO::HandleSet passiveSubscribers;
  GERTICO::HandleSet *handleSetPtr;
  GERTICO::HandleSet::const_iterator itRegion;
  GERTICO::HandleSet::iterator itHandleSet;
  GERTICO::HandleSetMap publishers;
  GERTICO::HandleSetMap::iterator itPublisher;
  Interaction *currInteraction;
  InteractionMap::iterator itI;

  if (theActive != 0 && theActive != 1)
  {
    throw GeRtiFactory::RTIinternalError(L"invalid active boolean");
  }

  print();
  itI = interactionMap.find(theInteraction);
  if (itI != interactionMap.end())
  {
    // Have an interaction.
    currInteraction = itI->second;
    for (itRegion = theRegions.begin(); itRegion != theRegions.end(); itRegion++)
    {
      if (currInteraction->isRegionSubscribed(theFederate, *itRegion))
      {
        currInteraction->delSubscribedRegions(theFederate);
        delInteractionClassRegionSubs(theFederate, theInteraction);
      }
      currInteraction->addSubInteraction(theFederate, theActive, *itRegion);
    }
  }
  else
  {
    // Create an interaction.
    currInteraction = new Interaction(theInteraction);
    for (itRegion = theRegions.begin(); itRegion != theRegions.end(); itRegion++)
    {
      currInteraction->addSubInteraction(theFederate, theActive, *itRegion);
    }

    interactionMap[theInteraction] = currInteraction;
  }

  // Add to federate.
  addInteractionClassRegionSub(theFederate, theInteraction, theRegions, theActive);

  // Have an active subscriber check if there are any publishers.
  interactionSubTurnOn(theFederate, theInteraction, publishers);
  if (theActive)
  {
    activeSubscribers.insert(theFederate);
  }
  else
  {
    passiveSubscribers.insert(theFederate);
  }
  for (itPublisher = publishers.begin(); itPublisher != publishers.end(); itPublisher++)
  {
    handleSetPtr = &itPublisher->second;
    for (itHandleSet = handleSetPtr->begin(); itHandleSet != handleSetPtr->end(); itHandleSet++)
    {
      addTurnOnForInteraction(itPublisher->first, *itHandleSet, activeSubscribers, passiveSubscribers);
      turnOnPublisher(itPublisher->first, *itHandleSet, theFedEventSenderMap);
    }
  }
  /*
  if (theActive)
  {
    // Have an active subscriber check if there are any publishers.
    interactionSubTurnOn(theFederate, theInteraction, publishers);
    activeSubscribers.insert(theFederate);
    for (itPublisher = publishers.begin(); itPublisher != publishers.end(); itPublisher++)
    {
      handleSetPtr = &itPublisher->second;
      for (itHandleSet = handleSetPtr->begin(); itHandleSet != handleSetPtr->end(); itHandleSet++)
      {
        addTurnOnForInteraction(itPublisher->first, *itHandleSet, activeSubscribers, passiveSubscribers, theFedEventSenderMap);
      }
    }
  }
  else
  {
    // Have an non-active subscriber check if there are any publishers that only publish for this federate.
    interactionClassSubTurnOff(theFederate, theInteraction, publishers);
    for (itPublisher = publishers.begin(); itPublisher != publishers.end(); itPublisher++)
    {
      handleSetPtr = &itPublisher->second;
      for (itHandleSet = handleSetPtr->begin(); itHandleSet != handleSetPtr->end(); itHandleSet++)
      {
        addTurnOffForInteraction(itPublisher->first, *itHandleSet, theFedEventSenderMap);
      }
    }
  }
  */
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::subscribeInteractionClassWithRegions(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet const &theRegions)
{
  GERTICO::HandleSet regions;
  GERTICO::HandleSet *regionsPtr;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::HandleSet::const_iterator itRegionIn;
  GERTICO::HandleSetMap *interactionRegionsPtr;
  GERTICO::HandleSetMap::iterator itInteractionRegions;
  GERTICO::HandleSetSetMap::iterator itFedInteractioRegion;

  itFedInteractioRegion = fedInteractionRegions.find(theFederate);
  if (itFedInteractioRegion == fedInteractionRegions.end())
  {
    GERTICO::HandleSetMap interactionRegions;
    fedInteractionRegions[theFederate] = interactionRegions;
  }

  itFedInteractioRegion = fedInteractionRegions.find(theFederate);
  if (itFedInteractioRegion != fedInteractionRegions.end())
  {
    interactionRegionsPtr = &itFedInteractioRegion->second;
    itInteractionRegions = interactionRegionsPtr->find(theInteraction);
    if (itInteractionRegions != interactionRegionsPtr->end())
    {
      regionsPtr = &itInteractionRegions->second;
    }
    else
    {
      (*interactionRegionsPtr)[theInteraction] = regions;
      itInteractionRegions = interactionRegionsPtr->find(theInteraction);
      if (itInteractionRegions != interactionRegionsPtr->end())
      {
        regionsPtr = &itInteractionRegions->second;
      }
    }

    for (itRegionIn = theRegions.begin(); itRegionIn != theRegions.end(); itRegionIn++)
    {
      itRegion = regionsPtr->find(*itRegionIn);
      if (itRegion == regionsPtr->end())
      {
        regionsPtr->insert(*itRegionIn);
      }
      else
      {
        if (*itRegionIn != 0)
        {
          GERTICO::HandleSet regionsCopy;
          GERTICO::HandleSet::iterator itHS;

          // Take a copy to avoid iteration problems.
          regionsCopy = *regionsPtr;
          for (itHS = regionsCopy.begin(); itHS != regionsCopy.end(); itHS++)
          {
            if (*itHS == 0 || *itHS == *itRegionIn)
            {
              continue;
            }
            regionsPtr->erase(*itHS);
          }
        }
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::setPublishingInteraction(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, bool const &thePublishing)
{
  GERTICO::FedPublishInteractionFlagsMap::iterator itFedPublishInteractionFlagsMap;
  GERTICO::PublishInteractionFlagsMap::iterator itPIF;

  pm.acquire();
  itFedPublishInteractionFlagsMap = fedPublishInteractionFlagsMap.find(theFederate);
  if (itFedPublishInteractionFlagsMap != fedPublishInteractionFlagsMap.end())
  {
    itPIF = itFedPublishInteractionFlagsMap->second.find(theInteraction);
    if (itPIF != itFedPublishInteractionFlagsMap->second.end())
    {
      itPIF->second.setTurnedOn(theFederate, thePublishing);
    }
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
/*
void GERTICO::InteractionHolder::testRegionDimensions(GeRtiFactory::GeRtiHandle const &theInteractionClass, GERTICO::HandleSet const &theRegions)
{
  GERTICO::ClassDescr *classDescr;
  GERTICO::HandleSet dimensions;
  GERTICO::HandleSet::const_iterator itRegion;
  GERTICO::Region *region;

  classDescr = interactionRoot.getClassDescr(theInteractionClass);
  classDescr->getDimensions(dimensions);
  for (itRegion = theRegions.begin(); itRegion != theRegions.end(); itRegion++)
  {
    if (*itRegion == 0)
    {
      continue;
    }
    region = regionsHolder.getRegion(*itRegion);
    region->testDimensions(dimensions);
  }
}
*/

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::unpublishInteractionClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction)
{
  GERTICO::FedPublishInteractionFlagsMap::iterator itFedPublishInteractionFlagsMap;
  GERTICO::PublishInteractionFlagsMap::iterator itPIF;

  pm.acquire();
  itFedPublishInteractionFlagsMap = fedPublishInteractionFlagsMap.find(theFederate);
  if (itFedPublishInteractionFlagsMap != fedPublishInteractionFlagsMap.end())
  {
    itPIF = itFedPublishInteractionFlagsMap->second.find(theInteraction);
    if (itPIF != itFedPublishInteractionFlagsMap->second.end())
    {
      itFedPublishInteractionFlagsMap->second.erase(itPIF);
    }
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::unsubscribeInteractionClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GeRtiFactory::GeRtiHandle const &theRegion, GERTICO::FedEventSenderMap &theFedEventSenderMap)
{
  GERTICO::HandleSet::iterator itInteractionClass;
  GERTICO::HandleSetMap publishers;
  GERTICO::HandleSetMap::iterator itPublisher;

  Interaction *currInteraction;
  InteractionMap::iterator itI;

  itI = interactionMap.find(theInteraction);
  if (itI != interactionMap.end())
  {
    currInteraction = itI->second;
    // Delete the region in the federate.
    currInteraction->delSubInteraction(theFederate, theRegion);
    if (currInteraction->isEmpty())
    {
      // Have no data.
      interactionMap.erase(itI);
    }
  }
  else
  {
    throw GeRtiFactory::InteractionClassNotSubscribed(L"unsubscribeInteractionClass");
  }

  // Delete from federate.
  delInteractionClassRegionSub(theFederate, theInteraction, theRegion);

  // Get any publishers where there is no subscriber.
  interactionSubTurnOff(theFederate, theInteraction, publishers);

  for (itPublisher = publishers.begin(); itPublisher != publishers.end(); itPublisher++)
  {
    for (itInteractionClass = itPublisher->second.begin(); itInteractionClass != itPublisher->second.end(); itInteractionClass++)
    {
      addTurnOffForInteraction(itPublisher->first, *itInteractionClass, theFedEventSenderMap);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionHolder::unsubscribeInteractionClassWithRegions(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet const &theRegions)
{
  GERTICO::HandleSet *regionsPtr;
  GERTICO::HandleSet::iterator itHS;
  GERTICO::HandleSet::const_iterator itRegionIn;
  GERTICO::HandleSetMap *interactionRegionsPtr;
  GERTICO::HandleSetMap::iterator itInteractionRegions;
  GERTICO::HandleSetSetMap::iterator itFedInteractioRegion;

  itFedInteractioRegion = fedInteractionRegions.find(theFederate);
  if (itFedInteractioRegion != fedInteractionRegions.end())
  {
    interactionRegionsPtr = &itFedInteractioRegion->second;
    itInteractionRegions = interactionRegionsPtr->find(theInteraction);
    if (itInteractionRegions != interactionRegionsPtr->end())
    {
      regionsPtr = &itInteractionRegions->second;
      for (itRegionIn = theRegions.begin(); itRegionIn != theRegions.end(); itRegionIn++)
      {
        itHS = regionsPtr->find(*itRegionIn);
        if (itHS != regionsPtr->end())
        {
          regionsPtr->erase(itHS);
        }
      }
    }
  }
}
