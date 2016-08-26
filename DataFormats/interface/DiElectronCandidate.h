#ifndef FLASHgg_DiElectronCandidate_h
#define FLASHgg_DiElectronCandidate_h

#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

#include "flashgg/DataFormats/interface/Electron.h"

namespace flashgg {
    class DiElectronCandidate : public reco::CompositeCandidate
    {
    public:
        DiElectronCandidate();
        DiElectronCandidate( edm::Ptr<flashgg::Electron>, edm::Ptr<flashgg::Electron> );
        DiElectronCandidate( const flashgg::Electron &, const flashgg::Electron & );
        ~DiElectronCandidate();

        const flashgg::Electron *leadingElectron() const;
        const flashgg::Electron *subleadingElectron() const;

        bool IsOSDiElPair() const { return IsOSDiElPair_; }
        void setIsOSDiElPair( bool val ) { IsOSDiElPair_ = val;}

        bool IfBothTightEl() const { return IfBothTightEl_; }
        void setIfBothTightEl( bool val ) { IfBothTightEl_  = val;}

        bool IfBothGlobalAndPF() const { return IfBothGlobalAndPF_; }
        void setIfBothGlobalAndPF( bool val ) { IfBothGlobalAndPF_  = val;}

    private:

        bool IsOSDiElPair_;
        bool IfBothTightEl_;
        bool IfBothGlobalAndPF_;

    };


}


#endif


