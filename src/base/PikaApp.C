#include "PikaApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ActionFactory.h"

// Modules
#include "PhaseFieldApp.h"
#include "HeatConductionApp.h"

// UserObjects
#include "ChemicalPotentialPropertyUserObject.h"
#include "PropertyUserObject.h"

// Materials
#include "ConstantProperties.h"
#include "PhaseFieldProperties.h"
#include "IceProperties.h"
#include "AirProperties.h"
#include "TensorMobilityMaterial.h"

// Kernels
#include "PikaTimeDerivative.h"
#include "PhaseFieldPotential.h"
#include "PhaseTransition.h"
#include "TensorDiffusion.h"
#include "MassTransportSourceMMS.h"
#include "HeatEquationSourceMMS.h"
#include "MaterialUserForcingFunction.h"

// AuxKernels
#include "ErrorFunctionAux.h"

// InitialConditions
#include "ChemicalPotentialIC.h"
#include "KaempferAnalyticPhaseIC.h"

// Actions
#include "PikaMaterialAction.h"

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
  registerUserObject(ChemicalPotentialPropertyUserObject);
  registerUserObject(PropertyUserObject);

  // Materials
  registerMaterial(ConstantProperties);
  registerMaterial(PhaseFieldProperties);
  registerMaterial(IceProperties);
  registerMaterial(AirProperties);
  registerMaterial(TensorMobilityMaterial);

  // Kernels
  registerKernel(PikaTimeDerivative);
  registerKernel(PhaseFieldPotential);
  registerKernel(PhaseTransition);
  registerKernel(TensorDiffusion);
  registerKernel(MassTransportSourceMMS);
  registerKernel(HeatEquationSourceMMS);
  registerKernel(MaterialUserForcingFunction);

  // InitialConditions
  registerInitialCondition(ChemicalPotentialIC);
  registerInitialCondition(KaempferAnalyticPhaseIC);

  // AuxKernels
  registerAux(ErrorFunctionAux);
}

void
PikaApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  // Actions
  registerTask("setup_pika_material", false);
  registerAction(PikaMaterialAction, "setup_pika_material");

  // Add the task dependency
  addTaskDependency("add_material", "setup_pika_material");
  addTaskDependency("add_user_object", "setup_pika_material");

  // Add the action syntax
  syntax.registerActionSyntax("PikaMaterialAction", "PikaMaterials");



}
