/******************************************************************************r
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: Fed.cpp,v $
Revision 1.8  2007/09/25 08:05:30  mul
Changes for ddm.

Revision 1.7  2007/09/05 15:01:14  mul
Changes for ieee1516.

Revision 1.6  2007/03/21 13:44:53  mul
Remove unused variable.

Revision 1.5  2007/03/12 12:57:18  mul
Changed string to wstring.

Revision 1.4  2005/11/17 13:09:08  mul
Fix memory leaks.

Revision 1.3  2005/05/24 07:03:52  mul
Add transport and ordering to fix timestamp problems.

Revision 1.2  2004/08/19 09:41:28  mul
Changes for save/restore logic.

Revision 1.1  2004/05/28 11:55:11  mul
Add new files.

 
**
*******************************************************************************/

#include <iostream>

#include "Fed.h"
#include "Util/Mapper.h"
#include "Util/NextHandle.h"

/*******************************************************************************
**
**
********************************************************************************/
GERTICO::ObjectModelImpl::ObjectModelImpl(FedPrivateData &fpd, GERTICO::NextHandle &theIdHandler)
{
  GERTICO::Attribute *newAttribute;
  GERTICO::FedDimension *newFedDimension;
  GERTICO::FedSpace *newSpace;
  GERTICO::HandleSet dummyDimensions;
  GERTICO::Parameter *newParameter;
  multitree<unsigned long>::node_iterator ni;
  std::map <unsigned long, AttributeInfo>::iterator itAttInfo;
  std::map <unsigned long, InteractionClassInfo>::iterator itInteractionClasses;
  std::map <unsigned long, ObjectClassInfo>::iterator itObjectClasses;
  std::map <unsigned long, ParameterInfo>::iterator itParInfo;
  std::wstring ws;
  std::vector<unsigned long>::iterator itUL;
  std::vector<SpaceInfo>::iterator itSp;
  std::vector<std::string>::iterator itDi;
  unsigned long sharingValue = 2;

  // Fill in federation information.
  name = fpd.FederationName;
  version = fpd.FEDVersion;
  DTDversion = fpd.DTDversion;

  for (itSp = fpd.Spaces.begin();
       itSp != fpd.Spaces.end();
       itSp++)
  {
    newSpace = new GERTICO::FedSpace(itSp->Name, theIdHandler);
    allFedSpaces[newSpace->getId()] = newSpace;
    for (itDi = itSp->DimensionNames.begin();
         itDi != itSp->DimensionNames.end();
         itDi++)
    {
      GERTICO::Mapper::mapWstringFromChar(ws, (*itDi).c_str());
      newFedDimension = new GERTICO::FedDimension(ws, theIdHandler);
      newSpace->dimensions[newFedDimension->getId()] = newFedDimension;
    }
  }

  // Fill in class information.
  for (ni = fpd.ObjectClassTree.begin();
       ni != fpd.ObjectClassTree.end();
       ni++)
  {
    itObjectClasses = fpd.ObjectClasses.find(ni.current->data_);
    if (itObjectClasses != fpd.ObjectClasses.end())
    {
      // Expect only one root element.
      rootClass = new ObjectClass(itObjectClasses->second.Name, sharingValue, theIdHandler);

      // Add any attributes.
      for (itUL = itObjectClasses->second.attributes.begin();
           itUL != itObjectClasses->second.attributes.end();
           itUL++)
      {
        itAttInfo = fpd.Attributes.find(*itUL);
        if (itAttInfo != fpd.Attributes.end())
        {
          newAttribute = new Attribute(itAttInfo->second.Name, itAttInfo->second.Space, itAttInfo->second.Ordering, itAttInfo->second.Transport, dummyDimensions, theIdHandler);
          rootClass->attributes[newAttribute->getId()] = newAttribute;
        }
      }

      // Process sub-classes.
      if (ni.current->first_)
      {
        processObjects(rootClass, ni, fpd.ObjectClasses, fpd.Attributes, theIdHandler);
      }
    }
  }

  // Fill in interaction information.
  for (ni = fpd.InteractionClassTree.begin();
       ni != fpd.InteractionClassTree.end();
       ni++)
  {
    itInteractionClasses = fpd.InteractionClasses.find(ni.current->data_);
    if (itInteractionClasses != fpd.InteractionClasses.end())
    {
      // Expect only one root element.
      rootInteraction = new InteractionClass(itInteractionClasses->second.Name, itInteractionClasses->second.Space, itInteractionClasses->second.Ordering, itInteractionClasses->second.Transport, sharingValue, dummyDimensions, theIdHandler);

      // Add any parameters.
      for (itUL = itInteractionClasses->second.parameters.begin();
           itUL != itInteractionClasses->second.parameters.end();
           itUL++)
      {
        itParInfo = fpd.Parameters.find(*itUL);
        if (itParInfo != fpd.Parameters.end())
        {
          newParameter = new Parameter(itParInfo->second.Name, theIdHandler);
          rootInteraction->parameters[newParameter->getId()] = newParameter;
        }
      }

      // Process sub-classes.
      if (ni.current->first_)
      {
        processInteractions(rootInteraction, ni, fpd.InteractionClasses, fpd.Parameters, theIdHandler);
      }
    }
  }

  // build up parent relationship table
  addParentRelation(rootClass);
  addParentRelation(rootInteraction);
}

/*******************************************************************************
**
**
*******************************************************************************/
GERTICO::ObjectModelImpl::~ObjectModelImpl(void)
{
  FedSpace *currFedSpace;
  FedSpaceMap::iterator itAFC;
  GERTICO::InteractionClass *currInteractionClass;
  GERTICO::ObjectClass *currObjectClass;
  std::map<unsigned long, GERTICO::InteractionClass*>::iterator itAI;
  std::map<unsigned long, GERTICO::ObjectClass*>::iterator itAC;
  unsigned long ul;

  for (itAI = allInteractions.begin(); itAI != allInteractions.end(); itAI = allInteractions.begin())
  {
    ul = itAI->first;
    currInteractionClass = itAI->second;
    allInteractions.erase(itAI);
    delete currInteractionClass;
  }

  for (itAC = allClasses.begin(); itAC != allClasses.end(); itAC = allClasses.begin())
  {
    currObjectClass = itAC->second;
    allClasses.erase(itAC);
    delete currObjectClass;
  }

  for (itAFC = allFedSpaces.begin(); itAFC != allFedSpaces.end(); itAFC = allFedSpaces.begin())
  {
    currFedSpace = itAFC->second;
    allFedSpaces.erase(itAFC);
    delete currFedSpace;
  }
}

/*******************************************************************************
**
**
*******************************************************************************/
void GERTICO::ObjectModelImpl::processObjects(ObjectClass *oc, multitree<unsigned long>::node_iterator &ni, std::map<unsigned long, ObjectClassInfo> &oci, std::map<unsigned long, AttributeInfo> &ai, GERTICO::NextHandle &theIdHandler)
{
  GERTICO::Attribute *newAttribute;
  GERTICO::HandleSet dummyDimensions;
  ObjectClass *newObjectClass;
  multitree<unsigned long>::node_iterator it(ni.current->first_);
  std::map <unsigned long, AttributeInfo>::iterator itAttInfo;
  std::map <unsigned long, ObjectClassInfo>::iterator itObjectClasses;
  std::vector<unsigned long>::iterator itUL;
  unsigned long sharingValue = 2;

  // Fill in class information.
  for (; it.current != NULL; it++)
  {
    itObjectClasses = oci.find(it.current->data_);
    if (itObjectClasses != oci.end())
    {
      // Create an object class.
      newObjectClass = new ObjectClass(itObjectClasses->second.Name, sharingValue, theIdHandler);
      oc->childClasses[newObjectClass->getId()] = newObjectClass;

      // Add attributes.
      for (itUL = itObjectClasses->second.attributes.begin();
           itUL != itObjectClasses->second.attributes.end();
           itUL++)
      {
        itAttInfo = ai.find(*itUL);
        if (itAttInfo != ai.end())
        {
          newAttribute = new Attribute(itAttInfo->second.Name, itAttInfo->second.Space, itAttInfo->second.Ordering, itAttInfo->second.Transport, dummyDimensions, theIdHandler);
          newObjectClass->attributes[newAttribute->getId()] = newAttribute;
        }
      }

      // Process sub-classes.
      if (it.current->first_)
      {
        processObjects(newObjectClass, it, oci, ai, theIdHandler);
      }
    }
  }
}

/*******************************************************************************
**
**
*******************************************************************************/
void GERTICO::ObjectModelImpl::processInteractions(InteractionClass *ic, multitree<unsigned long>::node_iterator &ni, std::map<unsigned long, InteractionClassInfo> &ici, std::map<unsigned long, ParameterInfo> & pi, GERTICO::NextHandle &theIdHandler)
{
  GERTICO::Parameter *newParameter;
  GERTICO::HandleSet dummyDimensions;
  InteractionClass *newInteractionClass;
  multitree<unsigned long>::node_iterator it(ni.current->first_);
  std::map <unsigned long, ParameterInfo>::iterator itParInfo;
  std::map <unsigned long, InteractionClassInfo>::iterator itInteractionClasses;
  std::vector<unsigned long>::iterator itUL;
  unsigned long sharingValue = 2;

  // Fill in class information.
  for (; it.current != NULL; it++)
  {
    itInteractionClasses = ici.find(it.current->data_);
    if (itInteractionClasses != ici.end())
    {
      // Create an interaction class.
      newInteractionClass = new InteractionClass(itInteractionClasses->second.Name, itInteractionClasses->second.Space, itInteractionClasses->second.Ordering, itInteractionClasses->second.Transport, sharingValue, dummyDimensions, theIdHandler);
      ic->childInteractions[newInteractionClass->getId()] = newInteractionClass;

      // Add parameters.
      for (itUL = itInteractionClasses->second.parameters.begin();
           itUL != itInteractionClasses->second.parameters.end();
           itUL++)
      {
        itParInfo = pi.find(*itUL);
        if (itParInfo != pi.end())
        {
          newParameter = new Parameter(itParInfo->second.Name, theIdHandler);
          newInteractionClass->parameters[newParameter->getId()] = newParameter;
        }
      }

      // Process sub-classes.
      if (it.current->first_)
      {
        processInteractions(newInteractionClass, it, ici, pi, theIdHandler);
      }
    }
  }
}

/*******************************************************************************
**
**
*******************************************************************************/
void GERTICO::ObjectModelImpl::addParentRelation(GERTICO::ObjectClass* oC)
{
  allClasses[oC->getId()] = oC;
  std::map <unsigned long, GERTICO::ObjectClass*>::iterator iChild;
  for (iChild = oC->childClasses.begin();
       iChild != oC->childClasses.end();
       iChild++)
  {
    parentRelations[iChild->second->getId()] = oC->getId();
    addParentRelation(iChild->second);
  }
}


/*******************************************************************************
**
**
*******************************************************************************/
void GERTICO::ObjectModelImpl::addParentRelation(GERTICO::InteractionClass* iC)
{
  allInteractions[iC->getId()] = iC;
  std::map <unsigned long, GERTICO::InteractionClass*>::iterator iChild;
  for (iChild = iC->childInteractions.begin();
       iChild != iC->childInteractions.end();
       iChild++)
  {
    parentRelations[iChild->second->getId()] = iC->getId();
    addParentRelation(iChild->second);
  }
}
