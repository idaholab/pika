/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef PHASETRANSITION_H
#define PHASETRANSITION_H

// modules/phase_field includes
#include "ACBulk.h"

#include "PropertyUserObjectInterface.h"
//Forward Declarations
class PhaseTransition;

template<>
InputParameters validParams<PhaseTransition>();

class PhaseTransition :
  public ACBulk,
  public PropertyUserObjectInterface
{
public:

  PhaseTransition(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeDFDOP(PFFunctionType type);
/**
 * Compute off-diagonal jacobain
 * The off-diagonal jacobain term, i.e., the derivative of the coupled time derivative with respect
 * to the coupled variable.
 */
//  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:
  VariableValue & _s;

  MaterialProperty<Real> & _lambda;

  MaterialProperty<Real> & _s_eq;

  unsigned int _v_var;

};
#endif // PHASETRANSITION_H
