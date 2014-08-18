/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef VARIABLEGRADIENTCOMPONENT_H
#define VARIABLEGRADIENTCOMPONENT_H

// MOOSE includes
#include "AuxKernel.h"

// Forward declarations
class VariableGradientComponent;

template<>
InputParameters validParams<VariableGradientComponent>();

/**
 *
 */
class VariableGradientComponent : public AuxKernel
{
public:

  /**
   * Class constructor
   * @param name
   * @param parameters
   */
  VariableGradientComponent(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeValue();

private:
  const VariableGradient & _gradient;

  int _component;

};

#endif //ERRORFUNCTIONAUX_H
