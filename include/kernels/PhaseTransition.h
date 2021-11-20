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

#ifndef PHASETRANSITION_H
#define PHASETRANSITION_H

// modules/phase_field includes
#include "ACBulk.h"

//Pika Includs
#include "PropertyUserObjectInterface.h"
#include "CoefficientKernelInterface.h"
//Forward Declarations

class PhaseTransition :
  public ACBulk<Real>,
  public CoefficientKernelInterface
{
public:

  PhaseTransition(const InputParameters & parameters);
  static InputParameters validParams();

protected:
  virtual Real computeDFDOP(PFFunctionType type);

private:
  const VariableValue & _s;

  const MaterialProperty<Real> & _lambda;

  const MaterialProperty<Real> & _s_eq;
};

#endif // PHASETRANSITION_H
