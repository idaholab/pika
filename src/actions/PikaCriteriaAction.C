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

template<>
InputParameters validParams<PikaCriteriaAction>()
{
  InputParameters params = validParams<Action>();
  params.addParam<bool>("ice_criteria", true, "Compute the criteria for ice, Eq. (43)a");
  params.addParam<bool>("air_criteria", true, "Compute the criteria for air, Eq. (43)b");
  params.addParam<bool>("vapor_criteria", true, "Compute the criteria for vapor, Eq. (43)c");
  params.addParam<bool>("interface_velocity", true, "Compute the interface velocity, Eq. (23)");
  params.addParam<bool>("super_saturation", true, "Compute the super saturation, Eqs. (30)-(32)");

  params.addRequiredCoupledVar("phase", "Phase-field variable");
  params.addRequiredCoupledVar("chemical_potential", "Chemical potential variable");
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
    addCriteriaAction("ice");

  if (getParam<bool>("air_criteria"))
    addCriteriaAction("air");

  if (getParam<bool>("vapor_criteria"))
    addCriteriaAction("vapor");

  if (getParam<bool>("interface_velocity"))
    addAction("PikaInterfaceVelocity", "velocity");

  if (getParam<bool>("super_saturation"))
    addAction("PikaSupersaturation", "super_saturation");
}

void
PikaCriteriaAction::addAction(const std::string & type, const std::string & name)
{
  MooseObjectAction * action = createAction(type, name);
  applyCoupledVar("phase", action->getObjectParams());
  applyCoupledVar("chemical_potential", action->getObjectParams());
  _awh.addActionBlock(action);
}

void
PikaCriteriaAction::addCriteriaAction(const std::string & name)
{
  MooseObjectAction * action = createAction("PikaCriteria", name);
  action->getObjectParams().set<MooseEnum>("criteria") = name;
  _awh.addActionBlock(action);
}

MooseObjectAction *
PikaCriteriaAction::createAction(const std::string & type, const std::string & name)
{
  // Set the AuxKernel action properties
  std::ostringstream long_name;
  long_name << "AuxKernels/_pika_" << name << "_aux_kernel";
  InputParameters action_params = _action_factory.getValidParams("AddKernelAction");
  action_params.set<std::string>("type") = type;
  action_params.set<ActionWarehouse *>("awh") = &_awh;
  action_params.set<std::string>("registered_identifier") = "(AutoBuilt)";
  action_params.set<std::string>("task") = "add_aux_kernel";

  // Create the action
  MooseObjectAction * action = static_cast<MooseObjectAction *>(_action_factory.create("AddKernelAction", long_name.str(), action_params));

  // Set the variable name
  std::ostringstream var_name;
  var_name << "_pika_" << name << "_aux";
  action->getObjectParams().set<AuxVariableName>("variable") = var_name.str();
  action->getObjectParams().set<std::vector<MooseEnum> >("execute_on")[0] = "timestep";

  // Add the variable
  FEType fe_type(CONSTANT, MONOMIAL);
  _problem->addAuxVariable(var_name.str(), fe_type);

  // Return the action
  return action;
}


void
PikaCriteriaAction::applyCoupledVar(const std::string & coupled_name, InputParameters & object_params)
{
  if (getParams().hasDefaultCoupledValue(coupled_name))
    object_params.addCoupledVar(coupled_name,
                                getParams().defaultCoupledValue(coupled_name),
                                getParams().getDocString(coupled_name));
  else
  {
    object_params.addCoupledVar(coupled_name, getParams().getDocString(coupled_name));
    object_params.set<std::vector<VariableName> >(coupled_name) = getParams().get<std::vector<VariableName> >(coupled_name);
  }
}
