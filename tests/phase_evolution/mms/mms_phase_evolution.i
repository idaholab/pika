[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 20
  ny = 20
  elem_type = QUAD4
[]

[Variables]
  [./phi]
    order = THIRD
    family = HERMITE
    block = 0
  [../]
[]

[AuxVariables]
  active = 'u T'
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
    value = t*sin(4.0*pi*x)*sin(4.0*pi*y)
  [../]
[]

[Kernels]
  active = 'phi_double_well mms'
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
  active = 'u_exact T_exact'
  [./error_aux]
    type = ErrorFunctionAux
    variable = abs_error
    function = u_func
    solution_variable = u
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
  petsc_options_iname = '-pc_type -pc_hypre'
  petsc_options_value = 'hypre boomeramg'
  end_time = 1
[]

[Outputs]
  exodus = true
  console = false
  [./console]
    type = Console
    linear_residuals = true
  [../]
[]

[ICs]
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
  reference_temperature = 263.15
  phi = phi
  temperature = T
[]

