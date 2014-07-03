#ifndef COUPLEDPIKATIMEDERIVATIVE_H
#define COUPLEDPIKATIMEDERIVATIVE_H
#include "PikaTimeDerivative.h"

//Forward Declarations
class CoupledPikaTimeDerivative;

template<>
InputParameters validParams<CoupledPikaTimeDerivative>();

class CoupledPikaTimeDerivative :
  public PikaTimeDerivative
{
public:

  CoupledPikaTimeDerivative(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:
 const VariableValue & _var_dot;
 const VariableValue & _dvar_dot_dvar;
 unsigned int  _v_var;
  
};
#endif //COUPLEDPIKATIMEDERIVATIVE
