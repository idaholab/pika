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

#ifndef PIKACOUPLEDTIMEDERIVATIVE_H
#define PIKACOUPLEDTIMEDERIVATIVE_H

// Pika includes
#include "PikaTimeDerivative.h"

// Forward Declarations
class PikaCoupledTimeDerivative;

template<>
InputParameters validParams<PikaCoupledTimeDerivative>();

 /**
 * A coefficient time derivative Kernel acting on a coupled variable
 *
 * This Kernel behaves exactly as PikaTimeDerivative, but instead the
 * time derivative is for a coupled variable.
 *
 * @see PikaTimeDerivative
 */

class PikaCoupledTimeDerivative :
  public PikaTimeDerivative
{
public:

  /**
   * Class constructor
   */
  PikaCoupledTimeDerivative(const InputParameters & parameters);

protected:

  /**
   * Compute residual
   * Utilizes PikaTimeDerivative::computeQpResidual to compute residual of coupled time variable
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

  /// Time derivative of coupled variable
  const VariableValue & _var_dot;

  /// Derivative of time derivative of the coupled variable
  const VariableValue & _dvar_dot_dvar;

  /// The coupled variable number
  unsigned int _v_var;

};

#endif //COUPLEDPIKATIMEDERIVATIVE
