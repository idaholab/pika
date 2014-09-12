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
#include "SharpInterfaceCheckAir.h"
template<>
InputParameters validParams<SharpInterfaceCheckAir>()
{
  InputParameters params = validParams<AuxKernel>();
  return params;
}

SharpInterfaceCheckAir::SharpInterfaceCheckAir(const std::string & name, InputParameters parameters) :
    AuxKernel(name, parameters),
    _w(getMaterialProperty<Real>("interface_thickness")),
    _ka(getMaterialProperty<Real>("conductivity_air")),
    _ca(getMaterialProperty<Real>("heat_capacity_air")),
    _beta(getMaterialProperty<Real>("interface_kinetic_coefficient"))
{}

Real
SharpInterfaceCheckAir::computeValue()
{
  return _w[_qp] - ( _ka[_qp] / _ca[_qp] ) * _beta[_qp];
}

