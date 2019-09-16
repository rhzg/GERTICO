/*********************************************************************************
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** Interaction.h
**
*******************************************************************************/

#ifndef Interaction_H_
#define Interaction_H_

#include <map>

#include <xercesc/util/PlatformUtils.hpp>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>

#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>

#include "idl/GeRtiFactoryS.h"
#include "Util/Federate.h"
#include "Util/HLAparseErrorHandler.h"
#include "Util/GeRtiTypes.h"
#include "Util/Region.h"

#include "FedEventSender.h"
#include "SupportingServicesEC.h"

namespace GERTICO
{
  class PublishInteractionFlags
  {
    // Key federate subscriber.
    GERTICO::HandleBoolMap turnedOn;
  public:
    PublishInteractionFlags(void);
    virtual ~PublishInteractionFlags(void);

    void getSubscribers(GERTICO::HandleSet &theSubscribers);
    bool getTurnedOn(GeRtiFactory::GeRtiHandle const &theFederateSubscriber);
    void print(void);
    void setTurnedOn(GeRtiFactory::GeRtiHandle const &theFederateSubscriber, bool const &theTurnedOn);
  };

  // Key is interaction class id.
  typedef std::map <GeRtiFactory::GeRtiHandle, PublishInteractionFlags> PublishInteractionFlagsMap;

  // Key is federate id.
  typedef std::map <GeRtiFactory::GeRtiHandle, PublishInteractionFlagsMap> FedPublishInteractionFlagsMap;

  // Key is region id.
  typedef std::map <GeRtiFactory::GeRtiHandle, bool> SubInteractionFlagMap;

  // Key is interaction class id.
  typedef std::map <GeRtiFactory::GeRtiHandle, SubInteractionFlagMap> SubInteractionFlagsMap;

  // Key is federate id.
  typedef std::map <GeRtiFactory::GeRtiHandle, SubInteractionFlagsMap> FedSubInteractionFlagsMap;

  class InteractionHolder
  {
    ACE_Thread_Mutex pm;
    // Key: <federate id < interaction class id, PublishInteractionFlags >>
    GERTICO::FedPublishInteractionFlagsMap fedPublishInteractionFlagsMap;
    // Key: <federate id <interaction class id < region id, bool >>>
    GERTICO::FedSubInteractionFlagsMap fedSubInteractionFlagsMap;

    GERTICO::InteractionMap &interactionMap;
    GERTICO::SupportingServicesEC &supportingServicesEC;

    // Key: interaction id
    GERTICO::RegionsHolder &regionsHolder;
    GeRtiFactory::GeRtiHandle momManagerInteractionRoot;

    void addInteractionClassRegionPub(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction);
    void addInteractionClassRegionSub(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet const &theRegions, bool const &theActive);
    void addTurnOffForInteraction(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::FedEventSenderMap &theFedEventSenderMap);
    void addTurnOnForInteraction(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet &theActiveSubscribers, GERTICO::HandleSet &thePassiveSubscribers);
    bool checkClassActiveSubscribers(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction);
    void delInteractionClassRegionSub(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GeRtiFactory::GeRtiHandle const &theRegion);
    void delInteractionClassRegionSubs(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction);
    void getActiveSubscribers(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet &theSubscribers);
    void getPassiveSubscribers(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet &theSubscribers);
    void interactionSubTurnOff(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSetMap &thePublishers);
    void interactionSubTurnOffFind(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSetMap &thePublishers);
    void interactionSubTurnOn(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSetMap &thePublishers);
    void interactionSubTurnOnFind(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSetMap &thePublishers);
    void onPublishers(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet &thePublishers);
    void print(void);
    void setPublishingInteraction(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, bool const &thePublishing);
  public:
    GERTICO::HandleSetSetMap fedInteractionRegions;
    InteractionHolder(GERTICO::InteractionMap &theInteractionMap, GERTICO::RegionsHolder &theRegionsHolder, GERTICO::SupportingServicesEC &theSupportingServicesEC);
    virtual ~InteractionHolder(void);

    bool checkActiveSubscribers(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction);
    bool checkSubscriber(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction);
    void clear(void);
    void getFederatesForInteraction(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet &theFederates);
    void getFederateRegions(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleBoolMap &theRegions);
    void getPublishedInteractionClasses(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &thePublishedInteractionClasses);
    void getSubscribedInteractionClasses(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleBoolMap &theSubscribedInteractionClasses);
    void interactionClassSubTurnOff(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSetMap &thePublishers);
    void publishInteractionClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::FedEventSenderMap &theFedEventSenderMap);
    void restore(DOMElement &theDOMElement, unsigned long const &theInteraction, unsigned long const &theOrdering, unsigned long const &theTransportation);
    void save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
    void setMomManagerInteractionRoot(GeRtiFactory::GeRtiHandle const &theMomManagerInteractionRoot);
    void subscribeInteractionClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, CORBA::Boolean const &theActive, GERTICO::HandleSet const &theRegions, GERTICO::FedEventSenderMap &theFedEventSenderMap);
    void subscribeInteractionClassWithRegions(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet const &theRegions);
//    void testRegionDimensions(GeRtiFactory::GeRtiHandle const &theInteractionClass, GERTICO::HandleSet const &theRegions);
    void turnOnPublisher(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::FedEventSenderMap &theFedEventSenderMap);
    void unpublishInteractionClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction);
    void unsubscribeInteractionClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GeRtiFactory::GeRtiHandle const &theRegion, GERTICO::FedEventSenderMap &theFedEventSenderMap);
    void unsubscribeInteractionClassWithRegions(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet const &theRegions);
  };
};

#endif /* Interaction_H_  */
