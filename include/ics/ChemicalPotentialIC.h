#ifndef CHEMICALPOTENTIALIC_H
#define CHEMICALPOTENTIALIC_H

// MOOSE includes
#include "InitialCondition.h"
#include <string>

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

protected:

  /**
   * The value of the variable at a point.
   *
   * This must be overridden by derived classes.
   */
  virtual Real value(const Point & /*p*/);

private:

  VariableValue & _temperature;

};

#endif // CHEMICALPOTENTIALIC_H
