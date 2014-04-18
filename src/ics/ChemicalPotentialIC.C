#include "ChemicalPotentialIC.h"

template<>
InputParameters validParams<ChemicalPotentialIC>()
{
  InputParameters params = validParams<InitialCondition>();
  ChemicalPotentialInterface(getUserObject("property_user_object")),
  params.addRequiredCoupledVar("temperature", "The temperature variable");
  return params;
}

ChemicalPotentialIC::ChemicalPotentialIC(const std::string & name, InputParameters parameters) :
    InitialCondition(name, parameters),
    ChemicalPotentialInterface(getUserObject("property_user_object")),
    _temperature(coupledValue("temperature"))
{
}

Real
ChemicalPotentialIC::value(const Point & /*p*/)
{
  return _property_ptr->equilibriumConcentration(_temperature[_qp]);
}
