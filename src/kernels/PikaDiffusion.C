
// MOOSE includes
#include "PikaDiffusion.h"

template<>
InputParameters validParams<PikaDiffusion>()
{
  InputParameters params = validParams<Diffusion>();
  params += validParams<PropertyUserObjectInterface>();
  params += validParams<CoefficientKernelInterface>();
  return params;
}

PikaDiffusion::PikaDiffusion(const std::string & name, InputParameters parameters) :
    Diffusion(name, parameters),
    PropertyUserObjectInterface(name, parameters),
    CoefficientKernelInterface(name, parameters)
{
  // The getMaterialProperty method cannot be replicated in interface
  if (useMaterial())
    setMaterialPropertyPointer(&getMaterialProperty<Real>("property"));
}

Real
PikaDiffusion::computeQpResidual()
{
  return coefficient(_qp) * Diffusion::computeQpResidual();
}

Real
PikaDiffusion::computeQpJacobian()
{
  return coefficient(_qp) * Diffusion::computeQpJacobian();
}
