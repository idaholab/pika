#ifndef PHASEFIELDPROPERTIES_H
#define PHASEFIELDPROPERTIES_H

#include "Material.h"

class PhaseFieldProperties;

template<>
InputParameters validParams<PhaseFieldProperties>();

/**
 * A material for defining properties associated with the phase-field equation
 */
class PhaseFieldProperties : public Material
{
public:
  PhaseFieldProperties(const std::string & name, InputParameters parameters);

protected:
  virtual void computeQpProperties();

private:

  Real _gamma;

  Real _a;

  Real _k;

  VariableValue & _temperature;


  MaterialProperty<Real> & _capillary_length;
};

#endif // PHASEFIELDPROPERTIES_H
