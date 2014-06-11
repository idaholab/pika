#ifndef CONSTANTPROPERTIES_H
#define CONSTANTPROPERTIES_H

#include "Material.h"
#include "ChemicalPotentialInterface.h"

class ConstantProperties;

template<>
InputParameters validParams<ConstantProperties>();

/**
 * A material for defining properties associated with the phase-field equation
 */
class ConstantProperties :
  public Material,
  public ChemicalPotentialInterface
{
public:
  ConstantProperties(const std::string & name, InputParameters parameters);

protected:
  virtual void computeQpProperties();

private:

  std::vector<std::string> _property_names;
  std::vector<Real> _property_values;
  std::vector<MaterialProperty<Real> *> _property_ptrs;


  MaterialProperty<Real> & _atmospheric_pressure;
};

#endif // CONSTANTPROPERTIES_H
