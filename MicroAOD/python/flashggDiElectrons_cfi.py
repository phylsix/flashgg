
import FWCore.ParameterSet.Config as cms

flashggDiElectrons = cms.EDProducer('FlashggDiElectronProducer',
                                  electronTag=cms.InputTag('slimmedElectrons'),
                                  vertexTag=cms.InputTag('offlineSlimmedPrimaryVertices'), 
                                  ##Parameters                                                
                                  minElectronPT=cms.double(20.),
                                  maxElectronEta=cms.double(2.4)
                                  )
