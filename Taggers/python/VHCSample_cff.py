import FWCore.ParameterSet.Config as cms
from flashgg.MicroAOD.flashggJets_cfi import flashggBTag, maxJetCollections

bDiscriminator74X = cms.vdouble(0.605,0.890)
bDiscriminator76X = cms.vdouble(0.460,0.800)



VHCSample = cms.EDProducer("FlashggVHCSampleProducer",
                                   DiPhotonTag=cms.InputTag('flashggPreselectedDiPhotons'),
                                   SystLabel=cms.string(""),
                                   #JetTag=cms.InputTag('flashggSelectedJets'),
                                   #inputTagJets= UnpackedJetCollectionVInputTag,
                                   ElectronTag=cms.InputTag('flashggSelectedElectrons'),
                                   MuonTag=cms.InputTag('flashggSelectedMuons'),
                                   VertexTag=cms.InputTag('offlineSlimmedPrimaryVertices'),
                                   MVAResultTag=cms.InputTag('flashggDiPhotonMVA'),
                                   METTag=cms.InputTag('slimmedMETs'),
                                   GenParticleTag=cms.InputTag( "flashggPrunedGenParticles" ),
                                   leptonPtThreshold = cms.double(20),
                                   muonEtaThreshold = cms.double(2.4),
                                   leadPhoOverMassThreshold = cms.double(0.375),
                                   subleadPhoOverMassThreshold = cms.double(0.25),
                                   MVAThreshold = cms.double(-1.0),
                                   deltaRMuonPhoThreshold = cms.double(1),
                                   #jetsNumberThreshold = cms.double(3.),
                                   #jetPtThreshold = cms.double(20.),
                                   #jetEtaThreshold= cms.double(2.4),
                                   #deltaRPhoLeadJet = cms.double(0.5),
                                   #deltaRPhoSubLeadJet = cms.double(0.5),
                                   muPFIsoSumRelThreshold = cms.double(0.25), 
                                   #deltaRJetMuonThreshold = cms.double(0.5),
                                   PuIDCutoffThreshold = cms.double(0.8),
                                   PhoMVAThreshold = cms.double(-0.9),
                                   METThreshold = cms.double(45.),
                                   ElectronPtThreshold = cms.double(20.),
                                   DeltaRTrkElec = cms.double(1.),
                                   TransverseImpactParam = cms.double(0.02),
                                   LongitudinalImpactParam = cms.double(0.2),
                                   deltaRPhoElectronThreshold = cms.double(1.),
                                   deltaMassElectronZThreshold = cms.double(10.),
                                   electronEtaThresholds=cms.vdouble(1.4442,1.566,2.5),
                                   nonTrigMVAThresholds = cms.vdouble(0.913286,0.805013,0.358969),
                                   nonTrigMVAEtaCuts = cms.vdouble(0.8,1.479,2.5),
                                   electronIsoThreshold = cms.double(0.15),
                                   electronNumOfHitsThreshold = cms.double(1)

				    )

