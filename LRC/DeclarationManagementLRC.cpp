/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** DeclarationManagementLRC.cpp
**
*******************************************************************************/

#include "DeclarationManagementLRC.h"
#include "Util/Mapper.h"
#include <iostream>

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
#ifdef IEEE_1516
GERTICO::DeclarationManagementLRC::DeclarationManagementLRC(GeRtiFactory::GeRtiAmbassador_var &theGeRtiAmbassador_var, GeRtiFactory::GeRtiHandle &theFederate, bool const &theJoined, GERTICO::RunTimeObjectDB &theRunTimeObjectDB, GERTICO::HandleSet &theInteractionHandleSet, GERTICO::EventHandler1516 &theEventHandler, GERTICO::SupportingServicesLRC &theSupportingServicesLRC) : eventHandler(theEventHandler), interactionHandleSet(theInteractionHandleSet), runTimeObjectDB(theRunTimeObjectDB), supportingServicesLRC(theSupportingServicesLRC), federate(theFederate), joined(theJoined)
#else
GERTICO::DeclarationManagementLRC::DeclarationManagementLRC(GeRtiFactory::GeRtiAmbassador_var &theGeRtiAmbassador_var, GeRtiFactory::GeRtiHandle &theFederate, bool const &theJoined, GERTICO::RunTimeObjectDB &theRunTimeObjectDB, GERTICO::HandleSet &theInteractionHandleSet, GERTICO::EventHandler &theEventHandler, GERTICO::SupportingServicesLRC &theSupportingServicesLRC) : eventHandler(theEventHandler), interactionHandleSet(theInteractionHandleSet), runTimeObjectDB(theRunTimeObjectDB), supportingServicesLRC(theSupportingServicesLRC), federate(theFederate), joined(theJoined)
#endif
{
  GeRtiAmb_var = GeRtiFactory::GeRtiAmbassador::_duplicate(theGeRtiAmbassador_var);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::DeclarationManagementLRC::~DeclarationManagementLRC(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementLRC::checkPublishing(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &theAttributes)
{
  runTimeObjectDB.checkPublishing(federate, theClass, theAttributes);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementLRC::getPublishedAttributes(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSet &theAttributeSet)
{
  runTimeObjectDB.getPublishedAttributes(federate, theClass, theAttributeSet);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::DeclarationManagementLRC::isPublishingInteraction(GeRtiFactory::GeRtiHandle const &theClass)
{
  GERTICO::HandleSet::iterator itPublishClass;

  itPublishClass = interactionHandleSet.find(theClass);
  if (itPublishClass == interactionHandleSet.end())
  {
    return false;
  }

  return true;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementLRC::mapIt(GERTICO::HandleSet &out, GeRtiFactory::Handles const &inAttributes)
{
  CORBA::ULong i;
  CORBA::ULong len;

  len = inAttributes.length();
  for (i = 0; i < len; i++)
  {
    out.insert(inAttributes[i]);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementLRC::publishInteractionClass(GeRtiFactory::GeRtiHandle &theInteraction)
{
  GERTICO::HandleSet::iterator itHS;
  GeRtiFactory::GertiDmEvent gertiDmEvent;

  // Publish interaction class.
  try
  {
    gertiDmEvent.service = 2;
    gertiDmEvent.sourceId = federate;
    gertiDmEvent.theHandle = theInteraction;
    supportingServicesLRC.getInteractionParents(theInteraction, gertiDmEvent.theHandles);
    eventMarket->addDmEvent(gertiDmEvent);
  }
  catch(...)
  {
    throw;
  }

  // Have a primitive management of published interations
  itHS = interactionHandleSet.find(theInteraction);
  if (itHS == interactionHandleSet.end())
  {
    interactionHandleSet.insert(theInteraction);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementLRC::publishObjectClass(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSet &attributeList)
{
  CORBA::ULong len;
  GeRtiFactory::GertiDmEvent gertiDmEvent;
  GeRtiFactory::Handles handles;
  size_t size;

  size = attributeList.size();
  GERTICO::Mapper::mapULongSizet(len, size);

  if (len)
  {
    GeRtiFactory::Handles attributeSet;

    GERTICO::Mapper::mapHandleSet(attributeSet, attributeList);
    // Automatically drops unused attributes from internal list.
    runTimeObjectDB.publishObjectClass(federate, theClass, attributeList);

    publishObjectClassReceiver(theClass, attributeList);

    // Publish object class.
    GeRtiAmb_var->publishObjectClass(theClass, attributeSet);
  }
  else
  {
    // zero length means unpublish all.
    runTimeObjectDB.publishObjectClass(federate, theClass, attributeList);

    unpublishObjectClassReceiver(theClass);

    // Unpublish object class.
    GeRtiAmb_var->unpublishObjectClass(theClass);
  }

  gertiDmEvent.service = 0;
  gertiDmEvent.sourceId = federate;
  gertiDmEvent.theHandle = theClass;
  GERTICO::Mapper::mapHandleSet(gertiDmEvent.theHandles, attributeList);
  supportingServicesLRC.getObjectClassParents(theClass, gertiDmEvent.theBaseClassHandles);
  eventMarket->addDmEvent(gertiDmEvent);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementLRC::publishObjectClassReceiver(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSet const & attributeList)
{
#ifdef IEEE_1516
  publishObjectClassSet[theClass] = attributeList;
#else
  publishObjectClassSet.insert(theClass);
#endif
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementLRC::remoteUnsubscribeInteractionClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementLRC::subscribeInteractionClass(GeRtiFactory::GeRtiHandle const &theInteraction, CORBA::Boolean const &theActive)
{
  GeRtiFactory::GertiDmEvent gertiDmEvent;

  // Subscribe interaction class.
  gertiDmEvent.service = 6;
  gertiDmEvent.sourceId = federate;
  gertiDmEvent.theHandle = theInteraction;
  gertiDmEvent.theActive = theActive;
  eventMarket->addDmEvent(gertiDmEvent);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementLRC::subscribeObjectClassAttributes(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSet &thePubAttributeSet, CORBA::Boolean const &theActive)
{
  CORBA::ULong i;
  CORBA::ULong len;
  GERTICO::AttributeDatumMap::iterator itAttributeDatumMap;
  GERTICO::HandleSet objects;
  GERTICO::HandleSet regions;
  GERTICO::HandleSet::iterator ito;
  GERTICO::HandleSetMap attRegMap;
  GeRtiFactory::GertiDmEvent gertiDmEvent;
  GeRtiFactory::Handles attributeHandles;
  size_t size;

  size = thePubAttributeSet.size();
  GERTICO::Mapper::mapULongSizet(len, size);
  GERTICO::Mapper::mapHandleSet(attributeHandles, thePubAttributeSet);

  // Distribute required data.
  if (len)
  {
    // Subscribe to class.
    gertiDmEvent.service = 4;
    gertiDmEvent.sourceId = federate;
    gertiDmEvent.theHandle = theClass;
    gertiDmEvent.theHandles = attributeHandles;
    gertiDmEvent.theActive = theActive;
    eventMarket->addDmEvent(gertiDmEvent);
    GeRtiAmb_var->subscribeObjectClassAttributes(theClass, attributeHandles, theActive);
  }
#ifndef IEEE_1516
  else
  {
    // Unsubscribe from class.
    try
    {
      unsubscribeObjectClass(theClass);
    }
    catch(GeRtiFactory::ObjectClassNotSubscribed)
    {
      // Do not throw exception.
    }
  }
#endif

  // Local information for incoming events.
  regions.insert(0);
  for (i = 0; i < len; i++)
  {
    attRegMap[attributeHandles[i]] = regions;
  }
  subscribeObjectClassAttributesReceiver(theClass, attRegMap);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementLRC::subscribeObjectClassAttributesReceiver(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSetMap &theAttRegMap)
{
  GERTICO::HandleSetMap handleSetMap;
  GERTICO::HandleSetMap::iterator itHandleSetMap;
  GERTICO::Mapper::mapHandleSetMapInvert(handleSetMap, theAttRegMap);

  for (itHandleSetMap = handleSetMap.begin(); itHandleSetMap != handleSetMap.end(); itHandleSetMap++)
  {
    eventHandler.subscribeObjectClassAttributes(theClass, itHandleSetMap->first, itHandleSetMap->second);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::DeclarationManagementLRC::testInteractionSubscribers(GeRtiFactory::GeRtiHandle const &theInteraction)
{
  GERTICO::HandleSet::iterator itInteraction;
  bool ret = false;

  itInteraction = interactionTurnedOnOSet.find(theInteraction);
  if (itInteraction != interactionTurnedOnOSet.end())
  {
    ret = true;
  }

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementLRC::turnInteractionsOff(GeRtiFactory::GeRtiHandle const &theInteraction)
{
  GERTICO::HandleSet::iterator itInteraction;

  itInteraction = interactionTurnedOnOSet.find(theInteraction);
  if (itInteraction != interactionTurnedOnOSet.end())
  {
    interactionTurnedOnOSet.erase(itInteraction);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementLRC::turnInteractionsOn(GeRtiFactory::GeRtiHandle const &theInteraction)
{
  GERTICO::HandleSet::iterator itInteraction;

  itInteraction = interactionTurnedOnOSet.find(theInteraction);
  if (itInteraction == interactionTurnedOnOSet.end())
  {
    interactionTurnedOnOSet.insert(theInteraction);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementLRC::unpublishInteractionClass(GeRtiFactory::GeRtiHandle &theInteraction)
{
  GERTICO::HandleSetMap::iterator itHandleSetMap;
  GERTICO::HandleSet::iterator itHS;
  GeRtiFactory::GertiDmEvent gertiDmEvent;

  // Have a primitive management of published interations
  itHS = interactionHandleSet.find(theInteraction);
  if (itHS != interactionHandleSet.end())
  {
    interactionHandleSet.erase(itHS);
  }

  // Unpublish interaction class.
  gertiDmEvent.service = 3;
  gertiDmEvent.sourceId = federate;
  gertiDmEvent.theHandle = theInteraction;
  eventMarket->addDmEvent(gertiDmEvent);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementLRC::unpublishObjectClass(GeRtiFactory::GeRtiHandle const &theClass)
{
  GeRtiFactory::GertiDmEvent gertiDmEvent;

  // Unpublish object class.
  gertiDmEvent.service = 1;
  gertiDmEvent.sourceId = federate;
  gertiDmEvent.theHandle = theClass;
  eventMarket->addDmEvent(gertiDmEvent);
  GeRtiAmb_var->unpublishObjectClass(theClass);

  runTimeObjectDB.unpublishObjectClass(federate, theClass);

  unpublishObjectClassReceiver(theClass);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementLRC::unpublishObjectClassReceiver(GeRtiFactory::GeRtiHandle const &theClass)
{
#ifdef IEEE_1516
  GERTICO::HandleSetMap::iterator itpublishObjectClassSet;

  itpublishObjectClassSet = publishObjectClassSet.find(theClass);
  if (itpublishObjectClassSet != publishObjectClassSet.end())
  {
    publishObjectClassSet.erase(itpublishObjectClassSet);
  }
#else
  GERTICO::HandleSet::iterator itPublishClass;

  itPublishClass = publishObjectClassSet.find(theClass);
  if (itPublishClass != publishObjectClassSet.end())
  {
    publishObjectClassSet.erase(itPublishClass);
  }
#endif
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementLRC::unpublishObjectClassAttributes(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &theAttributes)
{
  GeRtiFactory::GertiDmEvent gertiDmEvent;

  // Unpublish object class.
  GeRtiAmb_var->unpublishObjectClassAttributes(theClass, theAttributes);

  runTimeObjectDB.unpublishObjectClassAttributes(federate, theClass, theAttributes);

  unpublishObjectClassAttributesReceiver(theClass, theAttributes);

  gertiDmEvent.service = 8;
  gertiDmEvent.sourceId = federate;
  gertiDmEvent.theHandle = theClass;
  gertiDmEvent.theHandles = theAttributes;
  eventMarket->addDmEvent(gertiDmEvent);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementLRC::unpublishObjectClassAttributesReceiver(GeRtiFactory::GeRtiHandle  const & theClass, GeRtiFactory::Handles const &theAttributes)
{
#ifdef IEEE_1516
  CORBA::ULong i;
  CORBA::ULong len;
  GERTICO::HandleSet::iterator itAttribute;
  GERTICO::HandleSetMap::iterator itpublishObjectClassSet;

  itpublishObjectClassSet = publishObjectClassSet.find(theClass);
  if (itpublishObjectClassSet != publishObjectClassSet.end())
  {
    len = theAttributes.length();
    for (i = 0; i < len; i++)
    {
      itAttribute = itpublishObjectClassSet->second.find(theAttributes[i]);
      if (itAttribute != itpublishObjectClassSet->second.end())
      {
        itpublishObjectClassSet->second.erase(itAttribute);
      }
    }
    if (itpublishObjectClassSet->second.size() == 0)
    {
      publishObjectClassSet.erase(itpublishObjectClassSet);
    }
  }
#else
  // Dummy function for HLA 1.3
  throw GeRtiFactory::FederateInternalError(L"Not for HLA 1.3");
#endif
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementLRC::unsubscribeInteractionClass(GeRtiFactory::GeRtiHandle &theInteraction)
{
  GeRtiFactory::GertiDmEvent gertiDmEvent;

  // Subscribe interaction class.
  gertiDmEvent.service = 7;
  gertiDmEvent.sourceId = federate;
  gertiDmEvent.theHandle = theInteraction;
  eventMarket->addDmEvent(gertiDmEvent);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementLRC::unsubscribeObjectClass(GeRtiFactory::GeRtiHandle const &theClass)
{
  GeRtiFactory::GertiDmEvent gertiDmEvent;

  // Unsubscribe from class.
  GeRtiAmb_var->unsubscribeObjectClass(theClass);

  // Local information for incoming events.
#ifdef IEEE_1516
#else
  GeRtiFactory::GeRtiHandle region = 0;

  eventHandler.unsubscribeObjectClassWithRegion(theClass, region);
#endif

  // Subscribe interaction class.
  gertiDmEvent.service = 5;
  gertiDmEvent.sourceId = federate;
  gertiDmEvent.theHandle = theClass;
  eventMarket->addDmEvent(gertiDmEvent);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DeclarationManagementLRC::unsubscribeObjectClassAttributes(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &theAttributes)
{
  GeRtiFactory::GertiDmEvent gertiDmEvent;

  // Unsubscribe from class.
  GeRtiAmb_var->unsubscribeObjectClassAttributes(theClass, theAttributes);

  // Local information for incoming events.
#ifdef IEEE_1516
    eventHandler.unsubscribeObjectClassAttributes(theClass, theAttributes);
#else
  // Dummy function for HLA 1.3
  throw GeRtiFactory::FederateInternalError(L"Not for HLA 1.3");
#endif

  // Subscribe interaction class.
  gertiDmEvent.service = 9;
  gertiDmEvent.sourceId = federate;
  gertiDmEvent.theHandle = theClass;
  gertiDmEvent.theHandles = theAttributes;
  eventMarket->addDmEvent(gertiDmEvent);
}
