/**********************************************************************************/
/*                  Pika: Phase field snow micro-structure model                  */
/*                                                                                */
/*                     (C) 2014 Battelle Energy Alliance, LLC                     */
/*                              ALL RIGHTS RESERVED                               */
/*                                                                                */
/*                   Prepared by Battelle Energy Alliance, LLC                    */
/*                      Under Contract No. DE-AC07-05ID14517                      */
/*                      With the U. S. Department of Energy                       */
/**********************************************************************************/

// Pika includes
#include "PikaMaterial.h"

registerMooseObject("PikaApp", PikaMaterial);

template<>
InputParameters validParams<PikaMaterial>()
{
  InputParameters params = validParams<Material>();
  params += validParams<PropertyUserObjectInterface>();
  params.addRequiredCoupledVar("temperature", "The temperature variable to couple");
  params.addRequiredCoupledVar("phase", "The phase-field variable");
  params.addParam<bool>("debug", false, "Enable the creating of material properties for debugging");

  params.addParam<std::vector<OutputName> >("outputs", std::vector<OutputName>(1, "none"), "Vector of output names were you would like to restrict the output of material data (empty outputs to all)");
  params.addParam<std::vector<std::string> >("output_properties", std::vector<std::string>(), "List of material properties, from this material, to output (outputs must also be defined to an output type)");

  return params;
}

PikaMaterial::PikaMaterial(const InputParameters & parameters) :
    Material(parameters),
    PropertyUserObjectInterface(parameters),
    _debug(getParam<bool>("debug")),
    _temperature(coupledValue("temperature")),
    _phase(coupledValue("phase")),
    _interface_thickness(_property_uo.getParamTempl<Real>("interface_thickness")),
    _a_1((5./8.)*std::sqrt(2)),
    _density_ice(_property_uo.getParamTempl<Real>("density_ice")),
    _l_sg(_property_uo.getParamTempl<Real>("latent_heat")),
    _ki(_property_uo.getParamTempl<Real>("conductivity_ice")),
    _ka(_property_uo.getParamTempl<Real>("conductivity_air")),
    _ci(_property_uo.getParamTempl<Real>("heat_capacity_ice")),
    _ca(_property_uo.getParamTempl<Real>("heat_capacity_air")),
    _dv(_property_uo.getParamTempl<Real>("water_vapor_diffusion_coefficient")),
    _spatial_scale(_property_uo.getParamTempl<Real>("spatial_scaling")),
    _input_mobility(_property_uo.getParamTempl<Real>("mobility")),
    _reference_temperature(_property_uo.getParamTempl<Real>("reference_temperature")),
    _tau(declareProperty<Real>("relaxation_time")),
    _lambda(declareProperty<Real>("phase_field_coupling_constant")),
    _interface_thickness_squared(declareProperty<Real>("interface_thickness_squared")),
    _equilibrium_chemical_potential(declareProperty<Real>("equilibrium_chemical_potential")),
    _heat_capacity(declareProperty<Real>("heat_capacity")),
    _conductivity(declareProperty<Real>("conductivity")),
    _diffusion_coefficient(declareProperty<Real>("diffusion_coefficient")),
    _latent_heat(declareProperty<Real>("latent_heat")),
    _mobility(declareProperty<Real>("mobility")),
    _rho_vs(NULL),
    _specific_humidity_ratio(NULL),
    _saturation_pressure_of_water_vapor_over_ice(NULL),
    _capillary_length(NULL),
    _capillary_length_prime(NULL),
    _interface_kinetic_coefficient(NULL),
    _interface_kinetic_coefficient_prime(NULL)
{
  // If debugging is enable, declare the extra properties
  if (_debug)
  {
    _rho_vs = &declareProperty<Real>("equilibrium_water_vapor_concentration_at_saturation");
    _specific_humidity_ratio = &declareProperty<Real>("specific_humidity_ratio");
    _saturation_pressure_of_water_vapor_over_ice = &declareProperty<Real>("saturation_pressure_of_water_vapor_over_ice");
    _capillary_length = &declareProperty<Real>("capillary_length");
    _capillary_length_prime = &declareProperty<Real>("capillary_length_prime");
    _interface_kinetic_coefficient = &declareProperty<Real>("interface_kinetic_coefficient");
    _interface_kinetic_coefficient_prime = &declareProperty<Real>("interface_kinetic_coefficient_prime");
  }
}

void
PikaMaterial::computeQpProperties()
{
  // Compute \\rho_vs; Eq. (3)
  Real rho_vs = _property_uo.equilibriumWaterVaporConcentrationAtSaturation(_temperature[_qp]);
  const Real & rho_vs_T_0 = _property_uo.equilibriumWaterVaporConcentrationAtSaturationAtReferenceTemperature();

  // lambda; Eq. (37)
  const Real _d_0_prime = _property_uo.capillaryLengthPrime(_temperature[_qp], rho_vs);
  _lambda[_qp] = _a_1 * _interface_thickness / _d_0_prime;

  // tau; Eq. (38)
  const Real _beta_0_prime = _property_uo.interfaceKineticCoefficientPrime(_temperature[_qp], rho_vs);
  _tau[_qp] = _beta_0_prime * _interface_thickness * _lambda[_qp] / _a_1;

  // u_eq; Eq. (33)
  _equilibrium_chemical_potential[_qp] = (rho_vs - rho_vs_T_0) / _density_ice;

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

  // Mobility
  _mobility[_qp] = _input_mobility;

  // Debugging material creation
  if (_debug)
  {
    (*_rho_vs)[_qp] = rho_vs;
    (*_specific_humidity_ratio)[_qp] = _property_uo.specificHumidityRatio(_temperature[_qp]);
    (*_saturation_pressure_of_water_vapor_over_ice)[_qp] = _property_uo.saturationPressureOfWaterVaporOverIce(_temperature[_qp]);
    (*_capillary_length)[_qp] = _d_0_prime * (_density_ice / rho_vs);
    (*_capillary_length_prime)[_qp] = _d_0_prime;
    (*_interface_kinetic_coefficient)[_qp] = _beta_0_prime * (_density_ice / rho_vs);
    (*_interface_kinetic_coefficient_prime)[_qp] = _beta_0_prime;
  }
}
