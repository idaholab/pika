#include "PhaseEvolutionSourceMMS.h"
#include "ChemicalPotentialPropertyUserObject.h"
template<>
InputParameters validParams<PhaseEvolutionSourceMMS>()
{
  InputParameters params = validParams<Kernel>();
  params += validParams<ChemicalPotentialInterface>();
/*
  params.addParam<std::string>("relaxation_time", "tau",  "Relaxation coefficient on dPhi/dt in phase evolution equation [tau]");
  params.addParam<std::string>("interface_thickness", "w",  " Material property specifying the thickness between phases [w]");
  params.addParam<std::string>("lambda", "lambda",  " Material property specifying the phase field's coupling with chemical potential [lambda]");
  params.addParam<std::string>("solid_density", "density_ice",  " Material property specifying the density of the solid phase [rho_i]");
  params.addParam<std::string>("gas_density", "density_vapor",  " Material property specifying the density of the gas phase [rho_a]");
*/
  return params;
}

PhaseEvolutionSourceMMS::PhaseEvolutionSourceMMS(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),
    ChemicalPotentialInterface(getUserObject<ChemicalPotentialPropertyUserObject>("property_user_object")),
    _tau(getMaterialProperty<Real>("tau")),
    _w(getMaterialProperty<Real>("interface_thickness")),
    _lambda(getMaterialProperty<Real>("lambda")),
    _rho_i(getMaterialProperty<Real>("density_ice")),
    _rho_a(getMaterialProperty<Real>("density_air")),
    _R_da(getMaterialProperty<Real>("gas_constant_dry_air")),
    _R_v(getMaterialProperty<Real>("gas_constant_water_vapor")),
    _P_a(getMaterialProperty<Real>("atmospheric_pressure"))

{
}

Real
PhaseEvolutionSourceMMS::computeQpResidual()
{
  using namespace std;
  Real t = _t;
  Real x = _q_point[_qp](0);
  Real y = _q_point[_qp](1);
  Real tau = 1.0; //_tau[_qp];
  Real w = _w[_qp];
  Real lambda = _lambda[_qp];
  Real R_da = _R_da[_qp];
  Real R_v = _R_v[_qp];
  Real P_a = _P_a[_qp];

  Real rho_a = _rho_a[_qp];
  Real rho_i = _rho_i[_qp];

  Real pi = libMesh::pi;
  Real f = -lambda*pow(-pow(t, 2)*pow(sin(4.0*pi*x), 2)*pow(sin(4.0*pi*y), 2) + 1.0, 2.0)*(sin(4*x*y) - (4562027550.87433*R_da*rho_a*pow(-10*x*y + 273, 0.6918651)*exp(-5865.3696*1.0/(-10*x*y + 273) + 0.013749042*pow(-10*x*y + 273, 1.0) - 3.4031775e-5*pow(-10*x*y + 273, 2.0) + 2.6967687e-8*pow(-10*x*y + 273, 3.0))/(R_v*(P_a - 4562027550.87433*pow(-10*x*y + 273, 0.6918651)*exp(-5865.3696*1.0/(-10*x*y + 273) + 0.013749042*pow(-10*x*y + 273, 1.0) - 3.4031775e-5*pow(-10*x*y + 273, 2.0) + 2.6967687e-8*pow(-10*x*y + 273, 3.0)))) - 5.4296946499373*pow(263, 0.6918651)*R_da*rho_a/(R_v*(P_a - 5.4296946499373*pow(263, 0.6918651))))/rho_i) + pow(t, 3)*pow(sin(4.0*pi*x), 3)*pow(sin(4.0*pi*y), 3) + 32.0*pow(pi, 2)*t*pow(w, 2.0)*sin(4.0*pi*x)*sin(4.0*pi*y) - t*sin(4.0*pi*x)*sin(4.0*pi*y) + tau*sin(4.0*pi*x)*sin(4.0*pi*y);
  return -_test[_i][_qp] * f;
}
