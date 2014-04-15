#ifndef ICEPROPERTIES_H
#define ICEPROPERTIES_H

#include "Material.h"

class IceProperties;

template<>
InputParameters validParams<IceProperties>();

/**
 * A material for defining properties associated with the phase-field equation
 */
class IceProperties : public Material
{
public:
  IceProperties(const std::string & name, InputParameters parameters);

protected:
  virtual void computeQpProperties();

private:

  VariableValue & _temperature;

  MaterialProperty<Real> & _density_ice;
};

#endif // ICEPROPERTIES_H
