#ifndef COUPLEDPIKATIMEDERIVATIVE_H
#define COUPLEDPIKATIMEDERIVATIVE_H
#include "PikaTimeDerivative.h"

//Forward Declarations
class CoupledPikaTimeDerivative;

template<>
InputParameters validParams<CoupledPikaTimeDerivative>();

class CoupledPikaTimeDerivative :
  public PikaTimeDerivative,
{
public:

  CoupledPikaTimeDerivative(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:
  VariableValue & _var_dot;
  VariableValue & _dvar_dot_dvar;
  VariableValue & _v_var;
  const bool _time_scale; 
  const Real  _xi;
  
};
#endif //COUPLEDPIKATIMEDERIVATIVE
