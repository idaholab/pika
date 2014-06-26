[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 100
  ny = 2
  xmax = .005
  ymax = .0002
  elem_type = QUAD4
[]

[Variables]
  [./T]
  [../]
  [./u]
  [../]
  [./phi]
  [../]
[]

[Functions]
  [./T_func]
    type = ParsedFunction
    value = -200*x+261
  [../]
[]

[Kernels]
  [./heat_diffusion]
    type = MatDiffusion
    variable = T
    D_name = conductivity
  [../]
  [./heat_time]
    type = PikaTimeDerivative
    variable = T
    property = heat_capacity
    scale = 1.0
  [../]
  [./heat_phi_time]
    type = PikaScaledTimeDerivative
    variable = T
    property = latent_heat
    scale = -0.5
    differentiated_variable = phi
  [../]
  [./vapor_time]
    type = PikaTimeDerivative
    variable = u
    coefficient = 1.0
    scale = 1.0
  [../]
  [./vapor_diffusion]
    type = MatDiffusion
    variable = u
    D_name = diffusion_coefficient
  [../]
  [./vapor_phi_time]
    type = PikaScaledTimeDerivative
    variable = u
    coefficient = 0.5
    differentiated_variable = phi
  [../]
  [./phi_time]
    type = PikaTimeDerivative
    variable = phi
    property = tau
    scale = 1.0
  [../]
  [./phi_transition]
    type = PhaseTransition
    variable = phi
    mob_name = mobility
    chemical_potential = u
  [../]
  [./phi_double_well]
    type = DoubleWellPotential
    variable = phi
    mob_name = mobility
  [../]
  [./phi_square_gradient]
    type = ACInterface
    variable = phi
    mob_name = mobility
    kappa_name = interface_thickness_squared
  [../]
[]

[BCs]
  [./T_hot]
    type = DirichletBC
    variable = T
    boundary = left
    value = 261 # -5
  [../]
  [./T_cold]
    type = DirichletBC
    variable = T
    boundary = right
    value = 260 # -20
  [../]
  [./insulated_sides]
    type = NeumannBC
    variable = T
    boundary = 'top bottom'
  [../]
[]

[Postprocessors]
[]

[UserObjects]
  [./property_uo]
    type = PropertyUserObject
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  dt = 5
  solve_type = PJFNK
  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type'
  petsc_options_value = '500 hypre boomeramg'
  end_time = 2000000
[]

[Adaptivity]
  max_h_level = 3
  initial_steps = 3
  initial_marker = phi_marker
  marker = combo_mark
  [./Indicators]
    [./phi_grad_indicator]
      type = GradientJumpIndicator
      variable = phi
    [../]
    [./u_jump_indicator]
      type = GradientJumpIndicator
      variable = u
      block = 0
    [../]
  [../]
  [./Markers]
    active = 'phi_marker combo_mark u_marker'
    [./phi_marker]
      type = ErrorFractionMarker
      coarsen = 0.2
      indicator = phi_grad_indicator
      refine = .8
    [../]
    [./T_marker]
      type = ErrorFractionMarker
      coarsen = 0.2
      indicator = T_jump_indicator
      refine = 0.7
    [../]
    [./u_marker]
      type = ErrorFractionMarker
      indicator = u_jump_indicator
      coarsen = 0.2
      refine = 0.8
      block = 0
    [../]
    [./combo_mark]
      type = ComboMarker
      block = 0
      markers = 'u_marker phi_marker'
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
  [./phase_ic]
    x1 = 0.00214285714
    variable = phi
    type = KaempferAnalyticPhaseIC
    x2 = 0.00285714285
    phi_new = -1
    phi_old = 1
    x3 = 0.00357142857
    x4 = 0.00428571428
  [../]
  [./temperature_ic]
    variable = T
    type = FunctionIC
    function = T_func
  [../]
  [./vapor_ic]
    variable = u
    type = ChemicalPotentialIC
    block = 0
    phase_variable = phi
    temperature = T
  [../]
[]

[PikaMaterials]
  phi = phi
  temperature = T
  interface_thickness = 1e-6
  reference_temperature = 263.15
  temporal_scaling = 1e-4
[]

