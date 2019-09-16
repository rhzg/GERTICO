#ifndef GERTICOconfImpl_HEADER
#define GERTICOconfImpl_HEADER

/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: GERTICOconfImpl.h,v $
Revision 1.1  2008/02/07 09:20:01  mul
From another directory.

 
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
#include <xercesc/util/XMLStringTokenizer.hpp>
using namespace xercesc;


#include <string>

#include <map>

#include "GERTICOconf.h" 
#include "Util/HLAparseErrorHandler.h" 

/*******************************************************************************
**
**
*******************************************************************************/
class NS_xml: public virtual NS
{
public:
  NS_xml (DOMNode* n);
};


/*******************************************************************************
**
**
*******************************************************************************/
class GERTICOconf_xml: public virtual GERTICOconf
{
	const XMLCh* stringModelPath;

public:
    GERTICOconf_xml(DOMDocument* node);
    static XercesDOMParser* parser;
    XMLStringTokenizer* ModelPath;

    ~GERTICOconf_xml();
    
//    static GERTICOconf* parseFromFile (const string &fileName);

    bool hasMorePath ();
    char* nextPath();
    void resetPath();
};




#endif // GERTICOconfImpl_HEADER
