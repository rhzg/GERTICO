// stdafx.h : Include-Datei f�r Standard-System-Include-Dateien,
//  oder projektspezifische Include-Dateien, die h�ufig benutzt, aber
//      in unregelm��igen Abst�nden ge�ndert werden.
//


#if !defined(AFX_STDAFX_H__26A934E7_5684_4C46_A596_D30890941ECA__INCLUDED_)
#define AFX_STDAFX_H__26A934E7_5684_4C46_A596_D30890941ECA__INCLUDED_

#if defined(_MSC_VER)
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif /* _MSC_VER */

#include <string>
//#include <stdlib.h>
//#include <malloc.h>
#include <sys/timeb.h>
#include <time.h>
#ifdef WIN32
#include <process.h>
#else
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#endif 
#include "global.h"
#include "out.h"

// ZU ERLEDIGEN: Verweisen Sie hier auf zus�tzliche Header-Dateien, die Ihr Programm ben�tigt

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt zus�tzliche Deklarationen unmittelbar vor der vorherigen Zeile ein.

#endif // !defined(AFX_STDAFX_H__26A934E7_5684_4C46_A596_D30890941ECA__INCLUDED_)
