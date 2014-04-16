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

  VariableValue & _temperature;

  VariableValue & _phi;

  Real _gamma;

  Real _a;

  Real _k;

  Real _alpha;

  Real _m;

  Real _rho_vs;

  Real _w;

  Real _reference_temperature;

  const Real _mob;

  const Real _a1;

  std::vector<Real> _coefficients;

  MaterialProperty<Real> & _interface_velocity;

  MaterialProperty<Real> & _capillary_length;

  MaterialProperty<Real> & _beta;

  MaterialProperty<Real> & _lambda;

  MaterialProperty<Real> & _tau;

  MaterialProperty<Real> & _conductivity;

  MaterialProperty<Real> & _heat_capacity;

  MaterialProperty<Real> & _diffusion_coefficient;

  MaterialProperty<Real> & _interface_thickness_squared;

  MaterialProperty<Real> & _mobility;

  MaterialProperty<Real> & _chemical_potential_eq;

};

#endif // PHASEFIELDPROPERTIES_H
