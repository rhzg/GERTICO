/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** FederateDB.h
**
*******************************************************************************/

#ifndef FederateDB_H_
#define FederateDB_H_

#include <string>
#include "ace/Synch.h"
#include "idl/GeRtiFactoryC.h"
#include "LRC/DataDistributionManagementLRC.h"
#include "LRC/DeclarationManagementLRC.h"
#include "LRC/ObjectManagementLRC.h"
#include "LRC/SupportingServicesLRC.h"
#include "LRC/TimeManagementLRC.h"
#include "Util/GeRtiTypes.h"
#include "Util/RunTimeObjectDB.h"

namespace GERTICO
{
  typedef std::map <GeRtiFactory::GeRtiHandle, GERTICO::GeRtiFedTime *, GERTICO::CmpHandle> DeleteObjectWithTimeMap;

  /*
   * Database of federate characteristics.
   */
  class FederateDB
  {
    ACE_Mutex pm;
    GERTICO::DeleteObjectWithTimeMap deleteObjectWithTimeMap;
    std::set <GeRtiFactory::GeRtiHandle> objectsDeleted;
    std::set <GeRtiFactory::GeRtiHandle> objectsDiscovered;
    std::set <GeRtiFactory::GeRtiHandle> objectsReflected;
    std::set <GeRtiFactory::GeRtiHandle> objectsRegistered;
    std::set <GeRtiFactory::GeRtiHandle> objectsRemoved;
    std::set <GeRtiFactory::GeRtiHandle> objectsUpdated;
  public:
    ACE_Semaphore *ps;
    GERTICO::DataDistributionManagementLRC *dataDistributionManagementLRC;
    GERTICO::DeclarationManagementLRC *declarationManagementLRC;
    GERTICO::JobHolder momJobs;
    GERTICO::ObjectManagementLRC *objectManagementLRC;
    GERTICO::OwnershipService* ownership;
    GERTICO::RegionsHolder regionsHolder;
    GERTICO::RegisteredObjectsHolder registeredObjectsHolder;
    GERTICO::RunTimeObjectDB *runTimeObjectDB;
    GERTICO::SupportingServicesLRC *supportingServicesLRC;
    GERTICO::TimeManagementLRC *timeManagementLRC;
    GeRtiFactory::GeRtiHandle federate;
    bool joined;
#ifdef IEEE_1516
    std::wstring federateType;
    std::wstring hostName;
#else
    std::string federateType;
    std::string hostName;
#endif
    std::wstring FEDid;

    FederateDB(void);
    virtual ~FederateDB(void);

    void addDeleteObjectWithTime(GeRtiFactory::GeRtiHandle const &theObject, GERTICO::GeRtiFedTime const &theTime);
    void addObjectDiscovered(GeRtiFactory::GeRtiHandle const &theObject);
    void addObjectReflected(GeRtiFactory::GeRtiHandle const &theObject);
    void addObjectRemoved(GeRtiFactory::GeRtiHandle const &theObject);
    void addRegisterObjectInstance(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theClass);
    void clear(void);
    void delDeleteObjectWithTime(GeRtiFactory::GeRtiHandle const &theObject);
    void delObject(GeRtiFactory::GeRtiHandle const &theObject);
    CORBA::ULong getObjectsDeleted(void);
    CORBA::ULong getObjectsDiscovered(void);
    CORBA::ULong getObjectsReflected(void);
    CORBA::ULong getObjectsRegistered(void);
    CORBA::ULong getObjectsRemoved(void);
    CORBA::ULong getObjectsUpdated(void);
    bool process(void);
    void processDeleteObjectWithTime(GERTICO::GeRtiFedTime const &theGeRtiFedTime);
    void processDeleteObjectWithTime(GERTICO::GeRtiFedTime const &theGeRtiFedTime, GeRtiFactory::GeRtiHandle const &theObject);
    void reset(void);
  };
};

#endif
