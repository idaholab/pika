/**********************************************************************************/
/*                  Pika: Phase field snow micro-structure model                  */
/*                                                                                */
/*                     (C) 2014 Battelle Energy Alliance, LLC                     */
/*                              ALL RIGHTS RESERVED                               */
/*                                                                                */
/*                   Prepared by Battelle Energy Alliance, LLC                    */
/*                      Under Contract No. DE-AC07-05ID14517                      */
/*                      With the U. S. Department of Energy                       */
/**********************************************************************************/

#include "IbexShortwaveForcingFunction.h"
#include "Function.h"
#include "MooseMesh.h"

registerMooseObject("PikaApp", IbexShortwaveForcingFunction);

template<>
InputParameters validParams<IbexShortwaveForcingFunction>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<FunctionName>("short_wave", "The function computing the incoming short-wave radiation [W/m^2]");
  params.addParam<Real>("vis_albedo", 0.94, "Short-wave radiation albedo in visible (VIS) wavelengths (300-800 nm)");
  params.addParam<Real>("nir_albedo", 0.80, "Short-wave radiation albedo in near-infrared (NIR) wavelengths (800-1500 nm)");
  params.addParam<Real>("vis_extinction", 40, "Extinction coefficient in visible (VIS) wavelengths (300-800 nm) [1/m]");
  params.addParam<Real>("nir_extinction", 110, "Extinction coefficient in near-infrared (NIR) wavelenghts (800-1500 nm) [1/m]");

  MooseEnum direction("x=0 y=1 z=2", "y");
  params.addParam<MooseEnum>("direction", direction, "Direction to apply the extinction function");
  return params;
}

IbexShortwaveForcingFunction::IbexShortwaveForcingFunction(const InputParameters & parameters) :
    Kernel(parameters),
    _short_wave(getFunction("short_wave")),
    _vis_extinction(getParam<Real>("vis_extinction")),
    _nir_extinction(getParam<Real>("nir_extinction")),
    _vis_albedo(getParam<Real>("vis_albedo")),
    _nir_albedo(getParam<Real>("nir_albedo")),
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
    mooseError("Invalid direction supplied (", _direction, "), must be 1, 2, or 3");
}


Real
IbexShortwaveForcingFunction::computeQpResidual()
{
  Real sw_in = _short_wave.value(_t, _q_point[_qp]);
  Real q_vis = 0.545 * sw_in * (1 - _vis_albedo) * (1 - std::exp(-_vis_extinction * (_surface - _q_point[_qp](_direction))));
  Real q_nir = 0.274 * sw_in * (1 - _nir_albedo) * (1 - std::exp(-_nir_extinction * (_surface - _q_point[_qp](_direction))));
  return -_grad_test[_i][_qp] * (q_vis + q_nir) * _direction_vector;
}
