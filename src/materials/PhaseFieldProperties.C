#include "PhaseFieldProperties.h"

template<>
InputParameters validParams<PhaseFieldProperties>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredCoupledVar("temperature", "The temperature variable to couple");

  params.addParam<Real>("gamma", 1.09e-1, "Interface free energy [J/m^2]");

  params.addParam<Real>("a", 3.19e-10, "Mean inter-molecular spacing in ice [m]");

  params.addParam<Real>("k", 1.3806488e-23, "Boltzmann constant [J/k]");

  params.addParam<Real>("alpha", 1e-2, "Condensation coefficient [unitless]");

  params.addParam<Real>("m", 2.9900332e-26, "Mass of water molecule [kg]");

  params.addParam<Real>("rho_vs", 1e-2, "Equilibrium water vapor concentration at saturation [kg/m^3]");

  params.addParam<Real>("w", 8e-6, "Interface thickness [m]");


  return params;
}


PhaseFieldProperties::PhaseFieldProperties(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    _gamma(getParam<Real>("gamma")),
    _a(getParam<Real>("a")),
    _k(getParam<Real>("k")),
    _alpha(getParam<Real>("alpha")),
    _m(getParam<Real>("m")),
    _rho_vs(getParam<Real>("rho_vs")),
    _w(getParam<Real>("w")),
    _a1(5/8*std::sqrt(2)),
    _temperature(coupledValue("temperature")),
    _density_ice(getMaterialProperty<Real>("density_ice")),
    _interface_velocity(declareProperty<Real>("interface_velocity")),
    _capillary_length(declareProperty<Real>("capillary_length")),
    _beta(declareProperty<Real>("beta")),
    _lamda(declareProperty<Real>("lamda")),
    _tau(declareProperty<Real>("tau"))

{
}

void
PhaseFieldProperties::computeQpProperties()
{
  /// @todo{This needs to be computed}
  _interface_velocity[_qp] = 1e-9; // [m/s]

  _capillary_length[_qp] = (_gamma * std::pow(_a, 3) ) / (_k * _temperature[_qp]);

  _beta[_qp] = (1/_alpha) * _density_ice[_qp] / _rho_vs * std::sqrt((2*libMesh::pi*_m) / (_k * _temperature[_qp]));

  _lambda[_qp] = (_a1 * _w *_density_ice[_qp]) / (_capillary_length[_qp] * _rho_vs);

  _tau[_qp] = (_beta[_qp] * _rho_vs * _w * _lambda[_qp]) / (_density_ice[_qp] * _a1);

}
