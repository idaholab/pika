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

#ifndef KAEMPFERANALYTICPHASEIC_H
#define KAEMPFERANALYTICPHASEIC_H

#include "InitialCondition.h"

class KaempferAnalyticPhaseIC;

template<>
InputParameters validParams<KaempferAnalyticPhaseIC>();

class KaempferAnalyticPhaseIC : public InitialCondition
{
public:
  KaempferAnalyticPhaseIC(const InputParameters & parameters);

  virtual Real value(const Point & p);

protected:
  Real _x1, _x2, _x3, _x4;
  Real _phi_new;
  Real _phi_old;
};

#endif // KAEMPFERANALYTICPHASEIC_H
