[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 3
  ny = 9
  xmin = .001
  xmax = .0025 # mm
  ymax = .005 # mm
  elem_type = QUAD4
[]

[Variables]
  active = 'phi T'
  [./T]
  [../]
  [./u]
  [../]
  [./phi]
    initial_from_file_var = diffused_phi
    initial_from_file_timestep = 30
  [../]
[]

[AuxVariables]
  active = 'u'
  [./phi]
  [../]
  [./u]
  [../]
  [./T]
  [../]
[]

[Kernels]
  active = 'heat_diffusion phi_double_well heat_phi_time heat_time phi_time phi_square_gradient'
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
  [../]
  [./vapor_phi_time]
    type = PikaCoupledTimeDerivative
    variable = u
    coefficient = 0.5
    coupled_variable = phi
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
    boundary = bottom
    value = 267.515
  [../]
  [./T_cold]
    type = DirichletBC
    variable = T
    boundary = top
    value = 264.8
  [../]
[]

[Postprocessors]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  num_steps = 10
  dt = 200
  solve_type = PJFNK
  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type'
  petsc_options_value = '500 hypre boomeramg'
[]

[Adaptivity]
  max_h_level = 7
  initial_steps = 7
  initial_marker = range_marker
  marker = range_marker
  [./Indicators]
    active = 'phi_grad_indicator'
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
    active = 'range_marker'
    [./phi_marker]
      type = ErrorFractionMarker
      coarsen = .001
      indicator = phi_grad_indicator
      refine = .9
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
      markers = 'phi_marker range_marker'
    [../]
    [./range_marker]
      type = ErrorToleranceMarker
      coarsen = 1e-5
      indicator = phi_grad_indicator
      refine = 1e-6
    [../]
  [../]
[]

[Outputs]
  output_initial = true
  exodus = true
  file_base = phi_temp_diffusion
  xdr = true
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = true
    linear_residuals = true
  [../]
[]

[ICs]
  active = 'phase_ic temperature_ic'
  [./phase_ic]
    x1 = .0025
    y1 = .0025
    radius = .0005
    outvalue = 1
    variable = phi
    invalue = -1
    type = SmoothCircleIC
    int_width = 1e-6
  [../]
  [./temperature_ic]
    variable = T
    type = FunctionIC
    function = -543*y+267.515
  [../]
  [./vapor_ic]
    variable = u
    type = FunctionIC
    block = 0
    function = -4.7e-6
  [../]
  [./constant_temp_ic]
    variable = T
    type = ConstantIC
    value = 264.8
  [../]
[]

[PikaMaterials]
  phi = phi
  temperature = T
  interface_thickness = 1e-5
  temporal_scaling = 1e-4
[]

