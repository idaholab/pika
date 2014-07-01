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
