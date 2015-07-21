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

#include "IbexSnowMaterial.h"

template<>
InputParameters validParams<IbexSnowMaterial>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredCoupledVar("temperature", "The snow temperature variable to couple");
  params.addParam<Real>("snow_density", 200, "Density of snow [kg/m^3]");
  params.addParam<Real>("thermal_conductivity", "Thermal conductivity of snow; if omitted it is estimated based on density");
  params.addParam<Real>("specific_heat", "Specific heat of snow; if omitted it is estimated based on temperature");

  params.addCoupledVar("thermal_conductivity_name", "Name of a variable to utilize for thermal conductivity; this superceeds all other values");
  return params;
}

IbexSnowMaterial::IbexSnowMaterial(const InputParameters & parameters) :
    Material(parameters),
    _temperature(coupledValue("temperature")),
    _input_density(getParam<Real>("snow_density")),
    _compute_conductivity(!isParamValid("thermal_conductivity")),
    _input_conductivity(_compute_conductivity ? 0 : getParam<Real>("thermal_conductivity")),
    _compute_specific_heat(!isParamValid("specific_heat")),
    _input_specific_heat(_compute_specific_heat ? 0 : getParam<Real>("specific_heat")),
    _density(declareProperty<Real>("density")),
    _conductivity(declareProperty<Real>("thermal_conductivity")),
    _specific_heat(declareProperty<Real>("specific_heat")),
    _use_conductivity_variable(isParamValid("thermal_conductivity_name")),
    _conductivity_variable(_use_conductivity_variable ? coupledValue("thermal_conductivity_name") : _zero)
{
}

void
IbexSnowMaterial::computeQpProperties()
{
  _density[_qp] = _input_density;

  if (_use_conductivity_variable)
    _conductivity[_qp] = _conductivity_variable[_qp];
  else if (_compute_conductivity)
    _conductivity[_qp] = 0.021 + 2.5 * std::pow(_density[_qp] / 1000, 2);
  else
    _conductivity[_qp] = _input_conductivity;

  if (_compute_specific_heat)
    _specific_heat[_qp] = 1000 * (2.115 + 0.00779 * (273.15 - _temperature[_qp]));
  else
    _specific_heat[_qp] = _input_specific_heat;
}
