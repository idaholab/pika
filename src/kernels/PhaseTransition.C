#include "PhaseTransition.h"
#include "AirProperties.h"

template<>
InputParameters validParams<PhaseTransition>()
{
  InputParameters params = validParams<ACBulk>();
  params.addRequiredCoupledVar("chemical_potential", "The chemical potential variable to couple");
  params.addParam<std::string>("lambda", "lambda", "The name of the material property containing the definition of lambda");
  params.addParam<std::string>("equilibrium_concentration", "equilibrium_concentration", "The name of the material property containing the equilibrium concentration");

  return params;
}

PhaseTransition::PhaseTransition(const std::string & name, InputParameters parameters) :
    ACBulk(name, parameters),
    PropertyUserObjectInterface(name, parameters),
    _s(coupledValue("chemical_potential")),
    _lambda(getMaterialProperty<Real>(getParam<std::string>("lambda"))),
    _s_eq(getMaterialProperty<Real>(getParam<std::string>("equilibrium_concentration")))
{
}

Real
PhaseTransition::computeDFDOP(PFFunctionType type)
{
    Real f =  - (_lambda[_qp]) * (_s[_qp] - _s_eq[_qp]) * (1.0 - _u[_qp]*_u[_qp])*(1.0 - _u[_qp]*_u[_qp]);
    std::cout<<f<<std::endl;
  switch (type)
  {
  case Residual:
    return f;
  case Jacobian:
    return  -4.0 * _lambda[_qp] * _u[_qp] * (-_u[_qp]*_u[_qp]+1.0) * (_s[_qp] - _s_eq[_qp]);
  }
}
