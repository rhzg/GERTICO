DEST=gertico_0_56_20

mkdir $DEST
cp $GERTICO/GERTICOconf.xml $DEST
cp $GERTICO/Readme.txt $DEST
cp $GERTICO/gertico_manual.txt $DEST
cp $GERTICO/config.incl $DEST

mkdir $DEST/Gal
cp $GERTICO/Gal/StdAfx.h $DEST/Gal
cp $GERTICO/Gal/adm.h $DEST/Gal
cp $GERTICO/Gal/appender.h $DEST/Gal
cp $GERTICO/Gal/event.h $DEST/Gal
cp $GERTICO/Gal/format.h $DEST/Gal
cp $GERTICO/Gal/global.h $DEST/Gal
cp $GERTICO/Gal/in.h $DEST/Gal
cp $GERTICO/Gal/layout.h $DEST/Gal
cp $GERTICO/Gal/logger.h $DEST/Gal
cp $GERTICO/Gal/lst.h $DEST/Gal
cp $GERTICO/Gal/out.h $DEST/Gal
cp $GERTICO/Gal/param.h $DEST/Gal
cp $GERTICO/Gal/repository.h $DEST/Gal
cp $GERTICO/Gal/repository_l.h $DEST/Gal

cp -r $GERTICO/GalRes $DEST

mkdir $DEST/bin
cp -r $GERTICO/OMT_XML/Samples $DEST/bin
cp -r $GERTICO/bin/Naming_Service $DEST/bin
cp -r $GERTICO/bin/gerti13 $DEST/bin
cp -r $GERTICO/bin/gerti1516 $DEST/bin
cp -r $GERTICO/bin/tao_nslist $DEST/bin

cp $GERTICO/OMT_XML/Samples/HelloWorld.fed $DEST/bin
cp $GERTICO/OMT_XML/Samples/Schwarm.fed $DEST/bin
cp $GERTICO/OMT_XML/Samples/HLA.dtd $DEST/bin

mkdir $DEST/doc
cp -r $GERTICO/doc/GERTICO.doc $DEST/doc
cp -r $GERTICO/doc/MessageService.doc $DEST/doc
cp -r $GERTICO/doc/NameService.doc $DEST/doc
cp -r $GERTICO/doc/OMT_XML.doc $DEST/doc
cp -r $GERTICO/doc/WebPortal.doc $DEST/doc

cp -r $GERTICO/include $DEST

cp -r $GERTICO/lib $DEST

mkdir $DEST/scripts 
cp -r $GERTICO/scripts/gerti.sh $DEST/scripts
cp -r $GERTICO/scripts/l1a.sh $DEST/scripts
cp -r $GERTICO/scripts/l1b.sh $DEST/scripts
cp -r $GERTICO/scripts/l1r.sh $DEST/scripts
cp -r $GERTICO/scripts/ns.sh $DEST/scripts
cp -r $GERTICO/scripts/nslist.sh $DEST/scripts


mkdir $DEST/samples
cp $GERTICO/samples/Makefile $DEST/samples

mkdir $DEST/samples/BossFish
cp $GERTICO/samples/BossFish/BossFish.cpp $DEST/samples/BossFish
cp $GERTICO/samples/BossFish/SchwarmAmbassador.cpp $DEST/samples/BossFish
cp $GERTICO/samples/BossFish/SchwarmAmbassador.h $DEST/samples/BossFish
cp $GERTICO/samples/BossFish/Makefile $DEST/samples/BossFish

mkdir $DEST/samples/Common
cp $GERTICO/samples/Common/Federate.cpp $DEST/samples/Common
cp $GERTICO/samples/Common/Federate.h $DEST/samples/Common
cp $GERTICO/samples/Common/Fish.cpp $DEST/samples/Common
cp $GERTICO/samples/Common/Fish.h $DEST/samples/Common
cp $GERTICO/samples/Common/Makefile $DEST/samples/Common

mkdir $DEST/samples/SchwarmMonitorConsole
cp $GERTICO/samples/SchwarmMonitorConsole/Makefile $DEST/samples/SchwarmMonitorConsole
cp $GERTICO/samples/SchwarmMonitorConsole/SchwarmAmbassador.cpp $DEST/samples/SchwarmMonitorConsole
cp $GERTICO/samples/SchwarmMonitorConsole/SchwarmAmbassador.h $DEST/samples/SchwarmMonitorConsole
cp $GERTICO/samples/SchwarmMonitorConsole/SchwarmMonitor.cpp $DEST/samples/SchwarmMonitorConsole

mkdir $DEST/samples/SchwarmRandom
cp $GERTICO/samples/SchwarmRandom/Makefile $DEST/samples/SchwarmRandom
cp $GERTICO/samples/SchwarmRandom/Schwarm.cpp $DEST/samples/SchwarmRandom
cp $GERTICO/samples/SchwarmRandom/SchwarmAmbassador.cpp $DEST/samples/SchwarmRandom
cp $GERTICO/samples/SchwarmRandom/SchwarmAmbassador.h $DEST/samples/SchwarmRandom

mkdir $DEST/samples/helloWorld
cp $GERTICO/samples/helloWorld/Country.cpp $DEST/samples/helloWorld
cp $GERTICO/samples/helloWorld/Country.hh $DEST/samples/helloWorld
cp $GERTICO/samples/helloWorld/HelloWorld.cpp $DEST/samples/helloWorld
cp $GERTICO/samples/helloWorld/HwFederateAmbassador.cpp $DEST/samples/helloWorld
cp $GERTICO/samples/helloWorld/HwFederateAmbassador.hh $DEST/samples/helloWorld
cp $GERTICO/samples/helloWorld/Makefile $DEST/samples/helloWorld

