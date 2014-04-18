#ifndef ICEPROPERTIES_H
#define ICEPROPERTIES_H

// MOOSE includes
#include "Material.h"

// PIKA includes
#include "ChemicalPotentialInterface.h"

// Forward declarations
class IceProperties;

template<>
InputParameters validParams<IceProperties>();

/**
 * A material for defining properties associated with the phase-field equation
 */
class IceProperties :
  public Material,
  public ChemicalPotentialInterface
{
public:
  IceProperties(const std::string & name, InputParameters parameters);

protected:
  virtual void computeQpProperties();

private:

  VariableValue & _temperature;

  MaterialProperty<Real> & _rho_i;

  MaterialProperty<Real> & _kappa_i;

  MaterialProperty<Real> & _C_i;

};

#endif // ICEPROPERTIES_H
