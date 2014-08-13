[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 100
  ny = 2
  xmax = .005 # mm
  ymax = .0005 # mm
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
    boundary = left
    value = 261
  [../]
  [./T_cold]
    type = DirichletBC
    variable = T
    boundary = right
    value = 260
  [../]
[]

[Postprocessors]
[]

[UserObjects]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  num_steps = 20
  dt = 200
  solve_type = PJFNK
  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type'
  petsc_options_value = '500 hypre boomeramg'
[]

[Adaptivity]
  max_h_level = 4
  initial_steps = 4
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
    active = 'phi_marker'
    [./phi_marker]
      type = ErrorFractionMarker
      coarsen = .01
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
    x1 = .002143
    variable = phi
    type = KaempferAnalyticPhaseIC
    x2 = .002857
    phi_new = -1
    phi_old = 1
    x3 = .003571
    x4 = .004286
  [../]
  [./temperature_ic]
    variable = T
    type = FunctionIC
    function = -100*x+261
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
  temperature = 263.15
  interface_thickness = 1e-5
  temporal_scaling = 1e-4
[]

