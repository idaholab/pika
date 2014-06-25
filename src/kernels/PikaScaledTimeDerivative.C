#include "PikaScaledTimeDerivative.h"

template<>
InputParameters validParams<PikaScaledTimeDerivative>()
{
  InputParameters params = validParams<PikaTimeDerivative>();
  return params;
}

PikaScaledTimeDerivative::PikaScaledTimeDerivative(const std::string & name, InputParameters parameters) :
    PikaTimeDerivative(name, parameters),
    PropertyUserObjectInterface(name,parameters)
    
{}

Real
PikaScaledTimeDerivative::computeQpResidual()
{
  return (_property_uo.temporalScale()) * PikaTimeDerivative::computeQpResidual();
}
Real
PikaScaledTimeDerivative::computeQpJacobian()
{
  return (_property_uo.temporalScale()) * PikaTimeDerivative::computeQpJacobian();
}
