#include "PikaTimeDerivative.h"

template<>
InputParameters validParams<PikaTimeDerivative>()
{
  InputParameters params = validParams<TimeDerivative>();
  params += validParams<PropertyUserObjectInterface>();
  params += validParams<CoefficientKernelInterface>();
  return params;
}

PikaTimeDerivative::PikaTimeDerivative(const std::string & name, InputParameters parameters) :
    TimeDerivative(name, parameters),
    PropertyUserObjectInterface(name, parameters),
    CoefficientKernelInterface(name, parameters)
{
  // The getMaterialProperty method cannot be replicated in interface
  if (useMaterial())
    setMaterialPropertyPointer(&getMaterialProperty<Real>("property"));
}

Real
PikaTimeDerivative::computeQpResidual()
{
  return coefficient(_qp) * TimeDerivative::computeQpResidual();
}

Real
PikaTimeDerivative::computeQpJacobian()
{
  return coefficient(_qp) * TimeDerivative::computeQpJacobian();
}
