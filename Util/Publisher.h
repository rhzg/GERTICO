/*********************************************************************************
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** Publisher.h
**
*******************************************************************************/

#ifndef Publisher_H_
#define Publisher_H_

//#include <map>
#include "XercesInclude.h"
#include "HLAparseErrorHandler.h"
//#include "ClassDescr.h"
#include "GeRtiTypes.h"
#include "Federate.h"
#include "RegisteredObject.h"

namespace GERTICO
{
  typedef enum { Publish, Subscribe, PublishSubscribe, Neither } Sharing;

  class PublishedClass
  {
    GeRtiFactory::GeRtiHandle myId;
    HandleSet objects;

    void getFederatePubAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &thePubAttributes);
    void restoreAttributes(DOMElement &theDOMElement, PubAttributeDB &thePubAttributeDB);
    void restoreFederates(DOMElement &theDOMElement);
    void restoreObjects(DOMElement &theDOMElement);

  public:
    PublishedClass(GeRtiFactory::GeRtiHandle const &theClassId);
    virtual ~PublishedClass(void);

    // Key is federate.
    FedPubAttributeMap fedPubAttributeMap; // federate -> publishedAttributes
    Sharing sharingStatus;

    void addObject(GeRtiFactory::GeRtiHandle const &theObject);
    void addPubAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theAttributes);
    void checkPublishing(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::Handles const &theAttributes, GeRtiFactory::GeRtiHandle const &thePrivilegeToDeleteId);
    void delObject(GeRtiFactory::GeRtiHandle const &theObject);
    void delPubAttributes(GeRtiFactory::GeRtiHandle const &theFederate);
    void delPubAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::Handles const &theAttributes);
    GeRtiFactory::GeRtiHandle getId(void);
    void getObjectIds(GERTICO::HandleSet &theObjects);
    void getPublishInfo(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theAttributes);
    bool getStarted(GeRtiFactory::GeRtiHandle const &theFederate);
    void print(void);
    void restore(DOMElement &theDOMElement);
    void save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
    void setStarted(GeRtiFactory::GeRtiHandle const &theFederate, bool const &theStarted);
    void startRegistration(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theAttributes, GERTICO::HandleSet &thePublishers, GERTICO::HandleSet &theFederates);
  };

  typedef std::map <GeRtiFactory::GeRtiHandle, PublishedClass*>  PublishedClassMap;

  class PublisherHolder
  {
    ACE_Thread_Mutex pm;
    // Key is federate id.
    GERTICO::HandleSetMap fedPubObjectClassMap;
    GERTICO::PublishedClassMap publishedClassMap;
    std::string idStr;
    std::string publishedClassesStr;

  public:
    PublisherHolder(void);
    virtual ~PublisherHolder(void);

    void checkPublishing(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &theAttributes, GeRtiFactory::GeRtiHandle const &thePrivilegeToDeleteId);
    void clear(void);
    void getPublishFederates(GERTICO::HandleSet &theFederates);
    void getPublishedObjectClasses(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &thePublishedClasses);
    bool getStarted(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass);
    GERTICO::PublishedClass* createClass(GeRtiFactory::GeRtiHandle classId);
    void getPublishedAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSet &theAttributeSet, GeRtiFactory::GeRtiHandle const &thePrivilegeToDeleteId);
    GERTICO::PublishedClass* getPublishedClass(GeRtiFactory::GeRtiHandle const &classId) throw (GeRtiFactory::ObjectClassNotPublished);
    void publishObjectClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet &theAttributes);
    void restorePublishedClasses(DOMElement &theDOMElement);
    void save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
    void setStarted(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, bool const &theStarted);
    void unpublishObjectClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass);
  };  
};

#endif /* Interaction_H_  */
