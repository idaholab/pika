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
   * @param T Temperature at which to compute the ratio [kg/kg]
   * @return The specific humidity ratio
   */
  Real specificHumidityRatio(Real T);

  /**
   * Computes the saturation pressure of water vapor over ice (P_vs; [Pa]; Eq. (2))
   * @param T Temperature at which to compute the value
   * @return The saturation pressure of water vapor over ice [Pa]
   */
  Real saturationPressureOfWaterVaporOverIce(Real T);

  Real equilibriumWaterVaporConcentrationAtSaturation(Real T);

  Real equilibriumConcentration(Real T);


  const ChemicalPotentialPropertyUserObject & _property_uo;

private:

  /// Fitting coefficients for saturation vapor pressure, Wexler, 2007, Table 2
  std::vector<libMesh::Real> _K;
};

#endif // CHEMICALPOTENTIALINTERFACE_H
