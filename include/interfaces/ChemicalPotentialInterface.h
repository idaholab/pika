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

  Real humidityRatio(Real T);

  Real saturationPressureOfWaterVaporOverIce(Real T);

  Real equilibriumWaterVaporConcentrationAtSaturation(Real T);

  Real equilibriumConcentration(Real T);

  const ChemicalPotentialPropertyUserObject & _property_uo;

private:

  std::vector<libMesh::Real> _K;


};

#endif // CHEMICALPOTENTIALINTERFACE_H
