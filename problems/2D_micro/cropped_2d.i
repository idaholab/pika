[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 2
  ny = 2
  #nz = 10
  xmax = 0.001 # I am just guessing here
  ymax = 0.001
  #zmax = 0.006
[]

[Adaptivity]
  max_h_level = 7
  initial_steps = 14
  initial_marker = marker
  [./Indicators]
    [./indicator]
      type = GradientJumpIndicator
      variable = u
    [../]
  [../]
  [./Markers]
    [./marker]
      type = ErrorFractionMarker
      indicator = indicator
      refine = 0.8
      coarsen = 0.05
    [../]
  [../]
[]

[Variables]
  [./u]
  [../]
[]

[Functions]
  [./tif]
    type = ImageFunction
    file_base = 0930/cropped/0930_rr_rec_tra_bin__Tra
    file_type = png
    file_range = '1313'
    threshold = 128
    upper_value = -1
    lower_value = 1
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = u
    boundary = left
    value = 0
  [../]
  [./right]
    type = DirichletBC
    variable = u
    boundary = right
    value = 1
  [../]
[]

[ICs]
  [./u_ic]
    type = FunctionIC
    function = tif
    variable = u
  [../]
[]

[Problem]
  type = FEProblem
  solve = false
[../]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  num_steps = 1
  dt = 0.1
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  output_initial = true
  exodus = true
  xdr = true
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = true
    linear_residuals = true
  [../]
[]
