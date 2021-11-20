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

#ifndef IBEXSHORTWAVEFORCINGFUNCTION_H
#define IBEXSHORTWAVEFORCINGFUNCTION_H

#include "Kernel.h"

//Forward Declarations
class Function;

/**
 * Define the Kernel for a user defined forcing function that looks like:
 *
 * test function * forcing function
 */
class IbexShortwaveForcingFunction : public Kernel
{
public:

  IbexShortwaveForcingFunction(const InputParameters & parameters);
  static InputParameters validParams();

  void initialSetup();

protected:

  /**
   * Computes test function * forcing function.
   */
  virtual Real computeQpResidual();

private:

  const Function & _short_wave;
  const Real _vis_extinction;
  const Real _nir_extinction;
  const Real _vis_albedo;
  const Real _nir_albedo;
  const MooseEnum & _direction;
  RealVectorValue _direction_vector;
  Real _surface;
};

#endif // IBEXSHORTWAVEFORCINGFUNCTION_H
