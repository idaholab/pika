[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
  uniform_refine = 4
[]

[Variables]
  [./T]
    initial_condition = 263.15
  [../]
[]

[Kernels]
  [./diff]
    type = MatDiffusion
    variable = T
    D_name = conductivity
  [../]
  [./time]
    type = TimeDerivative
    variable = T
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = T
    boundary = left
    value = 263.15
  [../]
  [./right]
    type = DirichletBC
    variable = T
    boundary = right
    value = 273.15
  [../]
[]

[Materials]
  [./air]
    type = AirProperties
    block = 0
    conductivity_air = 0.1
    property_user_object = property_uo
    temperature = T
  [../]
  [./ice]
    # Change the condutivity of aior to that of the moose simple_transient_diffusion test. Also, the phi variable in PhaseFieldProperties is set to a default value of -1.
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
    phi = -1
    property_user_object = property_uo
    temperature = T
    output_properties = 'specific_humidity_ratio saturation_pressure_of_water_vapor_over_ice'
    outputs = all
  [../]
[]

[Postprocessors]
  [./T]
    type = PointValue
    variable = T
    point = '0.5 0.5 0'
  [../]
  [./x_s]
    type = PointValue
    variable = specific_humidity_ratio
    point = '0.5 0.5 0'
  [../]
  [./P_vs]
    type = PointValue
    variable = saturation_pressure_of_water_vapor_over_ice
    point = '0.5 0.5 0'
  [../]
[]

[UserObjects]
  [./property_uo]
    type = ChemicalPotentialPropertyUserObject
    atmospheric_pressure = 1.01325e5
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  num_steps = 3
  dt = 0.1
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  output_initial = false
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = true
    linear_residuals = true
  [../]
  [./out]
    type = CSV
    output_initial = false
  [../]
[]
