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

#ifndef PIKACHEMICALPOTENTIALBC_H
#define PIKACHEMICALPOTENTIALBC_H

// MOOSE includes
#include "NodalBC.h"

// PIKA includes
#include "PropertyUserObjectInterface.h"

//Forward Declarations

/**
 * Chemical potential equilibrium boundary condition
 *   u - u_eq (1 - phi)/2
 */
class PikaChemicalPotentialBC :
  public NodalBC,
  public PropertyUserObjectInterface
{
public:
  PikaChemicalPotentialBC(const InputParameters & parameters);
  static InputParameters validParams();
  virtual ~PikaChemicalPotentialBC(){};

protected:

  /**
   * Computes the chemical potential boundary condition
   */
  virtual Real computeQpResidual();

private:

  /// Coupled temperature variable
  const VariableValue & _temperature;

  /// Coupled phase-field variable
  const VariableValue & _phase;
};

#endif // PIKACHEMICALPOTENTIALBC_H
