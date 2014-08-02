/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "PikaCriteria.h"

template<>
InputParameters validParams<PikaCriteria>()
{
  MooseEnum criteria("ice=0, air=1, vapor=2");
  InputParameters params = validParams<AuxKernel>();
  params += validParams<PropertyUserObjectInterface>();
  params += validParams<CoefficientKernelInterface>();
  params.suppressParameter<Real>("offset");
  params.suppressParameter<Real>("scale");
  params.suppressParameter<Real>("coefficient");
  params.suppressParameter<std::string>("property");
  params.addParam<MooseEnum>("criteria", criteria, "Select the type of criteria to compute, see Eq. (43)");
  return params;
}

PikaCriteria::PikaCriteria(const std::string & name, InputParameters parameters) :
    AuxKernel(name, parameters),
    PropertyUserObjectInterface(name,parameters),
    CoefficientKernelInterface(name,parameters),
    _k_i(getMaterialProperty<Real>("conductivity_ice")),
    _k_a(getMaterialProperty<Real>("conductivity_air")),
    _c_i(getMaterialProperty<Real>("heat_capacity_ice")),
    _c_a(getMaterialProperty<Real>("heat_capacity_air")),
    _rho_vs(getMaterialProperty<Real>("equilibrium_water_vapor_concentration_at_saturation")),
    _rho_i(getMaterialProperty<Real>("density_ice")),
    _D_v(getMaterialProperty<Real>("water_vapor_diffusion_coefficient")),
    _beta(getMaterialProperty<Real>("interface_kinetic_coefficient")),
    _criteria(getParam<MooseEnum>("criteria"))
    
{
}

Real
PikaCriteria::computeValue()
{
  Real output;

  if (_criteria == 0)
    output = (_k_i[_qp] * _rho_vs[_qp] * _beta[_qp]) / (_c_i[_qp] * _rho_i[_qp] * coefficient(_qp));

  else if (_criteria == 1)
    output = (_k_a[_qp] * _rho_vs[_qp] * _beta[_qp]) / (_c_a[_qp] * _rho_i[_qp] * coefficient(_qp) );

  else if (_criteria == 2)
    output = (_D_v[_qp] * _rho_vs[_qp] * _beta[_qp]) / (_rho_i[_qp] * coefficient(_qp));

  else
    // Should not be possible to get here
    mooseError("Invalid criteria, select from: ice, air, or vapor");


  return output;

}
