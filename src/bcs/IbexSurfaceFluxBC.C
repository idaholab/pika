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

#include "IbexSurfaceFluxBC.h"

template<>
InputParameters validParams<IbexSurfaceFluxBC>()
{
  InputParameters params = validParams<IntegratedBC>();

  // Define the general parameters
  params.addCoupledVar("temperature", "The snow temperature variable");
  params.addParm<Real>("air_temperature", 268.15, "Air temperature above the snow surface [K]");
  params.addParam<Real>("relative_humidity", 50, "Relative humidity of air above snow [%]");
  params.addParam<Real>("atmospheric_pressure", 101.325, "Atmospheric pressure [kPa]");
  params.addParam<FunctionName>("long_wave", "Name of the function computing the incoming long-wave radiation function [W/m^2]");

  // Advanced
  params.addParam<Real>("emissivity", 0.988, "Emissivity of snow");
  params.addParam<Real>("ratio_of_molecular_weights", 0.622, "Ratio of dry-air to water-vapor molecular weights");
  params.addParam<Real>("latent_heat", 2833, "Latent heat of sublimation [kJ/kg]");
  params.addParam<Real>("water_vapor_transport", 0.0023, "Transport coefficient for water vapor");
  params.addParam<Real>("transport_coefficient", 0.0023, "Transport coefficient for sensible heat calclulation");
  params.addParam<Real>("water_vapor_gas_constant", 0.462, "Gas constant for water-vapor [kg/(kg K)]");
  params.addParam<Real>("reference_temperature", 268.15, "Reference temperature [K]");
  params.addParam<Real>("reference_vapor_pressure", 0.402, "Reference vapor pressure at reference temperature [kPa]");


  params.addParamNamesToGroup("emissivity ratio_of_molecular_weights latent_heat water_vapor_transport transport_coefficient reference_temperature reference_vapor_pressure");


  return params;
}

IbexSurfaceFluxBC::IbexSurfaceFluxBC(const std::string & name, InputParameters parameters) :
    IntegratedBC(name, parameters),
    _boltzmann(5.670e-8),
    _air_temperature(getParam<Real>("air_temperature")),
    _temperature(coupledValue("temperature")),
    _relative_humidity(getParam<Real>("relative_humidity")),
    _atmospheric_pressure(getParam<Real>("atmospheric_pressure")),
    _long_wave(getFunction("long_wave")),
    _emissivity(getParam<Real>("emissivity")),
    _ratio_of_molecular_weights(getParam<Real>("ratio_of_molecular_weights")),
    _latent_heat(getParam<Real>("latent_heat")),
    _water_vapor_transport(getParam<Real>("water_vapor_transport")),
    _transport_coefficient(getParam<Real>("transport_coefficient")),
    _gas_constant(getParam<Real>("water_vapor_gas_constant")),
    _reference_temperature(getParam<Real>("reference_temperature")),
    _reference_vapor_pressure(getParam<Real>("reference_vapor_pressure"))
{
}

Real
IbexSurfaceFluxBC::computeQpResidual()
{
  return -_test[_i][_qp] * longwave();
}

Real
IbexSurfaceFluxBC::longwave()
{
  Real return _long_wave.value(_t, _q_point[_qp]) - _emissivity * _boltzmann * std::pow(_temperature[_qp]);
}

Real
IbexSurfaceFluxBC::clausiusClapeyron()
{


}
