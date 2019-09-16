/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: DataDistributionManagementLRC.cpp,v $
Revision 1.7  2007/09/25 08:33:05  mul
Changes for ddm.

Revision 1.6  2007/09/06 06:29:27  mul
Changes for ieee1516.

Revision 1.5  2007/06/08 12:18:29  mul
Changes for ieee1516.

Revision 1.4  2007/05/15 13:33:23  mul
Changes for combined 1.3 and 1516 logic.

Revision 1.3  2007/05/03 14:52:45  mul
Add wchar parameter to exception constructor.

Revision 1.2  2006/10/30 09:39:33  mul
Fix memory management.

Revision 1.1  2006/10/23 14:51:20  mul
New management group.

 
**
*******************************************************************************/

#include <iostream>
#include "DataDistributionManagementLRC.h"
#include "Util/Mapper.h"

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::DataDistributionManagementLRC::DataDistributionManagementLRC(GeRtiFactory::GeRtiAmbassador_var &theGeRtiAmbassador_var, GeRtiFactory::GeRtiHandle &theFederate, GERTICO::RunTimeObjectDB &theRunTimeObjectDB) : runTimeObjectDB(theRunTimeObjectDB), federate(theFederate)
{
  GeRtiAmb_var = GeRtiFactory::GeRtiAmbassador::_duplicate(theGeRtiAmbassador_var);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::DataDistributionManagementLRC::~DataDistributionManagementLRC(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagementLRC::associateRegionsForUpdates(GeRtiFactory::GeRtiHandle const &theObject, GERTICO::HandleSetMap const &theAttRegMap)
{
  GeRtiFactory::AttributeRegionsSeq attributeRegionsSeq;

  GERTICO::Mapper::mapAttributeRegionsSeqFromHandleSetMap(attributeRegionsSeq, theAttRegMap);

  GeRtiAmb_var->associateRegionsForUpdates(theObject, attributeRegionsSeq);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::DataDistributionManagementLRC::createRegion(GeRtiFactory::GeRtiHandle const &theSpace, CORBA::ULong const &numberOfExtents, GERTICO::HandleSet const &theDimensions)
{
  GeRtiFactory::Handles dimensions;
  GeRtiFactory::GeRtiHandle region = 0;
  
  GERTICO::Mapper::mapHandleSet(dimensions, theDimensions);
  region = GeRtiAmb_var->createRegion(theSpace, numberOfExtents, dimensions);
  runTimeObjectDB.createRegion(federate, theSpace, numberOfExtents, theDimensions, region);
  return region;
}

// ---------------------------------------------------------------------------
// The caller has the region pointer and is responsible for deleteing the
// memory.
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagementLRC::deleteRegion(GeRtiFactory::GeRtiHandle const &theRegion)
{
  runTimeObjectDB.deleteRegion(theRegion);
  GeRtiAmb_var->deleteRegion(theRegion);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagementLRC::loadRegion(GeRtiFactory::GeRtiHandle const &theSpace, GeRtiFactory::GeRtiHandle const &theRegion, GeRtiFactory::Extents const &theExtents)
{
  CORBA::ULong i;
  CORBA::ULong len;
  CORBA::ULong zero = 0;
  GERTICO::HandleSet dimensions;
  const GeRtiFactory::Ranges *currRanges;

  // For IEEE 1516
  len = theExtents.length();
  if (len == 1)
  {
    currRanges = &theExtents[zero];
    len = currRanges->length();
    for (i = 0; i < len; i++)
    {
      dimensions.insert((*currRanges)[i].dimension);
    }
  }

  runTimeObjectDB.createRegion(federate, theSpace, theExtents.length(), dimensions, theRegion);
  runTimeObjectDB.modifyRegion(federate, theRegion, theExtents);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagementLRC::notifyAboutRegionModification(GeRtiFactory::GeRtiHandle const &theRegion, GeRtiFactory::Extents &theExtents)
{
  GeRtiAmb_var->modifyRegion(theRegion, theExtents);
  runTimeObjectDB.modifyRegion(federate, theRegion, theExtents);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagementLRC::requestClassAttributeValueUpdateWithRegions(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSetMap const &theAttRegMap, GeRtiFactory::UserSuppliedTag const &theTag)
{
  GeRtiFactory::AttributeRegionsSeq attributeRegionsSeq;

  GERTICO::Mapper::mapAttributeRegionsSeqFromHandleSetMap(attributeRegionsSeq, theAttRegMap);
  GeRtiAmb_var->requestAttributeValueUpdateWithRegions(theClass, attributeRegionsSeq, theTag);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagementLRC::subscribeInteractionClassWithRegion(GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet const &theRegions, const bool &active)
{
  CORBA::Boolean booleanActive = 0;
  GeRtiFactory::GertiDdmEvent gertiDdmEvent;
  GeRtiFactory::Handles regions;

  if (active)
  {
    booleanActive = 1;
  }

  // Subscribe interaction class.
  gertiDdmEvent.service = 5;
  gertiDdmEvent.sourceId = federate;
  gertiDdmEvent.theHandle = theInteraction;
  gertiDdmEvent.numOrBool = booleanActive;
  GERTICO::Mapper::mapHandleSet(gertiDdmEvent.theHandles, theRegions);
  eventMarket->addDdmEvent(gertiDdmEvent);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagementLRC::subscribeObjectClassAttributesWithRegions(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSetMap const &theAttRegMap, bool const &active)
{
  CORBA::Boolean boo = 0;
  CORBA::ULong len = theAttRegMap.size();
  GeRtiFactory::AttributeRegionsSeq attributeRegionsSeq;

  if (active)
  {
    boo = 1;
  }

  if (len)
  {
    // Subscribe to class.
    GERTICO::Mapper::mapAttributeRegionsSeqFromHandleSetMap(attributeRegionsSeq, theAttRegMap);
    GeRtiAmb_var->subscribeObjectClassAttributesWithRegions(theClass, attributeRegionsSeq, boo);
  }
#ifndef IEEE_1516
  else
  {
    // Unsubscribe from class.
    GeRtiAmb_var->unsubscribeObjectClassWithRegions(theClass, attributeRegionsSeq);
  }
#endif
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagementLRC::unassociateRegionForUpdates(GeRtiFactory::GeRtiHandle const &theRegion, GeRtiFactory::GeRtiHandle const &theObject)
{
  GeRtiAmb_var->unassociateRegionForUpdates(theRegion, theObject);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagementLRC::unassociateRegionsForUpdates(GeRtiFactory::GeRtiHandle const &theObject, GERTICO::HandleSetMap const &theAttRegMap)
{
  GeRtiFactory::AttributeRegionsSeq attributeRegionsSeq;

  GERTICO::Mapper::mapAttributeRegionsSeqFromHandleSetMap(attributeRegionsSeq, theAttRegMap);
  GeRtiAmb_var->unassociateRegionsForUpdates(theObject, attributeRegionsSeq);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagementLRC::unsubscribeInteractionClassWithRegions(GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet const &theRegions)
{
  CORBA::Boolean booleanActive = 0;
  GeRtiFactory::GertiDdmEvent gertiDdmEvent;
  GeRtiFactory::Handles regions;

  if (active)
  {
    booleanActive = 1;
  }

  // Unsubscribe interaction class.
  gertiDdmEvent.service = 6;
  gertiDdmEvent.sourceId = federate;
  gertiDdmEvent.theHandle = theInteraction;
  gertiDdmEvent.numOrBool = booleanActive;
  GERTICO::Mapper::mapHandleSet(gertiDdmEvent.theHandles, theRegions);
  eventMarket->addDdmEvent(gertiDdmEvent);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagementLRC::unsubscribeObjectClassWithRegion(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theRegion)
{
  GeRtiAmb_var->unsubscribeObjectClassWithRegion(theClass, theRegion);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagementLRC::unsubscribeObjectClassWithRegions(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSetMap const &theAttRegMap)
{
  GeRtiFactory::AttributeRegionsSeq attributeRegionsSeq;

  GERTICO::Mapper::mapAttributeRegionsSeqFromHandleSetMap(attributeRegionsSeq, theAttRegMap);
  GeRtiAmb_var->unsubscribeObjectClassWithRegions(theClass, attributeRegionsSeq);
}
