[Mesh]
  type = FileMesh
  file = temp_diffusion.e
  dim = 2
  distribution = serial
[]

[Variables]
  active = 'T'
  [./T]
  [../]
  [./u]
  [../]
  [./phi]
  [../]
[]

[Functions]
  [./T_func]
    type = SolutionFunction
    solution = T_initial_uo
  [../]
[]

[Postprocessors]
[]

[UserObjects]
  [./T_initial_uo]
    type = SolutionUserObject
    mesh = temp_diffusion.e
    nodal_variables = T
    execute_on = initial
    system = nl0
  [../]
[]

[Problem]
  type = FEProblem
  solve = false
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  num_steps = 5
  dt = 10000
  solve_type = PJFNK
  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type'
  petsc_options_value = '500 hypre boomeramg'
[]

[Outputs]
  output_initial = true
  exodus = true
  file_base = temp_diffusion
  xdr = true
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = true
    linear_residuals = true
  [../]
[]

[ICs]
  active = 'pre_solved_T'
  [./phase_ic]
    x1 = .0025
    y1 = .0025
    radius = 0.0005
    outvalue = 1
    variable = phi
    invalue = -1
    type = SmoothCircleIC
    int_width = 5e-5
  [../]
  [./temperature_ic]
    variable = T
    type = FunctionIC
    function = -543.0*y+267.515
  [../]
  [./vapor_ic]
    variable = u
    type = ChemicalPotentialIC
    phase_variable = phi
    temperature = T
  [../]
  [./constant_temp_ic]
    variable = T
    type = ConstantIC
    value = 264.8
  [../]
  [./vapor_function_ic]
    function = -4.7e-6+0.00188*y
    variable = u
    type = FunctionIC
    block = 0
  [../]
  [./pre_solved_T]
    function = T_func
    variable = T
    type = FunctionIC
  [../]
[]

