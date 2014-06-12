/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef PHASEEVOLUTIONSOURCEMMS_H
#define PHASEEVOLUTIONSOURCEMMS_H
#include "ChemicalPotentialInterface.h"
// MOOSE includes
#include "Kernel.h"

// Forward declarations
class PhaseEvolutionSourceMMS;

template<>
InputParameters validParams<PhaseEvolutionSourceMMS>();

/**
 * A kernel for adding forcing function for the MMS tests of the heat
 * transport equation, Eq. (34)
 */
class PhaseEvolutionSourceMMS : 
				public Kernel, public ChemicalPotentialInterface
{
public:

  /**
   * Class constructor
   * @param name
   * @param parameters
   */
  PhaseEvolutionSourceMMS(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();

private:
   MaterialProperty<Real> & _tau;
  const MaterialProperty<Real> & _w;
  const MaterialProperty<Real> & _lambda;
  const MaterialProperty<Real> & _rho_i;
  const MaterialProperty<Real> & _rho_a;
  const MaterialProperty<Real> & _R_da;
  const MaterialProperty<Real> & _R_v;
  const MaterialProperty<Real> & _P_a;
<<<<<<< HEAD
  const bool  & _use_potential_transition;
=======
>>>>>>> 3fbfd84f8fad91aea639a1611852e440ccd7de63

};

#endif //PHASEEVOLUTIONSOURCEMMS_H
