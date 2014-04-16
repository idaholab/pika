#include "CoefficientTimeDerivative.h"

template<>
InputParameters validParams<CoefficientTimeDerivative>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addParam<Real>("coefficient", 1.0, "Time derivative coefficient");
  return params;
}


CoefficientTimeDerivative::CoefficientTimeDerivative(const std::string & name, InputParameters parameters) :
    TimeDerivative(name, parameters),
    _coefficient(getParam<Real>("coefficient"))
{}

Real
CoefficientTimeDerivative::computeQpResidual()
{
  return _coefficient * TimeDerivative::computeQpResidual();
}

Real
CoefficientTimeDerivative::computeQpJacobian()
{
  return _coefficient * TimeDerivative::computeQpJacobian();
}
