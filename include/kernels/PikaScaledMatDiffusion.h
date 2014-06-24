#ifndef PIKASCALEDMATDIFFUSION_H
#define  PIKASCALEDMATDIFFUSION_H

#include "MatDiffusion.h"
#include "PropertyUserObjectInterface.h"

//Forward Declarations
class PikaScaledMatDiffusion;

template<>
InputParameters validParams<PikaScaledMatDiffusion>();

class PikaScaledMatDiffusion : 
  public MatDiffusion,
  public PropertyUserObjectInterface
{
public:
  PikaScaledMatDiffusion(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();

};

#endif // PIKASCALEDMATDIFFUSION_H
