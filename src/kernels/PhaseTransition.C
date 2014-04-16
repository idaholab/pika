#include "PhaseTransition.h"
#include "AirProperties.h"

template<>
InputParameters validParams<PhaseTransition>()
{
  InputParameters params = validParams<ACBulk>();
  params.addRequiredCoupledVar("u", "The dimensionless unknown from the vapor diffusion equation");
  params.addRequiredCoupledVar("temperature", "The temperature variable to couple");
  params.addParam<std::string>("lambda", "lambda", "The name of the material property containing the definition of lambda");
  return params;
}

PhaseTransition::PhaseTransition(const std::string & name, InputParameters parameters) :
    ACBulk(name, parameters),
    _s(coupledValue("u")),
    _temperature(getMaterialProperty<Real>(getParam<std::string>("temperature"))),
    _lambda(getMaterialProperty<Real>(getParam<std::string>("lambda"))),
    _s_eq(getMaterialProperty<Real>(getParam<std::string>("chemical_potential_eq")))
{
}

Real
PhaseTransition::computeDFDOP(PFFunctionType type)
{

  switch (type)
  {
  case Residual:
    return - _lambda[_qp] * (_s[_qp] - _s_eq[_qp]) * (1 - _u[_qp]*_u[_qp])*(1 - _u[_qp]*_u[_qp]);

  case Jacobian:
    return 4 * _lambda[_qp] * (_s[_qp] - _s_eq[_qp]) * (1 - _u[_qp]) * _u[_qp];
  }
}
