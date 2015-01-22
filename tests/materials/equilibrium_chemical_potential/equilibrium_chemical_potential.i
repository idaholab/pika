[Mesh]
  type = GeneratedMesh
  dim = 2
[]

[Variables]
  [./T]
    initial_condition = 268.15
  [../]
[]

[PikaMaterials]
    conductivity_air = 0.1
    temperature = T
    phase = -1
    output_properties = 'equilibrium_chemical_potential'
    outputs = all
  [../]
[]

[Postprocessors]
  [./T]
    type = PointValue
    variable = T
    point = '0.5 0.5 0'
  [../]
  [./u_eq]
    type = PointValue
    variable = 'equilibrium_chemical_potential'
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
  [./console]
    type = Console
    perf_log = true
    output_nonlinear = true
    output_linear = true
  [../]
  [./data]
    type = CSV
  [../]
[]