#include "HeatEquationSourceMMS.h"

template<>
InputParameters validParams<HeatEquationSourceMMS>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<std::string>("solid_conductivity_name", "conductivity_ice",  "The name of the solid's material property that contains the conductivity coefficient (Ki)");
  params.addParam<std::string>("gas_conductivity_name", "conductivity_air",  "The name of the gas's material property that contains the conductivity coefficient (Ka)");
  params.addParam<std::string>("solid_heat_capacity_name", "heat_capacity_ice",  "The name of the solid's material property that contains the heat capacity coefficient (Ci)");
  params.addParam<std::string>("gas_heat_capacity_name", "heat_capacity_air",  "The name of the solid's material property that contains the heat capacity coefficient (Ca)");
  params.addParam<std::string>("latent_heat_name", "latent_heat",  "The name of the material property that contains the latent heat coefficient for sublimation (L_sg)");
  params.addRequiredCoupledVar("phi", "Phase-field variable, phi");
  params.addParam<bool>("use_dphi_dt", true, "Include the dphi_dt portion of the forcing function");
  return params;
}

HeatEquationSourceMMS::HeatEquationSourceMMS(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),
    _ki(getMaterialProperty<Real>(getParam<std::string>("solid_conductivity_name"))),
    _ka(getMaterialProperty<Real>(getParam<std::string>("gas_conductivity_name"))),
    _ci(getMaterialProperty<Real>(getParam<std::string>("solid_heat_capacity_name"))),
    _ca(getMaterialProperty<Real>(getParam<std::string>("gas_heat_capacity_name"))),
    _L_sg(getMaterialProperty<Real>(getParam<std::string>("latent_heat_name"))),
    _phi(coupledValue("phi")),
    _use_dphi_dt(getParam<bool>("use_dphi_dt"))
{
}

Real
HeatEquationSourceMMS::computeQpResidual()
{
  using namespace std;

  Real t = _t;
  Real x = _q_point[_qp](0);
  Real y = _q_point[_qp](1);
  Real ki = _ki[_qp];
  Real ka = _ka[_qp];
  Real ci = _ci[_qp];
  Real ca = _ca[_qp];
  Real L_sg = _L_sg[_qp];
  Real pi = libMesh::pi;
  Real phi = _phi[_qp];
  Real xy3 = (x*y)*(x*y)*(x*y);

  Real f =
 
      8.0*pi*pi*t*(0.5*ka*(t*(xy3) + 1.0) + 0.5*ki*(-t*(xy3) + 1.0))*sin(2.0*pi*x)*sin(2.0*pi*y)
      - 2.0*pi*t*((1.5*ka*t*(xy3))/x - (1.5*ki*t*(xy3))/x)*sin(2.0*pi*y)*cos(2.0*pi*x) 
      - 2.0*pi*t*((1.5*ka*t*(xy3))/y - (1.5*ki*t*(xy3))/y)*sin(2.0*pi*x)*cos(2.0*pi*y) 
      + (0.5*ca*(t*(xy3) + 1.0) + 0.5*ci*(-t*(xy3) + 1.0))*sin(2.0*pi*x)*sin(2.0*pi*y); 
     
  if (_use_dphi_dt)
    f += -0.5*L_sg*(x*y)*(x*y)*(x*y);
 // cout<<t<<" "<<x<<" "<<y<<" "<< phi << endl;
  return -_test[_i][_qp] * f;
}
