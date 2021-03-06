#include "KGVolume.hh"

namespace KGeoBag
{
    KGVolume::KGVolume() :
            fInitialized( false ),
            fBoundaries()
    {
    }
    KGVolume::KGVolume( const KGVolume& aCopy ) :
            KTagged(),
            fInitialized( aCopy.fInitialized ),
            fBoundaries( aCopy.fBoundaries )
    {
    }
    KGVolume::~KGVolume()
    {
    }

    const KGVolume::BoundaryContainer& KGVolume::Boundaries() const
    {
        Check();
        return fBoundaries;
    }

    void KGVolume::Accept( KGVisitor* aVisitor )
    {
        Check();
        VolumeAccept( aVisitor );
    }

    bool KGVolume::Outside( const KThreeVector& aPoint ) const
    {
        Check();
        return VolumeOutside( aPoint );
    }
    KThreeVector KGVolume::Point( const KThreeVector& aPoint ) const
    {
        Check();
        return VolumePoint( aPoint );
    }
    KThreeVector KGVolume::Normal( const KThreeVector& aNormal ) const
    {
        Check();
        return VolumeNormal( aNormal );
    }

    void KGVolume::Check() const
    {
        if( fInitialized == false )
        {
            VolumeInitialize( fBoundaries );
            fInitialized = true;
        }
        return;
    }

    void KGVolume::VolumeAccept(KGVisitor* aVisitor) {
		KGVolume::Visitor* tVolumeVisitor = dynamic_cast< KGVolume::Visitor* >(aVisitor);
		if(tVolumeVisitor != NULL) {
			tVolumeVisitor->VisitVolume(this);
		}
    }
}
