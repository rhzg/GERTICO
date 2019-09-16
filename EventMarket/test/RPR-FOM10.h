    ClassDescr *newClassDescr1;
    ClassDescr *newClassDescr2;
    ClassDescr *newClassDescr3;
    ClassDescr *newClassDescr4;

//    (class0 ObjectRoot 
//       (attribute privilegeToDelete  reliable timestamp)
/*
 *  DELETED ONLY TO LET APPLICATION RUN AT ALL.
 *            pObjectRoot->addItem ("privilegeToDelete");
 *
 */

//       (class1 RTIprivate)
            s = "RTIprivate";
            newClassDescr1 = new ClassDescr (s, pObjectRoot, &threadData);
            add_objectClass (newClassDescr1);

//       (class1 BaseEntity
//         (attribute AccelerationVector reliable receive)
//         (attribute AngularVelocityVector reliable receive)
//         (attribute DeadReckoningAlgorithm reliable receive)
//         (attribute EntityType reliable receive)
//         (attribute EntityIdentifier reliable receive)
//         (attribute IsFrozen reliable receive)
//         (attribute Orientation reliable receive)
//         (attribute WorldLocation reliable receive)
//         (attribute VelocityVector reliable receive)
            s = "BaseEntity";
            newClassDescr1 = new ClassDescr (s, pObjectRoot, &threadData);
            newClassDescr1->addItem ("AccelerationVector");
            newClassDescr1->addItem ("AngularVelocityVector");
            newClassDescr1->addItem ("DeadReckoningAlgorithm");
            newClassDescr1->addItem ("EntityType");
            newClassDescr1->addItem ("EntityIdentifier");
            newClassDescr1->addItem ("IsFrozen");
            newClassDescr1->addItem ("Orientation");
            newClassDescr1->addItem ("WorldLocation");
            newClassDescr1->addItem ("VelocityVector");
            add_objectClass (newClassDescr1);

//         (class2 EnvironmentalEntity
//           (attribute OpacityCode reliable receive)
//         )
              s = "EnvironmentalEntity";
              newClassDescr2 = new ClassDescr (s, newClassDescr1, &threadData);
              newClassDescr2->addItem ("OpacityCode");
              add_objectClass (newClassDescr2);

//         (class2 PhysicalEntity
//           (attribute AlternateEntityType reliable receive)
//           (attribute ArticulatedParametersArray reliable receive)
//           (attribute CamouflageType reliable receive)
//           (attribute DamageState reliable receive)
//           (attribute EngineSmokeOn reliable receive)
//           (attribute FirePowerDisabled reliable receive)
//           (attribute FlamesPresent reliable receive)
//           (attribute ForceIdentifier reliable receive)
//           (attribute HasAmmunitionSupplyCap reliable receive)
//           (attribute HasFuelSupplyCap reliable receive)
//           (attribute HasRecoveryCap reliable receive)
//           (attribute HasRepairCap reliable receive)
//           (attribute Immobilized reliable receive)
//           (attribute IsConcealed reliable receive)
//           (attribute Marking reliable receive)
//           (attribute PowerPlantOn reliable receive)
//           (attribute SmokePlumePresent reliable receive)
//           (attribute TentDeployed reliable receive)
//           (attribute TrailingEffectsCode reliable receive)
              s = "PhysicalEntity";
              newClassDescr2 = new ClassDescr (s, newClassDescr1, &threadData);
              newClassDescr2->addItem ("AlternateEntityType");
              newClassDescr2->addItem ("ArticulatedParametersArray");
              newClassDescr2->addItem ("CamouflageType");
              newClassDescr2->addItem ("DamageState");
              newClassDescr2->addItem ("EngineSmokeOn");
              newClassDescr2->addItem ("FirePowerDisabled");
              newClassDescr2->addItem ("FlamesPresent");
              newClassDescr2->addItem ("ForceIdentifier");
              newClassDescr2->addItem ("HasAmmunitionSupplyCap");
              newClassDescr2->addItem ("HasFuelSupplyCap");
              newClassDescr2->addItem ("HasRecoveryCap");
              newClassDescr2->addItem ("HasRepairCap");
              newClassDescr2->addItem ("Immobilized");
              newClassDescr2->addItem ("IsConcealed");
              newClassDescr2->addItem ("Marking");
              newClassDescr2->addItem ("PowerPlantOn");
              newClassDescr2->addItem ("SmokePlumePresent");
              newClassDescr2->addItem ("TentDeployed");
              newClassDescr2->addItem ("TrailingEffectsCode");
              add_objectClass (newClassDescr2);

//           (class3 Platform
//             (attribute AfterburnerOn reliable receive)
//             (attribute AntiCollisionLightsOn reliable receive)
//             (attribute BlackOutBrakeLightsOn reliable receive)
//             (attribute BlackOutLightsOn reliable receive)
//             (attribute BrakeLightsOn reliable receive)
//             (attribute FormationLightsOn reliable receive)
//             (attribute HatchState reliable receive)
//             (attribute HeadLightsOn reliable receive)
//             (attribute InteriorLightsOn reliable receive)
//             (attribute LandingLightsOn reliable receive)
//             (attribute LauncherRaised reliable receive)
//             (attribute NavigationLightsOn reliable receive)
//             (attribute RampDeployed reliable receive)
//             (attribute RunningLightsOn reliable receive)
//             (attribute SpotLightsOn reliable receive)
//             (attribute TailLightsOn reliable receive)
                s = "Platform";
                newClassDescr3 = new ClassDescr (s, newClassDescr2, &threadData);
                newClassDescr3->addItem ("AfterburnerOn");
                newClassDescr3->addItem ("AntiCollisionLightsOn");
                newClassDescr3->addItem ("BlackOutBrakeLightsOn");
                newClassDescr3->addItem ("BlackOutLightsOn");
                newClassDescr3->addItem ("BrakeLightsOn");
                newClassDescr3->addItem ("FormationLightsOn");
                newClassDescr3->addItem ("HatchState");
                newClassDescr3->addItem ("HeadLightsOn");
                newClassDescr3->addItem ("InteriorLightsOn");
                newClassDescr3->addItem ("LandingLightsOn");
                newClassDescr3->addItem ("LauncherRaised");
                newClassDescr3->addItem ("NavigationLightsOn");
                newClassDescr3->addItem ("RampDeployed");
                newClassDescr3->addItem ("RunningLightsOn");
                newClassDescr3->addItem ("SpotLightsOn");
                newClassDescr3->addItem ("TailLightsOn");
                add_objectClass (newClassDescr3);

//             (class4 Aircraft
//             )
                  s = "Aircraft";
                  newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                  add_objectClass (newClassDescr4);

//             (class4 AmphibiousVehicle
//             )
                  s = "AmphibiousVehicle";
                  newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                  add_objectClass (newClassDescr4);

//             (class4 GroundVehicle
//             )
                  s = "GroundVehicle";
                  newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                  add_objectClass (newClassDescr4);

//             (class4 MultiDomainPlatform
//             )
                  s = "MultiDomainPlatform";
                  newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                  add_objectClass (newClassDescr4);

//             (class4 Spacecraft
//             )
                  s = "Spacecraft";
                  newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                  add_objectClass (newClassDescr4);

//             (class4 SubmersibleVessel
//             )
                  s = "SubmersibleVessel";
                  newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                  add_objectClass (newClassDescr4);

//             (class4 SurfaceVessel
//             )
                  s = "SurfaceVessel";
                  newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                  add_objectClass (newClassDescr4);

//           )
//           (class3 Lifeform
//             (attribute FlashLightsOn reliable receive)
//             (attribute StanceCode reliable receive)
//             (attribute PrimaryWeaponState reliable receive)
//             (attribute SecondaryWeaponState reliable receive)
                s = "Lifeform";
                newClassDescr3 = new ClassDescr (s, newClassDescr2, &threadData);
                newClassDescr3->addItem ("FlashLightsOn");
                newClassDescr3->addItem ("StanceCode");
                newClassDescr3->addItem ("PrimaryWeaponState");
                newClassDescr3->addItem ("SecondaryWeaponState");
                add_objectClass (newClassDescr3);

//             (class4 Human
//             )
                  s = "Human";
                  newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                  add_objectClass (newClassDescr4);

//             (class4 NonHuman
//             )
                  s = "NonHuman";
                  newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                  add_objectClass (newClassDescr4);

//           )
//           (class3 CulturalFeature
//             (attribute ExternalLightsOn reliable receive)
//             (attribute InternalHeatSourceOn reliable receive)
//             (attribute InternalLightsOn reliable receive)
//           )
                s = "CulturalFeature";
                newClassDescr3 = new ClassDescr (s, newClassDescr2, &threadData);
                newClassDescr3->addItem ("ExternalLightsOn");
                newClassDescr3->addItem ("InternalHeatSourceOn");
                newClassDescr3->addItem ("InternalLightsOn");
                add_objectClass (newClassDescr3);

//           (class3 Expendables
//           )
                s = "Expendables";
                newClassDescr3 = new ClassDescr (s, newClassDescr2, &threadData);
                add_objectClass (newClassDescr3);

//           (class3 Munition
//             (attribute LauncherFlashPresent reliable receive)
//           )
                s = "Munition";
                newClassDescr3 = new ClassDescr (s, newClassDescr2, &threadData);
                newClassDescr3->addItem ("LauncherFlashPresent");
                add_objectClass (newClassDescr3);

//           (class3 Radio
//           )
                s = "Radio";
                newClassDescr3 = new ClassDescr (s, newClassDescr2, &threadData);
                add_objectClass (newClassDescr3);

//           (class3 Sensor
//             (attribute AntennaRaised reliable receive)
//             (attribute BlackoutLightsOn reliable receive)
//             (attribute LightsOn reliable receive)
//             (attribute InteriorLightsOn reliable receive)
//             (attribute MissionKill reliable receive)
//           )
                s = "Sensor";
                newClassDescr3 = new ClassDescr (s, newClassDescr2, &threadData);
                newClassDescr3->addItem ("AntennaRaised");
                newClassDescr3->addItem ("BlackoutLightsOn");
                newClassDescr3->addItem ("LightsOn");
                newClassDescr3->addItem ("InteriorLightsOn");
                newClassDescr3->addItem ("MissionKill");
                add_objectClass (newClassDescr3);

//           (class3 Supplies
//           )
                s = "Supplies";
                newClassDescr3 = new ClassDescr (s, newClassDescr2, &threadData);
                add_objectClass (newClassDescr3);

//        )
//      )
//      (class1 EmbeddedSystem
//        (attribute EntityIdentifier reliable receive)
//        (attribute HostObjectIdentifier reliable receive)
//        (attribute RelativePosition reliable receive)
            s = "EmbeddedSystem";
            newClassDescr1 = new ClassDescr (s, pObjectRoot, &threadData);
            newClassDescr1->addItem ("EntityIdentifier");
            newClassDescr1->addItem ("HostObjectIdentifier");
            newClassDescr1->addItem ("RelativePosition");
            add_objectClass (newClassDescr1);

//        (class2 Designator
//          (attribute CodeName reliable receive)
//          (attribute DesignatedObjectIdentifier reliable receive)
//          (attribute DesignatorCode reliable receive)
//          (attribute DesignatorEmissionWavelength reliable receive)
//          (attribute DesignatorOutputPower reliable receive)
//          (attribute DesignatorSpotLocation reliable receive)
//          (attribute DeadReckoningAlgorithm reliable receive)
//          (attribute RelativeSpotLocation reliable receive)
//          (attribute SpotLinearAccelerationVector reliable receive)
//        )
              s = "Designator";
              newClassDescr2 = new ClassDescr (s, newClassDescr1, &threadData);
              newClassDescr2->addItem ("CodeName");
              newClassDescr2->addItem ("DesignatedObjectIdentifier");
              newClassDescr2->addItem ("DesignatorCode");
              newClassDescr2->addItem ("DesignatorEmissionWavelength");
              newClassDescr2->addItem ("DesignatorOutputPower");
              newClassDescr2->addItem ("DesignatorSpotLocation");
              newClassDescr2->addItem ("DeadReckoningAlgorithm");
              newClassDescr2->addItem ("RelativeSpotLocation");
              newClassDescr2->addItem ("SpotLinearAccelerationVector");
              add_objectClass (newClassDescr2);

//        (class2 EmitterSystem
//          (attribute EmitterFunctionCode reliable receive)
//          (attribute EmitterType reliable receive)
//          (attribute EmitterIndex reliable receive)
//          (attribute EventIdentifier reliable receive)
//        )
              s = "EmitterSystem";
              newClassDescr2 = new ClassDescr (s, newClassDescr1, &threadData);
              newClassDescr2->addItem ("EmitterFunctionCode");
              newClassDescr2->addItem ("EmitterType");
              newClassDescr2->addItem ("EmitterIndex");
              newClassDescr2->addItem ("EventIdentifier");
              add_objectClass (newClassDescr2);

//        (class2 RadioReceiver
//          (attribute RadioIndex reliable receive)
//          (attribute ReceivedPower reliable receive)
//          (attribute ReceivedTransmitterIdentifier reliable receive)
//          (attribute ReceiverOperationalStatus reliable receive)
//        )
              s = "RadioReceiver";
              newClassDescr2 = new ClassDescr (s, newClassDescr1, &threadData);
              newClassDescr2->addItem ("RadioIndex");
              newClassDescr2->addItem ("ReceivedPower");
              newClassDescr2->addItem ("ReceivedTransmitterIdentifier");
              newClassDescr2->addItem ("ReceiverOperationalStatus");
              add_objectClass (newClassDescr2);

//        (class2 RadioTransmitter
//          (attribute AntennaPatternData reliable receive)
//          (attribute CryptographicMode reliable receive)
//          (attribute CryptoSystem reliable receive)
//          (attribute EncryptionKeyIdentifier reliable receive)
//          (attribute Frequency reliable receive)
//          (attribute FrequencyBandwidth reliable receive)
//          (attribute FrequencyHopInUse reliable receive)
//          (attribute ModulationParameters reliable receive)
//          (attribute PsuedoNoiseSpectrumInUse reliable receive)
//          (attribute RadioIndex reliable receive)
//          (attribute RadioInputSource reliable receive)
//          (attribute RadioSystemType reliable receive)
//          (attribute RFModulationSystemType reliable receive)
//          (attribute RFModulationType reliable receive)
//          (attribute TimeHopInUse reliable receive)
//          (attribute TransmittedPower reliable receive)
//          (attribute TransmitterOperationalStatus reliable receive)
//          (attribute WorldLocation reliable receive)
//        )
              s = "RadioTransmitter";
              newClassDescr2 = new ClassDescr (s, newClassDescr1, &threadData);
              newClassDescr2->addItem ("AntennaPatternData");
              newClassDescr2->addItem ("CryptographicMode");
              newClassDescr2->addItem ("CryptoSystem");
              newClassDescr2->addItem ("EncryptionKeyIdentifier");
              newClassDescr2->addItem ("Frequency");
              newClassDescr2->addItem ("FrequencyBandwidth");
              newClassDescr2->addItem ("FrequencyHopInUse");
              newClassDescr2->addItem ("ModulationParameters");
              newClassDescr2->addItem ("PsuedoNoiseSpectrumInUse");
              newClassDescr2->addItem ("RadioIndex");
              newClassDescr2->addItem ("RadioInputSource");
              newClassDescr2->addItem ("RadioSystemType");
              newClassDescr2->addItem ("RFModulationSystemType");
              newClassDescr2->addItem ("RFModulationType");
              newClassDescr2->addItem ("TimeHopInUse");
              newClassDescr2->addItem ("TransmittedPower");
              newClassDescr2->addItem ("TransmitterOperationalStatus");
              newClassDescr2->addItem ("WorldLocation");
              add_objectClass (newClassDescr2);

//      )
//      (class1 EmitterBeam
//        (attribute BeamAzimuthCenter reliable receive)
//        (attribute BeamAzimuthSweep reliable receive)
//        (attribute BeamElevationCenter reliable receive)
//        (attribute BeamElevationSweep reliable receive)
//        (attribute BeamFunctionCode reliable receive)
//        (attribute BeamIdentifier reliable receive)
//        (attribute BeamParameterIndex reliable receive)
//        (attribute EffectiveRadiatedPower reliable receive)
//        (attribute EmissionFrequency reliable receive)
//        (attribute EmitterSystemIdentifier reliable receive)
//        (attribute EventIdentifier reliable receive)
//        (attribute FrequencyRange reliable receive)
//        (attribute PulseRepetitionFrequency reliable receive)
//        (attribute PulseWidth reliable receive)
//        (attribute SweepSynch reliable receive)
            s = "EmitterBeam";
            newClassDescr1 = new ClassDescr (s, pObjectRoot, &threadData);
            newClassDescr1->addItem ("BeamAzimuthCenter");
            newClassDescr1->addItem ("BeamAzimuthSweep");
            newClassDescr1->addItem ("BeamElevationCenter");
            newClassDescr1->addItem ("BeamElevationSweep");
            newClassDescr1->addItem ("BeamFunctionCode");
            newClassDescr1->addItem ("BeamIdentifier");
            newClassDescr1->addItem ("BeamParameterIndex");
            newClassDescr1->addItem ("EffectiveRadiatedPower");
            newClassDescr1->addItem ("EmissionFrequency");
            newClassDescr1->addItem ("EmitterSystemIdentifier");
            newClassDescr1->addItem ("EventIdentifier");
            newClassDescr1->addItem ("FrequencyRange");
            newClassDescr1->addItem ("PulseRepetitionFrequency");
            newClassDescr1->addItem ("PulseWidth");
            newClassDescr1->addItem ("SweepSynch");
            add_objectClass (newClassDescr1);

//        (class2 RadarBeam
//          (attribute HighDensityTrack reliable receive)
//          (attribute TrackObjectIdentifiers reliable receive)
//        )
              s = "RadarBeam";
              newClassDescr2 = new ClassDescr (s, newClassDescr1, &threadData);
              newClassDescr2->addItem ("HighDensityTrack");
              newClassDescr2->addItem ("TrackObjectIdentifiers");
              add_objectClass (newClassDescr2);

//        (class2 JammerBeam
//          (attribute JammingModeSequence reliable receive)
//          (attribute JammedObjectIdentifiers reliable receive)
//          (attribute HighDensityJam reliable receive)
//        )
              s = "JammerBeam";
              newClassDescr2 = new ClassDescr (s, newClassDescr1, &threadData);
              newClassDescr2->addItem ("JammingModeSequence");
              newClassDescr2->addItem ("JammedObjectIdentifiers");
              newClassDescr2->addItem ("HighDensityJam");
              add_objectClass (newClassDescr2);

//      )
//      (class1 Manager
            s = "Manager";
            newClassDescr1 = new ClassDescr (s, pObjectRoot, &threadData);
            add_objectClass (newClassDescr1);

//        (class2 Federation
//          (attribute FederationName reliable receive)
//          (attribute FederatesInFederation reliable receive)
//          (attribute RTIversion reliable receive)
//          (attribute FEDid reliable receive)
//          (attribute LastSaveName reliable receive)
//          (attribute LastSaveTime reliable receive)
//          (attribute NextSaveName reliable receive)
//          (attribute NextSaveTime reliable receive)
//        )
              s = "Federation";
              newClassDescr2 = new ClassDescr (s, newClassDescr1, &threadData);
              newClassDescr2->addItem ("FederationName");
              newClassDescr2->addItem ("FederatesInFederation");
              newClassDescr2->addItem ("RTIversion");
              newClassDescr2->addItem ("FEDid");
              newClassDescr2->addItem ("LastSaveName");
              newClassDescr2->addItem ("LastSaveTime");
              newClassDescr2->addItem ("NextSaveName");
              newClassDescr2->addItem ("NextSaveTime");
              add_objectClass (newClassDescr2);

//        (class2 Federate
//          (attribute FederateHandle reliable receive)
//          (attribute FederateType reliable receive)
//          (attribute FederateHost reliable receive)
//          (attribute RTIversion reliable receive)
//          (attribute FEDid reliable receive)
//          (attribute TimeConstrained reliable receive)
//          (attribute TimeRegulating reliable receive)
//          (attribute AsynchronousDelivery reliable receive)
//          (attribute FederateState reliable receive)
//          (attribute TimeManagerState reliable receive)
//          (attribute FederateTime reliable receive)
//          (attribute Lookahead reliable receive)
//          (attribute LBTS reliable receive)
//          (attribute MinNextEventTime reliable receive)
//          (attribute ROlength reliable receive)
//          (attribute TSOlength reliable receive)
//          (attribute ReflectionsReceived reliable receive)
//          (attribute UpdatesSent reliable receive)
//          (attribute InteractionsReceived reliable receive)
//          (attribute InteractionsSent reliable receive)
//          (attribute ObjectsOwned reliable receive)
//          (attribute ObjectsUpdated reliable receive)
//          (attribute ObjectsReflected reliable receive)
//        )
              s = "Federate";
              newClassDescr2 = new ClassDescr (s, newClassDescr1, &threadData);
              newClassDescr2->addItem ("FederateHandle");
              newClassDescr2->addItem ("FederateType");
              newClassDescr2->addItem ("FederateHost");
              newClassDescr2->addItem ("RTIversion");
              newClassDescr2->addItem ("FEDid");
              newClassDescr2->addItem ("TimeConstrained");
              newClassDescr2->addItem ("TimeRegulating");
              newClassDescr2->addItem ("AsynchronousDelivery");
              newClassDescr2->addItem ("FederateState");
              newClassDescr2->addItem ("TimeManagerState");
              newClassDescr2->addItem ("FederateTime");
              newClassDescr2->addItem ("Lookahead");
              newClassDescr2->addItem ("LBTS");
              newClassDescr2->addItem ("MinNextEventTime");
              newClassDescr2->addItem ("ROlength");
              newClassDescr2->addItem ("TSOlength");
              newClassDescr2->addItem ("ReflectionsReceived");
              newClassDescr2->addItem ("UpdatesSent");
              newClassDescr2->addItem ("InteractionsReceived");
              newClassDescr2->addItem ("InteractionsSent");
              newClassDescr2->addItem ("ObjectsOwned");
              newClassDescr2->addItem ("ObjectsUpdated");
              newClassDescr2->addItem ("ObjectsReflected");
              add_objectClass (newClassDescr2);

//      )
//    )



//  (interactions
//    (class0 InteractionRoot  reliable timestamp

//      (class1 RTIprivate  reliable timestamp)
           s = "RTIprivate";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);

//      (class1 Acknowledge reliable receive
//        (parameter OriginatingEntity)
//        (parameter ReceivingEntity)
//        (parameter RequestIdentifier)
//        (parameter AcknowledgeFlag)
//        (parameter ResponseFlag)
//      )
           s = "Acknowledge";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("OriginatingEntity");
           newClassDescr1->addItem ("ReceivingEntity");
           newClassDescr1->addItem ("RequestIdentifier");
           newClassDescr1->addItem ("AcknowledgeFlag");
           newClassDescr1->addItem ("ResponseFlag");

//      (class1 ActionRequest reliable receive
//        (parameter OriginatingEntity)
//        (parameter ReceivingEntity)
//        (parameter RequestIdentifier)
//        (parameter ActionRequestCode)
//        (parameter FixedDatums)
//        (parameter VariableDatumSet)
//      )
           s = "ActionRequest";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("OriginatingEntity");
           newClassDescr1->addItem ("ReceivingEntity");
           newClassDescr1->addItem ("RequestIdentifier");
           newClassDescr1->addItem ("ActionRequestCode");
           newClassDescr1->addItem ("FixedDatums");
           newClassDescr1->addItem ("VariableDatumSet");


//      (class1 ActionResponse reliable receive
//        (parameter OriginatingEntity)
//        (parameter ReceivingEntity)
//        (parameter RequestIdentifier)
//        (parameter RequestStatus)
//        (parameter FixedDatums)
//        (parameter VariableDatumSet)
//      )
           s = "ActionResponse";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("OriginatingEntity");
           newClassDescr1->addItem ("ReceivingEntity");
           newClassDescr1->addItem ("RequestIdentifier");
           newClassDescr1->addItem ("RequestStatus");
           newClassDescr1->addItem ("FixedDatums");
           newClassDescr1->addItem ("VariableDatumSet");


//      (class1 ActionRequestToObject reliable receive
//        (parameter ObjectIdentifiers)
//        (parameter ActionRequestCode)
//      )
           s = "ActionRequestToObject";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("ObjectIdentifiers");
           newClassDescr1->addItem ("ActionRequestCode");


//      (class1 ActionResponseFromObject reliable receive
//        (parameter ActionResult)
//      )
           s = "ActionResponseFromObject";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("ActionResult");


//      (class1 AttributeChangeRequest reliable receive
//        (parameter ObjectIdentifiers)
//        (parameter AttributeValueSet)
//      )
           s = "AttributeChangeRequest";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("ObjectIdentifiers");
           newClassDescr1->addItem ("AttributeValueSet");


//      (class1 AttributeChangeResult reliable receive
//        (parameter ObjectIdentifier)
//        (parameter AttributeChangeResult)
//        (parameter AttributeValueSet)
//      )
           s = "AttributeChangeResult";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("ObjectIdentifier");
           newClassDescr1->addItem ("AttributeChangeResult");
           newClassDescr1->addItem ("AttributeValueSet");


//      (class1 Collision reliable receive
//        (parameter CollidingObjectIdentifier)
//        (parameter IssuingObjectMass)
//        (parameter IssuingObjectVelocityVector)
//        (parameter CollisionType)
//        (parameter CollisionLocation)
//        (parameter EventIdentifier)
//        (parameter IssuingObjectIdentifier)
//      )
           s = "Collision";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("CollidingObjectIdentifier");
           newClassDescr1->addItem ("IssuingObjectMass");
           newClassDescr1->addItem ("IssuingObjectVelocityVector");
           newClassDescr1->addItem ("CollisionType");
           newClassDescr1->addItem ("CollisionLocation");
           newClassDescr1->addItem ("EventIdentifier");
           newClassDescr1->addItem ("IssuingObjectIdentifier");


//      (class1 Comment reliable receive
//        (parameter OriginatingEntity)
//        (parameter ReceivingEntity)
//        (parameter VariableDatumSet)
//      )
           s = "Comment";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("OriginatingEntity");
           newClassDescr1->addItem ("ReceivingEntity");
           newClassDescr1->addItem ("VariableDatumSet");


//      (class1 CreateObjectRequest reliable receive
//        (parameter ObjectClass)
//        (parameter AttributeValueSet)
//        (parameter RequestIdentifier)
//      )
           s = "CreateObjectRequest";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("ObjectClass");
           newClassDescr1->addItem ("AttributeValueSet");
           newClassDescr1->addItem ("RequestIdentifier");


//      (class1 CreateObjectResult reliable receive
//        (parameter CreateObjectResult)
//        (parameter RequestIdentifier)
//      )
           s = "CreateObjectResult";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("CreateObjectResult");
           newClassDescr1->addItem ("RequestIdentifier");


//      (class1 CreateEntity reliable receive
//        (parameter OriginatingEntity)
//        (parameter ReceivingEntity)
//        (parameter RequestIdentifier)
//      )
           s = "CreateEntity";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("OriginatingEntity");
           newClassDescr1->addItem ("ReceivingEntity");
           newClassDescr1->addItem ("RequestIdentifier");


//      (class1 Data reliable receive
//        (parameter OriginatingEntity)
//        (parameter ReceivingEntity)
//        (parameter RequestIdentifier)
//        (parameter FixedDatums)
//        (parameter VariableDatumSet)
//      )
           s = "Data";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("OriginatingEntity");
           newClassDescr1->addItem ("ReceivingEntity");
           newClassDescr1->addItem ("RequestIdentifier");
           newClassDescr1->addItem ("FixedDatums");
           newClassDescr1->addItem ("VariableDatumSet");


//      (class1 DataQuery reliable receive
//        (parameter OriginatingEntity)
//        (parameter ReceivingEntity)
//        (parameter RequestIdentifier)
//        (parameter TimeInterval)
//        (parameter FixedDatumIdentifiers)
//        (parameter VariableDatumIdentifiers)
//      )
           s = "DataQuery";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("OriginatingEntity");
           newClassDescr1->addItem ("ReceivingEntity");
           newClassDescr1->addItem ("RequestIdentifier");
           newClassDescr1->addItem ("TimeInterval");
           newClassDescr1->addItem ("FixedDatumIdentifiers");
           newClassDescr1->addItem ("VariableDatumIdentifiers");


//      (class1 EventReport reliable receive
//        (parameter OriginatingEntity)
//        (parameter ReceivingEntity)
//        (parameter EventType)
//        (parameter FixedDatums)
//        (parameter VariableDatumSet)
//      )
           s = "EventReport";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("OriginatingEntity");
           newClassDescr1->addItem ("ReceivingEntity");
           newClassDescr1->addItem ("EventType");
           newClassDescr1->addItem ("FixedDatums");
           newClassDescr1->addItem ("VariableDatumSet");


//      (class1 MunitionDetonation reliable receive
//        (parameter ArticulatedPartData)
//        (parameter DetonationLocation)
//        (parameter DetonationResultCode)
//        (parameter EventIdentifier)
//        (parameter FiringObjectIdentifier)
//        (parameter FinalVelocityVector)
//        (parameter FuseType)
//        (parameter MunitionObjectIdentifier)
//        (parameter MunitionType)
//        (parameter QuantityFired)
//        (parameter RateOfFire)
//        (parameter RelativeDetonationLocation)
//        (parameter TargetObjectIdentifier)
//        (parameter WarheadType)
//      )
           s = "MunitionDetonation";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("ArticulatedPartData");
           newClassDescr1->addItem ("DetonationLocation");
           newClassDescr1->addItem ("DetonationResultCode");
           newClassDescr1->addItem ("EventIdentifier");
           newClassDescr1->addItem ("FiringObjectIdentifier");
           newClassDescr1->addItem ("FinalVelocityVector");
           newClassDescr1->addItem ("FuseType");
           newClassDescr1->addItem ("MunitionObjectIdentifier");
           newClassDescr1->addItem ("MunitionType");
           newClassDescr1->addItem ("QuantityFired");
           newClassDescr1->addItem ("RateOfFire");
           newClassDescr1->addItem ("RelativeDetonationLocation");
           newClassDescr1->addItem ("TargetObjectIdentifier");
           newClassDescr1->addItem ("WarheadType");


//      (class1 RadioSignal reliable receive
           s = "RadioSignal";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);

//        (class2 ApplicationSpecificRadioSignal reliable receive
//          (parameter HostRadioIndex)
//          (parameter DataRate)
//          (parameter SignalDataLength)
//          (parameter SignalData)
//          (parameter TacticalDataLinkType)
//          (parameter TDLMessageCount)
//          (parameter UserProtocolID)
//        )
             s = "ApplicationSpecificRadioSignal";
             newClassDescr2 = new ClassDescr (s, newClassDescr1, &threadData);
             newClassDescr2->addItem ("HostRadioIndex");
             newClassDescr2->addItem ("DataRate");
             newClassDescr2->addItem ("SignalDataLength");
             newClassDescr2->addItem ("SignalData");
             newClassDescr2->addItem ("TacticalDataLinkType");
             newClassDescr2->addItem ("TDLMessageCount");
             newClassDescr2->addItem ("UserProtocolID");

//        (class2 DatabaseIndexRadioSignal reliable receive
//          (parameter HostRadioIndex)
//          (parameter DatabaseIndex)
//          (parameter Duration)
//          (parameter StartOffset)
//          (parameter TacticalDataLinkType)
//          (parameter TDLMessageCount)
//        )
             s = "DatabaseIndexRadioSignal";
             newClassDescr2 = new ClassDescr (s, newClassDescr1, &threadData);
             newClassDescr2->addItem ("HostRadioIndex");
             newClassDescr2->addItem ("DatabaseIndex");
             newClassDescr2->addItem ("Duration");
             newClassDescr2->addItem ("StartOffset");
             newClassDescr2->addItem ("TacticalDataLinkType");
             newClassDescr2->addItem ("TDLMessageCount");


//        (class2 EncodedAudioRadioSignal reliable receive
//          (parameter HostRadioIndex)
//          (parameter TransmitterSignalEncodingType)
//          (parameter SignalSampleRate)
//          (parameter SampleCount)
//          (parameter SignalDataLength)
//          (parameter SignalData)
//        )
             s = "EncodedAudioRadioSignal";
             newClassDescr2 = new ClassDescr (s, newClassDescr1, &threadData);
             newClassDescr2->addItem ("HostRadioIndex");
             newClassDescr2->addItem ("TransmitterSignalEncodingType");
             newClassDescr2->addItem ("SignalSampleRate");
             newClassDescr2->addItem ("SampleCount");
             newClassDescr2->addItem ("SignalDataLength");
             newClassDescr2->addItem ("SignalData");


//        (class2 RawBinaryRadioSignal reliable receive
//          (parameter HostRadioIndex)
//          (parameter DataRate)
//          (parameter SignalDataLength)
//          (parameter SignalData)
//          (parameter TacticalDataLinkType)
//          (parameter TDLMessageCount)
//        )
             s = "RawBinaryRadioSignal";
             newClassDescr2 = new ClassDescr (s, newClassDescr1, &threadData);
             newClassDescr2->addItem ("HostRadioIndex");
             newClassDescr2->addItem ("DataRate");
             newClassDescr2->addItem ("SignalDataLength");
             newClassDescr2->addItem ("SignalData");
             newClassDescr2->addItem ("TacticalDataLinkType");
             newClassDescr2->addItem ("TDLMessageCount");


//      )

//      (class1 RemoveObjectRequest reliable receive
//        (parameter ObjectIdentifiers)
//        (parameter RequestIdentifier)
//      )
           s = "RemoveObjectRequest";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("ObjectIdentifiers");
           newClassDescr1->addItem ("RequestIdentifier");


//      (class1 RemoveObjectResult reliable receive
//        (parameter RemoveObjectResult)
//        (parameter RequestIdentifier)
//      )
           s = "RemoveObjectResult";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("RemoveObjectResult");
           newClassDescr1->addItem ("RequestIdentifier");


//      (class1 RemoveEntity reliable receive
//        (parameter OriginatingEntity)
//        (parameter ReceivingEntity)
//        (parameter RequestIdentifier)
//      )
           s = "RemoveEntity";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("OriginatingEntity");
           newClassDescr1->addItem ("ReceivingEntity");
           newClassDescr1->addItem ("RequestIdentifier");


//      (class1 RepairComplete reliable receive
//        (parameter ReceivingObject)
//        (parameter RepairingObject)
//        (parameter RepairType)
//      )
           s = "RepairComplete";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("ReceivingObject");
           newClassDescr1->addItem ("RepairingObject");
           newClassDescr1->addItem ("RepairType");


//      (class1 RepairResponse reliable receive
//        (parameter ReceivingObject)
//        (parameter RepairingObject)
//        (parameter RepairResultCode)
//      )
           s = "RepairResponse";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("ReceivingObject");
           newClassDescr1->addItem ("RepairingObject");
           newClassDescr1->addItem ("RepairResultCode");


//      (class1 ResupplyCancel reliable receive
//        (parameter ReceivingObject)
//        (parameter SupplyingObject)
//      )
           s = "ResupplyCancel";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("ReceivingObject");
           newClassDescr1->addItem ("SupplyingObject");


//      (class1 ResupplyOffer reliable receive
//        (parameter ReceivingObject)
//        (parameter SupplyingObject)
//        (parameter SuppliesData)
//      )
           s = "ResupplyOffer";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("ReceivingObject");
           newClassDescr1->addItem ("SupplyingObject");
           newClassDescr1->addItem ("SuppliesData");


//      (class1 ResupplyReceived reliable receive
//        (parameter ReceivingObject)
//        (parameter SupplyingObject)
//        (parameter SuppliesData)
//      )
           s = "ResupplyReceived";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("ReceivingObject");
           newClassDescr1->addItem ("SupplyingObject");
           newClassDescr1->addItem ("SuppliesData");


//      (class1 ServiceRequest reliable receive
//        (parameter RequestingObject)
//        (parameter ServicingObject)
//        (parameter ServiceType)
//        (parameter SuppliesData)
//      )
           s = "ServiceRequest";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("RequestingObject");
           newClassDescr1->addItem ("ServicingObject");
           newClassDescr1->addItem ("ServiceType");
           newClassDescr1->addItem ("SuppliesData");

 
//      (class1 SetData reliable receive
//        (parameter OriginatingEntity)
//        (parameter ReceivingEntity)
//        (parameter RequestIdentifier)
//        (parameter FixedDatums)
//        (parameter VariableDatumSet)
//      )
           s = "SetData";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("OriginatingEntity");
           newClassDescr1->addItem ("ReceivingEntity");
           newClassDescr1->addItem ("RequestIdentifier");
           newClassDescr1->addItem ("FixedDatums");
           newClassDescr1->addItem ("VariableDatumSet");


//      (class1 StartResume reliable receive
//        (parameter OriginatingEntity)
//        (parameter ReceivingEntity)
//        (parameter RequestIdentifier)
//        (parameter RealWorldTime)
//        (parameter SimulationTime)
//      )
           s = "StartResume";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("OriginatingEntity");
           newClassDescr1->addItem ("ReceivingEntity");
           newClassDescr1->addItem ("RequestIdentifier");
           newClassDescr1->addItem ("RealWorldTime");
           newClassDescr1->addItem ("SimulationTime");


//      (class1 StopFreeze reliable receive
//        (parameter OriginatingEntity)
//        (parameter ReceivingEntity)
//        (parameter RequestIdentifier)
//        (parameter RealWorldTime)
//        (parameter Reason)
//        (parameter ReflectValues)
//        (parameter RunInternalSimulationClock)
//        (parameter UpdateAttributes)
//      )
           s = "StopFreeze";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("OriginatingEntity");
           newClassDescr1->addItem ("ReceivingEntity");
           newClassDescr1->addItem ("RequestIdentifier");
           newClassDescr1->addItem ("RealWorldTime");
           newClassDescr1->addItem ("Reason");
           newClassDescr1->addItem ("ReflectValues");
           newClassDescr1->addItem ("RunInternalSimulationClock");
           newClassDescr1->addItem ("UpdateAttributes");


//      (class1 WeaponFire reliable receive
//        (parameter EventIdentifier)
//        (parameter FireControlSolutionRange)
//        (parameter FireMissionIndex)
//        (parameter FiringLocation)
//        (parameter FiringObjectIdentifier)
//        (parameter FuseType)
//        (parameter InitialVelocityVector)
//        (parameter MunitionObjectIdentifier)
//        (parameter MunitionType)
//        (parameter QuantityFired)
//        (parameter RateOfFire)
//        (parameter TargetObjectIdentifier)
//        (parameter WarheadType)
//      )
           s = "WeaponFire";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);
           newClassDescr1->addItem ("EventIdentifier");
           newClassDescr1->addItem ("FireControlSolutionRange");
           newClassDescr1->addItem ("FireMissionIndex");
           newClassDescr1->addItem ("FiringLocation");
           newClassDescr1->addItem ("FiringObjectIdentifier");
           newClassDescr1->addItem ("FuseType");
           newClassDescr1->addItem ("InitialVelocityVector");
           newClassDescr1->addItem ("MunitionObjectIdentifier");
           newClassDescr1->addItem ("MunitionType");
           newClassDescr1->addItem ("QuantityFired");
           newClassDescr1->addItem ("RateOfFire");
           newClassDescr1->addItem ("TargetObjectIdentifier");
           newClassDescr1->addItem ("WarheadType");


//      (class1 Manager reliable receive
           s = "Manager";
           newClassDescr1 = new ClassDescr (s, pInteractionRoot, &threadData);

//        (class2 Federate reliable receive
//          (parameter Federate)
             s = "Federate";
             newClassDescr2 = new ClassDescr (s, newClassDescr1, &threadData);
             newClassDescr2->addItem ("Federate");

//          (class3 Request reliable receive
               s = "Request";
               newClassDescr3 = new ClassDescr (s, newClassDescr2, &threadData);

//            (class4 RequestPublications reliable receive
//            )
                 s = "RequestPublications";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);


//            (class4 RequestSubscriptions reliable receive
//            )
                 s = "RequestSubscriptions";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);


//            (class4 RequestObjectsOwned reliable receive
//            )
                 s = "RequestObjectsOwned";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);


//            (class4 RequestObjectsUpdated reliable receive
//            )
                 s = "RequestObjectsUpdated";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);


//            (class4 RequestObjectsReflected reliable receive
//            )
                 s = "RequestObjectsReflected";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);


//            (class4 RequestUpdatesSent reliable receive
//            )
                 s = "RequestUpdatesSent";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);


//            (class4 RequestInteractionsSent reliable receive
//            )
                 s = "RequestInteractionsSent";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);


//            (class4 RequestReflectionsReceived reliable receive
//            )
                 s = "RequestReflectionsReceived";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);


//            (class4 RequestInteractionsReceived reliable receive
//            )
                 s = "RequestInteractionsReceived";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);


//            (class4 RequestObjectInformation reliable receive
//              (parameter ObjectInstance)
//            )
                 s = "RequestObjectInformation";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("ObjectInstance");


//          )

//          (class3 Report reliable receive
               s = "Report";
               newClassDescr3 = new ClassDescr (s, newClassDescr2, &threadData);

//            (class4 ReportObjectPublication reliable receive
//              (parameter NumberOfClasses)
//              (parameter ObjectClass)
//              (parameter AttributeList)
//            )
                 s = "ReportObjectPublication";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("NumberOfClasses");
                 newClassDescr4->addItem ("ObjectClass");
                 newClassDescr4->addItem ("AttributeList");


//            (class4 ReportObjectSubscription reliable receive
//              (parameter NumberOfClasses)
//              (parameter ObjectClass)
//              (parameter Active)
//              (parameter AttributeList)
//            )
                 s = "ReportObjectSubscription";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("NumberOfClasses");
                 newClassDescr4->addItem ("ObjectClass");
                 newClassDescr4->addItem ("Active");
                 newClassDescr4->addItem ("AttributeList");


//            (class4 ReportInteractionPublication reliable receive
//              (parameter InteractionClassList)
//            )
                 s = "ReportInteractionPublication";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("InteractionClassList");


//            (class4 ReportInteractionSubscription reliable receive
//              (parameter InteractionClassList)
//            )
                 s = "ReportInteractionSubscription";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("InteractionClassList");


//            (class4 ReportObjectsOwned reliable receive
//              (parameter ObjectCounts)
//            )
                 s = "ReportObjectsOwned";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("ObjectCounts");


//            (class4 ReportObjectsUpdated reliable receive
//              (parameter ObjectCounts)
//            )
                 s = "ReportObjectsUpdated";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("ObjectCounts");


//            (class4 ReportObjectsReflected reliable receive
//              (parameter ObjectCounts)
//            )
                 s = "ReportObjectsReflected";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("ObjectCounts");


//            (class4 ReportUpdatesSent reliable receive
//              (parameter TransportationType)
//              (parameter UpdateCounts)
//            )
                 s = "ReportUpdatesSent";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("TransportationType");
                 newClassDescr4->addItem ("UpdateCounts");


//            (class4 ReportReflectionsReceived reliable receive
//              (parameter TransportationType)
//              (parameter ReflectCounts)
//            )
                 s = "ReportReflectionsReceived";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("TransportationType");
                 newClassDescr4->addItem ("ReflectCounts");


//            (class4 ReportInteractionsSent reliable receive
//              (parameter TransportationType)
//              (parameter InteractionCounts)
//            )
                 s = "ReportInteractionsSent";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("TransportationType");
                 newClassDescr4->addItem ("InteractionCounts");


//            (class4 ReportInteractionsReceived reliable receive
//              (parameter TransportationType)
//              (parameter InteractionCounts)
//            )
                 s = "ReportInteractionsReceived";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("TransportationType");
                 newClassDescr4->addItem ("InteractionCounts");


//            (class4 ReportObjectInformation reliable receive
//              (parameter ObjectInstance)
//              (parameter OwnedAttributeList)
//              (parameter RegisteredClass)
//              (parameter KnownClass)
//            )
                 s = "ReportObjectInformation";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("ObjectInstance");
                 newClassDescr4->addItem ("OwnedAttributeList");
                 newClassDescr4->addItem ("RegisteredClass");
                 newClassDescr4->addItem ("KnownClass");


//            (class4 Alert reliable receive
//              (parameter AlertSeverity)
//              (parameter AlertDescription)
//              (parameter AlertID)
//            )
                 s = "Alert";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("AlertSeverity");
                 newClassDescr4->addItem ("AlertDescription");
                 newClassDescr4->addItem ("AlertID");


//            (class4 ReportServiceInvocation reliable receive
//              (parameter Service)
//              (parameter Initiator)
//              (parameter SuccessIndicator)
//              (parameter SuppliedArgument1)
//              (parameter SuppliedArgument2)
//              (parameter SuppliedArgument3)
//              (parameter SuppliedArgument4)
//              (parameter SuppliedArgument5)
//              (parameter ReturnedArgument)
//              (parameter ExceptionDescription)
//              (parameter ExceptionID)
//            )
                 s = "ReportServiceInvocation";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("Service");
                 newClassDescr4->addItem ("Initiator");
                 newClassDescr4->addItem ("SuccessIndicator");
                 newClassDescr4->addItem ("SuppliedArgument1");
                 newClassDescr4->addItem ("SuppliedArgument2");
                 newClassDescr4->addItem ("SuppliedArgument3");
                 newClassDescr4->addItem ("SuppliedArgument4");
                 newClassDescr4->addItem ("SuppliedArgument5");
                 newClassDescr4->addItem ("ReturnedArgument");
                 newClassDescr4->addItem ("ExceptionDescription");
                 newClassDescr4->addItem ("ExceptionID");


//          )

//          (class3 Adjust reliable receive
               s = "Adjust";
               newClassDescr3 = new ClassDescr (s, newClassDescr2, &threadData);

//            (class4 SetTiming reliable receive
//              (parameter ReportPeriod)
//            )
                 s = "SetTiming";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("ReportPeriod");


//            (class4 ModifyAttributeState reliable receive
//              (parameter ObjectInstance)
//              (parameter Attribute)
//              (parameter AttributeState)
//            )
                 s = "ModifyAttributeState";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("ObjectInstance");
                 newClassDescr4->addItem ("Attribute");
                 newClassDescr4->addItem ("AttributeState");


//            (class4 SetServiceReporting reliable receive
//              (parameter ReportingState)
//            )
                 s = "SetServiceReporting";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("ReportingState");


//            (class4 SetExceptionLogging reliable receive
//              (parameter LoggingState)
//            )
                 s = "SetExceptionLogging";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("LoggingState");


//          )

//          (class3 Service reliable receive
               s = "Service";
               newClassDescr3 = new ClassDescr (s, newClassDescr2, &threadData);

//            (class4 ResignFederationExecution reliable receive
//              (parameter ResignAction)
//            )
                 s = "ResignFederationExecution";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("ResignAction");


//            (class4 SynchronizationPointAchieved reliable receive
//              (parameter Label)
//            )
                 s = "SynchronizationPointAchieved";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("Label");


//            (class4 FederateSaveBegun reliable receive
//            )
                 s = "FederateSaveBegun";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);


//            (class4 FederateSaveComplete reliable receive
//              (parameter SuccessIndicator)
//            )
                 s = "FederateSaveComplete";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("SuccessIndicator");


//            (class4 FederateRestoreComplete reliable receive
//              (parameter SuccessIndicator)
//            )
                 s = "FederateRestoreComplete";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("SuccessIndicator");


//            (class4 PublishObjectClass reliable receive
//              (parameter ObjectClass)
//              (parameter AttributeList)
//            )
                 s = "PublishObjectClass";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("ObjectClass");
                 newClassDescr4->addItem ("AttributeList");


//            (class4 UnpublishObjectClass reliable receive
//              (parameter ObjectClass)
//            )
                 s = "UnpublishObjectClass";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("ObjectClass");


//            (class4 PublishInteractionClass reliable receive
//              (parameter InteractionClass)
//            )
                 s = "PublishInteractionClass";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("InteractionClass");


//            (class4 UnpublishInteractionClass reliable receive
//              (parameter InteractionClass)
//            )
                 s = "UnpublishInteractionClass";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("InteractionClass");


//            (class4 SubscribeObjectClassAttributes reliable receive
//              (parameter ObjectClass)
//              (parameter AttributeList)
//              (parameter Active)
//            )
                 s = "SubscribeObjectClassAttributes";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("ObjectClass");
                 newClassDescr4->addItem ("AttributeList");
                 newClassDescr4->addItem ("Active");


//            (class4 UnsubscribeObjectClass reliable receive
//              (parameter ObjectClass)
//            )
                 s = "UnsubscribeObjectClass";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("ObjectClass");


//            (class4 SubscribeInteractionClass reliable receive
//             (parameter InteractionClass)
//             (parameter Active)
//            )
                 s = "SubscribeInteractionClass";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("InteractionClass");
                 newClassDescr4->addItem ("Active");


//            (class4 UnsubscribeInteractionClass reliable receive
//              (parameter InteractionClass)
//            )
                 s = "UnsubscribeInteractionClass";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("InteractionClass");


//            (class4 DeleteObjectInstance reliable receive
//              (parameter ObjectInstance)
//              (parameter Tag)
//              (parameter FederationTime)
//            )
                 s = "DeleteObjectInstance";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("ObjectInstance");
                 newClassDescr4->addItem ("Tag");
                 newClassDescr4->addItem ("FederationTime");


//            (class4 LocalDeleteObjectInstance reliable receive
//              (parameter ObjectInstance)
//            )
                 s = "LocalDeleteObjectInstance";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("ObjectInstance");


//            (class4 ChangeAttributeTransportationType reliable receive
//              (parameter ObjectInstance)
//              (parameter AttributeList)
//              (parameter TransportationType)
//            )
                 s = "ChangeAttributeTransportationType";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("ObjectInstance");
                 newClassDescr4->addItem ("AttributeList");
                 newClassDescr4->addItem ("TransportationType");


//            (class4 ChangeAttributeOrderType reliable receive
//              (parameter ObjectInstance)
//              (parameter AttributeList)
//              (parameter OrderingType)
//            )
                 s = "ChangeAttributeOrderType";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("ObjectInstance");
                 newClassDescr4->addItem ("AttributeList");
                 newClassDescr4->addItem ("OrderingType");


//            (class4 ChangeInteractionTransportationType reliable receive
//              (parameter InteractionClass)
//              (parameter TransportationType)
//            )
                 s = "ChangeInteractionTransportationType";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("InteractionClass");
                 newClassDescr4->addItem ("TransportationType");


//            (class4 ChangeInteractionOrderType reliable receive
//              (parameter InteractionClass)
//              (parameter OrderingType)
//            )
                 s = "ChangeInteractionOrderType";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("InteractionClass");
                 newClassDescr4->addItem ("OrderingType");


//            (class4 UnconditionalAttributeOwnershipDivestiture reliable receive
//              (parameter ObjectInstance)
//              (parameter AttributeList)
//            )
                 s = "UnconditionalAttributeOwnershipDivestiture";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("ObjectInstance");
                 newClassDescr4->addItem ("AttributeList");


//            (class4 EnableTimeRegulation reliable receive
//              (parameter FederationTime)
//              (parameter Lookahead)
//            )
                 s = "EnableTimeRegulation";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("FederationTime");
                 newClassDescr4->addItem ("Lookahead");


//            (class4 DisableTimeRegulation reliable receive
//            )
                 s = "DisableTimeRegulation";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);


//            (class4 EnableTimeConstrained reliable receive
//            )
                 s = "EnableTimeConstrained";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);


//            (class4 DisableTimeConstrained reliable receive
//            )
                 s = "DisableTimeConstrained";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);


//            (class4 EnableAsynchronousDelivery reliable receive
//            )
                 s = "EnableAsynchronousDelivery";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);


//            (class4 DisableAsynchronousDelivery reliable receive
//            )
                 s = "DisableAsynchronousDelivery";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);


//            (class4 ModifyLookahead reliable receive
//              (parameter Lookahead)
//            )
                 s = "ModifyLookahead";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("Lookahead");


//            (class4 TimeAdvanceRequest reliable receive
//              (parameter FederationTime)
//            )
                 s = "TimeAdvanceRequest";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("FederationTime");


//            (class4 TimeAdvanceRequestAvailable reliable receive
//              (parameter FederationTime)
//            )
                 s = "TimeAdvanceRequestAvailable";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("FederationTime");


//            (class4 NextEventRequest reliable receive
//              (parameter FederationTime)
//            )
                 s = "NextEventRequest";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("FederationTime");


//            (class4 NextEventRequestAvailable reliable receive
//              (parameter FederationTime)
//            )
                 s = "NextEventRequestAvailable";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("FederationTime");


//            (class4 FlushQueueRequest reliable receive
//              (parameter FederationTime)
//            )
                 s = "FlushQueueRequest";
                 newClassDescr4 = new ClassDescr (s, newClassDescr3, &threadData);
                 newClassDescr4->addItem ("FederationTime");


//          )

//        )

//      )

//    )
//  )
