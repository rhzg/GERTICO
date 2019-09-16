/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: HLAparse.cpp,v $
Revision 1.16  2007/09/05 15:34:41  mul
Changes for ieee1516.

Revision 1.15  2007/03/22 09:10:24  mul
Add required libraries.

Revision 1.14  2007/03/22 08:05:05  mul
Fix wstring mapping.

Revision 1.13  2004/05/28 12:01:48  mul
Remove files.

Revision 1.12  2004/03/02 09:36:33  mul
Remove comment.

Revision 1.11  2003/08/12 09:45:37  hzg
unused class removed,
namespace std for string

Revision 1.10  2003/08/11 07:59:52  mul
Logic for new fed file parser.

Revision 1.9  2003/04/30 15:30:35  hzg
SuSE 8.1 port

Revision 1.8  2002/11/29 13:14:59  hzg
priviledge to delete attribute tested

Revision 1.7  2002/11/29 11:08:30  hzg
getParentId

Revision 1.6  2002/09/09 10:12:37  hzg
XML Kodierung von GERTICO Konfigurationsdaten ergänzt

Revision 1.5  2002/09/05 15:32:51  hzg
Error Handling included

Revision 1.4  2002/09/05 10:12:32  hzg
Rückgabe von 0 Pointer bei parseFromFile falls xml Datei nicht vorhanden

Revision 1.3  2002/08/12 14:24:27  hzg
Migration auf XERCES Version 2.0.0
- DOM Klassen werden jetzt als Pointer verwendet
- String Objekte werden über XMLString verwendet
- Include Pfade haben sich geändert
- Anstelle des (depricated) DOMParser wird jetzt XercesDOMParser verwendet
- SAX Exception Handler sind entfallen

Revision 1.2  2002/07/15 15:17:56  hzg
copyright header

 
**
*******************************************************************************/


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax/SAXException.hpp>
#include <xercesc/sax/SAXParseException.hpp>
// #include <xercesc/parsers/DOMParser.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <iostream>

#include "Util/DataModel.h"
#include "Util/Mapper.h"

int main(int argC, char* argV[])
{
  GERTICO::NextHandle idHandler;
  std::wstring s;
  GERTICO::Mapper::mapWstringFromChar(s, argV[1]);
  GERTICO::ObjectModel* objectModel = GERTICO::ObjectModelFactory::createObjectModel (s, idHandler);
  if (objectModel != 0) objectModel->print ();

//  std::cout << "getAttributeId for privilegeToDelete: " 
//       << objectModel->getAttributeId (1, "privilegeToDelete") 
//       << std::endl;
  return 0;
}
