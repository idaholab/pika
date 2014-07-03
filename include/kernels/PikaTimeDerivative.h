#ifndef PIKATIMEDERIVATIVE_H
#define PIKATIMEDERIVATIVE_H 
#include "TimeDerivative.h"
#include "PropertyUserObjectInterface.h"
#include "Material.h"

//Forward Declarations
class PikaTimeDerivative;

template<>
InputParameters validParams<PikaTimeDerivative>();

class PikaTimeDerivative :
  public TimeDerivative,
  PropertyUserObjectInterface
{
public:

  PikaTimeDerivative(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

  const bool _has_material;
  MaterialProperty<Real> * _material_coefficient;
  const Real _offset;
  const Real _scale;
  Real _coefficient;
  const bool & _has_time_scale;
  Real _time_scale;

private:
};
#endif //PIKATIMEDERIVATIVE
