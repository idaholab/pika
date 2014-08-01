/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "Action.h"
#include "MooseObjectAction.h"

class PikaCriteriaAction;

template<>
InputParameters validParams<PikaCriteriaAction>();

class PikaCriteriaAction : public Action
{
public:
  PikaCriteriaAction(const std::string & name, InputParameters parameters);

  virtual ~PikaCriteriaAction(){}

  void act();

private:
  void addAction(const std::string & type, const std::string & name);
  void addCriteriaAction(const std::string & name);
  MooseObjectAction * createAction(const std::string & type, const std::string & name);
  void applyCoupledVar(const std::string & coupled_name, InputParameters & object_params);
  void addPostprocessorActionss(const std::string & name, const std::string & var_name);
};
