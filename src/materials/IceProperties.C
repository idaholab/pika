#include "IceProperties.h"
#include "ChemicalPotentialPropertyUserObject.h"

template<>
InputParameters validParams<IceProperties>()
{
  InputParameters params = validParams<Material>();
  params += validParams<ChemicalPotentialInterface>();
  params.addRequiredCoupledVar("temperature", "The temperature variable to couple");
  params.addParam<Real>("conductivity_ice", 2.29, "Thermal conductivity or air, kappa_i [ W/(m K)]");
  params.addParam<Real>("heat_capacity_ice", 1.8e6, "Heat capacity of air, C_i [J/(m^3 K)]");
  return params;
}


IceProperties::IceProperties(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    ChemicalPotentialInterface(getUserObject<ChemicalPotentialPropertyUserObject>("property_user_object")),
    _temperature(coupledValue("temperature")),
    _rho_i(declareProperty<Real>("density_ice")),
    _kappa_i(declareProperty<Real>("conductivity_ice")),
    _C_i(declareProperty<Real>("heat_capacity_ice"))
{
}

void
IceProperties::computeQpProperties()
{
  _rho_i[_qp] = _property_uo.iceDensity(_temperature[_qp]);
  _kappa_i[_qp] = getParam<Real>("conductivity_ice");
  _C_i[_qp] = getParam<Real>("heat_capacity_ice");
}
