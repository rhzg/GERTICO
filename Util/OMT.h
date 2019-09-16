#ifndef OMT_HEADER
#define OMT_HEADER

/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: OMT.h,v $
Revision 1.7  2007/11/13 10:20:46  mul
Minor type change.

Revision 1.6  2007/09/25 08:03:14  mul
Changes for ddm.

Revision 1.5  2007/09/05 15:12:26  mul
Changes for ieee1516.

Revision 1.4  2007/03/12 12:47:47  mul
Changed string to wstring.

Revision 1.3  2005/11/17 10:14:16  mul
Add destructors.

Revision 1.2  2005/02/11 14:46:34  mul
Add scoping.

Revision 1.1  2004/05/28 11:55:11  mul
Add new files.

 
**
*******************************************************************************/


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
using namespace xercesc;

#include <string>

//#include <stdlib.h>
#include <map> 

#include "DataModel.h"
#include "HLAparseErrorHandler.h"

namespace GERTICO
{
  /*******************************************************************************
  **
  **
  *******************************************************************************/
  class ObjectClassI: public GERTICO::ObjectClass
  {
  public:
    ObjectClassI(DOMElement* element, std::wstring const &theName, unsigned long const &theSharing, GERTICO::WstringHandleMap &theDimensionNameId, GERTICO::NextHandle &theIdHandler);
    virtual ~ObjectClassI(void);
  };

  /*******************************************************************************
  **
  **
  *******************************************************************************/
  class InteractionClassI: public GERTICO::InteractionClass
  {
  public:
    InteractionClassI(DOMElement* element, std::wstring const &theName, std::wstring const &theSpace, unsigned long &theOrdering, unsigned long &theTransport, unsigned long const &theSharing, GERTICO::HandleSet const &theDimensions, GERTICO::WstringHandleMap &theDimensionNameId, GERTICO::NextHandle &theIdHandler);
    virtual ~InteractionClassI(void);
  };


/*******************************************************************************
**
**
*******************************************************************************/
class ObjectModelI: public GERTICO::ObjectModel
{
    GERTICO::WstringHandleMap dimensionNameId;
    void addParentRelation (GERTICO::ObjectClass* oC);
    void addParentRelation (GERTICO::InteractionClass* iC);

public:
    ObjectModelI(DOMElement* element, GERTICO::NextHandle &theIdHandler);
    virtual ~ObjectModelI(void);

    static void processDimensions(char *theTmpChar, GERTICO::HandleSet &theDimensions, GERTICO::WstringHandleMap &theDimensionNameId);
};

/*******************************************************************************
**
**
*******************************************************************************/
class OMT 
{
    static XercesDOMParser* parser;
    static void initialize (void);

protected:
    OMT(DOMDocument* node, GERTICO::NextHandle &theIdHandler);

public:
    static XMLCh* nameString;
    static XMLCh* classNodeNameString;
    static XMLCh* interactionNodeNameString;

    ~OMT(void);
    ObjectModel* objectModel;
    
    static void printNodeTree (DOMNode* node, unsigned int level);
    static void printNodeWithChilds (DOMNode* node);
    static void printNode (DOMNode* doc);

    static OMT* parseFromFile(std::string const &fileName, GERTICO::NextHandle &theIdHandler);
};

};


#endif // OMT_HEADER
