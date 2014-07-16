/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef HEATEQUATIONSOURCEMMS_H
#define HEATEQUATIONSOURCEMMS_H

// MOOSE includes
#include "Kernel.h"
//Pika Includes
#include "PropertyUserObjectInterface.h"

// Forward declarations
class HeatEquationSourceMMS;

template<>
InputParameters validParams<HeatEquationSourceMMS>();

/**
 * A kernel for adding forcing function for the MMS tests of the heat
 * transport equation, Eq. (34)
 */
class HeatEquationSourceMMS :
  public Kernel,
         PropertyUserObjectInterface
{
public:

  /**
   * Class constructor
   * @param name
   * @param parameters
   */
  HeatEquationSourceMMS(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();

private:
  const MaterialProperty<Real> & _k;
  const MaterialProperty<Real> & _c;
  const MaterialProperty<Real> & _L_sg;
  const VariableValue & _phi;
  bool _use_dphi_dt;
  bool _use_scale;
  const Real & _xi;

};

#endif //HEATEQUATIONSOURCEMMS_H
