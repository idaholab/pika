#ifndef CHEMICALPOTENTIALINTERFACE_H
#define CHEMICALPOTENTIALINTERFACE_H

#include <vector>

#include "UserObject.h"

#include "libmesh/libmesh_common.h"

// Forward declarations
class ChemicalPotentialInterface;

template<>
InputParameters validParams<ChemicalPotentialInterface>();


class ChemicalPotentialInterface
{
public:

  ChemicalPotentialInterface(UserObject * property_user_object);

  virtual ~ChemicalPotentialInterface(){};

protected:

  Real humidityRatio(Real T);

  Real saturationPressureOfWaterVaporOverIce(Real T);

  Real equilibribumWaterVaporConcentrationAtSaturation(Real T);

  Real equilibriumConcentration(Real T);

  UserObject * _property_ptr;

private:

  std::vector<libMesh::Real> _K;


};

#endif // CHEMICALPOTENTIALINTERFACE_H
