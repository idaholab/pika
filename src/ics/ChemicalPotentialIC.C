#include "ChemicalPotentialIC.h"

template<>
InputParameters validParams<ChemicalPotentialIC>()
{
  InputParameters params = validParams<InitialCondition>();
  params.addRequiredCoupledVar("temperature", "The temperature variable to couple");
  return params;
}

ChemicalPotentialIC::ChemicalPotentialIC(const std::string & name, InputParameters parameters) :
    InitialCondition(name, parameters),
    ChemicalPotentialInterface(),
    _temperature(coupledValue("temperature"))
{
}

Real
ChemicalPotentialIC::value(const Point & /*p*/)
{

  Real rvs_T  = saturationVaporPressure(_temperature[_qp], _coefficients);
  Real rvs_T0 = saturationVaporPressure(_reference_temperature, _coefficients);
  _chemical_potential_eq[_qp] = (rvs_T - rvs_T0) / _density_ice[_qp];

  return
}
