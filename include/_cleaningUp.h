			ut->mySleepCycles(L2WAIT_CYCLES/50);

			ut->setAmb('0');
				(*fedAmb)->cbTestAllFlags(); 

			ut->setAmb('2');
				(*fedAmb)->cbTestAllFlags(); 

			ut->setAmb('3');
				(*fedAmb)->cbTestAllFlags();
				
			ut->setAmb('4');
				(*fedAmb)->cbTestAllFlags(); 

			ut->setAmb('5');
				(*fedAmb)->cbTestAllFlags(); 
				
			ut->setAmb('0');
				(*fedAmb)->cbResetAllFlags(false); 

			ut->setAmb('2');
				(*fedAmb)->cbResetAllFlags(false); 

			ut->setAmb('3');
				(*fedAmb)->cbResetAllFlags(false);
				
			ut->setAmb('4');
				(*fedAmb)->cbResetAllFlags(false); 

			ut->setAmb('5');
				(*fedAmb)->cbResetAllFlags(false); 

		ut->comment(cleaningUp);

			ut->setAmb('2');
				try
				{
					ut->resignFederationExecution(900,RTI_V1_3::DELETE_OBJECTS_AND_RELEASE_ATTRIBUTES);
				}
				catch(RTI_V1_3::FederateNotExecutionMember)
				{
			  }

			ut->setAmb('3');
				try
				{
					ut->resignFederationExecution(901,RTI_V1_3::DELETE_OBJECTS_AND_RELEASE_ATTRIBUTES);
				}
				catch(RTI_V1_3::FederateNotExecutionMember)
				{
			  }

			ut->setAmb('4');
				try
				{
					ut->resignFederationExecution(902,RTI_V1_3::DELETE_OBJECTS_AND_RELEASE_ATTRIBUTES);
				}
				catch(RTI_V1_3::FederateNotExecutionMember)
				{
			  }

			ut->setAmb('5');
				try
				{
					ut->resignFederationExecution(903,RTI_V1_3::DELETE_OBJECTS_AND_RELEASE_ATTRIBUTES);
				}
				catch(RTI_V1_3::FederateNotExecutionMember)
				{
			  }

			ut->setAmb('0');
				try
				{
					ut->resignFederationExecution(904,RTI_V1_3::DELETE_OBJECTS_AND_RELEASE_ATTRIBUTES);
				}
				catch(RTI_V1_3::FederateNotExecutionMember)
				{
			  }
				try
				{
					ut->destroyFederationExecution(905,"Verification"); 
				}
				catch(RTI_V1_3::FederationExecutionDoesNotExist)
				{
			  }
