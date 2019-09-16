/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** SupportingServicesEC.h
**
*******************************************************************************/

#ifndef SupportingServicesEC_H_
#define SupportingServicesEC_H_

#include "idl/GeRtiFactoryS.h"
#include "Util/GeRtiTypes.h"
#include "Util/Mapper.h"

namespace GERTICO
{
  class SupportingServicesEC
  {
    // Parents and children of classes.
    GERTICO::HandleMap parentsInteraction;
    GERTICO::HandleMap parentsObject;
    GERTICO::HandleSetMap childrenInteraction;
    GERTICO::HandleSetMap childrenObjectClass;

  public:
    //Constructor
    SupportingServicesEC(void);

    //Destructor
    virtual ~SupportingServicesEC(void);

    void clear(void);
    void fillInteractionParents(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &theParents);
    void fillObjectParents(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &theParents);

    void getInteractionChildren(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSet &theChildren);
    void getInteractionParents(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles &thePparents);
    void getObjectClassChildren(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSet &theChildren);

    GeRtiFactory::GeRtiHandle getPrivilegeToDeleteId(void);

    GeRtiFactory::GeRtiHandle getInteractionParent(GeRtiFactory::GeRtiHandle const &theClass);
    GeRtiFactory::GeRtiHandle getObjectParent(GeRtiFactory::GeRtiHandle const &theClass);
    bool isDerivedInteractionClass(GeRtiFactory::GeRtiHandle const &theDerivedClass, GeRtiFactory::GeRtiHandle const &theBaseClass);
    bool isDerivedObjectClass(GeRtiFactory::GeRtiHandle const &theDerivedClass, GeRtiFactory::GeRtiHandle const &theBaseClass);
  };
}
#endif /* SupportingServicesEC_H_  */
