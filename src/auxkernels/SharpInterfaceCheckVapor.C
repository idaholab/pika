/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/
#include "SharpInterfaceCheckVapor.h"
template<>
InputParameters validParams<SharpInterfaceCheckVapor>()
{
  InputParameters params = validParams<AuxKernel>();
  return params;
}

SharpInterfaceCheckVapor::SharpInterfaceCheckVapor(const std::string & name, InputParameters parameters) :
    AuxKernel(name, parameters),
    _w(getMaterialProperty<Real>("interface_thickness")),
    _dv(getMaterialProperty<Real>("water_vapor_diffusion_coefficient")),
    _beta(getMaterialProperty<Real>("interface_kinetic_coefficient"))
{}

Real
SharpInterfaceCheckVapor::computeValue()
{
  return _w[_qp] - _dv[_qp] * _beta[_qp];
}

