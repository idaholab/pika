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

#include "PikaPhaseInitializeAux.h"

template<>
InputParameters validParams<PikaPhaseInitializeAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("phase", "Phase-field variable to limit");
  params.addParam<Real>("upper_limit", 1, "Upper limit of phase-field variable");
  params.addParam<Real>("lower_limit", -1, "Lower limit of phase-field variable");
  return params;
}

PikaPhaseInitializeAux::PikaPhaseInitializeAux(const InputParameters & parameters) :
    AuxKernel(parameters),
    _phase(coupledValue("phase")),
    _upper(getParam<Real>("upper_limit")),
    _lower(getParam<Real>("lower_limit"))
{
}

Real
PikaPhaseInitializeAux::computeValue()
{
  // Return the upper limit
  if (_phase[_qp] > _upper)
    return _upper;

  // Return the lower limit
  else if (_phase[_qp] < _lower)
    return _lower;

  // Do nothing
  else
    return _phase[_qp];
}
