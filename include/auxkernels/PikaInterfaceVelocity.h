/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef PIKAINTERFACEVELOCITY_H
#define PIKAINTERFACEVELOCITY_H

// MOOSE includes
#include "AuxKernel.h"
#include "PropertyUserObjectInterface.h"

// Forward declarations
class PikaInterfaceVelocity;

template<>
InputParameters validParams<PikaInterfaceVelocity>();

/**
 *
 */
class PikaInterfaceVelocity :
  public AuxKernel,
  public PropertyUserObjectInterface
{
public:

  /**
   * Class constructor
   * @param name
   */
  PikaInterfaceVelocity(const std::string & name, InputParameters parameters);

  /**
   * Class destructor
   */
  virtual ~PikaInterfaceVelocity();

protected:

  /**
   *
   */
  virtual Real computeValue();

private:
  const Real & _D_v;
  VariableGradient & _grad_phase;
  VariableGradient & _grad_s;

};

#endif //PIKAINTERFACEVELOCITY_H
