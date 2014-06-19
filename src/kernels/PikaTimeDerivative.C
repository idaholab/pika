#include "PikaTimeDerivative.h"

template<>
InputParameters validParams<PikaTimeDerivative>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addParam<std::string>("property", "The name of the material property to be a coefficient on the time derivative. Cannot be specified simultaneaously as a coefficient");
  params.addParam<Real>("offset", 0.0, "Offset added to the coefficient");
  params.addParam<Real>("scale", 1.0, "Multiplier applied to the coefficient");
  params.addParam<Real>("coefficient", "Constant scalar coefficient alternate to a material property coefficient. Cannot be specified simultaneously as property.");
  params.addCoupledVar("differentiated_variable", "Variable actually being differentiated");
//  params.addParam<Real>("hasMaterial", 0, "Boolean showing that material property has been assigned");
  return params;
}

PikaTimeDerivative::PikaTimeDerivative(const std::string & name, InputParameters parameters) :
    TimeDerivative(name, parameters),
    _has_material(isParamValid("property")),
    _material_coefficient(NULL),
    _offset(getParam<Real>("offset")),
    _scale(getParam<Real>("scale")),
    _coefficient(0.0),
   _var_dot(isCoupled("differentiated_variable") ? coupledDot("differentiated_variable") : _u_dot),
    _dvar_dot_dvar(isCoupled("differentiated_variable") ? coupledDotDu("differentiated_variable") : _du_dot_du)
    
{
  if (_has_material && isParamValid("coefficient"))
    mooseError("A material property and a coefficient were specified in a PikaTimeDerivative kernel. Specify only one of them.");

  else if( !_has_material && !isParamValid("coefficient"))
    mooseError(" Neither a material property or a coefficient were specified in a PikaTimeDerivative kernel. Specify only one of them.");

  else if( _has_material)
    _material_coefficient = &getMaterialProperty<Real>(getParam<std::string>("property"));

  else
    _coefficient = getParam<Real>("coefficient");
}


Real
PikaTimeDerivative::computeQpResidual()
{
    if (_has_material)
    {
      return (_scale * ((*_material_coefficient)[_qp]) + _offset) * (_test[_i][_qp]) * _var_dot[_qp]; 
    }

    else
    {
      return (_scale * _coefficient + _offset) * (_test[_i][_qp]) * _var_dot[_qp]; 
    }
}

Real
PikaTimeDerivative::computeQpJacobian()
{
    if (_has_material)
     return  (_scale * ((*_material_coefficient)[_qp]) + _offset) * _test[_i][_qp]*_phi[_j][_qp]*_dvar_dot_dvar[_qp]; 

    else
     return (_scale * _coefficient + _offset) * _test[_i][_qp]*_phi[_j][_qp]*_dvar_dot_dvar[_qp]; 
}
