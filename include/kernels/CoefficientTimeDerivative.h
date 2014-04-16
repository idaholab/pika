#ifndef COEFFICIENTTIMEDERIVATIVE
#define COEFFICIENTTIMEDERIVATIVE

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
  const Real _coefficient;
};
#endif //COEFFICIENTTIMEDERIVATIVE
