#ifndef Fed_HEADER
#define Fed_HEADER

/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: Fed.h,v $
Revision 1.7  2007/09/05 15:01:14  mul
Changes for ieee1516.

Revision 1.6  2007/03/12 12:56:34  mul
Changed string to wstring.

Revision 1.5  2005/11/17 13:09:09  mul
Fix memory leaks.

Revision 1.4  2005/05/24 07:02:27  mul
Add transport and ordering to fix timestamp problem.

Revision 1.3  2005/02/11 14:46:33  mul
Add scoping.

Revision 1.2  2004/08/19 09:41:28  mul
Changes for save/restore logic.

Revision 1.1  2004/05/28 11:55:11  mul
Add new files.

 
**
*******************************************************************************/


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------

#include <string>
//#include <stdio.h>

#include <map> 

#include "ClassInfo.h"
#include "DataModel.h"
#include "FedParser.h"

/*******************************************************************************
**
**
*******************************************************************************/
namespace GERTICO
{
  /*******************************************************************************
  **
  **
  *******************************************************************************/
  class ObjectModelImpl: virtual public GERTICO::ObjectModel
  {
    void addParentRelation (GERTICO::ObjectClass* oC);
    void addParentRelation (GERTICO::InteractionClass* iC);
    void processObjects (ObjectClass*, multitree<unsigned long>::node_iterator &, std::map<unsigned long, ObjectClassInfo> &, std::map<unsigned long, AttributeInfo> &, GERTICO::NextHandle &theIdHandler);
    void processInteractions (InteractionClass*, multitree<unsigned long>::node_iterator &, std::map<unsigned long, InteractionClassInfo> &, std::map<unsigned long, ParameterInfo> &, GERTICO::NextHandle &theIdHandler);

  public:
    ObjectModelImpl (FedPrivateData &, GERTICO::NextHandle &theIdHandler);
    virtual ~ObjectModelImpl(void);
  };
};

#endif // Fed_HEADER
