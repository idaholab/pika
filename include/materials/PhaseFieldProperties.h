#ifndef PHASEFIELDPROPERTIES_H
#define PHASEFIELDPROPERTIES_H

#include "Material.h"
#include "ChemicalPotentialInterface.h"

class PhaseFieldProperties;

template<>
InputParameters validParams<PhaseFieldProperties>();

/**
 * A material for defining properties associated with the phase-field equation
 */
class PhaseFieldProperties :
  public Material,
  public ChemicalPotentialInterface
{
public:
  PhaseFieldProperties(const std::string & name, InputParameters parameters);

protected:
  virtual void computeQpProperties();

private:

  VariableValue & _temperature;

  VariableValue & _phase;

  const Real _a1;

  MaterialProperty<Real> & _interface_velocity;

  MaterialProperty<Real> & _capillary_length;

  MaterialProperty<Real> & _beta;

  MaterialProperty<Real> & _lambda;

  MaterialProperty<Real> & _tau;

  MaterialProperty<Real> & _conductivity;

  MaterialProperty<Real> & _heat_capacity;

  MaterialProperty<Real> & _diffusion_coefficient;

  MaterialProperty<Real> & _interface_thickness_squared;

  MaterialProperty<Real> & _equilibrium_concentration;

};

#endif // PHASEFIELDPROPERTIES_H
