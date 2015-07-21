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


// MOOSE includes
#include "PikaDiffusion.h"

template<>
InputParameters validParams<PikaDiffusion>()
{
  InputParameters params = validParams<Diffusion>();
  params += validParams<CoefficientKernelInterface>();
  return params;
}

PikaDiffusion::PikaDiffusion(const InputParameters & parameters) :
    Diffusion(parameters),
    CoefficientKernelInterface(parameters)
{
  // The getMaterialProperty method cannot be replicated in interface
  if (useMaterial())
    setMaterialPropertyPointer(&getMaterialProperty<Real>(getParam<std::string>("property")));
}

Real
PikaDiffusion::computeQpResidual()
{
  return coefficient(_qp) * Diffusion::computeQpResidual();
}

Real
PikaDiffusion::computeQpJacobian()
{
  return coefficient(_qp) * Diffusion::computeQpJacobian();
}
