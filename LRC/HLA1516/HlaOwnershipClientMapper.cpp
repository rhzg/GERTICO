/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Log: HlaOwnershipClientMapper.cpp,v $
Revision 1.3  2008/01/30 11:00:51  mul
Changes for ieee1516.

Revision 1.2  2007/09/05 15:40:14  mul
Changes for ieee1516.

Revision 1.1  2007/06/26 08:25:27  mul
New files for ieee1516.

Revision 1.12  2007/02/28 07:58:18  mul
Add namespace.

Revision 1.11  2006/09/13 09:13:14  mul
New gal.

Revision 1.10  2006/09/13 08:02:08  ba
new gal

Revision 1.9  2006/08/01 11:29:25  mul
Minor changes.

Revision 1.8  2005/05/03 15:19:25  mul
Add name scoping.

Revision 1.7  2003/08/20 08:45:36  hzg
name of gal resource changed

Revision 1.6  2003/08/07 12:07:05  mul
Make mapper a static/global function.

Revision 1.5  2003/05/28 06:38:27  mul
Use include paths starting in $GERTICO.

Revision 1.4  2003/05/21 11:59:25  hzg
Debug.h removed

Revision 1.3  2003/04/29 06:26:13  hzg
Portierung auf Windows

Revision 1.2  2003/02/10 14:59:04  ba
FedAm interface logged by Gal.

Revision 1.1  2002/11/06 15:06:31  hzg
Ownership included

 
**
*******************************************************************************/


#include "Util/Mapper.h"
#include "idl/GeRtiFactoryS.h"
#include "LRC/GeRtiEventMarketI.h"
#include "HlaOwnershipClientMapper.h"
#include "LRC/HLA1516/Mapper1516.h"

/********************************* Gal begin *********************************/   // inserted manually
// Redesign by GAL creator in 2006


//#define GalHLADebug 1

#ifdef GalHLADebug
#include "Gal/StdAfx.h"
#include "Gal/repository_l.h"
#include "Gal/event.h"

//#include "ut.h"
#define MAX_TXT 1024
 
static class Repository_l *rpGalM=(Repository::getSingleInstance())->getRepository_l("HLAServices.res","HLAServices");      
static class Event *rAOA_i0=rpGalM->getRefEvent("rAOA_i0");
static class Event *aODN_i0=rpGalM->getRefEvent("aODN_i0"); 
static class Event *aOAN_i0=rpGalM->getRefEvent("aOAN_i0"); 
static class Event *aOU_i0=rpGalM->getRefEvent("aOU_i0");
static class Event *rAOR_i0=rpGalM->getRefEvent("rAOR_i0"); 
static class Event *cAOAC_i0=rpGalM->getRefEvent("cAOAC_i0"); 
static class Event *iAO_i0=rpGalM->getRefEvent("iAO_i0"); 
static class Event *aINO=rpGalM->getRefEvent("aINO_i0"); 
static class Event *aOBRTI_i0=rpGalM->getRefEvent("aOBRTI_i0"); 

static char galMsg[MAX_TXT];

#endif

/*********************************** Gal end *********************************/

HlaOwnershipClientMapper::HlaOwnershipClientMapper(RTI::FederateAmbassador *amb) 
{
  fedAmb = amb;
}

HlaOwnershipClientMapper::~HlaOwnershipClientMapper() 
{
}


void HlaOwnershipClientMapper::requestAttributeOwnershipAssumption 
(
  GeRtiFactory::GeRtiHandle theObject, 
  const GeRtiFactory::Handles& offeredAttributes, 
  const GeRtiFactory::UserSuppliedTag &theTag
) 
{
  char *buff = NULL;
  RTI::AttributeHandleSet *attributeHandleSetPtr = new RTI::AttributeHandleSet();
  RTI::ObjectInstanceHandle objectInstanceHandle;
  RTI::UserSuppliedTag userSuppliedTag;
  std::auto_ptr<RTI::AttributeHandleSet> attributeHandleSet(attributeHandleSetPtr);

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectInstanceHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandleSet(*attributeHandleSet, offeredAttributes);
  GERTICO::Mapper1516::mapUserSuppliedTag(userSuppliedTag, theTag);
  GERTICO::Mapper::mapUserSuppliedTag(&buff, theTag);
					#ifdef GalHLADebug
		  			E1mBegin(rAOA_i0)
						{
							sprintf(galMsg,"object=%lu,tag=%s",theObject,buff);
							GERTICO::ut::printAttributeHandleSet(galMsg,*helperAttributes);
							E1mEnd(rAOA_i0,galMsg);
						}
					#endif  
  fedAmb->requestAttributeOwnershipAssumption(objectInstanceHandle, attributeHandleSet, userSuppliedTag); 
  delete []buff;
}

void HlaOwnershipClientMapper::requestDivestitureConfirmation 
(
  GeRtiFactory::GeRtiHandle theObject, 
  const GeRtiFactory::Handles& releasedAttributes
) 
{ 
  RTI::AttributeHandleSet *attributeHandleSetPtr = new RTI::AttributeHandleSet();
  RTI::ObjectInstanceHandle objectInstanceHandle;
  std::auto_ptr<RTI::AttributeHandleSet> attributeHandleSet(attributeHandleSetPtr);

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectInstanceHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandleSet(*attributeHandleSet, releasedAttributes);
  					#ifdef GalHLADebug
			  			E1mBegin(aODN_i0)
							{
								sprintf(galMsg,"object=%lu",theObject);
								GERTICO::ut::printAttributeHandleSet(galMsg,*helperAttributes);
								E1mEnd(aODN_i0,galMsg);
							}
						#endif  
  fedAmb->requestDivestitureConfirmation(objectInstanceHandle, attributeHandleSet); 
}

void HlaOwnershipClientMapper::attributeOwnershipDivestitureNotification 
(
  GeRtiFactory::GeRtiHandle theObject, 
  const GeRtiFactory::Handles& releasedAttributes
) 
{
  // Dummy for IEEE1516
}

void HlaOwnershipClientMapper::attributeOwnershipAcquisitionNotification 
(
  GeRtiFactory::GeRtiHandle theObject, 
  const GeRtiFactory::Handles& securedAttributes,
  const GeRtiFactory::UserSuppliedTag &theTag
) 
{ 
  char *buff = NULL;
  RTI::AttributeHandleSet *attributeHandleSetPtr = new RTI::AttributeHandleSet();
  RTI::ObjectInstanceHandle objectInstanceHandle;
  RTI::UserSuppliedTag userSuppliedTag;
  std::auto_ptr<RTI::AttributeHandleSet> attributeHandleSet(attributeHandleSetPtr);

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectInstanceHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandleSet(*attributeHandleSet, securedAttributes);
  GERTICO::Mapper1516::mapUserSuppliedTag(userSuppliedTag, theTag);
  GERTICO::Mapper::mapUserSuppliedTag(&buff, theTag);
  					#ifdef GalHLADebug
		  				E1mBegin(aOAN_i0)
							{
								sprintf(galMsg,"object=%lu,tag=%s",theObject,buff);
								E1mEnd(aOAN_i0,galMsg);
							}
						#endif  
  fedAmb->attributeOwnershipAcquisitionNotification(objectInstanceHandle, attributeHandleSet, userSuppliedTag); 
  delete []buff;
}

void HlaOwnershipClientMapper::attributeOwnershipUnavailable 
(
  GeRtiFactory::GeRtiHandle theObject, 
  const GeRtiFactory::Handles& theAttributes
) 
{ 
  RTI::AttributeHandleSet *attributeHandleSetPtr = new RTI::AttributeHandleSet();
  RTI::ObjectInstanceHandle objectInstanceHandle;
  std::auto_ptr<RTI::AttributeHandleSet> attributeHandleSet(attributeHandleSetPtr);

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectInstanceHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandleSet(*attributeHandleSet, theAttributes);
  					#ifdef GalHLADebug
		  				E1mBegin(aOU_i0)
							{
								sprintf(galMsg,"object=%lu",theObject);
								GERTICO::ut::printAttributeHandleSet(galMsg,*helperAttributes);
								E1mEnd(aOU_i0,galMsg);
							}
						#endif  
  fedAmb->attributeOwnershipUnavailable(objectInstanceHandle, attributeHandleSet); 
}

void HlaOwnershipClientMapper::requestAttributeOwnershipRelease 
(
  GeRtiFactory::GeRtiHandle theObject,
  const GeRtiFactory::Handles& candidateAttributes,
  const GeRtiFactory::UserSuppliedTag &theTag
) 
{ 
  char *buff = NULL;
  RTI::AttributeHandleSet *attributeHandleSetPtr = new RTI::AttributeHandleSet();
  RTI::ObjectInstanceHandle objectInstanceHandle;
  RTI::UserSuppliedTag userSuppliedTag;
  std::auto_ptr<RTI::AttributeHandleSet> attributeHandleSet(attributeHandleSetPtr);

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectInstanceHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandleSet(*attributeHandleSet, candidateAttributes);
  GERTICO::Mapper1516::mapUserSuppliedTag(userSuppliedTag, theTag);
  GERTICO::Mapper::mapUserSuppliedTag(&buff, theTag);
  					#ifdef GalHLADebug
			  			E1mBegin(rAOR_i0)
							{
								sprintf(galMsg,"object=%lu,tag=%s",theObject,buff);
								GERTICO::ut::printAttributeHandleSet(galMsg,*helperAttributes);
								E1mEnd(rAOR_i0,galMsg);
							}
						#endif  
  fedAmb->requestAttributeOwnershipRelease(objectInstanceHandle, attributeHandleSet, userSuppliedTag); 
  delete []buff;
}

void HlaOwnershipClientMapper::confirmAttributeOwnershipAcquisitionCancellation 
(
  GeRtiFactory::GeRtiHandle theObject, 
  const GeRtiFactory::Handles& theAttributes
) 
{ 
  RTI::AttributeHandleSet *attributeHandleSetPtr = new RTI::AttributeHandleSet();
  RTI::ObjectInstanceHandle objectInstanceHandle;
  std::auto_ptr<RTI::AttributeHandleSet> attributeHandleSet(attributeHandleSetPtr);

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectInstanceHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandleSet(*attributeHandleSet, theAttributes);
  					#ifdef GalHLADebug
			  			E1mBegin(cAOAC_i0)
							{
								sprintf(galMsg,"object=%lu",theObject);
								GERTICO::ut::printAttributeHandleSet(galMsg,*helperAttributes);
								E1mEnd(cAOAC_i0,galMsg);
							}
						#endif  
  fedAmb->confirmAttributeOwnershipAcquisitionCancellation(objectInstanceHandle, attributeHandleSet); 
}

void HlaOwnershipClientMapper::informAttributeOwnership 
(
  GeRtiFactory::GeRtiHandle theObject, 
  GeRtiFactory::GeRtiHandle theAttribute, 
  GeRtiFactory::GeRtiHandle theOwner
) 
{ 
  RTI::ObjectInstanceHandle objectInstanceHandle;
  RTI::AttributeHandle attribute;
  RTI::FederateHandle federate;
  
  GERTICO::Mapper1516::mapObjectInstanceHandle(objectInstanceHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandle(attribute, theAttribute);
  GERTICO::Mapper1516::mapFederateHandle(federate, theOwner);
					#ifdef GalHLADebug
						E1mBegin(iAO_i0)
						{
							sprintf(galMsg,"object=%lu,attribute=%lu,owner=%lu",theObject,theAttribute,theOwner);
							E1mEnd(iAO_i0,galMsg);
						}
					#endif  
  fedAmb->informAttributeOwnership(objectInstanceHandle, attribute, federate); 
}

void HlaOwnershipClientMapper::attributeIsNotOwned 
(
  GeRtiFactory::GeRtiHandle theObject, 
  GeRtiFactory::GeRtiHandle theAttribute
) 
{ 
  RTI::ObjectInstanceHandle objectInstanceHandle;
  RTI::AttributeHandle attribute;
  
  GERTICO::Mapper1516::mapObjectInstanceHandle(objectInstanceHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandle(attribute, theAttribute);
					#ifdef GalHLADebug
		  			E1mBegin(aINO)
						{
							sprintf(galMsg,"object=%lu,attribute=%lu",theObject,theAttribute);
							E1mEnd(aINO,galMsg);
						}
					#endif  
  fedAmb->attributeIsNotOwned(objectInstanceHandle, attribute); 
}

void HlaOwnershipClientMapper::attributeOwnedByRTI 
(
  GeRtiFactory::GeRtiHandle theObject, 
  GeRtiFactory::GeRtiHandle theAttribute
) 
{ 
  RTI::ObjectInstanceHandle objectInstanceHandle;
  RTI::AttributeHandle attribute;
  
  GERTICO::Mapper1516::mapObjectInstanceHandle(objectInstanceHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandle(attribute, theAttribute);
					#ifdef GalHLADebug
						E1mBegin(aOBRTI_i0)
						{
							sprintf(galMsg,"object=%lu,attribute=%lu",theObject,theAttribute);
							E1mEnd(aOBRTI_i0,galMsg);
						}
					#endif  
  fedAmb->attributeIsOwnedByRTI(objectInstanceHandle, attribute); 
}


