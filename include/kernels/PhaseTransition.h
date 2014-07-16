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

private:
  VariableValue & _s;

  MaterialProperty<Real> & _lambda;

  MaterialProperty<Real> & _s_eq;

};
#endif // PHASETRANSITION_H
