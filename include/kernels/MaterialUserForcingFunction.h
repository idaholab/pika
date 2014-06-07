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

#ifndef MATERIALUSERFORCINGFUNCTION_H
#define MATERIALUSERFORCINGFUNCTION_H

#include "UserForcingFunction.h"

//Forward Declarations
class MaterialUserForcingFunction;

template<>
InputParameters validParams<MaterialUserForcingFunction>();

/**
 * Multiplies a UserForcingFunction by a Material Property
 */
class MaterialUserForcingFunction : public UserForcingFunction
{
public:
  /**
   * Factory constructor, takes parameters so that all derived classes can be built using the same
   * constructor.
   */
  MaterialUserForcingFunction(const std::string & name, InputParameters parameters);

  virtual ~MaterialUserForcingFunction() {}

protected:
  virtual Real computeQpResidual();

  /// Material Property being used to multiply with the function of this kernel
  MaterialProperty<Real> & _material_coefficient;
  Real _scale;
};

#endif //MATERIALUSERFORCINGFUNCTION_H
