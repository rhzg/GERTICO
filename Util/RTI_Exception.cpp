/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: RTI_Exception.cpp,v $
Revision 1.2  2008/11/26 15:03:11  mul
Change for suse11.0.

Revision 1.1  2007/10/17 13:24:24  mul
Changes for linux.

 
**
*******************************************************************************/

#include <string.h>
#include <string>
#include "include/RTI_1.3/RTI.hh"

RTI::Exception::Exception (const char *reason)
{
  _reason = strdup (reason);
  _serial = 0;
}

RTI::Exception::Exception (RTI::ULong serial, const char *reason)
{
  _serial = serial;
  if (reason == NULL)
  {
    _reason = NULL;
  }
  else
  {
    _reason = strdup (reason);
  }
}

RTI::Exception::Exception (const RTI::Exception &toCopy)
{
  _reason = strdup (toCopy._reason);
  _serial = toCopy._serial;
}

RTI::Exception::~Exception ()
{
  delete _reason;
}

RTI::Exception & RTI::Exception::operator = (const RTI::Exception &e)
{
  if (_reason)
  {
    delete _reason;
  }
  _reason = strdup (e._reason);
  _serial = e._serial;
  return *this;
}

std::ostream & operator << (std::ostream &out, RTI::Exception *e)
{
	return out << "Exception: " << e->_reason << std::endl;
}

std::ostream & operator << (std::ostream &out, RTI::Exception const &e)
{
	return out << "Exception: " << e._reason << std::endl;
}
