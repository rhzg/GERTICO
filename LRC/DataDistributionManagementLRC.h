/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: DataDistributionManagementLRC.h,v $
Revision 1.4  2007/09/06 06:29:27  mul
Changes for ieee1516.

Revision 1.3  2007/06/08 12:18:18  mul
Changes for ieee1516.

Revision 1.2  2007/05/15 13:32:36  mul
Changes for combined 1.3 and 1516 logic.

Revision 1.1  2006/10/23 14:51:21  mul
New management group.

 
**
*******************************************************************************/


#ifndef DataDistributionManagementLRC_H_
#define DataDistributionManagementLRC_H_

#include "idl/GeRtiFactoryS.h"
#include "LRC/EventMarket.h"
#include "Util/RunTimeObjectDB.h"

namespace GERTICO
{
  class DataDistributionManagementLRC
  {
    GERTICO::RunTimeObjectDB &runTimeObjectDB;
    GeRtiFactory::GeRtiAmbassador_var GeRtiAmb_var;
    GeRtiFactory::GeRtiHandle &federate;

  public:
    GERTICO::EventMarket *eventMarket;
    DataDistributionManagementLRC(GeRtiFactory::GeRtiAmbassador_var &theGeRtiAmbassador_var,  GeRtiFactory::GeRtiHandle &theFederate, GERTICO::RunTimeObjectDB &theRunTimeObjectDB);
    virtual ~DataDistributionManagementLRC(void);

	  void associateRegionsForUpdates(GeRtiFactory::GeRtiHandle const &theObject, GERTICO::HandleSetMap const &theAttRegMap);
    GeRtiFactory::GeRtiHandle createRegion(GeRtiFactory::GeRtiHandle const &theSpace, CORBA::ULong const &numberOfExtents, GERTICO::HandleSet const &theDimensions);
    void deleteRegion(GeRtiFactory::GeRtiHandle const &theRegion);
    void loadRegion(GeRtiFactory::GeRtiHandle const &theSpace, GeRtiFactory::GeRtiHandle const &theRegion, GeRtiFactory::Extents const &theExtents);
    void notifyAboutRegionModification(GeRtiFactory::GeRtiHandle const &theRegion, GeRtiFactory::Extents &theExtents);
	  void requestClassAttributeValueUpdateWithRegions(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSetMap const &theAttRegMap, GeRtiFactory::UserSuppliedTag const &theTag);
	  void subscribeInteractionClassWithRegion(GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet const &theRegions, bool const &active);
	  void subscribeObjectClassAttributesWithRegions(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSetMap const &theAttRegMap, bool const &active);
    void unassociateRegionForUpdates(GeRtiFactory::GeRtiHandle const &theRegion, GeRtiFactory::GeRtiHandle const &theObject);
	  void unassociateRegionsForUpdates(GeRtiFactory::GeRtiHandle const &theObject, GERTICO::HandleSetMap const &theAttRegMap);
	  void unsubscribeInteractionClassWithRegions(GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet const &theRegions);
	  void unsubscribeObjectClassWithRegion(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theRegion);
	  void unsubscribeObjectClassWithRegions(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSetMap const &theAttRegMap);
  };
};

#endif /* DataDistributionManagementLRC_H_  */
