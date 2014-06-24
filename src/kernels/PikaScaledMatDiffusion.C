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
  return (1.0/_property_uo.temporalScale()) * MatDiffusion::computeQpResidual();;
}

