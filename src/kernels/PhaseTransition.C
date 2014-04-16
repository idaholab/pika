#include "PhaseTransition.h"
#include "AirProperties.h"

template<>
InputParameters validParams<PhaseTransition>()
{
  InputParameters params = validParams<ACBulk>();
  params.addRequiredCoupledVar("u", "The dimensionless unknown from the vapor diffusion equation");
  params.addRequiredCoupledVar("temperature", "The temperature variable to couple");
  params.addParam<std::string>("lambda", "lambda", "The name of the material property containing the definition of lambda");
  params.addParam<std::string>("reference_temperature", "reference_temperature", "The name of the material property containing the reference temperature");
  params.addParam<std::string>("density_ice", "density_ice", "The name of the material property containing the density of ice");
  return params;
}

PhaseTransition::PhaseTransition(const std::string & name, InputParameters parameters) :
    ACBulk(name, parameters),
    _s(coupledValue("u")),
    _temperature(getMaterialProperty<Real>(getParam<std::string>("temperature"))),
    _lambda(getMaterialProperty<Real>(getParam<std::string>("lambda"))),
    _density_ice(getMaterialProperty<Real>(getParam<std::string>("density_ice"))),
    _reference_temperature(getMaterialProperty<Real>(getParam<std::string>("reference_temperature")))
{
}

Real
PhaseTransition::computeDFDOP(PFFunctionType type)
{
  /// @todo{this is redudant code, should create an interface class that may be inherited by any method needing this calculation}
  std::vector<Real> K;
  K.push_back(-0.5865e4);
  K.push_back(0.2224e2);
  K.push_back(0.1375e-1);
  K.push_back(-0.3403e-4);
  K.push_back(0.2697e-7);
  K.push_back(0.6918);
  Real rvs_T  = AirProperties::saturationVaporPressureOfWaterVaporOverIce(_temperature[_qp], K);
  Real rvs_T0 = AirProperties::saturationVaporPressureOfWaterVaporOverIce(_reference_temperature[_qp], K);

  Real s_eq = (rvs_T - rvs_T0) / _density_ice[_qp];

  switch (type)
  {
  case Residual:
    return - _lambda[_qp] * (_s[_qp] - s_eq) * (1 - _u[_qp]*_u[_qp])*(1 - _u[_qp]*_u[_qp]);

  case Jacobian:
    return 4 * _lambda[_qp] * (_s[_qp] - s_eq) * (1 - _u[_qp]) * _u[_qp];
  }
}
