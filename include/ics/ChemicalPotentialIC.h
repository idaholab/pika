#ifndef CHEMICALPOTENTIALIC_H
#define CHEMICALPOTENTIALIC_H

// MOOSE includes
#include "InitialCondition.h"

// PIKA includes
#include "ChemicalPotentialInterface.h"

//Forward Declarations
class ChemicalPotentialIC;

template<>
InputParameters validParams<ChemicalPotentialIC>();

class ChemicalPotentialIC :
  public InitialCondition,
  public ChemicalPotentialInterface
{
public:
  ChemicalPotentialIC(const std::string & name, InputParameters parameters);

  virtual ~ChemicalPotentialIC(){};

protected:

  /**
   * The value of the variable at a point.
   *
   * This must be overridden by derived classes.
   */
  virtual Real value(const Point & /*p*/);

private:

  VariableValue & _temperature;

  Real _density_ice;

  Real _reference_temperature;

};

#endif // CHEMICALPOTENTIALIC_H
