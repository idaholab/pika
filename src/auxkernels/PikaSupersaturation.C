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

#include "PikaSupersaturation.h"

template<>
InputParameters validParams<PikaSupersaturation>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("phase", "Phase-field variable");
  params.addRequiredCoupledVar("temperature", "The temperature variable");
  params.addParam<bool>("use_temporal_scaling", true, "Apply the temporal scaling parameter");
  params.addParam<bool>("normalize", false, "When true the supersaturation is normalized by the equilibrium concentration");
  return params;
}

PikaSupersaturation::PikaSupersaturation(const InputParameters & parameters) :
    AuxKernel(parameters),
    PropertyUserObjectInterface(parameters),
    _s(coupledValue("chemical_potential")),
    _temperature(coupledValue("temperature")),
    _rho_i(_property_uo.getParam<Real>("density_ice")),
    _xi(getParam<bool>("use_temporal_scaling") ? _property_uo.temporalScale() : 1.0),
    _normalize(getParam<bool>("normalize"))
{
}

PikaSupersaturation::~PikaSupersaturation()
{
}

Real
PikaSupersaturation::computeValue()
{
  Real rho_vs = 1;
  if (_normalize)
    rho_vs = _property_uo.equilibriumWaterVaporConcentrationAtSaturation(_temperature[_qp]);
  return - (_s[_qp] * _rho_i) / rho_vs * _xi;
}
