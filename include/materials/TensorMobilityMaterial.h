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

#ifndef TENSORMOBILITYMATERIAL_H
#define TENSORMOBILITYMATERIAL_H

// MOOSE includes
#include "Material.h"

// Forward declerations
class TensorMobilityMaterial;

template<>
InputParameters validParams<TensorMobilityMaterial>();

/**
 *
 */
class TensorMobilityMaterial : public Material
{
public:

  /**
   * Class constructor
   * @param prop_name
   */
  TensorMobilityMaterial(const std::string & name, InputParameters parameters);

  /**
   * Class destructor
   */
  virtual ~TensorMobilityMaterial();

protected:
  virtual void computeQpProperties();

private:

  VariableValue & _phase;

  VariableGradient & _grad_phase;

  //
  Real _M_1;
  Real _M_2;

  MaterialProperty<Real> & _M_parallel;
  MaterialProperty<Real> & _M_perpendicular;





};

#endif //TENSORMOBILITYMATERIAL_H
