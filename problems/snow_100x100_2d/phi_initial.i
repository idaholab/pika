[Mesh]
  type = GeneratedMesh
  dim = 2
<<<<<<< HEAD
  nx = 200
  ny = 200
  xmax = .002
  ymax = .002
[]

[Variables]
=======
  nx = 12
  ny = 12
  xmax = .002 # m
  ymax = .002 # m
  elem_type = QUAD4
[]

[Variables]
  active = 'phi'
  [./T]
  [../]
>>>>>>> snow_small
  [./phi]
  [../]
[]

[AuxVariables]
  [./u]
  [../]
  [./phi_aux]
  [../]
[]

[Functions]
<<<<<<< HEAD
  [./snow_ct]
=======
  [./image]
>>>>>>> snow_small
    type = ImageFunction
    upper_value = -1
    lower_value = 1
    file = input.png
<<<<<<< HEAD
    threshold = 128
=======
    threshold = 100
>>>>>>> snow_small
  [../]
[]

[Kernels]
<<<<<<< HEAD
  [./phase_time]
    type = PikaTimeDerivative
    variable = phi
    property = relaxation_time
  [../]
  [./phase_diffusion]
    type = PikaDiffusion
    variable = phi
    property = interface_thickness_squared
  [../]
  [./phase_double_well]
=======
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
>>>>>>> snow_small
    type = DoubleWellPotential
    variable = phi
    mob_name = mobility
  [../]
<<<<<<< HEAD
[]

[AuxKernels]
  [./phi_aux]
=======
  [./phi_square_gradient]
    type = ACInterface
    variable = phi
    mob_name = mobility
    kappa_name = interface_thickness_squared
  [../]
[]

[AuxKernels]
  [./phi_initial_aux]
>>>>>>> snow_small
    type = PikaPhaseInitializeAux
    variable = phi_aux
    phase = phi
  [../]
[]

[BCs]
<<<<<<< HEAD
  [./phi_bc]
    type = DirichletBC
    variable = phi
    boundary = '0 1 2 3 '
    value = 1
=======
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
>>>>>>> snow_small
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
<<<<<<< HEAD
  num_steps = 20
  dt = 200
  solve_type = PJFNK
  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type'
  petsc_options_value = '500 hypre boomeramg'
  nl_rel_tol = 1e-07
  dtmax = 1000
  [./TimeStepper]
    type = IterationAdaptiveDT
    dt = 200
  [../]
=======
  num_steps = 10
  dt = 200
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  nl_rel_tol = 1e-07
>>>>>>> snow_small
[]

[Adaptivity]
  max_h_level = 4
  initial_steps = 10
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
      coarsen = .1
      indicator = phi_grad_indicator
      refine = .8
    [../]
<<<<<<< HEAD
  nl_abs_tol = 1e-13
  [./TimeStepper]
    type = IterationAdaptiveDT
    dt = 0.5
=======
>>>>>>> snow_small
  [../]
[]

[Outputs]
  output_initial = true
  exodus = true
<<<<<<< HEAD
  console = false
=======
>>>>>>> snow_small
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = true
    linear_residuals = true
  [../]
  [./xdr]
<<<<<<< HEAD
    file_base = phi_initial_1e5
    output_final = true
    type = XDR
    interval = 10
=======
    file_base = phi_initial
    output_intermediate = false
    output_final = true
    type = XDR
>>>>>>> snow_small
  [../]
[]

[ICs]
  [./phase_ic]
    variable = phi
    type = FunctionIC
<<<<<<< HEAD
    function = snow_ct
=======
    function = image
>>>>>>> snow_small
  [../]
[]

[PikaMaterials]
<<<<<<< HEAD
  temperature = 263.15
  interface_thickness = 1e-5
  phase = phi
  temporal_scaling = 1e-04
  condensation_coefficient = .001
=======
  phi = phi
  temperature = 263.15
  interface_thickness = 2e-5
>>>>>>> snow_small
[]

