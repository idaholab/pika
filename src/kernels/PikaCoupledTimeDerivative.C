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

#include "PikaCoupledTimeDerivative.h"

template<>
InputParameters validParams<PikaCoupledTimeDerivative>()
{
  InputParameters params = validParams<PikaTimeDerivative>();
  params.addRequiredCoupledVar("coupled_variable", "Variable to being differentiated with respect to time");
  return params;
}

PikaCoupledTimeDerivative::PikaCoupledTimeDerivative(const InputParameters & parameters) :
    PikaTimeDerivative(parameters),
    _var_dot(coupledDot("coupled_variable")),
    _dvar_dot_dvar(coupledDotDu("coupled_variable")),
    _v_var(coupled("coupled_variable"))
{
}

Real
PikaCoupledTimeDerivative::computeQpResidual()
{
  return coefficient(_qp) * _test[_i][_qp] * _var_dot[_qp];
}

Real
PikaCoupledTimeDerivative::computeQpJacobian()
{
  return 0.0;
}

Real
PikaCoupledTimeDerivative::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _v_var)
    return coefficient(_qp) * _test[_i][_qp]*_phi[_j][_qp]*_dvar_dot_dvar[_qp];
  else
    return 0.0;
}
