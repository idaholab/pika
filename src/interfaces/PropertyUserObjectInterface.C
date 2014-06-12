// MOOSE includes
#include "InputParameters.h"
#include "FEProblem.h"

// PIKA includes
#include "PropertyUserObjectInterface.h"

template<>
InputParameters validParams<PropertyUserObjectInterface>()
{
  InputParameters params = emptyInputParameters();
  params.addParam<UserObjectName>("property_user_object", "User object containing material property methods calculations. Defaults to the PropertyUserObject created by the PikaMaterial action");

  /* Generally, the PikaMaterial action will build the correct method, only specify the
     object if you know what you are doing */
  params.addParamNamesToGroup("property_user_object", "Advanced");

  return params;
}

PropertyUserObjectInterface::PropertyUserObjectInterface(const std::string & name, InputParameters parameters) :
    _problem_ptr(parameters.getCheckedPointerParam<FEProblem *>("_fe_problem")),
    _property_uo(parameters.isParamValid("property_user_object") ?
                 _problem_ptr->getUserObject<PropertyUserObject>(parameters.get<UserObjectName>("property_user_object")) :
                 _problem_ptr->getUserObject<PropertyUserObject>("_pika_property_user_object"))
{
}
