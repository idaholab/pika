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

#ifndef IBEXSURFACEFLUXBC_H
#define IBEXSURFACEFLUXBC_H

// MOOSE includes
#include "IntegratedBC.h"

// Forward declarations
class IbexSurfaceFluxBC;

template<>
InputParameters validParams<IbexSurfaceFluxBC>();

/**
 *
 */
class IbexSurfaceFluxBC : public IntegratedBC
{
public:

  /**
   * Class constructor
   * @param name
   * @param parameters
   */
  IbexSurfaceFluxBC(const std::string & name, InputParameters parameters);

protected:

  /**
   *
   */
  virtual Real computeQpResidual();

private:

  Real longwave();

  Real latent();

  Real sensible();

  Real clausiusClapeyron(const Real & T);

  Real airDensity();

  const Real _boltzmann;

  const Real _gas_constant_air;

  const Real _gas_constant_water_vapor;

  const VariableValue & _temperature;

  const Real _air_temperature;

  const Real _relative_humidity;

  const Real _atmospheric_pressure;

  const Real _air_velocity;

  Function & _long_wave;

  const Real _emissivity;

  Real _ratio_of_molecular_weights;

  Real _latent_heat;

  Real _water_vapor_transport;

  Real _transport_coefficient;

  Real _reference_temperature;

  Real _reference_vapor_pressure;

  Real _specific_heat_air;
};

#endif //IBEXSURFACEFLUXBC_H
