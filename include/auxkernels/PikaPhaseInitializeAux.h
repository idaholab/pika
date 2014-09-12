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
 *
 */
class PikaPhaseInitializeAux : public AuxKernel
{
public:

  /**
   * Class constructor
   * @param name
   * @param parameters
   */
  PikaPhaseInitializeAux(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeValue();

private:
  const VariableValue & _phase;
  Real _upper;
  Real _lower;

};

#endif //PIKAPHASEINITIALIZEAUX_H
