#include "MassTransportSourceMMS.h"

template<>
InputParameters validParams<MassTransportSourceMMS>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<std::string>("water_vapor_diffusion_coefficient_name", "water_vapor_diffusion_coefficient",  "The name of the material property that contains the water vapor diffusion coefficient (D_v)");
  params.addRequiredCoupledVar("phi", "Phase-field variable, phi");
  return params;
}

MassTransportSourceMMS::MassTransportSourceMMS(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),
    _D_v(getMaterialProperty<Real>(getParam<std::string>("water_vapor_diffusion_coefficient_name"))),
    _phi(coupledValue("phi"))
{
}

Real
MassTransportSourceMMS::computeQpResidual()
{
  using namespace std;

  Real t = _t;
  Real x = _q_point[_qp](0);
  Real y = _q_point[_qp](1);
  Real D_v = _D_v[_qp];
  Real Pi = libMesh::pi;
  Real phi = _phi[_qp];

  Real f = sin(2*Pi*x)*cos(2*Pi*y)
    + D_v*t*t*cos(2*Pi*x)*Pi*cos(2*Pi*y)
    + 8*D_v*(1/2-(1/2)*t*x)*t*sin(2*Pi*x)*Pi*Pi*cos(2*Pi*y);
  return -_test[_i][_qp] * f;
}
