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

#ifndef PIKAPHASETIMESTEPPOSTPROCESSOR_H
#define PIKAPHASETIMESTEPPOSTPROCESSOR_H

#include "NodalVariablePostprocessor.h"

//Forward Declarations
class PikaPhaseTimestepPostprocessor;

// Input parameters
template<>
InputParameters validParams<PikaPhaseTimestepPostprocessor>();

/// A postprocessor for collecting the nodal min or max value
class PikaPhaseTimestepPostprocessor : public NodalVariablePostprocessor
{
public:

  /**
   * Class constructor
   * @param name The name of the postprocessor
   * @param parameters The input parameters
   */
  PikaPhaseTimestepPostprocessor(const InputParameters & parameters);
  virtual void initialize();
  virtual void execute();
  virtual Real getValue();
  virtual void threadJoin(const UserObject & y);

protected:
  /// The minimum value
  Real _max_value;

  /// The maximum value
  Real _min_value;

  std::vector<Real> _range;
  Real _decrease_limit;
  Real _increase_limit;
  Real _decrease_factor;
  Real _increase_factor;


};

#endif // PIKAPHASETIMESTEPPOSTPROCESSOR_H
