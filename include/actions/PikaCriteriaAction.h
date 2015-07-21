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

// MOOSE includes
#include "Action.h"
#include "MooseObjectAction.h"

// Forward declarations
class PikaCriteriaAction;

template<>
InputParameters validParams<PikaCriteriaAction>();

/**
 * Creates necessary objects for outputing the various Phase-field related criterial checking objects.
 */
class PikaCriteriaAction : public Action
{
public:
  PikaCriteriaAction(InputParameters parameters);
  virtual ~PikaCriteriaAction(){}

  /**
   * Builds the required objects based on the selected output types
   */
  void act();

private:

  /**
   * A helper method for adding an action to the ActionWarhouse
   * @param type The type of object that the action is to create
   * @param name The name of the object that the action is to create
   */
  void addAction(const std::string & type, const std::string & name);

  /**
   * A helper method for adding a PikaCriteria AuxKernel action the ActionWarhouse
   * @param name The name of the object that the action is to create
   */
  void addCriteriaAction(const std::string & name);

  /**
   * A helper method for creating an MooseObjectAction
   * @param type The type of object to create
   * @param name The name of the object to create
   */
  MooseSharedPointer<MooseObjectAction> createAction(const std::string & type, const std::string & name);

  /**
   * Create the actions necessary for the postprocessor min/max/average outputs
   * @param name The name of the Postprocessor to create
   * @maram variable The variable name that the Postprocessor is operating on
   */
  void createPostprocessorActions(const std::string & name, const std::string & var_name);


  /**
   * Adds an action associated with postprocessor min/max/average outputs
   * @param name The name of the object generated
   * @param var_name The variable name the Postprocessor should act upon
   * @param type_id The type of computation (0 min, 1 max, 2 average)
   */
  void addPostprocessorAction(const std::string & name, const std::string & var_name, int type_id);
};
