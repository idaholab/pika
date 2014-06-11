#ifndef CONSTANTPROPERTIES_H
#define CONSTANTPROPERTIES_H

#include "PikaMaterialBase.h"

class ConstantProperties;

template<>
InputParameters validParams<ConstantProperties>();

/**
 * A material for defining properties associated with the phase-field equation
 */
class ConstantProperties :
  public PikaMaterialBase
{
public:
  ConstantProperties(const std::string & name, InputParameters parameters);

protected:
  virtual void computeQpProperties();

private:
  MaterialProperty<Real> & _interface_free_energy;

  MaterialProperty<Real> & _mean_molecular_spacing;

  MaterialProperty<Real> & _boltzmann;

  MaterialProperty<Real> & _condensation_coefficient;

  MaterialProperty<Real> & _mass_water_molecule;

  MaterialProperty<Real> & _interface_thickness;

  MaterialProperty<Real> & _atmospheric_pressure;

  MaterialProperty<Real> & _latent_heat;
};

#endif // CONSTANTPROPERTIES_H
