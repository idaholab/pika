#ifndef PIKATIMEDERIVATIVE_H
#define PIKATIMEDERIVATIVE_H 

#include "TimeDerivative.h"
#include "Material.h"

//Forward Declarations
class PikaTimeDerivative;

template<>
InputParameters validParams<PikaTimeDerivative>();

class PikaTimeDerivative : public TimeDerivative
{
public:

  PikaTimeDerivative(const std::string & name, InputParameters parameters);

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
#endif //PIKATIMEDERIVATIVE
