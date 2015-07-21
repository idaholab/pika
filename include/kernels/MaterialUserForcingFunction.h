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

#ifndef MATERIALUSERFORCINGFUNCTION_H
#define MATERIALUSERFORCINGFUNCTION_H

#include "UserForcingFunction.h"

//Forward Declarations
class MaterialUserForcingFunction;

template<>
InputParameters validParams<MaterialUserForcingFunction>();

/**
 * Multiplies a UserForcingFunction by a Material Property
 */
class MaterialUserForcingFunction : public UserForcingFunction
{
public:
  /**
   * Factory constructor, takes parameters so that all derived classes can be built using the same
   * constructor.
   */
  MaterialUserForcingFunction(const InputParameters & parameters);

  virtual ~MaterialUserForcingFunction() {}

protected:
  virtual Real computeQpResidual();

  /// Material Property being used to multiply with the function of this kernel
  const MaterialProperty<Real> & _material_coefficient;
  Real _scale;
};

#endif //MATERIALUSERFORCINGFUNCTION_H
