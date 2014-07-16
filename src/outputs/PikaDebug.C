/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

// MOOSE includes
#include "PikaDebug.h"
#include "FEProblem.h"
#include "Postprocessor.h"
#include "PetscSupport.h"
#include "Executioner.h"
#include "MooseApp.h"
#include "Conversion.h"

// libMesh includes
#include "libmesh/string_to_enum.h"

template<>
InputParameters validParams<PikaDebug>()
{
  // Fit mode selection Enum
  MooseEnum pps_fit_mode(FormattedTable::getWidthModes());

  // Base class parameters
  InputParameters params = validParams<PetscOutput>();
  params.addParam<unsigned int>("_tid",0,"HACKED thread ID, fix later!");
  // Suppressing the output of nodal and elemental variables disables this type of output
  params.suppressParameter<bool>("output_elemental_variables");
  params.suppressParameter<bool>("output_nodal_variables");
  params.suppressParameter<bool>("elemental_as_nodal");
  params.suppressParameter<bool>("scalar_as_nodal");
  params.suppressParameter<bool>("output_input");
  params.suppressParameter<bool>("output_postprocessors");
  params.suppressParameter<bool>("output_vector_postprocessors");
  params.suppressParameter<bool>("file_base");

  return params;
}

PikaDebug::PikaDebug(const std::string & name, InputParameters parameters) :
    PetscOutput(name, parameters),
    PropertyUserObjectInterface(name, parameters),
    MaterialPropertyInterface(name,parameters),
   _d_o(_property_uo.getParam<Real>("capillary_length")),
   _beta(_property_uo.getParam<Real>("interface_kinetic_coefficient"))

{
}

PikaDebug::~PikaDebug()
{
}

void
PikaDebug::outputNodalVariables()
{
  mooseError("Nodal nonlinear variable output not supported by PikaDebug output class");
}

void
PikaDebug::outputElementalVariables()
{
  mooseError("Elemental nonlinear variable output not supported by PikaDebug output class");
}

void
PikaDebug::outputPostprocessors()
{
  //MOOSE Error
}

void
PikaDebug::outputVectorPostprocessors()
{
  //Moose Error
}

void
PikaDebug::outputScalarVariables()
{
  //Moose Error
}

std::string PikaDebug::filename()
{
  //Moose Error
  return std::string();
}

void
PikaDebug::output()
{
  _console << "Moose Test in pika" << std::endl;
  _console<< "Temporal Scale Value = "<<  _property_uo.temporalScale()<<std::endl;
  _console<< "Interface Thickness  = "<<  _property_uo._W<<std::endl;
  _console<< "Capillary Length (d_o)  = "<<  _d_o<<std::endl;
  _console<< "Interface Kinetic Coefficient (beta)  = "<<  _beta<<std::endl;
}
