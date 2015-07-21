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
  params.addParam<bool>("time_criteria", true, "Compute the criteria for time, Eq. (47)");
  params.addParam<bool>("velocity_criteria", true, "Compute the criteria for time, Eq. (45)");
  params.addParam<bool>("interface_velocity", true, "Compute the interface velocity, Eq. (23)");
  params.addParam<bool>("super_saturation", true, "Compute the super saturation, Eqs. (30)-(32)");
  params.addParam<bool>("use_temporal_scaling", false, "Temporally scale this Kernel with a value specified in PikaMaterials");

  // Coupled variables needed
  params.addRequiredCoupledVar("phase", "Phase-field variable");
  params.addRequiredCoupledVar("chemical_potential", "Chemical potential variable");
  params.addRequiredCoupledVar("temperature", "Temperature variable");

  MooseEnum pps_types("min=0 max=1 average=2");
  std::vector<MooseEnum> vec_types(1, pps_types);
  params.addParam<std::vector<MooseEnum> >("ice_postprocessors", vec_types, "Types of postprocessors for ice criteria.");
  params.addParam<std::vector<MooseEnum> >("air_postprocessors", vec_types, "Types of postprocessors for air criteria.");
  params.addParam<std::vector<MooseEnum> >("vapor_postprocessors", vec_types, "Types of postprocessors for vapor criteria.");
  params.addParam<std::vector<MooseEnum> >("time_postprocessors", vec_types, "Types of postprocessors for time  criteria.");
  params.addParam<std::vector<MooseEnum> >("velocity_postprocessors", vec_types, "Types of postprocessors for interface velocity.");
  params.addParam<std::vector<MooseEnum> >("interface_velocity_postprocessors", vec_types, "Types of postprocessors for interface velocity.");
  params.addParam<std::vector<MooseEnum> >("super_saturation_postprocessors", vec_types, "Types of postprocessors for super saturation.");

  params.addParamNamesToGroup("ice_postprocessors air_postprocessors vapor_postprocessors time_postprocessors velocity_postprocessors interface_velocity_postprocessors super_saturation_postprocessors", "Postprocesors");

  return params;
}

PikaCriteriaAction::PikaCriteriaAction(InputParameters parameters) :
    Action(parameters)
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

  if (getParam<bool>("time_criteria"))
    addCriteriaAction("time");

  if (getParam<bool>("velocity_criteria"))
    addCriteriaAction("velocity");

  // If time_criteria or velocity_criteria are true, then the interface velocity is required
  if (getParam<bool>("interface_velocity") || getParam<bool>("time_criteria") || getParam<bool>("velocity_criteria"))
    addAction("PikaInterfaceVelocity", "interface_velocity");

  if (getParam<bool>("super_saturation"))
    addAction("PikaSupersaturation", "super_saturation");
}

void
PikaCriteriaAction::addAction(const std::string & type, const std::string & name)
{
  _awh.addActionBlock(createAction(type, name));
}

void
PikaCriteriaAction::addCriteriaAction(const std::string & name)
{
  MooseSharedPointer<MooseObjectAction> action = createAction("PikaCriteria", name);
  action->getObjectParams().set<MooseEnum>("criteria") = name;
  _awh.addActionBlock(action);
}

MooseSharedPointer<MooseObjectAction>
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
  MooseSharedPointer<MooseObjectAction> action = MooseSharedNamespace::static_pointer_cast<MooseObjectAction>
    (_action_factory.create("AddKernelAction", long_name.str(), action_params));

  // Set the variable name other object parameters
  std::ostringstream var_name;
  var_name << "_pika_" << name << "_aux";
  InputParameters & object_params = action->getObjectParams();
  object_params.set<AuxVariableName>("variable") = var_name.str();
  object_params.set<MultiMooseEnum>("execute_on") = "timestep_end";
//  object_params.set<bool>("use_temporal_scaling") = getParam<bool>("use_temporal_scaling");
  object_params.set<Real>("coefficient") = 1.0;
  object_params.applyParameters(_pars);

  // Add the variable
  FEType fe_type(CONSTANT, MONOMIAL);
  _problem->addAuxVariable(var_name.str(), fe_type);

  // Add the postprocessors actions
  createPostprocessorActions(name, var_name.str());

  // Return the action
  return action;
}

void
PikaCriteriaAction::createPostprocessorActions(const std::string & name, const std::string & var_name)
{
  std::vector<MooseEnum> pps = getParam<std::vector<MooseEnum> >(name + "_postprocessors");
  for (std::vector<MooseEnum>::const_iterator it = pps.begin(); it != pps.end(); ++it)
    if (it->isValid())
      addPostprocessorAction(name, var_name, *it);
}

void
PikaCriteriaAction::addPostprocessorAction(const std::string & name, const std::string & var_name, int id)
{
  // Name suffix
  std::string suffix;
  if (id == 0)
    suffix = "min";
  else if (id == 1)
    suffix = "max";
  else
    suffix = "avg";

  // Build the parameters
  std::ostringstream long_name;
  long_name << "Postprocessors/_pika_" << name << "_" << suffix;
  InputParameters action_params = _action_factory.getValidParams("AddPostprocessorAction");
  action_params.set<ActionWarehouse *>("awh") = &_awh;
  action_params.set<std::string>("registered_identifier") = "(AutoBuilt)";
  action_params.set<std::string>("task") = "add_postprocessor";

  // Account for the differing types
  if (id == 0 || id == 1)
    action_params.set<std::string>("type") = "ElementExtremeValue";
  else
    action_params.set<std::string>("type") = "ElementAverageValue";

  // Create the action
  MooseSharedPointer<MooseObjectAction> action = MooseSharedNamespace::static_pointer_cast<MooseObjectAction>
    (_action_factory.create("AddPostprocessorAction", long_name.str(), action_params));
  action->getObjectParams().set<VariableName>("variable") = var_name;
  action->getObjectParams().set<MultiMooseEnum>("execute_on") = "timestep_end";

  // Account for the differing types
  if (id == 0)
    action->getObjectParams().set<MooseEnum>("value_type") = "min";
  else if (id == 1)
    action->getObjectParams().set<MooseEnum>("value_type") = "max";

  // Add the action to the warehouse
  _awh.addActionBlock(action);
}
