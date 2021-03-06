#include "LamaApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

template<>
InputParameters validParams<LamaApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  params.set<bool>("use_legacy_output_syntax") = false;

  return params;
}

LamaApp::LamaApp(InputParameters parameters) :
    MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  LamaApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  LamaApp::associateSyntax(_syntax, _action_factory);
}

LamaApp::~LamaApp()
{
}

// External entry point for dynamic application loading
extern "C" void LamaApp__registerApps() { LamaApp::registerApps(); }
void
LamaApp::registerApps()
{
  registerApp(LamaApp);
}

// External entry point for dynamic object registration
extern "C" void LamaApp__registerObjects(Factory & factory) { LamaApp::registerObjects(factory); }
void
LamaApp::registerObjects(Factory & factory)
{
}

// External entry point for dynamic syntax association
extern "C" void LamaApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { LamaApp::associateSyntax(syntax, action_factory); }
void
LamaApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}
