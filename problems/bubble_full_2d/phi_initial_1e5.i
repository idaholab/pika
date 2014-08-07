[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 5
  ny = 10
  xmax = 0.0025
  ymax = 0.005
[]

[Variables]
  [./phi]
  [../]
[]

[AuxVariables]
  [./u]
  [../]
  [./phi_aux]
  [../]
[]

[Kernels]
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
    type = DoubleWellPotential
    variable = phi
    mob_name = mobility
  [../]
[]

[AuxKernels]
  [./phi_aux]
    type = PikaPhaseInitializeAux
    variable = phi_aux
    phase = phi
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  num_steps = 20
  dt = 10
  solve_type = PJFNK
  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type'
  petsc_options_value = '500 hypre boomeramg'
  nl_rel_tol = 1e-07
  nl_abs_tol = 1e-13
  [./TimeStepper]
    type = IterationAdaptiveDT
    dt = 0.5
  [../]
[]

[Adaptivity]
  max_h_level = 8
  initial_steps = 12
  marker = phi_marker
  initial_marker = phi_marker
  [./Indicators]
    [./phi_grad_indicator]
      type = GradientJumpIndicator
      variable = phi
    [../]
  [../]
  [./Markers]
    [./phi_marker]
      type = ErrorToleranceMarker
      coarsen = 1e-6
      indicator = phi_grad_indicator
      refine = 1e-4
    [../]
  [../]
[]

[Outputs]
  output_initial = true
  exodus = true
  console = false
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = true
    linear_residuals = true
  [../]
  [./xdr]
    file_base = phi_initial_1e5
    output_final = true
    type = XDR
    interval = 10
  [../]
[]

[ICs]
  [./phase_ic]
    int_width = 1e-6
    x1 = 0.0025
    y1 = 0.0025
    radius = 0.0005
    outvalue = 1
    variable = phi
    invalue = -1
    type = SmoothCircleIC
  [../]
[]

[PikaMaterials]
  temperature = 258.2
  interface_thickness = 1e-5
  phase = phi
  interface_kinetic_coefficient = 5.5e5
  capillary_length = 1.3e-9
  temporal_scaling = 1e-04
[]

