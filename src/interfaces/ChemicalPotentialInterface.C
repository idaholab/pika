
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
ChemicalPotentialInterface::specificHumidityRatio(Real T)
{
  Real R_da = _property_uo.gasConstantDryAir();         // Table 1
  Real R_v  = _property_uo.gasConstantWaterVapor();     // Table 1
  Real P_a  = _property_uo.atmosphericPressure();       // Table 1
  Real P_vs = saturationPressureOfWaterVaporOverIce(T); // Eq. (2)
  return (R_da/R_v) * P_vs / (P_a - P_vs);              // x_s, Eq. (1)
}

Real
ChemicalPotentialInterface::saturationPressureOfWaterVaporOverIce(Real T)
{
  return std::exp(_K[0]*std::pow(T,-1.0) + _K[1]*std::pow(T,0.0) + _K[2]*std::pow(T,1.0) +
                  _K[3]*std::pow(T,2.0) + _K[4]*std::pow(T,3.0)) + std::pow(T, _K[5]);
}

Real
ChemicalPotentialInterface::equilibriumWaterVaporConcentrationAtSaturation(Real T)
{
  return  _property_uo.airDensity(T) * specificHumidityRatio(T);

}

Real
ChemicalPotentialInterface::equilibriumConcentration(Real T)
{
  Real rho_vs_T   = equilibriumWaterVaporConcentrationAtSaturation(T);
  Real rho_vs_T_0 = equilibriumWaterVaporConcentrationAtSaturation(_property_uo.referenceTemperature());

  return (rho_vs_T - rho_vs_T_0) / _property_uo.iceDensity(T);

}
