/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef PIKASUPERSATURATION_H
#define PIKASUPERSATURATION_H

// MOOSE includes
#include "AuxKernel.h"

// Pika includes
#include "PropertyUserObjectInterface.h"

// Forward declarations
class PikaSupersaturation;

template<>
InputParameters validParams<PikaSupersaturation>();

/**
 *
 */
class PikaSupersaturation :
  public AuxKernel,
  public PropertyUserObjectInterface
{
public:

  /**
   * Class constructor
   * @param name
   */
  PikaSupersaturation(const std::string & name, InputParameters parameters);

  /**
   * Class destructor
   */
  virtual ~PikaSupersaturation();

protected:

  /**
   *
   */
  virtual Real computeValue();

private:

  VariableValue & _s;
  VariableValue & _temperature;
  const Real & _rho_i;
  Real _xi;
};

#endif //PIKASUPERSATURATION_H
