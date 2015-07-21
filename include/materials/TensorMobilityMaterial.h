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
  TensorMobilityMaterial(const InputParameters & parameters);

  /**
   * Class destructor
   */
  virtual ~TensorMobilityMaterial();

protected:
  virtual void computeQpProperties();

private:

  RealTensorValue normalOutputProduct();

  const RealTensorValue _identity;

  VariableValue & _phase;

  VariableGradient & _grad_phase;

  //
  const Real & _M_1;
  const Real & _M_2;

  MaterialProperty<Real> & _M_parallel;
  MaterialProperty<Real> & _M_perpendicular;
  MaterialProperty<RealTensorValue> & _M_tensor;




};

#endif //TENSORMOBILITYMATERIAL_H
