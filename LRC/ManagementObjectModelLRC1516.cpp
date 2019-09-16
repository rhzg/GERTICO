/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: ManagementObjectModelLRC1516.cpp,v $
Revision 1.14  2010/07/22 11:17:02  mul
Correct mom format.

Revision 1.13  2010/06/28 13:43:32  mul
Change version numbers.

Revision 1.12  2010/05/17 08:05:34  mul
Add logical time interval.

Revision 1.11  2010/04/13 12:35:24  mul
Change sender member variables to pointers.

Revision 1.10  2010/02/08 12:40:54  mul
Changes to increase performance.

Revision 1.9  2009/09/24 12:05:38  mul
Add a missing variable.

Revision 1.8  2009/09/23 07:15:49  mul
Add logic for decentral management of attribute ownership.

Revision 1.7  2009/05/07 12:35:19  mul
Changes for removing token logic in time management.

Revision 1.6  2009/03/19 09:13:22  mul
Changes to optimize reading mom in lrc.

Revision 1.5  2009/01/26 09:49:14  mul
Changes to private / public visibility of members.

Revision 1.4  2008/08/21 12:29:22  mul
Changed version number.

Revision 1.3  2008/05/15 14:33:55  mul
Change mom version number.

Revision 1.2  2008/03/06 10:22:01  mul
Change for windows.

Revision 1.1  2008/01/30 13:30:20  mul
New for ieee1516.


**
*******************************************************************************/


#include "LRC/ManagementObjectModelLRC.h"
#include "Util/Mapper.h"
#include "Util/GeRtiFedTimeI.h"
#include "VersionX.h"
#ifdef _WIN32
#define swprintf _snwprintf
#endif

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomDeleteObjectInstance::MomDeleteObjectInstance(GeRtiFactory::GeRtiHandle const &theObjecthandle, const std::string &theUserSuppliedTag, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  objectHandle = theObjecthandle;
  GERTICO::Mapper::mapUserSuppliedTag(userSuppliedTag, theUserSuppliedTag.c_str());
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomDeleteObjectInstance::~MomDeleteObjectInstance(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomDeleteObjectInstance::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"DeleteObjectInstance";
  bool gotError = false;

  try
  {
    geRtiSender.deleteObjectInstance(objectHandle, userSuppliedTag);
  }
  catch(GeRtiFactory::ObjectNotKnown &)
  {
    gotError = true;
    momException.exception = L"ObjectNotKnown";
  }
  catch(GeRtiFactory::DeletePrivilegeNotHeld &)
  {
    gotError = true;
    momException.exception = L"DeletePrivilegeNotHeld";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    GERTICO::MomReportServiceInvocation momReportServiceInvocation;
    wchar_t wc[128];

    momReportServiceInvocation.service = L"deleteObjectInstance";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    swprintf(wc, 128, L"%d", objectHandle);
    std::wstring ws(wc);
    momReportServiceInvocation.suppliedArguments = ws;
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomDeleteObjectInstanceWithTime::MomDeleteObjectInstanceWithTime(GeRtiFactory::GeRtiHandle const &theObjectHandle, std::string const &theUserSuppliedTag, GERTICO::GeRtiFedTime *theFederationTime, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  objectHandle = theObjectHandle;
  federationTime = theFederationTime;
  GERTICO::Mapper::mapUserSuppliedTag(userSuppliedTag, theUserSuppliedTag.c_str());
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomDeleteObjectInstanceWithTime::~MomDeleteObjectInstanceWithTime(void)
{
  delete federationTime;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomDeleteObjectInstanceWithTime::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"DeleteObjectInstanceWithTime";
  bool gotError = false;

  if (gotError == false)
  {
    try
    {
      geRtiSender.deleteObjectInstance(objectHandle, *federationTime, userSuppliedTag);
    }
    catch(GeRtiFactory::ObjectNotKnown &)
    {
      gotError = true;
      momException.exception = L"ObjectNotKnown";
    }
    catch(GeRtiFactory::DeletePrivilegeNotHeld &)
    {
      gotError = true;
      momException.exception = L"DeletePrivilegeNotHeld";
    }
    catch(GeRtiFactory::InvalidFederationTime &)
    {
      gotError = true;
      momException.exception = L"InvalidFederationTime";
    }
    catch(GeRtiFactory::FederateNotExecutionMember &)
    {
      gotError = true;
      momException.exception = L"FederateNotExecutionMember";
    }
    catch(GeRtiFactory::SaveInProgress &)
    {
      momException.exception = L"SaveInProgress";
    }
    catch(GeRtiFactory::RestoreInProgress &)
    {
      gotError = true;
      momException.exception = L"RestoreInProgress";
    }
    catch(GeRtiFactory::RTIinternalError &)
    {
      gotError = true;
      momException.exception = L"RTIinternalError";
    }
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    GERTICO::MomReportServiceInvocation momReportServiceInvocation;
    wchar_t wc[128];

    momReportServiceInvocation.service = L"deleteObjectInstance";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    swprintf(wc, 128, L"%d", objectHandle);
    momReportServiceInvocation.suppliedArguments = wc;
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomDisableAsynchronousDelivery::MomDisableAsynchronousDelivery(GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomDisableAsynchronousDelivery::~MomDisableAsynchronousDelivery(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomDisableAsynchronousDelivery::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"DisableAsynchronousDelivery";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.disableAsynchronousDelivery();
  }
  catch(GeRtiFactory::AsynchronousDeliveryAlreadyDisabled &)
  {
    gotError = true;
    momException.exception = L"AsynchronousDeliveryAlreadyDisabled";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = L"disableAsynchronousDelivery";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomDisableTimeConstrained::MomDisableTimeConstrained(GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomDisableTimeConstrained::~MomDisableTimeConstrained(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomDisableTimeConstrained::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"DisableTimeConstrained";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.disableTimeConstrained();
  }
  catch(GeRtiFactory::TimeConstrainedWasNotEnabled &)
  {
    gotError = true;
    momException.exception = L"TimeConstrainedWasNotEnabled";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = L"disableTimeConstrained";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomDisableTimeRegulation::MomDisableTimeRegulation(GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomDisableTimeRegulation::~MomDisableTimeRegulation(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomDisableTimeRegulation::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"DisableTimeRegulation";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.disableTimeRegulation();
  }
  catch(GeRtiFactory::TimeRegulationWasNotEnabled &)
  {
    gotError = true;
    momException.exception = L"TimeRegulationWasNotEnabled";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = L"disableTimeRegulation";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomEnableAsynchronousDelivery::MomEnableAsynchronousDelivery(GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomEnableAsynchronousDelivery::~MomEnableAsynchronousDelivery(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomEnableAsynchronousDelivery::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"EnableAsynchronousDelivery";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.enableAsynchronousDelivery();
  }
  catch(GeRtiFactory::AsynchronousDeliveryAlreadyEnabled &)
  {
    gotError = true;
    momException.exception = L"AsynchronousDeliveryAlreadyEnabled";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = L"enableAsynchronousDelivery";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomEnableTimeConstrained::MomEnableTimeConstrained(GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomEnableTimeConstrained::~MomEnableTimeConstrained(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomEnableTimeConstrained::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"EnableTimeConstrained";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.enableTimeConstrained();
  }
  catch(GeRtiFactory::TimeConstrainedAlreadyEnabled &)
  {
    gotError = true;
    momException.exception = L"TimeConstrainedAlreadyEnabled";
  }
  catch(GeRtiFactory::EnableTimeConstrainedPending &)
  {
    gotError = true;
    momException.exception = L"EnableTimeConstrainedPending";
  }
  catch(GeRtiFactory::TimeAdvanceAlreadyInProgress &)
  {
    gotError = true;
    momException.exception = L"TimeAdvanceAlreadyInProgress";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = L"enableTimeConstrained";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

GERTICO::MomEnableTimeRegulation::MomEnableTimeRegulation(GERTICO::GeRtiLogicalTimeInterval *theLookahead, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  lookahead = theLookahead;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomEnableTimeRegulation::~MomEnableTimeRegulation(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomEnableTimeRegulation::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"EnableTimeRegulation";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.enableTimeRegulation(*lookahead);
  }
  catch(GeRtiFactory::TimeRegulationAlreadyEnabled &)
  {
    gotError = true;
    momException.exception = L"TimeRegulationAlreadyEnabled";
  }
  catch(GeRtiFactory::EnableTimeRegulationPending &)
  {
    gotError = true;
    momException.exception = L"EnableTimeRegulationPending";
  }
  catch(GeRtiFactory::TimeAdvanceAlreadyInProgress &)
  {
    gotError = true;
    momException.exception = L"TimeAdvanceAlreadyInProgress";
  }
  catch(GeRtiFactory::InvalidFederationTime &)
  {
    gotError = true;
    momException.exception = L"InvalidFederationTime";
  }
  catch(GeRtiFactory::InvalidLookahead &)
  {
    gotError = true;
    momException.exception = L"InvalidLookahead";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = L"enableTimeRegulation";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomFederateRestoreComplete::MomFederateRestoreComplete(CORBA::Boolean &theBoolean, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  successIndicator = theBoolean;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomFederateRestoreComplete::~MomFederateRestoreComplete(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomFederateRestoreComplete::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"FederateRestoreComplete";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.federateRestoreComplete(successIndicator);
  }
  catch(GeRtiFactory::RestoreNotRequested &)
  {
    gotError = true;
    momException.exception = L"RestoreNotRequested";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = L"federateRestoreComplete";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomFederateSaveBegun::MomFederateSaveBegun(GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomFederateSaveBegun::~MomFederateSaveBegun(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomFederateSaveBegun::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"FederateSaveBegun";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.federateSaveBegun();
  }
  catch(GeRtiFactory::SaveNotInitiated &)
  {
    gotError = true;
    momException.exception = L"SaveNotInitiated";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = L"federateSaveBegun";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomFederateSaveComplete::MomFederateSaveComplete(CORBA::Boolean &theSuccessIndicator, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  successIndicator = theSuccessIndicator;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomFederateSaveComplete::~MomFederateSaveComplete(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomFederateSaveComplete::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"FederateSaveComplete";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.federateSaveComplete(successIndicator);
  }
  catch(GeRtiFactory::SaveNotInitiated &)
  {
    gotError = true;
    momException.exception = L"SaveNotInitiated";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = L"federateSaveComplete";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomFlushQueueRequest::MomFlushQueueRequest(GERTICO::GeRtiFedTime *theFederationTime, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  federationTime = theFederationTime;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomFlushQueueRequest::~MomFlushQueueRequest(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomFlushQueueRequest::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"FlushQueueRequest";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.flushQueueRequest(*federationTime);
  }
  catch(GeRtiFactory::InvalidFederationTime &)
  {
    gotError = true;
    momException.exception = L"InvalidFederationTime";
  }
  catch(GeRtiFactory::FederationTimeAlreadyPassed &)
  {
    gotError = true;
    momException.exception = L"FederationTimeAlreadyPassed";
  }
  catch(GeRtiFactory::TimeAdvanceAlreadyInProgress &)
  {
    gotError = true;
    momException.exception = L"TimeAdvanceAlreadyInProgress";
  }
  catch(GeRtiFactory::EnableTimeRegulationPending &)
  {
    gotError = true;
    momException.exception = L"EnableTimeRegulationPending";
  }
  catch(GeRtiFactory::EnableTimeConstrainedPending &)
  {
    gotError = true;
    momException.exception = L"EnableTimeConstrainedPending";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = L"flushQueueRequest";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomLocalDeleteObjectInstance::MomLocalDeleteObjectInstance(GeRtiFactory::GeRtiHandle const &theObjectHandle, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  objectHandle = theObjectHandle;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomLocalDeleteObjectInstance::~MomLocalDeleteObjectInstance(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomLocalDeleteObjectInstance::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"LocalDeleteObjectInstance";
  bool gotError = false;

  try
  {
    geRtiSender.localDeleteObjectInstance(objectHandle);
  }
  catch(GeRtiFactory::ObjectNotKnown &)
  {
    gotError = true;
    momException.exception = L"ObjectNotKnown";
  }
  catch(GeRtiFactory::FederateOwnsAttributes &)
  {
    gotError = true;
    momException.exception = L"FederateOwnsAttributes";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    GERTICO::MomReportServiceInvocation momReportServiceInvocation;
    wchar_t wc[128];

    momReportServiceInvocation.service = L"localDeleteObjectInstance";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    swprintf(wc, 128, L"%d", objectHandle);
    momReportServiceInvocation.suppliedArguments = wc;
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomModifyLookahead::MomModifyLookahead(GERTICO::GeRtiLogicalTimeInterval *theLookahead, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  lookahead = theLookahead;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomModifyLookahead::~MomModifyLookahead(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomModifyLookahead::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"ModifyLookahead";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.modifyLookahead(*lookahead);
  }
  catch(GeRtiFactory::InvalidLookahead &)
  {
    gotError = true;
    momException.exception = L"InvalidLookahead";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = L"modifyLookahead";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomNextEventRequest::MomNextEventRequest(GERTICO::GeRtiFedTime *theFederationTime, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  federationTime = theFederationTime;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomNextEventRequest::~MomNextEventRequest(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomNextEventRequest::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"NextEventRequest";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.nextEventRequest(*federationTime);
  }
  catch(GeRtiFactory::InvalidFederationTime &)
  {
    gotError = true;
    momException.exception = L"InvalidFederationTime";
  }
  catch(GeRtiFactory::FederationTimeAlreadyPassed &)
  {
    gotError = true;
    momException.exception = L"FederationTimeAlreadyPassed";
  }
  catch(GeRtiFactory::TimeAdvanceAlreadyInProgress &)
  {
    gotError = true;
    momException.exception = L"TimeAdvanceAlreadyInProgress";
  }
  catch(GeRtiFactory::EnableTimeRegulationPending &)
  {
    gotError = true;
    momException.exception = L"EnableTimeRegulationPending";
  }
  catch(GeRtiFactory::EnableTimeConstrainedPending &)
  {
    gotError = true;
    momException.exception = L"EnableTimeConstrainedPending";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = L"nextEventRequest";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomNextEventRequestAvailable::MomNextEventRequestAvailable(GERTICO::GeRtiFedTime *theFederationTime, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  federateTime = theFederationTime;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomNextEventRequestAvailable::~MomNextEventRequestAvailable(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomNextEventRequestAvailable::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"NextEventRequestAvailable";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.nextEventRequestAvailable(*federateTime);
  }
  catch(GeRtiFactory::InvalidFederationTime &)
  {
    gotError = true;
    momException.exception = L"InvalidFederationTime";
  }
  catch(GeRtiFactory::FederationTimeAlreadyPassed &)
  {
    gotError = true;
    momException.exception = L"FederationTimeAlreadyPassed";
  }
  catch(GeRtiFactory::TimeAdvanceAlreadyInProgress &)
  {
    gotError = true;
    momException.exception = L"TimeAdvanceAlreadyInProgress";
  }
  catch(GeRtiFactory::EnableTimeRegulationPending &)
  {
    gotError = true;
    momException.exception = L"EnableTimeRegulationPending";
  }
  catch(GeRtiFactory::EnableTimeConstrainedPending &)
  {
    gotError = true;
    momException.exception = L"EnableTimeConstrainedPending";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = L"nextEventRequestAvailable";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomPublishInteractionClass::MomPublishInteractionClass(const GeRtiFactory::GeRtiHandle &theInteractionClass, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  interactionClass = theInteractionClass;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomPublishInteractionClass::~MomPublishInteractionClass(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomPublishInteractionClass::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"PublishInteractionClass";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.publishInteractionClass(interactionClass);
  }
  catch(GeRtiFactory::InteractionClassNotDefined &)
  {
    gotError = true;
    momException.exception = L"InteractionClassNotDefined";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = L"publishInteractionClass";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomPublishObjectClass::MomPublishObjectClass(const GeRtiFactory::GeRtiHandle &theObjectClass, const GeRtiFactory::Handles &theAttributes, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  objectClass = theObjectClass;
  attributes = theAttributes;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomPublishObjectClass::~MomPublishObjectClass(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomPublishObjectClass::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"PublishObjectClass";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.publishObjectClass(objectClass, attributes);
  }
  catch(GeRtiFactory::ObjectClassNotDefined &)
  {
    gotError = true;
    momException.exception = L"ObjectClassNotDefined";
  }
  catch(GeRtiFactory::AttributeNotDefined &)
  {
    gotError = true;
    momException.exception = L"AttributeNotDefined";
  }
  catch(GeRtiFactory::OwnershipAcquisitionPending &)
  {
    gotError = true;
    momException.exception = L"OwnershipAcquisitionPending";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = L"publishObjectClass";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomResignFederationExecution::MomResignFederationExecution(GeRtiFactory::ResignAction &theResignAction, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  resignAction = theResignAction;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomResignFederationExecution::~MomResignFederationExecution(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomResignFederationExecution::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"ResignFederationExecution";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;
  bool stillConnected = true;

  try
  {
    geRtiSender.resignFederationExecution(resignAction);
    stillConnected = false;
  }
  catch(GeRtiFactory::FederateOwnsAttributes &)
  {
    gotError = true;
    momException.exception = L"FederateOwnsAttributes";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::InvalidResignAction &)
  {
    gotError = true;
    momException.exception = L"InvalidResignAction";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    if (stillConnected)
    {
      geRtiSender.sendReportException(momException);
    }
  }

  if (stillConnected)
  {
    if (geRtiSender.checkReportServiceInvocation())
    {
      momReportServiceInvocation.service = L"resignFederationExecution";
      momReportServiceInvocation.initiatorEnum = RtiEnum;
      if (gotError)
      {
        momReportServiceInvocation.successIndicator = false;
      }
      else
      {
        momReportServiceInvocation.successIndicator = true;
      }
      geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
    }
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomSubscribeInteractionClass::MomSubscribeInteractionClass(const GeRtiFactory::GeRtiHandle &theInteractionClass, const CORBA::Boolean &theActive, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  interactionClass = theInteractionClass;
  active = theActive;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomSubscribeInteractionClass::~MomSubscribeInteractionClass(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomSubscribeInteractionClass::execute(void)
{
  CORBA::Boolean activeCorba;
  GERTICO::MomException momException;
  momException.service = L"SubscribeInteractionClass";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;


  if (active)
  {
    activeCorba = 1;
  }
  else
  {
    activeCorba = 0;
  }

  try
  {
    geRtiSender.subscribeInteractionClass(interactionClass, activeCorba);
  }
  catch(GeRtiFactory::InteractionClassNotDefined &)
  {
    gotError = true;
    momException.exception = L"InteractionClassNotDefined";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::FederateLoggingServiceCalls &)
  {
    gotError = true;
    momException.exception = L"FederateLoggingServiceCalls";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = L"subscribeInteractionClass";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomSubscribeObjectClassAttributes::MomSubscribeObjectClassAttributes(const GeRtiFactory::GeRtiHandle &theObjectClass, const GeRtiFactory::Handles &theAttributes, const CORBA::Boolean &theActive, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  active = theActive;
  attributes = theAttributes;
  objectClass = theObjectClass;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomSubscribeObjectClassAttributes::~MomSubscribeObjectClassAttributes(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomSubscribeObjectClassAttributes::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"SubscribeObjectClassAttributes";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.subscribeObjectClassAttributes(objectClass, attributes, active);
  }
  catch(GeRtiFactory::ObjectClassNotDefined &)
  {
    gotError = true;
    momException.exception = L"ObjectClassNotDefined";
  }
  catch(GeRtiFactory::AttributeNotDefined &)
  {
    gotError = true;
    momException.exception = L"AttributeNotDefined";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = L"subscribeObjectClassAttributes";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomSynchronizationPointAchieved::MomSynchronizationPointAchieved(const std::wstring &theLabel, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  label = theLabel;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomSynchronizationPointAchieved::~MomSynchronizationPointAchieved(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomSynchronizationPointAchieved::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"SynchronizationPointAchieved";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.synchronizationPointAchieved(label.c_str());
  }
  catch(GeRtiFactory::SynchronizationPointLabelWasNotAnnounced &)
  {
    gotError = true;
    momException.exception = L"SynchronizationPointLabelWasNotAnnounced";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = L"synchronizationPointAchieved";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomTimeAdvanceRequest::MomTimeAdvanceRequest(GERTICO::GeRtiFedTime *theFederationTime, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  federationTime = theFederationTime;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomTimeAdvanceRequest::~MomTimeAdvanceRequest(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomTimeAdvanceRequest::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"TimeAdvanceRequest";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.timeAdvanceRequest(*federationTime);
  }
  catch(GeRtiFactory::InvalidFederationTime &)
  {
    gotError = true;
    momException.exception = L"InvalidFederationTime";
  }
  catch(GeRtiFactory::FederationTimeAlreadyPassed &)
  {
    gotError = true;
    momException.exception = L"FederationTimeAlreadyPassed";
  }
  catch(GeRtiFactory::TimeAdvanceAlreadyInProgress &)
  {
    gotError = true;
    momException.exception = L"TimeAdvanceAlreadyInProgress";
  }
  catch(GeRtiFactory::EnableTimeRegulationPending &)
  {
    gotError = true;
    momException.exception = L"EnableTimeRegulationPending";
  }
  catch(GeRtiFactory::EnableTimeConstrainedPending &)
  {
    gotError = true;
    momException.exception = L"EnableTimeConstrainedPending";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = L"timeAdvanceRequest";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomTimeAdvanceRequestAvailable::MomTimeAdvanceRequestAvailable(GERTICO::GeRtiFedTime *theFederationTime, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  federationTime = theFederationTime;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomTimeAdvanceRequestAvailable::~MomTimeAdvanceRequestAvailable(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomTimeAdvanceRequestAvailable::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"TimeAdvanceRequestAvailable";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.timeAdvanceRequestAvailable(*federationTime);
  }
  catch(GeRtiFactory::InvalidFederationTime &)
  {
    gotError = true;
    momException.exception = L"InvalidFederationTime";
  }
  catch(GeRtiFactory::FederationTimeAlreadyPassed &)
  {
    gotError = true;
    momException.exception = L"FederationTimeAlreadyPassed";
  }
  catch(GeRtiFactory::TimeAdvanceAlreadyInProgress &)
  {
    gotError = true;
    momException.exception = L"TimeAdvanceAlreadyInProgress";
  }
  catch(GeRtiFactory::EnableTimeRegulationPending &)
  {
    gotError = true;
    momException.exception = L"EnableTimeRegulationPending";
  }
  catch(GeRtiFactory::EnableTimeConstrainedPending &)
  {
    gotError = true;
    momException.exception = L"EnableTimeConstrainedPending";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = L"timeAdvanceRequestAvailable";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomUnconditionalAttributeOwnershipDivestiture::MomUnconditionalAttributeOwnershipDivestiture(GeRtiFactory::GeRtiHandle const &theObjectHandle, GeRtiFactory::Handles const &theAttributes, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  objectHandle = theObjectHandle;
  attributes = theAttributes;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomUnconditionalAttributeOwnershipDivestiture::~MomUnconditionalAttributeOwnershipDivestiture(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomUnconditionalAttributeOwnershipDivestiture::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"UnconditionalAttributeOwnershipDivestiture";
  bool gotError = false;

  try
  {
    geRtiSender.unconditionalAttributeOwnershipDivestiture(objectHandle, attributes);
  }
  catch(GeRtiFactory::ObjectNotKnown &)
  {
    gotError = true;
    momException.exception = L"ObjectNotKnown";
  }
  catch(GeRtiFactory::AttributeNotDefined &)
  {
    gotError = true;
    momException.exception = L"AttributeNotDefined";
  }
  catch(GeRtiFactory::AttributeNotOwned &)
  {
    gotError = true;
    momException.exception = L"AttributeNotOwned";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    GERTICO::MomReportServiceInvocation momReportServiceInvocation;
    wchar_t wc[128];

    momReportServiceInvocation.service = L"unconditionalAttributeOwnershipDivestiture";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    swprintf(wc, 128, L"%d", objectHandle);
    momReportServiceInvocation.suppliedArguments = wc;
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomUnpublishInteractionClass::MomUnpublishInteractionClass(const GeRtiFactory::GeRtiHandle &theInteractionClass, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  interactionClass = theInteractionClass;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomUnpublishInteractionClass::~MomUnpublishInteractionClass(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomUnpublishInteractionClass::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"UnpublishInteractionClass";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.unpublishInteractionClass(interactionClass);
  }
  catch(GeRtiFactory::InteractionClassNotDefined &)
  {
    gotError = true;
    momException.exception = L"InteractionClassNotDefined";
  }
  catch(GeRtiFactory::InteractionClassNotPublished &)
  {
    gotError = true;
    momException.exception = L"InteractionClassNotPublished";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = L"unpublishInteractionClass";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomUnpublishObjectClass::MomUnpublishObjectClass(const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  objectClass = theObjectClass;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomUnpublishObjectClass::~MomUnpublishObjectClass(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomUnpublishObjectClass::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"UnpublishObjectClass";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.unpublishObjectClass(objectClass);
  }
  catch(GeRtiFactory::ObjectClassNotDefined &)
  {
    gotError = true;
    momException.exception = L"ObjectClassNotDefined";
  }
  catch(GeRtiFactory::ObjectClassNotPublished &)
  {
    gotError = true;
    momException.exception = L"ObjectClassNotPublished";
  }
  catch(GeRtiFactory::OwnershipAcquisitionPending &)
  {
    gotError = true;
    momException.exception = L"OwnershipAcquisitionPending";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = L"unpublishObjectClass";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomUnsubscribeInteractionClass::MomUnsubscribeInteractionClass(const GeRtiFactory::GeRtiHandle &theInteractionClass, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  interactionClass = theInteractionClass;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomUnsubscribeInteractionClass::~MomUnsubscribeInteractionClass(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomUnsubscribeInteractionClass::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"UnsubscribeInteractionClass";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.unsubscribeInteractionClass(interactionClass);
  }
  catch(GeRtiFactory::InteractionClassNotDefined &)
  {
    gotError = true;
    momException.exception = L"InteractionClassNotDefined";
  }
  catch(GeRtiFactory::InteractionClassNotSubscribed &)
  {
    gotError = true;
    momException.exception = L"InteractionClassNotSubscribed";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = L"unsubscribeInteractionClass";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomUnsubscribeObjectClass::MomUnsubscribeObjectClass(const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  objectClass = theObjectClass;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomUnsubscribeObjectClass::~MomUnsubscribeObjectClass(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomUnsubscribeObjectClass::execute(void)
{
  GERTICO::MomException momException;
  momException.service = L"UnsubscribeObjectClass";
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.unsubscribeObjectClass(objectClass);
  }
  catch(GeRtiFactory::ObjectClassNotDefined &)
  {
    gotError = true;
    momException.exception = L"ObjectClassNotDefined";
  }
  catch(GeRtiFactory::ObjectClassNotSubscribed &)
  {
    gotError = true;
    momException.exception = L"ObjectClassNotSubscribed";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momException.exception = L"FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momException.exception = L"SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momException.exception = L"RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momException.exception = L"RTIinternalError";
  }

  if (gotError)
  {
    geRtiSender.sendReportException(momException);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = L"unsubscribeObjectClass";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ManagementObjectModelLRC::ManagementObjectModelLRC(GERTICO::FederateDB &theFederateDB, GERTICO::GeRtiSender *theGeRtiSender, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory, GERTICO::EventMarket &theEventMarket, GERTICO::ReceiverLRC &theReceiverLRC, ACE_Semaphore &thePs) : ps(thePs), eventMarket(theEventMarket), federateDB(theFederateDB), geRtiFedTimeFactory(theGeRtiFedTimeFactory), geRtiLogicalTimeIntervalFactory(theGeRtiLogicalTimeIntervalFactory), receiverLRC(theReceiverLRC)
{
  geRtiSender = theGeRtiSender;
  serviceReporting = false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ManagementObjectModelLRC::~ManagementObjectModelLRC(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::ManagementObjectModelLRC::checkReportServiceInvocation(void)
{
  return serviceReporting;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::adjustModifyAttributeState(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong len;
  GERTICO::AttributeInfo *attributeInfo;
  GERTICO::AttributeStatus status;
  GERTICO::RegisteredObject *registeredObject;
  long attribute;
  unsigned long federate;
  char *cptr;
  long objectInstance;
  long l;

  len = theData.length();
  for (i = 0; i < len; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theData[i].value);
      sscanf(cptr, "%lu", &federate);
      delete[] cptr;
      continue;
    }
    if (theData[i].id == managerFederateAdjustModifyAttributeStateObjectInstance)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(objectInstance, theData[i].value);
      continue;
    }
    if (theData[i].id == managerFederateAdjustModifyAttributeStateAttribute)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(attribute, theData[i].value);
      continue;
    }
    if (theData[i].id == managerFederateAdjustModifyAttributeStateAttributeState)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      if (l)
      {
        status = owned;
      }
      else
      {
        status = unowned;
      }
      continue;
    }
  }

  try
  {
    registeredObject = federateDB.objectManagementLRC->getObject(objectInstance);
    if (registeredObject == NULL)
    {
      std::cout << "OBJECT NOT FOUND!!!!!" << std::endl;
      return;
    }
    attributeInfo = registeredObject->getAttribute(attribute);
  }
  catch(GeRtiFactory::AttributeNotDefined &)
  {
//    attributeInfo = new AttributeInfo(federateDB.federate, unowned);
//    registeredObject->addAttribute(attribute, attributeInfo);
    return;
  }
  catch(...)
  {
    return;
  }

  attributeInfo->setStatusFlag(status);
  if (status == owned)
  {
    attributeInfo->setStatusOwned(federateDB.federate);
  }
  else
  {
    attributeInfo->setStatusOwned(0);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::adjustSetServiceReporting(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong len;
  long l;

  len = theData.length();
  for (i = 0; i < len; i++)
  {
    if (theData[i].id == managerFederateAdjustSetServiceReportingState)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      continue;
    }
  }

  if (l)
  {
    serviceReporting = true;
  }
  else
  {
    serviceReporting = false;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::doMomRequest(GeRtiFactory::GeRtiHandle theRequest, const GeRtiFactory::HandleValues &data)
{
  // Federate Adjust.
//  if (theRequest == managerFederateAdjustModifySetTiming)
//  {
//    Handled in gerti
//  }

  if (theRequest == managerFederateAdjustModifyAttributeState)
  {
    adjustModifyAttributeState(data);
  }

  if (theRequest == managerFederateAdjustSetServiceReporting)
  {
    adjustSetServiceReporting(data);
  }

  if (theRequest == managerFederateAdjustSetExceptionLogging)
  {
  }

  // Federate Request - handled in gerti.

  // Federate Report.
  if (theRequest == managerFederateReportException)
  {
  }

  if (theRequest == managerFederateReportServiceInvocation)
  {
  }

  // Federate service.
  if (theRequest == managerFederateServiceResignFederationExecution)
  {
    serviceResignFederationExecution(data);
  }

  if (theRequest == managerFederateServiceSynchronizationPointAchieved)
  {
    serviceSynchronizationPointAchieved(data);
  }

  if (theRequest == managerFederateServiceFederateSaveBegun)
  {
    serviceFederateSaveBegun(data);
  }

  if (theRequest == managerFederateServiceFederateSaveComplete)
  {
    serviceFederateSaveComplete(data);
  }

  if (theRequest == managerFederateServiceFederateRestoreComplete)
  {
    serviceFederateRestoreComplete(data);
  }

  if (theRequest == managerFederateServicePublishObjectClassAttributes)
  {
    servicePublishObjectClass(data);
  }

  if (theRequest == managerFederateServiceUnpublishObjectClassAttributes)
  {
    serviceUnpublishObjectClass(data);
  }

  if (theRequest == managerFederateServicePublishInteractionClass)
  {
    servicePublishInteractionClass(data);
  }

  if (theRequest == managerFederateServiceUnpublishInteractionClass)
  {
    serviceUnpublishInteractionClass(data);
  }

  if (theRequest == managerFederateServiceSubscribeObjectClassAttributes)
  {
    serviceSubscribeObjectClassAttributes(data);
  }

  if (theRequest == managerFederateServiceUnsubscribeObjectClassAttributes)
  {
    serviceUnsubscribeObjectClass(data);
  }

  if (theRequest == managerFederateServiceSubscribeInteractionClass)
  {
    serviceSubscribeInteractionClass(data);
  }

  if (theRequest == managerFederateServiceUnsubscribeInteractionClass)
  {
    serviceUnsubscribeInteractionClass(data);
  }

  if (theRequest == managerFederateServiceDeleteObjectInstance)
  {
    serviceDeleteObjectInstance(data);
  }

  if (theRequest == managerFederateServiceLocalDeleteObjectInstance)
  {
    serviceLocalDeleteObjectInstance(data);
  }

//  if (theRequest == managerFederateServiceUnconditionalAttributeOwnershipDivestiture)
//  {
//    serviceUnconditionalAttributeOwnershipDivestiture(data);
//  }

  if (theRequest == managerFederateServiceEnableTimeRegulation)
  {
    serviceEnableTimeRegulation(data);
  }

  if (theRequest == managerFederateServiceDisableTimeRegulation)
  {
    serviceDisableTimeRegulation(data);
  }

  if (theRequest == managerFederateServiceEnableTimeConstrained)
  {
    serviceEnableTimeConstrained(data);
  }

  if (theRequest == managerFederateServiceDisableTimeConstrained)
  {
    serviceDisableTimeConstrained(data);
  }

  if (theRequest == managerFederateServiceEnableAsynchronousDelivery)
  {
    serviceEnableAsynchronousDelivery(data);
  }

  if (theRequest == managerFederateServiceDisableAsynchronousDelivery)
  {
    serviceDisableAsynchronousDelivery(data);
  }

  if (theRequest == managerFederateServiceModifyLookahead)
  {
    serviceModifyLookahead(data);
  }

  if (theRequest == managerFederateServiceTimeAdvanceRequest)
  {
    serviceTimeAdvanceRequest(data);
  }

  if (theRequest == managerFederateServiceTimeAdvanceRequestAvailable)
  {
    serviceTimeAdvanceRequestAvailable(data);
  }

  if (theRequest == managerFederateServiceNextMessageRequest)
  {
    serviceNextEventRequest(data);
  }

  if (theRequest == managerFederateServiceNextMessageRequestAvailable)
  {
    serviceNextEventRequestAvailable(data);
  }

  if (theRequest == managerFederateServiceFlushQueueRequest)
  {
    serviceFlushQueueRequest(data);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::getMomData(GeRtiFactory::GeRtiHandle theRequest, const GeRtiFactory::Handles & theAttributes, GeRtiFactory::HandleValues_out data)
{
  CORBA::ULong i;
  CORBA::ULong ind = 0;
  CORBA::ULong len = theAttributes.length();
  long l;

  data = new GeRtiFactory::HandleValues();

  if (theRequest == managerFederateObjectClass)
  {
    data->length(len);
    data->length(ind);

    ind = 0;
    for (i = 0; i < len; i++)
    {
      if (theAttributes[i] == managerFederateFederateHandle)
      {
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAhandle(data[ind], managerFederateFederateHandle, federateDB.federate);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateFederateType)
      {
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAunicodeWstring(data[ind], managerFederateFederateType, federateDB.federateType);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateFederateHost)
      {
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAunicodeWstring(data[ind], managerFederateFederateHost, federateDB.hostName);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateRTIversion)
      {
        static char buf[512];
        std::wstring ws;

        sprintf(buf, "%s.%s", gerticoVersion, Revision);
        GERTICO::Mapper::mapWstringFromChar(ws, buf);

        data->length(ind + 1);
        GERTICO::Mapper::mapHLAunicodeWstring(data[ind], managerFederateRTIversion, ws);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateFDDid)
      {
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAunicodeWstring(data[ind], managerFederateFDDid, federateDB.FEDid);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateTimeConstrained)
      {
        bool b;
        if (federateDB.timeManagementLRC->isTimeConstrained())
        {
          b = true;
        }
        else
        {
          b = false;
        }
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAboolean(data[ind], managerFederateTimeConstrained, b);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateTimeRegulating)
      {
        bool b;
        if (federateDB.timeManagementLRC->isTimeRegulation())
        {
          b = true;
        }
        else
        {
          b = false;
        }
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAboolean(data[ind], managerFederateTimeRegulating, b);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateAsynchronousDelivery)
      {
        bool b;
        if (receiverLRC.getAsynchronousDelivery())
        {
          b = true;
        }
        else
        {
          b = false;
        }
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAboolean(data[ind], managerFederateAsynchronousDelivery, b);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateFederateState)
      {
        GERTICO::FederateState federateState = Running;

        receiverLRC.getFederateState(federateState);
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAfederateState(data[ind], managerFederateFederateState, federateState);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateTimeManagerState)
      {
        bool b;
        if (federateDB.timeManagementLRC->isTimeAdvancing())
        {
          b = true;
        }
        else
        {
          b = false;
        }
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAtimeManagerState(data[ind], managerFederateTimeManagerState, b);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateLogicalTime)
      {
        std::auto_ptr<GERTICO::GeRtiFedTime> t(geRtiFedTimeFactory.makeZero());

        federateDB.timeManagementLRC->queryLogicalTime(*t);
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAlogicalTime(data[ind], managerFederateLogicalTime, t);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateLookahead)
      {
        GERTICO::GeRtiLogicalTimeInterval *t;

        t = geRtiLogicalTimeIntervalFactory.makeZero();
        federateDB.timeManagementLRC->queryLookahead(*t);
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAlogicalTimeInterval(data[ind], managerFederateLookahead, *t);
        delete t;
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateGALT)
      {
        std::auto_ptr<GERTICO::GeRtiFedTime> t(geRtiFedTimeFactory.makeZero());

        federateDB.timeManagementLRC->queryGALT(*t);
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAlogicalTime(data[ind], managerFederateGALT, t);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateLITS)
      {
        std::auto_ptr<GERTICO::GeRtiFedTime> t(geRtiFedTimeFactory.makeZero());

        geRtiSender->queryMinNextEventTime(*t);
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAlogicalTime(data[ind], managerFederateLITS, t);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateROlength)
      {
        l = receiverLRC.getROlength();
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAinteger32BE(data[ind], managerFederateROlength, l);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateTSOlength)
      {
        l = receiverLRC.getTSOlength();
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAinteger32BE(data[ind], managerFederateTSOlength, l);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateReflectionsReceived)
      {
        l = receiverLRC.getReflectionsReceived();
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAinteger32BE(data[ind], managerFederateReflectionsReceived, l);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateUpdatesSent)
      {
        l = eventMarket.getUpdatesSent();
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAinteger32BE(data[ind], managerFederateUpdatesSent, l);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateInteractionsReceived)
      {
        l = receiverLRC.getInteractionsReceived();
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAinteger32BE(data[ind], managerFederateInteractionsReceived, l);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateInteractionsSent)
      {
        l = eventMarket.getInteractionsSent();
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAinteger32BE(data[ind], managerFederateInteractionsSent, l);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateObjectInstancesThatCanBeDeleted)
      {
        GeRtiFactory::GeRtiHandle privilegeToDeleteId;
        GERTICO::HandleSet objectIds;

        privilegeToDeleteId = federateDB.runTimeObjectDB->getPrivilegeToDeleteId();
        federateDB.registeredObjectsHolder.getOwnedObjectIds(federateDB.federate, objectIds, privilegeToDeleteId);
        l = objectIds.size();
        objectIds.clear();
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAinteger32BE(data[ind], managerFederateObjectInstancesThatCanBeDeleted, l);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateObjectInstancesUpdated)
      {
        l = federateDB.getObjectsUpdated();
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAinteger32BE(data[ind], managerFederateObjectInstancesUpdated, l);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateObjectInstancesReflected)
      {
        l = federateDB.getObjectsReflected();
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAinteger32BE(data[ind], managerFederateObjectInstancesReflected, l);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateObjectInstancesDeleted)
      {
        l = federateDB.getObjectsDeleted();
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAinteger32BE(data[ind], managerFederateObjectInstancesDeleted, l);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateObjectInstancesRemoved)
      {
        l = federateDB.getObjectsRemoved();
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAinteger32BE(data[ind], managerFederateObjectInstancesRemoved, l);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateObjectInstancesRegistered)
      {
        l = federateDB.getObjectsRegistered();
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAinteger32BE(data[ind], managerFederateObjectInstancesRegistered, l);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateObjectInstancesDiscovered)
      {
        l = federateDB.getObjectsDiscovered();
        data->length(ind + 1);
        GERTICO::Mapper::mapHLAinteger32BE(data[ind], managerFederateObjectInstancesDiscovered, l);
        ind += 1;
        continue;
      }
    // managerFederateTimeGrantedTime;
    // managerFederateTimetimeGrantedTime;
    }

    return;
  }

  if (theRequest == managerFederateReportReflectionsReceived)
  {
    data->length(6);

    ind = 0;
    for (i = 0; i < len; i++)
    {
      if (theAttributes[i] == managerInteractionFederateFederate)
      {
        GERTICO::Mapper::mapHLAhandle(data[ind], managerInteractionFederateFederate, federateDB.federate);
        GERTICO::Mapper::mapHLAhandle(data[ind + 3], managerInteractionFederateFederate, federateDB.federate);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateReportReflectionsReceivedTransportationType)
      {
        std::wstring hlaReliable = L"HLAreliable";
        GERTICO::Mapper::mapHLAunicodeWstring(data[ind], managerFederateReportReflectionsReceivedTransportationType, hlaReliable);
        std::wstring hlaBestEffort = L"HLAbestEffort";
        GERTICO::Mapper::mapHLAunicodeWstring(data[ind + 3], managerFederateReportReflectionsReceivedTransportationType, hlaBestEffort);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateReportReflectionsReceivedReflectCounts)
      {
        GERTICO::HandleMap reflections;

        receiverLRC.getReflectionsReceivedReliable(reflections);
        GERTICO::Mapper::mapHLAobjectClassBasedCounts(data[ind], managerFederateReportReflectionsReceivedReflectCounts, reflections);

        receiverLRC.getReflectionsReceivedBestEffort(reflections);
        GERTICO::Mapper::mapHLAobjectClassBasedCounts(data[ind + 3], managerFederateReportReflectionsReceivedReflectCounts, reflections);
        ind += 1;
        continue;
      }
    }
  }

  if (theRequest == managerFederateReportInteractionsReceived)
  {
    data->length(6);

    ind = 0;
    for (i = 0; i < len; i++)
    {
      if (theAttributes[i] == managerInteractionFederateFederate)
      {
        GERTICO::Mapper::mapHLAhandle(data[ind], managerInteractionFederateFederate, federateDB.federate);
        GERTICO::Mapper::mapHLAhandle(data[ind + 3], managerInteractionFederateFederate, federateDB.federate);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateReportInteractionsReceivedTransportationType)
      {
        std::wstring hlaReliable = L"HLAreliable";
        GERTICO::Mapper::mapHLAunicodeWstring(data[ind], managerFederateReportInteractionsReceivedTransportationType, hlaReliable);
        std::wstring hlaBestEffort = L"HLAbestEffort";
        GERTICO::Mapper::mapHLAunicodeWstring(data[ind + 3], managerFederateReportInteractionsReceivedTransportationType, hlaBestEffort);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateReportInteractionsReceivedInteractionCounts)
      {
        GERTICO::HandleMap reflections;

        receiverLRC.getInteractionsReceivedReliable(reflections);
        GERTICO::Mapper::mapHLAobjectClassBasedCounts(data[ind], managerFederateReportInteractionsReceivedInteractionCounts, reflections);

        receiverLRC.getInteractionsReceivedBestEffort(reflections);
        GERTICO::Mapper::mapHLAobjectClassBasedCounts(data[ind + 3], managerFederateReportInteractionsReceivedInteractionCounts, reflections);
        ind += 1;
        continue;
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::getOrderType(GeRtiFactory::GeRtiHandle &theOrderingType, char *theBuff)
{
  CORBA::ULong i;
  CORBA::ULong len;
  size_t size;

  size = strlen(theBuff);
  GERTICO::Mapper::mapULongSizet(len, size);
  for (i = 0; i < len; i++)
  {
    theBuff[i] = tolower(theBuff[i]);
  }

  if (strcmp(theBuff, "timestamp") == 0)
  {
    theOrderingType = 1;
  }
  else
  {
    theOrderingType = 0;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::getResignAction(GeRtiFactory::ResignAction &theResignAction, unsigned long const &theUlong)
{
  switch(theUlong)
  {
    case 1:
    {
      theResignAction = GeRtiFactory::unconditionallyDivestAttributes;
      break;
    }
    case 2:
    {
      theResignAction = GeRtiFactory::deleteObjects;
      break;
    }
    case 3:
    {
      theResignAction = GeRtiFactory::cancelPendingOwnershipAquisitions;
      break;
    }
    case 4:
    {
      theResignAction = GeRtiFactory::deleteObjectsThenDivest;
      break;
    }
    case 5:
    {
      theResignAction = GeRtiFactory::cancelThenDeleteThenDivest;
      break;
    }
    case 6:
    {
      theResignAction = GeRtiFactory::noAction;
      break;
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::ManagementObjectModelLRC::getTransportationType(GeRtiFactory::GeRtiHandle &theTransportationType, char *theBuff)
{
  CORBA::ULong i;
  CORBA::ULong len;
  size_t size;

  size = strlen(theBuff);
  GERTICO::Mapper::mapULongSizet(len, size);
  for (i = 0; i < len; i++)
  {
    theBuff[i] = tolower(theBuff[i]);
  }

  if (strcmp(theBuff, "best_effort") == 0)
  {
    theTransportationType = 1;
    return false;
  }
  if (strcmp(theBuff, "reliable") == 0)
  {
    theTransportationType = 0;
    return false;
  }

  return true;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::sendReportException(const GERTICO::MomException &theMomException)
{
  GERTICO::AttributeDatum interactionDatum;
  GeRtiFactory::HandleValues handleValues;
  GeRtiFactory::UserSuppliedTag userSuppliedTag;

  handleValues.length(3);

  GERTICO::Mapper::mapHLAhandle(handleValues[0], managerInteractionFederateFederate, federateDB.federate);

  GERTICO::Mapper::mapHandleValueFromWstring(handleValues[1], managerFederateReportExceptionService, theMomException.service);

  GERTICO::Mapper::mapHandleValueFromWstring(handleValues[2], managerFederateReportExceptionException, theMomException.exception);

  GERTICO::Mapper::mapUserSuppliedTag(userSuppliedTag, "MOM");

  if (federateDB.supportingServicesLRC->getInteractionAttributeDatum(managerFederateReportException, interactionDatum))
  {
    return;
  }

  if (federateDB.declarationManagementLRC->testInteractionSubscribers(managerFederateReportException))
  {
    eventMarket.addPushSupplierInteraction(managerFederateReportException, handleValues, userSuppliedTag, 0, interactionDatum);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::sendReportServiceInvocation(const GERTICO::MomReportServiceInvocation &theMomReportServiceInvocation)
{
  GERTICO::AttributeDatum interactionDatum;
  GeRtiFactory::HandleValues handleValues;
  GeRtiFactory::UserSuppliedTag userSuppliedTag;
  bool b;
  long l;

  handleValues.length(7);
  GERTICO::Mapper::mapHLAhandle(handleValues[0], managerInteractionFederateFederate, federateDB.federate);
  GERTICO::Mapper::mapHLAunicodeWstring(handleValues[1], managerFederateReportServiceInvocationService, theMomReportServiceInvocation.service);
  if (theMomReportServiceInvocation.successIndicator)
  {
    b = true;
  }
  else
  {
    b = false;
  }
  GERTICO::Mapper::mapHLAboolean(handleValues[2], managerFederateReportServiceInvocationSuccessIndicator, b);
  GERTICO::Mapper::mapHandleValueFromWstring(handleValues[3], managerFederateReportServiceInvocationSuppliedArguments, theMomReportServiceInvocation.suppliedArguments);
  GERTICO::Mapper::mapHandleValueFromWstring(handleValues[4], managerFederateReportServiceInvocationReturnedArguments, theMomReportServiceInvocation.returnedArguments);
  GERTICO::Mapper::mapHandleValueFromWstring(handleValues[5], managerFederateReportServiceInvocationException, theMomReportServiceInvocation.exception);
  l = theMomReportServiceInvocation.serialNumber;
  GERTICO::Mapper::mapHLAinteger32BE(handleValues[6], managerFederateReportServiceInvocationSerialNumber, l);
  // XX
  GERTICO::Mapper::mapUserSuppliedTag(userSuppliedTag, "MOM");

  if (federateDB.supportingServicesLRC->getInteractionAttributeDatum(managerFederateReportServiceInvocation, interactionDatum))
  {
    return;
  }

  if (federateDB.declarationManagementLRC->testInteractionSubscribers(managerFederateReportServiceInvocation))
  {
    eventMarket.addPushSupplierInteraction(managerFederateReportServiceInvocation, handleValues, userSuppliedTag, 0, interactionDatum);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceDeleteObjectInstance(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::GeRtiHandle objectHandle;
  GERTICO::GeRtiFedTime *federationTime;
  bool gotTime = false;
  std::string userSuppliedTag;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }

    if (theData[i].id == managerFederateServiceDeleteObjectInstanceObjectInstance)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      objectHandle = l;
      continue;
    }

    if (theData[i].id == managerFederateServiceDeleteObjectInstanceTag)
    {
// XXX     GERTICO::Mapper::mapHLAwstringFromOctetSequence(userSuppliedTag, theData[i].value);
      continue;
    }

    if (theData[i].id == managerFederateServiceDeleteObjectInstanceTimeStamp)
    {
      if (theData[i].value.length())
      {
        char *cPtr = NULL;
        gotTime = true;
        GERTICO::Mapper::mapOctetSequence(&cPtr, theData[i].value);
        federationTime = geRtiFedTimeFactory.decode(cPtr);
        delete []cPtr;
      }
      continue;
    }
  }

  if (gotTime)
  {
    GERTICO::MomDeleteObjectInstanceWithTime *momDeleteObjectInstanceWithTime;
    momDeleteObjectInstanceWithTime = new GERTICO::MomDeleteObjectInstanceWithTime(objectHandle, userSuppliedTag, federationTime, *geRtiSender);
    federateDB.momJobs.add(momDeleteObjectInstanceWithTime);
    ps.release();
  }
  else
  {
    GERTICO::MomDeleteObjectInstance *momDeleteObjectInstance;
    momDeleteObjectInstance = new GERTICO::MomDeleteObjectInstance(objectHandle, userSuppliedTag, *geRtiSender);
    federateDB.momJobs.add(momDeleteObjectInstance);
    ps.release();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceDisableAsynchronousDelivery(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomDisableAsynchronousDelivery *momDisableAsynchronousDelivery;
  GeRtiFactory::GeRtiHandle federate = 0;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }
  }

  momDisableAsynchronousDelivery = new GERTICO::MomDisableAsynchronousDelivery(*geRtiSender);
  federateDB.momJobs.add(momDisableAsynchronousDelivery);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceDisableTimeConstrained(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomDisableTimeConstrained *momDisableTimeConstrained;
  GeRtiFactory::GeRtiHandle federate = 0;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }
  }

  momDisableTimeConstrained = new GERTICO::MomDisableTimeConstrained(*geRtiSender);
  federateDB.momJobs.add(momDisableTimeConstrained);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceDisableTimeRegulation(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomDisableTimeRegulation *momDisableTimeRegulation;
  GeRtiFactory::GeRtiHandle federate = 0;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }
  }

  momDisableTimeRegulation = new GERTICO::MomDisableTimeRegulation(*geRtiSender);
  federateDB.momJobs.add(momDisableTimeRegulation);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceEnableAsynchronousDelivery(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomEnableAsynchronousDelivery *momEnableAsynchronousDelivery;
  GeRtiFactory::GeRtiHandle federate = 0;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }
  }

  momEnableAsynchronousDelivery = new GERTICO::MomEnableAsynchronousDelivery(*geRtiSender);
  federateDB.momJobs.add(momEnableAsynchronousDelivery);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceEnableTimeConstrained(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomEnableTimeConstrained *momEnableTimeConstrained;
  GeRtiFactory::GeRtiHandle federate = 0;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }
  }

  momEnableTimeConstrained = new GERTICO::MomEnableTimeConstrained(*geRtiSender);
  federateDB.momJobs.add(momEnableTimeConstrained);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceEnableTimeRegulation(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomEnableTimeRegulation *momEnableTimeRegulation;
  GeRtiFactory::GeRtiHandle federate = 0;
  GERTICO::GeRtiLogicalTimeInterval *lookahead;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }

    if (theData[i].id == managerFederateServiceEnableTimeRegulationLookahead)
    {
      char *cPtr = NULL;
      size_t len = 8; // NOT CORRECT FOR ALL CASES!

      GERTICO::Mapper::mapOctetSequence(&cPtr, theData[i].value);
      GERTICO::GeRtiEncodedLogicalTimeInterval *encodedLogicalTimeInterval = new GERTICO::GeRtiEncodedLogicalTimeIntervalI(cPtr, len);
      lookahead = geRtiLogicalTimeIntervalFactory.decode(*encodedLogicalTimeInterval);
      delete []cPtr;
      continue;
    }
  }

  momEnableTimeRegulation = new GERTICO::MomEnableTimeRegulation(lookahead, *geRtiSender);
  federateDB.momJobs.add(momEnableTimeRegulation);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceFederateRestoreComplete(const GeRtiFactory::HandleValues &theData)
{
  CORBA::Boolean successIndicator;
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomFederateRestoreComplete *momFederateRestoreComplete;
  GeRtiFactory::GeRtiHandle federate = 0;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }

    if (theData[i].id == managerFederateServiceFederateRestoreCompleteSuccessIndicator)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      if (l)
      {
        successIndicator = 1;
      }
      else
      {
        successIndicator = 0;
      }
      continue;
    }
  }

  momFederateRestoreComplete = new GERTICO::MomFederateRestoreComplete(successIndicator, *geRtiSender);
  federateDB.momJobs.add(momFederateRestoreComplete);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceFederateSaveBegun(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomFederateSaveBegun *momFederateSaveBegun;
  GeRtiFactory::GeRtiHandle federate = 0;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }
  }

  momFederateSaveBegun = new GERTICO::MomFederateSaveBegun(*geRtiSender);
  federateDB.momJobs.add(momFederateSaveBegun);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceFederateSaveComplete(const GeRtiFactory::HandleValues &theData)
{
  CORBA::Boolean successIndicator;
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomFederateSaveComplete *momFederateSaveComplete;
  GeRtiFactory::GeRtiHandle federate = 0;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }

    if (theData[i].id == managerFederateServiceFederateSaveCompleteSuccessIndicator)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      if (l)
      {
        successIndicator = 1;
      }
      else
      {
        successIndicator = 0;
      }
      continue;
    }
  }

  momFederateSaveComplete = new GERTICO::MomFederateSaveComplete(successIndicator, *geRtiSender);
  federateDB.momJobs.add(momFederateSaveComplete);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceFlushQueueRequest(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomFlushQueueRequest *momFlushQueueRequest;
  GeRtiFactory::GeRtiHandle federate = 0;
  GERTICO::GeRtiFedTime *federationTime;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }

    if (theData[i].id == managerFederateServiceFlushQueueRequestTimeStamp)
    {
      char *cPtr = NULL;
      GERTICO::Mapper::mapOctetSequence(&cPtr, theData[i].value);
      federationTime = geRtiFedTimeFactory.decode(cPtr);
      delete []cPtr;
      continue;
    }
  }

  momFlushQueueRequest = new GERTICO::MomFlushQueueRequest(federationTime, *geRtiSender);
  federateDB.momJobs.add(momFlushQueueRequest);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceLocalDeleteObjectInstance(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomLocalDeleteObjectInstance *momLocalDeleteObjectInstance;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::GeRtiHandle objectHandle;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }

    if (theData[i].id == managerFederateServiceLocalDeleteObjectInstanceObjectInstance)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      objectHandle = l;
      continue;
    }
  }

  momLocalDeleteObjectInstance = new GERTICO::MomLocalDeleteObjectInstance(objectHandle, *geRtiSender);
  federateDB.momJobs.add(momLocalDeleteObjectInstance);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceModifyLookahead(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomModifyLookahead *momModifyLookahead;
  GeRtiFactory::GeRtiHandle federate = 0;
  GERTICO::GeRtiLogicalTimeInterval *lookahead;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }

    if (theData[i].id == managerFederateServiceModifyLookaheadLookahead)
    {
      char *cPtr = NULL;
      size_t len = 8; // NOT CORRECT FOR ALL CASES!

      GERTICO::Mapper::mapOctetSequence(&cPtr, theData[i].value);
      GERTICO::GeRtiEncodedLogicalTimeInterval *encodedLogicalTimeInterval = new GERTICO::GeRtiEncodedLogicalTimeIntervalI(cPtr, len);
      lookahead = geRtiLogicalTimeIntervalFactory.decode(*encodedLogicalTimeInterval);
      delete []cPtr;
      continue;
    }
  }

  momModifyLookahead = new GERTICO::MomModifyLookahead(lookahead, *geRtiSender);
  federateDB.momJobs.add(momModifyLookahead);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceNextEventRequest(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomNextEventRequest *momNextEventRequest;
  GeRtiFactory::GeRtiHandle federate = 0;
  GERTICO::GeRtiFedTime *federationTime;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }

    if (theData[i].id == managerFederateServiceNextMessageRequestTimeStamp)
    {
      char *cPtr = NULL;
      GERTICO::Mapper::mapOctetSequence(&cPtr, theData[i].value);
      federationTime = geRtiFedTimeFactory.decode(cPtr);
      delete []cPtr;
      continue;
    }
  }

  momNextEventRequest = new GERTICO::MomNextEventRequest(federationTime, *geRtiSender);
  federateDB.momJobs.add(momNextEventRequest);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceNextEventRequestAvailable(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomNextEventRequestAvailable *momNextEventRequestAvailable;
  GeRtiFactory::GeRtiHandle federate = 0;
  GERTICO::GeRtiFedTime *federationTime;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }

    if (theData[i].id == managerFederateServiceNextMessageRequestAvailableTimeStamp)
    {
      char *cPtr = NULL;
      GERTICO::Mapper::mapOctetSequence(&cPtr, theData[i].value);
      federationTime = geRtiFedTimeFactory.decode(cPtr);
      delete []cPtr;
      continue;
    }
  }

  momNextEventRequestAvailable = new GERTICO::MomNextEventRequestAvailable(federationTime, *geRtiSender);
  federateDB.momJobs.add(momNextEventRequestAvailable);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::servicePublishInteractionClass(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomPublishInteractionClass *momPublishInteractionClass;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::GeRtiHandle interactionClass = 0;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }

    if (theData[i].id == managerFederateServicePublishInteractionClassInteractionClass)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      interactionClass = l;
      continue;
    }
  }

  momPublishInteractionClass = new GERTICO::MomPublishInteractionClass(interactionClass, *geRtiSender);
  federateDB.momJobs.add(momPublishInteractionClass);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::servicePublishObjectClass(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomPublishObjectClass *momPublishObjectClass;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::GeRtiHandle objectClass;
  GeRtiFactory::Handles attributes;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }

    if (theData[i].id == managerFederateServicePublishObjectClassObjectClass)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      objectClass = l;
      continue;
    }

    if (theData[i].id == managerFederateServicePublishObjectClassAttributeList)
    {
      GERTICO::Mapper::mapHLAAttributesFromOctetSequence(attributes, theData[i].value);
      continue;
    }
  }

  momPublishObjectClass = new GERTICO::MomPublishObjectClass(objectClass, attributes, *geRtiSender);
  federateDB.momJobs.add(momPublishObjectClass);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceResignFederationExecution(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomResignFederationExecution *momResignFederationExecution;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::ResignAction resignAction;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }

    if (theData[i].id == managerFederateServiceResignFederationExecutionResignAction)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      getResignAction(resignAction, l);
      continue;
    }
  }

  momResignFederationExecution = new GERTICO::MomResignFederationExecution(resignAction, *geRtiSender);
  federateDB.momJobs.add(momResignFederationExecution);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceSubscribeInteractionClass(const GeRtiFactory::HandleValues &theData)
{
  CORBA::Boolean active = false;
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomSubscribeInteractionClass *momSubscribeInteractionClass;
  GeRtiFactory::GeRtiHandle interactionClass = 0;
  GeRtiFactory::GeRtiHandle federate = 0;
  char *cptr;
  std::string activeStr;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }

    if (theData[i].id == managerFederateServiceSubscribeInteractionClassInteractionClass)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theData[i].value);
      sscanf(cptr, "%ld", &l);
      interactionClass = l;
      delete[] cptr;
      continue;
    }

    if (theData[i].id == managerFederateServiceSubscribeInteractionClassActive)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theData[i].value);
      activeStr = cptr;
      delete[] cptr;
      if (activeStr == "HLAtrue")
      {
        active = 1;
      }
      else
      {
        active = 0;
      }
      continue;
    }
  }

  momSubscribeInteractionClass = new GERTICO::MomSubscribeInteractionClass(interactionClass, active, *geRtiSender);
  federateDB.momJobs.add(momSubscribeInteractionClass);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceSubscribeObjectClassAttributes(const GeRtiFactory::HandleValues &theData)
{
  CORBA::Boolean active = 0;
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomSubscribeObjectClassAttributes *momSubscribeObjectClassAttributes;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::GeRtiHandle objectClass;
  GeRtiFactory::Handles attributes;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }

    if (theData[i].id == managerFederateServiceSubscribeObjectClassAttributesObjectClass)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      objectClass = l;
      continue;
    }

    if (theData[i].id == managerFederateServiceSubscribeObjectClassAttributesAttributeList)
    {
      GERTICO::Mapper::mapHLAAttributesFromOctetSequence(attributes, theData[i].value);
      continue;
    }

    if (theData[i].id == managerFederateServiceSubscribeObjectClassAttributesActive)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      if (l)
      {
        active = 1;
      }
      continue;
    }
  }

  momSubscribeObjectClassAttributes = new GERTICO::MomSubscribeObjectClassAttributes(objectClass, attributes, active, *geRtiSender);
  federateDB.momJobs.add(momSubscribeObjectClassAttributes);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceSynchronizationPointAchieved(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomSynchronizationPointAchieved *momSynchronizationPointAchieved;
  GeRtiFactory::GeRtiHandle federate = 0;
  std::wstring label;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }

    if (theData[i].id == managerFederateServiceSynchronizationPointAchievedLabel)
    {
      GERTICO::Mapper::mapHLAwstringFromOctetSequence(label, theData[i].value);
      continue;
    }
  }

  momSynchronizationPointAchieved = new GERTICO::MomSynchronizationPointAchieved(label, *geRtiSender);
  federateDB.momJobs.add(momSynchronizationPointAchieved);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceTimeAdvanceRequest(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomTimeAdvanceRequest *momTimeAdvanceRequest;
  GeRtiFactory::GeRtiHandle federate = 0;
  GERTICO::GeRtiFedTime *federationTime;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }

    if (theData[i].id == managerFederateServiceTimeAdvanceRequestTimeStamp)
    {
      char *cPtr = NULL;
      GERTICO::Mapper::mapOctetSequence(&cPtr, theData[i].value);
      federationTime = geRtiFedTimeFactory.decode(cPtr);
      delete []cPtr;
      continue;
    }
  }

  momTimeAdvanceRequest = new GERTICO::MomTimeAdvanceRequest(federationTime, *geRtiSender);
  federateDB.momJobs.add(momTimeAdvanceRequest);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceTimeAdvanceRequestAvailable(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomTimeAdvanceRequestAvailable *momTimeAdvanceRequestAvailable;
  GeRtiFactory::GeRtiHandle federate = 0;
  GERTICO::GeRtiFedTime *federationTime;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }

    if (theData[i].id == managerFederateServiceTimeAdvanceRequestAvailableTimeStamp)
    {
      char *cPtr = NULL;
      GERTICO::Mapper::mapOctetSequence(&cPtr, theData[i].value);
      federationTime = geRtiFedTimeFactory.decode(cPtr);
      delete []cPtr;
      continue;
    }
  }

  momTimeAdvanceRequestAvailable = new GERTICO::MomTimeAdvanceRequestAvailable(federationTime, *geRtiSender);
  federateDB.momJobs.add(momTimeAdvanceRequestAvailable);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceUnconditionalAttributeOwnershipDivestiture(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomUnconditionalAttributeOwnershipDivestiture *momUnconditionalAttributeOwnershipDivestiture;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::Handles attributes;
  GeRtiFactory::GeRtiHandle objecthandle;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }

    if (theData[i].id == managerFederateServiceUnconditionalAttributeOwnershipDivestitureObjectInstance)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      objecthandle = l;
      continue;
    }

    if (theData[i].id == managerFederateServiceUnconditionalAttributeOwnershipDivestitureAttributeList)
    {
      GERTICO::Mapper::mapHLAAttributesFromOctetSequence(attributes, theData[i].value);
      continue;
    }
  }

  momUnconditionalAttributeOwnershipDivestiture = new GERTICO::MomUnconditionalAttributeOwnershipDivestiture(objecthandle, attributes, *geRtiSender);
  federateDB.momJobs.add(momUnconditionalAttributeOwnershipDivestiture);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceUnpublishInteractionClass(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomUnpublishInteractionClass *momUnpublishInteractionClass;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::GeRtiHandle interactionClass;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }

    if (theData[i].id == managerFederateServiceUnpublishInteractionClassInteractionClass)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      interactionClass = l;
      continue;
    }
  }

  momUnpublishInteractionClass = new GERTICO::MomUnpublishInteractionClass(interactionClass, *geRtiSender);
  federateDB.momJobs.add(momUnpublishInteractionClass);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceUnpublishObjectClass(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomUnpublishObjectClass *momUnpublishObjectClass;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::GeRtiHandle objectClass;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }

    if (theData[i].id == managerFederateServiceUnpublishObjectClassObjectClass)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      objectClass = l;
      continue;
    }
  }

  momUnpublishObjectClass = new GERTICO::MomUnpublishObjectClass(objectClass, *geRtiSender);
  federateDB.momJobs.add(momUnpublishObjectClass);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceUnsubscribeInteractionClass(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomUnsubscribeInteractionClass *momUnsubscribeInteractionClass;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::GeRtiHandle interactionClass;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }

    if (theData[i].id == managerFederateServiceUnsubscribeInteractionClassInteractionClass)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      interactionClass = l;
      continue;
    }
  }

  momUnsubscribeInteractionClass = new GERTICO::MomUnsubscribeInteractionClass(interactionClass, *geRtiSender);
  federateDB.momJobs.add(momUnsubscribeInteractionClass);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceUnsubscribeObjectClass(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong lengthi;
  GERTICO::MomUnsubscribeObjectClass *momUnsubscribeObjectClass;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::GeRtiHandle objectClass;
  long l;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      federate = l;
      if (federate != federateDB.federate)
      {
        return;
      }
      continue;
    }

    if (theData[i].id == managerFederateServiceUnsubscribeObjectClassObjectClass)
    {
      GERTICO::Mapper::mapHLAlongFromOctetSequence(l, theData[i].value);
      objectClass = l;
      continue;
    }
  }

  momUnsubscribeObjectClass = new GERTICO::MomUnsubscribeObjectClass(objectClass, *geRtiSender);
  federateDB.momJobs.add(momUnsubscribeObjectClass);
  ps.release();
}
