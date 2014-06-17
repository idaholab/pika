#include "PhaseEvolutionSourceMMS.h"
#include "PropertyUserObject.h"
template<>
InputParameters validParams<PhaseEvolutionSourceMMS>()
{
  InputParameters params = validParams<Kernel>();
  params += validParams<PropertyUserObjectInterface>();
  params.addParam<bool>("use_potential_transition",false, "Include term proportional to lambda in Eq.(33)");
  return params;
}

PhaseEvolutionSourceMMS::PhaseEvolutionSourceMMS(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),
    PropertyUserObjectInterface(name, parameters),
    _tau(getMaterialProperty<Real>("tau")),
    _w(getMaterialProperty<Real>("interface_thickness")),
    _lambda(getMaterialProperty<Real>("lambda")),
    _rho_i(getMaterialProperty<Real>("density_ice")),
    _rho_a(getMaterialProperty<Real>("density_air")),
    _R_da(getMaterialProperty<Real>("gas_constant_dry_air")),
    _R_v(getMaterialProperty<Real>("gas_constant_water_vapor")),
    _P_a(getMaterialProperty<Real>("atmospheric_pressure")),
    _use_potential_transition(getParam<bool>("use_potential_transition"))
{
}

Real
PhaseEvolutionSourceMMS::computeQpResidual()
{
  using namespace std;
  Real t = _t;
  Real x = _q_point[_qp](0);
  Real y = _q_point[_qp](1);
  Real tau = _tau[_qp];
  Real w = _w[_qp];
  Real lambda = _lambda[_qp];
  Real R_da = _R_da[_qp];
  Real R_v = _R_v[_qp];
  Real P_a = _P_a[_qp];
  Real rho_a = _rho_a[_qp];
  Real rho_i = _rho_i[_qp];
  Real pi = libMesh::pi;
  Real f = 
 32.0*pow(pi, 2.0)*t*pow(w, 2.0)*sin(4.0*pi*x)*sin(4.0*pi*y) + tau*sin(4.0*pi*x)*sin(4.0*pi*y);

  if(_use_potential_transition)
    f+=lambda*pow(-pow(t, 2.0)*pow(sin(4.0*pi*x), 2.0)*pow(sin(4.0*pi*y), 2.0) + 1.0, 2.0)*(0.5*sin(4.0*x*y) - (4562027550.87433*R_da*rho_a*pow(-10.0*x*y + 273.0, 0.6918651)*exp(-5865.3696*1.0/(-10.0*x*y + 273) + 0.013749042*pow(-10.0*x*y + 273.0, 1.0) - 3.4031775e-5*pow(-10.0*x*y + 273.0, 2.0) + 2.6967687e-8*pow(-10.0*x*y + 273.0, 3.0))/(R_v*(P_a - 4562027550.87433*pow(-10.0*x*y + 273.0, 0.6918651)*exp(-5865.3696*1.0/(-10.0*x*y + 273) + 0.013749042*pow(-10.0*x*y + 273.0, 1.0) - 3.4031775e-5*pow(-10.0*x*y + 273.0, 2.0) + 2.6967687e-8*pow(-10.0*x*y + 273.0, 3.0)))) - 5.4296946499373*pow(263.0, 0.6918651)*R_da*rho_a/(R_v*(P_a - 5.4296946499373*pow(263.0, 0.6918651))))/rho_i); 

  return -_test[_i][_qp] * f;
}
