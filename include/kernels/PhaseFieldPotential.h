#ifndef PHASEFIELDPOTENTIAL_H
#define PHASEFIELDPOTENTIAL_H

// modules/phase_field includes
#include "ACBulk.h"

//Forward Declarations
class PhaseFieldPotential;

template<>
InputParameters validParams<PhaseFieldPotential>();

class PhaseFieldPotential : public ACBulk
{
public:

  PhaseFieldPotential(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeDFDOP(PFFunctionType type);


};
#endif // PHASEFIELDPOTENTIAL_H
