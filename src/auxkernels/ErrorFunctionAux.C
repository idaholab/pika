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

ErrorFunctionAux::ErrorFunctionAux(const InputParameters & parameters) :
    FunctionAux(parameters),
    _soln(coupledValue("solution_variable")),
    _error_type(getParam<MooseEnum>("error_type"))
{
}

Real
ErrorFunctionAux::computeValue()
{
  // Get that exact solution
  Real exact = FunctionAux::computeValue();

  // Compute the absolute difference of the solution and the exact value
  Real output = std::abs(exact - _soln[_qp]);

  // Make the error relative
  if (_error_type >= 1)
  {
    output /= _soln[_qp];

    // Make it a percent of the exact
    if (_error_type == 2)
      output *= 100.0;
  }

  return output;
}
