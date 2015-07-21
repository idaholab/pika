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

#ifndef IBEXSNOWMATERIAL_H
#define IBEXSNOWMATERIAL_H

// MOOSE includes
#include "Material.h"

// Forward declerations
class IbexSnowMaterial;

template<>
InputParameters validParams<IbexSnowMaterial>();

/**
 *
 */
class IbexSnowMaterial : public Material
{
public:

  /**
   * Class constructor
   * @param prop_name
   */
  IbexSnowMaterial(const InputParameters & parameters);

protected:
  void computeQpProperties();

private:

  const VariableValue & _temperature;



  const Real _input_density;

  bool _compute_conductivity;

  const Real _input_conductivity;
  bool _compute_specific_heat;
  const Real _input_specific_heat;
  MaterialProperty<Real> & _density;
  MaterialProperty<Real> & _conductivity;
  MaterialProperty<Real> & _specific_heat;

  bool _use_conductivity_variable;
  const VariableValue & _conductivity_variable;

};

#endif //IBEXSNOWMATERIAL_H
