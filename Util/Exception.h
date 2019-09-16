/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: Exception.h,v $
Revision 1.1  2004/04/19 14:37:04  mul
Add programs for DOM writer.

 
**
*******************************************************************************/

#include <string>

#ifndef Exception_H_
#define Exception_H_

namespace GERTICO
{
  class CouldNotOpenFED {};
  class ErrorReadingFED
  {
    std::string error;

  public:
    ErrorReadingFED (const std::string &);
    virtual ~ErrorReadingFED (void);

    void getError (std::string &);
  };
};

#endif
