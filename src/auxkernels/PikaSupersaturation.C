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
  params.addRequiredCoupledVar("phase", "Phase-field variable");
  params.addParam<bool>("use_temporal_scaling", true, "Apply the temporal scaling parameter");
  return params;
}

PikaSupersaturation::PikaSupersaturation(const std::string & name, InputParameters parameters) :
    AuxKernel(name, parameters),
    PropertyUserObjectInterface(name, parameters),
    _rho_i(getMaterialProperty<Real>("density_ice")),
    _s(coupledValue("chemical_potential")),
    _xi(getParam<bool>("use_temporal_scaling") ? _property_uo.temporalScale() : 1.0)
{
}

PikaSupersaturation::~PikaSupersaturation()
{
}

Real
PikaSupersaturation::computeValue()
{
  return -_s[_qp] * _rho_i[_qp] * _xi;
}
