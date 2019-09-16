/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: ManagementObjectModelLRC.cpp,v $
Revision 1.40  2010/06/28 13:43:32  mul
Change version numbers.

Revision 1.39  2010/05/17 08:06:21  mul
Add logical time interval.

Revision 1.38  2010/04/13 12:35:24  mul
Change sender member variables to pointers.

Revision 1.37  2009/09/30 14:28:02  mul
Changed version number.

Revision 1.36  2009/09/23 07:15:49  mul
Add logic for decentral management of attribute ownership.

Revision 1.35  2009/09/03 07:16:45  mul
Correct mom for local cache logic.

Revision 1.34  2009/08/17 10:14:50  mul
Change mutex type.

Revision 1.33  2009/05/07 12:36:06  mul
Minor changes.

Revision 1.32  2009/03/19 09:16:53  mul
Changes to optimize reading mom in lrc.

Revision 1.31  2009/01/26 09:51:02  mul
Changes to private / public visibility of members.

Revision 1.30  2008/08/21 12:29:22  mul
Changed version number.

Revision 1.29  2008/05/15 14:33:55  mul
Change mom version number.

Revision 1.28  2008/01/30 13:32:13  mul
Changes for ieee1615.

Revision 1.27  2007/09/25 08:30:32  mul
Changes for ddm.

Revision 1.26  2007/09/06 06:37:40  mul
Changes for ieee1516.

Revision 1.25  2007/05/15 13:24:31  mul
Changes for combined 1.3 and 1516 logic.

Revision 1.24  2007/05/09 13:17:14  mul
Use generic time.

Revision 1.23  2007/05/03 14:49:19  mul
Use mapper for HLA 1.3 types.

Revision 1.22  2007/03/26 07:45:53  mul
Change number.

Revision 1.21  2007/03/12 13:21:22  mul
Changed string to wstring.

Revision 1.20  2007/03/06 09:30:18  mul
Changes for ieee conversion.

Revision 1.19  2007/02/02 13:32:40  mul
Add some more services.

Revision 1.18  2007/01/12 14:52:41  mul
Minor change.

Revision 1.17  2007/01/12 14:49:40  mul
Remove dependency on receiver.

Revision 1.16  2007/01/09 14:28:40  mul
New version.

Revision 1.15  2006/11/29 11:29:48  mul
New version number.

Revision 1.14  2006/11/17 10:29:37  mul
Change version number.

Revision 1.13  2006/10/30 13:24:02  mul
Clean up some memory problems.

Revision 1.12  2006/10/23 14:54:45  mul
New version.

Revision 1.11  2006/09/29 10:03:45  mul
Fix handling of mom jobs.

Revision 1.10  2006/09/28 14:40:34  mul
Fix logic for mom thread.

Revision 1.9  2006/09/19 07:55:43  mul
Fix some program structure problems.

Revision 1.8  2006/09/15 11:51:58  mul
New version number.

Revision 1.7  2006/09/12 11:35:11  mul
Changes for phase 5 testcases.

Revision 1.6  2006/09/06 15:00:29  mul
Changes for phase 4 testcases.

Revision 1.5  2006/08/08 14:18:06  mul
Changes for mom test cases.

Revision 1.4  2006/08/01 11:37:54  mul
Changes for mom.

Revision 1.3  2006/05/12 13:38:11  mul
Fix logic for mom federate objects.

Revision 1.2  2006/04/19 15:06:14  mul
Changes for MOM.

Revision 1.1  2006/03/30 11:07:18  mul
New files.


**
*******************************************************************************/


#include "ManagementObjectModelLRC.h"
#include "Util/Mapper.h"

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomDeleteObjectInstance::MomDeleteObjectInstance(const std::wstring &theObjectName, const std::string &theUserSuppliedTag, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  objectName = theObjectName;
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  GeRtiFactory::GeRtiHandle object;
  bool gotError = false;

  try
  {
    object = geRtiSender.getObjectInstanceHandle(objectName);
  }
  catch(GeRtiFactory::NameNotFound &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ObjectNotKnown";
    momReportServiceInvocation.exceptionDescription = "ObjectNotKnown";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError == false)
  {
    try
    {
      geRtiSender.deleteObjectInstance(object, userSuppliedTag);
    }
    catch(GeRtiFactory::ObjectNotKnown &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "ObjectNotKnown";
      momReportServiceInvocation.exceptionDescription = "ObjectNotKnown";
    }
    catch(GeRtiFactory::DeletePrivilegeNotHeld &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "DeletePrivilegeNotHeld";
      momReportServiceInvocation.exceptionDescription = "DeletePrivilegeNotHeld";
    }
    catch(GeRtiFactory::FederateNotExecutionMember &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "FederateNotExecutionMember";
      momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
    }
    catch(GeRtiFactory::ConcurrentAccessAttempted &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "ConcurrentAccessAttempted";
      momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
    }
    catch(GeRtiFactory::SaveInProgress &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "SaveInProgress";
      momReportServiceInvocation.exceptionDescription = "SaveInProgress";
    }
    catch(GeRtiFactory::RestoreInProgress &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "RestoreInProgress";
      momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
    }
    catch(GeRtiFactory::RTIinternalError &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiInternalErrorEnum;
      momAlert.alertDescription = "RTIinternalError";
      momReportServiceInvocation.exceptionDescription = "RTIinternalError";
    }
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "deleteObjectInstance";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    GERTICO::Mapper::mapStringFromWstring(momReportServiceInvocation.suppliedArgument1, objectName);
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomDeleteObjectInstanceWithTime::MomDeleteObjectInstanceWithTime(const std::wstring &theObjectName, const std::string &theUserSuppliedTag, GERTICO::GeRtiFedTime *theFederationTime, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  objectName = theObjectName;
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  GeRtiFactory::GeRtiHandle object;
  bool gotError = false;

  try
  {
    object = geRtiSender.getObjectInstanceHandle(objectName);
  }
  catch(GeRtiFactory::NameNotFound &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ObjectNotKnown";
    momReportServiceInvocation.exceptionDescription = "ObjectNotKnown";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError == false)
  {
    try
    {
      geRtiSender.deleteObjectInstance(object, *federationTime, userSuppliedTag);
    }
    catch(GeRtiFactory::ObjectNotKnown &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "ObjectNotKnown";
      momReportServiceInvocation.exceptionDescription = "ObjectNotKnown";
    }
    catch(GeRtiFactory::DeletePrivilegeNotHeld &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "DeletePrivilegeNotHeld";
      momReportServiceInvocation.exceptionDescription = "DeletePrivilegeNotHeld";
    }
    catch(GeRtiFactory::InvalidFederationTime &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "InvalidFederationTime";
      momReportServiceInvocation.exceptionDescription = "InvalidFederationTime";
    }
    catch(GeRtiFactory::FederateNotExecutionMember &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "FederateNotExecutionMember";
      momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
    }
    catch(GeRtiFactory::ConcurrentAccessAttempted &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "ConcurrentAccessAttempted";
      momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
    }
    catch(GeRtiFactory::SaveInProgress &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "SaveInProgress";
      momReportServiceInvocation.exceptionDescription = "SaveInProgress";
    }
    catch(GeRtiFactory::RestoreInProgress &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "RestoreInProgress";
      momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
    }
    catch(GeRtiFactory::RTIinternalError &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiInternalErrorEnum;
      momAlert.alertDescription = "RTIinternalError";
      momReportServiceInvocation.exceptionDescription = "RTIinternalError";
    }
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "deleteObjectInstance";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    GERTICO::Mapper::mapStringFromWstring(momReportServiceInvocation.suppliedArgument1, objectName);
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.disableAsynchronousDelivery();
  }
  catch(GeRtiFactory::AsynchronousDeliveryAlreadyDisabled &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "AsynchronousDeliveryAlreadyDisabled";
    momReportServiceInvocation.exceptionDescription = "AsynchronousDeliveryAlreadyDisabled";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SaveInProgress";
    momReportServiceInvocation.exceptionDescription = "SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "RestoreInProgress";
    momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "disableAsynchronousDelivery";
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.disableTimeConstrained();
  }
  catch(GeRtiFactory::TimeConstrainedWasNotEnabled &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "TimeConstrainedWasNotEnabled";
    momReportServiceInvocation.exceptionDescription = "TimeConstrainedWasNotEnabled";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SaveInProgress";
    momReportServiceInvocation.exceptionDescription = "SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "RestoreInProgress";
    momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "disableTimeConstrained";
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.disableTimeRegulation();
  }
  catch(GeRtiFactory::TimeRegulationWasNotEnabled &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "TimeRegulationWasNotEnabled";
    momReportServiceInvocation.exceptionDescription = "TimeRegulationWasNotEnabled";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SaveInProgress";
    momReportServiceInvocation.exceptionDescription = "SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "RestoreInProgress";
    momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "disableTimeRegulation";
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.enableAsynchronousDelivery();
  }
  catch(GeRtiFactory::AsynchronousDeliveryAlreadyEnabled &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "AsynchronousDeliveryAlreadyEnabled";
    momReportServiceInvocation.exceptionDescription = "AsynchronousDeliveryAlreadyEnabled";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SaveInProgress";
    momReportServiceInvocation.exceptionDescription = "SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "RestoreInProgress";
    momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "enableAsynchronousDelivery";
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.enableTimeConstrained();
  }
  catch(GeRtiFactory::TimeConstrainedAlreadyEnabled &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "TimeConstrainedAlreadyEnabled";
    momReportServiceInvocation.exceptionDescription = "TimeConstrainedAlreadyEnabled";
  }
  catch(GeRtiFactory::EnableTimeConstrainedPending &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "EnableTimeConstrainedPending";
    momReportServiceInvocation.exceptionDescription = "EnableTimeConstrainedPending";
  }
  catch(GeRtiFactory::TimeAdvanceAlreadyInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "TimeAdvanceAlreadyInProgress";
    momReportServiceInvocation.exceptionDescription = "TimeAdvanceAlreadyInProgress";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SaveInProgress";
    momReportServiceInvocation.exceptionDescription = "SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "RestoreInProgress";
    momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "enableTimeConstrained";
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

GERTICO::MomEnableTimeRegulation::MomEnableTimeRegulation(GERTICO::GeRtiFedTime *theFederationTime, GERTICO::GeRtiLogicalTimeInterval *theLookahead, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  federationTime = theFederationTime;
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.enableTimeRegulation(*federationTime, *lookahead);
  }
  catch(GeRtiFactory::TimeRegulationAlreadyEnabled &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "TimeRegulationAlreadyEnabled";
    momReportServiceInvocation.exceptionDescription = "TimeRegulationAlreadyEnabled";
  }
  catch(GeRtiFactory::EnableTimeRegulationPending &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "EnableTimeRegulationPending";
    momReportServiceInvocation.exceptionDescription = "EnableTimeRegulationPending";
  }
  catch(GeRtiFactory::TimeAdvanceAlreadyInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "TimeAdvanceAlreadyInProgress";
    momReportServiceInvocation.exceptionDescription = "TimeAdvanceAlreadyInProgress";
  }
  catch(GeRtiFactory::InvalidFederationTime &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "InvalidFederationTime";
    momReportServiceInvocation.exceptionDescription = "InvalidFederationTime";
  }
  catch(GeRtiFactory::InvalidLookahead &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "InvalidLookahead";
    momReportServiceInvocation.exceptionDescription = "InvalidLookahead";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SaveInProgress";
    momReportServiceInvocation.exceptionDescription = "SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "RestoreInProgress";
    momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "enableTimeRegulation";
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.federateRestoreComplete(successIndicator);
  }
  catch(GeRtiFactory::RestoreNotRequested &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "RestoreNotRequested";
    momReportServiceInvocation.exceptionDescription = "RestoreNotRequested";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SaveInProgress";
    momReportServiceInvocation.exceptionDescription = "SaveInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "federateRestoreComplete";
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.federateSaveBegun();
  }
  catch(GeRtiFactory::SaveNotInitiated &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SaveNotInitiated";
    momReportServiceInvocation.exceptionDescription = "SaveNotInitiated";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "RestoreInProgress";
    momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "federateSaveBegun";
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.federateSaveComplete(successIndicator);
  }
  catch(GeRtiFactory::SaveNotInitiated &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SaveNotInitiated";
    momReportServiceInvocation.exceptionDescription = "SaveNotInitiated";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "RestoreInProgress";
    momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "federateSaveComplete";
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.flushQueueRequest(*federationTime);
  }
  catch(GeRtiFactory::InvalidFederationTime &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "InvalidFederationTime";
    momReportServiceInvocation.exceptionDescription = "InvalidFederationTime";
  }
  catch(GeRtiFactory::FederationTimeAlreadyPassed &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederationTimeAlreadyPassed";
    momReportServiceInvocation.exceptionDescription = "FederationTimeAlreadyPassed";
  }
  catch(GeRtiFactory::TimeAdvanceAlreadyInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "TimeAdvanceAlreadyInProgress";
    momReportServiceInvocation.exceptionDescription = "TimeAdvanceAlreadyInProgress";
  }
  catch(GeRtiFactory::EnableTimeRegulationPending &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "EnableTimeRegulationPending";
    momReportServiceInvocation.exceptionDescription = "EnableTimeRegulationPending";
  }
  catch(GeRtiFactory::EnableTimeConstrainedPending &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "EnableTimeConstrainedPending";
    momReportServiceInvocation.exceptionDescription = "EnableTimeConstrainedPending";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SaveInProgress";
    momReportServiceInvocation.exceptionDescription = "SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "RestoreInProgress";
    momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "flushQueueRequest";
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
GERTICO::MomLocalDeleteObjectInstance::MomLocalDeleteObjectInstance(const std::wstring &theObjectName, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  objectName = theObjectName;
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  GeRtiFactory::GeRtiHandle object;
  bool gotError = false;

  try
  {
    object = geRtiSender.getObjectInstanceHandle(objectName);
  }
  catch(GeRtiFactory::NameNotFound &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ObjectNotKnown";
    momReportServiceInvocation.exceptionDescription = "ObjectNotKnown";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError == false)
  {
    try
    {
      geRtiSender.localDeleteObjectInstance(object);
    }
    catch(GeRtiFactory::ObjectNotKnown &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "ObjectNotKnown";
      momReportServiceInvocation.exceptionDescription = "ObjectNotKnown";
    }
    catch(GeRtiFactory::FederateOwnsAttributes &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "FederateOwnsAttributes";
      momReportServiceInvocation.exceptionDescription = "FederateOwnsAttributes";
    }
    catch(GeRtiFactory::FederateNotExecutionMember &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "FederateNotExecutionMember";
      momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
    }
    catch(GeRtiFactory::ConcurrentAccessAttempted &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "ConcurrentAccessAttempted";
      momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
    }
    catch(GeRtiFactory::SaveInProgress &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "SaveInProgress";
      momReportServiceInvocation.exceptionDescription = "SaveInProgress";
    }
    catch(GeRtiFactory::RestoreInProgress &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "RestoreInProgress";
      momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
    }
    catch(GeRtiFactory::RTIinternalError &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiInternalErrorEnum;
      momAlert.alertDescription = "RTIinternalError";
      momReportServiceInvocation.exceptionDescription = "RTIinternalError";
    }
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "localDeleteObjectInstance";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    GERTICO::Mapper::mapStringFromWstring(momReportServiceInvocation.suppliedArgument1, objectName);
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomChangeAttributeTransportationType::MomChangeAttributeTransportationType(std::wstring const &theObjectName, GeRtiFactory::Handles &theAttributes, GeRtiFactory::GeRtiHandle const &theTransportationType, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  objectName = theObjectName;
  attributes = theAttributes;
  transportType = theTransportationType;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomChangeAttributeTransportationType::~MomChangeAttributeTransportationType(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomChangeAttributeTransportationType::execute(void)
{
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  GeRtiFactory::GeRtiHandle object;
  bool gotError = false;

  try
  {
    object = geRtiSender.getObjectInstanceHandle(objectName);
  }
  catch(GeRtiFactory::NameNotFound &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ObjectNotKnown";
    momReportServiceInvocation.exceptionDescription = "ObjectNotKnown";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError == false)
  {
    try
    {
      geRtiSender.changeAttributeTransportationType(object, attributes, transportType);
    }
    catch(GeRtiFactory::ObjectNotKnown &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "ObjectNotKnown";
      momReportServiceInvocation.exceptionDescription = "ObjectNotKnown";
    }
    catch(GeRtiFactory::AttributeNotDefined &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "AttributeNotDefined";
      momReportServiceInvocation.exceptionDescription = "AttributeNotDefined";
    }
    catch(GeRtiFactory::AttributeNotOwned &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "AttributeNotOwned";
      momReportServiceInvocation.exceptionDescription = "AttributeNotOwned";
    }
    catch(GeRtiFactory::InvalidTransportationHandle &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "InvalidTransportationHandle";
      momReportServiceInvocation.exceptionDescription = "InvalidTransportationHandle";
    }
    catch(GeRtiFactory::FederateNotExecutionMember &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "FederateNotExecutionMember";
      momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
    }
    catch(GeRtiFactory::ConcurrentAccessAttempted &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "ConcurrentAccessAttempted";
      momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
    }
    catch(GeRtiFactory::SaveInProgress &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "SaveInProgress";
      momReportServiceInvocation.exceptionDescription = "SaveInProgress";
    }
    catch(GeRtiFactory::RestoreInProgress &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "RestoreInProgress";
      momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
    }
    catch(GeRtiFactory::RTIinternalError &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiInternalErrorEnum;
      momAlert.alertDescription = "RTIinternalError";
      momReportServiceInvocation.exceptionDescription = "RTIinternalError";
    }
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "localDeleteObjectInstance";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    GERTICO::Mapper::mapStringFromWstring(momReportServiceInvocation.suppliedArgument1, objectName);
    geRtiSender.sendReportServiceInvocation(momReportServiceInvocation);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomChangeAttributeOrderType::MomChangeAttributeOrderType(std::wstring const &theObjectName, GeRtiFactory::Handles &theAttributes, GeRtiFactory::GeRtiHandle const &theOrderType, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  objectName = theObjectName;
  attributes = theAttributes;
  orderType = theOrderType;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MomChangeAttributeOrderType::~MomChangeAttributeOrderType(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::MomChangeAttributeOrderType::execute(void)
{
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  GeRtiFactory::GeRtiHandle object;
  bool gotError = false;

  try
  {
    object = geRtiSender.getObjectInstanceHandle(objectName);
  }
  catch(GeRtiFactory::NameNotFound &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ObjectNotKnown";
    momReportServiceInvocation.exceptionDescription = "ObjectNotKnown";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError == false)
  {
    try
    {
      geRtiSender.changeAttributeOrderType(object, attributes, orderType);
    }
    catch(GeRtiFactory::ObjectNotKnown &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "ObjectNotKnown";
      momReportServiceInvocation.exceptionDescription = "ObjectNotKnown";
    }
    catch(GeRtiFactory::AttributeNotDefined &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "AttributeNotDefined";
      momReportServiceInvocation.exceptionDescription = "AttributeNotDefined";
    }
    catch(GeRtiFactory::AttributeNotOwned &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "AttributeNotOwned";
      momReportServiceInvocation.exceptionDescription = "AttributeNotOwned";
    }
    catch(GeRtiFactory::InvalidTransportationHandle &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "InvalidTransportationHandle";
      momReportServiceInvocation.exceptionDescription = "InvalidTransportationHandle";
    }
    catch(GeRtiFactory::FederateNotExecutionMember &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "FederateNotExecutionMember";
      momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
    }
    catch(GeRtiFactory::ConcurrentAccessAttempted &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "ConcurrentAccessAttempted";
      momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
    }
    catch(GeRtiFactory::SaveInProgress &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "SaveInProgress";
      momReportServiceInvocation.exceptionDescription = "SaveInProgress";
    }
    catch(GeRtiFactory::RestoreInProgress &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "RestoreInProgress";
      momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
    }
    catch(GeRtiFactory::RTIinternalError &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiInternalErrorEnum;
      momAlert.alertDescription = "RTIinternalError";
      momReportServiceInvocation.exceptionDescription = "RTIinternalError";
    }
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "localDeleteObjectInstance";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    GERTICO::Mapper::mapStringFromWstring(momReportServiceInvocation.suppliedArgument1, objectName);
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.modifyLookahead(*lookahead);
  }
  catch(GeRtiFactory::InvalidLookahead &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "InvalidLookahead";
    momReportServiceInvocation.exceptionDescription = "InvalidLookahead";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SaveInProgress";
    momReportServiceInvocation.exceptionDescription = "SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "RestoreInProgress";
    momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "modifyLookahead";
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.nextEventRequest(*federationTime);
  }
  catch(GeRtiFactory::InvalidFederationTime &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "InvalidFederationTime";
    momReportServiceInvocation.exceptionDescription = "InvalidFederationTime";
  }
  catch(GeRtiFactory::FederationTimeAlreadyPassed &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederationTimeAlreadyPassed";
    momReportServiceInvocation.exceptionDescription = "FederationTimeAlreadyPassed";
  }
  catch(GeRtiFactory::TimeAdvanceAlreadyInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "TimeAdvanceAlreadyInProgress";
    momReportServiceInvocation.exceptionDescription = "TimeAdvanceAlreadyInProgress";
  }
  catch(GeRtiFactory::EnableTimeRegulationPending &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "EnableTimeRegulationPending";
    momReportServiceInvocation.exceptionDescription = "EnableTimeRegulationPending";
  }
  catch(GeRtiFactory::EnableTimeConstrainedPending &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "EnableTimeConstrainedPending";
    momReportServiceInvocation.exceptionDescription = "EnableTimeConstrainedPending";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SaveInProgress";
    momReportServiceInvocation.exceptionDescription = "SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "RestoreInProgress";
    momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "nextEventRequest";
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.nextEventRequestAvailable(*federateTime);
  }
  catch(GeRtiFactory::InvalidFederationTime &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "InvalidFederationTime";
    momReportServiceInvocation.exceptionDescription = "InvalidFederationTime";
  }
  catch(GeRtiFactory::FederationTimeAlreadyPassed &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederationTimeAlreadyPassed";
    momReportServiceInvocation.exceptionDescription = "FederationTimeAlreadyPassed";
  }
  catch(GeRtiFactory::TimeAdvanceAlreadyInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "TimeAdvanceAlreadyInProgress";
    momReportServiceInvocation.exceptionDescription = "TimeAdvanceAlreadyInProgress";
  }
  catch(GeRtiFactory::EnableTimeRegulationPending &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "EnableTimeRegulationPending";
    momReportServiceInvocation.exceptionDescription = "EnableTimeRegulationPending";
  }
  catch(GeRtiFactory::EnableTimeConstrainedPending &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "EnableTimeConstrainedPending";
    momReportServiceInvocation.exceptionDescription = "EnableTimeConstrainedPending";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SaveInProgress";
    momReportServiceInvocation.exceptionDescription = "SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "RestoreInProgress";
    momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "nextEventRequestAvailable";
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.publishInteractionClass(interactionClass);
  }
  catch(GeRtiFactory::InteractionClassNotDefined &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "InteractionClassNotDefined";
    momReportServiceInvocation.exceptionDescription = "InteractionClassNotDefined";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SaveInProgress";
    momReportServiceInvocation.exceptionDescription = "SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "RestoreInProgress";
    momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "publishInteractionClass";
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.publishObjectClass(objectClass, attributes);
  }
  catch(GeRtiFactory::ObjectClassNotDefined &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ObjectClassNotDefined";
    momReportServiceInvocation.exceptionDescription = "ObjectClassNotDefined";
  }
  catch(GeRtiFactory::AttributeNotDefined &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "AttributeNotDefined";
    momReportServiceInvocation.exceptionDescription = "AttributeNotDefined";
  }
  catch(GeRtiFactory::OwnershipAcquisitionPending &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "OwnershipAcquisitionPending";
    momReportServiceInvocation.exceptionDescription = "OwnershipAcquisitionPending";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SaveInProgress";
    momReportServiceInvocation.exceptionDescription = "SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "RestoreInProgress";
    momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "publishObjectClass";
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
  GERTICO::MomAlert momAlert;
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
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateOwnsAttributes";
    momReportServiceInvocation.exceptionDescription = "FederateOwnsAttributes";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
    stillConnected = false;
  }
  catch(GeRtiFactory::InvalidResignAction &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "InvalidResignAction";
    momReportServiceInvocation.exceptionDescription = "InvalidResignAction";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
    stillConnected = false;
  }

  if (gotError)
  {
    if (stillConnected)
    {
      momAlert.alertId = 0; // XX
      geRtiSender.sendReportAlert(momAlert);
    }
  }

  if (stillConnected)
  {
    if (geRtiSender.checkReportServiceInvocation())
    {
      momReportServiceInvocation.service = "resignFederationExecution";
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
  GERTICO::MomAlert momAlert;
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
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "InteractionClassNotDefined";
    momReportServiceInvocation.exceptionDescription = "InteractionClassNotDefined";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::FederateLoggingServiceCalls &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateLoggingServiceCalls";
    momReportServiceInvocation.exceptionDescription = "FederateLoggingServiceCalls";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SaveInProgress";
    momReportServiceInvocation.exceptionDescription = "SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "RestoreInProgress";
    momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "subscribeInteractionClass";
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.subscribeObjectClassAttributes(objectClass, attributes, active);
  }
  catch(GeRtiFactory::ObjectClassNotDefined &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ObjectClassNotDefined";
    momReportServiceInvocation.exceptionDescription = "ObjectClassNotDefined";
  }
  catch(GeRtiFactory::AttributeNotDefined &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "AttributeNotDefined";
    momReportServiceInvocation.exceptionDescription = "AttributeNotDefined";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SaveInProgress";
    momReportServiceInvocation.exceptionDescription = "SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "RestoreInProgress";
    momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "subscribeObjectClassAttributes";
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.synchronizationPointAchieved(label.c_str());
  }
  catch(GeRtiFactory::SynchronizationPointLabelWasNotAnnounced &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SynchronizationPointLabelWasNotAnnounced";
    momReportServiceInvocation.exceptionDescription = "SynchronizationPointLabelWasNotAnnounced";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SaveInProgress";
    momReportServiceInvocation.exceptionDescription = "SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "RestoreInProgress";
    momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "synchronizationPointAchieved";
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.timeAdvanceRequest(*federationTime);
  }
  catch(GeRtiFactory::InvalidFederationTime &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "InvalidFederationTime";
    momReportServiceInvocation.exceptionDescription = "InvalidFederationTime";
  }
  catch(GeRtiFactory::FederationTimeAlreadyPassed &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederationTimeAlreadyPassed";
    momReportServiceInvocation.exceptionDescription = "FederationTimeAlreadyPassed";
  }
  catch(GeRtiFactory::TimeAdvanceAlreadyInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "TimeAdvanceAlreadyInProgress";
    momReportServiceInvocation.exceptionDescription = "TimeAdvanceAlreadyInProgress";
  }
  catch(GeRtiFactory::EnableTimeRegulationPending &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "EnableTimeRegulationPending";
    momReportServiceInvocation.exceptionDescription = "EnableTimeRegulationPending";
  }
  catch(GeRtiFactory::EnableTimeConstrainedPending &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "EnableTimeConstrainedPending";
    momReportServiceInvocation.exceptionDescription = "EnableTimeConstrainedPending";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SaveInProgress";
    momReportServiceInvocation.exceptionDescription = "SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "RestoreInProgress";
    momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "timeAdvanceRequest";
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.timeAdvanceRequestAvailable(*federationTime);
  }
  catch(GeRtiFactory::InvalidFederationTime &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "InvalidFederationTime";
    momReportServiceInvocation.exceptionDescription = "InvalidFederationTime";
  }
  catch(GeRtiFactory::FederationTimeAlreadyPassed &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederationTimeAlreadyPassed";
    momReportServiceInvocation.exceptionDescription = "FederationTimeAlreadyPassed";
  }
  catch(GeRtiFactory::TimeAdvanceAlreadyInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "TimeAdvanceAlreadyInProgress";
    momReportServiceInvocation.exceptionDescription = "TimeAdvanceAlreadyInProgress";
  }
  catch(GeRtiFactory::EnableTimeRegulationPending &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "EnableTimeRegulationPending";
    momReportServiceInvocation.exceptionDescription = "EnableTimeRegulationPending";
  }
  catch(GeRtiFactory::EnableTimeConstrainedPending &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "EnableTimeConstrainedPending";
    momReportServiceInvocation.exceptionDescription = "EnableTimeConstrainedPending";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SaveInProgress";
    momReportServiceInvocation.exceptionDescription = "SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "RestoreInProgress";
    momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "timeAdvanceRequestAvailable";
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
GERTICO::MomUnconditionalAttributeOwnershipDivestiture::MomUnconditionalAttributeOwnershipDivestiture(const std::wstring &theObjectName, const GeRtiFactory::Handles &theAttributes, GERTICO::GeRtiSender &theGeRtiSender) : geRtiSender(theGeRtiSender)
{
  objectName = theObjectName;
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  GeRtiFactory::GeRtiHandle object;
  bool gotError = false;

  try
  {
    object = geRtiSender.getObjectInstanceHandle(objectName);
  }
  catch(GeRtiFactory::NameNotFound &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ObjectNotKnown";
    momReportServiceInvocation.exceptionDescription = "ObjectNotKnown";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError == false)
  {
    try
    {
      geRtiSender.unconditionalAttributeOwnershipDivestiture(object, attributes);
    }
    catch(GeRtiFactory::ObjectNotKnown &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "ObjectNotKnown";
      momReportServiceInvocation.exceptionDescription = "ObjectNotKnown";
    }
    catch(GeRtiFactory::AttributeNotDefined &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "AttributeNotDefined";
      momReportServiceInvocation.exceptionDescription = "AttributeNotDefined";
    }
    catch(GeRtiFactory::AttributeNotOwned &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "AttributeNotOwned";
      momReportServiceInvocation.exceptionDescription = "AttributeNotOwned";
    }
    catch(GeRtiFactory::FederateNotExecutionMember &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "FederateNotExecutionMember";
      momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
    }
    catch(GeRtiFactory::ConcurrentAccessAttempted &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "ConcurrentAccessAttempted";
      momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
    }
    catch(GeRtiFactory::SaveInProgress &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "SaveInProgress";
      momReportServiceInvocation.exceptionDescription = "SaveInProgress";
    }
    catch(GeRtiFactory::RestoreInProgress &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiExceptionEnum;
      momAlert.alertDescription = "RestoreInProgress";
      momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
    }
    catch(GeRtiFactory::RTIinternalError &)
    {
      gotError = true;
      momAlert.alertSeverityEnum = RtiInternalErrorEnum;
      momAlert.alertDescription = "RTIinternalError";
      momReportServiceInvocation.exceptionDescription = "RTIinternalError";
    }
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "unconditionalAttributeOwnershipDivestiture";
    momReportServiceInvocation.initiatorEnum = RtiEnum;
    if (gotError)
    {
      momReportServiceInvocation.successIndicator = false;
    }
    else
    {
      momReportServiceInvocation.successIndicator = true;
    }
    GERTICO::Mapper::mapStringFromWstring(momReportServiceInvocation.suppliedArgument1, objectName);
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.unpublishInteractionClass(interactionClass);
  }
  catch(GeRtiFactory::InteractionClassNotDefined &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "InteractionClassNotDefined";
    momReportServiceInvocation.exceptionDescription = "InteractionClassNotDefined";
  }
  catch(GeRtiFactory::InteractionClassNotPublished &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "InteractionClassNotPublished";
    momReportServiceInvocation.exceptionDescription = "InteractionClassNotPublished";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SaveInProgress";
    momReportServiceInvocation.exceptionDescription = "SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "RestoreInProgress";
    momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "unpublishInteractionClass";
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.unpublishObjectClass(objectClass);
  }
  catch(GeRtiFactory::ObjectClassNotDefined &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ObjectClassNotDefined";
    momReportServiceInvocation.exceptionDescription = "ObjectClassNotDefined";
  }
  catch(GeRtiFactory::ObjectClassNotPublished &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ObjectClassNotPublished";
    momReportServiceInvocation.exceptionDescription = "ObjectClassNotPublished";
  }
  catch(GeRtiFactory::OwnershipAcquisitionPending &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "OwnershipAcquisitionPending";
    momReportServiceInvocation.exceptionDescription = "OwnershipAcquisitionPending";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SaveInProgress";
    momReportServiceInvocation.exceptionDescription = "SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "RestoreInProgress";
    momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "unpublishObjectClass";
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.unsubscribeInteractionClass(interactionClass);
  }
  catch(GeRtiFactory::InteractionClassNotDefined &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "InteractionClassNotDefined";
    momReportServiceInvocation.exceptionDescription = "InteractionClassNotDefined";
  }
  catch(GeRtiFactory::InteractionClassNotSubscribed &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "InteractionClassNotSubscribed";
    momReportServiceInvocation.exceptionDescription = "InteractionClassNotSubscribed";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SaveInProgress";
    momReportServiceInvocation.exceptionDescription = "SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "RestoreInProgress";
    momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "unsubscribeInteractionClass";
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
  GERTICO::MomAlert momAlert;
  GERTICO::MomReportServiceInvocation momReportServiceInvocation;
  bool gotError = false;

  try
  {
    geRtiSender.unsubscribeObjectClass(objectClass);
  }
  catch(GeRtiFactory::ObjectClassNotDefined &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ObjectClassNotDefined";
    momReportServiceInvocation.exceptionDescription = "ObjectClassNotDefined";
  }
  catch(GeRtiFactory::ObjectClassNotSubscribed &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ObjectClassNotSubscribed";
    momReportServiceInvocation.exceptionDescription = "ObjectClassNotSubscribed";
  }
  catch(GeRtiFactory::FederateNotExecutionMember &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "FederateNotExecutionMember";
    momReportServiceInvocation.exceptionDescription = "FederateNotExecutionMember";
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "ConcurrentAccessAttempted";
    momReportServiceInvocation.exceptionDescription = "ConcurrentAccessAttempted";
  }
  catch(GeRtiFactory::SaveInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "SaveInProgress";
    momReportServiceInvocation.exceptionDescription = "SaveInProgress";
  }
  catch(GeRtiFactory::RestoreInProgress &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiExceptionEnum;
    momAlert.alertDescription = "RestoreInProgress";
    momReportServiceInvocation.exceptionDescription = "RestoreInProgress";
  }
  catch(GeRtiFactory::RTIinternalError &)
  {
    gotError = true;
    momAlert.alertSeverityEnum = RtiInternalErrorEnum;
    momAlert.alertDescription = "RTIinternalError";
    momReportServiceInvocation.exceptionDescription = "RTIinternalError";
  }

  if (gotError)
  {
    momAlert.alertId = 0; // XX
    geRtiSender.sendReportAlert(momAlert);
  }

  if (geRtiSender.checkReportServiceInvocation())
  {
    momReportServiceInvocation.service = "unsubscribeObjectClass";
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
  CORBA::ULong j;
  CORBA::ULong jLen;
  CORBA::ULong len;
  GERTICO::AttributeInfo *attributeInfo;
  GERTICO::AttributeStatus status;
  GERTICO::RegisteredObject *registeredObject;
  unsigned long attribute;
  unsigned long federate;
  char *cptr;
  std::wstring objectInstance;

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
      GERTICO::Mapper::mapOctetSequence(&cptr, theData[i].value);
      GERTICO::Mapper::mapWstringFromChar(objectInstance, cptr);
      delete[] cptr;
      continue;
    }
    if (theData[i].id == managerFederateAdjustModifyAttributeStateAttribute)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theData[i].value);
      sscanf(cptr, "%lu", &attribute);
      delete[] cptr;
      continue;
    }
    if (theData[i].id == managerFederateAdjustModifyAttributeStateAttributeState)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theData[i].value);
      jLen = strlen(cptr);
      for (j = 0; j < jLen; j++)
      {
        cptr[j] = tolower(cptr[j]);
      }
      if (strcmp(cptr, "owned") == 0)
      {
        status = owned;
      }
      else
      {
        status = unowned;
      }
      delete[] cptr;
      continue;
    }
  }

  try
  {
    registeredObject = federateDB.objectManagementLRC->getObjectByName(objectInstance);
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
  char *cptr;
  std::string serviceReportingStr;

  len = theData.length();
  for (i = 0; i < len; i++)
  {
    if (theData[i].id == managerFederateAdjustSetServiceReportingState)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theData[i].value);
      serviceReportingStr = cptr;
      delete[] cptr;
    }
  }

  GERTICO::Mapper::nameToLower(serviceReportingStr);
  if (serviceReportingStr == "true")
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
void GERTICO::ManagementObjectModelLRC::getAttributes(GeRtiFactory::Handles &theAttributes, char *theBuff)
{
  int i;
  int ind = 0;
  int items;
  int j;
  unsigned long len = 0;
  unsigned long ul;

  for (i = 0, j = 0; ;)
  {
    items = sscanf(&theBuff[ind], "%lu%n ,%n", &ul, &i, &j);
    if (items == -1 || items == 0)
    {
      break;
    }
    theAttributes.length(len + 1);
    theAttributes[len] = ul;
    len += 1;
    if (j == 0)
    {
      break;
    }
    ind += j;
    j = 0;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::getBoolean(CORBA::Boolean &theBoolean, char *theBuff)
{
  int i;
  int len;

  len = strlen(theBuff);
  for (i = 0; i < len; i++)
  {
    theBuff[i] = tolower(theBuff[i]);
  }

  if (strcmp(theBuff, "true") == 0)
  {
    theBoolean = 1;
  }
  else
  {
    theBoolean = 0;
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
  if (theRequest == managerFederateReportAlert)
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

  if (theRequest == managerFederateServicePublishObjectClass)
  {
    servicePublishObjectClass(data);
  }

  if (theRequest == managerFederateServiceUnpublishObjectClass)
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

  if (theRequest == managerFederateServiceUnsubscribeObjectClass)
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

  if (theRequest == managerFederateServiceChangeAttributeTransportationType)
  {
    serviceChangeAttributeTransportationType(data);
  }

  if (theRequest == managerFederateServiceChangeAttributeOrderType)
  {
    serviceChangeAttributeOrderType(data);
  }

  if (theRequest == managerFederateServiceChangeInteractionTransportationType)
  {
    serviceChangeInteractionTransportationType(data);
  }

  if (theRequest == managerFederateServiceChangeInteractionOrderType)
  {
    serviceChangeChangeInteractionOrderType(data);
  }

  if (theRequest == managerFederateServiceUnconditionalAttributeOwnershipDivestiture)
  {
    serviceUnconditionalAttributeOwnershipDivestiture(data);
  }

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

  if (theRequest == managerFederateServiceNextEventRequest)
  {
    serviceNextEventRequest(data);
  }

  if (theRequest == managerFederateServiceNextEventRequestAvailable)
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
  char buf[512];
  unsigned long ul;
  unsigned long ul1;

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
        ul = federateDB.federate;
        sprintf(buf, "%lu", ul);
        data->length(ind + 1);
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateFederateHandle, buf);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateFederateType)
      {
        data->length(ind + 1);
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateFederateType, federateDB.federateType.c_str());
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateFederateHost)
      {
        data->length(ind + 1);
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateFederateHost, federateDB.hostName.c_str());
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateRTIversion)
      {
        data->length(ind + 1);
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateRTIversion, "gertico_0_54");
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateFEDid)
      {
        data->length(ind + 1);
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateFEDid, "");
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateTimeConstrained)
      {
        if (federateDB.timeManagementLRC->isTimeConstrained())
        {
          strcpy(buf, "True");
        }
        else
        {
          strcpy(buf, "False");
        }
        data->length(ind + 1);
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateTimeConstrained, buf);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateTimeRegulating)
      {
        if (federateDB.timeManagementLRC->isTimeRegulation())
        {
          strcpy(buf, "True");
        }
        else
        {
          strcpy(buf, "False");
        }
        data->length(ind + 1);
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateTimeRegulating, buf);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateAsynchronousDelivery)
      {
        if (receiverLRC.getAsynchronousDelivery())
        {
          strcpy(buf, "True");
        }
        else
        {
          strcpy(buf, "False");
        }
        data->length(ind + 1);
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateAsynchronousDelivery, buf);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateFederateState)
      {
        GERTICO::FederateState federateState = Running;

        receiverLRC.getFederateState(federateState);
        switch(federateState)
        {
          case Running:
          {
            strcpy(buf, "Running");
            break;
          }
          case SavePending:
          {
            strcpy(buf, "Save Pending");
            break;
          }
          case Saving:
          {
            strcpy(buf, "Saving");
            break;
          }
          case RestorePending:
          {
            strcpy(buf, "Restore Pending");
            break;
          }
          case Restoring:
          {
            strcpy(buf, "Restoring");
            break;
          }
        }
        data->length(ind + 1);
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateFederateState, buf);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateTimeManagerState)
      {
        if (federateDB.timeManagementLRC->isTimeAdvancing())
        {
          strcpy(buf, "Advance pending");
        }
        else
        {
          strcpy(buf, "Idle");
        }
        data->length(ind + 1);
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateTimeManagerState, buf);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateFederateTime)
      {
        GERTICO::GeRtiFedTime *t;

        t = geRtiFedTimeFactory.makeZero();
        federateDB.timeManagementLRC->queryLogicalTime(*t);
        t->getPrintableString(buf);
        delete t;
        data->length(ind + 1);
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateFederateTime, buf);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateLookahead)
      {
        GERTICO::GeRtiLogicalTimeInterval *t;

        t = geRtiLogicalTimeIntervalFactory.makeZero();
        federateDB.timeManagementLRC->queryLookahead(*t);
        t->getPrintableString(buf);
        delete t;
        data->length(ind + 1);
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateLookahead, buf);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateLBTS)
      {
        GERTICO::GeRtiFedTime *t;

        t = geRtiFedTimeFactory.makeZero();
        federateDB.timeManagementLRC->queryGALT(*t);
        t->getPrintableString(buf);
        delete t;
        data->length(ind + 1);
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateLBTS, buf);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateMinNextEventTime)
      {
        GERTICO::GeRtiFedTime *t;

        t = geRtiFedTimeFactory.makeZero();
        geRtiSender->queryMinNextEventTime(*t);
        t->getPrintableString(buf);
        delete t;
        data->length(ind + 1);
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateMinNextEventTime, buf);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateROlength)
      {
        ul = receiverLRC.getROlength();
        sprintf (buf, "%lu", ul);
        data->length(ind + 1);
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateROlength, buf);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateTSOlength)
      {
        ul = receiverLRC.getTSOlength();
        sprintf (buf, "%lu", ul);
        data->length(ind + 1);
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateTSOlength, buf);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateReflectionsReceived)
      {
        ul = receiverLRC.getReflectionsReceived();
        sprintf (buf, "%lu", ul);
        data->length(ind + 1);
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateReflectionsReceived, buf);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateUpdatesSent)
      {
        ul = eventMarket.getUpdatesSent();
        sprintf (buf, "%lu", ul);
        data->length(ind + 1);
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateUpdatesSent, buf);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateInteractionsReceived)
      {
        ul = receiverLRC.getInteractionsReceived();
        sprintf (buf, "%lu", ul);
        data->length(ind + 1);
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateInteractionsReceived, buf);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateInteractionsSent)
      {
        ul = eventMarket.getInteractionsSent();
        sprintf (buf, "%lu", ul);
        data->length(ind + 1);
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateInteractionsSent, buf);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateObjectsOwned)
      {
        GeRtiFactory::GeRtiHandle privilegeToDeleteId;
        GERTICO::HandleSet objectIds;

        privilegeToDeleteId = federateDB.runTimeObjectDB->getPrivilegeToDeleteId();
        federateDB.registeredObjectsHolder.getOwnedObjectIds(federateDB.federate, objectIds, privilegeToDeleteId);
        ul = objectIds.size();
        objectIds.clear();
        sprintf (buf, "%lu", ul);
        data->length(ind + 1);
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateObjectsOwned, buf);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateObjectsUpdated)
      {
        ul = federateDB.getObjectsUpdated();
        sprintf (buf, "%lu", ul);
        data->length(ind + 1);
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateObjectsUpdated, buf);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateObjectsReflected)
      {
        ul = federateDB.getObjectsReflected();
        sprintf (buf, "%lu", ul);
        data->length(ind + 1);
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateObjectsReflected, buf);
        ind += 1;
        continue;
      }
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
        ul = federateDB.federate;
        sprintf(buf, "%lu", ul);
        GERTICO::Mapper::mapHandleValue(data[ind], managerInteractionFederateFederate, buf);
        GERTICO::Mapper::mapHandleValue(data[ind + 3], managerInteractionFederateFederate, buf);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateReportReflectionsReceivedTransportationType)
      {
        strcpy(buf, "Reliable");
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateReportReflectionsReceivedTransportationType, buf);
        strcpy(buf, "Best Effort");
        GERTICO::Mapper::mapHandleValue(data[ind + 3], managerFederateReportReflectionsReceivedTransportationType, buf);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateReportReflectionsReceivedReflectCounts)
      {
        CORBA::ULong pos;
        GERTICO::HandleMap reflections;
        GERTICO::HandleMap::iterator itReflection;

        buf[0] = '\0';
        receiverLRC.getReflectionsReceivedReliable(reflections);
        pos = 0;
        for (itReflection = reflections.begin(); itReflection != reflections.end(); itReflection++)
        {
          ul = itReflection->first;
          ul1 = itReflection->second;
          if (pos)
          {
            sprintf(&buf[pos], ",%lu/%lu", ul, ul1);
          }
          else
          {
            sprintf(&buf[pos], "%lu/%lu", ul, ul1);
          }
          pos = strlen(buf);
        }
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateReportReflectionsReceivedReflectCounts, buf);

        buf[0] = '\0';
        receiverLRC.getReflectionsReceivedBestEffort(reflections);
        pos = 0;
        for (itReflection = reflections.begin(); itReflection != reflections.end(); itReflection++)
        {
          ul = itReflection->first;
          ul1 = itReflection->second;
          if (pos)
          {
            sprintf(&buf[pos], ",%lu/%lu", ul, ul1);
          }
          else
          {
            sprintf(&buf[pos], "%lu/%lu", ul, ul1);
          }
          pos = strlen(buf);
        }
        GERTICO::Mapper::mapHandleValue(data[ind + 3], managerFederateReportReflectionsReceivedReflectCounts, buf);
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
        ul = federateDB.federate;
        sprintf(buf, "%lu", ul);
        GERTICO::Mapper::mapHandleValue(data[ind], managerInteractionFederateFederate, buf);
        GERTICO::Mapper::mapHandleValue(data[ind + 3], managerInteractionFederateFederate, buf);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateReportInteractionsReceivedTransportationType)
      {
        strcpy(buf, "Reliable");
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateReportInteractionsReceivedTransportationType, buf);
        strcpy(buf, "Best Effort");
        GERTICO::Mapper::mapHandleValue(data[ind + 3], managerFederateReportInteractionsReceivedTransportationType, buf);
        ind += 1;
        continue;
      }
      if (theAttributes[i] == managerFederateReportInteractionsReceivedInteractionCounts)
      {
        CORBA::ULong pos;
        GERTICO::HandleMap reflections;
        GERTICO::HandleMap::iterator itReflection;

        buf[0] = '\0';
        receiverLRC.getInteractionsReceivedReliable(reflections);
        pos = 0;
        for (itReflection = reflections.begin(); itReflection != reflections.end(); itReflection++)
        {
          ul = itReflection->first;
          ul1 = itReflection->second;
          if (pos)
          {
            sprintf(&buf[pos], ",%lu/%lu", ul, ul1);
          }
          else
          {
            sprintf(&buf[pos], "%lu/%lu", ul, ul1);
          }
          pos = strlen(buf);
        }
        GERTICO::Mapper::mapHandleValue(data[ind], managerFederateReportInteractionsReceivedInteractionCounts, buf);

        buf[0] = '\0';
        receiverLRC.getInteractionsReceivedBestEffort(reflections);
        pos = 0;
        for (itReflection = reflections.begin(); itReflection != reflections.end(); itReflection++)
        {
          ul = itReflection->first;
          ul1 = itReflection->second;
          if (pos)
          {
            sprintf(&buf[pos], ",%lu/%lu", ul, ul1);
          }
          else
          {
            sprintf(&buf[pos], "%lu/%lu", ul, ul1);
          }
          pos = strlen(buf);
        }
        GERTICO::Mapper::mapHandleValue(data[ind + 3], managerFederateReportInteractionsReceivedInteractionCounts, buf);
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
  int i;
  int len;

  len = strlen(theBuff);
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
void GERTICO::ManagementObjectModelLRC::getResignAction(GeRtiFactory::ResignAction &theResignAction, char *theBuff)
{
  int i;
  int len;

  len = strlen(theBuff);
  for (i = 0; i < len; i++)
  {
    theBuff[i] = tolower(theBuff[i]);
  }

  if (strcmp(theBuff, "release attributes") == 0)
  {
    theResignAction = GeRtiFactory::unconditionallyDivestAttributes;
    return;
  }

  if (strcmp(theBuff, "delete objects") == 0)
  {
    theResignAction = GeRtiFactory::deleteObjects;
    return;
  }

  if (strcmp(theBuff, "delete objects and release attributes") == 0)
  {
    theResignAction = GeRtiFactory::deleteObjectsThenDivest;
    return;
  }

  if (strcmp(theBuff, "no action") == 0)
  {
    theResignAction = GeRtiFactory::noAction;
    return;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::ManagementObjectModelLRC::getTransportationType(GeRtiFactory::GeRtiHandle &theTransportationType, char *theBuff)
{
  int i;
  int len;

  len = strlen(theBuff);
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
void GERTICO::ManagementObjectModelLRC::sendReportAlert(const GERTICO::MomAlert &theMomAlert)
{
  CORBA::ULong i;
  CORBA::ULong ind;
  CORBA::ULong len;
  GERTICO::AttributeDatum interactionDatum;
  GeRtiFactory::HandleValues handleValues;
  GeRtiFactory::UserSuppliedTag userSuppliedTag;
  char buf[256];
  unsigned long ul;

  handleValues.length(4);

  ind = 0;
  handleValues[ind].id = managerInteractionFederateFederate;
  ul = federateDB.federate;
  sprintf (buf, "%lu", ul);
  len = strlen(buf);
  handleValues[ind].value.length(len + 1);
  for (i = 0; i < len; i++)
  {
    handleValues[ind].value[i] = buf[i];
  }
  buf[len] = '\0';
  handleValues[ind].value[len] = buf[len];

  ind = 1;
  handleValues[ind].id = managerFederateReportAlertAlertSeverity;
  switch(theMomAlert.alertSeverityEnum)
  {
    case GERTICO::RtiExceptionEnum:
    {
      strcpy(buf, "RTI exception");
      break;
    }
    case GERTICO::RtiInternalErrorEnum:
    {
      strcpy(buf, "RTI internal error");
      break;
    }
    case GERTICO::RtiFederateErrorEnum:
    {
      strcpy(buf, "RTI federate error");
      break;
    }
    case GERTICO::RtiWarningEnum:
    {
      strcpy(buf, "RTI warning");
      break;
    }
    case GERTICO::RtiDiagnosticEnum:
    {
      strcpy(buf, "RTI diagnostic");
      break;
    }
  }
  len = strlen(buf);
  handleValues[ind].value.length(len + 1);
  for (i = 0; i < len; i++)
  {
    handleValues[ind].value[i] = buf[i];
  }
  buf[len] = '\0';
  handleValues[ind].value[len] = buf[len];

  ind = 2;
  handleValues[ind].id = managerFederateReportAlertAlertDescription;
  strcpy(buf, theMomAlert.alertDescription.c_str());
  len = strlen(buf);
  handleValues[ind].value.length(len + 1);
  for (i = 0; i < len; i++)
  {
    handleValues[ind].value[i] = buf[i];
  }
  buf[len] = '\0';
  handleValues[ind].value[len] = buf[len];

  ind = 3;
  handleValues[ind].id = managerFederateReportAlertAlertID;
  ul = theMomAlert.alertId;
  sprintf (buf, "%lu", ul);
  len = strlen(buf);
  handleValues[ind].value.length(len + 1);
  for (i = 0; i < len; i++)
  {
    handleValues[ind].value[i] = buf[i];
  }
  buf[len] = '\0';
  handleValues[ind].value[len] = buf[len];

  GERTICO::Mapper::mapUserSuppliedTag(userSuppliedTag, "MOM");

  if (federateDB.supportingServicesLRC->getInteractionAttributeDatum(managerFederateReportAlert, interactionDatum))
  {
    return;
  }

  if (federateDB.declarationManagementLRC->testInteractionSubscribers(managerFederateReportAlert))
  {
    eventMarket.addPushSupplierInteraction(managerFederateReportAlert, handleValues, userSuppliedTag, 0, interactionDatum);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::sendReportServiceInvocation(const GERTICO::MomReportServiceInvocation &theMomReportServiceInvocation)
{
  GERTICO::AttributeDatum interactionDatum;
  GERTICO::HandleSet subscribers;
  GeRtiFactory::HandleValues handleValues;
  GeRtiFactory::UserSuppliedTag userSuppliedTag;
  char buf[128];
  std::string tmpStr;
  unsigned long ul;

  handleValues.length(12);
  ul = federateDB.federate;
  sprintf(buf,"%lu", ul);
  GERTICO::Mapper::mapHandleValue(handleValues[0], managerInteractionFederateFederate, buf);
  GERTICO::Mapper::mapHandleValue(handleValues[1], managerFederateReportServiceInvocationService, theMomReportServiceInvocation.service.c_str());
  handleValues[2].id = managerFederateReportServiceInvocationInitiator;
  switch(theMomReportServiceInvocation.initiatorEnum)
  {
    case GERTICO::FederateEnum:
    {
      strcpy(buf, "Federate");
      break;
    }
    case GERTICO::RtiEnum:
    {
      strcpy(buf, "RTI");
      break;
    }
  }
  GERTICO::Mapper::mapHandleValue(handleValues[2], managerFederateReportServiceInvocationInitiator, buf);
  if (theMomReportServiceInvocation.successIndicator)
  {
    strcpy(buf, "True");
  }
  else
  {
    strcpy(buf, "False");
  }
  GERTICO::Mapper::mapHandleValue(handleValues[3], managerFederateReportServiceInvocationSuccessIndicator, buf);
  GERTICO::Mapper::mapHandleValue(handleValues[4], managerFederateReportServiceInvocationSuppliedArgument1, theMomReportServiceInvocation.suppliedArgument1.c_str());
  GERTICO::Mapper::mapHandleValue(handleValues[5], managerFederateReportServiceInvocationSuppliedArgument2, theMomReportServiceInvocation.suppliedArgument2.c_str());
  GERTICO::Mapper::mapHandleValue(handleValues[6], managerFederateReportServiceInvocationSuppliedArgument3, theMomReportServiceInvocation.suppliedArgument3.c_str());
  GERTICO::Mapper::mapHandleValue(handleValues[7], managerFederateReportServiceInvocationSuppliedArgument4, theMomReportServiceInvocation.suppliedArgument4.c_str());
  handleValues[8].id = managerFederateReportServiceInvocationSuppliedArgument5;
  GERTICO::Mapper::mapHandleValue(handleValues[8], managerFederateReportServiceInvocationSuppliedArgument5, theMomReportServiceInvocation.suppliedArgument5.c_str());
  GERTICO::Mapper::mapHandleValue(handleValues[9], managerFederateReportServiceInvocationReturnedArgument, theMomReportServiceInvocation.returnedArgument.c_str());
  GERTICO::Mapper::mapHandleValue(handleValues[10], managerFederateReportServiceInvocationExceptionDescription, theMomReportServiceInvocation.exceptionDescription.c_str());
  handleValues[11].id = managerFederateReportServiceInvocationExceptionID;
//  GERTICO::Mapper::mapHandleValue(handleValues[11], managerFederateReportServiceInvocationExceptionID, theMomReportServiceInvocation.exceptionId);
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
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GeRtiFactory::GeRtiHandle federate = 0;
  GERTICO::GeRtiFedTime *federationTime;
  bool gotTime = false;
  char buff[256];
  std::wstring objectName;
  std::string userSuppliedTag;
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
    }

    if (theData[i].id == managerFederateServiceDeleteObjectInstanceObjectInstance)
    {
      GERTICO::Mapper::mapWstringFromChar(objectName, buff);
    }

    if (theData[i].id == managerFederateServiceDeleteObjectInstanceTag)
    {
      userSuppliedTag = buff;
    }

    if (theData[i].id == managerFederateServiceDeleteObjectInstanceFederationTime)
    {
      gotTime = true;
      federationTime = geRtiFedTimeFactory.decode(buff);
    }
  }

  if (gotTime)
  {
    GERTICO::MomDeleteObjectInstanceWithTime *momDeleteObjectInstanceWithTime;
    momDeleteObjectInstanceWithTime = new GERTICO::MomDeleteObjectInstanceWithTime(objectName, userSuppliedTag, federationTime, *geRtiSender);
    federateDB.momJobs.add(momDeleteObjectInstanceWithTime);
    ps.release();
  }
  else
  {
    GERTICO::MomDeleteObjectInstance *momDeleteObjectInstance;
    momDeleteObjectInstance = new GERTICO::MomDeleteObjectInstance(objectName, userSuppliedTag, *geRtiSender);
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
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomDisableAsynchronousDelivery *momDisableAsynchronousDelivery;
  GeRtiFactory::GeRtiHandle federate = 0;
  char buff[256];
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
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
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomDisableTimeConstrained *momDisableTimeConstrained;
  GeRtiFactory::GeRtiHandle federate = 0;
  char buff[256];
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
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
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomDisableTimeRegulation *momDisableTimeRegulation;
  GeRtiFactory::GeRtiHandle federate = 0;
  char buff[256];
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
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
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomEnableAsynchronousDelivery *momEnableAsynchronousDelivery;
  GeRtiFactory::GeRtiHandle federate = 0;
  char buff[256];
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
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
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomEnableTimeConstrained *momEnableTimeConstrained;
  GeRtiFactory::GeRtiHandle federate = 0;
  char buff[256];
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
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
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomEnableTimeRegulation *momEnableTimeRegulation;
  GeRtiFactory::GeRtiHandle federate = 0;
  GERTICO::GeRtiFedTime *federationTime;
  GERTICO::GeRtiLogicalTimeInterval *lookahead;
  char buff[256];
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
    }

    if (theData[i].id == managerFederateServiceEnableTimeRegulationFederationTime)
    {
      federationTime = geRtiFedTimeFactory.decode(buff);
    }

    if (theData[i].id == managerFederateServiceEnableTimeRegulationLookahead)
    {
      GERTICO::GeRtiEncodedLogicalTimeInterval *elti = new GeRtiEncodedLogicalTimeIntervalI(buff, 8);
      lookahead = geRtiLogicalTimeIntervalFactory.decode(*elti);
    }
  }

  momEnableTimeRegulation = new GERTICO::MomEnableTimeRegulation(federationTime, lookahead, *geRtiSender);
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
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomFederateRestoreComplete *momFederateRestoreComplete;
  GeRtiFactory::GeRtiHandle federate = 0;
  char buff[256];
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
    }

    if (theData[i].id == managerFederateServiceFederateRestoreCompleteSuccessIndicator)
    {
      getBoolean(successIndicator, buff);
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
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomFederateSaveBegun *momFederateSaveBegun;
  GeRtiFactory::GeRtiHandle federate = 0;
  char buff[256];
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
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
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomFederateSaveComplete *momFederateSaveComplete;
  GeRtiFactory::GeRtiHandle federate = 0;
  char buff[256];
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
    }

    if (theData[i].id == managerFederateServiceFederateSaveCompleteSuccessIndicator)
    {
      getBoolean(successIndicator, buff);
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
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomFlushQueueRequest *momFlushQueueRequest;
  GeRtiFactory::GeRtiHandle federate = 0;
  GERTICO::GeRtiFedTime *federationTime;
  char buff[256];
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
    }

    if (theData[i].id == managerFederateServiceFlushQueueRequestFederationTime)
    {
      federationTime = geRtiFedTimeFactory.decode(buff);
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
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomLocalDeleteObjectInstance *momLocalDeleteObjectInstance;
  GeRtiFactory::GeRtiHandle federate = 0;
  char buff[256];
  std::wstring objectName;
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
    }

    if (theData[i].id == managerFederateServiceLocalDeleteObjectInstanceObjectInstance)
    {
      GERTICO::Mapper::mapWstringFromChar(objectName, buff);
    }
  }

  momLocalDeleteObjectInstance = new GERTICO::MomLocalDeleteObjectInstance(objectName, *geRtiSender);
  federateDB.momJobs.add(momLocalDeleteObjectInstance);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceChangeAttributeTransportationType(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomChangeAttributeTransportationType *momChangeAttributeTransportationType;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::Handles attributes;
  GeRtiFactory::GeRtiHandle transportationType;
  char buff[256];
  std::wstring objectName;
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
    }

    if (theData[i].id == managerFederateServiceChangeAttributeTransportationTypeObjectInstance)
    {
      GERTICO::Mapper::mapWstringFromChar(objectName, buff);
    }

    if (theData[i].id == managerFederateServiceChangeAttributeTransportationTypeAttributeList)
    {
      getAttributes(attributes, buff);
    }

    if (theData[i].id == managerFederateServiceChangeAttributeTransportationTypeTransportationType)
    {
      if (getTransportationType(transportationType, buff))
      {
        return;
      }
    }
  }

  momChangeAttributeTransportationType = new GERTICO::MomChangeAttributeTransportationType(objectName, attributes, transportationType, *geRtiSender);
  federateDB.momJobs.add(momChangeAttributeTransportationType);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceChangeAttributeOrderType(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomChangeAttributeOrderType *momChangeAttributeOrderType;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::Handles attributes;
  GeRtiFactory::GeRtiHandle orderType;
  char buff[256];
  std::wstring objectName;
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
    }

    if (theData[i].id == managerFederateServiceChangeAttributeOrderTypeObjectInstance)
    {
      GERTICO::Mapper::mapWstringFromChar(objectName, buff);
    }

    if (theData[i].id == managerFederateServiceChangeAttributeOrderTypeAttributeList)
    {
      getAttributes(attributes, buff);
    }

    if (theData[i].id == managerFederateServiceChangeAttributeOrderTypeOrderingType)
    {
      getOrderType(orderType, buff);
    }
  }

  momChangeAttributeOrderType = new GERTICO::MomChangeAttributeOrderType(objectName, attributes, orderType, *geRtiSender);
  federateDB.momJobs.add(momChangeAttributeOrderType);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceChangeInteractionTransportationType(const GeRtiFactory::HandleValues &theData)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceChangeChangeInteractionOrderType(const GeRtiFactory::HandleValues &theData)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceModifyLookahead(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomModifyLookahead *momModifyLookahead;
  GeRtiFactory::GeRtiHandle federate = 0;
  GERTICO::GeRtiLogicalTimeInterval *lookahead;
  char buff[256];
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
    }

    if (theData[i].id == managerFederateServiceModifyLookaheadLookahead)
    {
      GERTICO::GeRtiEncodedLogicalTimeInterval *elti = new GeRtiEncodedLogicalTimeIntervalI(buff, 8);
      lookahead = geRtiLogicalTimeIntervalFactory.decode(*elti);
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
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomNextEventRequest *momNextEventRequest;
  GeRtiFactory::GeRtiHandle federate = 0;
  GERTICO::GeRtiFedTime *federationTime;
  char buff[256];
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
    }

    if (theData[i].id == managerFederateServiceNextEventRequestFederationTime)
    {
      federationTime = geRtiFedTimeFactory.decode(buff);
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
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomNextEventRequestAvailable *momNextEventRequestAvailable;
  GeRtiFactory::GeRtiHandle federate = 0;
  GERTICO::GeRtiFedTime *federationTime;
  char buff[256];
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
    }

    if (theData[i].id == managerFederateServiceNextEventRequestAvailableFederationTime)
    {
      federationTime = geRtiFedTimeFactory.decode(buff);
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
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomPublishInteractionClass *momPublishInteractionClass;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::GeRtiHandle interactionClass = 0;
  char buff[256];
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
    }

    if (theData[i].id == managerFederateServicePublishInteractionClassInteractionClass)
    {
      sscanf(buff, "%lu", &ul);
      interactionClass = ul;
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
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomPublishObjectClass *momPublishObjectClass;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::GeRtiHandle objectClass;
  GeRtiFactory::Handles attributes;
  char buff[256];
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
    }

    if (theData[i].id == managerFederateServicePublishObjectClassObjectClass)
    {
      sscanf(buff, "%lu", &ul);
      objectClass = ul;
    }

    if (theData[i].id == managerFederateServicePublishObjectClassAttributeList)
    {
      getAttributes(attributes, buff);
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
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomResignFederationExecution *momResignFederationExecution;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::ResignAction resignAction;
  char buff[256];
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
    }

    if (theData[i].id == managerFederateServiceResignFederationExecutionResignAction)
    {
      getResignAction(resignAction, buff);
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
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    if (theData[i].id == managerInteractionFederateFederate)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theData[i].value);
      sscanf(cptr, "%lu", &ul);
      federate = ul;
      delete[] cptr;
      if (federate != federateDB.federate)
      {
        return;
      }
    }

    if (theData[i].id == managerFederateServiceSubscribeInteractionClassInteractionClass)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theData[i].value);
      sscanf(cptr, "%lu", &ul);
      interactionClass = ul;
      delete[] cptr;
    }

    if (theData[i].id == managerFederateServiceSubscribeInteractionClassActive)
    {
      GERTICO::Mapper::mapOctetSequence(&cptr, theData[i].value);
      activeStr = cptr;
      delete[] cptr;
      GERTICO::Mapper::nameToLower(activeStr);
      if (activeStr == "true")
      {
        active = 1;
      }
      else
      {
        active = 0;
      }
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
  CORBA::Boolean active;
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomSubscribeObjectClassAttributes *momSubscribeObjectClassAttributes;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::GeRtiHandle objectClass;
  GeRtiFactory::Handles attributes;
  char buff[256];
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
    }

    if (theData[i].id == managerFederateServiceSubscribeObjectClassAttributesObjectClass)
    {
      sscanf(buff, "%lu", &ul);
      objectClass = ul;
    }

    if (theData[i].id == managerFederateServiceSubscribeObjectClassAttributesAttributeList)
    {
      getAttributes(attributes, buff);
    }

    if (theData[i].id == managerFederateServiceSubscribeObjectClassAttributesActive)
    {
      getBoolean(active, buff);
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
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomSynchronizationPointAchieved *momSynchronizationPointAchieved;
  GeRtiFactory::GeRtiHandle federate = 0;
  char buff[256];
  std::wstring label;
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
    }

    if (theData[i].id == managerFederateServiceSynchronizationPointAchievedLabel)
    {
      GERTICO::Mapper::mapWstringFromChar(label, buff);
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
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomTimeAdvanceRequest *momTimeAdvanceRequest;
  GeRtiFactory::GeRtiHandle federate = 0;
  GERTICO::GeRtiFedTime *federationTime;
  char buff[256];
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
    }

    if (theData[i].id == managerFederateServiceTimeAdvanceRequestFederationTime)
    {
      federationTime = geRtiFedTimeFactory.decode(buff);
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
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomTimeAdvanceRequestAvailable *momTimeAdvanceRequestAvailable;
  GeRtiFactory::GeRtiHandle federate = 0;
  GERTICO::GeRtiFedTime *federationTime;
  char buff[256];
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
    }

    if (theData[i].id == managerFederateServiceTimeAdvanceRequestAvailableFederationTime)
    {
      federationTime = geRtiFedTimeFactory.decode(buff);
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
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomUnconditionalAttributeOwnershipDivestiture *momUnconditionalAttributeOwnershipDivestiture;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::Handles attributes;
  char buff[256];
  std::wstring objectName;
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
    }

    if (theData[i].id == managerFederateServiceUnconditionalAttributeOwnershipDivestitureObjectInstance)
    {
      GERTICO::Mapper::mapWstringFromChar(objectName, buff);
    }

    if (theData[i].id == managerFederateServiceUnconditionalAttributeOwnershipDivestitureAttributeList)
    {
      getAttributes(attributes, buff);
    }
  }

  momUnconditionalAttributeOwnershipDivestiture = new GERTICO::MomUnconditionalAttributeOwnershipDivestiture(objectName, attributes, *geRtiSender);
  federateDB.momJobs.add(momUnconditionalAttributeOwnershipDivestiture);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ManagementObjectModelLRC::serviceUnpublishInteractionClass(const GeRtiFactory::HandleValues &theData)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomUnpublishInteractionClass *momUnpublishInteractionClass;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::GeRtiHandle interactionClass;
  char buff[256];
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
    }

    if (theData[i].id == managerFederateServiceUnpublishInteractionClassInteractionClass)
    {
      sscanf(buff, "%lu", &ul);
      interactionClass = ul;
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
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomUnpublishObjectClass *momUnpublishObjectClass;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::GeRtiHandle objectClass;
  char buff[256];
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
    }

    if (theData[i].id == managerFederateServiceUnpublishObjectClassObjectClass)
    {
      sscanf(buff, "%lu", &ul);
      objectClass = ul;
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
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomUnsubscribeInteractionClass *momUnsubscribeInteractionClass;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::GeRtiHandle interactionClass;
  char buff[256];
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
    }

    if (theData[i].id == managerFederateServiceUnsubscribeInteractionClassInteractionClass)
    {
      sscanf(buff, "%lu", &ul);
      interactionClass = ul;
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
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::MomUnsubscribeObjectClass *momUnsubscribeObjectClass;
  GeRtiFactory::GeRtiHandle federate = 0;
  GeRtiFactory::GeRtiHandle objectClass;
  char buff[256];
  unsigned long ul;

  lengthi = theData.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = theData[i].value.length();
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = theData[i].value[j];
    }
    buff[lengthj] = '\0';

    if (theData[i].id == managerInteractionFederateFederate)
    {
      sscanf(buff, "%lu", &ul);
      federate = ul;
      if (federate != federateDB.federate)
      {
        return;
      }
    }

    if (theData[i].id == managerFederateServiceUnsubscribeObjectClassObjectClass)
    {
      sscanf(buff, "%lu", &ul);
      objectClass = ul;
    }
  }

  momUnsubscribeObjectClass = new GERTICO::MomUnsubscribeObjectClass(objectClass, *geRtiSender);
  federateDB.momJobs.add(momUnsubscribeObjectClass);
  ps.release();
}
