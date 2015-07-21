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

// STL includes
#include <string>

// MOOSE includes
#include "FEProblem.h"
#include "InputParameters.h"
#include "MaterialProperty.h"

// PIKA includes
#include "CoefficientKernelInterface.h"
#include "PropertyUserObject.h"

template<>
InputParameters validParams<CoefficientKernelInterface>()
{
  InputParameters params = validParams<PropertyUserObjectInterface>();
  params.addParam<std::string>("property", "The name of the material property to be a coefficient for this Kernel. Cannot be specified simultaneously with a coefficient");
  params.addParam<Real>("offset", 0.0, "Offset added to the coefficient (material and scalar");
  params.addParam<Real>("scale", 1.0, "Multiplier applied to the coefficient (material and scalar");
  params.addParam<Real>("coefficient", "Constant scalar coefficient alternate to a material property coefficient. Cannot be specified simultaneously with property.");
  params.addParam<bool>("use_temporal_scaling", false, "Temporally scale this Kernel with a value specified in PikaMaterials");
  return params;
}

CoefficientKernelInterface::CoefficientKernelInterface(const InputParameters & parameters) :
    PropertyUserObjectInterface(parameters),
    _use_material(parameters.isParamValid("property")),
    _material_coefficient(NULL),
    _coefficient(parameters.isParamValid("coefficient") ? parameters.get<Real>("coefficient") : 0.0),
    _offset(parameters.get<Real>("offset")),
    _scale(parameters.get<Real>("scale")),
    _time_scale(1.0)
{
  // Produce an error if both material and coefficient are defined
  if (_use_material && parameters.isParamValid("coefficient"))
    mooseError("A material property and a coefficient were specified in a kernel using CoefficientKernelInterface. Specify only one of them.");

  // Produce an error if neither coefficient or material property are defined
  else if ( !_use_material && !parameters.isParamValid("coefficient"))
    mooseError(" Neither a material property or a coefficient were specified in a kernel using CoefficientKernelInterface. Specify only one of them.");

  // If time scaling is used, get the scaling parameter from the user object
  if (parameters.get<bool>("use_temporal_scaling"))
    _time_scale = _property_uo.temporalScale();
}

bool
CoefficientKernelInterface::useMaterial()
{
  return _use_material;
}

void
CoefficientKernelInterface::setMaterialPropertyPointer(const MaterialProperty<libMesh::Real> * ptr)
{
  _material_coefficient = ptr;
}

Real
CoefficientKernelInterface::coefficient(unsigned int qp)
{
  // Material property coefficient
  if (_use_material)
    return _time_scale *(_scale * ((*_material_coefficient)[qp]) + _offset);

  // Scalar coefficient
  else
    return _time_scale *(_scale * _coefficient + _offset);
}
