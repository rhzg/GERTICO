/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/SpecificConfig.h
***********************************************************************/

// Purpose: This file contains definitions that are used to isolate
// platform configuration issues.  The contents of this file are completely
// implementation-specific.

#ifndef RTI_SpecificConfig_h
#define RTI_SpecificConfig_h

#include <sys/types.h> // for size_t

// macro to support Windows library export mechanism
#ifdef _WIN32
#ifdef BUILDING_RTI
#define RTI_EXPORT __declspec(dllexport)
#else
#define RTI_EXPORT
#endif
#else
#define RTI_EXPORT
#endif

#ifdef  DCT_DEBUG_ON
#define RTI_DEBUG_ON
#endif

//
// When and how to use inline methods is left up to the RTI implementor
//
#ifdef  RTI_DEBUG_ON
#undef  RTI_USE_INLINE
#define RTI_INLINE /* inline */
#else
#define RTI_USE_INLINE
#define RTI_INLINE inline
#endif // RTI_DEBUG_ON

#ifdef    __GNUC__
#ifndef RTI_TEMPLATES_REQUIRE_SOURCE
//#define RTI_TEMPLATES_REQUIRE_SOURCE
#endif
#endif // __GNUC__

#endif // RTI_SpecificConfig_h
