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

#include "PikaChemicalPotentialIC.h"
#include "PropertyUserObject.h"

template<>
InputParameters validParams<PikaChemicalPotentialIC>()
{
  InputParameters params = validParams<InitialCondition>();
  params += validParams<PropertyUserObjectInterface>();
  params.addRequiredCoupledVar("temperature", "The temperature variable");
  params.addRequiredCoupledVar("phase_variable", "The variable containing the phase of the continuum (phi)");
  return params;
}

PikaChemicalPotentialIC::PikaChemicalPotentialIC(const InputParameters & parameters) :
    InitialCondition(parameters),
    PropertyUserObjectInterface(parameters),
    _temperature(coupledValue("temperature")),
    _phase(coupledValue("phase_variable"))
{
}

Real
PikaChemicalPotentialIC::value(const Point & /*p*/)
{
  return _property_uo.equilibriumChemicalPotential(_temperature[_qp]) * ((1.0 - _phase[_qp]) / 2.0);
}
