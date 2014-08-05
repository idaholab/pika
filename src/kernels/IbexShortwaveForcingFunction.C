/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "IbexShortwaveForcingFunction.h"
#include "Function.h"

template<>
InputParameters validParams<IbexShortwaveForcingFunction>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<FunctionName>("short_wave", "The function computing the incoming short-wave radiation [W/m^2]");
  params.addParam<Real>("albedo", 0.95, "Short-wave radiation albedo");
  params.addParam<Real>("extinction", 100, "Extinction coefficient [1/m]");
  return params;
}

IbexShortwaveForcingFunction::IbexShortwaveForcingFunction(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),
    _short_wave(getFunction("short_wave")),
    _extinction(getParam<Real>("extinction")),
    _albedo(getParam<Real>("albedo"))
{
}

Real
IbexShortwaveForcingFunction::computeQpResidual()
{
#if LIBMESH_DIM == 1
  Real z = _q_point[_qp](0);
#elif LIBMESH_DIM == 2
  Real z = _q_point[_qp](1);
#else
  Real z = _q_point[_qp](2);
#endif
  Real sw = _short_wave.value(_t, _q_point[_qp]) * (1 - _albedo);
  return -_test[_i][_qp] * sw * exp(-_extinction * z);
}
