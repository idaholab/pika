/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "PikaWaterVaporConcentration.h"

template<>
InputParameters validParams<PikaWaterVaporConcentration>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("phase", "Phase-field variable");
  params.addRequiredCoupledVar("chemical_potential", "Chemical potential variable");
  return params;
}

PikaWaterVaporConcentration::PikaWaterVaporConcentration(const std::string & name, InputParameters parameters) :
    AuxKernel(name, parameters),
    PropertyUserObjectInterface(name, parameters),
    _rho_i(getMaterialProperty<Real>("density_ice")),
    _s(coupledValue("chemical_potential"))
{
}

PikaWaterVaporConcentration::~PikaWaterVaporConcentration()
{
}

Real
PikaWaterVaporConcentration::computeValue()
{
  return _s[_qp] * _rho_i[_qp] + _property_uo.equilibriumWaterVaporConcentrationAtSaturation(_property_uo.referenceTemp());
}
