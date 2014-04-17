#include "AirProperties.h"

template<>
InputParameters validParams<AirProperties>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredCoupledVar("temperature", "The temperature variable to couple");
  return params;
}


AirProperties::AirProperties(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    ChemicalPotentialInterface(),
    _temperature(coupledValue("temperature")),
    _density_air(declareProperty<Real>("density_air")),
    _conductivity_air(declareProperty<Real>("conductivity_air")),
    _heat_capacity_air(declareProperty<Real>("heat_capacity_air")),
    _diffusion_coefficient_air(declareProperty<Real>("diffusion_coefficient_air")),
    _water_vapor_mass_density_saturation(declareProperty<Real>("water_vapor_mass_density_saturation"))
{
}

void
AirProperties::computeQpProperties()
{

  MaterialProperty<Real> & R_da = getMaterialProperty<Real>("gas_constant_dry_air");
  MaterialProperty<Real> & R_v = getMaterialProperty<Real>("gas_constant_water_vapor");
  MaterialProperty<Real> & P_a = getMaterialProperty<Real>("atmospheric_pressure");

/// @\todo{Make this a function of temperature}
  _density_air[_qp] = 918.9; // [kg/m^3]

  _conductivity_air[_qp] = 0.02; // [W/(m K)]

  _heat_capacity_air[_qp] = 1.4e3; // [J/(m^3 K)]

  _diffusion_coefficient_air[_qp] = 2.178e-5; //[m^2/s]

  // Eq.(2)
  Real P_vs = 1;//saturationVaporPressure(_temperature[_qp]);

  // Eq. (1)
  Real x_s = 1;//(R_da[_qp] / R_v[_qp]) * (P_vs / (P_a[_qp] - P_vs));

  // Eq. (3)
  _water_vapor_mass_density_saturation[_qp] = P_a[_qp] * x_s;
}
