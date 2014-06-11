#ifndef CHEMICALPOTENTIALIC_H
#define CHEMICALPOTENTIALIC_H

// MOOSE includes
#include "InitialCondition.h"

//Forward Declarations
class ChemicalPotentialIC;
class PropertyUserObject;

template<>
InputParameters validParams<ChemicalPotentialIC>();

class ChemicalPotentialIC :
  public InitialCondition
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

  const PropertyUserObject & _property_uo;

  VariableValue & _temperature;
};

#endif // CHEMICALPOTENTIALIC_H
