/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: Item.cpp,v $
Revision 1.4  2007/09/25 08:04:18  mul
Changes for ddm.

Revision 1.3  2007/03/12 12:52:16  mul
Changed string to wstring.

Revision 1.2  2005/11/17 10:13:31  mul
Fix memory leaks.

Revision 1.1  2004/05/10 07:46:39  mul
Changes due to integrating object management with ownership.

 
**
*******************************************************************************/

#include <ctype.h>
#include "Item.h"
#include "Util/Mapper.h"

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Item::Item(const std::wstring &theName, const unsigned long &id, const unsigned long &theSpace, const unsigned long &theOrdering, const unsigned long &theTransportation, GERTICO::HandleSet const &theDimensions)
{
  dimensions = theDimensions;
  myName = theName;
  myNameLower = theName;
  GERTICO::Mapper::nameToLower(myNameLower);
  myId = id;
  ordering = theOrdering;
  space = theSpace;
  transportation = theTransportation;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Item::~Item (void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Item::getDimensions(GERTICO::HandleSet &theDimensions)
{
  theDimensions = dimensions;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
unsigned long GERTICO::Item::getId (void) const
{
  return myId;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
unsigned long GERTICO::Item::getOrdering (void) const
{
  return ordering;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
unsigned long GERTICO::Item::getSpace (void) const
{
  return space;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
unsigned long GERTICO::Item::getTransportation (void) const
{
  return transportation;
}
