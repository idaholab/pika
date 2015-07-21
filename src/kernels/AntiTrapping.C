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

#include "AntiTrapping.h"

template<>
InputParameters validParams<AntiTrapping>()
{
  InputParameters params = validParams<Kernel>();
  params+=validParams<CoefficientKernelInterface>();
  params.addRequiredCoupledVar("phase", "Phase-field variable");
  return params;
}

AntiTrapping::AntiTrapping(const InputParameters & parameters) :
    Kernel(parameters),
    CoefficientKernelInterface(parameters),
    _phase_dot(coupledDot("phase")),
    _grad_phase(coupledGradient("phase")),
    _w(_property_uo.getParam<Real>("interface_thickness"))
{
}

Real
AntiTrapping::computeQpResidual()
{
  RealGradient n = _grad_phase[_qp] / _grad_phase[_qp].size();
  return -(1.0/(2.0 * std::pow(2.0,0.5))) * n * _w * _phase_dot[_qp] * _grad_test[_i][_qp];
}

Real
AntiTrapping::computeQpJacobian()
{
  return 0.0;
}
/*
Real
AntiTrapping::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _v_var)
    RealGradient n = _grad_phase[_qp] / _grad_phase[_qp].size();
    return (1.0/(2.0 * std::pow(2.0,0.5))) * n * _w[qp] * _grad_test[_i][_qp];

  else
    return 0.0;
}*/
