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

#ifndef IBEXSHORTWAVEFORCINGFUNCTION_H
#define IBEXSHORTWAVEFORCINGFUNCTION_H

#include "Kernel.h"

//Forward Declarations
class IbexShortwaveForcingFunction;
class Function;

template<>
InputParameters validParams<IbexShortwaveForcingFunction>();

/**
 * Define the Kernel for a user defined forcing function that looks like:
 *
 * test function * forcing function
 */
class IbexShortwaveForcingFunction : public Kernel
{
public:

  IbexShortwaveForcingFunction(const std::string & name, InputParameters parameters);

  void initialSetup();

protected:

  /**
   * Computes test function * forcing function.
   */
  virtual Real computeQpResidual();

private:

  Function & _short_wave;
  const Real _extinction;
  const Real _vis_albedo;
  const Real _nir_albedo;
  const Real _swir_albedo;
  const MooseEnum & _direction;
  RealVectorValue _direction_vector;
  Real _surface;
};

#endif // IBEXSHORTWAVEFORCINGFUNCTION_H
