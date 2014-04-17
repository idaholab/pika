#ifndef MATERIALTIMEDERIVATIVE
#define MATERIALTIMEDERIVATIVE

#include "TimeDerivative.h"
#include "Material.h"

//Forward Declarations
class MaterialTimeDerivative;

template<>
InputParameters validParams<MaterialTimeDerivative>();

class MaterialTimeDerivative : public TimeDerivative
{
public:

  MaterialTimeDerivative(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

private:
  const MaterialProperty<Real> _coefficient;

  Real _factor;
  Real _scale;

};
#endif //MATERIALTIMEDERIVATIVE
