/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

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

  /* The CoefficientKernelInterface requires the temporal scaling from the property user object, this
   * is passed down via a private parameter */
   params.addPrivateParam<Real>("_temporal_scaling");

  return params;
}

PropertyUserObjectInterface::PropertyUserObjectInterface(const std::string & name, InputParameters & parameters) :
    _problem_ptr(parameters.getCheckedPointerParam<FEProblem *>("_fe_problem")),
    _property_uo(parameters.isParamValid("property_user_object") ?
                 _problem_ptr->getUserObject<PropertyUserObject>(parameters.get<UserObjectName>("property_user_object")) :
                 _problem_ptr->getUserObject<PropertyUserObject>("_pika_property_user_object"))
{
  parameters.set<Real>("_temporal_scaling") = _property_uo.getParam<Real>("temporal_scaling");
}
