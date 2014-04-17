#include "IceProperties.h"

template<>
InputParameters validParams<IceProperties>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredCoupledVar("temperature", "The temperature variable to couple");
  return params;
}


IceProperties::IceProperties(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    _temperature(coupledValue("temperature")),
    _density_ice(declareProperty<Real>("density_ice")),
    _conductivity_ice(declareProperty<Real>("conducivity_ice")),
    _heat_capacity_ice(declareProperty<Real>("heat_capacity_ice"))
{
}

void
IceProperties::computeQpProperties()
{
  _density_ice[_qp] = 918.9;        // [kg/m^3]
  _conductivity_ice[_qp] = 2.29;    // [W/(m K)]
  _heat_capacity_ice[_qp] = 1.8e-6; // [J/(m^3 K)]
}
