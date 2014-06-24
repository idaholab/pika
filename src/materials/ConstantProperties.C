#include "ConstantProperties.h"
#include "InputParameters.h"

template<>
InputParameters validParams<ConstantProperties>()
{
  InputParameters params = validParams<Material>();
  params += validParams<PropertyUserObjectInterface>();

  return params;
}


ConstantProperties::ConstantProperties(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    PropertyUserObjectInterface(name, parameters),
    _interface_free_energy(declareProperty<Real>("interface_free_energy")),
    _mean_molecular_spacing(declareProperty<Real>("mean_molecular_spacing")),
    _boltzmann(declareProperty<Real>("boltzmann")),
    _condensation_coefficient(declareProperty<Real>("condensation_coefficient")),
    _mass_water_molecule(declareProperty<Real>("mass_water_molecule")),
    _interface_thickness(declareProperty<Real>("interface_thickness")),
    _atmospheric_pressure(declareProperty<Real>("atmospheric_pressure")),
    _gas_constant_dry_air(declareProperty<Real>("gas_constant_dry_air")),
    _gas_constant_water_vapor(declareProperty<Real>("gas_constant_water_vapor")),
    _mobility(declareProperty<Real>("mobility")),
    _latent_heat(declareProperty<Real>("latent_heat"))
{
}

void
ConstantProperties::computeQpProperties()
{
  _interface_free_energy[_qp] = _property_uo._gamma;
  _mean_molecular_spacing[_qp] = _property_uo._a;
  _boltzmann[_qp] = _property_uo._k;
  _condensation_coefficient[_qp] = _property_uo._alpha;
  _mass_water_molecule[_qp] = _property_uo._m;
  _interface_thickness[_qp] = _property_uo._W;
  _atmospheric_pressure[_qp] = _property_uo._P_a;
  _gas_constant_dry_air[_qp] = _property_uo._R_da;
  _gas_constant_water_vapor[_qp] = _property_uo._R_v;
  _latent_heat[_qp] = _property_uo._L_sg;
  _mobility[_qp] = _property_uo._mobility;
}
