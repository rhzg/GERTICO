#define GalHLADebug 1

#include "tao/BiDir_GIOP/BiDirGIOP.h"

#include "Country.hh"
#include "HwFederateAmbassador.hh"

#if !defined(WIN32) && !defined(VXWORKS) && !defined(__KCC) && (__SUNPRO_CC_COMPAT != 5)
#  include <stream.h>
#endif

#include <string.h>
#include <stdlib.h>

#if !defined(WIN32) && !defined(VXWORKS)
#  include <unistd.h>
#endif

#include <RTI.hh>

#if defined(WIN32)
#  include <windows.h>   // for "Sleep"
#  include <sys/timeb.h> // for "struct _timeb"
#  include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#elif defined(VXWORKS)
#  include <ace/OS.h>
#  include <iostream>
#  include <timers.h>
using std::cout;
using std::flush;
using std::endl;
using std::cerr;
#else
#  include <sys/time.h>
#endif

#include <fedtime.hh>

RTI::Boolean        timeAdvGrant = RTI::RTI_FALSE;
RTI::Boolean        TimeRegulation = RTI::RTI_FALSE;
RTI::Boolean        TimeConstrained = RTI::RTI_FALSE;
RTI::FedTime &          grantTime=(*(RTI::FedTimeFactory::makeZero()));

void printUsage( const char* pExeName )
{
   cout << "FED_HW: usage: "
        << pExeName
        << " <Country Name> <Initial Population> [<Number of Ticks>]"
        << endl;
}

int hw_main(int argc, char *argv[])
{
   double      PreviousPopulation[100]; 
   const char* exeName = argv[0];         // Name of executable process
   char* const fedExecName = "HelloWorld"; // Name of the Federation Execution
   Country*    myCountry = NULL;          // Pointer to Federate's Country
   int         numberOfTicks( 100 );
   long        TimeManaged = 1;

   int loopCounter = 0; 

   for(;loopCounter < 100; ++loopCounter)
   {
     PreviousPopulation[loopCounter] = 0.0;
   }

   loopCounter = 0;

   //------------------------------------------------------
   // Make sure executable is provided with correct number
   // of arguments.
   //------------------------------------------------------
   if (argc < 3)
   {
      printUsage( exeName );
      return -1;
   }
   else if ( !argv[1] && !argv[2] && (argc == 3 || !argv[3]) )
   {
      printUsage( exeName );
      return -1;
   }
   else
   {
      myCountry = new Country( argv[1], argv[2] );

      if ( argc > 3 )
      {
         numberOfTicks = atoi( argv[3] );
      }

      if ( argc > 4 )
      {
	TimeManaged = 0;
      }
   }

   try
   {
      //------------------------------------------------------
      // Create RTI objects
      //
      // The federate communicates to the RTI through the RTIambassador
      // object and the RTI communicates back to the federate through
      // the FederateAmbassador object.
      //------------------------------------------------------
      RTI::RTIambassador       rtiAmb;         // libRTI provided
      HwFederateAmbassador     fedAmb;         // User-defined

      // Named value placeholder for the federates handle -
      // we don't really use this in HelloWorld but some
      // services and MOM might need it - if we were to use them.
      RTI::FederateHandle      federateId;


#if defined(WIN32)
      struct _timeb tb;
      _ftime(&tb);
      
      cout << myCountry->GetName() << " " << tb.time << " " << 
       tb.millitm * 1000 << " START" << endl;
#elif defined(VXWORKS)
      struct timespec tp;
      clock_gettime(CLOCK_REALTIME, &tp);
      
      cout << myCountry->GetName() << " " << tp.tv_sec << " " <<
       tp.tv_nsec / 1000L << " START" << endl;
#else
      static struct timeval tp;
      gettimeofday(&tp, NULL);

      cout << myCountry->GetName() << " "
           << tp.tv_sec << " "
           << tp.tv_usec << " "
           << "START\n";
#endif

      RTI::Boolean Joined    = RTI::RTI_FALSE;
      int          numTries  = 0;

      //------------------------------------------------------
      // Here we loop around the joinFederationExecution call
      // until we try to many times or the Join is successful.
      // 
      // The federate that successfully CREATES the federation
      // execution will get to the join call before the 
      // FedExec is initializes and will be unsuccessful at
      // JOIN call.  In this loop we catch the
      // FederationExecutionDoesNotExist exception to
      // determine that the FedExec is not initialized and to
      // keep trying. If the JOIN call does not throw an
      // exception then we set Joined to TRUE and that will
      // cause us to exit the loop anf proceed in the execution.
      // The loop only repeats if a FederationExecutionDoesNotExist
      // exception was thrown.  Since the RTI 1.3 specification
      // has the inherent race condition that another process
      // could have destroyed the federation after this process
      // calls create, we need to create the federation each
      // time through this loop.
      //------------------------------------------------------
      while( !Joined && (numTries++ < 20) )
      {

        //------------------------------------------------------
        // Create federation execution.
        //
        // The RTI_CONFIG environment variable must be set in the 
        // shell's environment to the directory that contains
        // the RTI.rid file and the HelloWorld.fed
        //      
        // In RTI 1.3, when a federate creates the federation 
        // execution the $RTI_HOME/bin/$RTI_ARCH/fedex.sh process
        // is executed on the localhost. Therefore, the RTI_HOME 
        // environment variable must be set to the root of the 
        // RTI 1.0 distribution tree in the federate environment.
        //------------------------------------------------------
        try
        {
          //------------------------------------------------------
          // A successful createFederationExecution will cause
          // the fedex process to be executed on this machine.
          //
          // A "HelloWorld.fed" file must exist in the current
          // directory. This file specifies the FOM
          // object and interaction class structures as well as 
          // default/initial transport and ordering information for
          // object attributes and interaction classes.
          //------------------------------------------------------
          cout << "FED_HW: CREATING FEDERATION EXECUTION" << endl;
          rtiAmb.createFederationExecution( fedExecName, "HelloWorld.fed" ); 
          std::cout << "FED_HW: SUCCESSFUL CREATE FEDERATION EXECUTION" << std::endl;
        }
        catch ( RTI::FederationExecutionAlreadyExists& e )
        {
          cerr << "FED_HW: Note: Federation execution already exists." <<
           e << endl;
        }
        catch ( RTI::Exception& e )
        {
          cerr << "FED_HW: ERROR:" << e << endl;
          return -1;
        }
         //------------------------------------------------------
         // Join the named federation execution as the named
         // federate type.  Federate types (2nd argument to
         // joinFederationExecution) does not have to be unique
         // in a federation execution; however, the save/restore
         // services use this information but we are not doing
         // save/restore in HelloWorld so we won't worry about it
         // here (best to make the names unique if you do
         // save/restore unless you understand how save/restore
         // will use the information
         //
         //------------------------------------------------------
         try
         {
            std::cout << "FED_HW: JOINING FEDERATION EXECUTION: " << exeName << std::endl;

            federateId = rtiAmb.joinFederationExecution( myCountry->GetName(),
                                                         fedExecName, 
                                                         &fedAmb);
            Joined = RTI::RTI_TRUE; 
         }
         catch (RTI::FederateAlreadyExecutionMember& e)
         {
            cerr << "FED_HW: ERROR: " << myCountry->GetName()
                 << " already exists in the Federation Execution "
                 << fedExecName << "." << endl;
            cerr << e << endl;
            return -1;
         }
         catch (RTI::FederationExecutionDoesNotExist&)
         {
            cerr << "FED_HW: ERROR: " << fedExecName << " Federation Execution "
                 << "does not exists."<< endl;
	    rtiAmb.tick(2.0, 2.0);
         }
         catch ( RTI::Exception& e )
         {
            cerr << "FED_HW: ERROR:" << e << endl;
            return -1;
         }
      } // end of while

      std::cout << "FED_HW: JOINED SUCCESSFULLY: " << exeName 
           << ": Federate Handle = " << federateId << std::endl;

      //------------------------------------------------------
      // The Country class needs to determine what the RTI is
      // going to call its class type and its attribute's types.
      //
      // This is stored globally even though it is
      // theoretically possible for a federate to join more
      // than one Federation Execution and thus
      // possibly have more than one Run-Time mapping.
      //
      // Note: This has not been tested and may not work.
      //       This would require having an RTIambassador for
      //       each FederationExecution.
      //------------------------------------------------------
      Country::Init( &rtiAmb );


      //------------------------------------------------------
      // Publication/Subscription
      //
      // Declare my interests to the RTI for the object and
      // interaction data types I want to receive.  Also tell
      // the RTI the types of data I can produce.
      //
      // Note: In publication I am telling the RTI the type
      // of data I CAN produce not that I necessarily will.
      // In this program we will create all data types that
      // are published however in more advance applications
      // this convention allows migration of object &
      // attributes to other simulations as neccessary
      // through the Ownership Management services.
      //
      // NOTE: Each time an object or interaction class is
      //       subscribed or published it replaces the previous
      //       subscription/publication for that class.
      //------------------------------------------------------
      myCountry->PublishAndSubscribe();

      //------------------------------------------------------
      // Register my object with the federation execution.
      // This requires invoking the registerObject service 
      // which returns an HLA object handle. 
      //------------------------------------------------------
      myCountry->Register();

      // Set time step to 10
#ifdef FedTimeInteger
      const IntegerTime timeStep(10);
#else
      const RTIfedTime timeStep(10);
#endif
      timeAdvGrant = RTI::RTI_FALSE;

      try
      {
         std::cout << "FED_HW: ENABLING ASYNCHRONOUS DELIVERY" << std::endl;
         //------------------------------------------------------
         // Turn on asynchronous delivery of receive ordered
         // messages. This will allow us to receive messages that
         // are not TimeStamp Ordered outside of a time
         // advancement.
         //------------------------------------------------------
         rtiAmb.enableAsynchronousDelivery();
         rtiAmb.disableAsynchronousDelivery();
      }
      catch ( RTI::Exception& e )
      {
         cerr << "FED_HW: ERROR:" << e << endl;
      }

    if(TimeManaged)
    {
      //------------------------------------------------------
      // Set the Time Management parameters
      //
      // This version of HelloWorld operates as a time-stepped
      // simulation.  This means that it should be constrained
      // and regulating.
      //
      // In the 1.0 version of HelloWorld this section of code
      // was before the publication and subscription.  In 1.3
      // enableTimeConstrained and enableTimeRegulation 
      //------------------------------------------------------
      try
      {
         std::cout << "FED_HW: ENABLING TIME CONTRAINT" << std::endl;
         //------------------------------------------------------
         // Turn on constrained status so that regulating
         // federates will control our advancement in time.
         //
         // If we are constrained and sending fderates specify
         // the Country attributes and Communication interaction
         // with timestamp in the HelloWorld.fed file we will
         // receive TimeStamp Ordered messages.
         //------------------------------------------------------
         rtiAmb.enableTimeConstrained();
         timeAdvGrant = RTI::RTI_FALSE;
	 TimeConstrained = RTI::RTI_FALSE;

         //------------------------------------------------------
         // Tick the RTI until we gwt the timeConstrainedEnabled
         // callback with my current time.
         //------------------------------------------------------
         while ( !TimeConstrained )
         {
	   rtiAmb.tick(0.01, 1.0);
         }
      }
      catch ( RTI::Exception& e )
      {
         cerr << "FED_HW: ERROR:" << e << endl;
      }
      try
      {
//         std::cout << "FED_HW: ENABLING TIME REGULATION WITH LOOKAHEAD = " << Country::GetLookahead() << std::endl;
         //------------------------------------------------------
         // Turn on regulating status so that constrained
         // federates will be controlled by our time.
         //
         // If we are regulating and our Country attributes and
         // Communication interaction are specified with timestamp
         // in the HelloWorld.fed file we will send TimeStamp
         // Ordered messages.
         //------------------------------------------------------
         rtiAmb.enableTimeRegulation( grantTime, Country::GetLookahead());

         //------------------------------------------------------
         // enableTimeRegulation is an implicit timeAdvanceRequest
         // so set timeAdvGrant to TRUE since we will get a
         // timeRegulationEnabled which is an implicit 
         // timeAdvanceGrant
         //------------------------------------------------------
         timeAdvGrant = RTI::RTI_FALSE;
	 TimeRegulation = RTI::RTI_FALSE;

         //------------------------------------------------------
         // Tick the RTI until we gwt the timeRegulationEnabled
         // callback with my current time.
         //------------------------------------------------------
         while ( !TimeRegulation )
         {
	   rtiAmb.tick(0.01, 1.0);
         }
      }
      catch ( RTI::Exception& e )
      {
         cerr << "FED_HW: ERROR:" << e << endl;
      }
    }
      //------------------------------------------------------
      // Event Loop
      // ----------
      // 
      // 1.) Calculate current state and update to RTI.
      // 2.) Ask for a time advance.
      // 3.) Tick the RTI waiting for the grant and process all
      //     RTI initiated services (especially reflections).
      // 4.) Repeat.
      //------------------------------------------------------
      int counter = 0;

      while ( counter++ < numberOfTicks-1 )
      {
         cout << "FED_HW: " << endl;
         cout << "FED_HW: HelloWorld Event Loop Iteration #: " << counter << endl; 

         //------------------------------------------------------
         // 1.) - Update current state
         //------------------------------------------------------
         myCountry->Update( grantTime );

         // Print state of all countries
         Country* pCountry = NULL;
         for ( unsigned int i = 0; i < Country::ms_extentCardinality; i++ )
         {
            pCountry = Country::ms_countryExtent[ i ];

            if ( pCountry )
            {
               cout << "FED_HW: Country[" << i << "] " << pCountry << endl;

	       // Start of the modification
	       if(pCountry->GetPopulation() == PreviousPopulation[i])
	       {
		 cout << "*************** Not Updated ************\n";
	       }
	       PreviousPopulation[i] = pCountry->GetPopulation();
	       // End of the modification
            }

         }

         //------------------------------------------------------
         // 2.) - Ask for a time advance.
         //------------------------------------------------------
	 if(RTI::RTI_FALSE)
	   {
	     try
	       {
#ifdef FedTimeInteger
		 IntegerTime requestTime(timeStep.getTime());
#else
		 RTIfedTime requestTime(timeStep.getTime());
#endif


		 requestTime += grantTime;
		 timeAdvGrant = RTI::RTI_FALSE;
		 loopCounter++;
		 rtiAmb.timeAdvanceRequest( requestTime );
	       }
	     catch ( RTI::Exception& e )
	       {
		 cerr << "FED_HW: ERROR: " << e << endl;
	       }
	   }
	 else
	   {
	     //------------------------------------------------------
	     // 2.) - Ask for a next event request advance.
	     //------------------------------------------------------
	     try
	       {
#ifdef FedTimeInteger
		 IntegerTime requestTime(timeStep.getTime());
#else
		 RTIfedTime requestTime(timeStep.getTime());
#endif

		 requestTime += grantTime;
		 timeAdvGrant = RTI::RTI_FALSE;
		 loopCounter = 0;
		 rtiAmb.nextEventRequest( requestTime );
	       }
	     catch ( RTI::Exception& e )
	       {
		 cerr << "FED_HW: ERROR: " << e << endl;
	       }
	   }

         //------------------------------------------------------
         // 3.) Tick the RTI waiting for the grant and process all
         //     RTI initiated services (especially reflections).
         //------------------------------------------------------
	 if( TimeManaged )
          while( timeAdvGrant != RTI::RTI_TRUE )
          {
            //------------------------------------------------------
            // Tick will turn control over to the RTI so that it can
            // process an event.  This will cause an invocation of one
            // of the federateAmbassadorServices methods.
            //
            // Be sure not to invoke the RTIambassadorServices from the
            // federateAmbassadorServices; otherwise, a ConcurrentAccess
            // exception will be thrown.
            //------------------------------------------------------
	   
	    rtiAmb.tick(0.01, 1.0);
          }
	 else
	   rtiAmb.tick(2.0, 3.0);

      } // 4.) - Repeat

      if ( myCountry )
      {
         // Perform last update - this is necessary to give the
         // Country instance the current granted time otherwise
         // the deleteObjectInstance call that happens in the
         // destructor will have an invalid time since it is in
         // the past. This is a problem with HelloWorld not RTI.
         myCountry->Update( grantTime );
         delete myCountry;
      }

    if( TimeManaged )
    {
      try{
	rtiAmb.disableTimeConstrained();
	TimeConstrained = RTI::RTI_FALSE;
      }
      catch(RTI::Exception& e)
      {
	  cerr << "FED_HW:ERR:" << e << endl;
      }

      try{
	rtiAmb.disableTimeRegulation();
	TimeRegulation = RTI::RTI_FALSE;
      }
      catch(RTI::Exception& e)
      {
	  cerr << "FED_HW: ERROR:" << e << endl;
      }
    }

      //------------------------------------------------------
      // Resign from the federation execution to remove this
      // federate from participation.  The flag provided
      // will instruct the RTI to call deleteObjectInstance
      // for all objects this federate has privilegeToDelete
      // for (which by default is all objects that this federate
      // registered) and to release ownership of any attributes
      // that this federate owns but does not own the
      // privilefeToDelete for.
      //------------------------------------------------------
      try
      {
         std::cout << "FED_HW: RESIGN FEDERATION EXECUTION CALLED" << std::endl;
         
         rtiAmb.resignFederationExecution(
                   RTI::DELETE_OBJECTS_AND_RELEASE_ATTRIBUTES ); 
         std::cout << "FED_HW: SUCCESSFUL RESIGN FEDERATION EXECUTION CALLED" << std::endl;
      }
      catch ( RTI::Exception& e )
      {
         cerr << "FED_HW: ERROR:" << e << endl;
         return -1;
      }

      //------------------------------------------------------
      // Destroy the federation execution in case we are the
      // last federate. This will not do anything bad if there
      // other federates joined.  The RTI will throw us an
      // exception telling us that other federates are joined
      // and we can just ignore that.
      //------------------------------------------------------
      try
      {
         std::cout << "FED_HW: DESTROY FEDERATION EXECUTION CALLED" << std::endl;
         rtiAmb.destroyFederationExecution( fedExecName ); 
         std::cout << "FED_HW: SUCCESSFUL DESTROY FEDERATION EXECUTION CALLED" << std::endl;
      }
      catch ( RTI::FederatesCurrentlyJoined& /* e */ )
      {
	cerr << "FED_HW: FederatesCurrentlyJoined" << endl;
	return 0;
      }
      catch ( RTI::FederationExecutionDoesNotExist& /* e */)
      {
	cerr << "FED_HW: FederationExecutionDoesNotExist" << endl;
	return 0;
      }
      catch ( RTI::Exception& e )
      {
         cerr << "FED_HW: ERROR:" << e << endl;
         return -1;
      }

   }
   catch (RTI::ConcurrentAccessAttempted& e)
   {
      cerr << "FED_HW: ERROR: Concurrent access to the RTI was attemted.\n"
           << "       Exception caught in main() - PROGRAM EXITING.\n"
           << "\n"
           << "Note:  Concurrent access will result from invoking\n"
           << "       RTIambassadorServices within the scope of\n"
           << "       federateAmbassadorService invocations.\n"
           << "\n"
           << "       e.g. RTI calls provideAttributeValueUpdate() and\n"
           << "       within that method you invoke updateAttributeValues\n"
           << endl;
      cerr << e << endl;
      return -1;
   }
   catch ( RTI::Exception& e )
   {
      cerr << "FED_HW: ERROR:" << e << endl;
      return -1;
   }

#if defined(WIN32)
   struct _timeb tb;
   _ftime(&tb);
   
   cout << argv[2] << " " << tb.time << " " << tb.millitm * 1000 << 
           " END" << endl;
#elif defined(VXWORKS)
   struct timespec tp;
   clock_gettime(CLOCK_REALTIME, &tp);
   
   cout << argv[2] << " " << tp.tv_sec << " " << tp.tv_nsec / 1000L 
	<< " START" << endl;
#else
   static struct timeval tp;
   gettimeofday(&tp, NULL);

   cout << argv[2] << " "
        << tp.tv_sec << " "
        << tp.tv_usec << " "
        << "END\n";
#endif

   cout << "FED_HW: Exiting " << exeName << "." << endl;

   return 0;
}


#if defined(VXWORKS)
extern "C" 
{
int
hwmain(char* arg1, char* arg2, char* arg3)
{
  ACE_MAIN_OBJECT_MANAGER;

  char* argv[] = { "hw_main", arg1, arg2, arg3 };
  int argc = 1;
  
  if ( argv[0] )
  {
    argc++;
    if ( argv[1] )
    {
      argc++;
      if ( argv[2] )
      {
	argc++;
      }
    }
  }

  return hw_main(argc, argv);
}
}
#else
int
main(int argc, char** argv)
{
  return hw_main(argc, argv);
}
#endif
