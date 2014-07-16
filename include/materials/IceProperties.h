/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef ICEPROPERTIES_H
#define ICEPROPERTIES_H

// MOOSE includes
#include "Material.h"

// PIKA indluces
#include "PropertyUserObjectInterface.h"

// Forward declarations
class IceProperties;

template<>
InputParameters validParams<IceProperties>();

/**
 * A material for defining properties associated with the phase-field equation
 */
class IceProperties :
  public Material,
  public PropertyUserObjectInterface
{
public:
  IceProperties(const std::string & name, InputParameters parameters);
  static InputParameters objectParams();
protected:
  virtual void computeQpProperties();

private:

  VariableValue & _temperature;

  MaterialProperty<Real> & _rho_i;

  MaterialProperty<Real> & _kappa_i;

  MaterialProperty<Real> & _C_i;

};

#endif // ICEPROPERTIES_H
