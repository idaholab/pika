#include "ChemicalPotentialIC.h"
#include "ChemicalPotentialPropertyUserObject.h"
template<>
InputParameters validParams<ChemicalPotentialIC>()
{
  InputParameters params = validParams<InitialCondition>();
  params += validParams<ChemicalPotentialInterface>();
  params.addRequiredCoupledVar("temperature", "The temperature variable");
  return params;
}

ChemicalPotentialIC::ChemicalPotentialIC(const std::string & name, InputParameters parameters) :
    InitialCondition(name, parameters),
    ChemicalPotentialInterface(getUserObject<ChemicalPotentialPropertyUserObject>("property_user_object")),
    _temperature(coupledValue("temperature"))
{
}

Real
ChemicalPotentialIC::value(const Point & /*p*/)
{
  return equilibriumConcentration(_temperature[_qp]);
}
