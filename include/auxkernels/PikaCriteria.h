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

#include "AuxKernel.h"

//Pika includes
#include "PropertyUserObjectInterface.h"
class PikaCriteria;

template<>
InputParameters validParams<PikaCriteria>();

/**
 * A class for computing phase-field related criteria
 *
 * The available 'criteria' (see Kaempfer and Plapp (2009)):
 *   'ice' - Eq. 43a
 *   'air' - Eq. 43b
 *   'vapor' - Eq. 43c
 *   'velocity' - Eq. 45
 *   'time' = Eq. 47
 *
 */
class PikaCriteria : public AuxKernel,
                     public PropertyUserObjectInterface
{
public:
  PikaCriteria(const InputParameters & parameters);
  virtual ~PikaCriteria(){}

protected:

  /**
   * Compute the desired criteria at the current quadrature point
   */
  Real computeValue();

private:

  /// The interface velocity
  const VariableValue & _v_n;

  /// Thermal conductivity of ice
  const MaterialProperty<Real> & _k_i;

  /// Thermal conductivity of air/vapor
  const MaterialProperty<Real> & _k_a;

  /// Heat capacity of ice
  const MaterialProperty<Real> & _c_i;

  /// Heat capaticy of ice/air
  const MaterialProperty<Real> & _c_a;

  /// Equilibribum water vapor concentration at saturation
  const MaterialProperty<Real> & _rho_vs;

  /// Density of ice
  const MaterialProperty<Real> & _rho_i;

  /// Diffusion coefficient of water vapor
  const MaterialProperty<Real> & _D_v;

  /// Interface kinetic coefficient
  const MaterialProperty<Real> & _beta;

  /// Capilary length
  const Real & _d_0;

  /// Desired criteria to compute
  MooseEnum _criteria;

  /// Estimated pore size
  Real _pore_size;

  /// Temporal scaling factor
  Real _xi;
};
