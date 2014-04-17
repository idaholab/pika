[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
  xmax = 0.005
  ymax = 0.005
[]

[Variables]
  [./T]
  [../]
  [./phi]
  [../]
  [./u]
  [../]
[]

[Kernels]
  [./phase_t]
    type = MaterialTimeDerivative
    variable = phi
    property = tau
  [../]
  [./phace_gradient]
    type = ACInterface
    variable = phi
    mob_name = mobility
    kappa_name = interface_thickness_squared
  [../]
  [./phase_transition]
    type = PhaseTransition
    variable = phi
    mob_name = mobility
    u = u
    temperature = T
  [../]
  [./phase_potential]
    type = PhaseFieldPotential
    variable = phi
    mob_name = mobility
  [../]
  [./heat_t]
    type = MaterialTimeDerivative
    variable = T
    property = heat_capacity
  [../]
  [./heat_diffusion]
    type = MatDiffusion
    variable = T
    D_name = conductivity
  [../]
  [./heat_phi_t]
    type = MaterialTimeDerivative
    variable = phi
    property = latent_heat
    scale = 0.5
  [../]
  [./potential_t]
    type = TimeDerivative
    variable = u
  [../]
  [./potential_diffusion]
    type = MatDiffusion
    variable = u
    D_name = diffusion_coefficient
  [../]
  [./potential_phi_t]
    type = CoefficientTimeDerivative
    variable = phi
    coefficient = -0.5
  [../]
[]

[BCs]
  [./T_hot]
    type = DirichletBC
    variable = T
    boundary = bottom
    value = 268.15 # -5C
  [../]
  [./T_cold]
    type = DirichletBC
    variable = T
    boundary = top
    value = 253.15
  [../]
[]

[Materials]
  [./air]
    type = AirProperties
    block = 0
    temperature = T
  [../]
  [./ice]
    type = IceProperties
    block = 0
    temperature = T
  [../]
  [./constants]
    type = ConstantProperties
    block = 0
  [../]
  [./phase]
    type = PhaseFieldProperties
    block = 0
    phi = phi
    temperature = T
  [../]
[]

[Executioner]
  type = Transient
  num_steps = 1000
  dt = 0.01
[]

[Outputs]
  exodus = true
  [./console]
    type = Console
    linear_residuals = true
  [../]
[]

[ICs]
  [./phase_ic]
    x1 = 0.0025
    y1 = 0.0025
    radius = 0.0005
    outvalue = 1
    variable = phi
    3D_spheres = false
    invalue = -1
    type = SmoothCircleIC
  [../]
  [./temperature_ic]
    variable = T
    type = ConstantIC
    value = -10
  [../]
  [./chemical_potential_ic]
    variable = u
    type = ChemicalPotentialIC
    temperature = T
  [../]
[]

