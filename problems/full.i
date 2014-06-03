[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
[]

[Variables]
  [./T]
  [../]
  [./u]
  [../]
  [./phi]
  [../]
[]

[Kernels]
  [./heat_diffusion]
    type = MatDiffusion
    variable = T
    D_name = conductivity
  [../]
  [./heat_time]
    type = TimeDerivative
    variable = T
  [../]
  [./vapor_time]
    type = TimeDerivative
    variable = u
  [../]
  [./vapor_diffusion]
    type = MatDiffusion
    variable = u
    D_name = diffusion_coefficient
  [../]
  [./vapor_phi_time]
    type = CoefficientTimeDerivative
    variable = phi
    coefficient = 0.5
  [../]
  [./phi_time]
    type = MaterialTimeDerivative
    variable = phi
    property = latent_heat
  [../]
  [./phi_interface]
    type = ACInterface
    variable = phi
    mob_name = mobility
    kappa_name = conductivity
  [../]
  [./phi_potential]
    type = PhaseFieldPotential
    variable = phi
    mob_name = mobility
  [../]
  [./phi_transition]
    type = PhaseTransition
    variable = phi
    mob_name = mobility
    chemical_potential = u
  [../]
[]

[BCs]
  [./T_hot]
    type = DirichletBC
    variable = T
    boundary = top
    value = 268.15 # -5
  [../]
  [./T_cold]
    type = DirichletBC
    variable = T
    boundary = bottom
    value = 253.15 # -20
  [../]
[]

[Materials]
  [./air]
    type = AirProperties
    block = 0
    property_user_object = property_uo
    temperature = T
  [../]
  [./ice]
    # Change the condutivity of ice to that of the moose simple_transient_diffusion test. Also, the phi variable in PhaseFieldProperties is set to a default value of 1.
    type = IceProperties
    block = 0
    property_user_object = property_uo
    temperature = T
  [../]
  [./constants]
    type = ConstantProperties
    block = 0
  [../]
  [./phase_field]
    # Use the default phi = 1 so that the material behaves as solid ice.
    type = PhaseFieldProperties
    block = 0
    phi = phi
    property_user_object = property_uo
    temperature = T
  [../]
[]

[UserObjects]
  [./property_uo]
    type = ChemicalPotentialPropertyUserObject
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  num_steps = 20
  dt = 0.1
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Adaptivity]
  max_h_level = 4
  initial_steps = 6
  initial_marker = error_fraction
  [./Indicators]
    [./phi_grad_indicator]
      type = GradientJumpIndicator
      variable = phi
    [../]
  [../]
  [./Markers]
    [./error_fraction]
      type = ErrorFractionMarker
      coarsen = 0.2
      indicator = phi_grad_indicator
      refine = 0.7
    [../]
  [../]
[]

[Outputs]
  output_initial = true
  exodus = true
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = true
    linear_residuals = true
  [../]
[]

[ICs]
  [./phi_ic]
    x1 = 0.5
    y1 = 0.5
    radius = 0.25
    outvalue = 1
    variable = phi
    invalue = -1
    type = SmoothCircleIC
  [../]
  [./vapor_ic]
    variable = u
    property_user_object = property_uo
    type = ChemicalPotentialIC
    temperature = T
  [../]
  [./heat_ic]
    variable = T
    type = ConstantIC
    value = 253.15
  [../]
[]

