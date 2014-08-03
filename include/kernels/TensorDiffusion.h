/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

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
  public PropertyUserObjectInterface,
  public CoefficientKernelInterface

{
public:

  /**
   * Class constructor
   * @param name
   * @param parameters
   */
  TensorDiffusion(const std::string & name, InputParameters parameters);

  /**
   * Class destructor
   */
  virtual ~TensorDiffusion();

protected:
  Real computeQpResidual();
  Real computeQpJacobian();


private:

  RealTensorValue mobilityTensor();
  RealTensorValue normalOutputProduct();

  const RealTensorValue _identity;
  VariableValue & _phase;

  VariableGradient & _grad_phase;

  MaterialProperty<Real> _M_1;
  MaterialProperty<Real> _M_2;

};

#endif //TENSORDIFFUSION_H
