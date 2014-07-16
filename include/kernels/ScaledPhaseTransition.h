/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef SCALEDPHASETRANSITION_H
#define SCALEPHASETRANSITION_H

// modules/phase_field includes
#include "ACBulk.h"

#include "PropertyUserObjectInterface.h"
//Forward Declarations
class ScaledPhaseTransition;

template<>
InputParameters validParams<ScaledPhaseTransition>();

class ScaledPhaseTransition :
  public ACBulk,
  public PropertyUserObjectInterface
{
public:

  ScaledPhaseTransition(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeDFDOP(PFFunctionType type);

private:
  VariableValue & _s;

  MaterialProperty<Real> & _lambda;

  MaterialProperty<Real> & _s_eq;

  const Real & _xi;

};
#endif // SCALEDPHASETRANSITION_H
