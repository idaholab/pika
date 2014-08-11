/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef CHEMFunctionALPOTENTIALFUNCTION_H
#define CHEMFunctionALPOTENTIALFUNCTION_H

// MOOSE includes
#include "Function.h"

// PIKA includes
#include "PropertyUserObjectInterface.h"

//Forward Declarations
class ChemicalPotentialFunction;

template<>
InputParameters validParams<ChemicalPotentialFunction>();

class ChemicalPotentialFunction :
  public Function,
  public PropertyUserObjectInterface
{
public:
  ChemicalPotentialFunction(const std::string & name, InputParameters parameters);

  virtual ~ChemicalPotentialFunction(){};

protected:

  /**
   * The value of the variable at a point.
   *
   * This must be overridden by derived classes.
   */
  virtual Real value( const Real & phi, const Real & T);
};

#endif // CHEMFunctionALPOTENTIALFUNCTION_H
