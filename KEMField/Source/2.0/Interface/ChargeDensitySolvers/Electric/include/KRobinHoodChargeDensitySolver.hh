/*
 * KRobinHoodChargeDensitySolver.hh
 *
 *  Created on: 29 Jul 2015
 *      Author: wolfgang
 */

#ifndef KEMFIELD_SOURCE_2_0_CHARGEDENSITYSOLVERS_ELECTRIC_INCLUDE_KROBINHOODCHARGEDENSITYSOLVER_HH_
#define KEMFIELD_SOURCE_2_0_CHARGEDENSITYSOLVERS_ELECTRIC_INCLUDE_KROBINHOODCHARGEDENSITYSOLVER_HH_

#include "KChargeDensitySolver.hh"
#include "KElectrostaticBoundaryIntegratorPolicy.hh"

#include "KEMCout.hh"

namespace KEMField {

class KRobinHoodChargeDensitySolver : public KChargeDensitySolver {
public:
	KRobinHoodChargeDensitySolver();
	virtual ~KRobinHoodChargeDensitySolver();

	void SetIntegratorPolicy(const KEBIPolicy& policy)
	{
		fIntegratorPolicy = policy;
	}
	void SetTolerance( double d )
	{
		fTolerance = d;
	}
	void SetCheckSubInterval( unsigned int i )
	{
		fCheckSubInterval = i;
	}
	void SetDisplayInterval( unsigned int i )
	{
		fDisplayInterval = i;
	}
	void SetWriteInterval( unsigned int i )
	{
		fWriteInterval = i;
	}
	void SetPlotInterval( unsigned int i )
	{
		fPlotInterval = i;
	}

	void CacheMatrixElements( bool choice )
	{
		fCacheMatrixElements = choice;
	}

	void UseOpenCL( bool choice )
	{
		if( choice == true )
		{
#ifdef KEMFIELD_USE_OPENCL
fUseOpenCL = choice;
return;
#endif
KEMField::cout << "WARNING: cannot use OpenCl in robin hood without"
		" KEMField being built with OpenCl, using defaults." << endl;
		}
		fUseOpenCL = false;
		return;
	}
	void UseVTK( bool choice )
	{
		if( choice == true )
		{
#ifdef KEMFIELD_USE_VTK
fUseVTK = choice;
return;
#endif
KEMField::cout << "WARNING: cannot use vtk in robin hood without"
		" KEMField being built with vtk, using defaults." << endl;
		}
		fUseVTK = false;
		return;
	}

private:
	void InitializeCore( KSurfaceContainer& container );

	KEBIPolicy fIntegratorPolicy;
	double fTolerance;
	unsigned int fCheckSubInterval;
	unsigned int fDisplayInterval;
	unsigned int fWriteInterval;
	unsigned int fPlotInterval;
	bool fCacheMatrixElements;
	bool fUseOpenCL;
	bool fUseVTK;
};

} //KEMField

#endif /* KEMFIELD_SOURCE_2_0_CHARGEDENSITYSOLVERS_ELECTRIC_INCLUDE_KROBINHOODCHARGEDENSITYSOLVER_HH_ */
