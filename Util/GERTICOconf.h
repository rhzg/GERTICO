/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** GERTICOconf.h
**
*******************************************************************************/

#ifndef GERTICOconf_HEADER
#define GERTICOconf_HEADER

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <string>

#include "Util/Mapper.h"

enum OMT_TYPE { FOM, SOM };

/*******************************************************************************
**
**
*******************************************************************************/
class NS
{
public:
  char* endPoint;
  char* rootEntry;
};


/*******************************************************************************
**
**
*******************************************************************************/
class GERTICOconf
{
protected:
  static GERTICOconf* singelton;
  GERTICOconf() {};

public:
    char* DTDfile;
    std::string gertiHub;
    std::string logicalTimeLibrary;
    std::string syncScope;
    GERTICO::StringSet configuredHubs;
    unsigned int resignAction;
    unsigned long dataLength;
    unsigned long transmissionWait_ms;
    NS *ns;

    virtual ~GERTICOconf() {};

    static GERTICOconf* parseFromFile (const std::string &fileName);

    virtual bool hasMorePath () = 0;
    virtual char* nextPath() = 0;
    virtual void resetPath() = 0;

    static bool  _hasMorePath() { if (singelton != 0) return singelton->hasMorePath(); else return false;};
    static char* _nextPath()    { if (singelton != 0) return singelton->nextPath(); else return "";};
    static void _resetPath()    { if (singelton != 0) singelton->resetPath();};
};




#endif // GERTICOconf_HEADER
