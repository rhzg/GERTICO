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
					ut->resignFederationExecution(910,RTI::CANCEL_THEN_DELETE_THEN_DIVEST);
				}
				catch(RTI::FederateNotExecutionMember)
				{
			  }

			ut->setAmb('3');
				try
				{
					ut->resignFederationExecution(911,RTI::CANCEL_THEN_DELETE_THEN_DIVEST);
				}
				catch(RTI::FederateNotExecutionMember)
				{
			  }

			ut->setAmb('4');
				try
				{
					ut->resignFederationExecution(912,RTI::CANCEL_THEN_DELETE_THEN_DIVEST);
				}
				catch(RTI::FederateNotExecutionMember)
				{
			  }

			ut->setAmb('5');
				try
				{
					ut->resignFederationExecution(913,RTI::CANCEL_THEN_DELETE_THEN_DIVEST);
				}
				catch(RTI::FederateNotExecutionMember)
				{
			  }

			ut->setAmb('0');
				try
				{
					ut->resignFederationExecution(914,RTI::CANCEL_THEN_DELETE_THEN_DIVEST);
				}
				catch(RTI::FederateNotExecutionMember)
				{
			  }
				try
				{
					ut->destroyFederationExecution(915,L"Verification"); 
				}
				catch(RTI::FederationExecutionDoesNotExist)
				{
			  }
