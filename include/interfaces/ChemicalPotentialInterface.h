#include "ChemicalPotentialInterface.h"

ChemicalPotentialInterface::ChemicalPotentialInterface()
{
  _K.push_back(-0.5865e4);
  _K.push_back(0.2224e2);
  _K.push_back(0.1375e-1);
  _K.push_back(-0.3403e-4);
  _K.push_back(0.2697e-7);
  _K.push_back(0.6918);
}

Real
ChemicalPotentialInterface::saturationVaporPressure(Real T)
{
  return std::exp(_K[0]*std::pow(T, -1) + _K[1] + _K[2]*std::pow(T, 1) + _K[3]*std::pow(T, 2) + _K[4]*std::pow(T, 3) + _K[5]*std::log(T));

}
