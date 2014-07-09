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
//  return -4.7e-6+ _q_point[_qp](1) * 0.00188;
  return _property_uo.equilibriumConcentration(_temperature[_qp]);
//   return _property_uo.equilibriumConcentration(_temperature[_qp])*(1-_phase[_qp])/2.0;
}
