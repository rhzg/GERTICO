/******************************************************************************r
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: FedParser.cpp,v $
Revision 1.7  2009/08/17 10:02:42  mul
Use standard length type.

Revision 1.6  2007/09/05 15:02:12  mul
Changes for ieee1516.

Revision 1.5  2007/03/12 12:55:15  mul
Changed string to wstring.

Revision 1.4  2006/11/17 10:23:42  mul
Extend error checking.

Revision 1.3  2006/10/18 11:31:07  mul
Minor changes to fix create federation execution problems.

Revision 1.2  2005/12/15 16:09:17  mul
Remove keyword struct.

Revision 1.1  2004/05/28 11:55:11  mul
Add new files.

 
**
*******************************************************************************/

#include <ctype.h>

#include "FedParser.h"
#include "Util/Mapper.h"

/*******************************************************************************
**
**
*******************************************************************************/
FedPrivateData::FedPrivateData (void)
{
}

/*******************************************************************************
**
**
*******************************************************************************/
FedPrivateData::~FedPrivateData (void)
{
}

/*******************************************************************************
**
**
*******************************************************************************/
FedParser::FedParser (void)
{
  l = 0;
  gotLookahead = false;
}

/*******************************************************************************
**
**
*******************************************************************************/
FedParser::~FedParser (void)
{
}

/*******************************************************************************
**
**
*******************************************************************************/
const char *FedParser::getToken (FILE *f)
{
  char *s;
  size_t i;
  size_t len;
  int n = 0;
  int p = 0;

  if (gotLookahead)
  {
    if (lookahead[0] == ')')
    {
      token[0] = lookahead[0];
      token[1] = '\0';
      len = strlen (lookahead);
      for (i = 0; i < len; i++)
      {
        lookahead[i] = lookahead[i + 1];
      }
      return token;
    }
    gotLookahead = false;
  }

  while (1)
  {
    if (l == 0)
    {
      if (gotLookahead)
      {
      }
      else
      {
        s = fgets (buff, 512, f);
        if (s == NULL)
        {
          return s;
        }
      }
    }
    p = sscanf (&buff[l], "%s%n", token, &n);
    l += n;
    if (p == -1 || p == 0)
    {
      l = 0;
      continue;
    }
    if (strncmp (token, ";;", 2) == 0)
    {
      l = 0;
      continue;
    }
    if (strcmp (token, ")") == 0)
    {
      return token;
    }
    s = strchr(&token[1], ')');
    if (s)
    {
      gotLookahead = true;
      strcpy (lookahead, s);
      *s = '\0';
    }
    return token;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void FedParser::addSpace(std::vector<SpaceInfo> &lowerSpaces, SpaceInfo &TempSpace)
{
  const char *cstr;
  char lowerString[128];
  size_t i;
  size_t len;
  std::string t;

  GERTICO::Mapper::mapStringFromWstring(t, TempSpace.Name);
  cstr = t.c_str ();
  len = strlen (cstr);
  for (i = 0; i < len; i++)
  {
    lowerString[i] = tolower (cstr[i]);
  }
  lowerString[len] = '\0';
  std::string s (lowerString);
  GERTICO::Mapper::mapWstringFromChar(TempSpace.Name, s.c_str());
  lowerSpaces.push_back(TempSpace); 
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
int FedParser::anyToken(const char *theToken, const char *thing )
{
  if (!theToken)
  {
//	  std::cerr << "RTI error reading fed file: unexpected end of file (was expecting " << thing << ")"<< std::endl << std::flush;  
     return 1;
  } else return 0;
}

// ---------------------------------------------------------------------------
// Do any data consistency checking:
// 1) same attribute name in parent and child is not allowed.
// ---------------------------------------------------------------------------
bool FedParser::checkConsistency(FedPrivateData &RTIVar, std::wstring &theError)
{
  // Check ObjectClassTree
  if (checkMultimapParentChild (RTIVar.ObjectClassTree, RTIVar.ObjectClasses, RTIVar.Attributes, theError))
  {
    // Found error.
    return true;
  }
  // Check InteractionClassTree
  if (checkMultimapParentChild (RTIVar.InteractionClassTree, RTIVar.InteractionClasses, RTIVar.Parameters, theError))
  {
    // Found error.
    return true;
  }

  // All ok
  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool FedParser::checkMultimapParentChild (multitree<unsigned long> &theTree, std::map<unsigned long, ObjectClassInfo> &theObjectClasses, std::map<unsigned long, AttributeInfo> &theAttributes, std::wstring &theError)
{
  multitree<unsigned long>::node_iterator ni;
  std::map <unsigned long, ObjectClassInfo>::iterator itObjectClasses;

  for (ni = theTree.begin (); ni != theTree.end (); ni++)
  {
    itObjectClasses = theObjectClasses.find (ni.current->data_);
    if (itObjectClasses != theObjectClasses.end ())
    {
      // Process sub-classes.
      if (ni.current->first_)
      {
        if (processObjects (ni, theObjectClasses, theAttributes, theError))
        {
          // Error.
          return true;
        }
      }
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool FedParser::checkMultimapParentChild (multitree<unsigned long> &theTree, std::map<unsigned long, InteractionClassInfo> &theInteractionClasses, std::map<unsigned long, ParameterInfo> &theParameters, std::wstring &theError)
{
  multitree<unsigned long>::node_iterator ni;
  std::map <unsigned long, InteractionClassInfo>::iterator itInteractionClasses;

  for (ni = theTree.begin (); ni != theTree.end (); ni++)
  {
    itInteractionClasses = theInteractionClasses.find (ni.current->data_);
    if (itInteractionClasses != theInteractionClasses.end ())
    {
      // Process sub-classes.
      if (ni.current->first_)
      {
        if (processInteractions (ni, theInteractionClasses, theParameters, theError))
        {
          // Error.
          return true;
        }
      }
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool FedParser::checkNameString(const char *theToken, std::wstring &theError)
{
  char tmpBuff[128];
  int a;
  std::wstring ws;
  unsigned int i;
  size_t len;

  strcpy(tmpBuff, theToken);

  len = strlen(tmpBuff);

  for (i = 0; i < len; i++)
  {
    if (i == 0)
    {
      a = tmpBuff[i];
      if (isalpha(a))
      {
        continue;
      }
      else
      {
        // Not alpha.
        theError = L"checkNameString: space name invalid character";
        return true;
      }
    }
    a = tmpBuff[i];
    if (isalnum(a))
    {
      continue;
    }
    if (tmpBuff[i] == '_' ||
        tmpBuff[i] == '+' ||
        tmpBuff[i] == '-' ||
        tmpBuff[i] == '*' ||
        tmpBuff[i] == '/' ||
        tmpBuff[i] == '@' ||
        tmpBuff[i] == '$' ||
        tmpBuff[i] == '^' ||
        tmpBuff[i] == '&' ||
        tmpBuff[i] == '=' ||
        tmpBuff[i] == '<' ||
        tmpBuff[i] == '>' ||
        tmpBuff[i] == '~' ||
        tmpBuff[i] == '!' ||
        tmpBuff[i] == '#'
       )
    {
      continue;
    }

    theError = L"checkNameString: space name invalid character ";
    GERTICO::Mapper::mapWstringFromChar(ws, theToken);
    theError.append(ws);
    return true;
  }

  // Value ok.
  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool FedParser::checkParentAttributeName (multitree<unsigned long>::node_iterator &theNI, std::map<unsigned long, ObjectClassInfo> &theObjectClasses, std::map<unsigned long, AttributeInfo> &theAttributes, const std::wstring &theName, std::wstring &theError)
{
  AttributeInfo *currAttributeInfo;
  ObjectClassInfo *currObjectClassInfo;
  multitree<unsigned long>::node_iterator currNI;
  std::map <unsigned long, AttributeInfo>::iterator itAttInfo;
  std::map <unsigned long, ObjectClassInfo>::iterator itObjectClasses;
  std::string s;
  std::vector<unsigned long>::iterator itUL;

  nameToLower (s, theName);
  for (currNI = theNI.current->parent_; currNI != NULL; currNI = currNI.current->parent_)
  {
    itObjectClasses = theObjectClasses.find (currNI.current->data_);
    if (itObjectClasses != theObjectClasses.end ())
    {
      // Process attributes.
      currObjectClassInfo = &itObjectClasses->second;
      for (itUL = itObjectClasses->second.attributes.begin (); itUL != itObjectClasses->second.attributes.end (); itUL++)
      {
        itAttInfo = theAttributes.find (*itUL);
        if (itAttInfo != theAttributes.end ())
        {
          std::string ss;
          currAttributeInfo = &itAttInfo->second;
          nameToLower (ss, currAttributeInfo->Name);
          if (s == ss)
          {
            // Error.
            theError = L"same attribute in parent and child ";
            theError.append (theName);
            return true;
          }
        }
      }
    }
  }

  // No error.
  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool FedParser::checkParentParameterName (multitree<unsigned long>::node_iterator &theNI, std::map<unsigned long, InteractionClassInfo> &theInteractionClasses, std::map<unsigned long, ParameterInfo> &theParameters, const std::wstring &theName, std::wstring &theError)
{
  ParameterInfo *currParameterInfo;
  InteractionClassInfo *currParameterClassInfo;
  multitree<unsigned long>::node_iterator currNI;
  std::map <unsigned long, ParameterInfo>::iterator itParamInfo;
  std::map <unsigned long, InteractionClassInfo>::iterator itInteractionClasses;
  std::string s;
  std::vector<unsigned long>::iterator itUL;

  nameToLower (s, theName);
  for (currNI = theNI.current->parent_; currNI != NULL; currNI = currNI.current->parent_)
  {
    itInteractionClasses = theInteractionClasses.find (currNI.current->data_);
    if (itInteractionClasses != theInteractionClasses.end ())
    {
      // Process parameters.
      currParameterClassInfo = &itInteractionClasses->second;
      for (itUL = itInteractionClasses->second.parameters.begin (); itUL != itInteractionClasses->second.parameters.end (); itUL++)
      {
        itParamInfo = theParameters.find (*itUL);
        if (itParamInfo != theParameters.end ())
        {
          std::string ss;
          currParameterInfo = &itParamInfo->second;
          nameToLower (ss, currParameterInfo->Name);
          if (s == ss)
          {
            // Error.
            theError = L"same parameter in parent and child ";
            theError.append (theName);
            return true;
          }
        }
      }
    }
  }

  // No error.
  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool FedParser::checkSpace(std::vector<SpaceInfo> &lowerSpaces, const char *Token, std::wstring &handle)
{
  char lowerString[128];
  size_t i;
  size_t len;
  std::vector<SpaceInfo>::iterator SpaceIter;

  len = strlen (Token);
  // buffer with lower case string
  for (i = 0; i < len; i++)
  {
    lowerString[i] = tolower (Token[i]);
  }
  lowerString[len] = '\0';
  // convert to standard string
  std::wstring testString;
  GERTICO::Mapper::mapWstringFromChar(testString, lowerString);
  // check if string known
  for (SpaceIter = lowerSpaces.begin (); SpaceIter != lowerSpaces.end (); SpaceIter++)
  {
    if (SpaceIter->Name == testString)
    {
      GERTICO::Mapper::mapWstringFromChar(handle, Token);
      return true;
    }
  }
  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool FedParser::getFederation(FILE *theFedFile, FedPrivateData &RTIVar, std::wstring &theError)
{
  const char *Token;

  Token = getToken(theFedFile);
  if (checkToken(Token, "(Federation"))
  {
    theError = L"readFedFile: cannot get (Federation token";
    return 1;
  }
  Token = getToken(theFedFile);   
  if (anyToken(Token, "Federation name"))
  {
    theError = L"readFedFile: cannot get Federation name";
    return 1;
  }
  else
  {
    if (checkNameString(Token, theError))
    {
      return 1 ;
    }
    RTIVar.FederationName = Token;
  }
  Token = getToken(theFedFile);
  if (checkToken(Token, ")"))
  {
    theError = L"readFedFile: cannot get ) after Federation";
    return 1;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool FedParser::getFEDversion(FILE *theFedFile, FedPrivateData &RTIVar, std::wstring &theError)
{
  const char *Token;

  Token = getToken(theFedFile);
  if (checkToken(Token, "(FEDversion"))
  {
    theError = L"readFedFile: cannot get (FEDversion";
    return 1;
  }
  Token = getToken(theFedFile); 
  if (anyToken(Token, " FEDversion label"))
  {
    theError = L"readFedFile: cannot get FEDversion label";
    return 1;
  }
  else
  {
    if (checkToken(Token, "v1.3"))
    {
      theError = L"readFedFile: invalid FEDversion value";
      return 1;
    }
    else
    {
      RTIVar.FEDVersion = Token;
    }
  }
  Token = getToken(theFedFile);
  if (checkToken(Token, ")"))
  {
    theError = L"readFedFile: cannot get ) after FEDversion label";
    return 1;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool FedParser::getSpaces(FILE *theFedFile, FedPrivateData &RTIVar, std::wstring &theError, SpaceInfo &theTempSpace, std::vector<SpaceInfo> &theLowerSpaces)
{
  const char *Token;
  int cdepth = 0; 

  Token = getToken(theFedFile);
  if (checkToken(Token, "(spaces"))
  {
    theError = L"readFedFile: cannot get (spaces token";
    return 1;
  }
  Token = getToken(theFedFile); 
  if (anyToken( Token, "begin spaces info"))
  {
    theError = L"readFedFile: cannot get begin spaces info";
    return 1;
  }
  cdepth = 0;
  while (true)
  { 
    if (strcmp(Token, "(space") == 0 )
    {                 // Token is a new space.                 
      cdepth++;
      Token = getToken(theFedFile);                       // get the name and create a new level
      if (anyToken( Token, "space name"))
      {
        theError = L"readFedFile: cannot get space name";
        return 1 ;
      }
      if (checkNameString(Token, theError))
      {
        return 1 ;
      }
      GERTICO::Mapper::mapWstringFromChar(theTempSpace.Name, Token);
      theTempSpace.Handle = RTIVar.Spaces.size();
      RTIVar.Spaces.push_back(theTempSpace); 
      addSpace (theLowerSpaces, theTempSpace);
    }
    else
    {
      if (strcmp(Token, "(dimension") == 0)
      {  // Token is a dimension.  get the name and addItem     
        Token = getToken(theFedFile);                       // Get the dimension name
        if (anyToken (Token, "dimension name" ))
        {
          theError = L"readFedFile: cannot get dimension name";
          return 1;  
        }
        else
        {
          if (checkNameString(Token, theError))
          {
            return 1 ;
          }
          RTIVar.Spaces[theTempSpace.Handle].DimensionNames.push_back(Token);     
        }
        Token = getToken(theFedFile);                    // Get the closing paren for the dimension name.
        if (checkToken(Token, ")"))
        {
          theError = L"readFedFile: cannot get ) after dimension";
          return 1;
        }
      }
      else
      {
        if (checkToken(Token, ")"))
        {
          theError = L"readFedFile: cannot get ) after spaces";
          return 1 ;// Token is the class end of this level
        }
        else
        {
          if (!cdepth)
          {
            break;                                   // we're done with space classes
          }
          cdepth--;
        }
      }
    }
    Token = getToken(theFedFile);                      // If we get to this line, we need another token 
    if (anyToken( Token, "continue spaces info"))
    {
      theError = L"readFedFile: cannot get continue spaces info";
      return 1;
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool FedParser::getObjectClasses(FILE *theFedFile, FedPrivateData &RTIVar, std::wstring &theError, std::vector<SpaceInfo> &theLowerSpaces)
{
  const char *Token;
  ObjectClassInfo TempObject;
  AttributeInfo TempAttribute;
  std::stack<unsigned long> parents;
  std::string TokenString;
  std::wstring ws;
  bool gotPrivilegeToDelete = false;
  bool gotRTIprivate = false;

  Token = getToken(theFedFile);
  if (checkToken(Token, "(objects"))
  {
    theError = L"readFedFile: cannot get (objects token";
    return true;
  }
  Token = getToken(theFedFile);
  if (checkToken(Token, "(class"))
  {
    theError = L"readFedFile: cannot get (class token";
    return true;
  }
  Token = getToken(theFedFile);                        // ObjectRoot must be the root node...
  if (checkToken(Token, "ObjectRoot"))
  {
    theError = L"readFedFile: cannot get ObjectRoot";
    return true;
  }
                                                    // initialize object class info
  GERTICO::Mapper::mapWstringFromChar(TempObject.Name, Token);
  GERTICO::Mapper::mapWstringFromChar(TempObject.FullName, Token);
  TempObject.Handle = RTIVar.ObjectClasses.size();
  RTIVar.ObjectClassTree.data_ = (TempObject.Handle);  
  TempObject.ClassSubTree = RTIVar.ObjectClassTree.begin();
  RTIVar.ObjectClasses[TempObject.Handle] = TempObject;
  parents.push(TempObject.Handle);
  Token = getToken(theFedFile);  
  while (Token)
  {
    if (strcmp(Token, "(class") == 0)
    {                //  Token is a new class 
      Token = getToken(theFedFile);                       // Get the classname
      if (anyToken(Token, "class name"))
      {
        theError = L"readFedFile: cannot get class name";
        return true;
      }
      if (gotRTIprivate == false)
      {
        if (checkToken(Token, "RTIprivate") == 0)
        {
          gotRTIprivate = true;
        }
      }
      if (checkNameString(Token, theError))
      {
        return 1 ;
      }
      GERTICO::Mapper::mapWstringFromChar(TempObject.Name, Token);
      TempObject.Handle = RTIVar.ObjectClasses.size();
      TempObject.ClassSubTree = RTIVar.ObjectClassTree.add_child(RTIVar.ObjectClasses[parents.top()].ClassSubTree, TempObject.Handle);
// include objectRoot.?      if (parents.size() > 1) TempObject.FullName = RTIVar.ObjectClasses[parents.top()].FullName+"."+std::string(Token) ;
//      else TempObject.FullName = std::string(Token);
      std::wstring wss;
      GERTICO::Mapper::mapWstringFromChar(wss, Token);
      TempObject.FullName = RTIVar.ObjectClasses[parents.top()].FullName + L"." + wss;
//      TempObject.attributes = RTIVar.ObjectClasses[parents.top()].attributes;  // accum parent's attributes
      RTIVar.ObjectClasses[TempObject.Handle] = TempObject;
      parents.push(TempObject.Handle);
    }
    else
    {
      if (strcmp(Token, "(attribute") == 0)
      {     // Token is an attribute
        Token = getToken(theFedFile);                       // Get Attribute name
        if (anyToken(Token, "attribute name"))
        {
          theError = L"readFedFile: cannot get attribute name";
          return true;
        }
        if (parents.size() == 1)
        {
          if (gotPrivilegeToDelete == false)
          {
#ifdef IEEE_1516
            if (checkToken(Token, "HLAprivilegeToDeleteObject") == 0)
#else
            if (checkToken(Token, "privilegeToDelete") == 0)
#endif
            {
              gotPrivilegeToDelete = true;
            }
          }
        }
        if (checkNameString(Token, theError))
        {
          return 1 ;
        }
        GERTICO::Mapper::mapWstringFromChar(TempAttribute.Name, Token);
        TempAttribute.Handle = RTIVar.Attributes.size();

        // Attribute transport
        Token = getToken(theFedFile);
        if (getMapValue (Token, TempAttribute.Transport, RTIVar.TransportMap))
        {
          theError = L"readFedFile: bad attribute transport: ";
          GERTICO::Mapper::mapWstringFromChar(ws, Token);
          theError.append(ws);
          return true;
        }

        // Attribute ordering
        Token = getToken(theFedFile);
        if (getMapValue (Token, TempAttribute.Ordering, RTIVar.OrderingMap))
        {
          theError = L"readFedFile: bad attribute ordering: ";
          GERTICO::Mapper::mapWstringFromChar(ws, Token);
          theError.append(ws);
          return true;
        }

        // Attribute space or closing paren
        Token = getToken(theFedFile);
        if (anyToken(Token, "attribute space"))
        {
          theError = L"readFedFile: cannot get attribute space";
          return true;
        }

        if (strcmp(Token, ")") != 0)
        {
          // must be the space
          if (checkSpace (theLowerSpaces, Token, TempAttribute.Space) == false)
          {
            theError = L"readFedFile: cannot get space";
            return true;
          }
        	Token = getToken(theFedFile);                     // the closing paren
        }
        else
        {
          TempAttribute.Space = L"";  // the default
        }
        if (checkToken(Token, ")" ))
        {
          theError = L"readFedFile: cannot get ) after attribute";
          return true;
        }
        RTIVar.Attributes[TempAttribute.Handle] = TempAttribute;
        RTIVar.ObjectClasses[parents.top()].addAttribute(TempAttribute.Handle);
      }
      else
      {
        if (checkToken(Token, ")") == 0)
        {
          if (parents.size() > 1)
          {
            parents.pop();
          }
          else
          {
            break;
          }
        }
        else
        {                                     // Closing off Class
          theError = L"readFedFile: too many ) after attributes";
          return true;
        } 
      } 
    } 
    Token = getToken(theFedFile); // if we get here, we need another token...
  }
  Token = getToken(theFedFile);  // we got the closing paren from the objectRoot, close (objects
  if (checkToken(Token, ")"))
  {
    theError = L"readFedFile: too many ) after objects";
    return true;
  }
  while (!parents.empty()) parents.pop();

  if (gotPrivilegeToDelete == false)
  {
    theError = L"readFedFile: missing privilegeToDelete";
    return true;
  }

  if (gotRTIprivate == false)
  {
    theError = L"readFedFile: missing RTIprivate";
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool FedParser::getInteractionClasses(FILE *theFedFile, FedPrivateData &RTIVar, std::wstring &theError, std::vector<SpaceInfo> &theLowerSpaces)
{
  const char *Token;
  InteractionClassInfo TempInteraction;
  ParameterInfo TempParameter;
  std::stack<unsigned long> parents;
  std::vector<SpaceInfo>::iterator SpaceIter;
  std::wstring ws;

  Token = getToken(theFedFile); 
  if (checkToken(Token, "(interactions"))
  {
    theError = L"readFedFile: cannot get (interactions token";
    return 1;
  }
  Token = getToken(theFedFile);
  if (checkToken(Token, "(class"))
  {
    theError = L"readFedFile: cannot get (class token";
    return 1;
  }
  Token = getToken(theFedFile);
  if (checkToken(Token, "InteractionRoot"))
  {
    theError = L"readFedFile: cannot get InteractionRoot";
    return 1;
  }
  GERTICO::Mapper::mapWstringFromChar(TempInteraction.Name, Token);
  GERTICO::Mapper::mapWstringFromChar(TempInteraction.FullName, Token);
  TempInteraction.Handle = RTIVar.InteractionClasses.size();
  RTIVar.InteractionClassTree.data_ = (TempInteraction.Handle);  
  TempInteraction.ClassSubTree = RTIVar.InteractionClassTree.begin();
  parents.push(TempInteraction.Handle);

  // Interaction transport
  Token = getToken(theFedFile);
  if (getMapValue (Token, TempInteraction.Transport, RTIVar.TransportMap))
  {
    theError = L"readFedFile: bad interaction transport: ";
    GERTICO::Mapper::mapWstringFromChar(ws, Token);
    theError.append(ws);
    return 1;
  }
  
  // Interaction ordering
  Token = getToken(theFedFile);
  if (getMapValue (Token, TempInteraction.Ordering, RTIVar.OrderingMap))
  {
    theError = L"readFedFile: bad interaction ordering: ";
    GERTICO::Mapper::mapWstringFromChar(ws, Token);
    theError.append(ws);
    return 1;
  }

  Token = getToken(theFedFile);                       // could be space, probably not.
  if (strcmp(Token, "(parameter") && strcmp(Token, ")") && strcmp(Token, "(class"))
  {  // must be spacename
    if (checkSpace (theLowerSpaces, Token, TempInteraction.Space) == false)
    {
      theError = L"readFedFile: cannot get interaction space";
      return 1;
    }
    Token = getToken(theFedFile);                     // the closing paren
  } else  TempInteraction.Space = L"";    // The default space
  RTIVar.InteractionClasses[TempInteraction.Handle] = TempInteraction;
   
  while (Token)
  {
    if (strcmp(Token, "(class") == 0)
    {
      Token = getToken(theFedFile);
      if (anyToken(Token, "class name"))
      {
        theError = L"readFedFile: cannot get class name";
        return 1;
      }
      if (checkNameString(Token, theError))
      {
        return 1 ;
      }
      GERTICO::Mapper::mapWstringFromChar(TempInteraction.Name, Token);
      TempInteraction.Handle = RTIVar.InteractionClasses.size();
      TempInteraction.ClassSubTree = 
        RTIVar.InteractionClassTree.add_child(RTIVar.InteractionClasses[parents.top()].ClassSubTree, TempInteraction.Handle);
// include interactionRoot.?      if (parents.size() > 1) TempInteraction.FullName = RTIVar.InteractionClasses[parents.top()].FullName+"."+std::string(Token) ;
//      else TempInteraction.FullName = std::string(Token);
      std::wstring wss;
      GERTICO::Mapper::mapWstringFromChar(wss, Token);
      TempInteraction.FullName = RTIVar.InteractionClasses[parents.top()].FullName + L"." + wss;
      Token = getToken(theFedFile);                   // Interaction transport
      if (anyToken(Token, "interaction transport"))
      {
        theError = L"readFedFile: cannot get interaction transport";
        return 1;
      }
      TempInteraction.Transport = RTIVar.TransportMap[std::string(Token)];
      Token = getToken(theFedFile);                   // Interaction order
      if (anyToken(Token, "interaction ordering"))
      {
        theError = L"readFedFile: cannot get interaction ordering";
        return 1;
      }
      TempInteraction.Ordering = RTIVar.OrderingMap[std::string(Token)];
      Token = getToken(theFedFile);                       // could be space, probably not.
      if (strcmp(Token, "(parameter") && strcmp(Token, ")") && strcmp(Token, "(class"))
      {  // must be spacename
     	  SpaceIter = RTIVar.Spaces.end(); --SpaceIter; 
        GERTICO::Mapper::mapWstringFromChar(wss, Token);
        while (SpaceIter->Name != wss)
        {
          --SpaceIter;
        }
        if (SpaceIter->Name != wss)
        {
          theError = L"readFedFile: interaction unknown space";
          return 1;  // Unknown Space
        }
//        TempInteraction.Space = SpaceIter->Handle;
        TempInteraction.Space = SpaceIter->Name;
        Token = getToken(theFedFile);                     // the closing paren
      }
      else
      {
        TempInteraction.Space = L"";
      }
//      TempInteraction.parameters = RTIVar.InteractionClasses[parents.top()].parameters;  // accum parent's parameters
      RTIVar.InteractionClasses[TempInteraction.Handle] = TempInteraction;  
      parents.push(TempInteraction.Handle);
      while (strcmp(Token, "(parameter") == 0)
      {
        Token = getToken(theFedFile);                   // parameter name
        if (anyToken(Token, "parameter name"))
        {
          theError = L"readFedFile: cannot get parameter name";
          return 1;
        }
        if (checkNameString(Token, theError))
        {
          return 1 ;
        }
        GERTICO::Mapper::mapWstringFromChar(TempParameter.Name, Token);
        TempParameter.Handle = RTIVar.Parameters.size();
        RTIVar.Parameters[TempParameter.Handle] = TempParameter;
        RTIVar.InteractionClasses[parents.top()].addParameter(TempParameter.Handle);
        Token = getToken(theFedFile);                   // closing paren
        if (checkToken(Token, ")"))
        {
          theError = L"readFedFile: cannot get ) after interaction";
          return 1;
        }
        Token = getToken(theFedFile);                   // closing paren
      }
    }
    else
    {
      if (strcmp(Token, ")") == 0)
      {
        if (parents.size() > 1)
        {
          parents.pop();
          Token = getToken(theFedFile);            
        }
        else
        {
          break;
        }
      }
      else
      {                                     // Closing off Class                           
        theError = L"readFedFile: too many ) after interaction";
        return 1;
      }
    }
  }    //while (Token)
  Token = getToken(theFedFile);                       // end of interaction classes
  if (checkToken(Token, ")"))
  {
    theError = L"readFedFile: too many ) after interactions";
    return 1;  
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
int FedParser::getMapValue (const char *theToken, unsigned long &theValue, std::map<std::string, unsigned long> &theMap)
{
  char lowerToken[128];
  int i;
  size_t len;
  std::map<std::string, unsigned long>::iterator itT;

  len = strlen (theToken);
  // buffer with lower case string
  for (i = 0; i < len; i++)
  {
    lowerToken[i] = tolower (theToken[i]);
  }
  lowerToken[len] = '\0';

  std::string s (lowerToken);

  itT = theMap.find (s);
  if (itT != theMap.end ())
  {
    theValue = itT->second;
    return 0;
  }

  return 1;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
// Read the fed file and initialize class handles
//  - PE zero creates a multicast group for each class name
//  - all other PEs just get the multicast group handle
// fed file format conforms to RTI 1.3R6 Format, except that comments aren't supporte
// and transport, ordering and space are ignored for attributes and interactions.
// ??? need to check for duplicated attribute/parameter names
// ??? this does not accept comment lines!!! (beginning with ;;)
int FedParser::checkToken(const char *theToken, const char *pattern )
{
  char lowerPattern[128];
  char lowerToken[128];
  int i;
  size_t len;

  len = strlen (theToken);
  // buffer with lower case string
  for (i = 0; i < len; i++)
  {
    lowerToken[i] = tolower (theToken[i]);
  }
  lowerToken[len] = '\0';

  len = strlen (pattern);
  // buffer with lower case string
  for (i = 0; i < len; i++)
  {
    lowerPattern[i] = tolower (pattern[i]);
  }
  lowerPattern[len] = '\0';

  if (theToken && strcmp(lowerToken, lowerPattern) != 0)
  {
//	  std::cout << "RTI error reading fed file: expected " << pattern << " but found " << theToken << std::endl << std::flush; 
    return 1;
  }
  else
  {
    return 0;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void FedParser::nameToLower(std::string &out, const std::wstring &in)
{
  char c[128];
  std::string tmp;

  GERTICO::Mapper::mapStringFromWstring(tmp, in);
  strcpy (c, tmp.c_str ());

  size_t len = strlen (c);
  for (int i = 0; i < len; i++)
  {
    c[i] = tolower(c[i]);
  }

  out = c;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool FedParser::processInteractions (multitree<unsigned long>::node_iterator &theNI, std::map<unsigned long, InteractionClassInfo> &theInteractionClasses, std::map<unsigned long, ParameterInfo> &theParameters, std::wstring &theError)
{
  ParameterInfo *currParameterInfo;
  multitree<unsigned long>::node_iterator it (theNI.current->first_);
  std::map <unsigned long, ParameterInfo>::iterator itParamInfo;
  std::map <unsigned long, InteractionClassInfo>::iterator itInteractionClasses;
  std::vector<unsigned long>::iterator itUL;

  // Fill in class information.
  for (; it.current != NULL; it++)
  {
    itInteractionClasses = theInteractionClasses.find (it.current->data_);
    if (itInteractionClasses != theInteractionClasses.end ())
    {
      // Process attributes.
      for (itUL = itInteractionClasses->second.parameters.begin (); itUL != itInteractionClasses->second.parameters.end (); itUL++)
      {
        itParamInfo = theParameters.find (*itUL);
        if (itParamInfo != theParameters.end ())
        {
          currParameterInfo = &itParamInfo->second;
          if (checkParentParameterName (it, theInteractionClasses, theParameters, currParameterInfo->Name, theError))
          {
            // Error.
            return true;
          }
        }
      }

      // Process sub-classes.
      if (it.current->first_)
      {
        if (processInteractions (it, theInteractionClasses, theParameters, theError))
        {
          // Error.
          return true;
        }
      }
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool FedParser::processObjects (multitree<unsigned long>::node_iterator &theNI, std::map<unsigned long, ObjectClassInfo> &theObjectClasses, std::map<unsigned long, AttributeInfo> &theAttributes, std::wstring &theError)
{
  AttributeInfo *currAttributeInfo;
  multitree<unsigned long>::node_iterator it (theNI.current->first_);
  std::map <unsigned long, AttributeInfo>::iterator itAttInfo;
  std::map <unsigned long, ObjectClassInfo>::iterator itObjectClasses;
  std::vector<unsigned long>::iterator itUL;

  // Fill in class information.
  for (; it.current != NULL; it++)
  {
    itObjectClasses = theObjectClasses.find (it.current->data_);
    if (itObjectClasses != theObjectClasses.end ())
    {
      // Process attributes.
      for (itUL = itObjectClasses->second.attributes.begin (); itUL != itObjectClasses->second.attributes.end (); itUL++)
      {
        itAttInfo = theAttributes.find (*itUL);
        if (itAttInfo != theAttributes.end ())
        {
          currAttributeInfo = &itAttInfo->second;
          if (checkParentAttributeName (it, theObjectClasses, theAttributes, currAttributeInfo->Name, theError))
          {
            // Error.
            return true;
          }
        }
      }

      // Process sub-classes.
      if (it.current->first_)
      {
        if (processObjects (it, theObjectClasses, theAttributes, theError))
        {
          // Error.
          return true;
        }
      }
    }
  }

  return false;
}

/*******************************************************************************
** Read from the fed file and parse the contents according to HLA
** specification.
*******************************************************************************/
int FedParser::ReadFedFile (const std::string &FedFileName, FedPrivateData &RTIVar, std::wstring &theError)
{
  FILE *FedFile = NULL;
  int ret = 0;
  char name[1024];

  name[0] = '\0';
  sscanf(FedFileName.c_str (), "%s", name);
  if (name[0] == '\0')
  {
    return 2;
  }

  // open the file
  FedFile = fopen(FedFileName.c_str (), "r");
  if (FedFile == NULL)
  {
    return 2;
  }

  // parse the file
  ret = readFedFile(FedFile, RTIVar, theError);

  // close the file
  fclose (FedFile);

  return ret;
}

/*******************************************************************************
** Low level parsing of the file contents.
**
*******************************************************************************/
int FedParser::readFedFile(FILE *FedFile, FedPrivateData &RTIVar, std::wstring &theError)
{
  const char *Token;
  std::vector<SpaceInfo> lowerSpaces;

  // Reset some flags.
  gotLookahead = false;
  l = 0;

  //  Federation Information 
  Token = getToken(FedFile);   // Get the (FED token
  if (Token == NULL)
  {
    theError = L"readFedFile: cannot get (FED token";
    return 1;
  }
  if (checkToken(Token, "(FED"))
  {
    theError = L"readFedFile: cannot get (FED token";
    return 1;
  }

  // Federation Name
  if (getFederation(FedFile, RTIVar, theError))
  {
    return 1;
  }

  // Federation Version
  if (getFEDversion(FedFile, RTIVar, theError))
  {
    return 1;
  }

  //  --- Spaces ---
  SpaceInfo TempSpace;   
  if (getSpaces(FedFile, RTIVar, theError, TempSpace, lowerSpaces))
  {
    return 1;
  }

  // --- Objects ---
  if (getObjectClasses(FedFile, RTIVar, theError, lowerSpaces))
  {
    return 1;
  }

  // ---Interaction Classes---
  if (getInteractionClasses(FedFile, RTIVar, theError, lowerSpaces))
  {
    return 1;
  }

  Token = getToken(FedFile);                       // end of FED
  if (checkToken(Token, ")"))
  {
    theError = L"readFedFile: too many ) after FED";
    return 1;
  }
  Token = getToken(FedFile);
  if (Token)
  {
    theError = L"readFedFile: extra characters found FED )";
    return 1;
  }

  if (checkConsistency (RTIVar, theError))
  {
    return 1;
  }
  return 0;
}
