/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

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
   * @param name
   */
  PikaWaterVaporConcentration(const std::string & name, InputParameters parameters);

  /**
   * Class destructor
   */
  virtual ~PikaWaterVaporConcentration();

protected:

  /**
   *
   */
  virtual Real computeValue();

private:
  MaterialProperty<Real> & _rho_i;
  VariableValue & _s;

};

#endif //PIKAWATERVAPORCONCENTRATION_H
