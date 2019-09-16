/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: GERTICOparse.cpp,v $
Revision 1.9  2008/02/07 09:25:11  mul
Minor change.

Revision 1.8  2004/04/19 14:43:17  mul
Minor change.

Revision 1.7  2004/03/17 13:08:27  mul
Remove iostream.

Revision 1.6  2003/08/15 07:19:11  hzg
this is still the test program

Revision 1.4  2003/08/08 13:27:04  mul
Logic for new fed file parser.

Revision 1.3  2003/04/30 15:30:35  hzg
SuSE 8.1 port

Revision 1.2  2002/09/11 09:18:36  hzg
Path name iterator included

Revision 1.1  2002/09/09 10:12:37  hzg
XML Kodierung von GERTICO Konfigurationsdaten ergänzt


 
**
*******************************************************************************/


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <iostream>
#include <string.h>

#include "Util/GERTICOconf.h"


int main(int argC, char* argV[])
{

  GERTICOconf* conf;
  std::string filename (argV[1]);
  conf = GERTICOconf::parseFromFile (filename);

//  GERTICOconf* conf = GERTICOconf::parseFromFile (argV[1]);
  std::cout << "Config Data: " << std::endl;
  std::cout << "- DTDfile   : " << conf->DTDfile << std::endl;
  std::cout << "- NamingService.endPoint  : " << conf->ns->endPoint << std::endl;
  std::cout << "- NamingService.rootEntry : " << conf->ns->rootEntry << std::endl;
  while (conf->hasMorePath())
  {
    std::cout << "- ModelPath : " << conf->nextPath() << std::endl;
  }
}




