/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: hzg $
$Name $
$Log: config.h,v $
Revision 1.3  2005/01/28 08:42:34  hzg
merging gertico_0_16b_fix into main thread

Revision 1.2.2.1  2005/01/27 10:22:23  hzg
bug fix concerning include and std usage
requred for using ACE-5.4+TAO-1.4

Revision 1.2  2002/07/16 08:57:22  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen

 
**
*******************************************************************************/


#ifndef config_HEADER
#define config_HEADER
/*******************************************************************************
**
** NAME
** config - Configuration file for GeRTI 1.0
**
******** Revision Control ******************************************************
**
** $Author: hzg $
** $RCSfile: config.h,v $
** $Revision: 1.3 $ $Date: 2005/01/28 08:42:34 $
** $Name:  $
** $Locker:  $ $State: Exp $
*/

#define NAMESPACE GeRTI_v1_0_CORBA
#define ID_STRING "GeRTI_v1_0_CORBA"
#define GLOBAL_LINKER_HOOK GeRTI_v1_0_CORBA_Hook
#endif // config_HEADER
