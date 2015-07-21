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

#ifndef COEFFICIENTKERNELTINTERFACE_H
#define COEFFICIENTKERNELTINTERFACE_H

// libMesh includes
#include "libmesh/libmesh_common.h"

// PIKA includes
#include "PropertyUserObjectInterface.h"

// Forward declarations
class CoefficientKernelInterface;
class InputParameters;
template <class T> class MaterialProperty;

template<>
InputParameters validParams<CoefficientKernelInterface>();

/**
 * A class providing common functionality for coefficient Kernels.
 */
class CoefficientKernelInterface : public PropertyUserObjectInterface
{
public:
  CoefficientKernelInterface(const InputParameters & parameters);

protected:

  /**
   * Flag for material property usage
   * @return True when material property coefficient is desired
   */
  bool useMaterial();

  /**
   * Set the pointer to the material property to use as the coefficient
   *
   * The MateialPropertyInterface::getMaterialProperty method does a lot more than
   * just returns the property and due to inheritance this method is not available to this
   * class, so the following must be included in any class using this interface.
   *
   *   if (useMaterial())
   *      setMaterialPropertyPointer(&getMaterialProperty<Real>("property"));
   */
  void setMaterialPropertyPointer(const MaterialProperty<libMesh::Real> * ptr);

  /**
   * Returns the proper, scaled coefficient
   * @param The current quadrature point index, i.e., _qp
   * @return A scalar (libMesh::Real) containing the properly scaled coefficient
   */
  libMesh::Real coefficient(unsigned int qp);

  /// Flag indicating to use material property rather than scalar coefficient
  const bool _use_material;

  /// Pointer to material property to utilize as a coefficient
  /* This must be a pointer because getMaterialProperty returns a const reference and
   * this member is optional, so NULL is a valid value */
  const MaterialProperty<libMesh::Real> * _material_coefficient;

  /// Scalar coefficient
  const libMesh::Real _coefficient;

  /// Coefficient offset
  const libMesh::Real _offset;

  /// Coefficient offset
  const libMesh::Real _scale;

  /// Time scaling factor (\xi)
  libMesh::Real _time_scale;

};
#endif // COEFFICIENTKERNELINTERFACE_H
