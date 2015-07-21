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

#ifndef PIKASUPERSATURATION_H
#define PIKASUPERSATURATION_H

// MOOSE includes
#include "AuxKernel.h"

// Pika includes
#include "PropertyUserObjectInterface.h"

// Forward declarations
class PikaSupersaturation;

template<>
InputParameters validParams<PikaSupersaturation>();

/**
 * AuxKernel for computing the supersaturation
 */
class PikaSupersaturation :
  public AuxKernel,
  public PropertyUserObjectInterface
{
public:

  /**
   * Class constructor
   * @param name Name of the object
   * @param parameters
   */
  PikaSupersaturation(const InputParameters & parameters);

  /**
   * Class destructor
   */
  virtual ~PikaSupersaturation();

protected:

  /**
   * Computes the value of supersaturation, Eq. 18 and Eq. 22
   */
  virtual Real computeValue();

private:

  /// Chemical potential variable
  VariableValue & _s;

  /// Temperature variable
  VariableValue & _temperature;

  /// Density of ice
  const Real & _rho_i;

  /// Temporal scaling factor
  Real _xi;

  /// If true, the supersaturation is normalized as in Eq. 18 by rho_vs
  bool _normalize;
};

#endif //PIKASUPERSATURATION_H
