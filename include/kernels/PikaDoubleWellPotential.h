#ifndef PIKADOUBLEWELLPOTENTIAL_H
#define PIKADOUBLEWELLPOTENTIAL_H

#include "ACBulk.h"

//Forward Declarations
class PikaDoubleWellPotential;

template<>
InputParameters validParams<PikaDoubleWellPotential>();

/**
 * Algebraic double well potential.
 */
class PikaDoubleWellPotential : public ACBulk
{
public:
  PikaDoubleWellPotential(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();
};

#endif //PIKADOUBLEWELLPOTENTIAL_H
