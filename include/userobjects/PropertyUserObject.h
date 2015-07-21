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
  PropertyUserObject(const InputParameters & parameters);

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
   * Returns the capillary length (d_0') using the given value or computed (Eq. (25))
   * @param T The Current temperature
   * @param rho_vs Equilibrium water vapor concentration at saturation for the current temperature, this is
   *               passed in to save computing the value more than once
   */
  Real capillaryLengthPrime(const Real & T, const Real & rho_vs) const;

  /** Returns the interface kinetic coefficient (beta_0')  using the given value or computed (Eq. (26))
   * @param T The Current temperature
   * @param rho_vs Equilibrium water vapor concentration at saturation for the current temperature, this is
   *               passed in to save computing the value more than once
   */
  Real interfaceKineticCoefficientPrime(const Real & T, const Real & rho_vs) const;

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

  /**
   * Returns a reference to the pre-computed value of rho_vs at the reference temperature,
   * this is for performance purposes
   **/
  const Real & equilibriumWaterVaporConcentrationAtSaturationAtReferenceTemperature() const;


  Real equilibriumChemicalPotential(const Real & T) const;

  const Real & temporalScale() const;

  /// Boltzmann's constant, k [J/K]
  const Real _boltzmann;

  /// Mass of water molecule, m [kg]
  const Real _mass_water_molecule;

  /// Gas constant of dry air [J/(Kg K)]
  const Real _R_da;

  /// Gas constant of water vapor [J/(Kg K)]
  const Real _R_v;

private:

  const bool _has_kinetic_coefficient;

  const Real _input_kinetic_coefficieint;

  const bool _has_capillary_length;

  const Real _input_capillary_length;


  const Real _gamma;
  const Real _a;
  const Real _P_a;
  const Real _alpha;
  const Real _rho_a;

  const Real _rho_i;

  const Real _T_0;

  /// Storage for pre-computing rho_vs at the reference temperature
  Real _rho_vs_T_0;

  const Real _xi;

  /// Fitting coefficients for saturation vapor pressure, Wexler, 2007, Table 2
  std::vector<Real> _K;
};

#endif // PROPERTYUSEROBJECT_H
