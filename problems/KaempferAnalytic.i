[Mesh]
  type = GeneratedMesh
  dim = 1
  xmin = 0
  xmax = 0.005 # 5 mm
  nx = 100
[]

[Variables]
  [./T]
    initial_condition = 253.15 # -20
  [../]
[]

[AuxVariables]
  [./phi]
  [../]
[]

[Kernels]
  [./heat_diffusion]
    type = MatDiffusion
    variable = T
    D_name = conductivity
  [../]
  [./heat_time]
    type = TimeDerivative
    variable = T
  [../]
[]

[BCs]
  [./T_hot]
    type = DirichletBC
    variable = T
    boundary = left
    value = 261
  [../]
  [./T_cold]
    type = DirichletBC
    variable = T
    boundary = right
    value = 260
  [../]
[]

[Materials]
  [./air]
    type = AirProperties
    block = 0
    property_user_object = property_uo
    temperature = T
  [../]
  [./ice]
    # Change the condutivity of ice to that of the moose simple_transient_diffusion test. Also, the phi variable in PhaseFieldProperties is set to a default value of 1.
    type = IceProperties
    block = 0
    property_user_object = property_uo
    temperature = T
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
    temperature = T
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

[Adaptivity]
  max_h_level = 4
  initial_steps = 6
  initial_marker = error_fraction
  [./Indicators]
    [./phi_grad_indicator]
      type = GradientJumpIndicator
      variable = phi
    [../]
  [../]
  [./Markers]
    [./error_fraction]
      type = ErrorFractionMarker
      coarsen = 0.2
      indicator = phi_grad_indicator
      refine = 0.7
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
[]

[ICs]
  [./pores]
    type = KaempferAnalyticPhaseIC
    variable = phi
    phi_new=-1
    phi_old=1
    x1 = 0.00214 # 3*L/7
    x2 = 0.00286 # 4*L/7
    x3 = 0.00357 # 5*L/7
    x4 = 0.00429 # 6*L/7
  [../]
[]
