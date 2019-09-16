/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
** Jobs.h
**
*******************************************************************************/

#ifndef Jobs_H_
#define Jobs_H_

#include <vector>

#include "idl/GeRtiFactoryS.h"
#include "Util/Federate.h"
#include "Util/GeRtiTypes.h"
#include "Util/JobHolder.h"

namespace GERTICO
{
  class AnnounceObjectJob : public virtual GERTICO::Job
  {
    GERTICO::FederatesHolder &federatesHolder;
    GERTICO::HandleSet attributes;
    std::wstring objectName;
    GeRtiFactory::GeRtiHandle classId;
    GeRtiFactory::GeRtiHandle fedId;
    GeRtiFactory::GeRtiHandle objectId;

  public:
    AnnounceObjectJob(const GeRtiFactory::GeRtiHandle &theClass, const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObject, GERTICO::FederatesHolder &theFederatesHolder, const std::wstring &theName, GERTICO::HandleSet &theAttributes);
    virtual ~AnnounceObjectJob();

    GERTICO::JobStatus execute (void);
  };

  class BeginFederationRestoreJob : public virtual GERTICO::Job
  {
    GERTICO::FederatesHolder &federatesHolder;
    GeRtiFactory::GeRtiHandle fed;
    bool &restoreStatus;
    bool success;
    std::wstring label;

  public:

    BeginFederationRestoreJob(GERTICO::FederatesHolder &theFederatesHolder, const GeRtiFactory::GeRtiHandle &theFederate, const std::wstring &theLabel, const bool &theSuccess, bool &theRestoreStatus);
    virtual ~BeginFederationRestoreJob (void);

    GERTICO::JobStatus execute (void);
  };

  class DiscoverObjectJob : public virtual GERTICO::Job
  {
    GERTICO::FederatesHolder &federatesHolder;
    std::wstring objectName;
    GeRtiFactory::GeRtiHandle classId;
    GeRtiFactory::GeRtiHandle fedId;
    GeRtiFactory::GeRtiHandle objectId;

  public:
    DiscoverObjectJob(const GeRtiFactory::GeRtiHandle &theClass, const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObject, GERTICO::FederatesHolder &theFederatesHolder, const std::wstring &theName);
    virtual ~DiscoverObjectJob();

    GERTICO::JobStatus execute (void);
  };

  class FederationRestoredJob : public virtual GERTICO::Job
  {
    GERTICO::FederatesHolder &federatesHolder;
    GeRtiFactory::RestoreFailureReason failureReason;
    bool &concurrencyFlag;
    bool &status;
    bool success;

  public:

    FederationRestoredJob(GERTICO::FederatesHolder &theFederatesHolder, bool &theStatus, const bool &theSuccess, const GeRtiFactory::RestoreFailureReason &theFailureReason, bool &theConcurrencyFlag);
    virtual ~FederationRestoredJob (void);

    GERTICO::JobStatus execute (void);
  };

  class FederationSavedJob : public virtual GERTICO::Job
  {
    GERTICO::FederatesHolder &federatesHolder;
    GeRtiFactory::SaveFailureReason failureReason;
    bool &concurrencyFlag;
    bool &status;
    bool success;

  public:

    FederationSavedJob(GERTICO::FederatesHolder &theFederatesHolder, bool &theStatus, const bool &theSuccess, const GeRtiFactory::SaveFailureReason &theFailureReason, bool &theConcurrencyFlag);
    virtual ~FederationSavedJob (void);

    GERTICO::JobStatus execute (void);
  };

  class IntoScopeJob : public virtual GERTICO::Job
  {
    GERTICO::FederatesHolder &federatesHolder;
    unsigned long fedId;
  public:
    unsigned long objectId;
    GERTICO::HandleSet items;

    IntoScopeJob(const unsigned long &, const unsigned long &, GERTICO::HandleSet &, GERTICO::FederatesHolder &theFederatesHolder);
    virtual ~IntoScopeJob ();

    GERTICO::JobStatus execute ();
  };

  class OutOfScopeJob : public virtual GERTICO::Job
  {
    GERTICO::FederatesHolder &federatesHolder;
    bool sendFlag;
    unsigned long fedId;
  public:
    unsigned long objectId;
    GERTICO::HandleSet items;

    OutOfScopeJob(const unsigned long &theFed, const unsigned long &theObj, const GERTICO::HandleSet &p_item, GERTICO::FederatesHolder &theFederatesHolder, const bool &theSendFlag);
    virtual ~OutOfScopeJob ();

    GERTICO::JobStatus execute ();
  };

  class ProvideUpdateJob : public virtual GERTICO::Job
  {
    GERTICO::FederatesHolder &federatesHolder;
    GeRtiFactory::GeRtiHandle fedId;
    GeRtiFactory::GeRtiHandle objectId;
    GeRtiFactory::Handles att;
    GeRtiFactory::UserSuppliedTag tag;

  public:

    ProvideUpdateJob(const GeRtiFactory::GeRtiHandle &theObject, GERTICO::HandleSet &theAttributes, const GeRtiFactory::UserSuppliedTag &theTag, const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::FederatesHolder &theFederatesHolder);
    virtual ~ProvideUpdateJob(void);

    GERTICO::JobStatus execute();
  };

  class RemoveObject : public virtual GERTICO::Job
  {
    GeRtiFactory::ERHandle myERHandle;
    GERTICO::FederatesHolder &federatesHolder;
    GeRtiFactory::GeRtiHandle fedId;
    GeRtiFactory::GeRtiHandle objectId;
    GeRtiFactory::UserSuppliedTag tag;
    GeRtiFactory::Time myTime;
    bool withTime;

  public:

    RemoveObject(const GeRtiFactory::GeRtiHandle &, const GeRtiFactory::GeRtiHandle &, GERTICO::FederatesHolder &theFederatesHolder, const GeRtiFactory::UserSuppliedTag &theTag);
    RemoveObject(const GeRtiFactory::GeRtiHandle &, const GeRtiFactory::GeRtiHandle &, GERTICO::FederatesHolder &theFederatesHolder, const GeRtiFactory::Time &, const GeRtiFactory::UserSuppliedTag &, const GeRtiFactory::ERHandle &);
    virtual ~RemoveObject (void);

    GERTICO::JobStatus execute (void);
  };

  class ReserveObjectInstanceNameJob : public virtual GERTICO::Job
  {
    GERTICO::FederatesHolder &federatesHolder;
    GeRtiFactory::GeRtiHandle fed;
    std::wstring objectName;

  public:
    ReserveObjectInstanceNameJob(GERTICO::FederatesHolder &theFederatesHolder, GeRtiFactory::GeRtiHandle const &theFed, std::wstring const &theObjectInstanceName);
    ~ReserveObjectInstanceNameJob (void);

    GERTICO::JobStatus execute (void);
  };

  class TurnOffForObjectInstance : public virtual GERTICO::Job
  {
    GERTICO::FederatesHolder &federatesHolder;
    GERTICO::HandleSetMap attributeSubscribers;
    unsigned long fedId;
  public:
    unsigned long objectId;

    TurnOffForObjectInstance(CORBA::ULong const &theFederate, CORBA::ULong const &theObject, GERTICO::HandleSetMap const &theAttributeSubscribers, GERTICO::FederatesHolder &theFederatesHolder);
    virtual ~TurnOffForObjectInstance ();

    GERTICO::JobStatus execute ();
  };

  class TurnOnForObjectInstance : public virtual GERTICO::Job
  {
    GERTICO::FederatesHolder &federatesHolder;
    GERTICO::HandleSetMap attributeSubscribers;
    unsigned long fedId;
  public:
    unsigned long objectId;

    TurnOnForObjectInstance(CORBA::ULong const &theFederate, CORBA::ULong const &theObject, GERTICO::HandleSetMap const &theAttributeSubscribers, GERTICO::FederatesHolder &theFederatesHolder);
    virtual ~TurnOnForObjectInstance ();

    GERTICO::JobStatus execute ();
  };
};

#endif /* Jobs_H_  */
