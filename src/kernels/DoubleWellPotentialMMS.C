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

#include "DoubleWellPotentialMMS.h"

registerMooseObject("PikaApp", DoubleWellPotentialMMS);

template<>
InputParameters validParams<DoubleWellPotentialMMS>()
{
  InputParameters params = validParams<Kernel>();
  return params;
}

DoubleWellPotentialMMS::DoubleWellPotentialMMS(const InputParameters & parameters) :
    Kernel(parameters)
{
}

Real
DoubleWellPotentialMMS::computeQpResidual()
{
  Real t = _t;
  Real x = _q_point[_qp](0);
  Real y = _q_point[_qp](1);
  Real f =
    -t*(pow(x - 0.5, 2) + pow(y - 0.5, 2) - 0.125) + pow(t*(pow(x - 0.5, 2) + pow(y - 0.5, 2) - 0.125), 3.0);
  return -_test[_i][_qp] * f;
}
