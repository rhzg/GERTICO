/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: RegisteredObject.h,v $
Revision 1.38  2009/09/23 06:48:13  mul
Add deleted objects.

Revision 1.37  2009/06/02 12:04:13  mul
Add acquiring federates to save / restore data.

Revision 1.36  2007/09/25 08:00:00  mul
Changes for ddm.

Revision 1.35  2007/09/05 15:14:42  mul
Changes for ieee1516.

Revision 1.34  2007/06/28 10:13:33  mul
Add new methods.

Revision 1.33  2007/03/06 09:26:56  mul
Changes for ieee conversion.

Revision 1.32  2007/01/09 09:55:21  mul
Clean up some program code.

Revision 1.31  2006/12/15 08:41:46  mul
Add function.

Revision 1.30  2006/10/12 13:48:17  mul
Fix region logic.

Revision 1.29  2006/10/05 15:01:52  hzg
release request

Revision 1.28  2006/09/21 14:45:28  mul
Remove unused methods.

Revision 1.27  2006/08/30 11:37:37  mul
Add federate holder class.

Revision 1.26  2006/08/23 11:13:17  mul
Changes for phase 4 testcases.

Revision 1.25  2006/08/21 06:59:15  mul
Changes for phase 4 testcases.

Revision 1.24  2006/08/18 12:54:29  mul
Changes for phase 4 testcases.

Revision 1.23  2006/08/15 12:35:32  mul
Changes for phase 4 tests.

Revision 1.22  2006/08/08 14:08:14  mul
Move named object map to registered object.

Revision 1.21  2006/08/01 11:20:54  mul
Changes in object handling and mapping.

Revision 1.20  2006/06/28 14:11:51  mul
Remove unused method.

Revision 1.19  2006/06/23 13:03:46  mul
Refine region logic.

Revision 1.18  2006/05/23 11:32:44  mul
Remove internal logic between declaration and ownership management.

Revision 1.17  2006/05/17 06:37:36  mul
Minor changes.

Revision 1.16  2006/05/09 13:19:52  hzg
new attribute state "acquired" introduced

Revision 1.15  2006/03/17 11:30:03  mul
Fix scope logic for data distribution.

Revision 1.14  2006/02/27 14:27:34  mul
Change handling of attribute/region pairs.

Revision 1.13  2006/02/09 15:33:04  mul
Removed an enum value.

Revision 1.12  2006/02/08 14:03:24  mul
Added a const qualifier for a method.

Revision 1.11  2005/08/22 14:12:24  mul
Add some helper functions.

Revision 1.10  2005/05/03 14:52:51  mul
Xerces interface in one file.

Revision 1.9  2005/02/25 11:20:26  mul
Minor changes.

Revision 1.8  2005/02/23 11:04:21  hzg
minor formatting

Revision 1.7  2005/02/07 10:34:02  mul
Changes due to test cases.

Revision 1.6  2004/12/13 15:52:41  mul
One function only for retrieving ownership attributes.

Revision 1.5  2004/09/23 14:57:08  mul
Changes for save federation.

Revision 1.4  2004/08/19 09:35:50  mul
Changes for save/restore logic.

Revision 1.3  2004/07/16 10:28:17  mul
Changes due to verfication test.

Revision 1.2  2004/05/28 11:20:13  mul
Fix include paths.

Revision 1.1  2004/05/27 11:22:16  mul
Integrate subscriber management.

 
**
*******************************************************************************/

/* -*- C++ -*- $Id: RegisteredObject.h,v 1.38 2009/09/23 06:48:13 mul Exp $ */

#ifndef RegisteredObject_H_
#define RegisteredObject_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
//#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "XercesInclude.h"
#include "HLAparseErrorHandler.h"

#include "ClassDescr.h"
#include "Util/GeRtiTypes.h"
#include "Item.h"

namespace GERTICO
{
  //****************************************************
  //
  enum AttributeStatus
  {
    undefined,
    unowned,	// attribute is defined but not owned by anyone
    owned,	// attribute is owned
    acquiring,	// attribute is owned and acquisition is in progress
    acquired,	// attribute is owned and acquisition is forwarded
    divesting,	// attribute is still owned but divesiture is in progress
    divestConfirm
  };

  //****************************************************
  //
  class AttributeInfo
  {
    // Key is region id, second is set of federate ids.
    GERTICO::AttributeStatus status;
    GERTICO::HandleSetMap regionFederates;
    GERTICO::HandleSet acquiringFederates;
    GERTICO::HandleSet previousOwners;
    GeRtiFactory::GeRtiHandle federate;
    GeRtiFactory::GeRtiHandle orderType;
    GeRtiFactory::GeRtiHandle orderTypeDefault;
    GeRtiFactory::GeRtiHandle transportationType;
    GeRtiFactory::GeRtiHandle transportationTypeDefault;
		bool isRequested;

    // Strings for save/restore.
    std::string acquiringFederateStr;
    std::string acquiringFederatesStr;
    std::string federateStr;
    std::string idStr;
    std::string orderTypeStr;
    std::string regionStr;
    std::string regionsStr;
    std::string statusStr;
    std::string transportationTypeStr;

    void addPreviousOwner(GeRtiFactory::GeRtiHandle const &theFederate);
    void init(void);

  public:
    AttributeInfo(void);
    AttributeInfo(GeRtiFactory::GeRtiHandle const &theFederate, AttributeStatus const &s, GeRtiFactory::GeRtiHandle const &theOrderTypeDefault, GeRtiFactory::GeRtiHandle const &theTransportationTypeDefault);

		void addAcquiringFederate(GeRtiFactory::GeRtiHandle const &theFederate);
		void removeAcquiringFederate(GeRtiFactory::GeRtiHandle const &theFederate);
		bool testIfFederateIsAcquiring(GeRtiFactory::GeRtiHandle const &theFederate);
		GeRtiFactory::GeRtiHandle getFirstAcquiringFederate();
		void setRequested();
		bool testRequested();
		void unsetRequested();
    void addRegion(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion);
    void associateRegion(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion);
    bool beingAcquired(void);
    void changeOrderType(GeRtiFactory::GeRtiHandle const &theOrderType);
    void changeTransportationType(GeRtiFactory::GeRtiHandle const &theTransportationType);
    void clearFederateRegion(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion);
    void clearFederateRegions(GeRtiFactory::GeRtiHandle const &theFederate);
    void delRegion(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion);
    GeRtiFactory::GeRtiHandle getFederate(void);
    GeRtiFactory::GeRtiHandle getOrderType(void);
    void getAllRegions(GERTICO::HandleSet &theRegions);
    void getFedRegions(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theRegions);
    void getOwner(GeRtiFactory::GeRtiHandle &theOwner);
    GERTICO::AttributeStatus getStatus(void);
    GeRtiFactory::GeRtiHandle getTransportationType(void);
    bool ownedByFederate(GeRtiFactory::GeRtiHandle const &theFederate);
    void print(void);
    void restore(DOMElement &theDOMElement);
    void save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
    void setStatusAcquired(void);
    void setStatusAcquiring(void);
    void setStatusDivestConfirm(void);
    void setStatusDivesting(void);
    void setStatusFlag(GERTICO::AttributeStatus const &theStatus);
    void setStatusOwned(GeRtiFactory::GeRtiHandle const &theFederate);
    void setStatusUnowned(void);
    bool testRegion(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion);
    void unsetFederate(GeRtiFactory::GeRtiHandle const &theFederate);
  };

  // Key is attribute id, second is attribute information.
  typedef std::map<GeRtiFactory::GeRtiHandle, AttributeInfo*, cmpHandle> AttributeMap;


  //****************************************************
  //
  class AttInfo
  {
    GeRtiFactory::GeRtiHandle status;
  public:
    GERTICO::HandleSet regions;
    GeRtiFactory::GeRtiHandle federate;
    GeRtiFactory::GeRtiHandle orderType;
    GeRtiFactory::GeRtiHandle transportationType;
    AttInfo();
    virtual ~AttInfo();
    GeRtiFactory::GeRtiHandle getStatus(void);
    void setStatus(GeRtiFactory::GeRtiHandle const &theStatus);
  };

  // Key is attribute id.
  typedef std::map<GeRtiFactory::GeRtiHandle, AttInfo> AttInfoMap;


  //****************************************************
  //
  class PubAttributeDB
  {
    bool started;
  public:
    GERTICO::HandleSet attributeSet;
    PubAttributeDB(void);
    virtual ~PubAttributeDB(void);

    bool getStarted(void);
    void setStarted(bool const &theStarted);
  };

  // Key is federate id, second is attribute 
  typedef std::map<GeRtiFactory::GeRtiHandle, PubAttributeDB> FedPubAttributeMap;


  //****************************************************
  //
  class RegisteredObject
  {
    AttributeMap attributes;
    GeRtiFactory::GeRtiHandle myId;
    GeRtiFactory::GeRtiHandle myClass;
    std::wstring myName;

    // Strings for save/restore.
    std::string attributeStr;
    std::string attributesStr;
    std::string classStr;
    std::string idStr;
    std::string nameStr;

    void init(void);

  public:

    // Use in LRC for discover object - attributes not known.
    // Use in gerti where attributes are added later.
    RegisteredObject(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theObjectId, std::wstring const &theObjectName);
    
    // Use in LRC where the class description is not available. Only partial class knowledge.
    RegisteredObject(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theObjectId, std::wstring const &theObjectName, GERTICO::HandleSet &theObjectAttributes, GERTICO::AttributeDatumMap &theAttributeDatumMap);
    
    // Use in gerti where all information on all classes, federates and objects known.
    RegisteredObject(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::ClassDescr &theClassDescr, GeRtiFactory::GeRtiHandle const &theObjectId, std::wstring const &theObjectName, GERTICO::HandleSet &theAttributesPub);

    virtual ~RegisteredObject(void);

    void addAttribute(GeRtiFactory::GeRtiHandle const &theAttributeId, AttributeInfo *theAttributeInfo);
    void addAttributesDefaultRegion(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theAttributePub);
    void addAttributesRegion(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theAttributes, GeRtiFactory::GeRtiHandle const &theRegion);
    void addAttributesRegions(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSetMap &theAttRegMap);
    void cancelPendingAcquisitions(GeRtiFactory::GeRtiHandle const &theFederate);
    void changeAttributeOrderType(GeRtiFactory::Handles const &theAttributes, GeRtiFactory::GeRtiHandle const &theOrderType);
    void changeAttributeTransportationType(GeRtiFactory::Handles const &theAttributes, GeRtiFactory::GeRtiHandle const &);
    void checkOwnershipAcquisitionPending(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theAttributes, GeRtiFactory::GeRtiHandle const &thePrivilegeToDeleteId);
    void clearRegion(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion);
    void delRegion(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion);
    void getAllRegions(GERTICO::HandleSet &theRegions);
    AttributeInfo* getAttribute(GeRtiFactory::GeRtiHandle theAttribute) throw(GeRtiFactory::AttributeNotDefined);
    GeRtiFactory::GeRtiHandle getClassId(void) const;
    void getAttributeIds(GERTICO::HandleSet &theAttributes);
    void getDefaultRegionAtts(GERTICO::HandleSet &theAttributes);
    void getFedAttRegions(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theAttributeId, GERTICO::HandleSet &theRegions);
    void getFedRegionOwnedAtts(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion, GERTICO::HandleSet &theAttributes);
    void getFederateObjectAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theAttributes, GeRtiFactory::GeRtiHandle const &theRegion);
    GeRtiFactory::GeRtiHandle getId(void);
    void getName(std::wstring &theObjectName);
    void getNotFederateObjectAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theAttributes);
    void getOwnedAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &privilegeToDeleteId, GERTICO::HandleSet &attributes, bool const &needPrivilegeToDelete);
    void getOwner(GeRtiFactory::GeRtiHandle &theOwner, GeRtiFactory::GeRtiHandle const &privilegeToDeleteId);
    void getOwners(GERTICO::HandleSet &theOwners);
    void getUnownedObjectAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theAttributes);
    void loadAttInfoMap(AttInfoMap &theAttInfoMap);
    bool ownsAnyAttributeInstances(GeRtiFactory::GeRtiHandle const &theFederate);
    bool ownsAnyAttributeInstancesNoPriv(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &thePrivilegeToDeleteId);
    void print(void);
    void restore(DOMElement &theDOMElement);
    void save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
    // USE IN LRC ONLY
    void unownAttribute(GeRtiFactory::GeRtiHandle theFederate, GeRtiFactory::GeRtiHandle theAttribute) throw(GeRtiFactory::OwnershipAcquisitionPending);
  };  

  typedef std::map <std::wstring, GeRtiFactory::GeRtiHandle> ObjByNameMap;
  typedef std::map<GeRtiFactory::GeRtiHandle, RegisteredObject*, cmpHandle> ObjectMap;

  //****************************************************
  //
  class RegisteredObjectsHolder
  {
    ACE_Thread_Mutex pm;
    GERTICO::ObjectMap deletedObjects;
    GERTICO::ObjectMap objects;
    GERTICO::ObjByNameMap objectsByName;
    std::set <std::wstring, cmpWstring> reservedObjectNames;
    static std::string classStr;
    static std::string idStr;
    static std::string nameStr;

    void addObjectByName(std::wstring const &theObjectName, GeRtiFactory::GeRtiHandle const &theObjectId)
      throw(GeRtiFactory::ObjectAlreadyRegistered);
    void delObjectByName(std::wstring const &theObjectName);

  public:
    RegisteredObjectsHolder(void);
    virtual ~RegisteredObjectsHolder(void);

    void addObject(GeRtiFactory::GeRtiHandle const &theObjectId, GERTICO::RegisteredObject *theRegisteredObject, std::wstring const &theObjectName);
    void cancelPendingAcquisitions(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theObjects);
    void clear(void);
    void delObject(GeRtiFactory::GeRtiHandle const &theObjectId);
    RegisteredObject *getObject(GeRtiFactory::GeRtiHandle const &theObject) throw(GeRtiFactory::ObjectNotKnown);
    RegisteredObject *getObjectByName(std::wstring const &theObjectName);
    void getObjectIds(GERTICO::HandleSet &theObjects);
    void getOwnedObjectIds(const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::HandleSet &theObjects, GeRtiFactory::GeRtiHandle const &privilegeToDeleteId);
    bool ownsAnyAttributeInstances(GeRtiFactory::GeRtiHandle const &theFederate);
    bool ownsAnyAttributeInstancesNoPriv(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &thePrivilegeToDeleteId);
    void registerObjectInstance(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::ClassDescr &theClassDescr, GeRtiFactory::GeRtiHandle const &theObjectId, std::wstring const &theObjectName, GERTICO::HandleSet &theAttributesPub);
    void reserveObjectInstanceName(std::wstring const &theObjectInstanceName);
    void restore(DOMElement &theDOMElement);
    void save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };  
};

#endif
