#include "PikaApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"

template<>
InputParameters validParams<PikaApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

PikaApp::PikaApp(const std::string & name, InputParameters parameters) :
    MooseApp(name, parameters)
{
  srand(libMesh::processor_id());
  
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  PikaApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
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
}

void
PikaApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
