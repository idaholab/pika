#include "DoubleWellPotentialMMS.h"

template<>
InputParameters validParams<DoubleWellPotentialMMS>()
{
  InputParameters params = validParams<Kernel>();
  return params;
}

DoubleWellPotentialMMS::DoubleWellPotentialMMS(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters)
{
}

Real
DoubleWellPotentialMMS::computeQpResidual()
{
  Real t = _t;
  Real x = _q_point[_qp](0);
  Real y = _q_point[_qp](1);
  Real f = 
    -t*sin(4.0*pi*x)*sin(4.0*pi*y) + pow(t*sin(4.0*pi*x)*sin(4.0*pi*y), 3.0);
  return -_test[_i][_qp] * f;
}
