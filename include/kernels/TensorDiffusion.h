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

#ifndef TENSORDIFFUSION_H
#define TENSORDIFFUSION_H

// MOOSE includes
#include "Diffusion.h"
//Pika includes
#include "PropertyUserObjectInterface.h"
#include "CoefficientKernelInterface.h"
// Forward declerations
class TensorDiffusion;

template<>
InputParameters validParams<TensorDiffusion>();

/**
 *
 */
class TensorDiffusion :
  public Diffusion,
  public CoefficientKernelInterface

{
public:

  /**
   * Class constructor
   * @param name
   * @param parameters
   */
  TensorDiffusion(const InputParameters & parameters);

  /**
   * Class destructor
   */
  virtual ~TensorDiffusion();

protected:
  Real computeQpResidual();
  Real computeQpJacobian();

private:
  const MaterialProperty<RealTensorValue> & _coef;
};

#endif //TENSORDIFFUSION_H
