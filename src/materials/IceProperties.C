#include "IceProperties.h"

template<>
InputParameters validParams<IceProperties>()
{
  InputParameters params = validParams<Material>();

  return params;
}


IceProperties::IceProperties(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    _temperature(coupledValue("temperature")),
    _density_ice(declareProperty<Real>("density_ice"))

{
}

void
IceProperties::computeQpProperties()
{
  /// @\todo{Make this a function of temperature}
  _density_ice[_qp] = 918.9; // [kg/m^3]
}
