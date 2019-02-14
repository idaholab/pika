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
#include "ModulesApp.h"

template<>
InputParameters validParams<PikaApp>()
{
  InputParameters params = validParams<MooseApp>();
  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  params.set<bool>("use_legacy_output_syntax") = false;
  return params;
}

// When using the new Registry system, this line is required so that
// dependent apps know about the BighornApp label.
registerKnownLabel("PikaApp");

PikaApp::PikaApp(InputParameters parameters) :
    MooseApp(parameters)
{
  PikaApp::registerAll(_factory, _action_factory, _syntax);
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
PikaApp::registerAll(Factory & f, ActionFactory & af, Syntax & syntax)
{
  ModulesApp::registerAll(f, af, syntax);
  Registry::registerObjectsTo(f, {"PikaApp"});
  Registry::registerActionsTo(af, {"PikaApp"});

  // Actions
  registerTask("setup_pika_material", false);
  registerTask("setup_pika_criteria", false);

  // Add the task dependency
  addTaskDependency("add_material", "setup_pika_material");
  addTaskDependency("add_user_object", "setup_pika_material");
  addTaskDependency("setup_pika_criteria", "add_material");

  // Add the action syntax
  syntax.registerActionSyntax("PikaMaterialAction", "PikaMaterials");
  syntax.registerActionSyntax("PikaCriteriaAction", "PikaCriteriaOutput");
}
