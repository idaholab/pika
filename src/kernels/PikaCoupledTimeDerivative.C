#include "PikaCoupledTimeDerivative.h"

template<>
InputParameters validParams<PikaCoupledTimeDerivative>()
{
  InputParameters params = validParams<PikaTimeDerivative>();
  params.addRequiredCoupledVar("coupled_variable", "Variable to being differentiated with respect to time");
  return params;
}

PikaCoupledTimeDerivative::PikaCoupledTimeDerivative(const std::string & name, InputParameters parameters) :
    PikaTimeDerivative(name,parameters),
    _var_dot(coupledDot("coupled_variable")),
    _dvar_dot_dvar(coupledDotDu("coupled_variable")),
    _v_var(coupled("coupled_variable"))
{
}

Real
PikaCoupledTimeDerivative::computeQpResidual()
{
  // Material property coefficient
  if (_has_material)
    return _time_scale * (_scale * ((*_material_coefficient)[_qp]) + _offset) * (_test[_i][_qp]) * _var_dot[_qp];
  // Scalar coefficient
  else
    return _time_scale * (_scale * _coefficient + _offset) * (_test[_i][_qp]) * _var_dot[_qp];
}

Real
PikaCoupledTimeDerivative::computeQpJacobian()
{
  return 0.0;
}

Real
PikaCoupledTimeDerivative::computeQpOffDiagJacobian(unsigned int jvar)
{
  // Off-diagonal term exists
  if (jvar == _v_var)
  {
    // Material property coefficient
    if (_has_material)
     return _time_scale * (_scale * ((*_material_coefficient)[_qp]) + _offset) * _test[_i][_qp]*_phi[_j][_qp]*_dvar_dot_dvar[_qp];

    // Scalar coefficient
    else
     return _time_scale * (_scale * _coefficient + _offset) * _test[_i][_qp]*_phi[_j][_qp]*_dvar_dot_dvar[_qp];
  }

  // No contribution to off-diagonal
  else
    return 0.0;
}
