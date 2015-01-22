[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 20
  ny = 20
  elem_type = QUAD8
[]

[Variables]
  [./phi]
    order = SECOND
    block = 0
  [../]
[]

[AuxVariables]
  [./abs_error]
  [../]
  [./u]
    block = 0
  [../]
  [./T]
    block = 0
  [../]
[]

[Functions]
  [./u_func]
    type = ParsedFunction
    value = 0.5*sin(4.0*x*y)
  [../]
  [./T_func]
    type = ParsedFunction
    value = -10.0*x*y+273.0
  [../]
  [./phi_func]
    type = ParsedFunction
    value = 't*((x-0.50)*(x-0.5)+(y-0.5)*(y-0.5) -.125)'
  [../]
[]

[Kernels]
  [./phi_time]
    type = PikaTimeDerivative
    variable = phi
    property = tau
    block = 0
  [../]
  [./phase_transition]
    type = PhaseTransition
    variable = phi
    mob_name = mobility
    chemical_potential = u
  [../]
  [./mms]
    type = PhaseEvolutionSourceMMS
    variable = phi
    block = 0
    chemical_potential = u
    use_potential_transition = true
    temperature = T
  [../]
  [./phi_time]
    type = PikaTimeDerivative
    variable = phi
    property = tau
    block = 0
  [../]
  [./phi_square_gradient]
    type = ACInterface
    variable = phi
    mob_name = mobility
    kappa_name = interface_thickness_squared
    block = 0
  [../]
  [./phi_double_well]
    type = DoubleWellPotential
    variable = phi
    mob_name = mobility
    block = 0
  [../]
[]

[AuxKernels]
  [./error_aux]
    type = ErrorFunctionAux
    variable = abs_error
    function = phi_func
    solution_variable = phi
  [../]
  [./u_exact]
    type = FunctionAux
    variable = u
    function = u_func
    block = 0
  [../]
  [./T_exact]
    type = FunctionAux
    variable = T
    function = T_func
    block = 0
  [../]
[]

[BCs]
  [./all]
    type = FunctionDirichletBC
    variable = phi
    boundary = 'bottom left top right'
    function = phi_func
  [../]
[]

[Executioner]
  type = Transient
  num_steps = 10
  dt = .1
  l_max_its = 100
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre'
  petsc_options_value = 'hypre boomeramg'
  end_time = .5
[]

[Outputs]
  exodus = true
  console = false
  file_base = mms_phase_evolution_out
  [./console]
    type = Console
    output_linear = true
  [../]
[]

[ICs]
  active = 'phi_ic'
  [./phi_ic]
    function = phi_func
    variable = phi
    type = FunctionIC
    block = 0
  [../]
  [./T_ic]
    function = T_func
    variable = T
    type = FunctionIC
  [../]
  [./u_ic]
    function = u_func
    variable = u
    type = FunctionIC
  [../]
[]

[PikaMaterials]
  phi = phi
  temperature = T
[]

