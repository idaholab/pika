#ifndef PIKAMATERIALBASE_H
#define PIKAMATERIALBASE_H

#include "Material.h"
#include "PropertyUserObject.h"

class PikaMaterialBase;

template<>
InputParameters validParams<PikaMaterialBase>();

/**
 * A base class providing access to the PropertyUserObject
 */
class PikaMaterialBase :
  public Material
{
public:
  PikaMaterialBase(const std::string & name, InputParameters parameters);

protected:
  const PropertyUserObject & _property_uo;
};
#endif // PIKAMATERIALBASE_H
