/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "ChemicalPotentialIC.h"
#include "PropertyUserObject.h"
template<>
InputParameters validParams<ChemicalPotentialIC>()
{
  InputParameters params = validParams<InitialCondition>();
  params += validParams<PropertyUserObjectInterface>();
  params.addRequiredCoupledVar("temperature", "The temperature variable");
  params.addRequiredCoupledVar("phase_variable", "The variable containing the phase of the continuum (phi)");
  return params;
}

ChemicalPotentialIC::ChemicalPotentialIC(const std::string & name, InputParameters parameters) :
    InitialCondition(name, parameters),
    PropertyUserObjectInterface(name, parameters),
    _temperature(coupledValue("temperature")),
    _phase(coupledValue("phase_variable"))
{
}

Real
ChemicalPotentialIC::value(const Point & /*p*/)
{
  if (_phase[_qp]<1.0)
    return _property_uo.equilibriumConcentration(_temperature[_qp])*(1-_phase[_qp])*(1-_phase[_qp]);
  //return _property_uo.equilibriumConcentration(_temperature[_qp]);
  else
    return 0;
}
