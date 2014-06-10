[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
  elem_type = QUAD8
[]

[Variables]
  [./phi]
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
  [./phi_func]
    type = ParsedFunction
    value = t*sin(4*pi*x)*sin(4*pi*y)
  [../]
  [./u_func]
    type = ParsedFunction
    value = sin(4*x*y)
  [../]
  [./T_func]
    type = ParsedFunction
    value = 100*x*y
  [../]
[]

[Kernels]
  [./mms]
    type = PhaseEvolutionSourceMMS
    variable = phi
    property_user_object = potential_uo
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
    type = PhaseFieldPotential
    variable = phi
    mob_name = mobility
    block = 0
  [../]
  [./phi_transition]
    type = PhaseTransition
    variable = phi
    mob_name = mobility
    chemical_potential = u
    block = 0
  [../]
[]

[AuxKernels]
  active = 'T_exact u_exact'
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
  [../]
[]

[BCs]
  [./all]
    type = FunctionDirichletBC
    variable = phi
    boundary = 'bottom left right top'
    function = phi_func
  [../]
[]

[Materials]
  [./air]
    type = AirProperties
    block = 0
    property_user_object = potential_uo
  [../]
  [./constants]
    type = ConstantProperties
    block = 0
  [../]
  [./ice]
    type = IceProperties
    block = 0
    property_user_object = potential_uo
  [../]
  [./phase_field]
    type = PhaseFieldProperties
    block = 0
    phi = phi
    property_user_object = potential_uo
    temperature = T
  [../]
[]

[Postprocessors]
  [./L2_errror]
    type = ElementL2Error
    variable = u
    function = u_func
  [../]
[]

[UserObjects]
  [./potential_uo]
    type = ChemicalPotentialPropertyUserObject
  [../]
[]

[Executioner]
  type = Transient
  num_steps = 10
  dt = 0.1
[]

[Outputs]
  active = ''
  output_initial = true
  exodus = true
  console = true
  [./oversample]
    refinements = 2
    oversample = true
    type = Exodus
  [../]
[]

[ICs]
  [./u_ic]
    function = u_func
    variable = u
    type = FunctionIC
  [../]
  [./phi_ic]
    function = phi_func
    variable = phi
    type = FunctionIC
  [../]
  [./T_IC]
    function = T_func
    variable = T
    type = FunctionIC
    block = 0
  [../]
[]

