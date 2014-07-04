#include "PikaTimeDerivative.h"

template<>
InputParameters validParams<PikaTimeDerivative>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addParam<std::string>("property", "The name of the material property to be a coefficient on the time derivative. Cannot be specified simultaneously with a coefficient");
  params.addParam<Real>("offset", 0.0, "Offset added to the coefficient (material and scalar");
  params.addParam<Real>("scale", 1.0, "Multiplier applied to the coefficient (material and scalar");
  params.addParam<Real>("coefficient", "Constant scalar coefficient alternate to a material property coefficient. Cannot be specified simultaneously with property.");
  params.addParam<bool>("use_temporal_scaling", false, "Temporally scale this Kernel with a value specified in PikaMaterials");
  return params;
}

PikaTimeDerivative::PikaTimeDerivative(const std::string & name, InputParameters parameters) :
    TimeDerivative(name, parameters),
    PropertyUserObjectInterface(name,parameters),
    _has_material(isParamValid("property")),
    _material_coefficient(_has_material ? &getMaterialProperty<Real>(getParam<std::string>("property")) : NULL),
    _coefficient(isParamValid("coefficient") ? getParam<Real>("coefficient") : 0.0),
    _offset(getParam<Real>("offset")),
    _scale(getParam<Real>("scale")),
    _time_scale(getParam<bool>("use_temporal_scaling") ? _property_uo.getParam<Real>("temporal_scaling") : 1.0)

{
  // Produce an error if both material and coefficient are defined
  if (_has_material && isParamValid("coefficient"))
    mooseError("A material property and a coefficient were specified in a PikaTimeDerivative kernel. Specify only one of them.");

  // Produce an error if neither coefficient or material property are defined
  else if( !_has_material && !isParamValid("coefficient"))
    mooseError(" Neither a material property or a coefficient were specified in a PikaTimeDerivative kernel. Specify only one of them.");

}

Real
PikaTimeDerivative::computeQpResidual()
{
  // Material property
  if (_has_material)
    return _time_scale *(_scale * ((*_material_coefficient)[_qp]) + _offset) * (_test[_i][_qp]) * TimeDerivative::computeQpResidual();

  // Scalar coefficient
  else
    return _time_scale *(_scale * _coefficient + _offset) * (_test[_i][_qp]) * TimeDerivative::computeQpResidual();
}

Real
PikaTimeDerivative::computeQpJacobian()
{
  // Material property coefficient
  if (_has_material)
    return _time_scale * (_scale * ((*_material_coefficient)[_qp]) + _offset) *  TimeDerivative::computeQpJacobian();

  // Scalar coefficient
  else
    return _time_scale *(_scale * _coefficient + _offset) *  TimeDerivative::computeQpJacobian();
}
