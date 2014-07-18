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

// Materials
#include "ConstantProperties.h"
#include "PhaseFieldProperties.h"
#include "IceProperties.h"
#include "AirProperties.h"
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
#include "ScaledPhaseTransition.h"

// AuxKernels
#include "ErrorFunctionAux.h"
#include "PikaInterfaceVelocity.h"
#include "SharpInterfaceCheckIce.h"
#include "SharpInterfaceCheckAir.h"
#include "SharpInterfaceCheckVapor.h"

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
  registerUserObject(PropertyUserObject);

  // Materials
  registerMaterial(ConstantProperties);
  registerMaterial(PhaseFieldProperties);
  registerMaterial(IceProperties);
  registerMaterial(AirProperties);
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
  registerKernel(ScaledPhaseTransition);

  // InitialConditions
  registerInitialCondition(ChemicalPotentialIC);
  registerInitialCondition(KaempferAnalyticPhaseIC);

  // AuxKernels
  registerAux(ErrorFunctionAux);
  registerAux(PikaInterfaceVelocity);
  registerAux(SharpInterfaceCheckIce);
  registerAux(SharpInterfaceCheckAir);
  registerAux(SharpInterfaceCheckVapor);
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
