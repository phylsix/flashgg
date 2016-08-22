#include "flashgg/DataFormats/interface/DiElectronCandidate.h"
#include "CommonTools/CandUtils/interface/AddFourMomenta.h"


using namespace flashgg;

DiElectronCandidate::DiElectronCandidate() {}

DiElectronCandidate::~DiElectronCandidate() {}

DiElectronCandidate::DiElectronCandidate( edm::Ptr<pat::Electron> elec1, edm::Ptr<pat::Electron> elec2 )
{
    addDaughter( *elec1 );
    addDaughter( *elec2 );

    // Adding momenta
    // Needs its own object - but why?
    // Copied from example
    AddFourMomenta addP4;
    addP4.set( *this );
}

DiElectronCandidate::DiElectronCandidate( const pat::Electron &elec1, const pat::Electron &elec2 )
{
    addDaughter( elec1 );
    addDaughter( elec2 );

    // Adding momenta
    // Needs its own object - but why?
    // Copied from example
    AddFourMomenta addP4;
    addP4.set( *this );
}

const pat::Electron *DiElectronCandidate::leadingElectron() const
{
    if( daughter( 0 )->pt() > daughter( 1 )->pt() ) {
        return dynamic_cast<const pat::Electron *>( daughter( 0 ) );
    } else {
        return dynamic_cast<const pat::Electron *>( daughter( 1 ) );
    }
}

const pat::Electron *DiElectronCandidate::subleadingElectron() const
{
    if( daughter( 0 )->pt() > daughter( 1 )->pt() ) {
        return dynamic_cast<const pat::Electron *>( daughter( 1 ) );
    } else {
        return dynamic_cast<const pat::Electron *>( daughter( 0 ) );
    }
}

