/**********************************************************************************/
/*                  Pika: Phase field snow micro-structure model                  */
/*                                                                                */
/*                     (C) 2014 Battelle Energy Alliance, LLC                     */
/*                              ALL RIGHTS RESERVED                               */
/*                                                                                */
/*                   Prepared by Battelle Energy Alliance, LLC                    */
/*                      Under Contract No. DE-AC07-05ID14517                      */
/*                      With the U. S. Department of Energy                       */
/**********************************************************************************/

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
 * Computes the interface velocity via Eq. 23
 */
class PikaInterfaceVelocity :
  public AuxKernel,
  public PropertyUserObjectInterface
{
public:

  /**
   * Class constructor
   * @param name Object name
   * @param parameters Object InputParameters
   */
  PikaInterfaceVelocity(const InputParameters & parameters);

  /**
   * Class destructor
   */
  virtual ~PikaInterfaceVelocity();

protected:

  /**
   * Computes the interface velocity at the current quadrature point
   */
  virtual Real computeValue();

private:

  /// Reference the the constant diffusivity coefficient for water vapor
  const Real & _D_v;

  /// Gradient of the phase-field variable
  VariableGradient & _grad_phase;

  /// Gradient of the chemical potential variable
  VariableGradient & _grad_s;

};

#endif //PIKAINTERFACEVELOCITY_H
