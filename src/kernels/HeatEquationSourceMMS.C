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

#include "HeatEquationSourceMMS.h"

registerMooseObject("PikaApp", HeatEquationSourceMMS);

template<>
InputParameters validParams<HeatEquationSourceMMS>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<std::string>("conductivity_name", "conductivity",  "The name of the phase dependent material property that contains the conductivity coefficient ( K(phi) )");
  params.addParam<std::string>("heat_capacity_name", "heat_capacity",  "The name of the phase dependent  material property that contains the heat capacity coefficient ( C(phi) )");
  params.addParam<std::string>("latent_heat_name", "latent_heat",  "The name of the material property that contains the latent heat coefficient for sublimation (L_sg)");
  params.addRequiredCoupledVar("phase_variable", "Phase-field variable, phi");
  params.addParam<bool>("use_dphi_dt", true, "Include the dphi_dt portion of the forcing function");
  params.addParam<bool>("use_time_scaling", false, "Temporally scale the forcing term");
  return params;
}

HeatEquationSourceMMS::HeatEquationSourceMMS(const InputParameters & parameters) :
    Kernel(parameters),
    PropertyUserObjectInterface(parameters),
    _k(getMaterialProperty<Real>(getParam<std::string>("conductivity_name"))),
    _c(getMaterialProperty<Real>(getParam<std::string>("heat_capacity_name"))),
    _L_sg(getMaterialProperty<Real>(getParam<std::string>("latent_heat_name"))),
    _phi(coupledValue("phase_variable")),
    _use_dphi_dt(getParam<bool>("use_dphi_dt")),
    _use_scale(getParam<bool>("use_time_scaling")),
    _xi(_property_uo.getParamTempl<Real>("temporal_scaling"))
{
}

Real
HeatEquationSourceMMS::computeQpResidual()
{
  using namespace std;

  Real t = _t;
  Real x = _q_point[_qp](0);
  Real y = _q_point[_qp](1);
  Real k = _k[_qp];
  Real c = _c[_qp];
  Real L_sg = _L_sg[_qp];
  Real pi = libMesh::pi;
  Real f,term1,term2,term3;
  term1 = c*sin(2.0*pi*x)*sin(2.0*pi*y);
  term2 = 8.0*pow(pi, 2)*k*t*sin(2.0*pi*x)*sin(2.0*pi*y);
  term3 = 0.5*L_sg*pow(x*y, 2.0);


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
