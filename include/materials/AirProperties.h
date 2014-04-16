#ifndef AIRPROPERTIES_H
#define AIRPROPERTIES_H

#include "Material.h"

class AirProperties;

template<>
InputParameters validParams<AirProperties>();

/**
 * A material for defining properties associated with the phase-field equation
 */
class AirProperties : public Material
{
public:
  AirProperties(const std::string & name, InputParameters parameters);

  static Real saturationVaporPressureOfWaterVaporOverIce(Real & T, std::vector<Real> K);

protected:
  virtual void computeQpProperties();

private:

  /// Fitting coefficients
  std::vector<Real> _coefficients;

  VariableValue & _temperature;

  MaterialProperty<Real> & _density_air;

  MaterialProperty<Real> & _conductivity_air;

  MaterialProperty<Real> & _heat_capacity_air;

  MaterialProperty<Real> & _diffusion_coefficient_air;

  MaterialProperty<Real> & _gas_constant_dry_air;

  MaterialProperty<Real> & _gas_constant_water_vapor;

  MaterialProperty<Real> & _saturation_pressure_vapor;

  MaterialProperty<Real> & _atmospheric_pressure;

  MaterialProperty<Real> & _humidity_ratio;

  MaterialProperty<Real> & _water_vapor_mass_density_saturation;
};

#endif // AIRPROPERTIES_H
