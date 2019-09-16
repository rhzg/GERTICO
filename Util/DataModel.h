#ifndef DataModel_HEADER
#define DataModel_HEADER

/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: DataModel.h,v $
Revision 1.6  2009/06/12 12:12:55  mul
Use thread mutex.

Revision 1.5  2007/09/25 08:05:30  mul
Changes for ddm.

Revision 1.4  2007/09/05 14:59:34  mul
Changes for ieee1516.

Revision 1.3  2007/03/12 12:57:49  mul
Changed string to wstring.

Revision 1.2  2005/02/11 14:46:33  mul
Add scoping.

Revision 1.1  2004/05/28 11:55:10  mul
Add new files.


**
*******************************************************************************/


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------

#include "ace/Synch.h"
#include <map>
#include <string>
#include <vector>
#include "Util/Exception.h"
#include "Util/NextHandle.h"

#include "ClassInfo.h"
#include "FedParser.h"
#include "GeRtiTypes.h"

namespace GERTICO
{
  enum OMT_TYPE { FOM, SOM };
  class ObjectClassNotDefined {};
  class AttributeNotDefined {};

  /*******************************************************************************
  **
  **
  *******************************************************************************/
  class FedDimension
  {
      std::wstring dataType;
      std::wstring name;
      unsigned long id;
      unsigned long upperBound;

  public:
#ifdef IEEE_1516
      FedDimension(std::wstring const &theName, std::wstring const &theDataType, unsigned long const &theUpperBound, GERTICO::NextHandle &theIdHandler);
#else
      FedDimension(std::wstring const &theName, GERTICO::NextHandle &theIdHandler);
#endif
      virtual ~FedDimension(void);

      std::wstring getName(void);
      unsigned long getId(void);
#ifdef IEEE_1516
      std::wstring getDataType(void);
      unsigned long getUpperBound(void);
#endif
  };

  typedef std::map <unsigned long, FedDimension*> FedDimensionMap;

  /*******************************************************************************
  **
  **
  *******************************************************************************/
  class FedSpace
  {
    std::wstring name;
    unsigned long id;

public:
    FedDimensionMap dimensions;

    FedSpace(std::wstring const &theName, GERTICO::NextHandle &theIdHandler);
    virtual ~FedSpace(void);

    std::wstring getName(void);
    unsigned long getId(void);
  };

  typedef std::map <unsigned long, FedSpace*> FedSpaceMap;

  /*******************************************************************************
  **
  **
  *******************************************************************************/
  class Attribute
  {
    GERTICO::HandleSet dimensions;
    std::wstring name;
    std::wstring space;
    unsigned long id;
    unsigned long ordering;
    unsigned long transportation;

  public:
    Attribute(std::wstring const &theName, std::wstring const &theSpace, unsigned long &theOrdering, unsigned long &theTransportation, GERTICO::HandleSet const &theDimensions, GERTICO::NextHandle &theIdHandler);
    virtual ~Attribute(void);
    std::wstring getName(void) { return name; };
    void print(void);
    void getDimensions(GERTICO::HandleSet &theDimensions);
    unsigned long getId(void) { return id; };
    unsigned long getOrdering(void) { return ordering; };
    std::wstring getSpace(void) { return space; };
    unsigned long getTransportation(void) { return transportation; };
  };


  /*******************************************************************************
  **
  **
  *******************************************************************************/
  class Parameter
  {
    // Just a dummy: dimensions are empty.
    GERTICO::HandleSet dimensions;
    std::wstring name;
    unsigned long id;

  public:
    Parameter(std::wstring const &theName, GERTICO::NextHandle &theIdHandler);
    virtual ~Parameter(void);
    // Just a dummy: dimensions are empty.
    void getDimensions(GERTICO::HandleSet &theDimensions);
    std::wstring getName(void) { return name; };
    void print(void);
    unsigned long getId(void) { return id; };
  };


  /*******************************************************************************
  **
  **
  *******************************************************************************/
  class ObjectClass
  {
    std::wstring name;
    unsigned long id;
    unsigned long sharing;

  public:
    ObjectClass(std::wstring const &theName, unsigned long const &theSharing, GERTICO::NextHandle &theIdHandler);
    virtual ~ObjectClass(void);
    std::map <unsigned long, ObjectClass*> childClasses;
    std::map <unsigned long, Attribute*> attributes;

    std::wstring getName(void) { return name;};
    void print(void);
    unsigned long getId(void) { return id; };
    unsigned long getSharing(void) { return sharing; };
  };

  /*******************************************************************************
  **
  **
  *******************************************************************************/
  class InteractionClass
  {
    GERTICO::HandleSet dimensions;
    std::wstring name;
    std::wstring space;
    unsigned long id;
    unsigned long ordering;
    unsigned long sharing;
    unsigned long transportation;

  public:
    InteractionClass(std::wstring const &theName, std::wstring const &theSpace, unsigned long &theOrdering, unsigned long &theTransport, unsigned long const &theSharing, GERTICO::HandleSet const &theDimensions, GERTICO::NextHandle &theIdHandler);
    virtual ~InteractionClass(void);
    std::map <unsigned long, InteractionClass*> childInteractions;
    std::map <unsigned long, Parameter*> parameters;

    virtual std::wstring getName(void) { return name;};
    virtual void print(void);
    virtual void getDimensions(GERTICO::HandleSet &theDimensions);
    virtual unsigned long getId(void) { return id; };
    virtual unsigned long getOrdering(void) { return ordering; };
    virtual std::wstring getSpace(void) { return space;};
    virtual unsigned long getSharing(void) { return sharing; };
    virtual unsigned long getTransportation(void) { return transportation; };
  };


  /*******************************************************************************
  **
  **
  *******************************************************************************/
  class ObjectModel
  {
  protected:
    std::string name;
    std::string DTDversion;
    std::string version;
    std::string type;

    ObjectClass* rootClass;
    InteractionClass* rootInteraction;
    std::map<unsigned long, unsigned long> parentRelations;
    std::map<unsigned long, GERTICO::ObjectClass*> allClasses;
    std::map<unsigned long, GERTICO::InteractionClass*> allInteractions;

  public:
    static ACE_Thread_Mutex pm;
#ifdef IEEE_1516
    FedDimensionMap fedDimensionMap;
#endif
    FedSpaceMap allFedSpaces;

    ObjectModel(void);
    virtual ~ObjectModel(void);
    std::string getName(void) {return name;};
    ObjectClass* getRootClass() {return rootClass;};
    InteractionClass* getRootInteraction() {return rootInteraction;};

    OMT_TYPE getType(void);
    void print(void);
    bool getParentId(unsigned long classId, unsigned long &parent);
    void getChildrenIds(unsigned long classId, std::vector<unsigned long> &children);
    unsigned long getAttributeId(unsigned long classId, std::wstring const &attributeName)
      throw(ObjectClassNotDefined, AttributeNotDefined);
  };


  /*******************************************************************************
  **
  **
  *******************************************************************************/
  class ObjectModelFactory
  {
  public:
    static ObjectModel* createObjectModel(std::wstring const &fileName, GERTICO::NextHandle &theIdHandler);
  };

};
#endif // DataModel_HEADER
