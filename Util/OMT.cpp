/******************************************************************************r
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: OMT.cpp,v $
Revision 1.9  2010/06/28 13:17:04  mul
Check for null pointers.

Revision 1.8  2007/11/14 15:19:28  mul
Changes for vc8.

Revision 1.7  2007/11/13 10:21:41  mul
Changes for vc8.

Revision 1.6  2007/09/25 08:03:36  mul
Changes for ddm.

Revision 1.5  2007/09/05 15:12:26  mul
Changes for ieee1516.

Revision 1.4  2007/03/12 12:49:05  mul
Changed string to wstring.

Revision 1.3  2005/11/17 10:14:16  mul
Add destructors.

Revision 1.2  2005/02/11 14:46:34  mul
Add scoping.

Revision 1.1  2004/05/28 11:55:11  mul
Add new files.

 
**
*******************************************************************************/

#include <iostream>

#include "OMT.h"
#include "Util/Mapper.h"
#include "Util/NextHandle.h"

// ---------------------------------------------------------------------------
// static Variables of class OMT
// ---------------------------------------------------------------------------
XMLCh* GERTICO::OMT::nameString;
XMLCh* GERTICO::OMT::classNodeNameString;
XMLCh* GERTICO::OMT::interactionNodeNameString;

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjectClassI::ObjectClassI(DOMElement* element, std::wstring const &theName, unsigned long const &theSharing, GERTICO::WstringHandleMap &theDimensionNameId, GERTICO::NextHandle &theIdHandler) : ObjectClass(theName, theSharing, theIdHandler)
{
  GERTICO::HandleSet dimensions;
  XMLCh *attributeXMLCh = XMLString::transcode("attribute");
  XMLCh *dimensionsXMLCh = XMLString::transcode("dimensions");
  XMLCh *orderXMLCh = XMLString::transcode("order");
  XMLCh *sharingXMLCh = XMLString::transcode("sharing");
  XMLCh *transportationXMLCh = XMLString::transcode("transportation");
  char *tmpChar;
  unsigned long ordering;
  unsigned long sharingValue;
  unsigned long transportation;
  std::wstring attributeName;
  std::wstring objectName;
  std::wstring space;

  DOMNode *child;
  for (child = element->getFirstChild(); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      //OMT::printNode (child);
      if (XMLString::compareString(child->getNodeName(), OMT::classNodeNameString) == 0)
      {
        tmpChar = XMLString::transcode (((DOMElement*)child)->getAttribute (OMT::nameString));
        GERTICO::Mapper::mapWstringFromChar(objectName, tmpChar);
        tmpChar = XMLString::transcode (((DOMElement*)child)->getAttribute(sharingXMLCh));
        if (strcmp(tmpChar, "Publish") == 0)
        {
          sharingValue = 0;
        }
        else if (strcmp(tmpChar, "Subscribe") == 0)
        {
          sharingValue = 1;
        }
        else if (strcmp(tmpChar, "PublishSubscribe") == 0)
        {
          sharingValue = 2;
        }
        else
        {
          sharingValue = 3;
        }
        ObjectClass* childClass = new ObjectClassI((DOMElement*) child, objectName, sharingValue, theDimensionNameId, theIdHandler);
        childClasses[childClass->getId()] = childClass;
      }
      else if (XMLString::compareString(child->getNodeName(), attributeXMLCh) == 0)
      {
        tmpChar = XMLString::transcode (((DOMElement*)child)->getAttribute (OMT::nameString));
        GERTICO::Mapper::mapWstringFromChar(attributeName, tmpChar);
        tmpChar = XMLString::transcode (((DOMElement*)child)->getAttribute(dimensionsXMLCh));
        ObjectModelI::processDimensions(tmpChar, dimensions, theDimensionNameId);
        tmpChar = XMLString::transcode (((DOMElement*)child)->getAttribute(orderXMLCh));
        if (strcmp(tmpChar, "Receive") == 0)
        {
          ordering = 0;
        }
        else if (strcmp(tmpChar, "TimeStamp") == 0)
        {
          ordering = 1;
        }
        else
        {
          // NOT CORRECT?
          ordering = 0;
        }
        tmpChar = XMLString::transcode (((DOMElement*)child)->getAttribute(transportationXMLCh));
        if (strcmp(tmpChar, "HLAreliable") == 0)
        {
          transportation = 0;
        }
        else if (strcmp(tmpChar, "HLAbestEffort") == 0)
        {
          transportation = 1;
        }
        else
        {
          // NOT CORRECT?
          transportation = 0;
        }
        Attribute* a = new Attribute (attributeName, space, ordering, transportation, dimensions, theIdHandler);
        attributes [a->getId()] = a;
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjectClassI::~ObjectClassI(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::InteractionClassI::InteractionClassI(DOMElement* element, std::wstring const &theName, std::wstring const &theSpace, unsigned long &theOrdering, unsigned long &theTransport, unsigned long const &theSharing, GERTICO::HandleSet const &theDimensions, GERTICO::WstringHandleMap &theDimensionNameId, GERTICO::NextHandle &theIdHandler) : InteractionClass(theName, theSpace, theOrdering, theTransport, theSharing, theDimensions, theIdHandler)
{
  GERTICO::HandleSet tmpDimensions;
  XMLCh *dimensionsXMLCh = XMLString::transcode("dimensions");
  XMLCh *orderXMLCh = XMLString::transcode("order");
  XMLCh *parameterXMLCh = XMLString::transcode("parameter");
  XMLCh *sharingXMLCh = XMLString::transcode("sharing");
  XMLCh *transportationXMLCh = XMLString::transcode("transportation");
  char *tmpChar;
  unsigned long order;
  unsigned long sharingValue;
  unsigned long trans;
  std::wstring interactionName;
  std::wstring parameterName;
  std::wstring spa;

  DOMNode* child;
  for (child = element->getFirstChild(); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      //OMT::printNode (child);
      if (XMLString::compareString(child->getNodeName(), OMT::interactionNodeNameString) ==0)
      {
        tmpChar = XMLString::transcode (((DOMElement*)child)->getAttribute (OMT::nameString));
        GERTICO::Mapper::mapWstringFromChar(interactionName, tmpChar);
        tmpChar = XMLString::transcode (((DOMElement*)child)->getAttribute(sharingXMLCh));
        if (strcmp(tmpChar, "Publish") == 0)
        {
          sharingValue = 0;
        }
        else if (strcmp(tmpChar, "Subscribe") == 0)
        {
          sharingValue = 1;
        }
        else if (strcmp(tmpChar, "PublishSubscribe") == 0)
        {
          sharingValue = 2;
        }
        else
        {
          sharingValue = 3;
        }
        tmpChar = XMLString::transcode (((DOMElement*)child)->getAttribute(dimensionsXMLCh));
        ObjectModelI::processDimensions(tmpChar, tmpDimensions, theDimensionNameId);
        tmpChar = XMLString::transcode (((DOMElement*)child)->getAttribute(transportationXMLCh));
        if (strcmp(tmpChar, "HLAreliable") == 0)
        {
          trans = 0;
        }
        else if (strcmp(tmpChar, "HLAbestEffort") == 0)
        {
          trans = 1;
        }
        else
        {
          // NOT CORRECT?
          trans = 0;
        }
        tmpChar = XMLString::transcode (((DOMElement*)child)->getAttribute(orderXMLCh));
        if (strcmp(tmpChar, "Receive") == 0)
        {
          order = 0;
        }
        else if (strcmp(tmpChar, "TimeStamp") == 0)
        {
          order = 1;
        }
        else
        {
          // NOT CORRECT?
          order = 0;
        }
        InteractionClass* childClass = new InteractionClassI((DOMElement*) child, interactionName, spa, order, trans, sharingValue, tmpDimensions, theDimensionNameId, theIdHandler);
        childInteractions [childClass->getId()] = childClass;
      }
      else if (XMLString::compareString(child->getNodeName(), parameterXMLCh) == 0)
      {
        tmpChar = XMLString::transcode (((DOMElement*)child)->getAttribute (OMT::nameString));
        GERTICO::Mapper::mapWstringFromChar(parameterName, tmpChar);
        Parameter* p = new Parameter (parameterName, theIdHandler);
        parameters [p->getId()] = p;
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::InteractionClassI::~InteractionClassI(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjectModelI::ObjectModelI(DOMElement* element, GERTICO::NextHandle &theIdHandler)
{
  GERTICO::FedDimension *fedDimension;
  XMLCh *DTDversionXMLCh = XMLString::transcode("DTDversion");
  XMLCh *dataTypeXMLCh = XMLString::transcode("dataType");
  XMLCh *dataTypesXMLCh = XMLString::transcode("dataTypes");
  XMLCh *dimensionXMLCh = XMLString::transcode("dimension");
  XMLCh *dimensionsXMLCh = XMLString::transcode("dimensions");
  XMLCh *interactionClassXMLCh = XMLString::transcode("interactionClass");
  XMLCh *interactionsXMLCh = XMLString::transcode("interactions");
  XMLCh *nameXMLCh = XMLString::transcode("name");
  XMLCh *objectClassXMLCh = XMLString::transcode("objectClass");
  XMLCh *objectsXMLCh = XMLString::transcode("objects");
  XMLCh *orderXMLCh = XMLString::transcode("order");
  XMLCh *sharingXMLCh = XMLString::transcode("sharing");
  XMLCh *switchesXMLCh = XMLString::transcode("switches");
  XMLCh *synchronizationsXMLCh = XMLString::transcode("synchronizations");
  XMLCh *timeXMLCh = XMLString::transcode("time");
  XMLCh *transportationXMLCh = XMLString::transcode("transportation");
  XMLCh *transportationsXMLCh = XMLString::transcode("transportations");
  XMLCh *typeXMLCh = XMLString::transcode("type");
  XMLCh *upperBoundXMLCh = XMLString::transcode("upperBound");
  XMLCh *versionXMLCh = XMLString::transcode("version");
  const XMLCh *xmlch;
  char *tmpChar;
  unsigned long ordering;
  unsigned long sharingValue;
  unsigned long transportation;
  unsigned long upperBound;
  std::wstring dataType;
  std::wstring dimensionName;
  std::wstring interactionName;
  std::wstring objectName;
  std::wstring space;
  std::wstring wString;

  name = XMLString::transcode (element->getAttribute (nameXMLCh));
  version = XMLString::transcode (element->getAttribute (versionXMLCh));
  DTDversion = XMLString::transcode (element->getAttribute (DTDversionXMLCh));
  type = XMLString::transcode (element->getAttribute (typeXMLCh));
  unsigned int counter = 0;

  DOMNode *child;
  for (child = element->getFirstChild(); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(), dimensionsXMLCh)==0)
      {
        // at this level only one child element "interactionClass" is expected
        DOMNode* subChild;
        for (subChild = child->getFirstChild(); subChild != 0; subChild = subChild->getNextSibling())
        {
          if (subChild->getNodeType() == DOMNode::ELEMENT_NODE)
          {
            if (XMLString::compareString(subChild->getNodeName(), dimensionXMLCh)==0)
            {
              xmlch = ((DOMElement*)subChild)->getAttribute(OMT::nameString);
              GERTICO::Mapper::mapWstringFromXMLCh(dimensionName, xmlch);
              xmlch = ((DOMElement*)subChild)->getAttribute(dataTypeXMLCh);
              GERTICO::Mapper::mapWstringFromXMLCh(dataType, xmlch);
              upperBound = 0;
              xmlch = ((DOMElement*)subChild)->getAttribute (upperBoundXMLCh);
              GERTICO::Mapper::mapWstringFromXMLCh(wString, xmlch);
              swscanf(wString.c_str(), L"%d", &upperBound);
              fedDimension = new GERTICO::FedDimension(dimensionName, dataType, upperBound, theIdHandler);
              fedDimensionMap[fedDimension->getId()] = fedDimension;
              dimensionNameId[dimensionName] = fedDimension->getId();
            }
          }
        }
      }
    }
  }

  for (child = element->getFirstChild(); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(), objectsXMLCh)==0)
      {
        // at this level only one child element "objectClass" is expected 
        DOMNode* subChild;

        for (subChild = child->getFirstChild(); subChild != 0; subChild = subChild->getNextSibling())
        {
          if (subChild->getNodeType() == DOMNode::ELEMENT_NODE)
          {
            if (XMLString::compareString(subChild->getNodeName(), objectClassXMLCh)==0)
            {
              tmpChar = XMLString::transcode (((DOMElement*)subChild)->getAttribute (OMT::nameString));
              GERTICO::Mapper::mapWstringFromChar(objectName, tmpChar);
              tmpChar = XMLString::transcode (((DOMElement*)subChild)->getAttribute(sharingXMLCh));
              if (strcmp(tmpChar, "Publish") == 0)
              {
                sharingValue = 0;
              }
              else if (strcmp(tmpChar, "Subscribe") == 0)
              {
                sharingValue = 1;
              }
              else if (strcmp(tmpChar, "PublishSubscribe") == 0)
              {
                sharingValue = 2;
              }
              else
              {
                sharingValue = 3;
              }
              rootClass = new ObjectClassI((DOMElement*) subChild, objectName, sharingValue, dimensionNameId, theIdHandler);
            }
          }
        }
      }
      else if (XMLString::compareString(child->getNodeName(), interactionsXMLCh)==0)
      {
        // at this level only one child element "interactionClass" is expected
        DOMNode* subChild;
        GERTICO::HandleSet dimensions;
        for (subChild = child->getFirstChild(); subChild != 0; subChild = subChild->getNextSibling())
        {
          if (subChild->getNodeType() == DOMNode::ELEMENT_NODE)
          {
            if (XMLString::compareString(subChild->getNodeName(), interactionClassXMLCh)==0)
            {
              tmpChar = XMLString::transcode (((DOMElement*)subChild)->getAttribute (OMT::nameString));
              GERTICO::Mapper::mapWstringFromChar(interactionName, tmpChar);
              tmpChar = XMLString::transcode (((DOMElement*)child)->getAttribute(sharingXMLCh));
              if (strcmp(tmpChar, "Publish") == 0)
              {
                sharingValue = 0;
              }
              else if (strcmp(tmpChar, "Subscribe") == 0)
              {
                sharingValue = 1;
              }
              else if (strcmp(tmpChar, "PublishSubscribe") == 0)
              {
                sharingValue = 2;
              }
              else
              {
                sharingValue = 3;
              }
              tmpChar = XMLString::transcode (((DOMElement*)child)->getAttribute(dimensionsXMLCh));
              ObjectModelI::processDimensions(tmpChar, dimensions, dimensionNameId);
              tmpChar = XMLString::transcode (((DOMElement*)subChild)->getAttribute(transportationXMLCh));
              if (strcmp(tmpChar, "HLAreliable") == 0)
              {
                transportation = 0;
              }
              else if (strcmp(tmpChar, "HLAbestEffort") == 0)
              {
                transportation = 1;
              }
              else
              {
                // NOT CORRECT?
                transportation = 0;
              }
              tmpChar = XMLString::transcode (((DOMElement*)subChild)->getAttribute(orderXMLCh));
              if (strcmp(tmpChar, "Receive") == 0)
              {
                ordering = 0;
              }
              else if (strcmp(tmpChar, "TimeStamp") == 0)
              {
                ordering = 1;
              }
              else
              {
                // NOT CORRECT?
                ordering = 0;
              }
              rootInteraction = new InteractionClassI((DOMElement*) subChild, interactionName, space, ordering, transportation, sharingValue, dimensions, dimensionNameId, theIdHandler);
            }
          }
        }
      }
      else if (XMLString::compareString(child->getNodeName(), dimensionsXMLCh)==0)
      {
        counter += 1;
      }
      else if (XMLString::compareString(child->getNodeName(), timeXMLCh)==0)
      {
        counter += 1;
      }
      else if (XMLString::compareString(child->getNodeName(), synchronizationsXMLCh)==0)
      {
        counter += 1;
      }
      else if (XMLString::compareString(child->getNodeName(), transportationsXMLCh)==0)
      {
        counter += 1;
      }
      else if (XMLString::compareString(child->getNodeName(), switchesXMLCh)==0)
      {
        counter += 1;
      }
      else if (XMLString::compareString(child->getNodeName(), dataTypesXMLCh)==0)
      {
        counter += 1;
      }
      else
      {
        counter += 1;
      }
    }
  }
  // build up parent relationship table
  if (rootClass)
  {
    addParentRelation (rootClass);
  }
  if (rootInteraction)
  {
    addParentRelation (rootInteraction);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjectModelI::~ObjectModelI(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectModelI::addParentRelation (GERTICO::ObjectClass* oC)
{
  allClasses[oC->getId()] = oC;
  std::map <unsigned long, GERTICO::ObjectClass*>::iterator iChild;
  for (iChild = oC->childClasses.begin();
       iChild != oC->childClasses.end();
       iChild++)
  {
    parentRelations[iChild->second->getId()] = oC->getId();
    addParentRelation (iChild->second);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectModelI::addParentRelation (GERTICO::InteractionClass* iC)
{
  allInteractions[iC->getId()] = iC;
  std::map <unsigned long, GERTICO::InteractionClass*>::iterator iChild;
  for (iChild = iC->childInteractions.begin();
       iChild != iC->childInteractions.end();
       iChild++)
  {
    parentRelations[iChild->second->getId()] = iC->getId();
    addParentRelation (iChild->second);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
XercesDOMParser *GERTICO::OMT::parser = 0;

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::OMT::initialize (void) 
{
  // check if allready initialized
  if (OMT::parser != 0)
  {
    return;
  }

  // Initialize the XML4C system
  try
  {
    XMLPlatformUtils::Initialize();
  }

  catch (const XMLException &)
  {
//    std::cerr << "Error during initialization! :\n"
//         << StrX(toCatch.getMessage()) << std::endl;
  }

  // initialize own classes
  nameString = XMLString::transcode ("name");
  classNodeNameString =  XMLString::transcode ("objectClass");
  interactionNodeNameString =  XMLString::transcode ("interactionClass");

  // Instantiate the DOM parser.
  parser = new XercesDOMParser;
  parser->setValidationScheme(XercesDOMParser::Val_Auto);

  // And create our error handler and install it
  parser->setErrorHandler(HLAparseErrorHandler::getErrorHandler());
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::OMT::printNodeTree (DOMNode* node, unsigned int level)
{
  unsigned int i;
  for (i=0; i<level; i++ ) std::cout << ".";
  std::cout << " ";
  printNode (node);
  DOMNodeList* nl = node->getChildNodes ();
  for (i=0; i<nl->getLength(); i++)
  {
    printNodeTree (nl->item(i), level+1);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::OMT::printNodeWithChilds (DOMNode* node)
{
  printNode (node);
  std::cout << std::endl;
  DOMNodeList* nl = node->getChildNodes ();
  for (unsigned int i=0; i<nl->getLength(); i++)
  {
     std::cout << "Child " << i << ": ";
     printNode (nl->item(i));
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::OMT::printNode (DOMNode* node)
{
  std::cout << "Node Name: " << node->getNodeName();
  switch (node->getNodeType())
  {
    case DOMNode::TEXT_NODE:
      std::cout << ", TEXT_NODE";
      break;
    case DOMNode::PROCESSING_INSTRUCTION_NODE :
      std::cout << ", PROCESSING_INSTRUCTION_NODE";
      break;
    case DOMNode::DOCUMENT_NODE:
      std::cout << ", DOCUMENT_NODE";
      break;
    case DOMNode::ELEMENT_NODE:
      std::cout << ", ELEMENT_NODE";
      break;
    case DOMNode::ENTITY_REFERENCE_NODE:
      std::cout << ", ENTITY_REFERENCE_NODE";
      break;
    case DOMNode::CDATA_SECTION_NODE:
      std::cout << ", CDATA_SECTION_NODE";
      break;
    case DOMNode::COMMENT_NODE:
      std::cout << ", COMMENT_NODE";
      break;
    case DOMNode::DOCUMENT_TYPE_NODE:
      std::cout << ", DOCUMENT_TYPE_NODE";
      break;
    case DOMNode::ENTITY_NODE:
      std::cout << ", ENTITY_NODE";
      break;
    default:
      std::cout << ", unkown type";
  }
  std::cout << std::endl;
}

// ---------------------------------------------------------------------------
// create a ObjectModel from a xml-File
// ---------------------------------------------------------------------------
GERTICO::OMT* GERTICO::OMT::parseFromFile(std::string const &fileName, GERTICO::NextHandle &theIdHandler) 
{
  initialize();
  parser->parse (fileName.c_str());
  if (HLAparseErrorHandler::getErrorHandler()->getSawErrors())
  {
    HLAparseErrorHandler::getErrorHandler()->resetErrors();
    throw GERTICO::ErrorReadingFED("parseFromFile");
  }

//  printNodeTree (parser->getDocument(), 0);
//  printNodeWithChilds (parser->getDocument());

  OMT *omt = NULL;
  DOMDocument *doc = parser->getDocument();
  if (doc != 0)
  {
    omt = new OMT(doc, theIdHandler);

    if (HLAparseErrorHandler::getErrorHandler()->getSawErrors())
    {
      HLAparseErrorHandler::getErrorHandler()->resetErrors();
      throw GERTICO::ErrorReadingFED("parseFromFile");
    }
  }
  else
  {
    HLAparseErrorHandler::getErrorHandler()->resetErrors();
    throw GERTICO::CouldNotOpenFED();
  }
  return omt;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::OMT::OMT(DOMDocument* doc, GERTICO::NextHandle &theIdHandler)
{
  DOMElement* elem = doc->getDocumentElement();
  if (elem != 0) objectModel = new ObjectModelI(elem, theIdHandler);
  else objectModel = 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::OMT::~OMT (void) 
{
  XMLPlatformUtils::Terminate();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectModelI::processDimensions(char *theTmpChar, GERTICO::HandleSet &theDimensions, GERTICO::WstringHandleMap &theDimensionNameId)
{
  WstringHandleMap::iterator itDimension;
  char buff[512];
  char tmp[512];
  std::wstring dimensionName;
  int offset = 0;
  int pos = 0;
  size_t size;

  theDimensions.clear();

  strcpy(buff, theTmpChar);
  size = strlen(buff);
  tmp[0] = '\0';
  for (pos = 0; pos < size; pos += offset)
  {
    sscanf(&buff[pos], "%s%n", tmp, &offset);
    GERTICO::Mapper::mapWstringFromChar(dimensionName, tmp);
    itDimension = theDimensionNameId.find(dimensionName);
    if (itDimension != theDimensionNameId.end())
    {
      theDimensions.insert(itDimension->second);
    }
  }
}

// ---------------------------------------------------------------------------
//  ostream << DOMString
//
//  Stream out a DOM string. Doing this requires that we first transcode
//  to char * form in the default code page for the system
// ---------------------------------------------------------------------------
std::ostream& operator<< (std::ostream& target, const XMLCh* s)
{
    target << XMLString::transcode(s);
    return target;
}
