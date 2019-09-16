#ifdef _WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif
#include <iostream>

#include "Federate.h"


void Federate::join(RTI::FederateAmbassadorPtr fedAmb)
{
	std::cout << "Try to joinFederationExecution" << std::endl;
    try
    {
      federateId = rtiAmb.joinFederationExecution ("random", "Swarm", fedAmb); 
    }
    catch (RTI::FederationExecutionDoesNotExist&)
    {
		std::cout << "does not exist yet - create new Federation" << std::endl;
		try
		{
		    rtiAmb.createFederationExecution("Swarm", "Schwarm.fed"); 
		}
		catch (RTI::FederationExecutionAlreadyExists&)
		{
			std::cout << "FederationExecutionAlreadyExists" << std::endl;
		}
		catch (RTI::CouldNotOpenFED&)
		{
			std::cout << "CouldNotOpenFED" << std::endl;
		}
		catch (RTI::ErrorReadingFED&)
		{
			std::cout << "ErrorReadingFED" << std::endl;
		}
		catch (RTI::ConcurrentAccessAttempted&)
		{
			std::cout << "ConcurrentAccessAttempted" << std::endl;
		}
		catch (RTI::RTIinternalError&)
		{
			std::cout << "RTIinternalError" << std::endl;
		}

		federateId = rtiAmb.joinFederationExecution ("random", "Swarm", fedAmb); 
    }
}

