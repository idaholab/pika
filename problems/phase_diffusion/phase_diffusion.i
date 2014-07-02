[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
  xmax = .005
  ymax = .005
  elem_type = QUAD8
[]

[Variables]
  active = 'phi'
  [./T]
  [../]
  [./u]
  [../]
  [./phi]
  [../]
[]

[Kernels]
  active = 'phi_time phi_square_gradient'
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
    type = PikaTimeDerivative
    variable = T
    property = latent_heat
    scale = -0.5
    differentiated_variable = phi
  [../]
  [./vapor_time]
    type = PikaScaledTimeDerivative
    variable = u
    coefficient = 1.0
    scale = 1.0
  [../]
  [./vapor_diffusion]
    type = PikaScaledMatDiffusion
    variable = u
    D_name = diffusion_coefficient
  [../]
  [./vapor_phi_time]
    type = PikaTimeDerivative
    variable = u
    coefficient = 0.5
    differentiated_variable = phi
    scale = 0.5
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
  active = 'phi_bc'
  [./T_hot]
    type = DirichletBC
    variable = T
    boundary = bottom
    value = 267.515 # -5
  [../]
  [./T_cold]
    type = DirichletBC
    variable = T
    boundary = top
    value = 264.8 # -20
  [../]
  [./insulated_sides]
    type = NeumannBC
    variable = T
    boundary = 'left right'
  [../]
  [./phi_bc]
    type = DirichletBC
    variable = phi
    boundary = '0 1 2 3'
    value = 1
  [../]
[]

[Postprocessors]
[]

[VectorPostprocessors]
  [./bubble_line]
    type = LineValueSampler
    variable = phi
    num_points = 1000
    start_point = '0 0.0025 0'
    end_point = '0.005 0.0025 0'
    sort_by = x
  [../]
[]

[UserObjects]
  [./property_uo]
    type = PropertyUserObject
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  num_steps = 100
  dt = 1e-5
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Adaptivity]
  max_h_level = 4
  initial_steps = 4
  initial_marker = phi_marker
  marker = phi_marker
  [./Indicators]
    active = 'phi_grad_indicator'
    [./phi_grad_indicator]
      type = GradientJumpIndicator
      variable = phi
    [../]
    [./T_jump_indicator]
      type = GradientJumpIndicator
      variable = T
      block = 0
    [../]
    [./u_indicator]
      type = GradientJumpIndicator
      variable = u
      block = 0
    [../]
  [../]
  [./Markers]
    active = 'phi_marker'
    [./phi_marker]
      type = ErrorFractionMarker
      coarsen = 0.2
      indicator = phi_grad_indicator
      refine = 0.7
    [../]
    [./T_marker]
      type = ErrorFractionMarker
      coarsen = 0.2
      indicator = T_jump_indicator
      refine = 0.7
    [../]
    [./u_marker]
      type = ErrorFractionMarker
      indicator = u_indicator
      coarsen = 0.2
      refine = 0.7
      block = 0
    [../]
    [./combo_mark]
      type = ComboMarker
      block = 0
      markers = 'T_marker phi_marker u_marker'
    [../]
  [../]
[]

[Outputs]
  output_initial = true
  exodus = true
  file_base = data/phase_diffusion_out
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = true
    linear_residuals = true
  [../]
  [./bubb_line_data]
    type = CSV
  [../]
[]

[ICs]
  active = 'phase_ic'
  [./phase_ic]
    x1 = .0025
    y1 = .0025
    radius = .001
    outvalue = 1
    variable = phi
    invalue = -1
    type = SmoothCircleIC
  [../]
  [./temperature_ic]
    variable = T
    type = ConstantIC
    value = 264.8
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
  temperature = 263.15
  interface_thickness = 1e-6
  reference_temperature = 263.15
  temporal_scaling = 1e-4
[]

