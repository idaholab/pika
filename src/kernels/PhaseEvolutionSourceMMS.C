#include "PhaseEvolutionSourceMMS.h"
#include "ChemicalPotentialPropertyUserObject.h"
template<>
InputParameters validParams<PhaseEvolutionSourceMMS>()
{
  InputParameters params = validParams<Kernel>();
  params += validParams<ChemicalPotentialInterface>();
  return params;
}

PhaseEvolutionSourceMMS::PhaseEvolutionSourceMMS(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),
    ChemicalPotentialInterface(getUserObject<ChemicalPotentialPropertyUserObject>("property_user_object")),
    _tau(getMaterialProperty<Real>(getParam<std::string>("relaxation_time"))),
    _w(getMaterialProperty<Real>(getParam<std::string>("interface_thickness"))),
    _lambda(getMaterialProperty<Real>(getParam<std::string>("phase_coupling_constant"))),
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
  Real tau = _tau[_qp];
  Real w = _w[_qp];
  Real lambda = _lambda[_qp];
  Real R_da = _R_da[_qp];
  Real R_v = _R_v[_qp];
  Real P_a = _P_a[_qp];

  Real rho_a = _rho_a[_qp];
  Real rho_i = _rho_i[_qp];

  Real pi = libMesh::pi;

  Real f = -lambda*pow(-pow(t, 2)*pow(sin(4.0*M_PI*x), 2)*pow(sin(4.0*M_PI*y), 2) + 1.0, 2.0)*(sin(4*x*y) - (110379418992.988*R_da*rho_a*pow(x*y, 0.6918651)*exp(-58.653696*1.0/(x*y) + 1.3749042*pow(x*y, 1.0) - 0.34031775*pow(x*y, 2.0) + 0.026967687*pow(x*y, 3.0))/(R_v*(P_a - 110379418992.988*pow(x*y, 0.6918651)*exp(-58.653696*1.0/(x*y) + 1.3749042*pow(x*y, 1.0) - 0.34031775*pow(x*y, 2.0) + 0.026967687*pow(x*y, 3.0)))) - 5.4296946499373*pow(263, 0.6918651)*R_da*rho_a/(R_v*(P_a - 5.4296946499373*pow(263, 0.6918651))))/rho_i) + pow(t, 3)*pow(sin(4.0*M_PI*x), 3)*pow(sin(4.0*M_PI*y), 3) + 32.0*pow(M_PI, 2)*t*pow(w, 2.0)*sin(4.0*M_PI*x)*sin(4.0*M_PI*y) - t*sin(4.0*M_PI*x)*sin(4.0*M_PI*y) + tau*sin(4.0*M_PI*x)*sin(4.0*M_PI*y);
  return -_test[_i][_qp] * f;
}
