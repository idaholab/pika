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

#include "PikaPhaseTimestepPostprocessor.h"

#include <algorithm>
#include <limits>

template<>
InputParameters validParams<PikaPhaseTimestepPostprocessor>()
{
  // Define the parameters
  InputParameters params = validParams<NodalVariablePostprocessor>();
  std::vector<Real> vec(2);
  vec[0] = -1;
  vec[1] = 1;
  params.addParam<std::vector<Real> >("range", vec, "Lower and upper limit of the variable to interrogate");
  params.addParam<Real>("decrease_limit", 1e-4, "If the phase-field parameter gets out-of-range by this amount, the time step is cut back");
  params.addParam<Real>("decrease_factor", 0.5, "The amount the timestep is to be cut back");
  params.addParam<Real>("increase_limit", 1e-5, "If the phase-field parameter within range by this amount, the time step is increased");
  params.addParam<Real>("increase_factor", 1.5, "The amount the timestep is to be increased back");

  return params;
}

PikaPhaseTimestepPostprocessor::PikaPhaseTimestepPostprocessor(const InputParameters & parameters) :
  NodalVariablePostprocessor(parameters),
  _range(getParam<std::vector<Real> >("range")),
  _decrease_limit(getParam<Real>("decrease_limit")),
  _increase_limit(getParam<Real>("increase_limit")),
  _decrease_factor(getParam<Real>("decrease_factor")),
  _increase_factor(getParam<Real>("increase_factor"))
{}

void
PikaPhaseTimestepPostprocessor::initialize()
{
  _max_value = -std::numeric_limits<Real>::max(); // start w/ the min
  _min_value = std::numeric_limits<Real>::max(); // start w/ the max
}

void
PikaPhaseTimestepPostprocessor::execute()
{
  _max_value = std::max(_max_value, _u[_qp]);
  _min_value = std::min(_min_value, _u[_qp]);

}

Real
PikaPhaseTimestepPostprocessor::getValue()
{
  gatherMax(_max_value);
  gatherMin(_min_value);

  // Cut-back
  if (std::abs(_min_value) - std::abs(_range[0]) > _decrease_limit)
    return _dt * _decrease_factor;
  else if (std::abs(_max_value) - std::abs(_range[1]) > _decrease_limit)
    return _dt * _decrease_factor;
  else if (std::abs(_min_value) - std::abs(_range[0]) < _increase_limit)
    return _dt * _increase_factor;
  else if (std::abs(_max_value) - std::abs(_range[1]) < _increase_limit)
    return _dt * _increase_factor;

  return _dt;
}

void
PikaPhaseTimestepPostprocessor::threadJoin(const UserObject & y)
{
  const PikaPhaseTimestepPostprocessor & pps = static_cast<const PikaPhaseTimestepPostprocessor &>(y);
  _min_value = std::max(_min_value, pps._min_value);
  _max_value = std::min(_max_value, pps._max_value);
}
