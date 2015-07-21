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

#include "PikaTimeDerivative.h"

template<>
InputParameters validParams<PikaTimeDerivative>()
{
  InputParameters params = validParams<TimeDerivative>();
  params += validParams<CoefficientKernelInterface>();
  return params;
}

PikaTimeDerivative::PikaTimeDerivative(const InputParameters & parameters) :
    TimeDerivative(parameters),
    CoefficientKernelInterface(parameters)
{
  // The getMaterialProperty method cannot be replicated in interface
  if (useMaterial())
    setMaterialPropertyPointer(&getMaterialProperty<Real>(getParam<std::string>("property")));
}

Real
PikaTimeDerivative::computeQpResidual()
{
  return coefficient(_qp) * TimeDerivative::computeQpResidual();
}

Real
PikaTimeDerivative::computeQpJacobian()
{
  return coefficient(_qp) * TimeDerivative::computeQpJacobian();
}
