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
  void addAction(std::string name);
};
