#ifndef Kassiopeia_KSTrajTrajectoryExactTrapped_h_
#define Kassiopeia_KSTrajTrajectoryExactTrapped_h_

#include "KSTrajectory.h"
#include "KSTrajExactTrappedTypes.h"

#include "KSList.h"

#include "KGBall.hh"
#include "KGBallSupportSet.hh"

namespace Kassiopeia
{

    class KSTrajTrajectoryExactTrapped :
        public KSComponentTemplate< KSTrajTrajectoryExactTrapped, KSTrajectory >,
        public KSTrajExactTrappedDifferentiator
    {
        public:
            KSTrajTrajectoryExactTrapped();
            KSTrajTrajectoryExactTrapped( const KSTrajTrajectoryExactTrapped& aCopy );
            KSTrajTrajectoryExactTrapped* Clone() const;
            virtual ~KSTrajTrajectoryExactTrapped();

        public:
            void SetIntegrator( KSTrajExactTrappedIntegrator* anIntegrator );
            void ClearIntegrator( KSTrajExactTrappedIntegrator* anIntegrator );

            void SetInterpolator( KSTrajExactTrappedInterpolator* anInterpolator );
            void ClearInterpolator( KSTrajExactTrappedInterpolator* anInterpolator );

            void AddTerm( KSTrajExactTrappedDifferentiator* aTerm );
            void RemoveTerm( KSTrajExactTrappedDifferentiator* aTerm );

            void AddControl( KSTrajExactTrappedControl* aControl );
            void RemoveControl( KSTrajExactTrappedControl* aControlSize );

            void SetAttemptLimit(unsigned int n)
            {
                if(n > 1 ){fMaxAttempts = n;}
                else{fMaxAttempts = 1;};
            }

            //**********
            //trajectory
            //**********

            void SetPiecewiseTolerance(double ptol){fPiecewiseTolerance = ptol;};
            double GetPiecewiseTolerance() const {return fPiecewiseTolerance;};

            void SetMaxNumberOfSegments(double n_max){fNMaxSegments = n_max; if(fNMaxSegments < 1 ){fNMaxSegments = 1;};};
            unsigned int GetMaxNumberOfSegments() const {return fNMaxSegments;};

        public:

            void Reset();
            void CalculateTrajectory( const KSParticle& anInitialParticle, KSParticle& aFinalParticle, KThreeVector& aCenter, double& aRadius, double& aTimeStep );
            void ExecuteTrajectory( const double& aTimeStep, KSParticle& anIntermediateParticle ) const;
            void GetPiecewiseLinearApproximation(const KSParticle& anInitialParticle, const KSParticle& /*aFinalParticle*/, std::vector< KSParticle >* intermediateParticleStates) const;

            //********************
            //ExactTrapped term interface
            //********************

        public:
            virtual void Differentiate(double aTime, const KSTrajExactTrappedParticle& aValue, KSTrajExactTrappedDerivative& aDerivative ) const;

        private:

            KSTrajExactTrappedParticle fInitialParticle;
            mutable KSTrajExactTrappedParticle fIntermediateParticle;
            mutable KSTrajExactTrappedParticle fFinalParticle;
            mutable KSTrajExactTrappedError fError;

            KSTrajExactTrappedIntegrator* fIntegrator;
            KSTrajExactTrappedInterpolator* fInterpolator;
            KSList< KSTrajExactTrappedDifferentiator > fTerms;
            KSList< KSTrajExactTrappedControl > fControls;

            //piecewise linear approximation
            double fPiecewiseTolerance;
            unsigned int fNMaxSegments;
            mutable KGeoBag::KGBallSupportSet<3> fBallSupport;
            mutable std::vector<KSTrajExactTrappedParticle> fIntermediateParticleStates;

            unsigned int fMaxAttempts;

    };

}

#endif
