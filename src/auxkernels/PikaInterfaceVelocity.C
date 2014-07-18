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

#include "PikaInterfaceVelocity.h"

template<>
InputParameters validParams<PikaInterfaceVelocity>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("phase", "Phase-field variable");
  params.addRequiredCoupledVar("chemical_potential", "Chemical potential variable");
  return params;
}

PikaInterfaceVelocity::PikaInterfaceVelocity(const std::string & name, InputParameters parameters) :
    AuxKernel(name, parameters),
    _D_v(getMaterialProperty<Real>("water_vapor_diffusion_coefficient")),
    _grad_phase(coupledGradient("phase")),
    _grad_s(coupledGradient("chemical_potential"))
{
}

PikaInterfaceVelocity::~PikaInterfaceVelocity()
{
}

Real
PikaInterfaceVelocity::computeValue()
{
  RealGradient n = _grad_phase[_qp] / _grad_phase[_qp].size();
  return _D_v[_qp] * n * _grad_s[_qp];
}
