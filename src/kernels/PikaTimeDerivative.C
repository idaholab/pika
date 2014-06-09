#include "PikaTimeDerivative.h"

template<>
InputParameters validParams<PikaTimeDerivative>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addParam<Real>("coefficient", 1.0, "Time derivative coefficient");
  params.addParam<std::string>("property", "The name of the material property to utilize as the coefficient");
  params.addParam<Real>("offset", 0., "Offset added to the material property value");
  params.addParam<Real>("scale", 1., "Multiplier applied to the material property value");
//  params.addParam<Real>("hasMaterial", 0, "Boolean showing that material property has been assigned");
  return params;
}

PikaTimeDerivative::PikaTimeDerivative(const std::string & name, InputParameters parameters) :
    TimeDerivative(name, parameters),
    _has_material(isParamValid("property")),
    _coefficient(getParam<Real>("coefficient")),
    _material_coefficient(NULL),
    _scale(getParam<Real>("scale")),
    _offset(getParam<Real>("offset"))

{
   if (_has_material)
   {
      mooseWarning(" Material property is being used and ignoring any coefficient inputs.");
      _material_coefficient = &getMaterialProperty<Real>(getParam<std::string>("property"));
   }
}

Real
PikaTimeDerivative::computeQpResidual()
{
    if (_has_material)
     return (_scale * ((*_material_coefficient)[_qp]) + _offset) * TimeDerivative::computeQpResidual();

    else
      return (_scale *_coefficient+_offset) * TimeDerivative::computeQpResidual();
}

Real
PikaTimeDerivative::computeQpJacobian()
{
    if (_has_material)
     return (_scale * ((*_material_coefficient)[_qp]) + _offset) * TimeDerivative::computeQpJacobian();
    else
      return (_scale *_coefficient+_offset) * TimeDerivative::computeQpJacobian();
}
