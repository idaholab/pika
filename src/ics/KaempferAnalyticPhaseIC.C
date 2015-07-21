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

#include "KaempferAnalyticPhaseIC.h"

template<>
InputParameters validParams<KaempferAnalyticPhaseIC>()
{
  InputParameters params = validParams<InitialCondition>();
  params.addRequiredParam<Real>("x1", "Input x_min for box 1");
  params.addRequiredParam<Real>("x2", "Input x_max for box 1");
  params.addRequiredParam<Real>("x3", "Input x_min for box 2");
  params.addRequiredParam<Real>("x4", "Input x_max for box 2");
  params.addParam<Real>("phi_new",0.0, "Set new value of phi to be applied");
  params.addParam<Real>("phi_old",0.0, "Set value of phi everywhere not in an interval");
  return params;
}

KaempferAnalyticPhaseIC::KaempferAnalyticPhaseIC(const InputParameters & parameters) :
    InitialCondition(parameters),
    _x1(getParam<Real>("x1")),
    _x2(getParam<Real>("x2")),
    _x3(getParam<Real>("x3")),
    _x4(getParam<Real>("x4")),
    _phi_new(getParam<Real>("phi_new")),
    _phi_old(getParam<Real>("phi_old"))
{}

Real
KaempferAnalyticPhaseIC::value( const Point & p)
{
  if ( (p(0) >= _x1 && p(0) <= _x2) ||  (p(0) >= _x3 && p(0) <= _x4) )
    return _phi_new;

  else
    return _phi_old;
}
