/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: Item.h,v $
Revision 1.3  2007/09/25 08:04:02  mul
Changes for ddm.

Revision 1.2  2007/03/12 12:52:16  mul
Changed string to wstring.

Revision 1.1  2004/05/10 07:46:39  mul
Changes due to integrating object management with ownership.

 
**
*******************************************************************************/

#ifndef Item_H_
#define Item_H_

#include <map>
#include <string>

#include "Util/GeRtiTypes.h"

namespace GERTICO
{
  class Item
  {
    GERTICO::HandleSet dimensions;
    unsigned long myId;
    unsigned long space;
    unsigned long ordering;
    unsigned long transportation;

  public:
    class notFound {};
    std::wstring myName;
    std::wstring myNameLower;

    Item(const std::wstring &theName, const unsigned long &id, const unsigned long &theSpace, const unsigned long &theOrdering, const unsigned long &theTransportation, GERTICO::HandleSet const &theDimensions);
    virtual ~Item (void);

    void getDimensions(GERTICO::HandleSet &theDimensions);
    unsigned long getId (void) const;
    unsigned long getOrdering (void) const;
    unsigned long getSpace (void) const;
    unsigned long getTransportation (void) const;
    unsigned long myClass;
  };

  typedef std::map <unsigned long, GERTICO::Item *> ItemMap;
};

#endif /* Item_H_  */
