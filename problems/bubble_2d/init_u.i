[Mesh]
  type = FileMesh
  file = init_T_out_0001_mesh.xdr
  dim = 2
[]

[Variables]
  [./u]
  [../]
[]

[AuxVariables]
  [./phi]
  [../]
  [./T]
  [../]
[]

[Kernels]
  [./vapor_time]
    type = PikaTimeDerivative
    variable = u
    coefficient = 1.0
    scale = 1.0
  [../]
  [./vapor_diffusion]
    type = PikaDiffusion
    variable = u
    property = diffusion_coefficient
  [../]
[]

[AuxKernels]
  [./T_aux]
    type = SolutionAux
    variable = T
    solution = init_T
    execute_on = initial
  [../]
  [./phi_aux]
    type = SolutionAux
    variable = phi
    solution = init_phi
    execute_on = initial
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  num_steps = 50
  dt = 1e-6
  solve_type = PJFNK
  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type'
  petsc_options_value = '50 hypre boomeramg'
[]

[Outputs]
  output_initial = true
  exodus = true
  interval = 10
  [./xdr]
    type = XDR
    file_base = init_u_out
  [../]
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = true
    linear_residuals = true
  [../]
[]

[BCs]
  [./vapor_bc]
    type = DirichletBC
    variable = u
    boundary = 'bottom left top'
    value = 0
  [../]
[]

[UserObjects]
  [./init_phi]
    type = SolutionUserObject
    system = nl0
    mesh = init_phi_out_0010_mesh.xdr
    nodal_variables = phi
    es = init_phi_out_0010.xdr
  [../]
  [./init_T]
    type = SolutionUserObject
    system = nl0
    mesh = init_T_out_0001_mesh.xdr
    nodal_variables = T
    es = init_T_out_0001.xdr
  [../]
[]

[Adaptivity]
  max_h_level = 7
  initial_steps = 10
  marker = u_marker
  initial_marker = u_marker
  [./Indicators]
    [./u_indicator]
      type = GradientJumpIndicator
      variable = u
    [../]
  [../]
  [./Markers]
    [./u_marker]
      type = ErrorFractionMarker
      indicator = u_indicator
      refine = 0.95
    [../]
  [../]
[]

[ICs]
  [./vapor_ic]
    variable = u
    type = SmoothCircleIC
    x1 = 0.0025
    y1 = 0.0025
    radius = 0.0005
    outvalue = 0
    invalue = 1e-9
  [../]
[]

[PikaMaterials]
  phi = phi
  temperature = 263.15
  interface_thickness = 5e-6
[]

