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

// Main application
#include "PikaApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ActionFactory.h"
#include "MooseSyntax.h"

// Modules
#include "PhaseFieldApp.h"
#include "HeatConductionApp.h"
#include "SolidMechanicsApp.h"

template<>
InputParameters validParams<PikaApp>()
{
  InputParameters params = validParams<MooseApp>();
  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  params.set<bool>("use_legacy_output_syntax") = false;
  return params;
}

PikaApp::PikaApp(InputParameters parameters) :
    MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  PhaseFieldApp::registerObjects(_factory);
  HeatConductionApp::registerObjects(_factory);
  SolidMechanicsApp::registerObjects(_factory);
  PikaApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  PhaseFieldApp::associateSyntax(_syntax, _action_factory);
  HeatConductionApp::associateSyntax(_syntax, _action_factory);
  SolidMechanicsApp::associateSyntax(_syntax, _action_factory);
  PikaApp::associateSyntax(_syntax, _action_factory);
}

PikaApp::~PikaApp()
{
}

void
PikaApp::registerApps()
{
  registerApp(PikaApp);
}

void
PikaApp::registerObjects(Factory & factory)
{
  Registry::registerObjectsTo(factory, {"PikaApp"});
}

void
PikaApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  Registry::registerActionsTo(action_factory, {"PikaApp"});

  // Actions
  registerTask("setup_pika_material", false);

  registerTask("setup_pika_criteria", false);

  // Add the task dependency
  addTaskDependency("add_material", "setup_pika_material");
  addTaskDependency("add_user_object", "setup_pika_material");
  addTaskDependency("setup_material_output", "setup_pika_criteria");
  addTaskDependency("setup_pika_criteria", "add_material");

  // Add the action syntax
  syntax.registerActionSyntax("PikaMaterialAction", "PikaMaterials");
  syntax.registerActionSyntax("PikaCriteriaAction", "PikaCriteriaOutput");
}
