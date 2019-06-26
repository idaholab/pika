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

#include "MassTransportSourceMMS.h"

registerMooseObject("PikaApp", MassTransportSourceMMS);

template<>
InputParameters validParams<MassTransportSourceMMS>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<std::string>("diffusion_coefficient_name", "diffusion_coefficient",  "The name of the phase dependent material property that contains the water vapor diffusion coefficient (D_v)");
  params.addRequiredCoupledVar("phi", "Phase-field variable, phi");
  params.addParam<bool>("use_dphi_dt", true, "Include the dphi_dt portion of the forcing function");
  params.addParam<bool>("use_time_scaling", false, "Temporally scale this term");

  return params;
}

MassTransportSourceMMS::MassTransportSourceMMS(const InputParameters & parameters) :
    Kernel(parameters),
    PropertyUserObjectInterface(parameters),
    _D_v(getMaterialProperty<Real>(getParam<std::string>("diffusion_coefficient_name"))),
    _phi(coupledValue("phi")),
    _use_dphi_dt(getParam<bool>("use_dphi_dt")),
    _use_scale(getParam<bool>("use_time_scaling")),
    _xi(_property_uo.getParamTempl<Real>("temporal_scaling"))
{
}

Real
MassTransportSourceMMS::computeQpResidual()
{
  using namespace std;

  Real t = _t;
  Real x = _q_point[_qp](0);
  Real y = _q_point[_qp](1);
  Real D = _D_v[_qp];

  Real f,term1,term2,term3;
  term1 = sin(2.0*pi*x)*cos(2.0*pi*y);
  term2 = 8.0*pow(pi, 2.0)*D*t*sin(2.0*pi*x)*cos(2.0*pi*y);
  term3  = 0.5*x*y;

  if (_use_scale)
  {
    term2=_xi*term2;
    term3=_xi*term3;
  }

  f=term1+term2;

  if (_use_dphi_dt)
    f+=term3;

  return -_test[_i][_qp] * f;
}
