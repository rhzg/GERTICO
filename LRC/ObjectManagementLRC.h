/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** ObjectManagementLRC.h
**
*******************************************************************************/

// -*- C++ -*-
//
// $Id: ObjectManagementLRC.h,v 1.13 2009/09/23 07:06:29 mul Exp $

#ifndef ObjectManagementLRC_H_
#define ObjectManagementLRC_H_

#include <string>

#include "idl/GeRtiFactoryS.h"

#include "Util/GeRtiTypes.h"
#include "Util/RunTimeObjectDB.h"
#include "LRC/SupportingServicesLRC.h"

namespace GERTICO
{
  class ObjectManagementLRC
  {
    ACE_Thread_Mutex pm;
    GERTICO::HandleSetMap classObjectsSet;
    GERTICO::RegisteredObjectsHolder &registeredObjectsHolder;
    GERTICO::RunTimeObjectDB &runTimeObjectDB;
    GERTICO::SupportingServicesLRC &supportingServicesLRC;
    GeRtiFactory::GeRtiAmbassador_var GeRtiAmbVar;
    GeRtiFactory::GeRtiHandle federate;

    // Interaction management.
    GERTICO::HandleMap interactionOrderTypeMap;
    GERTICO::HandleMap interactionTransportationTypeMap;

    // Turn On management.
    // Layout: <object, <attribute, subscriber>>
    GERTICO::HandleSetSetMap turnOnUpdatesDB;

    void addClassObjectsSet(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theObject);
    void deleteObject(GeRtiFactory::GeRtiHandle const &theObjectId);
    void deleteClassObjectsSet(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theObject);
    void registerObject(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectId, GeRtiFactory::GeRtiHandle const &theClass, std::wstring const &theObjectName);

  public:
    //Constructor 
    ObjectManagementLRC(GeRtiFactory::GeRtiAmbassador_var &theGeRtiAmbassador_var, GeRtiFactory::GeRtiHandle &theFederate, GERTICO::RegisteredObjectsHolder &theRegisteredObjectsHolder, GERTICO::RunTimeObjectDB &theRunTimeObjectDB, GERTICO::SupportingServicesLRC &theSupportingServicesLRC);

    //Destructor 
    virtual ~ObjectManagementLRC(void);

	  void changeAttributeOrderType(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes, GeRtiFactory::GeRtiHandle const &theType);
	  void changeAttributeTransportationType(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes, GeRtiFactory::GeRtiHandle const &theType);
	  void changeInteractionOrderType(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theType);
	  void changeInteractionTransportationType(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theType);
    void checkHLA(std::wstring const &theName);
    void deleteObjectInstance(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Time &theTime, GeRtiFactory::UserSuppliedTag const &theTag, GeRtiFactory::GeRtiHandle const &theSerialNumber);
    void deleteObjectInstance(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::UserSuppliedTag const &theTag);
    void discoverObjectInstance(GeRtiFactory::GeRtiHandle const &theObjectId, GeRtiFactory::GeRtiHandle const &theClass, std::wstring const &theObjectName);
    GeRtiFactory::GeRtiHandle getObjectClass(GeRtiFactory::GeRtiHandle const &theObject);
    GERTICO::RegisteredObject *getObject(GeRtiFactory::GeRtiHandle const &theObject);
    GERTICO::RegisteredObject *getObjectByName(std::wstring const &theObjectName);
    void getObjectsForClass(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSet &theObjects);
    void loadObjectAttInfoMap(GeRtiFactory::GeRtiHandle const &theObjectId, std::wstring const &theObjectName, GeRtiFactory::GeRtiHandle const &theClass, AttInfoMap &theAttInfoMap);
    void localDeleteObjectInstance(GeRtiFactory::GeRtiHandle theObject, GeRtiFactory::GeRtiHandle federate);
    GeRtiFactory::GeRtiHandle registerObjectInstance(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, std::wstring const &theObject);
    GeRtiFactory::GeRtiHandle registerObjectInstance(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass);
    GeRtiFactory::GeRtiHandle registerObjectInstanceWithRegion(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, std::wstring const &theObject, GERTICO::HandleSetMap &theAttRegMap);
    GeRtiFactory::GeRtiHandle registerObjectInstanceWithRegion(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSetMap &theAttRegMap);
    void requestClassAttributeValueUpdate(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &theAttributes, GeRtiFactory::UserSuppliedTag const &theTag);
    void requestObjectAttributeValueUpdate(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes, GeRtiFactory::UserSuppliedTag const &theTag);
    void reserveObjectInstanceName(std::wstring const &theObjectInstanceName);
    void reset(void);
    void setAttributeData(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::HandleValues &theAttributes);
    void turnUpdatesOffForObjectInstance(GeRtiFactory::GeRtiHandle const &theObject, GERTICO::HandleSetMap const &theAttributeSubscribers, GeRtiFactory::Handles &theUserAttributes);
    void turnUpdatesOnForObjectInstance(GeRtiFactory::GeRtiHandle const &theObject, GERTICO::HandleSetMap const &theAttributeSubscribers, GeRtiFactory::Handles &theUserAttributes);
  };
}
#endif /* ObjectManagementLRC_H_  */
