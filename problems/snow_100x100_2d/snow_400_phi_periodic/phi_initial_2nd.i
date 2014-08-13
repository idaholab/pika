[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 12
  ny = 12
  xmax = .002 # m
  ymax = .002 # m
  elem_type = QUAD8
[]

[Variables]
  active = 'phi'
  [./T]
    order = SECOND
  [../]
  [./phi]
    order = SECOND
  [../]
[]

[AuxVariables]
  [./u]
  [../]
  [./phi_aux]
  [../]
[]

[Functions]
  [./image]
    type = ImageFunction
    upper_value = -1
    lower_value = 1
    file = input.png
    threshold = 100
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
    property = relaxation_time
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

[AuxKernels]
  [./phi_initial_aux]
    type = PikaPhaseInitializeAux
    variable = phi_aux
    phase = phi
  [../]
[]

[BCs]
  [./Periodic]
    [./phi_bc]
      variable = phi
      auto_direction = y
    [../]
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  num_steps = 20
  dt = 200
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  nl_rel_tol = 1e-07
  dtmax = 2000
  [./TimeStepper]
    type = IterationAdaptiveDT
    dt = 2
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
  [../]
  [./Markers]
    [./phi_marker]
      type = ErrorFractionMarker
      coarsen = .05
      indicator = phi_grad_indicator
      refine = .85
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
  [./xdr]
    file_base = phi_initial
    output_intermediate = false
    output_final = true
    type = XDR
  [../]
[]

[ICs]
  [./phase_ic]
    variable = phi
    type = FunctionIC
    function = image
  [../]
[]

[PikaMaterials]
  temperature = 263.15
  interface_thickness = 5e-6
  phase = phi
  condensation_coefficient = 0.05
  temporal_scaling = 1e-04
[]
