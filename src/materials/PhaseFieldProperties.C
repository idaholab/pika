#include "PhaseFieldProperties.h"

template<>
InputParameters validParams<PhaseFieldProperties>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredCoupledVar("temperature", "The temperature variable to couple");

  params.addParam<Real>("gamma", 1.09e-1, "Interface free energy [J/m^2]");

  params.addParam<Real>("a", 3.19e-10, "Mean inter-molecular spacing in ice [m]");

  params.addParam<Real>("k", 1.3806488e-23, "Boltzmann constant [J/k]");

  return params;
}


PhaseFieldProperties::PhaseFieldProperties(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    _gamma(getParam<Real>("gamma")),
    _a(getParam<Real>("a")),
    _k(getParam<Real>("k")),
    _temperature(coupledValue("temperature")),
    _capillary_length(declareProperty<Real>("capillary_length"))
{
}

void
PhaseFieldProperties::computeQpProperties()
{
  _capillary_length[_qp] = (_gamma * std::pow(_a, 3) ) / (_k * _temperature[_qp]);
}
