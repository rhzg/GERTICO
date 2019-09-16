#ifndef FedFedParser_HEADER
#define FedFedParser_HEADER

/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: FedParser.h,v $
Revision 1.4  2007/03/12 12:54:43  mul
Changed string to wstring.

Revision 1.3  2006/11/17 10:23:43  mul
Extend error checking.

Revision 1.2  2005/12/15 16:09:17  mul
Remove keyword struct.

Revision 1.1  2004/05/28 11:55:11  mul
Add new files.

 
**
*******************************************************************************/


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------

#include <string>
#include <stdio.h>

#include <map> 

#include "ClassInfo.h"

/*******************************************************************************
**
**
*******************************************************************************/
class FedParser
{
  char buff[512];
  char lookahead[128];
  char token[128];
  void addSpace(std::vector<SpaceInfo> &, SpaceInfo &);
  int anyToken(const char *token, const char *thing );
  bool checkConsistency (FedPrivateData &RTIVar, std::wstring &theError);
  bool checkMultimapParentChild (multitree<unsigned long> &theTree, std::map<unsigned long, ObjectClassInfo> &theObjectClasses, std::map<unsigned long, AttributeInfo> &theAttributes, std::wstring &theError);
  bool checkMultimapParentChild (multitree<unsigned long> &theTree, std::map<unsigned long, InteractionClassInfo> &theInteractionClasses, std::map<unsigned long, ParameterInfo> &theParameters, std::wstring &theError);
  bool checkNameString(const char *theToken, std::wstring &theError);
  bool checkParentAttributeName (multitree<unsigned long>::node_iterator &theNI, std::map<unsigned long, ObjectClassInfo> &theObjectClasses, std::map<unsigned long, AttributeInfo> &theAttributes, const std::wstring &theName, std::wstring &theError);
  bool checkParentParameterName (multitree<unsigned long>::node_iterator &theNI, std::map<unsigned long, InteractionClassInfo> &theInteractionClasses, std::map<unsigned long, ParameterInfo> &theParameters, const std::wstring &theName, std::wstring &theError);
  bool checkSpace(std::vector<SpaceInfo> &, const char *, std::wstring &);
  int checkToken(const char *token, const char *pattern );
  bool getFederation(FILE *theFedFile, FedPrivateData &RTIVar, std::wstring &theError);
  bool getFEDversion(FILE *theFedFile, FedPrivateData &RTIVar, std::wstring &theError);
  bool getSpaces(FILE *theFedFile, FedPrivateData &RTIVar, std::wstring &theError, SpaceInfo &theTempSpace, std::vector<SpaceInfo> &theLowerSpaces);
  bool getObjectClasses(FILE *theFedFile, FedPrivateData &RTIVar, std::wstring &theError, std::vector<SpaceInfo> &theLowerSpaces);
  bool getInteractionClasses(FILE *theFedFile, FedPrivateData &RTIVar, std::wstring &theError, std::vector<SpaceInfo> &theLowerSpaces);
  int getMapValue (const char *theToken, unsigned long &theTransport, std::map<std::string, unsigned long> &theMap);
  const char *getToken(FILE *aFile);
  void nameToLower (std::string &out, const std::wstring &in);
  bool processInteractions (multitree<unsigned long>::node_iterator &theNI, std::map<unsigned long, InteractionClassInfo> &theInteractionClasses, std::map<unsigned long, ParameterInfo> &theParameters, std::wstring &theError);
  bool processObjects (multitree<unsigned long>::node_iterator &theNI, std::map<unsigned long, ObjectClassInfo> &theObjectClasses, std::map<unsigned long, AttributeInfo> &theAttributes, std::wstring &theError);
  int readFedFile(FILE *, FedPrivateData &, std::wstring &);

  bool gotLookahead;
  int l;

public:
  FedParser ();
  virtual ~FedParser ();
    
  int ReadFedFile(const std::string &FedFileName, FedPrivateData &, std::wstring &);
};

#endif // FedFedParser_HEADER
