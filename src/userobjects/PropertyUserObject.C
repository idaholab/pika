/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "PropertyUserObject.h"

template<>
InputParameters validParams<PropertyUserObject>()
{
  InputParameters params = validParams<GeneralUserObject>();
  params += PropertyUserObject::objectParams();
  return params;
}

PropertyUserObject::PropertyUserObject(const std::string & name, InputParameters parameters) :
    GeneralUserObject(name, parameters),
    _rho_i(getParam<Real>("density_ice")),
    _rho_a(getParam<Real>("density_air")),
    _P_a(getParam<Real>("atmospheric_pressure")),
    _R_da(getParam<Real>("gas_constant_dry_air")),
    _R_v(getParam<Real>("gas_constant_water_vapor")),
    _T_0(getParam<Real>("reference_temperature")),
    _gamma(getParam<Real>("interface_free_energy")),
    _a(getParam<Real>("mean_molecular_spacing")),
    _k(getParam<Real>("boltzmann")),
    _alpha(getParam<Real>("condensation_coefficient")),
    _m(getParam<Real>("mass_water_molecule")),
    _W(getParam<Real>("interface_thickness")),
    _L_sg(getParam<Real>("latent_heat")),
    _mobility(getParam<Real>("mobility")),
    _xi(getParam<Real>("temporal_scaling"))
{
    // Define K coefficients (Wexler, 1977, Table 2)
  _K.push_back(-0.58653696e4);
  _K.push_back(0.2224103300e2);
  _K.push_back(0.13749042e-1);
  _K.push_back(-0.34031775e-4);
  _K.push_back(0.26967687e-7);
  _K.push_back(0.6918651);

}

InputParameters
PropertyUserObject::objectParams()
{
  InputParameters params = emptyInputParameters();
  params.addParam<Real>("density_ice", 918.9, "Density of ice, \rho_i [kg/m^3]");
  params.addParam<Real>("density_air", 1.341, "Density of air, \rho_a [kg/m^3]");
  params.addParam<Real>("atmospheric_pressure", 1.01325e5, "Atmospheric pressure, P_a [Pa]");
  params.addParam<Real>("gas_constant_dry_air", 286.9, "Gas constant for dry air, R_{da} [J/(Kg K)]");
  params.addParam<Real>("gas_constant_water_vapor", 461.5, "Gas constant for water vapor, R_v [J/(Kg K)]");
  params.addParam<Real>("reference_temperature", 263.15 ,"Reference temperature, T_0 [K]");
  params.addParam<Real>("interface_free_energy", 1.09e-1, "Interface free energy, \gamma [J/m^2]");
  params.addParam<Real>("mean_molecular_spacing", 3.19e-10, "Mean inter-molecular spacing in ice, a [m]");
  params.addParam<Real>("boltzmann", 1.3806488e-23, "Boltzmann constant, k [J/k]");
  params.addParam<Real>("condensation_coefficient", 10e-2, "Condensation coefficient, \alpha [unitless]");
  params.addParam<Real>("mass_water_molecule", 2.9900332e-26, "Mass of water molecule, m [kg]");
  params.addParam<Real>("interface_thickness", 8e-6, "Interface thickness, W [m]");
  params.addParam<Real>("latent_heat", 2.6e9, "Latent heat of sublimation, L_{sg} [J/m^3]");
  params.addParam<Real>("mobility", 1.0, "Phase-field mobility value");
  params.addParam<Real>("temporal_scaling", 1.0, "Snow metamorphosis time scaling value");
  params.addParam<Real>("capillary_length", 1.3e-9 , "Capillary Length (d_o) ");
  params.addParam<Real>("interface_kinetic_coefficient", 5.5e5, "Interface kinetic coefficient (beta)");

  // @todo{Group the above}
  params.addParamNamesToGroup("atmospheric_pressure", "General");

  return params;
}

Real
PropertyUserObject::iceDensity(const Real &/* T */) const
{
  return _rho_i;
}

Real
PropertyUserObject::airDensity(const Real & /* T */) const
{
  return _rho_a;
}

Real
PropertyUserObject::specificHumidityRatio(const Real & T) const
{
  Real P_vs = saturationPressureOfWaterVaporOverIce(T); // Eq. (2)
  Real f = (_R_da/_R_v) * P_vs / (_P_a - P_vs); // x_s, Eq. (1)
  return f;
}

Real
PropertyUserObject::saturationPressureOfWaterVaporOverIce(const Real & T) const
{
  // Eq. (2)
  Real f =  std::exp(_K[0]*std::pow(T,-1.)
                  + _K[1]*std::pow(T,0.)
                  + _K[2]*std::pow(T,1.)
                  + _K[3]*std::pow(T,2.)
                  + _K[4]*std::pow(T,3.)
                  + _K[5]*log(T));
//  std::cout<<"P_vs = "<<f<<std::endl;

  return f;
}

Real
PropertyUserObject::equilibriumWaterVaporConcentrationAtSaturation(const Real & T) const
{
  return  airDensity(T) * specificHumidityRatio(T);
}

const Real &
PropertyUserObject::temporalScale() const
{
  return   _xi;
}

const Real &
PropertyUserObject::referenceTemp() const
{
  return   _T_0;
}

Real
PropertyUserObject::equilibriumConcentration(const Real & T) const
{
  Real rho_vs_T   = equilibriumWaterVaporConcentrationAtSaturation(T);
  Real rho_vs_T_0 = equilibriumWaterVaporConcentrationAtSaturation(_T_0);
  return (rho_vs_T - rho_vs_T_0) / _rho_i;
}

