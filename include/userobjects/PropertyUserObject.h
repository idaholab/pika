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

#ifndef PROPERTYUSEROBJECT_H
#define PROPERTYUSEROBJECT_H

// MOOSE includes
#include "GeneralUserObject.h"

// Forward declarations
class PropertyUserObject;

template<>
InputParameters validParams<PropertyUserObject>();

/**
 * Container for constant properties and property calculations.
 *
 * Inherit from the PropertyUserObjectInterface for general access to
 * the members and methods of this class.
 */
class PropertyUserObject : public GeneralUserObject
{
public:

  /**
   * Class constructor
   * @param name
   * @param parameters
   */
  PropertyUserObject(const std::string & name, InputParameters parameters);

  /**
   * Class destructor
   */
  virtual ~PropertyUserObject(){}

  /* Static function containing the constant properties; this is called by
     both the UserObject and PikaMaterialAction; generally the later should
     be used for changing these values */
  static InputParameters objectParams();

  ///@{
  /**
   * Not implemented.
   */
  virtual void execute(){}
  virtual void initialize(){}
  virtual void finalize(){}
  ///@}

  /**
   * Return the density of ice as a function of temperature
   */
  Real iceDensity(const Real & T) const;

  /**
   *
   */
  Real airDensity(const Real & T) const;
    /**
   * Computes the specific humidity ratio (x_s; [kg/kg]; Eq. (1))
   * @param T Temperature at which to compute the ratio [kg/kg]
   * @return The specific humidity ratio
   */
  Real specificHumidityRatio(const Real & T) const;

  /**
   * Computes the saturation pressure of water vapor over ice (P_vs; [Pa]; Eq. (2))
   * @param T Temperature at which to compute the value
   * @return The saturation pressure of water vapor over ice [Pa]
   */
  Real saturationPressureOfWaterVaporOverIce(const Real & T) const;

  Real equilibriumWaterVaporConcentrationAtSaturation(const Real & T) const;

  Real equilibriumConcentration(const Real & T) const;

  Real temporal_scale(const Real & T) const;


  const Real _rho_i;
  const Real _rho_a;
  const Real _P_a;
  const Real _R_da;
  const Real _R_v;
  const Real _T_0;
  const Real _gamma;
  const Real _a;
  const Real _k;
  const Real _alpha;
  const Real _m;
  const Real _W;
  const Real _L_sg;
  const Real _mobility;
  const Real _xi;

private:

  /// Fitting coefficients for saturation vapor pressure, Wexler, 2007, Table 2
  std::vector<Real> _K;

};

#endif // PROPERTYUSEROBJECT_H
