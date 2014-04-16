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
    _temperature(coupledValue("temperature")),
    _density_air(declareProperty<Real>("density_air")),
    _conductivity_air(declareProperty<Real>("conductivity_air")),
    _heat_capacity_air(declareProperty<Real>("heat_capacity_air")),
    _diffusion_coefficient_air(declareProperty<Real>("diffusion_coefficient_air")),
    _gas_constant_dry_air(declareProperty<Real>("gas_constant_dry_air")),
    _gas_constant_water_vapor(declareProperty<Real>("gas_constant_wator_vapor")),
    _saturation_pressure_vapor(declareProperty<Real>("saturation_pressure_vapor")),
    _atmospheric_pressure(declareProperty<Real>("atmospheric_pressure")),
    _humidity_ratio(declareProperty<Real>("humidity_ratio")),
    _water_vapor_mass_density_saturation(declareProperty<Real>("water_vapor_mass_density_saturation"))
{
  _k.push_back(-0.5865e4);
  _k.push_back(0.2224e2);
  _k.push_back(0.1375e-1);
  _k.push_back(-0.3403e-4);
  _k.push_back(0.2697e-7);
  _k.push_back(0.6918);
}

void
AirProperties::computeQpProperties()
{
  /// @\todo{Make this a function of temperature}
  _density_air[_qp] = 918.9; // [kg/m^3]

  _conductivity_air[_qp] = 0.02; // [W/(m K)]

  _heat_capacity_air[_qp] = 1.4e3; // [J/(m^3 K)]

  _diffusion_coefficient_air[_qp] = 2.178e-5; //[m^2/s]

  _gas_constant_dry_air[_qp] = 286.9; //[J/(Kg K)]
  _gas_constant_water_vapor[_qp] = 461.5; //[J/(Kg K)]

  _atmospheric_pressure[_qp] = 1.01325e-5; // [Pa]

  // Eq.(2)
  _saturation_pressure_vapor[_qp] = std::exp(_k[0]*std::pow(_temperature[_qp], -1)
                                             + _k[1]//*std::pow(_temperature[_qp], 0)
                                             + _k[2]*std::pow(_temperature[_qp], 1)
                                             + _k[3]*std::pow(_temperature[_qp], 2)
                                             + _k[4]*std::pow(_temperature[_qp], 3)
                                             + _k[5]*std::log(_temperature[_qp]));

  // Eq. (1)
  _humidity_ratio[_qp] = (_gas_constant_dry_air[_qp] / _gas_constant_water_vapor[_qp])
    * (_saturation_pressure_vapor[_qp] / (_atmospheric_pressure[_qp] - _saturation_pressure_vapor[_qp]));

  // Eq. (3)
  _water_vapor_mass_density_saturation[_qp] = _atmospheric_pressure[_qp] * _humidity_ratio[_qp];


}
