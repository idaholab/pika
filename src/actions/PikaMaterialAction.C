/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

// Pika includes
#include "PikaMaterialAction.h"

// Moose includes
#include "InputParameters.h"
#include "ActionFactory.h"
#include "ActionWarehouse.h"
#include "MooseObjectAction.h"

template<>
InputParameters validParams<PikaMaterialAction>()
{
  InputParameters params = validParams<Action>();
  params.addParam<Real>("atmospheric_pressure", 1.01325e5, "Atmospheric pressure, P_a [Pa]");

  params.addParam<std::vector<SubdomainName> >("block", std::vector<SubdomainName>(1,"0"), "The list subdomain ids that the generated materials should be limited");

  params.addCoupledVar("temperature", 273.15, "The temperature variable to couple (default: 273.15)");
  params.addCoupledVar("phi", 1, "The phase-field variable to couple (default: 1)");

  params.addParamNamesToGroup("atmospheric_pressure", "General");
  return params;
}

PikaMaterialAction::PikaMaterialAction(const std::string & name, InputParameters params) :
  Action(name, params)
{
}

PikaMaterialAction::~PikaMaterialAction()
{
}

void
PikaMaterialAction::act()
{
  // Add the UserObject containing constants and property calculations
  MooseObjectAction * uo = create("AddUserObjectAction", "PropertyUserObject", "UserObjects/_pika_property_user_object");

 MooseObjectAction * constants = create("AddMaterialAction", "ConstantProperties", "Materials/_pika_constant_properties");

  // Add Materials, being sure to pass down the coupled variables
  MooseObjectAction * air = create("AddMaterialAction", "AirProperties", "Materials/_pika_air_properties");
  applyCoupledVar("temperature", air->getObjectParams());

  MooseObjectAction * ice = create("AddMaterialAction", "IceProperties", "Materials/_pika_ice_properties");
  applyCoupledVar("temperature", ice->getObjectParams());

  MooseObjectAction * phase = create("AddMaterialAction", "PhaseFieldProperties", "Materials/_pika_phase_field_properties");
  applyCoupledVar("phi", phase->getObjectParams());
  applyCoupledVar("temperature", phase->getObjectParams());

  // Add the actions to the ActionWarehouse
  _awh.addActionBlock(uo);
  _awh.addActionBlock(constants);
  _awh.addActionBlock(air);
  _awh.addActionBlock(ice);
  _awh.addActionBlock(phase);
}
MooseObjectAction *
PikaMaterialAction::create(std::string action_name, std::string type, std::string object_name)
{
  // Setup the action parameters
  InputParameters params = _action_factory.getValidParams(action_name);
  params.set<ActionWarehouse *>("awh") = &_awh;
  params.set<std::string>("type") = type;

  // Create the actions
  MooseObjectAction * action = static_cast<MooseObjectAction *>(_action_factory.create(action_name, object_name, params));

  // Apply the parameters from this action
  action->getObjectParams().applyParameters(getParams());
  return action;
}

void
PikaMaterialAction::applyCoupledVar(const std::string & coupled_name, InputParameters & object_params)
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
