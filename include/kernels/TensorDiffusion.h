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

// Forward declerations
class TensorDiffusion;

template<>
InputParameters validParams<TensorDiffusion>();

/**
 *
 */
class TensorDiffusion : public Diffusion
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
  MaterialProperty<RealTensorValue> & _coef;


};

#endif //TENSORDIFFUSION_H
