#include "ConstantProperties.h"
#include "InputParameters.h"
#include "ChemicalPotentialPropertyUserObject.h"

template<>
InputParameters validParams<ConstantProperties>()
{
  typedef std::pair<Real, std::string> PropertyPair;
  typedef std::map<std::string, PropertyPair > PropertyMap;

  InputParameters params = validParams<Material>();
  params += validParams<ChemicalPotentialInterface>();


  PropertyMap map;
  map["interface_free_energy"] = PropertyPair(1.09e-1, "Interface free energy [J/m^2]");
  map["mean_molecular_spacing"] = std::pair<Real, std::string>(3.19e-10, "Mean inter-molecular spacing in ice [m]");
  map["boltzmann"] = std::pair<Real, std::string>(1.3806488e-23, "Boltzmann constant [J/k]");
  map["condensation_coefficient"] = std::pair<Real, std::string>(1e-2, "Condensation coefficient [unitless]");
  map["mass_water_molecule"] = std::pair<Real, std::string>(2.9900332e-26, "Mass of water molecule [kg]");
  map["interface_thickness"] = std::pair<Real, std::string>(8e-6, "Interface thickness [m]");
  map["mobility"] = std::pair<Real, std::string>(1, "Phase-field mobility value");
//  map["reference_temperature"] = std::pair<Real, std::string>(258.2 ,"Reference temperature [K]");
//  map["atmospheric_pressure"] = std::pair<Real, std::string>(1.01325e-5, "Atmospheric pressure [Pa]");
//  map["gas_constant_dry_air"] = std::pair<Real, std::string>(286.9, "Gas constant for dry air [J/(Kg K)]");
//  map["gas_constant_water_vapor"] = std::pair<Real, std::string>(461.5, "Gas constant for water vapor [J/(Kg K)]");
  map["latent_heat"] = std::pair<Real, std::string>(2.6e9, "Latent heat of sublimation [J/m^3]");

  std::vector<std::string> names;
  std::vector<Real> values;
  for (PropertyMap::iterator it = map.begin(); it != map.end(); ++it)
  {
    params.addParam<Real>(it->first, it->second.first, it->second.second);
    names.push_back(it->first);
    values.push_back(it->second.first);
  }

  params.addPrivateParam<std::vector<std::string> >("_property_names", names);
  params.addPrivateParam<std::vector<Real> >("_property_values", values);


  return params;
}


ConstantProperties::ConstantProperties(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    ChemicalPotentialInterface(getUserObject<ChemicalPotentialPropertyUserObject>("property_user_object")),
    _property_names(getParam<std::vector<std::string> >("_property_names")),
    _property_values(getParam<std::vector<Real> >("_property_values")),
    _atmospheric_pressure(declareProperty<Real>("atmospheric_pressure"))
{
  for (std::vector<std::string>::iterator it = _property_names.begin(); it != _property_names.end(); ++it)
    _property_ptrs.push_back(&declareProperty<Real>(*it));



}

void
ConstantProperties::computeQpProperties()
{
  for (unsigned int i = 0; i < _property_ptrs.size(); ++i)
    (*_property_ptrs[i])[_qp] = _property_values[i];


  _atmospheric_pressure[_qp] = atmosphericPressure();
}
