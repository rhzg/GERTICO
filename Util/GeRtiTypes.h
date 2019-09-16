/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: GeRtiTypes.h,v $
Revision 1.14  2010/05/14 13:31:11  mul
Add logical time interval.

Revision 1.13  2009/05/07 12:14:13  mul
Change location of time enums.

Revision 1.12  2008/01/30 10:17:38  mul
Changes for ieee1516.

Revision 1.11  2007/09/05 15:06:20  mul
Changes for ieee1516.

Revision 1.10  2007/05/15 13:12:28  mul
Changes for combined 1.3 and 1516 logic.

Revision 1.9  2007/05/09 11:29:09  mul
Generic time for gerti / lrc.

Revision 1.8  2007/05/03 14:35:50  mul
Remove HLA1.3 types.

Revision 1.7  2007/05/02 14:22:23  mul
Change include.

Revision 1.6  2007/02/07 09:28:42  mul
Add an auto ptr template.

Revision 1.5  2006/09/05 09:22:30  mul
Include file path changed.

Revision 1.4  2006/08/08 14:08:14  mul
Move named object map to registered object.

Revision 1.3  2006/08/01 11:23:41  mul
Add some new types.

Revision 1.2  2005/06/28 13:40:16  mul
Change for save with time.

Revision 1.1  2005/06/17 12:37:15  mul
Make unique names for objects in class scope.


**
*******************************************************************************/


#ifndef GeRtiTypes_H_
#define GeRtiTypes_H_

#include <map>
#include <set>
#include <string>

#include "GeRtiFedTime.h"
#include "idl/GeRtiFactoryC.h"

namespace GERTICO
{
  enum AlertSeverityEnum
  {
    RtiExceptionEnum,
    RtiInternalErrorEnum,
    RtiFederateErrorEnum,
    RtiWarningEnum,
    RtiDiagnosticEnum
  };

  enum FederateState
  {
    Running,
    SavePending,
    Saving,
    RestorePending,
    Restoring
  };

  enum TimeServiceFlag
  {
    idleFlag,
    nextEventFlag,
    nextEventAvailableFlag,
    timeAdvanceFlag,
    timeAdvanceAvailableFlag,
    flushQueueRequestFlag
  };

  template<class X> class AutoPtr;

  template<class X> class AutoPtrRef {
  public:
    inline AutoPtrRef(AutoPtr<X> &ref)
        : _ref(ref)
    {
        // This block intentionally left blank
    }

  private:
    AutoPtr<X> &_ref;
  };

  template<class X> class AutoPtr
  {
  public:
    inline explicit AutoPtr(X* p = 0) throw()
        : _ptr(p)
    {
        // This block intentionally left blank
    }

    inline ~AutoPtr() throw()
    {
        reset();
    }

//    inline AutoPtr(AutoPtr &a) throw()
//        : _ptr(a.ptr)
//    {
//        a._ptr = 0;
//    }

//    template<class Y> AutoPtr(AutoPtr<Y> &a) throw()
//        : _ptr(a.ptr)
//    {
//        a._ptr = 0;
//    }

    inline AutoPtr &operator=(AutoPtr &a) throw()
    {
        reset(a.release());
        return(*this);
    }

//    template<class Y> AutoPtr &operator=(AutoPtr<Y> &a) throw()
//    {
//        reset(a.release());
//        return(*this);
//    }

    inline X *get() const throw()
    {
        return(_ptr);
    }

    inline X &operator*() const throw()
    {
        return(*_ptr);
    }

    inline X *operator->() const throw()
    {
        return(_ptr);
    }

    inline X* release() throw()
    {
        X *t = _ptr;
        _ptr = 0;
        return(t);
    }

    inline void reset(X *p = 0) throw()
    {
        if (p != _ptr)
        {
            delete _ptr;
            _ptr = p;
        }
    }

    AutoPtr(AutoPtrRef<X> obj) throw()
        : _ptr(obj)
    {
        // This block intentionally left blank
    }

    template<class Y> operator AutoPtrRef<Y>() throw()
    {
        return(AutoPtrRef<Y>(_ptr));
    }

    template<class Y> operator AutoPtr<Y>() throw()
    {
        return(AutoPtr<Y>(release()));
    }

  private:
    X* _ptr;
  };

//  typedef std::auto_ptr<RTI::FedTime> FedTimePtr;
//  typedef AutoPtr<GERTICO::GeRtiFedTime> GeRtiFedTimeAutoPtr;

  enum InitiatorEnum
  {
    FederateEnum,
    RtiEnum
  };

  struct CmpHandle
  {
    bool operator()(const GeRtiFactory::GeRtiHandle s1, const GeRtiFactory::GeRtiHandle s2) const
    {
      return s1 < s2;
    }
  };

#ifdef IEEE_1516
  class MomException
  {
  public:
    GeRtiFactory::GeRtiHandle federate;
    std::wstring service;
    std::wstring exception;
  };
#else
  class MomAlert
  {
  public:
    GeRtiFactory::GeRtiHandle federate;
    AlertSeverityEnum alertSeverityEnum;
    std::string alertDescription;
    GeRtiFactory::GeRtiHandle alertId;
  };
#endif

  class MomReportServiceInvocation
  {
  public:
    InitiatorEnum initiatorEnum;
    bool successIndicator;
#ifdef IEEE_1516
    std::wstring service;
    std::wstring suppliedArguments;
    std::wstring returnedArguments;
    std::wstring exception;
    GeRtiFactory::GeRtiHandle serialNumber;
#else
    std::string service;
    std::string suppliedArgument1;
    std::string suppliedArgument2;
    std::string suppliedArgument3;
    std::string suppliedArgument4;
    std::string suppliedArgument5;
    std::string returnedArgument;
    std::string exceptionDescription;
    GeRtiFactory::GeRtiHandle exceptionId;
#endif
  };

  struct cmpHandle
  {
    bool operator()(const GeRtiFactory::GeRtiHandle s1, const GeRtiFactory::GeRtiHandle s2) const
    {
      return s1 < s2;
    }
  };

  struct cmpString
  {
    bool operator()(const std::string s1, const std::string s2) const
    {
      return s1 < s2;
    }
  };

  struct cmpWstring
  {
    bool operator()(const std::wstring s1, const std::wstring s2) const
    {
      return s1 < s2;
    }
  };

  typedef std::set <GeRtiFactory::GeRtiHandle, cmpHandle> HandleSet;
  typedef std::set <std::string, cmpString> StringSet;
  typedef std::map <GeRtiFactory::GeRtiHandle, GERTICO::HandleSet, cmpHandle> HandleSetMap;
  typedef std::map <GeRtiFactory::GeRtiHandle, GERTICO::HandleSetMap, cmpHandle> HandleSetSetMap;

  typedef std::map <GeRtiFactory::GeRtiHandle, GeRtiFactory::GeRtiHandle, cmpHandle> HandleMap;
  typedef std::map <GeRtiFactory::GeRtiHandle, GERTICO::HandleMap, cmpHandle> HandleMapMap;

  typedef std::map <GeRtiFactory::GeRtiHandle, bool, cmpHandle> HandleBoolMap;

  typedef std::map <std::wstring, GeRtiFactory::GeRtiHandle, cmpWstring> WstringHandleMap;
  typedef std::map <GeRtiFactory::GeRtiHandle, std::wstring, cmpHandle> HandleWstringMap;
  typedef std::map <GeRtiFactory::GeRtiHandle, GERTICO::WstringHandleMap, cmpHandle> HandleWstringHandleMap;
  typedef std::map <GeRtiFactory::GeRtiHandle, GERTICO::HandleWstringMap, cmpHandle> HandleHandleWstringMap;

  class AttributeDatum
  {
  public:
    std::wstring name;
		GeRtiFactory::GeRtiHandle theOrderType;
		GeRtiFactory::GeRtiHandle theTransportationType;
    GERTICO::HandleSet theDimensions;
  };

  // Attribute handle / Attribute Datum
  typedef std::map <GeRtiFactory::GeRtiHandle, AttributeDatum, cmpHandle> AttributeDatumMap;
  // Object Class / Attributes
  typedef std::map <GeRtiFactory::GeRtiHandle, AttributeDatumMap, cmpHandle> AttributeDataMap;
};

#endif
