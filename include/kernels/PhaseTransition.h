#ifndef PHASETRANSITION_H
#define PHASETRANSITION_H

// modules/phase_field includes
#include "ACBulk.h"

// PIKA includes
#include "ChemicalPotentialInterface.h"

//Forward Declarations
class PhaseTransition;

template<>
InputParameters validParams<PhaseTransition>();

class PhaseTransition :
  public ACBulk,
  public ChemicalPotentialInterface
{
public:

  PhaseTransition(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeDFDOP(PFFunctionType type);

private:
  VariableValue & _s;

  VariableValue & _temperature;

  MaterialProperty<Real> & _lambda;
};
#endif // PHASETRANSITION_H
