#include <memory>
#include <vector>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "DataFormats/Common/interface/PtrVector.h"

#include "flashgg/DataFormats/interface/DiElectronCandidate.h"

#include "TTree.h"
#include "Math/VectorUtil.h"

using namespace std;
using namespace edm;

class flashggDiElectron : public edm::EDAnalyzer
{
public:
    explicit flashggDiElectron( const edm::ParameterSet & );
    ~flashggDiElectron();

    static void fillDescriptions( edm::ConfigurationDescriptions &descriptions );


private:

    edm::Service<TFileService> fs_;

    virtual void beginJob() override;
    virtual void analyze( const edm::Event &, const edm::EventSetup & ) override;
    virtual void endJob() override;

    EDGetTokenT<View<pat::Electron> >  elecToken_;
    EDGetTokenT<View<reco::Vertex> >   vertexToken_;
    EDGetTokenT<View<pat::PackedCandidate> >  pfcandidateToken_;
    EDGetTokenT<View<reco::GenParticle> > genParticleToken_;

    TTree *electronTree;

    vector<Float_t> pt_;
    vector<Float_t> eta_;
    vector<Float_t> phi_;
    vector<Float_t> energy_;
    vector<bool> isGenMatched_;
};

flashggDiElectron::flashggDiElectron( const ParameterSet &iConfig ) :
    elecToken_( consumes<View<pat::Electron> >( iConfig.getUntrackedParameter<InputTag> ( "electronTag", InputTag( "slimmedElectrons") ) ) ),
    vertexToken_( consumes<View<reco::Vertex> >( iConfig.getUntrackedParameter<InputTag> ( "vertexTag", InputTag( "offlineSlimmedPrimaryVertices" ) ) ) ),
    pfcandidateToken_( consumes<View<pat::PackedCandidate> >( iConfig.getUntrackedParameter<InputTag> ( "PFCandidatesTag", InputTag("packedPFCandidates") ) ) ),
    genParticleToken_( consumes<View<reco::GenParticle> >( iConfig.getUntrackedParameter<InputTag> ("GenParticleTag", InputTag("prunedGenParticles") )) )
{

}

flashggDiElectron::~flashggDiElectron()
{

}



void
flashggDiElectron::analyze( const edm::Event &iEvent, const edm::EventSetup &iSetup )
{

    Handle<View<pat::Electron> > electrons;
    iEvent.getByToken( elecToken_, electrons );

    Handle<View<pat::PackedCandidate> > pfcandidates;
    iEvent.getByToken( pfcandidateToken_, pfcandidates );

    Handle<View<reco::GenParticle> > genParticles;
    iEvent.getByToken( genParticleToken_, genParticles );

    pt_.clear();
    eta_.clear();
    phi_.clear();
    energy_.clear();
    isGenMatched_.clear();
    
    for( size_t ielec = 0; ielec < electrons->size(); ielec++) {
        
        Ptr<pat::Electron> elecPtr = electrons->ptrAt( ielec );

        pt_.push_back( elecPtr->pt() );
        eta_.push_back( elecPtr->eta() );
        phi_.push_back( elecPtr->phi() );
        energy_.push_back( elecPtr->energy() );
        bool isGenMatched = false;

        for( unsigned int genLoop = 0; genLoop < genParticles->size(); genLoop++) {
            Ptr<reco::GenParticle> genPtr = genParticles->ptrAt(genLoop);
            if( abs(genPtr->pdgId()) != 11 || genPtr->status() != 1) { continue; }
            double dR = ROOT::Math::VectorUtil::DeltaR( elecPtr->p4(), genPtr->p4() );
            if( dR < 0.1) {
                isGenMatched = true;
                break;
            }
        }

        isGenMatched_.push_back( isGenMatched );
    }

    electronTree->Fill();
}

void
flashggDiElectron::beginJob()
{
    electronTree = fs_->make<TTree>("electronTree", "electronData");
 
    electronTree->Branch("pt", &pt_);
    electronTree->Branch("eta", &eta_);
    electronTree->Branch("phi", &phi_);
    electronTree->Branch("energy", &energy_);
    electronTree->Branch("isGenMatched", &isGenMatched_);

}

void
flashggDiElectron::endJob()
{
}

void
flashggDiElectron::fillDescriptions( edm::ConfigurationDescriptions &descriptions )
{
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault( desc );
}


DEFINE_FWK_MODULE( flashggDiElectron );
