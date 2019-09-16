/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************

$Author: mul $
$Name $
$Log: RTIambServices.cpp,v $
Revision 1.15  2010/07/22 11:13:05  mul
Added missing exception.

Revision 1.14  2010/05/17 08:00:55  mul
Add logical time interval.

Revision 1.13  2010/04/13 12:27:48  mul
Add delete receiver.

Revision 1.12  2009/03/19 09:01:21  mul
Changes to limit output of event logging.

Revision 1.11  2008/11/26 15:30:50  mul
Changes for shared libraries.

Revision 1.10  2008/10/17 13:58:58  mul
Refined usage of gal logging.

Revision 1.9  2008/09/30 11:13:29  mul
Activate logging - reduce names from 16 bits to 8 bits.

Revision 1.8  2008/08/21 07:03:15  mul
Change exception.

Revision 1.7  2008/08/20 08:39:17  mul
Fix problems for g++ compiler.

Revision 1.6  2008/08/07 12:36:47  mul
Changes for event channel.

Revision 1.5  2008/04/24 12:57:59  mul
Changed logging.

Revision 1.4  2008/03/06 09:57:16  mul
Add debugging.

Revision 1.3  2007/09/25 08:23:41  mul
Changes for  ddm.

Revision 1.2  2007/09/05 15:43:02  mul
Changes for ieee1516.

Revision 1.1  2007/06/26 08:25:28  mul
New files for ieee1516.


**
*******************************************************************************/

//File RTIambServices.hh
#include <ace/OS.h>
#include <orbsvcs/CosNamingC.h>
#include "RTIambServices.h"
#include "idl/GeRtiFactoryC.h"
//#include "Util/GeRtiTypes.h"
#include "Util/Mapper.h"
#include "Mapper1516.h"

#define GalHLADebug 1

/********************************* Gal begin *********************************/   // inserted by Gal converter

// Version: 1.0   // inserted by Gal converter
// Date/Time: Fri Jan 10 11:09:07 2003   // inserted by Gal converter
//
// insert Gal file .init here
/********************************* Gal begin *********************************/   // inserted by Gal converter
// inserted by Gal converter
// Version: 1.1   // inserted by Gal converter
// Date/Time: Wed Jan 22 15:41:52 2003   // inserted by Gal converter
// inserted by Gal converter

// Redesign by GAL creator in 2006

#ifdef GalHLADebug   // inserted by Gal converter

#include "Gal/StdAfx.h"   // inserted by Gal converter
#include "Gal/repository_l.h"   // inserted by Gal converter
#include "Gal/event.h"   // inserted by Gal converter
//#include <strstream.h>   // inserted by Gal converter
   // inserted by Gal converter
//static char GalBuffer[256];   // inserted by Gal converter
//static class ostrstream GalOs(GalBuffer,256);   // inserted by Gal converter
   // inserted by Gal converter

//#include "ut.h"
#define MAX_TXT 1024

static class Repository_l *rpGal=(Repository::getSingleInstance())->getRepository_l("HLAServices.res","HLAServices");
   // inserted by Gal converter

static class Event *cAA_d0=rpGal->getRefEvent("cAA_d0");   // inserted by Gal converter
static class Event *cFE_s0=rpGal->getRefEvent("cFE_s0");   // inserted by Gal converter
static class Event *cFE_ta=rpGal->getRefEvent("cFE_ta");   // inserted by Gal converter
static class Event *cFE_ts=rpGal->getRefEvent("cFE_ts");   // inserted by Gal converter
static class Event *dFE_s0=rpGal->getRefEvent("dFE_s0");   // inserted by Gal converter
static class Event *dFE_ta=rpGal->getRefEvent("dFE_ta");   // inserted by Gal converter
static class Event *dFE_ts=rpGal->getRefEvent("dFE_ts");   // inserted by Gal converter
static class Event *jFE_s0=rpGal->getRefEvent("jFE_s0");   // inserted by Gal converter
static class Event *jFE_ta=rpGal->getRefEvent("jFE_ta");   // inserted by Gal converter
static class Event *jFE_ts=rpGal->getRefEvent("jFE_ts");   // inserted by Gal converter
static class Event *rFE_s0=rpGal->getRefEvent("rFE_s0");   // inserted by Gal converter
static class Event *rFE_ta=rpGal->getRefEvent("rFE_ta");   // inserted by Gal converter
static class Event *rFE_ts=rpGal->getRefEvent("rFE_ts");   // inserted by Gal converter
static class Event *rFSP_s0=rpGal->getRefEvent("rFSP_s0");   // inserted by Gal converter
static class Event *rFSP_s1=rpGal->getRefEvent("rFSP_s1");   // inserted by Gal converter
static class Event *rFSP_ta=rpGal->getRefEvent("rFSP_ta");   // inserted by Gal converter
static class Event *rFSP_ts=rpGal->getRefEvent("rFSP_ts");   // inserted by Gal converter
static class Event *sPA_s0=rpGal->getRefEvent("sPA_s0");   // inserted by Gal converter
static class Event *sPA_ta=rpGal->getRefEvent("sPA_ta");   // inserted by Gal converter
static class Event *sPA_ts=rpGal->getRefEvent("sPA_ts");   // inserted by Gal converter
static class Event *rFS_s0=rpGal->getRefEvent("rFS_s0");   // inserted by Gal converter
static class Event *rFS_s1=rpGal->getRefEvent("rFS_s1");   // inserted by Gal converter
static class Event *rFS_ta=rpGal->getRefEvent("rFS_ta");   // inserted by Gal converter
static class Event *rFS_ts=rpGal->getRefEvent("rFS_ts");   // inserted by Gal converter
static class Event *fSB_s0=rpGal->getRefEvent("fSB_s0");   // inserted by Gal converter
static class Event *fSB_ta=rpGal->getRefEvent("fSB_ta");   // inserted by Gal converter
static class Event *fSB_ts=rpGal->getRefEvent("fSB_ts");   // inserted by Gal converter
static class Event *fSC_s0=rpGal->getRefEvent("fSC_s0");   // inserted by Gal converter
static class Event *fSC_ta=rpGal->getRefEvent("fSC_ta");   // inserted by Gal converter
static class Event *fSC_ts=rpGal->getRefEvent("fSC_ts");   // inserted by Gal converter
static class Event *fSNC_s0=rpGal->getRefEvent("fSNC_s0");   // inserted by Gal converter
static class Event *fSNC_ta=rpGal->getRefEvent("fSNC_ta");   // inserted by Gal converter
static class Event *fSNC_ts=rpGal->getRefEvent("fSNC_ts");   // inserted by Gal converter
static class Event *qFSS_s0=rpGal->getRefEvent("qFSS_s0");   // inserted by Gal converter
static class Event *rFR_s0=rpGal->getRefEvent("rFR_s0");   // inserted by Gal converter
static class Event *rFR_ta=rpGal->getRefEvent("rFR_ta");   // inserted by Gal converter
static class Event *rFR_ts=rpGal->getRefEvent("rFR_ts");   // inserted by Gal converter
static class Event *fRC_s0=rpGal->getRefEvent("fRC_s0");   // inserted by Gal converter
static class Event *fRC_ta=rpGal->getRefEvent("fRC_ta");   // inserted by Gal converter
static class Event *fRC_ts=rpGal->getRefEvent("fRC_ts");   // inserted by Gal converter
static class Event *fRNC_s0=rpGal->getRefEvent("fRNC_s0");   // inserted by Gal converter
static class Event *fRNC_ta=rpGal->getRefEvent("fRNC_ta");   // inserted by Gal converter
static class Event *fRNC_ts=rpGal->getRefEvent("fRNC_ts");   // inserted by Gal converter
static class Event *qFRS_s0=rpGal->getRefEvent("qFRS_s0");   // inserted by Gal converter
static class Event *pOC_s0=rpGal->getRefEvent("pOC_s0");   // inserted by Gal converter
static class Event *pOC_ta=rpGal->getRefEvent("pOC_ta");   // inserted by Gal converter
static class Event *pOC_ts=rpGal->getRefEvent("pOC_ts");   // inserted by Gal converter
static class Event *uOC_s0=rpGal->getRefEvent("uOC_s0");   // inserted by Gal converter
static class Event *uOC_ta=rpGal->getRefEvent("uOC_ta");   // inserted by Gal converter
static class Event *uOC_ts=rpGal->getRefEvent("uOC_ts");   // inserted by Gal converter
static class Event *pIC_s0=rpGal->getRefEvent("pIC_s0");   // inserted by Gal converter
static class Event *pIC_ta=rpGal->getRefEvent("pIC_ta");   // inserted by Gal converter
static class Event *pIC_ts=rpGal->getRefEvent("pIC_ts");   // inserted by Gal converter
static class Event *sOCA_s0=rpGal->getRefEvent("sOCA_s0");   // inserted by Gal converter
static class Event *sOCA_ta=rpGal->getRefEvent("sOCA_ta");   // inserted by Gal converter
static class Event *sOCA_ts=rpGal->getRefEvent("sOCA_ts");   // inserted by Gal converter
static class Event *usOC_s0=rpGal->getRefEvent("usOC_s0");   // inserted by Gal converter
static class Event *usOC_ta=rpGal->getRefEvent("usOC_ta");   // inserted by Gal converter
static class Event *usOC_ts=rpGal->getRefEvent("usOC_ts");   // inserted by Gal converter
static class Event *sIC_s0=rpGal->getRefEvent("sIC_s0");   // inserted by Gal converter
static class Event *sIC_ts=rpGal->getRefEvent("sIC_ts");   // inserted by Gal converter
static class Event *sIC_ta=rpGal->getRefEvent("sIC_ta");   // inserted by Gal converter
static class Event *uIC_s0=rpGal->getRefEvent("uIC_s0");   // inserted by Gal converter
static class Event *uIC_ta=rpGal->getRefEvent("uIC_ta");   // inserted by Gal converter
static class Event *uIC_ts=rpGal->getRefEvent("uIC_ts");   // inserted by Gal converter
static class Event *usIC_s0=rpGal->getRefEvent("usIC_s0");   // inserted by Gal converter
static class Event *usIC_ta=rpGal->getRefEvent("usIC_ta");   // inserted by Gal converter
static class Event *usIC_ts=rpGal->getRefEvent("usIC_ts");   // inserted by Gal converter
static class Event *rOI_s0=rpGal->getRefEvent("rOI_s0");   // inserted by Gal converter
static class Event *rOIN_s0=rpGal->getRefEvent("rOIN_s0");   // inserted by Gal converter
static class Event *rOI_s1=rpGal->getRefEvent("rOI_s1");   // inserted by Gal converter
static class Event *rOI_ta=rpGal->getRefEvent("rOI_ta");   // inserted by Gal converter
static class Event *rOI_ts=rpGal->getRefEvent("rOI_ts");   // inserted by Gal converter
static class Event *uAV_s0=rpGal->getRefEvent("uAV_s0");   // inserted by Gal converter
static class Event *uAV_s1=rpGal->getRefEvent("uAV_s1");   // inserted by Gal converter
static class Event *uAV_ta=rpGal->getRefEvent("uAV_ta");   // inserted by Gal converter
static class Event *uAV_ts=rpGal->getRefEvent("uAV_ts");   // inserted by Gal converter
static class Event *sI_s0=rpGal->getRefEvent("sI_s0");   // inserted by Gal converter
static class Event *sI_s1=rpGal->getRefEvent("sI_s1");   // inserted by Gal converter
static class Event *sI_ta=rpGal->getRefEvent("sI_ta");   // inserted by Gal converter
static class Event *sI_ts=rpGal->getRefEvent("sI_ts");   // inserted by Gal converter
static class Event *dOI_s0=rpGal->getRefEvent("dOI_s0");   // inserted by Gal converter
static class Event *dOI_s1=rpGal->getRefEvent("dOI_s1");   // inserted by Gal converter
static class Event *dOI_ta=rpGal->getRefEvent("dOI_ta");   // inserted by Gal converter
static class Event *dOI_ts=rpGal->getRefEvent("dOI_ts");   // inserted by Gal converter
static class Event *lDOI_s0=rpGal->getRefEvent("lDOI_s0");   // inserted by Gal converter
static class Event *lDOI_ta=rpGal->getRefEvent("lDOI_ta");   // inserted by Gal converter
static class Event *lDOI_ts=rpGal->getRefEvent("lDOI_ts");   // inserted by Gal converter
static class Event *cATT_s0=rpGal->getRefEvent("cATT_s0");   // inserted by Gal converter
static class Event *cATT_ta=rpGal->getRefEvent("cATT_ta");   // inserted by Gal converter
static class Event *cATT_ts=rpGal->getRefEvent("cATT_ts");   // inserted by Gal converter
static class Event *cITT_s0=rpGal->getRefEvent("cITT_s0");   // inserted by Gal converter
static class Event *cITT_ta=rpGal->getRefEvent("cITT_ta");   // inserted by Gal converter
static class Event *cITT_ts=rpGal->getRefEvent("cITT_ts");   // inserted by Gal converter
static class Event *rOAVU_s0=rpGal->getRefEvent("rOAVU_s0");   // inserted by Gal converter
static class Event *rOAVU_ta=rpGal->getRefEvent("rOAVU_ta");   // inserted by Gal converter
static class Event *rOAVU_ts=rpGal->getRefEvent("rOAVU_ts");   // inserted by Gal converter
static class Event *rCAVU_s0=rpGal->getRefEvent("rCAVU_s0");   // inserted by Gal converter
static class Event *rCAVU_ta=rpGal->getRefEvent("rCAVU_ta");   // inserted by Gal converter
static class Event *rCAVU_ts=rpGal->getRefEvent("rCAVU_ts");   // inserted by Gal converter
static class Event *uAOD_s0=rpGal->getRefEvent("uAOD_s0");   // inserted by Gal converter
static class Event *uAOD_ta=rpGal->getRefEvent("uAOD_ta");   // inserted by Gal converter
static class Event *uAOD_ts=rpGal->getRefEvent("uAOD_ts");   // inserted by Gal converter
static class Event *nAOD_s0=rpGal->getRefEvent("nAOD_s0");   // inserted by Gal converter
static class Event *nAOD_ta=rpGal->getRefEvent("nAOD_ta");   // inserted by Gal converter
static class Event *nAOD_ts=rpGal->getRefEvent("nAOD_ts");   // inserted by Gal converter
static class Event *aOA_s0=rpGal->getRefEvent("aOA_s0");   // inserted by Gal converter
static class Event *aOA_ta=rpGal->getRefEvent("aOA_ta");   // inserted by Gal converter
static class Event *aOA_ts=rpGal->getRefEvent("aOA_ts");   // inserted by Gal converter
static class Event *aOAIA_s0=rpGal->getRefEvent("aOAIA_s0");   // inserted by Gal converter
static class Event *aOAIA_ta=rpGal->getRefEvent("aOAIA_ta");   // inserted by Gal converter
static class Event *aOAIA_ts=rpGal->getRefEvent("aOAIA_ts");   // inserted by Gal converter
static class Event *aORR_s0=rpGal->getRefEvent("aORR_s0");   // inserted by Gal converter
static class Event *aORR_ta=rpGal->getRefEvent("aORR_ta");   // inserted by Gal converter
static class Event *aORR_ts=rpGal->getRefEvent("aORR_ts");   // inserted by Gal converter
static class Event *cNAOD_s0=rpGal->getRefEvent("cNAOD_s0");   // inserted by Gal converter
static class Event *cNAOD_ta=rpGal->getRefEvent("cNAOD_ta");   // inserted by Gal converter
static class Event *cNAOD_ts=rpGal->getRefEvent("cNAOD_ts");   // inserted by Gal converter
static class Event *cAOA_s0=rpGal->getRefEvent("cAOA_s0");   // inserted by Gal converter
static class Event *cAOA_ta=rpGal->getRefEvent("cAOA_ta");   // inserted by Gal converter
static class Event *cAOA_ts=rpGal->getRefEvent("cAOA_ts");   // inserted by Gal converter
static class Event *qAO_s0=rpGal->getRefEvent("qAO_s0");   // inserted by Gal converter
static class Event *qAO_ta=rpGal->getRefEvent("qAO_ta");   // inserted by Gal converter
static class Event *qAO_ts=rpGal->getRefEvent("qAO_ts");   // inserted by Gal converter
static class Event *iAOBF_s0=rpGal->getRefEvent("iAOBF_s0");   // inserted by Gal converter
static class Event *iAOBF_ta=rpGal->getRefEvent("iAOBF_ta");   // inserted by Gal converter
static class Event *iAOBF_ts=rpGal->getRefEvent("iAOBF_ts");   // inserted by Gal converter
static class Event *eTR_s0=rpGal->getRefEvent("eTR_s0");   // inserted by Gal converter
static class Event *eTR_ta=rpGal->getRefEvent("eTR_ta");   // inserted by Gal converter
static class Event *eTR_ts=rpGal->getRefEvent("eTR_ts");   // inserted by Gal converter
static class Event *dTR_s0=rpGal->getRefEvent("dTR_s0");   // inserted by Gal converter
static class Event *dTR_ta=rpGal->getRefEvent("dTR_ta");   // inserted by Gal converter
static class Event *dTR_ts=rpGal->getRefEvent("dTR_ts");   // inserted by Gal converter
static class Event *eTC_s0=rpGal->getRefEvent("eTC_s0");   // inserted by Gal converter
static class Event *eTC_ts=rpGal->getRefEvent("eTC_ts");   // inserted by Gal converter
static class Event *eTC_ta=rpGal->getRefEvent("eTC_ta");   // inserted by Gal converter
static class Event *dTC_s0=rpGal->getRefEvent("dTC_s0");   // inserted by Gal converter
static class Event *dTC_ta=rpGal->getRefEvent("dTC_ta");   // inserted by Gal converter
static class Event *dTC_ts=rpGal->getRefEvent("dTC_ts");   // inserted by Gal converter
static class Event *tAR_s0=rpGal->getRefEvent("tAR_s0");   // inserted by Gal converter
static class Event *tAR_ta=rpGal->getRefEvent("tAR_ta");   // inserted by Gal converter
static class Event *tAR_ts=rpGal->getRefEvent("tAR_ts");   // inserted by Gal converter
static class Event *tARA_s0=rpGal->getRefEvent("tARA_s0");   // inserted by Gal converter
static class Event *tARA_ta=rpGal->getRefEvent("tARA_ta");   // inserted by Gal converter
static class Event *tARA_ts=rpGal->getRefEvent("tARA_ts");   // inserted by Gal converter
static class Event *nER_s0=rpGal->getRefEvent("nER_s0");   // inserted by Gal converter
static class Event *nER_ta=rpGal->getRefEvent("nER_ta");   // inserted by Gal converter
static class Event *nER_ts=rpGal->getRefEvent("nER_ts");   // inserted by Gal converter
static class Event *nERA_s0=rpGal->getRefEvent("nERA_s0");   // inserted by Gal converter
static class Event *nERA_ta=rpGal->getRefEvent("nERA_ta");   // inserted by Gal converter
static class Event *nERA_ts=rpGal->getRefEvent("nERA_ts");   // inserted by Gal converter
static class Event *fQR_s0=rpGal->getRefEvent("fQR_s0");   // inserted by Gal converter
static class Event *fQR_ta=rpGal->getRefEvent("fQR_ta");   // inserted by Gal converter
static class Event *fQR_ts=rpGal->getRefEvent("fQR_ts");   // inserted by Gal converter
static class Event *eAD_s0=rpGal->getRefEvent("eAD_s0");   // inserted by Gal converter
static class Event *eAD_ta=rpGal->getRefEvent("eAD_ta");   // inserted by Gal converter
static class Event *eAD_ts=rpGal->getRefEvent("eAD_ts");   // inserted by Gal converter
static class Event *dAD_s0=rpGal->getRefEvent("dAD_s0");   // inserted by Gal converter
static class Event *dAD_ta=rpGal->getRefEvent("dAD_ta");   // inserted by Gal converter
static class Event *dAD_ts=rpGal->getRefEvent("dAD_ts");   // inserted by Gal converter
static class Event *qLBTS_s0=rpGal->getRefEvent("qLBTS_s0");   // inserted by Gal converter
static class Event *qLBTS_ta=rpGal->getRefEvent("qLBTS_ta");   // inserted by Gal converter
static class Event *qLBTS_ts=rpGal->getRefEvent("qLBTS_ts");   // inserted by Gal converter
static class Event *qFT_s0=rpGal->getRefEvent("qFT_s0");   // inserted by Gal converter
static class Event *qFT_ta=rpGal->getRefEvent("qFT_ta");   // inserted by Gal converter
static class Event *qFT_ts=rpGal->getRefEvent("qFT_ts");   // inserted by Gal converter
static class Event *qMNET_s0=rpGal->getRefEvent("qMNET_s0");   // inserted by Gal converter
static class Event *qMNET_ta=rpGal->getRefEvent("qMNET_ta");   // inserted by Gal converter
static class Event *qMNET_ts=rpGal->getRefEvent("qMNET_ts");   // inserted by Gal converter
static class Event *mL_s0=rpGal->getRefEvent("mL_s0");   // inserted by Gal converter
static class Event *mL_ta=rpGal->getRefEvent("mL_ta");   // inserted by Gal converter
static class Event *mL_ts=rpGal->getRefEvent("mL_ts");   // inserted by Gal converter
static class Event *qL_s0=rpGal->getRefEvent("qL_s0");   // inserted by Gal converter
static class Event *qL_ta=rpGal->getRefEvent("qL_ta");   // inserted by Gal converter
static class Event *qL_ts=rpGal->getRefEvent("qL_ts");   // inserted by Gal converter
static class Event *r_s0=rpGal->getRefEvent("r_s0");   // inserted by Gal converter
static class Event *r_ta=rpGal->getRefEvent("r_ta");   // inserted by Gal converter
static class Event *r_ts=rpGal->getRefEvent("r_ts");   // inserted by Gal converter
static class Event *cAOT_s0=rpGal->getRefEvent("cAOT_s0");   // inserted by Gal converter
static class Event *cAOT_ta=rpGal->getRefEvent("cAOT_ta");   // inserted by Gal converter
static class Event *cAOT_ts=rpGal->getRefEvent("cAOT_ts");   // inserted by Gal converter
static class Event *cIOT_s0=rpGal->getRefEvent("cIOT_s0");   // inserted by Gal converter
static class Event *cIOT_ta=rpGal->getRefEvent("cIOT_ta");   // inserted by Gal converter
static class Event *cIOT_ts=rpGal->getRefEvent("cIOT_ts");   // inserted by Gal converter
static class Event *cR_s0=rpGal->getRefEvent("cR_s0");   // inserted by Gal converter
static class Event *cR_ta=rpGal->getRefEvent("cR_ta");   // inserted by Gal converter
static class Event *cR_ts=rpGal->getRefEvent("cR_ts");   // inserted by Gal converter
static class Event *nARM_s0=rpGal->getRefEvent("nARM_s0");   // inserted by Gal converter
static class Event *nARM_ta=rpGal->getRefEvent("nARM_ta");   // inserted by Gal converter
static class Event *nARM_ts=rpGal->getRefEvent("nARM_ts");   // inserted by Gal converter
static class Event *dR_s0=rpGal->getRefEvent("dR_s0");   // inserted by Gal converter
static class Event *dR_ta=rpGal->getRefEvent("dR_ta");   // inserted by Gal converter
static class Event *dR_ts=rpGal->getRefEvent("dR_ts");   // inserted by Gal converter
static class Event *rOIWR_s0=rpGal->getRefEvent("rOIWR_s0");   // inserted by Gal converter
static class Event *rOIWR_s1=rpGal->getRefEvent("rOIWR_s1");   // inserted by Gal converter
static class Event *rOIWR_ta=rpGal->getRefEvent("rOIWR_ta");   // inserted by Gal converter
static class Event *rOIWR_ts=rpGal->getRefEvent("rOIWR_ts");   // inserted by Gal converter
static class Event *aRFU_s0=rpGal->getRefEvent("aRFU_s0");   // inserted by Gal converter
static class Event *aRFU_ta=rpGal->getRefEvent("aRFU_ta");   // inserted by Gal converter
static class Event *aRFU_ts=rpGal->getRefEvent("aRFU_ts");   // inserted by Gal converter
static class Event *uRFU_s0=rpGal->getRefEvent("uRFU_s0");   // inserted by Gal converter
static class Event *uRFU_ta=rpGal->getRefEvent("uRFU_ta");   // inserted by Gal converter
static class Event *uRFU_ts=rpGal->getRefEvent("uRFU_ts");   // inserted by Gal converter
static class Event *sOCAWR_s0=rpGal->getRefEvent("sOCAWR_s0");   // inserted by Gal converter
static class Event *sOCAWR_ta=rpGal->getRefEvent("sOCAWR_ta");   // inserted by Gal converter
static class Event *sOCAWR_ts=rpGal->getRefEvent("sOCAWR_ts");   // inserted by Gal converter
static class Event *uOCWR_s0=rpGal->getRefEvent("uOCWR_s0");   // inserted by Gal converter
static class Event *uOCWR_ta=rpGal->getRefEvent("uOCWR_ta");   // inserted by Gal converter
static class Event *uOCWR_ts=rpGal->getRefEvent("uOCWR_ts");   // inserted by Gal converter
static class Event *sICWR_s0=rpGal->getRefEvent("sICWR_s0");   // inserted by Gal converter
static class Event *sICWR_ta=rpGal->getRefEvent("sICWR_ta");   // inserted by Gal converter
static class Event *sICWR_ts=rpGal->getRefEvent("sICWR_ts");   // inserted by Gal converter
static class Event *uICWR_s0=rpGal->getRefEvent("uICWR_s0");   // inserted by Gal converter
static class Event *uICWR_ta=rpGal->getRefEvent("uICWR_ta");   // inserted by Gal converter
static class Event *uICWR_ts=rpGal->getRefEvent("uICWR_ts");   // inserted by Gal converter
static class Event *sIWR_s0=rpGal->getRefEvent("sIWR_s0");   // inserted by Gal converter
static class Event *sIWR_s1=rpGal->getRefEvent("sIWR_s1");   // inserted by Gal converter
static class Event *sIWR_ta=rpGal->getRefEvent("sIWR_ta");   // inserted by Gal converter
static class Event *sIWR_ts=rpGal->getRefEvent("sIWR_ts");   // inserted by Gal converter
static class Event *rCAVUWR_s0=rpGal->getRefEvent("rCAVUWR_s0");   // inserted by Gal converter
static class Event *rCAVUWR_ta=rpGal->getRefEvent("rCAVUWR_ta");   // inserted by Gal converter
static class Event *rCAVUWR_ts=rpGal->getRefEvent("rCAVUWR_ts");   // inserted by Gal converter
static class Event *gOCH_s0=rpGal->getRefEvent("gOCH_s0");   // inserted by Gal converter
static class Event *gOCH_ta=rpGal->getRefEvent("gOCH_ta");   // inserted by Gal converter
static class Event *gOCH_ts=rpGal->getRefEvent("gOCH_ts");   // inserted by Gal converter
static class Event *gOCN_s0=rpGal->getRefEvent("gOCN_s0");   // inserted by Gal converter
static class Event *gOCN_ta=rpGal->getRefEvent("gOCN_ta");   // inserted by Gal converter
static class Event *gOCN_ts=rpGal->getRefEvent("gOCN_ts");   // inserted by Gal converter
static class Event *gAH_s0=rpGal->getRefEvent("gAH_s0");   // inserted by Gal converter
static class Event *gAH_ta=rpGal->getRefEvent("gAH_ta");   // inserted by Gal converter
static class Event *gAH_ts=rpGal->getRefEvent("gAH_ts");   // inserted by Gal converter
static class Event *gAN_s0=rpGal->getRefEvent("gAN_s0");   // inserted by Gal converter
static class Event *gAN_ta=rpGal->getRefEvent("gAN_ta");   // inserted by Gal converter
static class Event *gAN_ts=rpGal->getRefEvent("gAN_ts");   // inserted by Gal converter
static class Event *gICH_s0=rpGal->getRefEvent("gICH_s0");   // inserted by Gal converter
static class Event *gICH_ta=rpGal->getRefEvent("gICH_ta");   // inserted by Gal converter
static class Event *gICH_ts=rpGal->getRefEvent("gICH_ts");   // inserted by Gal converter
static class Event *gICN_s0=rpGal->getRefEvent("gICN_s0");   // inserted by Gal converter
static class Event *gICN_ta=rpGal->getRefEvent("gICN_ta");   // inserted by Gal converter
static class Event *gICN_ts=rpGal->getRefEvent("gICN_ts");   // inserted by Gal converter
static class Event *gPH_s0=rpGal->getRefEvent("gPH_s0");   // inserted by Gal converter
static class Event *gPH_ta=rpGal->getRefEvent("gPH_ta");   // inserted by Gal converter
static class Event *gPH_ts=rpGal->getRefEvent("gPH_ts");   // inserted by Gal converter
static class Event *gPN_s0=rpGal->getRefEvent("gPN_s0");   // inserted by Gal converter
static class Event *gPN_ta=rpGal->getRefEvent("gPN_ta");   // inserted by Gal converter
static class Event *gPN_ts=rpGal->getRefEvent("gPN_ts");   // inserted by Gal converter
static class Event *gOIH_s0=rpGal->getRefEvent("gOIH_s0");   // inserted by Gal converter
static class Event *gOIH_ta=rpGal->getRefEvent("gOIH_ta");   // inserted by Gal converter
static class Event *gOIH_ts=rpGal->getRefEvent("gOIH_ts");   // inserted by Gal converter
static class Event *gOIN_s0=rpGal->getRefEvent("gOIN_s0");   // inserted by Gal converter
static class Event *gOIN_ta=rpGal->getRefEvent("gOIN_ta");   // inserted by Gal converter
static class Event *gOIN_ts=rpGal->getRefEvent("gOIN_ts");   // inserted by Gal converter
static class Event *gRSH_s0=rpGal->getRefEvent("gRSH_s0");   // inserted by Gal converter
static class Event *gRSH_ta=rpGal->getRefEvent("gRSH_ta");   // inserted by Gal converter
static class Event *gRSH_ts=rpGal->getRefEvent("gRSH_ts");   // inserted by Gal converter
static class Event *gRSN_s0=rpGal->getRefEvent("gRSN_s0");   // inserted by Gal converter
static class Event *gRSN_ta=rpGal->getRefEvent("gRSN_ta");   // inserted by Gal converter
static class Event *gRSN_ts=rpGal->getRefEvent("gRSN_ts");   // inserted by Gal converter
static class Event *gDH_s0=rpGal->getRefEvent("gDH_s0");   // inserted by Gal converter
static class Event *gDH_ta=rpGal->getRefEvent("gDH_ta");   // inserted by Gal converter
static class Event *gDH_ts=rpGal->getRefEvent("gDH_ts");   // inserted by Gal converter
static class Event *gDN_s0=rpGal->getRefEvent("gDN_s0");   // inserted by Gal converter
static class Event *gDN_ta=rpGal->getRefEvent("gDN_ta");   // inserted by Gal converter
static class Event *gDN_ts=rpGal->getRefEvent("gDN_ts");   // inserted by Gal converter
static class Event *gDUB_s0=rpGal->getRefEvent("gDUB_s0");   // inserted by Gal converter
static class Event *gADFCA_s0=rpGal->getRefEvent("gADFCA_s0");   // inserted by Gal converter
static class Event *gARSH_s0=rpGal->getRefEvent("gARSH_s0");   // inserted by Gal converter
static class Event *gARSH_ta=rpGal->getRefEvent("gARSH_ta");   // inserted by Gal converter
static class Event *gARSH_ts=rpGal->getRefEvent("gARSH_ts");   // inserted by Gal converter
static class Event *gOC_s0=rpGal->getRefEvent("gOC_s0");   // inserted by Gal converter
static class Event *gOC_ta=rpGal->getRefEvent("gOC_ta");   // inserted by Gal converter
static class Event *gOC_ts=rpGal->getRefEvent("gOC_ts");   // inserted by Gal converter
static class Event *gADFIC_s0=rpGal->getRefEvent("gADFIC_s0");   // inserted by Gal converter
static class Event *gIRSH_s0=rpGal->getRefEvent("gIRSH_s0");   // inserted by Gal converter
static class Event *gIRSH_ta=rpGal->getRefEvent("gIRSH_ta");   // inserted by Gal converter
static class Event *gIRSH_ts=rpGal->getRefEvent("gIRSH_ts");   // inserted by Gal converter
static class Event *gTH_s0=rpGal->getRefEvent("gTH_s0");   // inserted by Gal converter
static class Event *gTH_ta=rpGal->getRefEvent("gTH_ta");   // inserted by Gal converter
static class Event *gTH_ts=rpGal->getRefEvent("gTH_ts");   // inserted by Gal converter
static class Event *gTN_s0=rpGal->getRefEvent("gTN_s0");   // inserted by Gal converter
static class Event *gTN_ta=rpGal->getRefEvent("gTN_ta");   // inserted by Gal converter
static class Event *gTN_ts=rpGal->getRefEvent("gTN_ts");   // inserted by Gal converter
static class Event *gOH_s0=rpGal->getRefEvent("gOH_s0");   // inserted by Gal converter
static class Event *gOH_ta=rpGal->getRefEvent("gOH_ta");   // inserted by Gal converter
static class Event *gOH_ts=rpGal->getRefEvent("gOH_ts");   // inserted by Gal converter
static class Event *gON_s0=rpGal->getRefEvent("gON_s0");   // inserted by Gal converter
static class Event *gON_ta=rpGal->getRefEvent("gON_ta");   // inserted by Gal converter
static class Event *gON_ts=rpGal->getRefEvent("gON_ts");   // inserted by Gal converter
static class Event *eCRAS_s0=rpGal->getRefEvent("eCRAS_s0");   // inserted by Gal converter
static class Event *eCRAS_ta=rpGal->getRefEvent("eCRAS_ta");   // inserted by Gal converter
static class Event *eCRAS_ts=rpGal->getRefEvent("eCRAS_ts");   // inserted by Gal converter
static class Event *dCRAS_s0=rpGal->getRefEvent("dCRAS_s0");   // inserted by Gal converter
static class Event *dCRAS_ta=rpGal->getRefEvent("dCRAS_ta");   // inserted by Gal converter
static class Event *dCRAS_ts=rpGal->getRefEvent("dCRAS_ts");   // inserted by Gal converter
static class Event *eARAS_s0=rpGal->getRefEvent("eARAS_s0");   // inserted by Gal converter
static class Event *eARAS_ta=rpGal->getRefEvent("eARAS_ta");   // inserted by Gal converter
static class Event *eARAS_ts=rpGal->getRefEvent("eARAS_ts");   // inserted by Gal converter
static class Event *dARAS_s0=rpGal->getRefEvent("dARAS_s0");   // inserted by Gal converter
static class Event *dARAS_ta=rpGal->getRefEvent("dARAS_ta");   // inserted by Gal converter
static class Event *dARAS_ts=rpGal->getRefEvent("dARAS_ts");   // inserted by Gal converter
static class Event *eASAS_s0=rpGal->getRefEvent("eASAS_s0");   // inserted by Gal converter
static class Event *eASAS_ta=rpGal->getRefEvent("eASAS_ta");   // inserted by Gal converter
static class Event *eASAS_ts=rpGal->getRefEvent("eASAS_ts");   // inserted by Gal converter
static class Event *dASAS_s0=rpGal->getRefEvent("dASAS_s0");   // inserted by Gal converter
static class Event *dASAS_ta=rpGal->getRefEvent("dASAS_ta");   // inserted by Gal converter
static class Event *dASAS_ts=rpGal->getRefEvent("dASAS_ts");   // inserted by Gal converter
static class Event *eIRAS_s0=rpGal->getRefEvent("eIRAS_s0");   // inserted by Gal converter
static class Event *eIRAS_ta=rpGal->getRefEvent("eIRAS_ta");   // inserted by Gal converter
static class Event *eIRAS_ts=rpGal->getRefEvent("eIRAS_ts");   // inserted by Gal converter
static class Event *dIRAS_s0=rpGal->getRefEvent("dIRAS_s0");   // inserted by Gal converter
static class Event *dIRAS_ta=rpGal->getRefEvent("dIRAS_ta");   // inserted by Gal converter
static class Event *dIRAS_ts=rpGal->getRefEvent("dIRAS_ts");   // inserted by Gal converter
static class Event *gDHS_s0=rpGal->getRefEvent("gDHS_s0");   // inserted by Gal converter
static class Event *gRB_s0=rpGal->getRefEvent("gRB_s0");   // inserted by Gal converter
static class Event *sRB_s0=rpGal->getRefEvent("sRB_s0");   // inserted by Gal converter
static class Event *nFH_s0=rpGal->getRefEvent("nFH_s0");   // inserted by Gal converter
static class Event *nSG_s0=rpGal->getRefEvent("nSG_s0");   // inserted by Gal converter
static class Event *eC_e=rpGal->getRefEvent("eC_e");   // inserted by Gal converter
static class Event *eMC_e=rpGal->getRefEvent("eMC_e");   // inserted by Gal converter
static class Event *eC_s1=rpGal->getRefEvent("eC_s1");   // inserted by Gal converter
static class Event *dC_s1=rpGal->getRefEvent("dC_s1");   // inserted by Gal converter
static class Event *gRT_e=rpGal->getRefEvent("gRT_e");   // inserted by Gal converter
static class Event *gR_e=rpGal->getRefEvent("gR_e");   // inserted by Gal converter
static class Event *gR_ts=rpGal->getRefEvent("gR_ts");   // inserted by Gal converter
static class Event *t_e=rpGal->getRefEvent("t_e");   // inserted by Gal converter
static class Event *RTI_e=rpGal->getRefEvent("RTI_e");   // inserted by Gal converter
static class Event *RTI_ts=rpGal->getRefEvent("RTI_ts");   // inserted by Gal converter
static class Event *RTId_e=rpGal->getRefEvent("RTId_e");   // inserted by Gal converter
static class Event *RTId_l=rpGal->getRefEvent("RTId_l");   // inserted by Gal converter

static char galMsg[MAX_TXT];

#endif

/*********************************** Gal end *********************************/   // inserted by Gal converter

#if _MSC_VER == 1200
RTI::RTIambassador::RTIambassador()
#else
RTI::RTIambassador::RTIambassador()
  throw()
#endif
{
}

#if _MSC_VER == 1200
RTI::RTIambassador::~RTIambassador()
#else
RTI::RTIambassador::~RTIambassador()
  throw()
#endif
{
}

RTI::FederateAmbassador::FederateAmbassador()
  throw (RTI::FederateInternalError)
{
}

RTI::FederateAmbassador::~FederateAmbassador()
  throw ()
{
}

GERTICO::UpperLowerBounds::UpperLowerBounds(GeRtiFactory::GeRtiHandle const &theLower, GeRtiFactory::GeRtiHandle const &theUpper)
{
  lower = theLower;
  upper = theUpper;
}

GERTICO::UpperLowerBounds::~UpperLowerBounds(void)
{
}

GERTICO::RegionI::RegionI(GeRtiFactory::GeRtiHandle const &theId)
{
  id = theId;
}

GERTICO::RegionI::~RegionI(void)
{
}

void GERTICO::RegionI::getId(GeRtiFactory::GeRtiHandle &theId)
{
  theId = id;
}

////////////////////////////////////
// Federation Management Services //
////////////////////////////////////

#define maxRetries 10
#define waitTime 20000 // micro seconds

// ---------------------------------------------------------------------------
// 4.2
// ---------------------------------------------------------------------------
void GERTICO::RTIambServices::createFederationExecution(
  std::wstring const & federationExecutionName,
  std::wstring const & fullPathNameToTheFDDfile)
throw(
  RTI::FederationExecutionAlreadyExists,
  RTI::CouldNotOpenFDD,
  RTI::ErrorReadingFDD,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cFE_s0)
                            {
                              sprintf(galMsg,"name=%ls,designator=%ls", federationExecutionName.c_str(), fullPathNameToTheFDDfile.c_str());
                              E1mEnd(cFE_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  std::wstring ws;
  int maxExceptions=0;

  for (maxExceptions = 0;;maxExceptions++)
  {
    try
    {
      sender->createFederationExecution(federationExecutionName, fullPathNameToTheFDDfile);
      break;
    }
    catch (GeRtiFactory::ConcurrentAccessAttempted &ex)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAA_d0,"ConcurrentAccessAttempted");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      if (maxExceptions < maxRetries)
      {
        ACE_OS::sleep(1);
        continue;
      }
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      throw RTI::RTIinternalError(ws.c_str());
    }
    catch(GeRtiFactory::FederationExecutionAlreadyExists &ex)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cFE_ta,"FederationExecutionAlreadyExists");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      throw RTI::FederationExecutionAlreadyExists(ws.c_str());
    }
    catch(GeRtiFactory::CouldNotOpenFED &ex)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cFE_ta,"CouldNotOpenFED");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      throw RTI::CouldNotOpenFDD(ws.c_str());
    }
    catch(GeRtiFactory::ErrorReadingFED &ex)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cFE_ta,"ErrorReadingFED");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      throw RTI::ErrorReadingFDD(ws.c_str());
    }
    catch(GeRtiFactory::RTIinternalError &ex)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cFE_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      throw RTI::RTIinternalError(ws.c_str());
    }
    catch(CORBA::SystemException &sysex)
    {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep(ACE_Time_Value(0,waitTime));
          continue;
        }
      }
      ACE_PRINT_EXCEPTION(sysex, "System Exception in createFederationExecution ");

                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cFE_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      throw RTI::RTIinternalError(L"CORBA::SystemException");
    }
    catch(...)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cFE_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      throw RTI::RTIinternalError(L"unknown Exception");
    }
  }
}

// ---------------------------------------------------------------------------
// 4.3
// ---------------------------------------------------------------------------
void GERTICO::RTIambServices::destroyFederationExecution(
  std::wstring const & federationExecutionName)
throw(
  RTI::FederatesCurrentlyJoined,
  RTI::FederationExecutionDoesNotExist,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(dFE_s0)
                            {
                              sprintf(galMsg,"name=%ls", federationExecutionName.c_str());
                              E1mEnd(dFE_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  std::wstring ws;
  int maxExceptions=0;

  for (maxExceptions = 0;;maxExceptions++)
  {
    try
    {
      sender->destroyFederationExecution(federationExecutionName);
      break;
    }
    catch(GeRtiFactory::FederatesCurrentlyJoined &ex)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dFE_ta,"FederatesCurrentlyJoined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      throw RTI::FederatesCurrentlyJoined(ws.c_str());
    }
    catch(GeRtiFactory::FederationExecutionDoesNotExist &ex)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dFE_ta,"FederationExecutionDoesNotExist");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      throw RTI::FederationExecutionDoesNotExist(ws.c_str());
    }
    catch(GeRtiFactory::RTIinternalError &ex)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dFE_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
      throw RTI::RTIinternalError(ws.c_str());
    }
    catch(CORBA::SystemException &sysex)
    {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep(ACE_Time_Value(0,waitTime));
          continue;
        }
      }
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dFE_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      throw RTI::RTIinternalError(L"CORBA::SystemException");
    }
    catch(...)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dFE_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      throw RTI::RTIinternalError(L"unknown Exception");
    }
  }
}

// 4.4
RTI::FederateHandle
GERTICO::RTIambServices::joinFederationExecution(
  std::wstring const & federateType,
  std::wstring const & federationExecutionName,
  RTI::FederateAmbassador & federateAmbassador,
  RTI::LogicalTimeFactory & logicalTimeFactory,
  RTI::LogicalTimeIntervalFactory & logicalTimeIntervalFactory)
throw(
  RTI::FederateAlreadyExecutionMember,
  RTI::FederationExecutionDoesNotExist,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(jFE_s0)
                            {
                              sprintf(galMsg,"type=%ls,name=%ls", federateType.c_str(), federationExecutionName.c_str());
                              E1mEnd(jFE_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::GeRtiHandle fedId;
  std::wstring ws;

  myLogicalTimeFactory = new GERTICO::GeRtiFedTimeFactory(logicalTimeFactory, logicalTimeIntervalFactory);
  myLogicalTimeIntervalFactory = new GERTICO::GeRtiLogicalTimeIntervalFactory(logicalTimeIntervalFactory);
  receiverI->initiate(&federateAmbassador);

  try
  {
    fedId = sender->joinFederationExecution(federateType, federationExecutionName, *myLogicalTimeFactory, *myLogicalTimeIntervalFactory);
  }
  catch(GeRtiFactory::FederateAlreadyExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(jFE_ta,"FederateAlreadyExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateAlreadyExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::FederationExecutionDoesNotExist &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(jFE_ta,"FederationExecutionDoesNotExist");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederationExecutionDoesNotExist(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(jFE_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(jFE_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(jFE_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(jFE_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(jFE_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(jFE_s0)
                            {
                              unsigned long ul;

                              ul = fedId;
                              sprintf(galMsg, "ret=%lu", ul);
                              E1mEnd(jFE_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::FederateHandle ret(fedId);
  return ret;
}

// 4.5
void GERTICO::RTIambServices::resignFederationExecution(
  RTI::ResignAction resignAction)
throw(
  RTI::OwnershipAcquisitionPending,
  RTI::FederateOwnsAttributes,
  RTI::FederateNotExecutionMember,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rFE_s0)
                            {
                              strcpy(galMsg,"action=NO_ACTION");
                              if (resignAction == RTI::UNCONDITIONALLY_DIVEST_ATTRIBUTES)
                              {
                                strcpy(galMsg,"action=UNCONDITIONALLY_DIVEST_ATTRIBUTES");
                              }
                              if (resignAction == RTI::DELETE_OBJECTS)
                              {
                                strcpy(galMsg,"action=DELETE_OBJECTS");
                              }
                              if (resignAction == RTI::CANCEL_PENDING_OWNERSHIP_ACQUISITIONS)
                              {
                                strcpy(galMsg,"action=CANCEL_PENDING_OWNERSHIP_ACQUISITIONS");
                              }
                              if (resignAction == RTI::DELETE_OBJECTS_THEN_DIVEST)
                              {
                                strcpy(galMsg,"action=DELETE_OBJECTS_THEN_DIVEST");
                              }
                              if (resignAction == RTI::CANCEL_THEN_DELETE_THEN_DIVEST)
                              {
                                strcpy(galMsg,"action=CANCEL_THEN_DELETE_THEN_DIVEST");
                              }
                              E1mEnd(rFE_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::ResignAction ra = GeRtiFactory::noAction;
  int maxExceptions=0;
  std::wstring ws;

  if (resignAction == RTI::UNCONDITIONALLY_DIVEST_ATTRIBUTES)
  {
    ra = GeRtiFactory::unconditionallyDivestAttributes;
  }
  else
  {
    if (resignAction == RTI::DELETE_OBJECTS)
    {
      ra = GeRtiFactory::deleteObjects;
    }
    else
    {
      if (resignAction == RTI::CANCEL_PENDING_OWNERSHIP_ACQUISITIONS)
      {
        ra = GeRtiFactory::cancelPendingOwnershipAquisitions;
      }
      else
      {
        if (resignAction == RTI::DELETE_OBJECTS_THEN_DIVEST)
        {
          ra = GeRtiFactory::deleteObjectsThenDivest;
        }
        else
        {
          if (resignAction == RTI::CANCEL_THEN_DELETE_THEN_DIVEST)
          {
            ra = GeRtiFactory::cancelThenDeleteThenDivest;
          }
          else
          {
            ra = GeRtiFactory::noAction;
          }
        }
      }
    }
  }

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->resignFederationExecution(ra);
    break;
  }
  catch(GeRtiFactory::OwnershipAcquisitionPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFE_ta,"OwnershipAcquisitionPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::OwnershipAcquisitionPending(ws.c_str());
  }
  catch(GeRtiFactory::FederateOwnsAttributes &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFE_ta,"FederateOwnsAttributes");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateOwnsAttributes(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFE_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFE_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in resignFederationExecution ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFE_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFE_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// 4.6
void GERTICO::RTIambServices::registerFederationSynchronizationPoint(
  std::wstring const & label,
  RTI::UserSuppliedTag const & theUserSuppliedTag)
throw(
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::UserSuppliedTag tag;
  std::wstring ws;

  GERTICO::Mapper1516::mapUserSuppliedTag(tag, theUserSuppliedTag);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rFSP_s0)
                            {
                              sprintf(galMsg,"label=%ls", label.c_str());
                              E1mEnd(rFSP_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rFSP_s0)
                            {
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, tag);
                              E1mEnd(rFSP_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->registerFederationSynchronizationPoint(label, tag);
    break;
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFSP_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFSP_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFSP_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFSP_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep(ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in registerFederationSynchronizationPoint ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFSP_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFSP_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

void GERTICO::RTIambServices::registerFederationSynchronizationPoint(
  std::wstring const & label,
  RTI::UserSuppliedTag const & theUserSuppliedTag,
  RTI::FederateHandleSet const & syncSet)
throw(
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::UserSuppliedTag tag;
  GeRtiFactory::Handles designators;
  std::wstring ws;

  GERTICO::Mapper1516::mapUserSuppliedTag(tag, theUserSuppliedTag);
  GERTICO::Mapper1516::mapFederateHandleSet(designators, syncSet);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rFSP_s1)
                            {
                              sprintf(galMsg,"label=%ls", label.c_str());
                              E1mEnd(rFSP_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rFSP_s1)
                            {
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, tag);
                              E1mEnd(rFSP_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rFSP_s1)
                            {
                              GERTICO::Mapper::printGeRtiFactoryHandles("syncSet=", galMsg, designators);
                              E1mEnd(rFSP_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->registerFederationSynchronizationPoint(label, tag, designators);
    break;
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFSP_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFSP_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFSP_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFSP_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep(ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in registerFederationSynchronizationPoint ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFSP_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFSP_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// 4.9
void GERTICO::RTIambServices::synchronizationPointAchieved(
  std::wstring const & label)
throw(
  RTI::SynchronizationPointLabelNotAnnounced,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sPA_s0)
                            {
                              sprintf(galMsg,"label=%ls", label.c_str());
                              E1mEnd(sPA_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->synchronizationPointAchieved(label);
    break;
  }
  catch(GeRtiFactory::SynchronizationPointLabelWasNotAnnounced &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sPA_ta,"SynchronizationPointLabelWasNotAnnounced");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SynchronizationPointLabelNotAnnounced(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sPA_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sPA_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sPA_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sPA_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep(ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in synchronizationPointAchieved ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sPA_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sPA_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// 4.11
void GERTICO::RTIambServices::requestFederationSave(
  std::wstring const & label,
  RTI::LogicalTime const & theTime)
throw(
  RTI::LogicalTimeAlreadyPassed,
  RTI::InvalidLogicalTime,
  RTI::FederateUnableToUseTime,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());
  int maxExceptions=0;
  std::wstring ws;

  GERTICO::Mapper1516::mapLogicalTime(*myLogicalTimeFactory, geRtiFedTime, theTime);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rFS_s0)
                            {
                              char timeBuff[512];
                              std::string l;

                              GERTICO::Mapper::mapStringFromWstring(l, label);
                              geRtiFedTime->getPrintableString(timeBuff);
                              sprintf(galMsg,"label=%ls,time=%s", label.c_str(), timeBuff);
                              E1mEnd(rFS_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->requestFederationSave(label, *geRtiFedTime);
    break;
  }
  catch(GeRtiFactory::FederationTimeAlreadyPassed &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ta,"FederationTimeAlreadyPassed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::LogicalTimeAlreadyPassed(ws.c_str());
  }
  catch(GeRtiFactory::InvalidFederationTime &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidLogicalTime(ws.c_str());
  }
  catch(GeRtiFactory::FederateUnableToUseTime &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ta,"FederateUnableToUseTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateUnableToUseTime(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep(ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in requestFederationSave ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

void GERTICO::RTIambServices::requestFederationSave(
  std::wstring const & label)
  throw(
    RTI::FederateNotExecutionMember,
    RTI::SaveInProgress,
    RTI::RestoreInProgress,
    RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rFS_s1)
                            {
                              sprintf(galMsg,"label=%ls", label.c_str());
                              E1mEnd(rFS_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->requestFederationSave(label);
    break;
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep(ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in requestFederationSave ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFS_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// 4.13
void GERTICO::RTIambServices::federateSaveBegun()
throw(
  RTI::SaveNotInitiated,
  RTI::FederateNotExecutionMember,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(fSB_s0);
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->federateSaveBegun();
    break;
  }
  catch(GeRtiFactory::SaveNotInitiated &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSB_ta,"SaveNotInitiated");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveNotInitiated(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSB_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSB_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSB_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep(ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in federateSaveBegun ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSB_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSB_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// 4.14
void GERTICO::RTIambServices::federateSaveComplete()
throw(
  RTI::FederateHasNotBegunSave,
  RTI::FederateNotExecutionMember,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(fSC_s0);
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->federateSaveComplete(true);
    break;
  }
  catch(GeRtiFactory::SaveNotInitiated &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSC_ta,"SaveNotInitiated");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateHasNotBegunSave(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSC_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep(ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in federateSaveComplete ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

void GERTICO::RTIambServices::federateSaveNotComplete()
throw(
  RTI::FederateHasNotBegunSave,
  RTI::FederateNotExecutionMember,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(fSNC_s0);
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->federateSaveComplete(false);
    break;
  }
  catch(GeRtiFactory::SaveNotInitiated &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSNC_ta,"SaveNotInitiated");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateHasNotBegunSave(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSNC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSNC_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSNC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep(ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in federateSaveNotComplete ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSNC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fSNC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// 4.16
void GERTICO::RTIambServices::queryFederationSaveStatus()
throw(
  RTI::FederateNotExecutionMember,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(qFSS_s0);
                           #endif   // inserted by Gal converter
  std::wstring ws;

  try
  {
    sender->queryFederationSaveStatus();
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in queryFederationSaveStatus ");
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}


// 4.16
void GERTICO::RTIambServices::requestFederationRestore(
  std::wstring const & label)
throw(
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rFR_s0)
                            {
                              sprintf(galMsg,"label=%ls", label.c_str());
                              E1mEnd(rFR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->requestFederationRestore(label);
    break;
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep(ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in requestFederationRestore ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rFR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// 4.20
void GERTICO::RTIambServices::federateRestoreComplete()
  throw(
    RTI::RestoreNotRequested,
    RTI::FederateNotExecutionMember,
    RTI::SaveInProgress,
    RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(fRC_s0);
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->federateRestoreComplete(true);
    break;
  }
  catch(GeRtiFactory::RestoreNotRequested &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fRC_ta,"RestoreNotRequested");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreNotRequested(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fRC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fRC_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fRC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep(ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in federateRestoreComplete ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fRC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fRC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

void GERTICO::RTIambServices::federateRestoreNotComplete()
throw(
  RTI::RestoreNotRequested,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(fRNC_s0);
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  std::wstring ws;

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->federateRestoreComplete(false);
    break;
  }
  catch(GeRtiFactory::RestoreNotRequested &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fRNC_ta,"RestoreNotRequested");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreNotRequested(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fRNC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fRNC_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fRNC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep(ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in federateRestoreNotComplete ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fRNC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fRNC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// XXX 4.24
void GERTICO::RTIambServices::queryFederationRestoreStatus()
throw(
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(qFRS_s0);
                           #endif   // inserted by Gal converter
  std::wstring ws;

  try
  {
    sender->queryFederationRestoreStatus();
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in queryFederationRestoreStatus ");
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

/////////////////////////////////////
// Declaration Management Services //
/////////////////////////////////////

// 5.2
void GERTICO::RTIambServices::publishObjectClassAttributes (
  RTI::ObjectClassHandle  const & theClass,
  RTI::AttributeHandleSet const & attributeList)
throw (
  RTI::ObjectClassNotDefined,
  RTI::AttributeNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle classHandle;
  GeRtiFactory::Handles handles;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectClassHandle(classHandle, theClass);
  GERTICO::Mapper1516::mapAttributeHandleSet(handles, attributeList);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(pOC_s0)
                            {
                              unsigned long ul;

                              ul = classHandle;
                              sprintf(galMsg,"class=%lu", ul);
                              E1mEnd(pOC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(pOC_s0)
                            {
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributeList=", galMsg, handles);
                              E1mEnd(pOC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->publishObjectClass(classHandle, handles);
    break;
  }
  catch(GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pOC_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pOC_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pOC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pOC_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pOC_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pOC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in publishObjectClass ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pOC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pOC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }

  if (sender->checkReportServiceInvocation())
  {
    CORBA::ULong i;
    CORBA::ULong len;
    CORBA::ULong pos;
    long l;
    GERTICO::MomReportServiceInvocation momReportServiceInvocation;
    char buf[256];
    char buf1[128];
    char buf2[128];
    std::wstring ws;
    size_t size;

    momReportServiceInvocation.service = L"publishObjectClass";
    momReportServiceInvocation.initiatorEnum = GERTICO::FederateEnum;
    momReportServiceInvocation.successIndicator = true;
    l = classHandle;
    sprintf(buf1,"%ld", l);
    pos = 0;
    len = handles.length();
    for (i = 0; i < len; i++)
    {
      if (pos)
      {
        l = handles[i];
        sprintf(&buf2[pos], ",%ld", l);
      }
      else
      {
        l = handles[i];
        sprintf(&buf2[pos], "%ld", l);
      }
      size = strlen(buf2);
      GERTICO::Mapper::mapULongSizet(pos, size);
    }
    sprintf(buf, "%s %s", buf1, buf2);
    GERTICO::Mapper::mapWstringFromChar(ws, buf);
    momReportServiceInvocation.suppliedArguments = ws;
//    momReportServiceInvocation.returnedArgument =
//    momReportServiceInvocation.exceptionDescription =
//    momReportServiceInvocation.exceptionId =
    sender->sendReportServiceInvocation(momReportServiceInvocation);
  }
}

// 5.3
void GERTICO::RTIambServices::unpublishObjectClass (
  RTI::ObjectClassHandle const & theClass)
throw (
  RTI::ObjectClassNotDefined,
  RTI::OwnershipAcquisitionPending,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  unsigned long ul;
  GeRtiFactory::GeRtiHandle classHandle;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectClassHandle(classHandle, theClass);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uOC_s0)
                            {
                              ul = classHandle;
                              sprintf(galMsg,"class=%lu", ul);
                              E1mEnd(uOC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    sender->unpublishObjectClass(classHandle);
  }
  catch(GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOC_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::OwnershipAcquisitionPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOC_ta,"OwnershipAcquisitionPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::OwnershipAcquisitionPending(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOC_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOC_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in unpublishObjectClass ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// XXX 5.3
void GERTICO::RTIambServices::unpublishObjectClassAttributes
(RTI::ObjectClassHandle  const & theClass,
 RTI::AttributeHandleSet const & attributeList)
  throw (RTI::ObjectClassNotDefined,
         RTI::AttributeNotDefined,
         RTI::OwnershipAcquisitionPending,
         RTI::FederateNotExecutionMember,
         RTI::SaveInProgress,
         RTI::RestoreInProgress,
         RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle classHandle;
  GeRtiFactory::Handles attributes;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectClassHandle(classHandle, theClass);
  GERTICO::Mapper1516::mapAttributeHandleSet(attributes, attributeList);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uOC_s0)
                            {
                              unsigned long ul;

                              ul = classHandle;
                              sprintf(galMsg,"class=%lu", ul);
                              E1mEnd(uOC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uOC_s0)
                            {
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributeList=", galMsg, attributes);
                              E1mEnd(uOC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    sender->unpublishObjectClassAttributes(classHandle, attributes);
  }
  catch(GeRtiFactory::ObjectClassNotDefined &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::OwnershipAcquisitionPending &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::OwnershipAcquisitionPending(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in unpublishObjectClassAttributes ");
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 5.4
void GERTICO::RTIambServices::publishInteractionClass (
  RTI::InteractionClassHandle const & theInteraction)
throw (
  RTI::InteractionClassNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  unsigned long ul;
  GeRtiFactory::GeRtiHandle classHandle;
  int maxExceptions=0;
  std::wstring ws;

  GERTICO::Mapper1516::mapInteractionClassHandle(classHandle, theInteraction);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(pIC_s0)
                            {
                              ul = classHandle;
                              sprintf(galMsg,"class=%lu",ul);
                              E1mEnd(pIC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->publishInteractionClass(classHandle);
    break;
  }
  catch(GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pIC_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pIC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pIC_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pIC_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pIC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in publishInteractionClass ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pIC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(pIC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// 5.5
void GERTICO::RTIambServices::unpublishInteractionClass (
  RTI::InteractionClassHandle const & theInteraction)
throw (
  RTI::InteractionClassNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  unsigned long ul;
  GeRtiFactory::GeRtiHandle classHandle;
  int maxExceptions=0;
  std::wstring ws;

  GERTICO::Mapper1516::mapInteractionClassHandle(classHandle, theInteraction);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uIC_s0)
                            {
                              ul = classHandle;
                              sprintf(galMsg,"class=%lu", ul);
                              E1mEnd(uIC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->unpublishInteractionClass(classHandle);
    break;
  }
  catch(GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uIC_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::InteractionClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uIC_ta,"InteractionClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionClassNotPublished(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uIC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uIC_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uIC_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uIC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in unpublishInteractionClass ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uIC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uIC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// 5.6
void GERTICO::RTIambServices::subscribeObjectClassAttributes (
  RTI::ObjectClassHandle  const & theClass,
  RTI::AttributeHandleSet const & attributeList,
  bool active)
throw (
  RTI::ObjectClassNotDefined,
  RTI::AttributeNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle classHandle;
  GeRtiFactory::Handles handles;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectClassHandle(classHandle, theClass);
  GERTICO::Mapper1516::mapAttributeHandleSet(handles, attributeList);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sOCA_s0)
                            {
                              unsigned long ul;

                              ul = classHandle;
                              if (active)
                              {
                                sprintf(galMsg,"class=%lu, active=true", ul);
                              }
                              else
                              {
                                sprintf(galMsg,"class=%lu, active=false", ul);
                              }
                              E1mEnd(sOCA_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sOCA_s0)
                            {
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributeList=", galMsg, handles);
                              E1mEnd(sOCA_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->subscribeObjectClassAttributes(classHandle, handles, active);
    break;
  }
  catch(GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCA_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCA_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCA_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCA_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCA_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCA_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in subscribeObjectClassAttributes ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCA_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCA_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// 5.7
void GERTICO::RTIambServices::unsubscribeObjectClass (
  RTI::ObjectClassHandle const & theClass)
throw (
  RTI::ObjectClassNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  unsigned long ul;

  GeRtiFactory::GeRtiHandle classHandle;
  int maxExceptions=0;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectClassHandle(classHandle, theClass);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(usOC_s0)
                            {
                              ul = classHandle;
                              sprintf(galMsg,"class=%lu",ul);
                              E1mEnd(usOC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->unsubscribeObjectClass(classHandle);
    break;
  }
  catch(GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usOC_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usOC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usOC_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usOC_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usOC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in unsubscribeObjectClass ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usOC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usOC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// XXX
void GERTICO::RTIambServices::unsubscribeObjectClassAttributes
(RTI::ObjectClassHandle  const & theClass,
 RTI::AttributeHandleSet const & attributeList)
  throw (RTI::ObjectClassNotDefined,
         RTI::AttributeNotDefined,
         RTI::FederateNotExecutionMember,
         RTI::SaveInProgress,
         RTI::RestoreInProgress,
         RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle classHandle;
  GeRtiFactory::Handles handles;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectClassHandle(classHandle, theClass);
  GERTICO::Mapper1516::mapAttributeHandleSet(handles, attributeList);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(usOC_s0)
                            {
                              unsigned long ul;

                              ul = classHandle;
                              sprintf(galMsg,"class=%lu",ul);
                              E1mEnd(usOC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(usOC_s0)
                            {
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributeList=", galMsg, handles);
                              E1mEnd(usOC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    sender->unsubscribeObjectClassAttributes(classHandle, handles);
  }
  catch(GeRtiFactory::ObjectClassNotDefined &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in unsubscribeObjectClassAttributes ");
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 5.8
void GERTICO::RTIambServices::subscribeInteractionClass (
  RTI::InteractionClassHandle const & theClass,
  bool active)
throw (
  RTI::InteractionClassNotDefined,
  RTI::FederateServiceInvocationsAreBeingReportedViaMOM,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  unsigned long ul;
  CORBA::Boolean boo = 0;
  GeRtiFactory::GeRtiHandle classHandle;
  std::wstring ws;

  GERTICO::Mapper1516::mapInteractionClassHandle(classHandle, theClass);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sIC_s0)
                            {
                              ul = classHandle;
                              if (active)
                              {
                                sprintf(galMsg,"class=%lu,active=true", ul);
                              }
                              else
                              {
                                sprintf(galMsg,"class=%lu,active=false", ul);
                              }
                              E1mEnd(sIC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  if (active)
  {
    boo = 1;
  }

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->subscribeInteractionClass(classHandle, boo);
    break;
  }
  catch(GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIC_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::FederateServiceInvocationsAreBeingReportedViaMOM &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIC_ta,"FederateServiceInvocationsAreBeingReportedViaMOM");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateServiceInvocationsAreBeingReportedViaMOM(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIC_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIC_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < 3)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in subscribeInteractionClass ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// 5.9
void GERTICO::RTIambServices::unsubscribeInteractionClass (
  RTI::InteractionClassHandle const & theClass)
throw (
  RTI::InteractionClassNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  unsigned long ul;
  GeRtiFactory::GeRtiHandle classHandle;
  int maxExceptions=0;
  std::wstring ws;

  GERTICO::Mapper1516::mapInteractionClassHandle(classHandle, theClass);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(usIC_s0)
                            {
                              ul = classHandle;
                              sprintf(galMsg,"class=%lu",ul);
                              E1mEnd(usIC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->unsubscribeInteractionClass(classHandle);
    break;
  }
  catch(GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usIC_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usIC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usIC_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usIC_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usIC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in unsubscribeInteractionClass ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usIC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(usIC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

////////////////////////////////
// Object Management Services //
////////////////////////////////

// XXX 6.2
void GERTICO::RTIambServices::reserveObjectInstanceName
(std::wstring const & theObjectInstanceName)
  throw (RTI::IllegalName,
         RTI::FederateNotExecutionMember,
         RTI::SaveInProgress,
         RTI::RestoreInProgress,
         RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rOIN_s0)
                            {
                              std::string l;
                              GERTICO::Mapper::mapStringFromWstring(l, theObjectInstanceName);
                              E1mEnd(rOIN_s0,l.c_str());
                            }
                           #endif   // inserted by Gal converter
  std::wstring ws;

  try
  {
    sender->reserveObjectInstanceName(theObjectInstanceName);
  }
  catch(GeRtiFactory::IllegalName &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::IllegalName(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in reserveObjectInstanceName ");
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 6.2
RTI::ObjectInstanceHandle
GERTICO::RTIambServices::registerObjectInstance (
  RTI::ObjectClassHandle const & theClass,
  std::wstring const & theObjectInstanceName)
throw (
  RTI::ObjectClassNotDefined,
  RTI::ObjectClassNotPublished,
  RTI::ObjectInstanceNameNotReserved,
  RTI::ObjectInstanceNameInUse,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle classHandle;
  GeRtiFactory::GeRtiHandle objectId;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectClassHandle(classHandle, theClass);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rOI_s0)
                            {
                              unsigned long ul;

                              ul = classHandle;
                              sprintf(galMsg,"class=%lu,object=%ls", ul, theObjectInstanceName.c_str());
                              E1mEnd(rOI_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    objectId = sender->registerObjectInstance(classHandle, theObjectInstanceName);
  }
  catch(GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::ObjectClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ta,"ObjectClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassNotPublished(ws.c_str());
  }
  catch(GeRtiFactory::ObjectInstanceNameNotReserved &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ta,"ObjectInstanceNameNotReserved");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNameNotReserved(ws.c_str());
  }
  catch(GeRtiFactory::ObjectInstanceNameInUse &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ta,"ObjectInstanceNameInUse");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNameInUse(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in registerObjectInstance ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rOI_s0)
                            {
                              unsigned long ul;

                              ul = objectId;
                              sprintf(galMsg, "ret=%lu", ul);
                              E1mEnd(rOI_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::ObjectInstanceHandle ret(objectId);
  return ret;
}

RTI::ObjectInstanceHandle
GERTICO::RTIambServices::registerObjectInstance (
  RTI::ObjectClassHandle const & theClass)
throw (
  RTI::ObjectClassNotDefined,
  RTI::ObjectClassNotPublished,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle classHandle;
  GeRtiFactory::GeRtiHandle objectId;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectClassHandle(classHandle, theClass);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rOI_s1)
                            {
                              unsigned long ul;

                              ul = classHandle;
                              sprintf(galMsg,"class=%lu",ul);
                              E1mEnd(rOI_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    objectId = sender->registerObjectInstance(classHandle);
  }
  catch(GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::ObjectClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ta,"ObjectClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassNotPublished(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in registerObjectInstance ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOI_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rOI_s1)
                            {
                              unsigned long ul;

                              ul = objectId;
                              sprintf(galMsg,"ret=%lu", ul);
                              E1mEnd(rOI_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::ObjectInstanceHandle ret(objectId);
  return ret;
}

// 6.4
std::auto_ptr< RTI::MessageRetractionHandle >
GERTICO::RTIambServices::updateAttributeValues (
  RTI::ObjectInstanceHandle const & theObject,
  RTI::AttributeHandleValueMap const & theAttributeValues,
  RTI::UserSuppliedTag const & theUserSuppliedTag,
  RTI::LogicalTime const & theTime)
throw (
  RTI::ObjectInstanceNotKnown,
  RTI::AttributeNotDefined,
  RTI::AttributeNotOwned,
  RTI::InvalidLogicalTime,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());
  GeRtiFactory::GeRtiHandle objectHandle;
  GeRtiFactory::HandleValues handleValues;
  GeRtiFactory::ERHandle erHandle;
  GeRtiFactory::UserSuppliedTag tag;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandleValueMap(handleValues, theAttributeValues);
  GERTICO::Mapper1516::mapUserSuppliedTag(tag, theUserSuppliedTag);
  GERTICO::Mapper1516::mapLogicalTime(*myLogicalTimeFactory, geRtiFedTime, theTime);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uAV_s0)
                            {
                              char timeBuff[512];
                              unsigned long ul;

                              ul = objectHandle;
                              geRtiFedTime->getPrintableString(timeBuff);
                              sprintf(galMsg,"object=%lu,time=%s", ul, timeBuff);
                              E1mEnd(uAV_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uAV_s0)
                            {
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, tag);
                              E1mEnd(uAV_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uAV_s0)
                            {
                              unsigned int indItem;
                              unsigned long lenItems;
                              lenItems = handleValues.length();
                              for (indItem = 0; indItem < lenItems; indItem++)
                              {
                                GERTICO::Mapper::printAttributeHandleValue("attributeValue=", galMsg, handleValues[indItem]);
                                E1mEnd(uAV_s0,galMsg);
                              }
                            }
                           #endif   // inserted by Gal converter

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    erHandle = sender->updateAttributeValues(objectHandle, handleValues, *geRtiFedTime, tag);
    break;
  }
  catch(GeRtiFactory::ObjectNotKnown &ex)
  {
std::cout << "updateAttributeValues ObjectInstanceNotKnown" << std::endl;
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNotKnown(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
std::cout << "updateAttributeValues ObjectInstanceNotKnown" << std::endl;
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNotKnown(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotOwned &ex)
  {
std::cout << "updateAttributeValues AttributeNotOwned" << std::endl;
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"AttributeNotOwned");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotOwned(ws.c_str());
  }
  catch(GeRtiFactory::InvalidFederationTime &ex)
  {
std::cout << "updateAttributeValues InvalidLogicalTime" << std::endl;
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"InvalidLogicalTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidLogicalTime(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
std::cout << "updateAttributeValues FederateNotExecutionMember" << std::endl;
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
std::cout << "updateAttributeValues SaveInProgress" << std::endl;
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
std::cout << "updateAttributeValues RestoreInProgress" << std::endl;
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
std::cout << "updateAttributeValues RTIinternalError" << std::endl;
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
std::cout << "updateAttributeValues System Exception" << std::endl;
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in updateAttributeValues ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }


                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uAV_s0)
                            {
                              unsigned long ul;
                              unsigned long ul1;

                              ul = erHandle.theSerialNumber;
                              ul1 = erHandle.sendingFederate;
                              sprintf(galMsg,"serialNumber=%lu,sendingFederate=%lu", ul, ul1);
                              E1mEnd(uAV_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::MessageRetractionHandle *messageRetractionHandlePtr = new RTI::MessageRetractionHandle();
  GERTICO::Mapper1516::mapMessageRetractionHandle(*messageRetractionHandlePtr, erHandle);
  RTI::MessageRetractionHandle *messageRetractionHandlePtrr = new RTI::MessageRetractionHandle(*messageRetractionHandlePtr);
  std::auto_ptr< RTI::MessageRetractionHandle > ret(messageRetractionHandlePtrr);
  return ret;
}

void GERTICO::RTIambServices::updateAttributeValues (
  RTI::ObjectInstanceHandle const & theObject,
  RTI::AttributeHandleValueMap const & theAttributeValues,
  RTI::UserSuppliedTag const & theUserSuppliedTag)
throw (
  RTI::ObjectInstanceNotKnown,
  RTI::AttributeNotDefined,
  RTI::AttributeNotOwned,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle objectHandle;
  GeRtiFactory::HandleValues handleValues;
  GeRtiFactory::UserSuppliedTag tag;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandleValueMap(handleValues, theAttributeValues);
  GERTICO::Mapper1516::mapUserSuppliedTag(tag, theUserSuppliedTag);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uAV_s1)
                            {
                              unsigned long ul;

                              ul = objectHandle;
                              sprintf(galMsg,"object=%lu",ul);
                              E1mEnd(uAV_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uAV_s1)
                            {
                              unsigned int indItem;
                              unsigned long lenItems;
                              lenItems = handleValues.length();
                              for (indItem = 0; indItem < lenItems; indItem++)
                              {
                                GERTICO::Mapper::printAttributeHandleValue("attributeValue=", galMsg, handleValues[indItem]);
                                E1mEnd(uAV_s1,galMsg);
                              }
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uAV_s1)
                            {
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, tag);
                              E1mEnd(uAV_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->updateAttributeValues(objectHandle, handleValues, tag);
    break;
  }
  catch(GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNotKnown(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotOwned &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"AttributeNotOwned");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotOwned(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in updateAttributeValues ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAV_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// 6.6
std::auto_ptr< RTI::MessageRetractionHandle >
GERTICO::RTIambServices::sendInteraction (
  RTI::InteractionClassHandle  const & theInteraction,
  RTI::ParameterHandleValueMap const & theParameterValues,
  RTI::UserSuppliedTag const & theUserSuppliedTag,
  RTI::LogicalTime const & theTime)
throw (
  RTI::InteractionClassNotPublished,
  RTI::InteractionClassNotDefined,
  RTI::InteractionParameterNotDefined,
  RTI::InvalidLogicalTime,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());
  GeRtiFactory::GeRtiHandle classHandle;
  GeRtiFactory::HandleValues handleValues;
  GeRtiFactory::ERHandle erHandle;
  GeRtiFactory::UserSuppliedTag tag;
  std::wstring ws;

  GERTICO::Mapper1516::mapInteractionClassHandle(classHandle, theInteraction);
  GERTICO::Mapper1516::mapParameterHandleValueMap(handleValues, theParameterValues);
  GERTICO::Mapper1516::mapUserSuppliedTag(tag, theUserSuppliedTag);
  GERTICO::Mapper1516::mapLogicalTime(*myLogicalTimeFactory, geRtiFedTime, theTime);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sI_s0)
                            {
                              char timeBuff[512];
                              unsigned long ul;

                              ul = classHandle;
                              geRtiFedTime->getPrintableString(timeBuff);
                              sprintf(galMsg,"interaction=%lu,time=%s", ul, timeBuff);
                              E1mEnd(sI_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sI_s0)
                            {
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, tag);
                              E1mEnd(sI_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sI_s0)
                            {
                              unsigned int indItem;
                              unsigned long lenItems;
                              lenItems = handleValues.length();
                              for (indItem = 0; indItem < lenItems; indItem++)
                              {
                                GERTICO::Mapper::printAttributeHandleValue("parameterValue=", galMsg, handleValues[indItem]);
                                E1mEnd(sI_s0,galMsg);
                              }
                            }
                           #endif   // inserted by Gal converter

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    erHandle = sender->sendInteraction(classHandle, handleValues, *geRtiFedTime, tag);
    break;
  }
  catch(GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::InteractionClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"InteractionClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionClassNotPublished(ws.c_str());
  }
  catch(GeRtiFactory::InteractionParameterNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"InteractionParameterNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionParameterNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::InvalidFederationTime &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"InvalidLogicalTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidLogicalTime(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in sendInteraction ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sI_s0)
                            {
                              unsigned long ul;
                              unsigned long ul1;

                              ul = erHandle.theSerialNumber;
                              ul1 = erHandle.sendingFederate;
                              sprintf(galMsg,"serialNumber=%lu,sendingFederate=%lu", ul, ul1);
                              E1mEnd(sI_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::MessageRetractionHandle *messageRetractionHandlePtr = new RTI::MessageRetractionHandle();
  GERTICO::Mapper1516::mapMessageRetractionHandle(*messageRetractionHandlePtr, erHandle);
  std::auto_ptr< RTI::MessageRetractionHandle > ret(messageRetractionHandlePtr);
  return ret;
}

void GERTICO::RTIambServices::sendInteraction (
  RTI::InteractionClassHandle  const & theInteraction,
  RTI::ParameterHandleValueMap const & theParameterValues,
  RTI::UserSuppliedTag const & theUserSuppliedTag)
throw (
  RTI::InteractionClassNotPublished,
  RTI::InteractionClassNotDefined,
  RTI::InteractionParameterNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle classHandle;
  GeRtiFactory::HandleValues handleValues;
  GeRtiFactory::UserSuppliedTag tag;
  std::wstring ws;

  GERTICO::Mapper1516::mapInteractionClassHandle(classHandle, theInteraction);
  GERTICO::Mapper1516::mapParameterHandleValueMap(handleValues, theParameterValues);
  GERTICO::Mapper1516::mapUserSuppliedTag(tag, theUserSuppliedTag);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sI_s1)
                            {
                              unsigned long ul;

                              ul = classHandle;
                              sprintf(galMsg,"interaction=%lu",ul);
                              E1mEnd(sI_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sI_s1)
                            {
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, tag);
                              E1mEnd(sI_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sI_s1)
                            {
                              unsigned int indItem;
                              unsigned long lenItems;
                              lenItems = handleValues.length();
                              for (indItem = 0; indItem < lenItems; indItem++)
                              {
                                GERTICO::Mapper::printAttributeHandleValue("parameterValue=", galMsg, handleValues[indItem]);
                                E1mEnd(sI_s1,galMsg);
                              }
                            }
                           #endif   // inserted by Gal converter

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->sendInteraction(classHandle, handleValues, tag);
    break;
  }
  catch(GeRtiFactory::InteractionClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"InteractionClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionClassNotPublished(ws.c_str());
  }
  catch(GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::InteractionParameterNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"InteractionParameterNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionParameterNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in sendInteraction ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sI_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// 6.8
std::auto_ptr< RTI::MessageRetractionHandle >
GERTICO::RTIambServices::deleteObjectInstance (
  RTI::ObjectInstanceHandle const & theObject,
  RTI::UserSuppliedTag const & theUserSuppliedTag,
  RTI::LogicalTime  const & theTime)
throw (
  RTI::DeletePrivilegeNotHeld,
  RTI::ObjectInstanceNotKnown,
  RTI::InvalidLogicalTime,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());
  GeRtiFactory::GeRtiHandle objectHandle;
  GeRtiFactory::ERHandle erHandle;
  GeRtiFactory::UserSuppliedTag tag;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectHandle, theObject);
  GERTICO::Mapper1516::mapUserSuppliedTag(tag, theUserSuppliedTag);
  GERTICO::Mapper1516::mapLogicalTime(*myLogicalTimeFactory, geRtiFedTime, theTime);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(dOI_s0)
                            {
                              char timeBuff[512];
                              unsigned long ul;

                              ul = objectHandle;
                              geRtiFedTime->getPrintableString(timeBuff);
                              sprintf(galMsg,"object=%lu,time=%s", ul, timeBuff);
                              E1mEnd(dOI_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(dOI_s0)
                            {
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, tag);
                              E1mEnd(dOI_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    erHandle = sender->deleteObjectInstance(objectHandle, *geRtiFedTime, tag);
    break;
  }
  catch(GeRtiFactory::DeletePrivilegeNotHeld &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ta,"DeletePrivilegeNotHeld");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::DeletePrivilegeNotHeld(ws.c_str());
  }
  catch(GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNotKnown(ws.c_str());
  }
  catch(GeRtiFactory::InvalidFederationTime &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ta,"InvalidLogicalTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidLogicalTime(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in deleteObjectInstance ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(dOI_s0)
                            {
                              unsigned long ul;
                              unsigned long ul1;

                              ul = erHandle.theSerialNumber;
                              ul1 = erHandle.sendingFederate;
                              sprintf(galMsg,"serialNumber=%lu,sendingFederate=%lu", ul, ul1);
                              E1mEnd(dOI_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::MessageRetractionHandle *messageRetractionHandlePtr = new RTI::MessageRetractionHandle();
  GERTICO::Mapper1516::mapMessageRetractionHandle(*messageRetractionHandlePtr, erHandle);
  std::auto_ptr< RTI::MessageRetractionHandle > ret(messageRetractionHandlePtr);
  return ret;
}

void GERTICO::RTIambServices::deleteObjectInstance (
  RTI::ObjectInstanceHandle const & theObject,
  RTI::UserSuppliedTag const & theUserSuppliedTag)
throw (
  RTI::DeletePrivilegeNotHeld,
  RTI::ObjectInstanceNotKnown,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle objectHandle;
  GeRtiFactory::UserSuppliedTag tag;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectHandle, theObject);
  GERTICO::Mapper1516::mapUserSuppliedTag(tag, theUserSuppliedTag);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(dOI_s1)
                            {
                              unsigned long ul;

                              ul = objectHandle;
                              sprintf(galMsg,"object=%lu",ul);
                              E1mEnd(dOI_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(dOI_s1)
                            {
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, tag);
                              E1mEnd(dOI_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->deleteObjectInstance(objectHandle, tag);
    break;
  }
  catch(GeRtiFactory::DeletePrivilegeNotHeld &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ta,"DeletePrivilegeNotHeld");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::DeletePrivilegeNotHeld(ws.c_str());
  }
  catch(GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNotKnown(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in deleteObjectInstance ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dOI_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E0(dOI_ts);   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// 6.10
void GERTICO::RTIambServices::localDeleteObjectInstance (
  RTI::ObjectInstanceHandle const & theObject)
throw (
  RTI::ObjectInstanceNotKnown,
  RTI::FederateOwnsAttributes,
  RTI::OwnershipAcquisitionPending,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle objectHandle;
  int maxExceptions=0;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectHandle, theObject);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(lDOI_s0)
                            {
                              unsigned long ul;

                              ul = objectHandle;
                              sprintf(galMsg,"object=%lu",ul);
                              E1mEnd(lDOI_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->localDeleteObjectInstance(objectHandle);
    break;
  }
  catch(GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(lDOI_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNotKnown(ws.c_str());
  }
  catch(GeRtiFactory::FederateOwnsAttributes &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(lDOI_ta,"FederateOwnsAttributes");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateOwnsAttributes(ws.c_str());
  }
  catch(GeRtiFactory::OwnershipAcquisitionPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(lDOI_ta,"OwnershipAcquisitionPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::OwnershipAcquisitionPending(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(lDOI_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(lDOI_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(lDOI_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(lDOI_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in localDeleteObjectInstance ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(lDOI_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(lDOI_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// 6.11
void GERTICO::RTIambServices::changeAttributeTransportationType (
  RTI::ObjectInstanceHandle const & theObject,
  RTI::AttributeHandleSet const & theAttributes,
  RTI::TransportationType const & theType)
throw (
  RTI::ObjectInstanceNotKnown,
  RTI::AttributeNotDefined,
  RTI::AttributeNotOwned,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle objectHandle;
  GeRtiFactory::GeRtiHandle transportationType;
  GeRtiFactory::Handles handles;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandleSet(handles, theAttributes);
  GERTICO::Mapper1516::mapTransportationType(transportationType, theType);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cATT_s0)
                            {
                              unsigned long ul;
                              unsigned long ul1;

                              ul = objectHandle;
                              ul1 = transportationType;
                              sprintf(galMsg,"object=%lu,type=%lu", ul, ul1);
                              E1mEnd(cATT_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cATT_s0)
                            {
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, handles);
                              E1mEnd(cATT_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->changeAttributeTransportationType(objectHandle, handles, transportationType);
    break;
  }
  catch(GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cATT_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNotKnown(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cATT_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotOwned &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cATT_ta,"AttributeNotOwned");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotOwned(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cATT_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cATT_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cATT_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cATT_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in changeAttributeTransportationType ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cATT_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cATT_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// 6.12
void GERTICO::RTIambServices::changeInteractionTransportationType (
  RTI::InteractionClassHandle const & theClass,
  RTI::TransportationType const & theType)
throw (
  RTI::InteractionClassNotDefined,
  RTI::InteractionClassNotPublished,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle classHandle;
  GeRtiFactory::GeRtiHandle transportationType;
  int maxExceptions=0;
  std::wstring ws;

  GERTICO::Mapper1516::mapInteractionClassHandle(classHandle, theClass);
  GERTICO::Mapper1516::mapTransportationType(transportationType, theType);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cITT_s0)
                            {
                              unsigned long ul;
                              unsigned long ul1;

                              ul = classHandle;
                              ul1 = transportationType;
                              sprintf(galMsg,"class=%lu,type=", ul);
                              E1mEnd(cITT_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->changeInteractionTransportationType(classHandle, transportationType);
    break;
  }
  catch(GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cITT_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::InteractionClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cITT_ta,"InteractionClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionClassNotPublished(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cITT_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cITT_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cITT_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cITT_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in changeInteractionTransportationType ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cITT_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cITT_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// 6.15
void GERTICO::RTIambServices::requestAttributeValueUpdate (
  RTI::ObjectInstanceHandle const & theObject,
  RTI::AttributeHandleSet const & theAttributes,
  RTI::UserSuppliedTag const & theUserSuppliedTag)
throw (
  RTI::ObjectInstanceNotKnown,
  RTI::AttributeNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle objectHandle;
  GeRtiFactory::UserSuppliedTag tag;
  GeRtiFactory::Handles handles;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandleSet(handles, theAttributes);
  GERTICO::Mapper1516::mapUserSuppliedTag(tag, theUserSuppliedTag);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rOAVU_s0)
                            {
                              unsigned long ul;

                              ul = objectHandle;
                              sprintf(galMsg,"object=%lu", ul);
                              E1mEnd(rOAVU_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rOAVU_s0)
                            {
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, tag);
                              E1mEnd(rOAVU_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rOAVU_s0)
                            {
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, handles);
                              E1mEnd(rOAVU_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->requestObjectAttributeValueUpdate(objectHandle, handles, tag);
    break;
  }
  catch(GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOAVU_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNotKnown(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOAVU_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOAVU_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOAVU_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOAVU_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOAVU_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in requestObjectAttributeValueUpdate ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOAVU_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOAVU_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

void GERTICO::RTIambServices::requestAttributeValueUpdate (
  RTI::ObjectClassHandle const & theClass,
  RTI::AttributeHandleSet const & theAttributes,
  RTI::UserSuppliedTag const & theUserSuppliedTag)
throw (
  RTI::ObjectClassNotDefined,
  RTI::AttributeNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle classHandle;
  GeRtiFactory::UserSuppliedTag tag;
  GeRtiFactory::Handles handles;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectClassHandle(classHandle, theClass);
  GERTICO::Mapper1516::mapAttributeHandleSet(handles, theAttributes);
  GERTICO::Mapper1516::mapUserSuppliedTag(tag, theUserSuppliedTag);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rCAVU_s0)
                            {
                              unsigned long ul;

                              ul = classHandle;
                              sprintf(galMsg,"class=%lu", ul);
                              E1mEnd(rCAVU_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rCAVU_s0)
                            {
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, handles);
                              E1mEnd(rCAVU_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rCAVU_s0)
                            {
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, tag);
                              E1mEnd(rCAVU_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->requestClassAttributeValueUpdate(classHandle, handles, tag);
    break;
  }
  catch(GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVU_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVU_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVU_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVU_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVU_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVU_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in requestClassAttributeValueUpdate ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVU_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVU_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

///////////////////////////////////
// Ownership Management Services //
///////////////////////////////////

// 7.2
void GERTICO::RTIambServices::unconditionalAttributeOwnershipDivestiture (
  RTI::ObjectInstanceHandle const & theObject,
  RTI::AttributeHandleSet const & theAttributes)
throw (
  RTI::ObjectInstanceNotKnown,
  RTI::AttributeNotDefined,
  RTI::AttributeNotOwned,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle objectHandle;
  GeRtiFactory::Handles handles;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandleSet(handles, theAttributes);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uAOD_s0)
                            {
                              unsigned long ul;

                              ul = objectHandle;
                              sprintf(galMsg,"object=%lu", ul);
                              E1mEnd(uAOD_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uAOD_s0)
                            {
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, handles);
                              E1mEnd(uAOD_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->unconditionalAttributeOwnershipDivestiture(objectHandle, handles);
    break;
  }
  catch(GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAOD_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNotKnown(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAOD_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotOwned &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAOD_ta,"AttributeNotOwned");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotOwned(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAOD_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAOD_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAOD_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAOD_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in unconditionalAttributeOwnershipDivestiture ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAOD_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uAOD_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// 7.3
void GERTICO::RTIambServices::negotiatedAttributeOwnershipDivestiture (
  RTI::ObjectInstanceHandle const & theObject,
  RTI::AttributeHandleSet const & theAttributes,
  RTI::UserSuppliedTag const & theUserSuppliedTag)
throw (
  RTI::ObjectInstanceNotKnown,
  RTI::AttributeNotDefined,
  RTI::AttributeNotOwned,
  RTI::AttributeAlreadyBeingDivested,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle objectHandle;
  GeRtiFactory::Handles handles;
  GeRtiFactory::UserSuppliedTag tag;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandleSet(handles, theAttributes);
  GERTICO::Mapper1516::mapUserSuppliedTag(tag, theUserSuppliedTag);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(nAOD_s0)
                            {
                              unsigned long ul;

                              ul = objectHandle;
                              sprintf(galMsg,"object=%lu",ul);
                              E1mEnd(nAOD_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(nAOD_s0)
                            {
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, tag);
                              E1mEnd(nAOD_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(nAOD_s0)
                            {
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, handles);
                              E1mEnd(nAOD_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->negotiatedAttributeOwnershipDivestiture(objectHandle, handles, tag);
    break;
  }
  catch(GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nAOD_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNotKnown(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nAOD_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotOwned &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nAOD_ta,"AttributeNotOwned");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotOwned(ws.c_str());
  }
  catch(GeRtiFactory::AttributeAlreadyBeingDivested &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nAOD_ta,"AttributeAlreadyBeingDivested");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeAlreadyBeingDivested(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nAOD_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nAOD_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nAOD_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nAOD_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in negotiatedAttributeOwnershipDivestiture ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nAOD_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nAOD_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// 7.7
void GERTICO::RTIambServices::attributeOwnershipAcquisition (
  RTI::ObjectInstanceHandle const & theObject,
  RTI::AttributeHandleSet const & desiredAttributes,
  RTI::UserSuppliedTag const & theUserSuppliedTag)
throw (
  RTI::ObjectInstanceNotKnown,
  RTI::ObjectClassNotPublished,
  RTI::AttributeNotDefined,
  RTI::AttributeNotPublished,
  RTI::FederateOwnsAttributes,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle objectHandle;
  GeRtiFactory::Handles handles;
  GeRtiFactory::UserSuppliedTag tag;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandleSet(handles, desiredAttributes);
  GERTICO::Mapper1516::mapUserSuppliedTag(tag, theUserSuppliedTag);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aOA_s0)
                            {
                              unsigned long ul;

                              ul = objectHandle;
                              sprintf(galMsg,"object=%lu", ul);
                              E1mEnd(aOA_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aOA_s0)
                            {
                              GERTICO::Mapper::printGeRtiFactoryHandles("desiredAttributes=", galMsg, handles);
                              E1mEnd(aOA_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aOA_s0)
                            {
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, tag);
                              E1mEnd(aOA_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->attributeOwnershipAcquisition(objectHandle, handles, tag);
    break;
  }
  catch(GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOA_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNotKnown(ws.c_str());
  }
  catch(GeRtiFactory::ObjectClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOA_ta,"ObjectClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassNotPublished(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOA_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOA_ta,"AttributeNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotPublished(ws.c_str());
  }
  catch(GeRtiFactory::FederateOwnsAttributes &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOA_ta,"FederateOwnsAttributes");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateOwnsAttributes(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOA_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOA_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOA_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOA_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in attributeOwnershipAcquisition ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOA_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOA_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// 7.8
void GERTICO::RTIambServices::attributeOwnershipAcquisitionIfAvailable (
  RTI::ObjectInstanceHandle const & theObject,
  RTI::AttributeHandleSet const & desiredAttributes)
throw (
  RTI::ObjectInstanceNotKnown,
  RTI::ObjectClassNotPublished,
  RTI::AttributeNotDefined,
  RTI::AttributeNotPublished,
  RTI::FederateOwnsAttributes,
  RTI::AttributeAlreadyBeingAcquired,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle objectHandle;
  GeRtiFactory::Handles handles;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandleSet(handles, desiredAttributes);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aOAIA_s0)
                            {
                              unsigned long ul;

                              ul = objectHandle;
                              sprintf(galMsg,"object=%lu", ul);
                              E1mEnd(aOAIA_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aOAIA_s0)
                            {
                              GERTICO::Mapper::printGeRtiFactoryHandles("desiredAttributes=", galMsg, handles);
                              E1mEnd(aOAIA_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->attributeOwnershipAcquisitionIfAvailable(objectHandle, handles);
    break;
  }
  catch(GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOAIA_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNotKnown(ws.c_str());
  }
  catch(GeRtiFactory::ObjectClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOAIA_ta,"ObjectClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassNotPublished(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOAIA_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOAIA_ta,"AttributeNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotPublished(ws.c_str());
  }
  catch(GeRtiFactory::FederateOwnsAttributes &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOAIA_ta,"FederateOwnsAttributes");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateOwnsAttributes(ws.c_str());
  }
  catch(GeRtiFactory::AttributeAlreadyBeingAcquired &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOAIA_ta,"AttributeAlreadyBeingAcquired");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeAlreadyBeingAcquired(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOAIA_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOAIA_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOAIA_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOAIA_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in attributeOwnershipAcquisitionIfAvailable ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOAIA_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOAIA_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// XXX 7.12
std::auto_ptr< RTI::AttributeHandleSet >
GERTICO::RTIambServices::attributeOwnershipDivestitureIfWanted(
  RTI::ObjectInstanceHandle const & theObject,
  RTI::AttributeHandleSet const & theAttributes)
throw (
  RTI::ObjectInstanceNotKnown,
  RTI::AttributeNotDefined,
  RTI::AttributeNotOwned,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  std::auto_ptr<RTI::AttributeHandleSet> ret(new RTI::AttributeHandleSet());

  GeRtiFactory::GeRtiHandle objectHandle;
  GeRtiFactory::Handles attributes;
  GeRtiFactory::Handles divestedAttributes;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandleSet(attributes, theAttributes);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aOAIA_s0)
                            {
                              unsigned long ul;

                              ul = objectHandle;
                              sprintf(galMsg,"object=%lu", ul);
                              E1mEnd(aOAIA_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aOAIA_s0)
                            {
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, attributes);
                              E1mEnd(aOAIA_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  try
  {
    sender->attributeOwnershipDivestitureIfWanted(objectHandle, attributes, divestedAttributes);
    GERTICO::Mapper1516::mapAttributeHandleSet(*ret, divestedAttributes);
  }
  catch(GeRtiFactory::ObjectNotKnown &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNotKnown(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotOwned &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotOwned(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in attributeOwnershipDivestitureIfWanted ");
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
    throw RTI::RTIinternalError(L"unknown Exception");
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aOAIA_s0)
                            {
                              GERTICO::Mapper::printGeRtiFactoryHandles("divestedAttributes=", galMsg, divestedAttributes);
                              E1mEnd(aOAIA_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  return ret;
}

// 7.11
void
GERTICO::RTIambServices::confirmDivestiture (
  RTI::ObjectInstanceHandle const & theObject,
  RTI::AttributeHandleSet const & confirmedAttributes,
  RTI::UserSuppliedTag const & theUserSuppliedTag)
throw (
  RTI::ObjectInstanceNotKnown,
  RTI::AttributeNotDefined,
  RTI::AttributeNotOwned,
  RTI::AttributeDivestitureWasNotRequested,
  RTI::NoAcquisitionPending,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle objectHandle;
  GeRtiFactory::Handles handles;
  GeRtiFactory::UserSuppliedTag tag;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandleSet(handles, confirmedAttributes);
  GERTICO::Mapper1516::mapUserSuppliedTag(tag, theUserSuppliedTag);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aORR_s0)
                            {
                              unsigned long ul;

                              ul = objectHandle;
                              sprintf(galMsg,"object=%lu", ul);
                              E1mEnd(aORR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aORR_s0)
                            {
                              GERTICO::Mapper::printGeRtiFactoryHandles("confirmedAttributes=", galMsg, handles);
                              E1mEnd(aORR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aORR_s0)
                            {
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, tag);
                              E1mEnd(aORR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->confirmDivestiture(objectHandle, handles, tag);
    break;
  }
  catch(GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aORR_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNotKnown(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aORR_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotOwned &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aORR_ta,"AttributeNotOwned");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotOwned(ws.c_str());
  }
  catch(GeRtiFactory::FederateWasNotAskedToReleaseAttribute &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aORR_ta,"AttributeDivestitureWasNotRequested");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeDivestitureWasNotRequested(ws.c_str());
  }
  catch(GeRtiFactory::NoAcquisitionPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aORR_ta,"NoAcquisitionPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::NoAcquisitionPending(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aORR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aORR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aORR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aORR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in confirmDivestiture ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aORR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aORR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aORR_s0)
                            {
                              sprintf(galMsg,"ret=");
//                              sprintf(galMsg,"%s","ret");
//                              GERTICO::ut::printAttributeHandleSet(galMsg,*ret);
                              E1mEnd(aORR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
}

// 7.12
void GERTICO::RTIambServices::cancelNegotiatedAttributeOwnershipDivestiture (
  RTI::ObjectInstanceHandle const & theObject,
  RTI::AttributeHandleSet const & theAttributes)
throw (
  RTI::ObjectInstanceNotKnown,
  RTI::AttributeNotDefined,
  RTI::AttributeNotOwned,
  RTI::AttributeDivestitureWasNotRequested,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle objectHandle;
  GeRtiFactory::Handles handles;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandleSet(handles, theAttributes);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cNAOD_s0)
                            {
                              unsigned long ul;

                              ul = objectHandle;
                              sprintf(galMsg,"object=%lu,tag=", ul);
                              E1mEnd(cNAOD_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cNAOD_s0)
                            {
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, handles);
                              E1mEnd(cNAOD_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->cancelNegotiatedAttributeOwnershipDivestiture(objectHandle, handles);
    break;
  }
  catch(GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cNAOD_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNotKnown(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cNAOD_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotOwned &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cNAOD_ta,"AttributeNotOwned");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotOwned(ws.c_str());
  }
  catch(GeRtiFactory::AttributeDivestitureWasNotRequested &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cNAOD_ta,"AttributeDivestitureWasNotRequested");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeDivestitureWasNotRequested(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cNAOD_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cNAOD_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cNAOD_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cNAOD_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in cancelNegotiatedAttributeOwnershipDivestiture ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cNAOD_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cNAOD_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// 7.13
void GERTICO::RTIambServices::cancelAttributeOwnershipAcquisition (
  RTI::ObjectInstanceHandle const & theObject,
  RTI::AttributeHandleSet const & theAttributes)
throw (
  RTI::ObjectInstanceNotKnown,
  RTI::AttributeNotDefined,
  RTI::AttributeAlreadyOwned,
  RTI::AttributeAcquisitionWasNotRequested,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle objectHandle;
  GeRtiFactory::Handles handles;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandleSet(handles, theAttributes);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cAOA_s0)
                            {
                              unsigned long ul;

                              ul = objectHandle;
                              sprintf(galMsg,"object=%lu,tag=", ul);
                              E1mEnd(cAOA_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cAOA_s0)
                            {
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, handles);
                              E1mEnd(cAOA_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  int maxExceptions=0;
  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->cancelAttributeOwnershipAcquisition(objectHandle, handles);
    break;
  }
  catch(GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOA_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNotKnown(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOA_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::AttributeAlreadyOwned &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOA_ta,"AttributeAlreadyOwned");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeAlreadyOwned(ws.c_str());
  }
  catch(GeRtiFactory::AttributeAcquisitionWasNotRequested &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOA_ta,"AttributeAcquisitionWasNotRequested");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeAcquisitionWasNotRequested(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOA_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOA_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOA_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOA_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in cancelAttributeOwnershipAcquisition ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOA_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOA_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// 7.15
void GERTICO::RTIambServices::queryAttributeOwnership (
  RTI::ObjectInstanceHandle const & theObject,
  RTI::AttributeHandle const & theAttribute)
throw (
  RTI::ObjectInstanceNotKnown,
  RTI::AttributeNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle objectHandle;
  GeRtiFactory::GeRtiHandle attributeHandle;
  int maxExceptions=0;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandle(attributeHandle, theAttribute);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(qAO_s0)
                            {
                              unsigned long ul;
                              unsigned long ul1;

                              ul = objectHandle;
                              ul1 = attributeHandle;
                              sprintf(galMsg,"object=%lu,tag=,attribute=%lu", ul, ul1);
                              E1mEnd(qAO_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    sender->queryAttributeOwnership(objectHandle, attributeHandle);
    break;
  }
  catch(GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qAO_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNotKnown(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qAO_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qAO_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qAO_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qAO_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qAO_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in queryAttributeOwnership ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qAO_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qAO_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }
}

// 7.17
bool
GERTICO::RTIambServices::isAttributeOwnedByFederate (
  RTI::ObjectInstanceHandle const & theObject,
  RTI::AttributeHandle const & theAttribute)
throw (
  RTI::ObjectInstanceNotKnown,
  RTI::AttributeNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle objectHandle;
  GeRtiFactory::GeRtiHandle attributeHandle;
  bool ret = false;
  int maxExceptions=0;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandle(attributeHandle, theAttribute);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(iAOBF_s0)
                            {
                              unsigned long ul;
                              unsigned long ul1;

                              ul = objectHandle;
                              ul1 = attributeHandle;
                              sprintf(galMsg,"object=%lu,attribute=%lu", ul, ul1);
                              E1mEnd(iAOBF_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  for (maxExceptions = 0;;maxExceptions++)
  {
  try
  {
    if (sender->isAttributeOwnedByFederate(objectHandle, attributeHandle))
    {
      ret = true;
    }
    else
    {
      ret = false;
    }
    break;
  }
  catch(GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(iAOBF_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNotKnown(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(iAOBF_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(iAOBF_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(iAOBF_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(iAOBF_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(iAOBF_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < maxRetries)
        {
          ACE_OS::sleep (ACE_Time_Value(0,waitTime));
          continue;
        }
      }
    ACE_PRINT_EXCEPTION(sysex, "System Exception in isAttributeOwnedByFederate ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(iAOBF_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(iAOBF_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(iAOBF_s0)
                            {
                              if (ret)
                              {
                                sprintf(galMsg,"ret=true");
                              }
                              else
                              {
                                sprintf(galMsg,"ret=false");
                              }
                              E1mEnd(iAOBF_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

//////////////////////////////
// Time Management Services //
//////////////////////////////

// 8.2
void GERTICO::RTIambServices::enableTimeRegulation (
  RTI::LogicalTimeInterval const & theLookahead)
throw (
  RTI::TimeRegulationAlreadyEnabled,
  RTI::InvalidLookahead,
  RTI::InTimeAdvancingState,
  RTI::RequestForTimeRegulationPending,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> geRtiFedTimeLookahead(myLogicalTimeIntervalFactory->makeZero());
  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> zeroLookahead(myLogicalTimeIntervalFactory->makeZero());
  std::wstring ws = L"enableTimeRegulation";

  GERTICO::Mapper1516::mapLogicalTimeInterval(*myLogicalTimeIntervalFactory, geRtiFedTimeLookahead, theLookahead);
  if (*geRtiFedTimeLookahead < *zeroLookahead)
  {
    throw RTI::InvalidLookahead(ws.c_str());
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(eTR_s0)
                            {
                              char timeBuff[512];

                              geRtiFedTimeLookahead->getPrintableString(timeBuff);
                              sprintf(galMsg,"lookAhead=%s", timeBuff);
                              E1mEnd(eTR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    sender->enableTimeRegulation(*geRtiFedTimeLookahead);
  }
  catch(GeRtiFactory::TimeRegulationAlreadyEnabled &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTR_ta,"TimeRegulationAlreadyEnabled");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::TimeRegulationAlreadyEnabled(ws.c_str());
  }
  catch(GeRtiFactory::InvalidLookahead &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTR_ta,"InvalidLookahead");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidLookahead(ws.c_str());
  }
  catch(GeRtiFactory::EnableTimeRegulationPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTR_ta,"EnableTimeRegulationPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RequestForTimeRegulationPending(ws.c_str());
  }
  catch(GeRtiFactory::TimeAdvanceAlreadyInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTR_ta,"TimeAdvanceAlreadyInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InTimeAdvancingState(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in enableTimeRegulation ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 8.4
void GERTICO::RTIambServices::disableTimeRegulation ()
throw (
  RTI::TimeRegulationIsNotEnabled,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(dTR_s0);
                           #endif   // inserted by Gal converter
  std::wstring ws;

  try
  {
    sender->disableTimeRegulation();
  }
  catch(GeRtiFactory::TimeRegulationWasNotEnabled &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTR_ta,"TimeRegulationWasNotEnabled");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::TimeRegulationIsNotEnabled(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in disableTimeRegulation ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 8.5
void GERTICO::RTIambServices::enableTimeConstrained ()
throw (
  RTI::TimeConstrainedAlreadyEnabled,
  RTI::InTimeAdvancingState,
  RTI::RequestForTimeConstrainedPending,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(eTC_s0);
                           #endif   // inserted by Gal converter
  std::wstring ws;

  try
  {
    sender->enableTimeConstrained();
  }
  catch(GeRtiFactory::TimeConstrainedAlreadyEnabled &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTC_ta,"TimeConstrainedAlreadyEnabled");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::TimeConstrainedAlreadyEnabled(ws.c_str());
  }
  catch(GeRtiFactory::EnableTimeConstrainedPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTC_ta,"EnableTimeConstrainedPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RequestForTimeConstrainedPending(ws.c_str());
  }
  catch(GeRtiFactory::TimeAdvanceAlreadyInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTC_ta,"TimeAdvanceAlreadyInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InTimeAdvancingState(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTC_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTC_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in enableTimeConstrained ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eTC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 8.7
void GERTICO::RTIambServices::disableTimeConstrained ()
throw (
  RTI::TimeConstrainedIsNotEnabled,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(dTC_s0);
                           #endif   // inserted by Gal converter
  std::wstring ws;

  try
  {
    sender->disableTimeConstrained();
  }
  catch(GeRtiFactory::TimeConstrainedWasNotEnabled &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTC_ta,"TimeConstrainedWasNotEnabled");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::TimeConstrainedIsNotEnabled(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTC_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTC_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in disableTimeConstrained ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dTC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 8.8
void GERTICO::RTIambServices::timeAdvanceRequest (
 RTI::LogicalTime const & theTime)
throw (
  RTI::InvalidLogicalTime,
  RTI::LogicalTimeAlreadyPassed,
  RTI::InTimeAdvancingState,
  RTI::RequestForTimeRegulationPending,
  RTI::RequestForTimeConstrainedPending,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());
  std::wstring ws;

  GERTICO::Mapper1516::mapLogicalTime(*myLogicalTimeFactory, geRtiFedTime, theTime);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(tAR_s0)
                            {
                              char timeBuff[512];

                              geRtiFedTime->getPrintableString(timeBuff);
                              sprintf(galMsg,"time=%s", timeBuff);
                              E1mEnd(tAR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    sender->timeAdvanceRequest(*geRtiFedTime);
  }
  catch(GeRtiFactory::InvalidFederationTime &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tAR_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidLogicalTime(ws.c_str());
  }
  catch(GeRtiFactory::FederationTimeAlreadyPassed &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tAR_ta,"FederationTimeAlreadyPassed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::LogicalTimeAlreadyPassed(ws.c_str());
  }
  catch(GeRtiFactory::TimeAdvanceAlreadyInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tAR_ta,"TimeAdvanceAlreadyInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InTimeAdvancingState(ws.c_str());
  }
  catch(GeRtiFactory::EnableTimeRegulationPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tAR_ta,"EnableTimeRegulationPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RequestForTimeRegulationPending(ws.c_str());
  }
  catch(GeRtiFactory::EnableTimeConstrainedPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tAR_ta,"EnableTimeConstrainedPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RequestForTimeConstrainedPending(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tAR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tAR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tAR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tAR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in timeAdvanceRequest ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tAR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tAR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 8.9
void GERTICO::RTIambServices::timeAdvanceRequestAvailable (
RTI::LogicalTime const & theTime)
  throw (
    RTI::InvalidLogicalTime,
    RTI::LogicalTimeAlreadyPassed,
    RTI::InTimeAdvancingState,
    RTI::RequestForTimeRegulationPending,
    RTI::RequestForTimeConstrainedPending,
    RTI::FederateNotExecutionMember,
    RTI::SaveInProgress,
    RTI::RestoreInProgress,
    RTI::RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());
  std::wstring ws;

  GERTICO::Mapper1516::mapLogicalTime(*myLogicalTimeFactory, geRtiFedTime, theTime);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(tARA_s0)
                            {
                              char timeBuff[512];

                              geRtiFedTime->getPrintableString(timeBuff);
                              sprintf(galMsg,"time=%s", timeBuff);
                              E1mEnd(tARA_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    sender->timeAdvanceRequestAvailable(*geRtiFedTime);
  }
  catch(GeRtiFactory::InvalidFederationTime &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tARA_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidLogicalTime(ws.c_str());
  }
  catch(GeRtiFactory::FederationTimeAlreadyPassed &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tARA_ta,"FederationTimeAlreadyPassed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::LogicalTimeAlreadyPassed(ws.c_str());
  }
  catch(GeRtiFactory::TimeAdvanceAlreadyInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tARA_ta,"TimeAdvanceAlreadyInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InTimeAdvancingState(ws.c_str());
  }
  catch(GeRtiFactory::EnableTimeRegulationPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tARA_ta,"EnableTimeRegulationPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RequestForTimeRegulationPending(ws.c_str());
  }
  catch(GeRtiFactory::EnableTimeConstrainedPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tARA_ta,"EnableTimeConstrainedPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RequestForTimeConstrainedPending(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tARA_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tARA_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tARA_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tARA_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in timeAdvanceRequestAvailable ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tARA_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(tARA_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 8.10
void GERTICO::RTIambServices::nextMessageRequest (
  RTI::LogicalTime const & theTime)
throw (
  RTI::InvalidLogicalTime,
  RTI::LogicalTimeAlreadyPassed,
  RTI::InTimeAdvancingState,
  RTI::RequestForTimeRegulationPending,
  RTI::RequestForTimeConstrainedPending,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());
  std::wstring ws;

  GERTICO::Mapper1516::mapLogicalTime(*myLogicalTimeFactory, geRtiFedTime, theTime);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(nER_s0)
                            {
                              char timeBuff[512];

                              geRtiFedTime->getPrintableString(timeBuff);
                              sprintf(galMsg,"time=%s", timeBuff);
                              E1mEnd(nER_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    sender->nextEventRequest(*geRtiFedTime);
  }
  catch(GeRtiFactory::InvalidFederationTime &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nER_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidLogicalTime(ws.c_str());
  }
  catch(GeRtiFactory::FederationTimeAlreadyPassed &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nER_ta,"FederationTimeAlreadyPassed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::LogicalTimeAlreadyPassed(ws.c_str());
  }
  catch(GeRtiFactory::TimeAdvanceAlreadyInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nER_ta,"TimeAdvanceAlreadyInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InTimeAdvancingState(ws.c_str());
  }
  catch(GeRtiFactory::EnableTimeRegulationPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nER_ta,"EnableTimeRegulationPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RequestForTimeRegulationPending(ws.c_str());
  }
  catch(GeRtiFactory::EnableTimeConstrainedPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nER_ta,"EnableTimeConstrainedPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RequestForTimeConstrainedPending(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nER_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nER_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nER_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nER_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in nextEventRequest ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nER_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nER_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 8.11
void GERTICO::RTIambServices::nextMessageRequestAvailable (
  RTI::LogicalTime const & theTime)
throw (
  RTI::InvalidLogicalTime,
  RTI::LogicalTimeAlreadyPassed,
  RTI::InTimeAdvancingState,
  RTI::RequestForTimeRegulationPending,
  RTI::RequestForTimeConstrainedPending,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());
  std::wstring ws;

  GERTICO::Mapper1516::mapLogicalTime(*myLogicalTimeFactory, geRtiFedTime, theTime);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(nERA_s0)
                            {
                              char timeBuff[512];

                              geRtiFedTime->getPrintableString(timeBuff);
                              sprintf(galMsg,"time=%s", timeBuff);
                              E1mEnd(nERA_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    sender->nextEventRequestAvailable(*geRtiFedTime);
  }
  catch(GeRtiFactory::InvalidFederationTime &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nERA_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidLogicalTime(ws.c_str());
  }
  catch(GeRtiFactory::FederationTimeAlreadyPassed &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nERA_ta,"FederationTimeAlreadyPassed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::LogicalTimeAlreadyPassed(ws.c_str());
  }
  catch(GeRtiFactory::TimeAdvanceAlreadyInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nERA_ta,"TimeAdvanceAlreadyInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InTimeAdvancingState(ws.c_str());
  }
  catch(GeRtiFactory::EnableTimeRegulationPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nERA_ta,"EnableTimeRegulationPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RequestForTimeRegulationPending(ws.c_str());
  }
  catch(GeRtiFactory::EnableTimeConstrainedPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nERA_ta,"EnableTimeConstrainedPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RequestForTimeConstrainedPending(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nERA_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nERA_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nERA_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nERA_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in nextEventRequestAvailable ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nERA_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nERA_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 8.12
void GERTICO::RTIambServices::flushQueueRequest (
  RTI::LogicalTime const & theTime)
throw (
  RTI::InvalidLogicalTime,
  RTI::LogicalTimeAlreadyPassed,
  RTI::InTimeAdvancingState,
  RTI::RequestForTimeRegulationPending,
  RTI::RequestForTimeConstrainedPending,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());
  std::wstring ws;

  GERTICO::Mapper1516::mapLogicalTime(*myLogicalTimeFactory, geRtiFedTime, theTime);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(fQR_s0)
                            {
                              char timeBuff[512];

                              geRtiFedTime->getPrintableString(timeBuff);
                              sprintf(galMsg,"time=%s", timeBuff);
                              E1mEnd(fQR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    sender->flushQueueRequest(*geRtiFedTime);
  }
  catch(GeRtiFactory::InvalidFederationTime &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fQR_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidLogicalTime(ws.c_str());
  }
  catch(GeRtiFactory::FederationTimeAlreadyPassed &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fQR_ta,"FederationTimeAlreadyPassed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::LogicalTimeAlreadyPassed(ws.c_str());
  }
  catch(GeRtiFactory::TimeAdvanceAlreadyInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fQR_ta,"TimeAdvanceAlreadyInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InTimeAdvancingState(ws.c_str());
  }
  catch(GeRtiFactory::EnableTimeRegulationPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fQR_ta,"EnableTimeRegulationPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RequestForTimeRegulationPending(ws.c_str());
  }
  catch(GeRtiFactory::EnableTimeConstrainedPending &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fQR_ta,"EnableTimeConstrainedPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RequestForTimeConstrainedPending(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fQR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fQR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fQR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fQR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in flushQueueRequest ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fQR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fQR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 8.14
void GERTICO::RTIambServices::enableAsynchronousDelivery()
  throw (
    RTI::AsynchronousDeliveryAlreadyEnabled,
    RTI::FederateNotExecutionMember,
    RTI::SaveInProgress,
    RTI::RestoreInProgress,
    RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E0(eAD_s0);   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  std::wstring ws;

  try
  {
    sender->enableAsynchronousDelivery();
  }
  catch(GeRtiFactory::AsynchronousDeliveryAlreadyEnabled &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eAD_ta,"AsynchronousDeliveryAlreadyEnabled");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AsynchronousDeliveryAlreadyEnabled(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eAD_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eAD_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eAD_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eAD_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in enableAsynchronousDelivery ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eAD_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eAD_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 8.15
void GERTICO::RTIambServices::disableAsynchronousDelivery()
  throw (
    RTI::AsynchronousDeliveryAlreadyDisabled,
    RTI::FederateNotExecutionMember,
    RTI::SaveInProgress,
    RTI::RestoreInProgress,
    RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(dAD_s0);
                           #endif   // inserted by Gal converter
  std::wstring ws;

  try
  {
    sender->disableAsynchronousDelivery();
  }
  catch(GeRtiFactory::AsynchronousDeliveryAlreadyDisabled &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dAD_ta,"AsynchronousDeliveryAlreadyDisabled");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AsynchronousDeliveryAlreadyDisabled(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dAD_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dAD_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dAD_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dAD_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in disableAsynchronousDelivery ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dAD_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dAD_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 8.16
std::auto_ptr< RTI::LogicalTime > GERTICO::RTIambServices::queryGALT ()
throw (
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(qLBTS_s0);
                           #endif   // inserted by Gal converter
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());
  std::wstring ws;

  try
  {
    sender->queryLBTS(*geRtiFedTime);
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qLBTS_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qLBTS_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qLBTS_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qLBTS_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in queryLBTS ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qLBTS_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qLBTS_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(qLBTS_s0)
                            {
                              char timeBuff[512];

                              geRtiFedTime->getPrintableString(timeBuff);
                              sprintf(galMsg,"time=%s", timeBuff);
                              E1mEnd(qLBTS_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  RTI::EncodedLogicalTime *encodedLogicalTime;
  GERTICO::Mapper1516::mapEncodedLogicalTime(&encodedLogicalTime, *geRtiFedTime);
  std::auto_ptr< RTI::LogicalTime > ret = myLogicalTimeFactory->logicalTimeFactory.decode(*encodedLogicalTime);
  return ret;
}

// 8.17
std::auto_ptr< RTI::LogicalTime > GERTICO::RTIambServices::queryLogicalTime ()
throw (
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(qFT_s0);
                           #endif   // inserted by Gal converter
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());
  std::wstring ws;

  try
  {
    sender->queryFederateTime(*geRtiFedTime);
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qFT_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qFT_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qFT_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qFT_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in queryFederateTime ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qFT_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qFT_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(qFT_s0)
                            {
                              char timeBuff[512];

                              geRtiFedTime->getPrintableString(timeBuff);
                              sprintf(galMsg,"time=%s", timeBuff);
                              E1mEnd(qFT_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  RTI::EncodedLogicalTime *encodedLogicalTime;
  GERTICO::Mapper1516::mapEncodedLogicalTime(&encodedLogicalTime, *geRtiFedTime);
  std::auto_ptr< RTI::LogicalTime > ret = myLogicalTimeFactory->logicalTimeFactory.decode(*encodedLogicalTime);
  return ret;
}

// 8.18
std::auto_ptr< RTI::LogicalTime > GERTICO::RTIambServices::queryLITS ()
throw (
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(qMNET_s0);
                           #endif   // inserted by Gal converter
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());
  std::wstring ws;

  try
  {
    sender->queryMinNextEventTime(*geRtiFedTime);
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qMNET_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qMNET_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qMNET_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qMNET_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in queryMinNextEventTime ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qMNET_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qMNET_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(qMNET_s0)
                            {
                              char timeBuff[512];

                              geRtiFedTime->getPrintableString(timeBuff);
                              sprintf(galMsg,"time=%s", timeBuff);
                              E1mEnd(qMNET_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  RTI::EncodedLogicalTime *encodedLogicalTime;
  GERTICO::Mapper1516::mapEncodedLogicalTime(&encodedLogicalTime, *geRtiFedTime);
  std::auto_ptr< RTI::LogicalTime > ret = myLogicalTimeFactory->logicalTimeFactory.decode(*encodedLogicalTime);
  return ret;
}

// 8.19
void GERTICO::RTIambServices::modifyLookahead (
  RTI::LogicalTimeInterval const & theLookahead)
throw (
RTI::TimeRegulationIsNotEnabled,
RTI::InvalidLookahead,
RTI::InTimeAdvancingState,
RTI::FederateNotExecutionMember,
RTI::SaveInProgress,
RTI::RestoreInProgress,
RTI::RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> geRtiFedTime(myLogicalTimeIntervalFactory->makeZero());
  std::wstring ws;

  GERTICO::Mapper1516::mapLogicalTimeInterval(*myLogicalTimeIntervalFactory, geRtiFedTime, theLookahead);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(mL_s0)
                            {
                              char timeBuff[512];

                              geRtiFedTime->getPrintableString(timeBuff);
                              sprintf(galMsg,"lookahead=%s", timeBuff);
                              E1mEnd(mL_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    sender->modifyLookahead(*geRtiFedTime);
  }
  catch(GeRtiFactory::InvalidLookahead &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(mL_ta,"InvalidLookahead");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidLookahead(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(mL_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(mL_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(mL_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(mL_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in modifyLookahead ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(mL_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(mL_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 8.20
std::auto_ptr< RTI::LogicalTimeInterval > GERTICO::RTIambServices::queryLookahead ()
throw (
RTI::TimeRegulationIsNotEnabled,
RTI::FederateNotExecutionMember,
RTI::SaveInProgress,
RTI::RestoreInProgress,
RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(qL_s0);
                           #endif   // inserted by Gal converter
  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> geRtiFedTime(myLogicalTimeIntervalFactory->makeZero());
  std::wstring ws;

  try
  {
    sender->queryLookahead(*geRtiFedTime);
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qL_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qL_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qL_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qL_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in queryLookahead ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qL_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(qL_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(qL_s0)
                            {
                              char timeBuff[512];

                              geRtiFedTime->getPrintableString(timeBuff);
                              sprintf(galMsg,"time=%s", timeBuff);
                              E1mEnd(qL_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  std::auto_ptr<RTI::LogicalTimeInterval> ret;
  ret = myLogicalTimeIntervalFactory->logicalTimeIntervalFactory.makeZero();
  GERTICO::Mapper1516::mapLogicalTimeInterval(*myLogicalTimeIntervalFactory, *ret, *geRtiFedTime);

  return ret;
}

// 8.21
void GERTICO::RTIambServices::retract (
  RTI::MessageRetractionHandle const & theHandle)
throw (
RTI::InvalidRetractionHandle,
RTI::TimeRegulationIsNotEnabled,
RTI::MessageCanNoLongerBeRetracted,
RTI::FederateNotExecutionMember,
RTI::SaveInProgress,
RTI::RestoreInProgress,
RTI::RTIinternalError)
{
  GeRtiFactory::ERHandle erHandle;
  std::wstring ws;

  GERTICO::Mapper1516::mapMessageRetractionHandle(erHandle, theHandle);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(r_s0)
                            {
                              unsigned long ul;

                              ul = erHandle.sendingFederate;
                              sprintf(galMsg,"sendingFederate=%lu", ul);
                              E1mEnd(r_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    sender->retract(erHandle);
  }
  catch(GeRtiFactory::InvalidRetractionHandle &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(r_ta,"InvalidRetractionHandle");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidRetractionHandle(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(r_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(r_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(r_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(r_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in retract ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(r_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(r_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 8.23
void GERTICO::RTIambServices::changeAttributeOrderType (
  RTI::ObjectInstanceHandle const & theObject,
  RTI::AttributeHandleSet const & theAttributes,
  RTI::OrderType const & theType)
throw (
  RTI::ObjectInstanceNotKnown,
  RTI::AttributeNotDefined,
  RTI::AttributeNotOwned,
  RTI::FederateNotExecutionMember,
  RTI::InvalidOrderType,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle objectHandle;
  GeRtiFactory::GeRtiHandle typeHandle;
  GeRtiFactory::Handles handles;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandleSet(handles, theAttributes);
  GERTICO::Mapper1516::mapOrderType(typeHandle, theType);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cAOT_s0)
                            {
                              unsigned long ul;
                              unsigned long ul1;

                              ul = objectHandle;
                              ul1 = typeHandle;
                              sprintf(galMsg,"object=%lu,type=%lu", ul, ul1);
                              E1mEnd(cAOT_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cAOT_s0)
                            {
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, handles);
                              E1mEnd(cAOT_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    sender->changeAttributeOrderType(objectHandle, handles, typeHandle);
  }
  catch(GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOT_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNotKnown(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOT_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotOwned &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOT_ta,"AttributeNotOwned");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotOwned(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOT_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOT_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOT_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOT_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in changeAttributeOrderType ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOT_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cAOT_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 8.24
void GERTICO::RTIambServices::changeInteractionOrderType (
  RTI::InteractionClassHandle const & theClass,
  RTI::OrderType const & theType)
throw (
  RTI::InteractionClassNotDefined,
  RTI::InteractionClassNotPublished,
  RTI::FederateNotExecutionMember,
  RTI::InvalidOrderType,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle classHandle;
  GeRtiFactory::GeRtiHandle typeHandle;
  std::wstring ws;

  GERTICO::Mapper1516::mapInteractionClassHandle(classHandle, theClass);
  GERTICO::Mapper1516::mapOrderType(typeHandle, theType);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cIOT_s0)
                            {
                              unsigned long ul;
                              unsigned long ul1;

                              ul = classHandle;
                              ul1 = typeHandle;
                              sprintf(galMsg,"class=%lu,type=%lu", ul, ul1);
                              E1mEnd(cIOT_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    sender->changeInteractionOrderType(classHandle, typeHandle);
  }
  catch(GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cIOT_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::InteractionClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cIOT_ta,"InteractionClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionClassNotPublished(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cIOT_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cIOT_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cIOT_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cIOT_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in changeInteractionOrderType ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cIOT_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cIOT_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

//////////////////////////////////
// Data Distribution Management //
//////////////////////////////////

// 9.2
RTI::RegionHandle
GERTICO::RTIambServices::createRegion (
  RTI::DimensionHandleSet const & theDimensions)
throw (
  RTI::InvalidDimensionHandle,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GERTICO::HandleSet dimensions;
  GERTICO::HandleSet::iterator itdimensions;
  GeRtiFactory::GeRtiHandle numberOfExtents;
  GeRtiFactory::GeRtiHandle regionHandle;
  GeRtiFactory::GeRtiHandle spaceHandle = 0;
  std::wstring ws;

  numberOfExtents = 1;

  GERTICO::Mapper1516::mapDimensionHandleSet(dimensions, theDimensions);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cR_s0)
                            {
                              GERTICO::Mapper::printHandleSet("dimensions=", galMsg, dimensions);
                              E1mEnd(cR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    GERTICO::RegionI *regionI;
    GERTICO::UpperLowerBounds *upperLowerBounds;
    regionHandle = sender->createRegion(spaceHandle, numberOfExtents, dimensions);
    regionI = new GERTICO::RegionI(regionHandle);
    for (itdimensions = dimensions.begin(); itdimensions != dimensions.end(); itdimensions++)
    {
      upperLowerBounds = new GERTICO::UpperLowerBounds(0, 0);
      regionI->boundsMap[*itdimensions] = upperLowerBounds;
    }
    regionIMap[regionHandle] = regionI;
  }
  catch(GeRtiFactory::InvalidExtents &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cR_ta,"InvalidExtents");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidDimensionHandle(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in createRegion ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(cR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cR_s0)
                            {
                              unsigned long ul;

                              ul = regionHandle;
                              sprintf(galMsg, "ret=%lu", ul);
                              E1mEnd(cR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  RTI::RegionHandle ret;
  GERTICO::Mapper1516::mapRegionHandle(ret, regionHandle);
  return ret;
}

// 9.3
void GERTICO::RTIambServices::commitRegionModifications (
  RTI::RegionHandleSet const & theRegionHandleSet)
throw (
  RTI::InvalidRegion,
  RTI::RegionNotCreatedByThisFederate,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GERTICO::BoundsMap::iterator itBoundsMap;
  GERTICO::HandleSet handleSet;
  GERTICO::HandleSet::iterator itHandleSet;
  GERTICO::RegionI *regionI;
  GERTICO::RegionIMap::iterator itRegionIMap;
  GeRtiFactory::Extents myExtents;
  std::wstring ws;

  GERTICO::Mapper1516::mapRegionHandleSet(handleSet, theRegionHandleSet);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cR_s0)
                            {
                              GERTICO::Mapper::printHandleSet("regions=", galMsg, handleSet);
                              E1mEnd(cR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  GERTICO::UpperLowerBounds *upperLowerBounds;
  unsigned long ul;
  for (itRegionIMap = regionIMap.begin(); itRegionIMap != regionIMap.end(); itRegionIMap++)
  {
    ul = itRegionIMap->first;
    regionI = itRegionIMap->second;
    for (itBoundsMap = regionI->boundsMap.begin(); itBoundsMap != regionI->boundsMap.end(); itBoundsMap++)
    {
      ul = itBoundsMap->first;
      upperLowerBounds = itBoundsMap->second;
    }
  }

  for (itHandleSet = handleSet.begin(); itHandleSet != handleSet.end(); itHandleSet++)
  {
    itRegionIMap = regionIMap.find(*itHandleSet);
    if (itRegionIMap != regionIMap.end())
    {
      regionI = itRegionIMap->second;
      for (itBoundsMap = regionI->boundsMap.begin(); itBoundsMap != regionI->boundsMap.end(); itBoundsMap++)
      {
        try
        {
          sender->setRangeBounds(*itHandleSet, itBoundsMap->first, itBoundsMap->second->lower, itBoundsMap->second->upper);
        }
        catch(GeRtiFactory::RegionNotKnown &ex)
        {
          GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
          throw RTI::InvalidRegion(ws.c_str());
        }
        catch(GeRtiFactory::RegionDoesNotContainSpecifiedDimension &ex)
        {
          GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
          throw RTI::RegionDoesNotContainSpecifiedDimension(ws.c_str());
        }
        catch(GeRtiFactory::FederateNotExecutionMember &ex)
        {
          GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
          throw RTI::FederateNotExecutionMember(ws.c_str());
        }
        catch(GeRtiFactory::SaveInProgress &ex)
        {
          GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
          throw RTI::SaveInProgress(ws.c_str());
        }
        catch(GeRtiFactory::RestoreInProgress &ex)
        {
          GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
          throw RTI::RestoreInProgress(ws.c_str());
        }
        catch(GeRtiFactory::RTIinternalError &ex)
        {
          GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
          throw RTI::RTIinternalError(ws.c_str());
        }
        catch(CORBA::SystemException &sysex)
        {
          ACE_PRINT_EXCEPTION(sysex, "System Exception in setRangeBounds ");
          throw RTI::RTIinternalError(L"CORBA::SystemException");
        }
        catch(...)
        {
          throw RTI::RTIinternalError(L"unknown Exception");
        }
      }
    }
  }

  try
  {
    for (itHandleSet = handleSet.begin(); itHandleSet != handleSet.end(); itHandleSet++)
    {
      sender->notifyAboutRegionModification(*itHandleSet, myExtents);
    }
  }
  catch(GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nARM_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidRegion(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nARM_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nARM_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nARM_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nARM_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in notifyAboutRegionModification ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nARM_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(nARM_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 9.4
void GERTICO::RTIambServices::deleteRegion (
  RTI::RegionHandle theRegion)
throw (
  RTI::InvalidRegion,
  RTI::RegionNotCreatedByThisFederate,
  RTI::RegionInUseForUpdateOrSubscription,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle regionHandle;
  std::wstring ws;

  GERTICO::Mapper1516::mapRegionHandle(regionHandle, theRegion);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(dR_s0)
                            {
                              unsigned long ul;

                              ul = regionHandle;
                              sprintf(galMsg, "region=%lu", ul);
                              E1mEnd(dR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  try
  {
    sender->deleteRegion(regionHandle);
  }
  catch(GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dR_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidRegion(ws.c_str());
  }
  catch(GeRtiFactory::RegionNotCreatedByThisFederate &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dR_ta,"RegionNotCreatedByThisFederate");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RegionNotCreatedByThisFederate(ws.c_str());
  }
  catch(GeRtiFactory::RegionInUse &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dR_ta,"RegionInUse");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RegionInUseForUpdateOrSubscription(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in deleteRegion ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 9.5
RTI::ObjectInstanceHandle
GERTICO::RTIambServices::registerObjectInstanceWithRegions (
  RTI::ObjectClassHandle const & theClass,
  RTI::AttributeHandleSetRegionHandleSetPairVector const &
  theAttributeHandleSetRegionHandleSetPairVector)
throw (
  RTI::ObjectClassNotDefined,
  RTI::ObjectClassNotPublished,
  RTI::AttributeNotDefined,
  RTI::AttributeNotPublished,
  RTI::InvalidRegion,
  RTI::RegionNotCreatedByThisFederate,
  RTI::InvalidRegionContext,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GERTICO::HandleSetMap attRegHandles;
  GeRtiFactory::GeRtiHandle classHandle;
  GeRtiFactory::GeRtiHandle objectHandle;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectClassHandle(classHandle, theClass);
  GERTICO::Mapper1516::mapAttributeHandleSetRegionHandleSetPairVector(attRegHandles, theAttributeHandleSetRegionHandleSetPairVector);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rOIWR_s0)
                            {
                              unsigned long ul;

                              ul = classHandle;
                              sprintf(galMsg,"class=%lu,object=,numberOfHandles=u", ul);
                              E1mEnd(rOIWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rOIWR_s0)
                            {
                              GERTICO::Mapper::printHandleSetMap("attributeRegions=", galMsg, attRegHandles);
                              E1mEnd(rOIWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    objectHandle = sender->registerObjectInstanceWithRegion(classHandle, attRegHandles);
  }
  catch(GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::ObjectClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"ObjectClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassNotPublished(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"AttributeNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotPublished(ws.c_str());
  }
  catch(GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidRegion(ws.c_str());
  }
  catch(GeRtiFactory::InvalidRegionContext &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"InvalidRegionContext");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidRegionContext(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in registerObjectInstanceWithRegion ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rOIWR_s0)
                            {
                              unsigned long ul;

                              ul = objectHandle;
                              sprintf(galMsg,"ret=%lu", ul);
                              E1mEnd(rOIWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::ObjectInstanceHandle ret;
  GERTICO::Mapper1516::mapObjectInstanceHandle(ret, objectHandle);
  return ret;
}

RTI::ObjectInstanceHandle
GERTICO::RTIambServices::registerObjectInstanceWithRegions (
  RTI::ObjectClassHandle const & theClass,
  RTI::AttributeHandleSetRegionHandleSetPairVector const &
  theAttributeHandleSetRegionHandleSetPairVector,
  std::wstring const & theObjectInstanceName)
throw (
  RTI::ObjectClassNotDefined,
  RTI::ObjectClassNotPublished,
  RTI::AttributeNotDefined,
  RTI::AttributeNotPublished,
  RTI::InvalidRegion,
  RTI::RegionNotCreatedByThisFederate,
  RTI::InvalidRegionContext,
  RTI::ObjectInstanceNameNotReserved,
  RTI::ObjectInstanceNameInUse,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GERTICO::HandleSetMap attRegHandles;
  GeRtiFactory::GeRtiHandle classHandle;
  GeRtiFactory::GeRtiHandle objectHandle;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectClassHandle(classHandle, theClass);
  GERTICO::Mapper1516::mapAttributeHandleSetRegionHandleSetPairVector(attRegHandles, theAttributeHandleSetRegionHandleSetPairVector);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rOIWR_s1)
                            {
                              unsigned long ul;

                              ul = classHandle;
                              sprintf(galMsg,"class=%lu", ul);
                              E1mEnd(rOIWR_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rOIWR_s1)
                            {
                              GERTICO::Mapper::printHandleSetMap("attributeRegions=", galMsg, attRegHandles);
                              E1mEnd(rOIWR_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    objectHandle = sender->registerObjectInstanceWithRegion(classHandle, theObjectInstanceName, attRegHandles);
  }
  catch(GeRtiFactory::ObjectClassNotDefined &ex)
  {
                             #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::ObjectClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"ObjectClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassNotPublished(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"AttributeNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotPublished(ws.c_str());
  }
  catch(GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidRegion(ws.c_str());
  }
  catch(GeRtiFactory::InvalidRegionContext &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"InvalidRegionContext");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidRegionContext(ws.c_str());
  }
  catch(GeRtiFactory::ObjectAlreadyRegistered &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"InvalidRegionContext");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNameInUse(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in registerObjectInstanceWithRegion ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rOIWR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rOIWR_s1)
                            {
                              unsigned long ul;

                              ul = objectHandle;
                              sprintf(galMsg,"ret=%lu", ul);
                              E1mEnd(rOIWR_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::ObjectInstanceHandle ret;
  GERTICO::Mapper1516::mapObjectInstanceHandle(ret, objectHandle);
  return ret;
}

// 9.6
void GERTICO::RTIambServices::associateRegionsForUpdates (
  RTI::ObjectInstanceHandle const & theObject,
  RTI::AttributeHandleSetRegionHandleSetPairVector const &
  theAttributeHandleSetRegionHandleSetPairVector)
throw (
  RTI::ObjectInstanceNotKnown,
  RTI::AttributeNotDefined,
  RTI::InvalidRegion,
  RTI::RegionNotCreatedByThisFederate,
  RTI::InvalidRegionContext,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GERTICO::HandleSetMap attRegHandles;
  GeRtiFactory::GeRtiHandle objectHandle;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandleSetRegionHandleSetPairVector(attRegHandles, theAttributeHandleSetRegionHandleSetPairVector);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aRFU_s0)
                            {
                              unsigned long ul;

                              ul = objectHandle;
                              sprintf(galMsg, "object=%lu", ul);
                              E1mEnd(aRFU_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aRFU_s0)
                            {
                              GERTICO::Mapper::printHandleSetMap("attributeRegions=", galMsg, attRegHandles);
                              E1mEnd(aRFU_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    sender->associateRegionForUpdates(objectHandle, attRegHandles);
  }
  catch(GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aRFU_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNotKnown(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aRFU_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::InvalidRegionContext &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aRFU_ta,"InvalidRegionContext");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidRegionContext(ws.c_str());
  }
  catch(GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aRFU_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidRegion(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aRFU_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aRFU_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aRFU_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aRFU_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in associateRegionForUpdates ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aRFU_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aRFU_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 9.7
void GERTICO::RTIambServices::unassociateRegionsForUpdates (
  RTI::ObjectInstanceHandle const & theObject,
  RTI::AttributeHandleSetRegionHandleSetPairVector const &
     theAttributeHandleSetRegionHandleSetPairVector)
throw (
  RTI::ObjectInstanceNotKnown,
  RTI::AttributeNotDefined,
  RTI::InvalidRegion,
  RTI::RegionNotCreatedByThisFederate,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GERTICO::HandleSetMap attRegHandles;
  GeRtiFactory::GeRtiHandle objectHandle;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectHandle, theObject);
  GERTICO::Mapper1516::mapAttributeHandleSetRegionHandleSetPairVector(attRegHandles, theAttributeHandleSetRegionHandleSetPairVector);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uRFU_s0)
                            {
                              unsigned long ul;

                              ul = objectHandle;
                              sprintf(galMsg, "object=%lu", ul);
                              E1mEnd(uRFU_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uRFU_s0)
                            {
                              GERTICO::Mapper::printHandleSetMap("attributeRegions=", galMsg, attRegHandles);
                              E1mEnd(uRFU_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    sender->unassociateRegionsForUpdates(objectHandle, attRegHandles);
  }
  catch(GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uRFU_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNotKnown(ws.c_str());
  }
  catch(GeRtiFactory::InvalidRegionContext &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uRFU_ta,"InvalidRegionContext");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidRegion(ws.c_str());
  }
  catch(GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uRFU_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidRegion(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uRFU_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uRFU_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uRFU_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uRFU_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in unassociateRegionForUpdates ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uRFU_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uRFU_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 9.8
void GERTICO::RTIambServices::subscribeObjectClassAttributesWithRegions (
  RTI::ObjectClassHandle const & theClass,
  RTI::AttributeHandleSetRegionHandleSetPairVector const &
    theAttributeHandleSetRegionHandleSetPairVector,
  bool active)
throw (
  RTI::ObjectClassNotDefined,
  RTI::AttributeNotDefined,
  RTI::InvalidRegion,
  RTI::RegionNotCreatedByThisFederate,
  RTI::InvalidRegionContext,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GERTICO::HandleSetMap attRegHandles;
  GeRtiFactory::GeRtiHandle classHandle;
  GeRtiFactory::Handles handles;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectClassHandle(classHandle, theClass);
  GERTICO::Mapper1516::mapAttributeHandleSetRegionHandleSetPairVector(attRegHandles, theAttributeHandleSetRegionHandleSetPairVector);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sOCAWR_s0)
                            {
                              unsigned long ul;

                              ul = classHandle;
                              if (active)
                              {
                                sprintf(galMsg,"class=%lu, active=true", ul);
                              }
                              else
                              {
                                sprintf(galMsg,"class=%lu, active=false", ul);
                              }
                              E1mEnd(sOCAWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sOCAWR_s0)
                            {
                              GERTICO::Mapper::printHandleSetMap("attributeRegions=", galMsg, attRegHandles);
                              E1mEnd(sOCAWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    sender->subscribeObjectClassAttributesWithRegion(classHandle, attRegHandles, active);
  }
  catch(GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCAWR_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCAWR_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCAWR_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidRegion(ws.c_str());
  }
  catch(GeRtiFactory::InvalidRegionContext &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCAWR_ta,"InvalidRegionContext");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidRegionContext(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCAWR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCAWR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCAWR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCAWR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in subscribeObjectClassAttributesWithRegion ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCAWR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sOCAWR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 9.9
void GERTICO::RTIambServices::unsubscribeObjectClassAttributesWithRegions (
  RTI::ObjectClassHandle const & theClass,
  RTI::AttributeHandleSetRegionHandleSetPairVector const &
     theAttributeHandleSetRegionHandleSetPairVector)
throw (
  RTI::ObjectClassNotDefined,
  RTI::AttributeNotDefined,
  RTI::InvalidRegion,
  RTI::RegionNotCreatedByThisFederate,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GERTICO::HandleSetMap attRegHandles;
  GeRtiFactory::GeRtiHandle classHandle;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectClassHandle(classHandle, theClass);
  GERTICO::Mapper1516::mapAttributeHandleSetRegionHandleSetPairVector(attRegHandles, theAttributeHandleSetRegionHandleSetPairVector);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uOCWR_s0)
                            {
                              unsigned long ul;

                              ul = classHandle;
                              sprintf(galMsg, "class=%lu", ul);
                              E1mEnd(uOCWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uOCWR_s0)
                            {
                              GERTICO::Mapper::printHandleSetMap("attributeRegions=", galMsg, attRegHandles);
                              E1mEnd(uOCWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    sender->unsubscribeObjectClassWithRegions(classHandle, attRegHandles);
  }
  catch(GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOCWR_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOCWR_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOCWR_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidRegion(ws.c_str());
  }
  catch(GeRtiFactory::RegionNotCreatedByThisFederate &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOCWR_ta,"RegionNotCreatedByThisFederate");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RegionNotCreatedByThisFederate(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOCWR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }

  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOCWR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOCWR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOCWR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in unsubscribeObjectClassWithRegion ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOCWR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uOCWR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 9.10
void GERTICO::RTIambServices::subscribeInteractionClassWithRegions (
  RTI::InteractionClassHandle const & theClass,
  RTI::RegionHandleSet const & theRegionHandleSet,
  bool active)
throw (
  RTI::InteractionClassNotDefined,
  RTI::InvalidRegion,
  RTI::RegionNotCreatedByThisFederate,
  RTI::InvalidRegionContext,
  RTI::FederateServiceInvocationsAreBeingReportedViaMOM,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  unsigned long ul;
  GERTICO::HandleSet regions;
  GeRtiFactory::GeRtiHandle classHandle;
  std::wstring ws;

  GERTICO::Mapper1516::mapInteractionClassHandle(classHandle, theClass);
  GERTICO::Mapper1516::mapRegionHandleSet(regions, theRegionHandleSet);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sICWR_s0)
                            {
                              ul = classHandle;

                              if (active)
                              {
                                sprintf(galMsg,"class=%lu,active=true", ul);
                              }
                              else
                              {
                                sprintf(galMsg,"class=%lu,active=false", ul);
                              }
                              E1mEnd(sICWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sICWR_s0)
                            {
                              GERTICO::Mapper::printHandleSet("regions=", galMsg, regions);
                              E1mEnd(sICWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    sender->subscribeInteractionClassWithRegion(classHandle, regions, active);
  }
  catch(GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sICWR_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sICWR_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidRegion(ws.c_str());
  }
  catch(GeRtiFactory::InvalidRegionContext &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sICWR_ta,"InvalidRegionContext");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidRegionContext(ws.c_str());
  }
  catch(GeRtiFactory::FederateLoggingServiceCalls &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sICWR_ta,"FederateLoggingServiceCalls");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateServiceInvocationsAreBeingReportedViaMOM(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sICWR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sICWR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sICWR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sICWR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in subscribeInteractionClassWithRegion ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sICWR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sICWR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 9.11
void GERTICO::RTIambServices::unsubscribeInteractionClassWithRegions (
  RTI::InteractionClassHandle const & theClass,
  RTI::RegionHandleSet const & theRegionHandleSet)
throw (
  RTI::InteractionClassNotDefined,
  RTI::InvalidRegion,
  RTI::RegionNotCreatedByThisFederate,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GERTICO::HandleSet regions;
  GeRtiFactory::GeRtiHandle classHandle;
  std::wstring ws;

  GERTICO::Mapper1516::mapInteractionClassHandle(classHandle, theClass);
  GERTICO::Mapper1516::mapRegionHandleSet(regions, theRegionHandleSet);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uICWR_s0)
                            {
                              unsigned long ul;

                              ul = classHandle;
                              sprintf(galMsg,"class=%lu", ul);
                              E1mEnd(uICWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(uICWR_s0)
                            {
                              GERTICO::Mapper::printHandleSet("regions=", galMsg, regions);
                              E1mEnd(uICWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    sender->unsubscribeInteractionClassWithRegion(classHandle, regions);
  }
  catch(GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uICWR_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::InteractionClassNotSubscribed &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uICWR_ta,"InteractionClassNotSubscribed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionClassNotSubscribed(ws.c_str());
  }
  catch(GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uICWR_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidRegion(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uICWR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uICWR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uICWR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uICWR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in unsubscribeInteractionClassWithRegion ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uICWR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(uICWR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 9.12
std::auto_ptr< RTI::MessageRetractionHandle >
GERTICO::RTIambServices::sendInteractionWithRegions (
  RTI::InteractionClassHandle  const & theInteraction,
  RTI::ParameterHandleValueMap const & theParameterValues,
  RTI::RegionHandleSet const & theRegionHandleSet,
  RTI::UserSuppliedTag const & theUserSuppliedTag,
  RTI::LogicalTime const & theTime)
throw (
  RTI::InteractionClassNotDefined,
  RTI::InteractionClassNotPublished,
  RTI::InteractionParameterNotDefined,
  RTI::InvalidRegion,
  RTI::RegionNotCreatedByThisFederate,
  RTI::InvalidRegionContext,
  RTI::InvalidLogicalTime,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(myLogicalTimeFactory->makeZero());
  GERTICO::HandleSet regions;
  GeRtiFactory::GeRtiHandle classHandle;
  GeRtiFactory::HandleValues handleValues;
  GeRtiFactory::ERHandle erHandle;
  GeRtiFactory::UserSuppliedTag tag;
  std::wstring ws;

  GERTICO::Mapper1516::mapInteractionClassHandle(classHandle, theInteraction);
  GERTICO::Mapper1516::mapParameterHandleValueMap(handleValues, theParameterValues);
  GERTICO::Mapper1516::mapRegionHandleSet(regions, theRegionHandleSet);
  GERTICO::Mapper1516::mapUserSuppliedTag(tag, theUserSuppliedTag);
  GERTICO::Mapper1516::mapLogicalTime(*myLogicalTimeFactory, geRtiFedTime, theTime);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sIWR_s0)
                            {
                              char timeBuff[512];
                              unsigned long ul;

                              ul = classHandle;
                              geRtiFedTime->getPrintableString(timeBuff);
                              sprintf(galMsg,"interaction=%lu,time=%s", ul, timeBuff);
                              E1mEnd(sIWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sIWR_s0)
                            {
                              unsigned int indItem;
                              unsigned long lenItems;
                              lenItems = handleValues.length();
                              for (indItem = 0; indItem < lenItems; indItem++)
                              {
                                GERTICO::Mapper::printAttributeHandleValue("parameterValue=", galMsg, handleValues[indItem]);
                                E1mEnd(sIWR_s0,galMsg);
                              }
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sIWR_s0)
                            {
                              GERTICO::Mapper::printHandleSet("regions=", galMsg, regions);
                              E1mEnd(sIWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sIWR_s0)
                            {
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, tag);
                              E1mEnd(sIWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    erHandle = sender->sendInteractionWithRegion(classHandle, handleValues, *geRtiFedTime, tag, regions);
  }
  catch(GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::InteractionClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"InteractionClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionClassNotPublished(ws.c_str());
  }
  catch(GeRtiFactory::InteractionParameterNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"InteractionParameterNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionParameterNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::InvalidFederationTime &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidLogicalTime(ws.c_str());
  }
  catch(GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidRegion(ws.c_str());
  }
  catch(GeRtiFactory::InvalidRegionContext &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"InvalidRegionContext");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidRegionContext(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in sendInteractionWithRegion ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sIWR_s0)
                            {
                              unsigned long ul;
                              unsigned long ul1;

                              ul = erHandle.theSerialNumber;
                              ul1 = erHandle.sendingFederate;
                              sprintf(galMsg,"serialNumber=%lu,sendingFederate=%lu", ul, ul1);
                              E1mEnd(sIWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::MessageRetractionHandle *messageRetractionHandlePtr = new RTI::MessageRetractionHandle();
  GERTICO::Mapper1516::mapMessageRetractionHandle(*messageRetractionHandlePtr, erHandle);
  std::auto_ptr< RTI::MessageRetractionHandle > ret(messageRetractionHandlePtr);
  return ret;
}

void GERTICO::RTIambServices::sendInteractionWithRegions (
  RTI::InteractionClassHandle  const & theInteraction,
  RTI::ParameterHandleValueMap const & theParameterValues,
  RTI::RegionHandleSet const & theRegionHandleSet,
  RTI::UserSuppliedTag const & theUserSuppliedTag)
throw (
  RTI::InteractionClassNotDefined,
  RTI::InteractionClassNotPublished,
  RTI::InteractionParameterNotDefined,
  RTI::InvalidRegion,
  RTI::RegionNotCreatedByThisFederate,
  RTI::InvalidRegionContext,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GERTICO::HandleSet regions;
  GeRtiFactory::GeRtiHandle classHandle;
  GeRtiFactory::HandleValues handleValues;
  GeRtiFactory::UserSuppliedTag tag;
  std::wstring ws;

  GERTICO::Mapper1516::mapInteractionClassHandle(classHandle, theInteraction);
  GERTICO::Mapper1516::mapParameterHandleValueMap(handleValues, theParameterValues);
  GERTICO::Mapper1516::mapRegionHandleSet(regions, theRegionHandleSet);
  GERTICO::Mapper1516::mapUserSuppliedTag(tag, theUserSuppliedTag);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sIWR_s1)
                            {
                              unsigned long ul;

                              ul = classHandle;
                              sprintf(galMsg,"interaction=%lu",ul);
                              E1mEnd(sIWR_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sIWR_s1)
                            {
                              unsigned int indItem;
                              unsigned long lenItems;
                              lenItems = handleValues.length();
                              for (indItem = 0; indItem < lenItems; indItem++)
                              {
                                GERTICO::Mapper::printAttributeHandleValue("parameterValue=", galMsg, handleValues[indItem]);
                                E1mEnd(sIWR_s1,galMsg);
                              }
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sIWR_s1)
                            {
                              GERTICO::Mapper::printHandleSet("regions=", galMsg, regions);
                              E1mEnd(sIWR_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sIWR_s1)
                            {
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, tag);
                              E1mEnd(sIWR_s1,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    sender->sendInteractionWithRegion(classHandle, handleValues, tag, regions);
  }
  catch(GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::InteractionClassNotPublished &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"InteractionClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionClassNotPublished(ws.c_str());
  }
  catch(GeRtiFactory::InteractionParameterNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"InteractionParameterNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionParameterNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidRegion(ws.c_str());
  }
  catch(GeRtiFactory::InvalidRegionContext &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"InvalidRegionContext");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidRegionContext(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in sendInteractionWithRegion ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sIWR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 9.13
void GERTICO::RTIambServices::requestAttributeValueUpdateWithRegions (
  RTI::ObjectClassHandle const & theClass,
  RTI::AttributeHandleSetRegionHandleSetPairVector const & theSet,
  RTI::UserSuppliedTag const & theUserSuppliedTag)
throw (
  RTI::ObjectClassNotDefined,
  RTI::AttributeNotDefined,
  RTI::InvalidRegion,
  RTI::RegionNotCreatedByThisFederate,
  RTI::InvalidRegionContext,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GERTICO::HandleSetMap attRegHandles;
  GeRtiFactory::GeRtiHandle classHandle;
  GeRtiFactory::UserSuppliedTag tag;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectClassHandle(classHandle, theClass);
  GERTICO::Mapper1516::mapAttributeHandleSetRegionHandleSetPairVector(attRegHandles, theSet);
  GERTICO::Mapper1516::mapUserSuppliedTag(tag, theUserSuppliedTag);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rCAVUWR_s0)
                            {
                              unsigned long ul;

                              ul = classHandle;
                              sprintf(galMsg,"class=%lu", ul);
                              E1mEnd(rCAVUWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rCAVUWR_s0)
                            {
                              GERTICO::Mapper::printHandleSetMap("attributeRegions=", galMsg, attRegHandles);
                              E1mEnd(rCAVUWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(rCAVUWR_s0)
                            {
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, tag);
                              E1mEnd(rCAVUWR_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    sender->requestClassAttributeValueUpdateWithRegion(classHandle, attRegHandles, tag);
  }
  catch(GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVUWR_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVUWR_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::RegionNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVUWR_ta,"RegionNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidRegionContext(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVUWR_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVUWR_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVUWR_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVUWR_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in requestClassAttributeValueUpdateWithRegion ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVUWR_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(rCAVUWR_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

//////////////////////////
// RTI Support Services //
//////////////////////////

// 10.2
RTI::ObjectClassHandle
GERTICO::RTIambServices::getObjectClassHandle (
  std::wstring const & theName)
throw (
  RTI::NameNotFound,
  RTI::FederateNotExecutionMember,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gOCH_s0)
                            {
                              sprintf(galMsg,"name=%ls", theName.c_str());
                              E1mEnd(gOCH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::GeRtiHandle classHandle;
  std::wstring ws;

  try
  {
    classHandle = sender->getObjectClassHandle(theName);
  }
  catch(GeRtiFactory::NameNotFound &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOCH_ta,"NameNotFound");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::NameNotFound(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOCH_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOCH_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in getObjectClassHandle ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOCH_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOCH_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gOCH_s0)
                            {
                              unsigned long ul;

                              ul = classHandle;
                              sprintf(galMsg, "ret=%lu", ul);
                              E1mEnd(gOCH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::ObjectClassHandle ret;
  GERTICO::Mapper1516::mapObjectClassHandle(ret, classHandle);
  return ret;
}

// 10.3
std::wstring
GERTICO::RTIambServices::getObjectClassName (
  RTI::ObjectClassHandle const & theHandle)
throw (
  RTI::InvalidObjectClassHandle,
  RTI::FederateNotExecutionMember,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle classHandle;
  std::wstring ret;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectClassHandle(classHandle, theHandle);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gOCN_s0)
                            {
                              unsigned long ul;

                              ul = classHandle;
                              sprintf(galMsg, "handle=%lu", ul);
                              E1mEnd(gOCN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    ret = sender->getObjectClassName(classHandle);
  }
  catch(GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOCN_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOCN_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOCN_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in getObjectClassName ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOCN_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOCN_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gOCN_s0)
                            {
                              sprintf(galMsg,"ret=%ls", ret.c_str());
                              E1mEnd(gOCN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.4
RTI::AttributeHandle
GERTICO::RTIambServices::getAttributeHandle (
  RTI::ObjectClassHandle const & whichClass,
  std::wstring const & theAttributeName)
throw (
  RTI::InvalidObjectClassHandle,
  RTI::NameNotFound,
  RTI::FederateNotExecutionMember,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle classHandle;
  GeRtiFactory::GeRtiHandle attributeHandle;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectClassHandle(classHandle, whichClass);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gAH_s0)
                            {
                              unsigned long ul;

                              ul = classHandle;
                              sprintf(galMsg,"class=%lu,name=%ls", ul, theAttributeName.c_str());
                              E1mEnd(gAH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    attributeHandle = sender->getAttributeHandle(theAttributeName, classHandle);
  }
  catch(GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gAH_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::NameNotFound &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gAH_ta,"NameNotFound");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::NameNotFound(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gAH_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gAH_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in getAttributeHandle ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gAH_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gAH_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gAH_s0)
                            {
                              unsigned long ul;

                              ul = attributeHandle;
                              sprintf(galMsg,"ret=%lu", ul);
                              E1mEnd(gAH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::AttributeHandle ret;
  GERTICO::Mapper1516::mapAttributeHandle(ret, attributeHandle);
  return ret;
}

// 10.5
std::wstring
GERTICO::RTIambServices::getAttributeName (
  RTI::ObjectClassHandle const & whichClass,
  RTI::AttributeHandle const & theHandle)
throw (
  RTI::InvalidObjectClassHandle,
  RTI::InvalidAttributeHandle,
  RTI::AttributeNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle classHandle;
  GeRtiFactory::GeRtiHandle attributeHandle;
  std::wstring ret;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectClassHandle(classHandle, whichClass);
  GERTICO::Mapper1516::mapAttributeHandle(attributeHandle, theHandle);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gAN_s0)
                            {
                              unsigned long ul;
                              unsigned long ul1;

                              ul = classHandle;
                              ul1 = attributeHandle;
                              sprintf(galMsg, "handle=%lu,class=%lu", ul, ul1);
                              E1mEnd(gAN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  try
  {
    ret = sender->getAttributeName(attributeHandle, classHandle);
  }
  catch(GeRtiFactory::ObjectClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gAN_ta,"ObjectClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gAN_ta,"AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gAN_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gAN_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in getAttributeName ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gAN_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gAN_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gAN_s0)
                            {
                              sprintf(galMsg,"ret=%ls", ret.c_str());
                              E1mEnd(gAN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.6
RTI::InteractionClassHandle
GERTICO::RTIambServices::getInteractionClassHandle (
  std::wstring const & theName)
throw (
  RTI::NameNotFound,
  RTI::FederateNotExecutionMember,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gICH_s0)
                            {
                              sprintf(galMsg,"name=%ls", theName.c_str());
                              E1mEnd(gICH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::GeRtiHandle classHandle;
  std::wstring ws;

  try
  {
    classHandle = sender->getInteractionClassHandle(theName);
  }
  catch(GeRtiFactory::NameNotFound &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gICH_ta,"NameNotFound");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::NameNotFound(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gICH_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gICH_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in getInteractionClassHandle ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gICH_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gICH_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gICH_s0)
                            {
                              unsigned long ul;

                              ul = classHandle;
                              sprintf(galMsg,"ret=%lu", ul);
                              E1mEnd(gICH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::InteractionClassHandle ret;
  GERTICO::Mapper1516::mapInteractionClassHandle(ret, classHandle);
  return ret;
}

// 10.7
std::wstring
GERTICO::RTIambServices::getInteractionClassName (
  RTI::InteractionClassHandle const & theHandle)
throw (
  RTI::InvalidInteractionClassHandle,
  RTI::FederateNotExecutionMember,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle classHandle;
  std::wstring ret;
  std::wstring ws;

  GERTICO::Mapper1516::mapInteractionClassHandle(classHandle, theHandle);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gICN_s0)
                            {
                              unsigned long ul;

                              ul = classHandle;
                              sprintf(galMsg,"handle=%lu", ul);
                              E1mEnd(gICN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    ret = sender->getInteractionClassName(classHandle);
  }
  catch(GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gICN_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidInteractionClassHandle(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gICN_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gICN_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in getInteractionClassName ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gICN_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gICN_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gICN_s0)
                            {
                              sprintf(galMsg,"ret=%ls", ret.c_str());
                              E1mEnd(gICN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.8
RTI::ParameterHandle
GERTICO::RTIambServices::getParameterHandle (
  RTI::InteractionClassHandle const & whichClass,
  std::wstring const & theName)
throw (
  RTI::InvalidInteractionClassHandle,
  RTI::NameNotFound,
  RTI::FederateNotExecutionMember,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle classHandle;
  GeRtiFactory::GeRtiHandle parameterHandle;
  std::wstring ws;

  GERTICO::Mapper1516::mapInteractionClassHandle(classHandle, whichClass);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gPH_s0)
                            {
                              unsigned long ul;

                              ul = classHandle;
                              sprintf(galMsg,"name=%ls,class=%lu", theName.c_str(), ul);
                              E1mEnd(gPH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    parameterHandle = sender->getParameterHandle(theName, classHandle);
  }
  catch(GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gPH_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::NameNotFound &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gPH_ta,"NameNotFound");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::NameNotFound(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gPH_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gPH_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in getParameterHandle ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gPH_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gPH_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gPH_s0)
                            {
                              unsigned long ul;

                              ul = parameterHandle;
                              sprintf(galMsg,"ret=%lu", ul);
                              E1mEnd(gPH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::ParameterHandle ret;
  GERTICO::Mapper1516::mapParameterHandle(ret, parameterHandle);
  return ret;
}

// 10.9
std::wstring
GERTICO::RTIambServices::getParameterName (
  RTI::InteractionClassHandle const & whichClass,
  RTI::ParameterHandle const & theHandle)
throw (
  RTI::InvalidInteractionClassHandle,
  RTI::InvalidParameterHandle,
  RTI::InteractionParameterNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle classHandle;
  GeRtiFactory::GeRtiHandle parameterHandle;
  std::wstring ret;
  std::wstring ws;

  GERTICO::Mapper1516::mapInteractionClassHandle(classHandle, whichClass);
  GERTICO::Mapper1516::mapParameterHandle(parameterHandle, theHandle);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gPN_s0)
                            {
                              unsigned long ul;
                              unsigned long ul1;

                              ul = classHandle;
                              ul1 = parameterHandle;
                              sprintf(galMsg,"class=%lu,parameter=%lu", ul, ul1);
                              E1mEnd(gPN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    ret = sender->getParameterName(parameterHandle, classHandle);
  }
  catch(GeRtiFactory::InteractionClassNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gPN_ta,"InteractionClassNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionClassNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::InteractionParameterNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gPN_ta,"InteractionParameterNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionParameterNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gPN_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gPN_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in getParameterName ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gPN_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gPN_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gPN_s0)
                            {
                              sprintf(galMsg,"ret=%ls", ret.c_str());
                              E1mEnd(gPN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.10
RTI::ObjectInstanceHandle
GERTICO::RTIambServices::getObjectInstanceHandle (
  std::wstring const & theName)
throw (
    RTI::ObjectInstanceNotKnown,
    RTI::FederateNotExecutionMember,
    RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gOIH_s0)
                            {
                              sprintf(galMsg,"name=%ls",theName.c_str());
                              E1mEnd(gOIH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::GeRtiHandle objectHandle;
  std::wstring ws;

  try
  {
    objectHandle = sender->getObjectInstanceHandle(theName);
  }
  catch(GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOIH_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNotKnown(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOIH_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOIH_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in getObjectInstanceHandle ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOIH_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOIH_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gOIH_s0)
                            {
                              unsigned long ul;

                              ul = objectHandle;
                              sprintf(galMsg,"ret=%lu", ul);
                              E1mEnd(gOIH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::ObjectInstanceHandle ret;
  GERTICO::Mapper1516::mapObjectInstanceHandle(ret, objectHandle);
  return ret;
}

// 10.11
std::wstring
GERTICO::RTIambServices::getObjectInstanceName (
  RTI::ObjectInstanceHandle const & theHandle)
throw (
  RTI::ObjectInstanceNotKnown,
  RTI::FederateNotExecutionMember,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle objectHandle;
  std::wstring ret;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectHandle, theHandle);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gOIN_s0)
                            {
                              unsigned long ul;

                              ul = objectHandle;
                              sprintf(galMsg, "handle=%lu", ul);
                              E1mEnd(gOIN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  try
  {
    ret = sender->getObjectInstanceName(objectHandle);
  }
  catch(GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOIN_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNotKnown(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOIN_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOIN_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in getObjectInstanceName ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOIN_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOIN_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gOIN_s0)
                            {
                              sprintf(galMsg,"ret=%ls", ret.c_str());
                              E1mEnd(gOIN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.14
RTI::DimensionHandle
GERTICO::RTIambServices::getDimensionHandle (
  std::wstring const & theName)
throw (
  RTI::NameNotFound,
  RTI::FederateNotExecutionMember,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gDH_s0)
                            {
                              sprintf(galMsg,"name=%ls", theName.c_str());
                              E1mEnd(gDH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::GeRtiHandle dimensionHandle;
  GeRtiFactory::GeRtiHandle spaceHandle = 0;
  std::wstring ws;

  try
  {
    dimensionHandle = sender->getDimensionHandle(theName, spaceHandle);
  }
  catch(GeRtiFactory::NameNotFound &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gDH_ta,"NameNotFound");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::NameNotFound(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gDH_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gDH_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in getDimensionHandle ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gDH_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gDH_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gDH_s0)
                            {
                              unsigned long ul;

                              ul = dimensionHandle;
                              sprintf(galMsg,"ret=%lu", ul);
                              E1mEnd(gDH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::DimensionHandle ret;
  GERTICO::Mapper1516::mapDimensionHandle(ret, dimensionHandle);
  return ret;
}

// 10.15
std::wstring
GERTICO::RTIambServices::getDimensionName (
  RTI::DimensionHandle const & theHandle)
throw (
  RTI::InvalidDimensionHandle,
  RTI::FederateNotExecutionMember,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle dimensionHandle;
  GeRtiFactory::GeRtiHandle spaceHandle = 0;
  std::wstring ret;
  std::wstring ws;

  GERTICO::Mapper1516::mapDimensionHandle(dimensionHandle, theHandle);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gDN_s0)
                            {
                              unsigned long ul;

                              ul = dimensionHandle;
                              sprintf(galMsg,"handle=%lu", ul);
                              E1mEnd(gDN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  try
  {
    ret = sender->getDimensionName(dimensionHandle, spaceHandle);
  }
  catch(GeRtiFactory::DimensionNotDefined &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gDN_ta,"DimensionNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidDimensionHandle(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gDN_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gDN_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in getDimensionName ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gDN_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gDN_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gDN_s0)
                            {
                              sprintf(galMsg,"ret=%ls", ret.c_str());
                              E1mEnd(gDN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// XXX 10.14
unsigned long GERTICO::RTIambServices::getDimensionUpperBound
(RTI::DimensionHandle const & theHandle)
  throw (RTI::InvalidDimensionHandle,
         RTI::FederateNotExecutionMember,
         RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle dimensionHandle;
  std::wstring ws;
  unsigned long ret = 0;

  GERTICO::Mapper1516::mapDimensionHandle(dimensionHandle, theHandle);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gDUB_s0)
                            {
                              unsigned long ul;

                              ul = dimensionHandle;
                              sprintf(galMsg,"handle=%lu", ul);
                              E1mEnd(gDUB_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  try
  {
    ret = sender->getDimensionUpperBound(dimensionHandle);
  }
  catch(GeRtiFactory::DimensionNotDefined &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidDimensionHandle(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in getDimensionUpperBound ");
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
    throw RTI::RTIinternalError(L"unknown Exception");
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gDUB_s0)
                            {
                              sprintf(galMsg,"handle=%lu", ret);
                              E1mEnd(gDUB_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// XXX 10.15
RTI::DimensionHandleSet GERTICO::RTIambServices::getAvailableDimensionsForClassAttribute
(RTI::ObjectClassHandle const & theClass,
 RTI::AttributeHandle const & theHandle)
  throw (RTI::InvalidObjectClassHandle,
         RTI::InvalidAttributeHandle,
         RTI::AttributeNotDefined,
         RTI::FederateNotExecutionMember,
         RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle attributeHandle;
  GeRtiFactory::GeRtiHandle classHandle;
  GeRtiFactory::Handles dimensionHandles;
  RTI::DimensionHandleSet ret;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectClassHandle(classHandle, theClass);
  GERTICO::Mapper1516::mapAttributeHandle(attributeHandle, theHandle);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gADFCA_s0)
                            {
                              unsigned long ul;
                              unsigned long ul1;

                              ul = classHandle;
                              ul1 = attributeHandle;
                              sprintf(galMsg,"handle=%lu,attribute=%lu", ul, ul1);
                              E1mEnd(gADFCA_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    sender->getAvailableDimensionsForClassAttribute(classHandle, attributeHandle, dimensionHandles);
    GERTICO::Mapper1516::mapDimensionHandleSet(ret, dimensionHandles);
  }
  catch(GeRtiFactory::ObjectClassNotDefined &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidObjectClassHandle(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotKnown &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidAttributeHandle(ws.c_str());
  }
  catch(GeRtiFactory::AttributeNotDefined &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeNotDefined(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in getAvailableDimensionsForClassAttribute ");
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
    throw RTI::RTIinternalError(L"unknown Exception");
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gADFCA_s0)
                            {
                              GERTICO::Mapper::printGeRtiFactoryHandles("dimensions=", galMsg, dimensionHandles);
                              E1mEnd(gADFCA_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  return ret;
}

// 10.17
RTI::ObjectClassHandle
GERTICO::RTIambServices::getKnownObjectClassHandle (
  RTI::ObjectInstanceHandle const & theObject)
throw (
  RTI::ObjectInstanceNotKnown,
  RTI::FederateNotExecutionMember,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle classHandle;
  GeRtiFactory::GeRtiHandle objectHandle;
  std::wstring ws;

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectHandle, theObject);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gOC_s0)
                            {
                              unsigned long ul;

                              ul = objectHandle;
                              sprintf(galMsg, "object=%lu", ul);
                              E1mEnd(gOC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  try
  {
    classHandle = sender->getObjectClass(objectHandle);
  }
  catch(GeRtiFactory::ObjectNotKnown &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOC_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectInstanceNotKnown(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOC_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOC_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in getObjectClass ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOC_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOC_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gOC_s0)
                            {
                              unsigned long ul;

                              ul = classHandle;
                              sprintf(galMsg,"ret=%lu", ul);
                              E1mEnd(gOC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  RTI::ObjectClassHandle ret;
  GERTICO::Mapper1516::mapObjectClassHandle(ret, classHandle);
  return ret;
}

// XXX 10.17
RTI::DimensionHandleSet
GERTICO::RTIambServices::getAvailableDimensionsForInteractionClass(
  RTI::InteractionClassHandle const & theClass)
throw (RTI::InvalidInteractionClassHandle,
       RTI::FederateNotExecutionMember,
       RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle interactionHandle;
  GeRtiFactory::Handles dimensionHandles;
  RTI::DimensionHandleSet ret;
  std::wstring ws;

  GERTICO::Mapper1516::mapInteractionClassHandle(interactionHandle, theClass);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gADFIC_s0)
                            {
                              unsigned long ul;

                              ul = interactionHandle;
                              sprintf(galMsg,"handle=%lu", ul);
                              E1mEnd(gADFIC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  try
  {
    sender->getAvailableDimensionsForInteractionClass(interactionHandle, dimensionHandles);
    GERTICO::Mapper1516::mapDimensionHandleSet(ret, dimensionHandles);
  }
  catch(GeRtiFactory::InteractionClassNotDefined &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidInteractionClassHandle(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in getAvailableDimensionsForInteractionClass ");
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
    throw RTI::RTIinternalError(L"unknown Exception");
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gADFIC_s0)
                            {
                              GERTICO::Mapper::printGeRtiFactoryHandles("dimensions=", galMsg, dimensionHandles);
                              E1mEnd(gADFIC_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.19
RTI::TransportationType
GERTICO::RTIambServices::getTransportationType (
  std::wstring const & transportationName)
throw (
  RTI::InvalidTransportationName,
  RTI::FederateNotExecutionMember,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle transportationType = 0;
  bool nameFound = false;

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gTH_s0)
                            {
                              sprintf(galMsg,"name=%ls",transportationName.c_str());
                              E1mEnd(gTH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  if (transportationName == L"HLAreliable")
  {
    nameFound = true;
    transportationType = 0;
  }

  if (transportationName == L"HLAbestEffort")
  {
    nameFound = true;
    transportationType = 1;
  }

  if (nameFound == false)
  {
    std::wstring ws = L"getTransportationType";
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gTH_ta,"NameNotFound");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::NameNotFound(ws.c_str());
  }

  RTI::TransportationType ret(RTI::TransportationType::reliable());
  if (transportationType)
  {
    ret = RTI::TransportationType::bestEffort();
  }

  return ret;
}

// 10.20
std::wstring
GERTICO::RTIambServices::getTransportationName (
  RTI::TransportationType const & transportationType)
throw (
  RTI::InvalidTransportationType,
  RTI::FederateNotExecutionMember,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle transportationHandle;
  bool typeFound = false;
  std::wstring ret;

  GERTICO::Mapper1516::mapTransportationType(transportationHandle, transportationType);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gTN_s0)
                            {
                              unsigned long ul;

                              ul = transportationHandle;
                              sprintf(galMsg, "handle=%lu", ul);
                              E1mEnd(gTN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  if (transportationType == RTI::RELIABLE)
  {
    ret = L"HLAreliable";
    typeFound = true;
  }
  if (transportationType == RTI::BEST_EFFORT)
  {
    ret = L"HLAbest_effort";
    typeFound = true;
  }

  if (typeFound == false)
  {
    std::wstring ws = L"getTransportationName";
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gTN_ta,"InvalidTransportationHandle");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::InvalidTransportationType(ws.c_str());
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gTN_s0)
                            {
                              sprintf(galMsg,"ret=%ls", ret.c_str());
                              E1mEnd(gTN_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// ---------------------------------------------------------------------------
// 10.21
// ---------------------------------------------------------------------------
RTI::OrderType
GERTICO::RTIambServices::getOrderType (
  std::wstring const & orderName)
throw (
  RTI::InvalidOrderName,
  RTI::FederateNotExecutionMember,
  RTI::RTIinternalError)
{
  bool nameFound = false;
  unsigned long orderHandle;

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gOH_s0)
                            {
                              sprintf(galMsg,"name=%ls", orderName.c_str());
                              E1mEnd(gOH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  if (orderName == L"Receive")
  {
    nameFound = true;
    orderHandle = 0;
  }

  if (orderName == L"TimeStamp")
  {
    nameFound = true;
    orderHandle = 1;
  }

  if (nameFound == false)
  {
    std::wstring ws = L"getOrderType";
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gOH_ta,"InvalidOrderName");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::InvalidOrderName(ws.c_str());
  }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gOH_s0)
                            {
                              sprintf(galMsg,"orderType=%lu", orderHandle);
                              E1mEnd(gOH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  RTI::OrderType ret(RTI::OrderType::receive());
  if (orderHandle == 1)
  {
    ret = RTI::OrderType::timestamp();
  }

  return ret;
}

// ---------------------------------------------------------------------------
// 10.22
// ---------------------------------------------------------------------------
std::wstring
GERTICO::RTIambServices::getOrderName (
  RTI::OrderType const & orderType)
throw (
  RTI::InvalidOrderType,
  RTI::FederateNotExecutionMember,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle orderHandle;
  bool typeFound = false;
  std::wstring ret;

  GERTICO::Mapper1516::mapOrderType(orderHandle, orderType);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gON_s0)
                            {
                              unsigned long ul;

                              ul = orderHandle;
                              sprintf(galMsg, "handle=%lu", ul);
                              E1mEnd(gON_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  if (orderType == RTI::RECEIVE)
  {
    ret = L"receive";
    typeFound = true;
  }
  if (orderType == RTI::TIMESTAMP)
  {
    ret = L"TimeStamp";
    typeFound = true;
  }

  if (typeFound == false)
  {
    std::wstring ws = L"getOrderName";
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(gON_ta,"InvalidOrderingHandle");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::InvalidOrderType(ws.c_str());
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gON_s0)
                            {
                              sprintf(galMsg,"ret=%ls", ret.c_str());
                              E1mEnd(gON_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// 10.23
void GERTICO::RTIambServices::enableObjectClassRelevanceAdvisorySwitch()
throw(
  RTI::ObjectClassRelevanceAdvisorySwitchIsOn,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(eCRAS_s0);
                           #endif   // inserted by Gal converter
  std::wstring ws;

  try
  {
    sender->enableClassRelevanceAdvisorySwitch();
  }
  catch(GeRtiFactory::ObjectClassRelevanceAdvisorySwitchIsOn &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ta,"ObjectClassRelevanceAdvisorySwitchIsOn");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassRelevanceAdvisorySwitchIsOn(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in enableClassRelevanceAdvisorySwitch ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 10.24
void GERTICO::RTIambServices::disableObjectClassRelevanceAdvisorySwitch()
throw(
  RTI::ObjectClassRelevanceAdvisorySwitchIsOff,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(dCRAS_s0);
                           #endif   // inserted by Gal converter
  std::wstring ws;

  try
  {
    sender->disableClassRelevanceAdvisorySwitch();
  }
  catch(GeRtiFactory::ObjectClassRelevanceAdvisorySwitchIsOff &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ta,"ObjectClassRelevanceAdvisorySwitchIsOff");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::ObjectClassRelevanceAdvisorySwitchIsOff(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in disableClassRelevanceAdvisorySwitch ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eCRAS_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 10.25
void GERTICO::RTIambServices::enableAttributeRelevanceAdvisorySwitch()
throw(
  RTI::AttributeRelevanceAdvisorySwitchIsOn,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(eARAS_s0);
                           #endif   // inserted by Gal converter
  std::wstring ws;

  try
  {
    sender->enableAttributeRelevanceAdvisorySwitch();
  }
  catch(GeRtiFactory::AttributeRelevanceAdvisorySwitchIsOn &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eARAS_ta,"AttributeRelevanceAdvisorySwitchIsOn");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeRelevanceAdvisorySwitchIsOn(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eARAS_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eARAS_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eARAS_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eARAS_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in enableAttributeRelevanceAdvisorySwitch ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eARAS_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eARAS_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 10.26
void GERTICO::RTIambServices::disableAttributeRelevanceAdvisorySwitch()
throw(
  RTI::AttributeRelevanceAdvisorySwitchIsOff,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(dARAS_s0);
                           #endif   // inserted by Gal converter
  std::wstring ws;

  try
  {
    sender->disableAttributeRelevanceAdvisorySwitch();
  }
  catch(GeRtiFactory::AttributeRelevanceAdvisorySwitchIsOff &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dARAS_ta,"AttributeRelevanceAdvisorySwitchIsOff");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeRelevanceAdvisorySwitchIsOff(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dARAS_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dARAS_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dARAS_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dARAS_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in disableAttributeRelevanceAdvisorySwitch ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dARAS_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dARAS_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 10.27
void GERTICO::RTIambServices::enableAttributeScopeAdvisorySwitch()
throw(
  RTI::AttributeScopeAdvisorySwitchIsOn,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(eASAS_s0);
                           #endif   // inserted by Gal converter
  std::wstring ws;

  try
  {
    sender->enableAttributeScopeAdvisorySwitch();
  }
  catch(GeRtiFactory::AttributeScopeAdvisorySwitchIsOn &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eASAS_ta,"AttributeScopeAdvisorySwitchIsOn");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeScopeAdvisorySwitchIsOn(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eASAS_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eASAS_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eASAS_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eASAS_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in enableAttributeScopeAdvisorySwitch ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eASAS_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eASAS_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 10.28
void GERTICO::RTIambServices::disableAttributeScopeAdvisorySwitch()
throw(
  RTI::AttributeScopeAdvisorySwitchIsOff,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(dASAS_s0);
                           #endif   // inserted by Gal converter
  std::wstring ws;

  try
  {
    sender->disableAttributeScopeAdvisorySwitch();
  }
  catch(GeRtiFactory::AttributeScopeAdvisorySwitchIsOff &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dASAS_ta,"AttributeScopeAdvisorySwitchIsOff");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::AttributeScopeAdvisorySwitchIsOff(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dASAS_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dARAS_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dARAS_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dASAS_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in disableAttributeScopeAdvisorySwitch ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dARAS_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dARAS_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 10.29
void GERTICO::RTIambServices::enableInteractionRelevanceAdvisorySwitch()
throw(
  RTI::InteractionRelevanceAdvisorySwitchIsOn,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(eIRAS_s0);
                           #endif   // inserted by Gal converter
  std::wstring ws;

  try
  {
    sender->enableInteractionRelevanceAdvisorySwitch();
  }
  catch(GeRtiFactory::InteractionRelevanceAdvisorySwitchIsOn &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eIRAS_ta,"InteractionRelevanceAdvisorySwitchIsOn");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionRelevanceAdvisorySwitchIsOn(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eIRAS_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eIRAS_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eIRAS_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eIRAS_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in enableInteractionRelevanceAdvisorySwitch ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eIRAS_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(eIRAS_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// 10.30
void GERTICO::RTIambServices::disableInteractionRelevanceAdvisorySwitch()
throw(
  RTI::InteractionRelevanceAdvisorySwitchIsOff,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E0(dIRAS_s0);
                           #endif   // inserted by Gal converter
  std::wstring ws;

  try
  {
    sender->disableInteractionRelevanceAdvisorySwitch();
  }
  catch(GeRtiFactory::InteractionRelevanceAdvisorySwitchIsOff &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dIRAS_ta,"InteractionRelevanceAdvisorySwitchIsOff");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InteractionRelevanceAdvisorySwitchIsOff(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dIRAS_ta,"FederateNotExecutionMember");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dIRAS_ta,"SaveInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dIRAS_ta,"RestoreInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dIRAS_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in disableInteractionRelevanceAdvisorySwitch ");
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dIRAS_ts,"CORBA::SystemException");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(dIRAS_ts,"unknown Exception");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"unknown Exception");
  }
}

// XXX 10.30
RTI::DimensionHandleSet GERTICO::RTIambServices::getDimensionHandleSet(
  RTI::RegionHandle const & theRegionHandle)
throw (
  RTI::InvalidRegion,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle regionHandle;
  GeRtiFactory::Handles dimensionHandles;
  RTI::DimensionHandleSet ret;
  std::wstring ws;

  GERTICO::Mapper1516::mapRegionHandle(regionHandle, theRegionHandle);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gDHS_s0)
                            {
                              unsigned long ul;

                              ul = regionHandle;
                              sprintf(galMsg,"handle=%lu", ul);
                              E1mEnd(gDHS_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  try
  {
    sender->getDimensionHandleSet(regionHandle, dimensionHandles);
    GERTICO::Mapper1516::mapDimensionHandleSet(ret, dimensionHandles);
  }
  catch(GeRtiFactory::InteractionClassNotDefined &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidInteractionClassHandle(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in getDimensionHandleSet ");
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
    throw RTI::RTIinternalError(L"unknown Exception");
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gDHS_s0)
                            {
                              GERTICO::Mapper::printGeRtiFactoryHandles("dimensions=", galMsg, dimensionHandles);
                              E1mEnd(gDHS_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// XXX 10.31
RTI::RangeBounds GERTICO::RTIambServices::getRangeBounds
(RTI::RegionHandle    const & theRegionHandle,
 RTI::DimensionHandle const & theDimensionHandle)
  throw (RTI::InvalidRegion,
         RTI::RegionDoesNotContainSpecifiedDimension,
         RTI::FederateNotExecutionMember,
         RTI::SaveInProgress,
         RTI::RestoreInProgress,
         RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle dimensionHandle;
  GeRtiFactory::GeRtiHandle regionHandle;
  GeRtiFactory::Handles rangeBounds;
  RTI::RangeBounds ret;
  std::wstring ws;

  GERTICO::Mapper1516::mapRegionHandle(regionHandle, theRegionHandle);
  GERTICO::Mapper1516::mapDimensionHandle(dimensionHandle, theDimensionHandle);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gRB_s0)
                            {
                              unsigned long ul;
                              unsigned long ul1;

                              ul = regionHandle;
                              ul1 = dimensionHandle;
                              sprintf(galMsg,"regionHandle=%lu,dimensionHandle=%lu", ul, ul1);
                              E1mEnd(gRB_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  try
  {
    sender->getRangeBounds(regionHandle, dimensionHandle, rangeBounds);
    GERTICO::Mapper1516::mapRangeBounds(ret, rangeBounds);
  }
  catch(GeRtiFactory::RegionNotKnown &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::InvalidRegion(ws.c_str());
  }
  catch(GeRtiFactory::RegionDoesNotContainSpecifiedDimension &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RegionDoesNotContainSpecifiedDimension(ws.c_str());
  }
  catch(GeRtiFactory::FederateNotExecutionMember &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::FederateNotExecutionMember(ws.c_str());
  }
  catch(GeRtiFactory::SaveInProgress &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::SaveInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RestoreInProgress &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RestoreInProgress(ws.c_str());
  }
  catch(GeRtiFactory::RTIinternalError &ex)
  {
    GERTICO::Mapper::mapWstringFromWchar(ws, ex.reason);
    throw RTI::RTIinternalError(ws.c_str());
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in getRangeBounds ");
    throw RTI::RTIinternalError(L"CORBA::SystemException");
  }
  catch(...)
  {
    throw RTI::RTIinternalError(L"unknown Exception");
  }

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(gRB_s0)
                            {
                              GERTICO::Mapper::printGeRtiFactoryHandles("rangeBounds=", galMsg, rangeBounds);
                              E1mEnd(gRB_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// XXX 10.32
void GERTICO::RTIambServices::setRangeBounds
(RTI::RegionHandle    const & theRegionHandle,
 RTI::DimensionHandle const & theDimensionHandle,
 RTI::RangeBounds     const & theRangeBounds)
  throw (RTI::InvalidRegion,
         RTI::RegionNotCreatedByThisFederate,
         RTI::RegionDoesNotContainSpecifiedDimension,
         RTI::InvalidRangeBound,
         RTI::FederateNotExecutionMember,
         RTI::SaveInProgress,
         RTI::RestoreInProgress,
         RTI::RTIinternalError)
{
  GERTICO::BoundsMap::iterator itBoundsMap;
  GERTICO::RegionIMap::iterator itRegionIMap;
  GERTICO::UpperLowerBounds upperLowerBounds(0, 0);
  GeRtiFactory::GeRtiHandle dimensionHandle;
  GeRtiFactory::GeRtiHandle regionHandle;
  std::wstring ws;

  GERTICO::Mapper1516::mapRegionHandle(regionHandle, theRegionHandle);
  GERTICO::Mapper1516::mapDimensionHandle(dimensionHandle, theDimensionHandle);
  GERTICO::Mapper1516::mapRangeBounds(upperLowerBounds, theRangeBounds);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sRB_s0)
                            {
                              unsigned long ul;
                              unsigned long ul1;
                              unsigned long ul2;
                              unsigned long ul3;

                              ul = regionHandle;
                              ul1 = dimensionHandle;
                              ul2 = upperLowerBounds.lower;
                              ul3 = upperLowerBounds.upper;
                              sprintf(galMsg,"regionHandle=%lu,dimensionHandle=%lu,lower=%lu,upper=%lu", ul, ul1, ul2, ul3);
                              E1mEnd(sRB_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  itRegionIMap = regionIMap.find(regionHandle);
  if (itRegionIMap != regionIMap.end())
  {
    itBoundsMap = itRegionIMap->second->boundsMap.find(dimensionHandle);
    if (itBoundsMap != itRegionIMap->second->boundsMap.end())
    {
      itBoundsMap->second->lower = upperLowerBounds.lower;
      itBoundsMap->second->upper = upperLowerBounds.upper;
    }
    else
    {
      throw RTI::RegionDoesNotContainSpecifiedDimension(ws.c_str());
    }
  }
  else
  {
    throw RTI::InvalidRegion(ws.c_str());
  }
}

// XXX 10.33
unsigned long GERTICO::RTIambServices::normalizeFederateHandle
(RTI::FederateHandle const & theFederateHandle)
  throw (RTI::InvalidFederateHandle,
         RTI::FederateNotExecutionMember,
         RTI::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle fed;
  unsigned long ret = 0;

  GERTICO::Mapper1516::mapFederateHandle(fed, theFederateHandle);

                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(nFH_s0)
                            {
                              unsigned long ul;

                              ul = fed;
                              sprintf(galMsg,"handle=%lu", ul);
                              E1mEnd(nFH_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter

  ret = fed;

  return ret;
}

// XXX 10.34
unsigned long GERTICO::RTIambServices::normalizeServiceGroup
(RTI::ServiceGroupIndicator const & theServiceGroup)
  throw (RTI::FederateNotExecutionMember,
         RTI::InvalidServiceGroup,
         RTI::RTIinternalError)
{
  if (theServiceGroup == RTI::ServiceGroupIndicator::federationManagement())
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(nSG_s0)
                            {
                              strcpy(galMsg,"federationManagement");
                              E1mEnd(nSG_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
    return 1;
  }

  if (theServiceGroup == RTI::ServiceGroupIndicator::declarationManagement())
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(nSG_s0)
                            {
                              strcpy(galMsg,"declarationManagement");
                              E1mEnd(nSG_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
    return 2;
  }

  if (theServiceGroup == RTI::ServiceGroupIndicator::objectManagement())
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(nSG_s0)
                            {
                              strcpy(galMsg,"objectManagement");
                              E1mEnd(nSG_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
    return 3;
  }

  if (theServiceGroup == RTI::ServiceGroupIndicator::ownershipManagement())
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(nSG_s0)
                            {
                              strcpy(galMsg,"ownershipManagement");
                              E1mEnd(nSG_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
    return 4;
  }

  if (theServiceGroup == RTI::ServiceGroupIndicator::timeManagement())
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(nSG_s0)
                            {
                              strcpy(galMsg,"timeManagement");
                              E1mEnd(nSG_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
    return 5;
  }

  if (theServiceGroup == RTI::ServiceGroupIndicator::dataDistributionManagement())
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(nSG_s0)
                            {
                              strcpy(galMsg,"dataDistributionManagement");
                              E1mEnd(nSG_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
    return 6;
  }

  if (theServiceGroup == RTI::ServiceGroupIndicator::supportServices())
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(nSG_s0)
                            {
                              strcpy(galMsg,"supportServices");
                              E1mEnd(nSG_s0,galMsg);
                            }
                           #endif   // inserted by Gal converter
    return 7;
  }

  throw RTI::InvalidServiceGroup(L"normalizeServiceGroup");
}

//
bool
GERTICO::RTIambServices::evokeCallback (double approximateMinimumTimeInSeconds)
throw (
  RTI::FederateNotExecutionMember,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E0(eC_e);   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  CORBA::Boolean b = 0;
  bool ret = false;

  try
  {
    b = sender->tick();
  }
  catch(...)
  {
  }

  if (b == 1)
  {
    ret = true;
  }

  return ret;
}

bool
GERTICO::RTIambServices::evokeMultipleCallbacks (
  double approximateMinimumTimeInSeconds,
  double approximateMaximumTimeInSeconds)
throw (
  RTI::FederateNotExecutionMember,
  RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E0(eMC_e);   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  CORBA::Boolean b = 0;
  bool ret = false;

  try
  {
    b = sender->tick(approximateMinimumTimeInSeconds, approximateMaximumTimeInSeconds);
  }
  catch(...)
  {
  }

  if (b == 1)
  {
    ret = true;
  }

  return ret;
}

// 10.39
void GERTICO::RTIambServices::enableCallbacks ()
  throw (RTI::FederateNotExecutionMember,
         RTI::SaveInProgress,
         RTI::RestoreInProgress,
         RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E0(eC_s1);   // inserted by Gal converter
                           #endif   // inserted by Gal converter
// XXX   sender->enableCallbacks();
}

// 10.40
void GERTICO::RTIambServices::disableCallbacks ()
  throw (RTI::FederateNotExecutionMember,
         RTI::SaveInProgress,
         RTI::RestoreInProgress,
         RTI::RTIinternalError)
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E0(dC_s1);   // inserted by Gal converter
                           #endif   // inserted by Gal converter
// XXX   sender->disableCallbacks();
}

GERTICO::RTIambServices::RTIambServices()
throw()
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E0(RTI_e);   // inserted by Gal converter
                           #endif   // inserted by Gal converter

  try
  {
    receiverI = new GERTICO::ReceiverI1516();
    sender = new NAMESPACE::Sender(receiverI);
  }
  catch(...)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(RTI_ts,"RTIinternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw RTI::RTIinternalError(L"init failed");
  }

}

GERTICO::RTIambServices::~RTIambServices()
throw()
{
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E0(RTI_e);   // inserted by Gal converter
                           #endif   // inserted by Gal converter

//  delete sender;
  delete receiverI;

}
