#ifndef MATDIFFUSION_H
#define MATDIFFUSION_H

#include "Diffusion.h"
#include "Material.h"
#include "PropertyUserObjectInterface.h"

//Forward Declarations
class PikaScaledMatDiffusion;

template<>
InputParameters validParams<PikaScaledMatDiffusion>();

class PikaScaledMatDiffusion : 
  public Diffusion,
  PropertyUserObjectInterface
{
public:
  PikaScaledMatDiffusion(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  std::string _D_name;

  MaterialProperty<Real> & _D;

  const Real & _xi;
};

#endif //MATDIFFUSION_H
