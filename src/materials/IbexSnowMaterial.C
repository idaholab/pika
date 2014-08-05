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

#include "IbexSnowMaterial.h"

template<>
InputParameters validParams<IbexSnowMaterial>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredCoupledVar("temperature", "The snow temperature variable to couple");
  return params;
}

IbexSnowMaterial::IbexSnowMaterial(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    _temperature(coupledValue("temperature")),
    _input_density(getParam<Real>("snow_density")),
    _density(declareProperty<Real>("density")),
    _conductivity(declareProperty<Real>("conductivity")),
    _specific_heat(declareProperty<Real>("specific_heat"))
{
}

void
IbexSnowMaterial::computeQpProperties()
{
  _density[_qp] = _input_density;
  _conductivity[_qp] = 0.021 + 2.5 * std::pow(_density[_qp] / 1000, 2);
  _specific_heat[_qp] = 1000 * (2.115 + 0.00779 * _temperature[_qp]);
}
