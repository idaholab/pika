#include "MassTransportSourceMMS.h"

template<>
InputParameters validParams<MassTransportSourceMMS>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<std::string>("water_vapor_diffusion_coefficient_name", "water_vapor_diffusion_coefficient",  "The name of the material property that contains the water vapor diffusion coefficient (D_v)");
  params.addRequiredCoupledVar("phi", "Phase-field variable, phi");
  params.addParam<bool>("use_dphi_dt", true, "Include the dphi_dt portion of the forcing function");
  return params;
}

MassTransportSourceMMS::MassTransportSourceMMS(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),
    _D_v(getMaterialProperty<Real>(getParam<std::string>("water_vapor_diffusion_coefficient_name"))),
    _phi(coupledValue("phi")),
    _use_dphi_dt(getParam<bool>("use_dphi_dt"))
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

  Real f = sin(2.*Pi*x)*cos(2.*Pi*y)
    + D_v*t*t*y*cos(2.*Pi*x)*Pi*cos(2.*Pi*y)
    + 8.*D_v*(0.5-0.5*t*x*y)*t*sin(2.*Pi*x)*Pi*Pi*cos(2.*Pi*y)
    - D_v*t*t*sin(2.*Pi*x)*sin(2.*Pi*y)*Pi;

  if (_use_dphi_dt)
    f += 0.5*x*y;

  return -_test[_i][_qp] * f;
}
