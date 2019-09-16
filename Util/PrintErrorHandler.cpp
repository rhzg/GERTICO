/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: PrintErrorHandler.cpp,v $
Revision 1.1  2004/04/19 14:37:04  mul
Add programs for DOM writer.


**
*******************************************************************************/

#include <iostream>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOMError.hpp>

#include "PrintErrorHandler.h"

bool GERTICO::PrintErrorHandler::handleError(const DOMError &domError)
{
  // Display whatever error message passed from the serializer
  if (domError.getSeverity() == DOMError::DOM_SEVERITY_WARNING)
      std::cerr << "\nWarning Message: ";
  else if (domError.getSeverity() == DOMError::DOM_SEVERITY_ERROR)
      std::cerr << "\nError Message: ";
  else
      std::cerr << "\nFatal Message: ";

  char *msg = XMLString::transcode(domError.getMessage());
  std::cerr<< msg <<std::endl;
  XMLString::release(&msg);

  // Instructs the serializer to continue serialization if possible.
  return true;
}
