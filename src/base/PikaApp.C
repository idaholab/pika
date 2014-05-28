#include "PikaApp.h"
#include "Moose.h"
#include "AppFactory.h"

// Modules
#include "PhaseFieldApp.h"
#include "HeatConductionApp.h"

// UserObjects
#include "ChemicalPotentialPropertyUserObject.h"

// Materials
#include "ConstantProperties.h"
#include "PhaseFieldProperties.h"
#include "IceProperties.h"
#include "AirProperties.h"
#include "TensorMobilityMaterial.h"

// Kernels
#include "MaterialTimeDerivative.h"
#include "CoefficientTimeDerivative.h"
#include "PhaseFieldPotential.h"
#include "PhaseTransition.h"
#include "StefanCondition.h"
#include "TensorDiffusion.h"

// InitialConditions
#include "ChemicalPotentialIC.h"
#include "KaempferAnalyticPhaseIC.h"

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

  // Materials
  registerMaterial(ConstantProperties);
  registerMaterial(PhaseFieldProperties);
  registerMaterial(IceProperties);
  registerMaterial(AirProperties);
  registerMaterial(TensorMobilityMaterial);

  // Kernels
  registerKernel(MaterialTimeDerivative);
  registerKernel(CoefficientTimeDerivative);
  registerKernel(PhaseFieldPotential);
  registerKernel(PhaseTransition);
  registerKernel(StefanCondition);
  registerKernel(TensorDiffusion);

  // InitialConditions
  registerInitialCondition(ChemicalPotentialIC);
  registerInitialCondition(KaempferAnalyticPhaseIC);

}

void
PikaApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}
