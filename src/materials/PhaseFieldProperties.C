#include "PhaseFieldProperties.h"

template<>
InputParameters validParams<PhaseFieldProperties>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredCoupledVar("temperature", "The temperature variable to couple");
  params.addRequiredCoupledVar("phi", "The phase-field variable to couple");

  params.addParam<Real>("gamma", 1.09e-1, "Interface free energy [J/m^2]");

  params.addParam<Real>("a", 3.19e-10, "Mean inter-molecular spacing in ice [m]");

  params.addParam<Real>("k", 1.3806488e-23, "Boltzmann constant [J/k]");

  params.addParam<Real>("alpha", 1e-2, "Condensation coefficient [unitless]");

  params.addParam<Real>("m", 2.9900332e-26, "Mass of water molecule [kg]");

  params.addParam<Real>("w", 8e-6, "Interface thickness [m]");

  return params;
}


PhaseFieldProperties::PhaseFieldProperties(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    _temperature(coupledValue("temperature")),
    _phi(coupledValue("phi")),
    _gamma(getParam<Real>("gamma")),
    _a(getParam<Real>("a")),
    _k(getParam<Real>("k")),
    _alpha(getParam<Real>("alpha")),
    _m(getParam<Real>("m")),
    _w(getParam<Real>("w")),
    _a1(5/8*std::sqrt(2)),
    _interface_velocity(declareProperty<Real>("interface_velocity")),
    _capillary_length(declareProperty<Real>("capillary_length")),
    _beta(declareProperty<Real>("beta")),
    _lambda(declareProperty<Real>("lamda")),
    _tau(declareProperty<Real>("tau")),
    _conductivity(declareProperty<Real>("conductivity")),
    _heat_capacity(declareProperty<Real>("head_capacity")),
    _diffusion_coefficient(declareProperty<Real>("diffusion_coefficient")),
    _density(declareProperty<Real>("density"))

{
}

void
PhaseFieldProperties::computeQpProperties()
{
  MaterialProperty<Real> & rho_vs = getMaterialProperty<Real>("water_vapor_mass_density_saturation");

  MaterialProperty<Real> & ki = getMaterialProperty<Real>("conductivity_ice");
  MaterialProperty<Real> & ka = getMaterialProperty<Real>("conductivity_air");

  MaterialProperty<Real> & ci = getMaterialProperty<Real>("heat_capacity_ice");
  MaterialProperty<Real> & ca = getMaterialProperty<Real>("heat_capacity_air");

  MaterialProperty<Real> & dv = getMaterialProperty<Real>("diffusion_coefficient_air");

  MaterialProperty<Real> & pi = getMaterialProperty<Real>("density_ice");

  /// @todo{This needs to be computed}
  _interface_velocity[_qp] = 1e-9; // [m/s]

  _capillary_length[_qp] = (_gamma * std::pow(_a, 3) ) / (_k * _temperature[_qp]);

  _beta[_qp] = (1/_alpha) * pi[_qp] / rho_vs[_qp] * std::sqrt((2*libMesh::pi*_m) / (_k * _temperature[_qp]));

  _lambda[_qp] = (_a1 * _w *pi[_qp]) / (_capillary_length[_qp] * rho_vs[_qp]);

  _tau[_qp] = (_beta[_qp] * rho_vs[_qp] * _w * _lambda[_qp]) / (pi[_qp] * _a1);

  _conductivity[_qp] = ki[_qp] * (1 + _phi[_qp]) / 2 + ka[_qp] * (1 - _phi[_qp]) / 2;

  _heat_capacity[_qp] = ci[_qp] * (1 + _phi[_qp]) / 2 + ca[_qp] * (1 - _phi[_qp]) / 2;

  _diffusion_coefficient[_qp] = dv[_qp] * (1 - _phi[_qp]) / 2;

}
