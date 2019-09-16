/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: DataModel.cpp,v $
Revision 1.8  2010/06/28 13:20:06  mul
Initialze null pointers.

Revision 1.7  2009/06/12 12:12:55  mul
Use thread mutex.

Revision 1.6  2007/09/25 08:05:29  mul
Changes for ddm.

Revision 1.5  2007/09/05 14:59:33  mul
Changes for ieee1516.

Revision 1.4  2007/03/12 12:58:27  mul
Changed string to wstring.

Revision 1.3  2006/10/18 11:31:07  mul
Minor changes to fix create federation execution problems.

Revision 1.2  2005/11/17 10:11:43  mul
Fix memory leaks.

Revision 1.1  2004/05/28 11:55:10  mul
Add new files.


**
*******************************************************************************/


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------

#include <iostream>
#include "DataModel.h"
#include "ClassInfo.h"
#include "FedParser.h"
#ifdef IEEE_1516
#include "OMT.h"
#else
#include "Fed.h"
#endif
#include "Util/Mapper.h"

ACE_Thread_Mutex GERTICO::ObjectModel::pm;

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
#ifdef IEEE_1516
GERTICO::FedDimension::FedDimension(std::wstring const &theName, std::wstring const &theDataType, unsigned long const &theUpperBound, GERTICO::NextHandle &theIdHandler)
#else
GERTICO::FedDimension::FedDimension(std::wstring const &theName, GERTICO::NextHandle &theIdHandler)
#endif
{
  name = theName;
  id = theIdHandler.nextHandle ();
#ifdef IEEE_1516
  dataType = theDataType;
  upperBound = theUpperBound;
#endif
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FedDimension::~FedDimension (void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring GERTICO::FedDimension::getName (void)
{
  return name;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
unsigned long GERTICO::FedDimension::getId (void)
{
  return id;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FedSpace::FedSpace (std::wstring const &theName, GERTICO::NextHandle &theIdHandler)
{
  name = theName;
  id = theIdHandler.nextHandle ();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FedSpace::~FedSpace (void)
{
  FedDimension *currFedDimension;
  FedDimensionMap::iterator itD;

  for (itD = dimensions.begin(); itD != dimensions.end(); itD = dimensions.begin())
  {
    currFedDimension = itD->second;
    dimensions.erase(itD);
    delete currFedDimension;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring GERTICO::FedSpace::getName (void)
{
  return name;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
unsigned long GERTICO::FedSpace::getId (void)
{
  return id;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Attribute::Attribute(std::wstring const &theName, std::wstring const &theSpace, unsigned long &theOrdering, unsigned long &theTransportation, GERTICO::HandleSet const &theDimensions, GERTICO::NextHandle &theIdHandler)
{
  id = theIdHandler.nextHandle();
  name = theName;
  space = theSpace;
  ordering = theOrdering;
  transportation = theTransportation;
  dimensions = theDimensions;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Attribute::~Attribute(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Attribute::getDimensions(GERTICO::HandleSet &theDimensions)
{
  theDimensions = dimensions;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Attribute::print(void)
{
  std::wcout << L"Attribute Name: " << name << L" (" << id << L")" << std::endl;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Parameter::Parameter(std::wstring const &theName, GERTICO::NextHandle &theIdHandler)
{
  name = theName;
  id = theIdHandler.nextHandle();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Parameter::~Parameter(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Parameter::getDimensions(GERTICO::HandleSet &theDimensions)
{
  theDimensions = dimensions;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Parameter::print(void)
{
  std::wcout << L"Parameter Name: " << name << L" (" << id << L")" << std::endl;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjectClass::ObjectClass(std::wstring const &theName, unsigned long const &theSharing, GERTICO::NextHandle &theIdHandler)
{
  name = theName;
  id = theIdHandler.nextHandle();
  sharing = theSharing;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjectClass::~ObjectClass(void)
{
  Attribute *currAttribute;
  ObjectClass *currObjectClass;
  std::map <unsigned long, Attribute*>::iterator itA;
  std::map <unsigned long, ObjectClass*>::iterator itCC;

  for (itA = attributes.begin(); itA != attributes.end(); itA = attributes.begin())
  {
    currAttribute = itA->second;
    attributes.erase(itA);
    delete currAttribute;
  }

  for (itCC = childClasses.begin(); itCC != childClasses.end(); itCC = childClasses.begin())
  {
    currObjectClass = itCC->second;
    childClasses.erase(itCC);
    // Not here
//    delete currObjectClass;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectClass::print(void)
{
  std::wcout << L"[ Class Name: " << name << L" (" << id << L")" << std::endl;

  std::cout << "[ Attributes" << std::endl;
  std::map <unsigned long, GERTICO::Attribute*> ::iterator iAttribute;
  iAttribute = attributes.begin();
  while (iAttribute != attributes.end())
  {
    iAttribute->second->print();
    iAttribute++;
  }
  std::cout << "Attributes ]" << std::endl;

  std::cout << "[ Childs" << std::endl;
  std::map <unsigned long, GERTICO::ObjectClass*> ::iterator iClass;
  iClass = childClasses.begin();
  while (iClass != childClasses.end())
  {
    iClass->second->print();
    iClass++;
  }
  std::cout << "Attributes ]" << std::endl;

  std::cout << "Class ]" << std::endl;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::InteractionClass::InteractionClass(std::wstring const &theName, std::wstring const &theSpace, unsigned long &theOrdering, unsigned long &theTransport, unsigned long const &theSharing, GERTICO::HandleSet const &theDimensions, GERTICO::NextHandle &theIdHandler)
{
  id = theIdHandler.nextHandle();
  name = theName;
  space = theSpace;
  ordering = theOrdering;
  transportation = theTransport;
  sharing = theSharing;
  dimensions = theDimensions;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::InteractionClass::~InteractionClass(void)
{
  InteractionClass *currInteractionClass;
  Parameter *currParameter;
  std::map <unsigned long, InteractionClass*>::iterator itCI;
  std::map <unsigned long, Parameter*>::iterator itP;

  for (itCI = childInteractions.begin(); itCI != childInteractions.end(); itCI = childInteractions.begin())
  {
    currInteractionClass = itCI->second;
    childInteractions.erase(itCI);
    // Not here
//    delete currInteractionClass;
  }

  for (itP = parameters.begin(); itP != parameters.end(); itP = parameters.begin())
  {
    currParameter = itP->second;
    parameters.erase(itP);
    delete currParameter;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionClass::getDimensions(GERTICO::HandleSet &theDimensions)
{
  theDimensions = dimensions;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::InteractionClass::print(void)
{
  std::wcout << L"[ Interaction Name: " << name << L" (" << id << L")" << std::endl;

  std::cout << "[ Parameter" << std::endl;
  std::map <unsigned long, GERTICO::Parameter*> ::iterator iParameter;
  iParameter = parameters.begin();
  while (iParameter != parameters.end())
  {
    iParameter->second->print();
    iParameter++;
  }
  std::cout << "Parameter ]" << std::endl;

  std::cout << "[ Childs" << std::endl;
  std::map <unsigned long, GERTICO::InteractionClass*> ::iterator iClass;
  iClass = childInteractions.begin();
  while (iClass != childInteractions.end())
  {
    iClass->second->print();
    iClass++;
  }
  std::cout << "Childs ]" << std::endl;

  std::cout << "Interaction ]" << std::endl;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjectModel::ObjectModel(void)
{
  rootClass = NULL;
  rootInteraction = NULL;
#ifndef IEEE_1516
  allFedSpaces.clear();
#endif
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjectModel::~ObjectModel(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::OMT_TYPE GERTICO::ObjectModel::getType(void)
{
  return GERTICO::FOM;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectModel::print(void)
{
  if (rootClass != 0) rootClass->print();
  else std::cout << "empty Class Tree" << std::endl;
  if (rootInteraction != 0) rootInteraction->print();
  else std::cout << "empty Interaction Tree" << std::endl;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectModel::getChildrenIds(unsigned long classId, std::vector<unsigned long> &children)
{
  std::map<unsigned long, GERTICO::ObjectClass*>::iterator iC;
  iC = allClasses.find(classId);
  if (iC == allClasses.end()) return;
  GERTICO::ObjectClass* theClass = iC->second;

  std::map <unsigned long, GERTICO::ObjectClass*>::iterator iChildren;
  for (iChildren = theClass->childClasses.begin();
       iChildren != theClass->childClasses.end();
       iChildren++)
  {
    children.push_back(iChildren->second->getId());
    getChildrenIds(iChildren->second->getId(), children);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::ObjectModel::getParentId(unsigned long classId, unsigned long &parent)
{
  std::map<unsigned long, unsigned long>::iterator iP;
  iP = parentRelations.find(classId);
  if (iP != parentRelations.end())
  {
    parent = iP->second;
    return true;
  }
  else
  {
    return false;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
unsigned long GERTICO::ObjectModel::getAttributeId(unsigned long classId, std::wstring const &attributeName)
  throw(GERTICO::ObjectClassNotDefined, GERTICO::AttributeNotDefined)
{
   std::map<unsigned long, GERTICO::ObjectClass*>::iterator iC;
   iC = allClasses.find(classId);
   if (iC == allClasses.end())
     throw GERTICO::ObjectClassNotDefined();
   std::map <unsigned long, GERTICO::Attribute*>::iterator iA;
   for (iA = iC->second->attributes.begin();
        iA != iC->second->attributes.end();
  iA++)
   {
     if (attributeName == iA->second->getName())
     {
       return iA->second->getId();
     }
   }
   std::map<unsigned long, unsigned long>::iterator iP;
   iP = parentRelations.find(iC->second->getId());
   if (iP != parentRelations.end())
   {
     return getAttributeId(iP->second, attributeName);
   }

   throw GERTICO::AttributeNotDefined();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjectModel *GERTICO::ObjectModelFactory::createObjectModel(std::wstring const &fileName, GERTICO::NextHandle &theIdHandler)
{
  std::string error;
  std::string myFile;
//  unsigned int pos;

  GERTICO::Mapper::mapStringFromWstring(myFile, fileName);
  GERTICO::ObjectModel::pm.acquire ();
#ifdef IEEE_1516
//  pos = myFile.rfind(".xml");
//  if (pos != std::string::npos)
//  {
    OMT *omt;
    try
    {
      omt = OMT::parseFromFile(myFile, theIdHandler);
    }
    catch(...)
    {
      GERTICO::ObjectModel::pm.release ();
      throw;
    }
    GERTICO::ObjectModel::pm.release ();
    return omt->objectModel;
//  }
#else
    GERTICO::ObjectModel *objectModel = NULL;
    FedPrivateData apd;
    FedParser fedParser;
    std::wstring errorMsg;
    std::string best_effort ("best_effort");
    std::string receive ("receive");
    std::string reliable ("reliable");
    std::string timestamp ("timestamp");
    int retCode;

    apd.TransportMap [reliable] = 0;
    apd.TransportMap [best_effort] = 1;
    apd.OrderingMap [receive] = 0;
    apd.OrderingMap [timestamp] = 1;

    retCode = fedParser.ReadFedFile (myFile, apd, errorMsg);
    if (retCode == 1)
    {
      GERTICO::ObjectModel::pm.release ();
      GERTICO::Mapper::mapStringFromWstring(error, errorMsg);
      throw GERTICO::ErrorReadingFED(error.c_str());
    }
    if (retCode == 2)
    {
      GERTICO::ObjectModel::pm.release ();
      throw GERTICO::CouldNotOpenFED ();
    }
    objectModel = new GERTICO::ObjectModelImpl(apd, theIdHandler);
    GERTICO::ObjectModel::pm.release ();
    return objectModel;
#endif
}
