/*********************************************************************************
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
** Federate.h
**
*******************************************************************************/

#ifndef Federate_H_
#define Federate_H_

#include <map>
#include <string>

#include "XercesInclude.h"
#include "Util/HLAparseErrorHandler.h"

#include "idl/GeRtiFactoryS.h"
#include "Util/GeRtiFedTime.h"
#include "Util/GeRtiTypes.h"
#include "Util/JobHolder.h"
#include "Util/RegisteredObject.h"

namespace GERTICO
{
  class AttributeInstanceKnown
  {
    GeRtiFactory::GeRtiHandle id;
    bool inScope;

  public:
    AttributeInstanceKnown(void);
    virtual ~AttributeInstanceKnown (void);

    GeRtiFactory::GeRtiHandle getId (void);
    bool getInScope (void);
    void setId (const GeRtiFactory::GeRtiHandle &);
    void setScope(const bool &theScope);
  };

  // Key is attribute id, second information about attribute instances.
  typedef std::map <GeRtiFactory::GeRtiHandle, AttributeInstanceKnown> AttributeInstanceKnownMap;

  class ObjectKnown
  {
    GeRtiFactory::GeRtiHandle classId;
    GeRtiFactory::GeRtiHandle objectId;

    void clear(void);

  public:
    // Key is attribute id, second information about attributes.
    AttributeInstanceKnownMap atts;

    ObjectKnown(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSet &theAttributes);
    virtual ~ObjectKnown (void);

    GeRtiFactory::GeRtiHandle getClassId (void);
    GeRtiFactory::GeRtiHandle getObjectId (void);
void print(void);
    void setInScope(GERTICO::HandleSet &theAttributes);
  };

  // Key is object id, second information about object/attributes.
  typedef std::map <GeRtiFactory::GeRtiHandle, ObjectKnown *> ObjectKnownMap;

  class RegionAttributes
  {
  public:
    CORBA::Boolean myActive;
    HandleSet attributes;

    RegionAttributes (void);
    virtual ~RegionAttributes (void);
  };

  // Key is region.
  typedef std::map <GeRtiFactory::GeRtiHandle, RegionAttributes> RegionAttributesMap;

  class FedRegionsHolder
  {
    static std::string activeStr;
    static std::string attributeStr;
    static std::string attributesStr;
    static std::string idStr;
    static std::string regionStr;
  public:

    // Key is region id / second is attributes.
    RegionAttributesMap regionAttributesMap;

    FedRegionsHolder (void);
    virtual ~FedRegionsHolder (void);

    void restore (DOMElement &theDOMElement);
    void save (DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  typedef std::map <GeRtiFactory::GeRtiHandle, FedRegionsHolder> ClassRegionsHolderMap;

  class PublishObjectClassFlagsRTI
  {
    bool started;
  public:
    GERTICO::HandleSet attributes;

    PublishObjectClassFlagsRTI(void);
    virtual ~PublishObjectClassFlagsRTI(void);

    bool getStarted (void);
    void setStarted (const bool &theStarted);
  };

  // Key is interaction class id.
  typedef std::map <GeRtiFactory::GeRtiHandle, PublishObjectClassFlagsRTI> PublishObjectClassFlagsRTIMap;

  class Federate
  {
    // Object tree information.
    GERTICO::ClassDescrHolder &pObjectRoot;

    // CORBA Reference.
    GeRtiFactory::FederateAmbassador_var fedAm;

    // Federate id.
    GeRtiFactory::GeRtiHandle id;
    GeRtiFactory::GeRtiRestore_var geRtiRestoreVar;

    // Key is object instance id, second is object class id.
    GERTICO::ObjectKnownMap knownObjects;
    GERTICO::RegisteredObjectsHolder &registeredObjectsHolder;

    // Publishers
    // Key is object class id.
    PublishObjectClassFlagsRTIMap pubObjectClassMap;

    // Subscribers
    // Key is object class ids / second to region holder.
    ClassRegionsHolderMap subObjectClassMap;

    // Turn On management.
    GERTICO::HandleSetSetMap turnOnUpdates;

    // Associate region db.
    GERTICO::HandleSetSetMap objectAttributesRegions;

    // Whether federate wants any Advisory service.
    bool attributeScopeAdvisorySwitch;
    bool classRelevanceAdvisorySwitch;

    GERTICO::GeRtiFedTimeFactory &geRtiFedTimeFactory;
    bool timeConstrained;
    char buf[128];

    // Strings for save/restore.
    static std::string activeStr;
    static std::string attributeStr;
    static std::string attributesStr;
    static std::string classStr;
    static std::string dataStr;
    static std::string federateStr;
    static std::string idStr;
    static std::string inScopeStr;
    static std::string knownObjectStr;
    static std::string knownObjectsStr;
    static std::string lrcDataStr;
    static std::string publishedInteractionsStr;
    static std::string publishedObjectClassesStr;
    static std::string publishingStr;
    static std::string regionStr;
    static std::string regionsStr;
    static std::string startedStr;
    static std::string subscribedInteractionsStr;
    static std::string subscribedObjectClassesStr;
    static std::string turnedOnStr;

    GERTICO::GeRtiFedTime *nextSaveTime;
    std::string saveData;
    std::wstring saveLabel;

    bool joinedFinished;

  void clear (void);
    void getSubscribedAttributes(const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSet &theAttributesOut, GERTICO::HandleSet &theAttributesIn);

  public:
    bool confirmed;
    bool restoreBegun;
    bool restoreComplete;
    bool restoreInitiated;
    bool restoreSuccess;
    bool saveBegun;
    bool saveComplete;
    bool saveInitiated;
    bool saveInitiatedWithTime;
    bool saveSuccess;
    bool stillAlive;

    // Strings for save/restore.
    std::wstring federateType;

    Federate(const GeRtiFactory::GeRtiHandle &theId, const std::wstring &theType, GERTICO::RegisteredObjectsHolder &theRegisteredObjectsHolder, GERTICO::ClassDescrHolder &theObjectClassDescr, GeRtiFactory::FederateAmbassador_ptr theFederateAmbassadorPtr, GeRtiFactory::GeRtiRestore_ptr theGeRtiRestorePtr, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory);
    virtual ~Federate (void);

    // Interactions
    void addInteractionClassRegionSub (const GeRtiFactory::GeRtiHandle &theInteraction, const GERTICO::HandleSet &theRegions, const bool &theActive);

    // Objects known to federate.
    void addKnownObject (const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSet &theAttributes);

    void addSubscribeObjectClass(const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSet &theAttSet, const CORBA::Boolean &theActive);
    void addSubscribeObjectClassRegion(const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSetMap &theAttRegMap, const CORBA::Boolean &theActive);

    void announceSynchronizationPoint(const std::wstring &theLabel, const GeRtiFactory::UserSuppliedTag &tag);

    void associateRegionForUpdates(const GeRtiFactory::GeRtiHandle &theObject, GERTICO::HandleSetMap &theAttributeRegions);

    void attributeOwnershipDivestitureNotification(const GeRtiFactory::GeRtiHandle &theObject, GeRtiFactory::Handles &theDivestedAttributes);

    void attributeIsNotOwned(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theAttribute);
    void attributeOwnedByRTI(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theAttribute);
    void attributeOwnershipAcquisitionNotification(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &securedAttributes, GeRtiFactory::UserSuppliedTag const &theTag);
    void attributeOwnershipUnavailable(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes);
    void confirmAttributeOwnershipAcquisitionCancellation(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes);
    void informAttributeOwnership(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theAttribute, GeRtiFactory::GeRtiHandle const &theOwner);
    void requestAttributeOwnershipAssumption(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &offeredAttributes, GeRtiFactory::UserSuppliedTag const &theTag);
    void requestAttributeOwnershipRelease(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &candidateAttributes, GeRtiFactory::UserSuppliedTag const &theTag);
    void requestDivestitureConfirmation(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &releasedAttributes);

    // Logic to handle in/out scope.
    void attributesInScope(const GeRtiFactory::GeRtiHandle &theObject, GERTICO::HandleSet &theAttributes);
    void attributesInScopeRemote(const GeRtiFactory::GeRtiHandle &theObject, GERTICO::HandleSet &theAttributes);
    void attributesOutOfScope(const GeRtiFactory::GeRtiHandle &theObject, GERTICO::HandleSet &theAttributes);
    void attributesOutOfScopeRemote(const GeRtiFactory::GeRtiHandle &theObject, GERTICO::HandleSet &theAttributes, const bool &theSendFlag);

    void checkPublishedAttributes(const GeRtiFactory::GeRtiHandle &theClass, const GERTICO::HandleSetMap &theAttRegMap);

    void confirmFederationRestorationRequest(const std::wstring &theLabel, const bool &);
    void confirmSynchronizationPointRegistration(const std::wstring &theLabel, const CORBA::Boolean &success, const GeRtiFactory::SynchronizationPointFailureReason &theReason);

    // Delete interactions
    void delInteractionClassRegionPub (const GeRtiFactory::GeRtiHandle &);
    void delInteractionClassRegionSub(const GeRtiFactory::GeRtiHandle &theInteraction, const GeRtiFactory::GeRtiHandle &theRegion);
    void delInteractionClassRegionSubs(const GeRtiFactory::GeRtiHandle &theInteraction);

    // Delete known object.
    void delObject (const GeRtiFactory::GeRtiHandle &);

    void delObjectClassRegionPub (const GeRtiFactory::GeRtiHandle &);
    void delObjectClassSub(const GeRtiFactory::GeRtiHandle &theObjectClass);
    void unsubscribeObjectClassWithRegion(const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSet &theRegions);
    void unsubscribeObjectClassWithRegions(const GeRtiFactory::GeRtiHandle &theObjectClass, const GERTICO::HandleSetMap &theAttributeRegions);

    // Disable switches.
    void disableAttributeScopeAdvisorySwitch (void);
    void disableClassRelevanceAdvisorySwitch (void);

    void announceObjectInstance(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theClass, const std::wstring &theName, GERTICO::HandleSet &theAttributes);
    void discoverObjectInstance(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theClass, const std::wstring &theName);

    void doMomRequest(GeRtiFactory::GeRtiHandle theRequest, const GeRtiFactory::HandleValues & data);

    // Enable switches.
    void enableAttributeScopeAdvisorySwitch (void);
    void enableClassRelevanceAdvisorySwitch (void);

    // Federation restore complete.
    void federateRestoreComplete (const bool &);

    // Federate save begun.
    void federateSaveBegun (void);

    // Federate save complete.
    void federateSaveComplete(const bool &theSuccess, const std::string &theSaveData);

    void federationRestored(const bool &theSuccess, const GeRtiFactory::RestoreFailureReason &theFailureReason);
    void federationRestoreBegun (void);
    void federationSaved(const bool &theSuccess, const GeRtiFactory::SaveFailureReason &theFailureReason);
    void federationSynchronized(const std::wstring &theLabel);

    GeRtiFactory::GeRtiRestore_ptr getGeRtiRestore (void);

    // Get switch values.
    bool getAttributeScopeAdvisorySwitch (void);
    bool getClassRelevanceAdvisorySwitch (void);

    // Federate id.
    GeRtiFactory::GeRtiHandle getId (void);

    void getInScope (const unsigned long &theObject, GERTICO::HandleSet &theAttributes);
    bool getInScope (const unsigned long &theObject, GERTICO::HandleSet &theOutAttributes, GERTICO::HandleSet &theInAttributes);

    void getObjectAttributeRegions(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theAttribute, GERTICO::HandleSet &theRegion);

    // Supporting service for getting the known object class
    GeRtiFactory::GeRtiHandle getObjectClass (const GeRtiFactory::GeRtiHandle &);

    void getKnownObjects(GERTICO::HandleSet &theObjects);
    void getKnownObjects(const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theObjects);

    bool getOutScope (const unsigned long &, GERTICO::HandleSet &, GERTICO::HandleSet &);

    bool getPublishingInteraction (const GeRtiFactory::GeRtiHandle &);

    void getMaps(HandleSetMap &theSubObjectsMap);

    bool getMomData(GeRtiFactory::GeRtiHandle theRequest, const GeRtiFactory::Handles & theAttributes, GeRtiFactory::HandleValues_out data);

    void getPublishedAttributes(const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theAttributeSet);
    void getPublishedInteractionClasses(GERTICO::HandleSet &thePublishedInteractionClasses);
    void getPublishedObjectClasses(GERTICO::HandleSet &thePublishedClasses);

//    bool getStarted (const GeRtiFactory::GeRtiHandle &);

    // Use ONLY when the the publisher is publishing in the default region!!!!
    void getSubscribedAttributes(const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theAttributes);

    void getSubscribedAttributeRegions(const GeRtiFactory::GeRtiHandle &theClass, const GeRtiFactory::GeRtiHandle &theAttribute, GERTICO::HandleSet &theRegions, const bool &onlyActiveSubscriptions);
    void getSubscribedInteractionClasses(GERTICO::HandleBoolMap &theSubscribedInteractionClasses);
    void getSubscribedObjectClasses(GERTICO::HandleSet &theSubscribedObjectClasses);
    void getSubscribedRegionAttributes(const GeRtiFactory::GeRtiHandle &theClass, const GeRtiFactory::GeRtiHandle &theRegion, GERTICO::HandleSet &theAttributes);
    void getSubscribedRegions(const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theRegions);

    bool getTimeConstrained (void);

    // Initiate federate restore.
    void initiateFederateRestore(const std::wstring &theLabel, const GeRtiFactory::GeRtiHandle &);

    // Initiate federate save.
    void initiateFederateSave(const std::wstring &theLabel, const bool &theCorbaCall);
    // Special gerti logic.
    void initiateFederateSaveWithTime(const std::wstring &theLabel, const GERTICO::GeRtiFedTime &theFedTime, const GERTICO::GeRtiFedTime &theRtiFedTime, const bool &theCorbaCall);

    bool isInScope(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theAttribute);

  bool isJoinedFinished(void);

  bool isPublishingObjectClassAttribute(const GeRtiFactory::GeRtiHandle &theObjectClass, const GeRtiFactory::GeRtiHandle &theAttribute);
    bool isSubscribedToObjectClass(const GeRtiFactory::GeRtiHandle &theObjectClass);
    bool isSubscribedToObjectClassAttribute(const GeRtiFactory::GeRtiHandle &theObjectClass, const GeRtiFactory::GeRtiHandle &theAttribute, const bool &onlyActiveSubscriptions);
    bool isSubscribedToObjectClassRegionAttribute(const GeRtiFactory::GeRtiHandle &theObjectClass, const GeRtiFactory::GeRtiHandle &theRegion, const GeRtiFactory::GeRtiHandle &theAttribute);
    bool isSubscribedToObjectClassAttributes(const GeRtiFactory::GeRtiHandle &theObjectClass, const GeRtiFactory::GeRtiHandle &theRegion, GERTICO::HandleSet &theAttributes);

    void joinFederationExecutionFinished(void);

    // Test if object is known.
    bool knowObject (const GeRtiFactory::GeRtiHandle &);

    void loadRegion(const GeRtiFactory::GeRtiHandle &theSpace, const GeRtiFactory::GeRtiHandle &theRegion, GeRtiFactory::Extents &theExtents);

    // Turn flag off that the federate knows the object.
    void localDeleteObjectInstance (const GeRtiFactory::GeRtiHandle &);
    void objectInstanceNameReservationSucceeded(std::wstring const &theObjectInstanceName);
    void ping(void);
void print(void);
void print(const GeRtiFactory::GeRtiHandle &theObject);
    void provideAttributeValueUpdate(const GeRtiFactory::GeRtiHandle &theObject, GeRtiFactory::Handles &theAttributes, const GeRtiFactory::UserSuppliedTag &theTag);

    void publishObjectClass (const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSet &theAttributes);

    void removeObjectInstance(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::UserSuppliedTag &theTag);
    void removeObjectInstanceWithTime(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::UserSuppliedTag &theTag, const GeRtiFactory::Time &theTime, const GeRtiFactory::ERHandle &theERHandle);

    void resetAlive(void);

    void restore (DOMElement &theDOMElement);

    void save (DOMDocument &theDOMDocument, DOMElement &theDOMElement);

    void setAlive(void);
    void setId (const GeRtiFactory::GeRtiHandle &theFederateId);

    void setInScope(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theAttribute);
    void setOutScope(const GeRtiFactory::GeRtiHandle &theObject, GeRtiFactory::Handles &theAttributes);

    void setPublishingInteraction (const GeRtiFactory::GeRtiHandle &, const bool &);

//    void setStarted (const GeRtiFactory::GeRtiHandle &, const bool &);
    bool testAlive(void);
    // If attribute is turned on.
    bool testTurnedOn(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theAttribute);
    // If a particular subscriber for this attribute is turned on.
    bool testTurnedOn(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theAttribute, const GeRtiFactory::GeRtiHandle &theSubscriber);
    void turnUpdatesOffForObjectInstance(const GeRtiFactory::GeRtiHandle &theObject, const GERTICO::HandleSetMap &theAttributeSubscribers);
    void turnUpdatesOffForObjectInstanceRemote(const GeRtiFactory::GeRtiHandle &theObject, const GERTICO::HandleSetMap &theAttributeSubscribers);
    void turnUpdatesOnForObjectInstance(const GeRtiFactory::GeRtiHandle &theObject, const GERTICO::HandleSetMap &theAttributeSubscribers);
    void turnUpdatesOnForObjectInstanceRemote(const GeRtiFactory::GeRtiHandle &theObject, const GERTICO::HandleSetMap &theAttributeSubscribers);
    void unassociateAttributeRegionForUpdates(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theAttribute, const GeRtiFactory::GeRtiHandle &theRegion);
    void unassociateRegionForUpdates(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theRegion);
    void unassociateRegionsForUpdates(const GeRtiFactory::GeRtiHandle &theObject, const GERTICO::HandleSetMap &theAttributeRegions);
    void unsetFederateSave (void);
  };

  // Key is federate id.
  typedef std::map <GeRtiFactory::GeRtiHandle, GERTICO::Federate *> FederateMap;

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
  typedef std::map <unsigned long, std::wstring> FedTypes;

  class FederatesHolder
  {
    ACE_Thread_Mutex pm;
    GERTICO::FederateMap federateMap;
    GERTICO::GeRtiFedTimeFactory &geRtiFedTimeFactory;
    std::vector <Federate *> resignedFederates;
  public:

    FederatesHolder(GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory);
    virtual ~FederatesHolder(void);

    void addFederate(GeRtiFactory::GeRtiHandle const &theFederate, std::wstring const &theFedType, GERTICO::RegisteredObjectsHolder &theRegisteredObjectsHolder, GeRtiFactory::FederateAmbassador_ptr theFederateAmbassadorPtr, GeRtiFactory::GeRtiRestore_ptr theGeRtiRestorePtr, GERTICO::ClassDescrHolder &theObjectRoot);
    void deleteFederate(GeRtiFactory::GeRtiHandle const &theFederate);
    GERTICO::Federate *getFederate(GeRtiFactory::GeRtiHandle const &theFederate);
    void getFederates(GERTICO::HandleSet &theFederates);
    void getNewFederates(GERTICO::HandleSet &theNewFederates, GERTICO::HandleSet const &theOldFederates, GERTICO::HandleSet &theAllFederates);
    void pruneResignedFederates(void);
    void rehashFederateIds(FedTypes &theFedTypes);
  };
};

#endif /* Federate_H_  */
