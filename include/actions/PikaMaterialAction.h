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

#ifndef PIKAMATERIALACTION_H
#define PIKAMATERIALACTION_H

// MOOSE includes
#include "Action.h"

// Forward declerations
class PikaMaterialAction;
class MooseObjectAction;

template<>
InputParameters validParams<PikaMaterialAction>();

/**
 * Setups the necessary infrastructure for the various material properties.
 *
 * This method creates:
 *   (1) PropertyUserObject that defines all of the constants values as well as functions
 *       that are required both in materials and initial conditions.
 *   (2) AirProperties - contains properties relating to air and water vapor
 *   (3) IceProperties - contains properties relating to ice
 *   (4) PhaseFieldProperties - contains properties related to the the phase field equation
 *   (5) ConstantProperties - converts constants defined in the PropertyUserObject into
 *                          material proprieties for access inside of Kernels.
 *
 * Note: This action does not create the aforementioned objects themselves, it creates the
 * actions that will then build the objects.
 */
class PikaMaterialAction : public Action
{
public:

  /**
   * Class constructor
   * @param name Name of the action
   * @param params Input parameters associated with this actions
   */
  PikaMaterialAction(InputParameters params);

  /**
   * Class destructor
   */
  virtual ~PikaMaterialAction();

  /**
   * Creates the various materials and user objects needed for Pika
   */
  virtual void act();

private:

  /**
   * Builds a MooseObject action
   * @param action_name The type of action to create
   * @param type The type object that the action will build
   * @param object_name The longname of the object
   */
  void create(std::string action_name, std::string type, std::string object_name);
};

#endif //PIKAMATERIALACTION_H
