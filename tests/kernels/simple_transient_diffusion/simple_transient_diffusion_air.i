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

[Kernels]
  [./diff]
    type = MatDiffusion
    variable = u
    D_name = conductivity
  [../]
  [./time]
    type = TimeDerivative
    variable = u
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

[Materials]
  [./air]
    type = AirProperties
    block = 0
    conductivity_air = 0.1
    property_user_object = property_uo
    temperature = u
  [../]
  [./ice]
    # Change the condutivity of aior to that of the moose simple_transient_diffusion test. Also, the phi variable in PhaseFieldProperties is set to a default value of -1.
    type = IceProperties
    block = 0
    property_user_object = property_uo
    temperature = u
  [../]
  [./constants]
    type = ConstantProperties
    block = 0
  [../]
  [./phase_field]
    # Use the default phi = 1 so that the material behaves as solid ice.
    type = PhaseFieldProperties
    block = 0
    phi = -1
    property_user_object = property_uo
    temperature = u
  [../]
[]

[UserObjects]
  [./property_uo]
    type = ChemicalPotentialPropertyUserObject
  [../]
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
