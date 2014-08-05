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
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredParam<FunctionName>("short_wave", "The function computing the incoming short-wave radiation [W/m^2]");
  params.addParam<Real>("albedo", 0.95, "Short-wave radiation albedo");
  params.addParam<Real>("extinction", 100, "Extinction coefficient [1/m]");
  params.addParam<int>("direction", 1, "Direction to apply the extinction function");
  return params;
}

IbexShortwaveForcingFunction::IbexShortwaveForcingFunction(const std::string & name, InputParameters parameters) :
    AuxKernel(name, parameters),
    _short_wave(getFunction("short_wave")),
    _extinction(getParam<Real>("extinction")),
    _albedo(getParam<Real>("albedo")),
    _direction(getParam<int>("direction"))
{
}

void
IbexShortwaveForcingFunction::initialSetup()
{
  if (_direction == 0)
    _surface = _mesh.getParam<Real>("xmax");
  else if (_direction == 1)
    _surface = _mesh.getParam<Real>("ymax");
  else if (_direction == 2)
    _surface = _mesh.getParam<Real>("zmax");
  else
    mooseError("Invalid direction supplied (" << _direction << "), must be 1, 2, or 3");
}


Real
IbexShortwaveForcingFunction::computeValue()
{
  Real sw = _short_wave.value(_t, _q_point[_qp]) * (1 - _albedo);
  return sw * exp(-_extinction * (_surface - _q_point[_qp](_direction)));
}
