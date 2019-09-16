#ifndef CLASSINFO_H
  #define CLASSINFO_H
#include <vector>
#include <map>
#include <string>
#include "multitree"

// ClassInfo and ClassSet are classes to contain information from the fed file.
// A ClassInfo class is created for each node (space, object or interaction) as it is 
// parsed from the fed file.
// Since this information also may relate to routing (DM and DDM) ClassInfo
// retains information about mcast groups.  
// During join (but should be during create fedex) the parsing of the fed file results in
// the creation of MCast groups based on the value of ClassSet.CreateMCast.
//
// To do:
// -Incorporate any changes neede to support DDM
//

struct AttributeInfo
{
  std::wstring Name;
  unsigned long Handle;
  unsigned long Transport;
  unsigned long Ordering;
  std::wstring Space;
};

struct ObjectClassInfo
{
  std::wstring Name;
  std::wstring FullName;
  unsigned long Handle;
  multitree<unsigned long>::node_iterator ClassSubTree;
  std::vector<unsigned long> attributes;   // Including inherited attributes
  void addAttribute(unsigned long h) { attributes.push_back(h); }
};

struct ParameterInfo
{
  std::wstring Name;
  unsigned long Handle;
};

struct InteractionClassInfo
{
  std::wstring Name;
  std::wstring FullName;
  unsigned long Handle;
  unsigned long Transport;
  unsigned long Ordering;
  std::wstring Space;
  multitree<unsigned long>::node_iterator ClassSubTree;
  std::vector<unsigned long> parameters;
  void addParameter(unsigned long h) { parameters.push_back(h); }
};

struct SpaceInfo
{
  std::wstring Name;
  unsigned long Handle;
  std::vector<std::string> DimensionNames;
};

class FedPrivateData
{
public:
  // RTI state information -- each RTI ambassador has one of these structs
  std::map<std::string, unsigned long> TransportMap;
  std::map<std::string, unsigned long> OrderingMap;
  
  // Fed File information - Some of this will change during the execution
  //  e.g. transport and ordering, region association, etc.
  
  std::string FederationName;
  std::string FEDVersion;
  std::string DTDversion;
  std::vector<SpaceInfo> Spaces;
  std::map<unsigned long, AttributeInfo> Attributes;
  std::map<unsigned long, ObjectClassInfo> ObjectClasses;
  multitree<unsigned long> ObjectClassTree;
  std::map<unsigned long, ParameterInfo> Parameters;
  std::map<unsigned long, InteractionClassInfo> InteractionClasses;
  multitree<unsigned long> InteractionClassTree;

  FedPrivateData (void);
  virtual ~FedPrivateData (void);
};                                        

#endif // CLASSINFO_H
