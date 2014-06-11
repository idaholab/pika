#ifndef ICEPROPERTIES_H
#define ICEPROPERTIES_H

// MOOSE includes
#include "PikaMaterialBase.h"

// Forward declarations
class IceProperties;

template<>
InputParameters validParams<IceProperties>();

/**
 * A material for defining properties associated with the phase-field equation
 */
class IceProperties :
  public PikaMaterialBase
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
