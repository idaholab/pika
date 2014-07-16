/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef PROPERTYUSEROBJECTINTERFACE_H
#define PROPERTYUSEROBJECTINTERFACE_H

// PIKA includes
#include "PropertyUserObject.h"

// Forward declarations
class PropertyUserObjectInterface;
class FEProblem;

template<>
InputParameters validParams<PropertyUserObjectInterface>();

/**
 * A class providing access to the PropertyUserObject.
 *
 * By default PikaMaterials creates the necessary PropertyUserObject, this
 * class will use the pika created version if the user does not define explicitly
 * a PropertyUserObject.
 */
class PropertyUserObjectInterface
{
public:
  PropertyUserObjectInterface(const std::string & name, InputParameters & parameters);

private:
  FEProblem * _problem_ptr;

protected:
  const PropertyUserObject & _property_uo;

};

#endif // PROPERTYUSEROBJECTINTERFACE_H
