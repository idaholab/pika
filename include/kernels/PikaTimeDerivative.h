#ifndef PIKATIMEDERIVATIVE_H
#define PIKATIMEDERIVATIVE_H
#include "TimeDerivative.h"
#include "PropertyUserObjectInterface.h"
#include "Material.h"

//Forward Declarations
class PikaTimeDerivative;

template<>
InputParameters validParams<PikaTimeDerivative>();

/**
 * A coefficient time derivative Kernel
 *
 * This time Kernel allows to a coefficient to be applied to the time derivative, that
 * coefficient may be either a scalar value or a scalar material property.
 *
 * This Kernel includes the ability to scale and offset the coefficient. The
 * coefficient (material or scalar) is applied as:
 *     (scale * coefficient + offset) * du/dt
 *
 * Also, include the ability to toggle the additional temporal scaling parameter (\xi)
 * as defined by Kaempfer and Plapp (2009). This temporal scalling is applied in
 * additions to the coefficient scaling:
 *     xi * (scale * coefficient + offset) * du/dt
 */
class PikaTimeDerivative :
  public TimeDerivative,
  PropertyUserObjectInterface
{
public:

  /**
   * Class constructor.
   */
  PikaTimeDerivative(const std::string & name, InputParameters parameters);

protected:

  /**
   * Compute residual
   * Utilizes TimeDerivative::computeQpResidual with applied coefficients and scaling
   */
  virtual Real computeQpResidual();

  /**
   * Compute residual
   * Utilizes TimeDerivative::computeQpJacobian with applied coefficients and scaling
   */
  virtual Real computeQpJacobian();

  /// Flag indicating to use material property rather than scalar coefficient
  const bool _has_material;

  /// Pointer to material property to utilize as a coefficient
  /* This must be a pointer because getMaterialProperty returns a const reference and
   * this member is optional, so NULL is a valid value */
  MaterialProperty<Real> * _material_coefficient;

  /// Scalar coefficient
  const Real _coefficient;

  /// Coefficient offset
  const Real _offset;

  /// Coefficient offset
  const Real _scale;

  /// Time scaling factor (\xi)
  const Real _time_scale;
};

#endif //PIKATIMEDERIVATIVE
