#include "MaterialTimeDerivative.h"

template<>
InputParameters validParams<MaterialTimeDerivative>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addRequiredParam<std::string>("property", "The name of the material property to utilize as the coefficient");
  return params;
}


MaterialTimeDerivative::MaterialTimeDerivative(const std::string & name, InputParameters parameters) :
    TimeDerivative(name, parameters),
    _coefficient(getMaterialProperty<Real>(getParam<std::string>("property")))
{}

Real
MaterialTimeDerivative::computeQpResidual()
{
  return _coefficient[_qp] * TimeDerivative::computeQpResidual();
}

Real
MaterialTimeDerivative::computeQpJacobian()
{
  return _coefficient[_qp] * TimeDerivative::computeQpJacobian();
}
