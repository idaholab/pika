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

#include "PhaseTransition.h"

template<>
InputParameters validParams<PhaseTransition>()
{
  InputParameters params = validParams<ACBulk>();
  params += validParams<CoefficientKernelInterface>();
  params.addRequiredCoupledVar("chemical_potential", "The chemical potential variable to couple");
  params.addParam<std::string>("lambda", "lambda", "The name of the material property containing the definition of lambda");
  params.addParam<std::string>("equilibrium_chemical_potential", "equilibrium_chemical_potential", "The name of the material property containing the equilibrium concentration");

  return params;
}

PhaseTransition::PhaseTransition(const InputParameters & parameters) :
    ACBulk(parameters),
    CoefficientKernelInterface(parameters),
    _s(coupledValue("chemical_potential")),
    _lambda(getMaterialProperty<Real>(getParam<std::string>("lambda"))),
    _s_eq(getMaterialProperty<Real>(getParam<std::string>("equilibrium_chemical_potential")))
{
}

Real
PhaseTransition::computeDFDOP(PFFunctionType type)
{
  switch (type)
  {
    case Residual:
     return - coefficient(_qp) * (_lambda[_qp]) * (_s[_qp] - _s_eq[_qp]) * (1.0 - _u[_qp]*_u[_qp])*(1.0 - _u[_qp]*_u[_qp]);

    case Jacobian:
      return coefficient(_qp) *  4.0 * _lambda[_qp] * _u[_qp] * (-_u[_qp] * _u[_qp]+1.0) * (_s[_qp] - _s_eq[_qp]) * _phi[_j][_qp];
  }
  return 0.0;
}
