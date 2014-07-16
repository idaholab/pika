/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef PIKAAPP_H
#define PIKAAPP_H

#include "MooseApp.h"

class PikaApp;

template<>
InputParameters validParams<PikaApp>();

class PikaApp : public MooseApp
{
public:
  PikaApp(const std::string & name, InputParameters parameters);
  virtual ~PikaApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* PIKAAPP_H */
