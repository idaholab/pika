#include "ChemicalPotentialIC.h"
#include "PropertyUserObject.h"
template<>
InputParameters validParams<ChemicalPotentialIC>()
{
  InputParameters params = validParams<InitialCondition>();
  params += validParams<PropertyUserObjectInterface>();
  params.addRequiredCoupledVar("temperature", "The temperature variable");
  return params;
}

ChemicalPotentialIC::ChemicalPotentialIC(const std::string & name, InputParameters parameters) :
    InitialCondition(name, parameters),
    PropertyUserObjectInterface(name, parameters),
    _temperature(coupledValue("temperature"))
{
}

Real
ChemicalPotentialIC::value(const Point & /*p*/)
{
  return _property_uo.equilibriumConcentration(_temperature[_qp]);
}
