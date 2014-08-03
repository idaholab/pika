/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "TensorDiffusion.h"

template<>
InputParameters validParams<TensorDiffusion>()
{
  InputParameters params = validParams<Diffusion>();
  params += validParams<PropertyUserObjectInterface>();
  params += validParams<CoefficientKernelInterface>();
  params.addCoupledVar("phase", "Phase-field variable");

  params.addParam<bool>("use_temporal_scaling", false, "Use the temporal scaling factor");

  params.addRequiredParam<std::string>("M_1_property_name", "Name of material property for first mobility coefficient");
  params.addRequiredParam<std::string>("M_2_property_name", "Name of material property for second econd mobility coefficient");


  return params;
}

TensorDiffusion::TensorDiffusion(const std::string & name, InputParameters parameters) :
    Diffusion(name, parameters),
    PropertyUserObjectInterface(name,parameters),
    _phase(coupledValue("phase")),
    _grad_phase(coupledGradient("phase")),
    _M_1(getMaterialProperty<Real>(getParam<std::string>("M_1_property_name"))),
    _M_2(getMaterialProperty<Real>(getParam<std::string>("M_2_property_name"))),
    _xi(getParam<bool>("use_temporal_scaling") ? _property_uo.temporalScale() : 1.0)
{
}

TensorDiffusion::~TensorDiffusion()
{
}


Real
TensorDiffusion::computeQpResidual()
{
  RealTensorValue M = mobilityTensor();
  return _grad_test[_i][_qp] * _xi * M * _grad_u[_qp];
}

Real
TensorDiffusion::computeQpJacobian()
{
  RealTensorValue M = mobilityTensor();
  return _grad_test[_i][_qp] * _xi * M *_grad_phi[_j][_qp];
}

RealTensorValue
TensorDiffusion::mobilityTensor()
{
    //Mobility for PHI = {-1,1}
  _M_parallel[_qp] = _M_1[_qp] * (1.0 + _phase[_qp]) / 2.0 + _M_2[_qp[ * (1.0 - _phase[_qp])/2.0;
  _M_perpendicular[_qp] = 1.0 / ((1.0/_M_1[_qp]) * (1 + _phase[_qp])/2.0 + (1.0/_M_2[_qp]) * ((1.0 - _phase[_qp])/2.0));

  RealTensorValue nxn = normalOutputProduct();
  return _M_perpendicular[_qp]*nxn + _M_parallel[_qp]*(_identity - nxn);

                                                                       }
RealTensorValue
TensorDiffusion::normalOutputProduct()
{

  RealVectorValue n = _grad_phase[_qp] / _grad_phase[_qp].size();
  RealTensorValue nxn;

  for (unsigned int i = 0; i < LIBMESH_DIM; ++i)
    for (unsigned int j = 0; j < LIBMESH_DIM; ++j)
      nxn(i,j) = n(i)*n(j);

  return nxn;

}
