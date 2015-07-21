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

#ifndef PIKAPHASEINITIALIZEAUX_H
#define PIKAPHASEINITIALIZEAUX_H

// MOOSE includes
#include "AuxKernel.h"

// Forward declarations
class PikaPhaseInitializeAux;

template<>
InputParameters validParams<PikaPhaseInitializeAux>();

/**
 * An AuxKernel for computing a limited phase variable
 */
class PikaPhaseInitializeAux : public AuxKernel
{
public:

  /**
   * Class constructor
   * @param name The name of the object
   * @param parameters InputParameters for the object
   */
  PikaPhaseInitializeAux(const InputParameters & parameters);

protected:

  /**
   * Computes limited value of the supplied phase variable
   */
  virtual Real computeValue();

private:

  /// The variable to range limit
  const VariableValue & _phase;

  /// The upper range to limit the variable
  Real _upper;

  /// The lower range to limit the variable
  Real _lower;

};

#endif //PIKAPHASEINITIALIZEAUX_H
