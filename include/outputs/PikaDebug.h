/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef PIKADEBUG_H
#define PIKADEBUG_H

// MOOSE includes
#include "PetscOutput.h"
#include "FormattedTable.h"
#include "PropertyUserObjectInterface.h"
#include "PhaseFieldProperties.h"
class PikaDebug;

template<>
InputParameters validParams<PikaDebug>();

/**
 * Base class for scalar variables and postprocessors output objects
 *
 * This class populates three FormattedTable objects that may then be used
 * by child classes for creating custom output objects:
 * _all_data_table - includes the data from both postprocessors and scalar aux variables
 * _postprocessor_table - includes the data from only the postprocessors
 * _scalar_table - includes the data from only the scalar aux variables
 *
 * @see CSV Console
 */
class PikaDebug :
  public
  PetscOutput,
  PropertyUserObjectInterface,
  MaterialPropertyInterface
{
  public:

  /**
   * Class constructor.
   */
  PikaDebug(const std::string & name, InputParameters);

  /**
   * Destructor
   */
  virtual ~PikaDebug();

  protected:

  //@{
  /**
   * Produces an error, it is not possible to output nodal and elemental data to a table
   *
   * The call to this function is disable by suppressing the input parameter: output_nodal_variables
   */
  virtual void outputNodalVariables();
  virtual void outputElementalVariables();
  virtual void outputScalarVariables();
  virtual void outputPostprocessors();
  virtual void outputVectorPostprocessors();
  virtual std::string filename();
  //@}
virtual void output();
const Real & _d_o;
const Real & _beta;
};

#endif /* TABLEOUTPUT_H */
