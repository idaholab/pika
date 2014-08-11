/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "ChemicalPotentialFunction.h"
#include "PropertyUserObject.h"
template<>
InputParameters validParams<ChemicalPotentialFunction>()
{
  InputParameters params = validParams<Function>();
  params += validParams<PropertyUserObjectInterface>();
  return params;
}

ChemicalPotentialFunction::ChemicalPotentialFunction(const std::string & name, InputParameters parameters) :
    Function(name, parameters),
    PropertyUserObjectInterface(name, parameters)
{
}

Real
ChemicalPotentialFunction::value( const Real & phi, const Real & T) 
{
  return _property_uo.equilibriumConcentration(T) * ((1.0 - phi)/2.0);
}
