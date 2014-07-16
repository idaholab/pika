
// PIKA includes
#include "PhaseFieldProperties.h"

template<>
InputParameters validParams<PhaseFieldProperties>()
{
  InputParameters params = validParams<Material>();
  params += validParams<PropertyUserObjectInterface>();
  params.addCoupledVar("temperature", 273.15, "The temperature variable to couple (default: 273.15)");
  params.addCoupledVar("phi", 1.0, "The phase-field variable to couple");
  return params;
}


PhaseFieldProperties::PhaseFieldProperties(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    PropertyUserObjectInterface(name, parameters),
    _temperature(coupledValue("temperature")),
    _phase(coupledValue("phi")),
    _a1((5./8.)*std::sqrt(2.)),
    _interface_velocity(declareProperty<Real>("interface_velocity")),
    _capillary_length(declareProperty<Real>("capillary_length")),
    _beta(declareProperty<Real>("beta")),
    _lambda(declareProperty<Real>("lambda")),
    _tau(declareProperty<Real>("tau")),
    _conductivity(declareProperty<Real>("conductivity")),
    _heat_capacity(declareProperty<Real>("heat_capacity")),
    _diffusion_coefficient(declareProperty<Real>("diffusion_coefficient")),
    _interface_thickness_squared(declareProperty<Real>("interface_thickness_squared")),
    _equilibrium_concentration(declareProperty<Real>("equilibrium_concentration")),
    _saturation_pressure_of_water_vapor_over_ice(declareProperty<Real>("saturation_pressure_of_water_vapor_over_ice")),
    _specific_humidity_ratio(declareProperty<Real>("specific_humidity_ratio")),
    _xi(_property_uo.temporalScale()),
    _d_o(_property_uo.getParam<Real>("capillary_length")),
    _interface_kinetic_coefficient(_property_uo.getParam<Real>("interface_kinetic_coefficient"))

{
}

void
PhaseFieldProperties::computeQpProperties()
{
  Real convert_meters = _property_uo.getParam<Real>("conversion_factor");
  Real & gamma = getMaterialProperty<Real>("interface_free_energy")[_qp];
  Real & a = getMaterialProperty<Real>("mean_molecular_spacing")[_qp];
  Real & k = getMaterialProperty<Real>("boltzmann")[_qp];
  Real & alpha = getMaterialProperty<Real>("condensation_coefficient")[_qp];
  Real & m = getMaterialProperty<Real>("mass_water_molecule")[_qp];
  const Real & w = (convert_meters) *  getMaterialProperty<Real>("interface_thickness")[_qp];
  const Real & L_sg = (1.0/std::pow(convert_meters,2.0)) *  getMaterialProperty<Real>("latent_heat")[_qp];

  Real rho_vs = _property_uo.equilibriumWaterVaporConcentrationAtSaturation(_property_uo.referenceTemp());
  MaterialProperty<Real> & rho_i = getMaterialProperty<Real>("density_ice");

  MaterialProperty<Real> & ki = getMaterialProperty<Real>("conductivity_ice");
  MaterialProperty<Real> & ka = getMaterialProperty<Real>("conductivity_air");

  MaterialProperty<Real> & ci = getMaterialProperty<Real>("heat_capacity_ice");
  MaterialProperty<Real> & ca = getMaterialProperty<Real>("heat_capacity_air");

  MaterialProperty<Real> & dv = getMaterialProperty<Real>("water_vapor_diffusion_coefficient");

  _capillary_length[_qp] = (convert_meters) * (rho_vs/(rho_i[_qp])) * (gamma * std::pow(a, 3.) ) / (k * _property_uo.referenceTemp());

  _beta[_qp] =(1.0/convert_meters) * (1./(alpha)) * std::sqrt((2.*libMesh::pi*m) / (k * _property_uo.referenceTemp()));

  _lambda[_qp] =(1.0/(convert_meters)) *  (_a1 * w  / _capillary_length[_qp]);

  _tau[_qp] = (_beta[_qp] * w * _lambda[_qp]) / _a1;

  _conductivity[_qp] = (convert_meters) * (ki[_qp] * (1. + _phase[_qp]) / 2. + ka[_qp] * (1. - _phase[_qp]) / 2.);

  _heat_capacity[_qp] =(1.0/(convert_meters)) * ci[_qp] * (1. + _phase[_qp]) / 2. + ca[_qp] * (1. - _phase[_qp]) / 2.;

  _diffusion_coefficient[_qp] =(convert_meters) * (convert_meters) * (dv[_qp] * (1. - _phase[_qp]) / 2.);

  _interface_thickness_squared[_qp] =  w*w;

  _equilibrium_concentration[_qp] =  _property_uo.equilibriumConcentration(_temperature[_qp]);

  // x_s, Eq. (1)
  _specific_humidity_ratio[_qp] = _property_uo.specificHumidityRatio(_temperature[_qp]);

  // P_{vs}, Eq. (2)
  _saturation_pressure_of_water_vapor_over_ice[_qp] =  _property_uo.saturationPressureOfWaterVaporOverIce(_temperature[_qp]);
}
