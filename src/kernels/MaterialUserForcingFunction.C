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

#include "MaterialUserForcingFunction.h"

template<>
InputParameters validParams<MaterialUserForcingFunction>()
{
  InputParameters params = validParams<UserForcingFunction>();
  params.addRequiredParam<std::string>("material_coefficient", "Provide a material property to multiply the provided function by");
  params.addParam<Real>("scale", 1.0, "Value to scale the material property (e.g. coefficients)");
  return params;
}

MaterialUserForcingFunction::MaterialUserForcingFunction(const InputParameters & parameters) :
    UserForcingFunction(parameters),
    _material_coefficient(getMaterialProperty<Real>(getParam<std::string>("material_coefficient"))),
    _scale(getParam<Real>("scale"))
{
}

Real
MaterialUserForcingFunction::computeQpResidual()
{
  return _scale * _material_coefficient[_qp] * UserForcingFunction::computeQpResidual();
}
