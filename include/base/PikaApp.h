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

#ifndef PIKAAPP_H
#define PIKAAPP_H

#include "MooseApp.h"


/**
 * The main application for the Pika phase-field model
 */
class PikaApp : public MooseApp
{
public:
  PikaApp(InputParameters parameters);
  static InputParameters validParams();
  virtual ~PikaApp();
  static void registerApps();
  static void registerAll(Factory &, ActionFactory &, Syntax &);
};

#endif /* PIKAAPP_H */
