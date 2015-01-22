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
  phase = -1
  interface_kinetic_coefficient = 5.5e5
  interface_thickness = 1e-6
  temperature = T
  output_properties = 'relaxation_time interface_kinetic_coefficient interface_kinetic_coefficient_prime'
  outputs = all
  debug = true
[]

[Postprocessors]
  [./T]
    type = PointValue
    variable = T
    point = '0.5 0.5 0'
  [../]
  [./beta_0]
    type = PointValue
    variable = interface_kinetic_coefficient
    point = '0.5 0.5 0'
  [../]
  [./beta_0_prime]
    type = PointValue
    variable = interface_kinetic_coefficient_prime
    point = '0.5 0.5 0'
  [../]
  [./tau]
    type = PointValue
    variable = relaxation_time
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
