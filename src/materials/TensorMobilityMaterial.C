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

#include "TensorMobilityMaterial.h"

template<>
InputParameters validParams<TensorMobilityMaterial>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredCoupledVar("phi", "The phase-field variable to couple");
  params.addRequiredParam<Real>("M_1_value", "Name of material property for first mobility coefficient");
  params.addRequiredParam<Real>("M_2_value", "Name of material property for second econd mobility coefficient");
  params.addParam<std::string>("coefficient_name","M_tensor", "The name of the tensor mobility material property");
  return params;
}

TensorMobilityMaterial::TensorMobilityMaterial(const InputParameters & parameters) :
    Material(parameters),
    _identity(1,0,0, 0,1,0, 0,0,1),
    _phase(coupledValue("phi")),
    _grad_phase(coupledGradient("phi")),
    _M_1(getParam<Real>("M_1_value")),
    _M_2(getParam<Real>("M_2_value")),
    _M_parallel(declareProperty<Real>("M_parallel")),
    _M_perpendicular(declareProperty<Real>("M_perpendicular")),
    _M_tensor(declareProperty<RealTensorValue>(getParam<std::string>("coefficient_name")))
{
}

TensorMobilityMaterial::~TensorMobilityMaterial()
{
}

void
TensorMobilityMaterial::computeQpProperties()
{
  //Mobility for PHI = {0,1}
  /*_M_parallel[_qp] = _M_1 * _phase[_qp] + _M_2 * (1.0 - _phase[_qp]);
  _M_perpendicular[_qp] = 1.0 / (1.0/_M_1 * _phase[_qp] + 1.0/_M_2 * (1.0 - _phase[_qp]));
  */

  //Mobility for PHI = {-1,1}
  _M_parallel[_qp] = _M_1 * (1.0 + _phase[_qp]) / 2.0 + _M_2 * (1.0 - _phase[_qp])/2.0;
  _M_perpendicular[_qp] = 1.0 / ((1.0/_M_1) * (1 + _phase[_qp])/2.0 + (1.0/_M_2) * ((1.0 - _phase[_qp])/2.0));
  RealTensorValue nxn = normalOutputProduct();

  _M_tensor[_qp] = _M_perpendicular[_qp]*nxn + _M_parallel[_qp]*(_identity - nxn);
}

RealTensorValue
TensorMobilityMaterial::normalOutputProduct()
{

  RealVectorValue n = _grad_phase[_qp] / _grad_phase[_qp].size();
  RealTensorValue nxn;

  for (unsigned int i = 0; i < LIBMESH_DIM; ++i)
    for (unsigned int j = 0; j < LIBMESH_DIM; ++j)
      nxn(i,j) = n(i)*n(j);

  return nxn;

}
