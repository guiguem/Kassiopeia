#ifndef Kassiopeia_KSIntScatteringBuilder_h_
#define Kassiopeia_KSIntScatteringBuilder_h_

#include "KComplexElement.hh"
#include "KSIntScattering.h"
#include "KToolbox.h"

using namespace Kassiopeia;
namespace katrin
{

    class KSIntCalculatorSet
    {
        public:
            KSIntCalculatorSet();
            virtual ~KSIntCalculatorSet();

        public:
            virtual void AddCalculator( KSIntCalculator* aCalculator ) = 0;
            virtual void ReleaseCalculators( KSIntScattering* aScattering ) = 0;
    };

    typedef KComplexElement< KSIntScattering > KSIntScatteringBuilder;

    template< >
    inline bool KSIntScatteringBuilder::AddAttribute( KContainer* aContainer )
    {
        if( aContainer->GetName() == "name" )
        {
            aContainer->CopyTo( fObject, &KNamed::SetName );
            return true;
        }
        if( aContainer->GetName() == "split" )
        {
            aContainer->CopyTo( fObject, &KSIntScattering::SetSplit );
            return true;
        }
        if( aContainer->GetName() == "density" )
        {
            KSIntDensity* tDensityCalculator = KToolbox::GetInstance().Get< KSIntDensity >( aContainer->AsReference< std::string >() );
            fObject->SetDensity( tDensityCalculator->Clone() );
            return true;
        }
        if( aContainer->GetName() == "calculator" )
        {
            KSIntCalculator* tCalculator = KToolbox::GetInstance().Get< KSIntCalculator >( aContainer->AsReference< std::string >() );
            fObject->AddCalculator( tCalculator );
            return true;
        }
        if( aContainer->GetName() == "calculators" )
        {
            std::vector< KSIntCalculator* > aCalculatorVector = KToolbox::GetInstance().GetAll< KSIntCalculator >( aContainer->AsReference< std::string >() );
            std::vector< KSIntCalculator* >::iterator tIt;
            for( tIt = aCalculatorVector.begin(); tIt != aCalculatorVector.end(); tIt++ )
            {
                fObject->AddCalculator( (*tIt) );
            }
            return true;
        }
        if( aContainer->GetName() == "enhancement" )
        {
            aContainer->CopyTo( fObject, &KSIntScattering::SetEnhancement );
            return true;
        }
        return false;
    }

    template< >
    inline bool KSIntScatteringBuilder::AddElement( KContainer* aContainer )
    {
        if( aContainer->Is< KSIntDensity >() == true )
        {
            aContainer->ReleaseTo( fObject, &KSIntScattering::SetDensity );
            return true;
        }
        if( aContainer->Is< KSIntCalculator >() == true )
        {
            aContainer->ReleaseTo( fObject, &KSIntScattering::AddCalculator );
            return true;
        }
        if( aContainer->Is< KSIntCalculatorSet >() == true )
        {
            KSIntCalculatorSet* tSet = NULL;
            aContainer->ReleaseTo( tSet );
            tSet->ReleaseCalculators( fObject );
            delete tSet;
            return true;
        }
        return false;
    }

}

#endif
