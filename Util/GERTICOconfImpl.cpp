/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** GERTICOconfImpl.cpp
**
*******************************************************************************/

#include <stdio.h>
#include "GERTICOconfImpl.h"

// Best practice for fixed strings.
static XMLCh Crash_ResignActionXMLCh[]={ chLatin_C, chLatin_r, chLatin_a, chLatin_s, chLatin_h, chUnderscore, chLatin_R, chLatin_e, chLatin_s, chLatin_i, chLatin_g, chLatin_n, chLatin_A, chLatin_c, chLatin_t, chLatin_i, chLatin_o, chLatin_n, chNull };
static XMLCh DTDfileXMLCh[]={ chLatin_D, chLatin_T, chLatin_D, chLatin_f, chLatin_i, chLatin_l, chLatin_e, chNull };
static XMLCh DataLengthXMLCh[]={ chLatin_D, chLatin_a, chLatin_t, chLatin_a, chLatin_L, chLatin_e, chLatin_n, chLatin_g, chLatin_t, chLatin_h, chNull };
static XMLCh EventHubXMLCh[]={ chLatin_E, chLatin_v, chLatin_e, chLatin_n, chLatin_t, chLatin_H, chLatin_u, chLatin_b, chNull };
static XMLCh EventHubsXMLCh[]={ chLatin_E, chLatin_v, chLatin_e, chLatin_n, chLatin_t, chLatin_H, chLatin_u, chLatin_b, chLatin_s, chNull };
static XMLCh GerticoEventHubXMLCh[]={ chLatin_G, chLatin_e, chLatin_r, chLatin_t, chLatin_i, chLatin_c, chLatin_o, chLatin_E, chLatin_v, chLatin_e, chLatin_n, chLatin_t, chLatin_H, chLatin_u, chLatin_b, chNull };
static XMLCh LogicalTime1516XMLCh[]={ chLatin_L, chLatin_o, chLatin_g, chLatin_i, chLatin_c, chLatin_a, chLatin_l, chLatin_T, chLatin_i, chLatin_m, chLatin_e, chDigit_1, chDigit_5, chDigit_1, chDigit_6, chNull };
static XMLCh ModelPathXMLCh[]={ chLatin_M, chLatin_o, chLatin_d, chLatin_e, chLatin_l, chLatin_P, chLatin_a, chLatin_t, chLatin_h, chNull };
static XMLCh NamingServiceXMLCh[]={ chLatin_N, chLatin_a, chLatin_m, chLatin_i, chLatin_n, chLatin_g, chLatin_S, chLatin_e, chLatin_r, chLatin_v, chLatin_i, chLatin_c, chLatin_e, chNull };
static XMLCh SemiColonXMLCh[]={ chSemiColon, chNull };
static XMLCh SyncScopeXMLCh[]={ chLatin_S, chLatin_y, chLatin_n, chLatin_c, chLatin_S, chLatin_c, chLatin_o, chLatin_p, chLatin_e, chNull };
static XMLCh TransmissionWait_msXMLCh[]={ chLatin_T, chLatin_r, chLatin_a, chLatin_n, chLatin_s, chLatin_m, chLatin_i, chLatin_s, chLatin_s, chLatin_i, chLatin_o, chLatin_n, chLatin_W, chLatin_a, chLatin_i, chLatin_t, chUnderscore, chLatin_m, chLatin_s, chNull };
static XMLCh endPointXMLCh[]={ chLatin_e, chLatin_n, chLatin_d, chLatin_P, chLatin_o, chLatin_i, chLatin_n, chLatin_t, chNull };
static XMLCh rootEntryXMLCh[]={ chLatin_r, chLatin_o, chLatin_o, chLatin_t, chLatin_E, chLatin_n, chLatin_t, chLatin_r, chLatin_y, chNull };

/*******************************************************************************
** returns the text content of the one and only TextNode Child Element
**
*******************************************************************************/
char* getTextContent (DOMNode* n)
{
  if (n->getNodeType() == DOMNode::ELEMENT_NODE)
    return XMLString::transcode (n->getFirstChild()->getNodeValue());
  else
    return "";
}
const XMLCh* getContent (DOMNode* n)
{
  if (n->getNodeType() == DOMNode::ELEMENT_NODE)
    return n->getFirstChild()->getNodeValue();
  else
    return 0;
}


/*******************************************************************************
**
**
********************************************************************************/
NS_xml::NS_xml (DOMNode* n)
{
  endPoint = "iiop";
  rootEntry = "GeRTI";

  for (DOMNode* child = n->getFirstChild(); child != 0; child=child->getNextSibling())
  {
    if ( XMLString::compareString(child->getNodeName(), endPointXMLCh) == 0 )
      endPoint = getTextContent (child);
    if ( XMLString::compareString(child->getNodeName(), rootEntryXMLCh) == 0 )
      rootEntry = getTextContent (child);
  }
};




/*******************************************************************************
**
**
********************************************************************************/
XercesDOMParser *GERTICOconf_xml::parser = 0;

GERTICOconf* GERTICOconf::singelton = 0;


/*******************************************************************************
**
**
********************************************************************************/
GERTICOconf* GERTICOconf::parseFromFile (const string &fileName)
{
  if (singelton != 0) return singelton;

  if (GERTICOconf_xml::parser == 0)
  {
    // Initialize the XML4C system
    try
    {
      XMLPlatformUtils::Initialize();
    }

    catch (const XMLException& /*toCatch*/)
    {
//      std::cerr << "Error during initialization! :\n"
//           << StrX(toCatch.getMessage()) << std::endl;
    }

    // Instantiate the DOM parser.
    GERTICOconf_xml::parser = new XercesDOMParser();
    GERTICOconf_xml::parser->setValidationScheme(XercesDOMParser::Val_Auto);
  }

  // And create our error handler and install it
  GERTICOconf_xml::parser->setErrorHandler(HLAparseErrorHandler::getErrorHandler());

  GERTICOconf_xml::parser->parse (fileName.c_str ());


  GERTICOconf_xml* conf = 0;
  if (GERTICOconf_xml::parser->getDocument() != 0)
  {
    conf = new GERTICOconf_xml(GERTICOconf_xml::parser->getDocument());
  }

  if (HLAparseErrorHandler::getErrorHandler()->getSawErrors())
  {
//    std::cout << "GERTICOconf Parser: Errors!" << std::endl;
    conf = 0;
  }
  singelton = conf;
  return conf;
};

/*******************************************************************************
**
**
*******************************************************************************/
bool GERTICOconf_xml::hasMorePath ()
{
  return ModelPath->hasMoreTokens();
}

/*******************************************************************************
**
**
*******************************************************************************/
char* GERTICOconf_xml::nextPath()
{
  XMLCh *ch = ModelPath->nextToken();
  XMLString::trim(ch);
  return XMLString::transcode (ch);
}



/*******************************************************************************
**
**
********************************************************************************/
GERTICOconf_xml::GERTICOconf_xml(DOMDocument* doc)
{
  DOMElement* elem = doc->getDocumentElement();
  DOMNode *child0;
  GERTICO::StringSet::iterator itStringSet;
  char *textPointer;

  dataLength = 1024;
  logicalTimeLibrary = "fedtime1516";
  resignAction = 4;
  syncScope = "SYNC_WITH_TARGET";
  transmissionWait_ms = 1;

  for (DOMNode* child = elem->getFirstChild(); child != 0; child=child->getNextSibling())
  {
    // ---------------------------------------------------------------------------
    if (XMLString::compareString(child->getNodeName(), DTDfileXMLCh) == 0)
    {
      if (child->getNodeType() == DOMNode::ELEMENT_NODE)
      {
        textPointer = XMLString::transcode(child->getFirstChild()->getNodeValue());
        DTDfile = textPointer;
        XMLString::release(&textPointer);
      }
    }

    // ---------------------------------------------------------------------------
    if (XMLString::compareString(child->getNodeName(), ModelPathXMLCh) == 0)
    {
      stringModelPath = getContent(child);
      ModelPath = new XMLStringTokenizer(stringModelPath, SemiColonXMLCh);
    }

    // ---------------------------------------------------------------------------
    if (XMLString::compareString(child->getNodeName(), NamingServiceXMLCh) == 0)
      ns = new NS_xml (child);

    // ---------------------------------------------------------------------------
    if (XMLString::compareString(child->getNodeName(), Crash_ResignActionXMLCh) == 0)
    {
      if (child->getNodeType() == DOMNode::ELEMENT_NODE)
      {
        textPointer = XMLString::transcode(child->getFirstChild()->getNodeValue());
        if (strcmp(textPointer, "unconditionallyDivestAttributes") == 0)
        {
          resignAction = 0;
        }
        if (strcmp(textPointer, "deleteObjects") == 0)
        {
          resignAction = 1;
        }
        if (strcmp(textPointer, "cancelPendingOwnershipAcquisitions") == 0)
        {
#ifdef IEEE_1516
          resignAction = 2;
#else
          resignAction = 5;
#endif
        }
        if (strcmp(textPointer, "deleteObjectsThenDivest") == 0)
        {
          resignAction = 3;
        }
        if (strcmp(textPointer, "cancelThenDeleteThenDivest") == 0)
        {
#ifdef IEEE_1516
          resignAction = 4;
#else
          resignAction = 3;
#endif
        }
        if (strcmp(textPointer, "noAction") == 0)
        {
          resignAction = 5;
        }
        XMLString::release(&textPointer);
      }
    }

    // ---------------------------------------------------------------------------
    if ( XMLString::compareString(child->getNodeName(), DataLengthXMLCh) == 0 )
    {
      if (child->getNodeType() == DOMNode::ELEMENT_NODE)
      {
        textPointer = XMLString::transcode(child->getFirstChild()->getNodeValue());
        sscanf(textPointer, "%d", &dataLength);
        XMLString::release(&textPointer);
      }
    }

    // ---------------------------------------------------------------------------
    if (XMLString::compareString(child->getNodeName(), EventHubsXMLCh) == 0 )
    {
      for (child0 = child->getFirstChild(); child0 != 0; child0=child0->getNextSibling())
      {
        if (XMLString::compareString(child0->getNodeName(), EventHubXMLCh) == 0 )
        {
          if (child0->getNodeType() == DOMNode::ELEMENT_NODE)
          {
            textPointer = XMLString::transcode(child0->getFirstChild()->getNodeValue());
            configuredHubs.insert(textPointer);
            XMLString::release(&textPointer);
          }
        }
      }
    }

    // ---------------------------------------------------------------------------
    if (XMLString::compareString(child->getNodeName(), GerticoEventHubXMLCh) == 0 )
    {
      if (child->getNodeType() == DOMNode::ELEMENT_NODE)
      {
        textPointer = XMLString::transcode(child->getFirstChild()->getNodeValue());
        gertiHub = textPointer;
        XMLString::release(&textPointer);
      }
    
      itStringSet = configuredHubs.find(gertiHub.c_str());
      if (itStringSet == configuredHubs.end())
      {
        std::cout << "Configuration file inconsistent: gerti hub not in the list of hubs" << std::endl;
        exit(1);
      }
    }

    // ---------------------------------------------------------------------------
    if (XMLString::compareString(child->getNodeName(), LogicalTime1516XMLCh) == 0 )
    {
      if (child->getNodeType() == DOMNode::ELEMENT_NODE)
      {
        textPointer = XMLString::transcode(child->getFirstChild()->getNodeValue());
        logicalTimeLibrary = textPointer;
        XMLString::release(&textPointer);
      }
    }

    // ---------------------------------------------------------------------------
    if (XMLString::compareString(child->getNodeName(), SyncScopeXMLCh) == 0 )
    {
      if (child->getNodeType() == DOMNode::ELEMENT_NODE)
      {
        textPointer = XMLString::transcode(child->getFirstChild()->getNodeValue());
        syncScope = textPointer;
        XMLString::release(&textPointer);
        if (syncScope != "SYNC_WITH_TARGET" && syncScope != "SYNC_NONE" && syncScope != "SYNC_WITH_SERVER" && syncScope != "SYNC_WITH_TRANSPORT")
        {
          std::cerr << "ERROR: SyncScope in GERTICOconf.xml INVALID! Found: " << syncScope << std::endl;
          std::cerr << "USING SYNC_WITH_TARGET" << std::endl << std::endl;
        }
      }
    }

    // ---------------------------------------------------------------------------
    if (XMLString::compareString(child->getNodeName(), TransmissionWait_msXMLCh) == 0 )
    {
      if (child->getNodeType() == DOMNode::ELEMENT_NODE)
      {
        textPointer = XMLString::transcode(child->getFirstChild()->getNodeValue());
        sscanf(textPointer, "%d", &transmissionWait_ms);
        XMLString::release(&textPointer);
        if (transmissionWait_ms == 0)
        {
          transmissionWait_ms = 1;
        }
      }
    }
  }
}

/*******************************************************************************
**
**
********************************************************************************/
void GERTICOconf_xml::resetPath()
{
  delete ModelPath;
  ModelPath = ModelPath = new XMLStringTokenizer(
                        stringModelPath,
                        XMLString::transcode (";"));
}

/*******************************************************************************
**
**
********************************************************************************/
GERTICOconf_xml::~GERTICOconf_xml ()
{
  delete ModelPath;
  XMLPlatformUtils::Terminate();
};

