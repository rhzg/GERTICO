/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**
 
$Author: mul $
$Name $
$Log: HLAparseErrorHandler.cpp,v $
Revision 1.2  2007/09/05 15:07:26  mul
Changes for ieee1516.

Revision 1.1  2004/05/28 11:55:11  mul
Add new files.

 
**
*******************************************************************************/
 
 
#include "HLAparseErrorHandler.h"


HLAparseErrorHandler *HLAparseErrorHandler::errorHandler = 0;



HLAparseErrorHandler::HLAparseErrorHandler(void)
{
  fSawErrors = false;
}
 
HLAparseErrorHandler::~HLAparseErrorHandler(void)
{
}
 
// ---------------------------------------------------------------------------
//  HLAparseHandlers: Overrides of the SAX ErrorHandler interface
// ---------------------------------------------------------------------------
void HLAparseErrorHandler::error(const xercesc::SAXParseException& e)
{
  fSawErrors = true;
  std::wcerr << L"\nError while parsing xml file "
       << L", line " << e.getLineNumber()
       << L", char " << e.getColumnNumber()
       << L"\n  Message: " << e.getMessage() << std::endl;
}
 
void HLAparseErrorHandler::fatalError(const xercesc::SAXParseException& e)
{
  fSawErrors = true;
  std::wcerr << L"\nFatal Error while parsing xml file "
       << L", line " << e.getLineNumber()
       << L", char " << e.getColumnNumber()
       << L"\n  Message: " << e.getMessage() << std::endl;
}
 
void HLAparseErrorHandler::warning(const xercesc::SAXParseException& e)
{
  fSawErrors = true;
  std::wcerr << L"\nWarning while parsing xml file "
       << L", line " << e.getLineNumber()
       << L", char " << e.getColumnNumber()
       << L"\n  Message: " << e.getMessage() << std::endl;
}
 
void HLAparseErrorHandler::resetErrors(void)
{
    fSawErrors = false;
}

