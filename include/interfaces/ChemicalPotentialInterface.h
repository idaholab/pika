#ifndef CHEMICALPOTENTIALINTERFACE_H
#define CHEMICALPOTENTIALINTERFACE_H

#include <vector>

#include "UserObject.h"

#include "libmesh/libmesh_common.h"

// Forward declarations
class ChemicalPotentialInterface;
class ChemicalPotentialPropertyUserObject;


template<>
InputParameters validParams<ChemicalPotentialInterface>();


class ChemicalPotentialInterface
{
public:

  ChemicalPotentialInterface(const ChemicalPotentialPropertyUserObject & uo);

  virtual ~ChemicalPotentialInterface(){};

protected:

  /**
   * Computes the specific humidity ratio (x_s; [kg/kg]; Eq. (1))
   * @param T Temperature at which to compute the ratio
   */
  Real specificHumidityRatio(Real T);

  Real saturationPressureOfWaterVaporOverIce(Real T);

  Real equilibriumWaterVaporConcentrationAtSaturation(Real T);

  Real equilibriumConcentration(Real T);

  const ChemicalPotentialPropertyUserObject & _property_uo;

private:

  /// Fitting coefficients for saturation vapor pressure, Table 1
  std::vector<libMesh::Real> _K;


};

#endif // CHEMICALPOTENTIALINTERFACE_H
