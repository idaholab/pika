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

#ifndef MASSTRANSPORTSOURCEMMS_H
#define MASSTRANSPORTSOURCEMMS_H

// MOOSE includes
#include "Kernel.h"
//Pika Includes
#include "PropertyUserObjectInterface.h"

// Forward declarations
class MassTransportSourceMMS;

template<>
InputParameters validParams<MassTransportSourceMMS>();

/**
 * A kernel for adding forcing function for the MMS tests of the mass
 * transport equation, Eq. (35)
 */
class MassTransportSourceMMS :
  public Kernel,
         PropertyUserObjectInterface

{
public:

  /**
   * Class constructor
   * @param name
   * @param parameters
   */
  MassTransportSourceMMS(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

private:
  const MaterialProperty<Real> & _D_v;
  const VariableValue & _phi;
  bool _use_dphi_dt;
  bool _use_scale;
  const Real & _xi;

};

#endif //MASSTRANSPORTSOURCEMMS_H
