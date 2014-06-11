#include "ChemicalPotentialIC.h"
#include "PropertyUserObject.h"
template<>
InputParameters validParams<ChemicalPotentialIC>()
{
  InputParameters params = validParams<InitialCondition>();
  params.addParam<UserObjectName>("property_user_object", "_pika_property_user_object", "User object containing material property methods calculations");
  params.addRequiredCoupledVar("temperature", "The temperature variable");
  return params;
}

ChemicalPotentialIC::ChemicalPotentialIC(const std::string & name, InputParameters parameters) :
    InitialCondition(name, parameters),
    _property_uo(getUserObject<PropertyUserObject>("property_user_object")),
    _temperature(coupledValue("temperature"))
{
}

Real
ChemicalPotentialIC::value(const Point & /*p*/)
{
  return _property_uo.equilibriumConcentration(_temperature[_qp]);
}
