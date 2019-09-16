			err=0;
		  break;
    }
    catch(RTI_V1_3::ConcurrentAccessAttempted)
    {
#ifdef _UT_DEBUG
    	commentW_CAA(id,"");
#endif
		}
	}
	if(err)
   	commentE_CAA(id,"");
