#include "PikaDoubleWellPotential.h"

// Algebraic double well potential.

template<>
InputParameters validParams<PikaDoubleWellPotential>()
{
  InputParameters params = validParams<KernelValue>();
  params.addParam<std::string>("mob_name", "L", "The mobility used with the kernel");

  return params;
}

PikaDoubleWellPotential::PikaDoubleWellPotential(const std::string & name, InputParameters parameters) :
    ACBulk( name, parameters )
{
}

Real
PikaDoubleWellPotential::computeQpResidual()
{
      return (_u[_qp]*_u[_qp]*_u[_qp] - _u[_qp])*_test[_i][_qp] ;
}
