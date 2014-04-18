
// PIKA includes
#include "PhaseFieldProperties.h"
#include "ChemicalPotentialPropertyUserObject.h"

template<>
InputParameters validParams<PhaseFieldProperties>()
{
  InputParameters params = validParams<Material>();
  params += validParams<ChemicalPotentialInterface>();
  params.addRequiredCoupledVar("temperature", "The temperature variable to couple");
  params.addCoupledVar("phi", 1, "The phase-field variable to couple");

  return params;
}


PhaseFieldProperties::PhaseFieldProperties(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    ChemicalPotentialInterface(getUserObject<ChemicalPotentialPropertyUserObject>("property_user_object")),
    _temperature(coupledValue("temperature")),
    _phi(coupledValue("phi")),
    _a1(5/8*std::sqrt(2)),
    _interface_velocity(declareProperty<Real>("interface_velocity")),
    _capillary_length(declareProperty<Real>("capillary_length")),
    _beta(declareProperty<Real>("beta")),
    _lambda(declareProperty<Real>("lambda")),
    _tau(declareProperty<Real>("tau")),
    _conductivity(declareProperty<Real>("conductivity")),
    _heat_capacity(declareProperty<Real>("heat_capacity")),
    _diffusion_coefficient(declareProperty<Real>("diffusion_coefficient")),
    _interface_thickness_squared(declareProperty<Real>("interface_thickness_squared")),
    _equilibrium_concentration(declareProperty<Real>("equilibrium_concentration"))
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

  Real rho_vs = equilibriumWaterVaporConcentrationAtSaturation(_temperature[_qp]);

  MaterialProperty<Real> & ki = getMaterialProperty<Real>("conductivity_ice");
  MaterialProperty<Real> & ka = getMaterialProperty<Real>("conductivity_air");

  MaterialProperty<Real> & ci = getMaterialProperty<Real>("heat_capacity_ice");
  MaterialProperty<Real> & ca = getMaterialProperty<Real>("heat_capacity_air");

  MaterialProperty<Real> & dv = getMaterialProperty<Real>("diffusion_coefficient_air");

  MaterialProperty<Real> & pi = getMaterialProperty<Real>("density_ice");

  /// @todo{This needs to be computed}
  _interface_velocity[_qp] = 1e-9; // [m/s]

  _capillary_length[_qp] = (gamma * std::pow(a, 3) ) / (k * _temperature[_qp]);

  _beta[_qp] = (1/alpha) * pi[_qp] / rho_vs * std::sqrt((2*libMesh::pi*m) / (k * _temperature[_qp]));

  _lambda[_qp] = (_a1 * w *pi[_qp]) / (_capillary_length[_qp] * rho_vs);

  _tau[_qp] = (_beta[_qp] * rho_vs * w * _lambda[_qp]) / (pi[_qp] * _a1);

  _conductivity[_qp] = ki[_qp] * (1 + _phi[_qp]) / 2 + ka[_qp] * (1 - _phi[_qp]) / 2;

  _heat_capacity[_qp] = ci[_qp] * (1 + _phi[_qp]) / 2 + ca[_qp] * (1 - _phi[_qp]) / 2;

  _diffusion_coefficient[_qp] = dv[_qp] * (1 - _phi[_qp]) / 2;

  _interface_thickness_squared[_qp] = w*w;

  _equilibrium_concentration[_qp] = equilibriumConcentration(_temperature[_qp]);
}
