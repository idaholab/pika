#include "PhaseFieldPotential.h"

template<>
InputParameters validParams<PhaseFieldPotential>()
{
  InputParameters params = validParams<ACBulk>();
 return params;
}

PhaseFieldPotential::PhaseFieldPotential(const std::string & name, InputParameters parameters) :
    ACBulk(name, parameters)
{
}

Real
PhaseFieldPotential::computeDFDOP(PFFunctionType type)
{
  switch (type)
  {
  case Residual:
    return _u[_qp]*_u[_qp]*_u[_qp] - _u[_qp] ;

  case Jacobian:
    return _phi[_j][_qp]*(3*_u[_qp]*_u[_qp] - 1. );
  }
}
