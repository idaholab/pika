#ifndef COEFFICIENTTIMEDERIVATIVE_H
#define COEFFICIENTTIMEDERIVATIVE_H

#include "TimeDerivative.h"
#include "Material.h"

//Forward Declarations
class CoefficientTimeDerivative;

template<>
InputParameters validParams<CoefficientTimeDerivative>();

class CoefficientTimeDerivative : public TimeDerivative
{
public:

  CoefficientTimeDerivative(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

private:
  const bool _has_material;
  const Real _coefficient;
  MaterialProperty<Real> * _material_coefficient;
  Real _scale;
  Real _offset;
};
#endif //COEFFICIENTTIMEDERIVATIVE_H
