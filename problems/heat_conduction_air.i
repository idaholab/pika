[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
  xmax = 0.005
  ymax = 0.005
  uniform_refine = 2
[]

[Variables]
  [./T]
  [../]
[]

[Kernels]
  [./heat_t]
    type = MaterialTimeDerivative
    variable = T
    property = heat_capacity
  [../]
  [./heat_diffusion]
    type = MatDiffusion
    variable = T
    D_name = conductivity
  [../]
[]

[BCs]
  [./T_hot]
    type = DirichletBC
    variable = T
    boundary = bottom
    value = 268.15 # -5C
  [../]
  [./T_cold]
    type = DirichletBC
    variable = T
    boundary = top
    value = 253.15 # -20C
  [../]
[]

[Materials]
  [./air]
    type = AirProperties
    block = 0
    property_user_object = potential_uo
    temperature = T
  [../]
  [./ice]
    type = IceProperties
    block = 0
    property_user_object = potential_uo
    temperature = T
  [../]
  [./constants]
    type = ConstantProperties
    block = 0
  [../]
  [./phase]
    type = PhaseFieldProperties
    block = 0
    phi = -1
    property_user_object = potential_uo
    temperature = T
  [../]
[]

[UserObjects]
  [./potential_uo]
    type = ChemicalPotentialPropertyUserObject
    execute_on = initial
  [../]
[]

[Executioner]
  type = Transient
  num_steps = 1000
  dt = 0.00001
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  output_initial = true
  exodus = true
  [./console]
    type = Console
    output_initial = true
    linear_residuals = true
  [../]
[]

[ICs]
  [./temperature_ic]
    variable = T
    type = ConstantIC
    value = 253.15 # -20C
  [../]
[]
