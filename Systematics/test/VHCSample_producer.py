import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils
#from flashgg.Systematics.tagVariables import * 
process = cms.Process("CSampleProduce")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = 'POSTLS170_V5::All'
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc')
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
#process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32( 100000 )

# Uncomment the following if you notice you have a memory leak
# This is a lightweight tool to digg further
#process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",
#                                        ignoreTotal = cms.untracked.int32(1),
#                                        monitorPssAndPrivate = cms.untracked.bool(True)
#                                       )

process.source = cms.Source ("PoolSource",fileNames = cms.untracked.vstring(
        "/store/group/phys_higgs/cmshgg/ferriff/flashgg/RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2/2_2_0/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2-2_2_0-v0-RunIISpring16MiniAODv1-PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_v3-v1/160707_151052/0000/myMicroAODOutputFile_1.root"
	#"/store/group/phys_higgs/cmshgg/ferriff/flashgg/RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2/2_2_0/DoubleEG/RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2-2_2_0-v0-Run2016B-PromptReco-v1/160707_143214/0000/myMicroAODOutputFile_10.root"
	#"/store/group/phys_higgs/cmshgg/ferriff/flashgg/RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2/2_2_0/DoubleEG/RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2-2_2_0-v0-Run2016B-PromptReco-v1/160707_143214/0000/myMicroAODOutputFile_107.root",
	#"/store/group/phys_higgs/cmshgg/ferriff/flashgg/RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2/2_2_0/DoubleEG/RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2-2_2_0-v0-Run2016B-PromptReco-v1/160707_143214/0000/myMicroAODOutputFile_108.root",
	#"/store/group/phys_higgs/cmshgg/ferriff/flashgg/RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2/2_2_0/DoubleEG/RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2-2_2_0-v0-Run2016B-PromptReco-v1/160707_143214/0000/myMicroAODOutputFile_109.root",
	#"/store/group/phys_higgs/cmshgg/ferriff/flashgg/RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2/2_2_0/DoubleEG/RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2-2_2_0-v0-Run2016B-PromptReco-v1/160707_143214/0000/myMicroAODOutputFile_110.root",
	#"/store/group/phys_higgs/cmshgg/ferriff/flashgg/RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2/2_2_0/DoubleEG/RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2-2_2_0-v0-Run2016B-PromptReco-v1/160707_143214/0000/myMicroAODOutputFile_110.root"
	#"/store/group/phys_higgs/cmshgg/ferriff/flashgg/RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2/2_2_0/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2-2_2_0-v0-RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016_v3-v1/160707_142718/0000/myMicroAODOutputFile_100.root",
	#"/store/group/phys_higgs/cmshgg/ferriff/flashgg/RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2/2_2_0/DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa/RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2-2_2_0-v0-RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/160707_143055/0000/myMicroAODOutputFile_66.root"
	#"/store/group/phys_higgs/cmshgg/ferriff/flashgg/RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2/2_2_0/QCD_Pt-30to40_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8/RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2-2_2_0-v0-RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/160707_145255/0000/myMicroAODOutputFile_11.root"
))

#process.load("flashgg/Taggers/customSequence_cfi")
#process.load("flashgg/Taggers/flashggTagTester_cfi")
# For debugging
switchToUnPreselected = False
switchToFinal = False
switchToPuppi = False
switchToReadOld = False
assert(not switchToUnPreselected or not switchToFinal)
assert(not switchToReadOld or not switchToUnPreselected)
assert(not switchToReadOld or not switchToFinal)

if switchToUnPreselected:
    from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
    massSearchReplaceAnyInputTag(process.flashggTagSequence,cms.InputTag("flashggPreselectedDiPhotons"),cms.InputTag("flashggDiPhotons"))

if switchToFinal:
    from flashgg.MicroAOD.flashggFinalEGamma_cfi import flashggFinalEGamma
    from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
    massSearchReplaceAnyInputTag(process.flashggTagSequence,cms.InputTag("flashggPreselectedDiPhotons"),cms.InputTag("flashggFinalEGamma",flashggFinalEGamma.DiPhotonCollectionName.value()))

if switchToPuppi:
    process.flashggUnpackedJets.JetsTag = cms.InputTag("flashggFinalPuppiJets")

from flashgg.Taggers.flashggTagOutputCommands_cff import tagDefaultOutputCommand

#process.out = cms.OutputModule("PoolOutputModule", fileName = cms.untracked.string('/tmp/nancy/vhEtTagOutputFile_Data.root'),
#                               outputCommands = tagDefaultOutputCommand			       
#                               )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("test.root"))

from flashgg.Taggers.tagsDumpers_cfi import createTagDumper
import flashgg.Taggers.dumperConfigTools as cfgTools

#process.out = cms.OutputModule("PoolOutputModule",
#                               fileName = cms.untracked.string('general.root'),
#                               #outputCommands = tagDefaultOutputCommand			       
#                               )

#process.load("flashgg.Taggers.customDumpers_cfi")
process.load("flashgg.Taggers.tagsDumpers_cfi")

#from flashgg.Taggers.VHCSample_cff import CSampleDumper 
#from flashgg.Taggers.flashggTagSequence_cfi import flashggTagSequence
process.load("flashgg.Taggers.VHCSample_cff")
process.load("flashgg.Taggers.flashggTagSequence_cfi")

#process.CSampleTagDumper = createTagDumper("CSampleTag")
#process.CSampleTagDumper.dumpTrees = True
#process.CSampleTagDumper.dumpWorkspace = False
#process.CSampleTagDumper.quietRooFit = True

process.CSampleDumper = createTagDumper("VHLooseTag")
process.CSampleDumper.src = cms.InputTag("VHCSample")  
process.CSampleDumper.dumpTrees = True
process.CSampleDumper.dumpWorkspace = False
process.CSampleDumper.quietRooFit = True


#process.load("flashgg.Taggers.diphotonTagDumper_cfi") ##  import diphotonTagDumper 
#process.tagsDumper.className = "DiPhotonTagDumper"
#process.tagsDumper.src = "flashggTagMerger"
##process.tagsDumper.src = "flashggTagSystematics"
#process.tagsDumper.processId = "test"
#process.tagsDumper.dumpTrees = True
#process.tagsDumper.dumpWorkspace = False 
#process.tagsDumper.dumpHistos = False
#process.tagsDumper.quietRooFit = True
#process.tagsDumper.nameTemplate = cms.untracked.string("$PROCESS_$SQRTS_$CLASSNAME_$SUBCAT_$LABEL")

#tagList=[
#    ["UntaggedTag",4],
#    ["VBFTag",2],
#    ["VHTightTag",0],
#    ["VHLooseTag",0],
#    ["VHEtTag",0],
#    ["VHHadronicTag",0],
#    ["TTHHadronicTag",0],
#    ["TTHLeptonicTag",0]
#    ]
#
#systlabels = [""]
#process.tagsDumper.classifierCfg.remap=cms.untracked.VPSet()
#process.flashggTagMerger = cms.EDProducer("TagMerger",src=cms.VInputTag("flashggTagSorter"))
#for tag in tagList: 
#  tagName=tag[0]
#  tagCats=tag[1]
#  # remap return value of class-based classifier
#  process.tagsDumper.classifierCfg.remap.append( cms.untracked.PSet( src=cms.untracked.string("flashgg%s"%tagName), dst=cms.untracked.string(tagName) ) )
#  cfgTools.addCategory(process.tagsDumper,
#                           label="",
#                           #classname=tagName,
#                           cutbased=None,
#                           subcats=tagCats, 
#                           variables=dipho_var,
#                           histograms=[],
#		           mvas=None,
#			   classname=tagName,
#                           binnedOnly=None,
#                           dumpPdfWeights=False,
#                           nPdfWeights=-1,
#                           nAlphaSWeights=-1,
#                           nScaleWeights=-1
#                           )

dipho_var = ["invM := diphoton().mass()",
	     #"mva",
	     "leadPt := diphoton().leadingPhoton().Pt()",
	     "subleadPt := diphoton().subleadingPhoton().Pt()"
	     ]

cfgTools.addCategories(process.CSampleDumper,
			[
			("All","1",0)
			],
			variables= dipho_var, #+ vhlVariables,
			histograms=[
			#
			]
		)



#process.vbfTagDumper.classifierCfg.remap=cms.untracked.VPSet()
#process.vbfTagDumper.classifierCfg.remap.append(cms.untracked.PSet( src=cms.untracked.string("flashggVBFTag"), dst=cms.untracked.string("VBFTag") ) )
#
#cfgTools.addCategory(process.vbfTagDumper,
#	      	     systlabel="",
#	             classname="VBFTag",
#	             cutbased=None,	
#	             subcats=2,
#	             variables=truthVariables,				
#	             histograms=[],
#	             binnedOnly=False,
#	             dumpPdfWeights=False,
#	             nPdfWeights=-1,
#	             nAlphaSWeights=-1,
#	             nScaleWeights=-1	
#		)

from flashgg.MetaData.JobConfig import customize

process.dataRequirements = cms.Sequence()

from HLTrigger.HLTfilters.hltHighLevel_cfi import hltHighLevel
process.hltHighLevel= hltHighLevel.clone(HLTPaths = cms.vstring("HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90_v*",
#                                                                "HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_DoublePixelVeto_Mass55_v1",
#                                                                "HLT_Diphoton30EB_18EB_R9Id_OR_IsoCaloId_AND_HE_R9Id_DoublePixelVeto_Mass55_v1"
                                                                ))

if customize.processId == "Data":
	process.dataRequirements += process.hltHighLevel

#process.p = cms.Path(process.customSequence*process.flashggUntaggedVHHadronicTag*process.tightTagDumper*process.vbfTagDumper)
#process.p = cms.Path(process.dataRequirements*process.customSequence*process.flashggTagMerger*process.flashggVHEtUntaggedTag*process.looseTagDumper*process.tightTagDumper*process.vbfTagDumper*process.thadTagDumper*process.tlepTagDumper*process.etTagDumper*process.hadTagDumper*process.hadDiJetDumper*process.tightUntaggedDumper*process.looseUntaggedDumper*process.etUntaggedTagDumper*process.tagsDumper)
process.p = cms.Path(process.dataRequirements*process.flashggTagSequence*process.VHCSample)

#print process.vhEtTagDumper.src
#process.p = cms.Path(process.flashggTagSequence)

#process.e = cms.EndPath(process.out)

# import flashgg customization
# set default options if needed
customize.setDefault("maxEvents",-1)
customize.setDefault("targetLumi",3.6e+3)
customize.setDefault("puTarget",'2.18e+03,2.4e+04,7e+04,1.98e+05,3.61e+05,6.19e+05,1.29e+06,9e+06,2.33e+07,3.11e+07,4.09e+07,5.77e+07,8.37e+07,1.16e+08,1.51e+08,1.84e+08,2.06e+08,2.11e+08,2.01e+08,1.82e+08,1.56e+08,1.28e+08,9.8e+07,7.05e+07,4.72e+07,2.94e+07,1.71e+07,9.23e+06,4.68e+06,2.24e+06,1.02e+06,4.36e+05,1.78e+05,6.87e+04,2.51e+04,8.62e+03,2.79e+03,851,244,66.2,17.1,4.25,1.04,0.257,0.0658,0.0178,0.00504,0.00146,0.000424,0.000121')

# OLD customize.setDefault("puTarget", '1.435e+05,6.576e+05,8.781e+05,1.304e+06,2.219e+06,5.052e+06,1.643e+07,6.709e+07,1.975e+08,3.527e+08,4.44e+08,4.491e+08,3.792e+08,2.623e+08,1.471e+08,6.79e+07,2.748e+07,1.141e+07,5.675e+06,3.027e+06,1.402e+06,5.119e+05,1.467e+05,3.53e+04,8270,2235,721.3,258.8,97.27,36.87,13.73,4.932,1.692,0.5519,0.1706,0.04994,0.01383,0.003627,0.0008996,0.0002111,4.689e-05,9.854e-06,1.959e-06,3.686e-07,6.562e-08,1.105e-08,1.762e-09,2.615e-10,4.768e-11,0,0,0')

# call the customization
customize(process)
