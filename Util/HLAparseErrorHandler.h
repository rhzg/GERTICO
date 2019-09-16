#ifndef HLAparseErrorHandler_HEADER
#define HLAparseErrorHandler_HEADER


/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**
 
$Author: mul $
$Name $
$Log: HLAparseErrorHandler.h,v $
Revision 1.2  2007/09/05 15:07:25  mul
Changes for ieee1516.

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
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXException.hpp>
using namespace xercesc;
 
 
#include <string>
#include <iostream>

//#include <stdlib.h>
#include <map>
using std::map;
using std::string;


class SAXParseException;  

// ---------------------------------------------------------------------------
//  This is a simple class that lets us do easy (though not terribly efficient)
//  trancoding of XMLCh data to local code page for display.
// ---------------------------------------------------------------------------
class StrX
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    StrX(const XMLCh* const toTranscode)
    {
        // Call the private transcoding method
        fLocalForm = XMLString::transcode(toTranscode);
    }
 
    ~StrX(void)
    {
        //delete [] fLocalForm;
    }
 
 
    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    const char* localForm(void) const
    {
        return fLocalForm;
    }
 
private :
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fLocalForm
    //      This is the local code page form of the string.
    // -----------------------------------------------------------------------
    char*   fLocalForm;
};

/* 
inline std::ostream& operator<<(std::ostream& target, const StrX& toDump)
{
    target << toDump.localForm(void);
    return target;
}
*/

// ---------------------------------------------------------------------------
//  Simple error handler deriviative to install on parser
// ---------------------------------------------------------------------------
class HLAparseErrorHandler : public ErrorHandler
{
private:
    static HLAparseErrorHandler* errorHandler; 


public:
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    HLAparseErrorHandler(void);
    ~HLAparseErrorHandler(void);
 
 
    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    bool getSawErrors(void) const { return fSawErrors; };
    static HLAparseErrorHandler* getErrorHandler (void)
    {
      if (errorHandler == 0) errorHandler = new HLAparseErrorHandler();
      return errorHandler;
    }
 
 
    // -----------------------------------------------------------------------
    //  Implementation of the SAX ErrorHandler interface
    // -----------------------------------------------------------------------
    void warning(const xercesc::SAXParseException& e);
    void error(const xercesc::SAXParseException& e);
    void fatalError(const xercesc::SAXParseException& e);
    void resetErrors(void);
 
private :
 
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fSawErrors
    //      This is set if we get any errors, and is queryable via a getter
    //      method. Its used by the main code to suppress output if there are
    //      errors.
    // -----------------------------------------------------------------------
    bool    fSawErrors;
};


#endif // HLAparseErrorHandler
