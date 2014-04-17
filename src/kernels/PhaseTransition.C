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
    ChemicalPotentialInterface(),
    _s(coupledValue("u")),
    _temperature(coupledValue("temperature")),
    _lambda(getMaterialProperty<Real>(getParam<std::string>("lambda")))
{
}

Real
PhaseTransition::computeDFDOP(PFFunctionType type)
{

  MaterialProperty<Real> & pi = getMaterialProperty<Real>("density_ice");
  MaterialProperty<Real> & T0 = getMaterialProperty<Real>("reference_temperature");

  Real rvs_T  = 1;//saturationVaporPressure(_temperature[_qp]);
  Real rvs_T0 = 1;//saturationVaporPressure(T0[_qp]);
  Real s_eq = 1;//(rvs_T - rvs_T0) / pi[_qp];



  switch (type)
  {
  case Residual:
    return - _lambda[_qp] * (_s[_qp] - s_eq) * (1 - _u[_qp]*_u[_qp])*(1 - _u[_qp]*_u[_qp]);

  case Jacobian:
    return 4 * _lambda[_qp] * (_s[_qp] - s_eq) * (1 - _u[_qp]) * _u[_qp];
  }
}
