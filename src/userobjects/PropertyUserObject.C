/**********************************************************************************/
/*                  Pika: Phase field snow micro-structure model                  */
/*                                                                                */
/*                     (C) 2014 Battelle Energy Alliance, LLC                     */
/*                              ALL RIGHTS RESERVED                               */
/*                                                                                */
/*                   Prepared by Battelle Energy Alliance, LLC                    */
/*                      Under Contract No. DE-AC07-05ID14517                      */
/*                      With the U. S. Department of Energy                       */
/**********************************************************************************/

#include "PropertyUserObject.h"

template<>
InputParameters validParams<PropertyUserObject>()
{
  InputParameters params = validParams<GeneralUserObject>();
  params += PropertyUserObject::objectParams();
  params.suppressParameter<MultiMooseEnum>("execute_on");
  return params;
}

PropertyUserObject::PropertyUserObject(const std::string & name, InputParameters parameters) :
    GeneralUserObject(name, parameters),
    _boltzmann(1.38e-23),
    _mass_water_molecule(2.99e-26),
    _R_da(286.9),
    _R_v(461.5),
    _has_kinetic_coefficient(isParamValid("interface_kinetic_coefficient")),
    _input_kinetic_coefficieint(_has_kinetic_coefficient ? getParam<Real>("interface_kinetic_coefficient") : 0.0),
    _has_capillary_length(isParamValid("capillary_length")),
    _input_capillary_length(_has_capillary_length ? getParam<Real>("capillary_length") : 0.0),
    _gamma(getParam<Real>("interface_free_energy")),
    _a(getParam<Real>("mean_molecular_spacing")),
    _P_a(getParam<Real>("atmospheric_pressure")),
    _alpha(getParam<Real>("condensation_coefficient")),
    _rho_a(getParam<Real>("density_air")),
    _rho_i(getParam<Real>("density_ice")),
    _T_0(getParam<Real>("reference_temperature")),
    _xi(getParam<Real>("temporal_scaling"))
{
  // Define K coefficients (Wexler, 1977, Table 2)
  _K.push_back(-0.58653696e4);
  _K.push_back(0.2224103300e2);
  _K.push_back(0.13749042e-1);
  _K.push_back(-0.34031775e-4);
  _K.push_back(0.26967687e-7);
  _K.push_back(0.6918651);

  // Pre-compute rho_vs at T_0, this only needs to be done once.
  // The value should be used vi `equilibriumWaterVaporConcentrationAtSaturationAtRefereneTemperature`;
  _rho_vs_T_0 = equilibriumWaterVaporConcentrationAtSaturation(_T_0);
}

InputParameters
PropertyUserObject::objectParams()
{
  InputParameters params = emptyInputParameters();

  // Ice properties
  params.addParam<Real>("density_ice", 918.9, "Density of ice, \rho_i [kg/m^3]");
  params.addParam<Real>("conductivity_ice", 2.29, "Thermal conductivity or air, kappa_i [ W/(m K)]");
  params.addParam<Real>("heat_capacity_ice", 1.8e6, "Heat capacity of air, C_i [J/(m^3 K)]");
  params.addParamNamesToGroup("density_ice conductivity_ice heat_capacity_ice", "Ice");

  // Water vapor / air properties
  params.addParam<Real>("conductivity_air", 0.02, "Thermal conductivity or air, kappa_a [ W/(m K)]");
  params.addParam<Real>("heat_capacity_air", 1.4e3, "Heat capacity of air, C_a [J/(m^3 K)]");
  params.addParam<Real>("water_vapor_diffusion_coefficient", 2.178e-5, "Diffusion coefficient water vapor in air, D_v [m^2/s]");
  params.addParam<Real>("density_air", 1.341, "Density of air, \rho_a [kg/m^3]");
  params.addParamNamesToGroup("density_air conductivity_air heat_capacity_air water_vapor_diffusion_coefficient", "Vapor");

  // Phase-field properties
  params.addParam<Real>("interface_free_energy", 1.09e-1, "Interface free energy, \\gamma [J/m^2]");
  params.addParam<Real>("mean_molecular_spacing", 3.19e-10, "Mean inter-molecular spacing in ice, a [m]");
  params.addParam<Real>("condensation_coefficient", 10e-2, "Condensation coefficient, \alpha [unitless]");
  params.addParam<Real>("interface_thickness", 8e-6, "Interface thickness, W [m]");
  params.addParam<Real>("mobility", 1.0, "Phase-field mobility value");
  params.addParam<Real>("capillary_length", "Capillary Length (d_0), if not specified this is computed ");
  params.addParam<Real>("interface_kinetic_coefficient", "Interface kinetic coefficient (beta), if not specified this is computed");
  params.addParamNamesToGroup("interface_free_energy mean_molecular_spacing condensation_coefficient interface_thickness mobility capillary_length interface_kinetic_coefficient", "Phase");

  // General environmental properties
  params.addParam<Real>("latent_heat", 2.6e9, "Latent heat of sublimation, L_{sg} [J/m^3]");
  params.addParam<Real>("atmospheric_pressure", 1.01325e5, "Atmospheric pressure, P_a [Pa]");
  params.addParam<Real>("reference_temperature", 263.15, "Reference temperature, T_0 [K]");
  params.addParam<bool>("debug", false, "Enable the creating of material properties for debugging");

  params.addParamNamesToGroup("latent_heat reference_temperature atmospheric_pressure ", "Misc");

  // Scaling terms
  params.addParam<Real>("temporal_scaling", 1e-5, "Snow metamorphosis time scaling value");
  params.addParam<Real>("spatial_scaling", 1.0, "Conversion value for switching between spatial units (i.e meters to mm)");
  params.addParamNamesToGroup("temporal_scaling spatial_scaling", "Scaling");
  return params;
}

Real
PropertyUserObject::capillaryLengthPrime(const Real & T, const Real & rho_vs) const
{
  Real d0;
  if (_has_capillary_length)
    d0 = (rho_vs / _rho_i) * _input_capillary_length;
  else
    d0 = (rho_vs / _rho_i) * _gamma * std::pow(_a, 3) / (_boltzmann * T); // Eq. (25)
  return d0;
}

Real
PropertyUserObject::interfaceKineticCoefficientPrime(const Real & T, const Real & rho_vs) const
{
  Real beta0;
  if (_has_kinetic_coefficient)
    beta0 = (rho_vs / _rho_i) * _input_kinetic_coefficieint;
  else
    beta0 = 1./_alpha * std::sqrt((2.*libMesh::pi*_mass_water_molecule)/(_boltzmann * T)); // Eq. (26)
  return beta0;
}

Real
PropertyUserObject::specificHumidityRatio(const Real & T) const
{
  Real P_vs = saturationPressureOfWaterVaporOverIce(T); // Eq. (2)
  Real f =  (_R_da/_R_v) * P_vs / (_P_a - P_vs); // x_s, Eq. (1)
  return f;
}

Real
PropertyUserObject::saturationPressureOfWaterVaporOverIce(const Real & T) const
{
  // Eq. (2)
  Real f =  std::exp(_K[0]*std::pow(T, -1.)
                     + _K[1]*std::pow(T, 0.)
                     + _K[2]*std::pow(T, 1.)
                     + _K[3]*std::pow(T, 2.)
                     + _K[4]*std::pow(T, 3.)
                     + _K[5]*log(T));
  return f;
}

Real
PropertyUserObject::equilibriumWaterVaporConcentrationAtSaturation(const Real & T) const
{
  return  _rho_a * specificHumidityRatio(T); // Eq. (3)
}


const Real &
PropertyUserObject::equilibriumWaterVaporConcentrationAtSaturationAtReferenceTemperature() const
{
  return _rho_vs_T_0;
}

const Real &
PropertyUserObject::temporalScale() const
{
  return _xi;
}

Real
PropertyUserObject::equilibriumChemicalPotential(const Real & T) const
{
  Real rho_vs_T = equilibriumWaterVaporConcentrationAtSaturation(T); // defined just after Eq. (32) in text
  return (rho_vs_T - _rho_vs_T_0) / _rho_i;
}
