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
  params.addParam<bool>("use_temporal_scaling", true, "Apply the temporal scaling parameter");
  return params;
}

PikaSupersaturation::PikaSupersaturation(const std::string & name, InputParameters parameters) :
    AuxKernel(name, parameters),
    PropertyUserObjectInterface(name, parameters),
    _s(coupledValue("chemical_potential")),
    _rho_i(_property_uo.getParam<Real>("density_ice"))
    _xi(getParam<bool>("use_temporal_scaling") ? _property_uo.temporalScale() : 1.0)
{
}

PikaSupersaturation::~PikaSupersaturation()
{
}

Real
PikaSupersaturation::computeValue()
{
  return -s[_qp] * _rho_i[_qp] * _xi;
}
