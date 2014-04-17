#include "PhaseFieldProperties.h"

template<>
InputParameters validParams<PhaseFieldProperties>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredCoupledVar("temperature", "The temperature variable to couple");
  params.addRequiredCoupledVar("phi", "The phase-field variable to couple");

  return params;
}


PhaseFieldProperties::PhaseFieldProperties(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    ChemicalPotentialInterface(),
    _temperature(coupledValue("temperature")),
    _phi(coupledValue("phi")),
    _a1(5/8*std::sqrt(2)),
    _interface_velocity(declareProperty<Real>("interface_velocity")),
    _capillary_length(declareProperty<Real>("capillary_length")),
    _beta(declareProperty<Real>("beta")),
    _lambda(declareProperty<Real>("lamda")),
    _tau(declareProperty<Real>("tau")),
    _conductivity(declareProperty<Real>("conductivity")),
    _heat_capacity(declareProperty<Real>("head_capacity")),
    _diffusion_coefficient(declareProperty<Real>("diffusion_coefficient")),
    _interface_thickness_squared(declareProperty<Real>("interface_thickness_squared")),
    _chemical_potential_eq(declareProperty<Real>("chemical_potential_eq"))
{



}

void
PhaseFieldProperties::computeQpProperties()
{
  Real & gamma = getMaterialProperty<Real>("interface_free_energy")[_qp];
  Real & a = getMaterialProperty<Real>("mean_molecular_spacing")[_qp];
  Real & k = getMaterialProperty<Real>("mean_molecular_spacing")[_qp];
  Real & alpha = getMaterialProperty<Real>("condensation_coefficient")[_qp];
  Real & m = getMaterialProperty<Real>("mass_water_molecule")[_qp];
  Real & w = getMaterialProperty<Real>("interface_thickness")[_qp];
  Real & T0 = getMaterialProperty<Real>("reference_temperature")[_qp];

  MaterialProperty<Real> & rho_vs = getMaterialProperty<Real>("water_vapor_mass_density_saturation");

  MaterialProperty<Real> & ki = getMaterialProperty<Real>("conductivity_ice");
  MaterialProperty<Real> & ka = getMaterialProperty<Real>("conductivity_air");

  MaterialProperty<Real> & ci = getMaterialProperty<Real>("heat_capacity_ice");
  MaterialProperty<Real> & ca = getMaterialProperty<Real>("heat_capacity_air");

  MaterialProperty<Real> & dv = getMaterialProperty<Real>("diffusion_coefficient_air");

  MaterialProperty<Real> & pi = getMaterialProperty<Real>("density_ice");


  /// @todo{This needs to be computed}
  _interface_velocity[_qp] = 1e-9; // [m/s]

  _capillary_length[_qp] = (gamma * std::pow(a, 3) ) / (k * _temperature[_qp]);

  _beta[_qp] = (1/alpha) * pi[_qp] / rho_vs[_qp] * std::sqrt((2*libMesh::pi*m) / (k * _temperature[_qp]));

  _lambda[_qp] = (_a1 * w *pi[_qp]) / (_capillary_length[_qp] * rho_vs[_qp]);

  _tau[_qp] = (_beta[_qp] * rho_vs[_qp] * w * _lambda[_qp]) / (pi[_qp] * _a1);

  _conductivity[_qp] = ki[_qp] * (1 + _phi[_qp]) / 2 + ka[_qp] * (1 - _phi[_qp]) / 2;

  _heat_capacity[_qp] = ci[_qp] * (1 + _phi[_qp]) / 2 + ca[_qp] * (1 - _phi[_qp]) / 2;

  _diffusion_coefficient[_qp] = dv[_qp] * (1 - _phi[_qp]) / 2;

  _interface_thickness_squared[_qp] = w*w;

  Real rvs_T  = saturationVaporPressure(_temperature[_qp]);
  Real rvs_T0 = saturationVaporPressure(T0);
  _chemical_potential_eq[_qp] = (rvs_T - rvs_T0) / pi[_qp];

}
