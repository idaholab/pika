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

#include "Val2Var.h"

template<>
InputParameters validParams<Val2Var>()
{
  InputParameters params = validParams<Function>();
  params.addRequiredParam<Real>("x1", "Input least X over which new phi will be applied");
  params.addRequiredParam<Real>("x2", "Input greatest X  over which new phi will be applied");
  params.addRequiredParam<Real>("x3", "Input least X over 2nd interval which new phi will be applied");
  params.addRequiredParam<Real>("x4", "Input greatest X  over 2nd interval which new phi will be applied");
  params.addParam<Real>("phi_new",0.0, "Set new value of phi to be applied");
  params.addParam<Real>("phi_old",1.0, "Set new value of phi to be applied");
  return params;
}

Val2Var::Val2Var(const std::string & name, InputParameters parameters) :
    Function(name, parameters),
    _x1(getParam<Real>("x1")),
    _x2(getParam<Real>("x2")),
    _x3(getParam<Real>("x3")),
    _x4(getParam<Real>("x4")),
    _phi_new(getParam<Real>("phi_new")),
    _phi_old(getParam<Real>("phi_old"))
{}

Real
Val2Var::value(Real /*t*/, const Point & p)
{
  if ( (p(0) >= _x1 && p(0) <= _x2) ||  (p(0) >= _x3 && p(0) <= _x4) ) 
    return _phi_new; 

  else
    return _phi_old;
}
