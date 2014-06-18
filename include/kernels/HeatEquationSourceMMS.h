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

#ifndef HEATEQUATIONSOURCEMMS_H
#define HEATEQUATIONSOURCEMMS_H

// MOOSE includes
#include "Kernel.h"

// Forward declarations
class HeatEquationSourceMMS;

template<>
InputParameters validParams<HeatEquationSourceMMS>();

/**
 * A kernel for adding forcing function for the MMS tests of the heat
 * transport equation, Eq. (34)
 */
class HeatEquationSourceMMS : public Kernel
{
public:

  /**
   * Class constructor
   * @param name
   * @param parameters
   */
  HeatEquationSourceMMS(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();

private:
  const MaterialProperty<Real> & _k;
  const MaterialProperty<Real> & _c;
  const MaterialProperty<Real> & _L_sg;
  const VariableValue & _phi;
  bool _use_dphi_dt;

};

#endif //HEATEQUATIONSOURCEMMS_H
