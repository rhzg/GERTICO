/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
** FederationManagement.h
**
*******************************************************************************/

#ifndef FederationManagement_H_
#define FederationManagement_H_

#include <string>

#include "Util/XercesInclude.h"

#include "Util/HLAparseErrorHandler.h"

#include "idl/GeRtiFactoryS.h"
#include "Util/Federate.h"
#include "Util/GERTICOconf.h"
#include "Util/GeRtiOrb.h"
#include "EventMarket/Jobs.h"
#include "GeRti/GeRtiOwnershipMasterI.h"

#include "EventMarket/EventHandler.h"
#include "EventMarket/FederationManagementEC.h"
#include "EventMarket/GeRtiEventMarketI.h"

#include "DataDistributionManagement.h"
#include "ManagementObjectModel.h"
#include "EventMarket/ObjectManagement.h"
#include "SupportingServices.h"
#include "SyncPointHandler.h"

namespace GERTICO
{
  typedef std::map <std::wstring, unsigned long> FedCounts;

  class FederationManagement
  {
    ACE_Thread_Mutex pm;
    CORBA::Object_var gertiObj;
    FedCounts fedCounts;
    GERTICO::ClassDescrHolder interactionRoot;
    GERTICO::ClassDescrHolder objectRoot;
    GERTICO::FederatesHolder *federatesHolder;
    PortableServer::POA_var myPOA;
    PortableServer::POA_var myPOAbestEffort;
    PortableServer::POA_var myPoaSender;
    GERTICO::FederationManagementEC *federationManagementEC;
    GERTICO::GeRtiFedTime *nextSaveTime;
    GERTICO::GeRtiFedTimeFactory &geRtiFedTimeFactory;
    GERTICO::GeRtiLogicalTimeIntervalFactory &geRtiLogicalTimeIntervalFactory;
    GERTICO::RegionsHolder regionsHolder;
    GERTICO::SyncPointHandler *syncPointHandler;
    XercesDOMParser *parser;
    bool concurrencyFlag;
    bool restoreInProgress;
    bool saveInProgress;
    bool saveRequested;
    bool saveTimeReachedFlag;
    bool gotPreviousTime;
    double doublePreviousTime;
    std::string zeroTimeStr;
    std::wstring fedFile;
    std::wstring federationName;
    std::wstring nextSaveName;
    // Object model.
    GERTICO::ObjectModel *objectModel;
    const GERTICOconf &gerticoConf;
    GERTICO::NextHandle &idHandler;

    // Save / Restore strings
    static std::string countStr;
    static std::string federateStr;
    static std::string federateIdsStr;
    static std::string federateTypeStr;
    static std::string federateTypesStr;
    static std::string federatesStr;
    static std::string federationTimeStr;
    static std::string idStr;
    static std::string timeValueStr;
    static std::string typeStr;

    bool checkFederationCounts (void);
    void clear (void);
    bool compareFederationCounts (FedCounts &theFedCounts);
    GeRtiFactory::GeRtiHandle getSpaceHandle(const std::wstring &);
    // Used by primary time master client.
    void initiateFederateSave(void);
    void initialize (void);
    bool parseEnv(char *out, char *in);
    bool parseFromFile (void);
    void performDeleteObjects(const GeRtiFactory::GeRtiHandle &theFederate);
    void performReleaseAttributes(const GeRtiFactory::GeRtiHandle &theFederate);

    // Restore.
    void restore(DOMElement &theDOMElement);
    void restoree(void);

    // Save.
    void save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
    void savee(void);

    bool addNsDirectory(GERTICO::GeRtiOrb &theGeRtiOrb, CosNaming::Name const &theDirectoryName);
    
    void addXmlInteractionClass (GERTICO::ClassDescr* parent, GERTICO::InteractionClass* child);

    void addXmlObjectClass (GERTICO::ClassDescr* parent, GERTICO::ObjectClass* child);

  public:
    ACE_Semaphore *ps;
    DOMElement *domElement;
//    EventHandler *eventHandler;
    GERTICO::JobHolder federationJobs;
    GeRtiEventMarket_MarketConsumerAdmin_i *consumerAdmin;
    GeRtiEventMarket_MarketSupplierAdmin_i *supplierAdmin;
    GeRtiEventMarket_MarketSupplierAdmin_i *supplierAdminBestEffort;
    bool notDone;
    std::wstring federationSaveLabel;
    std::string federationState;

    // Declaration Management
    GERTICO::DeclarationManagementRTI *declarationManagementRTI;

    // Ownership
    GERTICO::GeRtiOwnershipMasterI* ownershipMaster;
    GERTICO::RegisteredObjectsHolder *registeredObjectsHolder;
    GERTICO::RunTimeObjectDB *runTimeObjectDB;

    // Object Management.
    GERTICO::ObjectManagement *objectManagement;

    // Data Distribution Management.
    GERTICO::DataDistributionManagement *dataDistributionManagement;

    GERTICO::ManagementObjectModel *managementObjectModel;

    // Supporting Services
    GERTICO::SupportingServices *supportingServices;

    FederationManagement(GERTICO::GeRtiOrb &theGeRtiOrb, PortableServer::POA_ptr thePOA, PortableServer::POA_ptr thePoaBestEffort, PortableServer::POA_ptr thePoaSender, std::wstring const &theFederationName, std::wstring const &theFedFile, GERTICO::NextHandle &theIdHandler, GERTICOconf const &theGERTICOconf, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory);
    virtual ~FederationManagement (void);

    void checkSaveRestore (void);
    void federateSaveBegun (const GeRtiFactory::GeRtiHandle &theFederate);
    void federateRestoreComplete(const GeRtiFactory::GeRtiHandle &theFederate, const bool &theSuccess);
    void federateSaveComplete(const GeRtiFactory::GeRtiHandle &theFederate, const bool &theSuccess, const std::string &theSaveData);
    void federationRestored(const bool &, const GeRtiFactory::RestoreFailureReason &theFailureReason);
    void federationSaved(const bool &allSuccess, const GeRtiFactory::SaveFailureReason &theFailureReason);
    void getNextSaveName(std::wstring &theNextSaveName);
    void getNextSaveTime (std::string &theNextSaveTime);
    GeRtiFactory::GeRtiHandle getRegionSpace(const GeRtiFactory::GeRtiHandle &theRegion);
    bool getRestoreInProgress (void);
    bool getSaveInProgress (void);
    void getSaveRequestedTime(GERTICO::GeRtiFedTime &theFedTime);
    bool gotSaveRequested(void);
    void joinFederationExecution(const GeRtiFactory::GeRtiHandle &theFederate, const std::wstring &theFedType, GeRtiFactory::FederateAmbassador_ptr, GeRtiFactory::GeRtiRestore_ptr);
    void joinFederationExecutionFinished ( GeRtiFactory::GeRtiHandle federate);
    int process (void);
    void processLive(void);
    void registerSynchronizationPoint (const GeRtiFactory::GeRtiHandle &theFederate, const std::wstring &theLabel, const GeRtiFactory::UserSuppliedTag &theTag, const GeRtiFactory::Handles &designators);
    void requestFederationRestore (const GeRtiFactory::GeRtiHandle &theFederate, const std::wstring &theFederationSaveLabel);
    void requestFederationSave(const GeRtiFactory::GeRtiHandle &theFederate, const std::wstring &theLabel);
    void requestFederationSave(const GeRtiFactory::GeRtiHandle &theFederate, const std::wstring &theLabel, GERTICO::GeRtiFedTime &theTime);
    void requestFederateSaveStart(const GeRtiFactory::GeRtiHandle &theFederate, const std::wstring &theLabel, const GeRtiFactory::Time &theTime, const bool &theBool);
    void resignFed (const GeRtiFactory::GeRtiHandle &theFederate, const std::wstring &theFedType);
    void resignFederationExecution (const GeRtiFactory::ResignAction &, const GeRtiFactory::GeRtiHandle &);
    void saveTimeReached(void);
    void setAlive(GeRtiFactory::GeRtiHandle const &theHandle);
    void synchronizationPointAchieved(const std::wstring &theLabel, const GeRtiFactory::GeRtiHandle &theFederate);
    void terminate(void);
    void wallClockWorker(void);
  };
};

#endif /* FederationManagement_H_  */
