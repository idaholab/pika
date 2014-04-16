class ChemicalPotentialInterface
{
public:

  ChemicalPotentialInterface();

  virtual ~ChemicalPotentialInterface();

  Real saturationVaporPressure(Real T);

private:
  std::vector<Real> _K;
}
