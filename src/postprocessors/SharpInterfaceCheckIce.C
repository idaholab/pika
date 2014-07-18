/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "SharpInterfaceCheckIce.h"

template<>
InputParameters validParams<SharpInterfaceCheck>()
{
  InputParameters params = validParams<AuxKernel>();
  return params;
}

SharpInterfaceCheck::SharpInterfaceCheck(const std::string & name, InputParameters parameters) :
    AuxKernel(name, parameters),
    _w(getMaterialProperty<Real>("interface_thickness")),
    _ki(getMaterialProperty<Real>("conductivity_ice")),
    _ci(getMaterialProperty<Real>("heat_capacity_ice")),
    _beta(getMaterialProperty<Real>("beta")),
{}

void SharpInterfaceCheck::computeValue()
{
  return _w - ( _ki / _ci ) * _beta;
}

