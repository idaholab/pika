#ifndef AIRPROPERTIES_H
#define AIRPROPERTIES_H

#include "Material.h"
#include "ChemicalPotentialInterface.h"

class AirProperties;

template<>
InputParameters validParams<AirProperties>();

/**
 * A material for defining properties associated with the phase-field equation
 */
class AirProperties :
  public Material,
  public ChemicalPotentialInterface
{
public:
  AirProperties(const std::string & name, InputParameters parameters);

protected:
  virtual void computeQpProperties();

private:

  VariableValue & _temperature;

  MaterialProperty<Real> & _rho_a;

  MaterialProperty<Real> & _kappa_a;

  MaterialProperty<Real> & _C_a;

  MaterialProperty<Real> & _D_a;
};

#endif // AIRPROPERTIES_H
