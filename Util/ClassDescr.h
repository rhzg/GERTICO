/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: ClassDescr.h,v $
Revision 1.14  2010/06/28 13:35:28  mul
Add class to bundle attribute information.

Revision 1.13  2009/09/23 06:50:52  mul
Add class description holder.

Revision 1.12  2009/06/12 12:13:37  mul
Use thread mutex.

Revision 1.11  2007/09/25 08:05:29  mul
Changes for ddm.

Revision 1.10  2007/09/05 14:55:51  mul
Changes for ieee1516.

Revision 1.9  2007/03/12 12:59:27  mul
Changed string to wstring.

Revision 1.8  2006/06/23 12:58:32  mul
New method to check for derived classes.

Revision 1.7  2005/03/15 14:32:53  mul
Add get interaction space function.

Revision 1.6  2005/02/11 14:46:33  mul
Add scoping.

Revision 1.5  2005/02/07 10:34:01  mul
Changes due to test cases.

Revision 1.4  2004/12/13 15:37:21  mul
Add additional access fuctionality to the class tree.

Revision 1.3  2004/09/23 14:50:07  mul
Add logic to get set of derived classes.

Revision 1.2  2004/07/16 11:16:59  mul
Changes due to verfication test.

Revision 1.1  2004/05/10 07:46:39  mul
Changes due to integrating object management with ownership.


**
*******************************************************************************/


#ifndef ClassDescr_H_
#define ClassDescr_H_

#include "ace/Synch.h"
#include "idl/GeRtiFactoryS.h"
#include <map>
#include <string>
#include <vector>

#include "GeRtiTypes.h"
#include "Item.h"

namespace GERTICO
{
  class LRCattributeFlags
  {
  public:
    GERTICO::HandleSet dimensions;
    std::wstring name;
    unsigned long ordering;
    unsigned long transportation;
  };

  class LRCparameterFlags
  {
  public:
    std::wstring name;
  };

  typedef std::map <GeRtiFactory::GeRtiHandle, GERTICO::LRCattributeFlags, cmpHandle> LRCattributeFlagsMap;
  typedef std::map <GeRtiFactory::GeRtiHandle, GERTICO::LRCparameterFlags, cmpHandle> LRCparameterFlagsMap;

  class ClassDescr
  {
    GERTICO::HandleSet dimensions;
    std::wstring name;
    std::wstring nameFull;
    unsigned long myId;
    unsigned long space;
    unsigned long ordering;
    unsigned long transportation;

  public:
    class notFound {};
    ClassDescr *parent;
    GERTICO::ItemMap items;
    std::map <unsigned long, ClassDescr *> classDescrs;

    ClassDescr(std::wstring const &theName, unsigned long const &id, unsigned long const &theSpace, unsigned long const &theOrdering, unsigned long const &theTransportation, unsigned long const &theSharing, GERTICO::HandleSet const &theDimensions);
    ClassDescr(std::wstring const &theName, unsigned long const &id, unsigned long const &theSpace, unsigned long const &theOrdering, unsigned long const &theTransportation, unsigned long const &theSharing, GERTICO::HandleSet const &theDimensions, ClassDescr *);

    virtual ~ClassDescr (void);
    void addItem(std::wstring const &theName, unsigned long const &id, unsigned long const &theSpace, unsigned long const &theOrdering, unsigned long const &theTransportation, GERTICO::HandleSet const &theDimensions);

    // Get all attributes for class including inherited attributes.
    void getAttributes(GERTICO::HandleSet &theAttributes);

    ClassDescr *getClassDescr(unsigned const long &id);

    // Param: item name
    GERTICO::Item *getClassItemByName(const std::wstring &theName);

    // Param: item id
    GERTICO::Item *getClassItem (unsigned long const &);

    void getDimensions(GERTICO::HandleSet &theDimensions);

    unsigned long getId (void) const;
    void getInteractionSpaceHandle(unsigned long &theSpaceHandle);

    std::wstring getNameLower(void);
    std::wstring getNameFull(void);

    void getOrdering(unsigned long &theOrdering);

    void getRoutingSpaceHandle (ClassDescr *theClassDescr, unsigned long const &theClass, GeRtiFactory::GeRtiHandle &theSpace, bool &theClassFound);

    void getRoutingSpaceHandle (ClassDescr *theClassDescr, unsigned long const &theAttribute, unsigned long const &theClass, GeRtiFactory::GeRtiHandle &theSpace, bool &theClassFound, bool &theAttributeFound);

    void getTransportation(unsigned long &theTransportation);

    bool isDerivedClass(unsigned long const &theBaseClass);
  };

  typedef std::map <unsigned long, GERTICO::ClassDescr *> ClassDescrMap;

  class ClassDescrHolder
  {
    std::wstring findClassNamePrivate(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::ClassDescr *theClassDescr);
    GeRtiFactory::GeRtiHandle findHandlePrivate(std::wstring const &theName, GERTICO::ClassDescr &c);
  public:
    ACE_Thread_Mutex pm;
    GERTICO::ClassDescr *classDescr;

    ClassDescrHolder(void);
    virtual ~ClassDescrHolder(void);
    std::wstring findClassName(GeRtiFactory::GeRtiHandle const &theClass);
    GeRtiFactory::GeRtiHandle findHandle(std::wstring const &theName);
    ClassDescr *getClassDescr(unsigned long const &theClass);
    void getAttributeRoutingSpaceHandle(const GeRtiFactory::GeRtiHandle &theAttribute, const GeRtiFactory::GeRtiHandle &theClass, GeRtiFactory::GeRtiHandle &theSpace, bool &theClassFound, bool &theAttributeFound);
    void getLRCattributeFlags(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::LRCattributeFlagsMap &theLRCattributeFlagsMap);
    bool getLRCparameterFlags(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::LRCparameterFlagsMap &theLRCparameterFlagsMap);
    void getRoutingSpaceHandle(unsigned long const &theClass, GeRtiFactory::GeRtiHandle &theSpace, bool &theClassFound);
  };
};

#endif /* ClassDescr_H_  */
