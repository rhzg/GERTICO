/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
** SupportingServices.h
**
*******************************************************************************/

#ifndef SupportingServices_H_
#define SupportingServices_H_

#include "EventMarket/ObjectManagement.h"
#include "Util/RunTimeObjectDB.h"

namespace GERTICO
{
  class SupportingServices
  {
    GERTICO::ClassDescrHolder &interactionRoot;
    GERTICO::ClassDescrHolder &objectRoot;
    GERTICO::FederatesHolder &federatesHolder;
    GERTICO::ObjectManagement &objectManagement;
    GERTICO::RunTimeObjectDB &runTimeObjectDB;

  public:
    SupportingServices(GERTICO::ObjectManagement &theObjectManagement, GERTICO::RunTimeObjectDB &theRunTimeObjectDB, GERTICO::ClassDescrHolder &theObjectRoot, GERTICO::ClassDescrHolder &theInteractionRoot, GERTICO::FederatesHolder &theFederatesHolder);
    virtual ~SupportingServices(void);

    void disableAttributeScopeAdvisorySwitch(const GeRtiFactory::GeRtiHandle &theFederate);
    void disableClassRelevanceAdvisorySwitch(const GeRtiFactory::GeRtiHandle &theFederate);
    void enableAttributeScopeAdvisorySwitch(const GeRtiFactory::GeRtiHandle &theFederate);
    void enableClassRelevanceAdvisorySwitch(const GeRtiFactory::GeRtiHandle &theFederate);
    std::wstring findInteractionName(const GeRtiFactory::GeRtiHandle &theClassHandle, GERTICO::AttributeDatum &theInteractionDatum);
    std::wstring findObjectClassName(const GeRtiFactory::GeRtiHandle &theHandle);
    void getAttributeRoutingSpaceHandle(const GeRtiFactory::GeRtiHandle &theAttribute, const GeRtiFactory::GeRtiHandle &theClass, GeRtiFactory::GeRtiHandle &theSpace, bool &theClassFound, bool &theAttributeFound);
    GeRtiFactory::GeRtiHandle findObjectClassHandle(const std::wstring &theName);
    GeRtiFactory::GeRtiHandle getDimensionHandle(const std::wstring &theName, const GeRtiFactory::GeRtiHandle &whichSpace);
    void getDimensionName(std::wstring &theName, const GeRtiFactory::GeRtiHandle &theHandle, const GeRtiFactory::GeRtiHandle &whichSpace);
    GeRtiFactory::GeRtiHandle getInteractionClassHandle(const std::wstring &theName);
    GERTICO::RegisteredObject *getObjectById(const GeRtiFactory::GeRtiHandle &theObjectId);
    GERTICO::RegisteredObject *getObjectByName(const std::wstring &theObjectName);
    GeRtiFactory::GeRtiHandle getObjectClass (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObject);
    void getLRCattributeFlags(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::LRCattributeFlagsMap &theLRCattributeFlagsMap);
    bool getLRCparameterFlags(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::LRCparameterFlagsMap &theLRCparameterFlagsMap);
    void getObjectClassItem(const std::wstring &theName, const GeRtiFactory::GeRtiHandle &theClass, GeRtiFactory::GeRtiHandle &retId, bool &boolFoundItem, bool &boolFoundClass);
    void getObjectClassItem(const GeRtiFactory::GeRtiHandle &theId, const GeRtiFactory::GeRtiHandle &theClass, std::wstring &retName, bool &boolFoundItem, bool &boolFoundClass);
    void getParameterHandle(const std::wstring &, const GeRtiFactory::GeRtiHandle &, GeRtiFactory::GeRtiHandle &, bool &, bool &);
    void getParameterName(const GeRtiFactory::GeRtiHandle &, const GeRtiFactory::GeRtiHandle &, std::wstring &, bool &, bool &);
    GeRtiFactory::GeRtiHandle getInteractionParent(const GeRtiFactory::GeRtiHandle &theHandle);
    GeRtiFactory::GeRtiHandle getObjectParent(const GeRtiFactory::GeRtiHandle &theHandle);
    GeRtiFactory::GeRtiHandle getRoutingSpaceHandle(const std::wstring &theName);
    std::wstring getRoutingSpaceName(const GeRtiFactory::GeRtiHandle &theHandle);
    void setRangeBounds(GeRtiFactory::GeRtiHandle const &theRegionHandle, GeRtiFactory::GeRtiHandle const &theDimensionHandle, GeRtiFactory::GeRtiHandle const &theLowerBound, GeRtiFactory::GeRtiHandle const &theUpperBound);
  };
};

#endif /* SupportingServices_H_  */
