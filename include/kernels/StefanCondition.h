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

#ifndef STEFANCONDITION_H
#define STEFANCONDITION_H

// MOOSE includes
#include "Kernel.h"

// Forward declerations
class StefanCondition;

template<>
InputParameters validParams<StefanCondition>();

/**
 *
 */
class StefanCondition : public Kernel
{
public:

  /**
   * Class constructor
   * @param name
   * @param parameters
   */
  StefanCondition(const std::string & name, InputParameters parameters);

  /**
   * Class destructor
   */
  virtual ~StefanCondition();

protected:

  /**
   *
   */
  virtual Real computeQpResidual();

private:

  VariableValue & _phase;
  VariableGradient & _grad_phase;
  VariableGradient & _grad_potential;
  const MaterialProperty<Real> _L_sg;
  const MaterialProperty<Real> _D_v;
  const MaterialProperty<Real> _kappa_a;
  const MaterialProperty<Real> _kappa_i;

};

#endif //STEFANCONDITION_H
