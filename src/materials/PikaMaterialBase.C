
#include "PikaMaterialBase.h"
#include "InputParameters.h"

template<>
InputParameters validParams<PikaMaterialBase>()
{
  InputParameters params = validParams<Material>();
  params.addParam<UserObjectName>("property_user_object", "User object containing material property methods calculations. Defaults to the PropertyUserObject created by the PikaMaterial action");

  /* Generally, the PikaMaterial action will build the correct method, only specify the
     object if you know what you are doing */
  params.addParamNamesToGroup("property_user_object", "Advanced");

  return params;
}

PikaMaterialBase::PikaMaterialBase(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    _property_uo(isParamValid("property_user_object") ?
                 getUserObject<PropertyUserObject>("property_user_object") :
                 getUserObjectByName<PropertyUserObject>("_pika_property_user_object"))
{
}
