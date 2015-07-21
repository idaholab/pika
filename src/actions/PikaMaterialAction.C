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

// Moose includes
#include "InputParameters.h"
#include "ActionFactory.h"
#include "ActionWarehouse.h"
#include "MooseObjectAction.h"

// Pika includes
#include "PikaMaterialAction.h"
#include "PikaMaterial.h"

template<>
InputParameters validParams<PikaMaterialAction>()
{
  InputParameters params = validParams<Action>();

  // Add the constant properties that are defined by the various objects
  params += PropertyUserObject::objectParams();

  // Add the block parameter
  params.addParam<std::vector<SubdomainName> >("block", std::vector<SubdomainName>(1, "0"), "The list subdomain ids that the generated materials should be limited");

  // Add the variables needed
  params.addRequiredCoupledVar("temperature", "The temperature variable to couple");
  params.addRequiredCoupledVar("phase", "The phase-field variable to couple ");

  // Parameters for outputting Material properties
  params.addParam<std::vector<OutputName> >("outputs", std::vector<OutputName>(1, "none"), "Vector of output names were you would like to restrict the output of material data (empty outputs to all)");
  params.addParam<std::vector<std::string> >("output_properties", "List of material properties, from this material, to output (outputs must also be defined to an output type)");

  return params;
}

PikaMaterialAction::PikaMaterialAction(InputParameters params) :
  Action(params)
{
}

PikaMaterialAction::~PikaMaterialAction()
{
}

void
PikaMaterialAction::act()
{
  // Add the UserObject containing constants and property calculations
  create("AddUserObjectAction", "PropertyUserObject", "UserObjects/_pika_property_user_object");
  create("AddMaterialAction", "PikaMaterial", "Materials/_pika_material");
}

void
PikaMaterialAction::create(std::string action_name, std::string type, std::string object_name)
{
  // Setup the action parameters
  InputParameters params = _action_factory.getValidParams(action_name);
  params.set<ActionWarehouse *>("awh") = &_awh;
  params.set<std::string>("type") = type;

  // Create the actions
  MooseSharedPointer<MooseObjectAction> action = MooseSharedNamespace::static_pointer_cast<MooseObjectAction>
    (_action_factory.create(action_name, object_name, params));

  // Apply the parameters from this action
  action->getObjectParams().applyParameters(parameters());

  // This should be done by applyParameters, but for some reason it is not (see MOOSE #3851)
  action->getObjectParams().set<std::vector<OutputName> >("outputs") = getParam<std::vector<OutputName> >("outputs");
  action->getObjectParams().set<std::vector<std::string> >("output_properties") = getParam<std::vector<std::string> >("output_properties");
  _awh.addActionBlock(action);
}
