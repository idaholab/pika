/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef CHEMICALPOTENTIALBC_H
#define CHEMICALPOTENTIALBC_H

// MOOSE includes
#include "NodalBC.h"

// PIKA includes
#include "PropertyUserObjectInterface.h"

//Forward Declarations
class ChemicalPotentialBC;

template<>
InputParameters validParams<ChemicalPotentialBC>();

class ChemicalPotentialBC :
  public NodalBC,
  public PropertyUserObjectInterface
{
public:
  ChemicalPotentialBC(const std::string & name, InputParameters parameters);

  virtual ~ChemicalPotentialBC(){};

protected:

  /**
   * The value of the variable at a point.
   *
   * This must be overridden by derived classes.
   */
  virtual Real computeQpResidual();

private:

  VariableValue & _temperature;
  VariableValue & _phase;
};

#endif // CHEMICALPOTENTIALBC_H
