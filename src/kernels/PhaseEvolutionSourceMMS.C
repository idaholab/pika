#include "PhaseEvolutionSourceMMS.h"
#include "PropertyUserObject.h"
template<>
InputParameters validParams<PhaseEvolutionSourceMMS>()
{
  InputParameters params = validParams<Kernel>();
  params += validParams<PropertyUserObjectInterface>();
  params.addParam<bool>("use_potential_transition",false, "Include term proportional to lambda in Eq.(33)");
  params.addRequiredCoupledVar("temperature","temperature specifying vapor density, T) ");
  params.addRequiredCoupledVar("chemical_potential","vapor concentration, u) ");
  return params;
}

PhaseEvolutionSourceMMS::PhaseEvolutionSourceMMS(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),
    PropertyUserObjectInterface(name, parameters),
    _tau(getMaterialProperty<Real>("tau")),
    _w(getMaterialProperty<Real>("interface_thickness")),
    _lambda(getMaterialProperty<Real>("lambda")),
    _use_potential_transition(getParam<bool>("use_potential_transition")),
    _T(coupledValue("temperature")),
    _u(coupledValue("chemical_potential"))


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
  Real u_eq =_property_uo.equilibriumConcentration( _T[_qp]);
  Real f = 
    -4*t*pow(w, 2.0) - t*(pow(x - 0.5, 2) + pow(y - 0.5, 2) - 0.125) + tau*(pow(x - 0.5, 2) + pow(y - 0.5, 2) - 0.125) + pow(t*(pow(x - 0.5, 2) + pow(y - 0.5, 2) - 0.125), 3.0);

  if(_use_potential_transition)
    f+=
       -lambda*(_u[_qp] - u_eq)*pow(-pow(t, 2)*pow(pow(x - 0.5, 2) + pow(y - 0.5, 2) - 0.125, 2) + 1.0, 2.0);
  return -_test[_i][_qp] * f;
}
