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

#ifndef CHEMICALPOTENTIALPROPERTYUSEROBJECT_H
#define CHEMICALPOTENTIALPROPERTYUSEROBJECT_H

// MOOSE includes
#include "GeneralUserObject.h"

// Forward declarations
class ChemicalPotentialPropertyUserObject;

template<>
InputParameters validParams<ChemicalPotentialPropertyUserObject>();

/**
 *
 */
class ChemicalPotentialPropertyUserObject : public GeneralUserObject
{
public:

  /**
   * Class constructor
   * @param name
   * @param parameters
   */
  ChemicalPotentialPropertyUserObject(const std::string & name, InputParameters parameters);

  /**
   * Class destructor
   */
  virtual ~ChemicalPotentialPropertyUserObject(){}

  /**
   *
   */
  virtual void execute(){}

  virtual void initialize(){}
  virtual void finalize(){}


  /**
   * Return the density of ice as a function of temperature
   */
  Real iceDensity(Real T) const;

  /**
   *
   */
  Real airDensity(Real T) const;

  Real referenceTemperature() const;

  Real gasConstantWaterVapor() const;

  Real gasConstantDryAir() const;

  Real atmosphericPressure() const;

private:

  const Real _rho_i;
  const Real _rho_a;
  const Real _P_a;
  const Real _R_da;
  const Real _R_v;
  const Real _T_0;

};

#endif // CHEMICALPOTENTIALPROPERTYUSEROBJECT_H
