/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

// Pika includes
#include "PikaCriteriaAction.h"

// MOOSE includes
#include "ActionFactory.h"
#include "FEProblem.h"
#include "MooseObjectAction.h"

template<>
InputParameters validParams<PikaCriteriaAction>()
{
  InputParameters params = validParams<Action>();
  params.addParam<bool>("ice_criteria", true, "Compute the criteria for ice, Eq. (43)a");
  params.addParam<bool>("air_criteria", true, "Compute the criteria for air, Eq. (43)b");
  params.addParam<bool>("vapor_criteria", true, "Compute the criteria for vapor, Eq. (43)c");
  return params;
}

PikaCriteriaAction::PikaCriteriaAction(const std::string & name, InputParameters parameters) :
    Action(name, parameters)
{
}

void
PikaCriteriaAction::act()
{
  if (getParam<bool>("ice_criteria"))
    addAction("ice");
  if (getParam<bool>("air_criteria"))
    addAction("air");
  if (getParam<bool>("vapor_criteria"))
    addAction("vapor");
}

void
PikaCriteriaAction::addAction(std::string name)
{
  // Add the Aux Variable
  std::ostringstream var_name;
  var_name << "_pika_" << name << "_criteria_aux";

  // Set the AuxKernel action propertiers
  std::ostringstream long_name;
  long_name << "AuxKernels/_pika_" << name << "_criteria";
  InputParameters action_params = _action_factory.getValidParams("AddKernelAction");
  action_params.set<std::string>("type") = "PikaCriteria";
  action_params.set<ActionWarehouse *>("awh") = &_awh;
  action_params.set<std::string>("registered_identifier") = "(AutoBuilt)";
  action_params.set<std::string>("task") = "add_aux_kernel";

  MooseObjectAction * action = static_cast<MooseObjectAction *>(_action_factory.create("AddKernelAction", long_name.str(), action_params));
  InputParameters & object_params = action->getObjectParams();
  object_params.set<MooseEnum>("criteria") = name;
  object_params.set<AuxVariableName>("variable") = var_name.str();
  object_params.set<std::vector<MooseEnum> >("execute_on")[0] = "timestep";

  _awh.addActionBlock(action);

  FEType fe_type(CONSTANT, MONOMIAL);
  _problem->addAuxVariable(var_name.str(), fe_type);

}
