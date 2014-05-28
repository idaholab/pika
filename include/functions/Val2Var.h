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

#ifndef VAL2VAR_H
#define VAL2VAR_H

#include "Function.h"

class Val2Var;

template<>
InputParameters validParams<Val2Var>();

class Val2Var : public Function
{
public:
  Val2Var(const std::string & name, InputParameters parameters);

  virtual Real value(Real t, const Point & p);

protected:
  Real _x1, _x2, _x3, _x4;
  Real _phi_new;
  Real _phi_old;
};

#endif //VAL2VAR_H
