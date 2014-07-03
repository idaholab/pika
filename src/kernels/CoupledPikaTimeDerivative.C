#include "CoupledPikaTimeDerivative.h"

template<>
InputParameters validParams<CoupledPikaTimeDerivative>()
{
  InputParameters params = validParams<PikaTimeDerivative>();
  params.addRequiredCoupledVar("differentiated_variable", "Variable actually being differentiated");
  params.addParam<bool>("use_temporal_scaling");
  return params;
}

CoupledPikaTimeDerivative::CoupledPikaTimeDerivative(const std::string & name, InputParameters parameters) :
    PikaTimeDerivative(name,parameters),
    _var_dot(isCoupled("differentiated_variable") ? coupledDot("differentiated_variable") : _u_dot),
    _dvar_dot_dvar(isCoupled("differentiated_variable") ? coupledDotDu("differentiated_variable") : _du_dot_du),
    _v_var(coupled("differentiated_variable"))
    
{
  if(_time_scale)
    _xi = _property_uo.getParam<Real>("temporal_scaling");

  else
    _xi = 1.0;
}


Real
CoupledPikaTimeDerivative::computeQpResidual()
{
    if (_has_material)
      return _xi * (_scale * ((*_material_coefficient)[_qp]) + _offset) * (_test[_i][_qp]) * _var_dot[_qp]; 

    else
      return _xi * (_scale * _coefficient + _offset) * (_test[_i][_qp]) * _var_dot[_qp]; 
}

Real
CoupledPikaTimeDerivative::computeQpJacobian()
{
  return 0.0;
}

Real
CoupledPikaTimeDerivative::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _var)
  {
    if (_has_material)
     return _xi * (_scale * ((*_material_coefficient)[_qp]) + _offset) * _test[_i][_qp]*_phi[_j][_qp]*_dvar_dot_dvar[_qp]; 

    else
     return _xi * (_scale * _coefficient + _offset) * _test[_i][_qp]*_phi[_j][_qp]*_dvar_dot_dvar[_qp]; 
  }
  else
    return 0.0;
}
