/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** SupportingServicesLRC.h
**
*******************************************************************************/

#ifndef SupportingServicesLRC_H_
#define SupportingServicesLRC_H_

#include "idl/GeRtiFactoryS.h"
#include "Util/GeRtiTypes.h"
#include "Util/Mapper.h"

namespace GERTICO
{
  class SupportingServicesLRC
  {
    // Interaction Class/Parameter Cache.
    // Interaction Class Handle / Interaction Data.
    GERTICO::AttributeDatumMap cacheInteractionClassInteractionData;
    // Interaction Class Name / Interaction Class Handle.
    GERTICO::WstringHandleMap cacheNameInteractionClass;
    // Interaction Class / Name / Parameter Handle.
    GERTICO::HandleWstringHandleMap cacheInteractionNameParameter;
    // Interaction Class / Parameter Handle / Name.
    GERTICO::HandleHandleWstringMap cacheInteractionParameterName;

    // Object Class/Attribute Cache.
    // Object Class Handle / Object Class Name.
    GERTICO::HandleWstringMap cacheObjectClassName;
    // Object Class Name / Object Class Handle.
    GERTICO::WstringHandleMap cacheNameObjectClass;
    // Object Class / Name / Attribute Handle.
    GERTICO::HandleWstringHandleMap cacheObjectNameAttribute;
    // < Object Class < Attribute Handle, AttributeData>>.
    GERTICO::AttributeDataMap cacheObjectAttributeData;

    GeRtiFactory::GeRtiAmbassador_var GeRtiAmbVar;

    // Parents and children of classes.
    GERTICO::HandleMap parentsInteraction;
    GERTICO::HandleMap parentsObject;
    GERTICO::HandleSetMap childrenInteraction;
    GERTICO::HandleSetMap childrenObjectClass;

    // Adds to cacheObjectNameAttribute.
    void addCacheObjectNameAttribute(GeRtiFactory::GeRtiHandle const &theObjectClass, GeRtiFactory::GeRtiHandle const &theAttribute, std::wstring const &theName);

    // Adds to cacheObjectAttributeData
    void addCacheObjectAttributeData(GeRtiFactory::GeRtiHandle const &theObjectClass, GeRtiFactory::GeRtiHandle const &theAttribute, std::wstring const &theName, GeRtiFactory::GeRtiHandle const &theOrderType, GeRtiFactory::GeRtiHandle const &theTransportationType, GeRtiFactory::Handles theDimensions);

    void fillInteractionParents(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles_var &theParents);
    void fillObjectParents(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles_var &theParents);

    // Whether federate wants any Advisory service.
    bool attributeRelevanceAdvisorySwitch;
    bool attributeScopeAdvisorySwitch;
    bool classRelevanceAdvisorySwitch;
    bool interactionRelevanceAdvisorySwitch;

  public:
    //Constructor
    SupportingServicesLRC(GeRtiFactory::GeRtiAmbassador_var &theGeRtiAmbassador_var);

    //Destructor
    virtual ~SupportingServicesLRC(void);

    void checkAttributeNotDefined(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &theAttributes);
    void checkAttributeNotDefined(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSetMap &theAttributes);
    void clear(void);

    void disableAttributeRelevanceAdvisorySwitch(void);
    void disableAttributeScopeAdvisorySwitch(void);
    void disableClassRelevanceAdvisorySwitch(void);
    void disableInteractionRelevanceAdvisorySwitch(void);

    void enableAttributeRelevanceAdvisorySwitch(void);
    void enableAttributeScopeAdvisorySwitch(void);
    void enableClassRelevanceAdvisorySwitch(void);
    void enableInteractionRelevanceAdvisorySwitch(void);

    bool getAttributeRelevanceAdvisorySwitch(void);
    bool getAttributeScopeAdvisorySwitch(void);
    bool getClassRelevanceAdvisorySwitch(void);
    bool getInteractionRelevanceAdvisorySwitch(void);

    GeRtiFactory::GeRtiHandle getAttributeHandle(std::wstring const &theName, GeRtiFactory::GeRtiHandle const &whichClass);
    std::wstring getAttributeName(GeRtiFactory::GeRtiHandle const &theHandle, GeRtiFactory::GeRtiHandle const &whichClass);

    GeRtiFactory::GeRtiHandle getAttributeRoutingSpaceHandle(GeRtiFactory::GeRtiHandle const &theHandle, GeRtiFactory::GeRtiHandle const &whichClass);

    void getAvailableDimensionsForClassAttribute(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theAttribute, GeRtiFactory::Handles &theDimensions);

    void getAvailableDimensionsForInteractionClass(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles &theDimensions);

    GeRtiFactory::GeRtiHandle getDimensionHandle(std::wstring const &theName, GeRtiFactory::GeRtiHandle const &whichSpace);
    std::wstring getDimensionName(GeRtiFactory::GeRtiHandle const &theHandle, GeRtiFactory::GeRtiHandle const &whichSpace);

    void getDimensionHandleSet(GeRtiFactory::GeRtiHandle const &theRegionHandle, GeRtiFactory::Handles &theDimensions);

    GeRtiFactory::GeRtiHandle getDimensionUpperBound(GeRtiFactory::GeRtiHandle const &theHandle);

    bool getInteractionAttributeDatum(GeRtiFactory::GeRtiHandle const &whichClass, GERTICO::AttributeDatum &parameterDatum);

    void getInteractionChildren(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSet &theChildren);
    void getInteractionParents(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles &theParents);
    void getObjectClassChildren(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSet &theChildren);
    void getObjectClassParents(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles &theParents);

    GeRtiFactory::GeRtiHandle getInteractionClassHandle(std::wstring const &theName);
    std::wstring getInteractionClassName(GeRtiFactory::GeRtiHandle const &theHandle);

    GeRtiFactory::GeRtiHandle getInteractionRoutingSpaceHandle(GeRtiFactory::GeRtiHandle const &theHandle);

    GeRtiFactory::GeRtiHandle getObjectClass(GeRtiFactory::GeRtiHandle const &theObject);

    GeRtiFactory::GeRtiHandle getObjectClassHandle(std::wstring const &theName);
    std::wstring getObjectClassName(GeRtiFactory::GeRtiHandle const &theHandle);

    void getObjectClassAttributeDataMap(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::AttributeDatumMap &theAttributeDatumMap);

    GeRtiFactory::GeRtiHandle getObjectInstanceHandle(std::wstring const &theName);
    std::wstring getObjectInstanceName(GeRtiFactory::GeRtiHandle const &theHandle);

    GeRtiFactory::GeRtiHandle getParameterHandle(std::wstring const &theName, GeRtiFactory::GeRtiHandle const &whichClass);
    std::wstring getParameterName(GeRtiFactory::GeRtiHandle const &theHandle, GeRtiFactory::GeRtiHandle const &whichClass);

    GeRtiFactory::GeRtiHandle getPrivilegeToDeleteId(void);

    GeRtiFactory::GeRtiHandle getInteractionParent(GeRtiFactory::GeRtiHandle const &theClass);
    GeRtiFactory::GeRtiHandle getObjectParent(GeRtiFactory::GeRtiHandle const &theClass);

    void getRangeBounds(GeRtiFactory::GeRtiHandle const &theRegionHandle, GeRtiFactory::GeRtiHandle const &theDimensionHandle, GeRtiFactory::Handles &theRangeBounds);

    GeRtiFactory::GeRtiHandle getRoutingSpaceHandle(std::wstring const &theName);
    std::wstring getRoutingSpaceName(GeRtiFactory::GeRtiHandle const &theHandle);


    void setRangeBounds(GeRtiFactory::GeRtiHandle const &theRegionHandle, GeRtiFactory::GeRtiHandle const &theDimensionHandle, GeRtiFactory::GeRtiHandle theLowerBound, GeRtiFactory::GeRtiHandle theUpperBound);

    bool testDimensionAttributes(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSet &theHandleSet);
    bool testDimensionInteraction(GeRtiFactory::GeRtiHandle const &theClass);
  };
}
#endif /* SupportingServicesLRC_H_  */
