
// Pika includes
#include "AirProperties.h"

template<>
InputParameters validParams<AirProperties>()
{
  InputParameters params = validParams<Material>();
  params += validParams<PropertyUserObjectInterface>();
  params += AirProperties::objectParams();
  params.addCoupledVar("temperature", 273.15, "The temperature variable to couple (default: 273.15 K)");
  return params;
}

AirProperties::AirProperties(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    PropertyUserObjectInterface(name, parameters),
    _temperature(coupledValue("temperature")),
    _rho_a(declareProperty<Real>("density_air")),
    _kappa_a(declareProperty<Real>("conductivity_air")),
    _C_a(declareProperty<Real>("heat_capacity_air")),
    _D_v(declareProperty<Real>("water_vapor_diffusion_coefficient"))
{
}

void
AirProperties::computeQpProperties()
{
  _rho_a[_qp] = _property_uo.airDensity(_temperature[_qp]);

  _kappa_a[_qp] = getParam<Real>("conductivity_air");

  _C_a[_qp] = getParam<Real>("heat_capacity_air");

  _D_v[_qp] = getParam<Real>("water_vapor_diffusion_coefficient");
}

InputParameters
AirProperties::objectParams()
{
  InputParameters params = emptyInputParameters();
  params.addParam<Real>("conductivity_air", 0.02, "Thermal conductivity or air, kappa_a [ W/(m K)]");
  params.addParam<Real>("heat_capacity_air", 1.4e3, "Heat capacity of air, C_a [J/(m^3 K)]");
  params.addParam<Real>("water_vapor_diffusion_coefficient", 2.178e-5, "Diffusion coefficient water vapor in air, D_v [m^2/s]");
  return params;
}
