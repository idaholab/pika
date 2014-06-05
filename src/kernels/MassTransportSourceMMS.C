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
    _diffusion_coefficient(getMaterialProperty<Real>(getParam<std::string>("diffusion_coefficient_name"))),
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
  Real K = _diffusion_coefficient[_qp];
  Real Pi = libMesh::pi;
  Real phi = _phi[_qp];

  // Real f = (1/2)*sin(pi*x) * (4*D*exp(phi)*pi*pi*sin(pi*y) + cos(pi*y));



  Real f = 3*K*y*pow(sin(Pi*phi),2)*sin(Pi*x)*Pi*Pi*exp(y*sin(Pi*phi)*cos(Pi*x))*cos(Pi*x)-K*y*y*pow(sin(Pi*phi),3)*pow(sin(Pi*x),3)*Pi*Pi*exp(y*sin(Pi*phi)*cos(Pi*x))+K*exp(y*sin(Pi*phi)*cos(Pi*x))*sin(Pi*phi)*sin(Pi*x)*Pi*pi-K*pow(sin(Pi*phi),3)*pow(cos(Pi*x),2)*exp(y*sin(Pi*phi)*cos(Pi*x))*sin(Pi*x)+(1/2)*sin(Pi*x)*cos(Pi*y);


    return -_test[_i][_qp] * f;
}
