[Mesh]
  type = GeneratedMesh
  dim = 2
[]

[Variables]
  [./T]
    initial_condition = 263.15
  [../]
[]

[PikaMaterials]
  conductivity_air = 0.1
  atmospheric_pressure = 1.01325e5
  phase = -1
  temperature = T
  output_properties = 'specific_humidity_ratio saturation_pressure_of_water_vapor_over_ice'
  outputs = all
  debug = true
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

[Problem]
  type = FEProblem
  solve = false
  kernel_coverage_check = false
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  num_steps = 1
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  exodus = true
  print_linear_residuals = true
  print_perf_log = true
  [./data]
    type = CSV
  [../]
[]
