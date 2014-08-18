[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
[]

[Variables]
  [./u]
  [../]
[]

[AuxVariables]
  [./master_aux]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[Functions]
  [./func]
    type = ParsedFunction
    value = x*y*t
  [../]
[]

[Kernels]
  [./diff]
    type = PikaDiffusion
    variable = u
    coefficient = 0.1
  [../]
  [./time]
    type = TimeDerivative
    variable = u
  [../]
[]

[AuxKernels]
  [./func_aux]
    type = FunctionAux
    variable = master_aux
    function = func
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

[PikaMaterials]
  phase = 1
  temperature = 1
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  num_steps = 20
  dt = 0.1
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
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
[]

[MultiApps]
  [./quad]
    type = TransientMultiApp
    app_type = PikaApp
    positions = '0.1 0.1 0 0.9 0.1 0 0.1 0.9 0 0.9 0.9 0'
    input_files = sub.i
  [../]
[]

[Transfers]
  [./master_to_sub]
    type = MultiAppVariableValueSamplePostprocessorTransfer
    direction = to_multiapp
    multi_app = quad
    source_variable = master_aux
    postprocessor = pp
  [../]
[]

