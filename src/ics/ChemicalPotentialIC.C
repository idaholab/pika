#include "ChemicalPotentialIC.h"
#include "PropertyUserObject.h"
template<>
InputParameters validParams<ChemicalPotentialIC>()
{
  InputParameters params = validParams<InitialCondition>();
  params += validParams<PropertyUserObjectInterface>();
  params.addRequiredCoupledVar("temperature", "The temperature variable");
  params.addRequiredCoupledVar("phase_variable", "The variable containing the phase of the continuum (phi)");
  return params;
}

ChemicalPotentialIC::ChemicalPotentialIC(const std::string & name, InputParameters parameters) :
    InitialCondition(name, parameters),
    PropertyUserObjectInterface(name, parameters),
    _temperature(coupledValue("temperature")),
    _phase(coupledValue("phase_variable"))
{
}

Real
ChemicalPotentialIC::value(const Point & /*p*/)
{
  if (_phase[_qp]<0.95)
  {
    Real f =  _property_uo.equilibriumConcentration(_temperature[_qp]) * (1.0-_phase[_qp])/2.0;
    std::cout<<_temperature[_qp]<<' ' <<_phase[_qp]<< ' '<<f<<std::endl; 
    return f;
  }    
  else
    return 0.0;
}
