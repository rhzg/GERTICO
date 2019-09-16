// stdafx.h : Include-Datei für Standard-System-Include-Dateien,
//  oder projektspezifische Include-Dateien, die häufig benutzt, aber
//      in unregelmäßigen Abständen geändert werden.
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

// ZU ERLEDIGEN: Verweisen Sie hier auf zusätzliche Header-Dateien, die Ihr Programm benötigt

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt zusätzliche Deklarationen unmittelbar vor der vorherigen Zeile ein.

#endif // !defined(AFX_STDAFX_H__26A934E7_5684_4C46_A596_D30890941ECA__INCLUDED_)
