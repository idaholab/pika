#include "ConstantProperties.h"
#include "InputParameters.h"
#include "ChemicalPotentialPropertyUserObject.h"

template<>
InputParameters validParams<ConstantProperties>()
{
  InputParameters params = validParams<Material>();
  params += validParams<ChemicalPotentialInterface>();

  params.addParam<Real>("interface_free_energy", 1.09e-1, "Interface free energy [J/m^2]");
  params.addParam<Real>("mean_molecular_spacing", 3.19e-10, "Mean inter-molecular spacing in ice [m]");
  params.addParam<Real>("boltzmann", 1.3806488e-23, "Boltzmann constant [J/k]");
  params.addParam<Real>("condensation_coefficient", 1e-2, "Condensation coefficient [unitless]");
  params.addParam<Real>("mass_water_molecule", 2.9900332e-26, "Mass of water molecule [kg]");
  params.addParam<Real>("interface_thickness", 8e-6, "Interface thickness [m]");
  params.addParam<Real>("mobility", 1, "Phase-field mobility value");
  params.addParam<Real>("latent_heat", 2.6e9, "Latent heat of sublimation [J/m^3]");

  return params;
}


ConstantProperties::ConstantProperties(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    ChemicalPotentialInterface(getUserObject<ChemicalPotentialPropertyUserObject>("property_user_object")),
    _interface_free_energy(declareProperty<Real>("interface_free_energy")),
    _mean_molecular_spacing(declareProperty<Real>("mean_molecular_spacing")),
    _boltzmann(declareProperty<Real>("boltzmann")),
    _condensation_coefficient(declareProperty<Real>("condensation_coefficient")),
    _mass_water_molecule(declareProperty<Real>("mass_water_molecule")),
    _interface_thickness(declareProperty<Real>("interface_thickness")),
    _atmospheric_pressure(declareProperty<Real>("atmospheric_pressure")),
    _latent_heat(declareProperty<Real>("latent_heat"))
{
}

void
ConstantProperties::computeQpProperties()
{
  _interface_free_energy[_qp] = getParam<Real>("interface_free_energy");
  _mean_molecular_spacing[_qp] = getParam<Real>("mean_molecular_spacing");
  _boltzmann[_qp] = getParam<Real>("boltzmann");
  _condensation_coefficient[_qp] = getParam<Real>("condensation_coefficient");
  _mass_water_molecule[_qp] = getParam<Real>("mass_water_molecule");
  _interface_thickness[_qp] = getParam<Real>("interface_thickness");
  _atmospheric_pressure[_qp] = atmosphericPressure();
  _latent_heat[_qp] = getParam<Real>("latent_heat");
}
