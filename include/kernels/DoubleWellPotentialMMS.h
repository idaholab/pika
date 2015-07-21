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

#ifndef DOUBLEWELLPOTENTIALMMSMMS_H
#define DOUBLEWELLPOTENTIALMMSMMS_H

// MOOSE includes
#include "Kernel.h"

// Forward declarations
class DoubleWellPotentialMMS;

template<>
InputParameters validParams<DoubleWellPotentialMMS>();

/**
 */
class DoubleWellPotentialMMS : public Kernel
{
public:

  /**
   * Class constructor
   * @param name
   * @param parameters
   */
  DoubleWellPotentialMMS(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

};

#endif //DOUBLEWELLPOTENTIALMMSMMS_H
