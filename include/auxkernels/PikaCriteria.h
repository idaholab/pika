/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "AuxKernel.h"

//Pika includes
#include "PropertyUserObjectInterface.h"
class PikaCriteria;

template<>
InputParameters validParams<PikaCriteria>();

class PikaCriteria : public AuxKernel,
                     public PropertyUserObjectInterface
{
public:
  PikaCriteria(const std::string & name, InputParameters parameters);

  virtual ~PikaCriteria(){}

protected:
  Real computeValue();

private:
  const VariableValue & _v_n;
  const MaterialProperty<Real> & _k_i;
  const MaterialProperty<Real> & _k_a;
  const MaterialProperty<Real> & _c_i;
  const MaterialProperty<Real> & _c_a;
  const MaterialProperty<Real> & _rho_vs;
  const MaterialProperty<Real> & _rho_i;
  const MaterialProperty<Real> & _D_v;
  const MaterialProperty<Real> & _beta;
  const Real & _d_0;
  MooseEnum _criteria;
  Real _pore_size;
  Real _xi;

};
