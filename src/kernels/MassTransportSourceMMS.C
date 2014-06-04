#include "MassTransportSourceMMS.h"

template<>
InputParameters validParams<MassTransportSourceMMS>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<std::string>("diffusion_coefficient_name", "diffusion_coefficient",  "The name of the material property that contains the water vapor diffusion coefficient (D_v)");
  return params;
}

MassTransportSourceMMS::MassTransportSourceMMS(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),
    _diffusion_coefficient(getMaterialProperty<Real>(getParam<std::string>("diffusion_coefficient_name")))

{
}

Real
MassTransportSourceMMS::computeQpResidual()
{
  Real t = _t;
  Real x = _q_point[_qp](0);
  Real y = _q_point[_qp](1);
  Real D_v = _diffusion_coefficient[_qp];
  Real pi = libMesh::pi;

  return - std::exp(t) * std::sin(pi*x) * std::sin(pi*y) +
    (1/2) * D_v * t * std::pow(std::cos(pi*x),2) * pi*pi * std::pow(std::sin(pi*y),2) * std::exp(t) +
    2 * D_v * (1/2-(1/2) * t * std::sin(pi*x) * std::sin(pi*y)) * std::exp(t)*std::sin(pi*x) * pi*pi * std::sin(pi*y) +
  (1/2) * D_v * t * std::pow(std::sin(pi*x),2) * std::pow(std::cos(pi*y),2) * pi*pi * std::exp(t) +
    (1/2)*std::sin(pi*x)*std::sin(pi*y);
}
