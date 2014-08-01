/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef PIKACOUPLEDTIMEDERIVATIVE_H
#define PIKACOUPLEDTIMEDERIVATIVE_H

//Moose Includes
#include "Kernel.h"

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
  public Kernel
{
public:

  /**
   * Class constructor
   */
  AntiTrapping(const std::string & name, InputParameters parameters);

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
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:
 const <Real> &_w;
 VariableValue & _phase_dot;
 VariableValue & _grad_phase;

};

#endif //COUPLEDPIKATIMEDERIVATIVE
