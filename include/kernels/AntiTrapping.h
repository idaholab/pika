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

#ifndef ANTITRAPPING_H
#define ANTITRAPPING_H

//Moose Includes
#include "Kernel.h"

//PIKA Includes
#include "PropertyUserObjectInterface.h"
#include "CoefficientKernelInterface.h"
//Pika

// Forward Declarations
class AntiTrapping;

template<>
InputParameters validParams<AntiTrapping>();

 /**
 * A coefficient time derivative Kernel acting on a coupled variable
 *
 * This Kernel behaves exactly as AntiTrapping, but instead the
 * time derivative is for a coupled variable.
 *
 * @see AntiTrapping
 */

class AntiTrapping :
  public Kernel,
  public CoefficientKernelInterface
{
public:

  /**
   * Class constructor
   */
  AntiTrapping(const InputParameters & parameters);

protected:

  /**
   * Compute residual
   * Utilizes AntiTrapping::computeQpResidual to compute residual of the antiTrapping method applied
   */
  virtual Real computeQpResidual();

  /**
   * Compute jacobian
   * The Jacobian entry for this Kernel is zero.
   */
  virtual Real computeQpJacobian();

  /**
   * Compute off-diagonal jacobain
   * The off-diagonal jacobain term, i.e., the derivative of the coupled time derivative with respect
   * to the coupled variable.
   */
//  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:
 const VariableValue & _phase_dot;
 const VariableGradient & _grad_phase;
 const Real & _w;

};

#endif // ANTITRAPPING_H
