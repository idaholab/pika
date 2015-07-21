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

#include "IbexSurfaceFluxBC.h"

#include "Function.h"

template<>
InputParameters validParams<IbexSurfaceFluxBC>()
{
  InputParameters params = validParams<IntegratedBC>();

  // Define the general parameters
  params.addParam<Real>("air_temperature", 268.15, "Air temperature above the snow surface [K]");
  params.addParam<Real>("relative_humidity", 50, "Relative humidity of air above snow [%]");
  params.addParam<Real>("atmospheric_pressure", 101.325, "Atmospheric pressure [kPa]");
  params.addParam<Real>("air_velocity", 1, "Air velocity over the snow surface [m/s]");
  params.addParam<Real>("swir_albedo", 0.59, "Short-wave radiation albedo");
  params.addRequiredParam<FunctionName>("long_wave", "Name of the function computing the incoming long-wave radiation function [W/m^2]");
  params.addRequiredParam<FunctionName>("short_wave", "Name of the function computing the incoming short-wave radiation function [W/m^2]");


  // Advanced
  params.addParam<Real>("emissivity", 0.988, "Emissivity of snow");
  params.addParam<Real>("ratio_of_molecular_weights", 0.622, "Ratio of dry-air to water-vapor molecular weights");
  params.addParam<Real>("latent_heat", 2833, "Latent heat of sublimation [kJ/kg]");
  params.addParam<Real>("water_vapor_transport", 0.0023, "Transport coefficient for water vapor");
  params.addParam<Real>("transport_coefficient", 0.0023, "Transport coefficient for sensible heat calculation");
  params.addParam<Real>("reference_temperature", 268.15, "Reference temperature [K]");
  params.addParam<Real>("reference_vapor_pressure", 0.402, "Reference vapor pressure at reference temperature [kPa]");
  params.addParam<Real>("specific_heat_air", 1.012, "Specific heat capacity of air [kJ/(kg K)]");

  params.addParamNamesToGroup("emissivity ratio_of_molecular_weights latent_heat water_vapor_transport transport_coefficient reference_temperature reference_vapor_pressure specific_heat_air", "Advanced");


  return params;
}

IbexSurfaceFluxBC::IbexSurfaceFluxBC(const InputParameters & parameters) :
    IntegratedBC(parameters),
    _boltzmann(5.670e-8),
    _gas_constant_air(0.622),
    _gas_constant_water_vapor(0.287),
    _air_temperature(getParam<Real>("air_temperature")),
    _relative_humidity(getParam<Real>("relative_humidity")),
    _atmospheric_pressure(getParam<Real>("atmospheric_pressure")),
    _air_velocity(getParam<Real>("air_velocity")),
    _swir_albedo(getParam<Real>("swir_albedo")),
    _long_wave(getFunction("long_wave")),
    _short_wave(getFunction("short_wave")),
    _emissivity(getParam<Real>("emissivity")),
    _ratio_of_molecular_weights(getParam<Real>("ratio_of_molecular_weights")),
    _latent_heat(getParam<Real>("latent_heat")),
    _water_vapor_transport(getParam<Real>("water_vapor_transport")),
    _transport_coefficient(getParam<Real>("transport_coefficient")),
    _reference_temperature(getParam<Real>("reference_temperature")),
    _reference_vapor_pressure(getParam<Real>("reference_vapor_pressure")),
    _specific_heat_air(getParam<Real>("specific_heat_air"))
{
}

Real
IbexSurfaceFluxBC::computeQpResidual()
{
  return -_test[_i][_qp] * (longwave() + shortwave() + latent() + sensible());
}

Real
IbexSurfaceFluxBC::longwave()
{
  return _long_wave.value(_t, _q_point[_qp]) - _emissivity * _boltzmann * std::pow(_u[_qp], 4);
}

Real
IbexSurfaceFluxBC::shortwave()
{
  Real sw = _short_wave.value(_t, _q_point[_qp]) * (1 - _swir_albedo);

  // SWIR + "missing" SWIR, see Slaughter 2010
  return 0.094 * sw;// + 0.032/0.913 * sw;
}

Real
IbexSurfaceFluxBC::latent()
{
  Real e_a = clausiusClapeyron(_air_temperature);
  Real e_s = clausiusClapeyron(_u[_qp]);
  Real e = e_a * _relative_humidity / 100 - e_s;

  return (_ratio_of_molecular_weights * airDensity() * _latent_heat * _water_vapor_transport * _air_velocity * e) / _atmospheric_pressure;

}

Real
IbexSurfaceFluxBC::sensible()
{
  return airDensity() * _specific_heat_air * _transport_coefficient * _air_velocity * (_air_temperature - _u[_qp]);
}

Real
IbexSurfaceFluxBC::clausiusClapeyron(const Real & T)
{
  return _reference_vapor_pressure * exp( _latent_heat / _gas_constant_water_vapor * (1/_reference_temperature - 1/T));
}

Real
IbexSurfaceFluxBC::airDensity()
{
  return _atmospheric_pressure / (_gas_constant_air * _air_temperature);
}
