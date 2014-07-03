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
  params.addParam<bool>("use_temporal_scaling",false, "Temporally scale this kernal with a value specified in PikaMaterials");
  return params;
}

PikaTimeDerivative::PikaTimeDerivative(const std::string & name, InputParameters parameters) :
    TimeDerivative(name, parameters),
    _has_material(isParamValid("property")),
    _material_coefficient(NULL),
    _offset(getParam<Real>("offset")),
    _scale(getParam<Real>("scale")),
    _coefficient(0.0),
    _has_time_scale(getParam<bool>("use_temporal_scaling")),
    _time_scale(0.0)
    
{
  if (_has_material && isParamValid("coefficient"))
    mooseError("A material property and a coefficient were specified in a PikaTimeDerivative kernel. Specify only one of them.");

  else if( !_has_material && !isParamValid("coefficient"))
    mooseError(" Neither a material property or a coefficient were specified in a PikaTimeDerivative kernel. Specify only one of them.");

  else if( _has_material)
    _material_coefficient = &getMaterialProperty<Real>(getParam<std::string>("property"));

  else
    _coefficient = getParam<Real>("coefficient");

   if(_has_time_scale)
      _time_scale = _property_uo.getParam<Real>("temporal_scaling");

   else
     _time_scale = 1.0;

}


Real
PikaTimeDerivative::computeQpResidual()
{
    if (_has_material)
      return _time_scale *(_scale * ((*_material_coefficient)[_qp]) + _offset) * (_test[_i][_qp]) * TimeDerivative::computeQpResidual(); 

    else
      return _time_scale *(_scale * _coefficient + _offset) * (_test[_i][_qp]) * TimeDerivative::computeQpResidual(); 
}

Real
PikaTimeDerivative::computeQpJacobian()
{
    if (_has_material)
     return _time_scale * (_scale * ((*_material_coefficient)[_qp]) + _offset) *  TimeDerivative::computeQpJacobian(); 

    else
     return _time_scale *(_scale * _coefficient + _offset) *  TimeDerivative::computeQpJacobian(); 
}
