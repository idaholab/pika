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
  params.addParam<Real>("vis_albedo", 0.94, "Short-wave radiation albedo in visible (VIS) wavelengths (300-800 nm)");
  params.addParam<Real>("nir_albedo", 0.80, "Short-wave radiation albedo in near-infrared (NIR) wavelengths (800-1500 nm)");
  params.addParam<Real>("swir_albedo", 0.59, "Short-wave radiation albedo in short-wave infrared (SWIR) wavelengths (1500-2800 nm)");
  params.addParam<Real>("extinction", 100, "Extinction coefficient [1/m]");

  MooseEnum direction("x=0, y=1, z=2", "y");
  params.addParam<MooseEnum>("direction", direction, "Direction to apply the extinction function");
  return params;
}

IbexShortwaveForcingFunction::IbexShortwaveForcingFunction(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),
    _short_wave(getFunction("short_wave")),
    _extinction(getParam<Real>("extinction")),
    _vis_albedo(getParam<Real>("vis_albedo")),
    _nir_albedo(getParam<Real>("nir_albedo")),
    _swir_albedo(getParam<Real>("swir_albedo")),
    _direction(getParam<MooseEnum>("direction"))
{
  _direction_vector(_direction) = 1;
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
IbexShortwaveForcingFunction::computeQpResidual()
{
  Real sw_in = _short_wave.value(_t, _q_point[_qp]);
  Real sw_vis = 0.545 * sw_in * (1 - _vis_albedo);
  Real sw_nir = 0.274 * sw_in * (1 - _nir_albedo);
  Real sw_swir = 0.087 * sw_in * (1 - _swir_albedo);
  Real q_sw = (sw_vis + sw_nir + sw_swir) * (1 - std::exp(-_extinction * (_surface - _q_point[_qp](_direction))));
  return -_grad_test[_i][_qp] * q_sw * _direction_vector;
}
