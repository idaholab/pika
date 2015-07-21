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

#ifndef PHASEEVOLUTIONSOURCEMMS_H
#define PHASEEVOLUTIONSOURCEMMS_H
#include "PropertyUserObjectInterface.h"
// MOOSE includes
#include "Kernel.h"

// Forward declarations
class PhaseEvolutionSourceMMS;

template<>
InputParameters validParams<PhaseEvolutionSourceMMS>();

/**
 * A kernel for adding forcing function for the MMS tests of the heat
 * transport equation, Eq. (34)
 */
class PhaseEvolutionSourceMMS :
    public Kernel,
    public PropertyUserObjectInterface
{
public:

  /**
   * Class constructor
   * @param name
   * @param parameters
   */
  PhaseEvolutionSourceMMS(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

private:
  const MaterialProperty<Real> & _tau;
  const MaterialProperty<Real> & _w;
  const MaterialProperty<Real> & _lambda;
  const bool  & _use_potential_transition;
  const VariableValue  & _T;
  const VariableValue  & _u;
  const bool  & _use_scale;
  const Real & _xi;

};

#endif //PHASEEVOLUTIONSOURCEMMS_H
