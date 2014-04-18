
#include "ChemicalPotentialInterface.h"
#include "ChemicalPotentialPropertyUserObject.h"

#include "libmesh/utility.h"

template<>
InputParameters validParams<ChemicalPotentialInterface>()
{
  InputParameters params = emptyInputParameters();
  params.addRequiredParam<UserObjectName>("property_user_object", "User object containing material property methods related to chemical potential calculations");
  return params;
}

ChemicalPotentialInterface::ChemicalPotentialInterface(const ChemicalPotentialPropertyUserObject & uo) :
    _property_uo(uo)
{
  _K.push_back(-0.5865e4);
  _K.push_back(0.2224e2);
  _K.push_back(0.1375e-1);
  _K.push_back(-0.3403e-4);
  _K.push_back(0.2697e-7);
  _K.push_back(0.6918);
}


Real
ChemicalPotentialInterface::humidityRatio(Real T)
{

  Real R_da = _property_uo.gasConstantDryAir();
  Real R_v  = _property_uo.gasConstantWaterVapor();
  Real P_a  = _property_uo.atmosphericPressure();
  Real P_vs = saturationPressureOfWaterVaporOverIce(T);
  return (R_da/R_v) * P_vs / (P_a - P_vs);
}

Real
ChemicalPotentialInterface::saturationPressureOfWaterVaporOverIce(Real T)
{
  Real s = 0;

  for (int j = 0; j < 5; ++j)
    s += _K[j]*std::pow(T, j-1);

  return std::exp(s + _K[5]*std::log(T) );
}

Real
ChemicalPotentialInterface::equilibriumWaterVaporConcentrationAtSaturation(Real T)
{
  return  _property_uo.airDensity(T) * humidityRatio(T);

}

Real
ChemicalPotentialInterface::equilibriumConcentration(Real T)
{
  Real rho_vs_T   = equilibriumWaterVaporConcentrationAtSaturation(T);
  Real rho_vs_T_0 = equilibriumWaterVaporConcentrationAtSaturation(_property_uo.referenceTemperature());

  return (rho_vs_T - rho_vs_T_0) / _property_uo.iceDensity(T);

}
