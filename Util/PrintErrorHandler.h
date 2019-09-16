/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: PrintErrorHandler.h,v $
Revision 1.1  2004/04/19 14:37:05  mul
Add programs for DOM writer.

 
**
*******************************************************************************/

#ifndef PRINT_ERROR_HANDLER_HPP
#define PRINT_ERROR_HANDLER_HPP

#include <xercesc/dom/DOMErrorHandler.hpp>

XERCES_CPP_NAMESPACE_USE

namespace GERTICO
{
  class PrintErrorHandler : public DOMErrorHandler
  {
  public:

    PrintErrorHandler(){};
    ~PrintErrorHandler(){};

    /** @name The error handler interface */
    bool handleError(const DOMError& domError);
    void resetErrors(){};

  private :
    /* Unimplemented constructors and operators */
    PrintErrorHandler(const DOMErrorHandler&);
    void operator=(const DOMErrorHandler&);

  };
};

#endif
