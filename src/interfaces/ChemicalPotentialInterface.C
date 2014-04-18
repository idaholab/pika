
#include "ChemicalPotentialInterface.h"
#include "ChemicalPotentialPropertyUserObject.h"


template<>
InputParameters validParams<ChemicalPotentialInterface>()
{
  InputParameters params = emptyInputParameters();
  params.addRequiredParam<UserObjectName>("property_user_object");
  return params;
}

ChemicalPotentialInterface::ChemicalPotentialInterface(UserObject * property_user_object);
{

  ChemicalPotentialPropertyUserObject * _property_ptr = dynamic_cast<ChemicalPotentialPropertyUserObject *>(property_user_object);
  if (_property_ptr == NULL)
    mooseError("The supplied user object must be of type ChemicalPotentialPropertyUserObject");

  _K.push_back(-0.5865e4);
  _K.push_back(0.2224e2);
  _K.push_back(0.1375e-1);
  _K.push_back(-0.3403e-4);
  _K.push_back(0.2697e-7);
  _K.push_back(0.6918);
}


Real
EquilibrumChemicalPotential::humidityRatio(Real T)
{

  Real R_da = _property_ptr->gasConstantDryAir();
  Real R_da = _property_ptr->gasConstantWaterVapor();
  Real P_a  = _property_ptr->atmosphericPressure();
  Real P_vs = saturationPressureOfWaterVaporOverIce(T);
  return (R_da/R_v) * P_vs / (P_a - P_vs);
}

Real
EquilibrumChemicalPotential::saturationPressureOfWaterVaporOverIce(Real T)
{
  Real s = 0;

  for (unsigned int j = 0; j < 5; ++j)
    s += _K[j]*std::pow(T, j-1);

  return std::exp(s + _K[5]*std::log(T) );
}

Real
EquilibrumChemicalPotential::equilibribumWaterVaporConcentrationAtSaturation(Real T)
{
  return  _property_ptr->airDensity(T) * _property_ptr->humidityRatio(T);

}

Real
EquilibrumChemicalPotential::equilibriumConcentration(Real T)
{
  Real rho_vs_T = equilibribumWaterVaporConcentrationAtSaturation(T);
  Real rho_vs_T_0 = equilibribumWaterVaporConcentrationAtSaturation(_T_0);

  return (rho_vs_T - rho_vs_T_0) / _property_ptr->iceDensity(T);

}
