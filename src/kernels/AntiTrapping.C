/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "AntiTrapping.h"

template<>
InputParameters validParams<AntiTrapping>()
{
  InputParameters params = validParams<PikaCoupledTimeDerivative>();
  params.addRequiredCoupledVar("phase","Phase-field vairable")
  return params;
}

AntiTrapping::AntiTrapping(const std::string & name, InputParameters parameters) :
    _phase_dot = CoupledDot("phase") 
    _grad_phase = CoupledGradient("phase") 
    _w(_property_uo.getParam<Real>("interface_thickness"))
{
}

Real
AntiTrapping::computeQpResidual()
{
  RealGradient n = _grad_phase[_qp] / _grad_phase[_qp].size();
  return (1.0/(2.0 * std::pow(2.0,0.5))) * n * _w[qp] * _phase_dot _grad_test[_i][_qp];
}

Real
AntiTrapping::computeQpJacobian()
{
  return 0.0;
}

Real
AntiTrapping::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _v_var)
    RealGradient n = _grad_phase[_qp] / _grad_phase[_qp].size();
    return (1.0/(2.0 * std::pow(2.0,0.5))) * n * _w[qp] * _grad_test[_i][_qp];

  else
    return 0.0;
}
