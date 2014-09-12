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

#ifndef SHARPINTERFACECHECKICE_H
#define SHARPINTERFACECHECKICE_H

// MOOSE includes
#include "AuxKernel.h"

// Forward declarations
class SharpInterfaceCheckIce;

template<>
InputParameters validParams<SharpInterfaceCheckIce>();

class SharpInterfaceCheckIce : public AuxKernel
{
  public:

  /**
   * Class constructor
   * @param name
   * @param parameters
   */
   SharpInterfaceCheckIce(const std::string & name, InputParameters parameters);

   protected:
     virtual Real computeValue();

   private:
    const MaterialProperty<Real> & _w;
    const MaterialProperty<Real> & _ki;
    const MaterialProperty<Real> & _ci;
    const MaterialProperty<Real> & _beta;
};
#endif //SHARPINTERFACECHECKICE_H
