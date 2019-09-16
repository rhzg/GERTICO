GERTICO Version $Name:  $

===============================================================================
Installation (Windows)
===============================================================================

Extract the GERTICO installation file from the *.zip file

Execute the installation:

   for Release:
   
      Release\setup.exe
      
   for Debug:
   
      Debug\setup.exe
      
Follow the steps to install GERTICO until the choice of installation folder:

   default: [ProgramFilesFolder]\FHG\GERTICO\

Continue install until completion.

Set global variables:

   set GERTICO=[ProgramFilesFolder]\FHG\GERTICO
   set PATH=%PATH%;%GERTICO%\bin

===============================================================================
GERTICOconf.xml
===============================================================================

After Installation is complete, the GERTICOconf.xml file should be checked to
reflect the local requirements

1. Naming Service
-----------------

  1.1 endPoint
  ------------
  The name of the computer where NamingService runs is specified.

  Windows
  -------
    a) NamingService, GERTICO and Federates all on one computer
    
		  <endPoint>corbaloc:iiop:localhost:3000</endPoint>

    b) NamingService, GERTICO and Federates on several computers
    
		  <endPoint>corbaloc:iiop:myHost.de:3000</endPoint>

		  or

		  <endPoint>corbaloc:iiop:12.34.56.78:3000</endPoint>

  Linux
  -----

		  <endPoint>corbaloc:iiop:myHost.de:3000</endPoint>

		  or
		  
		  <endPoint>corbaloc:iiop:12.34.56.78:3000</endPoint>

  1.2 rootEntry
  -------------
  When several GERTICO Processes are started, different names
  have to be used for the Root Entry im NamingService.

		<rootEntry>GeRTI</rootEntry>
or
		<rootEntry>GeRTItwo</rootEntry>

2. Crash_ResignAction
---------------------
When a Federate crashes, the ResignAction which will be used in
ResignFederationExecution for this federate is specified here.

  Value                              HLA1.3 Semantic                       IEEE1516 Semantic
  ----                               ---------------                       -----------------
  unconditionallyDivestAttributes    RELEASE_ATTRIBUTES                    unconditionallyDivestAttributes
  deleteObjects                      DELETE_OBJECTS                        deleteObjects
  cancelPendingOwnershipAcquisitions NO_ACTION                             cancelPendingOwnershipAcquisitions
  deleteObjectsThenDivest            DELETE_OBJECTS_AND_RELEASE_ATTRIBUTES deleteObjectsThenDivest
  cancelThenDeleteThenDivest         DELETE_OBJECTS_AND_RELEASE_ATTRIBUTES cancelThenDeleteThenDivest
  noAction                           NO_ACTION                             noAction

3. DataLength
-------------
When a value of DataLength greater than  1  is given, the events (Update oder
SendInteraction) will be buffered in LRC until this length or the
TransmissionWait_ms is exceeded. Then the available events will be sent
in one bundle.

When a value of DataLength equal to  0  or  1  is given, each event will be
sent individually LRC to GERTICO.

4. DTDfile
----------
Not used.

5. LogicalTime1516 (ignored by 1.3)
-----------------------------------
Specifies the name of the logical time library.

  Windows
  -------
  The extension  .dll  will be added automatically

  Linux
  -----
  The prefix  lib  and the extension  .so  will be added automatically
  
6. ModelPath
------------
Search path for  FOM / SOM files. Several paths may be specified - the
firstpath with a valid file will be used. A macro in the form $(macro)
may be used.

7. SyncScope
------------
The CORBA QoS (Quality of Service) is specified here.

  Value                 CORBA QoS actually used
  ----                  -----------------------
  SYNC_NONE             SYNC_NONE
  SYNC_WITH_TRANSPORT   SYNC_WITH_TRANSPORT
  SYNC_WITH_SERVER      SYNC_WITH_SERVER
  SYNC_WITH_TARGET      SYNC_WITH_TARGET

The value SYNC_WITH_TRANSPORT has been found to provide the best results.

8. TransmissionWait_ms
----------------------
When DataLength greater than  1  is specified, a watchdog is started and
this will send, after this transmission wait time (in ms), all available
events to the GERTICO process.

===============================================================================
Starting the naming service (Windows)
===============================================================================

in %GERTICO%\scripts execute:

In general, on the host <host_name> (same as in GERTICOconf.xml) use the command: 

   startNS.bat <host_name>
   
to start the naming service

In particular, for naming service, GERTICO and all federates on one host use the
command:

   startNS.bat

===============================================================================
Overview of the GERTICO Module
===============================================================================

Build:            Project files GERTICO

EventMarket:      Implementation of the event channel

FedTime:          Implementation of a 1.3 time library

FedTime1516:      Implementation of a 1516 time library

FedTime1516PSISA: Implementation of a 1516 time library

Gal:              "GERTICO Application Logging" Logging module

GalRes:           Resource files for Gal

GeRti:		        GeRti Server

GeRtiTime:	      Time Management Module

LRC:		          Local RTI Component
		              Federate-side Module

LRC/HLASpec:	    LRC Mapping of the HLA 1.3 Interface Specification

LRC/HLA1516:	    LRC Mapping of the HLA IEEE1516 Interface Specification

OMT_XML:	        XML Parser Module (Version 2.0.0)

Util:             Utility functions.

bin:		          In the Binary Distribution, contains the necessary libraries and
                  utility programs.

doc:		          Documentation
		              (unfortunately not up-to-date in all parts)

idl:		          GERTICO internal CORBA interfaces

include:          Standard 1.3/1516 header files to be included

samples:	        Some sample applications

scripts:	        Useful shell scripts


===============================================================================
GERTICO compilation for Linux
===============================================================================

1. Setting the global variables
-------------------------------

The following global variables must be set:

	$GERTICO:	Must be the Top-Level GERTICO installation directory
	$ACE_ROOT:	Is defined as with the ACE Installation
	$TAO_ROOT:	Is defined as with the TAO Installation
	$XERCESCROOT:	Points to the Top-Level directory which contains 
			the lib and include directories
			The current versions are available from the following URL:
			http://xml.apache.org/dist/xerces-c/stable/

2. Compilation
--------------

On the top level, set off the make command:

	> cd $GERTICO
For 1.3
	> make install
For 1516
	> make -f Makefile1516 install


===============================================================================
GERTICO compilation for Windows (MS-Visual C++ VC8.0)
===============================================================================

Project files:

        %GERTICO%\Build\VC8\Build.sln

===============================================================================
IMPORTANT Notes
===============================================================================

1) If dynamic Netwerk Addressing is not used, then the address resolution files

        /etc/hosts (Linux)
   
   and
   
        %SystemRoot%\system32\drivers\etc\hosts (Windows)
   
   must be correct.

2) The %GERTICO%\GERTICOconf.xml must contain the Hostname of the computer
   where the CORBA Naming Service is running. (It is only possible under Windows
   where Naming Service, gerti and all Federates are running on the same
   computer that the "localhost" option can be used.)
   
3) Loading libraries:

   Linux: $GERTICO/lib must be contained in $LD_LIBRARY_PATH
   
   Windows: %GERTICO%\bin must be contained in %path%

===============================================================================
Starting the HelloWorld example (1.3 only)
===============================================================================


1. Starting Naming Service
-------------------------------

The Naming Service of the GERTICO distribution may be used. The TAO NamingService
must be started with a defined Port ID:

	> $GERTICO/bin/Naming_Service -ORBEndpoint iiop://localhost:3000 -d
(the -d option is optional to control whether NamingService displays logging messages)	

	> $GERTICO/bin/nslist -ORBInitRef NameService=corbaloc:iiop:localhost:3000/NameService

This ORBEndpoint must also be entered in the GERTICO configuration file GERTICOconf.xml.


2. Starting GeRti server
----------------------------

The GeRti server must be started in a directory, in which the XML Fed-files
and the HLA.dtd file are present. Note: the GERTICOconf.xml may be changed to allow
for a list of directories to be searched

Linux:

For 1.3
	$GERTICO/bin/gerti13
For 1516
	$GERTICO/bin/gerti1516

Windows:

For 1.3
  %GERTICO%\bin\GeRti13.exe
  
For 1516
  %GERTICO%\bin\GeRti1516.exe
  

3. Starting HelloWorld federates
-----------------------------------

The HelloWorld example is taken from the RTI 1.3NGv3 Distribution
and uses the following parameters:

	helloWorld <Country Name> <Initial Population> [<Number of Ticks>]

where 

	Country Name: an arbitrary country name,
	Initial Population: an arbitrary positive number and 
	Number of Ticks: optional - the number of cycles to run 

Thus the following commands (example) are required per federate:

	> cd $GERTICO/LRC/HLASpec/App/helloWorld
	> helloWorld fedA 100 1000


===============================================================================
Installation of ACE/TAO
===============================================================================

GERTICO uses a standard installation von ACE/TAO for its internal communication.
The complete installation instructions are found in $ACE_ROOT/Install.html
In particular, the following steps are required (Linux):

1. Set global variable $ACE_ROOT
2. Create Link: ace/config.h -> config-linux.h
3. Create Link: include/makeinclude/platform_macros.GNU -> platform_linux.GNU
4. Set LD_LIBRARY_PATH to $ACE_ROOT/ace
5. Do make in $ACE_ROOT
6. Set global variable $TAO_ROOT
7. Do make in $TAO_ROOT


===============================================================================
Installation of XERCES
===============================================================================

GERTICO uses a standard XERCES distribution without any changes.
The Source-Code Distribution was used, and the build instructions
in the XERCES Documentation were followed.


