/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "PikaSupersaturation.h"

template<>
InputParameters validParams<PikaSupersaturation>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("chemical_potential", "Chemical potential variable");
  return params;
}

PikaSupersaturation::PikaSupersaturation(const std::string & name, InputParameters parameters) :
    AuxKernel(name, parameters),
    PropertyUserObjectInterface(name, parameters),
    _s(coupledValue("chemical_potential")),
    _rho_i(_property_uo.getParam<Real>("density_ice"))
{
}

PikaSupersaturation::~PikaSupersaturation()
{
}

Real
PikaSupersaturation::computeValue()
{
  return _s[_qp] * _rho_i;
}
