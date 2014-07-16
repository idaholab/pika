/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef PHASEFIELDPROPERTIES_H
#define PHASEFIELDPROPERTIES_H

// MOOSE includes
#include "Material.h"

// PIKA includes
#include "PropertyUserObjectInterface.h"

class PhaseFieldProperties;

template<>
InputParameters validParams<PhaseFieldProperties>();

/**
 * A material for defining properties associated with the phase-field equation
 */
class PhaseFieldProperties :
  public Material,
  public PropertyUserObjectInterface
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

  MaterialProperty<Real> & _saturation_pressure_of_water_vapor_over_ice;

  MaterialProperty<Real> & _specific_humidity_ratio;

  const Real & _xi;

  const Real & _d_o;

  const Real & _interface_kinetic_coefficient;

};

#endif // PHASEFIELDPROPERTIES_H
