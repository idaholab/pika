[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 25
  ny = 25
  xmax = .005
  ymax = .005
  uniform_refine = 2
  elem_type = QUAD4
[]

[Variables]
  active = 'phi u'
  [./T]
  [../]
  [./u]
  [../]
  [./phi]
  [../]
[]

[AuxVariables]
  active = ''
  [./phi]
  [../]
  [./u]
  [../]
  [./T]
  [../]
[]

[Kernels]
  active = 'vapor_time phi_transition phi_double_well vapor_phi_time vapor_diffusion phi_time phi_square_gradient'
  [./heat_diffusion]
    type = PikaDiffusion
    variable = T
    use_temporal_scaling = true
    property = conductivity
  [../]
  [./heat_time]
    type = PikaTimeDerivative
    variable = T
    property = heat_capacity
    scale = 1.0
  [../]
  [./heat_phi_time]
    type = PikaCoupledTimeDerivative
    variable = T
    property = latent_heat
    scale = -0.5
    use_temporal_scaling = true
    coupled_variable = phi
  [../]
  [./vapor_time]
    type = PikaTimeDerivative
    variable = u
    coefficient = 1.0
    scale = 1.0
  [../]
  [./vapor_diffusion]
    type = PikaDiffusion
    variable = u
    coefficient = 1e-7
    use_temporal_scaling = true
  [../]
  [./vapor_phi_time]
    type = PikaCoupledTimeDerivative
    variable = u
    coefficient = 0.5
    coupled_variable = phi
    use_temporal_scaling = true
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
  active = 'u_bottom u_top'
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
    boundary = '0 1 2 3 '
    value = 1.0
  [../]
  [./u_bottom]
    type = DirichletBC
    variable = u
    boundary = bottom
    value = -4.7e-6
  [../]
  [./u_top]
    type = DirichletBC
    variable = u
    boundary = top
    value = 4.7e-6
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
  dt = 200
  solve_type = PJFNK
  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type'
  petsc_options_value = '500 hypre boomeramg'
  end_time = 100000
  [./TimeStepper]
    type = SolutionTimeAdaptiveDT
    dt = 1
  [../]
[]

[Adaptivity]
  max_h_level = 5
  initial_steps = 5
  initial_marker = phi_marker
  marker = phi_marker
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
    active = 'phi_marker u_marker'
    [./phi_marker]
      type = ErrorFractionMarker
      coarsen = .12
      indicator = phi_grad_indicator
      refine = .6
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
      coarsen = .02
      refine = .5
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
  active = 'phase_ic vapor_ic'
  [./phase_ic]
    x1 = .0025
    y1 = .0025
    radius = 0.0005
    outvalue = 1
    variable = phi
    invalue = -1
    type = SmoothCircleIC
    int_width = 5e-5
  [../]
  [./temperature_ic]
    variable = T
    type = FunctionIC
    function = -543.0*y+267.515
  [../]
  [./vapor_ic]
    variable = u
    type = FunctionIC
    block = 0
    function = -4.7e-6+0.00188*y
  [../]
  [./constant_temp_ic]
    variable = T
    type = ConstantIC
    value = 264.8
  [../]
[]

[PikaMaterials]
  phi = phi
  temperature = 263.15
  interface_thickness = 1e-5
  temporal_scaling = 1e-4
[]

