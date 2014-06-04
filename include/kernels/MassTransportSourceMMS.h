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

#ifndef MASSTRANSPORTSOURCEMMS_H
#define MASSTRANSPORTSOURCEMMS_H

// MOOSE includes
#include "Kernel.h"

// Forward declarations
class MassTransportSourceMMS;

template<>
InputParameters validParams<MassTransportSourceMMS>();

/**
 *
 */
class MassTransportSourceMMS : public Kernel
{
public:

  /**
   * Class constructor
   * @param name
   * @param parameters
   */
  MassTransportSourceMMS(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();

private:
  const MaterialProperty<Real> & _diffusion_coefficient;

};

#endif //MASSTRANSPORTSOURCEMMS_H
