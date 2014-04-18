/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "ChemicalPotentialPropertyUserObject.h"

template<>
InputParameters validParams<ChemicalPotentialPropertyUserObject>()
{
  InputParameters params = validParams<GeneralUserObject>();
  params.addParam<Real>("density_ice", 918.9, "Density of ice, \rho_i [kg/m^3]");
  params.addParam<Real>("density_air", 1.341, "Density of air, \rho_a [kg/m^3]");
  params.addParam<Real>("atmospheric_pressure", 1.01325e-5, "Atmospheric pressure, P_a [Pa]");
  params.addParam<Real>("gas_constant_dry_air", 286.9, "Gas constant for dry air, R_{da} [J/(Kg K)]");
  params.addParam<Real>("gas_constant_water_vapor", 461.5, "Gas constant for water vapor, R_v [J/(Kg K)]");
  params.addParam<Real>("reference_temperature", 258.2 ,"Reference temperature [K]");
  return params;
}

ChemicalPotentialPropertyUserObject::ChemicalPotentialPropertyUserObject(const std::string & name, InputParameters parameters) :
    GeneralUserObject(name, parameters),
    _rho_i(getParam<Real>("density_ice")),
    _rho_a(getParam<Real>("density_air")),
    _P_a(getParam<Real>("atmospheric_pressure")),
    _R_da(getParam<Real>("gas_constant_dry_air")),
    _R_v(getParam<Real>("gas_constant_water_vapor")),
    _T_0(getParam<Real>("reference_temperature"))
{
}

ChemicalPotentialPropertyUserObject::~ChemicalPotentialPropertyUserObject()
{
}

void
ChemicalPotentialPropertyUserObject::execute()
{
}

Real
ChemicalPotentialPropertyUserObject::iceDensity(Real /* T */)
{
  return _rho_i;
}

Real
ChemicalPotentialPropertyUserObject::airDensity(Real /* T */)
{
  return _rho_i;
}


Real
ChemicalPotentialPropertyUserObject::atmosphericPressure()
{
  return _P_a;
}

Real
ChemicalPotentialPropertyUserObject::gasConstantWatorVapor()
{
  return _R_v;
}

Real
ChemicalPotentialPropertyUserObject::gasConstantDryAir()
{
  return _R_da;
}
