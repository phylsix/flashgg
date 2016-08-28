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
#include "flashgg/DataFormats/interface/Electron.h"

#include "TTree.h"
#include "Math/VectorUtil.h"

using namespace std;
using namespace edm;

namespace flashgg {
class DiElectronAnalyzer : public edm::EDAnalyzer
{
public:
    explicit DiElectronAnalyzer( const edm::ParameterSet & );
    ~DiElectronAnalyzer();

    static void fillDescriptions( edm::ConfigurationDescriptions &descriptions );


private:

    edm::Service<TFileService> fs_;

    virtual void beginJob() override;
    virtual void analyze( const edm::Event &, const edm::EventSetup & ) override;
    virtual void endJob() override;

    //EDGetTokenT<View<flashgg::Electron> >  elecToken_;
    //EDGetTokenT<View<reco::Vertex> >   vertexToken_;
    EDGetTokenT<View<flashgg::DiElectronCandidate> > diElecToken_;
    EDGetTokenT<View<pat::PackedCandidate> >  pfcandidateToken_;
    EDGetTokenT<View<reco::GenParticle> > genParticleToken_;

    TTree *diElectronTree;

    Float_t pt_0_;
    Float_t eta_0_;
    Float_t phi_0_;
    Float_t energy_0_;
   
    Float_t pt_1_;
    Float_t eta_1_;
    Float_t phi_1_;
    Float_t energy_1_;
   
    Float_t invM_;
};

DiElectronAnalyzer::DiElectronAnalyzer( const ParameterSet &iConfig ) :
    //elecToken_( consumes<View<pat::Electron> >( iConfig.getUntrackedParameter<InputTag> ( "electronTag", InputTag( "slimmedElectrons") ) ) ),
    //vertexToken_( consumes<View<reco::Vertex> >( iConfig.getUntrackedParameter<InputTag> ( "vertexTag", InputTag( "offlineSlimmedPrimaryVertices" ) ) ) ),
    diElecToken_( consumes<View<flashgg::DiElectronCandidate> >(iConfig.getUntrackedParameter<InputTag> ("dielectronTag", InputTag("diElectronProduce")))),
    pfcandidateToken_( consumes<View<pat::PackedCandidate> >( iConfig.getUntrackedParameter<InputTag> ( "PFCandidatesTag", InputTag("packedPFCandidates") ) ) ),
    genParticleToken_( consumes<View<reco::GenParticle> >( iConfig.getUntrackedParameter<InputTag> ("GenParticleTag", InputTag("prunedGenParticles") )) )
{

}

DiElectronAnalyzer::~DiElectronAnalyzer()
{

}



void
DiElectronAnalyzer::analyze( const edm::Event &iEvent, const edm::EventSetup &iSetup )
{

    //Handle<View<flashgg::Electron> > electrons;
    //iEvent.getByToken( elecToken_, electrons );

    //Handle<View<flashgg::PackedCandidate> > pfcandidates;
    //iEvent.getByToken( pfcandidateToken_, pfcandidates );

    Handle<View<reco::GenParticle> > genParticles;
    iEvent.getByToken( genParticleToken_, genParticles );

    Handle<View<flashgg::DiElectronCandidate> > dielectrons;
    iEvent.getByToken( diElecToken_, dielectrons );

    pt_0_ = 0;;
    eta_0_ = 0;;
    phi_0_ = 0;;
    energy_0_ = 0;;
    
    pt_1_ = 0;;
    eta_1_ = 0;;
    phi_1_ = 0;;
    energy_1_ = 0;;
    
    invM_ = 0;;
   
    cout << "dielectron size " << dielectrons->size() << endl; 
	
    for( size_t iDiEl = 0; iDiEl < dielectrons->size(); iDiEl++) {
	Ptr<flashgg::DiElectronCandidate> dielecPtr = dielectrons->ptrAt( iDiEl );
	
	const flashgg::Electron* elecLd = dielecPtr->leadingElectron();
	const flashgg::Electron* elecSb = dielecPtr->subleadingElectron();
	
	bool bothGenMatched = false;

	if(! iEvent.isRealData() ) {
	for( unsigned int igen = 0; igen < genParticles->size(); igen++) {
            Ptr<reco::GenParticle> genPtr = genParticles->ptrAt(igen);
            if( abs(genPtr->pdgId()) != 11 || genPtr->status() != 1) { continue; }
            double dR_0= ROOT::Math::VectorUtil::DeltaR( elecLd->p4(), genPtr->p4() );
            double dR_1= ROOT::Math::VectorUtil::DeltaR( elecSb->p4(), genPtr->p4() );

	    if( dR_0 < 0.1 && dR_1 < 0.1) {
                bothGenMatched = true;
                break;
            }
	}
	}
	
	if( bothGenMatched ) { cout<<"one matched couple found"<<endl; }
        	
	pt_0_ = elecLd->pt();
	eta_0_ = elecLd->eta();
	phi_0_ = elecLd->phi();
	energy_0_ = elecLd->energy();

	pt_1_ = elecSb->pt();
	eta_1_ = elecSb->eta();
	phi_1_ = elecSb->phi();
	energy_1_ = elecSb->energy();

	Float_t zMass = ( elecLd->p4() + elecSb->p4() ).mass();
	invM_ = zMass;
    }
    //cout<< "pt_0 "<< pt_0_ <<endl;
    diElectronTree->Fill();
}

void
DiElectronAnalyzer::beginJob()
{
    diElectronTree = fs_->make<TTree>("diElectronTree", "diElectronData");
 
    diElectronTree->Branch("pt_0", &pt_0_, "pt_0/F");
    diElectronTree->Branch("eta_0", &eta_0_, "eta_0/F");
    diElectronTree->Branch("phi_0", &phi_0_, "phi_0/F");
    diElectronTree->Branch("energy_0", &energy_0_, "energy_0/F");

    diElectronTree->Branch("pt_1", &pt_1_, "pt_1/F");
    diElectronTree->Branch("eta_1", &eta_1_, "eta_1/F");
    diElectronTree->Branch("phi_1", &phi_1_, "phi_1/F");
    diElectronTree->Branch("energy_1", &energy_1_, "energy_1/F");

    diElectronTree->Branch("invM", &invM_, "invM/F");
}

void
DiElectronAnalyzer::endJob()
{
}

void
DiElectronAnalyzer::fillDescriptions( edm::ConfigurationDescriptions &descriptions )
{
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault( desc );
}

}

typedef flashgg::DiElectronAnalyzer FlashggDiElectronAnalyzer;
DEFINE_FWK_MODULE( FlashggDiElectronAnalyzer );
