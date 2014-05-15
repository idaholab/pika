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

#include "StefanCondition.h"

template<>
InputParameters validParams<StefanCondition>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("phi", "The phase-field variable to couple");
  params.addRequiredCoupledVar("chemical_potential", "The chemical potential variable to couple");
  params.addParam<std::string>("latent_heat_name", "latent_heat", "Material property name containing the latent heat of sublimation");
  params.addParam<std::string>("diffusion_coefficient_name", "diffusion_coefficient", "Material property name containing the diffusion coefficient of water vapor");
  params.addParam<std::string>("conductivity_air_name", "conductivity_air", "Material property name containing the thermal conductivity of air");
  params.addParam<std::string>("conductivity_ice_name", "conductivity_ice", "Material property name containing the thermal conductivity of ice");
  return params;
}

StefanCondition::StefanCondition(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),
    _phase(coupledValue("phi")),
    _grad_phase(coupledGradient("phi")),
    _grad_potential(coupledGradient("chemical_potential")),
    _L_sg(getMaterialProperty<Real>(getParam<std::string>("latent_heat_name"))),
    _D_v(getMaterialProperty<Real>(getParam<std::string>("diffusion_coefficient_name"))),
    _kappa_a(getMaterialProperty<Real>(getParam<std::string>("conductivity_air_name"))),
    _kappa_i(getMaterialProperty<Real>(getParam<std::string>("conductivity_ice_name")))
{
}

StefanCondition::~StefanCondition()
{
}

Real
StefanCondition::computeQpResidual()
{
  if (_phase[_qp] < 1 && _phase[_qp] > -1)
  {
    RealGradient n = _grad_phase[_qp] / _grad_phase[_qp].size();

    return (_kappa_i[_qp] * n * _grad_u[_qp]) * _test[_i][_qp];

    //  - _kappa_a[_qp] * n * _grad_u[_qp] * _test[_i][_qp]
    //  - _L_sg[_qp] * _D_v[_qp] * n * _grad_potential[_qp] * _test[_i][_qp];
  }

  else
    return 0;

}
