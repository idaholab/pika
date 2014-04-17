#include "MaterialTimeDerivative.h"

template<>
InputParameters validParams<MaterialTimeDerivative>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addRequiredParam<std::string>("property", "The name of the material property to utilize as the coefficient");
  params.addParam<Real>("factor", 0, "Factor added to the material property value");
  params.addParam<Real>("scale", 1, "Multiplier applied to the material property value");
  return params;
}


MaterialTimeDerivative::MaterialTimeDerivative(const std::string & name, InputParameters parameters) :
    TimeDerivative(name, parameters),
    _coefficient(getMaterialProperty<Real>(getParam<std::string>("property"))),
    _factor(getParam<Real>("factor")),
    _scale(getParam<Real>("scale"))
{}

Real
MaterialTimeDerivative::computeQpResidual()
{
  return (_scale * 1 + _factor) * TimeDerivative::computeQpResidual();
//  return (_scale * _coefficient[_qp] + _factor) * TimeDerivative::computeQpResidual();
}

Real
MaterialTimeDerivative::computeQpJacobian()
{
  return (_scale * 1 + _factor) * TimeDerivative::computeQpJacobian();
//  return (_scale * _coefficient[_qp] + _factor) * TimeDerivative::computeQpJacobian();
}
