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

#ifndef PIKAWATERVAPORCONCENTRATION_H
#define PIKAWATERVAPORCONCENTRATION_H

// MOOSE includes
#include "AuxKernel.h"

// Pika includes
#include "PropertyUserObjectInterface.h"

// Forward declarations
class PikaWaterVaporConcentration;

template<>
InputParameters validParams<PikaWaterVaporConcentration>();

/**
 *
 */
class PikaWaterVaporConcentration :
  public AuxKernel,
  public PropertyUserObjectInterface
{
public:

  /**
   * Class constructor
   * @param name Name of the object
   * @param parameters InputParameters for the object
   */
  PikaWaterVaporConcentration(const InputParameters & parameters);

  /**
   * Class destructor
   */
  virtual ~PikaWaterVaporConcentration();

protected:

  /**
   *  Computes the value of the water vapor concentration using Eq. 21
   */
  virtual Real computeValue();

private:

  /// Coupled chemical potential variable
   const VariableValue & _s;

  /// Reference to ice density stored in PropertyUserObject
  const Real _rho_i;

  /// Reference to the reference temperature stored in PropertyUserObject
  const Real & _T_0;

};

#endif //PIKAWATERVAPORCONCENTRATION_H
