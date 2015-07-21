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

#include "PikaCriteria.h"

template<>
InputParameters validParams<PikaCriteria>()
{
  // Grab all the parameters from the base classes
  InputParameters params = validParams<AuxKernel>();
  params += validParams<PropertyUserObjectInterface>();

  // Controls which type of AuxKernel calculation if performed
  MooseEnum criteria("ice=0, air=1, vapor=2, velocity=3, time=4");
  params.addParam<MooseEnum>("criteria", criteria, "Select the type of criteria to compute, see Eqs. (43), (45), and (47)");
  params.addParam<bool>("use_temporal_scaling", false, "Temporally scale this Kernel with a value specified in PikaMaterials");

  // Temporal scaling
  params.addParam<Real>("estimated_pore_size", 10e-4, "Estimated pore size for time criterial (m); ; only need with 'criteria = time'");
  params.addCoupledVar("interface_velocity", 3.2e-10, "The name of the variable containing the interface velocity; only need with 'criteria = time | velocity'. Default: 3.2e-10 m/s");

  // These terms are not used, CoefficientKernelIntrface for temporal scaling of rho_i
  params.suppressParameter<Real>("offset");
  params.suppressParameter<Real>("scale");
  params.suppressParameter<Real>("coefficient");
  params.suppressParameter<std::string>("property");
  return params;
}

PikaCriteria::PikaCriteria(const InputParameters & parameters) :
    AuxKernel(parameters),
    PropertyUserObjectInterface(parameters),
    _v_n(coupledValue("interface_velocity")),
    _k_i(getMaterialProperty<Real>("conductivity_ice")),
    _k_a(getMaterialProperty<Real>("conductivity_air")),
    _c_i(getMaterialProperty<Real>("heat_capacity_ice")),
    _c_a(getMaterialProperty<Real>("heat_capacity_air")),
    _rho_vs(getMaterialProperty<Real>("equilibrium_water_vapor_concentration_at_saturation")),
    _rho_i(getMaterialProperty<Real>("density_ice")),
    _D_v(getMaterialProperty<Real>("water_vapor_diffusion_coefficient")),
    _beta(getMaterialProperty<Real>("interface_kinetic_coefficient")),
    _d_0(_property_uo.getParam<Real>("capillary_length")),
    _criteria(getParam<MooseEnum>("criteria")),
    _pore_size(getParam<Real>("estimated_pore_size")),
    _xi(getParam<bool>("use_temporal_scaling") ? _property_uo.temporalScale() : 1.0)
{
}

Real
PikaCriteria::computeValue()
{

  // The value to return
  Real output;

  // Eq. 43(a)
  if (_criteria == 0)
    output = (_k_i[_qp] * _rho_vs[_qp] * _beta[_qp]) / (_c_i[_qp] * _rho_i[_qp] * _xi);

  // Eq. 43(b)
  else if (_criteria == 1)
    output = (_k_a[_qp] * _rho_vs[_qp] * _beta[_qp]) / (_c_a[_qp] * _rho_i[_qp] * _xi);

  // Eq. 43(c)
  else if (_criteria == 2)
    output = (_D_v[_qp] * _rho_vs[_qp] * _beta[_qp]) / (_rho_i[_qp] * _xi);

  // Eq. 45
  else if (_criteria == 3)
    output = _d_0 / (_v_n[_qp] * _beta[_qp]);

  // Eq. 47
  else if (_criteria == 4)
  {
    Real tn = _pore_size / _v_n[_qp];
    Real td = _pore_size * _pore_size / _D_v[_qp];
    output = td / (_xi * tn);
  }
  else
    // Should not be possible to get here
    mooseError("Invalid criteria, select from: ice, air, or vapor");

  return output;
}
