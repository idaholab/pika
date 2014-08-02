/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "TensorDiffusion.h"

template<>
InputParameters validParams<TensorDiffusion>()
{
  InputParameters params = validParams<Diffusion>();
  params += validParams<PropertyUserObjectInterface>();
  params += validParams<CoefficientKernelInterface>();
  params.addParam<std::string>("mobility_tensor", "The tensor form of mobility (Nicoli, 2011)");
  return params;
}

TensorDiffusion::TensorDiffusion(const std::string & name, InputParameters parameters) :
    Diffusion(name, parameters),
    PropertyUserObjectInterface(name,parameters),
    CoefficientKernelInterface(name, parameters),
    _coef(getMaterialProperty<RealTensorValue>(getParam<std::string>("mobility_tensor")))
{
}

TensorDiffusion::~TensorDiffusion()
{
}


Real
TensorDiffusion::computeQpResidual()
{
  return coefficient(_qp) * _coef[_qp] * _grad_test[_i][_qp] * _grad_u[_qp];
}

Real
TensorDiffusion::computeQpJacobian()
{
  return coefficient(_qp) * _coef[_qp] * _grad_test[_i][_qp] * _grad_phi[_j][_qp];
}
