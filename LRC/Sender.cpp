/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** Sender.cpp
**
*******************************************************************************/

// C++ standard library
//#include <stdlib.h>
#include <stdexcept>

#include "ace/Thread_Manager.h"
#include "ace/High_Res_Timer.h"

// project include files
#include "Sender.h"
#include "Util/GeRtiOrb.h"
#include "Util/XercesInclude.h"
#include <xercesc/framework/MemBufFormatTarget.hpp>
#include "Util/GeRtiTypes.h"
#include "Util/Mapper.h"
#include "Util/PrintErrorHandler.h"
#include "Util/PrintFilter.h"
#include "LrcOwnershipClient.h"

// ---------------------------------------------------------------------------
//  Local data
//
//  gOutputEncoding
//      The encoding we are to output in. If not set on the command line,
//      then it is defaults to the encoding of the input XML file.
//
//  gMyEOLSequence
//      The end of line sequence we are to output.
//
//  gSplitCdataSections
//      Indicates whether split-cdata-sections is to be enabled or not.
//
//  gDiscardDefaultContent
//      Indicates whether default content is discarded or not.
//
//  gUseFilter
//      Indicates if user wants to plug in the PrintFilter.
//
//  gValScheme
//      Indicates what validation scheme to use. It defaults to 'auto', but
//      can be set via the -v= command.
//
// ---------------------------------------------------------------------------

static char*                    goutputfile            = 0;
// options for DOMWriter's features
static XMLCh*             gOutputEncoding        = 0;
static XMLCh*             gMyEOLSequence         = 0;

static bool                     gSplitCdataSections    = true;
static bool                     gDiscardDefaultContent = true;
static bool                     gUseFilter             = false;
static bool                     gFormatPrettyPrint     = false;
static bool                     gWriteBOM              = false;

/********************************** Gal begin ***************************************/


#ifdef GalDebug

#include "Gal/StdAfx.h"
#include "Gal/repository.h"
#include "Gal/event.h"

static class Repository_l *r=(Repository::getSingleInstance())->getRepository_l("SENDER.res","SENDER");

static class Event *S_aOAIA_e=r->getRefEvent("S_aOAIA_e");
static class Event *S_aOAIA_l=r->getRefEvent("S_aOAIA_l");
static class Event *S_aOAIA_t1=r->getRefEvent("S_aOAIA_t1");
static class Event *S_aOA_e=r->getRefEvent("S_aOA_e");
static class Event *S_aOA_l=r->getRefEvent("S_aOA_l");
static class Event *S_aOA_t1=r->getRefEvent("S_aOA_t1");
static class Event *S_aORR_e=r->getRefEvent("S_aORR_e");
static class Event *S_aORR_l=r->getRefEvent("S_aORR_l");
static class Event *S_aORR_t1=r->getRefEvent("S_aORR_t1");
static class Event *S_aRFU1_q=r->getRefEvent("S_aRFU1_q");
static class Event *S_aRFU1_t1=r->getRefEvent("S_aRFU1_t1");
static class Event *S_aRFU2_q=r->getRefEvent("S_aRFU2_q");
static class Event *S_aRFU2_t1=r->getRefEvent("S_aRFU2_t1");
static class Event *S_cAOA1_e=r->getRefEvent("S_cAOA1_e");
static class Event *S_cAOA1_l=r->getRefEvent("S_cAOA1_l");
static class Event *S_cAOA1_t1=r->getRefEvent("S_cAOA1_t1");
static class Event *S_cAOA2_e=r->getRefEvent("S_cAOA2_e");
static class Event *S_cAOA2_l=r->getRefEvent("S_cAOA2_l");
static class Event *S_cAOA2_t1=r->getRefEvent("S_cAOA2_t1");
static class Event *S_cAOT_q=r->getRefEvent("S_cAOT_q");
static class Event *S_cAOT_t1=r->getRefEvent("S_cAOT_t1");
static class Event *S_cATT_q=r->getRefEvent("S_cATT_q");
static class Event *S_cATT_t1=r->getRefEvent("S_cATT_t1");
static class Event *S_cFE_e=r->getRefEvent("S_cFE_e");
static class Event *S_cFE_l=r->getRefEvent("S_cFE_l");
static class Event *S_cIOT_q=r->getRefEvent("S_cIOT_q");
static class Event *S_cIOT_t1=r->getRefEvent("S_cIOT_t1");
static class Event *S_cITT_q=r->getRefEvent("S_cITT_q");
static class Event *S_cITT_t1=r->getRefEvent("S_cITT_t1");
static class Event *S_cNAOD_e=r->getRefEvent("S_cNAOD_e");
static class Event *S_cNAOD_l=r->getRefEvent("S_cNAOD_l");
static class Event *S_cNAOD_t1=r->getRefEvent("S_cNAOD_t1");
static class Event *S_cR_q=r->getRefEvent("S_cR_q");
static class Event *S_cR_t1=r->getRefEvent("S_cR_t1");
static class Event *S_dAD_q=r->getRefEvent("S_dAD_q");
static class Event *S_dAD_t1=r->getRefEvent("S_dAD_t1");
static class Event *S_dARAS_q=r->getRefEvent("S_dARAS_q");
static class Event *S_dARAS_t1=r->getRefEvent("S_dARAS_t1");
static class Event *S_dASAS_q=r->getRefEvent("S_dASAS_q");
static class Event *S_dASAS_t1=r->getRefEvent("S_dASAS_t1");
static class Event *S_dCRAS_q=r->getRefEvent("S_dCRAS_q");
static class Event *S_dCRAS_t1=r->getRefEvent("S_dCRAS_t1");
static class Event *S_dFE_e=r->getRefEvent("S_dFE_e");
static class Event *S_dFE_l=r->getRefEvent("S_dFE_l");
static class Event *S_dIRAS_q=r->getRefEvent("S_dIRAS_q");
static class Event *S_dIRAS_t1=r->getRefEvent("S_dIRAS_t1");
static class Event *S_dOI1_e=r->getRefEvent("S_dOI1_e");
static class Event *S_dOI1_l=r->getRefEvent("S_dOI1_l");
static class Event *S_dOI1_t1=r->getRefEvent("S_dOI1_t1");
static class Event *S_dOI2_e=r->getRefEvent("S_dOI2_e");
static class Event *S_dOI2_l=r->getRefEvent("S_dOI2_l");
static class Event *S_dOI2_t1=r->getRefEvent("S_dOI2_t1");
static class Event *S_dOI2_t2=r->getRefEvent("S_dOI2_t2");
static class Event *S_dR_q=r->getRefEvent("S_dR_q");
static class Event *S_dR_t1=r->getRefEvent("S_dR_t1");
static class Event *S_dTC_e=r->getRefEvent("S_dTC_e");
static class Event *S_dTC_l=r->getRefEvent("S_dTC_l");
static class Event *S_dTC_t1=r->getRefEvent("S_dTC_t1");
static class Event *S_dTR_e=r->getRefEvent("S_dTR_e");
static class Event *S_dTR_l=r->getRefEvent("S_dTR_l");
static class Event *S_dTR_t1=r->getRefEvent("S_dTR_t1");
static class Event *S_eAD_q=r->getRefEvent("S_eAD_q");
static class Event *S_eAD_t1=r->getRefEvent("S_eAD_t1");
static class Event *S_eARAS_e=r->getRefEvent("S_eARAS_e");
static class Event *S_eARAS_l=r->getRefEvent("S_eARAS_l");
static class Event *S_eARAS_t1=r->getRefEvent("S_eARAS_t1");
static class Event *S_eARAS_t2=r->getRefEvent("S_eARAS_t2");
static class Event *S_eASAS_e=r->getRefEvent("S_eASAS_e");
static class Event *S_eASAS_l=r->getRefEvent("S_eASAS_l");
static class Event *S_eASAS_t1=r->getRefEvent("S_eASAS_t1");
static class Event *S_eASAS_t2=r->getRefEvent("S_eASAS_t2");
static class Event *S_eCRAS_e=r->getRefEvent("S_eCRAS_e");
static class Event *S_eCRAS_l=r->getRefEvent("S_eCRAS_l");
static class Event *S_eCRAS_t1=r->getRefEvent("S_eCRAS_t1");
static class Event *S_eCRAS_t2=r->getRefEvent("S_eCRAS_t2");
static class Event *S_eIRAS_e=r->getRefEvent("S_eIRAS_e");
static class Event *S_eIRAS_l=r->getRefEvent("S_eIRAS_l");
static class Event *S_eIRAS_t1=r->getRefEvent("S_eIRAS_t1");
static class Event *S_eIRAS_t2=r->getRefEvent("S_eIRAS_t2");
static class Event *S_eTC_e=r->getRefEvent("S_eTC_e");
static class Event *S_eTC_l=r->getRefEvent("S_eTC_l");
static class Event *S_eTC_t1=r->getRefEvent("S_eTC_t1");
static class Event *S_eTR_e=r->getRefEvent("S_eTR_e");
static class Event *S_eTR_l=r->getRefEvent("S_eTR_l");
static class Event *S_eTR_t1=r->getRefEvent("S_eTR_t1");
static class Event *S_fQR_q=r->getRefEvent("S_fQR_q");
static class Event *S_fQR_t1=r->getRefEvent("S_fQR_t1");
static class Event *S_fRC_q=r->getRefEvent("S_fRC_q");
static class Event *S_fRC_t1=r->getRefEvent("S_fRC_t1");
static class Event *S_fRNC_q=r->getRefEvent("S_fRNC_q");
static class Event *S_fRNC_t1=r->getRefEvent("S_fRNC_t1");
static class Event *S_fSB_q=r->getRefEvent("S_fSB_q");
static class Event *S_fSB_t1=r->getRefEvent("S_fSB_t1");
static class Event *S_fSC_q=r->getRefEvent("S_fSC_q");
static class Event *S_fSC_t1=r->getRefEvent("S_fSC_t1");
static class Event *S_fSNC_q=r->getRefEvent("S_fSNC_q");
static class Event *S_fSNC_t1=r->getRefEvent("S_fSNC_t1");
static class Event *S_gAH_e=r->getRefEvent("S_gAH_e");
static class Event *S_gAH_l=r->getRefEvent("S_gAH_l");
static class Event *S_gAH_t1=r->getRefEvent("S_gAH_t1");
static class Event *S_gAH_t2=r->getRefEvent("S_gAH_t2");
static class Event *S_gAN_e=r->getRefEvent("S_gAN_e");
static class Event *S_gAN_l=r->getRefEvent("S_gAN_l");
static class Event *S_gAN_t1=r->getRefEvent("S_gAN_t1");
static class Event *S_gAN_t2=r->getRefEvent("S_gAN_t2");
static class Event *S_gARSH_q=r->getRefEvent("S_gARSH_q");
static class Event *S_gARSH_t1=r->getRefEvent("S_gARSH_t1");
static class Event *S_gDH_q=r->getRefEvent("S_gDH_q");
static class Event *S_gDH_t1=r->getRefEvent("S_gDH_t1");
static class Event *S_gDN_q=r->getRefEvent("S_gDN_q");
static class Event *S_gDN_t1=r->getRefEvent("S_gDN_t1");
static class Event *S_gFV_e=r->getRefEvent("S_gFV_e");
static class Event *S_gFV_l=r->getRefEvent("S_gFV_l");
static class Event *S_gF_c1=r->getRefEvent("S_gF_c1");
static class Event *S_gF_e=r->getRefEvent("S_gF_e");
static class Event *S_gF_l=r->getRefEvent("S_gF_l");
static class Event *S_gF_l1=r->getRefEvent("S_gF_l1");
static class Event *S_gF_t1=r->getRefEvent("S_gF_t1");
static class Event *S_gICH_e=r->getRefEvent("S_gICH_e");
static class Event *S_gICH_l=r->getRefEvent("S_gICH_l");
static class Event *S_gICH_t1=r->getRefEvent("S_gICH_t1");
static class Event *S_gICH_t2=r->getRefEvent("S_gICH_t2");
static class Event *S_gICN_e=r->getRefEvent("S_gICN_e");
static class Event *S_gICN_l=r->getRefEvent("S_gICN_l");
static class Event *S_gICN_t1=r->getRefEvent("S_gICN_t1");
static class Event *S_gICN_t2=r->getRefEvent("S_gICN_t2");
static class Event *S_gIRSH_q=r->getRefEvent("S_gIRSH_q");
static class Event *S_gIRSH_t1=r->getRefEvent("S_gIRSH_t1");
static class Event *S_gOCH_e=r->getRefEvent("S_gOCH_e");
static class Event *S_gOCH_l=r->getRefEvent("S_gOCH_l");
static class Event *S_gOCH_t1=r->getRefEvent("S_gOCH_t1");
static class Event *S_gOCH_t2=r->getRefEvent("S_gOCH_t2");
static class Event *S_gOCN_e=r->getRefEvent("S_gOCN_e");
static class Event *S_gOCN_l=r->getRefEvent("S_gOCN_l");
static class Event *S_gOCN_t1=r->getRefEvent("S_gOCN_t1");
static class Event *S_gOCN_t2=r->getRefEvent("S_gOCN_t2");
static class Event *S_gOC_q=r->getRefEvent("S_gOC_q");
static class Event *S_gOC_t1=r->getRefEvent("S_gOC_t1");
static class Event *S_gOH_q=r->getRefEvent("S_gOH_q");
static class Event *S_gOH_t1=r->getRefEvent("S_gOH_t1");
static class Event *S_gOIH1_e=r->getRefEvent("S_gOIH1_e");
static class Event *S_gOIH1_l=r->getRefEvent("S_gOIH1_l");
static class Event *S_gOIH1_t1=r->getRefEvent("S_gOIH1_t1");
static class Event *S_gOIH1_t2=r->getRefEvent("S_gOIH1_t2");
static class Event *S_gOIH2_e=r->getRefEvent("S_gOIH2_e");
static class Event *S_gOIH2_l=r->getRefEvent("S_gOIH2_l");
static class Event *S_gOIH2_t1=r->getRefEvent("S_gOIH2_t1");
static class Event *S_gOIH2_t2=r->getRefEvent("S_gOIH2_t2");
static class Event *S_gON_q=r->getRefEvent("S_gON_q");
static class Event *S_gON_t1=r->getRefEvent("S_gON_t1");
static class Event *S_gPH_e=r->getRefEvent("S_gPH_e");
static class Event *S_gPH_l=r->getRefEvent("S_gPH_l");
static class Event *S_gPH_t1=r->getRefEvent("S_gPH_t1");
static class Event *S_gPH_t2=r->getRefEvent("S_gPH_t2");
static class Event *S_gPN_q=r->getRefEvent("S_gPN_q");
static class Event *S_gPN_t1=r->getRefEvent("S_gPN_t1");
static class Event *S_gRSH_q=r->getRefEvent("S_gRSH_q");
static class Event *S_gRSH_t1=r->getRefEvent("S_gRSH_t1");
static class Event *S_gRSN_q=r->getRefEvent("S_gRSN_q");
static class Event *S_gRSN_t1=r->getRefEvent("S_gRSN_t1");
static class Event *S_gRT_q=r->getRefEvent("S_gRT_q");
static class Event *S_gRT_t1=r->getRefEvent("S_gRT_t1");
static class Event *S_gR_q=r->getRefEvent("S_gR_q");
static class Event *S_gR_t1=r->getRefEvent("S_gR_t1");
static class Event *S_gTH_q=r->getRefEvent("S_gTH_q");
static class Event *S_gTH_t1=r->getRefEvent("S_gTH_t1");
static class Event *S_gTN_q=r->getRefEvent("S_gTN_q");
static class Event *S_gTN_t1=r->getRefEvent("S_gTN_t1");
static class Event *S_gTS=r->getRefEvent("S_gTS_e");
static class Event *S_gTS_c1=r->getRefEvent("S_gTS_c1");
static class Event *S_gTS_c2=r->getRefEvent("S_gTS_c2");
static class Event *S_gTS_c3=r->getRefEvent("S_gTS_c3");
static class Event *S_gTS_l=r->getRefEvent("S_gTS_l");
static class Event *S_iAOBF_e=r->getRefEvent("S_iAOBF_e");
static class Event *S_iAOBF_l=r->getRefEvent("S_iAOBF_l");
static class Event *S_iAOBF_t1=r->getRefEvent("S_iAOBF_t1");
static class Event *S_jFE_e=r->getRefEvent("S_jFE_e");
static class Event *S_jFE_l=r->getRefEvent("S_jFE_l");
static class Event *S_jFE_t0=r->getRefEvent("S_jFE_t0");
static class Event *S_jFE_t1=r->getRefEvent("S_jFE_t1");
static class Event *S_jFE_t2=r->getRefEvent("S_jFE_t2");
static class Event *S_jFE_t3=r->getRefEvent("S_jFE_t3");
static class Event *S_jFE_t4=r->getRefEvent("S_jFE_t4");
static class Event *S_jFE_t5=r->getRefEvent("S_jFE_t5");
static class Event *S_jFE_t6=r->getRefEvent("S_jFE_t6");
static class Event *S_lDOI_q=r->getRefEvent("S_lDOI_q");
static class Event *S_lDOI_t1=r->getRefEvent("S_lDOI_t1");
static class Event *S_mL_e=r->getRefEvent("S_mL_e");
static class Event *S_mL_l=r->getRefEvent("S_mL_l");
static class Event *S_mL_t1=r->getRefEvent("S_mL_t1");
static class Event *S_mL_t2=r->getRefEvent("S_mL_t2");
static class Event *S_nAOD_e=r->getRefEvent("S_nAOD_e");
static class Event *S_nAOD_l=r->getRefEvent("S_nAOD_l");
static class Event *S_nAOD_t1=r->getRefEvent("S_nAOD_t1");
static class Event *S_nARM_q=r->getRefEvent("S_nARM_q");
static class Event *S_nARM_t1=r->getRefEvent("S_nARM_t1");
static class Event *S_nERA_e=r->getRefEvent("S_nERA_e");
static class Event *S_nERA_l=r->getRefEvent("S_nERA_l");
static class Event *S_nERA_t1=r->getRefEvent("S_nERA_t1");
static class Event *S_nER_e=r->getRefEvent("S_nER_e");
static class Event *S_nER_l=r->getRefEvent("S_nER_l");
static class Event *S_nER_t1=r->getRefEvent("S_nER_t1");
static class Event *S_pIC_e=r->getRefEvent("S_pIC_e");
static class Event *S_pIC_l=r->getRefEvent("S_pIC_l");
static class Event *S_pIC_t1=r->getRefEvent("S_pIC_t1");
static class Event *S_pIC_t2=r->getRefEvent("S_pIC_t2");
static class Event *S_pOC_e=r->getRefEvent("S_pOC_e");
static class Event *S_pOC_l=r->getRefEvent("S_pOC_l");
static class Event *S_pOC_t1=r->getRefEvent("S_pOC_t1");
static class Event *S_pOC_t2=r->getRefEvent("S_pOC_t2");
static class Event *S_qFT_q=r->getRefEvent("S_qFT_q");
static class Event *S_qFT_t1=r->getRefEvent("S_qFT_t1");
static class Event *S_qLBTS_q=r->getRefEvent("S_qLBTS_q");
static class Event *S_qLBTS_t1=r->getRefEvent("S_qLBTS_t1");
static class Event *S_qL_e=r->getRefEvent("S_qL_e");
static class Event *S_qL_l=r->getRefEvent("S_qL_l");
static class Event *S_qL_t1=r->getRefEvent("S_qL_t1");
static class Event *S_qL_t2=r->getRefEvent("S_qL_t2");
static class Event *S_qMNET_q=r->getRefEvent("S_qMNET_q");
static class Event *S_qMNET_t1=r->getRefEvent("S_qMNET_t1");
static class Event *S_rCAVUWR_q=r->getRefEvent("S_rCAVUWR_q");
static class Event *S_rCAVUWR_t1=r->getRefEvent("S_rCAVUWR_t1");
static class Event *S_rCAVU_e=r->getRefEvent("S_rCAVU_e");
static class Event *S_rCAVU_l=r->getRefEvent("S_rCAVU_l");
static class Event *S_rCAVU_t1=r->getRefEvent("S_rCAVU_t1");
static class Event *S_rFE_e=r->getRefEvent("S_rFE_e");
static class Event *S_rFE_l=r->getRefEvent("S_rFE_l");
static class Event *S_rFE_t1=r->getRefEvent("S_rFE_t1");
static class Event *S_rFR_q=r->getRefEvent("S_rFR_q");
static class Event *S_rFR_t1=r->getRefEvent("S_rFR_t1");
static class Event *S_rFS1_q=r->getRefEvent("S_rFS1_q");
static class Event *S_rFS1_t1=r->getRefEvent("S_rFS1_t1");
static class Event *S_rFS2_q=r->getRefEvent("S_rFS2_q");
static class Event *S_rFS2_t1=r->getRefEvent("S_rFS2_t1");
static class Event *S_rFSP1_e=r->getRefEvent("S_rFSP1_e");
static class Event *S_rFSP1_l=r->getRefEvent("S_rFSP1_l");
static class Event *S_rFSP1_t1=r->getRefEvent("S_rFSP1_t1");
static class Event *S_rFSP1_t2=r->getRefEvent("S_rFSP1_t2");
static class Event *S_rFSP2_q=r->getRefEvent("S_rFSP2_q");
static class Event *S_rFSP2_t1=r->getRefEvent("S_rFSP2_t1");
static class Event *S_rOAVU_e=r->getRefEvent("S_rOAVU_e");
static class Event *S_rOAVU_l=r->getRefEvent("S_rOAVU_l");
static class Event *S_rOAVU_t1=r->getRefEvent("S_rOAVU_t1");
static class Event *S_rOAVU_t2=r->getRefEvent("S_rOAVU_t2");
static class Event *S_rOI1_e=r->getRefEvent("S_rOI1_e");
static class Event *S_rOI1_l=r->getRefEvent("S_rOI1_l");
static class Event *S_rOI1_t1=r->getRefEvent("S_rOI1_t1");
static class Event *S_rOI1_t2=r->getRefEvent("S_rOI1_t2");
static class Event *S_rOI2_e=r->getRefEvent("S_rOI2_e");
static class Event *S_rOI2_l=r->getRefEvent("S_rOI2_l");
static class Event *S_rOI2_t1=r->getRefEvent("S_rOI2_t1");
static class Event *S_rOI2_t2=r->getRefEvent("S_rOI2_t2");
static class Event *S_rOIWR1_q=r->getRefEvent("S_rOIWR1_q");
static class Event *S_rOIWR1_t1=r->getRefEvent("S_rOIWR1_t1");
static class Event *S_rOIWR2_q=r->getRefEvent("S_rOIWR2_q");
static class Event *S_rOIWR2_t1=r->getRefEvent("S_rOIWR2_t1");
static class Event *S_r_q=r->getRefEvent("S_r_q");
static class Event *S_r_t1=r->getRefEvent("S_r_t1");
static class Event *S_sE_e=r->getRefEvent("S_sE_e");
static class Event *S_sE_l=r->getRefEvent("S_sE_l");
static class Event *S_sI1_e=r->getRefEvent("S_sI1_e");
static class Event *S_sI1_l=r->getRefEvent("S_sI1_l");
static class Event *S_sI1_t1=r->getRefEvent("S_sI1_t1");
static class Event *S_sI2_e=r->getRefEvent("S_sI2_e");
static class Event *S_sI2_l=r->getRefEvent("S_sI2_l");
static class Event *S_sI2_t1=r->getRefEvent("S_sI2_t1");
static class Event *S_sICWR_q=r->getRefEvent("S_sICWR_q");
static class Event *S_sICWR_t1=r->getRefEvent("S_sICWR_t1");
static class Event *S_sIC_e=r->getRefEvent("S_sIC_e");
static class Event *S_sIC_l=r->getRefEvent("S_sIC_l");
static class Event *S_sIC_t1=r->getRefEvent("S_sIC_t1");
static class Event *S_sIWR1_q=r->getRefEvent("S_sIWR1_q");
static class Event *S_sIWR1_t1=r->getRefEvent("S_sIWR1_t1");
static class Event *S_sIWR2_q=r->getRefEvent("S_sIWR2_q");
static class Event *S_sIWR2_t1=r->getRefEvent("S_sIWR2_t1");
static class Event *S_sOCAWR_q=r->getRefEvent("S_sOCAWR_q");
static class Event *S_sOCAWR_t1=r->getRefEvent("S_sOCAWR_t1");
static class Event *S_sOCA_e=r->getRefEvent("S_sOCA_e");
static class Event *S_sOCA_l=r->getRefEvent("S_sOCA_l");
static class Event *S_sOCA_t1=r->getRefEvent("S_sOCA_t1");
static class Event *S_sPA_e=r->getRefEvent("S_sPA_e");
static class Event *S_sPA_t1=r->getRefEvent("S_sPA_t1");
static class Event *S_sPA_l=r->getRefEvent("S_sPA_l");
static class Event *S_sPA_t2=r->getRefEvent("S_sPA_t2");
static class Event *S_sc_e=r->getRefEvent("S_sc_e");
static class Event *S_sc_l=r->getRefEvent("S_sc_l");
static class Event *S_sd_e=r->getRefEvent("S_sd_e");
static class Event *S_sd_l=r->getRefEvent("S_sd_l");
static class Event *S_t1_e=r->getRefEvent("S_t1_e");
static class Event *S_t1_l=r->getRefEvent("S_t1_l");
static class Event *S_t1_l1=r->getRefEvent("S_t1_l1");
static class Event *S_t2_e=r->getRefEvent("S_t2_e");
static class Event *S_t2_l=r->getRefEvent("S_t2_l");
static class Event *S_t3_e=r->getRefEvent("S_t3_e");
static class Event *S_t3_l=r->getRefEvent("S_t3_l");
static class Event *S_tARA_e=r->getRefEvent("S_tARA_e");
static class Event *S_tARA_l=r->getRefEvent("S_tARA_l");
static class Event *S_tARA_t1=r->getRefEvent("S_tARA_t1");
static class Event *S_tAR_e=r->getRefEvent("S_tAR_e");
static class Event *S_tAR_l=r->getRefEvent("S_tAR_l");
static class Event *S_tAR_t1=r->getRefEvent("S_tAR_t1");
static class Event *S_tW_e=r->getRefEvent("S_tW_e");
static class Event *S_tW_l=r->getRefEvent("S_tW_l");
static class Event *S_uAOD_e=r->getRefEvent("S_uAOD_e");
static class Event *S_uAOD_l=r->getRefEvent("S_uAOD_l");
static class Event *S_uAOD_t1=r->getRefEvent("S_uAOD_t1");
static class Event *S_uAV1_e=r->getRefEvent("S_uAV1_e");
static class Event *S_uAV1_l=r->getRefEvent("S_uAV1_l");
static class Event *S_uAV1_t1=r->getRefEvent("S_uAV1_t1");
static class Event *S_uAV1_t2=r->getRefEvent("S_uAV1_t2");
static class Event *S_uAV2_e=r->getRefEvent("S_uAV2_e");
static class Event *S_uAV2_l=r->getRefEvent("S_uAV2_l");
static class Event *S_uAV2_t1=r->getRefEvent("S_uAV2_t1");
static class Event *S_uIC1_e=r->getRefEvent("S_uIC1_e");
static class Event *S_uIC1_l=r->getRefEvent("S_uIC1_l");
static class Event *S_uIC1_t1=r->getRefEvent("S_uIC1_t1");
static class Event *S_uIC2_e=r->getRefEvent("S_uIC2_e");
static class Event *S_uIC2_l=r->getRefEvent("S_uIC2_l");
static class Event *S_uIC2_t1=r->getRefEvent("S_uIC2_t1");
static class Event *S_uICWR_q=r->getRefEvent("S_uICWR_q");
static class Event *S_uICWR_t1=r->getRefEvent("S_uICWR_t1");
static class Event *S_uOC1_e=r->getRefEvent("S_uOC1_e");
static class Event *S_uOC1_l=r->getRefEvent("S_uOC1_l");
static class Event *S_uOC1_t1=r->getRefEvent("S_uOC1_t1");
static class Event *S_uOC2_e=r->getRefEvent("S_uOC2_e");
static class Event *S_uOC2_l=r->getRefEvent("S_uOC2_l");
static class Event *S_uOC2_t1=r->getRefEvent("S_uOC2_t1");
static class Event *S_uOCWR_q=r->getRefEvent("S_uOCWR_q");
static class Event *S_uOCWR_t1=r->getRefEvent("S_uOCWR_t1");

#endif
/********************************** Gal end ***************************************/

#define TimeService "TimeMaster"

static unsigned int GERTICO_POA_counter = 0;

struct Arg
{
  ACE_Barrier *barrier;
  GERTICO::GeRtiOrb *myGeRtiOrb;
};

// ---------------------------------------------------------------------------
// A special thread to handle jobs and granularity (seconds).
// The managementObjectModelLRC module will take care of any details.
// ---------------------------------------------------------------------------
void *timed_worker(void *arg)
{
  NAMESPACE::TimedArg *myArg = (NAMESPACE::TimedArg *)arg;
  bool ret;

  myArg->barrier->wait();
  for (;myArg->toContinue;)
  {
    myArg->ps->acquire();
    try
    {
      if (myArg->federateDB)
      {
        ret = myArg->federateDB->process();
      }
      if (myArg->federateDB->joined)
      {
        myArg->eventMarket->sendEvents();
      }
    }
   catch (...)
   {
   }
  }

  return (void *) 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void *transmission_worker(void *arg)
{
  NAMESPACE::TransmissionArg *myArg = (NAMESPACE::TransmissionArg *)arg;
  // Separate into seconds and milli-seconds.
  long l = (long) (myArg->conf->transmissionWait_ms / 1000);
  long m = myArg->conf->transmissionWait_ms - l * 1000;

  myArg->barrier->wait();
  for (;myArg->toContinue;)
  {
    myArg->ps->acquire();

    // Once a send has been made wait, wait the specified time
    // NB. second parameter in micro-seconds
    ACE_OS::sleep (ACE_Time_Value(l, m * 1000));

    try
    {
      if (myArg->federateDB->joined)
      {
        myArg->eventMarket->sendEvents ();
      }
    }
   catch (...)
   {
   }
  }

  return (void *) 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void *bestEffort_worker (void *arg)
{
  Arg *myArg = (Arg *) arg;

  try
  {
    myArg->barrier->wait ();
    myArg->myGeRtiOrb->orbSenderBestEffort->run ();
  }
  catch (...)
  {
    return (void *) 1;
  }
  return (void *) 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void *server_worker (void *arg)
{
  Arg *myArg = (Arg *) arg;

  try
  {
    myArg->barrier->wait ();
    myArg->myGeRtiOrb->orbReceiver->run ();
/*
    while (doMore)
    {
      if (orb->work_pending ())
      {
        orb->perform_work ();
        continue;
      }
      usleep (10);
    }
*/
  }
  catch (...)
  {
    return (void *) 1;
  }
  return (void *) 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
NAMESPACE::TimedArg::TimedArg(void)
{
  ps = new ACE_Semaphore(1);
  eventMarket = NULL;
  federateDB = NULL;
  toContinue = true;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
NAMESPACE::TimedArg::~TimedArg(void)
{
  delete ps;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
NAMESPACE::TransmissionArg::TransmissionArg(void)
{
  ps = new ACE_Semaphore(1);
  conf = NULL;
  eventMarket = NULL;
  federateDB = NULL;
  toContinue = true;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
NAMESPACE::TransmissionArg::~TransmissionArg(void)
{
  delete ps;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
NAMESPACE::Sender::Sender(GERTICO::ReceiverLRC *theReceiverLRC)
throw (GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_sc_e);
        #endif
  Arg arg;
  CORBA::Object_var gertiObj;
  CORBA::WChar *wChar = L"";
  CosNaming::Name bindName;
  char *eventHubName;
  char *file_xml = "GERTICOconf.xml";
  char buff[256];

  conf = NULL;
  fedAm = NULL;
  geRtiRestore = NULL;
  gotFactory = false;
  managementObjectModelLRC = NULL;
  pushConsumer = NULL;
  receiver = NULL;
  retractionHandleCounter = 1;

#ifdef GalDebug
  // Gal init
  repository = Repository::getSingleInstance();
  char* error;
  error = repository->init("MAIN.res");
  if (error)
  {
    exit (1);
  }
#endif

  char *gertico = getenv ("GERTICO");
  if (gertico == NULL)
  {
    strcpy (buff, file_xml);
  }
  else
  {
    sprintf (buff, "%s/%s", gertico, file_xml);
  }

  string filename (buff);

  // Read configuration file.
  conf = GERTICOconf::parseFromFile (filename);

  gertiName = conf->ns->rootEntry;

  try
  {
    myGeRtiOrb = new GERTICO::GeRtiOrb(*conf);
  }
  catch (...)
  {
    throw GeRtiFactory::RTIinternalError(wChar);
  }

  // Set up a nil poa manager reference.
  nilMgr = PortableServer::POAManager::_nil ();

  // Create policy list for child poas.
  policyListReceiver.length (2);
  policyListReceiver[0] = myGeRtiOrb->poaRootReceiver->create_implicit_activation_policy (PortableServer::IMPLICIT_ACTIVATION);
  policyListReceiver[1] = myGeRtiOrb->poaRootReceiver->create_thread_policy (PortableServer::SINGLE_THREAD_MODEL);

  policyListBestEffort.length (2);
  policyListBestEffort[0] = myGeRtiOrb->poaRootSenderBestEffort->create_implicit_activation_policy (PortableServer::IMPLICIT_ACTIVATION);
  policyListBestEffort[1] = myGeRtiOrb->poaRootSenderBestEffort->create_thread_policy (PortableServer::SINGLE_THREAD_MODEL);

  bindName.length (1);
  bindName[0].id = CORBA::string_dup (gertiName.c_str ());
  bindName[0].kind = CORBA::string_dup ("");
  try
  {
    gertiObj = myGeRtiOrb->getRootContext()->resolve (bindName);
  }
  catch (...)
  {
    throw GeRtiFactory::RTIinternalError(wChar);
  }

  gerti_context = CosNaming::NamingContext::_narrow (gertiObj);

  eventHubName = getenv("MY_HUB");
  if (eventHubName)
  {
    GERTICO::Mapper::mapWstringFromChar(eventHubNameStr, eventHubName);
  }
  else
  {
    GERTICO::Mapper::mapWstringFromChar(eventHubNameStr, "MyHub");
  }

  if (conf->dataLength > 1)
  {
    barrier = new ACE_Barrier(5);
  }
  else
  {
    barrier = new ACE_Barrier(4);
  }
  arg.barrier = barrier;
  arg.myGeRtiOrb = myGeRtiOrb;
  tid = ACE_Thread_Manager::instance()->spawn (ACE_reinterpret_cast (ACE_THR_FUNC, &server_worker), &arg);
  tid2 = ACE_Thread_Manager::instance()->spawn (ACE_reinterpret_cast (ACE_THR_FUNC, &bestEffort_worker), &arg);
  timedArg.barrier = barrier;
  timedArg.federateDB = &federateDB;
  tid0 = ACE_Thread_Manager::instance()->spawn (ACE_reinterpret_cast (ACE_THR_FUNC, &timed_worker), &timedArg);
  if (conf->dataLength > 1)
  {
    transmissionArg.barrier = barrier;
    transmissionArg.federateDB = &federateDB;
    transmissionArg.conf = conf;
    tid1 = ACE_Thread_Manager::instance()->spawn (ACE_reinterpret_cast (ACE_THR_FUNC, &transmission_worker), &transmissionArg);
  }
  barrier->wait ();
  ACE_OS::sleep (1);

  receiver = theReceiverLRC;
  receiver->federateDB = &federateDB;

        #ifdef GalDebug
        E0(S_sc_l);
        #endif
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
NAMESPACE::Sender&
NAMESPACE::Sender::operator = (Sender const & s)
{
  CORBA::WChar *wChar = L"";

  throw GeRtiFactory::RTIinternalError(wChar);
  return *this;
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
NAMESPACE::Sender::~Sender()
{
        #ifdef GalDebug
        E0(S_sd_e);
        #endif
  clear();

  myGeRtiOrb->mgrReceiver->discard_requests (true);
  myGeRtiOrb->mgrReceiver->deactivate (false, true);
  myGeRtiOrb->orbSenderBestEffort->shutdown (0);
  myGeRtiOrb->orbReceiver->shutdown (0);
  timedArg.toContinue = false;
  timedArg.ps->release();
  ACE_Thread_Manager::instance()->wait_grp (tid);
  ACE_Thread_Manager::instance()->wait_grp (tid0);
  ACE_Thread_Manager::instance()->wait_grp (tid2);
  if (conf)
  {
    if (conf->dataLength > 1)
    {
      transmissionArg.toContinue = false;
      transmissionArg.ps->release();
      ACE_Thread_Manager::instance()->wait_grp (tid1);
    }
  }
  delete barrier;
        #ifdef GalDebug
        E0(S_sd_l);
        // Gal terminate
        // Bähre !!! repository->terminate();
        #endif
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool NAMESPACE::Sender::isJoined(void)
{
  return federateDB.joined;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool NAMESPACE::Sender::checkReportServiceInvocation(void)
{
  return managementObjectModelLRC->checkReportServiceInvocation();
}

#ifdef IEEE_1516
void NAMESPACE::Sender::sendReportException(const GERTICO::MomException &theMomException)
{
  managementObjectModelLRC->sendReportException(theMomException);
}
#else
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::sendReportAlert(GERTICO::MomAlert const &theMomAlert)
{
  managementObjectModelLRC->sendReportAlert(theMomAlert);
}
#endif

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::sendReportServiceInvocation(GERTICO::MomReportServiceInvocation const &theMomReportServiceInvocation)
{
  managementObjectModelLRC->sendReportServiceInvocation(theMomReportServiceInvocation);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::clear()
{
        #ifdef GalDebug
        E0(S_t1_e);
        #endif
        #ifdef GalDebug
        E0(S_t1_l1);
        #endif
  // Allow poa to discard requests.
  ACE_OS::sleep (ACE_Time_Value(0,20000));

  if (managementObjectModelLRC)
  {
    delete managementObjectModelLRC;
    managementObjectModelLRC = NULL;
  }

  if (fedAm)
  {
    PortableServer::ObjectId_var objectId = myPOA->servant_to_id(fedAm);
    myPOA->deactivate_object (objectId.in());
    delete fedAm;
    fedAm = NULL;
  }

  if (geRtiRestore)
  {
    PortableServer::ObjectId_var objectId = myPOA->servant_to_id(geRtiRestore);
    myPOA->deactivate_object (objectId.in());
    delete geRtiRestore;
    geRtiRestore = NULL;
  }

  if (eventMarket)
  {
    delete eventMarket;
    eventMarket = NULL;
  }
  if (pushConsumer)
  {
    delete pushConsumer;
    pushConsumer = NULL;
  }
  timedArg.eventMarket = NULL;
  transmissionArg.eventMarket = NULL;

        #ifdef GalDebug
        E0(S_t1_l);
        #endif
  return;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::addPublishInfo (
  GeRtiFactory::GeRtiHandle const &theClass,
  GeRtiFactory::Handles const &theAttributes)
{
  GERTICO::HandleSet attributeSet;

  mapIt (attributeSet, theAttributes);
  federateDB.runTimeObjectDB->publishObjectClass(federateDB.federate, theClass, attributeSet);

}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::addPushConsumers(const GeRtiFactory::GeRtiHandle &federate, GERTICO::GeRtiOrb &theGeRtiOrb, GERTICO::ReceiverLRC &receiverLRC, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory)
{
  CORBA::Boolean reliableFlag;
  CORBA::Object_var rti_obj;
  CORBA::WChar *wChar = L"addPushConsumers";
  CosNaming::Name bindName;
  GeRtiFactory::GeRtiHandle sourceType = 2;
  std::wstring sourceName;

  reliableFlag = 1;
  pushConsumer = new GERTICO::cPushConsumer(myPOA, receiverLRC, theGeRtiFedTimeFactory);

  pushConsumer->proxySupplier = consumerAdminVar->obtain_push_supplier(sourceType, federate, sourceName.c_str(), reliableFlag);
  pushConsumer->proxySupplier->connect_push_consumer(GeRtiFactory::PushConsumer::_duplicate(pushConsumer->pConsumer));

  reliableFlag = 0;
  pushConsumerBestEffort  = new GERTICO::cPushConsumer(myPOA, receiverLRC, theGeRtiFedTimeFactory);
  pushConsumerBestEffort->proxySupplier = consumerAdminVar->obtain_push_supplier(sourceType, federate, sourceName.c_str(), reliableFlag);
  pushConsumerBestEffort->proxySupplier->connect_push_consumer(GeRtiFactory::PushConsumer::_duplicate(pushConsumerBestEffort->pConsumer));
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::mapIt (GERTICO::HandleSet &out, GeRtiFactory::Handles const &inAttributes)
{
  CORBA::ULong i;
  CORBA::ULong len;

  len = inAttributes.length ();
  for (i = 0; i < len; i++)
  {
    out.insert (inAttributes[i]);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::checkAttributeNotDefined(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSetMap &theAttributes)
{
  GERTICO::HandleSetMap::iterator itHandleSetMap;
  std::wstring ws;

  for (itHandleSetMap = theAttributes.begin(); itHandleSetMap != theAttributes.end(); itHandleSetMap++)
  {
    ws = federateDB.supportingServicesLRC->getAttributeName(itHandleSetMap->first, theClass);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::checkAttributeNotDefined(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &theAttributes)
{
  CORBA::ULong i;
  CORBA::ULong len = theAttributes.length();
  std::wstring ws;

  for (i = 0; i < len; i++)
  {
    ws = federateDB.supportingServicesLRC->getAttributeName(theAttributes[i], theClass);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::checkAttributeNotDefined(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::HandleValues const &theAttributeValues)
{
  CORBA::ULong i;
  CORBA::ULong len = theAttributeValues.length();
  std::wstring ws;

  for (i = 0; i < len; i++)
  {
    ws = federateDB.supportingServicesLRC->getAttributeName(theAttributeValues[i].id, theClass);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::checkSaveRestore(void)
{
  CORBA::WChar *buff = L"";

  if (receiver->getRestoreInProgress())
  {
    throw GeRtiFactory::RestoreInProgress(buff);
  }
  if (receiver->getSaveInProgress())
  {
    throw GeRtiFactory::SaveInProgress(buff);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::getFactory ()
{
        #ifdef GalDebug
        E0(S_gF_e);
        #endif
  CORBA::WChar *wChar = L"";
  char *err = NULL;

  if (gotFactory)
  {
        #ifdef GalDebug
        E0(S_gF_l1);
        #endif
    return;
  }

  try
  {
    CosNaming::Name rtiName;
    rtiName.length (1);
    rtiName[0].id = CORBA::string_dup ("Factory");
    rtiName[0].kind = CORBA::string_dup ("");

    err = "While resolving the factory finder";
    CORBA::Object_var rti_obj = gerti_context->resolve (rtiName);

    err = "While narrowing the rti";
    theFactoryVar = GeRtiFactory::TheFactory::_narrow (rti_obj);
    // remarshal / demarshal
    CORBA::String_var cbstr = myGeRtiOrb->orbReceiver->object_to_string(theFactoryVar.in());
    CORBA::Object_var new_ior = myGeRtiOrb->orbSenderReliable->string_to_object(cbstr.in());
    theFactoryVar = GeRtiFactory::TheFactory::_narrow(new_ior.in());

    if (CORBA::is_nil (theFactoryVar.in ()))
    {
//      std::cerr << "       getFactory: " << err << std::endl;
    }
  }
  catch (...)
  {
        #ifdef GalDebug
        E0(S_gF_c1);
        #endif
    {
                                #ifdef GalDebug
        E0(S_gF_t1);
        #endif
      throw GeRtiFactory::RTIinternalError(wChar);
    }
  }

  gotFactory = true;
        #ifdef GalDebug
        E0(S_gF_l);
        #endif
  return;
}

// ---------------------------------------------------------------------------
// Get Federation Manager.
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::getFactoryVars(std::wstring const &theExecutionName)
{
  CORBA::WChar *executionName;
  GERTICO::Mapper::mapWcharFromWstring(&executionName, theExecutionName);
  fedManVar = theFactoryVar->getFederationManagement(executionName);
  // remarshal / demarshal
  CORBA::String_var cbstr = myGeRtiOrb->orbReceiver->object_to_string(fedManVar.in());
  CORBA::Object_var new_ior = myGeRtiOrb->orbSenderReliable->string_to_object(cbstr.in());
  fedManVar = GeRtiFactory::FederationManagement::_narrow(new_ior.in());
  CORBA::wstring_free(executionName);
}

// ---------------------------------------------------------------------------
// This method will send any local LRC information to gerti.
// It should only be called by the federate save complete method.
// NB. Most information in LRC is cached information.
// Time management data needs to be saved.
// Events not delivered to the application need to be saved.
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::save(std::string &theBuffer)
{
  // Initialize the XML4C2 system
  try
  {
    XERCES_CPP_NAMESPACE::XMLPlatformUtils::Initialize();
  }

  catch (const XERCES_CPP_NAMESPACE::XMLException &toCatch)
  {
    std::string s = "Error during Xerces-c Initialization: ";
    std::string t = StrX(toCatch.getMessage()).localForm ();
    std::wstring ws;

    s.append (t);
    GERTICO::Mapper::mapWstringFromChar(ws, s.c_str());
    throw GeRtiFactory::RTIinternalError(ws.c_str());
  }

  GERTICO::PrintFilter   *myFilter = 0;

  try
  {
    // get a serializer, an instance of DOMWriter
    XMLCh tempStr[100];
    XMLString::transcode("LS", tempStr, 99);
    DOMImplementation *impl          = DOMImplementationRegistry::getDOMImplementation(tempStr);
    DOMWriter         *theSerializer = ((DOMImplementationLS*)impl)->createDOMWriter();

    // set user specified end of line sequence and output encoding
    theSerializer->setNewLine(gMyEOLSequence);
    theSerializer->setEncoding(gOutputEncoding);

    // plug in user's own filter
    if (gUseFilter)
    {
      // even we say to show attribute, but the DOMWriter
      // will not show attribute nodes to the filter as
      // the specs explicitly says that DOMWriter shall
      // NOT show attributes to DOMWriterFilter.
      //
      // so DOMNodeFilter::SHOW_ATTRIBUTE has no effect.
      // same DOMNodeFilter::SHOW_DOCUMENT_TYPE, no effect.
      //
      myFilter = new GERTICO::PrintFilter(DOMNodeFilter::SHOW_ELEMENT   |
                                    DOMNodeFilter::SHOW_ATTRIBUTE |
                                    DOMNodeFilter::SHOW_DOCUMENT_TYPE);
      theSerializer->setFilter(myFilter);
    }

    // plug in user's own error handler
    DOMErrorHandler *myErrorHandler = new GERTICO::PrintErrorHandler();
    theSerializer->setErrorHandler(myErrorHandler);

    // set feature if the serializer supports the feature/mode
    if (theSerializer->canSetFeature(XMLUni::fgDOMWRTSplitCdataSections, gSplitCdataSections))
    {
      theSerializer->setFeature(XMLUni::fgDOMWRTSplitCdataSections, gSplitCdataSections);
    }

    if (theSerializer->canSetFeature(XMLUni::fgDOMWRTDiscardDefaultContent, gDiscardDefaultContent))
    {
      theSerializer->setFeature(XMLUni::fgDOMWRTDiscardDefaultContent, gDiscardDefaultContent);
    }

    if (theSerializer->canSetFeature(XMLUni::fgDOMWRTFormatPrettyPrint, gFormatPrettyPrint))
    {
      theSerializer->setFeature(XMLUni::fgDOMWRTFormatPrettyPrint, gFormatPrettyPrint);
    }

    if (theSerializer->canSetFeature(XMLUni::fgDOMWRTBOM, gWriteBOM))
    {
      theSerializer->setFeature(XMLUni::fgDOMWRTBOM, gWriteBOM);
    }

    //
    // Plug in a format target to receive the resultant
    // XML stream from the serializer.
    //
    // StdOutFormatTarget prints the resultant XML stream
    // to stdout once it receives any thing from the serializer.
    //
//    MemBufFormatTarget *memBufFormatTarget= new MemBufFormatTarget();

    XMLFormatTarget *myFormTarget = new MemBufFormatTarget();

    // get the DOM representation
    XMLString::transcode("saveLRC", tempStr, 99);
    DOMDocument                     *doc = impl->createDocument(
            0,                    // root element namespace URI.
            tempStr,         // root element name
            0);

    DOMElement* elemLevel0;
    DOMElement* rootElem = doc->getDocumentElement();

    // Save Secondary Time Master data
    XMLString::transcode(GERTICO::GeRtiFactory_GeRtiRestore_i::federationTimeStr.c_str(), tempStr, 99);
    elemLevel0 = doc->createElement(tempStr);
    rootElem->appendChild(elemLevel0);

    // Time management save.
    federateDB.timeManagementLRC->save(*doc, *elemLevel0);

    // Timed events have to be saved.
    receiver->save(*doc, *rootElem);

    // do the serialization through DOMWriter::writeNode();
    //
    theSerializer->writeNode(myFormTarget, *doc);
    size_t inte = ((MemBufFormatTarget *)myFormTarget)->getLen();
    const XMLByte *x = ((MemBufFormatTarget *)myFormTarget)->getRawBuffer();
    theBuffer = (const char*)x;
    delete theSerializer;

    //
    // Filter, formatTarget and error handler
    // are NOT owned by the serializer.
    //
    delete myFormTarget;
    delete myErrorHandler;

    if (gUseFilter)
    {
      delete myFilter;
    }
  }
  catch (XMLException& e)
  {
    std::string s = "Error occurred during creation of output transcoder: ";
    std::string t = StrX(e.getMessage()).localForm ();
    std::wstring ws;

    s.append (t);
    GERTICO::Mapper::mapWstringFromChar(ws, s.c_str());
    throw GeRtiFactory::RTIinternalError(ws.c_str ());
  }


  // And call the termination method
  XMLPlatformUtils::Terminate();

  delete gOutputEncoding;        // const problems.
  delete gMyEOLSequence;         // const problems.
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::createFederationExecution
(
  std::wstring const &theExecutionName,
  std::wstring const &theFED
)
{
        #ifdef GalDebug
  std::string executionName;
  std::string fed;
  GERTICO::Mapper::mapStringFromWstring(executionName, theExecutionName);
  GERTICO::Mapper::mapStringFromWstring(fed, theFED);
        E2(S_cFE_e,executionName.c_str(), fed.c_str());
        #endif
  CORBA::WChar *execName;
  CORBA::WChar *wFed;

  if (theFED.size() == 0)
  {
    throw GeRtiFactory::CouldNotOpenFED();
  }

  getFactory ();
  GERTICO::Mapper::mapWcharFromWstring(&execName, theExecutionName);
  GERTICO::Mapper::mapWcharFromWstring(&wFed, theFED);
  theFactoryVar->createFederationExecution(execName, wFed);
  getFactoryVars(theExecutionName);
  federateDB.FEDid = theFED;
  CORBA::wstring_free(execName);
  CORBA::wstring_free(wFed);
        #ifdef GalDebug
        E0(S_cFE_l);
        #endif
  return;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::destroyFederationExecution
(
  std::wstring const &theExecutionName
)
{
  CORBA::WChar *execName;
        #ifdef GalDebug
  std::string executionName;

  GERTICO::Mapper::mapStringFromWstring(executionName, theExecutionName);
        E1(S_dFE_e,executionName.c_str());
        #endif
  getFactory ();
  getFactoryVars(theExecutionName);
  GERTICO::Mapper::mapWcharFromWstring(&execName, theExecutionName);
  fedManVar->destroyFederationExecution(execName);
  CORBA::wstring_free(execName);
        #ifdef GalDebug
        E0(S_dFE_l);
        #endif
  return;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle NAMESPACE::Sender::joinFederationExecution
(
  std::wstring const &theYourName,
  std::wstring const &theExecutionName, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory
)
{
  CORBA::Object_var rti_obj;
  CORBA::WChar *eventHubName;
  CORBA::WChar *yName;
  CORBA::WChar *wChar = L"joinFederationExecution";
  std::string yourName;
  std::string executionName;
  GERTICO::Mapper::mapStringFromWstring(yourName, theYourName);
  GERTICO::Mapper::mapStringFromWstring(executionName, theExecutionName);
        #ifdef GalDebug
        E2(S_jFE_e,yourName.c_str(),executionName.c_str());
        #endif
  GeRtiFactory::EventChannel_var eventChannelVar;
  GeRtiFactory::GertiFmEvent gertiFmEvent;
  char name[64];
  int maxExceptions=0;

  if (federateDB.joined)
  {
    throw GeRtiFactory::FederateAlreadyExecutionMember(theYourName.c_str());
  }

  // Clear / init certain items.
  federateDB.ps->acquire();
  try
  {
  federateDB.clear();
  interactionHandleMap.clear();
  interactionHandleSet.clear();

  receiver->reset();

  // Create and activate child poa.
  sprintf(name, "POA%ud", GERTICO_POA_counter++);
  myPOA = myGeRtiOrb->poaRootReceiver->create_POA(name, nilMgr, policyListReceiver);
  myPOAMgr = myPOA->the_POAManager();
  myPOAMgr->activate();

  sprintf(name, "POA%ud", GERTICO_POA_counter++);
  myPOAbestEffort = myGeRtiOrb->poaRootSenderBestEffort->create_POA(name, nilMgr, policyListBestEffort);
  myPOAbestEffortMgr = myPOAbestEffort->the_POAManager();
  myPOAbestEffortMgr->activate();

  eventMarket = new GERTICO::EventMarket(federateDB.federate, theGeRtiFedTimeFactory);
  eventMarket->setPOA(myPOA.in(), myPOAbestEffort.in());
  eventMarket->setGERTICOconf(conf);
  timedArg.eventMarket = eventMarket;
  transmissionArg.eventMarket = eventMarket;

#ifdef IEEE_1516
  federateDB.federateType = theYourName;
#else
  federateDB.federateType = yourName;
#endif

  getFactory ();
  getFactoryVars(theExecutionName);

  if (geRtiRestore == NULL)
  {
    geRtiRestore = new GERTICO::GeRtiFactory_GeRtiRestore_i(myPOA, *eventMarket, *receiver, interactionHandleSet);
    geRtiRestoreVar = geRtiRestore->_this ();
  }

  if (fedAm == NULL)
  {
    fedAm = new GERTICO::GeRtiFactory_FederateAmbassador_i(myPOA, federateDB.registeredObjectsHolder, theGeRtiFedTimeFactory);
    fedAmbassadorReferenceVar = fedAm->_this ();
  }
  fedAm->setReceiver (receiver);
  }
  catch(...)
  {
    federateDB.ps->release();
    throw;
  }

  for (maxExceptions = 0;;maxExceptions++)
  {
    try
    {
      GERTICO::Mapper::mapWcharFromWstring(&yName, theYourName);
      GERTICO::Mapper::mapWcharFromWstring(&eventHubName, eventHubNameStr);
      federateDB.federate = fedManVar->joinFederationExecution(yName, eventHubName, fedAmbassadorReferenceVar, geRtiRestoreVar, eventHubFederationVar);
      joinedExecutionName = theExecutionName;
      CORBA::wstring_free(yName);
      CORBA::wstring_free(eventHubName);
      break;
    }
    catch (CORBA::SystemException &sysex)
    {
      CORBA::wstring_free(yName);
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < 2)
        {
          ACE_OS::sleep (ACE_Time_Value(0,500));
          continue;
        }
      }
      myPOAMgr->discard_requests(true);
      clear();
      myPOAMgr->deactivate(false, true);
      federateDB.ps->release();
      throw;
    }
    catch(...)
    {
      CORBA::wstring_free(yName);
      myPOAMgr->discard_requests(true);
      clear();
      myPOAMgr->deactivate(false, true);
      federateDB.ps->release();
      throw;
    }
  }
        #ifdef GalDebug
        E0(S_jFE_t0);
        #endif
  try
  {
  federateDB.joined = true;

  GeRtiAmb = GeRtiFactory::GeRtiAmbassador::_duplicate(fedManVar->getGeRtiAmbassador(federateDB.federate));
  // remarshal / demarshal
  CORBA::String_var cbstr = myGeRtiOrb->orbReceiver->object_to_string(GeRtiAmb.in());
  CORBA::Object_var new_ior = myGeRtiOrb->orbSenderReliable->string_to_object(cbstr.in());
  GeRtiAmb = GeRtiFactory::GeRtiAmbassador::_narrow(new_ior.in());

        #ifdef GalDebug
        E0(S_jFE_t1);
        #endif

  // Get supplier adminstration.
  // remarshal / demarshal
  try
  {
    eventHubFederationVar->getEventChannelAdmins(eventChannelVar, timeManagementVar);
    consumerAdminVar = GeRtiFactory::ConsumerAdmin::_duplicate(eventChannelVar->for_consumers());
    eventMarket->supplierAdminBestEffortVar = GeRtiFactory::SupplierAdmin::_duplicate(eventChannelVar->for_suppliers());
    eventMarket->supplierAdminReceiverVar = GeRtiFactory::SupplierAdmin::_duplicate(eventChannelVar->for_suppliers());
  }
  catch (...)
  {
        #ifdef GalDebug
        E0(S_gF_c1);
        #endif
        #ifdef GalDebug
        E0(S_gF_t1);
        #endif
      throw GeRtiFactory::RTIinternalError(wChar);
  }


  /*
  cbstr = myGeRtiOrb->orbReceiver->object_to_string(eventMarket->supplierAdminReceiverVar.in());
  new_ior = myGeRtiOrb->orbSender->string_to_object(cbstr.in());
  eventMarket->supplierAdminReceiverVar = GeRtiFactory::SupplierAdmin::_narrow(new_ior.in());
  cbstr = myGeRtiOrb->orbReceiver->object_to_string(eventMarket->supplierAdminBestEffortVar.in());
  new_ior = myGeRtiOrb->orbBestEffort->string_to_object(cbstr.in());
  eventMarket->supplierAdminBestEffortVar = GeRtiFactory::SupplierAdmin::_narrow(new_ior.in());
  */

  // remarshal / demarshal
  cbstr = myGeRtiOrb->orbReceiver->object_to_string(timeManagementVar.in());
  new_ior = myGeRtiOrb->orbSenderReliable->string_to_object(cbstr.in());
  timeManagementVar = GeRtiFactory::TimeManagement::_narrow(new_ior.in());

  // Supporting services.
  federateDB.supportingServicesLRC = new GERTICO::SupportingServicesLRC(GeRtiAmb);

  federateDB.timeManagementLRC = new GERTICO::TimeManagementLRC(federateDB.federate, theGeRtiFedTimeFactory, theGeRtiLogicalTimeIntervalFactory, timeManagementVar);
  federateDB.timeManagementLRC->setGeRtiAmbassador(GeRtiAmb);
  federateDB.timeManagementLRC->eventMarket = eventMarket;
  receiver->setTimeService(federateDB.timeManagementLRC);
  receiver->setGeRtiAmVar(GeRtiAmb);
  federateDB.declarationManagementLRC = new GERTICO::DeclarationManagementLRC(GeRtiAmb, federateDB.federate, federateDB.joined, *federateDB.runTimeObjectDB, interactionHandleSet, *receiver->eventHandler, *federateDB.supportingServicesLRC);
  federateDB.declarationManagementLRC->eventMarket = eventMarket;
  federateDB.dataDistributionManagementLRC = new GERTICO::DataDistributionManagementLRC(GeRtiAmb, federateDB.federate, *federateDB.runTimeObjectDB);
  federateDB.dataDistributionManagementLRC->eventMarket = eventMarket;

  // Publish the attributes.
  eventMarket->addPushSuppliers(federateDB.federate, *myGeRtiOrb);
  addPushConsumers(federateDB.federate, *myGeRtiOrb, *receiver, theGeRtiFedTimeFactory);
  gertiFmEvent.service = 0;
  gertiFmEvent.sourceId = federateDB.federate;
  eventMarket->addFmEvent(gertiFmEvent);

  geRtiRestore->setTimeService(federateDB.timeManagementLRC);

        #ifdef GalDebug
        E0(S_jFE_t3);
        #endif
  federateDB.runTimeObjectDB->setPrivilegeToDeleteId(GeRtiAmb->getPrivilegeToDeleteId ());
  federateDB.runTimeObjectDB->isGerti = false;
  // initialize OwnershipService
  federateDB.ownership = new GERTICO::OwnershipService(federateDB.federate, federateDB.registeredObjectsHolder, GeRtiAmb);
        #ifdef GalDebug
        E0(S_jFE_t4);
        #endif
//  eventMarket->setOwnershipService(federateDB.ownership);
        #ifdef GalDebug
        E0(S_jFE_t6);
        #endif
  federateDB.objectManagementLRC = new GERTICO::ObjectManagementLRC(GeRtiAmb, federateDB.federate, federateDB.registeredObjectsHolder, *federateDB.runTimeObjectDB, *federateDB.supportingServicesLRC);

  // Mom.
  managementObjectModelLRC = new GERTICO::ManagementObjectModelLRC(federateDB, this, theGeRtiFedTimeFactory, theGeRtiLogicalTimeIntervalFactory, *eventMarket, *receiver, *timedArg.ps);
  timedArg.federateDB = &federateDB;
  timedArg.toContinue = true;
  receiver->setMomLRC(managementObjectModelLRC);
  }
  catch(...)
  {
    federateDB.ps->release();
    throw;
  }
        #ifdef GalDebug
        E0(S_jFE_l);
        #endif
  GeRtiFactory::Handles_var momHandles;
  fedManVar->getMom(momHandles);

#ifdef IEEE_1516
  // NB: THE INDICES HERE MUST MATCH THOSE IN getMom() IN GERTI
  managementObjectModelLRC->managerObject = momHandles[0];
  managementObjectModelLRC->managerFederateObjectClass = momHandles[1];
  managementObjectModelLRC->managerFederateFederateHandle = momHandles[2];
  managementObjectModelLRC->managerFederateFederateType = momHandles[3];
  managementObjectModelLRC->managerFederateFederateHost = momHandles[4];
  managementObjectModelLRC->managerFederateRTIversion = momHandles[5];
  managementObjectModelLRC->managerFederateFDDid = momHandles[6];
  managementObjectModelLRC->managerFederateTimeConstrained = momHandles[7];
  managementObjectModelLRC->managerFederateTimeRegulating = momHandles[8];
  managementObjectModelLRC->managerFederateAsynchronousDelivery = momHandles[9];
  managementObjectModelLRC->managerFederateFederateState = momHandles[10];
  managementObjectModelLRC->managerFederateTimeManagerState = momHandles[11];
  managementObjectModelLRC->managerFederateLogicalTime = momHandles[12];
  managementObjectModelLRC->managerFederateLookahead = momHandles[13];
  managementObjectModelLRC->managerFederateGALT = momHandles[14];
  managementObjectModelLRC->managerFederateLITS = momHandles[15];
  managementObjectModelLRC->managerFederateROlength = momHandles[16];
  managementObjectModelLRC->managerFederateTSOlength = momHandles[17];
  managementObjectModelLRC->managerFederateReflectionsReceived = momHandles[18];
  managementObjectModelLRC->managerFederateUpdatesSent = momHandles[19];
  managementObjectModelLRC->managerFederateInteractionsReceived = momHandles[20];
  managementObjectModelLRC->managerFederateInteractionsSent = momHandles[21];
  managementObjectModelLRC->managerFederateObjectInstancesThatCanBeDeleted = momHandles[22];
  managementObjectModelLRC->managerFederateObjectInstancesUpdated = momHandles[23];
  managementObjectModelLRC->managerFederateObjectInstancesReflected = momHandles[24];
  managementObjectModelLRC->managerFederateObjectInstancesDeleted = momHandles[25];
  managementObjectModelLRC->managerFederateObjectInstancesRemoved = momHandles[26];
  managementObjectModelLRC->managerFederateObjectInstancesRegistered = momHandles[27];
  managementObjectModelLRC->managerFederateObjectInstancesDiscovered = momHandles[28];
  managementObjectModelLRC->managerInteractionFederate = momHandles[29];
  managementObjectModelLRC->managerInteractionFederateFederate = momHandles[30];
  managementObjectModelLRC->managerFederateAdjustSetTiming = momHandles[31];
  managementObjectModelLRC->managerFederateAdjustModifyAttributeState = momHandles[32];
  managementObjectModelLRC->managerFederateAdjustModifyAttributeStateObjectInstance = momHandles[33];
  managementObjectModelLRC->managerFederateAdjustModifyAttributeStateAttribute = momHandles[34];
  managementObjectModelLRC->managerFederateAdjustModifyAttributeStateAttributeState = momHandles[35];
  managementObjectModelLRC->managerFederateAdjustSetServiceReporting = momHandles[36];
  managementObjectModelLRC->managerFederateAdjustSetServiceReportingState = momHandles[37];
  managementObjectModelLRC->managerFederateAdjustSetExceptionLogging = momHandles[38];
  managementObjectModelLRC->managerFederateReportReflectionsReceived = momHandles[39];
  managementObjectModelLRC->managerFederateReportReflectionsReceivedTransportationType = momHandles[40];
  managementObjectModelLRC->managerFederateReportReflectionsReceivedReflectCounts = momHandles[41];
  managementObjectModelLRC->managerFederateReportInteractionsReceived = momHandles[42];
  managementObjectModelLRC->managerFederateReportInteractionsReceivedTransportationType = momHandles[43];
  managementObjectModelLRC->managerFederateReportInteractionsReceivedInteractionCounts = momHandles[44];
  managementObjectModelLRC->managerFederateReportException = momHandles[45];
  managementObjectModelLRC->managerFederateReportExceptionService = momHandles[46];
  managementObjectModelLRC->managerFederateReportExceptionException = momHandles[47];
  managementObjectModelLRC->managerFederateReportServiceInvocation = momHandles[48];
  managementObjectModelLRC->managerFederateReportServiceInvocationService = momHandles[49];
  managementObjectModelLRC->managerFederateReportServiceInvocationSuccessIndicator = momHandles[50];
  managementObjectModelLRC->managerFederateReportServiceInvocationSuppliedArguments = momHandles[51];
  managementObjectModelLRC->managerFederateReportServiceInvocationReturnedArguments = momHandles[52];
  managementObjectModelLRC->managerFederateReportServiceInvocationException = momHandles[53];
  managementObjectModelLRC->managerFederateReportServiceInvocationSerialNumber = momHandles[54];
  managementObjectModelLRC->managerFederateServiceResignFederationExecution = momHandles[55];
  managementObjectModelLRC->managerFederateServiceResignFederationExecutionResignAction = momHandles[56];
  managementObjectModelLRC->managerFederateServiceSynchronizationPointAchieved = momHandles[57];
  managementObjectModelLRC->managerFederateServiceSynchronizationPointAchievedLabel = momHandles[58];
  managementObjectModelLRC->managerFederateServiceFederateSaveBegun = momHandles[59];
  managementObjectModelLRC->managerFederateServiceFederateSaveComplete = momHandles[60];
  managementObjectModelLRC->managerFederateServiceFederateSaveCompleteSuccessIndicator = momHandles[61];
  managementObjectModelLRC->managerFederateServiceFederateRestoreComplete = momHandles[62];
  managementObjectModelLRC->managerFederateServiceFederateRestoreCompleteSuccessIndicator = momHandles[63];
  managementObjectModelLRC->managerFederateServicePublishObjectClassAttributes = momHandles[64];
  managementObjectModelLRC->managerFederateServicePublishObjectClassObjectClass = momHandles[65];
  managementObjectModelLRC->managerFederateServicePublishObjectClassAttributeList = momHandles[66];
  managementObjectModelLRC->managerFederateServiceUnpublishObjectClassAttributes = momHandles[67];
  managementObjectModelLRC->managerFederateServiceUnpublishObjectClassObjectClass = momHandles[68];
  managementObjectModelLRC->managerFederateServicePublishInteractionClass = momHandles[69];
  managementObjectModelLRC->managerFederateServicePublishInteractionClassInteractionClass = momHandles[70];
  managementObjectModelLRC->managerFederateServiceUnpublishInteractionClass = momHandles[71];
  managementObjectModelLRC->managerFederateServiceUnpublishInteractionClassInteractionClass = momHandles[72];
  managementObjectModelLRC->managerFederateServiceSubscribeObjectClassAttributes = momHandles[73];
  managementObjectModelLRC->managerFederateServiceSubscribeObjectClassAttributesObjectClass = momHandles[74];
  managementObjectModelLRC->managerFederateServiceSubscribeObjectClassAttributesAttributeList = momHandles[75];
  managementObjectModelLRC->managerFederateServiceSubscribeObjectClassAttributesActive = momHandles[76];
  managementObjectModelLRC->managerFederateServiceUnsubscribeObjectClassAttributes = momHandles[77];
  managementObjectModelLRC->managerFederateServiceUnsubscribeObjectClassObjectClass = momHandles[78];
  managementObjectModelLRC->managerFederateServiceSubscribeInteractionClass = momHandles[79];
  managementObjectModelLRC->managerFederateServiceSubscribeInteractionClassInteractionClass = momHandles[80];
  managementObjectModelLRC->managerFederateServiceSubscribeInteractionClassActive = momHandles[81];
  managementObjectModelLRC->managerFederateServiceUnsubscribeInteractionClass = momHandles[82];
  managementObjectModelLRC->managerFederateServiceUnsubscribeInteractionClassInteractionClass = momHandles[83];
  managementObjectModelLRC->managerFederateServiceDeleteObjectInstance = momHandles[84];
  managementObjectModelLRC->managerFederateServiceDeleteObjectInstanceObjectInstance = momHandles[85];
  managementObjectModelLRC->managerFederateServiceDeleteObjectInstanceTag = momHandles[86];
  managementObjectModelLRC->managerFederateServiceDeleteObjectInstanceTimeStamp = momHandles[87];
  managementObjectModelLRC->managerFederateServiceLocalDeleteObjectInstance = momHandles[88];
  managementObjectModelLRC->managerFederateServiceLocalDeleteObjectInstanceObjectInstance = momHandles[89];
  managementObjectModelLRC->managerFederateServiceChangeAttributeTransportationType = momHandles[90];
  managementObjectModelLRC->managerFederateServiceChangeAttributeTransportationTypeObjectInstance = momHandles[91];
  managementObjectModelLRC->managerFederateServiceChangeAttributeTransportationTypeAttributeList = momHandles[92];
  managementObjectModelLRC->managerFederateServiceChangeAttributeTransportationTypeTransportationType = momHandles[93];
  managementObjectModelLRC->managerFederateServiceChangeAttributeOrderType = momHandles[94];
  managementObjectModelLRC->managerFederateServiceChangeAttributeOrderTypeObjectInstance = momHandles[95];
  managementObjectModelLRC->managerFederateServiceChangeAttributeOrderTypeAttributeList = momHandles[96];
  managementObjectModelLRC->managerFederateServiceChangeAttributeOrderTypeOrderingType = momHandles[97];
  managementObjectModelLRC->managerFederateServiceChangeInteractionTransportationType = momHandles[98];
  managementObjectModelLRC->managerFederateServiceChangeInteractionOrderType = momHandles[99];
  managementObjectModelLRC->managerFederateServiceUnconditionalAttributeOwnershipDivestiture = momHandles[100];
  managementObjectModelLRC->managerFederateServiceUnconditionalAttributeOwnershipDivestitureObjectInstance = momHandles[101];
  managementObjectModelLRC->managerFederateServiceUnconditionalAttributeOwnershipDivestitureAttributeList = momHandles[102];
  managementObjectModelLRC->managerFederateServiceEnableTimeRegulation = momHandles[103];
  managementObjectModelLRC->managerFederateServiceEnableTimeRegulationLookahead = momHandles[104];
  managementObjectModelLRC->managerFederateServiceDisableTimeRegulation = momHandles[105];
  managementObjectModelLRC->managerFederateServiceEnableTimeConstrained = momHandles[106];
  managementObjectModelLRC->managerFederateServiceDisableTimeConstrained = momHandles[107];
  managementObjectModelLRC->managerFederateServiceEnableAsynchronousDelivery = momHandles[108];
  managementObjectModelLRC->managerFederateServiceDisableAsynchronousDelivery = momHandles[109];
  managementObjectModelLRC->managerFederateServiceModifyLookahead = momHandles[110];
  managementObjectModelLRC->managerFederateServiceModifyLookaheadLookahead = momHandles[111];
  managementObjectModelLRC->managerFederateServiceTimeAdvanceRequest = momHandles[112];
  managementObjectModelLRC->managerFederateServiceTimeAdvanceRequestTimeStamp = momHandles[113];
  managementObjectModelLRC->managerFederateServiceTimeAdvanceRequestAvailable = momHandles[114];
  managementObjectModelLRC->managerFederateServiceTimeAdvanceRequestAvailableTimeStamp = momHandles[115];
  managementObjectModelLRC->managerFederateServiceNextMessageRequest = momHandles[116];
  managementObjectModelLRC->managerFederateServiceNextMessageRequestTimeStamp = momHandles[117];
  managementObjectModelLRC->managerFederateServiceNextMessageRequestAvailable = momHandles[118];
  managementObjectModelLRC->managerFederateServiceNextMessageRequestAvailableTimeStamp = momHandles[119];
  managementObjectModelLRC->managerFederateServiceFlushQueueRequest = momHandles[120];
  managementObjectModelLRC->managerFederateServiceFlushQueueRequestTimeStamp = momHandles[121];
#else
  // NB: THE INDICES HERE MUST MATCH THOSE IN getMom() IN GERTI
  managementObjectModelLRC->managerObject = momHandles[0];
  managementObjectModelLRC->managerFederateObjectClass = momHandles[1];
  managementObjectModelLRC->managerFederateFederateHandle = momHandles[2];
  managementObjectModelLRC->managerFederateFederateType = momHandles[3];
  managementObjectModelLRC->managerFederateFederateHost = momHandles[4];
  managementObjectModelLRC->managerFederateRTIversion = momHandles[5];
  managementObjectModelLRC->managerFederateFEDid = momHandles[6];
  managementObjectModelLRC->managerFederateTimeConstrained = momHandles[7];
  managementObjectModelLRC->managerFederateTimeRegulating = momHandles[8];
  managementObjectModelLRC->managerFederateAsynchronousDelivery = momHandles[9];
  managementObjectModelLRC->managerFederateFederateState = momHandles[10];
  managementObjectModelLRC->managerFederateTimeManagerState = momHandles[11];
  managementObjectModelLRC->managerFederateFederateTime = momHandles[12];
  managementObjectModelLRC->managerFederateLookahead = momHandles[13];
  managementObjectModelLRC->managerFederateLBTS = momHandles[14];
  managementObjectModelLRC->managerFederateMinNextEventTime = momHandles[15];
  managementObjectModelLRC->managerFederateROlength = momHandles[16];
  managementObjectModelLRC->managerFederateTSOlength = momHandles[17];
  managementObjectModelLRC->managerFederateReflectionsReceived = momHandles[18];
  managementObjectModelLRC->managerFederateUpdatesSent = momHandles[19];
  managementObjectModelLRC->managerFederateInteractionsReceived = momHandles[20];
  managementObjectModelLRC->managerFederateInteractionsSent = momHandles[21];
  managementObjectModelLRC->managerFederateObjectsOwned = momHandles[22];
  managementObjectModelLRC->managerFederateObjectsUpdated = momHandles[23];
  managementObjectModelLRC->managerFederateObjectsReflected = momHandles[24];
  managementObjectModelLRC->managerInteractionFederate = momHandles[25];
  managementObjectModelLRC->managerInteractionFederateFederate = momHandles[26];
  managementObjectModelLRC->managerFederateAdjustSetTiming = momHandles[27];
  managementObjectModelLRC->managerFederateAdjustModifyAttributeState = momHandles[28];
  managementObjectModelLRC->managerFederateAdjustModifyAttributeStateObjectInstance = momHandles[29];
  managementObjectModelLRC->managerFederateAdjustModifyAttributeStateAttribute = momHandles[30];
  managementObjectModelLRC->managerFederateAdjustModifyAttributeStateAttributeState = momHandles[31];
  managementObjectModelLRC->managerFederateAdjustSetServiceReporting = momHandles[32];
  managementObjectModelLRC->managerFederateAdjustSetServiceReportingState = momHandles[33];
  managementObjectModelLRC->managerFederateAdjustSetExceptionLogging = momHandles[34];
  managementObjectModelLRC->managerFederateReportReflectionsReceived = momHandles[35];
  managementObjectModelLRC->managerFederateReportReflectionsReceivedTransportationType = momHandles[36];
  managementObjectModelLRC->managerFederateReportReflectionsReceivedReflectCounts = momHandles[37];
  managementObjectModelLRC->managerFederateReportInteractionsReceived = momHandles[38];
  managementObjectModelLRC->managerFederateReportInteractionsReceivedTransportationType = momHandles[39];
  managementObjectModelLRC->managerFederateReportInteractionsReceivedInteractionCounts = momHandles[40];
  managementObjectModelLRC->managerFederateReportAlert = momHandles[41];
  managementObjectModelLRC->managerFederateReportAlertAlertSeverity = momHandles[42];
  managementObjectModelLRC->managerFederateReportAlertAlertDescription = momHandles[43];
  managementObjectModelLRC->managerFederateReportAlertAlertID = momHandles[44];
  managementObjectModelLRC->managerFederateReportServiceInvocation = momHandles[45];
  managementObjectModelLRC->managerFederateReportServiceInvocationService = momHandles[46];
  managementObjectModelLRC->managerFederateReportServiceInvocationInitiator = momHandles[47];
  managementObjectModelLRC->managerFederateReportServiceInvocationSuccessIndicator = momHandles[48];
  managementObjectModelLRC->managerFederateReportServiceInvocationSuppliedArgument1 = momHandles[49];
  managementObjectModelLRC->managerFederateReportServiceInvocationSuppliedArgument2 = momHandles[50];
  managementObjectModelLRC->managerFederateReportServiceInvocationSuppliedArgument3 = momHandles[51];
  managementObjectModelLRC->managerFederateReportServiceInvocationSuppliedArgument4 = momHandles[52];
  managementObjectModelLRC->managerFederateReportServiceInvocationSuppliedArgument5 = momHandles[53];
  managementObjectModelLRC->managerFederateReportServiceInvocationReturnedArgument = momHandles[54];
  managementObjectModelLRC->managerFederateReportServiceInvocationExceptionDescription = momHandles[55];
  managementObjectModelLRC->managerFederateReportServiceInvocationExceptionID = momHandles[56];
  managementObjectModelLRC->managerFederateServiceResignFederationExecution = momHandles[57];
  managementObjectModelLRC->managerFederateServiceResignFederationExecutionResignAction = momHandles[58];
  managementObjectModelLRC->managerFederateServiceSynchronizationPointAchieved = momHandles[59];
  managementObjectModelLRC->managerFederateServiceSynchronizationPointAchievedLabel = momHandles[60];
  managementObjectModelLRC->managerFederateServiceFederateSaveBegun = momHandles[61];
  managementObjectModelLRC->managerFederateServiceFederateSaveComplete = momHandles[62];
  managementObjectModelLRC->managerFederateServiceFederateSaveCompleteSuccessIndicator = momHandles[63];
  managementObjectModelLRC->managerFederateServiceFederateRestoreComplete = momHandles[64];
  managementObjectModelLRC->managerFederateServiceFederateRestoreCompleteSuccessIndicator = momHandles[65];
  managementObjectModelLRC->managerFederateServicePublishObjectClass = momHandles[66];
  managementObjectModelLRC->managerFederateServicePublishObjectClassObjectClass = momHandles[67];
  managementObjectModelLRC->managerFederateServicePublishObjectClassAttributeList = momHandles[68];
  managementObjectModelLRC->managerFederateServiceUnpublishObjectClass = momHandles[69];
  managementObjectModelLRC->managerFederateServiceUnpublishObjectClassObjectClass = momHandles[70];
  managementObjectModelLRC->managerFederateServicePublishInteractionClass = momHandles[71];
  managementObjectModelLRC->managerFederateServicePublishInteractionClassInteractionClass = momHandles[72];
  managementObjectModelLRC->managerFederateServiceUnpublishInteractionClass = momHandles[73];
  managementObjectModelLRC->managerFederateServiceUnpublishInteractionClassInteractionClass = momHandles[74];
  managementObjectModelLRC->managerFederateServiceSubscribeObjectClassAttributes = momHandles[75];
  managementObjectModelLRC->managerFederateServiceSubscribeObjectClassAttributesObjectClass = momHandles[76];
  managementObjectModelLRC->managerFederateServiceSubscribeObjectClassAttributesAttributeList = momHandles[77];
  managementObjectModelLRC->managerFederateServiceSubscribeObjectClassAttributesActive = momHandles[78];
  managementObjectModelLRC->managerFederateServiceUnsubscribeObjectClass = momHandles[79];
  managementObjectModelLRC->managerFederateServiceUnsubscribeObjectClassObjectClass = momHandles[80];
  managementObjectModelLRC->managerFederateServiceSubscribeInteractionClass = momHandles[81];
  managementObjectModelLRC->managerFederateServiceSubscribeInteractionClassInteractionClass = momHandles[82];
  managementObjectModelLRC->managerFederateServiceSubscribeInteractionClassActive = momHandles[83];
  managementObjectModelLRC->managerFederateServiceUnsubscribeInteractionClass = momHandles[84];
  managementObjectModelLRC->managerFederateServiceUnsubscribeInteractionClassInteractionClass = momHandles[85];
  managementObjectModelLRC->managerFederateServiceDeleteObjectInstance = momHandles[86];
  managementObjectModelLRC->managerFederateServiceDeleteObjectInstanceObjectInstance = momHandles[87];
  managementObjectModelLRC->managerFederateServiceDeleteObjectInstanceTag = momHandles[88];
  managementObjectModelLRC->managerFederateServiceDeleteObjectInstanceFederationTime = momHandles[89];
  managementObjectModelLRC->managerFederateServiceLocalDeleteObjectInstance = momHandles[90];
  managementObjectModelLRC->managerFederateServiceLocalDeleteObjectInstanceObjectInstance = momHandles[91];
  managementObjectModelLRC->managerFederateServiceChangeAttributeTransportationType = momHandles[92];
  managementObjectModelLRC->managerFederateServiceChangeAttributeTransportationTypeObjectInstance = momHandles[93];
  managementObjectModelLRC->managerFederateServiceChangeAttributeTransportationTypeAttributeList = momHandles[94];
  managementObjectModelLRC->managerFederateServiceChangeAttributeTransportationTypeTransportationType = momHandles[95];
  managementObjectModelLRC->managerFederateServiceChangeAttributeOrderType = momHandles[96];
  managementObjectModelLRC->managerFederateServiceChangeAttributeOrderTypeObjectInstance = momHandles[97];
  managementObjectModelLRC->managerFederateServiceChangeAttributeOrderTypeAttributeList = momHandles[98];
  managementObjectModelLRC->managerFederateServiceChangeAttributeOrderTypeOrderingType = momHandles[99];
  managementObjectModelLRC->managerFederateServiceChangeInteractionTransportationType = momHandles[100];
  managementObjectModelLRC->managerFederateServiceChangeInteractionOrderType = momHandles[101];
  managementObjectModelLRC->managerFederateServiceUnconditionalAttributeOwnershipDivestiture = momHandles[102];
  managementObjectModelLRC->managerFederateServiceUnconditionalAttributeOwnershipDivestitureObjectInstance = momHandles[103];
  managementObjectModelLRC->managerFederateServiceUnconditionalAttributeOwnershipDivestitureAttributeList = momHandles[104];
  managementObjectModelLRC->managerFederateServiceEnableTimeRegulation = momHandles[105];
  managementObjectModelLRC->managerFederateServiceEnableTimeRegulationFederationTime = momHandles[106];
  managementObjectModelLRC->managerFederateServiceEnableTimeRegulationLookahead = momHandles[107];
  managementObjectModelLRC->managerFederateServiceDisableTimeRegulation = momHandles[108];
  managementObjectModelLRC->managerFederateServiceEnableTimeConstrained = momHandles[109];
  managementObjectModelLRC->managerFederateServiceDisableTimeConstrained = momHandles[110];
  managementObjectModelLRC->managerFederateServiceEnableAsynchronousDelivery = momHandles[111];
  managementObjectModelLRC->managerFederateServiceDisableAsynchronousDelivery = momHandles[112];
  managementObjectModelLRC->managerFederateServiceModifyLookahead = momHandles[113];
  managementObjectModelLRC->managerFederateServiceModifyLookaheadLookahead = momHandles[114];
  managementObjectModelLRC->managerFederateServiceTimeAdvanceRequest = momHandles[115];
  managementObjectModelLRC->managerFederateServiceTimeAdvanceRequestFederationTime = momHandles[116];
  managementObjectModelLRC->managerFederateServiceTimeAdvanceRequestAvailable = momHandles[117];
  managementObjectModelLRC->managerFederateServiceTimeAdvanceRequestAvailableFederationTime = momHandles[118];
  managementObjectModelLRC->managerFederateServiceNextEventRequest = momHandles[119];
  managementObjectModelLRC->managerFederateServiceNextEventRequestFederationTime = momHandles[120];
  managementObjectModelLRC->managerFederateServiceNextEventRequestAvailable = momHandles[121];
  managementObjectModelLRC->managerFederateServiceNextEventRequestAvailableFederationTime = momHandles[122];
  managementObjectModelLRC->managerFederateServiceFlushQueueRequest = momHandles[123];
  managementObjectModelLRC->managerFederateServiceFlushQueueRequestFederationTime = momHandles[124];
#endif
  federateDB.ps->release();
  fedManVar->joinFederationExecutionFinished(federateDB.federate);
  return federateDB.federate;
}


// Process linked list of channels.
void NAMESPACE::Sender::sendEvents ()
{
        #ifdef GalDebug
        E0(S_sE_e);
        #endif
  eventMarket->sendEvents();
        #ifdef GalDebug
        E0(S_sE_l);
        #endif
}

bool NAMESPACE::Sender::tickWork(bool const &useTimers, double const &minimum, double const &maximum)
{
        #ifdef GalDebug
        E0(S_tW_e);
        #endif
  CORBA::WChar *wChar = L"tickWork";
  bool ret;

  try
  {
    std::auto_ptr<GERTICO::GeRtiFedTime> logicalTime(federateDB.timeManagementLRC->geRtiFedTimeFactory.makeZero());
    sendEvents();

    federateDB.timeManagementLRC->queryLogicalTime(*logicalTime);
    federateDB.processDeleteObjectWithTime(*logicalTime);

    if (receiver)
    {
      if (useTimers)
      {
        ACE_High_Res_Timer cStopWatch;
        ACE_Time_Value tv;
        ACE_Time_Value tvMax;
        ACE_Time_Value tvMin;

        tvMax.set(maximum);
        tvMin.set(minimum);

        // Get a reference for start time.
        cStopWatch.start();
        for (;;)
        {
          ret = receiver->process(false);
          cStopWatch.stop();
          cStopWatch.elapsed_time(tv);
          // Check if minimum has not been reached.
          if (tv < tvMin)
          {
            continue;
          }
          // Check if maximum has expired.
          if (tv > tvMax)
          {
            break;
          }
          // If nothing to do, leave.
          if (ret == false)
          {
            break;
          }
        }
      }
      else
      {
#ifdef IEEE_1516
        // Return after one attempt.
        ret = receiver->process(false);
#else
        // Return after all processed.
        ret = receiver->process(true);
#endif
      }
    }
  }
  catch(...)
  {
    throw GeRtiFactory::RTIinternalError(wChar);
  }
        #ifdef GalDebug
        E0(S_tW_l);
        #endif

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::resignFederationExecution (GeRtiFactory::ResignAction theAction)
throw
(
  GeRtiFactory::FederateOwnsAttributes,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::InvalidResignAction,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError
)
{
        #ifdef GalDebug
        E0(S_rFE_e);
        #endif
  GeRtiFactory::GertiFmEvent gertiFmEvent;

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
          E0(S_rFE_t1);
          #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  // Important to get the right federation.
  getFactoryVars(joinedExecutionName);

  gertiFmEvent.service = 1;
  gertiFmEvent.sourceId = federateDB.federate;
  eventMarket->addFmEvent(gertiFmEvent);
  eventMarket->sendEvents();

  try
  {
    fedManVar->resignFederationExecution(theAction, federateDB.federate);
  }
  catch(GeRtiFactory::FederateOwnsAttributes)
  {
    throw;
  }
  catch(GeRtiFactory::ConcurrentAccessAttempted)
  {
    throw;
  }
  catch(GeRtiFactory::InvalidResignAction)
  {
    throw;
  }
  federateDB.joined = false;
  myPOAMgr->discard_requests(true);
  federateDB.clear();

  clear();
  myPOAMgr->deactivate(false, true);
        #ifdef GalDebug
        E0(S_rFE_l);
        #endif
}

////////////////////////////////////
// Federation Management Services //
////////////////////////////////////

// 4.6
void NAMESPACE::Sender::registerFederationSynchronizationPoint(
  std::wstring const &theLabel,
  GeRtiFactory::UserSuppliedTag const &theTag)
throw (
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
  CORBA::WChar *label;
  GERTICO::Mapper::mapWcharFromWstring(&label, theLabel);
        #ifdef GalDebug
        E1(S_rFSP1_e,label);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_rFSP1_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  bool b = true;

  while (b)
  {
    try
    {
      GeRtiAmb->registerFederationSynchronizationPoint (label, theTag);
      CORBA::wstring_free(label);
    }
    catch (CORBA::SystemException &sysex)
    {
      CORBA::wstring_free(label);
      if (sysex.completed () == CORBA::COMPLETED_NO)
      {
        continue;
      }
      else
      {
        #ifdef GalDebug
        E0(S_rFSP1_t2);
        #endif
        ACE_PRINT_EXCEPTION (sysex, "System Exception");
        throw;
      }
    }

    b = false;
  }
        #ifdef GalDebug
        E0(S_rFSP1_l);
        #endif
}

void NAMESPACE::Sender::registerFederationSynchronizationPoint(
  std::wstring const &theLabel,
  GeRtiFactory::UserSuppliedTag const &theTag,
  GeRtiFactory::Handles const &designators)
throw (
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
  CORBA::WChar *label;
  GERTICO::Mapper::mapWcharFromWstring(&label, theLabel);
        #ifdef GalDebug
        E1(S_rFSP2_q,label);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_rFSP2_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  GeRtiAmb->registerFederationSynchronizationPointWithDesignators (label, theTag, designators);
  CORBA::wstring_free(label);
}

// 4.9
void NAMESPACE::Sender::synchronizationPointAchieved(
  std::wstring const &theLabel)
throw (
  GeRtiFactory::SynchronizationPointLabelWasNotAnnounced,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
  CORBA::WChar *label;
  GERTICO::Mapper::mapWcharFromWstring(&label, theLabel);
        #ifdef GalDebug
        E1(S_sPA_e,label);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_sPA_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  bool b = true;

  while (b)
  {
    try
    {
      GeRtiAmb->synchronizationPointAchieved (label);
      CORBA::wstring_free(label);
    }
    catch (CORBA::SystemException &sysex)
    {
      CORBA::wstring_free(label);
      if (sysex.completed () == CORBA::COMPLETED_NO)
      {
        continue;
      }
      else
      {
        #ifdef GalDebug
        E0(S_sPA_t2);
        #endif
        ACE_PRINT_EXCEPTION (sysex, "System Exception");
        throw;
      }
    }

    b = false;
  }
        #ifdef GalDebug
        E0(S_sPA_l);
        #endif
}

// ---------------------------------------------------------------------------
// 4.11
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::requestFederationSave(
  std::wstring const &theLabel,
  GERTICO::GeRtiFedTime const &theTime)
throw (
  GeRtiFactory::FederationTimeAlreadyPassed,
  GeRtiFactory::InvalidFederationTime,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
  CORBA::WChar *label;
  GeRtiFactory::Time t;

  if (federateDB.joined == false)
  {
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  federateDB.timeManagementLRC->testRequestTime(theTime);
  GERTICO::ConvertTime::mapIt (t, theTime);
  GERTICO::Mapper::mapWcharFromWstring(&label, theLabel);
  GeRtiAmb->requestFederationSaveWithTime (label, t);
  receiver->addInitiateFederateSaveWithTime(theLabel, theTime);
  CORBA::wstring_free(label);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::requestFederationSave(
  std::wstring const &theLabel)
throw (
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
  CORBA::WChar *label;

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_rFS2_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  GERTICO::Mapper::mapWcharFromWstring(&label, theLabel);
  GeRtiAmb->requestFederationSave (label);
  receiver->addInitiateFederateSave(theLabel);
  CORBA::wstring_free(label);
}

// ---------------------------------------------------------------------------
// 4.13
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::federateSaveBegun()
throw (
  GeRtiFactory::SaveNotInitiated,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_fSB_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_fSB_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  GeRtiAmb->federateSaveBegun ();
  receiver->federateSaveBegun();
}

// ---------------------------------------------------------------------------
// 4.14
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::federateSaveComplete(CORBA::Boolean success)
throw (
  GeRtiFactory::SaveNotInitiated,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_fSC_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_fSC_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  std::string s;

  // Save local LRC data if application says success.
  if (success)
  {
    save(s);
  }

  GeRtiAmb->federateSaveComplete(success, s.c_str());
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::queryFederationSaveStatus()
throw (
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
  CORBA::WChar *buff = L"";

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_fRC_t1);
        #endif
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  if (receiver->getRestoreInProgress())
  {
    throw GeRtiFactory::RestoreInProgress(buff);
  }

  GeRtiAmb->queryFederationSaveStatus();
}

// ---------------------------------------------------------------------------
// 4.16
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::requestFederationRestore(
  std::wstring const &theLabel)
throw (
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_rFR_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  CORBA::WChar *label;
  GERTICO::Mapper::mapWcharFromWstring(&label, theLabel);
  GeRtiAmb->requestFederationRestore (label);
  CORBA::wstring_free(label);
}

// 4.20
void NAMESPACE::Sender::federateRestoreComplete(CORBA::Boolean success)
throw (
  GeRtiFactory::RestoreNotRequested,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_fRC_q);
        #endif
  CORBA::WChar *buff = L"";

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_fRC_t1);
        #endif
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  if (receiver->getSaveInProgress())
  {
    throw GeRtiFactory::SaveInProgress(buff);
  }

  GeRtiAmb->federateRestoreComplete (success);
}

void NAMESPACE::Sender::queryFederationRestoreStatus()
throw (
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RTIinternalError)
{
  CORBA::WChar *buff = L"";

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_fRC_t1);
        #endif
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  if (receiver->getSaveInProgress())
  {
    throw GeRtiFactory::SaveInProgress(buff);
  }

  GeRtiAmb->queryFederationRestoreStatus();
}

/////////////////////////////////////
// Declaration Management Services //
/////////////////////////////////////

// 5.2
void NAMESPACE::Sender::publishObjectClass
(
  GeRtiFactory::GeRtiHandle  theClass,
  GeRtiFactory::Handles const &attributeList
)
throw
(
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::OwnershipAcquisitionPending,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError
)
{
        #ifdef GalDebug
        E0(S_pOC_e);
        #endif
  CORBA::ULong len = attributeList.length();
  GERTICO::AttributeInfo* info;
  GERTICO::HandleSet attributeSet;
  GERTICO::HandleSet attributeSetDropped;
  GERTICO::HandleSet attributeSetPrev;
  GERTICO::HandleSet objects;
  GERTICO::HandleSet::iterator itAttributeSet;
  GERTICO::HandleSet::iterator itAttributeSetDropped;
  GERTICO::HandleSet::iterator itAttributeSetPrev;
  GERTICO::HandleSet::iterator itObject;
  GERTICO::RegisteredObject *object;
  GeRtiFactory::GeRtiHandle privilegeToDeleteId;

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_pOC_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  // Test for attribute not defined.
  checkAttributeNotDefined(theClass, attributeList);

  // Get previously published attributes.
  try
  {
    federateDB.declarationManagementLRC->getPublishedAttributes(theClass, attributeSetPrev);
  }
  catch(...)
  {
  }

  GERTICO::Mapper::mapHandleSet(attributeSet, attributeList);
  federateDB.declarationManagementLRC->publishObjectClass(theClass, attributeSet);

  // Check if previously published attributes are no longer published
  // If yes, set ownership of these attributes to unowned,
  privilegeToDeleteId = federateDB.runTimeObjectDB->getPrivilegeToDeleteId();
  for (itAttributeSetPrev = attributeSetPrev.begin(); itAttributeSetPrev != attributeSetPrev.end(); itAttributeSetPrev++)
  {
    if (*itAttributeSetPrev == privilegeToDeleteId)
    {
      continue;
    }
    itAttributeSet = attributeSet.find(*itAttributeSetPrev);
    if (itAttributeSet == attributeSet.end())
    {
      attributeSetDropped.insert(*itAttributeSetPrev);
    }
  }

  // Get the objects
  federateDB.objectManagementLRC->getObjectsForClass(theClass, objects);

  // Set the object attributes to unowned
  for (itObject = objects.begin(); itObject != objects.end(); itObject++)
  {
    try
    {
      object = federateDB.objectManagementLRC->getObject(*itObject);
      for (itAttributeSetDropped = attributeSetDropped.begin(); itAttributeSetDropped != attributeSetDropped.end(); itAttributeSetDropped++)
      {
        info = object->getAttribute(*itAttributeSetDropped);
        info->setStatusUnowned();
      }
    }
    catch(...)
    {
    }
  }
        #ifdef GalDebug
        E0(S_pOC_l);
        #endif
}

// 5.3
void NAMESPACE::Sender::unpublishObjectClass(
  GeRtiFactory::GeRtiHandle theClass)
throw (
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::ObjectClassNotPublished,
  GeRtiFactory::OwnershipAcquisitionPending,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_uOC1_e);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_uOC1_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }
  GERTICO::AttributeInfo* info;
  GERTICO::RegisteredObject *object;
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet objects;
  GERTICO::HandleSet::iterator itAttribute;
  GERTICO::HandleSet::iterator itObject;

  checkSaveRestore();

  federateDB.declarationManagementLRC->unpublishObjectClass(theClass);

  federateDB.objectManagementLRC->getObjectsForClass(theClass, objects);

  for (itObject = objects.begin(); itObject != objects.end(); itObject++)
  {
    try
    {
      object = federateDB.objectManagementLRC->getObject(*itObject);
      object->getAttributeIds(attributes);
      for (itAttribute = attributes.begin(); itAttribute != attributes.end(); itAttribute++)
      {
        info = object->getAttribute(*itAttribute);
        info->setStatusUnowned();
      }
    }
    catch(...)
    {
    }
  }
        #ifdef GalDebug
        E0(S_uOC1_l);
        #endif
}

void NAMESPACE::Sender::unpublishObjectClassAttributes(
  GeRtiFactory::GeRtiHandle const &theClass,
  GeRtiFactory::Handles const &theAttributes)
throw(
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::OwnershipAcquisitionPending,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_uOC1_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  // Test for attribute not defined.
  checkAttributeNotDefined(theClass, theAttributes);

  federateDB.declarationManagementLRC->unpublishObjectClassAttributes(theClass, theAttributes);
}

// 5.4
void NAMESPACE::Sender::publishInteractionClass(
  GeRtiFactory::GeRtiHandle theInteraction)
throw (
  GeRtiFactory::InteractionClassNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_pIC_e);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_pIC_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  federateDB.declarationManagementLRC->publishInteractionClass(theInteraction);
        #ifdef GalDebug
        E0(S_pIC_l);
        #endif
}

// 5.5
void NAMESPACE::Sender::unpublishInteractionClass(
  GeRtiFactory::GeRtiHandle theInteraction)
throw (
  GeRtiFactory::InteractionClassNotDefined,
  GeRtiFactory::InteractionClassNotPublished,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_uIC1_e);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_uIC1_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }
  checkSaveRestore();

  federateDB.declarationManagementLRC->unpublishInteractionClass(theInteraction);
        #ifdef GalDebug
        E0(S_uIC1_l);
        #endif
}

// 5.6
void NAMESPACE::Sender::subscribeObjectClassAttributes
(
  GeRtiFactory::GeRtiHandle theClass,
  GeRtiFactory::Handles const &attributeList,
  CORBA::Boolean active
)
throw
(
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError
)
{
        #ifdef GalDebug
        E0(S_sOCA_e);
        #endif
  GERTICO::HandleSet attributeSet;
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_sOCA_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  // Test for known class.
  std::wstring dummy = federateDB.supportingServicesLRC->getObjectClassName(theClass);

  // Test for attribute not defined.
  checkAttributeNotDefined(theClass, attributeList);

  GERTICO::Mapper::mapHandleSet(attributeSet, attributeList);
  federateDB.declarationManagementLRC->subscribeObjectClassAttributes(theClass, attributeSet, active);
        #ifdef GalDebug
        E0(S_sOCA_l);
        #endif
}

// 5.7
void NAMESPACE::Sender::unsubscribeObjectClass(
  GeRtiFactory::GeRtiHandle const &theClass)
throw (
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::ObjectClassNotSubscribed,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_uOC2_e);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_uOC2_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  // Test for known class.
  std::wstring dummy = federateDB.supportingServicesLRC->getObjectClassName(theClass);

  federateDB.declarationManagementLRC->unsubscribeObjectClass(theClass);
        #ifdef GalDebug
        E0(S_uOC2_l);
        #endif
}

void NAMESPACE::Sender::unsubscribeObjectClassAttributes(
  GeRtiFactory::GeRtiHandle const &theClass,
  GeRtiFactory::Handles const &theAttributes)
throw (
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_uOC2_e);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_uOC2_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  // Test for known class.
  std::wstring dummy = federateDB.supportingServicesLRC->getObjectClassName(theClass);

  // Test for attribute not defined.
  checkAttributeNotDefined(theClass, theAttributes);

  federateDB.declarationManagementLRC->unsubscribeObjectClassAttributes(theClass, theAttributes);
        #ifdef GalDebug
        E0(S_uOC2_l);
        #endif
}


// 5.8
void NAMESPACE::Sender::subscribeInteractionClass(
  GeRtiFactory::GeRtiHandle theClass,
  CORBA::Boolean active)
throw (
  GeRtiFactory::InteractionClassNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::FederateLoggingServiceCalls,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
  std::wstring ws;

        #ifdef GalDebug
        E0(S_sIC_e);
        #endif

    if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_sIC_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  ws = federateDB.supportingServicesLRC->getInteractionClassName(theClass);

  federateDB.declarationManagementLRC->subscribeInteractionClass(theClass, active);
        #ifdef GalDebug
        E0(S_sIC_l);
        #endif
}

// 5.9
void NAMESPACE::Sender::unsubscribeInteractionClass(
  GeRtiFactory::GeRtiHandle theClass)
throw (
  GeRtiFactory::InteractionClassNotDefined,
  GeRtiFactory::InteractionClassNotSubscribed,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
  std::wstring ws;

        #ifdef GalDebug
        E0(S_uIC2_e);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_uIC2_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  ws = federateDB.supportingServicesLRC->getInteractionClassName(theClass);

  // Subscribe to interaction class.
  federateDB.declarationManagementLRC->unsubscribeInteractionClass(theClass);
        #ifdef GalDebug
        E0(S_uIC2_l);
        #endif
}

////////////////////////////////
// Object Management Services //
////////////////////////////////

void NAMESPACE::Sender::reserveObjectInstanceName(
  std::wstring const &theObjectInstanceName)
throw(
  GeRtiFactory::IllegalName,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
  if (federateDB.joined == false)
  {
    CORBA::WChar *buff = L"Federate not joined";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  federateDB.objectManagementLRC->reserveObjectInstanceName(theObjectInstanceName);
}

// 6.2
GeRtiFactory::GeRtiHandle
NAMESPACE::Sender::registerObjectInstance(
  GeRtiFactory::GeRtiHandle  theClass,
  std::wstring const &theObjectName)
throw (
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::ObjectClassNotPublished,
  GeRtiFactory::ObjectAlreadyRegistered,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_rOI1_e);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_rOI1_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  GeRtiFactory::GeRtiHandle objectId;

  checkSaveRestore();

        #ifdef GalDebug
        E0(S_rOI1_l);
        #endif
  objectId = federateDB.objectManagementLRC->registerObjectInstance(federateDB.federate, theClass, theObjectName);

  federateDB.addRegisterObjectInstance(objectId, theClass);

  return objectId;
}

GeRtiFactory::GeRtiHandle
NAMESPACE::Sender::registerObjectInstance(
  GeRtiFactory::GeRtiHandle theClass)
throw (
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::ObjectClassNotPublished,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_rOI2_e);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_rOI2_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  GeRtiFactory::GeRtiHandle objectId;

  checkSaveRestore();

        #ifdef GalDebug
        E0(S_rOI2_l);
        #endif
  objectId = federateDB.objectManagementLRC->registerObjectInstance(federateDB.federate, theClass);

  federateDB.addRegisterObjectInstance(objectId, theClass);

  return objectId;
}

// 6.4
GeRtiFactory::ERHandle
NAMESPACE::Sender::updateAttributeValues
(
  GeRtiFactory::GeRtiHandle const &theObject,
  GeRtiFactory::HandleValues &theAttributes,
  GERTICO::GeRtiFedTime const &theTime,
  GeRtiFactory::UserSuppliedTag const &theTag
)
throw
(
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::AttributeNotOwned,
  GeRtiFactory::InvalidFederationTime,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError
)
{
        #ifdef GalDebug
        E0(S_uAV1_e);
        #endif
  CORBA::ULong i;
  CORBA::ULong len;
  CORBA::WChar *wChar = L"";
  std::auto_ptr<GERTICO::GeRtiFedTime> logicalTime(federateDB.timeManagementLRC->geRtiFedTimeFactory.makeZero());
  GERTICO::RegisteredObject *registeredObject;
  GeRtiFactory::ERHandle h;
  GeRtiFactory::GeRtiHandle knownObjectClass;
  GeRtiFactory::GeRtiHandle myClass;

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_uAV1_t1);
        #endif
    throw GeRtiFactory::FederateNotExecutionMember(wChar);
  }

  checkSaveRestore();

  knownObjectClass = federateDB.objectManagementLRC->getObjectClass(theObject);

  // Test for attribute not defined.
  checkAttributeNotDefined(knownObjectClass, theAttributes);

  // Maybe object has been deleted with time.
  federateDB.timeManagementLRC->queryLogicalTime(*logicalTime);
  federateDB.processDeleteObjectWithTime(*logicalTime, theObject);
  registeredObject = federateDB.registeredObjectsHolder.getObject(theObject);
  myClass = registeredObject->getClassId();

  h.theSerialNumber = retractionHandleCounter++;
  h.sendingFederate = federateDB.federate;
  receiver->addRetractionHandle(h, theTime);

  len = theAttributes.length();
  for (i = 0; i < len; i++)
  {
    if (federateDB.ownership->isAttributeOwnedByFederate(theObject, theAttributes[i].id) == false)
    {
      throw GeRtiFactory::AttributeNotOwned(wChar);
    }
  }

  federateDB.objectManagementLRC->setAttributeData(theObject, theAttributes);

  if (federateDB.timeManagementLRC->isTimeRegulation())
  {
    std::auto_ptr<GERTICO::GeRtiFedTime> l(federateDB.timeManagementLRC->geRtiFedTimeFactory.makeZero());
    std::auto_ptr<GERTICO::GeRtiFedTime> z(federateDB.timeManagementLRC->geRtiFedTimeFactory.makeZero());

    federateDB.timeManagementLRC->testSendTime(theTime);

    eventMarket->addPushSupplierObject(theObject, myClass, theAttributes, theTime, theTag, h.theSerialNumber);
  }
  else
  {
    eventMarket->addPushSupplierObject(theObject, myClass, theAttributes, theTag);
  }

  transmissionArg.ps->release();

        #ifdef GalDebug
        E0(S_uAV1_l);
        #endif
  return h;
}

void NAMESPACE::Sender::updateAttributeValues
(
  GeRtiFactory::GeRtiHandle const &theObject,
  GeRtiFactory::HandleValues &theAttributes,
  GeRtiFactory::UserSuppliedTag const &theTag
)
throw
(
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::AttributeNotOwned,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError
)
{
        #ifdef GalDebug
        E0(S_uAV2_e);
        #endif
  CORBA::WChar *wChar = L"updateAttributeValues";
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_uAV2_t1);
        #endif
    throw GeRtiFactory::FederateNotExecutionMember(wChar);
  }
  std::auto_ptr<GERTICO::GeRtiFedTime> logicalTime(federateDB.timeManagementLRC->geRtiFedTimeFactory.makeZero());
  CORBA::ULong i;
  CORBA::ULong len;
  GeRtiFactory::GeRtiHandle knownObjectClass;

  checkSaveRestore();

  // Maybe object has been deleted with time.
  federateDB.timeManagementLRC->queryLogicalTime(*logicalTime);
  federateDB.processDeleteObjectWithTime(*logicalTime, theObject);

  knownObjectClass = federateDB.objectManagementLRC->getObjectClass(theObject);

  // Test for attribute not defined.
  checkAttributeNotDefined(knownObjectClass, theAttributes);
  len = theAttributes.length();
  for (i = 0; i < len; i++)
  {
    if (federateDB.ownership->isAttributeOwnedByFederate(theObject, theAttributes[i].id) == false)
    {
      throw GeRtiFactory::AttributeNotOwned(wChar);
    }
  }

  federateDB.objectManagementLRC->setAttributeData(theObject, theAttributes);

  eventMarket->addPushSupplierObject(theObject, knownObjectClass, theAttributes, theTag);

  transmissionArg.ps->release();

        #ifdef GalDebug
        E0(S_uAV2_l);
        #endif
}

// ---------------------------------------------------------------------------
// 6.6
// ---------------------------------------------------------------------------
GeRtiFactory::ERHandle
NAMESPACE::Sender::sendInteraction(
  GeRtiFactory::GeRtiHandle const &theInteraction,
  GeRtiFactory::HandleValues const &theParameters,
  GERTICO::GeRtiFedTime const &theTime,
  GeRtiFactory::UserSuppliedTag const &theTag)
throw (
  GeRtiFactory::InteractionClassNotDefined,
  GeRtiFactory::InteractionClassNotPublished,
  GeRtiFactory::InteractionParameterNotDefined,
  GeRtiFactory::InvalidFederationTime,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_sI1_e);
        #endif
  GERTICO::AttributeDatum interactionDatum;
  std::wstring ws;

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_sI1_t1);
        #endif
    CORBA::WChar *wChar = L"sendInteraction";
    throw GeRtiFactory::FederateNotExecutionMember(wChar);
  }
  CORBA::ULong i;
  CORBA::ULong len = theParameters.length();

  checkSaveRestore();

  if (federateDB.declarationManagementLRC->isPublishingInteraction(theInteraction) == false)
  {
    ws = federateDB.supportingServicesLRC->getInteractionClassName(theInteraction);
    throw GeRtiFactory::InteractionClassNotPublished(L"sendInteraction");
  }

  if (federateDB.supportingServicesLRC->getInteractionAttributeDatum(theInteraction, interactionDatum))
  {
    CORBA::WChar *wChar = L"getInteractionAttributeDatum";
    throw GeRtiFactory::RTIinternalError(wChar);
  }

  for (i = 0; i < len; i++)
  {
    ws = federateDB.supportingServicesLRC->getParameterName(theParameters[i].id, theInteraction);
  }

  GeRtiFactory::ERHandle h;

  h.theSerialNumber = retractionHandleCounter++;
  h.sendingFederate = federateDB.federate;
  receiver->addRetractionHandle(h, theTime);

  if (federateDB.declarationManagementLRC->testInteractionSubscribers(theInteraction))
  {
    if (federateDB.timeManagementLRC->isTimeRegulation())
    {
      std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> l(federateDB.timeManagementLRC->geRtiLogicalTimeIntervalFactory.makeZero());
      std::auto_ptr<GERTICO::GeRtiFedTime> t(federateDB.timeManagementLRC->geRtiFedTimeFactory.makeZero());
      std::auto_ptr<GERTICO::GeRtiFedTime> z(federateDB.timeManagementLRC->geRtiFedTimeFactory.makeZero());

      federateDB.timeManagementLRC->testSendTime(theTime);

      federateDB.timeManagementLRC->queryLookahead(*l);
      federateDB.timeManagementLRC->queryLogicalTime(*t);
      if (l.get() && t.get())
      {
        *z = *t;
        *z += *l;
      }
      if (theTime < *z)
      {
        #ifdef GalDebug
        E0(S_uAV1_t2);
        #endif
        char b[128];
        t->getPrintableString (b);
        federateDB.timeManagementLRC->queryLookahead(*l);
        l->getPrintableString (b);
        CORBA::WChar *wChar = L"sendInteraction";
        throw GeRtiFactory::InvalidFederationTime(wChar);
      }

      eventMarket->addPushSupplierInteraction(theInteraction, theParameters, theTime, theTag, 0, h.theSerialNumber, interactionDatum);
    }
    else
    {
      eventMarket->addPushSupplierInteraction(theInteraction, theParameters, theTag, 0, interactionDatum);
    }

    transmissionArg.ps->release();

  }

        #ifdef GalDebug
        E0(S_sI1_l);
        #endif
  return h;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::sendInteraction(
  GeRtiFactory::GeRtiHandle const &theInteraction,
  GeRtiFactory::HandleValues const &theParameters,
  GeRtiFactory::UserSuppliedTag const &theTag)
throw (
  GeRtiFactory::InteractionClassNotDefined,
  GeRtiFactory::InteractionClassNotPublished,
  GeRtiFactory::InteractionParameterNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_sI2_e);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_sI2_t1);
        #endif
    CORBA::WChar *wChar = L"sendInteraction";
    throw GeRtiFactory::FederateNotExecutionMember(wChar);
  }
  CORBA::ULong i;
  CORBA::ULong len = theParameters.length();
  GERTICO::AttributeDatum interactionDatum;
  std::wstring ws;

  checkSaveRestore();

  if (federateDB.declarationManagementLRC->isPublishingInteraction(theInteraction) == false)
  {
    ws = federateDB.supportingServicesLRC->getInteractionClassName(theInteraction);
    throw GeRtiFactory::InteractionClassNotPublished(L"sendInteraction");
  }

  for (i = 0; i < len; i++)
  {
    ws = federateDB.supportingServicesLRC->getParameterName(theParameters[i].id, theInteraction);
  }

  if (federateDB.supportingServicesLRC->getInteractionAttributeDatum(theInteraction, interactionDatum))
  {
    CORBA::WChar *wChar = L"getInteractionAttributeDatum";
    throw GeRtiFactory::RTIinternalError(wChar);
  }

//  if (federateDB.declarationManagementLRC->testInteractionSubscribers(theInteraction))
//  {
    eventMarket->addPushSupplierInteraction(theInteraction, theParameters, theTag, 0, interactionDatum);

    transmissionArg.ps->release();
//  }

        #ifdef GalDebug
        E0(S_sI2_l);
        #endif
}

// ---------------------------------------------------------------------------
// 6.8
// ---------------------------------------------------------------------------
GeRtiFactory::ERHandle
NAMESPACE::Sender::deleteObjectInstance(
  GeRtiFactory::GeRtiHandle theObject,
  GERTICO::GeRtiFedTime const &theTime,
  GeRtiFactory::UserSuppliedTag const &theTag)
throw (
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::DeletePrivilegeNotHeld,
  GeRtiFactory::InvalidFederationTime,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_dOI1_e);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_dOI1_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }
  std::auto_ptr<GERTICO::GeRtiFedTime> logicalTime(federateDB.timeManagementLRC->geRtiFedTimeFactory.makeZero());

  checkSaveRestore();

  federateDB.timeManagementLRC->testSendTime(theTime);

  GeRtiFactory::ERHandle h;

  // Send events in the queue before deleting object.
  sendEvents();

  h.theSerialNumber = retractionHandleCounter++;
  h.sendingFederate = federateDB.federate;

  if (federateDB.timeManagementLRC->isTimeRegulation())
  {
    GeRtiFactory::Time t;
    GERTICO::ConvertTime::mapIt (t, theTime);
    federateDB.objectManagementLRC->deleteObjectInstance(theObject, t, theTag, h.theSerialNumber);
    federateDB.addDeleteObjectWithTime(theObject, theTime);
    federateDB.timeManagementLRC->queryLogicalTime(*logicalTime);
    federateDB.processDeleteObjectWithTime(*logicalTime, theObject);
    receiver->addRetractionHandle(h, theTime);
  }
  else
  {
    federateDB.objectManagementLRC->deleteObjectInstance(theObject, theTag);

    federateDB.delObject(theObject);
  }

        #ifdef GalDebug
        E0(S_dOI1_l);
        #endif
  return h;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::deleteObjectInstance(
  GeRtiFactory::GeRtiHandle theObject,
  GeRtiFactory::UserSuppliedTag const &theTag)
throw (
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::DeletePrivilegeNotHeld,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_dOI2_e);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_dOI2_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  // Send events in the queue before deleting object.
  sendEvents();
  federateDB.delDeleteObjectWithTime(theObject);

  federateDB.objectManagementLRC->deleteObjectInstance(theObject, theTag);
        #ifdef GalDebug
        E0(S_dOI2_l);
        #endif
}

// ---------------------------------------------------------------------------
// 6.10
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::localDeleteObjectInstance(
  GeRtiFactory::GeRtiHandle    theObject)
throw (
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::FederateOwnsAttributes,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_lDOI_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_lDOI_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  federateDB.objectManagementLRC->localDeleteObjectInstance(theObject, federateDB.federate);
  federateDB.delObject(theObject);
}

// ---------------------------------------------------------------------------
// 6.11
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::changeAttributeTransportationType(
  GeRtiFactory::GeRtiHandle theObject,
  GeRtiFactory::Handles const &theAttributes,
  GeRtiFactory::GeRtiHandle theType)
throw (
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::AttributeNotOwned,
  GeRtiFactory::InvalidTransportationHandle,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_cATT_q);
        #endif
  GeRtiFactory::GeRtiHandle knownObjectClass;

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_cATT_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  knownObjectClass = federateDB.objectManagementLRC->getObjectClass(theObject);

  // Test for attribute not defined.
  checkAttributeNotDefined(knownObjectClass, theAttributes);

  // Send events in the queue before changing transportation type.
  sendEvents();

  federateDB.objectManagementLRC->changeAttributeTransportationType(theObject, theAttributes, theType);
}

// 6.12
void NAMESPACE::Sender::changeInteractionTransportationType(
  GeRtiFactory::GeRtiHandle theClass,
  GeRtiFactory::GeRtiHandle theType)
throw (
  GeRtiFactory::InteractionClassNotDefined,
  GeRtiFactory::InteractionClassNotPublished,
  GeRtiFactory::InvalidTransportationHandle,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_cITT_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_cITT_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  // Send events in the queue before changing transportation type.
  sendEvents();

  federateDB.objectManagementLRC->changeInteractionTransportationType(theClass, theType);
}

// 6.15
void NAMESPACE::Sender::requestObjectAttributeValueUpdate(
  GeRtiFactory::GeRtiHandle theObject,
  GeRtiFactory::Handles const &theAttributes,
  GeRtiFactory::UserSuppliedTag const &theTag)
throw (
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_rOAVU_e);
        #endif
  GeRtiFactory::GeRtiHandle knownObjectClass;

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_rOAVU_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  knownObjectClass = federateDB.objectManagementLRC->getObjectClass(theObject);

  // Test for attribute not defined.
  checkAttributeNotDefined(knownObjectClass, theAttributes);

  federateDB.objectManagementLRC->requestObjectAttributeValueUpdate(theObject, theAttributes, theTag);
        #ifdef GalDebug
        E0(S_rOAVU_l);
        #endif
}

void NAMESPACE::Sender::requestClassAttributeValueUpdate(
  GeRtiFactory::GeRtiHandle theClass,
  GeRtiFactory::Handles const & theAttributes,
  GeRtiFactory::UserSuppliedTag const &theTag)
throw(
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_rCAVU_e);
        #endif
  CORBA::WChar *wChar = L"";

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_rCAVU_t1);
        #endif
    throw GeRtiFactory::FederateNotExecutionMember(wChar);
  }

  checkSaveRestore();

  // Test for attribute not defined.
  checkAttributeNotDefined(theClass, theAttributes);

  try
  {
    federateDB.objectManagementLRC->requestClassAttributeValueUpdate(theClass, theAttributes, theTag);
  }
  catch (CORBA::SystemException &)
  {
    throw GeRtiFactory::RTIinternalError(wChar);
  }
        #ifdef GalDebug
        E0(S_rCAVU_l);
        #endif
}

///////////////////////////////////
// Ownership Management Services //
///////////////////////////////////

// 7.2
void NAMESPACE::Sender::unconditionalAttributeOwnershipDivestiture(
  GeRtiFactory::GeRtiHandle theObject,
  GeRtiFactory::Handles const &theAttributes)
throw (
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::AttributeNotOwned,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_uAOD_e);
        #endif
  GeRtiFactory::GeRtiHandle knownObjectClass;

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_uAOD_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  knownObjectClass = federateDB.objectManagementLRC->getObjectClass(theObject);

  // Test for attribute not defined.
  checkAttributeNotDefined(knownObjectClass, theAttributes);

  federateDB.ownership->unconditionalAttributeOwnershipDivestiture (theObject, theAttributes);
        #ifdef GalDebug
        E0(S_uAOD_l);
        #endif
}

// 7.3
void NAMESPACE::Sender::negotiatedAttributeOwnershipDivestiture(
  GeRtiFactory::GeRtiHandle theObject,
  GeRtiFactory::Handles const &theAttributes,
  GeRtiFactory::UserSuppliedTag const &theTag)
throw (
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::AttributeNotOwned,
  GeRtiFactory::AttributeAlreadyBeingDivested,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_nAOD_e);
        #endif
  GeRtiFactory::GeRtiHandle knownObjectClass;

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_nAOD_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  //check if object is locally known
  knownObjectClass = federateDB.objectManagementLRC->getObjectClass(theObject);

  // Test for attribute not defined.
  checkAttributeNotDefined(knownObjectClass, theAttributes);

  federateDB.ownership->negotiatedAttributeOwnershipDivestiture (theObject, theAttributes, theTag);
        #ifdef GalDebug
        E0(S_nAOD_l);
        #endif
}

// 7.7
void NAMESPACE::Sender::attributeOwnershipAcquisition(
  GeRtiFactory::GeRtiHandle theObject,
  GeRtiFactory::Handles const & desiredAttributes,
  GeRtiFactory::UserSuppliedTag const &theTag)
throw (
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::ObjectClassNotPublished,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::AttributeNotPublished,
  GeRtiFactory::FederateOwnsAttributes,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
//        E1(S_aOA_e,theTag);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_aOA_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }
  GeRtiFactory::GeRtiHandle knownObjectClass;

  checkSaveRestore();

  knownObjectClass = federateDB.objectManagementLRC->getObjectClass(theObject);

  // Test for known class.
  std::wstring dummy = federateDB.supportingServicesLRC->getObjectClassName(knownObjectClass);

  // Test for attribute not defined.
  checkAttributeNotDefined(knownObjectClass, desiredAttributes);

  federateDB.declarationManagementLRC->checkPublishing(knownObjectClass, desiredAttributes);

  federateDB.ownership->attributeOwnershipAcquisition (theObject, desiredAttributes, theTag);
        #ifdef GalDebug
        E0(S_aOA_l);
        #endif
}

// 7.8
void NAMESPACE::Sender::attributeOwnershipAcquisitionIfAvailable(
  GeRtiFactory::GeRtiHandle theObject,
  GeRtiFactory::Handles const &desiredAttributes)
throw (
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::ObjectClassNotPublished,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::AttributeNotPublished,
  GeRtiFactory::FederateOwnsAttributes,
  GeRtiFactory::AttributeAlreadyBeingAcquired,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_aOAIA_e);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_aOAIA_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }
  GeRtiFactory::GeRtiHandle knownObjectClass;

  checkSaveRestore();

  knownObjectClass = federateDB.objectManagementLRC->getObjectClass(theObject);

  // Test for known class.
  std::wstring dummy = federateDB.supportingServicesLRC->getObjectClassName(knownObjectClass);

  // Test for attribute not defined.
  checkAttributeNotDefined(knownObjectClass, desiredAttributes);

  federateDB.declarationManagementLRC->checkPublishing(knownObjectClass, desiredAttributes);

  federateDB.ownership->attributeOwnershipAcquisitionIfAvailable (theObject, desiredAttributes);
        #ifdef GalDebug
        E0(S_aOAIA_l);
        #endif
}

void NAMESPACE::Sender::attributeOwnershipDivestitureIfWanted(
  GeRtiFactory::GeRtiHandle const &theObject,
  GeRtiFactory::Handles const &theAttributes,
  GeRtiFactory::Handles &theDivestedAttributes)
throw(
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::AttributeNotOwned,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
  GeRtiFactory::GeRtiHandle knownObjectClass;

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_aOAIA_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  knownObjectClass = federateDB.objectManagementLRC->getObjectClass(theObject);

  // Test for known class.
  std::wstring dummy = federateDB.supportingServicesLRC->getObjectClassName(knownObjectClass);

  // Test for attribute not defined.
  checkAttributeNotDefined(knownObjectClass, theAttributes);

  federateDB.declarationManagementLRC->checkPublishing(knownObjectClass, theAttributes);

  federateDB.ownership->attributeOwnershipDivestitureIfWanted(theObject, theAttributes, theDivestedAttributes);
}

// 7.11
GeRtiFactory::Handles*
NAMESPACE::Sender::confirmDivestiture(
  GeRtiFactory::GeRtiHandle theObject,
  GeRtiFactory::Handles const &theAttributes,
  GeRtiFactory::UserSuppliedTag const &theTag)
throw (
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::AttributeNotOwned,
  GeRtiFactory::FederateWasNotAskedToReleaseAttribute,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_aORR_e);
        #endif
  GeRtiFactory::GeRtiHandle knownObjectClass;

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_aORR_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }
        #ifdef GalDebug
        E0(S_aORR_l);
        #endif

  checkSaveRestore();

  knownObjectClass = federateDB.objectManagementLRC->getObjectClass(theObject);

  // Test for attribute not defined.
  checkAttributeNotDefined(knownObjectClass, theAttributes);

  return federateDB.ownership->confirmDivestiture(theObject, theAttributes, theTag);
}

// 7.12
void NAMESPACE::Sender::cancelNegotiatedAttributeOwnershipDivestiture(
  GeRtiFactory::GeRtiHandle theObject,
  GeRtiFactory::Handles const &theAttributes)
throw (
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::AttributeNotOwned,
  GeRtiFactory::AttributeDivestitureWasNotRequested,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_cNAOD_e);
        #endif
  GeRtiFactory::GeRtiHandle knownObjectClass;

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_cNAOD_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  knownObjectClass = federateDB.objectManagementLRC->getObjectClass(theObject);

  // Test for attribute not defined.
  checkAttributeNotDefined(knownObjectClass, theAttributes);

  federateDB.ownership->cancelNegotiatedAttributeOwnershipDivestiture (theObject, theAttributes);
        #ifdef GalDebug
        E0(S_cNAOD_l);
        #endif
}

// 7.13
void NAMESPACE::Sender::cancelAttributeOwnershipAcquisition(
  GeRtiFactory::GeRtiHandle theObject,
  GeRtiFactory::Handles const &theAttributes)
throw (
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::AttributeAlreadyOwned,
  GeRtiFactory::AttributeAcquisitionWasNotRequested,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_cAOA1_e);
        #endif
  GeRtiFactory::GeRtiHandle knownObjectClass;

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_cAOA1_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  knownObjectClass = federateDB.objectManagementLRC->getObjectClass(theObject);

  // Test for attribute not defined.
  checkAttributeNotDefined(knownObjectClass, theAttributes);

  federateDB.ownership->cancelAttributeOwnershipAcquisition (theObject, theAttributes);
        #ifdef GalDebug
        E0(S_cAOA1_l);
        #endif
}

// 7.15
void NAMESPACE::Sender::queryAttributeOwnership(
  GeRtiFactory::GeRtiHandle theObject,
  GeRtiFactory::GeRtiHandle theAttribute)
throw (
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_cAOA2_e);
        #endif
  GeRtiFactory::GeRtiHandle knownObjectClass;
  std::wstring ws;

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_cAOA2_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  //check if object is locally known
  knownObjectClass = federateDB.objectManagementLRC->getObjectClass(theObject);

  // Test for attribute not defined.
  ws = federateDB.supportingServicesLRC->getAttributeName(theAttribute, knownObjectClass);

  federateDB.ownership->queryAttributeOwnership (theObject, theAttribute);
        #ifdef GalDebug
        E0(S_cAOA2_l);
        #endif
}

// 7.17
CORBA::Boolean
NAMESPACE::Sender::isAttributeOwnedByFederate(
  GeRtiFactory::GeRtiHandle theObject,
  GeRtiFactory::GeRtiHandle theAttribute)
throw (
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_iAOBF_e);
        #endif
  CORBA::Boolean ret = false;
  GeRtiFactory::GeRtiHandle knownObjectClass;
  GeRtiFactory::GeRtiHandle objectClass;
  std::wstring ws;

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_iAOBF_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  knownObjectClass = federateDB.objectManagementLRC->getObjectClass(theObject);

  // Test for attribute not defined.
  ws = federateDB.supportingServicesLRC->getAttributeName(theAttribute, knownObjectClass);

  // Send events in the queue before checking object.
  sendEvents();

        #ifdef GalDebug
        E0(S_iAOBF_l);
        #endif
  objectClass = GeRtiAmb->getObjectClass (theObject);

  try
  {
    ret = federateDB.ownership->isAttributeOwnedByFederate (theObject, theAttribute);
  }
  catch (GeRtiFactory::AttributeNotDefined)
  {
    std::wstring name;
    name = GeRtiAmb->getAttributeName(theAttribute, objectClass);
  }

  return ret;
}

//////////////////////////////
// Time Management Services //
//////////////////////////////

// ---------------------------------------------------------------------------
// 8.2
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::enableTimeRegulation(
#ifndef IEEE_1516
  GERTICO::GeRtiFedTime const &theFederateTime,
#endif
  GERTICO::GeRtiLogicalTimeInterval const &theLookahead)
throw (
  GeRtiFactory::TimeRegulationAlreadyEnabled,
  GeRtiFactory::EnableTimeRegulationPending,
  GeRtiFactory::TimeAdvanceAlreadyInProgress,
  GeRtiFactory::InvalidFederationTime,
  GeRtiFactory::InvalidLookahead,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_eTR_e);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_eTR_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

#ifdef IEEE_1516
  federateDB.timeManagementLRC->enableTimeRegulation(theLookahead);
#else
  federateDB.timeManagementLRC->enableTimeRegulation(theFederateTime, theLookahead);
#endif
        #ifdef GalDebug
        E0(S_eTR_l);
        #endif
}

// ---------------------------------------------------------------------------
// 8.4
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::disableTimeRegulation()
throw (
  GeRtiFactory::TimeRegulationWasNotEnabled,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_dTR_e);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_dTR_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  federateDB.timeManagementLRC->disableTimeRegulation();
  receiver->setDisableTimeRegulation();
        #ifdef GalDebug
        E0(S_dTR_l);
        #endif
}

// ---------------------------------------------------------------------------
// 8.5
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::enableTimeConstrained()
throw (
  GeRtiFactory::TimeConstrainedAlreadyEnabled,
  GeRtiFactory::EnableTimeConstrainedPending,
  GeRtiFactory::TimeAdvanceAlreadyInProgress,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_eTC_e);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_eTC_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  federateDB.timeManagementLRC->enableTimeConstrained();
        #ifdef GalDebug
        E0(S_eTC_l);
        #endif
}

// ---------------------------------------------------------------------------
// 8.7
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::disableTimeConstrained()
throw (
  GeRtiFactory::TimeConstrainedWasNotEnabled,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_dTC_e);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_dTC_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  federateDB.timeManagementLRC->disableTimeConstrained();
  receiver->setDisableTimeConstrained ();
        #ifdef GalDebug
        E0(S_dTC_l);
        #endif
}

// ---------------------------------------------------------------------------
// 8.8
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::timeAdvanceRequest(
  GERTICO::GeRtiFedTime const &theTime)
throw (
  GeRtiFactory::InvalidFederationTime,
  GeRtiFactory::FederationTimeAlreadyPassed,
  GeRtiFactory::TimeAdvanceAlreadyInProgress,
  GeRtiFactory::EnableTimeRegulationPending,
  GeRtiFactory::EnableTimeConstrainedPending,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_tAR_e);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_tAR_t1);
        #endif
    CORBA::WChar *buff = L"timeAdvanceRequest";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  // Send events in the queue before time advance request.
  sendEvents();

  bool avail = false;

  federateDB.timeManagementLRC->timeAdvanceRequest(theTime, avail);
  receiver->setTimeAdvanceRequest(avail);

        #ifdef GalDebug
        E0(S_tAR_l);
        #endif
}

// ---------------------------------------------------------------------------
// 8.9
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::timeAdvanceRequestAvailable(
  GERTICO::GeRtiFedTime const &theTime)
throw (
  GeRtiFactory::InvalidFederationTime,
  GeRtiFactory::FederationTimeAlreadyPassed,
  GeRtiFactory::TimeAdvanceAlreadyInProgress,
  GeRtiFactory::EnableTimeRegulationPending,
  GeRtiFactory::EnableTimeConstrainedPending,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_tARA_e);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_tARA_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  // Send events in the queue before time advance request.
  sendEvents();

  bool avail = true;

  federateDB.timeManagementLRC->timeAdvanceRequest(theTime, avail);
  receiver->setTimeAdvanceRequest(avail);
        #ifdef GalDebug
        E0(S_tARA_l);
        #endif
}

// ---------------------------------------------------------------------------
// 8.10
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::nextEventRequest(
  GERTICO::GeRtiFedTime const &theTime)
throw (
  GeRtiFactory::InvalidFederationTime,
  GeRtiFactory::FederationTimeAlreadyPassed,
  GeRtiFactory::TimeAdvanceAlreadyInProgress,
  GeRtiFactory::EnableTimeRegulationPending,
  GeRtiFactory::EnableTimeConstrainedPending,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_nER_e);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_nER_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  // Send events in the queue before time advance request.
  sendEvents();

  bool avail = false;

  federateDB.timeManagementLRC->nextEventRequest(theTime, avail);
  receiver->setNextEventRequest(avail);
        #ifdef GalDebug
        E0(S_nER_l);
        #endif
}

// ---------------------------------------------------------------------------
// 8.11
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::nextEventRequestAvailable(
  GERTICO::GeRtiFedTime const &theTime)
throw (
  GeRtiFactory::InvalidFederationTime,
  GeRtiFactory::FederationTimeAlreadyPassed,
  GeRtiFactory::TimeAdvanceAlreadyInProgress,
  GeRtiFactory::EnableTimeRegulationPending,
  GeRtiFactory::EnableTimeConstrainedPending,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_nERA_e);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_nERA_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  // Send events in the queue before time advance request.
  sendEvents();

  bool avail = true;

  federateDB.timeManagementLRC->nextEventRequest(theTime, avail);
  receiver->setNextEventRequest(avail);
        #ifdef GalDebug
        E0(S_nERA_l);
        #endif
}

// ---------------------------------------------------------------------------
// 8.12
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::flushQueueRequest(
  GERTICO::GeRtiFedTime const &theTime)
throw (
  GeRtiFactory::InvalidFederationTime,
  GeRtiFactory::FederationTimeAlreadyPassed,
  GeRtiFactory::TimeAdvanceAlreadyInProgress,
  GeRtiFactory::EnableTimeRegulationPending,
  GeRtiFactory::EnableTimeConstrainedPending,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_fQR_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_fQR_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  // Send events in the queue before time advance request.
  sendEvents();

  GeRtiFactory::Time fedTime;
  GERTICO::ConvertTime::mapIt(fedTime, theTime);

  federateDB.timeManagementLRC->flushQueueRequest(theTime);
  receiver->setFlushQueueRequest();
}

// ---------------------------------------------------------------------------
// 8.14
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::enableAsynchronousDelivery()
throw (
  GeRtiFactory::AsynchronousDeliveryAlreadyEnabled,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_eAD_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_eAD_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  receiver->setAsynchronousDelivery(true);
}

// ---------------------------------------------------------------------------
// 8.15
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::disableAsynchronousDelivery()
throw (
  GeRtiFactory::AsynchronousDeliveryAlreadyDisabled,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_dAD_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_dAD_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  receiver->setAsynchronousDelivery (false);
}

// ---------------------------------------------------------------------------
// 8.16
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::queryLBTS(
  GERTICO::GeRtiFedTime &theTime)
throw (
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_qLBTS_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_qLBTS_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  federateDB.timeManagementLRC->queryGALT(theTime);
}

// ---------------------------------------------------------------------------
// 8.17
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::queryFederateTime(
  GERTICO::GeRtiFedTime& theTime)
throw (
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_qFT_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_qFT_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  federateDB.timeManagementLRC->queryLogicalTime(theTime);
}

// ---------------------------------------------------------------------------
// 8.18
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::queryMinNextEventTime(
  GERTICO::GeRtiFedTime &theTime)
throw (
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_qMNET_q);
        #endif
  std::auto_ptr<GERTICO::GeRtiFedTime> t(federateDB.timeManagementLRC->geRtiFedTimeFactory.makeZero());

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_qMNET_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  receiver->queryMinNextEventTime(theTime);
  federateDB.timeManagementLRC->queryLITS(*t);
  if (t->isPositiveInfinity() == false)
  {
    if (*t < theTime)
    {
      theTime = *t;
    }
  }
}

// ---------------------------------------------------------------------------
// 8.19
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::modifyLookahead(
  GERTICO::GeRtiLogicalTimeInterval const &theLookahead)
throw (
  GeRtiFactory::InvalidLookahead,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_mL_e);
        #endif
  CORBA::WChar *wChar = L"";

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_mL_t1);
        #endif
    throw GeRtiFactory::FederateNotExecutionMember(wChar);
  }

  checkSaveRestore();

  try
  {
    federateDB.timeManagementLRC->modifyLookahead(theLookahead);
  }
  catch (GeRtiFactory::TimeAdvanceAlreadyInProgress)
  {
    // Wrong for IEEE 1516
        #ifdef GalDebug
        E0(S_mL_t2);
        #endif
    throw GeRtiFactory::RTIinternalError(wChar);
  }
        #ifdef GalDebug
        E0(S_mL_l);
        #endif
}

// ---------------------------------------------------------------------------
// 8.20
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::queryLookahead(
  GERTICO::GeRtiLogicalTimeInterval &theTime)
throw (
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_qL_e);
        #endif

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_qL_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  federateDB.timeManagementLRC->queryLookahead(theTime);
        #ifdef GalDebug
        E0(S_qL_l);
        #endif
}

// ---------------------------------------------------------------------------
// 8.21
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::retract(
  GeRtiFactory::ERHandle const &theERHandle)
throw (
  GeRtiFactory::InvalidRetractionHandle,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_r_q);
        #endif

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_r_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  if (receiver->eventHandler)
  {
    receiver->eventHandler->checkRetractionHandle(theERHandle);
  }

  federateDB.timeManagementLRC->retract(theERHandle);

  if (receiver->eventHandler)
  {
    receiver->eventHandler->deleteRetractionHandle(theERHandle);
  }
}

// ---------------------------------------------------------------------------
// 8.23
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::changeAttributeOrderType(
  GeRtiFactory::GeRtiHandle theObject,
  GeRtiFactory::Handles const &theAttributes,
  GeRtiFactory::GeRtiHandle theType)
throw (
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::AttributeNotOwned,
  GeRtiFactory::InvalidOrderingHandle,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_cAOT_q);
        #endif
  GeRtiFactory::GeRtiHandle knownObjectClass;

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_cAOT_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  knownObjectClass = federateDB.objectManagementLRC->getObjectClass(theObject);

  // Test for attribute not defined.
  checkAttributeNotDefined(knownObjectClass, theAttributes);

  // Send events in the queue before changing order type.
  sendEvents();

  federateDB.objectManagementLRC->changeAttributeOrderType(theObject, theAttributes, theType);
}

// ---------------------------------------------------------------------------
// 8.24
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::changeInteractionOrderType(
  GeRtiFactory::GeRtiHandle theClass,
  GeRtiFactory::GeRtiHandle theType)
throw (
  GeRtiFactory::InteractionClassNotDefined,
  GeRtiFactory::InteractionClassNotPublished,
  GeRtiFactory::InvalidOrderingHandle,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_cIOT_q);
        #endif

  CORBA::WChar *buff = L"changeInteractionOrderType";
  std::wstring ws;

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_cIOT_t1);
        #endif
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }
  GERTICO::HandleSet::iterator itHS;

  checkSaveRestore();

  ws = federateDB.supportingServicesLRC->getInteractionClassName(theClass);

  if (federateDB.declarationManagementLRC->isPublishingInteraction(theClass) == false)
  {
    throw GeRtiFactory::InteractionClassNotPublished(buff);
  }

  // Send events in the queue before changing order type.
  sendEvents();

  federateDB.objectManagementLRC->changeInteractionOrderType(theClass, theType);
}

//////////////////////////////////
// Data Distribution Management //
//////////////////////////////////

// 9.2
GeRtiFactory::GeRtiHandle
NAMESPACE::Sender::createRegion
(
  GeRtiFactory::GeRtiHandle const &theSpace,
  CORBA::ULong const &numberOfExtents,
  GERTICO::HandleSet const &theDimensions
)
throw (
  GeRtiFactory::SpaceNotDefined,
  GeRtiFactory::InvalidExtents,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_cR_q);
        #endif
  CORBA::WChar *wChar = L"";

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_cR_t1);
        #endif
    throw GeRtiFactory::FederateNotExecutionMember(wChar);
  }

  checkSaveRestore();

  GeRtiFactory::GeRtiHandle ret;

  ret = federateDB.dataDistributionManagementLRC->createRegion(theSpace, numberOfExtents, theDimensions);

  return ret;
}

// 9.3
void NAMESPACE::Sender::notifyAboutRegionModification(
  GeRtiFactory::GeRtiHandle const &theRegion,
  GeRtiFactory::Extents &theExtents)
throw (
  GeRtiFactory::RegionNotKnown,
  GeRtiFactory::InvalidExtents,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_nARM_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_nARM_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  federateDB.dataDistributionManagementLRC->notifyAboutRegionModification(theRegion, theExtents);
}

// 9.4
void NAMESPACE::Sender::deleteRegion(
  GeRtiFactory::GeRtiHandle const &theRegion)
throw (
  GeRtiFactory::RegionNotKnown,
  GeRtiFactory::RegionInUse,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_dR_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_dR_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  federateDB.dataDistributionManagementLRC->deleteRegion(theRegion);
}

// 9.5
GeRtiFactory::GeRtiHandle
NAMESPACE::Sender::registerObjectInstanceWithRegion(
  GeRtiFactory::GeRtiHandle const &theClass,
  std::wstring const &theObjectName,
  GERTICO::HandleSetMap &theAttRegMap)
throw (
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::ObjectClassNotPublished,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::AttributeNotPublished,
  GeRtiFactory::RegionNotKnown,
  GeRtiFactory::InvalidRegionContext,
  GeRtiFactory::ObjectAlreadyRegistered,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
  std::wstring ws;
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_rOIWR1_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  // Check if class is defined.
  ws = federateDB.supportingServicesLRC->getObjectClassName(theClass);

  // Check if class is published.
  GERTICO::PublishedClass *publishedClass = federateDB.runTimeObjectDB->getPublishedClass(theClass);
  if (publishedClass == NULL)
  {
    throw GeRtiFactory::ObjectClassNotPublished(L"registerObjectInstanceWithRegion");
  }

  // Test for attribute not defined.
  checkAttributeNotDefined(theClass, theAttRegMap);

  return federateDB.objectManagementLRC->registerObjectInstanceWithRegion(federateDB.federate, theClass, theObjectName, theAttRegMap);
}

GeRtiFactory::GeRtiHandle
NAMESPACE::Sender::registerObjectInstanceWithRegion(
  GeRtiFactory::GeRtiHandle const &theClass,
  GERTICO::HandleSetMap &theAttRegMap)
throw (
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::ObjectClassNotPublished,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::AttributeNotPublished,
  GeRtiFactory::RegionNotKnown,
  GeRtiFactory::InvalidRegionContext,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_rOIWR2_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_rOIWR2_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  // Check if class is published.
  GERTICO::PublishedClass *publishedClass = federateDB.runTimeObjectDB->getPublishedClass(theClass);
  if (publishedClass == NULL)
  {
    throw GeRtiFactory::ObjectClassNotPublished(L"registerObjectInstanceWithRegion");
  }

  // Test for attribute not defined.
  checkAttributeNotDefined(theClass, theAttRegMap);

  return federateDB.objectManagementLRC->registerObjectInstanceWithRegion(federateDB.federate, theClass, theAttRegMap);
}

// 9.6
void NAMESPACE::Sender::associateRegionForUpdates(
  GeRtiFactory::GeRtiHandle theObject,
  GERTICO::HandleSetMap &theAttRegMap)
throw (
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::InvalidRegionContext,
  GeRtiFactory::RegionNotKnown,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_aRFU1_q);
        #endif
  GERTICO::RegisteredObject *registeredObject;
  GeRtiFactory::GeRtiHandle objClass;

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_aRFU1_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  registeredObject = federateDB.registeredObjectsHolder.getObject(theObject);
  objClass = registeredObject->getClassId();

  // Test for attribute not defined.
  checkAttributeNotDefined(objClass, theAttRegMap);

  federateDB.dataDistributionManagementLRC->associateRegionsForUpdates(theObject, theAttRegMap);
}

// 9.7
void NAMESPACE::Sender::unassociateRegionForUpdates(
  GeRtiFactory::GeRtiHandle &theRegion,
  GeRtiFactory::GeRtiHandle theObject)
throw (
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::InvalidRegionContext,
  GeRtiFactory::RegionNotKnown,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_aRFU2_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_aRFU2_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  federateDB.dataDistributionManagementLRC->unassociateRegionForUpdates(theRegion, theObject);
}

void NAMESPACE::Sender::unassociateRegionsForUpdates(
  GeRtiFactory::GeRtiHandle theObject,
  GERTICO::HandleSetMap &theAttRegMap)
throw (
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::InvalidRegionContext,
  GeRtiFactory::RegionNotKnown,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_aRFU2_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_aRFU2_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  federateDB.dataDistributionManagementLRC->unassociateRegionsForUpdates(theObject, theAttRegMap);
}

// 9.8
void NAMESPACE::Sender::subscribeObjectClassAttributesWithRegion(
  GeRtiFactory::GeRtiHandle theClass,
  GERTICO::HandleSetMap &theAttRegMap,
  bool const &active)
throw (
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::RegionNotKnown,
  GeRtiFactory::InvalidRegionContext,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
  CORBA::WChar *buff = L"subscribeObjectClassAttributesWithRegion";
        #ifdef GalDebug
        E0(S_sOCAWR_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_sOCAWR_t1);
        #endif
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  GERTICO::HandleSet handleSet;
  GERTICO::HandleSetMap::iterator itHandleSetMap;

  checkSaveRestore();

  // Test for known class.
  std::wstring dummy = federateDB.supportingServicesLRC->getObjectClassName(theClass);

  for (itHandleSetMap = theAttRegMap.begin(); itHandleSetMap != theAttRegMap.end(); itHandleSetMap++)
  {
    handleSet.insert(itHandleSetMap->first);
  }

  if (federateDB.supportingServicesLRC->testDimensionAttributes(theClass, handleSet))
  {
    throw GeRtiFactory::InvalidRegionContext(buff);
  }

  /*
  typedef std::set <GeRtiFactory::GeRtiHandle, cmpHandle> HandleSet;
  typedef std::map <GeRtiFactory::GeRtiHandle, GERTICO::HandleSet, cmpHandle> HandleSetMap;
  */

  // Test for attribute not defined.
  checkAttributeNotDefined(theClass, theAttRegMap);

  federateDB.dataDistributionManagementLRC->subscribeObjectClassAttributesWithRegions(theClass, theAttRegMap, active);

  // Local information for incoming events.
  federateDB.declarationManagementLRC->subscribeObjectClassAttributesReceiver(theClass, theAttRegMap);
}

// 9.9
void NAMESPACE::Sender::unsubscribeObjectClassWithRegion(
  GeRtiFactory::GeRtiHandle theClass,
  GeRtiFactory::GeRtiHandle &theRegion)
throw (
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::RegionNotKnown,
  GeRtiFactory::ObjectClassNotSubscribed,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_uOCWR_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_uOCWR_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  // Test for known class.
  std::wstring dummy = federateDB.supportingServicesLRC->getObjectClassName(theClass);

  // Unsubscribe to class.
  federateDB.dataDistributionManagementLRC->unsubscribeObjectClassWithRegion(theClass, theRegion);

  // Local information for incoming events.
  receiver->unsubscribeObjectClassWithRegionReceiver(theClass, theRegion);
}

void NAMESPACE::Sender::unsubscribeObjectClassWithRegions(
  GeRtiFactory::GeRtiHandle theClass,
  GERTICO::HandleSetMap &theAttRegMap)
throw (
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::RegionNotKnown,
  GeRtiFactory::ObjectClassNotSubscribed,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_uOCWR_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_uOCWR_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  // Test for known class.
  std::wstring dummy = federateDB.supportingServicesLRC->getObjectClassName(theClass);

  // Unsubscribe to class.
  federateDB.dataDistributionManagementLRC->unsubscribeObjectClassWithRegions(theClass, theAttRegMap);

  // Local information for incoming events.
  receiver->unsubscribeObjectClassWithRegionsReceiver(theClass, theAttRegMap);
}

// 9.10
void NAMESPACE::Sender::subscribeInteractionClassWithRegion(
  GeRtiFactory::GeRtiHandle theClass,
  GERTICO::HandleSet &theRegions,
  bool const &active)
throw (
  GeRtiFactory::InteractionClassNotDefined,
  GeRtiFactory::RegionNotKnown,
  GeRtiFactory::InvalidRegionContext,
  GeRtiFactory::FederateLoggingServiceCalls,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_sICWR_q);
        #endif
  // Zero length list.
  GeRtiFactory::Handles attributeList;
  std::wstring ws;

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_sICWR_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  ws = federateDB.supportingServicesLRC->getInteractionClassName(theClass);

  // Subscribe to interaction class.
  federateDB.dataDistributionManagementLRC->subscribeInteractionClassWithRegion(theClass, theRegions, active);
}

// 9.11
void NAMESPACE::Sender::unsubscribeInteractionClassWithRegion(
  GeRtiFactory::GeRtiHandle theClass,
  GERTICO::HandleSet &theRegions)
throw (
  GeRtiFactory::InteractionClassNotDefined,
  GeRtiFactory::InteractionClassNotSubscribed,
  GeRtiFactory::RegionNotKnown,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
  std::wstring ws;

        #ifdef GalDebug
        E0(S_uICWR_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_uICWR_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  ws = federateDB.supportingServicesLRC->getInteractionClassName(theClass);

  // Subscribe to interaction class.
  federateDB.dataDistributionManagementLRC->unsubscribeInteractionClassWithRegions(theClass, theRegions);
}

// ---------------------------------------------------------------------------
// 9.12
// ---------------------------------------------------------------------------
GeRtiFactory::ERHandle
NAMESPACE::Sender::sendInteractionWithRegion(
  GeRtiFactory::GeRtiHandle const &theInteraction,
  GeRtiFactory::HandleValues const &theParameters,
  GERTICO::GeRtiFedTime const &theTime,
  GeRtiFactory::UserSuppliedTag const &theTag,
  GERTICO::HandleSet const &theRegions)
throw (
  GeRtiFactory::InteractionClassNotDefined,
  GeRtiFactory::InteractionClassNotPublished,
  GeRtiFactory::InteractionParameterNotDefined,
  GeRtiFactory::InvalidFederationTime,
  GeRtiFactory::RegionNotKnown,
  GeRtiFactory::InvalidRegionContext,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
  CORBA::ULong i;
  CORBA::ULong len = theParameters.length();
  GERTICO::AttributeDatum interactionDatum;
  GERTICO::HandleMap::iterator itHM;
  GERTICO::HandleSet::const_iterator itRegion;
  GERTICO::Region *regionPtr;
  GeRtiFactory::GeRtiHandle region = 0;
  GeRtiFactory::GeRtiHandle spaceHandle = 0;
  std::wstring ws;

  if (federateDB.joined == false)
  {
    CORBA::WChar *wChar = L"sendInteractionWithRegion";
    throw GeRtiFactory::FederateNotExecutionMember(wChar);
  }

  checkSaveRestore();

  federateDB.timeManagementLRC->testSendTime(theTime);

  if (federateDB.declarationManagementLRC->isPublishingInteraction(theInteraction) == false)
  {
    ws = federateDB.supportingServicesLRC->getInteractionClassName(theInteraction);
    throw GeRtiFactory::InteractionClassNotPublished(L"sendInteraction");
  }

  for (itRegion = theRegions.begin(); itRegion != theRegions.end(); itRegion++)
  {
    // XX not correct!!
    region = *itRegion;

    // Get region to check space handle.
    regionPtr = federateDB.runTimeObjectDB->getRegion(*itRegion);
    if (regionPtr == NULL)
    {
      throw GeRtiFactory::RegionNotKnown(L"sendInteractionWithRegion");
    }
  }

  itHM = interactionHandleMap.find(theInteraction);
  if (itHM != interactionHandleMap.end())
  {
    spaceHandle = itHM->second;
  }
  else
  {
    spaceHandle = GeRtiAmb->getInteractionRoutingSpaceHandle(theInteraction);
    interactionHandleMap[theInteraction] = spaceHandle;
  }

  if (spaceHandle != regionPtr->getSpace())
  {
    throw GeRtiFactory::InvalidRegionContext(L"sendInteractionWithRegion");
  }

  for (i = 0; i < len; i++)
  {
    ws = federateDB.supportingServicesLRC->getParameterName(theParameters[i].id, theInteraction);
  }

  GeRtiFactory::ERHandle h;

  h.theSerialNumber = retractionHandleCounter++;
  h.sendingFederate = federateDB.federate;
  receiver->addRetractionHandle(h, theTime);

  if (federateDB.supportingServicesLRC->getInteractionAttributeDatum(theInteraction, interactionDatum))
  {
    CORBA::WChar *wChar = L"getInteractionAttributeDatum";
    throw GeRtiFactory::RTIinternalError(wChar);
  }

  if (federateDB.declarationManagementLRC->testInteractionSubscribers(theInteraction))
  {
    if (federateDB.timeManagementLRC->isTimeRegulation())
    {
      std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> l(federateDB.timeManagementLRC->geRtiLogicalTimeIntervalFactory.makeZero());
      std::auto_ptr<GERTICO::GeRtiFedTime> t(federateDB.timeManagementLRC->geRtiFedTimeFactory.makeZero());
      std::auto_ptr<GERTICO::GeRtiFedTime> z(federateDB.timeManagementLRC->geRtiFedTimeFactory.makeZero());

      federateDB.timeManagementLRC->queryLookahead(*l);
      federateDB.timeManagementLRC->queryLogicalTime(*t);
      if (l.get() && t.get())
      {
        *z = *t;
        *z += *l;
      }
      if (theTime < *z)
      {
        #ifdef GalDebug
        E0(S_uAV1_t2);
        #endif
        char b[128];
        federateDB.timeManagementLRC->queryLogicalTime(*t);
        t->getPrintableString (b);
        federateDB.timeManagementLRC->queryLookahead(*l);
        l->getPrintableString (b);
        CORBA::WChar *wChar = L"sendInteractionWithRegion";
        throw GeRtiFactory::InvalidFederationTime(wChar);
      }

      eventMarket->addPushSupplierInteraction(theInteraction, theParameters, theTime, theTag, region, h.theSerialNumber, interactionDatum);
    }
    else
    {
      eventMarket->addPushSupplierInteraction(theInteraction, theParameters, theTag, region, interactionDatum);
    }

    transmissionArg.ps->release();
  }

  return h;
}

void NAMESPACE::Sender::sendInteractionWithRegion(
  GeRtiFactory::GeRtiHandle const &theInteraction,
  GeRtiFactory::HandleValues const &theParameters,
  GeRtiFactory::UserSuppliedTag const &theTag,
  GERTICO::HandleSet const &theRegions)
throw (
  GeRtiFactory::InteractionClassNotDefined,
  GeRtiFactory::InteractionClassNotPublished,
  GeRtiFactory::InteractionParameterNotDefined,
  GeRtiFactory::RegionNotKnown,
  GeRtiFactory::InvalidRegionContext,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
  if (federateDB.joined == false)
  {
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }
  CORBA::ULong i;
  CORBA::ULong len = theParameters.length();
  GERTICO::AttributeDatum interactionDatum;
  GERTICO::HandleMap::iterator itHM;
  GERTICO::HandleSet::const_iterator itRegion;
  GERTICO::Region *regionPtr;
  GeRtiFactory::GeRtiHandle region = 0;
  GeRtiFactory::GeRtiHandle spaceHandle = 0;
  std::wstring ws;

  checkSaveRestore();

  if (federateDB.declarationManagementLRC->isPublishingInteraction(theInteraction) == false)
  {
    ws = federateDB.supportingServicesLRC->getInteractionClassName(theInteraction);
    throw GeRtiFactory::InteractionClassNotPublished(L"sendInteraction");
  }

  for (itRegion = theRegions.begin(); itRegion != theRegions.end(); itRegion++)
  {
    // XX not correct!!
    region = *itRegion;

    // Get region to check space handle.
    regionPtr = federateDB.runTimeObjectDB->getRegion(*itRegion);
    if (regionPtr == NULL)
    {
      throw GeRtiFactory::RegionNotKnown(L"sendInteractionWithRegion");
    }
  }

  itHM = interactionHandleMap.find(theInteraction);
  if (itHM != interactionHandleMap.end())
  {
    spaceHandle = itHM->second;
  }
  else
  {
    spaceHandle = GeRtiAmb->getInteractionRoutingSpaceHandle(theInteraction);
    interactionHandleMap[theInteraction] = spaceHandle;
  }

  if (spaceHandle != regionPtr->getSpace())
  {
    throw GeRtiFactory::InvalidRegionContext(L"sendInteractionWithRegion");
  }

  for (i = 0; i < len; i++)
  {
    ws = federateDB.supportingServicesLRC->getParameterName(theParameters[i].id, theInteraction);
  }

  if (federateDB.supportingServicesLRC->getInteractionAttributeDatum(theInteraction, interactionDatum))
  {
    CORBA::WChar *wChar = L"getInteractionAttributeDatum";
    throw GeRtiFactory::RTIinternalError(wChar);
  }

//  if (federateDB.declarationManagementLRC->testInteractionSubscribers(theInteraction))
//  {
    eventMarket->addPushSupplierInteraction(theInteraction, theParameters, theTag, region, interactionDatum);

    transmissionArg.ps->release();
//  }
}

// 9.13
void NAMESPACE::Sender::requestClassAttributeValueUpdateWithRegion(
  GeRtiFactory::GeRtiHandle theClass,
  GERTICO::HandleSetMap &theAttRegMap,
  GeRtiFactory::UserSuppliedTag const &theTag)
throw (
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::RegionNotKnown,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_rCAVUWR_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_rCAVUWR_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  // Test for attribute not defined.
  checkAttributeNotDefined(theClass, theAttRegMap);

  federateDB.dataDistributionManagementLRC->requestClassAttributeValueUpdateWithRegions(theClass, theAttRegMap, theTag);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::getExtents(GeRtiFactory::GeRtiHandle const &theRegion, GeRtiFactory::GeRtiHandle &theSpace, GeRtiFactory::Extents &theExtents)
  throw(
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::RTIinternalError)
{
  GERTICO::Region *region = NULL;

  region = federateDB.runTimeObjectDB->getRegion(theRegion);
  if (region)
  {
    theSpace = region->getSpace();
    region->getExtents(theExtents);
  }
  else
  {
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }
}

//////////////////////////
// RTI Support Services //
//////////////////////////

// ---------------------------------------------------------------------------
// 10.2
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle
NAMESPACE::Sender::getObjectClassHandle(
  std::wstring const &theName)
throw (
  GeRtiFactory::NameNotFound,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError)
{
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_gOCH_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  return federateDB.supportingServicesLRC->getObjectClassHandle(theName);
}

// ---------------------------------------------------------------------------
// 10.3
// ---------------------------------------------------------------------------
std::wstring
NAMESPACE::Sender::getObjectClassName(
  GeRtiFactory::GeRtiHandle const &theHandle)
throw (
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_gOCN_e);
        #endif

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_gOCN_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  return federateDB.supportingServicesLRC->getObjectClassName(theHandle);
}

// ---------------------------------------------------------------------------
// 10.4
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle
NAMESPACE::Sender::getAttributeHandle(
  std::wstring const &theName,
  GeRtiFactory::GeRtiHandle const &whichClass)
throw (
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::NameNotFound,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError)
{
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_gAH_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  return federateDB.supportingServicesLRC->getAttributeHandle(theName, whichClass);
}

// ---------------------------------------------------------------------------
// 10.5
// ---------------------------------------------------------------------------
std::wstring
NAMESPACE::Sender::getAttributeName(
  GeRtiFactory::GeRtiHandle const &theHandle,
  GeRtiFactory::GeRtiHandle const &whichClass)
throw (
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_gAN_e);
        #endif

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_gAN_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  return federateDB.supportingServicesLRC->getAttributeName(theHandle, whichClass);
}

// ---------------------------------------------------------------------------
// 10.6
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle
NAMESPACE::Sender::getInteractionClassHandle(
  std::wstring const &theName)
throw (
  GeRtiFactory::NameNotFound,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError)
{
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_gICH_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  return federateDB.supportingServicesLRC->getInteractionClassHandle(theName);
}

// ---------------------------------------------------------------------------
// 10.7
// ---------------------------------------------------------------------------
std::wstring
NAMESPACE::Sender::getInteractionClassName(
  GeRtiFactory::GeRtiHandle const &theHandle)
throw (
  GeRtiFactory::InteractionClassNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_gICN_e);
        #endif

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_gICN_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  return federateDB.supportingServicesLRC->getInteractionClassName(theHandle);
}

// ---------------------------------------------------------------------------
// 10.8
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle
NAMESPACE::Sender::getParameterHandle
(
  std::wstring const &theName,
  GeRtiFactory::GeRtiHandle const &whichClass
)
throw
(
  GeRtiFactory::InteractionClassNotDefined,
  GeRtiFactory::NameNotFound,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError
)
{
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_gPH_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  return federateDB.supportingServicesLRC->getParameterHandle(theName, whichClass);
}

// ---------------------------------------------------------------------------
// 10.9
// ---------------------------------------------------------------------------
std::wstring
NAMESPACE::Sender::getParameterName(
  GeRtiFactory::GeRtiHandle const &theHandle,
  GeRtiFactory::GeRtiHandle const &whichClass)
throw (
  GeRtiFactory::InteractionClassNotDefined,
  GeRtiFactory::InteractionParameterNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_gPN_q);
        #endif

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_gPN_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  return federateDB.supportingServicesLRC->getParameterName(theHandle, whichClass);
}

// ---------------------------------------------------------------------------
// 10.10
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle
NAMESPACE::Sender::getObjectInstanceHandle(
  std::wstring const &theName)
throw (
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError)
{
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_gOIH1_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  GeRtiFactory::GeRtiHandle ret = 0;

  ret = federateDB.supportingServicesLRC->getObjectInstanceHandle(theName);

  return ret;
}

// ---------------------------------------------------------------------------
// 10.11
// ---------------------------------------------------------------------------
std::wstring
NAMESPACE::Sender::getObjectInstanceName
(
  GeRtiFactory::GeRtiHandle const &theHandle
)
throw
(
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError
)
{
        #ifdef GalDebug
        E0(S_gOIH2_e);
        #endif

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_gOIH2_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  std::wstring ret;

  ret = federateDB.supportingServicesLRC->getObjectInstanceName(theHandle);

        #ifdef GalDebug
        E0(S_gOIH2_l);
        #endif
  return ret;
}

// ---------------------------------------------------------------------------
// 10.12
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle
NAMESPACE::Sender::getRoutingSpaceHandle(
  std::wstring const &theName)
throw (
  GeRtiFactory::NameNotFound,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError)
{
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_gRSH_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  GeRtiFactory::GeRtiHandle ret = 0;

  ret = federateDB.supportingServicesLRC->getRoutingSpaceHandle(theName);

  return ret;
}

// ---------------------------------------------------------------------------
// 10.13
// ---------------------------------------------------------------------------
std::wstring
NAMESPACE::Sender::getRoutingSpaceName(
//
// This const was removed for the RTI 1.3 NG to work around a limitation of
// the Sun 4.2 C++ compiler regarding template instantiation.  The const
// is unnecessary.
//
/* const */ GeRtiFactory::GeRtiHandle theHandle) // supplied C4
throw (
  GeRtiFactory::SpaceNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_gRSN_q);
        #endif

  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_gRSN_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  std::wstring ret;

  ret = federateDB.supportingServicesLRC->getRoutingSpaceName(theHandle);

  return ret;
}

// ---------------------------------------------------------------------------
// 10.14
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle
NAMESPACE::Sender::getDimensionHandle(
  std::wstring const &theName,
  GeRtiFactory::GeRtiHandle const &whichSpace)
throw (
  GeRtiFactory::SpaceNotDefined,
  GeRtiFactory::NameNotFound,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError)
{
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_gDH_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  GeRtiFactory::GeRtiHandle ret = 0;

  ret = federateDB.supportingServicesLRC->getDimensionHandle(theName, whichSpace);

  return ret;
}

// ---------------------------------------------------------------------------
// 10.15
// ---------------------------------------------------------------------------
std::wstring
NAMESPACE::Sender::getDimensionName(
  GeRtiFactory::GeRtiHandle theHandle,
  GeRtiFactory::GeRtiHandle whichSpace)
throw (
  GeRtiFactory::SpaceNotDefined,
  GeRtiFactory::DimensionNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_gDN_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_gDN_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  std::wstring ret;

  ret = federateDB.supportingServicesLRC->getDimensionName(theHandle, whichSpace);

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle NAMESPACE::Sender::getDimensionUpperBound(
  GeRtiFactory::GeRtiHandle const &theHandle)
throw(
  GeRtiFactory::DimensionNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::RTIinternalError)
{
  if (federateDB.joined == false)
  {
    CORBA::WChar *buff = L"getDimensionUpperBound";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  GeRtiFactory::GeRtiHandle ret;

  ret = federateDB.supportingServicesLRC->getDimensionUpperBound(theHandle);

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::getAvailableDimensionsForClassAttribute(
  GeRtiFactory::GeRtiHandle const & theClass,
  GeRtiFactory::GeRtiHandle const & theHandle,
  GeRtiFactory::Handles &theDimensions)
throw(
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::AttributeNotKnown,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::RTIinternalError)
{
  if (federateDB.joined == false)
  {
    CORBA::WChar *buff = L"getAvailableDimensionsForClassAttribute";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  federateDB.supportingServicesLRC->getAvailableDimensionsForClassAttribute(theClass, theHandle, theDimensions);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::getAvailableDimensionsForInteractionClass(
    GeRtiFactory::GeRtiHandle const &theClass,
    GeRtiFactory::Handles &theDimensions
  )
  throw (
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError)
{
  if (federateDB.joined == false)
  {
    CORBA::WChar *buff = L"getAvailableDimensionsForInteractionClass";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  federateDB.supportingServicesLRC->getAvailableDimensionsForInteractionClass(theClass, theDimensions);
}

// ---------------------------------------------------------------------------
// 10.16
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle
NAMESPACE::Sender::getAttributeRoutingSpaceHandle(
  GeRtiFactory::GeRtiHandle theHandle,
  GeRtiFactory::GeRtiHandle whichClass)
throw (
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_gARSH_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_gARSH_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  GeRtiFactory::GeRtiHandle ret;

  ret = federateDB.supportingServicesLRC->getAttributeRoutingSpaceHandle(theHandle, whichClass);

  return ret;
}

// ---------------------------------------------------------------------------
// 10.17
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle
NAMESPACE::Sender::getObjectClass(
  GeRtiFactory::GeRtiHandle theObject)
throw (
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_gOC_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_gOC_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  GeRtiFactory::GeRtiHandle ret = 0;

  ret = federateDB.supportingServicesLRC->getObjectClass(theObject);

  return ret;
}

// ---------------------------------------------------------------------------
// 10.18
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle
NAMESPACE::Sender::getInteractionRoutingSpaceHandle(
  GeRtiFactory::GeRtiHandle theHandle)
throw (
  GeRtiFactory::InteractionClassNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_gIRSH_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_gIRSH_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  GeRtiFactory::GeRtiHandle ret = 0;

  ret = federateDB.supportingServicesLRC->getInteractionRoutingSpaceHandle(theHandle);

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::getDimensionHandleSet (
  GeRtiFactory::GeRtiHandle const &theRegionHandle,
  GeRtiFactory::Handles &theDimensions
)
throw (
  CORBA::SystemException,
  GeRtiFactory::RegionNotKnown,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
  if (federateDB.joined == false)
  {
    CORBA::WChar *buff = L"getDimensionHandleSet";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  federateDB.supportingServicesLRC->getDimensionHandleSet(theRegionHandle, theDimensions);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::getRangeBounds (
  GeRtiFactory::GeRtiHandle const &theRegionHandle,
  GeRtiFactory::GeRtiHandle const &theDimensionHandle,
  GeRtiFactory::Handles &theRangeBounds
)
throw (
  CORBA::SystemException,
  GeRtiFactory::RegionNotKnown,
  GeRtiFactory::RegionDoesNotContainSpecifiedDimension,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
  if (federateDB.joined == false)
  {
    CORBA::WChar *buff = L"getRangeBounds";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  federateDB.supportingServicesLRC->getRangeBounds(theRegionHandle, theDimensionHandle, theRangeBounds);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::setRangeBounds (
  GeRtiFactory::GeRtiHandle const &theRegionHandle,
  GeRtiFactory::GeRtiHandle const &theDimensionHandle,
  GeRtiFactory::GeRtiHandle theLowerBound,
  GeRtiFactory::GeRtiHandle theUpperBound
)
throw (
  CORBA::SystemException,
  GeRtiFactory::RegionNotKnown,
  GeRtiFactory::RegionNotCreatedByThisFederate,
  GeRtiFactory::RegionDoesNotContainSpecifiedDimension,
  GeRtiFactory::InvalidRangeBound,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
  if (federateDB.joined == false)
  {
    CORBA::WChar *buff = L"setRangeBounds";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  federateDB.supportingServicesLRC->setRangeBounds(theRegionHandle, theDimensionHandle, theLowerBound, theUpperBound);
}

// ---------------------------------------------------------------------------
// 10.23
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::enableClassRelevanceAdvisorySwitch()
throw (
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_eCRAS_e);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_eCRAS_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  federateDB.supportingServicesLRC->enableClassRelevanceAdvisorySwitch();
        #ifdef GalDebug
        E0(S_eCRAS_l);
        #endif
}

// ---------------------------------------------------------------------------
// 10.24
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::disableClassRelevanceAdvisorySwitch()
throw (
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_dCRAS_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_dCRAS_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  federateDB.supportingServicesLRC->disableClassRelevanceAdvisorySwitch();
}

// ---------------------------------------------------------------------------
// 10.25
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::enableAttributeRelevanceAdvisorySwitch()
throw (
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_eARAS_e);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_eARAS_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  federateDB.supportingServicesLRC->enableAttributeRelevanceAdvisorySwitch();
        #ifdef GalDebug
        E0(S_eARAS_l);
        #endif
}

// ---------------------------------------------------------------------------
// 10.26
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::disableAttributeRelevanceAdvisorySwitch()
throw (
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_dARAS_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_dARAS_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  federateDB.supportingServicesLRC->disableAttributeRelevanceAdvisorySwitch();
}

// ---------------------------------------------------------------------------
// 10.27
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::enableAttributeScopeAdvisorySwitch()
throw (
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_eASAS_e);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_eASAS_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  federateDB.supportingServicesLRC->enableAttributeScopeAdvisorySwitch();
        #ifdef GalDebug
        E0(S_eASAS_l);
        #endif
}

// ---------------------------------------------------------------------------
// 10.28
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::disableAttributeScopeAdvisorySwitch()
throw (
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_dASAS_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_dASAS_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  federateDB.supportingServicesLRC->disableAttributeScopeAdvisorySwitch();
}

// ---------------------------------------------------------------------------
// 10.29
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::enableInteractionRelevanceAdvisorySwitch()
throw (
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_eIRAS_e);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_eIRAS_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  federateDB.supportingServicesLRC->enableInteractionRelevanceAdvisorySwitch();
        #ifdef GalDebug
        E0(S_eIRAS_l);
        #endif
}

// ---------------------------------------------------------------------------
// 10.30
// ---------------------------------------------------------------------------
void NAMESPACE::Sender::disableInteractionRelevanceAdvisorySwitch()
throw (
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError)
{
        #ifdef GalDebug
        E0(S_dIRAS_q);
        #endif
  if (federateDB.joined == false)
  {
        #ifdef GalDebug
        E0(S_dIRAS_t1);
        #endif
    CORBA::WChar *buff = L"";
    throw GeRtiFactory::FederateNotExecutionMember(buff);
  }

  checkSaveRestore();

  federateDB.supportingServicesLRC->disableInteractionRelevanceAdvisorySwitch();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
CORBA::Boolean
NAMESPACE::Sender::tick()
{
        #ifdef GalDebug
        E0(S_t2_e);
        #endif
  CORBA::Boolean ret = 0;
  double d = 0.0;

  if (federateDB.joined == false)
  {
    return ret;
  }

  ret = tickWork(false, d, d);
  ACE_Thread::yield();

        #ifdef GalDebug
        E0(S_t2_l);
        #endif
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
CORBA::Boolean
NAMESPACE::Sender::tick(
  double const &minimum,
  double const &maximum)
{
        #ifdef GalDebug
        E0(S_t3_e);
        #endif
  CORBA::Boolean retCorba = 0;
  bool ret = false;

  // Strip off decimal value.
  long sec = minimum;

  // Take decimal value.
  long usec = (long) ((minimum - sec) * 1000000);

  // time values must be >0
  if (sec<0)
  {
    sec *= -1;
    usec *= -1;
  }

  if (federateDB.joined == false)
  {
    ACE_OS::sleep (ACE_Time_Value(sec,usec));
    return ret;
  }

  ret = tickWork(true, minimum, maximum);
  ACE_Thread::yield();

        #ifdef GalDebug
        E0(S_t3_l);
        #endif
  if (ret)
  {
    retCorba = 1;
  }

  return retCorba;
}

