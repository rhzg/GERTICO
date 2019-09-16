/*****************************************************************************
**                                                                          **
** IITB, Karlsruhe                                                          **
**                                                                          **
******************************************************************************
**                                                                          **
** Project      : GERTICO                                                   **
** Sub-Project  : logging system                                            **
**                                                                          **
*****************************************************************************/
/*
** File(s)      : global.h
** Component(s) : -
** Device(s)    : Windows NT, Visual C++
** Terminology  : -
**              :
** Definition   : 
** Author       : Reinhard Bähre, FhG-IITB
** Date         : 13.09.2002
**              :
** Version      : 0.1 Beta
** Date         :
** Status       : untested
**              :
** Description  : 
**              :
******************************************************************************/

#ifndef __Global__included__
#define __Global__included__

#ifndef _WIN32
#define _getpid getpid
#endif

/*****************************************************************************
****  DLL MACROS                                                          ****
*****************************************************************************/

#ifndef _BENCHMARK

  #ifdef _WIN32
// disable warning about exceptions not being part of a method's signature
    #pragma warning(disable: 4290)
// disable warnings about deriving a "dllexport" class from a regular class
    #pragma warning(disable: 4275)
    #pragma warning(disable: 4251)
    #ifdef BUILDING_GAL
// define the proper qualifiers to import/export symbols from/to DLL
      #define GAL_EXPORT __declspec(dllexport)
    #else // !BUILDING_GAL
      #define GAL_EXPORT __declspec(dllimport)
    #endif // BUILDING_GAL
  #else // !WIN32
// no special qualfifers are necessary on non-WIN32 platforms
    #define GAL_EXPORT
  #endif

#else

  #ifdef _WIN32
// disable warning about exceptions not being part of a method's signature
  #pragma warning(disable: 4290)
  #define GAL_EXPORT
  #endif

#endif

/*****************************************************************************
****  INCLUDES/DEFINITIONS                                                ****
*****************************************************************************/

#define false 0
#define true 1

#define GAL_TXT 512
#define GAL_CTXT 512
#define GAL_CTXT_MAX 128
#define GAL_MSG_TXT 512
#define GAL_NAME 128
#define GAL_VERSION 128
#define GAL_FMT 128
#define GAL_FILENAME 128
#define GAL_PATH_FILENAME 512
#define GAL_STRING_LINE 256
#define GAL_LEVEL_GROUP 128

#define GAL_LST_EVENT_INIT 5
#define GAL_LST_LOGGER_INIT 5
#define GAL_LST_PARAM_INIT 5
#define GAL_LST_FORMAT_INIT 5
#define GAL_LST_APPENDER_INIT 5
#define GAL_LST_LAYOUT_INIT 5
#define GAL_LST_REPOSITORY_L_INIT 5

enum GAL_LEVEL {lminLEVEL,lDEBUG,lINFO,lWARN,lERROR,lmaxLEVEL};
enum GAL_APPENDER {aNULL,aSTDOUT,aFILE,aBUFFER};

/*****************************************************************************
****  CLASS DEFINITIONS                                                   ****
*****************************************************************************/

/****************************************************************************/

#endif
