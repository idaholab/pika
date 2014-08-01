[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 5
  ny = 10
  xmax = .0025
  ymax = .005
  elem_type = QUAD4
[]

[Variables]
  [./phi]
  [../]
[]

[Kernels]
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

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  num_steps = 100
  dt = 100
  solve_type = PJFNK
  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type'
  petsc_options_value = '500 hypre boomeramg'
[]

[Adaptivity]
  max_h_level = 7
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
      coarsen = .05
      indicator = phi_grad_indicator
      refine = .7
    [../]
  [../]
[]

[Outputs]
  output_initial = true
  [./xdr]
    type = XDR
    file_base = init_phi_out
    interval = 10
  [../]
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = true
    linear_residuals = true
  [../]
  [./exodus]
    file_base = init_phi_out
    type = Exodus
  [../]
[]

[BCs]
[]

[ICs]
  [./phase_ic]
    x1 = .0025
    y1 = .0025
    radius = 0.0005
    outvalue = 1
    variable = phi
    invalue = -1
    type = SmoothCircleIC
    int_width = 1e-5
  [../]
[]

[PikaMaterials]
  phi = phi
  temperature = 263.15
  interface_thickness = 5e-6
[]

