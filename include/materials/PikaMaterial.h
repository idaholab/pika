/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef PIKAMATERIAL_H
#define PIKAMATERIAL_H

// Pika includes
#include "PropertyUserObjectInterface.h"

// MOOSE includes
#include "Material.h"

class PikaMaterial;

template<>
InputParameters validParams<PikaMaterial>();

/**
 * A material for defining properties associated with the energy balance, mass balance, and phase-field equations. This class only contains properties that are directly used in these relationships. All constants and additional parameters for the simulation are stored in PropertyUserObject.
 */
class PikaMaterial :
  public Material,
  public PropertyUserObjectInterface
{
public:
  PikaMaterial(const std::string & name, InputParameters parameters);

protected:
  /**
   * Computes the various material properties for solving energy, mass, and phase equations
   */
  virtual void computeQpProperties();

  /**
   * Computes rho_vs(T_0) to avoid computing this more the needed
   */
  virtual void initialSetup();

private:

  /// Coupled temperature variable
  VariableValue & _temperature;

  /// Coupled phase-field variable
  VariableValue & _phase;

  /// Interface thickness, W
  const Real & _interface_thickness;

  /// Coefficient for capillary length coefficient, Eq. (37)
  const Real _a_1;

  /// Density of ice
  const Real & _density_ice;

  /// Latent heat of sublimation
  const Real &  _l_sg;

  /// Conductivity of ice
  const Real & _ki;

  /// Conductivity of air
  const Real & _ka;

  /// Heat capacity of ice
  const Real & _ci;

  /// Heat capacity of air
  const Real & _ca;

  /// Diffusion coefficient of water vapor
  const Real & _dv;

  /// Spatial scaling
  const Real & _spatial_scale;

  /// Phase-field mobility
  const Real & _input_mobility;

  /// Equilibrium water vapor concentration at reference temperature
  Real _rho_vs_T_0;

  /// Equilibrium water vapor concentration at saturation
  MaterialProperty<Real> & _rho_vs;

  /// Phase-field relaxation time
  MaterialProperty<Real> & _tau;

  /// Phase-field coupling constant
  MaterialProperty<Real> & _lambda;

  /// Square of the interface thickness, W^2
  MaterialProperty<Real> & _interface_thickness_squared;

  /// Equilibrium chemical potential, u_{eq}
  MaterialProperty<Real> & _equilibrium_chemical_potential;

  /// Phase-adjusted heat capacity, C
  MaterialProperty<Real> & _heat_capacity;

  /// Phase-adjusted thermal conductivity, \\kappa
  MaterialProperty<Real> & _conductivity;

  /// Phase-adjust mass diffusion coefficient
  MaterialProperty<Real> & _diffusion_coefficient;

  /// Latent heat of sublimation
  MaterialProperty<Real> & _latent_heat;

  /// Phase-field mobility
  MaterialProperty<Real> & _mobility;

};

#endif // PIKAMATERIAL_H
