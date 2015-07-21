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

#include "PikaWaterVaporConcentration.h"

template<>
InputParameters validParams<PikaWaterVaporConcentration>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("phase", "Phase-field variable");
  params.addRequiredCoupledVar("chemical_potential", "Chemical potential variable");
  return params;
}

PikaWaterVaporConcentration::PikaWaterVaporConcentration(const InputParameters & parameters) :
    AuxKernel(parameters),
    PropertyUserObjectInterface(parameters),
    _s(coupledValue("chemical_potential")),
    _rho_i(_property_uo.getParam<Real>("density_ice")),
    _T_0(_property_uo.getParam<Real>("reference_temperature"))
{
}

PikaWaterVaporConcentration::~PikaWaterVaporConcentration()
{
}

Real
PikaWaterVaporConcentration::computeValue()
{
  // Eq. 21
  return _s[_qp] * _rho_i + _property_uo.equilibriumWaterVaporConcentrationAtSaturation(_T_0);
}
