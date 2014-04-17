#include "ChemicalPotentialIC.h"

template<>
InputParameters validParams<ChemicalPotentialIC>()
{
  InputParameters params = validParams<InitialCondition>();
  params.addRequiredCoupledVar("temperature", "The temperature variable");
  params.addParam<Real>("density_ice", 918.9, "Density of ice [kg/m^3]");
  params.addParam<Real>("reference_temperature", 258.2, "The reference temperature [K]");
  return params;
}

ChemicalPotentialIC::ChemicalPotentialIC(const std::string & name, InputParameters parameters) :
    InitialCondition(name, parameters),
    ChemicalPotentialInterface(),
    _temperature(coupledValue("temperature")),
    _density_ice(getParam<Real>("density_ice")),
    _reference_temperature(getParam<Real>("reference_temperature"))
{
}

Real
ChemicalPotentialIC::value(const Point & /*p*/)
{
  Real rvs_T  = saturationVaporPressure(_temperature[_qp]);
  Real rvs_T0 = saturationVaporPressure(_reference_temperature);
  return (rvs_T - rvs_T0) / _density_ice;
}
