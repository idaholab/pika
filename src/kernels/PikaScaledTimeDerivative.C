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
  return (1.0/_property_uo.temporalScale()) * PikaTimeDerivative::computeQpResidual();
}
