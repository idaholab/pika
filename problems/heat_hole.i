[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
  uniform_refine = 2
[]

[Variables]
  [./u]
    initial_condition = 253.15 # -20
  [../]
[]

[AuxVariables]
  [./phi]
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
  [./top]
    type = DirichletBC
    variable = u
    boundary = top
    value = 268.15 # -5
  [../]
  [./bottom]
    type = DirichletBC
    variable = u
    boundary = bottom
    value = 253.15 # -20
  [../]
[]

[Materials]
  [./air]
    type = AirProperties
    block = 0
    property_user_object = property_uo
    temperature = u
  [../]
  [./ice]
    # Change the condutivity of ice to that of the moose simple_transient_diffusion test. Also, the phi variable in PhaseFieldProperties is set to a default value of 1.
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
    phi = phi
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

[ICs]
  [./phi_ic]
    x1 = 0.5
    y1 = 0.5
    radius = 0.25
    outvalue = 1
    variable = phi
    invalue = -1
    type = SmoothCircleIC
  [../]
[]

