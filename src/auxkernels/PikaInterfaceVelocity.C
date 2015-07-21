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

#include "PikaInterfaceVelocity.h"

template<>
InputParameters validParams<PikaInterfaceVelocity>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("phase", "Phase-field variable");
  params.addRequiredCoupledVar("chemical_potential", "Chemical potential variable");
  return params;
}

PikaInterfaceVelocity::PikaInterfaceVelocity(const InputParameters & parameters) :
    AuxKernel(parameters),
    PropertyUserObjectInterface(parameters),
    _D_v(_property_uo.getParam<Real>("water_vapor_diffusion_coefficient")),
    _grad_phase(coupledGradient("phase")),
    _grad_s(coupledGradient("chemical_potential"))
{
}

PikaInterfaceVelocity::~PikaInterfaceVelocity()
{
}

Real
PikaInterfaceVelocity::computeValue()
{
  // Compute the normal vector
  RealGradient n = _grad_phase[_qp] / _grad_phase[_qp].size();

  // Return the velocity (Eq. 23)
  return _D_v * n * _grad_s[_qp];
}
