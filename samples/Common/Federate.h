#ifndef Federate_h
#define Federate_h

#include <RTI.hh>
#include <fedtime.hh>



class Federate
{
public:
	RTI::RTIambassador   rtiAmb;         // libRTI provided
	RTI::FederateHandle  federateId;     // assigned to federated

	void join (RTI::FederateAmbassadorPtr fedAmb);
};





#endif

