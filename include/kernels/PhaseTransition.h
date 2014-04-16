#ifndef PHASETRANSITION_H
#define PHASETRANSITION_H

// modules/phase_field includes
#include "ACBulk.h"

//Forward Declarations
class PhaseTransition;

template<>
InputParameters validParams<PhaseTransition>();

class PhaseTransition : public ACBulk
{
public:

  PhaseTransition(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeDFDOP(PFFunctionType type);

private:
  VariableValue & _s;

  MaterialProperty<Real> & _temperature;

  MaterialProperty<Real> & _lambda;

  MaterialProperty<Real> & _density_ice;

  MaterialProperty<Real> & _reference_temperature;

};
#endif // PHASETRANSITION_H
