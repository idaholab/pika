/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "ChemicalPotentialBC.h"
#include "PropertyUserObject.h"
template<>
InputParameters validParams<ChemicalPotentialBC>()
{
  InputParameters params = validParams<NodalBC>();
  params += validParams<PropertyUserObjectInterface>();
  params.addRequiredCoupledVar("temperature", "The temperature variable");
  params.addRequiredCoupledVar("phase_variable", "The variable containing the phase of the continuum (phi)");
  return params;
}

ChemicalPotentialBC::ChemicalPotentialBC(const std::string & name, InputParameters parameters) :
    NodalBC(name, parameters),
    PropertyUserObjectInterface(name, parameters),
    _temperature(coupledValue("temperature")),
    _phase(coupledValue("phase_variable"))
{
}

Real
ChemicalPotentialBC::computeQpResidual()
{
  return _u[_qp] - _property_uo.equilibriumChemicalPotential(_temperature[_qp]) * ((1.0 - _phase[_qp]) / 2.0);
}
