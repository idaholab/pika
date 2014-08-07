[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 6
  ny = 12
  xmax = .002 # m
  ymax = .004 # m
  elem_type = QUAD4
[]

[MeshModifiers]
  active = 'bottom_left top_left'
  [./bottom_left]
    type = SubdomainBoundingBox
    top_right = '0.002 0.002 0'
    bottom_left = '0 0 0'
    block_id = 0
  [../]
  [./top_right]
    type = SubdomainBoundingBox
    top_right = '0.004 0.004 0'
    bottom_left = '0.002 0.002 0'
    block_id = 2
  [../]
  [./bottom_right]
    type = SubdomainBoundingBox
    top_right = '0.004 0.002 0'
    bottom_left = '0.002 0 0'
    block_id = 3
  [../]
  [./top_left]
    type = SubdomainBoundingBox
    top_right = '0.002 0.004 0'
    bottom_left = '0 0.002 0'
    block_id = 1
  [../]
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
  [./phi_aux]
  [../]
[]

[Functions]
  [./phi_func]
    type = SolutionFunction
    solution = phi_image
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

[UserObjects]
  [./phi_image]
    type = SolutionUserObject
    mesh = phi_image_initial_0000_mesh.xdr
    es = phi_image_initial_0000.xdr
    system_variables = phi
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  num_steps = 10
  dt = 200
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  nl_rel_tol = 1e-07
[]

[Adaptivity]
  max_h_level = 10
  initial_steps = 15
  initial_marker = phi_marker
  marker = combo
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
      refine = 1.0000001
    [../]
    [./phi_below]
      type = ValueThresholdMarker
      variable = phi
      invert = true
      refine = -1.0000001
    [../]
    [./combo]
      type = ComboMarker
      markers = 'phi_above phi_below phi_marker'
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
    function = phi_func
    variable = phi
    type = FunctionIC
    block = 1
  [../]
[]

[PikaMaterials]
  phi = phi
  temperature = 263.15
  interface_thickness = 1e-6
  block = '0 1'
[]

