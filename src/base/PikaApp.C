/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "PikaApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ActionFactory.h"

// Modules
#include "PhaseFieldApp.h"
#include "HeatConductionApp.h"

// UserObjects
#include "PropertyUserObject.h"

// Postprocessors
#include "PikaPhaseTimestepPostprocessor.h"

// Materials
#include "PikaMaterial.h"
#include "TensorMobilityMaterial.h"

// Kernels
#include "PikaTimeDerivative.h"
#include "PikaCoupledTimeDerivative.h"
#include "PikaDiffusion.h"
#include "PhaseTransition.h"
#include "TensorDiffusion.h"
#include "MassTransportSourceMMS.h"
#include "HeatEquationSourceMMS.h"
#include "PhaseEvolutionSourceMMS.h"
#include "MaterialUserForcingFunction.h"
#include "DoubleWellPotential.h"
#include "DoubleWellPotentialMMS.h"

// AuxKernels
#include "ErrorFunctionAux.h"
#include "PikaInterfaceVelocity.h"
#include "PikaWaterVaporConcentration.h"
#include "PikaSupersaturation.h"
#include "SharpInterfaceCheckIce.h"
#include "SharpInterfaceCheckAir.h"
#include "SharpInterfaceCheckVapor.h"
#include "PikaPhaseInitializeAux.h"

// InitialConditions
#include "KaempferAnalyticPhaseIC.h"
#include "PikaCriteria.h"

// Actions
#include "PikaMaterialAction.h"
#include "PikaCriteriaAction.h"

//Functions
#include "ChemicalPotentialFunction.h"

template<>
InputParameters validParams<PikaApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

PikaApp::PikaApp(const std::string & name, InputParameters parameters) :
    MooseApp(name, parameters)
{
  srand(processor_id());

  Moose::registerObjects(_factory);
  PhaseFieldApp::registerObjects(_factory);
  HeatConductionApp::registerObjects(_factory);
  PikaApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  PhaseFieldApp::associateSyntax(_syntax, _action_factory);
  HeatConductionApp::associateSyntax(_syntax, _action_factory);
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
  // UserObjects
  registerUserObject(PropertyUserObject);

  // Postprocessors
  registerPostprocessor(PikaPhaseTimestepPostprocessor);

  // Materials
  registerMaterial(PikaMaterial);
  registerMaterial(TensorMobilityMaterial);

  // Kernels
  registerKernel(PikaTimeDerivative);
  registerKernel(PikaCoupledTimeDerivative);
  registerKernel(PikaDiffusion);
  registerKernel(PhaseTransition);
  registerKernel(TensorDiffusion);
  registerKernel(MassTransportSourceMMS);
  registerKernel(HeatEquationSourceMMS);
  registerKernel(PhaseEvolutionSourceMMS);
  registerKernel(MaterialUserForcingFunction);
  registerKernel(DoubleWellPotential);
  registerKernel(DoubleWellPotentialMMS);

  // InitialConditions
  registerInitialCondition(KaempferAnalyticPhaseIC);

  // AuxKernels
  registerAux(ErrorFunctionAux);
  registerAux(PikaInterfaceVelocity);
  registerAux(PikaWaterVaporConcentration);
  registerAux(PikaSupersaturation);
  registerAux(SharpInterfaceCheckIce);
  registerAux(SharpInterfaceCheckAir);
  registerAux(SharpInterfaceCheckVapor);
  registerAux(PikaCriteria);
  registerAux(PikaPhaseInitializeAux);

  //Functions
  registerFunction(ChemicalPotentialFunction);

}

void
PikaApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  // Actions
  registerTask("setup_pika_material", false);
  registerAction(PikaMaterialAction, "setup_pika_material");

  registerTask("setup_pika_criteria", false);
  registerAction(PikaCriteriaAction, "setup_pika_criteria");

  // Add the task dependency
  addTaskDependency("add_material", "setup_pika_material");
  addTaskDependency("add_user_object", "setup_pika_material");
  addTaskDependency("setup_material_output", "setup_pika_criteria");
  addTaskDependency("setup_pika_criteria", "add_material");

  // Add the action syntax
  syntax.registerActionSyntax("PikaMaterialAction", "PikaMaterials");
  syntax.registerActionSyntax("PikaCriteriaAction", "PikaCriteriaOutput");
}
