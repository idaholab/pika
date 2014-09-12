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
