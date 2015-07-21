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

#ifndef PIKATIMEDERIVATIVE_H
#define PIKATIMEDERIVATIVE_H

// MOOSE includes
#include "TimeDerivative.h"

// Pika includes
#include "PropertyUserObjectInterface.h"
#include "CoefficientKernelInterface.h"

//Forward Declarations
class PikaTimeDerivative;

template<>
InputParameters validParams<PikaTimeDerivative>();

/**
 * A coefficient time derivative Kernel
 *
 * This time Kernel allows to a coefficient to be applied to the time derivative, that
 * coefficient may be either a scalar value or a scalar material property.
 *
 * This Kernel includes the ability to scale and offset the coefficient. The
 * coefficient (material or scalar) is applied as:
 *     (scale * coefficient + offset) * du/dt
 *
 * Also, include the ability to toggle the additional temporal scaling parameter (\xi)
 * as defined by Kaempfer and Plapp (2009). This temporal scaling is applied in
 * additions to the coefficient scaling:
 *     xi * (scale * coefficient + offset) * du/dt
 */
class PikaTimeDerivative :
  public TimeDerivative,
  public CoefficientKernelInterface
{
public:

  /**
   * Class constructor.
   */
  PikaTimeDerivative(const InputParameters & parameters);

protected:

  /**
   * Compute residual
   * Utilizes TimeDerivative::computeQpResidual with applied coefficients and scaling
   */
  virtual Real computeQpResidual();

  /**
   * Compute residual
   * Utilizes TimeDerivative::computeQpJacobian with applied coefficients and scaling
   */
  virtual Real computeQpJacobian();
};

#endif //PIKATIMEDERIVATIVE
