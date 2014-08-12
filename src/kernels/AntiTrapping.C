/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "AntiTrapping.h"

template<>
InputParameters validParams<AntiTrapping>()
{
  InputParameters params = validParams<PikaCoupledTimeDerivative>();
  params.addRequiredCoupledVar("coupled_variable", "Variable to being differentiated with respect to time");
  return params;
}

AntiTrapping::AntiTrapping(const std::string & name, InputParameters parameters) :
    PikaCoupledTimeDerivative(name,parameters),
    _var_dot(coupledDot("coupled_variable")),
    _dvar_dot_dvar(coupledDotDu("coupled_variable")),
    _v_var(coupled("coupled_variable"))
{
}

Real
AntiTrapping::computeQpResidual()
{
  return coefficient(_qp) * _test[_i][_qp] * _var_dot[_qp];
}

Real
AntiTrapping::computeQpJacobian()
{
  return 0.0;
}

Real
AntiTrapping::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _v_var)
    return coefficient(_qp) * _test[_i][_qp]*_phi[_j][_qp]*_dvar_dot_dvar[_qp];
  else
    return 0.0;
}
