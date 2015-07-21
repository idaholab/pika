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

#ifndef PIKADIFFUSION_H
#define PIKADIFFUSION_H

// MOOSE includes
#include "Diffusion.h"

// Pika includes
#include "PropertyUserObjectInterface.h"
#include "CoefficientKernelInterface.h"

//Forward Declarations
class PikaDiffusion;

template<>
InputParameters validParams<PikaDiffusion>();

/**
 * A coefficient diffusion Kernel
 *
 * This Kernel allows to a coefficient to be applied to the diffusion term, that
 * coefficient may be either a scalar value or a scalar material property.
 *
 * This Kernel includes the ability to scale and offset the coefficient. The
 * coefficient (material or scalar) is applied as:
 *     (scale * coefficient + offset) * div(coefficient \nabla u)
 *
 * Also, include the ability to toggle the additional temporal scaling parameter (\xi)
 * as defined by Kaempfer and Plapp (2009). This temporal scalling is applied in
 * additions to the coefficient scaling:
 *     xi * (scale * coefficient + offset) * div(coefficient \nabla u)
 */
class PikaDiffusion :
  public Diffusion,
  public CoefficientKernelInterface
{
public:

  /**
   * Class constructor
   */
  PikaDiffusion(const InputParameters & parameters);

protected:

  /**
   * Compute residual
   * Utilizes Diffusion::computeQpResidual with applied coefficients and scaling
   */
  virtual Real computeQpResidual();

  /**
   * Compute residual
   * Utilizes Diffusion::computeQpJacobian with applied coefficients and scaling
   */
  virtual Real computeQpJacobian();

};

#endif //MATDIFFUSION_H
