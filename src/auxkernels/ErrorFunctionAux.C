/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "ErrorFunctionAux.h"

template<>
InputParameters validParams<ErrorFunctionAux>()
{

  MooseEnum error_type("absolute=0 relative=1 percent=2", "absolute");

  InputParameters params = validParams<FunctionAux>();
  params.addRequiredCoupledVar("solution_variable", "The variable to compare the function against");
  params.addParam<MooseEnum>("error_type", error_type, "The type of error to compute");
  return params;
}

ErrorFunctionAux::ErrorFunctionAux(const std::string & name, InputParameters parameters) :
    FunctionAux(name, parameters),
    _soln(coupledValue("solution_variable")),
    _error_type(getParam<MooseEnum>("error_type"))
{
}

Real
ErrorFunctionAux::computeValue()
{

  Real exact = FunctionAux::computeValue();

  Real output = std::abs(exact - _soln[_qp]);

  if (_error_type >= 1)
    output /= _soln[_qp];

  if (_error_type == 2)
    output *= 100.0;

  return output;

}
