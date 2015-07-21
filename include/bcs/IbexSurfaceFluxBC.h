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
  IbexSurfaceFluxBC(const InputParameters & parameters);

protected:

  /**
   *
   */
  virtual Real computeQpResidual();

private:

  Real longwave();

  /// returns missing swir component
  Real shortwave();

  Real latent();

  Real sensible();

  Real clausiusClapeyron(const Real & T);

  Real airDensity();

  const Real _boltzmann;

  const Real _gas_constant_air;

  const Real _gas_constant_water_vapor;

  const Real _air_temperature;

  const Real _relative_humidity;

  const Real _atmospheric_pressure;

  const Real _air_velocity;

  const Real _swir_albedo;

  Function & _long_wave;

  Function & _short_wave;

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
