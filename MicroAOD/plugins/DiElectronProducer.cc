#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "flashgg/DataFormats/interface/DiElectronCandidate.h"


using namespace edm;
using namespace std;

namespace flashgg {

    class DiElectronProducer : public EDProducer
    {

    public:
        DiElectronProducer( const ParameterSet & );
    private:
        void produce( Event &, const EventSetup & ) override;
        EDGetTokenT<View<flashgg::Electron> > elecToken_;
        EDGetTokenT<View<reco::Vertex> > vertexToken_;

        double minElPT_;
        double maxElEta_;

    };

    DiElectronProducer::DiElectronProducer( const ParameterSet &iConfig ) :
        elecToken_( consumes<View<flashgg::Electron> >( iConfig.getParameter<InputTag> ( "electronTag" ) ) ),
        vertexToken_( consumes<View<reco::Vertex> >( iConfig.getParameter<InputTag> ( "vertexTag" ) ) )
    {
        minElPT_ = iConfig.getParameter<double>( "minElectronPT" );
        maxElEta_ = iConfig.getParameter<double>( "maxElectronEta" );
        produces<vector<flashgg::DiElectronCandidate> >();
    }

    void DiElectronProducer::produce( Event &evt, const EventSetup & )
    {

        Handle<View<reco::Vertex> > primaryVertices;
        evt.getByToken( vertexToken_, primaryVertices );
        //const PtrVector<reco::Vertex>& pvPointers = primaryVertices->ptrVector();
        edm::Ptr<reco::Vertex> vtx = primaryVertices->ptrAt( 0 ); //pvPointers[0]; //selected vertex 0
        const reco::Vertex myrecovtx = reco::Vertex( *vtx );

        Handle<View<flashgg::Electron> > electrons;
        evt.getByToken( elecToken_, electrons );
        const std::vector<edm::Ptr<flashgg::Electron> > &elecPointers = electrons->ptrs();


        auto_ptr<vector<flashgg::DiElectronCandidate> > diElectronColl( new vector<flashgg::DiElectronCandidate> );
        //    cout << "evt.id().event()= " << evt.id().event() << "\tevt.isRealData()= " << evt.isRealData() << "\telecPointers.size()= " << elecPointers.size() << "\tpvPointers.size()= " << pvPointers.size() << endl;

        for( unsigned int i = 0 ; i < elecPointers.size() ; i++ ) {
            Ptr<flashgg::Electron> elec1 = elecPointers[i];
            double pt1 = elec1->pt();
            double eta1 = elec1->eta();
            if( pt1 < minElPT_ || fabs( eta1 ) > maxElEta_ ) { continue; }
            for( unsigned int j = i + 1 ; j < elecPointers.size() ; j++ ) {
                Ptr<flashgg::Electron> elec2 = elecPointers[j];
                double pt2 = elec2->pt();
                double eta2 = elec2->eta();
                if( pt2 < minElPT_ || fabs( eta2 ) > maxElEta_ ) { continue; }

                if( max( pt1, pt2) < 30 ) { continue; }

                Ptr<flashgg::Electron> LeadElectron = elecPointers[i];
                Ptr<flashgg::Electron> SubLeadElectron = elecPointers[j];
                if( pt2 > pt1 ) {
                    LeadElectron = elecPointers[j];
                    SubLeadElectron = elecPointers[i];
                }

                DiElectronCandidate diEl( LeadElectron, SubLeadElectron );
                int El1_charge = elec1->charge();
                int El2_charge = elec2->charge();

                bool IsOPCharge = false;
                if( El1_charge * El2_charge < 0 ) { IsOPCharge = true; }
                diEl.setIsOSDiElPair( IsOPCharge );

                if (!IsOPCharge)  { continue; }

                //bool leadElIsTight  = LeadElectron->isTightElectron( myrecovtx );
                //bool subleadElIsTight  = SubLeadElectron->isTightElectron( myrecovtx );
                //bool bothTightEl = false;
                //if( leadElIsTight && subleadElIsTight ) { bothTightEl = true; }
                //diEl.setIfBothTightEl( bothTightEl );

                //bool bothGlobalAndPF = false;
                //if( LeadElectron->isPFElectron() && LeadElectron->isGlobalElectron() && SubLeadElectron->isPFElectron() && SubLeadElectron->isGlobalElectron() ) { bothGlobalAndPF = true; }
                //diEl.setIfBothGlobalAndPF( bothGlobalAndPF );

                // store the dielec into the collection
                diElectronColl->push_back( diEl );
            }
            
	    //if(diElectronColl->size() == 0 ) { continue; }
	}
	if ( diElectronColl->size() > 0 ) {
	    evt.put( diElectronColl );
	}

    }
}

typedef flashgg::DiElectronProducer FlashggDiElectronProducer;
DEFINE_FWK_MODULE( FlashggDiElectronProducer );
