#include "PikaScaledMatDiffusion.h"


template<>
InputParameters validParams<PikaScaledMatDiffusion>()
{
  InputParameters params = validParams<MatDiffusion>();
  return params;
}

PikaScaledMatDiffusion::PikaScaledMatDiffusion(const std::string & name, InputParameters parameters) :
    MatDiffusion(name, parameters),
    PropertyUserObjectInterface(name,parameters)
{}

Real
PikaScaledMatDiffusion::computeQpResidual()
{
  return (_property_uo.temporalScale()) * MatDiffusion::computeQpResidual();;
}
Real
PikaScaledMatDiffusion::computeQpJacobian()
{
  return (_property_uo.temporalScale()) * MatDiffusion::computeQpJacobian();;
}

