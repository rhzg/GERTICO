/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**
** MODULE
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: Typedefs.cpp,v $
Revision 1.1  2007/12/06 11:26:29  mul
Changes for ieee1516.

 
**
*******************************************************************************/

#include "RTI/1516.h"

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring RTI::FederateHandle::toString() const
{
  std::wstring result;
  wchar_t wc[128];

  swprintf(wc, 128, L"%ld", _impl);
  result = wc;
  return result;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring RTI::ObjectClassHandle::toString() const
{
  std::wstring result;
  wchar_t wc[128];

  swprintf(wc, 128, L"%ld", _impl);
  result = wc;
  return result;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring RTI::InteractionClassHandle::toString() const
{
  std::wstring result;
  wchar_t wc[128];

  swprintf(wc, 128, L"%ld", _impl);
  result = wc;
  return result;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring RTI::ObjectInstanceHandle::toString() const
{
  std::wstring result;
  wchar_t wc[128];

  swprintf(wc, 128, L"%ld", _impl);
  result = wc;
  return result;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring RTI::AttributeHandle::toString() const
{
  std::wstring result;
  wchar_t wc[128];

  swprintf(wc, 128, L"%ld", _impl);
  result = wc;
  return result;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring RTI::ParameterHandle::toString() const
{
  std::wstring result;
  wchar_t wc[128];

  swprintf(wc, 128, L"%ld", _impl);
  result = wc;
  return result;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring RTI::DimensionHandle::toString() const
{
  std::wstring result;
  wchar_t wc[128];

  swprintf(wc, 128, L"%ld", _impl);
  result = wc;
  return result;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring RTI::MessageRetractionHandle::toString() const
{
  std::wstring result;
  wchar_t wc[128];

  swprintf(wc, 128, L"%ld", _impl);
  result = wc;
  return result;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring RTI::RegionHandle::toString() const
{
  std::wstring result;
  wchar_t wc[128];

  swprintf(wc, 128, L"%ld", _impl);
  result = wc;
  return result;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring RTI::RestoreFailureReason::toString() const
{
  std::wstring result;
  wchar_t wc[128];

  swprintf(wc, 128, L"%d", _RestoreFailureReason);
  result = wc;
  return result;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring RTI::SaveFailureReason::toString() const
{
  std::wstring result;
  wchar_t wc[128];

  swprintf(wc, 128, L"%d", _saveFailureReason);
  result = wc;
  return result;
}
