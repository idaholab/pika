#include "PikaScaledMatDiffusion.h"


template<>
InputParameters validParams<PikaScaledMatDiffusion>()
{
  InputParameters params = validParams<Diffusion>();
  params.addParam<std::string>("diffusivity", "D", "The name of the diffusivity");
  return params;
}

PikaScaledMatDiffusion::PikaScaledMatDiffusion(const std::string & name, InputParameters parameters) :
    Diffusion(name, parameters),
    PropertyUserObjectInterface(name, parameters),
    _D_name(getParam<std::string>("diffusivity")),
    _D(getMaterialProperty<Real>(_D_name)),
    _xi(_property_uo.getParam<Real>("temporal_scaling"))
{}

Real
PikaScaledMatDiffusion::computeQpResidual()
{
  return _xi*_D[_qp] * _grad_test[_i][_qp] * _grad_u[_qp];
}

Real
PikaScaledMatDiffusion::computeQpJacobian()
{
  return _xi* _D[_qp] * _grad_test[_i][_qp] * _grad_phi[_j][_qp];
}
