/*********************************************************************************
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
**********************************************************************************
 
$Author: mul $
$Name $
$Log: Space.h,v $
Revision 1.6  2007/09/05 15:16:47  mul
Changes for ieee1516.

Revision 1.5  2007/03/12 12:36:14  mul
Changed string to wstring.

Revision 1.4  2005/05/03 14:36:18  mul
Xerces interface in one file.

Revision 1.3  2004/07/16 10:23:28  mul
Minor change.

Revision 1.2  2004/05/28 11:19:14  mul
Fix include paths.

Revision 1.1  2004/05/27 11:24:38  mul
Integrate subscriber management.

 
**
*******************************************************************************/ 
#ifndef Space_H_
#define Space_H_

#include <map>
#include "idl/GeRtiFactoryS.h"
#include "XercesInclude.h"
#include "HLAparseErrorHandler.h"

namespace GERTICO
{
  class Dimension
  {
    GeRtiFactory::GeRtiHandle id;
    std::wstring myName;
 
  public:
    Dimension (const std::wstring &theName, const GeRtiFactory::GeRtiHandle &theId);
    virtual ~Dimension (void);
 
    void getName(std::wstring &theName);
    void getNameLower(std::wstring &theName);
    GeRtiFactory::GeRtiHandle getId (void);
    void save (DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  typedef std::map <GeRtiFactory::GeRtiHandle, GERTICO::Dimension *> DimensionMap;

  class RoutingSpace
  {
    GeRtiFactory::GeRtiHandle id;
    std::wstring myName;
 
  public:
    DimensionMap dimensions;
 
    RoutingSpace(const std::wstring &theName, const GeRtiFactory::GeRtiHandle &theId);
    virtual ~RoutingSpace (void);
 
    void getName(std::wstring &);
    void getNameLower(std::wstring &);
    GeRtiFactory::GeRtiHandle getId (void);
    void restore (DOMElement *theDOMElement);
    void save (DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  typedef std::map <GeRtiFactory::GeRtiHandle, GERTICO::RoutingSpace *> RoutingSpaceMap;
};

#endif /* Space_H_  */
