#ifndef CHEMICALPOTENTIALINTERFACE_H
#define CHEMICALPOTENTIALINTERFACE_H

#include <vector>

#include "libmesh/libmesh_common.h"

class ChemicalPotentialInterface
{
public:

  ChemicalPotentialInterface();

  virtual ~ChemicalPotentialInterface(){};

  libMesh::Real saturationVaporPressure(libMesh::Real T);

private:
  std::vector<libMesh::Real> _K;
};

#endif // CHEMICALPOTENTIALINTERFACE_H
