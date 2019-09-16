/*********************************************************************************
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
**********************************************************************************

$Author: mul $
$Name $
$Log: Space.cpp,v $
Revision 1.4  2007/09/05 15:16:48  mul
Changes for ieee1516.

Revision 1.3  2007/03/12 12:38:20  mul
Changed string to wstring.

Revision 1.2  2005/11/17 10:14:43  mul
Fix memory leaks.

Revision 1.1  2004/05/27 11:24:38  mul
Integrate subscriber management.


**
*******************************************************************************/

#include "Space.h"
#include "Util/Mapper.h"

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Dimension::Dimension(const std::wstring &theName, const GeRtiFactory::GeRtiHandle &theId)
{
  myName = theName;
  id = theId;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Dimension::~Dimension (void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::Dimension::getId (void)
{
  return id;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Dimension::getName(std::wstring &theName)
{
  theName = myName;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Dimension::getNameLower(std::wstring &theName)
{
  theName = myName;
  GERTICO::Mapper::nameToLower(theName);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Dimension::save (DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel1;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[128];
  std::string s;
  unsigned long ul;

  XMLString::transcode("dimensions", tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel1);

  XMLString::transcode("name", tempStr, 99);
  GERTICO::Mapper::mapStringFromWstring(s, myName);
  XMLString::transcode(s.c_str (), tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode("id", tempStr, 99);
  ul = id;
  sprintf (buf, "%lu", ul);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RoutingSpace::RoutingSpace(const std::wstring &theName, const GeRtiFactory::GeRtiHandle &theId)
{
  myName = theName;
  id = theId;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RoutingSpace::~RoutingSpace (void)
{
  DimensionMap::iterator itDM;
  GERTICO::Dimension *currDimension;
  
  for (itDM = dimensions.begin ();
       itDM != dimensions.end ();
       itDM = dimensions.begin ())
  {
    currDimension = itDM->second;
    dimensions.erase (itDM);
    delete currDimension;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::RoutingSpace::getId (void)
{
  return id;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RoutingSpace::getName(std::wstring &theName)
{
  theName = myName;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RoutingSpace::getNameLower(std::wstring &theName)
{
  theName = myName;
  GERTICO::Mapper::nameToLower(theName);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RoutingSpace::save (DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel1;
  DOMElement* elemLevel2;
  DimensionMap::iterator itDM;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[128];
  std::string s;
  unsigned long ul;

  XMLString::transcode("space", tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel1);

  XMLString::transcode("name", tempStr, 99);
  GERTICO::Mapper::mapStringFromWstring(s, myName);
  XMLString::transcode(s.c_str (), tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode("id", tempStr, 99);
  ul = id;
  sprintf (buf, "%lu", ul);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode("dimensions", tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  elemLevel1->appendChild(elemLevel2);

  for (itDM = dimensions.begin (); itDM != dimensions.end (); itDM++)
  {
    itDM->second->save (theDOMDocument, *elemLevel2);
  }
}
