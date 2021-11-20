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

#ifndef ERRORFUNCTIONAUX_H
#define ERRORFUNCTIONAUX_H

// MOOSE includes
#include "FunctionAux.h"

/**
 * A class for computing the absolute error of a variable
 */
class ErrorFunctionAux : public FunctionAux
{
public:

  /**
   * Class constructor
   * @param name Object name
   * @param parameters Object input parameters
   */
  ErrorFunctionAux(const InputParameters & parameters);
  static InputParameters validParams();

protected:

  /**
   * Computes the error
   */
  virtual Real computeValue();

private:

  /// A reference to the solution variable to compute the error from
  const VariableValue & _soln;

  /// The type of error to compute
  MooseEnum _error_type;

};

#endif //ERRORFUNCTIONAUX_H
