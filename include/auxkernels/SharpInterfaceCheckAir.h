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

#ifndef SHARPINTERFACECHECKAIR_H
#define SHARPINTERFACECHECKAIR_H

// MOOSE includes
#include "AuxKernel.h"

// Forward declarations
class SharpInterfaceCheckAir;

template<>
InputParameters validParams<SharpInterfaceCheckAir>();

class SharpInterfaceCheckAir : public AuxKernel
{
  public:

  /**
   * Class constructor
   * @param name
   * @param parameters
   */
   SharpInterfaceCheckAir(const std::string & name, InputParameters parameters);

   protected:
     virtual Real computeValue();

   private:
    const MaterialProperty<Real> & _w;
    const MaterialProperty<Real> & _ka;
    const MaterialProperty<Real> & _ca;
    const MaterialProperty<Real> & _beta;
};
#endif //SHARPINTERFACECHECKAIR_H
