/*********************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** Subscriber.h
**
*******************************************************************************/ 

#ifndef Subscriber_H_
#define Subscriber_H_

#include <map>

#include "idl/GeRtiFactoryS.h"

#include "GeRtiTypes.h"
#include "Region.h"
#include "XercesInclude.h"

namespace GERTICO
{
  class Subscriber
  {
    // Default region is region 0.
    GERTICO::HandleBoolMap regionActiveMap;

    static std::string activeStr;
    static std::string idStr;
    static std::string regionStr;
    static std::string regionsStr;

    void clear(void);

  public:
    Subscriber(void);
    virtual ~Subscriber(void);

    void addActiveRegion(CORBA::Boolean const &theActive);
    void addActiveRegion(CORBA::Boolean const &theActive, GERTICO::HandleSet &theRegions);
    bool checkActiveSubscriber(void);
    bool checkSubscribedDefault(void);
    void delRegion(GeRtiFactory::GeRtiHandle const &theRegion);
    void getRegions(GERTICO::HandleBoolMap &theRegions);
    bool isEmpty(void);
    bool isRegionSubscribed(GeRtiFactory::GeRtiHandle const &);
    bool isSubscribed(void);
    bool isSubscribedActive(void);
    void print(void);
    void restore(DOMElement &theDOMElement);
    void save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  // Key is federate id.
  typedef std::map <GeRtiFactory::GeRtiHandle, Subscriber> SubscriberMap;

  class SubscribeAttributeDB
  {
    SubscriberMap subscribedFederates;

    static std::string federateStr;
    static std::string subscriberStr;
    static std::string subscribersStr;

    void clear(void);

  public:
    SubscribeAttributeDB(void);
    virtual ~SubscribeAttributeDB(void);

    void addSubFederate(GeRtiFactory::GeRtiHandle const &theFederate, CORBA::Boolean const &theActive);
    void addSubFederate(GeRtiFactory::GeRtiHandle const &theFederate, CORBA::Boolean const &theActive, GERTICO::HandleSet &theRegions);
    bool checkActiveSubscriber(GeRtiFactory::GeRtiHandle const &);
    bool checkFederateSubscribed(GeRtiFactory::GeRtiHandle const &theFederate);
    bool checkFederateSubscribedRegion(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theRegions);
    void delSubFederate(GeRtiFactory::GeRtiHandle const &theFederate);
    void delSubFederateRegion(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion);
    void getRegions(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleBoolMap &theRegions);
    bool isEmpty(void);
    bool isRegionSubscribed(GeRtiFactory::GeRtiHandle const &, GeRtiFactory::GeRtiHandle const &);
    bool isSubscribed(GeRtiFactory::GeRtiHandle const &theFederate);
    bool isSubscribedActive(GeRtiFactory::GeRtiHandle const &theFederate);
    void print(void);
    void restore(DOMElement &theDOMElement);
    void save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
    bool subscribedToAttribute(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion, GERTICO::RegionMap &theRegionMap);
    bool testIntersection(GeRtiFactory::GeRtiHandle const &, GeRtiFactory::GeRtiHandle const &, GERTICO::RegionMap &);
  };

  // Key is attribute id, second is federate attribute.
  typedef std::map <GeRtiFactory::GeRtiHandle, SubscribeAttributeDB> SubscribeAttributeDBMap;

  class SubscribedClass
  {
    // Key is attribute, second is attribute data.
    SubscribeAttributeDBMap subscribeAttributeDBMap;

    GeRtiFactory::GeRtiHandle myObjectClassId;

    static std::string attributeStr;
    static std::string attributesStr;
    static std::string idStr;

    void clear(void);
    void delFederateRegionSubscribed(GeRtiFactory::GeRtiHandle const &theFederate);
    void delFederateRegionSubscribed(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSetMap &theAttributeRegions);
    bool getRegions(GeRtiFactory::GeRtiHandle const &, GeRtiFactory::GeRtiHandle const &, GERTICO::HandleBoolMap &theRegions);

  public:
    SubscribedClass(GeRtiFactory::GeRtiHandle const &);
    virtual ~SubscribedClass(void);

    void addSubAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theAttributes, CORBA::Boolean const &theActive);
    void addSubAttributesWithRegion(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSetMap &theAttributeRegions, CORBA::Boolean const &theActive);
    bool checkActiveSubscribers(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theAttributes);
    void delSubObjectClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion);
#ifdef IEEE_1516
    void delSubObjectClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theAttribute, GERTICO::HandleSet const &theRegions);
#endif
    GeRtiFactory::GeRtiHandle getClassId(void);
    void getDesiredAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet const &theEventAttributes, GERTICO::HandleSet &theDesiredAttributes);
    bool isEmpty(void);
    bool isRegionSubscribed(GeRtiFactory::GeRtiHandle const &, GeRtiFactory::GeRtiHandle const &);
    void print(void);
    bool subscribedToAttribute(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theAttributes);
    bool subscribedToAttribute(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSetMap &theAttributeRegions, GERTICO::RegionMap &theRegionMap);
    bool subscribedToAttributeActive(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theAttributes);
    void restore(DOMElement &theDOMElement);
    void save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  // Key is object class, second object class information.
  typedef std::map <GeRtiFactory::GeRtiHandle, SubscribedClass *> SubscribedClassMap;

  class SubscribedClassHolder
  {
    ACE_Thread_Mutex pm;
    // Key is object class id.
    GERTICO::SubscribedClassMap subObjectClassMap;
    std::string subscribedClassesStr;
  public:

    SubscribedClassHolder(void);
    virtual ~SubscribedClassHolder(void);
    bool checkActiveObjectClassSubscribers(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClassId, GERTICO::HandleSet &theAttributes);
    void clear(void);
    void getDesiredAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClassId, GERTICO::HandleSet const &theEventAttributes, GERTICO::HandleSet &theDesiredAttributes);
    SubscribedClass* getSubscribedClass(GeRtiFactory::GeRtiHandle const &classId) throw (GeRtiFactory::ObjectClassNotSubscribed);
    bool isRegionSubscribed(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion);
    void restoreSubscribedClasses(DOMElement &theDOMElement);
    void save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
    void subscribeObjectClassAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet &theAttributes, CORBA::Boolean const &theActive);
    void subscribeObjectClassAttributesWithRegion(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSetMap &theAttributeRegions, CORBA::Boolean const &theActive);
    void unsubscribeObjectClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet const &theRegions);
#ifdef IEEE_1516
    void unsubscribeObjectClassWithAttributeRegions(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSetMap const &theAttributeRegions);
#endif
  };
};

#endif /* Subscriber_H_  */
