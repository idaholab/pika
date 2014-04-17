#ifndef CONSTANTPROPERTIES_H
#define CONSTANTPROPERTIES_H

#include "Material.h"

class ConstantProperties;

template<>
InputParameters validParams<ConstantProperties>();

/**
 * A material for defining properties associated with the phase-field equation
 */
class ConstantProperties : public Material
{
public:
  ConstantProperties(const std::string & name, InputParameters parameters);

protected:
  virtual void computeQpProperties();

private:

  std::vector<std::string> _property_names;
  std::vector<Real> _property_values;
  std::vector<MaterialProperty<Real> *> _property_ptrs;
};

#endif // CONSTANTPROPERTIES_H
