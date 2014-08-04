[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 13
  ny = 26
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
  active = 'image_bottom_left image_top_left'
  [./image_bottom_left]
    type = ImageFunction
    origin = '0 0 0'
    upper_value = -1
    lower_value = 1
    file = input.png
    threshold = 100
    dimensions = '0.002 0.002 0'
  [../]
  [./image_bottom_right]
    type = ImageFunction
    origin = '0.002 0 0'
    upper_value = -1
    lower_value = 1
    flip_x = true
    file = input.png
    threshold = 100
    dimensions = '0.002 0.002 0'
  [../]
  [./image_top_right]
    type = ImageFunction
    origin = '0.002 0.002 0'
    upper_value = -1
    lower_value = 1
    flip_x = true
    flip_y = true
    file = input.png
    threshold = 100
    dimensions = '0.002 0.002 0'
  [../]
  [./image_top_left]
    type = ImageFunction
    origin = '0 0.002 0'
    upper_value = -1
    lower_value = 1
    flip_y = true
    file = input.png
    threshold = 100
    dimensions = '0.002 0.002 0'
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

[Problem]
  type = FEProblem
  solve = false
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
  max_h_level = 4
  initial_steps = 8
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
    file_base = phi_image_initial
    output_intermediate = false
    type = XDR
  [../]
[]

[ICs]
  active = 'phase_ic_top_left phase_ic_bottom_left'
  [./phase_ic_bottom_right]
    function = image_bottom_right
    variable = phi
    type = FunctionIC
    block = 3
  [../]
  [./phase_ic_top_left]
    function = image_top_left
    variable = phi
    type = FunctionIC
    block = 1
  [../]
  [./phase_ic_bottom_left]
    function = image_bottom_left
    variable = phi
    type = FunctionIC
    block = 0
  [../]
  [./phase_top_right]
    function = image_top_right
    variable = phi
    type = FunctionIC
    block = 2
  [../]
[]

[PikaMaterials]
  phi = phi
  temperature = 263.15
  interface_thickness = 1e-6
  block = '0 1'
[]

