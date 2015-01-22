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
  interface_thickness = 1e-6
  phase = -1
  temperature = T
  output_properties = 'capillary_length capillary_length_prime phase_field_coupling_constant'
  outputs = all
  debug = true
[]

[Postprocessors]
  [./T]
    type = PointValue
    variable = T
    point = '0.5 0.5 0'

  [../]
  [./lambda]
    type = PointValue
    variable = phase_field_coupling_constant
    point = '0.5 0.5 0'
  [../]
  [./d_0]
    type = PointValue
    variable = capillary_length
    point = '0.5 0.5 0'
  [../]
  [./d_0_prime]
    type = PointValue
    variable = capillary_length_prime
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
