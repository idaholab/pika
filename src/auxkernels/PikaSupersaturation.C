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
  params.addRequiredCoupledVar("chemical_potential", "Chemical potential variable");
  return params;
}

PikaSupersaturation::PikaSupersaturation(const std::string & name, InputParameters parameters) :
    AuxKernel(name, parameters),
    PropertyUserObjectInterface(name, parameters),
    _rho_i(getMaterialProperty<Real>("density_ice")),
    _rho_vs(getMaterialProperty<Real>("equilibrium_water_vapor_concentration_at_saturation")),
    _phase(coupledValue("phase")),
    _s(coupledValue("chemical_potential"))
{
}

PikaSupersaturation::~PikaSupersaturation()
{
}

Real
PikaSupersaturation::computeValue()
{
  Real rho_eq = _rho_i[_qp] * (1 + _phase[_qp])/2 + _rho_vs[_qp] * (1 - _phase[_qp])/2;
  Real rho = _s[_qp] * _rho_i[_qp] + _property_uo.equilibriumWaterVaporConcentrationAtSaturation(_property_uo.referenceTemp());
  return rho_eq - rho;

}
