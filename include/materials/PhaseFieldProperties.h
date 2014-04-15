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

  Real _alpha;

  Real _m;

  Real _rho_vs;

  Real _w;

  const Real _a1;

  VariableValue & _temperature;

  MaterialProperty<Real> & _density_ice;

  MaterialProperty<Real> & _interface_velocity;

  MaterialProperty<Real> & _capillary_length;

  MaterialProperty<Real> & _beta;

  MaterialProperty<Real> & _lambda;

  MaterialProperty<Real> & _tau;

};

#endif // PHASEFIELDPROPERTIES_H
