
#include <vector>

#include "libmesh/libmesh_common.h"

class ChemicalPotentialInterface
{
public:

  ChemicalPotentialInterface();

  virtual ~ChemicalPotentialInterface();

  libMesh::Real saturationVaporPressure(libMesh::Real T);

private:
  std::vector<libMesh::Real> _K;
};
