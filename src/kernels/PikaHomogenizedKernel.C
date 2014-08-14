#include "PikaHomogenizedKernel.h"

template<>
InputParameters validParams<PikaHomogenizedKernel>()
{
  InputParameters params = validParams<HomogenizationHeatConduction>();
  params += validParams<PropertyUserObjectInterface>();
  params += validParams<CoefficientKernelInterface>();
  return params;
}


PikaHomogenizedKernel::PikaHomogenizedKernel(const std::string & name, InputParameters parameters):
  HomogenizationHeatConduction(name, parameters),
  PropertyUserObjectInterface(name, parameters),
  CoefficientKernelInterface(name, parameters)
{}

Real
PikaHomogenizedKernel::computeQpResidual()
{
  return coefficient(_qp) * HomogenizationHeatConduction::computeQpResidual();
}
