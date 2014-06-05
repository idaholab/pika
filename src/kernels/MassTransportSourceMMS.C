#include "MassTransportSourceMMS.h"

template<>
InputParameters validParams<MassTransportSourceMMS>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<std::string>("diffusion_coefficient_name", "diffusion_coefficient",  "The name of the material property that contains the water vapor diffusion coefficient (D_v)");
  params.addRequiredCoupledVar("phi", "Phase-field variable, phi");
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
  using namespace std;

  Real t = _t;
  Real x = _q_point[_qp](0);
  Real y = _q_point[_qp](1);
  Real D= _diffusion_coefficient[_qp];
  Real pi = libMesh::pi;

  Real f = exp(t) * sin(pi*x) * sin(pi*y)
    + 2 * D * exp(t) * sin(pi*x) * pow(pi,2) * sin(pi*y)
    + (1/2) * sin(pi*x) * cos(pi*y);
  return -f;
}
