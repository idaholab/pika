#ifndef PIKASCALEDTIMEDERIVATIVE_H
#define PIKASCALEDTIMEDERIVATIVE_H 
//Pika Includes
#include "PikaTimeDerivative.h"
#include "PropertyUserObjectInterface.h"

//Forward Declarations
class PikaScaledTimeDerivative;

template<>
InputParameters validParams<PikaScaledTimeDerivative>();

class PikaScaledTimeDerivative :
  public PikaTimeDerivative,
  public PropertyUserObjectInterface

{
public:

  PikaScaledTimeDerivative(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

};
#endif //PIKASCALEDTIMEDERIVATIVE
