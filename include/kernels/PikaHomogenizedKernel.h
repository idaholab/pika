#ifndef PIKAHOMOGENIZEDKERNEL_H
#define PIKAHOMOGENIZEDKERNEL_H

#include "HomogenizationHeatConduction.h"

//PIKA Include
#include "PropertyUserObjectInterface.h"
#include "CoefficientKernelInterface.h"

class PikaHomogenizedKernel : public 
  HomogenizationHeatConduction, 
  PropertyUserObjectInterface,
  CoefficientKernelInterface 
{
public:

  PikaHomogenizedKernel(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();

};

template<>
InputParameters validParams<PikaHomogenizedKernel>();

#endif //PIKAHOMOGENIZEDKERNEL_H
