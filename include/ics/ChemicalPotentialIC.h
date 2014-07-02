#ifndef CHEMICALPOTENTIALIC_H
#define CHEMICALPOTENTIALIC_H

// MOOSE includes
#include "InitialCondition.h"

// PIKA includes
#include "PropertyUserObjectInterface.h"

//Forward Declarations
class ChemicalPotentialIC;

template<>
InputParameters validParams<ChemicalPotentialIC>();

class ChemicalPotentialIC :
  public InitialCondition,
  public PropertyUserObjectInterface
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
  VariableValue & _phase;
};

#endif // CHEMICALPOTENTIALIC_H
