/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/
#include "SharpInterfaceCheckIce.h"
template<>
InputParameters validParams<SharpInterfaceCheckIce>()
{
  InputParameters params = validParams<AuxKernel>();
  return params;
}

SharpInterfaceCheckIce::SharpInterfaceCheckIce(const std::string & name, InputParameters parameters) :
    AuxKernel(name, parameters),
    _w(getMaterialProperty<Real>("interface_thickness")),
    _ki(getMaterialProperty<Real>("conductivity_ice")),
    _ci(getMaterialProperty<Real>("heat_capacity_ice")),
    _beta(getMaterialProperty<Real>("interface_kinetic_coefficient"))
{}

Real
SharpInterfaceCheckIce::computeValue()
{
  return _w[_qp] - ( _ki[_qp] / _ci[_qp] ) * _beta[_qp];
}

