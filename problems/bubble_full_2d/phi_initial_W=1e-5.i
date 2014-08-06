[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 5
  ny = 10
  xmax = .0025 # m
  ymax = .005 # m
  elem_type = QUAD4
[]

[Variables]
  active = 'phi'
  [./T]
  [../]
  [./phi]
  [../]
[]

[AuxVariables]
  [./u]
  [../]
[]

[Kernels]
  active = 'phi_double_well phi_square_gradient phi_time'
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
  [./phi_time]
    type = PikaTimeDerivative
    variable = phi
    property = tau
    scale = 1.0
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
  active = ''
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

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  num_steps = 10
  dt = 500
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Adaptivity]
  max_h_level = 7
  initial_steps = 10
  initial_marker = phi_marker
  marker = combo_marker
  [./Indicators]
    [./phi_grad_indicator]
      type = GradientJumpIndicator
      variable = phi
    [../]
  [../]
  [./Markers]
    [./phi_marker]
      type = ErrorFractionMarker
      coarsen = .1
      indicator = phi_grad_indicator
      refine = .8
    [../]
    [./phi_above]
      type = ValueThresholdMarker
      variable = phi
      third_state = DO_NOTHING
      refine = 1.000001
    [../]
    [./combo_marker]
      type = ComboMarker
      markers = 'phi_above phi_marker phi_below'
    [../]
    [./phi_below]
      type = ValueThresholdMarker
      variable = phi
      invert = true
      refine = -1.000001
    [../]
  [../]
[]

[Outputs]
  exodus = true
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = true
    linear_residuals = true
  [../]
  [./xdr]
    file_base = phi_initial
    output_intermediate = false
    interval = 10
    output_final = true
    type = XDR
  [../]
[]

[ICs]
  active = 'phase_ic'
  [./phase_ic]
    x1 = .0025
    y1 = .0025
    radius = .0005
    outvalue = 1
    variable = phi
    invalue = -1
    type = SmoothCircleIC
    int_width = 5e-6
  [../]
  [./temperature_ic]
    variable = T
    type = FunctionIC
    function = -543*y+267.515
  [../]
[]

[PikaMaterials]
  phase = phi
  temperature = 263.15
  interface_thickness = 1e-5
[]