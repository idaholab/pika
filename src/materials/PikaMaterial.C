/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

// Pika includes
#include "PikaMaterial.h"

template<>
InputParameters validParams<PikaMaterial>()
{
  InputParameters params = validParams<Material>();
  params += validParams<PropertyUserObjectInterface>();
  params.addRequiredCoupledVar("temperature", "The temperature variable to couple");
  params.addRequiredCoupledVar("phase", "The phase-field variable");
  return params;
}

PikaMaterial::PikaMaterial(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    PropertyUserObjectInterface(name, parameters),
    _temperature(coupledValue("temperature")),
    _phase(coupledValue("phase")),
    _interface_thickness(_property_uo.getParam<Real>("interface_thickness")),
    _a_1((5./8.)*std::sqrt(2)),
    _density_ice(_property_uo.getParam<Real>("density_ice")),
    _l_sg(_property_uo.getParam<Real>("latent_heat")),
    _ki(_property_uo.getParam<Real>("conductivity_ice")),
    _ka(_property_uo.getParam<Real>("conductivity_air")),
    _ci(_property_uo.getParam<Real>("heat_capacity_ice")),
    _ca(_property_uo.getParam<Real>("heat_capacity_air")),
    _dv(_property_uo.getParam<Real>("water_vapor_diffusion_coefficient")),
    _spatial_scale(_property_uo.getParam<Real>("spatial_scaling")),
    _rho_vs(declareProperty<Real>("equilibrium_water_vapor_concentration_at_saturation")),
    _tau(declareProperty<Real>("relaxation_time")),
    _lambda(declareProperty<Real>("phase_field_coupling_constant")),
    _interface_thickness_squared(declareProperty<Real>("interface_thickness_squared")),
    _equilibrium_chemical_potential(declareProperty<Real>("equilibrium_chemical_potential")),
    _heat_capacity(declareProperty<Real>("heat_capacity")),
    _conductivity(declareProperty<Real>("conductivity")),
    _diffusion_coefficient(declareProperty<Real>("diffusion_coefficient")),
    _latent_heat(declareProperty<Real>("latent_heat"))
{
}

void
PikaMaterial::initialSetup()
{
  const Real & T_0 = _property_uo.getParam<Real>("reference_temperature");
  _rho_vs_T_0 = _property_uo.equilibriumWaterVaporConcentrationAtSaturation(T_0);
}


void
PikaMaterial::computeQpProperties()
{
  // Compute \\rho_vs; Eq. (3)
  _rho_vs[_qp] = _property_uo.equilibriumWaterVaporConcentrationAtSaturation(_temperature[_qp]);
  std::cout << "_rho_vs[_qp] = " << _rho_vs[_qp] << std::endl;

  // lambda; Eq. (37)
  const Real _d_0_prime = (_rho_vs[_qp] / _density_ice) * _property_uo.capillaryLength(_temperature[_qp]);
  _lambda[_qp] = _a_1 * _interface_thickness / _d_0_prime;

  // tau; Eq. (38)
  const Real _beta_0_prime = (_rho_vs[_qp] / _density_ice) * _property_uo.interfaceKineticCoefficient(_temperature[_qp]);
  _tau[_qp] = _beta_0_prime * _interface_thickness * _lambda[_qp] / _a_1;

  // u_eq; Eq. (33)
  _equilibrium_chemical_potential[_qp] = (_rho_vs[_qp] - _rho_vs_T_0) / _density_ice;
  std::cout << "_rho_vs_T_0 = " << _rho_vs_T_0 << std::endl;

  std::cout << "_equilibrium_chemical_potential[_qp] = " << _equilibrium_chemical_potential[_qp] << std::endl;

  // Thermal conductivity
  _conductivity[_qp] = (_spatial_scale) * (_ki * (1. + _phase[_qp]) / 2. + _ka * (1. - _phase[_qp]) / 2.);

  // Heat capacity
  _heat_capacity[_qp] =(1.0/(_spatial_scale)) * _ci * (1. + _phase[_qp]) / 2. + _ca * (1. - _phase[_qp]) / 2.;

  // Diffusion coefficient
  _diffusion_coefficient[_qp] = (_spatial_scale) * (_spatial_scale) * _dv * (1. - _phase[_qp]) / 2. ;

  // W^2
  _interface_thickness_squared[_qp] = std::pow(_interface_thickness, 2);

  // Latent heat of sublimation
  _latent_heat[_qp] = _l_sg;
}
