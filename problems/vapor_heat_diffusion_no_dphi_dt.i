[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
  xmax = .01
  ymax = .01
[]

[Variables]
  [./u]
  [../]
  [./T]
  [../]
[]

[AuxVariables]
  [./phi]
  [../]
[]

[Functions]
  [./phi_func]
    type = ParsedFunction
    value = (1/15000.0)*t*x^2
  [../]
[]

[Kernels]
  [./vapor_diffusion]
    type = PikaScaledMatDiffusion
    variable = u
    D_name = diffusion_coefficient
  [../]
  [./vapor_time]
    type = PikaScaledTimeDerivative
    variable = u
    coefficient = 1.0
  [../]
  [./heat_time]
    type = PikaTimeDerivative
    variable = T
    property = heat_capacity
  [../]
  [./heat_diffusion]
    type = MatDiffusion
    variable = T
    D_name = conductivity
  [../]
[]

[AuxKernels]
  [./phi_aux]
    type = FunctionAux
    variable = phi
    function = phi_func
  [../]
[]

[BCs]
  [./vapor_right]
    type = DirichletBC
    variable = u
    boundary = left
    value = 0.5
  [../]
  [./vapor_left]
    type = DirichletBC
    variable = u
    boundary = right
    value = 0
  [../]
  [./T_hot]
    type = DirichletBC
    variable = T
    boundary = left
    value = 265
  [../]
  [./T_cold]
    type = DirichletBC
    variable = T
    boundary = right
    value = 260
  [../]
[]

[PikaMaterials]
  conductivity_air = 0.1
  temperature = u
  phi = phi
  reference_temperature = 263.15
  temporal_scaling = 1e-4
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  num_steps = 25
  dt = .1
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

[ICs]
  [./T_ic]
    variable = T
    type = ConstantIC
    value = 263.15
  [../]
[]

