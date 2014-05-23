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

#include "TensorMobilityMaterial.h"

template<>
InputParameters validParams<TensorMobilityMaterial>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredCoupledVar("phi", "The phase-field variable to couple");
  params.addRequiredParam<Real>("M_1", "First mobility coefficient");
  params.addRequiredParam<Real>("M_2", "Second mobility coefficient");
  return params;
}

TensorMobilityMaterial::TensorMobilityMaterial(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    _identity(1,0,0, 0,1,0, 0,0,1),
    _phase(coupledValue("phi")),
    _grad_phase(coupledGradient("phi")),
    _M_1(getParam<Real>("M_1")),
    _M_2(getParam<Real>("M_2")),
    _M_parallel(declareProperty<Real>("M_parallel")),
    _M_perpendicular(declareProperty<Real>("M_perpendicular")),
    _M_tensor(declareProperty<RealTensorValue>("M_tensor"))
{
}

TensorMobilityMaterial::~TensorMobilityMaterial()
{
}

void
TensorMobilityMaterial::computeQpProperties()
{
  _M_parallel[_qp] = _M_1 * _phase[_qp] + _M_2 * (1 - _phase[_qp]);
  _M_perpendicular[_qp] = 1 / (1/_M_1 * _phase[_qp] + 1/_M_2 * (1 - _phase[_qp]));
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
