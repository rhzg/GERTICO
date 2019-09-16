/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: PrintFilter.h,v $
Revision 1.1  2004/04/19 14:37:05  mul
Add programs for DOM writer.

 
**
*******************************************************************************/

#ifndef PrintFilter_HEADER_GUARD_
#define PrintFilter_HEADER_GUARD_

#include <xercesc/dom/DOMWriterFilter.hpp>

XERCES_CPP_NAMESPACE_USE

namespace GERTICO
{
  class PrintFilter : public DOMWriterFilter
  {
  public:

    PrintFilter(unsigned long whatToShow = DOMNodeFilter::SHOW_ALL);

    ~PrintFilter(){};

    virtual short acceptNode(const DOMNode*) const;

    virtual unsigned long getWhatToShow() const {return fWhatToShow;};

    virtual void          setWhatToShow(unsigned long toShow) {fWhatToShow = toShow;};

  private:
    // unimplemented copy ctor and assignement operator
    PrintFilter(const PrintFilter&);
    PrintFilter & operator = (const PrintFilter&);

    unsigned long fWhatToShow;
  };
};

#endif
