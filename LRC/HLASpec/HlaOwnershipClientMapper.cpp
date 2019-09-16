/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Log: HlaOwnershipClientMapper.cpp,v $
Revision 1.16  2007/09/05 15:45:32  mul
Changes for ieee1516.

Revision 1.15  2007/06/25 15:12:08  mul
Changes for ieee1516.

Revision 1.14  2007/06/08 12:06:09  mul
Changes for ieee1516.

Revision 1.13  2007/05/03 14:43:40  mul
Add wchar parameter to exception constructor.

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

#include "idl/GeRtiFactoryS.h"
#include "LRC/GeRtiEventMarketI.h"
#include "HlaOwnershipClientMapper.h"
#include "include/RTI_1.3/RTI.hh"
#include "Mapper13.h"

/********************************* Gal begin *********************************/   // inserted manually
// Redesign by GAL creator in 2006


#define GalHLADebug 1

#ifdef GalHLADebug
#include "Gal/StdAfx.h"
#include "Gal/repository_l.h"
#include "Gal/event.h"

#include "ut.h"
 
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

HlaOwnershipClientMapper::HlaOwnershipClientMapper (RTI::FederateAmbassador *amb) 
{
  fedAmb = amb;
  helperAttributes = RTI::AttributeHandleSetFactory::create(0);
}

HlaOwnershipClientMapper::~HlaOwnershipClientMapper () 
{
  delete helperAttributes;
}


void HlaOwnershipClientMapper::requestAttributeOwnershipAssumption 
(
  GeRtiFactory::GeRtiHandle theObject, 
  const GeRtiFactory::Handles& offeredAttributes, 
  const GeRtiFactory::UserSuppliedTag &theTag
) 
{ 
  char *buff = NULL;
  helperAttributes->empty();
  GERTICO::Mapper13::mapAttributeHandleSet(*helperAttributes, offeredAttributes);
  GERTICO::Mapper::mapUserSuppliedTag(&buff, theTag);
					#ifdef GalHLADebug
		  			E1mBegin(rAOA_i0)
						{
              if (buff)
              {
							  sprintf(galMsg,"object=%lu,tag=%s",theObject,buff);
              }
              else
              {
							  sprintf(galMsg,"object=%lu,tag=",theObject);
              }
							GERTICO::ut::printAttributeHandleSet(galMsg,*helperAttributes);
							E1mEnd(rAOA_i0,galMsg);
						}
					#endif  
  fedAmb->requestAttributeOwnershipAssumption(theObject, *helperAttributes, buff);
  delete []buff;
}

void HlaOwnershipClientMapper::requestDivestitureConfirmation 
(
  GeRtiFactory::GeRtiHandle theObject, 
  const GeRtiFactory::Handles& releasedAttributes
) 
{
  // Dummy for HLA 1.3
}

void HlaOwnershipClientMapper::attributeOwnershipDivestitureNotification 
(
  GeRtiFactory::GeRtiHandle theObject, 
  const GeRtiFactory::Handles& releasedAttributes
) 
{ 
  helperAttributes->empty();
  GERTICO::Mapper13::mapAttributeHandleSet(*helperAttributes, releasedAttributes);
  					#ifdef GalHLADebug
			  			E1mBegin(aODN_i0)
							{
								sprintf(galMsg,"object=%lu",theObject);
								GERTICO::ut::printAttributeHandleSet(galMsg,*helperAttributes);
								E1mEnd(aODN_i0,galMsg);
							}
						#endif  
  fedAmb->attributeOwnershipDivestitureNotification (theObject, *helperAttributes); 
}

void HlaOwnershipClientMapper::attributeOwnershipAcquisitionNotification 
(
  GeRtiFactory::GeRtiHandle theObject, 
  const GeRtiFactory::Handles& securedAttributes,
  const GeRtiFactory::UserSuppliedTag &theTag
) 
{ 
  helperAttributes->empty();
  GERTICO::Mapper13::mapAttributeHandleSet(*helperAttributes, securedAttributes);
  					#ifdef GalHLADebug
		  				E1mBegin(aOAN_i0)
							{
								sprintf(galMsg,"object=%lu",theObject);
								E1mEnd(aOAN_i0,galMsg);
							}
						#endif  
  fedAmb->attributeOwnershipAcquisitionNotification (theObject, *helperAttributes); 
}

void HlaOwnershipClientMapper::attributeOwnershipUnavailable 
(
  GeRtiFactory::GeRtiHandle theObject, 
  const GeRtiFactory::Handles& theAttributes
) 
{ 
  helperAttributes->empty();
  GERTICO::Mapper13::mapAttributeHandleSet(*helperAttributes, theAttributes);
  					#ifdef GalHLADebug
		  				E1mBegin(aOU_i0)
							{
								sprintf(galMsg,"object=%lu",theObject);
								GERTICO::ut::printAttributeHandleSet(galMsg,*helperAttributes);
								E1mEnd(aOU_i0,galMsg);
							}
						#endif  
  fedAmb->attributeOwnershipUnavailable (theObject, *helperAttributes); 
}

void HlaOwnershipClientMapper::requestAttributeOwnershipRelease 
(
  GeRtiFactory::GeRtiHandle theObject, 
  const GeRtiFactory::Handles& candidateAttributes, 
  const GeRtiFactory::UserSuppliedTag &theTag
) 
{ 
  char *buff = NULL;
  helperAttributes->empty();
  GERTICO::Mapper13::mapAttributeHandleSet(*helperAttributes, candidateAttributes);
  GERTICO::Mapper::mapUserSuppliedTag(&buff, theTag);
  					#ifdef GalHLADebug
			  			E1mBegin(rAOR_i0)
							{
                if (buff)
                {
								  sprintf(galMsg,"object=%lu,tag=%s",theObject,buff);
                }
                else
                {
								  sprintf(galMsg,"object=%lu,tag=",theObject);
                }
								GERTICO::ut::printAttributeHandleSet(galMsg,*helperAttributes);
								E1mEnd(rAOR_i0,galMsg);
							}
						#endif  
  fedAmb->requestAttributeOwnershipRelease(theObject, *helperAttributes, buff); 
  delete []buff;
}

void HlaOwnershipClientMapper::confirmAttributeOwnershipAcquisitionCancellation 
(
  GeRtiFactory::GeRtiHandle theObject, 
  const GeRtiFactory::Handles& theAttributes
) 
{ 
  helperAttributes->empty();
  GERTICO::Mapper13::mapAttributeHandleSet(*helperAttributes, theAttributes);
  					#ifdef GalHLADebug
			  			E1mBegin(cAOAC_i0)
							{
								sprintf(galMsg,"object=%lu",theObject);
								GERTICO::ut::printAttributeHandleSet(galMsg,*helperAttributes);
								E1mEnd(cAOAC_i0,galMsg);
							}
						#endif  
  fedAmb->confirmAttributeOwnershipAcquisitionCancellation (theObject, *helperAttributes); 
}

void HlaOwnershipClientMapper::informAttributeOwnership 
(
  GeRtiFactory::GeRtiHandle theObject, 
  GeRtiFactory::GeRtiHandle theAttribute, 
  GeRtiFactory::GeRtiHandle theOwner
) 
{ 
					#ifdef GalHLADebug
						E1mBegin(iAO_i0)
						{
							sprintf(galMsg,"object=%lu,attribute=%lu,owner=%lu",theObject,theAttribute,theOwner);
							E1mEnd(iAO_i0,galMsg);
						}
					#endif  
  fedAmb->informAttributeOwnership (theObject, theAttribute, theOwner); 
}

void HlaOwnershipClientMapper::attributeIsNotOwned 
(
  GeRtiFactory::GeRtiHandle theObject, 
  GeRtiFactory::GeRtiHandle theAttribute
) 
{ 
					#ifdef GalHLADebug
		  			E1mBegin(aINO)
						{
							sprintf(galMsg,"object=%lu,attribute=%lu",theObject,theAttribute);
							E1mEnd(aINO,galMsg);
						}
					#endif  
  fedAmb->attributeIsNotOwned (theObject, theAttribute); 
}

void HlaOwnershipClientMapper::attributeOwnedByRTI 
(
  GeRtiFactory::GeRtiHandle theObject, 
  GeRtiFactory::GeRtiHandle theAttribute
) 
{ 
					#ifdef GalHLADebug
						E1mBegin(aOBRTI_i0)
						{
							sprintf(galMsg,"object=%lu,attribute=%lu",theObject,theAttribute);
							E1mEnd(aOBRTI_i0,galMsg);
						}
					#endif  
  fedAmb->attributeOwnedByRTI (theObject, theAttribute); 
}


