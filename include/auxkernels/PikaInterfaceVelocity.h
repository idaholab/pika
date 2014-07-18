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

#ifndef PIKAINTERFACEVELOCITY_H
#define PIKAINTERFACEVELOCITY_H

// MOOSE includes
#include "AuxKernel.h"

// Forward declarations
class PikaInterfaceVelocity;

template<>
InputParameters validParams<PikaInterfaceVelocity>();

/**
 *
 */
class PikaInterfaceVelocity :
  public AuxKernel
{
public:

  /**
   * Class constructor
   * @param name
   */
  PikaInterfaceVelocity(const std::string & name, InputParameters parameters);

  /**
   * Class destructor
   */
  virtual ~PikaInterfaceVelocity();

protected:

  /**
   *
   */
  virtual Real computeValue();

private:
  MaterialProperty<Real> & _D_v;
  VariableGradient & _grad_phase;
  VariableGradient & _grad_s;

};

#endif //PIKAINTERFACEVELOCITY_H
